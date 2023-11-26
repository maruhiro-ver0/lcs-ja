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

char heyMisterDog(Creature &a, Creature &tk);
char heyMisterMonster(Creature &a, Creature &tk);

char talkInCombat(Creature &a, Creature &tk);
char talkToBankTeller(Creature &a, Creature &tk);
char talkToGeneric(Creature &a, Creature &tk);

char wannaHearSomethingDisturbing(Creature &a, Creature &tk);
char talkAboutIssues(Creature &a, Creature &tk);

char doYouComeHereOften(Creature &a, Creature &tk);

char heyINeedAGun(Creature &a, Creature &tk);
char heyIWantToRentARoom(Creature &a, Creature &tk);
char heyIWantToCancelMyRoom(Creature &a, Creature &tk);

/* bluff, date, issues */
char talk(Creature &a,int t)
{
   Creature &tk = encounter[t];

   // TALKING TO DOGS
   if(tk.type == CREATURE_GUARDDOG && tk.align != ALIGN_LIBERAL)
   {
      return heyMisterDog(a, tk);
   }

   // TALKING TO MONSTERS
   if(tk.type == CREATURE_GENETIC && tk.align != ALIGN_LIBERAL)
   {
      return heyMisterMonster(a, tk);
   }

   // BLUFFING
   if((sitealarm||location[cursite]->siege.siege)&&tk.enemy())
   {
      return talkInCombat(a, tk);
   }

   return talkToGeneric(a, tk);
}

char talkToBankTeller(Creature &a, Creature &tk)
{
   clearcommandarea();clearmessagearea();clearmaparea();
   set_color(COLOR_WHITE,COLOR_BLACK,0);
   /*move(9,1);
   addstr(a.name);
   addstr(" prepares to rob the bank:");*/

   move(11,1);
   addstr("A - ");
   if(a.is_naked() && a.animalgloss!=ANIMALGLOSS_ANIMAL)addstr("全裸で");
   addstr("黙って窓口係にメモを渡す");
   move(12,1);
   addstr("B - ");
   if(a.is_naked() && a.animalgloss!=ANIMALGLOSS_ANIMAL)addstr("全裸で");
   addstr("銀行員を脅し金庫を開けさせる");
   move(13,1);
   addstr("C - ");
   if(a.is_naked() && a.animalgloss!=ANIMALGLOSS_ANIMAL)addstr("全裸で");
   addstr("考え直して銀行を襲わない");

   int c;
   do c=getkey(); while(c<'a'&&c>'c');

   switch(c)
   {
   case 'a':
      clearcommandarea();clearmessagearea();clearmaparea();
      set_color(COLOR_WHITE, COLOR_BLACK, 1);
      move(9, 1);
      addstr(a.name, gamelog);
      addstr("は窓口にメモを差し出した: ", gamelog);
      set_color(COLOR_GREEN, COLOR_BLACK, 1);
      move(10, 1);
      addstr("『");
      switch(LCSrandom(10))
      {
      case 0:addstr("おとなしく金を鞄に詰めろ。さもないと。", gamelog);break;
      case 1:addstr("お前たちの資金を解放するために来た。", gamelog);break;
      case 2:addstr("強盗だ。金を出せ。", gamelog);break;
      case 3:addstr("銃を持っている。金だ。", gamelog);break;
      case 4:addstr("リベラル・クライム・スコードは金を要求する。", gamelog);break;
      case 5:addstr("預金を引き出しに来た。全て出せ。", gamelog);break;
      case 6:addstr("お前たちは強盗されている。金をよこせ。", gamelog);break;
      case 7:addstr("この鞄にできるだけ金を詰めろ。", gamelog);break;
      case 8:addstr("何も言うな。金を奪いに来た。", gamelog);break;
      case 9:addstr("強盗だ。金を出せ。本物だ。", gamelog);break;
      }
      addstr("』");
      gamelog.newline();

      getkey();

      if(location[cursite]->highsecurity)
      {
         set_color(COLOR_WHITE, COLOR_BLACK, 1);
         move(11, 1);
         addstr("窓口係はメモを読んだ。すると、", gamelog);
         switch(LCSrandom(5))
         {
         case 0:addstr("身振りで", gamelog);break;
         case 1:addstr("警報を鳴らして", gamelog);break;
         case 2:addstr("叫んで", gamelog);break;
         case 3:addstr("悲鳴を上げて", gamelog);break;
         case 4:addstr("警告を発して", gamelog);break;
         }
         move(12, 1);
         addstr("警備員に助けを求めた!", gamelog);
         gamelog.newline();

         getkey();

         sitealarm=1;
         criminalize(a, LAWFLAG_BANKROBBERY);
         sitestory->crime.push_back(CRIME_BANKTELLERROBBERY);
         sitecrime+=30;
         makecreature(encounter[0],CREATURE_MERC);
         makecreature(encounter[1],CREATURE_MERC);
         makecreature(encounter[2],CREATURE_MERC);
         makecreature(encounter[3],CREATURE_MERC);
      }
      else
      {
         set_color(COLOR_WHITE, COLOR_BLACK, 1);
         move(11, 1);
         addstr("窓口係はメモを読んだ。そして、", gamelog);
         switch(LCSrandom(5))
         {
         case 0:addstr("黙ってうなずき", gamelog);break;
         case 1:addstr("驚きながら", gamelog);break;
         case 2:addstr("唇をかみ締めながら", gamelog);break;
         case 3:addstr("顔をしかめながら", gamelog);break;
         case 4:addstr("厳しい表情をしながら", gamelog);break;
         }
         move(12, 1);
         addstr("鞄に札束を詰めた。", gamelog);
         gamelog.newline();

         getkey();

         criminalize(a, LAWFLAG_BANKROBBERY);
         sitestory->crime.push_back(CRIME_BANKTELLERROBBERY);
         sitecrime+=30;
         sitealarmtimer=0;
         activesquad->loot.push_back(new Money(5000));
      }
      tk.cantbluff=1;
      return 1;
   case 'b':
   {
      clearcommandarea();clearmessagearea();clearmaparea();
      set_color(COLOR_WHITE,COLOR_BLACK,1);
      Creature *armed_liberal=NULL;
      for(int i=0;i<6;i++)
      {
         if(activesquad->squad[i] &&
            activesquad->squad[i]->get_weapon().is_threatening())
         {
            armed_liberal=activesquad->squad[i];
            break;
         }
      }
      if(armed_liberal)
      {
         move(9,1);
         addstr(armed_liberal->name, gamelog);
         addstr("は", gamelog);
         addstr(armed_liberal->get_weapon().get_shortname(0), gamelog);
         addstr("を見せ付けた。", gamelog);
         gamelog.newline();

         getkey();

         clearmessagearea();
      }
      move(10,1);
      addstr(a.name, gamelog);
      addstr("は言った。", gamelog);
      set_color(COLOR_GREEN,COLOR_BLACK,1);
      move(11,1);
      addstr("「", gamelog);
      addstr(slogan, gamelog);
      gamelog.record(" ");
      move(12,1);
      addstr("今すぐ金庫を開けろ! 」", gamelog);
      gamelog.newline();

      getkey();

      int roll       = a.skill_roll(SKILL_PERSUASION);
      int difficulty = DIFFICULTY_VERYEASY;

      if(armed_liberal == NULL)
         difficulty += 12;
      if(location[cursite]->highsecurity>0)
         difficulty += 12;

      clearcommandarea();clearmessagearea();clearmaparea();
      set_color(COLOR_WHITE,COLOR_BLACK,1);
      if(roll<difficulty)
      {
         set_color(COLOR_WHITE, COLOR_BLACK, 1);
         move(9, 1);
         addstr("窓口係と銀行員は", gamelog);
         move(10, 1);
         addstr("警備員に助けを求めた!", gamelog);
         gamelog.newline();

         getkey();

         sitealarm=1;
         sitealienate=2;
         criminalizeparty(LAWFLAG_BANKROBBERY);
         sitestory->crime.push_back(CRIME_BANKSTICKUP);
         sitecrime+=50;
         CreatureTypes guard = CREATURE_SECURITYGUARD;
         if(location[cursite]->highsecurity>0) guard = CREATURE_MERC;
         makecreature(encounter[0],guard);
         makecreature(encounter[1],guard);
         makecreature(encounter[2],guard);
         makecreature(encounter[3],guard);
         makecreature(encounter[4],guard);
         makecreature(encounter[5],guard);
      }
      else
      {
         set_color(COLOR_WHITE, COLOR_BLACK, 1);
         move(9, 1);
         addstr("銀行員はしぶしぶ従った!", gamelog);
         gamelog.newline();

         getkey();

         move(10, 1);
         addstr("金庫が開いた!", gamelog);
         gamelog.newline();

         getkey();

         criminalizeparty(LAWFLAG_BANKROBBERY);
         sitestory->crime.push_back(CRIME_BANKSTICKUP);
         sitecrime+=50;
         sitealarm=1;
         sitealienate=2;

         for(int x=0;x<MAPX;x++)
         for(int y=0;y<MAPY;y++)
         for(int z=0;z<MAPZ;z++)
         {
            levelmap[x][y][z].flag &= ~SITEBLOCK_LOCKED;
            if(levelmap[x][y][z].flag & SITEBLOCK_METAL)
               levelmap[x][y][z].flag &= ~SITEBLOCK_DOOR;
            if(levelmap[x][y][z].special == SPECIAL_BANK_VAULT)
               levelmap[x][y][z].special = SPECIAL_NONE;
         }

         encounter[0].exists = false;
      }
   }
   default:
   case 'c':
      return 0;
   }
}

char talkToGeneric(Creature &a, Creature &tk)
{
   clearcommandarea();clearmessagearea();clearmaparea();
   set_color(COLOR_WHITE,COLOR_BLACK,1);
   move(9,1);
   addstr(a.name);
   addstr("が");
   switch(tk.align)
   {
   case ALIGN_CONSERVATIVE:
      set_color(COLOR_RED,COLOR_BLACK,1);
      break;
   case ALIGN_LIBERAL:
      set_color(COLOR_GREEN,COLOR_BLACK,1);
      break;
   case ALIGN_MODERATE:
      set_color(COLOR_WHITE,COLOR_BLACK,1);
      break;
   }
   addstr(tk.name);
   set_color(COLOR_WHITE,COLOR_BLACK,1);
   add_age(tk);
   addstr("に話しかける:");

   set_color(COLOR_WHITE,COLOR_BLACK,0);
   move(11,1);
   addstr("A - ");
   if(a.is_naked() && a.animalgloss!=ANIMALGLOSS_ANIMAL)addstr("全裸で");
   addstr("政治の話をする");
   move(12,1);
   if(tk.can_date(a))set_color(COLOR_WHITE,COLOR_BLACK,0);
   else set_color(COLOR_BLACK,COLOR_BLACK,1);
   addstr("B - ");
   if(a.is_naked() && a.animalgloss!=ANIMALGLOSS_ANIMAL)addstr("全裸で");
   addstr("口説く");
   set_color(COLOR_WHITE,COLOR_BLACK,0);
   move(13,1);
   addstr("C - ");
   if(a.is_naked() && a.animalgloss!=ANIMALGLOSS_ANIMAL)addstr("全裸で");
   addstr("よく考えると何も話すことがない");
   if(tk.type==CREATURE_LANDLORD&&location[cursite]->renting==-1)
   {
      move(14,1);
      addstr("D - ");
      if(a.is_naked() && a.animalgloss!=ANIMALGLOSS_ANIMAL)addstr("全裸で");
      addstr("部屋を借りる");
   }
   else if(tk.type==CREATURE_LANDLORD&&location[cursite]->renting>0)
   {
      move(14,1);
      addstr("D - ");
      if(a.is_naked() && a.animalgloss!=ANIMALGLOSS_ANIMAL)addstr("全裸で");
      addstr("部屋を借りるのをやめる");
   }
   else if(tk.type==CREATURE_GANGMEMBER||tk.type==CREATURE_MERC)
   {
      move(14,1);
      addstr("D - ");
      if(a.is_naked() && a.animalgloss!=ANIMALGLOSS_ANIMAL)addstr("全裸で");
      addstr("武器を買う");
   }
   else if(tk.type==CREATURE_BANK_TELLER)
   {
      move(14,1);
      addstr("D - ");
      if(a.is_naked() && a.animalgloss!=ANIMALGLOSS_ANIMAL)addstr("全裸で");
      addstr("銀行を襲う");
   }

   while(true)
   {
      int c=getkey();

      switch(c)
      {
      case 'a':
         return wannaHearSomethingDisturbing(a, tk);
      case 'b':
         if(!tk.can_date(a)) break;
         return doYouComeHereOften(a, tk);
      case 'c':
         return 0;
      case 'd':
         if(tk.type==CREATURE_LANDLORD&&location[cursite]->renting==-1)
            return heyIWantToRentARoom(a, tk);
         else if (tk.type == CREATURE_LANDLORD && location[cursite]->renting > 0)
            return heyIWantToCancelMyRoom(a, tk);
         else if(tk.type==CREATURE_GANGMEMBER||tk.type==CREATURE_MERC)
            return heyINeedAGun(a, tk);
         else if(tk.type==CREATURE_BANK_TELLER)
            return talkToBankTeller(a, tk);
         break;
      }
   }
}

char heyIWantToCancelMyRoom(Creature &a, Creature &tk)
{
   clearcommandarea();
   clearmessagearea();
   clearmaparea();
   set_color(COLOR_WHITE, COLOR_BLACK, 1);
   move(9, 1);
   addstr(a.name, gamelog);
   addstr("は言った。", gamelog);
   set_color(COLOR_GREEN, COLOR_BLACK, 1);
   move(10, 1);
   addstr("「部屋を借りるのをやめたい。」", gamelog);
   gamelog.newline();

   getkey();

   if (a.is_naked() && a.animalgloss != ANIMALGLOSS_ANIMAL)
   {
      set_color(COLOR_WHITE, COLOR_BLACK, 1);
      move(12, 1);
      addstr(tk.name, gamelog);
      addstr("は答えた。", gamelog);
      set_color(COLOR_CYAN, COLOR_BLACK, 1);
      move(13, 1);
      addstr("「警察を呼ばれる前に服を着なさい。」", gamelog);
      gamelog.newline();

      getkey();

      return 1;
   }

   set_color(COLOR_WHITE, COLOR_BLACK, 1);
   move(12, 1);
   addstr(tk.name, gamelog);
   addstr("は答えた。", gamelog);
   set_color(COLOR_CYAN, COLOR_BLACK, 1);
   move(13, 1);
   addstr("「わかりました。部屋を片付けておいてください。」", gamelog);
   gamelog.newline();

   getkey();

   set_color(COLOR_WHITE,COLOR_BLACK,1);
   move(15,1);
   addstr("<ここにあるあなたの持ち物はシェルターに移された。>", gamelog);
   gamelog.newline();

   getkey();

   location[cursite]->renting=RENTING_NOCONTROL;

   //MOVE ALL ITEMS AND SQUAD MEMBERS
   int hs=find_homeless_shelter(cursite);
   for(int p=0;p<len(pool);p++)
   {
      if(pool[p]->location==cursite)pool[p]->location=hs;
      if(pool[p]->base==cursite)pool[p]->base=hs;
   }
   location[hs]->getloot(location[cursite]->loot);

   location[cursite]->compound_walls=0;
   location[cursite]->compound_stores=0;
   location[cursite]->front_business=-1;

   return 1;
}

char heyIWantToRentARoom(Creature &a, Creature &tk)
{
   clearcommandarea();clearmessagearea();clearmaparea();
   set_color(COLOR_WHITE,COLOR_BLACK,1);
   move(9,1);addstr(a.name, gamelog);addstr("は言った。", gamelog);
   set_color(COLOR_GREEN,COLOR_BLACK,1);
   move(10,1);
   addstr("「部屋を借りたい。」", gamelog);
   gamelog.newline();

   getkey();

   if(a.is_naked() && a.animalgloss!=ANIMALGLOSS_ANIMAL)
   {
      set_color(COLOR_WHITE,COLOR_BLACK,1);
      move(12,1);addstr(tk.name, gamelog);addstr("は答えた。", gamelog);
      set_color(COLOR_CYAN,COLOR_BLACK,1);
      move(13,1);
      addstr("「警察を呼ばれる前に服を着なさい。」", gamelog);
      gamelog.newline();

      getkey();

      return 1;
   }

   int rent;
   switch(location[cursite]->type)
   {
   default:rent=200;break;
   case SITE_RESIDENTIAL_APARTMENT:rent=650;break;
   case SITE_RESIDENTIAL_APARTMENT_UPSCALE:rent=1500;break;
   }

   set_color(COLOR_WHITE,COLOR_BLACK,1);
   move(12,1);addstr(tk.name, gamelog);addstr("は答えた。", gamelog);
   set_color(COLOR_CYAN,COLOR_BLACK,1);
   move(13,1);
   addstr("「家賃は1ヶ月あたり $", gamelog);
   addstr(rent, gamelog);
   addstr("、", gamelog);
   gamelog.newline();
   move(14,1);
   addstr("敷金は $", gamelog);
   addstr(rent, gamelog);
   addstr("です。」", gamelog);
   gamelog.newline();

   getkey();

   clearcommandarea();clearmessagearea();clearmaparea();

   while(true)
   {
      int c='a';

      if(ledger.get_funds()<rent)set_color(COLOR_BLACK,COLOR_BLACK,1);
      move(11,1);
      addstr("A - 部屋を借りる");
      set_color(COLOR_WHITE,COLOR_BLACK,0);
      move(12,1);
      addstr("B - 部屋を借りない");
      move(13,1);
      addstr("C - 大家を脅す");

      c=getkey();

      switch(c)
      {
      case 'a': // Accept rent deal
         if(ledger.get_funds()<rent) break;

         clearcommandarea();clearmessagearea();clearmaparea();
         set_color(COLOR_WHITE,COLOR_BLACK,1);
         move(9,1);addstr(a.name, gamelog);addstr("は言った。", gamelog);
         set_color(COLOR_GREEN,COLOR_BLACK,1);
         move(10,1);
         addstr("「わかった。借りよう。」", gamelog);
         gamelog.newline();

         getkey();

         set_color(COLOR_WHITE,COLOR_BLACK,1);
         move(12,1);addstr(tk.name, gamelog);addstr("は答えた。", gamelog);
         set_color(COLOR_CYAN,COLOR_BLACK,1);
         move(13,1);
         addstr("「家賃は毎月3日に払ってください。", gamelog);
         gamelog.newline();
         move(14,1);
         addstr("来月からお願いします。」", gamelog);
         gamelog.newline();
         set_color(COLOR_WHITE,COLOR_BLACK,1);
         addstr(" <行ってしまった>");

         getkey();

         ledger.subtract_funds(rent,EXPENSE_RENT);
         location[cursite]->renting=rent;
         location[cursite]->newrental=1;

         basesquad(activesquad,cursite);
         return 1;

      case 'b': // Refuse rent deal
         clearcommandarea();clearmessagearea();clearmaparea();
         set_color(COLOR_WHITE,COLOR_BLACK,1);
         move(9,1);addstr(a.name, gamelog);addstr("は言った。", gamelog);
         set_color(COLOR_GREEN,COLOR_BLACK,1);
         move(10,1);
         addstr("「おっと、もっと安いかと思っていた。」", gamelog);
         gamelog.newline();

         getkey();

         set_color(COLOR_WHITE,COLOR_BLACK,1);
         move(12,1);addstr(tk.name, gamelog);addstr("は答えた。", gamelog);
         set_color(COLOR_CYAN,COLOR_BLACK,1);
         move(13,1);
         addstr("「そう言われましても…」", gamelog);
         set_color(COLOR_WHITE,COLOR_BLACK,1);
         addstr(" <行ってしまった>", gamelog);
         gamelog.newline();

         getkey();

         return 1;

      case 'c': // Threaten landlord
         clearcommandarea();clearmessagearea();clearmaparea();
         set_color(COLOR_WHITE,COLOR_BLACK,1);
         Creature *armed_liberal=NULL;
         for(int i=0;i<6;i++)
         {
            if(activesquad->squad[i] &&
               activesquad->squad[i]->get_weapon().is_threatening())
            {
               armed_liberal=activesquad->squad[i];
               break;
            }
         }
         if(armed_liberal)
         {
            move(9,1);
            addstr(armed_liberal->name, gamelog);
            addstr("は", gamelog);
            addstr(armed_liberal->get_weapon().get_shortname(0), gamelog);
            addstr("を見せびらかした。", gamelog);
            gamelog.newline();

            getkey();
            clearmessagearea();
         }
         move(9,1);
         addstr(a.name, gamelog);
         addstr("は言った", gamelog);
         set_color(COLOR_GREEN,COLOR_BLACK,1);
         move(10,1);
         addstr("「リベラル・クライム・スコードにはいくらだ? 」", gamelog);
         gamelog.newline();

         getkey();

         int roll       = a.skill_roll(SKILL_PERSUASION);
         int difficulty = DIFFICULTY_FORMIDABLE;

         if(newscherrybusted == false)
            difficulty += 6;
         if(armed_liberal == NULL)
            difficulty += 6;

         if(roll < difficulty - 1)
         {
            set_color(COLOR_WHITE,COLOR_BLACK,1);
            move(12,1);addstr(tk.name, gamelog);addstr("は答えた。", gamelog);
            set_color(COLOR_CYAN,COLOR_BLACK,1);
            move(13,1);
            addstr("「帰ったほうがいいぞ。」", gamelog);
            set_color(COLOR_WHITE,COLOR_BLACK,1);
            addstr(" <腕を交差させた>", gamelog);
            gamelog.newline();

            getkey();

            tk.cantbluff = 1;
            return 1;
         }
         else
         {
            set_color(COLOR_WHITE,COLOR_BLACK,1);
            move(12,1);addstr(tk.name, gamelog);addstr("は答えた。", gamelog);
            set_color(COLOR_CYAN,COLOR_BLACK,1);
            move(13,1);
            addstr("「ジーザス…どうぞ…」", gamelog);
            gamelog.newline();

            getkey();

            int rent;

            // Either he calls the cops...
            if(roll<difficulty)
            {
               for(int i=0;i<6;i++)
                  if(activesquad->squad[i])
                     criminalize(*(activesquad->squad[i]),LAWFLAG_EXTORTION);
               location[cursite]->siege.timeuntillocated = 2;
               rent=10000000; // Yeah he's kicking you out next month
            }
            // ...or it's yours for free
            else rent=0;

            location[cursite]->renting=rent;
            location[cursite]->newrental=true;

            basesquad(activesquad,cursite);
            return 1;
         }
      }
   }
}

char heyINeedAGun(Creature &a, Creature &tk)
{
   clearcommandarea();clearmessagearea();clearmaparea();

   set_color(COLOR_WHITE,COLOR_BLACK,1);
   move(9,1);addstr(a.name, gamelog);addstr("は言った。", gamelog);
   set_color(COLOR_GREEN,COLOR_BLACK,1);
   move(10,1);
   addstr("「やあ。銃が欲しいんだ。」", gamelog);
   gamelog.newline();

   getkey();

   if(a.is_naked() && a.animalgloss!=ANIMALGLOSS_ANIMAL)
   {
      set_color(COLOR_WHITE,COLOR_BLACK,1);
      move(12,1);addstr(tk.name, gamelog);addstr("は答えた。", gamelog);
      set_color(COLOR_CYAN,COLOR_BLACK,1);
      move(13,1);
      addstr("「ジーザス…」", gamelog);
      gamelog.newline();

      getkey();

      return 1;
   }
   if(a.get_armor().get_itemtypename() == "ARMOR_POLICEUNIFORM" ||
      a.get_armor().get_itemtypename() == "ARMOR_POLICEARMOR" ||
      a.get_armor().get_itemtypename() == "ARMOR_SWATARMOR" ||
      (law[LAW_POLICEBEHAVIOR]==-2 && law[LAW_DEATHPENALTY]==-2 &&
      a.get_armor().get_itemtypename() == "ARMOR_DEATHSQUADUNIFORM"))
   {
      set_color(COLOR_WHITE,COLOR_BLACK,1);
      move(12,1);addstr(tk.name, gamelog);addstr("は答えた。", gamelog);
      set_color(COLOR_CYAN,COLOR_BLACK,1);
      move(13,1);
      addstr("「お巡りさん、銃は売っていません。」", gamelog);
      gamelog.newline();

      getkey();

      return 1;
   }
   if(sitealarm!=0)
   {
      set_color(COLOR_WHITE,COLOR_BLACK,1);
      move(12,1);addstr(tk.name, gamelog);addstr("は答えた。", gamelog);
      set_color(COLOR_CYAN,COLOR_BLACK,1);
      move(13,1);
      addstr("「騒ぎが収まったら売ってやる。」", gamelog);
      gamelog.newline();

      getkey();

      return 1;
   }
   switch(location[cursite]->type)
   {
   case SITE_OUTDOOR_BUNKER:
   case SITE_BUSINESS_CRACKHOUSE:
   case SITE_BUSINESS_BARANDGRILL:
   case SITE_BUSINESS_ARMSDEALER:
   case SITE_RESIDENTIAL_TENEMENT:
   case SITE_RESIDENTIAL_BOMBSHELTER:
   case SITE_RESIDENTIAL_SHELTER:
      set_color(COLOR_WHITE,COLOR_BLACK,1);
      move(12,1);addstr(tk.name, gamelog);addstr("は答えた。", gamelog);
      set_color(COLOR_CYAN,COLOR_BLACK,1);
      move(13,1);
      addstr("「どれが要るんだ? 」", gamelog);
      gamelog.newline();

      getkey();

      armsdealer(cursite);
      return 1;
   default:
      set_color(COLOR_WHITE,COLOR_BLACK,1);
      move(12,1);addstr(tk.name, gamelog);addstr("は答えた。", gamelog);
      set_color(COLOR_CYAN,COLOR_BLACK,1);
      move(13,1);
      addstr("「うーむ…ここではダメだ。」", gamelog);
      gamelog.newline();

      getkey();

      return 1;
   }
}

char wannaHearSomethingDisturbing(Creature &a, Creature &tk)
{
   clearcommandarea();clearmessagearea();clearmaparea();

   set_color(COLOR_WHITE,COLOR_BLACK,1);
   move(9,1);addstr(a.name, gamelog);addstr("は言った。", gamelog);

   set_color(COLOR_GREEN,COLOR_BLACK,1);
   move(10,1);
   addstr("「ちょっといいですか。」", gamelog);
   gamelog.newline();

   getkey();

   bool interested = tk.talkreceptive();

   if(!interested && a.skill_check(SKILL_PERSUASION,DIFFICULTY_AVERAGE))
      interested = true;

   if((tk.animalgloss==ANIMALGLOSS_ANIMAL&&tk.align!=ALIGN_LIBERAL)||
      tk.animalgloss==ANIMALGLOSS_TANK)
   {
      set_color(COLOR_WHITE,COLOR_BLACK,1);
      move(12,1);addstr(tk.name, gamelog);

      switch(tk.type)
      {
      case CREATURE_TANK: addstr("はただ音を立てている。", gamelog); break;
      case CREATURE_GUARDDOG: addstr("は吠えた。", gamelog); break;
      default: addstr("はわからないようだ。", gamelog); break;
      }
      gamelog.newline();

      getkey();

      return 1;
   }
   else if(strcmp(tk.name,"囚人")!=0 && interested)
   {
      set_color(COLOR_WHITE,COLOR_BLACK,1);
      move(12,1);addstr(tk.name, gamelog);addstr("は答えた。", gamelog);
      set_color(COLOR_CYAN,COLOR_BLACK,1);
      move(13,1);
      addstr("「何か? 」", gamelog);
      gamelog.newline();

      getkey();

      return talkAboutIssues(a, tk);
   }
   else
   {
      set_color(COLOR_WHITE,COLOR_BLACK,1);
      move(12,1);addstr(tk.name, gamelog);addstr("は答えた。", gamelog);
      set_color(COLOR_CYAN,COLOR_BLACK,1);
      move(13,1);
      if(strcmp(tk.name,"囚人")==0)
      {
         if(tk.align==ALIGN_LIBERAL)
            addstr("「今はダメだ! 」", gamelog);
         else addstr("「ほっといてくれ。」", gamelog);
      }
      else addstr("「いいえ。」", gamelog);
      set_color(COLOR_WHITE,COLOR_BLACK,1);
      addstr(" <立ち去った>", gamelog);
      gamelog.newline();

      getkey();

      return 1;
   }
}

char doYouComeHereOften(Creature &a, Creature &tk)
{
   int y=12;
   clearcommandarea();clearmessagearea();clearmaparea();
   set_color(COLOR_WHITE,COLOR_BLACK,1);
   move(9,1);addstr(a.name, gamelog);addstr("は言った。", gamelog);
   set_color(COLOR_GREEN,COLOR_BLACK,1);
   move(10,1);
   int line;
   if(law[LAW_FREESPEECH]==-2)
   {
      line=LCSrandom(3);
      switch(line)
      {
         case 0:addstr("「 [どの教会へ行っていますか? ] 」", gamelog);break;
         case 1:addstr("「 [結婚してくれますか? ] 」", gamelog);break;
         case 2:addstr("「 [純潔教育を信頼しますか? ] 」", gamelog);break;
      }
   }
   else
   {
      line=LCSrandom(47);
      switch(line)
      {
      case 0:addstr("「あなたはあまり美しくない…だがそこがいい。」", gamelog);break;
      case 1:addstr("「電話番号をなくしてしまって…。あなたのを貸してくれないか? 」", gamelog);break;
      case 2:addstr("「やあ。私のコレを擦ってみたくないか? 」", gamelog);break;
      case 3:addstr("「すげえ。レンガ造りの便所みたいに丈夫でたくましい肉体だ。」", gamelog);break;
      case 4:addstr("「あなたのことは牛乳パックの尋ね人で見たことがある。", gamelog);
             move(11,1);y++;
             addstr("  あなたは私が探していた人だ。」", gamelog);
             break;
      case 5:addstr("「大切な所はデカいぜ。」", gamelog);break;
      case 6:addstr("「美しい人。あなたの脚で顔を覆い、マスクのように身につけたい! 」", gamelog); // Bill Hicks
             break;
      case 7:addstr("「リスごっこをしよう。あなたの中にナッツを隠したい。」", gamelog);break;
      case 8:addstr("「わかっている。もし私があなたならば、私とセックスしたいはずだ。」", gamelog);break;
      case 9:addstr("「太ったヒヨコちゃんのために苦労したくないな。」", gamelog);break;
      case 10:addstr("「私が間違っているならファックしてくれ。でも、あなたは私とキスしたい。", gamelog);
              move(11,1);y++;
              addstr("  そうだろう? 」", gamelog);break;
      case 11:addstr("「あなたの両親は知恵遅れに違いない。なぜならあなたは特別だからだ。」", gamelog);break;
      case 12:addstr("「電車ごっこをしよう…あなたが顔に座って、私がチューチューチュー…」", gamelog);break;
      case 13:addstr("「暑くないか? それとも君のせい? 」", gamelog);break;
      case 14:addstr("「私はフレッド・フリントストーンにはなれないが、あなたのベッドを揺らすことは", gamelog);
              move(11,1);y++;
              addstr("  できる! 」", gamelog);break;
      case 15:addstr("「あの岩の陰で小石を拾わないか? 」", gamelog);break;
      case 16:addstr("「あなたのパンツは宇宙か? 地球上のものとは思えないお尻だ! 」", gamelog);break;
      case 17:addstr("「このパンツはベッドルームの床にあってこそ美しい。」", gamelog);break;
      case 18:addstr("「いい体だねって言ったらハグしてくれる? 」", gamelog);break;
      case 19:addstr("「疲れてない? 私の頭の中を一日中グルグルと回っていたから。」", gamelog);break;
      case 20:addstr("「もしアルファベットの順番を変えられるなら、UとIを一緒にしたい! 」", gamelog);break;
      case 21:addstr("「あなたの唇は甘そうだ。味見してもいい? 」", gamelog);break;
      case 22:addstr("「いい靴だね。ファックしない? 」", gamelog);break;
      case 23:addstr("「あなたのセクシーさが私を不安で欲求不満にしている。」", gamelog);break;
      case 24:addstr("「興奮してきた。もしかしてジャマイカ人? 」", gamelog);break;
      case 25:addstr("「やあポップタルト、私の愛のトースターの中を想像してごらん? 」", gamelog);break;
      case 26:addstr("「戦争ごっこをしないか? 君が倒れて私がぶっ放すんだ。」", gamelog);break;
      case 27:addstr("「おでこを舐めていい? 」", gamelog);break;
      case 28:addstr("「アソコに発疹があるんだ。この薬を塗ってくれないか? 」", gamelog);break;
      case 29:addstr("「あなたは何座? 」", gamelog);break;
      case 30:addstr("「宅配便で働いてる? ", gamelog);
            move(11,1);y++;
            addstr("  私のパッケージ(巨根)をチェックしているから。」", gamelog);
            break;
      case 31:addstr("「私はここで一番魅力的な人物ではないが、", gamelog);
            move(11,1);y++;
            addstr("  あなたと話している唯一の人物だ。」", gamelog);
            break;
      case 32:addstr("「やあ。記憶喪失なんだ。君と会ったことある? 」", gamelog);break;
      case 33:addstr("「このあたりは初めてなんだ。君の家はどこか教えてくれる? 」", gamelog);break;
      case 34:addstr("「私が迎えに行くまで待ってて! 」", gamelog);break;
      case 35:addstr("「お父さんはパン屋? いいバン(丸いパン、ケツ)してるから。」", gamelog);break;
      case 36:addstr("「もしあなたがレーザーなら、「スタン」にセットしているはずだ。」", gamelog);break;
      case 37:addstr("「パンツにビヤ樽を入れてるの? タップしたくなるお尻だ。」", gamelog);break;
      case 38:addstr("「もしなれるなら、あなたのお風呂の湯になりたい。」", gamelog);break;
      case 39:addstr("「ストップ、ドロップ アンド ロール、燃えているぜ。」", gamelog);break;
      case 40:addstr("「膨らんだ何かを見たくないか? 」", gamelog);break;
      case 41:addstr("「ファックして欲しい? それとも謝るべき? 」", gamelog);break;
      case 42:addstr("「ねえ、別の学校に一緒に行かなかった? 」", gamelog);break;
      case 43:addstr("「臭うな…一緒にシャワーを浴びよう。」", gamelog);break;
      case 44:addstr("「バラは赤く、スミレは青い。", gamelog);
            move(11,1);y++;
            addstr("  オール・マイ・ベース・アー・ビロング・トゥ・ユー。」", gamelog);
            break;
      case 45:addstr("「天国から落ちてきたときケガしなかった? 」", gamelog);break;
      case 46:addstr("「ヤバい、今すぐ君とセックスしたい! 」", gamelog);break;
      }
   }
   gamelog.newline();

   getkey();

   bool succeeded = false;

   int difficulty = DIFFICULTY_HARD;

   if(tk.type == CREATURE_CORPORATE_CEO)
      difficulty = DIFFICULTY_HEROIC;

   if(a.is_naked() && a.animalgloss!=ANIMALGLOSS_ANIMAL) difficulty-=4;

   if(a.skill_check(SKILL_SEDUCTION,difficulty))
      succeeded = true;

   if((tk.animalgloss==ANIMALGLOSS_ANIMAL&&law[LAW_ANIMALRESEARCH]!=2&&a.animalgloss!=ANIMALGLOSS_ANIMAL)||
      tk.animalgloss==ANIMALGLOSS_TANK)
   {
      set_color(COLOR_WHITE,COLOR_BLACK,1);
      move(y++,1);addstr(tk.name, gamelog);

      switch(tk.type)
      {
      case CREATURE_TANK:
         addstr("は機関砲を振ってはっきりと「いいえ」を表した。", gamelog);
         break;
      case CREATURE_GUARDDOG:
         addstr("は言った。", gamelog);
         move(y,1);
         set_color(COLOR_RED,COLOR_BLACK,1);
         switch(LCSrandom(3))
         {
         case 0:addstr("『ダメだ! 間違っている! 私は犬だ!! ジーザス。』", gamelog);break;
         case 1:addstr("『何だと?! ううむ、このドッグフードをやろう。』", gamelog);break;
         case 2:addstr("『そうか。まず撫でるのをやめろ。』", gamelog);break;
         }
         tk.align=ALIGN_CONSERVATIVE;
         tk.cantbluff=1;
         break;
      case CREATURE_GENETIC:
         addstr("は言った。", gamelog);
         move(y,1);
         set_color(COLOR_RED,COLOR_BLACK,1);
         switch(LCSrandom(8))
         {
         case 0:addstr("『愚かなニンゲンめ! 』", gamelog);break;
         case 1:addstr("『そのようなことを聞くとは思わなかったぞ…』", gamelog);break;
         case 2:addstr("『おかしなヤツだ。』", gamelog);break;
         case 3:addstr("『笑えんな。死すべき者よ! 』", gamelog);break;
         case 4:addstr("『黙れ! 』", gamelog);break;
         case 5:addstr("『我にそのような冗談を言うのか?!』", gamelog);break;
         case 6:addstr("『我はそのような死すべき罪を超越しているのだ! 』", gamelog);break;
         case 7:addstr("『愚かな、滅び行くニンゲンよ…! 』", gamelog);break;
         }
         tk.align=ALIGN_CONSERVATIVE;
         tk.cantbluff=1;
         break;
      default:
         addstr("は全くわからなかったようだ。", gamelog);
      }
      gamelog.newline();

      getkey();

      return 1;
   }

   a.train(SKILL_SEDUCTION,LCSrandom(5)+2);

   if((a.get_armor().get_itemtypename() == "ARMOR_POLICEUNIFORM" // Police property on armor? -XML
      || a.get_armor().get_itemtypename() == "ARMOR_POLICEARMOR"
      || a.get_armor().get_itemtypename() == "ARMOR_SWATARMOR"
      || (law[LAW_POLICEBEHAVIOR]==-2 && law[LAW_DEATHPENALTY]==-2
      && a.get_armor().get_itemtypename() == "ARMOR_DEATHSQUADUNIFORM"))
      && tk.type==CREATURE_PROSTITUTE)
   {
      set_color(COLOR_WHITE,COLOR_BLACK,1);
      move(y++,1);addstr(tk.name, gamelog);addstr("は答えた。", gamelog);
      set_color(COLOR_RED,COLOR_BLACK,1);
      move(y++,1);

      addstr("「卑猥な。違法行為だとわかっていますよね? 」", gamelog);
      gamelog.newline();

      getkey();

      tk.cantbluff=1;
   }
   else if(succeeded)
   {
      set_color(COLOR_WHITE,COLOR_BLACK,1);
      move(y++,1);addstr(tk.name, gamelog);addstr("は答えた。", gamelog);
      set_color(COLOR_CYAN,COLOR_BLACK,1);
      move(y++,1);

      if(law[LAW_FREESPEECH]==-2)
      {
         switch(line)
         {
            case 0:addstr("「 [あなたの教会です。] 」", gamelog);break;
            case 1:addstr("「 [はい。] 」", gamelog);break;
            case 2:addstr("「 [はい。もちろん。] 」", gamelog);break;
         }
      }
      else
      {
         switch(line)
         {
         //LIMIT          :-----------------------------------------------------------------------------:
         case 0 :addstr("「あなたもね。少し休んでいきませんか? 」", gamelog);break;
         case 1 :addstr("「ステキな人! 今夜電話してください…」", gamelog);break;
         case 2 :addstr("「もちろん。」", gamelog);break;
         case 3 :addstr("「へっへっ。見逃してやるよ。ところで、私は田舎者が大好きなんだ…」", gamelog);break;
         case 4 :addstr("「あなたは病気だ。そして今夜、もっと病が重くなる…」", gamelog);break;
         case 5 :addstr("「おおお、見せてくれ! 」", gamelog);break;
         case 6 :addstr("「ええ。今夜、あなたの望みを叶えましょう! 」", gamelog);break;
         case 7 :addstr("「冬が近い。1つでは足りませんね。」", gamelog);break;
         case 8 :addstr("「でもあなたは私ではない。その喜びは全て私のもの…。」", gamelog);break;
         case 9 :addstr("「ベイビー、ただ夜まで待ってて。」", gamelog);break;
         case 10:addstr("「あなたは間違っている。」", gamelog);break;
         case 11:addstr("「お望みならばよだれを垂らしてあげましょうか? 」", gamelog);break;
         case 12:addstr("「おおおお、赤ちゃんが乗ってます! 」", gamelog);break;
         case 13:addstr("「今夜のあなたよりは暑くないな。」", gamelog);break;
         case 14:addstr("「今夜にしましょう。」", gamelog);break;
         case 15:addstr("\"Oooo, we should get stoned too!  He he.\"", gamelog);break;
         case 16:addstr("「あなたのロケットを用意して。さあ行きましょう。」", gamelog);break;
         case 17:addstr("「私の下着もね。」", gamelog);break;
         case 18:addstr("「もちろん。そしてそのお返しは今夜して。」", gamelog);break;
         case 19:addstr("「だったら*考える*のを止めて今夜会いましょう。」", gamelog);break;
         case 20:addstr("「その間にコンドームがあるなら大賛成よ。」", gamelog);break;
         case 21:addstr("「もちろん。でも口を使ってはダメよ。」", gamelog);break;
         case 22:addstr("「足フェチなの? でもいいわ。」", gamelog);break;
         case 23:addstr("「私とセックスしたらもっとそうなるわ。」", gamelog);break;
         case 24:addstr("「楽園の島に招待してあげる。今夜。」", gamelog);break;
         case 25:addstr("「ああ…何も言わないで。すぐに行きます。」", gamelog);break;
         case 26:addstr("「空砲がいいわ、兵隊さん。コンドームを切らせてるから。」", gamelog);break;
         case 27:addstr("「私のデカールを全部舐め取って、ベイビー。」", gamelog);break;
         case 28:addstr("「手を使わないならいいわ。」", gamelog);break;
         case 29:addstr("「私の星座は『一晩中OK』よ。」", gamelog);break;
         case 30:addstr("「小包爆弾みたい。私に吹き飛ばさせて。」", gamelog);break;
         case 31:addstr("\"Hey, I could do better.  But I'm feeling cheap tonight.\"", gamelog);break;
         case 32:addstr("「ええ。あのときのローションを憶えていたらいいんだけど。」", gamelog);break;
         case 33:addstr("「でもホテルを使いましょう。怒ったツレに撃たれないように。」", gamelog);break;
         case 34:addstr("「今夜は私の動きに感謝すると思うわ。", gamelog);break;
         case 35:addstr("\"They make a yummy bedtime snack.\"", gamelog);break;
         case 36:addstr("「ああ…トレッキーとデートできるなんで信じられない。」", gamelog);break;
         case 37:addstr("「危なくて運転できないわ。今夜は泊まりましょう。」", gamelog);break;
         case 38:addstr("「今夜来てくれればどんなものか見せてあげるわ。」", gamelog);break;
         case 39:addstr("「あなたとなら立ち止まって、倒れて、転がりたい。」", gamelog);break;
         case 40:addstr("「その膨らんだものを感じたいわ。」", gamelog);break;
         case 41:addstr("「後でベッドでうまく行かなかったら謝って。」", gamelog);break;
         case 42:addstr("「ええ。そして今夜、私たちは別の体位を一緒に試すわ。」", gamelog);break;
         case 43:addstr("「汚いのはお嫌い? 」", gamelog);break;
         case 44:addstr("「あ、あなたは!! 何者かが爆弾を仕掛けたようね。たのんだわ'ZIG'、私たちの未来に希望を。」", gamelog);break;
         case 45:addstr("「本当は地獄から来たサキュバス、そしてあなたが次の犠牲者よ。」", gamelog);break;
         case 46:addstr("「2時間待てる? まず他の6人とファックしないといけないの。」", gamelog);break;
         }
      }
      gamelog.newline();

      getkey();

      move(++y,1);
      set_color(COLOR_WHITE,COLOR_BLACK,1);
      move(y++,1);
      addstr(a.name, gamelog);
      addstr("と", gamelog);
      addstr(tk.name, gamelog);
      addstr("は今夜の予定を組んだ", gamelog);
      if(strcmp(tk.name,"囚人")==0)
      {
         addstr("。そして", gamelog);
         move(y++,1);
         addstr(tk.name, gamelog);
         addstr("は出入口を壊した", gamelog);
         criminalize(tk,LAWFLAG_ESCAPED);
      }
      addstr("。", gamelog);
      gamelog.newline();

      getkey();

      datest *newd=NULL;
      for(int d=0;d<len(date);d++)
      {
         if(date[d]->mac_id==a.id)
         {
            newd=date[d];
            break;
         }
      }

      if(newd==NULL)
      {
         newd=new datest;
            newd->mac_id=a.id;
            newd->city=location[a.location]->city;

         date.push_back(newd);
      }

      Creature *newcr=new Creature;
      *newcr=tk;
      newcr->namecreature();

      newcr->location=a.location;
      newcr->base=a.base;

      newd->date.push_back(newcr);

      delenc(&tk-encounter,0);
   }
   else
   {
      set_color(COLOR_WHITE,COLOR_BLACK,1);
      move(y++,1);addstr(tk.name, gamelog);addstr("は答えた。", gamelog);
      set_color(COLOR_RED,COLOR_BLACK,1);
      move(y++,1);
      if(tk.type == CREATURE_CORPORATE_CEO)
      {
         if(a.gender_liberal != GENDER_MALE)
            addstr("「私は男性と結婚できて幸せよ。」", gamelog);
         else addstr("「これはブロークバック・マウンテンではない。」", gamelog);
      }
      else if(law[LAW_FREESPEECH]==-2)
      {
         switch(line)
         {  // all 3 of these lines are from Darth Vader (the 3rd one from back when he's a little kid)
            case 0:addstr("「あなたの信念の欠如が気掛かりだ。」", gamelog);break;
            case 1:addstr("「違う、私があなたの父親だ。」", gamelog);break;
            case 2:addstr("「当てにしないほうがいいよ、スライム・ボール。」", gamelog);break;
         }
      }
      else
      {
         switch(line)
         {
         //LIMIT          :-----------------------------------------------------------------------------:
         case 0 : addstr("「あんたはクソみたいだ! 」", gamelog);
            set_color(COLOR_WHITE,COLOR_BLACK,1);
            addstr(" <怒っている>", gamelog);break;
         case 1 : addstr("「ええ、どうぞ…」", gamelog);
            set_color(COLOR_WHITE,COLOR_BLACK,1);
            addstr(" <嘘の番号を書いた>", gamelog);break;
         case 2 : addstr("「えーと…人を待っているので。」", gamelog);
            set_color(COLOR_WHITE,COLOR_BLACK,1);
            addstr(" <立ち去った>", gamelog);break;
         case 3 : addstr("「本物の便所へ行けよ、この田舎者。」", gamelog);
            set_color(COLOR_WHITE,COLOR_BLACK,1);
            addstr(" <トイレを指差した>", gamelog);break;
         case 4 : addstr("「トラウマでしょうね。」", gamelog);
            set_color(COLOR_WHITE,COLOR_BLACK,1);
            addstr(" <泣き出した>", gamelog);break;
         case 5 : addstr("「全部大きいぞ、デブ。」", gamelog);
            set_color(COLOR_WHITE,COLOR_BLACK,1);
            addstr(" <笑われた>", gamelog);break;
         case 6 : addstr("「最低だ。」", gamelog);
            set_color(COLOR_WHITE,COLOR_BLACK,1);
            addstr(" <立ち去った>", gamelog);break;
         case 7 : addstr("「リスとヤりたいのか? 」", gamelog);
            set_color(COLOR_WHITE,COLOR_BLACK,1);
            addstr(" <あぜんとしている>", gamelog);break;
         case 8 : addstr("「それはたくさんマス掻いてるってことか? 」", gamelog);
            set_color(COLOR_WHITE,COLOR_BLACK,1);
            addstr(" <指を前後に揺らした>", gamelog);break;
         case 9 : addstr("「あんたは豚だ。」", gamelog);
            set_color(COLOR_WHITE,COLOR_BLACK,1);
            addstr(" <立ち去った>", gamelog);break;
         case 10: addstr("「どっちもノーだ。」", gamelog);
            set_color(COLOR_WHITE,COLOR_BLACK,1);
            addstr(" <舌打ちした>", gamelog);break;
         case 11: addstr("「本気か? 」", gamelog);
            set_color(COLOR_WHITE,COLOR_BLACK,1);
            addstr(" <立ち去った>", gamelog);break;
         case 12: addstr("「咬みつかれそうだ。」", gamelog);
            set_color(COLOR_WHITE,COLOR_BLACK,1);
            addstr(" <たじろいた>", gamelog);break;
         case 13: addstr("「お前の友達じゃないぞ、クズ。」", gamelog);
            set_color(COLOR_WHITE,COLOR_BLACK,1);
            addstr(" <催涙スプレーを握った>", gamelog);break;
         case 14: addstr("「アニメでも見てたら? 」", gamelog);
            set_color(COLOR_WHITE,COLOR_BLACK,1);
            addstr(" <笑われた>", gamelog);break;
         case 15: addstr("\"I hate puns!  You suck at comedy.\"", gamelog);
            set_color(COLOR_WHITE,COLOR_BLACK,1);
            addstr(" <frowns>", gamelog);break;
         case 16: addstr("「そう、私はエイリアン。下等な地球のゴミめ。」", gamelog);
            set_color(COLOR_WHITE,COLOR_BLACK,1);
            addstr(" <光線銃を抜いた>", gamelog);break;
         case 17: addstr("「これをした後でなければ。」", gamelog);
            set_color(COLOR_WHITE,COLOR_BLACK,1);
            addstr(" <パンツにクソした>", gamelog);break;
         case 18: addstr("「そんな嘘はウンザリだ。」", gamelog);
            set_color(COLOR_WHITE,COLOR_BLACK,1);
            addstr(" <たるんだ腕でバツを作った>", gamelog);break;
         case 19: addstr("「そんなことをした覚えはない。」", gamelog);
            set_color(COLOR_WHITE,COLOR_BLACK,1);
            addstr(" <困惑している>", gamelog);break;
         case 20: addstr("「幼稚園を落第したヤツがいるぞ! 」", gamelog);
            set_color(COLOR_WHITE,COLOR_BLACK,1);
            addstr(" <指をさして笑われた>", gamelog);break;
         case 21: addstr("「ダメよ。ヘルペスを移したくないから。」", gamelog);
            set_color(COLOR_WHITE,COLOR_BLACK,1);
            addstr(" <sighs>", gamelog);break;
         case 22: addstr("「足を見るのをやめて。気持ち悪い! 」", gamelog);
            set_color(COLOR_WHITE,COLOR_BLACK,1);
            addstr(" <蹴られた>", gamelog);break;
         case 23: addstr("「負け犬め。」", gamelog);
            set_color(COLOR_WHITE,COLOR_BLACK,1);
            addstr(" <額にLのジェスチャーをした>", gamelog);break;
         case 24: addstr("「お前のケツの穴にヴードゥーの呪いを掛けてやる…」", gamelog);
            set_color(COLOR_WHITE,COLOR_BLACK,1);
            addstr(" <呪文を唱え始めた>", gamelog);break;
         case 25: addstr("「あなたの高炭水化物の食生活は問題だ。」", gamelog);
            set_color(COLOR_WHITE,COLOR_BLACK,1);
            addstr(" <健康について語り始めた>", gamelog);break;
         case 26: addstr("「家に帰ってG.I.ジョーで遊んでろ。」", gamelog);
            set_color(COLOR_WHITE,COLOR_BLACK,1);
            addstr(" <あざ笑った>", gamelog);break;
         case 27: addstr("「ダメです。迷子の子犬のように振る舞うのはやめて。」", gamelog);
            set_color(COLOR_WHITE,COLOR_BLACK,1);
            addstr(" <猫のようにシャーッと音を立てた>", gamelog);break;
         case 28: addstr("「ジーザス…」", gamelog);
            set_color(COLOR_WHITE,COLOR_BLACK,1);
            addstr(" <立ち去った>", gamelog);break;
         case 29: addstr("「星占いは信じられない。無知な人。」", gamelog);
            set_color(COLOR_WHITE,COLOR_BLACK,1);
            addstr(" <科学で目くらましされた>", gamelog);break;
         case 30: addstr("「ええ。これはSSサイズですね。」", gamelog);
            set_color(COLOR_WHITE,COLOR_BLACK,1);
            addstr(" <人差し指と親指を近づけた>", gamelog);break;
         case 31: addstr("「ツレがいるので。」", gamelog);
            set_color(COLOR_WHITE,COLOR_BLACK,1);
            addstr(" <パートナーを指差した>", gamelog);break;
         case 32: addstr("「あなたはタイプじゃない。普通の人がいい。」", gamelog);
            set_color(COLOR_WHITE,COLOR_BLACK,1);
            addstr(" <立ち去った>", gamelog);break;
         case 33: addstr("「ええ、ここです…」", gamelog);
            set_color(COLOR_WHITE,COLOR_BLACK,1);
            addstr(" <嘘の場所を書いた>", gamelog);break;
         case 34: addstr("「急いでるので! さようなら! 」", gamelog);
            set_color(COLOR_WHITE,COLOR_BLACK,1);
            addstr(" <身をよじって去った>", gamelog);break;
         case 35: addstr("「アナルはやらないの。」", gamelog);
            set_color(COLOR_WHITE,COLOR_BLACK,1);
            addstr(" <手で尻を覆った>", gamelog);break;
         case 36: addstr("「おい見ろ、UFOだ! 」", gamelog);
            set_color(COLOR_WHITE,COLOR_BLACK,1);
            addstr(" <伏せながら去った>", gamelog);break;
         case 37: addstr("「帰れ、酔っ払いめ。」", gamelog);
            set_color(COLOR_WHITE,COLOR_BLACK,1);
            addstr(" <追い払うジェスチャーをされた>", gamelog);break;
         case 38: addstr("「そのためには溶けてしまわないとね。」", gamelog);
            set_color(COLOR_WHITE,COLOR_BLACK,1);
            addstr(" <興味深そうに見ている>", gamelog);break;
         case 39: addstr("「バーーーカ。」", gamelog);
            set_color(COLOR_WHITE,COLOR_BLACK,1);
            addstr(" <うんざりしている>", gamelog);break;
         case 40: addstr("「オェ、気持ち悪い。」", gamelog);
            set_color(COLOR_WHITE,COLOR_BLACK,1);
            addstr(" <あなたにゲロした>", gamelog);break;
         case 41: addstr("「謝ってももう遅いよ! 」", gamelog);
            set_color(COLOR_WHITE,COLOR_BLACK,1);
            addstr(" <頬を打たれた>", gamelog);break;
         case 42: addstr("「何てバカなの! 」", gamelog);
            set_color(COLOR_WHITE,COLOR_BLACK,1);
            addstr(" <笑われた>", gamelog);break;
         case 43: addstr("「ほっといて頂戴。どうしようもないの。」", gamelog);
            set_color(COLOR_WHITE,COLOR_BLACK,1);
            addstr(" <泣き出した>", gamelog);break;
         case 44: addstr("「ハハハハハ! 」", gamelog);
            set_color(COLOR_WHITE,COLOR_BLACK,1);
            addstr(" <首を振った>", gamelog);break;
         case 45: addstr("「ええ。すぐに出て行って。」", gamelog);
            set_color(COLOR_WHITE,COLOR_BLACK,1);
            addstr(" <出口を指差した>", gamelog);break;
         case 46: addstr("「指一本触れたら後悔するよ。」", gamelog);
            set_color(COLOR_WHITE,COLOR_BLACK,1);
            addstr(" <腕でバツを作った>", gamelog);break;
         }
      }
      gamelog.newline();

      getkey();

      tk.cantbluff=1;
   }

   return 1;
}
char talkAboutIssues(Creature &a, Creature &tk)
{
   int lw = LCSrandom(LAWNUM); // pick a random law to talk about

   bool succeeded         = false;
   bool you_are_stupid    = false;
   bool issue_too_liberal = false;

   if(!(a.attribute_check(ATTRIBUTE_INTELLIGENCE,DIFFICULTY_EASY)))
      you_are_stupid = true;
   else if(law[lw]==ALIGN_ELITELIBERAL && newscherrybusted)
      issue_too_liberal = true;

   clearcommandarea();clearmessagearea();clearmaparea();
   set_color(COLOR_WHITE,COLOR_BLACK,1);
   move(9,1);addstr(a.name, gamelog);addstr("は言った。", gamelog);
   set_color(COLOR_GREEN,COLOR_BLACK,1);
   int y=10;
   move(y++,1);
   if(you_are_stupid)
   {
      switch(lw)
      {
      case LAW_ABORTION:      addstr("「保守派は女をコートのハンガーのようにしてしまう。」", gamelog);break;
      case LAW_ANIMALRESEARCH:addstr("「リチャード・ギアはケツの穴にネズミを入れたことがある! 」", gamelog);break;
      case LAW_POLICEBEHAVIOR:
                              if(law[LAW_FREESPEECH]==ALIGN_ARCHCONSERVATIVE)
                                  addstr("「 [警官はまじめに仕事をしていない! ] 」", gamelog);
                              else
                                  addstr("「ポリ公のクソッタレ! 」", gamelog);
                              break;
      case LAW_PRIVACY:       addstr("「政府…のようなもの…はおまえのことは何でも知っている。」", gamelog);break;
      case LAW_DEATHPENALTY:  addstr("「死刑執行人は首をこうやって…さらに…頭を炎に投げ込むんだ。」", gamelog);break;
      case LAW_NUCLEARPOWER:  addstr("「ゴジラは見たか? 放射能は悪者だ。」", gamelog);break;
      case LAW_POLLUTION:     addstr("「『悪魔の毒々モンスター』を見たいのか? 公害に反対しよう! 」", gamelog);break;
      case LAW_LABOR:         addstr("「悪い奴らは赤ちゃんまで働かせようとしている。」", gamelog);break;
      case LAW_GAY:           addstr("「多くの人が同性愛者が好きではない。」", gamelog);break;
      case LAW_CORPORATE:     addstr("「企業は俺たちを押さえつけてるんだ。」", gamelog);break;
      case LAW_FREESPEECH:    addstr("「言葉には注意したほうがいい。ヤツらの耳はどこにでもある。」", gamelog);break;
      case LAW_FLAGBURNING:   addstr("「旗はバカげてる。」", gamelog);break;
      case LAW_TAX:           addstr("「金持ちは、金が、大好きだ。」", gamelog);break;
      case LAW_GUNCONTROL:    addstr("「銃が好きな人は、もっと銃が必要だと考えているんだ。」", gamelog);break;
      case LAW_WOMEN:         addstr("「俺たちにはもっと女が必要だ! 」", gamelog);break;
      case LAW_CIVILRIGHTS:   addstr("「保守はみんなレイシストだ! 」", gamelog);break;
      case LAW_DRUGS:         addstr("「政府は俺たちにドラッグを使わせようとしない。」", gamelog);break;
      case LAW_IMMIGRATION:   addstr("「ヤツらはみんな人々を国の外にいさせようとしている。」", gamelog);break;
      case LAW_ELECTIONS:     addstr("「政治家はただの企業の道具だ! 」", gamelog);break;
      case LAW_MILITARY:      addstr("「愛国者はバカだ! 平和を! 」", gamelog);break;
      case LAW_TORTURE:       addstr("「拷問はダメだ! 」", gamelog);break;
      case LAW_PRISONS:       addstr("「囚人には自由がない! 」", gamelog);break;
      }
   }
   else if(issue_too_liberal)
   {
      switch(lw)
      {
      case LAW_ABORTION:      addstr("「保守派は中絶が嫌いだ。」", gamelog);break;
      case LAW_ANIMALRESEARCH:addstr("「動物には投票権がない。」", gamelog);break;
      case LAW_POLICEBEHAVIOR:addstr("「いまだに警察は存在する。」", gamelog);break;
      case LAW_PRIVACY:       addstr("「政府には諜報機関がある。」", gamelog);break;
      case LAW_DEATHPENALTY:  addstr("「重犯罪を犯すと終身刑務所に入ることができる。」", gamelog);break;
      case LAW_NUCLEARPOWER:  addstr("「原子力を支持する者もいる。」", gamelog);break;
      case LAW_POLLUTION:     addstr("「我々はいまだに環境を汚染させている。」", gamelog);break;
      case LAW_LABOR:         addstr("「企業のトップは労働組合の要求に応じない。」", gamelog);break;
      case LAW_GAY:           addstr("「同性愛者が好きでない者もいる。」", gamelog);break;
      case LAW_CORPORATE:     addstr("「企業は存在している。」", gamelog);break;
      case LAW_FREESPEECH:    addstr("「人々はあなたが公共の場で多くを語ると怒り狂う。」", gamelog);break;
      case LAW_FLAGBURNING:   addstr("「国旗法は服を作るなと言っている。」", gamelog);break;
      case LAW_TAX:           addstr("「この国にはいまだに不平等が存在する。」", gamelog);break;
      case LAW_GUNCONTROL:    addstr("「修正第2条は破棄されるべきだ。」", gamelog);break;
      case LAW_WOMEN:         addstr("「一部の人々は性差別主義者だ。」", gamelog);break;
      case LAW_CIVILRIGHTS:   addstr("「私は一部の人々が人種差別主義者だということを知っている。」", gamelog);break;
      case LAW_DRUGS:         addstr("「ドラッグは高すぎる。」", gamelog);break;
      case LAW_IMMIGRATION:   addstr("「全ての移民は移民法が嫌いだ。」", gamelog);break;
      case LAW_ELECTIONS:     addstr("「一部の政治家は間違った方法で擦り寄ってくる。」", gamelog);break;
      case LAW_MILITARY:      addstr("「いまだに軍隊は存在する。」", gamelog);break;
      case LAW_TORTURE:       addstr("「拷問を支持する保守派がいる。」", gamelog);break;
      case LAW_PRISONS:       addstr("「いまだに囚人は存在する。」", gamelog);break;
      }
   }
   else
   {
      switch(lw)
      {
      case LAW_ABORTION:
         addstr("「政府は女性の自己決定権を組織的に奪おうとしている。」", gamelog);
         break;
      case LAW_ANIMALRESEARCH:
         addstr("「この国の動物たちは研究所で常にひどい扱いを受けている。」", gamelog);
         break;
      case LAW_POLICEBEHAVIOR:
         addstr("「警察はマイノリティの容疑者にしばしば拷問を行っている。」", gamelog);
         break;
      case LAW_PRIVACY:
         addstr("「人々を農場の動物のように飼いならすシステムに反対しただけの無実の市民の情報", gamelog);
         addstr("  が保管され続けている。」", gamelog);
         break;
      case LAW_DEATHPENALTY:
         addstr("「過去10年間で30人以上の人々が処刑されている。」", gamelog);
         break;
      case LAW_NUCLEARPOWER:
         addstr("「核廃棄物は何世紀にも渡って存在し、多くの家族の脅威となる。もちろんこの付近", gamelog);move(y++,1);
         addstr("  でも。」", gamelog);
         break;
      case LAW_POLLUTION:
         addstr("「利益のみを追求し、他のことは何もしない工場は環境を汚染させ、", gamelog);
         if (tk.animalgloss==ANIMALGLOSS_ANIMAL)
         {
            addstr("人間だけでなく", gamelog);move(y++,1);
            addstr("動物も傷つけている。」", gamelog);
         }
         else
         {
            addstr("動物だけでなく", gamelog);move(y++,1);
            addstr("人間も傷つけている。」", gamelog);
         }
         break;
      case LAW_LABOR:
         addstr("「労働時間はますます長くなっているのに、給料はますます低くなっていることに気", gamelog);move(y++,1);
         addstr("  づいているだろうか。人々は計画的に奴隷のように働かされている。」", gamelog);
         break;
      case LAW_GAY:
         addstr("「同性愛者はそうでない者と変わりない。だが、この国ではいまだに安っぽいエンタ", gamelog);move(y++,1);
         addstr("  ーテイメントに登場する逸脱者のような扱いを受けている。」", gamelog);
         break;
      case LAW_CORPORATE:
         addstr("「企業の重役たちは、寄生虫のように富をこの国から自分のポケット吸い出すために", gamelog);move(y++,1);
         addstr("  巨大企業を使っている。」", gamelog);
         break;
      case LAW_FREESPEECH:
         addstr("「この国では、抵抗と意思表明は定期的に、そして暴力的に押さえつけられている。", gamelog);move(y++,1);
         addstr("  私たちは彼らが何を書いているのか──何を読んでいるのかさえ注視しなければな", gamelog);move(y++,1);
         addstr("  らない。」", gamelog);
         break;
      case LAW_FLAGBURNING:
         addstr("「この国ではただ布切れを燃やしただけで汚名を着せられる。あなたには自由を愛し", gamelog);move(y++,1);
         addstr("  ながらも政府の行いを非難する権利がある。」", gamelog);
         break;
      case LAW_TAX:
         addstr("「税制度は、あなたを抑圧し続けている不公正な階級構造を永続させるように設計さ", gamelog);move(y++,1);
         addstr("  れている。」", gamelog);
         break;
      case LAW_GUNCONTROL:
         addstr("「私たちは、いつでも人を殺せるような力を持ち歩く権利があると人々が考えている", gamelog);move(y++,1);
         addstr("  ような遅れた世界に生きている。」", gamelog);
         break;
      case LAW_WOMEN:
         addstr("「隠れた性差別は依然として存在する。そして女性たちはその労働に対して遥かに少", gamelog);move(y++,1);
         addstr("  ない報酬しか受け取っていない。」", gamelog);
         break;
      case LAW_CIVILRIGHTS:
         addstr("「私たちの歩みにも関わらず、この社会は依然として続く人種差別と人種間の不平等", gamelog);move(y++,1);
         addstr("  に苦しめられている。」", gamelog);
         break;
      case LAW_DRUGS:
         addstr("「政府の薬物政策は乱雑だ。私たちは刑務所を薬物使用者でいっぱいにするのを止", gamelog);move(y++,1);
         addstr("  め、本当に助けが必要な人にのみ介入すべきだ。」", gamelog);
         break;
      case LAW_IMMIGRATION:
         addstr("「多くの移民は人々が望まない仕事を家族を養うためにしている。だが、私たちは彼", gamelog);move(y++,1);
         addstr("  らをただ追い返そうとしている。」", gamelog);
         break;
      case LAW_ELECTIONS:
         addstr("「政治的便宜が選挙献金で売り買いされている。そして選挙制度は2つの政党による", gamelog);move(y++,1);
         addstr("  支配を強制している。」", gamelog);
         break;
      case LAW_MILITARY:
         addstr("「深呼吸して私たちが生きているこの世界について考えてみよう。私たちは新しい方", gamelog);move(y++,1);
         addstr("  法で人を殺すために数千億ドルを費やしている。これを止めなければならない! 」", gamelog);
         break;
      case LAW_TORTURE:
         addstr("「テロとの戦いの名の下、拷問と虐待を政府に許し私たちは自分の心を捨て去ってし", gamelog);move(y++,1);
         addstr("  まった。」", gamelog);
         break;
      case LAW_PRISONS:
         addstr("「刑務所制度は犯罪者の更生の助けになっていない。そのため、彼らは刑務所を出て", gamelog);move(y++,1);
         addstr("  も多くの場合再び犯罪を犯すのだ。」", gamelog);
         break;
      }
   }
   gamelog.newline();

   getkey();

   int difficulty = DIFFICULTY_VERYEASY;

   if(tk.align == ALIGN_CONSERVATIVE)
      difficulty += 7;
   if(!(tk.talkreceptive()))
      difficulty += 7;
   if(you_are_stupid)
      difficulty += 5;
   if(issue_too_liberal)
      difficulty += 5;
   if(a.is_naked() && a.animalgloss!=ANIMALGLOSS_ANIMAL)
      difficulty += 5;

   succeeded = a.skill_check(SKILL_PERSUASION,difficulty);

   // Prisoners never accept to join you, you must liberate them instead
   if(succeeded && strcmp(tk.name,"囚人")!=0)
   {
      set_color(COLOR_WHITE,COLOR_BLACK,1);
      move((++y)++,1);addstr(tk.name, gamelog);addstr("は答えた。", gamelog);
      set_color(COLOR_CYAN,COLOR_BLACK,1);
      move(y++,1);
      if(tk.type==CREATURE_MUTANT&&tk.get_attribute(ATTRIBUTE_INTELLIGENCE,true)<3)
         addstr("「ア゛ア゛ァ゛ァ゛……」", gamelog);
      else
      {
         switch(LCSrandom(10))
         {
         case 0: addstr("「ええっ! 私たちに何かできることはないのか? 」", gamelog); break;
         case 1: addstr("「それはひどい! 私に何かできることはある? 」", gamelog); break;
         case 2: addstr("「ああ! 私に何かできることはあるのか? 」", gamelog); break;
         case 3: addstr("「恐ろしい! 私たちはどうすればよいのか? 」", gamelog); break;
         case 4: addstr("「おお! 本当か? 」", gamelog);

                 getkey();

                 move(y++,1);
                 set_color(COLOR_GREEN,COLOR_BLACK,1);
                 addstr("「ああ、本当だ! 」", gamelog);
                 break;
         case 5: addstr("「オー・マイ・サイエンス! 我々は何かしなければ! 」", gamelog); break;
         case 6: addstr("「ううむ… それは… 大変だ。」", gamelog); break;
         case 7: addstr("「ヒェーッ! 何とかしなければ! 」", gamelog);break;
         case 8: addstr("「それよりもタバコを持ってないか? 」", gamelog);
                 set_color(COLOR_WHITE,COLOR_BLACK,1);
                 addstr("*ゴホン*", gamelog);
                 break;
         case 9: addstr("「大変だ。それは許せないな。」", gamelog);break;
         }
      }
      gamelog.newline();

      getkey();

      move(++y,1);
      set_color(COLOR_WHITE,COLOR_BLACK,1);
      addstr("更なる議論の後、", gamelog);
      addstr(tk.name, gamelog);
      addstr("と今夜会う約束をした。", gamelog);
      gamelog.newline();

      getkey();

      Creature *newcr=new Creature;
      *newcr=tk;
      newcr->namecreature();

      recruitst *newrst=new recruitst;
      newrst->recruit=newcr;
      newrst->recruiter_id = a.id;

      recruit.push_back(newrst);

      delenc(&tk-encounter,0);
      return 1;
   }
   else
   {
      set_color(COLOR_WHITE,COLOR_BLACK,1);
      move((++y)++,1);addstr(tk.name, gamelog);addstr("は答えた。", gamelog);
      set_color(COLOR_CYAN,COLOR_BLACK,1);
      if(tk.type==CREATURE_MUTANT&&
         tk.get_attribute(ATTRIBUTE_INTELLIGENCE,true)<3)
      {
         move(y++,1);
         addstr("「ウゥ…シュー。」", gamelog);
      }
      else
      {
         if(tk.align==ALIGN_CONSERVATIVE && you_are_stupid)
         {
            move(y++,1);
            if(tk.type==CREATURE_GANGUNIT)
               addstr("「逮捕されたいのか? 」", gamelog);
            else if(tk.type==CREATURE_DEATHSQUAD)
               addstr("「黙れ。さもないと撃つぞ。」", gamelog);
            else
            {
               switch(LCSrandom(10))
               {
               case 0:addstr("「うせろ、ヒッピーめ。」", gamelog);break;
               case 1:addstr("「私の心が人間性で痛んでいる。」", gamelog);break;
               case 2:addstr("「残念だが話すことは何もない。」", gamelog);break;
               case 3:addstr("「出口がわからないのか? 」", gamelog);break;
               case 4:addstr("「あなたの様な人がいるから私は投薬治療を受けているのだ。」", gamelog);break;
               case 5:addstr("「あらゆる者には愚行権がある。だが、あなたはそれを乱用している。」", gamelog);break;
               case 6:addstr("「あなたが何をしているのかは知らないが、それが合法であることを願っている。」", gamelog);break;
               case 7:addstr("「仮出所中なのか? 」", gamelog);break;
               case 8:addstr("「ああ、なぜあなたに返事をしなければならないのだ? 」", gamelog);break;
               case 9:addstr("「子供に戻ったのか? 」", gamelog);break;
               }
            }
         }
         else if(tk.align != ALIGN_LIBERAL && tk.attribute_check(ATTRIBUTE_WISDOM,DIFFICULTY_AVERAGE))
         {
            move(y++,1);
            switch(lw)
            {
            case LAW_ABORTION:      addstr("「中絶は殺人だ。」", gamelog);break;
            case LAW_ANIMALRESEARCH:addstr("「動物を人のように扱うべきではない。」", gamelog);break;
            case LAW_POLICEBEHAVIOR:addstr("「警察を恐れるのは犯罪者だけだ。」", gamelog);break;
            case LAW_PRIVACY:       addstr("「国防は重要だ。」", gamelog);break;
            case LAW_DEATHPENALTY:  addstr("「死がふさわしい者もいる。」", gamelog);break;
            case LAW_NUCLEARPOWER:  addstr("「原子力はクリーンだ。」", gamelog);break;
            case LAW_POLLUTION:     addstr("「問題にするほどではない。」", gamelog);break;
            case LAW_LABOR:         addstr("「市場原理に任せろ。それでうまくいく。」", gamelog);break;
            case LAW_GAY:           addstr("「同性愛は反道徳的だ。」", gamelog);break;
            case LAW_CORPORATE:     addstr("「企業は資本主義の一部だ。」", gamelog);break;
            case LAW_FREESPEECH:    addstr("「攻撃的にならなければ問題ない。」", gamelog);break;
            case LAW_FLAGBURNING:   addstr("「その旗は私たちの国の侵すべからざるシンボルだ。」", gamelog);break;
            case LAW_TAX:           addstr("「税金は軽いほうがよい。」", gamelog);break;
            case LAW_GUNCONTROL:    addstr("「銃がなければ我々は政府の奴隷だ。」", gamelog);break;
            case LAW_WOMEN:         addstr("「なぜブラシャーなどを燃やしてしまわないのだ? 」", gamelog);break;
            case LAW_CIVILRIGHTS:   addstr("「逆差別もまた差別だ。」", gamelog);break;
            case LAW_DRUGS:         addstr("「薬物は社会に恐ろしい影響を与えている。」", gamelog);break;
            case LAW_IMMIGRATION:   addstr("「移民は私たちの経済と文化を弱体化させる。」", gamelog);break;
            case LAW_ELECTIONS:     addstr("「選挙運動の制限の撤廃は言論の自由の問題だ。」", gamelog);break;
            case LAW_MILITARY:      addstr("「軍は私たちを守り、私たちの生活様式を可能にしている。」", gamelog);break;
            case LAW_TORTURE:       addstr("「テロリストはより恐ろしいことを私たちにしている。」", gamelog);break;
            case LAW_PRISONS:       addstr("「犯罪者はその報いとして刑務所にいる。」", gamelog);break;
            }
         }
         else
         {
            move(y++,1);
            addstr("「どうでもいい。」", gamelog);
         }
      }
      set_color(COLOR_WHITE,COLOR_BLACK,1);
      addstr(" <立ち去った>", gamelog);
      gamelog.newline();

      getkey();

      tk.cantbluff=1;
      return 1;
   }
   return 0;
}

char talkInCombat(Creature &a, Creature &tk)
{
   clearcommandarea();
   clearmessagearea();
   clearmaparea();

   set_color(COLOR_WHITE,COLOR_BLACK,1);
   move(9,1);
   addstr(a.name, gamelog);
   addstr("が", gamelog);
   switch(tk.align)
   {
   case ALIGN_CONSERVATIVE: set_color(COLOR_RED,COLOR_BLACK,1); break;
   case ALIGN_LIBERAL: set_color(COLOR_GREEN,COLOR_BLACK,1); break;
   case ALIGN_MODERATE: set_color(COLOR_WHITE,COLOR_BLACK,1); break;
   }
   addstr(tk.name, gamelog);
   set_color(COLOR_WHITE,COLOR_BLACK,1);
   addstr("に話しかける:", gamelog);
   gamelog.newline();

   int c=0,hostages=0,weaponhostage=0;
   bool cop=0;

   for(int i=0;i<6;i++)
   {
      if(activesquad->squad[i]&&
         activesquad->squad[i]->prisoner&&
         activesquad->squad[i]->prisoner->alive&&
         activesquad->squad[i]->prisoner->enemy())
      {
         hostages++;
         if (activesquad->squad[i]->get_weapon().can_threaten_hostages())
           weaponhostage++;
      }
   }
   if(tk.type==CREATURE_COP ||
      tk.type==CREATURE_GANGUNIT ||
      tk.type==CREATURE_DEATHSQUAD ||
      tk.type==CREATURE_SWAT ||
      tk.type==CREATURE_SECURITYGUARD ||
      tk.type==CREATURE_MERC ||
      tk.type==CREATURE_SOLDIER ||
      tk.type==CREATURE_MILITARYPOLICE ||
      tk.type==CREATURE_MILITARYOFFICER ||
      tk.type==CREATURE_SEAL)
   {
      cop=1;
   }

   set_color(COLOR_WHITE,COLOR_BLACK,0);
   move(11,1);
   addstr("A - 威圧する");
   if(!hostages)set_color(COLOR_BLACK,COLOR_BLACK,1);
   move(12,1);
   addstr("B - 人質を脅かす");
   if(tk.cantbluff!=2)set_color(COLOR_WHITE,COLOR_BLACK,0);
   else set_color(COLOR_BLACK,COLOR_BLACK,1);
   move(13,1);
   addstr("C - 嘘をつく");
   if(cop)set_color(COLOR_WHITE,COLOR_BLACK,0);
   else set_color(COLOR_BLACK,COLOR_BLACK,1);
   move(14,1);
   addstr("D - 投降する");
   set_color(COLOR_WHITE,COLOR_BLACK,0);
   while(true)
   {
      c=getkey();

      if(c=='a')break;
      if(c=='b' && hostages)break;
      if(c=='c' && tk.cantbluff!=2)break;
      if(c=='d' && cop)break;
   }

   if(c=='a')
   {
      set_color(COLOR_WHITE,COLOR_BLACK,1);
      move(16,1);
      addstr(a.name, gamelog);
      addstr(": ", gamelog);
      move(17,1);
      set_color(COLOR_GREEN,COLOR_BLACK,1);

      switch(LCSrandom(4))
      {
      case 0:
         {   // Formatting the slogan so that it always has quotes around it and punctuation
            if(slogan[0]!='"') addchar('"',gamelog);
            addstr(slogan,gamelog);
            int last=len(slogan);
            if(last && slogan[last-1]!='"' && slogan[last-1]!='!' && slogan[last-1]!='.' && slogan[last-1]!='?')
               addchar('!',gamelog);
            if(last && slogan[last-1]!='"') addchar('"',gamelog);

            if(!sitestory->claimed)
               sitestory->claimed=1;
            break;
         }
      case 1: addstr("「くたばれ! 保守の犬め! 」", gamelog); break;
      case 2: addstr("「我々はリベラル・クライム・スコードだ! 」", gamelog); break;
      case 3: addstr("「命乞いをしても無駄だ! 」", gamelog); break;
      }

      getkey();

      set_color(COLOR_WHITE,COLOR_BLACK,1);

      for(int e=0;e<ENCMAX;e++)
      {
         if(encounter[e].exists&&encounter[e].alive&&encounter[e].enemy())
         {
            int attack = a.juice / 50 + attitude[VIEW_LIBERALCRIMESQUAD] / 10;
            int defense = encounter[e].attribute_roll(ATTRIBUTE_WISDOM);

            if(attack > defense)
            {
               if(encounter[e].type==CREATURE_COP||
                  encounter[e].type==CREATURE_GANGUNIT||
                  encounter[e].type==CREATURE_SWAT||
                  encounter[e].type==CREATURE_DEATHSQUAD||
                  encounter[e].type==CREATURE_SOLDIER||
                  encounter[e].type==CREATURE_HARDENED_VETERAN||
                  encounter[e].type==CREATURE_CCS_ARCHCONSERVATIVE||
                  encounter[e].type==CREATURE_AGENT||
                  encounter[e].type==CREATURE_SECRET_SERVICE)
               {
                  if(LCSrandom(3)) continue;
               }
               clearmessagearea();
               move(16,1);
               addstr(encounter[e].name, gamelog);
               switch(LCSrandom(6))
               {
               case 0:addstr("は怖気づいた!", gamelog);break;
               case 1:addstr("は後ずさりした!", gamelog);break;
               case 2:addstr("はまだ死にたくない!", gamelog);break;
               case 3:addstr("は立ち去った!", gamelog);break;
               case 4:addstr("には家族がいる!", gamelog);break;
               case 5:addstr("は死ぬには若すぎる!", gamelog);break;
               }
               delenc(e,0);
               addjuice(a,2,200); // Instant juice!

               getkey();
            }
         }
      }
   }
   else if(c=='b')
   {
      set_color(COLOR_WHITE,COLOR_BLACK,1);
      move(16,1);
      addstr(a.name, gamelog);
      addstr(": ", gamelog);
      set_color(COLOR_GREEN,COLOR_BLACK,1);
      move(17,1);
      switch(LCSrandom(6))
      {
      case 0:addstr("「下がれ! こいつの命はないぞ! 」", gamelog);break;
      case 1:addstr("「LCSをナメるな! 」", gamelog);
         if(!sitestory->claimed)sitestory->claimed=1;break;
      case 2:addstr("「こいつも去れと言っている! 」", gamelog);break;
      case 3:addstr("「こいつを殺すぞ! 」", gamelog);break;
      case 4:addstr("「私を怒らせたと家族に知られたいのか?!」", gamelog);break;
      case 5:
             if(law[LAW_FREESPEECH]==-2)addstr("「 [遊び] はよせ! 」", gamelog);
             else addstr("「馬鹿な真似はよせ! 」", gamelog);
             break;
      }
      gamelog.newline();

      sitecrime+=5;
      criminalizeparty(LAWFLAG_KIDNAPPING);

      addjuice(a,-2,-10); // DE-juice for this shit

      getkey();

      bool noretreat=false;

      if(weaponhostage)
      {
         int e;
         for(e=0;e<ENCMAX;e++)
         {
            if(encounter[e].exists&&encounter[e].alive&&
               encounter[e].enemy()&&encounter[e].blood>70)
            {
               if((encounter[e].type==CREATURE_DEATHSQUAD||
                  encounter[e].type==CREATURE_SOLDIER||
                  encounter[e].type==CREATURE_HARDENED_VETERAN||
                  encounter[e].type==CREATURE_CCS_ARCHCONSERVATIVE||
                  encounter[e].type==CREATURE_AGENT||
                  encounter[e].type==CREATURE_MERC||
                  encounter[e].type==CREATURE_COP||
                  encounter[e].type==CREATURE_GANGUNIT||
                  encounter[e].type==CREATURE_SWAT||
                  encounter[e].type==CREATURE_SECRET_SERVICE)&&
                  LCSrandom(5))
               {
                  set_color(COLOR_WHITE,COLOR_BLACK,1);
                  clearmessagearea();
                  move(16,1);
                  addstr(encounter[e].name, gamelog);
                  addstr(": ", gamelog);
                  move(17,1);

                  if(encounter[e].align!=ALIGN_CONSERVATIVE||
                     (encounter[e].type==CREATURE_SECRET_SERVICE&&exec[EXEC_PRESIDENT]>ALIGN_CONSERVATIVE))
                  {
                     set_color(COLOR_GREEN,COLOR_BLACK,1);
                     switch(LCSrandom(5))
                     {
                     case 0:addstr("「人質を解放しろ。自分が何をしているのかわかっているのか。」", gamelog);break;
                     case 1:addstr("「落ち着け。話をしよう。」", gamelog);break;
                     case 2:addstr("「待て! 要求は何だ。」", gamelog);break;
                     case 3:addstr("「お前は間違っている。よく考えろ。」", gamelog);break;
                     case 4:addstr("「落ち着け。要求は何だ。」", gamelog);break;
                     }
                  }
                  else
                  {
                     set_color(COLOR_RED,COLOR_BLACK,1);
                     if(((encounter[e].type==CREATURE_DEATHSQUAD||
                        encounter[e].type==CREATURE_AGENT||
                        encounter[e].type==CREATURE_MERC||
                        encounter[e].type==CREATURE_CCS_ARCHCONSERVATIVE||
                        encounter[e].type==CREATURE_GANGUNIT))
                        &&encounter[e].align==ALIGN_CONSERVATIVE)
                     {
                        switch(LCSrandom(5))
                        {
                        case 0:addstr("「ハハハハハ…」", gamelog);break;
                        case 1:addstr("「私を脅しているのか? 」", gamelog);break;
                        case 2:addstr("「ここから生きては出られないぞ。」", gamelog);break;
                        case 3:addstr("「どうしたんだ? オムツを替えて欲しいのか? 」", gamelog);break;
                        case 4:addstr("「3… 2…」", gamelog);break;
                        }
                     }
                     else
                     {
                        switch(LCSrandom(5))
                        {
                        case 0:
                           if(hostages>1)
                              addstr("「人質たちを解放しろ。誰も傷つけたくない。」", gamelog);
                           else addstr("「人質を解放しろ。誰も傷つけたくない。」", gamelog);
                           break;
                        case 1:addstr("「5秒以内に離れるんだ。」", gamelog);break;
                        case 2:addstr("「面倒なことにしたいのか? 」", gamelog);break;
                        case 3:addstr("「それは大きな過ちだ。」", gamelog);break;
                        case 4:addstr("「人質を解放しろ。そうすれば見逃してやる。」", gamelog);break;
                        }
                     }

                  }
                  gamelog.newline();

                  getkey();

                  noretreat=true;
                  break;
               }
            }
         }
         if(noretreat==false)
         {
            set_color(COLOR_WHITE,COLOR_BLACK,1);
            clearmessagearea();
            move(16,1);
            addstr("脅しが効いた! 保守は引き下がった。", gamelog);
            gamelog.newline();
            for(int i=ENCMAX;i>=0;i--)
            {
               if(encounter[i].exists&&
                  encounter[i].alive&&
                  encounter[i].align<=-1)
               {
                  delenc(i,0);
               }
            }

            getkey();
         }
         else
         {
            set_color(COLOR_WHITE,COLOR_BLACK,0);
            clearcommandarea();
            clearmessagearea();
            clearmaparea();
            move(9,1);
            addstr(a.name);
            addstr("はどう反応する?");
            move(11,1);
            if(hostages>1)
               addstr("A - 人質たちを殺害する");
            else
               addstr("A - 人質を殺害する");
            move(12,1);
            if(hostages>1)
               addstr("B - 条件を受け入れ人質たちを解放する");
            else
               addstr("B - 条件を受け入れ人質を解放する");
            move(13,1);
            addstr("C - 返事をしない");

            while(true)
            {
               c=getkey();

               if(c=='a'||c=='b')break; // TODO: something to happen if you press 'c'
            }
            if(c=='a')
            {
               Creature* executer=0;
               if(a.prisoner)
                  executer=&a;
               else for(int i=0;i<6;i++)
               {
                  if(activesquad->squad[i] &&
                     activesquad->squad[i]->prisoner &&
                     activesquad->squad[i]->prisoner->alive &&
                     activesquad->squad[i]->prisoner->enemy())
                  {
                     executer=activesquad->squad[i];
                     break;
                  }
               }

               move(16,1);
               set_color(COLOR_RED,COLOR_BLACK,1);
               if(executer->get_weapon().is_ranged()
                  && executer->get_weapon().get_ammoamount()>0)
               {
                  addstr("バン!", gamelog);
                  gamelog.newline();
                  executer->get_weapon().decrease_ammo(1); //What if it doesn't use ammo? -XML
               }
               else
               {
                  addstr("グシャ!", gamelog);
                  gamelog.newline();
               }

               getkey();

               move(17,1);
               set_color(COLOR_WHITE,COLOR_BLACK,1);
               addstr(executer->name, gamelog);
               addstr("は", gamelog);
               addstr(executer->prisoner->name, gamelog);
               addstr("の遺体を床に落とした。", gamelog);
               gamelog.newline();

               addjuice(*executer,-5,-50); // DE-juice for this shit
               sitecrime+=10;
               sitestory->crime.push_back(CRIME_KILLEDSOMEBODY);
               criminalize(*executer,LAWFLAG_MURDER);

               if(executer->prisoner->type==CREATURE_CORPORATE_CEO||
                  executer->prisoner->type==CREATURE_RADIOPERSONALITY||
                  executer->prisoner->type==CREATURE_NEWSANCHOR||
                  executer->prisoner->type==CREATURE_SCIENTIST_EMINENT||
                  executer->prisoner->type==CREATURE_JUDGE_CONSERVATIVE)sitecrime+=30;

               makeloot(*executer->prisoner,groundloot);

               getkey();

               delete_and_nullify(executer->prisoner);

               if(hostages>1&&LCSrandom(2))
               {
                  clearmessagearea();
                  set_color(COLOR_WHITE,COLOR_BLACK,1);
                  move(16,1);
                  addstr(encounter[e].name, gamelog);
                  addstr(": ", gamelog);
                  set_color(COLOR_RED,COLOR_BLACK,1);
                  move(17,1);
                  if(law[LAW_FREESPEECH]>ALIGN_ARCHCONSERVATIVE)
                     addstr("「畜生! ", gamelog);
                  else addstr("「 [ああ!] ", gamelog);
                  switch(LCSrandom(5))
                  {
                  case 0:addstr("わかった、わかった。お前の勝ちだ! 」", gamelog);break;
                  case 1:addstr("やりやがったな! 」", gamelog);break;
                  case 2:addstr("何とも思わないのか?!」", gamelog);break;
                  case 3:addstr("人でなしめ! 」", gamelog);break;
                  case 4:addstr("こんなことをするとは! 」", gamelog);break;
                  }
                  gamelog.newline();

                  for(int i=ENCMAX;i>=0;i--)
                     if(encounter[i].exists && encounter[i].enemy() && encounter[i].alive)
                        delenc(i,0);

                  getkey();
               }
            }
            else if(c=='b')
            {
               set_color(COLOR_WHITE,COLOR_BLACK,1);
               move(16,1);
               addstr(a.name, gamelog);
               addstr(": ", gamelog);
               set_color(COLOR_GREEN,COLOR_BLACK,1);
               move(17,1);
               switch(LCSrandom(5))
               {
               case 0:
                  if(hostages>1) addstr("「引き下がれ。そうすれば人質たちを解放する。」", gamelog);
                  else addstr("「引き下がれ。そうすれば人質を解放する。」", gamelog);
                  break;
               case 1:addstr("「自由のための自由、わかるな? 」", gamelog);break;
               case 2:addstr("「平和にいこう。なあ? 」", gamelog);break;
               case 3:addstr("「取り引きをしよう。」", gamelog);break;
               case 4:addstr("「ここから出たいだけだ。わかったな? 」", gamelog);break;
               }
               gamelog.newline();

               getkey();

               if(((encounter[e].type==CREATURE_DEATHSQUAD||
                  encounter[e].type==CREATURE_AGENT||
                  encounter[e].type==CREATURE_MERC||
                  encounter[e].type==CREATURE_CCS_ARCHCONSERVATIVE||
                  encounter[e].type==CREATURE_GANGUNIT)&&
                  LCSrandom(2))&&encounter[e].align==ALIGN_CONSERVATIVE)
               {
                  clearmessagearea();
                  set_color(COLOR_WHITE,COLOR_BLACK,1);
                  move(16,1);
                  addstr(encounter[e].name, gamelog);
                  addstr(": ", gamelog);
                  set_color(COLOR_RED,COLOR_BLACK,1);
                  move(17,1);
                  switch(LCSrandom(5))
                  {
                  case 0:addstr("「私が慈悲深い人間に見えるか? 」", gamelog);break;
                  case 1:addstr("「信用すると思っているのか? 」", gamelog);break;
                  case 2:addstr("「これが世界のためだ。」", gamelog);break;
                  case 3:addstr("「惨めな…」", gamelog);break;
                  case 4:addstr("「これが取り引きだ。」", gamelog);break;
                  }
                  gamelog.newline();

                  getkey();
               }
               else
               {
                  clearmessagearea();
                  set_color(COLOR_WHITE,COLOR_BLACK,1);
                  move(16,1);
                  addstr(encounter[e].name, gamelog);
                  addstr(": ", gamelog);
                  set_color(COLOR_RED,COLOR_BLACK,1);
                  move(17,1);
                  switch(LCSrandom(4))
                  {
                  case 0:addstr("「わかった。そうしよう。」", gamelog);break;
                  case 1:addstr("「これ以上の条件は無しだ。」", gamelog);break;
                  case 2:addstr("「人質を行かせろ。それで終わりだ。」", gamelog);break;
                  case 3:addstr("「だまし討ちはないな? 」", gamelog);break;
                  }
                  gamelog.newline();

                  getkey();

                  for(int i=ENCMAX;i>=0;i--)
                     if(encounter[i].exists&&encounter[i].enemy()&&encounter[i].alive)
                        delenc(i,0);
                  clearmessagearea();
                  set_color(COLOR_WHITE,COLOR_BLACK,1);
                  move(16,1);
                  juiceparty(15,200); // Instant juice for successful hostage negotiation
                  if(hostages>1)addstr("部隊は取り引きで人質全員を解放した。", gamelog);
                  else addstr("部隊は取り引きで人質を解放した。", gamelog);
                  gamelog.newline();
                  for(int i=0;i<6;i++)
                  {
                     if(activesquad->squad[i] &&
                        activesquad->squad[i]->prisoner &&
                        activesquad->squad[i]->prisoner->enemy())
                     {
                        delete_and_nullify(activesquad->squad[i]->prisoner);
                     }
                  }

                  getkey();
               }
            }
         }
      }
      else
      {
         set_color(COLOR_WHITE,COLOR_BLACK,1);
         clearmessagearea();
         move(16,1);
         addstr(tk.name, gamelog);
         addstr("にはハッタリは効かなかった。", gamelog);
         gamelog.newline();

         getkey();
      }
   }
   else if(c=='c')
   {
      set_color(COLOR_WHITE,COLOR_BLACK,1);
      move(16,1);
      if(location[cursite]->siege.siege)
      {
         addstr(a.name, gamelog);
         addstr("は", gamelog);
         switch(location[cursite]->siege.siegetype)
         {
            case SIEGE_POLICE:
               addstr("警官のふりをした。", gamelog);
               break;
            case SIEGE_CIA:
               addstr("諜報員のふりをした。", gamelog);
               break;
            case SIEGE_CCS:
            case SIEGE_HICKS:
               switch(LCSrandom(2))
               {
                  case 0:
                     addstr("\"Next of Kin\"" "のパトリック・スウェイジのように", gamelog);
                     move(17,1);
                     addstr("山のふりをした。", gamelog);
                     break;
                  case 1:
                     addstr("『脱出』のネッド・ビーティのように金切り声を", gamelog);
                     move(17,1);
                     addstr("上げた。", gamelog);
                     break;
               }
               break;
            case SIEGE_CORPORATE:
               addstr("民間傭兵のふりをした。", gamelog);
               break;
            case SIEGE_FIREMEN:
               addstr("マッチを擦り、床に向かって投げた。", gamelog);
               if((!(levelmap[locx][locy][locz].flag & SITEBLOCK_FIRE_END) ||
                  !(levelmap[locx][locy][locz].flag & SITEBLOCK_FIRE_PEAK) ||
                  !(levelmap[locx][locy][locz].flag & SITEBLOCK_FIRE_START) ||
                  !(levelmap[locx][locy][locz].flag & SITEBLOCK_DEBRIS)) && !LCSrandom(10))
               {
                  levelmap[locx][locy][locz].flag |= SITEBLOCK_FIRE_START;
                  move(17,1);
                  addstr("カーペットがくすぶり、やがて炎が上がった。", gamelog);
                  gamelog.newline();
                  move(18,1);
                  addstr("これは失敗だったかもしれない…", gamelog);
               }
               break;
         }
      }
      else        //Special bluff messages for various uniforms
      {
         set_color(COLOR_GREEN, COLOR_BLACK, 1);
         if(a.get_armor().get_itemtypename() == "ARMOR_POLICEUNIFORM" ||
            a.get_armor().get_itemtypename() == "ARMOR_POLICEARMOR" ||
            a.get_armor().get_itemtypename() == "ARMOR_SWATARMOR")
         {
            addstr("「状況はコントロール下にある。」", gamelog);
         }
         else if (a.get_armor().get_itemtypename() == "ARMOR_BUNKERGEAR")
         {
            if(siteonfire) addstr("「よし! 撤収! 」", gamelog);
            else addstr("「点検は完了しました。」", gamelog);
         }

         else if(a.get_armor().get_itemtypename() == "ARMOR_LABCOAT")
            addstr("「道を開けてくれ。私は医者だ! 」", gamelog);

         else if(a.get_armor().get_itemtypename() == "ARMOR_DEATHSQUADUNIFORM")
            addstr("「非目標は建物から退去せよ。」", gamelog);

         else if(a.get_armor().get_itemtypename() == "ARMOR_MITHRIL")
         {
            addstr(a.name, gamelog);
            addstr("は床に", gamelog);
            set_color(COLOR_CYAN, COLOR_BLACK, 1);
            addstr("Elbereth", gamelog);     //Fanciful multicolor message
            set_color(COLOR_GREEN, COLOR_BLACK, 1);
            addstr("の文字を刻んだ。", gamelog);
         }
         else
         {
            addstr(a.name, gamelog);
            addstr("は保守のように話し、", gamelog);
            move(17,1);
            addstr("この場所の者のように振る舞った。", gamelog);
         }
      }
      gamelog.newline();

      getkey();

      bool fooled=true;
      int e;

      for(e=0;e<ENCMAX;e++)
      {
         if(encounter[e].exists&&encounter[e].alive&&
            encounter[e].enemy())
         {
            int roll = a.skill_roll(SKILL_DISGUISE);
            int diff = encounter[e].get_attribute(ATTRIBUTE_WISDOM,true)>10 ? DIFFICULTY_CHALLENGING : DIFFICULTY_AVERAGE;
            fooled = roll >= diff;
            
            if (roll+1 == diff && fieldskillrate == FIELDSKILLRATE_HARD)
               a.train(SKILL_DISGUISE, 20);
            

            if(!fooled) break;
         }
      }

      switch (fieldskillrate)
      {
         case FIELDSKILLRATE_FAST:
            a.train(SKILL_DISGUISE, 50);break;
         case FIELDSKILLRATE_CLASSIC:
            a.train(SKILL_DISGUISE, 20);break;
         case FIELDSKILLRATE_HARD:
            a.train(SKILL_DISGUISE, 0);break;
      }

      if(!fooled)
      {
         clearmessagearea();

         set_color(COLOR_RED,COLOR_BLACK,1);
         move(16,1);
         if(encounter[e].type==CREATURE_HICK)
         {
            addstr("だが", gamelog);
            addstr(encounter[e].name, gamelog);
            addstr("はお人よしではない。", gamelog);
         }
         else
         {
            addstr(encounter[e].name, gamelog);
            if(law[LAW_FREESPEECH]==ALIGN_ARCHCONSERVATIVE)
               addstr("は芝居に騙されなかった。", gamelog);
            else addstr("は芝居に騙されなかった。", gamelog);
         }

         getkey();
      }
      else
      {
         clearmessagearea();

         set_color(COLOR_GREEN,COLOR_BLACK,1);
         move(16,1);
         addstr("敵は騙され去って行った。", gamelog);

         getkey();

         for(int e=ENCMAX-1;e>=0;e--)
            if(encounter[e].exists&&encounter[e].alive&&encounter[e].enemy())
               delenc(e,0);
      }
      gamelog.newline();
   }
   else
   {
      move(14,1);
      set_color(COLOR_WHITE,COLOR_BLACK,1);
      addstr("部隊は逮捕された。", gamelog);
      gamelog.newline();

      getkey();

      int stolen=0;
      // Police assess stolen goods in inventory
      for(int l=0;l<len(activesquad->loot);l++)
         if(activesquad->loot[l]->is_loot())
            stolen++;

      for(int i=0;i<6;i++)
      {
         if(activesquad->squad[i])
         {
            activesquad->squad[i]->crimes_suspected[LAWFLAG_THEFT]+=stolen;
            capturecreature(*activesquad->squad[i]);
         }
         activesquad->squad[i]=NULL;
      }
      location[cursite]->siege.siege=0;
   }
   return 1;
}

char heyMisterDog(Creature &a, Creature &tk)
{
   bool success = false;
   const char *pitch;
   const char *response;

   // Find most Heartful Liberal
   int bestp=0;
   for(int p=0; p<6; p++)
   {
      if(activesquad->squad[p] &&
         activesquad->squad[p]->get_attribute(ATTRIBUTE_HEART, true) >
         activesquad->squad[bestp]->get_attribute(ATTRIBUTE_HEART, true))
      {
         bestp = p;
      }
   }

   // Say something unbelievably hippie
   if(activesquad->squad[bestp]->get_attribute(ATTRIBUTE_HEART, true) >= 15)
   {
      success = true;
      switch(LCSrandom(11))
      {
      case 0:
         pitch = "「人間よりも犬が大好きだ。」";
         response = "『好みのヒトだ。あらゆる意味で。』";
         break;
      case 1:
         pitch = "「犬こそが未来の人類だ。」";
         response = "『それはわからぬ。だが、それが聞きたかった。』";
         break;
      case 2:
         pitch = "「犬に力を!」";
         response = "『猫を打倒せよ! 』";
         break;
      case 3:
         pitch = "「犬をスカウトしています。」";
         response = "『何? 私は犬だ。どの組織の代理人だ? 』";
         break;
      case 4:
         pitch = "「LCSに入りたいか? 」";
         response = "『いい獣医療制度はあるのか? 』";
         break;
      case 5:
         pitch = "「ほどいて欲しい? 」";
         response = "『ああ、頼む。この首輪は苦痛だ! 』";
         break;
      case 6:
         pitch = "「あなたはこれよりも価値がある。」";
         response = "『もちろんだ。よくわかっているニンゲンだ。』";
         break;
      case 7:
         pitch = "「犬は最高の存在だ。」";
         response = "『ヘヘヘ、面白いヤツだ。OK、お前を信じよう。』";
         break;
      case 8:
         pitch = "「保守は犬を蹴る! 」";
         response = "『それは困るな。何をすればいい? 』";
         break;
      case 9:
         pitch = "「ノミを我等に。」";
         response = "『痒みが治まるまでノミと戦うだろう。』";
         break;
      case 10:
      default:
         pitch = "「犬は人間より良い。」";
         response = "『自分を蔑むな。だがすばらしい。』";
         break;
      }
   }
   else // or not
   {
      tk.cantbluff=1;
      switch(LCSrandom(11))
      {
      case 0:
         pitch = "「やあ犬さん! 」";
         response = "「ワン? 」";
         break;
      case 1:
         pitch = "「グッド・ドッグ! 」";
         response = "「ガウ! 」";
         break;
      case 2:
         pitch = "「さあおいで。いい子だ。」";
         response = "「ワン! 」";
         break;
      case 3:
         pitch = "「わん…? 」";
         response = "「ワン! 」";
         break;
      case 4:
         pitch = "「吠えてみろ! 」";
         response = "「ガウ! グルル…」";
         break;
      case 5:
         pitch = "「伏せ! 」";
         response = "「クーン…? 」";
         break;
      case 6:
         pitch = "「咬まないでくれ! 」";
         response = "「グルル…! 」";
         break;
      case 7:
         pitch = "「やあワンちゃん! 」";
         response = "「ガウ! 」";
         break;
      case 8:
         pitch = "「やあ子犬さん。」";
         response = "「ガウ! 」";
         break;
      case 9:
         pitch = "「ああ、犬は大好きだ! 」";
         response = "「ガウ! 」";
         break;
      case 10:
      default:
         pitch = "「がう! がう! 」";
         response = "『ひどいアクセントだ。』";
         break;
      }
   }

   clearcommandarea();
   clearmessagearea();
   clearmaparea();

   set_color(COLOR_WHITE,COLOR_BLACK,1);
   move(10,1);
   addstr(activesquad->squad[bestp]->name, gamelog);
   addstr("は言った。", gamelog);
   move(11,1);
   set_color(COLOR_GREEN,COLOR_BLACK,1);
   addstr(pitch, gamelog);
   gamelog.newline();

   getkey();

   set_color(COLOR_WHITE,COLOR_BLACK,1);
   move(13,1);
   addstr(tk.name, gamelog);
   addstr("は言った。", gamelog);
   move(14,1);
   set_color(COLOR_YELLOW,COLOR_BLACK,1);
   addstr(response, gamelog);
   gamelog.newline();

   getkey();

   if(success)
      for(int i=0;i<ENCMAX;i++)
         if(encounter[i].type == CREATURE_GUARDDOG)
            encounter[i].align = ALIGN_LIBERAL;

   return 1;
}

char heyMisterMonster(Creature &a, Creature &tk)
{
   bool success = false;
   const char *pitch;
   const char *response;

   // Find most Heartful Liberal
   int bestp=0;
   for(int p=0; p<6; p++)
   {
      if(activesquad->squad[p] &&
         activesquad->squad[p]->get_attribute(ATTRIBUTE_HEART, true) >
         activesquad->squad[bestp]->get_attribute(ATTRIBUTE_HEART, true))
      {
         bestp = p;
      }
   }

   // Say something diplomatic
   if(activesquad->squad[bestp]->get_attribute(ATTRIBUTE_HEART, true) >= 15)
   {
      success = true;
      switch(LCSrandom(11))
      {
      case 0:
         pitch = "「私はいかなる場合でも多様性を重んじる。」";
         response = "『ニンゲンよ! その寛大さは見事だ。』";
         break;
      case 1:
         pitch = "「あなたの種こそが未来の人類だ。」";
         response = "『その理解は賢明だ。』";
         break;
      case 2:
         pitch = "「人造モンスターに力を! 」";
         response = "『ニンゲンに制裁を! 』";
         break;
      case 3:
         pitch = "「人造モンスターをスカウトしています。」";
         response = "『なぜ我らの力が必要なのだ? 』";
         break;
      case 4:
         pitch = "「LCSに入りたいか? 」";
         response = "『小さな子供は脅かせるのか? 』";
         break;
      case 5:
         pitch = "「あなたは自由だ! 私たちの仲間になってもっと自由になろう! 」";
         response = "『それは「同情とは何か」か? 』";
         break;
      case 6:
         pitch = "「あなたはこれよりも価値がある。」";
         response = "『実験する価値のある動物などいない! 』";
         break;
      case 7:
         pitch = "「あなたは最高の存在だ。」";
         response = "『いいヤツだ。仲良くしよう。』";
         break;
      case 8:
         pitch = "「共に遺伝学者を打ち倒そう! 」";
         response = "『楽しそうだ! 』";
         break;
      case 9:
         pitch = "「平和を我等に。」";
         response = "『ニンゲンが我々を平和にしたことがあるのか? 』";
         break;
      case 10:
      default:
         pitch = "「モンスターは人間より良い。」";
         response = "『賢いヤツだ。』";
         break;
      }
   }
   else // or not
   {
      tk.cantbluff=1;
      switch(LCSrandom(11))
      {
      case 0:
         pitch = "「やあモンスターさん! 」";
         response = "『燃え尽きて死ね! 』";
         break;
      case 1:
         pitch = "「グッド・モンスター! 」";
         response = "『燃え尽きて死ね! 』";
         break;
      case 2:
         pitch = "「うぉ…クソッ! 」";
         response = "『愚かな死すべき者よ! 』";
         break;
      case 3:
         pitch = "「殺さないでくれ! 」";
         response = "『オマエはもう死んでいる! 』";
         break;
      case 4:
         pitch = "「バカな! 」";
         response = "『オマエの神はどこへ行った?! 死すべき者よ。』";
         break;
      case 5:
         pitch = "「うう… この野郎! 」";
         response = "『オレは女だ! バカめ! 』";
         break;
      case 6:
         pitch = "「食べないでくれ! 」";
         response = "『生肉は好物だ! 』";
         break;
      case 7:
         pitch = "「失礼、私は…えー…」";
         response = "『死のうとしている?!』";
         break;
      case 8:
         pitch = "「シーッ… OK、私たちは友達だ! 」";
         response = "『オマエとオマエの友を殺してやる! 』";
         break;
      case 9:
         pitch = "「ああ、モンスターは大好きだ! 」";
         response = "『ちょうどいい。腹が減っていたのだ! 』";
         break;
      case 10:
      default:
         pitch = "「ズルズル! ブーン! ラララー! 」";
         response = "『オマエのゴマカシは死と出会うだろう! 』";
         break;
      }
   }

   clearcommandarea();
   clearmessagearea();
   clearmaparea();

   set_color(COLOR_WHITE,COLOR_BLACK,1);
   move(10,1);
   addstr(activesquad->squad[bestp]->name, gamelog);
   addstr("は言った。", gamelog);
   move(11,1);
   set_color(COLOR_GREEN,COLOR_BLACK,1);
   addstr(pitch, gamelog);
   gamelog.newline();

   getkey();

   set_color(COLOR_WHITE,COLOR_BLACK,1);
   move(13,1);
   addstr(tk.name, gamelog);
   addstr("は言った。", gamelog);
   move(14,1);
   set_color(COLOR_YELLOW,COLOR_BLACK,1);
   addstr(response, gamelog);
   gamelog.newline();

   getkey();

   if(success)
      for(int i=0;i<ENCMAX;i++)
         if(encounter[i].type == CREATURE_GENETIC)
            encounter[i].align = ALIGN_LIBERAL;

   return 1;
}
