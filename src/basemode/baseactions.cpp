/*

Copyright (c) 2002,2003,2004 by Tarn Adams                                            //
//
This file is part of Liberal Crime Squad.                                             //
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

/*
This file was created by Chris Johnson (grundee@users.sourceforge.net)
by copying code from game.cpp.
To see descriptions of files and functions, see the list at
the bottom of includes.h in the top src folder.
*/

#include <externs.h>

/* base - burn the flag */
void burnflag()
{
   int flagparts=126,flag[18][7][4],x,y;

   for(y=0;y<7;y++) if(y<6) for(x=0;x<18;x++)
   {
      if(x<9&&y<4)
      {
         switch(y)
         {
         case 0: flag[x][y][0]=(x%2?'.':':'); break;
         default: flag[x][y][0]=':'; break;
         case 3: flag[x][y][0]=CH_LOWER_HALF_BLOCK; break;
         }
         flag[x][y][2]=COLOR_BLUE;
      }
      else
      {
         flag[x][y][0]=CH_LOWER_HALF_BLOCK;
         flag[x][y][2]=COLOR_RED;
      }
      flag[x][y][1]=COLOR_WHITE;
      flag[x][y][3]=1;
   }
   else for(x=0;x<18;x++)
   {
      flag[x][y][0]=CH_UPPER_HALF_BLOCK;
      flag[x][y][1]=COLOR_RED;
      flag[x][y][2]=COLOR_BLACK;
      flag[x][y][3]=0;
   }

   x=LCSrandom(18),y=LCSrandom(7);
   flag[x][y][0]=CH_DARK_SHADE;
   flag[x][y][1]=COLOR_YELLOW;
   flag[x][y][2]=COLOR_BLACK;
   flag[x][y][3]=1;

   bool first=true;

   while(flagparts>0)
   {
      if(!first) for(x=0;x<18;x++) for(y=0;y<7;y++)
      {
         if(flag[x][y][0]==CH_BOX_DRAWINGS_LIGHT_VERTICAL)flag[x][y][0]=CH_DARK_SHADE;
         else if(flag[x][y][0]==CH_DARK_SHADE)
         {
            flag[x][y][0]=CH_MEDIUM_SHADE;
            flag[x][y][1]=COLOR_RED;
            flag[x][y][2]=COLOR_BLACK;
            flag[x][y][3]=0;
         }
         else if(flag[x][y][0]==CH_MEDIUM_SHADE)
         {
            flag[x][y][0]=CH_LIGHT_SHADE;
            flag[x][y][1]=COLOR_BLACK;
            flag[x][y][2]=COLOR_BLACK;
            flag[x][y][3]=1;
         }
         else if(flag[x][y][0]==CH_LIGHT_SHADE)
         {
            flagparts--;
            flag[x][y][0]=' ';
            flag[x][y][1]=COLOR_BLACK;
            flag[x][y][2]=COLOR_BLACK;
            flag[x][y][3]=0;
         }
      }
      else first=false;

      for(x=0;x<18;x++) for(y=0;y<7;y++)
      {
         set_color(short(flag[x][y][1]),short(flag[x][y][2]),bool(flag[x][y][3]));
         mvaddch(y+10,x+31,flag[x][y][0]);
      }

      pause_ms(10);

      bool gotnew=false;
      while(!gotnew&&flagparts>3)
      {
         x=LCSrandom(18),y=LCSrandom(7);
         bool conf=false;
         if(flag[x][y][0]==':'||flag[x][y][0]=='.'||flag[x][y][0]==CH_UPPER_HALF_BLOCK||flag[x][y][0]==CH_LOWER_HALF_BLOCK)
         {
            if(x>0)
            {
               if(flag[x-1][y][0]!=':'&&
                  flag[x-1][y][0]!='.'&&
                  flag[x-1][y][0]!=CH_UPPER_HALF_BLOCK&&
                  flag[x-1][y][0]!=CH_LOWER_HALF_BLOCK) conf=true;
            }
            if(x<17)
            {
               if(flag[x+1][y][0]!=':'&&
                  flag[x+1][y][0]!='.'&&
                  flag[x+1][y][0]!=CH_UPPER_HALF_BLOCK&&
                  flag[x+1][y][0]!=CH_LOWER_HALF_BLOCK) conf=true;
            }
            if(y>0)
            {
               if(flag[x][y-1][0]!=':'&&
                  flag[x][y-1][0]!='.'&&
                  flag[x][y-1][0]!=CH_UPPER_HALF_BLOCK&&
                  flag[x][y-1][0]!=CH_LOWER_HALF_BLOCK) conf=true;
            }
            if(y<6)
            {
               if(flag[x][y+1][0]!=':'&&
                  flag[x][y+1][0]!='.'&&
                  flag[x][y+1][0]!=CH_UPPER_HALF_BLOCK&&
                  flag[x][y+1][0]!=CH_LOWER_HALF_BLOCK) conf=true;
            }
            if(conf)
            {
               flag[x][y][0]=CH_BOX_DRAWINGS_LIGHT_VERTICAL;
               flag[x][y][1]=COLOR_YELLOW;
               flag[x][y][2]=COLOR_BLACK;
               flag[x][y][3]=1;
               gotnew=true;
            }
         }
      }
   }
}

/* base - new slogan */
void getslogan()
{
   set_color(COLOR_WHITE,COLOR_BLACK,0);

   mvaddstr(16,0,"新しいスローガンは?");
   mvaddstr(17,0,"                                                                                          "); // 80 spaces

   enter_name(17,0,slogan,SLOGAN_LEN,"We need a slogan!");
}



/* base - reorder party */
void orderparty()
{
   party_status=-1;

   int partysize=squadsize(activesquad);

   if(partysize<=1) return;

   while(true)
   {
      printparty();
      set_color(COLOR_WHITE,COLOR_BLACK,1);
      mvaddstr(8,26,"移動させるメンバーを選択する ");

      int oldPos=getkey();

      if(oldPos<'1'||oldPos>partysize+'1'-1) return; // User chose index out of range, exit
      makedelimiter();
      set_color(COLOR_WHITE,COLOR_BLACK,1);
      std::string str="メンバーの移動先を選択する ";
      str+=activesquad->squad[oldPos-'1']->name;
      str+="は";
      str+=(char)oldPos;
      str+="にいる";
      int x=39-((len(str)-1)>>1);
      if(x<0) x=0;
      mvaddstr(8,x,str);

      int newPos=getkey();

      if(newPos<'1'||newPos>partysize+'1'-1) return; // User chose index out of range, exit
      swap(activesquad->squad[oldPos-'1'],activesquad->squad[newPos-'1']);
   }
}

/* base - go forth to stop evil */
void stopevil()
{
   int l=0,p=0;

   if(!activesquad) return;

   bool havecar=false;
   for(p=0;p<6;p++) if(activesquad->squad[p]) if(activesquad->squad[p]->pref_carid != -1)
   {
      havecar=true;
      break;
   }

   Location* squad_location=location[activesquad->squad[0]->location];

   int page=0,loc=-1;

   // Start at the city level, rather than the absolute top
   if(multipleCityMode) {
      for(l=0;l<len(location);l++) {
         if(location[l]->type == squad_location->city) {
            loc = l;
            break;
         }
      }
   }

   vector<long> temploc;
   // 1. LCS safe houses
   for(l=0;l<len(location);l++)
      if(location[l]->parent==loc && location[l]->renting>=0 && !location[l]->hidden)
         temploc.push_back(l);
   // 2. CCS safe houses
   for(l=0;l<len(location);l++)
      if(location[l]->parent==loc && location[l]->renting==RENTING_CCS && !location[l]->hidden)
         temploc.push_back(l);
   // 3. Other sites
   for(l=0;l<len(location);l++)
      if(location[l]->parent==loc && location[l]->renting==RENTING_NOCONTROL && !location[l]->hidden)
         temploc.push_back(l);

   // Determine cost of tickets for travel
   int ticketprice=100*squadsize(activesquad);

   while(true)
   {
      music.play(MUSIC_STOPEVIL);
      erase();

      set_color(COLOR_WHITE,COLOR_BLACK,0);
      mvaddstr(0,0,"部隊はどこへ向かうか?");

      printparty();

      if(loc!=-1)
      {
         set_color(COLOR_WHITE,COLOR_BLACK,0);
         mvaddstr(8,0,location[loc]->getname(-1, true));
      }

      /*mvaddstr(12,50,"Z - Toggle Squad Stance");
      switch(activesquad->stance)
      {
      case SQUADSTANCE_ANONYMOUS:
         set_color(COLOR_WHITE,COLOR_BLACK,1);
         mvaddstr(13,50,"ANONYMOUS ACTION");
         set_color(COLOR_BLACK,COLOR_BLACK,1);
         mvaddstr(14,50,"+ Less Likely to be identified");
         mvaddstr(15,50,"- Can't gain Juice");
         mvaddstr(16,50,"- Unlikely to affect issues");
         break;
      case SQUADSTANCE_STANDARD:
         set_color(COLOR_GREEN,COLOR_BLACK,1);
         mvaddstr(13,50,"CLAIMED ACTION");
         set_color(COLOR_BLACK,COLOR_BLACK,1);
         mvaddstr(14,50,"+ Can sneak and bluff");
         mvaddstr(15,50,"+ Can gain juice");
         mvaddstr(16,50,"+ Can affect issues");
         break;
      case SQUADSTANCE_BATTLECOLORS:
         set_color(COLOR_GREEN,COLOR_BLACK,1);
         mvaddstr(13,50,"GREEN ARMBANDS");
         set_color(COLOR_BLACK,COLOR_BLACK,1);
         mvaddstr(14,50,"- Alarm conservatives on sight");
         mvaddstr(15,50,"+ Gain extra juice");
         mvaddstr(16,50,"+ Bonus issue effects");
         break;
      }*/

      temploc.clear();
      for(l=0;l<len(location);l++)
         if(location[l]->parent==loc&&location[l]->renting>=0&&!location[l]->hidden)temploc.push_back(l);
      for(l=0;l<len(location);l++)
         if(location[l]->parent==loc&&location[l]->renting==RENTING_CCS&&!location[l]->hidden)temploc.push_back(l);
      for(l=0;l<len(location);l++)
         if(location[l]->parent==loc&&location[l]->renting==RENTING_NOCONTROL&&!location[l]->hidden)temploc.push_back(l);

      int y=10;
      for(p=page*11;p<len(temploc)&&p<page*11+11;p++)
      {
         if(p==-1) break;
         Location* this_location=location[temploc[p]];

         set_color(COLOR_WHITE,COLOR_BLACK,0);
         mvaddchar(y,0,y-10+'A');
         addstr(" - ");
         addstr(location[temploc[p]]->getname());

         bool show_safehouse_info=false;
         if(this_location == squad_location) {
            set_color(COLOR_WHITE,COLOR_BLACK,1);
            addstr(" (現在地)");
            show_safehouse_info=true;
         } else if(this_location->renting >= 0) {
            set_color(COLOR_GREEN,COLOR_BLACK,1);
            addstr(" (アジト)");
            show_safehouse_info=true;
         } else if(this_location->renting == RENTING_CCS) {
            set_color(COLOR_RED,COLOR_BLACK,1);
            addstr(" (空のアジト)");
         } else if(this_location->closed) {
            set_color(COLOR_RED,COLOR_BLACK,1);
            addstr(" (閉鎖)");
         } else if(this_location->highsecurity) {
            set_color(COLOR_MAGENTA,COLOR_BLACK,1);
            addstr(" (高セキュリティ)");
         } else if(multipleCityMode && this_location->type == squad_location->city) {
            set_color(COLOR_WHITE,COLOR_BLACK,1);
            addstr(" (現在地)");
         } else if(this_location->area != squad_location->area && !havecar) {
            set_color(COLOR_YELLOW,COLOR_BLACK,1);
            addstr(" (要自動車)");
         } else if(this_location->type == SITE_TRAVEL) {
            if(ledger.get_funds() < ticketprice)
               set_color(COLOR_RED,COLOR_BLACK,1);
            else
               set_color(COLOR_GREEN,COLOR_BLACK,1);
            addstr(" ($"+tostring(ticketprice)+")");
         }
         if(this_location->siege.siege > 0) {
            set_color(COLOR_RED,COLOR_BLACK,0);
            addstr(" (包囲中)");
         }

         if(show_safehouse_info)
         {
            this_location->update_heat_protection();

            set_color(COLOR_WHITE,COLOR_BLACK,0);
            mvaddstr(y,54,"危険: ");
            if(this_location->heat > this_location->heat_protection)
               set_color(COLOR_YELLOW,COLOR_BLACK,1);
            else set_color(COLOR_BLACK,COLOR_BLACK,1);
            addstr(this_location->heat);
            addstr("%");
            set_color(COLOR_WHITE,COLOR_BLACK,0);
            move(y,66);
            addstr("隠蔽: ");
            if(this_location->heat > this_location->heat_protection)
               set_color(COLOR_YELLOW,COLOR_BLACK,1);
            else set_color(COLOR_BLACK,COLOR_BLACK,1);
            addstr(this_location->heat_protection);
            addstr("%");
         }

         if(multipleCityMode && this_location->city == this_location->type)
         {
            set_color(COLOR_BLACK,COLOR_BLACK,1);
            mvaddstr(y,50,this_location->city_description());
         }

         y++;
      }
      if(multipleCityMode && loc != -1 && location[loc]->type == location[loc]->city)
      {
         set_color(COLOR_WHITE,COLOR_BLACK,0);
         mvaddchar(y+1,0,y-10+'A');
         addstr(" - 別の都市へ行く");
         if(!havecar) {
            set_color(COLOR_YELLOW,COLOR_BLACK,1);
            addstr(" (要自動車)");
         } else {
            if(ledger.get_funds() < ticketprice)
               set_color(COLOR_RED,COLOR_BLACK,1);
            else set_color(COLOR_GREEN,COLOR_BLACK,1);
            addstr(" ($"+tostring(ticketprice)+")");
         }
         temploc.push_back(-1);
      }

      set_color(COLOR_WHITE,COLOR_BLACK,0);
      //PAGE UP
      if(page>0)
      {
         move(10,60);
         addprevpagestr();
      }
      //PAGE DOWN
      if((page+1)*11<len(temploc))
      {
         move(20,60);
         addnextpagestr();
      }

      set_color(COLOR_WHITE,COLOR_BLACK,0);
      move(24,1);
      if((loc == -1) || (multipleCityMode && location[loc]->type == squad_location->city)) addstr("Enter - 部隊はまだ十分にはリベラルでない");
      else addstr("Enter - 1段階戻る");

      int c=getkey();

      //PAGE UP
      if((c==interface_pgup||c==KEY_UP||c==KEY_LEFT)&&page>0) page--;
      //PAGE DOWN
      if((c==interface_pgdn||c==KEY_DOWN||c==KEY_RIGHT)&&(page+1)*11<len(temploc)) page++;

      if(c>='a'&&c<='k')
      {
         int sq=page*11+c-'a';
         if(sq<len(temploc)&&sq>=0)
         {
            int oldloc=loc;
            loc=temploc[sq];
            if((loc==-1 || (multipleCityMode && location[loc]->city != squad_location->city)) && !havecar)
               loc=oldloc;
            int subcount = 0;

            for(l=0;l<len(location);l++)
               if(location[l]->parent==loc)
                  subcount++;

            if(subcount==0 || (multipleCityMode && loc >= 0 && location[loc]->city != squad_location->city))
            {
               if(!location[loc]->closed&&
                  ((location[loc]->area==squad_location->area&&location[loc]->city==squad_location->city)||havecar))
               {
                  activesquad->activity.type=ACTIVITY_VISIT;
                  activesquad->activity.arg=loc;
                  return;
               }
               else loc=oldloc;
            }
         }
      }

      /*if(c=='z')
      {
      activesquad->stance++;
      if(activesquad->stance>SQUADSTANCE_STANDARD)
      activesquad->stance=0;
      }*/

      if(c=='x'||c==ENTER||c==ESC||c==SPACEBAR)
      {
         if(loc!=-1 && (location[loc]->city != location[loc]->type || location[loc]->city != squad_location->city))
            loc=location[loc]->parent;
         else
         {
            activesquad->activity.type=ACTIVITY_NONE; // Clear squad activity
            break;
         }
      }
   }
}



/* base - invest in this location */
void investlocation()
{
   int loc=selectedsiege;

   while(true)
   {
      erase();

      locheader();
      printlocation(loc);

      if(location[loc]->can_be_fortified())
      {
         if(ledger.get_funds()>=2000) set_color(COLOR_WHITE,COLOR_BLACK,0);
         else set_color(COLOR_BLACK,COLOR_BLACK,1);
         move(8,1);
         if(location[loc]->type == SITE_OUTDOOR_BUNKER)
            addstr("W - 壕を修理する ($2000)");
         else if(location[loc]->type == SITE_RESIDENTIAL_BOMBSHELTER)
            addstr("W - 防空壕の入り口を要塞化する ($2000)");
         else
            addstr("W - 包囲に備えて要塞化する ($2000)");
      }

      if(!(location[loc]->compound_walls & COMPOUND_CAMERAS))
      {
         if(ledger.get_funds()>=2000) set_color(COLOR_WHITE,COLOR_BLACK,0);
         else set_color(COLOR_BLACK,COLOR_BLACK,1);
         move(9,1);
         addstr("C - 周りに監視カメラを配置する ($2000)");
      }

      if(location[loc]->can_be_trapped())
      {
         if(ledger.get_funds()>=3000) set_color(COLOR_WHITE,COLOR_BLACK,0);
         else set_color(COLOR_BLACK,COLOR_BLACK,1);
         move(10,1);
         addstr("B - 周りにブービートラップを配置する ($3000)");
      }

      if(location[loc]->can_install_tanktraps())
      {
         if(ledger.get_funds()>=3000) set_color(COLOR_WHITE,COLOR_BLACK,0);
         else set_color(COLOR_BLACK,COLOR_BLACK,1);
         move(11,1);
         addstr("T - 対戦車障害物で囲む ($3000)");
      }

      if(!(location[loc]->compound_walls & COMPOUND_GENERATOR))
      {
         if(ledger.get_funds()>=3000) set_color(COLOR_WHITE,COLOR_BLACK,0);
         else set_color(COLOR_BLACK,COLOR_BLACK,1);
         move(12,1);
         addstr("G - 非常用発電機を購入する ($3000)");
      }

      if(!(location[loc]->compound_walls & COMPOUND_AAGUN))
      {
         if(law[LAW_GUNCONTROL]==ALIGN_ARCHCONSERVATIVE)
         {
            if(ledger.get_funds()>=35000) set_color(COLOR_WHITE,COLOR_BLACK,0);
            move(13,1);
            addstr("A - 屋根の上に合法的に対空砲を配備する ($35,000)");
         }
         else
         {
            if(ledger.get_funds()>=200000) set_color(COLOR_WHITE,COLOR_BLACK,0);
            else set_color(COLOR_BLACK,COLOR_BLACK,1);
            move(13,1);
            addstr("A - 屋根の上に違法に対空砲を配備する ($200,000)");
         }
      }

      if(!(location[loc]->compound_walls & COMPOUND_PRINTINGPRESS))
      {
         if(ledger.get_funds()>=3000) set_color(COLOR_WHITE,COLOR_BLACK,0);
         else set_color(COLOR_BLACK,COLOR_BLACK,1);
         move(14,1);
         addstr("P - 新聞を発行するために印刷機を購入する ($3000)");
      }

      if(location[loc]->can_have_businessfront())
      {
         if(ledger.get_funds()>=3000) set_color(COLOR_WHITE,COLOR_BLACK,0);
         else set_color(COLOR_BLACK,COLOR_BLACK,1);
         move(15,1);
         addstr("F - ビジネス・オフィスで偽装する ($3000)");
      }

      if(ledger.get_funds()>=150) set_color(COLOR_WHITE,COLOR_BLACK,0);
      else set_color(COLOR_BLACK,COLOR_BLACK,1);
      move(16,1);
      addstr("R - 20日分の食料を蓄える ($150)");

      move(17,1);
      addstr("Enter - 完了");

      int c=getkey();

      if(c=='x'||c==ENTER||c==ESC||c==SPACEBAR) break;

      if(c=='w')
      {
         if(location[loc]->can_be_fortified()&&ledger.get_funds()>=2000)
         {
            ledger.subtract_funds(2000,EXPENSE_COMPOUND);
            location[loc]->compound_walls|=COMPOUND_BASIC;
         }
      }

      if(c=='c')
      {
         if(!(location[loc]->compound_walls & COMPOUND_CAMERAS)&&ledger.get_funds()>=2000)
         {
            ledger.subtract_funds(2000,EXPENSE_COMPOUND);
            location[loc]->compound_walls|=COMPOUND_CAMERAS;
         }
      }

      if(c=='b')
      {
         if(location[loc]->can_be_trapped()&&ledger.get_funds()>=3000)
         {
            ledger.subtract_funds(3000,EXPENSE_COMPOUND);
            location[loc]->compound_walls|=COMPOUND_TRAPS;
         }
      }

      if(c=='t')
      {
         if(location[loc]->can_install_tanktraps()&&ledger.get_funds()>=3000)
         {
            ledger.subtract_funds(3000,EXPENSE_COMPOUND);
            location[loc]->compound_walls|=COMPOUND_TANKTRAPS;
         }
      }

      if(c=='g')
      {
         if(!(location[loc]->compound_walls & COMPOUND_GENERATOR)&&ledger.get_funds()>=3000)
         {
            ledger.subtract_funds(3000,EXPENSE_COMPOUND);
            location[loc]->compound_walls|=COMPOUND_GENERATOR;
         }
      }

      if(c=='a')
      {
         int aagunPrice = 200000;
         if(law[LAW_GUNCONTROL]==ALIGN_ARCHCONSERVATIVE)
            aagunPrice = 35000;

         if(!(location[loc]->compound_walls & COMPOUND_AAGUN)&&ledger.get_funds()>=aagunPrice)
         {
            ledger.subtract_funds(aagunPrice,EXPENSE_COMPOUND);
            location[loc]->compound_walls|=COMPOUND_AAGUN;
         }
      }

      if(c=='p')
      {
         if(!(location[loc]->compound_walls & COMPOUND_PRINTINGPRESS)&&ledger.get_funds()>=3000)
         {
            ledger.subtract_funds(3000,EXPENSE_COMPOUND);
            location[loc]->compound_walls|=COMPOUND_PRINTINGPRESS;
         }
      }

      if(c=='r')
      {
         if(ledger.get_funds()>=150)
         {
            ledger.subtract_funds(150,EXPENSE_COMPOUND);
            location[loc]->compound_stores+=20;
         }
      }

      if(c=='f')
      {
         if(location[loc]->can_have_businessfront()&&ledger.get_funds()>=3000)
         {
            ledger.subtract_funds(3000,EXPENSE_COMPOUND);
            do
            {
               location[loc]->front_business=LCSrandom(BUSINESSFRONTNUM);
               lastname(location[loc]->front_name,true);
               switch(location[loc]->front_business)
               {
               case BUSINESSFRONT_INSURANCE:
                  switch(LCSrandom(7))
                  {
                  case 0:
                     strcat(location[loc]->front_name,"自動車");
                     strcpy(location[loc]->front_shortname,"自動車");
                     break;
                  case 1:
                     strcat(location[loc]->front_name,"生命");
                     strcpy(location[loc]->front_shortname,"生命");
                     break;
                  case 2:
                     strcat(location[loc]->front_name,"医療");
                     strcpy(location[loc]->front_shortname,"医療");
                     break;
                  case 3:
                     strcat(location[loc]->front_name,"住宅");
                     strcpy(location[loc]->front_shortname,"住宅");
                     break;
                  case 4:
                     strcat(location[loc]->front_name,"船舶");
                     strcpy(location[loc]->front_shortname,"船舶");
                     break;
                  case 5:
                     strcat(location[loc]->front_name,"火災");
                     strcpy(location[loc]->front_shortname,"火災");
                     break;
                  case 6:
                     strcat(location[loc]->front_name,"水害");
                     strcpy(location[loc]->front_shortname,"水害");
                     break;
                  }
                  strcat(location[loc]->front_name,"保険");
                  strcat(location[loc]->front_shortname,"保険");
                  break;
               case BUSINESSFRONT_TEMPAGENCY:
                  switch(LCSrandom(7))
                  {
                  case 0:
                     strcat(location[loc]->front_name,"人材派遣");
                     strcpy(location[loc]->front_shortname,"派遣");
                     break;
                  case 1:
                     strcat(location[loc]->front_name,"ﾏﾝﾊﾟﾜｰLLC");
                     strcpy(location[loc]->front_shortname,"ﾏﾝﾊﾟﾜｰ");
                     break;
                  case 2:
                     strcat(location[loc]->front_name,"ｽﾀｯﾌｨﾝｸﾞInc");
                     strcpy(location[loc]->front_shortname,"ｽﾀｯﾌｨﾝｸﾞ");
                     break;
                  case 3:
                     strcat(location[loc]->front_name,"ﾚｲﾊﾞｰ･ﾚﾃﾞｨｰ");
                     strcpy(location[loc]->front_shortname,"ﾚｲﾊﾞｰ");
                     break;
                  case 4:
                     strcat(location[loc]->front_name,"ｴﾝﾌﾟﾛｲﾒﾝﾄ");
                     strcpy(location[loc]->front_shortname,"ｴﾝﾌﾟﾛｲ");
                     break;
                  case 5:
                     strcat(location[loc]->front_name,"ｻｰﾋﾞｼｰｽﾞ");
                     strcpy(location[loc]->front_shortname,"ｻｰﾋﾞｽ");
                     break;
                  case 6:
                     strcat(location[loc]->front_name,"ｿﾘｭｰｼｮﾝｽﾞ");
                     strcpy(location[loc]->front_shortname,"ｿﾘｭｰｼｮﾝｽﾞ");
                     break;
                  }
                  break;
               case BUSINESSFRONT_RESTAURANT:
                  switch(LCSrandom(7))
                  {
                  case 0:
                     strcat(location[loc]->front_name,"ﾌﾗｲﾄﾞﾁｷﾝ");
                     strcpy(location[loc]->front_shortname,"ﾁｷﾝ");
                     break;
                  case 1:
                     strcat(location[loc]->front_name,"ﾊﾝﾊﾞｰｶﾞｰ");
                     strcpy(location[loc]->front_shortname,"ﾊﾞｰｶﾞｰ");
                     break;
                  case 2:
                     strcat(location[loc]->front_name,"ｽﾃｰｷﾊｳｽ");
                     strcpy(location[loc]->front_shortname,"ｽﾃｰｷ");
                     break;
                  case 3:
                     strcat(location[loc]->front_name,"中華料理");
                     strcpy(location[loc]->front_shortname,"中華");
                     break;
                  case 4:
                     strcat(location[loc]->front_name,"タイ料理");
                     strcpy(location[loc]->front_shortname,"タイ");
                     break;
                  case 5:
                     strcat(location[loc]->front_name,"ピザ");
                     strcpy(location[loc]->front_shortname,"ピザ");
                     break;
                  case 6:
                     strcat(location[loc]->front_name,"ﾚｽﾄﾗﾝ");
                     strcpy(location[loc]->front_shortname,"ﾚｽﾄﾗﾝ");
                     break;
                  }
                  break;
               case BUSINESSFRONT_MISCELLANEOUS:
                  switch(LCSrandom(7))
                  {
                  case 0:
                     strcat(location[loc]->front_name,"不動産");
                     strcpy(location[loc]->front_shortname,"不動産");
                     break;
                  case 1:
                     strcat(location[loc]->front_name,"輸入雑貨");
                     strcpy(location[loc]->front_shortname,"雑貨");
                     break;
                  case 2:
                     strcat(location[loc]->front_name,"廃棄物処理");
                     strcpy(location[loc]->front_shortname,"廃棄物");
                     break;
                  case 3:
                     strcat(location[loc]->front_name,"酒店");
                     strcpy(location[loc]->front_shortname,"酒店");
                     break;
                  case 4:
                     strcat(location[loc]->front_name,"ｱﾝﾃｨｰｸ");
                     strcpy(location[loc]->front_shortname,"ｱﾝﾃｨｰｸ");
                     break;
                  case 5:
                     strcat(location[loc]->front_name,"修理屋");
                     strcpy(location[loc]->front_shortname,"修理");
                     break;
                  case 6:
                     strcat(location[loc]->front_name,"ﾍﾟｯﾄｼｮｯﾌﾟ");
                     strcpy(location[loc]->front_shortname,"ﾍﾟｯﾄ");
                     break;
                  }
                  break;
               }
            } while(location[loc]->duplicatelocation());
         }
      }
   }
}



/* base - assign a vehicle to this squad */
void setvehicles()
{
   int p,l;
   if(!activesquad) return;

   int page=0;

   while(true)
   {
      erase();

      set_color(COLOR_WHITE,COLOR_BLACK,1);
      mvaddstr(0,0,"リベラル自動車の選択");

      printparty();

      int x=1,y=10;
      char str[200];

      for(l=page*18;l<len(vehicle)&&l<page*18+18;l++)
      {
         bool this_squad=false,another_squad=false;
         for(p=0;p<6;p++)
         {
            if(activesquad->squad[p]==NULL) continue;
            if(activesquad->squad[p]->alive&&
               activesquad->squad[p]->pref_carid==vehicle[l]->id())
            {
               this_squad=true;
               break;
            }
         }
         for(p=0;p<len(pool);p++)
         {
            if(pool[p]->squadid!=-1&&pool[p]->alive&&
               pool[p]->pref_carid==vehicle[l]->id()&&pool[p]->squadid!=activesquad->id)
            {
               another_squad=true;
               break;
            }
         }

         if(this_squad&&another_squad)
            set_color(COLOR_RED,COLOR_BLACK,1);
         else if(another_squad)
            set_color(COLOR_YELLOW,COLOR_BLACK,1);
         else if(this_squad)
            set_color(COLOR_GREEN,COLOR_BLACK,1);
         else
            set_color(COLOR_WHITE,COLOR_BLACK,0);

         str[0]=l-page*18+'A';
         str[1]='\x0';
         strcat(str," - ");
         strcat(str,vehicle[l]->fullname(true));

         mvaddstr(y,x,str);

         x+=26;
         if(x>53) x=1,y++;
      }

      set_color(COLOR_WHITE,COLOR_BLACK,0);
      //PAGE UP
      if(page>0)
      {
         move(17,1);
         addprevpagestr();
      }
      //PAGE DOWN
      if((page+1)*18<len(vehicle))
      {
         move(17,53);
         addnextpagestr();
      }

      mvaddstr(18,1,"アルファベットキーでそのリベラル車に乗る者を設定できる。");
      mvaddstr(19,1,"SHIFT+アルファベットキーで運転手を割り当てる。");
      mvaddstr(20,1,"数字キーでメンバーを車から除く。");
      mvaddstr(21,1,"メモ:  黄色の車は既に別の部隊が選択している。");
      mvaddstr(22,1,"       赤色の車は複数の部隊が選択している。この場合、それぞれの部隊が");
      mvaddstr(23,1,"       車を使うが、同じ日には使えない。");
      mvaddstr(24,1,"Enter - 完了");

      int c=getkey_cap();

      if(c>='A'&&c<='R')
      {
         int slot=c-'A'+page*18;

         if(slot>=0&&slot<len(vehicle))
         {
            bool choice=true;
            if(activesquad->squad[0])
            {
               choice=false;
               for(int c=1; c<6; c++)
               {
                  if(activesquad->squad[c]) //are these slots always filled in order?
                  {
                     choice=true;
                     break;
                  }
               }
            }
            int c='1';
            if(choice)
            {
               set_color(COLOR_WHITE,COLOR_BLACK,1);
               mvaddstr(8,20,"この自動車を運転する者を選択する");

               c=getkey();
            }

            if(c>='1'&&c<='6')
            {
               if(activesquad->squad[c-'1']!=NULL)
               {
                  activesquad->squad[c-'1']->pref_carid=vehicle[slot]->id();
                  if(activesquad->squad[c-'1']->canwalk())
                     activesquad->squad[c-'1']->pref_is_driver=1;
                  else activesquad->squad[c-'1']->pref_is_driver=0;
               }
            }
         }
      }

      if(c>='a'&&c<='r')
      {
         int slot=c-'a'+page*18;

         if(slot>=0&&slot<len(vehicle))
         {
            bool choice=true;
            if(activesquad->squad[0])
            {
               choice=false;
               for(int c=1; c<6; c++)
               {
                  if(activesquad->squad[c]) //are these slots always filled in order?
                  {
                     choice=true;
                     break;
                  }
               }
            }
            int c='1';
            if(choice)
            {
               set_color(COLOR_WHITE,COLOR_BLACK,1);
               mvaddstr(8,20,"この自動車に乗る者を選択する");

               c=getkey();
            }

            if(c>='1'&&c<='6')
            {
               if(activesquad->squad[c-'1'])
               {
                  activesquad->squad[c-'1']->pref_carid=vehicle[slot]->id();
                  activesquad->squad[c-'1']->pref_is_driver=0;
               }
            }
         }
      }

      //SAV - adding way to remove people from vehicles.
      if(c>='1'&&c<='6')
      {
         // 1. Is there someone there?
         if(activesquad->squad[c-'1'])
         {
            // 2. Are they in a vehicle? Someday we'll want to enforce car capacity
            int vin=activesquad->squad[c-'1']->pref_carid;
            if(vin>-1)
            {
               activesquad->squad[c-'1']->pref_carid=-1;
               activesquad->squad[c-'1']->pref_is_driver=0;
            }
         }
      }
      //SAV - End add

      //PAGE UP
      if((c==interface_pgup||c==KEY_UP||c==KEY_LEFT)&&page>0) page--;
      //PAGE DOWN
      if((c==interface_pgdn||c==KEY_DOWN||c==KEY_RIGHT)&&(page+1)*18<len(vehicle)) page++;

      if(c=='x'||c=='X'||c==ENTER||c==ESC||c==SPACEBAR) return;
   }
}
