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
   addstr("A - Quietly pass the teller a robbery note");
   if(a.is_naked() && a.animalgloss!=ANIMALGLOSS_ANIMAL)addstr(" while naked");
   addstr(".");
   move(12,1);
   addstr("B - Threaten bystanders and demand access to the vault");
   if(a.is_naked() && a.animalgloss!=ANIMALGLOSS_ANIMAL)addstr(" while naked");
   addstr(".");
   move(13,1);
   addstr("C - On second thought, don't rob the bank");
   if(a.is_naked() && a.animalgloss!=ANIMALGLOSS_ANIMAL)addstr(" while naked");
   addstr(".");

   int c;
   do c=getkey(); while(c<'a'&&c>'c');

   switch(c)
   {
   case 'a':
      clearcommandarea();clearmessagearea();clearmaparea();
      set_color(COLOR_WHITE, COLOR_BLACK, 1);
      move(9, 1);
      addstr(a.name, gamelog);
      addstr(" slips the teller a note: ", gamelog);
      set_color(COLOR_GREEN, COLOR_BLACK, 1);
      move(10, 1);
      switch(LCSrandom(10))
      {
      case 0:addstr("KINDLY PUT MONEY IN BAG. OR ELSE.", gamelog);break;
      case 1:addstr("I AM LIBERATING YOUR MONEY SUPPLY.", gamelog);break;
      case 2:addstr("THIS IS A ROBBERY. GIVE ME THE MONEY.", gamelog);break;
      case 3:addstr("I HAVE A GUN. CASH PLEASE.", gamelog);break;
      case 4:addstr("THE LIBERAL CRIME SQUAD REQUESTS CASH.", gamelog);break;
      case 5:addstr("I AM MAKING A WITHDRAWAL. ALL YOUR MONEY.", gamelog);break;
      case 6:addstr("YOU ARE BEING ROBBED. GIVE ME YOUR MONEY.", gamelog);break;
      case 7:addstr("PLEASE PLACE LOTS OF DOLLARS IN THIS BAG.", gamelog);break;
      case 8:addstr("SAY NOTHING. YOU ARE BEING ROBBED.", gamelog);break;
      case 9:addstr("ROBBERY. GIVE ME CASH. NO FUNNY MONEY.", gamelog);break;
      }
      gamelog.newline();

      getkey();

      if(location[cursite]->highsecurity)
      {
         set_color(COLOR_WHITE, COLOR_BLACK, 1);
         move(11, 1);
         addstr("The bank teller reads the note, ", gamelog);
         switch(LCSrandom(5))
         {
         case 0:addstr("gestures, ", gamelog);break;
         case 1:addstr("signals, ", gamelog);break;
         case 2:addstr("shouts, ", gamelog);break;
         case 3:addstr("screams, ", gamelog);break;
         case 4:addstr("gives a warning, ", gamelog);break;
         }
         move(12, 1);
         addstr("and dives for cover as the guards move in on the squad!", gamelog);
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
         addstr("The bank teller reads the note, ", gamelog);
         switch(LCSrandom(5))
         {
         case 0:addstr("nods calmly, ", gamelog);break;
         case 1:addstr("looks startled, ", gamelog);break;
         case 2:addstr("bites her lip, ", gamelog);break;
         case 3:addstr("grimaces, ", gamelog);break;
         case 4:addstr("frowns, ", gamelog);break;
         }
         move(12, 1);
         addstr("and slips several bricks of cash into the squad's bag.", gamelog);
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
         addstr(" brandishes the ", gamelog);
         addstr(armed_liberal->get_weapon().get_shortname(0), gamelog);
         addstr(".", gamelog);
         gamelog.newline();

         getkey();

         clearmessagearea();
      }
      move(10,1);
      addstr(a.name, gamelog);
      addstr(" says, ", gamelog);
      set_color(COLOR_GREEN,COLOR_BLACK,1);
      move(11,1);
      addstr("\"", gamelog);
      addstr(slogan, gamelog);
      gamelog.record(" ");
      move(12,1);
      addstr("OPEN THE VAULT, NOW!\"", gamelog);
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
         addstr("The bank teller and dives for cover as ", gamelog);
         move(10, 1);
         addstr("guards move in on the squad!", gamelog);
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
         addstr("The bank employees hesitantly cooperate!", gamelog);
         gamelog.newline();

         getkey();

         move(10, 1);
         addstr("The vault is open!", gamelog);
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
   addstr("「部屋を借りるのを止めたい。」", gamelog);
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
         case 2:addstr("\"[Do you believe in abstinence education?]\"", gamelog);break;
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
             addstr("あなたは私が探していた人だ。」", gamelog);
             break;
      case 5:addstr("「大切な所はデカいぜ。」", gamelog);break;
      case 6:addstr("\"Daaaaaamn girl, I want to wrap your legs around my face and ", gamelog);
             move(11,1);y++;
             addstr("wear you like a feed bag!\"", gamelog); // Bill Hicks
             break;
      case 7:addstr("\"Let's play squirrel.  I'll bust a nut in your hole.\"", gamelog);break;
      case 8:addstr("\"You know, if I were you, I'd have sex with me.\"", gamelog);break;
      case 9:addstr("\"You don't sweat much for a fat chick.\"", gamelog);break;
      case 10:addstr("\"Fuck me if I'm wrong but you want to kiss me, right?\"", gamelog);break;
      case 11:addstr("\"Your parents must be retarded, because you are special.\"", gamelog);break;
      case 12:addstr("\"Let's play trains...  you can sit on my face and I will chew chew chew.\"", gamelog);break;
      case 13:addstr("\"Is it hot in here or is it just you?\"", gamelog);break;
      case 14:addstr("\"I may not be Fred Flintstone, but I can make your bed rock!\"", gamelog);break;
      case 15:addstr("\"What do you say we go behind a rock and get a little boulder?\"", gamelog);break;
      case 16:addstr("\"Do you have stars on your panties?  Your ass is outta this world!\"", gamelog);break;
      case 17:addstr("\"Those pants would look great on the floor of my bedroom.\"", gamelog);break;
      case 18:addstr("\"If I said you had a nice body, would you hold it against me?\"", gamelog);break;
      case 19:addstr("\"Are you tired?  You've been running around in my thoughts all day.\"", gamelog);break;
      case 20:addstr("\"If I could change the alphabet baby, I would put the U and I together!\"", gamelog);break;
      case 21:addstr("\"Your lips look sweet.  Can I taste them?\"", gamelog);break;
      case 22:addstr("\"Nice shoes.  Wanna fuck?\"", gamelog);break;
      case 23:addstr("\"Your sexuality makes me nervous and this frustrates me.\"", gamelog);break;
      case 24:addstr("\"Are you Jamaican?  Cuz Jamaican me horny.\"", gamelog);break;
      case 25:addstr("\"Hey pop tart, fancy coming in my toaster of love?\"", gamelog);break;
      case 26:addstr("\"Wanna play army?  You lie down and I'll blow you away.\"", gamelog);break;
      case 27:addstr("\"Can I lick your forehead?\"", gamelog);break;
      case 28:addstr("\"I have a genital rash.  Will you rub this ointment on me?\"", gamelog);break;
      case 29:addstr("\"What's your sign?\"", gamelog);break;
      case 30:addstr("\"Do you work for the post office? ", gamelog);
            move(11,1);y++;
            addstr("Because I could have sworn you were checking out my package.\"", gamelog);
            break;
      case 31:addstr("\"I'm not the most attractive person in here, ", gamelog);
            move(11,1);y++;
            addstr("but I'm the only one talking to you.\"", gamelog);
            break;
      case 32:addstr("\"Hi.  I suffer from amnesia.  Do I come here often?\"", gamelog);break;
      case 33:addstr("\"I'm new in town.  Could you give me directions to your apartment?\"", gamelog);break;
      case 34:addstr("\"Stand still so I can pick you up!\"", gamelog);break;
      case 35:addstr("\"Your daddy must have been a baker, cuz you've got a nice set of buns.\"", gamelog);break;
      case 36:addstr("\"If you were a laser, you'd be set on 'stunning'.\"", gamelog);break;
      case 37:addstr("\"Is that a keg in your pants?  Cuz I'd love to tap that ass.\"", gamelog);break;
      case 38:addstr("\"If I could be anything, I'd love to be your bathwater.\"", gamelog);break;
      case 39:addstr("\"Stop, drop and roll, baby.  You are on fire.\"", gamelog);break;
      case 40:addstr("\"Do you want to see something swell?\"", gamelog);break;
      case 41:addstr("\"Excuse me.  Do you want to fuck or should I apologize?\"", gamelog);break;
      case 42:addstr("\"Say, did we go to different schools together?\"", gamelog);break;
      case 43:addstr("\"You smell...  Let's go take a shower.\"", gamelog);break;
      case 44:addstr("\"Roses are red, violets are blue,", gamelog);
            move(11,1);y++;
            addstr("All my base, are belong to you.\"", gamelog);
            break;
      case 45:addstr("\"Did it hurt when you fell from heaven?\"", gamelog);break;
      case 46:addstr("\"Holy shit you're hot!  I want to have sex with you RIGHT NOW.\"", gamelog);break;
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
         addstr(" shakes its turret a firm 'no'.", gamelog);
         break;
      case CREATURE_GUARDDOG:
         addstr(" says, ", gamelog);
         move(y,1);
         set_color(COLOR_RED,COLOR_BLACK,1);
         switch(LCSrandom(3))
         {
         case 0:addstr("\"No! Wrong! I'm a dog!! Jesus.\"", gamelog);break;
         case 1:addstr("\"What?! Ugh, I'm going to toss my kibble.\"", gamelog);break;
         case 2:addstr("\"Okay, you need to stop petting me now.\"", gamelog);break;
         }
         tk.align=ALIGN_CONSERVATIVE;
         tk.cantbluff=1;
         break;
      case CREATURE_GENETIC:
         addstr(" says, ", gamelog);
         move(y,1);
         set_color(COLOR_RED,COLOR_BLACK,1);
         switch(LCSrandom(8))
         {
         case 0:addstr("\"Foolish human!\"", gamelog);break;
         case 1:addstr("\"Never thought I'd hear that...\"", gamelog);break;
         case 2:addstr("\"STRANGER DANGER.\"", gamelog);break;
         case 3:addstr("\"I am not laughing, mortal!\"", gamelog);break;
         case 4:addstr("\"Gag!\"", gamelog);break;
         case 5:addstr("\"You would make jokes with the likes of me?!\"", gamelog);break;
         case 6:addstr("\"I am above such mortal sins!\"", gamelog);break;
         case 7:addstr("\"You foul, disgusting human...!\"", gamelog);break;
         }
         tk.align=ALIGN_CONSERVATIVE;
         tk.cantbluff=1;
         break;
      default:
         addstr(" doesn't quite pick up on the subtext.", gamelog);
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

      addstr("\"Dirty. You know that's illegal, officer.\"", gamelog);
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
            case 2:addstr("\"[Yes.  Yes, I do.]\"", gamelog);break;
         }
      }
      else
      {
         switch(line)
         {
         //LIMIT          :-----------------------------------------------------------------------------:
         case 0 :addstr("「あなたもね。少し休んでいきませんか? 」", gamelog);break;
         case 1 :addstr("「ステキな人! 今晩電話してください…」", gamelog);break;
         case 2 :addstr("「もちろん。」", gamelog);break;
         case 3 :addstr("「へっへっ。見逃してやるよ。ところで、私は田舎者が大好きなんだ…」", gamelog);break;
         case 4 :addstr("「病気だ。そして今夜、もっと病が重くなる…」", gamelog);break;
         case 5 :addstr("「おおお、見せてくれ! 」", gamelog);break;
         case 6 :addstr("\"Wow, looks like I'm going to have to reward creativity tonight!\"", gamelog);break;
         case 7 :addstr("\"Winter's coming.  You'd better bust more than one.\"", gamelog);break;
         case 8 :addstr("\"But you're not, so the pleasure's all mine.\"", gamelog);break;
         case 9 :addstr("\"Just wait until tonight, baby.\"", gamelog);break;
         case 10:addstr("\"You're wrong.\"", gamelog);break;
         case 11:addstr("\"I can drool on you if you like it that way.\"", gamelog);break;
         case 12:addstr("\"Oooo, all aboard baby!\"", gamelog);break;
         case 13:addstr("\"Not as hot as we'll be tonight you slut.\"", gamelog);break;
         case 14:addstr("\"Goober.  You wanna hook up tonight?\"", gamelog);break;
         case 15:addstr("\"Oooo, we should get stoned too!  He he.\"", gamelog);break;
         case 16:addstr("\"You'll have to whip out your rocket to get some.  Let's do it.\"", gamelog);break;
         case 17:addstr("\"So would my underwear.\"", gamelog);break;
         case 18:addstr("\"Yeah, and you're going to repay me tonight.\"", gamelog);break;
         case 19:addstr("\"Then stop *thinking* about it and come over tonight.\"", gamelog);break;
         case 20:addstr("\"As long as you put a condom between them, I'm all for it.\"", gamelog);break;
         case 21:addstr("\"Sure, but you can't use your mouth.\"", gamelog);break;
         case 22:addstr("\"I hope you don't have a foot fetish, but I'm game.\"", gamelog);break;
         case 23:addstr("\"My sex could do even more.\"", gamelog);break;
         case 24:addstr("\"Let me invite you to visit my island paradise.  Tonight.\"", gamelog);break;
         case 25:addstr("\"Oh, man...  just don't tell anybody I'm seeing you.\"", gamelog);break;
         case 26:addstr("\"I hope we're shooting blanks, soldier.  I'm out of condoms.\"", gamelog);break;
         case 27:addstr("\"You can lick all my decals off, baby.\"", gamelog);break;
         case 28:addstr("\"Only if I'm not allowed to use my hands.\"", gamelog);break;
         case 29:addstr("\"The one that says 'Open All Night'.\"", gamelog);break;
         case 30:addstr("\"It looks like a letter bomb to me.  Let me blow it up.\"", gamelog);break;
         case 31:addstr("\"Hey, I could do better.  But I'm feeling cheap tonight.\"", gamelog);break;
         case 32:addstr("\"Yeah.  I hope you remember the lube this time.\"", gamelog);break;
         case 33:addstr("\"But if we use a hotel, you won't get shot by an angry spouse tonight.\"", gamelog);break;
         case 34:addstr("\"I think you'll appreciate the way I move after tonight.\"", gamelog);break;
         case 35:addstr("\"They make a yummy bedtime snack.\"", gamelog);break;
         case 36:addstr("\"Oh..  oh, God.  I can't believe I'm going to date a Trekkie.\"", gamelog);break;
         case 37:addstr("\"Oh, it isn't safe for you to drive like that.  You'd better stay the night.\"", gamelog);break;
         case 38:addstr("\"Come over tonight and I can show you what it's like.\"", gamelog);break;
         case 39:addstr("\"I'll stop, drop and roll if you do it with me.\"", gamelog);break;
         case 40:addstr("\"I'd rather feel something swell.\"", gamelog);break;
         case 41:addstr("\"You can apologize later if it isn't any good.\"", gamelog);break;
         case 42:addstr("\"Yeah, and we tonight can try different positions together.\"", gamelog);break;
         case 43:addstr("\"Don't you like it dirty?\"", gamelog);break;
         case 44:addstr("\"It's you!!  Somebody set up us the bomb.  Move 'Zig'.  For great justice.\"", gamelog);break;
         case 45:addstr("\"Actually I'm a succubus from hell, and you're my next victim.\"", gamelog);break;
         case 46:addstr("\"Can you wait a couple hours?  I got 6 other people to fuck first.\"", gamelog);break;
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
         addstr("は出入り口を壊した", gamelog);
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
            addstr("\"I'm a happily married man, sweetie.\"", gamelog);
         else addstr("\"This ain't Brokeback Mountain, son.\"", gamelog);
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
         case 4 : addstr("「トラウマ的事件だ。」", gamelog);
            set_color(COLOR_WHITE,COLOR_BLACK,1);
            addstr(" <泣き出した>", gamelog);break;
         case 5 : addstr("「全部大きいぞ、デブ。」", gamelog);
            set_color(COLOR_WHITE,COLOR_BLACK,1);
            addstr(" <笑われた>", gamelog);break;
         case 6 : addstr("\"You're disgusting.\"", gamelog);
            set_color(COLOR_WHITE,COLOR_BLACK,1);
            addstr(" <turns away>", gamelog);break;
         case 7 : addstr("\"You fuck squirrels?\"", gamelog);
            set_color(COLOR_WHITE,COLOR_BLACK,1);
            addstr(" <looks dumbfounded>", gamelog);break;
         case 8 : addstr("\"So what you're saying is you masturbate a lot.\"", gamelog);
            set_color(COLOR_WHITE,COLOR_BLACK,1);
            addstr(" <wags finger>", gamelog);break;
         case 9 : addstr("\"You're a pig.\"", gamelog);
            set_color(COLOR_WHITE,COLOR_BLACK,1);
            addstr(" <turns away>", gamelog);break;
         case 10: addstr("\"Nice try, but no.\"", gamelog);
            set_color(COLOR_WHITE,COLOR_BLACK,1);
            addstr(" <sticks out tongue>", gamelog);break;
         case 11: addstr("\"Are you serious?\"", gamelog);
            set_color(COLOR_WHITE,COLOR_BLACK,1);
            addstr(" <turns away>", gamelog);break;
         case 12: addstr("\"You look like a biter.\"", gamelog);
            set_color(COLOR_WHITE,COLOR_BLACK,1);
            addstr(" <flinches>", gamelog);break;
         case 13: addstr("\"I'm way outta your league, scumbag.\"", gamelog);
            set_color(COLOR_WHITE,COLOR_BLACK,1);
            addstr(" <grabs pepper spray>", gamelog);break;
         case 14: addstr("\"You still watch cartoons?\"", gamelog);
            set_color(COLOR_WHITE,COLOR_BLACK,1);
            addstr(" <laughs>", gamelog);break;
         case 15: addstr("\"I hate puns!  You suck at comedy.\"", gamelog);
            set_color(COLOR_WHITE,COLOR_BLACK,1);
            addstr(" <frowns>", gamelog);break;
         case 16: addstr("\"Yes, I'm an alien, you inferior Earth scum.\"", gamelog);
            set_color(COLOR_WHITE,COLOR_BLACK,1);
            addstr(" <reaches for ray gun>", gamelog);break;
         case 17: addstr("\"Not after I do this.\"", gamelog);
            set_color(COLOR_WHITE,COLOR_BLACK,1);
            addstr(" <shits pants>", gamelog);break;
         case 18: addstr("\"Yes, I can't stand liars.\"", gamelog);
            set_color(COLOR_WHITE,COLOR_BLACK,1);
            addstr(" <crosses flabby arms>", gamelog);break;
         case 19: addstr("\"I don't remember doing that.\"", gamelog);
            set_color(COLOR_WHITE,COLOR_BLACK,1);
            addstr(" <looks confused>", gamelog);break;
         case 20: addstr("\"We got a kindergarten dropout over here!\"", gamelog);
            set_color(COLOR_WHITE,COLOR_BLACK,1);
            addstr(" <points and laughs>", gamelog);break;
         case 21: addstr("\"No, I don't want to infect anyone else with herpes.\"", gamelog);
            set_color(COLOR_WHITE,COLOR_BLACK,1);
            addstr(" <sighs>", gamelog);break;
         case 22: addstr("\"Stop staring at my feet, you freak!\"", gamelog);
            set_color(COLOR_WHITE,COLOR_BLACK,1);
            addstr(" <kicks you>", gamelog);break;
         case 23: addstr("\"You're such a loser.\"", gamelog);
            set_color(COLOR_WHITE,COLOR_BLACK,1);
            addstr(" <makes L sign on forehead>", gamelog);break;
         case 24: addstr("\"I'm about to put a voodoo curse on yo ass...\"", gamelog);
            set_color(COLOR_WHITE,COLOR_BLACK,1);
            addstr(" <starts chanting>", gamelog);break;
         case 25: addstr("\"I don't approve of your hi-carb diet.\"", gamelog);
            set_color(COLOR_WHITE,COLOR_BLACK,1);
            addstr(" <starts ranting about nutrition>", gamelog);break;
         case 26: addstr("\"Go back home to play with your G.I. Joe dolls.\"", gamelog);
            set_color(COLOR_WHITE,COLOR_BLACK,1);
            addstr(" <scoffs>", gamelog);break;
         case 27: addstr("\"No, and stop acting like a lost puppy.\"", gamelog);
            set_color(COLOR_WHITE,COLOR_BLACK,1);
            addstr(" <hisses like a cat>", gamelog);break;
         case 28: addstr("\"Jesus...\"", gamelog);
            set_color(COLOR_WHITE,COLOR_BLACK,1);
            addstr(" <turns away>", gamelog);break;
         case 29: addstr("\"I don't believe in astrology, you ignoramus.\"", gamelog);
            set_color(COLOR_WHITE,COLOR_BLACK,1);
            addstr(" <blinds you with science>", gamelog);break;
         case 30: addstr("\"Yes, and it's practically microscopic.\"", gamelog);
            set_color(COLOR_WHITE,COLOR_BLACK,1);
            addstr(" <puts 2 fingers really close together>", gamelog);break;
         case 31: addstr("\"My spouse will be here soon to straighten things out.\"", gamelog);
            set_color(COLOR_WHITE,COLOR_BLACK,1);
            addstr(" <looks for spouse>", gamelog);break;
         case 32: addstr("\"You're not my type.  I like sane people.\"", gamelog);
            set_color(COLOR_WHITE,COLOR_BLACK,1);
            addstr(" <turns away>", gamelog);break;
         case 33: addstr("\"Yes, here you go...\"", gamelog);
            set_color(COLOR_WHITE,COLOR_BLACK,1);
            addstr(" <writes fake directions>", gamelog);break;
         case 34: addstr("\"Gotta go!  Bye!\"", gamelog);
            set_color(COLOR_WHITE,COLOR_BLACK,1);
            addstr(" <squirms away>", gamelog);break;
         case 35: addstr("\"I don't do anal.\"", gamelog);
            set_color(COLOR_WHITE,COLOR_BLACK,1);
            addstr(" <puts hands over butt>", gamelog);break;
         case 36: addstr("\"Hey, look, a UFO!\"", gamelog);
            set_color(COLOR_WHITE,COLOR_BLACK,1);
            addstr(" <ducks away>", gamelog);break;
         case 37: addstr("\"Go home, you're drunk.\"", gamelog);
            set_color(COLOR_WHITE,COLOR_BLACK,1);
            addstr(" <gestures away>", gamelog);break;
         case 38: addstr("\"At least then you'd be liquidated.\"", gamelog);
            set_color(COLOR_WHITE,COLOR_BLACK,1);
            addstr(" <stares intently>", gamelog);break;
         case 39: addstr("\"Laaaame.\"", gamelog);
            set_color(COLOR_WHITE,COLOR_BLACK,1);
            addstr(" <looks bored>", gamelog);break;
         case 40: addstr("\"Eew, no, gross.\"", gamelog);
            set_color(COLOR_WHITE,COLOR_BLACK,1);
            addstr(" <vomits on you>", gamelog);break;
         case 41: addstr("\"Too late for apologies!\"", gamelog);
            set_color(COLOR_WHITE,COLOR_BLACK,1);
            addstr(" <slaps you>", gamelog);break;
         case 42: addstr("\"What an idiot!\"", gamelog);
            set_color(COLOR_WHITE,COLOR_BLACK,1);
            addstr(" <laughs>", gamelog);break;
         case 43: addstr("\"Nothing works, I can't help it.\"", gamelog);
            set_color(COLOR_WHITE,COLOR_BLACK,1);
            addstr(" <starts crying>", gamelog);break;
         case 44: addstr("\"Hahahahaha!\"", gamelog);
            set_color(COLOR_WHITE,COLOR_BLACK,1);
            addstr(" <shakes head>", gamelog);break;
         case 45: addstr("\"Yes, now go away.\"", gamelog);
            set_color(COLOR_WHITE,COLOR_BLACK,1);
            addstr(" <points to exit>", gamelog);break;
         case 46: addstr("\"Touch me and you'll regret it.\"", gamelog);
            set_color(COLOR_WHITE,COLOR_BLACK,1);
            addstr(" <crosses arms>", gamelog);break;
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
      case LAW_CORPORATE:     addstr("\"The corporations are putting you down, dude.\"", gamelog);break;
      case LAW_FREESPEECH:    addstr("\"Better watch what you say.  They've got ears everywhere.\"", gamelog);break;
      case LAW_FLAGBURNING:   addstr("\"The flag is stupid.\"", gamelog);break;
      case LAW_TAX:           addstr("\"Rich people, like, have money, man.\"", gamelog);break;
      case LAW_GUNCONTROL:    addstr("\"People like, think they need lots of guns.\"", gamelog);break;
      case LAW_WOMEN:         addstr("\"We need more women!\"", gamelog);break;
      case LAW_CIVILRIGHTS:   addstr("\"Conservatives are all racists!\"", gamelog);break;
      case LAW_DRUGS:         addstr("\"Dude, the government won't let you do drugs.\"", gamelog);break;
      case LAW_IMMIGRATION:   addstr("\"They're all trying to keep people out of the country.\"", gamelog);break;
      case LAW_ELECTIONS:     addstr("\"The politicians are just tools of the corporations!\"", gamelog);break;
      case LAW_MILITARY:      addstr("\"Patriots are idiots! Give peace a chance!\"", gamelog);break;
      case LAW_TORTURE:       addstr("\"Torture is bad!\"", gamelog);break;
      case LAW_PRISONS:       addstr("\"Prisoners don't have freedom!\"", gamelog);break;
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
      case LAW_CORPORATE:     addstr("\"There are corporations.\"", gamelog);break;
      case LAW_FREESPEECH:    addstr("\"People get mad if you swear a lot in public.\"", gamelog);break;
      case LAW_FLAGBURNING:   addstr("\"The flag code says you shouldn't make it into clothing.\"", gamelog);break;
      case LAW_TAX:           addstr("\"There's still inequality in this country.\"", gamelog);break;
      case LAW_GUNCONTROL:    addstr("\"We need to repeal the second amendment.\"", gamelog);break;
      case LAW_WOMEN:         addstr("\"Some people are sexist.\"", gamelog);break;
      case LAW_CIVILRIGHTS:   addstr("\"I knew some people that were pretty racist.\"", gamelog);break;
      case LAW_DRUGS:         addstr("\"Drugs are expensive.\"", gamelog);break;
      case LAW_IMMIGRATION:   addstr("\"All the immigrants, not everybody likes them.\"", gamelog);break;
      case LAW_ELECTIONS:     addstr("\"Some of these politicians rub me the wrong way.\"", gamelog);break;
      case LAW_MILITARY:      addstr("\"We still have a military.\"", gamelog);break;
      case LAW_TORTURE:       addstr("\"Some conservatives support torture.\"", gamelog);break;
      case LAW_PRISONS:       addstr("\"Prisons still exist.\"", gamelog);break;
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
         addstr("「人々を農場の動物のように飼いならすシステムに反対しただけの", gamelog);move(y++,1);
         addstr("無実の市民の情報が保管され続けている。」", gamelog);
         break;
      case LAW_DEATHPENALTY:
         addstr("「過去10年間で30人以上の人々が処刑されている。」", gamelog);
         break;
      case LAW_NUCLEARPOWER:
         addstr("「核廃棄物は何世紀にも渡って存在し、多くの家族の脅威となる。", gamelog);move(y++,1);
         addstr("もちろんこの付近でも。」", gamelog);
         break;
      case LAW_POLLUTION:
         addstr("「利益のみを追求し他のことは何もしない工場は、環境を汚染させ", gamelog);move(y++,1);
         if (tk.animalgloss==ANIMALGLOSS_ANIMAL) addstr("人間だけでなく動物も傷つけている。」", gamelog);
         else addstr("動物だけでなく人間も傷つけている。」", gamelog);
         break;
      case LAW_LABOR:
         addstr("「労働時間はますます長くなっているのに、給料はますます低くなっている", gamelog);move(y++,1);
         addstr("ことに気づいているか。人々は計画的に奴隷のように働かされている。」", gamelog);
         break;
      case LAW_GAY:
         addstr("「同性愛者はそうでない者と変わりない。だが、この国では未だ安っぽい", gamelog);move(y++,1);
         addstr("エンターテイメントに登場する逸脱者のような扱いを受けている。」", gamelog);
         break;
      case LAW_CORPORATE:
         addstr("\"Corporate executives use giant corporations as a means to become parasites ", gamelog);move(y++,1);
         addstr("that suck wealth out of this country and put it into their pockets.\"", gamelog);
         break;
      case LAW_FREESPEECH:
         addstr("\"Protests and demonstrations are regularly and often brutally suppressed in ", gamelog);move(y++,1);
         addstr("this country.  People have to watch what they write -- even what they read.\"", gamelog);
         break;
      case LAW_FLAGBURNING:
         addstr("\"Burning a piece of cloth is actually stigmatized in this country. ", gamelog);move(y++,1);
         addstr("You can love freedom and still hate what our government stands for.\"", gamelog);
         break;
      case LAW_TAX:
         addstr("\"The tax code has been designed to perpetuate an unjust class ", gamelog);move(y++,1);
         addstr("structure that is keeping you oppressed.\"", gamelog);
         break;
      case LAW_GUNCONTROL:
         addstr("\"We live in such a backwards country right now that people think it's ", gamelog);move(y++,1);
         addstr("a right to walk around with the power to murder at any moment.\"", gamelog);
         break;
      case LAW_WOMEN:
         addstr("\"Sexism is still pervasive, in subtle ways, and women make much less ", gamelog);move(y++,1);
         addstr("than they deserve for their labor.\"", gamelog);
         break;
      case LAW_CIVILRIGHTS:
         addstr("\"Despite our progress, this society is still strangled by its continuing ", gamelog);move(y++,1);
         addstr("legacy of racial discrimination and inequality.\"", gamelog);
         break;
      case LAW_DRUGS:
         addstr("\"The government's drug policy is a mess.  We need to stop filling ", gamelog);move(y++,1);
         addstr("prisons with drug users, and only intervene when people really need help.\"", gamelog);
         break;
      case LAW_IMMIGRATION:
         addstr("\"Millions of people are doing jobs most folks don't even want, and ", gamelog);move(y++,1);
         addstr("saving their families from poverty, but we just try to kick them out.\"", gamelog);
         break;
      case LAW_ELECTIONS:
         addstr("\"Political favors are bought and sold for campaign contributions, ", gamelog);move(y++,1);
         addstr("and the voting system enforces two party dominance.\"", gamelog);
         break;
      case LAW_MILITARY:
         addstr("\"Take a breath and think about the world we live in, that we're spending ", gamelog);move(y++,1);
         addstr("hundreds of billions on new ways to kill people.  This has to stop!\"", gamelog);
         break;
      case LAW_TORTURE:
         addstr("\"In the name of the war on terror, we've sacrificed our soul by letting ", gamelog);move(y++,1);
         addstr("the government torture and abuse human beings on our behalf.\"", gamelog);
         break;
      case LAW_PRISONS:
         addstr("\"The prison system doesn't help criminals by providing rehabilitation, so ", gamelog);move(y++,1);
         addstr("when they get released, they mostly become criminals again.\"", gamelog);
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
         case 8: addstr("「タバコを持ってないか? 」", gamelog);
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
      addstr("と今晩会う約束をした。", gamelog);
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
            case LAW_CORPORATE:     addstr("\"Corporations are part of capitalism.\"", gamelog);break;
            case LAW_FREESPEECH:    addstr("\"Don't be offensive and you'll be fine.\"", gamelog);break;
            case LAW_FLAGBURNING:   addstr("\"That flag is the sacred symbol of our country.\"", gamelog);break;
            case LAW_TAX:           addstr("\"I want to pay lower taxes.\"", gamelog);break;
            case LAW_GUNCONTROL:    addstr("\"Without guns, we're slaves to the Government.\"", gamelog);break;
            case LAW_WOMEN:         addstr("\"Why don't you go burn a bra or something?\"", gamelog);break;
            case LAW_CIVILRIGHTS:   addstr("\"Reverse discrimination is still discrimination.\"", gamelog);break;
            case LAW_DRUGS:         addstr("\"Drugs are a terrible influence on society.\"", gamelog);break;
            case LAW_IMMIGRATION:   addstr("\"Immigration undermines our economy and culture.\"", gamelog);break;
            case LAW_ELECTIONS:     addstr("\"Unregulated campaigning is a matter of free speech.\"", gamelog);break;
            case LAW_MILITARY:      addstr("\"The military protects us and enables our way of life.\"", gamelog);break;
            case LAW_TORTURE:       addstr("\"The terrorists would do worse to us.\"", gamelog);break;
            case LAW_PRISONS:       addstr("\"Criminals deserve what they get in prison.\"", gamelog);break;
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
                              addstr("「人質を解放しろ。誰も傷つけたくない。」", gamelog);
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
               addstr("A - 人質を殺害する");
            else
               addstr("A - 人質を殺害する");
            move(12,1);
            if(hostages>1)
               addstr("B - 条件を受け入れ人質を解放する");
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
                  if(hostages>1) addstr("\"Back off and we'll let the hostages go.\"", gamelog);
                  else addstr("\"Back off and the hostage goes free.\"", gamelog);
                  break;
               case 1:addstr("\"Freedom for freedom, understand?\"", gamelog);break;
               case 2:addstr("\"Let me go in peace, okay?\"", gamelog);break;
               case 3:addstr("\"Let's make a trade, then.\"", gamelog);break;
               case 4:addstr("\"I just want out of here, yeah?\"", gamelog);break;
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
                  case 0:addstr("\"Do I look like a loving person?\"", gamelog);break;
                  case 1:addstr("\"You don't take a hint, do you?\"", gamelog);break;
                  case 2:addstr("\"I'm doing the world a favor.\"", gamelog);break;
                  case 3:addstr("\"That's so pathetic...\"", gamelog);break;
                  case 4:addstr("\"It's a deal.\"", gamelog);break;
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
                  case 0:addstr("\"Right. Let's do it.\"", gamelog);break;
                  case 1:addstr("\"No further conditions.\"", gamelog);break;
                  case 2:addstr("\"Let them go, and we're done.\"", gamelog);break;
                  case 3:addstr("\"No tricks, okay?\"", gamelog);break;
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
                  if(hostages>1)addstr("The squad releases all hostages in the trade.", gamelog);
                  else addstr("The squad releases the hostage in the trade.", gamelog);
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
         addstr(" isn't interested in your pathetic threats.", gamelog);
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
                     addstr("「脱出」のネッド・ビーティのように金切り声を", gamelog);
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
         addstr("敵は騙され解散した。", gamelog);

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
         pitch = "\"I love dogs more than people.\"";
         response = "\"A human after my own heart, in more ways than one.\"";
         break;
      case 1:
         pitch = "\"Dogs are the future of humanity.\"";
         response = "\"I don't see it, but I'll hear you out.\"";
         break;
      case 2:
         pitch = "\"Power to the canines!\"";
         response = "\"Down with the feline establishment!\"";
         break;
      case 3:
         pitch = "\"We need to recruit more dogs.\"";
         response = "\"Oh yeah? I'm a dog. What do you represent?\"";
         break;
      case 4:
         pitch = "\"Wanna join the LCS?\"";
         response = "\"Do you have a good veteranary plan?\"";
         break;
      case 5:
         pitch = "\"Want me to untie you?\"";
         response = "\"Yes, please! This collar is painful!\"";
         break;
      case 6:
         pitch = "\"You deserve better than this.\"";
         response = "\"Finally, a human that understands.\"";
         break;
      case 7:
         pitch = "\"Dogs are the best anything ever.\"";
         response = "\"Heheheh, you're funny. Okay, I won't rat you out.\"";
         break;
      case 8:
         pitch = "\"Conservatives kick dogs!\"";
         response = "\"That IS disturbing. What can I do?\"";
         break;
      case 9:
         pitch = "\"All we are saying is give fleas a chance.\"";
         response = "\"We'll fight the fleas until our dying itch.\"";
         break;
      case 10:
      default:
         pitch = "\"Dogs are better than humans.\"";
         response = "\"You're pandering, but I love it.\"";
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
         pitch = "\"I love diversity in all its forms.\"";
         response = "\"Your tolerance is impressive, human!\"";
         break;
      case 1:
         pitch = "\"Your kind are the future of humanity.\"";
         response = "\"Your recognition of our superiority is wise.\"";
         break;
      case 2:
         pitch = "\"Power to the genetic monsters!\"";
         response = "\"Down with the human establishment!\"";
         break;
      case 3:
         pitch = "\"We need to recruit more genetic monsters.\"";
         response = "\"For what purpose do you seek our aid?\"";
         break;
      case 4:
         pitch = "\"Wanna join the LCS?\"";
         response = "\"Maybe. Can we scare small children?\"";
         break;
      case 5:
         pitch = "\"You're free! Join us to liberate more!\"";
         response = "\"Is this what compassion is?\"";
         break;
      case 6:
         pitch = "\"You deserve better than this.\"";
         response = "\"No beast deserves to be an experiment!\"";
         break;
      case 7:
         pitch = "\"You are the best anything ever.\"";
         response = "\"It's okay blokes, this one is friendly.\"";
         break;
      case 8:
         pitch = "\"We should flay geneticists together!\"";
         response = "\"My favorite future hobby!\"";
         break;
      case 9:
         pitch = "\"All we are saying is give peace a chance.\"";
         response = "\"Will humans ever let us have peace?\"";
         break;
      case 10:
      default:
         pitch = "\"Monsters are better than humans.\"";
         response = "\"You're a clever one.\"";
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
