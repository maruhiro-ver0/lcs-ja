/*
This file is part of Liberal Crime Squad.                                           //
                                                                                    //
    Liberal Crime Squad is free software; you can redistribute it and/or modify     //
    it under the terms of the GNU General Public License as published by            //
    the Free Software Foundation; either version 2 of the License, or               //
    (at your option) any later version.                                             //
                                                                                    //
    Liberal Crime Squad is distributed in the hope that it will be useful,          //
    but WITHOUT ANY WARRANTY; without even the implied warranty of                  //
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.   See the                  //
    GNU General Public License for more details.                                    //
                                                                                    //
    You should have received a copy of the GNU General Public License               //
    along with Liberal Crime Squad; if not, write to the Free Software              //
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA   02111-1307   USA     //
*/

#include <externs.h>

/* base - activate sleepers */
void activate_sleepers()
{
   vector<Creature *> temppool;
   // Comb the pool of Liberals for sleeper agents
   for(int p=0;p<len(pool);p++)
   {
      // Select only sleepers that can work
      if(pool[p]->alive==true&&
         pool[p]->flag & CREATUREFLAG_SLEEPER&&
         pool[p]->align==ALIGN_LIBERAL&&
         pool[p]->hiding==false&&
         pool[p]->clinic==false&&
         pool[p]->dating==false)
      {
         temppool.push_back(pool[p]);
      }
   }

   if(!len(temppool)) return;

   sortliberals(temppool,activesortingchoice[SORTINGCHOICE_ACTIVATESLEEPERS]);

   int page=0;

   while(true)
   {
      music.play(MUSIC_SLEEPERS);
      clear();

      set_color(COLOR_WHITE,COLOR_BLACK,0);
      printfunds();

      move(0,0);
      addstr("潜伏者のスパイ活動");
      makedelimiter(1);
      move(1,4);
      addstr("コードネーム");
      move(1,25);
      addstr("職業");
      move(1,42);
      addstr("場所");
      move(1,57);
      addstr("活動");

      int y=2;
      for(int p=page*9;p<len(temppool)&&p<page*9+9;p++,y+=2)
      {
         set_color(COLOR_WHITE,COLOR_BLACK,0);
         mvaddchar(y,0,(y-2)/2+'A');addstr(" - ");
         addstr(to_half(temppool[p]->name));

         move(y,25);
         addstr(temppool[p]->get_type_name());

         move(y+1,6);
         addstr("有効性: ");

         if(temppool[p]->infiltration > 0.8f)
            set_color(COLOR_RED,COLOR_BLACK,1);
         else if(temppool[p]->infiltration > 0.6f)
            set_color(COLOR_MAGENTA,COLOR_BLACK,1);
         else if(temppool[p]->infiltration > 0.4f)
            set_color(COLOR_YELLOW,COLOR_BLACK,1);
         else if(temppool[p]->infiltration > 0.2f)
            set_color(COLOR_WHITE,COLOR_BLACK,1);
         else if(temppool[p]->infiltration > 0.1f)
            set_color(COLOR_WHITE,COLOR_BLACK,0);
         else set_color(COLOR_GREEN,COLOR_BLACK,0);
         addstr(static_cast<long>(temppool[p]->infiltration*100+0.5)); // gets rounded to nearest integer
         addstr("%");

         set_color(COLOR_WHITE,COLOR_BLACK,0);
         mvaddstr(y,42,location[temppool[p]->worklocation]->getname(true, true));

         move(y,57);
         // Let's add some color here...
         set_activity_color(temppool[p]->activity.type);
         addstr(getactivity(temppool[p]->activity));
      }

      set_color(COLOR_WHITE,COLOR_BLACK,0);
      move(22,0);
      addstr("アルファベットキーで活動を割り当てる。");
      move(23,0);
      addpagestr();
      addstr(" T - ソートする");

      set_color(COLOR_WHITE,COLOR_BLACK,0);

      int c=getkey();

      //PAGE UP
      if((c==interface_pgup||c==KEY_UP||c==KEY_LEFT)&&page>0) page--;
      //PAGE DOWN
      if((c==interface_pgdn||c==KEY_DOWN||c==KEY_RIGHT)&&(page+1)*9<len(temppool)) page++;

      if(c>='a'&&c<='s')
      {
         int p=page*9+(int)(c-'a');
         if(p<len(temppool))
            activate_sleeper(temppool[p]);
      }

      if(c=='t')
      {
         sorting_prompt(SORTINGCHOICE_ACTIVATESLEEPERS);
         sortliberals(temppool,activesortingchoice[SORTINGCHOICE_ACTIVATESLEEPERS],true);
      }

      if(c=='x'||c==ENTER||c==ESC||c==SPACEBAR) break;
   }
}


void activate_sleeper(Creature *cr)
{
   int state=0,choice=0;

   while(true)
   {
      clear();

      set_color(COLOR_WHITE,COLOR_BLACK,0);
      printfunds();

      move(0,0);
      addstr("スパイ活動: ");
      addstr(cr->name);
      addstr("は何に注力するか?");

      printcreatureinfo(cr);

      makedelimiter();

      set_color(COLOR_WHITE,COLOR_BLACK,state=='a');
      move(10,1);
      addstr("A - ロビー活動");

      set_color(COLOR_WHITE,COLOR_BLACK,state=='b');
      move(11,1);
      addstr("B - 諜報活動");

      set_color(COLOR_WHITE,COLOR_BLACK,state=='c');
      move(12,1);
      addstr("C - LCSに加える");

      set_color(COLOR_WHITE,COLOR_BLACK,0);
      move(20,40);
      addstr("Enter - 決定");

      switch(state)
      {
      case 'a':
         set_color(COLOR_WHITE,COLOR_BLACK,cr->activity.type==ACTIVITY_NONE);
         move(10,40);
         addstr("1 - 潜伏");

         set_color(COLOR_WHITE,COLOR_BLACK,cr->activity.type==ACTIVITY_SLEEPER_LIBERAL);
         move(11,40);
         addstr("2 - リベラル主義の推進");

         move(12,40);
         if(subordinatesleft(*cr))
         {
            set_color(COLOR_WHITE,COLOR_BLACK,cr->activity.type==ACTIVITY_SLEEPER_RECRUIT);
            addstr("3 - 潜伏者のネットワークを広げる");
         }
         else
         {
            set_color(COLOR_BLACK,COLOR_BLACK,1);
            if(cr->flag & CREATUREFLAG_BRAINWASHED)
               addstr("3 - [啓蒙された者はスカウトできない]");
            else addstr("3 - [スカウトにはもっとジュースが必要だ]");
         }
         break;
      case 'b':
         set_color(COLOR_WHITE,COLOR_BLACK,cr->activity.type==ACTIVITY_SLEEPER_SPY);
         move(10,40);
         addstr("1 - 機密を探る");

         set_color(COLOR_WHITE,COLOR_BLACK,cr->activity.type==ACTIVITY_SLEEPER_EMBEZZLE);
         move(11,40);
         addstr("2 - 資金を横領する");

         set_color(COLOR_WHITE,COLOR_BLACK,cr->activity.type==ACTIVITY_SLEEPER_STEAL);
         move(12,40);
         addstr("3 - 設備を盗む");
         break;
      }

      set_color(COLOR_WHITE,COLOR_BLACK,0);
      switch(cr->activity.type)
      {
      case ACTIVITY_NONE:
         move(22,3);
         addstr(cr->name);
         addstr("はトラブルを起こさないように潜伏する。");
         break;
      case ACTIVITY_SLEEPER_LIBERAL:
         move(22,3);
         addstr(cr->name);
         addstr("はリベラルへの支持を拡大する。");
         break;
      case ACTIVITY_SLEEPER_RECRUIT:
         if(subordinatesleft(*cr))
         {
            move(22,3);
            addstr(cr->name);
            addstr("は新たな潜伏者のスカウトを試みる。");
         }
         break;
      case ACTIVITY_SLEEPER_SPY:
         move(22,3);
         addstr(cr->name);
         addstr("は機密と敵の作戦を探る。");
         break;
      case ACTIVITY_SLEEPER_EMBEZZLE:
         move(22,3);
         addstr(cr->name);
         addstr("はLCSのために資金を横領する。");
         break;
      case ACTIVITY_SLEEPER_STEAL:
         move(22,3);
         addstr(cr->name);
         addstr("は設備を盗みアジトに送る。");
         break;
      }

      int c=getkey();

      if(c>='a'&&c<='z') state=c;
      if((c>='a'&&c<='z') || (c>='1'&&c<='9'))
      {
         choice=c;
         switch(state)
         {
         case 'a':
            switch(choice)
            {
            default:
            case '1':cr->activity.type=ACTIVITY_NONE;break;
            case '2':cr->activity.type=ACTIVITY_SLEEPER_LIBERAL;break;
            case '3':
               if(subordinatesleft(*cr))
                  cr->activity.type=ACTIVITY_SLEEPER_RECRUIT;break;
            }
            break;
         case 'b':
            switch(choice)
            {
            default:
            case '1':cr->activity.type=ACTIVITY_SLEEPER_SPY;break;
            case '2':cr->activity.type=ACTIVITY_SLEEPER_EMBEZZLE;break;
            case '3':cr->activity.type=ACTIVITY_SLEEPER_STEAL;break;
            }
            break;
         }
      }

      if(state=='c')
      {
         //activityst oact=cr->activity;
         cr->activity.type=ACTIVITY_SLEEPER_JOINLCS;
      }
      if(c=='x')
      {
         cr->activity.type=ACTIVITY_NONE;
         break;
      }
      if(c==ENTER||c==ESC||c==SPACEBAR) break;
   }
}
