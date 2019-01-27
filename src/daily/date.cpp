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

enum DateResults
{
   DATERESULT_MEETTOMORROW,
   DATERESULT_BREAKUP,
   DATERESULT_JOINED,
   DATERESULT_ARRESTED
};

// Handles the result of a date or vacation
static int dateresult(int aroll,int troll,datest &d,int e,int p,int y)
{
   music.play(MUSIC_DATING);
   std::string s = "";
   if(aroll>troll)
   {
      set_color(COLOR_CYAN,COLOR_BLACK,1);
      move(y,0);y++;
      addstr(d.date[e]->name, gamelog);
      addstr("は", gamelog);
      addstr(pool[p]->name, gamelog);
      addstr("の独自の人生哲学に引き付けられた…", gamelog);
      gamelog.newline();

      getkey();

      if(loveslavesleft(*pool[p]) <= 0)
      {
         set_color(COLOR_YELLOW,COLOR_BLACK,1);

         move(y++,0);
         addstr("しかし", gamelog);
         addstr(pool[p]->name, gamelog);
         addstr("は既に", gamelog);
         int num_relationships=loveslaves(*pool[p]);
         if(pool[p]->flag&CREATUREFLAG_LOVESLAVE) num_relationships++;
         if(num_relationships==1) addstr("誰かと付き合っている!", gamelog);
         else addstr(tostring(num_relationships)+"人と付き合っている!", gamelog);
         gamelog.newline();
         move(y++,0);
         addstr(pool[p]->name, gamelog);
         addstr("には", gamelog);
         if(num_relationships==1) addstr("他の", gamelog);
         else addstr("さらに他の", gamelog);
         addstr("者との関係を持てるほど誘惑的でない。", gamelog);
         gamelog.newline();

         getkey();
         set_color(COLOR_WHITE,COLOR_BLACK,0);

         move(y++,0);
         addstr("楽しい時間だった。2人は穏便に別れた。", gamelog);
         gamelog.nextMessage();

         getkey();

         delete_and_remove(d.date,e);

         return DATERESULT_BREAKUP;
      }

      if(LCSrandom((aroll-troll)/2)>d.date[e]->get_attribute(ATTRIBUTE_WISDOM,true))
      {
         set_color(COLOR_GREEN,COLOR_BLACK,1);
         move(y,0);y++;
         addstr("もはや", gamelog);
         addstr(d.date[e]->name, gamelog);
         addstr("は", gamelog);
         addstr(pool[p]->name, gamelog);
         addstr("の完全な愛の奴隷だ!", gamelog);
         gamelog.nextMessage();
         //Get map of their workplace
         location[d.date[e]->worklocation]->mapped=1;
         location[d.date[e]->worklocation]->hidden=0;

         getkey();

         d.date[e]->flag|=CREATUREFLAG_LOVESLAVE;
         d.date[e]->hireid=pool[p]->id;

         erase();

         set_color(COLOR_WHITE,COLOR_BLACK,1);
         move(0,0);
         addstr(d.date[e]->propername);
         addstr("の自我消去");

         move(2,0);
         set_color(COLOR_WHITE,COLOR_BLACK,0);
         addstr(d.date[e]->get_type_name());
         addstr("をどのような名前で呼ぶか?");
         move(3,0);
         addstr("もし何も入力しなければ、本名が使われる。");

         enter_name(4,0,d.date[e]->name,CREATURE_NAMELEN,d.date[e]->propername);

         sleeperize_prompt(*d.date[e],*pool[p],8);

         pool.push_back(d.date[e]);
         stat_recruits++;
         d.date.erase(d.date.begin() + e);

         return DATERESULT_JOINED;
      }
      else
      {
         if(d.date[e]->align == ALIGN_CONSERVATIVE && d.date[e]->get_attribute(ATTRIBUTE_WISDOM,false)>3)
         {
            set_color(COLOR_GREEN,COLOR_BLACK,1);
            y++;
            move(y++,0);
            addstr(s+pool[p]->name+"は"+d.date[e]->name+"の凍りついた保守の心を暖めつつある。", gamelog);
            gamelog.newline();
            move(y++,0);
            d.date[e]->adjust_attribute(ATTRIBUTE_WISDOM,-1);
            d.date[e]->adjust_attribute(ATTRIBUTE_HEART,+1);
         }
         else if(d.date[e]->get_attribute(ATTRIBUTE_WISDOM,false)>3)
         {
            d.date[e]->adjust_attribute(ATTRIBUTE_WISDOM,-1);
         }
         //Possibly date reveals map of location
         else if(location[d.date[e]->worklocation]->mapped==0 && !LCSrandom(d.date[e]->get_attribute(ATTRIBUTE_WISDOM,false)))
         {
            y++;
            move(y++,0);
            addstr(s+d.date[e]->name+"は話題を"
               +location[d.date[e]->worklocation]->name+"に切り替えた。", gamelog);
            gamelog.newline();
            move(y++,0);
            if(!(location[d.date[e]->worklocation]->type<=SITE_RESIDENTIAL_SHELTER))
            {
               addstr(pool[p]->name, gamelog);
               addstr("はその情報を元に地図を作った。", gamelog);
               gamelog.newline();
               y++;
            }
            else
            {
               addstr(pool[p]->name, gamelog);
               addstr("はその場所についてよく知っている。", gamelog);
               gamelog.newline();
               y++;
            }
            location[d.date[e]->worklocation]->mapped=1;
            location[d.date[e]->worklocation]->hidden=0;
         }

         set_color(COLOR_WHITE,COLOR_BLACK,0);
         move(y++,0);
         addstr("2人は翌日再び会う約束をした。", gamelog);
         gamelog.nextMessage();

         getkey();

         return DATERESULT_MEETTOMORROW;
      }
   }
   else if(aroll==troll)
   {
      set_color(COLOR_WHITE,COLOR_BLACK,0);
      move(y++,0);
      addstr(d.date[e]->name,gamelog);
      addstr("は興味を示したが、",gamelog);
      move(y++,0);
      switch(LCSrandom(4))
      {
      case 0: addstr("髪を洗わなければならない",gamelog); break;
      case 1: addstr("アレルギーのせい",gamelog); break;
      case 2: addstr("明日は朝が早い",gamelog); break;
      case 3: addstr("好きなテレビ番組を見なければならない", gamelog); break;
      case 4:
         addstr("ペットの",gamelog);
         switch(LCSrandom(3+(law[LAW_ANIMALRESEARCH]==-2)))
         {
         case 0: addstr("猫",gamelog); break;
         case 1: addstr("犬",gamelog); break;
         case 2: addstr("熱帯魚",gamelog); break;
         case 3: addstr("6足豚",gamelog); break;
         }
         addstr("の世話をしなければならない",gamelog);
         break;
      case 5: addstr("バースデーパーティーへ行かなければならない",gamelog); break;
      case 6: addstr("携帯電話を充電しなければならない",gamelog); break;
      }
      addstr("と言って早々と帰宅した。",gamelog);
      move(y++,0);
      addstr("2人は翌日再び会う約束をした。", gamelog);
      gamelog.nextMessage();

      getkey();

      return DATERESULT_MEETTOMORROW;
   }
   else
   {
      //WISDOM POSSIBLE INCREASE
      if(d.date[e]->align==-1&&aroll<troll/2)
      {
         set_color(COLOR_RED,COLOR_BLACK,1);
         move(y++,0);

         addstr("Talking with ", gamelog);
         addstr(d.date[e]->name, gamelog);
         addstr(" actually curses ", gamelog);
         addstr(pool[p]->name, gamelog);
         addstr("'s mind with wisdom!!!", gamelog);
         gamelog.newline();
         pool[p]->adjust_attribute(ATTRIBUTE_WISDOM,+1);

         if(d.date[e]->get_skill(SKILL_RELIGION)>pool[p]->get_skill(SKILL_RELIGION))
            pool[p]->train(SKILL_RELIGION,20*(d.date[e]->get_skill(SKILL_RELIGION)-pool[p]->get_skill(SKILL_RELIGION)));
         if(d.date[e]->get_skill(SKILL_SCIENCE)>pool[p]->get_skill(SKILL_SCIENCE))
            pool[p]->train(SKILL_SCIENCE,20*(d.date[e]->get_skill(SKILL_SCIENCE)-pool[p]->get_skill(SKILL_SCIENCE)));
         if(d.date[e]->get_skill(SKILL_BUSINESS)>pool[p]->get_skill(SKILL_BUSINESS))
            pool[p]->train(SKILL_BUSINESS,20*(d.date[e]->get_skill(SKILL_BUSINESS)-pool[p]->get_skill(SKILL_BUSINESS)));

         getkey();
      }

      //BREAK UP

      // If your squad member is wanted by the police, a conservative who breaks up with
      // them has a 1 in 50 chance of ratting them out, unless the person being dated is law
      // enforcement, prison guard, or agent, in which case there is a 1 in 4 chance. -Fox
      if((iscriminal(*pool[p])) &&
         (!LCSrandom(50) ||(LCSrandom(2) && (d.date[e]->kidnap_resistant()))))
      {
         move(y++,0);
         set_color(COLOR_RED,COLOR_BLACK,1);
         addstr(d.date[e]->name, gamelog);
         addstr(" was leaking information to the police the whole time!", gamelog);

         getkey();

         move(y++,0);
         // 3/4 chance of being arrested if less than 50 juice,
         // 1/2 chance of being arrested if more than 50 juice
         if((pool[p]->juice<50 && LCSrandom(2)) || LCSrandom(2))
         {
            // Find the police station
            long ps=find_police_station(*pool[p]);

            set_color(COLOR_MAGENTA,COLOR_BLACK,1);
            addstr(pool[p]->name, gamelog);
            addstr(" has been arrested.", gamelog);
            gamelog.nextMessage();

            removesquadinfo(*pool[p]);
            pool[p]->carid=-1;
            pool[p]->location=ps;
            pool[p]->drop_weapons_and_clips(NULL);
            pool[p]->activity.type=ACTIVITY_NONE;

            getkey();

            delete_and_remove(d.date,e);

            return DATERESULT_ARRESTED;
         }
         else
         {
            set_color(COLOR_GREEN,COLOR_BLACK,1);
            addstr("But ", gamelog);
            addstr(pool[p]->name, gamelog);
            addstr(" escapes the police ambush!", gamelog);
            gamelog.nextMessage();
         }
      }
      else
      {
         int ls = loveslaves(*pool[p]);
         if (ls > 0 && LCSrandom(2))
         {
            set_color(COLOR_MAGENTA,COLOR_BLACK,1);
            move(y++,0);
            addstr(s+"The date starts well, but goes horribly wrong when "+d.date[e]->name, gamelog);
            move(y++,0);
            addstr(s+"notices "+pool[p]->name+"'s ", gamelog);
            switch (ls)
            {
               case 5:
                  addstr("awe-inspiring ", gamelog);
                  break;
               case 4:
                  addstr("intricate ", gamelog);
                  break;
               case 3:
                  addstr("complicated ", gamelog);
                  break;
               case 2:
                  addstr("detailed ", gamelog);
                  break;
               case 1:
                  break;
               default:
                  addstr("mind-bending ", gamelog);
            }
            addstr(s+"schedule for keeping "+d.date[e]->himher(),gamelog);
            addstr(s+" from meeting ",gamelog);
            move(y++,0);
            int lsfound = 0;
            for (int q=0; q<(int)pool.size(); q++)
            {
               if(pool[q]->hireid == pool[p]->id && pool[q]->alive && pool[q]->flag & CREATUREFLAG_LOVESLAVE)
               {
                  lsfound++;
                  if (lsfound == 1)
                  {
                     addstr(pool[q]->name, gamelog);
                  }
                  else if (lsfound < ls)
                  {
                     addstr(s+", "+pool[q]->name, gamelog);
                  }else
                  {
                     addstr(s+" and "+ pool[q]->name, gamelog);
                  }
               }
            }
            addstr(".",gamelog);
            gamelog.newline();
            move(y++,0);
         }
         else
         {
            set_color(COLOR_MAGENTA,COLOR_BLACK,1);
            move(y++,0);
            addstr(d.date[e]->name, gamelog);
            addstr(" can sense that things just aren't working out.", gamelog);
            gamelog.newline();
            move(y++,0);
         }
         addstr("This relationship is over.", gamelog);
         gamelog.nextMessage();
      }

      getkey();

      delete_and_remove(d.date,e);

      return DATERESULT_BREAKUP;
   }
}

/* daily - date - dater p gets back from vacation */
char completevacation(datest &d,int p,char &clearformess)
{
   music.play(MUSIC_DATING);
   int e=0;

   clearformess=1;

   erase();
   set_color(COLOR_WHITE,COLOR_BLACK,1);
   move(0,0);
   addstr(pool[p]->name, gamelog);
   addstr(" is back from vacation.", gamelog);
   gamelog.nextMessage();

   // Temporarily make the date Conservative so that high-juice liberals aren't trivial to seduce
   int datealignment=d.date[e]->align;
   d.date[e]->align=-1;

   short aroll=pool[p]->skill_roll(SKILL_SEDUCTION)*2;
   short troll=d.date[e]->attribute_roll(ATTRIBUTE_WISDOM);

   // Attribute roll over; reset date's alignment to what it should be
   d.date[e]->align=datealignment;

   pool[p]->train(SKILL_SEDUCTION,LCSrandom(11)+15);

   int thingsincommon=0;
   for(int s=0;s<SKILLNUM;s++)
      if(d.date[e]->get_skill(s)>=1 && pool[p]->get_skill(s)>=1)
         //Has a skill that is at least half the same skill of the other person on the date.
         if (d.date[e]->get_skill(s)<=pool[p]->get_skill(s)*2)
            thingsincommon++;
   aroll += thingsincommon*3;

   pool[p]->train(SKILL_SCIENCE,
      max(d.date[e]->get_skill(SKILL_SCIENCE)-pool[p]->get_skill(SKILL_SCIENCE),0));
   pool[p]->train(SKILL_RELIGION,
      max(d.date[e]->get_skill(SKILL_RELIGION)-pool[p]->get_skill(SKILL_RELIGION),0));
   pool[p]->train(SKILL_BUSINESS,
      max(d.date[e]->get_skill(SKILL_BUSINESS)-pool[p]->get_skill(SKILL_BUSINESS),0));

   if(d.date[e]->skill_roll(SKILL_BUSINESS))
   {
      troll+=d.date[e]->skill_roll(SKILL_BUSINESS);
      aroll+=pool[p]->skill_roll(SKILL_BUSINESS);
   }
   if(d.date[e]->skill_roll(SKILL_RELIGION))
   {
      troll+=d.date[e]->skill_roll(SKILL_RELIGION);
      aroll+=pool[p]->skill_roll(SKILL_RELIGION);
   }
   if(d.date[e]->skill_roll(SKILL_SCIENCE))
   {
      troll+=d.date[e]->skill_roll(SKILL_SCIENCE);
      aroll+=pool[p]->skill_roll(SKILL_SCIENCE);
   }


   switch(dateresult(aroll,troll,d,e,p,2))
   {
   default:
   case DATERESULT_MEETTOMORROW:return 0;
   case DATERESULT_BREAKUP:     return 1;
   case DATERESULT_JOINED:      return 1;
   case DATERESULT_ARRESTED:    return 1;
   }
}



/* daily - date - dater p goes on some dates */
char completedate(datest &d,int p,char &clearformess)
{
   music.play(MUSIC_DATING);
   int e;
   clearformess=1;

   erase();
   set_color(COLOR_WHITE,COLOR_BLACK,1);
   move(0,0);
   addstr(pool[p]->name, gamelog);
   addstr("は", gamelog);
   if(len(d.date)==1)
   {
      if(pool[p]->clinic) addstr("「楽しく」", gamelog);
      else addstr("楽しく", gamelog);
   }
   else addstr("何とか", gamelog);
   for(e=0;e<len(d.date);e++)
   {
      addstr(d.date[e]->name, gamelog);

      if(e<=len(d.date)-3) addstr("、", gamelog);
      else if(e==len(d.date)-2) addstr("と", gamelog);
      else
      {
         if(pool[p]->clinic>0)
         {
            addstr("と", gamelog);
            addstr(location[pool[p]->location]->name, gamelog);
            addstr("で", gamelog);
         }
         else
         {
            addstr("と", gamelog);
         }
      }
   }
   addstr("デートした。", gamelog);

   gamelog.newline();

   getkey();

   if(len(d.date)>1&&!LCSrandom(len(d.date)>2?4:6))
   {
      switch(LCSrandom(3))
      {
         case 0:
            move(2,0);
            if(len(d.date)>2) addstr("Unfortunately, they all know each other and had been discussing",gamelog);
            else addstr("Unfortunately, they know each other and had been discussing",gamelog);
            move(3,0);
            addstr(pool[p]->name,gamelog);
            addstr(".  An ambush was set for the lying dog...",gamelog);
            gamelog.newline();

            getkey();

            break;
         case 1:
            move(2,0);
            if(len(d.date)>2) addstr("Unfortunately, they all turn up at the same time.",gamelog);
            else addstr("Unfortunately, they turn up at the same time.",gamelog);
            gamelog.newline();
            move(3,0);
            addstr("Ruh roh...",gamelog);
            gamelog.newline();

            getkey();

            break;
         default:
            move(2,0);
            addstr(pool[p]->name,gamelog);
            if(len(d.date)>2)
               addstr_fl(gamelog," realizes %s has committed to eating %d meals at once.",pool[p]->heshe(),len(d.date));
            else
            {
               addstr(" mixes up the names of ",gamelog);
               addstr(d.date[0]->name,gamelog);
               addstr(" and ",gamelog);
               addstr(d.date[1]->name,gamelog);
               gamelog.newline();
            }
            move(3,0);
            addstr("Things go downhill fast.",gamelog);
            gamelog.newline();

            getkey();

            break;
      }

	   static const char *date_fail[] =
	   {
	      " is publicly humiliated."
	      " runs away.",
	      " escapes through the bathroom window.",
	      " spends the night getting drunk alone.",
	      " gets chased out by an angry mob.",
	      " gets stuck washing dishes all night.",
	      " is rescued by a passing Elite Liberal.",
	      " makes like a tree and leaves."
	   };
      move(5,0);
      addstr(pool[p]->name,gamelog);
      addstr(pickrandom(date_fail),gamelog);
      addjuice(*pool[p],-5,-50);
      gamelog.nextMessage();

      getkey();

      return 1;
   }

   for(e=len(d.date)-1;e>=0;e--)
   {
      erase();
      set_color(COLOR_WHITE,COLOR_BLACK,1);
      move(0,0);
      addstr(d.date[e]->name, gamelog);
      addstr("とのデート、", gamelog);
      addstr(d.date[e]->get_type_name(),gamelog);
      addstr("、", gamelog);
      addstr(location[d.date[e]->worklocation]->getname(false,true), gamelog);
      gamelog.newline();

      set_color(COLOR_WHITE,COLOR_BLACK,0);
      printfunds();

      //Others come to dates unarmed and wearing normal
      //clothing
      vector<Item*> temp;
      d.date[e]->drop_weapons_and_clips(&temp);
      Armor atmp(*armortype[getarmortype("ARMOR_CLOTHES")]);
      d.date[e]->give_armor(atmp,&temp);

      printcreatureinfo(d.date[e]);
      makedelimiter();

      while(len(temp))
      {
         if(temp.back()->is_weapon())
            d.date[e]->give_weapon(*(static_cast<Weapon*>(temp.back())),NULL); //casts -XML
         else if(temp.back()->is_armor())
            d.date[e]->give_armor(*(static_cast<Armor*>(temp.back())),NULL);
         else if(temp.back()->is_clip())
            d.date[e]->take_clips(*(static_cast<Clip*>(temp.back())),temp.back()->get_number());
         delete_and_remove(temp,len(temp)-1);
      }

      move(10,0);
      addstr(pool[p]->name);
      addstr("はどのようなシチュエーションで迫るか?");

      if(ledger.get_funds()>=100&&!pool[p]->clinic)set_color(COLOR_WHITE,COLOR_BLACK,0);
      else set_color(COLOR_BLACK,COLOR_BLACK,1);
      move(11,0);
      addstr("A - きっかけを掴むために$100を費やす");
      set_color(COLOR_WHITE,COLOR_BLACK,0);
      move(12,0);
      addstr("B - 1セントも使わずに夜まで過ごす");
      if(!pool[p]->clinic&&pool[p]->blood==100)set_color(COLOR_WHITE,COLOR_BLACK,0);
      else set_color(COLOR_BLACK,COLOR_BLACK,1);
      move(13,0);
      if(pool[p]->blood==100) addstr("C - 1週間を安いバケーションに費やす (他のデートはすっぽかす)");
      else addstr("C - 1週間を安いバケーションに費やす (負傷していてはならない)");
      set_color(COLOR_WHITE,COLOR_BLACK,0);
      move(14,0);
      addstr("D - 打ち切る");
      if(d.date[e]->align==-1&&!pool[p]->clinic)
      {
         set_color(COLOR_WHITE,COLOR_BLACK,0);
         move(15,0);
         addstr("E - 保守の狐をだた誘拐する");
      }

      int thingsincommon = 0;
      for(int s=0;s<SKILLNUM;s++)
         if(d.date[e]->get_skill(s)>=1 && pool[p]->get_skill(s)>=1)
            //Has a skill that is at least half the same skill of the other person on the date.
            if (d.date[e]->get_skill(s)<=pool[p]->get_skill(s)*2)
               thingsincommon++;
      while(true)
      {
         int c=getkey();

         short aroll=pool[p]->skill_roll(SKILL_SEDUCTION);
         short troll=d.date[e]->attribute_roll(ATTRIBUTE_WISDOM);
         if(d.date[e]->align==ALIGN_CONSERVATIVE)
            troll+=troll*(d.date[e]->juice/100);
         // Even liberals and moderates shouldn't be TOO easy to seduce! -- SlatersQuest
         else if(d.date[e]->align==ALIGN_MODERATE)
            troll+=troll*(d.date[e]->juice/150);
         else troll+=troll*(d.date[e]->juice/200);

         char test=0;
		   aroll += thingsincommon * 3;
         if(c=='a'&&ledger.get_funds()>=100&&!pool[p]->clinic)
         {
            ledger.subtract_funds(100,EXPENSE_DATING);
            aroll+=LCSrandom(10);
            test=true;
         }
         else if(c=='b') test=true;

         if(test)
         {
            pool[p]->train(SKILL_SEDUCTION,LCSrandom(4)+5);
            pool[p]->train(SKILL_SCIENCE,
               max(d.date[e]->get_skill(SKILL_SCIENCE)-pool[p]->get_skill(SKILL_SCIENCE),0));
            pool[p]->train(SKILL_RELIGION,
               max(d.date[e]->get_skill(SKILL_RELIGION)-pool[p]->get_skill(SKILL_RELIGION),0));
            pool[p]->train(SKILL_BUSINESS,
               max(d.date[e]->get_skill(SKILL_BUSINESS)-pool[p]->get_skill(SKILL_BUSINESS),0));

            if(d.date[e]->get_skill(SKILL_BUSINESS))
            {
               troll+=d.date[e]->skill_roll(SKILL_BUSINESS);
               aroll+=pool[p]->skill_roll(SKILL_BUSINESS);
            }
            if(d.date[e]->get_skill(SKILL_RELIGION))
            {
               troll+=d.date[e]->skill_roll(SKILL_RELIGION);
               aroll+=pool[p]->skill_roll(SKILL_RELIGION);
            }
            if(d.date[e]->get_skill(SKILL_SCIENCE))
            {
               troll+=d.date[e]->skill_roll(SKILL_SCIENCE);
               aroll+=pool[p]->skill_roll(SKILL_SCIENCE);
            }

            int y=17;
            if(dateresult(aroll,troll,d,e,p,y)==DATERESULT_ARRESTED) return 1;
            break;
         }

         if(c=='c'&&!pool[p]->clinic&&pool[p]->blood==100)
         {
            for(int e2=len(d.date)-1;e2>=0;e2--)
            {
               if(e2==e) continue;
               delete_and_remove(d.date,e2);
               e=0;
            }
            d.timeleft=7;
            pool[p]->train(SKILL_SEDUCTION,LCSrandom(40)+15);
            pool[p]->train(SKILL_SCIENCE,
               max((d.date[e]->get_skill(SKILL_SCIENCE)-pool[p]->get_skill(SKILL_SCIENCE))*4,0));
            pool[p]->train(SKILL_RELIGION,
               max((d.date[e]->get_skill(SKILL_RELIGION)-pool[p]->get_skill(SKILL_RELIGION))*4,0));
            pool[p]->train(SKILL_BUSINESS,
               max((d.date[e]->get_skill(SKILL_BUSINESS)-pool[p]->get_skill(SKILL_BUSINESS))*4,0));
            return 0;
         }
         if(c=='d')
         {
            delete_and_remove(d.date,e);
            break;
         }
         if(c=='e'&&d.date[e]->align==-1&&!pool[p]->clinic)
         {
            set_color(COLOR_YELLOW,COLOR_BLACK,1);
            int bonus=0;
            move(17,0);
            addstr(pool[p]->name, gamelog);

            if(pool[p]->get_weapon().is_ranged())
            {
               addstr("はバスルームから", gamelog);
               addstr(pool[p]->get_weapon().get_name(1), gamelog);
               move(18,0);
               addstr("を持って戻り、保守を脅した!", gamelog);
               gamelog.newline();
               bonus=5;
            }
            else if(pool[p]->is_armed())
            {
               addstr("は保守を後ろから掴み、首に", gamelog);
               addstr(pool[p]->get_weapon().get_name(1), gamelog);
               move(18,0);
               addstr("を押し付けた!", gamelog);
               gamelog.newline();
               if(pool[p]->get_weapon().can_take_hostages())
                  bonus=5;
               else bonus=-1; // Conservative emboldened by the fact that you're trying
            }                 // to kidnap them with a gavel or some shit like that
            else
            {
               addstr("は後ろから保守の豚を掴み、", gamelog);
               move(18,0);
               if(law[LAW_FREESPEECH]!=-2)
                  addstr("馬鹿な真似をするなと脅した!", gamelog);
               else
                  addstr("[抵抗]するなと脅した!", gamelog);
               gamelog.newline();

               bonus+=pool[p]->get_skill(SKILL_HANDTOHAND)-1;
            }

            getkey();

            // Kidnap probably succeeds if the conservative isn't very dangerous,
            // but fails 15 times as often if the conservative is tough stuff.
            if((!d.date[e]->kidnap_resistant()&&
                LCSrandom(15))||
                LCSrandom(2+bonus))
            {

               set_color(COLOR_GREEN,COLOR_BLACK,1);
               move(20,0);
               addstr(d.date[e]->name, gamelog);
               if(bonus)
               {
                  addstr("は抵抗しなかった。", gamelog);
                  gamelog.newline();
               }
               else
               {
                  addstr("は抵抗し助けを呼んだが、誰も来なかった。", gamelog);
                  gamelog.newline();
               }

               getkey();

               move(22,0);
               addstr(pool[p]->name, gamelog);
               addstr("は保守を捕らえた!", gamelog);
               gamelog.nextMessage();

               getkey();

               d.date[e]->namecreature();
               strcpy(d.date[e]->propername,d.date[e]->name);

               d.date[e]->location=pool[p]->location;
               d.date[e]->base=pool[p]->base;
               d.date[e]->flag|=CREATUREFLAG_MISSING;

               //Kidnapped wearing normal clothes and no weapon
               d.date[e]->drop_weapons_and_clips(NULL);
               Armor clothes(*armortype[getarmortype("ARMOR_CLOTHES")]);
               d.date[e]->give_armor(clothes,NULL);

               //Create interrogation data
               d.date[e]->activity.intr()=new interrogation;

               erase();

               set_color(COLOR_WHITE,COLOR_BLACK,1);
               move(0,0);
               addstr(d.date[e]->propername);
               addstr("への教育");

               move(2,0);
               set_color(COLOR_WHITE,COLOR_BLACK,0);
               addstr(d.date[e]->get_type_name());
               addstr("をどのような名前で呼ぶか?");

               move(3,0);
               addstr("もし何も入力しなければ、本名が使われる。");

               enter_name(4,0,d.date[e]->name,CREATURE_NAMELEN,d.date[e]->propername);

               pool.push_back(d.date[e]);
               stat_kidnappings++;
               d.date.erase(d.date.begin()+e);
               break;
            }
            else
            {
               int y=20;
               if(LCSrandom(2))
               {
                  set_color(COLOR_MAGENTA,COLOR_BLACK,1);
                  move(y++,0);
                  addstr(d.date[e]->name, gamelog);
                  addstr("はアジトへ向かう途中で何とか逃げ出した!", gamelog);
                  gamelog.newline();

                  getkey();

                  move((++y)++,0);
                  addstr(pool[p]->name, gamelog);
                  addstr("は保守の誘拐に失敗した。", gamelog);
                  gamelog.nextMessage();

                  // Charge with kidnapping
                  criminalize(*pool[p],LAWFLAG_KIDNAPPING);

                  getkey();

                  delete_and_remove(d.date,e);
                  break;
               }
               else
               {
                  set_color(COLOR_RED,COLOR_BLACK,1);
                  move(y++,0);
                  addstr(d.date[e]->name, gamelog);
                  addstr("の拳が", gamelog);
                  addstr(pool[p]->name, gamelog);
                  addstr("が最後に見たものだった!", gamelog);
                  gamelog.newline();

                  getkey();

                  move((++y)++,0);
                  addstr("リベラルは拘置所で目が覚めた…", gamelog);
                  gamelog.nextMessage();

                  // Find the police station
                  int ps=find_police_station(*pool[p]);

                  // Arrest the Liberal
                  removesquadinfo(*pool[p]);
                  pool[p]->carid=-1;
                  pool[p]->location=ps;
                  pool[p]->drop_weapons_and_clips(NULL);
                  pool[p]->activity.type=ACTIVITY_NONE;

                  // Charge with kidnapping
                  criminalize(*pool[p],LAWFLAG_KIDNAPPING);

                  getkey();

                  delete_and_remove(d.date,e);
                  return 1;
               }
            }
         }
      }
   }

   if(len(d.date))
   {
      d.timeleft=0;
      return 0;
   }
   else return 1;
}
