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

// Note: this file is encoded in the PC-8 / Code Page 437 / OEM-US character set
// (The same character set used by Liberal Crime Squad when it is running)
// Certain special characters won't display correctly unless your text editor is
// set to use that character set, such as this e with an accent: é

// In Windows Notepad with the Terminal font, OEM/DOS encoding it should work fine.
// You can set this in Notepad by going to Format->Font and choosing the Terminal font,
// then choosing OEM/DOS in the Script dropdown box.

// In Notepad++ go to the Encoding menu, Character sets, Western European, OEM-US... easy!

// In Code::Blocks's editor go to Settings->Editor->the Other Settings tab and
// then pick WINDOWS-437 from the dropdown box and then choose the radio button
// to make this the default encoding and disable auto-detection of the encoding.
// Then close the file and reopen it (since Code::Blocks detects the encoding
// when it opens the file and it can't be changed after that; what we changed was
// how it detects encoding for files it opens in the future, not files already open).

// In Microsoft Visual C++, right-click the file in the Solution Explorer,
// select "Open With...", choose "C++ Source Code Editor (with encoding)",
// then choose "OEM United States - Codepage 437".

// In MS-DOS Editor (included with Windows as EDIT.COM in your system32 directory),
// the codepage will be correct already since it's running in a console window just
// like Liberal Crime Squad. Well OK, the encoding might be wrong, but then it's wrong
// in Liberal Crime Squad TOO, and to fix it, go to Control Panel, Regional and Language Settings,
// Advanced tab, and choose English (United States) from the dropdown box as the encoding
// for non-Unicode applications, then press OK.

// If you have a Linux or other UNIX-based system you are obviously smart enough
// to figure out for yourself how to open a file in OEM-US PC-8 codepage 437 in
// your favorite text editor. If you're on Mac OS X, well that's UNIX-based, figure
// it out for yourself.

#include <externs.h>

void doActivitySolicitDonations(vector<Creature *> &solicit, char &clearformess);
void doActivitySellTshirts(vector<Creature *> &tshirts, char &clearformess);
void doActivitySellArt(vector<Creature *> &art, char &clearformess);
void doActivitySellMusic(vector<Creature *> &music, char &clearformess);
void doActivitySellBrownies(vector<Creature *> &brownies, char &clearformess);
void doActivityHacking(vector<Creature *> &hack, char &clearformess);
void doActivityGraffiti(vector<Creature *> &graffiti, char &clearformess);
void doActivityProstitution(vector<Creature *> &prostitutes, char &clearformess);
void doActivityLearn(vector<Creature *> &students, char &clearformess);
void doActivityTrouble(vector<Creature *> &trouble, char &clearformess);
void doActivityTeach(vector<Creature *> &teachers, char &clearformess);
void doActivityBury(vector<Creature *> &bury, char &clearformess);


void adjustblogpower(int &power)
{
   if(power<20)
   {
      switch(LCSrandom(20))
      {
      case 0:addstr("a sub-Liberal");break;
      case 1:addstr("a really bad");break;
      case 2:addstr("a pathetic");break;
      case 3:addstr("a dreadful");break;
      case 4:addstr("a god-awful");break;
      case 5:addstr("a Conservative");break;
      case 6:addstr("a heinous");break;
      case 7:addstr("an embarrassing");break;
      case 8:addstr("a shameful");break;
      case 9:addstr("a counter-productive");break;
      case 10:addstr("a sad");break;
      case 11:addstr("a vapid");break;
      case 12:addstr("a weak");break;
      case 13:addstr("a brainless");break;
      case 14:addstr("a repellant");break;
      case 15:addstr("a nonsensical");break;
      case 16:addstr("a ludicrous");break;
      case 17:addstr("a half-baked");break;
      case 18:addstr("a laughable");break;
      case 19:addstr("an insane");break;
      }
      power = -signed(LCSrandom(2));
   }
   else if(power<35)
   {
      //switch(LCSrandom(1))
      //{
      //case 0:addstr("a fair");break;
      //case 1:addstr("a mainstream");break;
      //case 2:addstr("a mediocre");break;
      //case 3:addstr("a middling");break;
      //case 4:addstr("a passable");break;
      //case 5:addstr("a regular");break;
      //case 6:addstr("a normal");break;
      //case 7:addstr("a standard");break;
      //case 9:addstr("a reasonable");break;
      //case 0:addstr("a typical");break;
      //case 11:addstr("a vanilla");break;
      //case 12:addstr("a basic");break;
      //case 13:addstr("a plain");break;
      //case 14:addstr("a simple");break;
      /*case 0:*/addstr("a standard");//break;
      //case 16:addstr("an everyday");break;
      //case 17:addstr("a stock");break;
      //case 18:addstr("a stereotypical");break;
      //case 19:addstr("an okay");break;
      //case 8:addstr("a respectable");break;
      //}
      power = 1;
   }
   else if(power<50)
   {
      switch(LCSrandom(11))
      {
      //case 0:addstr("a solid");break;
      case 0:addstr("a good");break;
      //case 2:addstr("an intelligent");break;
      case 1:addstr("a satisfying");break;
      //case 4:addstr("an impressive");break;
      case 2:addstr("a sound");break;
      //case 6:addstr("a splendid");break;
      case 3:addstr("a competent");break;
      case 4:addstr("a clever");break;
      //case 10:addstr("a skillful");break;
      //case 11:addstr("a talented");break;
      case 5:addstr("a persuasive");break;
      case 6:addstr("a thorough");break;
      case 7:addstr("a bold");break;
      //case 15:addstr("a clever");break;
      case 8:addstr("a fresh");break;
      case 9:addstr("a pointed");break;
      case 10:addstr("a sassy");break;
      //case 19:addstr("a sharp");break;
      case 11:addstr("a Liberal");break;
      }
      power = 2;
   }
   else
   {
      switch(LCSrandom(10))
      {
      case 0:addstr("a great");break;
      //case 1:addstr("a masterful");break;
      //case 2:addstr("a penetrating");break;
      //case 3:addstr("a profound");break;
      case 1:addstr("a top-quality");break;
      //case 5:addstr("a very sound");break;
      case 2:addstr("an excellent");break;
      //case 7:addstr("a competent");break;
      case 3:addstr("a brilliant");break;
      case 4:addstr("a powerful");break;
      //case 10:addstr("a slick");break;
      //case 11:addstr("a winning");break;
      case 5:addstr("an inspiring");break;
      case 6:addstr("a touching");break;
      case 7:addstr("an eloquent");break;
      case 8:addstr("a forceful");break;
      case 9:addstr("a compelling");break;
      //case 17:addstr("an impelling");break;
      //case 18:addstr("a smooth");break;
      case 10:addstr("an Elite Liberal");break;
      }
      power = 3;
   }
}


/* armor repair */
void repairarmor(Creature &cr,char &clearformess)
{
   Armor *armor=NULL;
   Item *pile=NULL;
   vector<Item *> *pilelist=NULL;
   int pileindex = 0;

   // Clean yourself up first
   if(cr.get_armor().is_bloody() || cr.get_armor().is_damaged())
      armor=&cr.get_armor();
   else if(cr.squadid!=-1)
   {
      int sq=getsquad(cr.squadid);
      for(int l=0;l<len(squad[sq]->loot);l++)
         if(squad[sq]->loot[l]->is_armor())
         {
            Armor* a = static_cast<Armor*>(squad[sq]->loot[l]); //cast -XML
            if (a->is_bloody() || a->is_damaged())
            {
               armor=a;
               pile=squad[sq]->loot[l];
               pileindex=l;
               pilelist=&squad[sq]->loot;
               break;
            }
         }
   }
   // Multiple passes, to find the best item to work on
   bool dothis = false;
   for (int passnum=0; passnum < 3 && !dothis; passnum++)
      if(armor==NULL&&cr.location!=-1)
         for(int l=0;l<len(location[cr.location]->loot);l++)
            if(location[cr.location]->loot[l]->is_armor())
            {
               Armor* a = static_cast<Armor*>(location[cr.location]->loot[l]);//cast -XML
               switch (passnum)
               {
                  case 0: // Guaranteed to accomplish something
                     dothis = (a->is_bloody() && a->is_damaged());
                     break;
                  case 1: // Find something to clean if low skill, repair if high
                     dothis =  (a->is_bloody() && armor_makedifficulty(*a,&cr)>4)
                            || (a->is_damaged() && armor_makedifficulty(*a,&cr)<=4);
                     break;
                  case 2: // Anything that needs work
                     dothis = (a->is_bloody() || a->is_damaged());
                     break;
               }
               if(dothis)
               {
                  armor=a;
                  pile=location[cr.location]->loot[l];
                  pileindex=l;
                  pilelist=&location[cr.location]->loot;
                  break;
               }
            }

   if(clearformess) erase();
   else makedelimiter();

   if(armor==NULL)
   {
      move(8,1);
      addstr(cr.name, gamelog);
      switch (LCSrandom(4))
      {
         case 0: addstr("はアジトを掃除した。", gamelog); break;
         case 1: addstr("はアーマークローゼットを整理した。", gamelog); break;
         case 2: addstr("は台所を片付けた。", gamelog); break;
         case 3:
            addstr("は手芸雑誌を読みふけった。", gamelog);
            cr.train(SKILL_TAILORING,1);
            break;
      }
      gamelog.nextMessage();

      getkey();
   }
   else
   {
      string armorname = armor->get_name();// Get name before we maybe destroy it
      bool repairfailed=false;
      bool qualityReduction=!LCSrandom(10);
      bool armorDestroyed=!armor->decrease_quality(0);

      if(armor->is_damaged())
      {
         long dif=armor_makedifficulty(*armor,&cr);
         dif>>=(armor->get_quality()-1);  // it is easy to patch up rags
         cr.train(SKILL_TAILORING,dif/2+1);

         if(LCSrandom(1+dif/2)) repairfailed=true;
      }else{
         repairfailed=true;
      }
      if (armorDestroyed)
         repairfailed = false;  // Its dead, Jim; stop trying to fix it
      if (repairfailed)
         qualityReduction = false; // Low skill repairers shredding your shirts seem too harsh

      set_color(COLOR_WHITE,COLOR_BLACK,1);
      move(8,1);

      std::string result = "";
      result += cr.name;
      result += "は";

      if (pile)
      {
         result += armor->aan();
      }
      else
         result += cr.hisher();

      if (armorDestroyed)
         result += "壊れた";

      result += armorname + "を";

      if (armorDestroyed)
      {
         set_color(COLOR_RED,COLOR_BLACK,1);
         result += "廃棄した";
      }else if(repairfailed && armor->is_bloody())
      {
         set_color(COLOR_CYAN,COLOR_BLACK,1);
         result += "洗濯した";
      }else if(repairfailed)
      {
         set_color(COLOR_WHITE,COLOR_BLACK,1);
         result += "修繕しようとした";
      }else
      {
         if(!qualityReduction)
         {
            set_color(COLOR_GREEN,COLOR_BLACK,1);
            result += "修繕した";
         }else
         {
            armorDestroyed = !armor->decrease_quality(1);
            if(armorDestroyed)
            {
               set_color(COLOR_RED,COLOR_BLACK,1);
               result += "直せないことがわかった";
            }else
            {
               set_color(COLOR_YELLOW,COLOR_BLACK,1);
               result += "直すのが困難だとわかった";
            }
         }
      }

      result += "。";

      addstr(result,gamelog);
      gamelog.nextMessage();

      if(pile)
      {
         if(pile->get_number()>1)
         {
            Item *newpile=pile->split(pile->get_number()-1);
            pilelist->push_back(newpile);
         }
      }

      armor->set_bloody(false);
      if(!repairfailed)
      {
         armor->set_damaged(false);
      }
      if (armorDestroyed)
      {
         if (!pile) // repairer was wearing it
         {
            cr.strip(NULL);
         }
         else // scrap from stockpile
         {
            delete_and_remove(*pilelist, pileindex);
         }
      }

      getkey();
   }
}



/* armor manufacture */
void makearmor(Creature &cr,char &clearformess)
{
   int at=cr.activity.arg;

   int cost=armortype[at]->get_make_price();
   int hcost=(cost>>1)+1;
   int dif=armor_makedifficulty(*armortype[at],&cr);

   if(ledger.get_funds()<hcost)
   {
      if(clearformess) erase();
      else makedelimiter();

      set_color(COLOR_WHITE,COLOR_BLACK,1);
      move(8,1);
      addstr(cr.name, gamelog);
      addstr("には服を作るだけの金がない。", gamelog);
      gamelog.nextMessage();

      getkey();
      return;
   }
   else
   {
      char foundcloth=0;

      if(cr.squadid!=-1)
      {
         int sq=getsquad(cr.squadid);
         for(int l=0;l<len(squad[sq]->loot);l++)
            if(squad[sq]->loot[l]->is_loot()&&
               static_cast<Loot*>(squad[sq]->loot[l])->is_cloth()) //cast -XML
            {
               if(squad[sq]->loot[l]->get_number()==1)
                  delete_and_remove(squad[sq]->loot,l);
               else squad[sq]->loot[l]->decrease_number(1);
               foundcloth=1;
               break;
            }
      }
      if(!foundcloth) for(int l=0;l<len(location[cr.location]->loot);l++)
         if(location[cr.location]->loot[l]->is_loot()&&
            static_cast<Loot*>(location[cr.location]->loot[l])->is_cloth()) //cast -XML
         {
            if(location[cr.location]->loot[l]->get_number()==1)
               delete_and_remove(location[cr.location]->loot,l);
            else location[cr.location]->loot[l]->decrease_number(1);
            foundcloth=1;
            break;
         }

      if(!foundcloth&&ledger.get_funds()<cost)
      {
         if(clearformess) erase();
         else makedelimiter();

         set_color(COLOR_WHITE,COLOR_BLACK,1);
         move(8,1);
         addstr(cr.name, gamelog);
         addstr("は買うよりも安く服を作れないとわかった。", gamelog);
         gamelog.nextMessage();

         getkey();
      }
      else
      {
         if(foundcloth) ledger.subtract_funds(hcost,EXPENSE_MANUFACTURE);
         else ledger.subtract_funds(cost,EXPENSE_MANUFACTURE);

         cr.train(SKILL_TAILORING,dif*2+1);

         int quality = 1;
         while (LCSrandom(10)<dif && quality <= armortype[at]->get_quality_levels())
            quality++;

         if(clearformess) erase();
         else makedelimiter();

         Item *it=new Armor(*armortype[at],quality);

         set_color(COLOR_WHITE,COLOR_BLACK,1);
         move(8,1);
         addstr(cr.name, gamelog);
         if(quality <= ((Armor*)it)->get_quality_levels() )
         {
            addstr("は", gamelog);
            switch(quality)
            {
               case 1:addstr("1級品", gamelog);break;
               case 2:addstr("2級品", gamelog);break;
               case 3:addstr("3級品", gamelog);break;
               case 4:addstr("4級品", gamelog);break;
               default:addstr(quality,gamelog);addstr("級品", gamelog); break;
            }
            location[cr.location]->loot.push_back(it);
            addstr("の", gamelog);
            addstr(armortype[at]->get_name(), gamelog);
            addstr("を作った。", gamelog);
         }
         else
         {
            addstr("材料を無駄にするだけで", gamelog);
            addstr(armortype[at]->get_name(), gamelog);
            addstr("を作れなかった。", gamelog);
         }
         gamelog.nextMessage();

         getkey();
      }
   }
}



/* search for polls */
void survey(Creature *cr)
{
   music.play(MUSIC_ELECTIONS);
   static const char SURVEY_PAGE_SIZE=14;

   int v,creatureskill=cr->skill_roll(SKILL_COMPUTERS);
   int misschance=30-creatureskill,noise;
   if(misschance<5)misschance=5;
   if(creatureskill<1) noise=18+LCSrandom(3); // 18 to 20
   else if(creatureskill<2) noise=16+LCSrandom(2); // 16 or 17
   else if(creatureskill<3) noise=14+LCSrandom(2); // 14 or 15
   else if(creatureskill<4) noise=12+LCSrandom(2); // 12 or 13
   else if(creatureskill<5) noise=10+LCSrandom(2); // 10 or 11
   else if(creatureskill<6) noise=8+LCSrandom(2); // 8 or 9
   else if(creatureskill<7) noise=7;
   else if(creatureskill<9) noise=6;
   else if(creatureskill<11) noise=5;
   else if(creatureskill<14) noise=4;
   else if(creatureskill<18) noise=3;
   else noise=2;

   int survey[VIEWNUM];

   int maxview=-1;
   for(v=0;v<VIEWNUM;v++)
   {
      survey[v]=attitude[v];
      if(v!=VIEW_LIBERALCRIMESQUAD&&v!=VIEW_LIBERALCRIMESQUADPOS/*&&v!=VIEW_POLITICALVIOLENCE*/)
      {
         if(maxview!=-1) { if(public_interest[v]>public_interest[maxview]) maxview=v; }
         else { if(public_interest[v]>0) maxview=v; }
      }

      //MAKE SURVEY ACCURATE IF DEBUGGING
      #ifndef SHOWMECHANICS
      do { survey[v]+=LCSrandom(noise*2+1)-noise; } while(!LCSrandom(20));
      #endif

      if(survey[v]<0) survey[v]=0;
      if(survey[v]>100) survey[v]=100;

      #ifndef SHOWMECHANICS
      if(LCSrandom(public_interest[v]+100)<int(misschance)) survey[v]=-1;
      #endif

      if(v==VIEW_LIBERALCRIMESQUAD&&attitude[v]==0) survey[v]=-1;
      if(v==VIEW_LIBERALCRIMESQUADPOS&&survey[VIEW_LIBERALCRIMESQUAD]<=0) survey[v]=-1;
   }

   erase();

   //TODO: Sort out the gamelog for this.
   set_color(COLOR_WHITE,COLOR_BLACK,1);
   move(0,0);
   addstr("現在の世論");

   int y=8,approval=presidentapproval();
   move(2,0);
   set_color(COLOR_WHITE,COLOR_BLACK,0);
   addstr(approval/10+(LCSrandom(noise*2+1)-noise), gamelog);
   addstr("%の人が");
   set_alignment_color(exec[EXEC_PRESIDENT],true);
   addstr(execname[EXEC_PRESIDENT]);
   set_color(COLOR_WHITE,COLOR_BLACK,0);
   addstr("大統領に良い印象を持っている。");

   //Top excitement issue
   if(maxview!=-1)
   {
      move(4,0);
      addstr("多くの人が");
      switch(maxview)
      {
         case VIEW_GAY:
            if(attitude[VIEW_GAY]>50) addstr("同性愛者の権利をどう守るか");
            else addstr("伝統的な家族観をどう守るか");
            break;
         case VIEW_DEATHPENALTY:
            if(attitude[VIEW_DEATHPENALTY]>50) addstr("不当な死刑");
            else
            {
               if(law[LAW_DEATHPENALTY]==2) addstr("死刑制度の復活");
               else addstr("死刑制度の維持");
            }
            break;
         case VIEW_TAXES:
            if(attitude[VIEW_TAXES]>50) addstr("不公正な税制度");
            else addstr("重すぎる税負担");
            break;
         case VIEW_NUCLEARPOWER:
            if(attitude[VIEW_NUCLEARPOWER]>50) addstr("原子力の危険性");
            else
            {
               if(law[LAW_NUCLEARPOWER]==2) addstr("原子力利用の再開");
               else  addstr("原子力利用の危機");
            }
            break;
         case VIEW_ANIMALRESEARCH:
            if(attitude[VIEW_ANIMALRESEARCH]>50) addstr("動物実験の残酷さ");
            else addstr("過度な動物実験の制限");
            break;
         case VIEW_POLICEBEHAVIOR:
            if(attitude[VIEW_POLICEBEHAVIOR]>50) addstr("警察による暴力の防止");
            else addstr("警察の強化");
            break;
         case VIEW_INTELLIGENCE:
            if(attitude[VIEW_INTELLIGENCE]>50) addstr("市民の自由とプライバシー保護");
            else addstr("安全保障と諜報機関の重要性");
            break;
         case VIEW_FREESPEECH:
            if(attitude[VIEW_FREESPEECH]>50) addstr("言論の自由をどう守るか");
            else addstr("どうやってヘイトスピーチを止めさせるか");
            break;
         case VIEW_GENETICS:
            if(attitude[VIEW_GENETICS]>50) addstr("遺伝子工学の危険性");
            else addstr("過度な遺伝子研究の制限");
            break;
         case VIEW_JUSTICES:
            if(attitude[VIEW_JUSTICES]>50) addstr("リベラル派判事の必要性");
            else addstr("保守派判事の必要性");
            break;
         case VIEW_SWEATSHOPS:
            if(attitude[VIEW_SWEATSHOPS]>50) addstr("労働者の権利の危機");
            else addstr("労働組合の不当な要求");
            break;
         case VIEW_POLLUTION:
            if(attitude[VIEW_POLLUTION]>50) addstr("環境の危機");
            else addstr("過度な公害規制");
            break;
         case VIEW_CORPORATECULTURE:
            if(attitude[VIEW_CORPORATECULTURE]>50) addstr("企業腐敗");
            else addstr("過度な企業への規制");
            break;
         case VIEW_CEOSALARY:
            if(attitude[VIEW_CEOSALARY]>50) addstr("過度に不公正な賃金");
            else addstr("社会主義的な報酬の制限");
            break;
         case VIEW_PRISONS:
            if(attitude[VIEW_PRISONS]>50) addstr("囚人への虐待の防止");
            else addstr("囚人の更生");
            break;
         //case VIEW_POLITICALVIOLENCE:
         //   if(attitude[VIEW_POLITICALVIOLENCE]>50) addstr("taking strong action");
         //   else addstr("political terrorism");
         //   break;
         case VIEW_IMMIGRATION:
            if(attitude[VIEW_IMMIGRATION]>50) addstr("移民の権利");
            else
            {
               if(law[LAW_IMMIGRATION]>=1) addstr("管理されていない移民");
               else addstr("不法移民");
            }
            break;
         case VIEW_DRUGS:
            if(attitude[VIEW_DRUGS]>50) addstr("薬物の権利");
            else addstr("薬物の規制");
            break;
         case VIEW_WOMEN:
            if(attitude[VIEW_WOMEN]>50) addstr("男女平等");
            else addstr("女性");
            break;
         case VIEW_CIVILRIGHTS:
            if(attitude[VIEW_CIVILRIGHTS]>50) addstr("市民の権利");
            else addstr("問題を引き起こすマイノリティ");
            break;
         case VIEW_GUNCONTROL:
            if(attitude[VIEW_GUNCONTROL]>50) addstr("銃犯罪");
            else addstr("修正第2条の堅持");
            break;
         case VIEW_MILITARY:
            if(attitude[VIEW_MILITARY]>50) addstr("軍事的帝国主義");
            else addstr("国防");
            break;
         case VIEW_LIBERALCRIMESQUAD:
         case VIEW_LIBERALCRIMESQUADPOS:
            if(attitude[VIEW_LIBERALCRIMESQUAD]<50) addstr("政治活動家");
            else
            {
               if(attitude[VIEW_LIBERALCRIMESQUADPOS]>50) addstr("リベラル・クライム・スコード");
               else addstr("LCSのテロリスト");
            }
            break;
         case VIEW_CONSERVATIVECRIMESQUAD:
            if(attitude[VIEW_CONSERVATIVECRIMESQUAD]<50) addstr("コンサバ・クライム・スコード");
            else addstr("CCSのテロリスト");
            break;
         case VIEW_TORTURE:
            if(attitude[VIEW_TORTURE]>50)addstr("拷問の禁止");
            else addstr("取調べの強化");
            break;
         case VIEW_AMRADIO:
         case VIEW_CABLENEWS:
            if(attitude[VIEW_AMRADIO]+attitude[VIEW_CABLENEWS]>100) addstr("保守メディアの偏向");
            else addstr("リベラルメディアの偏向");
            break;
      }
      addstr("に関心を持っている。");
   }
   else
   {
      move(4,0);
      addstr("ほとんどの人が政治に無関心だ。");
   }

   //Header for issue box
   move(6,0);
   addstr("更なる調査結果:");
   move(7,0);
   addstr("XX%  議題 ------------------------------------------------- 関心度");

   //Footer
   set_color(COLOR_WHITE,COLOR_BLACK,0);
   move(23,0);
   addstr("結果には±");
   addstr(noise);
   addstr("%程度の誤差がある。");
   move(24,0);
   addstr("Enter - 了解");
   move(24,40);
   addprevpagestr();
   addstr("    ");
   addnextpagestr();

   int page=0;
   const int maxpage=VIEWNUM/SURVEY_PAGE_SIZE;
   while(true)
   {
      //Keep pages within bounds
      if(page<0) page=maxpage;
      if(page>maxpage) page=0;
      //Start from the top
      y=8;
      //Draw each line
      for(v=page*SURVEY_PAGE_SIZE;v<(page+1)*SURVEY_PAGE_SIZE;v++,y++)
      {
         if(v>=VIEWNUM || (v==VIEW_CONSERVATIVECRIMESQUAD && (endgamestate>=ENDGAME_CCS_DEFEATED||newscherrybusted<2)))
         {
            move(y,0);
            addstr("                                                                                ");
            continue;
         }
         set_color(COLOR_WHITE,COLOR_BLACK,0);
         move(y,4);
         addstr("........................................................");
         if(noise>=7||survey[v]==-1) addstr("不明     ");
         else if(noise>=4)
         {
            if(public_interest[v]>50) addstr("高       ");
            else addstr("低       ");
         }
         else
         {
            if(public_interest[v]>100) addstr("非常に高 ");
            else if(public_interest[v]>50) addstr("高       ");
            else if(public_interest[v]>10) addstr("中       ");
            else if(public_interest[v]) addstr("低       ");
            else addstr("無       ");
         }

         if(survey[v]==-1)set_color(COLOR_BLACK,COLOR_BLACK,1);
         else if(survey[v]<10)set_color(COLOR_RED,COLOR_BLACK,1);
         else if(survey[v]<30)set_color(COLOR_MAGENTA,COLOR_BLACK,1);
         else if(survey[v]<50)set_color(COLOR_YELLOW,COLOR_BLACK,1);
         else if(survey[v]<70)set_color(COLOR_BLUE,COLOR_BLACK,1);
         else if(survey[v]<90)set_color(COLOR_CYAN,COLOR_BLACK,1);
         else set_color(COLOR_GREEN,COLOR_BLACK,1);

         move(y,0);
         if(survey[v]==-1) addstr("??");
         else
         {
            if(survey[v]<10)addchar('0');
            addstr(survey[v]);
         }
         addstr("%");

         switch(v)
         {
         case VIEW_GAY: addstr("が同性愛者の対等な権利を歓迎している"); break;
         case VIEW_DEATHPENALTY: addstr("が死刑制度に反対している"); break;
         case VIEW_TAXES: addstr("が減税に抗議している"); break;
         case VIEW_NUCLEARPOWER: addstr("が原子力に不安を感じている"); break;
         case VIEW_ANIMALRESEARCH: addstr("が動物実験を非難している"); break;
         case VIEW_POLICEBEHAVIOR: addstr("が警察の暴力を批判している"); break;
         case VIEW_TORTURE: addstr("が拷問が行われていないかの監視の強化を望んでいる"); break;
         case VIEW_INTELLIGENCE: addstr("が情報機関がプライバシーを侵害していると考えている"); break;
         case VIEW_FREESPEECH: addstr("が無制限の言論の自由を信用している"); break;
         case VIEW_GENETICS: addstr("が遺伝子組み換え食品を避けている"); break;
         case VIEW_JUSTICES: addstr("が司法は自由主義的であるべきと考えている"); break;
         case VIEW_SWEATSHOPS: addstr("が労働者を搾取する企業に抗議している"); break;
         case VIEW_POLLUTION: addstr("が工場は低公害であるべきと考えている"); break;
         case VIEW_CORPORATECULTURE: addstr("が企業の不正にうんざりしている"); break;
         case VIEW_CEOSALARY: addstr("がCEOの報酬が高すぎると感じている"); break;
         case VIEW_WOMEN: addstr("が男女平等の推進を求めている"); break;
         case VIEW_CIVILRIGHTS: addstr("が人種の平等のための更なる取り組みが必要だと感じている"); break;
         case VIEW_GUNCONTROL: addstr("が銃犯罪を憂慮している"); break;
         case VIEW_DRUGS: if(law[LAW_DRUGS]>=1) addstr("がマリファナ合法化の維持を支持している");
                          else addstr("がマリファナの合法化を支持している"); break;
         case VIEW_IMMIGRATION: if(law[LAW_IMMIGRATION]>=1) addstr("が入管法を問題視している");
                                else addstr("が不法移民への恩赦を望んでいる"); break;
         case VIEW_MILITARY: addstr("が軍事支出の増加に反対している"); break;
         case VIEW_LIBERALCRIMESQUAD: addstr("がリベラル・クライム・スコードに良い印象を持っている"); break;
         case VIEW_LIBERALCRIMESQUADPOS: addstr("がリベラル・クライム・スコードに高い関心を持っている"); break;
         case VIEW_CONSERVATIVECRIMESQUAD: addstr("がコンサバ・クライム・スコードに悪い印象を持っている"); break;
         case VIEW_PRISONS: addstr("が囚人への虐待と拷問を止めるべきだと考えている"); break;
         case VIEW_AMRADIO: addstr("がAMラジオを好まない"); break;
         case VIEW_CABLENEWS: addstr("がケーブルテレビニュースに否定的な意見を持っている"); break;
         //case VIEW_POLITICALVIOLENCE: addstr("thought political violence was justified");break;
         }
      }

      while(true)
      {
         int c=getkey();

         if(c=='x'||c==ENTER||c==ESC||c==SPACEBAR) return;
         else if(c==interface_pgup||c==KEY_UP||c==KEY_LEFT) { page--; break; }
         else if(c==interface_pgdn||c==KEY_DOWN||c==KEY_RIGHT) { page++; break; }
      }
   }


}

// Police accost your liberal!
void attemptarrest(Creature & liberal,const char* string,int clearformess)
{
   if(string)
   {
      if(clearformess) erase();
      else makedelimiter();

      set_color(COLOR_WHITE,COLOR_BLACK,1);
      move(8,1);
      addstr(liberal.name, gamelog);
      addstr("が", gamelog);
      addstr(string, gamelog);
      addstr("警官が近づいてきた!", gamelog);
      gamelog.nextMessage();

      getkey();
   }

   // Chase sequence! Wee!
   makechasers(-1,5);

   if(!sitestory)
   {
      newsstoryst *ns=new newsstoryst;
      ns->type=NEWSSTORY_WANTEDARREST; // TODO: Make a more generic catch-all arrest story
      ns->loc=-1;
      newsstory.push_back(ns);
      sitestory=ns;
   }

   chaseseq.clean();
   chaseseq.location=location[liberal.location]->parent;
   footchase(liberal);
}

// While galavanting in public, your liberals may be ambushed by police
int checkforarrest(Creature & liberal,const char* string,int clearformess)
{
   bool arrest=false;

   if(!liberal.animalgloss && liberal.is_naked() && LCSrandom(2))
   {
      criminalize(liberal,LAWFLAG_DISTURBANCE);

      newsstoryst *ns=new newsstoryst;
      ns->type=NEWSSTORY_NUDITYARREST;
      ns->loc=-1;
      newsstory.push_back(ns);
      sitestory=ns;

      arrest=true;
   }
   else if(liberal.heat>liberal.get_skill(SKILL_STREETSENSE)*10)
   {
      if(!LCSrandom(50))
      {
         newsstoryst *ns=new newsstoryst;
         ns->type=NEWSSTORY_WANTEDARREST;
         ns->loc=-1;
         newsstory.push_back(ns);
         sitestory=ns;

         arrest=true;
      }
   }

   if(arrest) attemptarrest(liberal,string,clearformess);
   return arrest;
}



/* misc activation related things */
// *JDSRETURN*
void funds_and_trouble(char &clearformess)
{  //ACTIVITIES FOR INDIVIDUALS
   vector<Creature *> trouble,hack,bury,solicit,tshirts,art,music,graffiti,brownies,prostitutes,teachers,students;

   for(int p=0;p<len(pool);p++)
   {
      if(!pool[p]->alive) continue;
      if(pool[p]->location==-1)
      {
         pool[p]->activity.type=ACTIVITY_NONE;
         continue;
      }
      switch(pool[p]->activity.type)
      {
      case ACTIVITY_TEACH_FIGHTING:
      case ACTIVITY_TEACH_POLITICS:
      case ACTIVITY_TEACH_COVERT:
         teachers.push_back(pool[p]);
         break;
      case ACTIVITY_CCFRAUD:
      case ACTIVITY_DOS_RACKET:
      case ACTIVITY_DOS_ATTACKS:
      case ACTIVITY_HACKING:
         hack.push_back(pool[p]);
         break;
      case ACTIVITY_GRAFFITI:
         graffiti.push_back(pool[p]);
         break;
      case ACTIVITY_TROUBLE:
         trouble.push_back(pool[p]);
         break;
      case ACTIVITY_COMMUNITYSERVICE:
         addjuice(*pool[p],1,10);
         change_public_opinion(VIEW_LIBERALCRIMESQUADPOS,1,0,80);
         break;
      case ACTIVITY_SELL_TSHIRTS:
         tshirts.push_back(pool[p]);
         break;
      case ACTIVITY_SELL_ART:
         art.push_back(pool[p]);
         break;
      case ACTIVITY_SELL_MUSIC:
         music.push_back(pool[p]);
         break;
      case ACTIVITY_DONATIONS:
         solicit.push_back(pool[p]);
         break;
      case ACTIVITY_SELL_DRUGS:
         brownies.push_back(pool[p]);
         break;
      case ACTIVITY_PROSTITUTION:
         prostitutes.push_back(pool[p]);
         break;
      case ACTIVITY_BURY:
         bury.push_back(pool[p]);
         pool[p]->activity.type=ACTIVITY_NONE;
         break;
      case ACTIVITY_CLINIC:
         hospitalize(find_clinic(*pool[p]),*pool[p]);
         pool[p]->activity.type=ACTIVITY_NONE;
         break;
      case ACTIVITY_STUDY_DEBATING:
      case ACTIVITY_STUDY_MARTIAL_ARTS:
      case ACTIVITY_STUDY_DRIVING:
      case ACTIVITY_STUDY_PSYCHOLOGY:
      case ACTIVITY_STUDY_FIRST_AID:
      case ACTIVITY_STUDY_LAW:
      case ACTIVITY_STUDY_DISGUISE:
      case ACTIVITY_STUDY_SCIENCE:
      case ACTIVITY_STUDY_BUSINESS:
      //case ACTIVITY_STUDY_COOKING:
      case ACTIVITY_STUDY_GYMNASTICS:
      case ACTIVITY_STUDY_ART:
      case ACTIVITY_STUDY_TEACHING:
      case ACTIVITY_STUDY_MUSIC:
      case ACTIVITY_STUDY_WRITING:
      case ACTIVITY_STUDY_LOCKSMITHING:
         students.push_back(pool[p]);
         break;
      case ACTIVITY_SLEEPER_JOINLCS:
         if(!location[find_homeless_shelter(*pool[p])]->siege.siege)
         {
            pool[p]->activity.type=ACTIVITY_NONE;
            pool[p]->flag &= ~CREATUREFLAG_SLEEPER;
            pool[p]->location = pool[p]->base = find_homeless_shelter(*pool[p]);
         }
         //Letters to the editor
      case ACTIVITY_WRITE_LETTERS:
         if(pool[p]->skill_check(SKILL_WRITING,DIFFICULTY_EASY))
            background_liberal_influence[randomissue()]+=5;
         pool[p]->train(SKILL_WRITING,LCSrandom(5)+1);
         break;
      //Guardian Essays
      //Basically letters to the editor, but thrice as potent, and can backfire
      case ACTIVITY_WRITE_GUARDIAN:
         if(pool[p]->skill_check(SKILL_WRITING,DIFFICULTY_EASY))
            background_liberal_influence[randomissue()]+=15;
         else
            background_liberal_influence[randomissue()]-=15;
         pool[p]->train(SKILL_WRITING,LCSrandom(5)+1);
         break;
      }
   }

	doActivitySolicitDonations(solicit, clearformess);
	doActivitySellTshirts(tshirts, clearformess);
	doActivitySellArt(art, clearformess);
	doActivitySellMusic(music, clearformess);
	doActivitySellBrownies(brownies, clearformess);
  	doActivityHacking(hack, clearformess);
	doActivityGraffiti(graffiti, clearformess);
  	doActivityProstitution(prostitutes, clearformess);
  	doActivityLearn(students, clearformess);
  	doActivityTrouble(trouble, clearformess);
  	doActivityTeach(teachers, clearformess);
  	doActivityBury(bury, clearformess);
}

void doActivitySolicitDonations(vector<Creature *> &solicit, char &clearformess)
{  //SOLICITORS
   long total_income=0;
   for(int s=0;s<len(solicit);s++)
   {
      if(!checkforarrest(*solicit[s],"寄付金を集めていると",clearformess))
      {
         int income=solicit[s]->skill_roll(SKILL_PERSUASION) *
                    solicit[s]->get_armor().get_professionalism()+1;

         // Country's alignment dramatically affects effectiveness
         // The more conservative the country, the more effective
         if(publicmood(-1)>90) income/=2;
         if(publicmood(-1)>65) income/=2;
         if(publicmood(-1)>35) income/=2;
         if(publicmood(-1)>10) income/=2;

         solicit[s]->income=income;

         total_income += income;

         solicit[s]->train(SKILL_PERSUASION,max(5-solicit[s]->get_skill(SKILL_PERSUASION),2));
      }
   }
   ledger.add_funds(total_income,INCOME_DONATIONS);
}

void doActivitySellTshirts(vector<Creature *> &tshirts, char &clearformess)
{
   for(int s=0;s<len(tshirts);s++)
   {
      if(!checkforarrest(*tshirts[s],"Tシャツを売っていると",clearformess))
      {
         long money = (tshirts[s]->skill_roll(SKILL_TAILORING) +
                       tshirts[s]->skill_roll(SKILL_BUSINESS))/2;

         // Country's alignment affects effectiveness
         // In a Liberal country, there are many competing vendors
         if(publicmood(-1)>65) money/=2;
         if(publicmood(-1)>35) money/=2;

         //If you're selling epic shirts enough they'll have some political impact
         if(tshirts[s]->skill_check(SKILL_TAILORING,DIFFICULTY_FORMIDABLE))
            background_liberal_influence[randomissue()]+=5;

         tshirts[s]->income=money;
         ledger.add_funds(money,INCOME_TSHIRTS);

         tshirts[s]->train(SKILL_TAILORING,max(7-tshirts[s]->get_skill(SKILL_TAILORING),2));
         tshirts[s]->train(SKILL_BUSINESS,max(7-tshirts[s]->get_skill(SKILL_BUSINESS),2));
      }
   }
}

void doActivitySellArt(vector<Creature *> &art, char &clearformess)
{
	for(int s=0;s<len(art);s++)
   {
      if(!checkforarrest(*art[s],"似顔絵を描いていると",clearformess))
      {
         long money = art[s]->skill_roll(SKILL_ART);

         // Country's alignment affects effectiveness
         // In a Liberal country, there are many competing vendors
         if(publicmood(-1)>65) money/=2;
         if(publicmood(-1)>35) money/=2;

         //Epic Liberal art may have positive political effect
         if(art[s]->skill_check(SKILL_ART,DIFFICULTY_FORMIDABLE))
            background_liberal_influence[randomissue()]+=5;

         art[s]->income=money;
         ledger.add_funds(money,INCOME_SKETCHES);

         art[s]->train(SKILL_ART,max(7-art[s]->get_skill(SKILL_ART),4));
      }
   }
}

void doActivitySellMusic(vector<Creature *> &music, char &clearformess)
{
   for(int s=0;s<len(music);s++)
   {
      if(!checkforarrest(*music[s],"音楽を弾いていると",clearformess))
      {
         long money = music[s]->skill_roll(SKILL_MUSIC)/2;
         bool has_instrument = music[s]->get_weapon().is_instrument();

         if(has_instrument) money*=4;

         // Country's alignment affects effectiveness
         // In a Liberal country, there are many competing vendors
         if(publicmood(-1)>65) money/=2;
         if(publicmood(-1)>35) money/=2;

         //Epic Liberal protest songs
         if(music[s]->skill_check(SKILL_MUSIC,DIFFICULTY_FORMIDABLE))
            background_liberal_influence[randomissue()]+=has_instrument ? 10 : 5;

         ledger.add_funds(money,INCOME_BUSKING);
         music[s]->income=money;

         if(has_instrument) music[s]->train(SKILL_MUSIC,max(7-music[s]->get_skill(SKILL_MUSIC),4));
         else music[s]->train(SKILL_MUSIC,max(5-music[s]->get_skill(SKILL_MUSIC),2));
      }
   }
}

void doActivitySellBrownies(vector<Creature *> &brownies, char &clearformess)
{
   for(int s=0;s<len(brownies);s++)
   {
      //Check for police search
      int dodgelawroll=LCSrandom(1+30*law[LAW_DRUGS]+3);

      //Saved by street sense?
      if(dodgelawroll==0)
         dodgelawroll=brownies[s]->skill_check(SKILL_STREETSENSE,DIFFICULTY_AVERAGE);

      if(dodgelawroll==0 && law[LAW_DRUGS]<=0) // Busted!
      {
         newsstoryst *ns=new newsstoryst;
         ns->type=NEWSSTORY_DRUGARREST;
         ns->loc=-1;
         newsstory.push_back(ns);
         sitestory=ns;

         criminalize(*brownies[s],LAWFLAG_BROWNIES);
         attemptarrest(*brownies[s],"ケーキを売っていると",clearformess);
      }

      long money = brownies[s]->skill_roll(SKILL_PERSUASION) +
                   brownies[s]->skill_roll(SKILL_BUSINESS) +
                   brownies[s]->skill_roll(SKILL_STREETSENSE);

      // more money when more illegal
      if(law[LAW_DRUGS]==-2) money*=4;
      if(law[LAW_DRUGS]==-1) money*=2;
      if(law[LAW_DRUGS]==1) money/=4;
      if(law[LAW_DRUGS]==2) money/=8;

      brownies[s]->income=money;
      ledger.add_funds(money,INCOME_BROWNIES);

      // Make the sale
      brownies[s]->train(SKILL_PERSUASION,max(4-brownies[s]->get_skill(SKILL_PERSUASION),1));
      // Know the streets
      brownies[s]->train(SKILL_STREETSENSE,max(7-brownies[s]->get_skill(SKILL_STREETSENSE),3));
      // Manage your money
      brownies[s]->train(SKILL_BUSINESS,max(10-brownies[s]->get_skill(SKILL_BUSINESS),3));
   }

}

void doActivityHacking(vector<Creature *> &hack, char &clearformess)
{
   if(len(hack))
   {
      vector<Creature *> cc,web,ddos,truehack;

      //First, do accounting to figure out who's doing what
      for(int h=0;h<len(hack);h++)
      {
         switch(hack[h]->activity.type)
         {
         case ACTIVITY_CCFRAUD:
            hack[h]->train(SKILL_COMPUTERS,2);
            cc.push_back(hack[h]);
            break;
         case ACTIVITY_DOS_ATTACKS:
            hack[h]->train(SKILL_COMPUTERS,2);
            web.push_back(hack[h]);
            break;
         case ACTIVITY_DOS_RACKET:
            hack[h]->train(SKILL_COMPUTERS,4);
            ddos.push_back(hack[h]);
            break;
         case ACTIVITY_HACKING:
            hack[h]->train(SKILL_COMPUTERS,4);
            truehack.push_back(hack[h]);
            break;
         }
      }

      char msg[200] = {0};

      //MAJOR HACKING
      int hack_skill=0;
      for(int h=0;h<len(truehack);h++)
         hack_skill=MAX(hack_skill,truehack[h]->skill_roll(SKILL_COMPUTERS));

      if(DIFFICULTY_HEROIC<=hack_skill+len(truehack)-1)
      {
         if(len(truehack)>1) strcpy(msg,"あなたのハッカー集団は");
         else { strcpy(msg,truehack[0]->name); strcat(msg,"は"); }

         int trackdif=0,juiceval=0;
         int short crime=0;

         switch(LCSrandom(11))
         {
            case 0:
            {
               strcat(msg,"企業のサーバからファイルを盗み取った");

               Item *it=new Loot(*loottype[getloottype("LOOT_CORPFILES")]);
               location[hack[0]->location]->loot.push_back(it);

               trackdif=DIFFICULTY_SUPERHEROIC;
               crime=LAWFLAG_INFORMATION;
               juiceval=10;
               break;
            }
            case 1: // *JDS* Penetrated government networks; don't get any loot, but do scare the info community
               strcat(msg,"CIAネットワークに侵入して恐怖を与えた");

               trackdif=DIFFICULTY_IMPOSSIBLE;
               crime=LAWFLAG_INFORMATION;
               juiceval=25;
               change_public_opinion(VIEW_INTELLIGENCE,10,0,75);
               break;
            case 2:
               strcat(msg,"遺伝子調査会社のネットワークを妨害した");

               trackdif=DIFFICULTY_SUPERHEROIC;
               crime=LAWFLAG_INFORMATION;
               juiceval=10;
               change_public_opinion(VIEW_GENETICS,2,0,75);
               break;
            case 3:
            {
               strcat(msg,"マスメディアの電子メールを傍受した");

               Item *it;
               if(LCSrandom(2))it=new Loot(*loottype[getloottype("LOOT_CABLENEWSFILES")]);
               else it=new Loot(*loottype[getloottype("LOOT_AMRADIOFILES")]);
               location[hack[0]->location]->loot.push_back(it);

               trackdif=DIFFICULTY_SUPERHEROIC;
               crime=LAWFLAG_INFORMATION;
               juiceval=10;
               break;
            }
            case 4:
               strcat(msg,"軍用ネットワークに侵入しLCSのスローガンを書き残した");

               trackdif=DIFFICULTY_IMPOSSIBLE;
               crime=LAWFLAG_INFORMATION;
               juiceval=10;
               change_public_opinion(VIEW_LIBERALCRIMESQUAD,5,0,75);
               break;
            case 5:
            {
               strcat(msg,"問題のある研究の情報を明らかにした");

               Item *it=new Loot(*loottype[getloottype("LOOT_RESEARCHFILES")]);
               location[hack[0]->location]->loot.push_back(it);

               trackdif=DIFFICULTY_SUPERHEROIC;
               crime=LAWFLAG_INFORMATION;
               juiceval=10;
               break;
            }
            case 6:
            {
               strcat(msg,"司法の汚職の証拠を発見した");

               Item *it=new Loot(*loottype[getloottype("LOOT_JUDGEFILES")]);
               location[hack[0]->location]->loot.push_back(it);

               trackdif=DIFFICULTY_SUPERHEROIC;
               crime=LAWFLAG_INFORMATION;
               juiceval=10;
               break;
            }
            case 7:
            {
               strcat(msg,"保守的家族のフォーラムを攻撃した");

               trackdif=DIFFICULTY_SUPERHEROIC;
               crime=LAWFLAG_INFORMATION;
               juiceval=10;
               change_public_opinion(VIEW_GAY,2,0,75);
               change_public_opinion(VIEW_WOMEN,2,0,75);
               break;
            }
            case 8:
            {
               strcat(msg,"人種差別的な警官が暴行する動画を拡散した");

               trackdif=DIFFICULTY_SUPERHEROIC;
               crime=LAWFLAG_INFORMATION;
               juiceval=10;
               change_public_opinion(VIEW_POLICEBEHAVIOR,2,0,75);
               change_public_opinion(VIEW_CIVILRIGHTS,2,0,75);
               break;
            }
            case 9:
            {
               strcat(msg,"CEOの税金逃れを暴露する電子メールを送った");
               //Scambaiting, except you're baiting a CEO

               trackdif=DIFFICULTY_SUPERHEROIC;
               crime=LAWFLAG_INFORMATION;
               juiceval=10;
               change_public_opinion(VIEW_CEOSALARY,2,0,75);
               change_public_opinion(VIEW_TAXES,2,0,75);
               break;
            }
            case 10:
            {
               strcat(msg,"移民帰化局の政治的偏りを暴露した");

               trackdif=DIFFICULTY_SUPERHEROIC;
               crime=LAWFLAG_INFORMATION;
               juiceval=10;
               change_public_opinion(VIEW_IMMIGRATION,2,0,75);
               change_public_opinion(VIEW_FREESPEECH,2,0,75);
               break;
            }

         }

         if(trackdif>hack_skill + LCSrandom(5)-2)
            for(int h=0;h<len(truehack);h++)
               criminalize(*hack[h],crime);

         // Award juice to the hacking team for a job well done
         for(int h=0;h<len(truehack);h++)
            addjuice(*truehack[h],juiceval,200);
      }
      else if(DIFFICULTY_FORMIDABLE<=hack_skill+len(truehack)-1)
      {
         int issue=LCSrandom(VIEWNUM-5),crime=LAWFLAG_INFORMATION;

         // Maybe do a switch on issue here to specify which website it was, but I don't feel like
         // doing that right now

         if(len(truehack)>1) strcpy(msg,"あなたのハッカー集団は");
         else { strcpy(msg,truehack[0]->name); strcat(msg,"は"); }

         switch(LCSrandom(5))
         {
         case 0: strcat(msg,"企業のウェブサイト"); break;
         case 1: strcat(msg,"保守派のフォーラム");break;
         case 2: strcat(msg,"保守派のブログ"); break;
         case 3: strcat(msg,"ニュースサイト"); break;
         case 4: strcat(msg,"政府のウェブサイト"); break;
         }
         strcat(msg,"を");
         switch(LCSrandom(4))
         {
         case 0: strcat(msg,"改ざんした");crime=LAWFLAG_INFORMATION; break;
         case 1: strcat(msg,"停止させた");crime=LAWFLAG_COMMERCE; break;
         case 2: strcat(msg,"脅迫した");crime=LAWFLAG_SPEECH; break;
         case 3: strcat(msg,"ハックした");crime=LAWFLAG_INFORMATION; break;
         }
         strcat(msg,"。");

         change_public_opinion(issue,1);

         if(DIFFICULTY_HEROIC>hack_skill+LCSrandom(5)-2)
            for(int h=0;h<len(truehack);h++)
               criminalize(*truehack[h],crime);

         // Award juice to the hacking team for a job well done
         for(int h=0;h<len(truehack);h++)
            addjuice(*truehack[h],5,100);
      }

      if(msg[0])
      {
         if(clearformess) erase();
         else makedelimiter();

         set_color(COLOR_WHITE,COLOR_BLACK,1);
         move(8,1);

         addstr(msg, gamelog);
         gamelog.nextMessage();
         msg[0]=0;

         getkey();
      }

      //CREDIT CARD FRAUD
      for(int h=0;h<len(cc);h++)
      {
         hack_skill = cc[h]->skill_roll(SKILL_COMPUTERS);
         int difficulty = DIFFICULTY_CHALLENGING;

         if(difficulty<=hack_skill)
         {
            // *JDS* You get between $1 and $100, plus an extra $1-50 every
            // time you pass a check against your hacking skill, where chance of
            // failure is one over the adjusted hackers' skill divided by four. Once
            // a check fails, no more money is gained. This check will be made
            // up to 20 times, at which point the loop breaks. The skill check
            // here doesn't take into account funding.
            int fundgain=LCSrandom(101);
            while(difficulty<hack_skill)
            {
               fundgain+=LCSrandom(51);
               difficulty+=2;
            }
            ledger.add_funds(fundgain,INCOME_CCFRAUD);

            cc[h]->income = fundgain / len(cc);

            if(fundgain/25>LCSrandom(hack_skill+1))
               criminalize(*cc[h],LAWFLAG_CCFRAUD);
         }

         if(msg[0])
         {
            if(clearformess) erase();
            else makedelimiter();

            set_color(COLOR_WHITE,COLOR_BLACK,1);
            move(8,1);

            addstr(msg, gamelog); //TODO: Log this?
            gamelog.nextMessage();
            msg[0]=0;

            getkey();
         }
      }
   }

}

void doActivityGraffiti(vector<Creature *> &graffiti, char &clearformess)
{
	int s;

   if(len(graffiti))
   {
      for(s=0;s<len(graffiti);s++)
      {
         if(!graffiti[s]->get_weapon().can_graffiti())
         {

            if(clearformess) erase();
            else makedelimiter();

            set_color(COLOR_WHITE,COLOR_BLACK,1);
            move(8,1);
            addstr(graffiti[s]->name, gamelog);

            //Check base inventory for a spraycan
            bool foundone=false;
            for(int i=0;i<len(location[graffiti[s]->base]->loot);i++)
            {
               if(location[graffiti[s]->base]->loot[i]->is_weapon())
               {
                  Weapon *w = static_cast<Weapon*>(location[graffiti[s]->base]->loot[i]); //cast -XML
                  if(w->can_graffiti())
                  {
                     addstr("は", gamelog);
                     addstr(w->get_name(), gamelog);
                     addstr("を", gamelog);
                     addstr(location[graffiti[s]->base]->getname()); //TODO: Explicitly log it, or will the game log it?
                     addstr("で現地調達した。", gamelog);

                     getkey();

                     graffiti[s]->give_weapon(*w,&(location[graffiti[s]->base]->loot));

                     if(location[graffiti[s]->base]->loot[i]->empty())
                        delete_and_remove(location[graffiti[s]->base]->loot,i);
                     foundone = true;
                     break;
                  }
               }
            }

            if(!foundone && ledger.get_funds()>=20)
            {
               ledger.subtract_funds(20,EXPENSE_SHOPPING);
               addstr("は落書きのためにスプレー缶を買った。", gamelog);

               getkey();

               Weapon spray(*weapontype[getweapontype("WEAPON_SPRAYCAN")]);
               graffiti[s]->give_weapon(spray,&location[graffiti[s]->base]->loot);
            }
            else if (!foundone)
            {
               addstr("が落書きするにはスプレー缶が必要だ。", gamelog);
               graffiti[s]->activity.type=ACTIVITY_NONE;

               getkey();
            }
            gamelog.nextMessage(); //Next message now so that we don't have to type it for every case.
         }

         int issue=VIEW_LIBERALCRIMESQUAD,power=1;

         if(clearformess) erase();
         else makedelimiter();

         if(!LCSrandom(10) &&
            !(graffiti[s]->skill_check(SKILL_STREETSENSE,DIFFICULTY_AVERAGE)))
         {
            if(clearformess) erase();
            else makedelimiter();

            set_color(COLOR_WHITE,COLOR_BLACK,1);
            move(8,1);

            addstr(graffiti[s]->name, gamelog);
            addstr("は", gamelog);
            criminalize(*graffiti[s],LAWFLAG_VANDALISM);
            graffiti[s]->train(SKILL_STREETSENSE,20);

            if(graffiti[s]->activity.arg!=-1)
            {
               addstr("壁絵を描いている", gamelog);
               graffiti[s]->activity.arg=-1;
            }
            else addstr("LCSのマークをスプレーしている", gamelog);
            addstr("ところを警官に見られた!", gamelog);
            gamelog.nextMessage();

            newsstoryst *ns=new newsstoryst;
            ns->type=NEWSSTORY_GRAFFITIARREST;
            ns->loc=-1;
            ns->positive=0;
            newsstory.push_back(ns);
            sitestory=ns;

            getkey();

            attemptarrest(*graffiti[s],NULL,clearformess);
         }
         else if(graffiti[s]->activity.arg!=-1)
         {
            power=0;
            if(!LCSrandom(3))
            {
               issue=graffiti[s]->activity.arg;
               power=graffiti[s]->skill_roll(SKILL_ART)/3;

               set_color(COLOR_WHITE,COLOR_BLACK,1);
               move(8,1);
               addstr(graffiti[s]->name, gamelog);
               addstr("は", gamelog);
               if(power>3)addstr("すばらしい", gamelog);
               addstr(getview(issue,false), gamelog);
               addstr("の壁絵を完成させた。", gamelog);
               gamelog.nextMessage();

               graffiti[s]->activity.arg=-1;
               addjuice(*graffiti[s],power,power*20);
               change_public_opinion(issue,power);
               graffiti[s]->train(SKILL_ART,MAX(10-graffiti[s]->get_skill(SKILL_ART)/2,1));

               getkey();
            }
            else
            {
               power=0;
               set_color(COLOR_WHITE,COLOR_BLACK,1);
               move(8,1);
               addstr(graffiti[s]->name, gamelog);
               addstr("は一晩をかけて巨大な壁絵を描いた。", gamelog);
               gamelog.nextMessage();
               graffiti[s]->train(SKILL_ART,MAX(10-graffiti[s]->get_skill(SKILL_ART)/2,1));

               getkey();
            }
         }
         else if(!LCSrandom(MAX(30-graffiti[s]->get_skill(SKILL_ART)*2,5)))
         {
            issue=randomissue();
            set_color(COLOR_WHITE,COLOR_BLACK,1);
            move(8,1);
            addstr(graffiti[s]->name, gamelog);
            addstr("は", gamelog);
            addstr(getview(issue,false), gamelog);
            addstr("の巨大な壁絵を描き始めた。", gamelog);
            gamelog.nextMessage();
            graffiti[s]->activity.arg=issue;
            power=0;
            graffiti[s]->train(SKILL_ART,MAX(10-graffiti[s]->get_skill(SKILL_ART)/2,1));

            getkey();
         }

         graffiti[s]->train(SKILL_ART,MAX(4-graffiti[s]->get_skill(SKILL_ART),0));
         if(issue==VIEW_LIBERALCRIMESQUAD)
         {
            change_public_opinion(VIEW_LIBERALCRIMESQUAD,LCSrandom(2),0,65);
            change_public_opinion(VIEW_LIBERALCRIMESQUADPOS,!LCSrandom(8),0,65);
            public_interest[issue]+=power;
         }
         else
         {
            change_public_opinion(VIEW_LIBERALCRIMESQUAD,LCSrandom(2)+1,0,85);
            change_public_opinion(VIEW_LIBERALCRIMESQUADPOS,!LCSrandom(4),0,65);
            public_interest[issue]+=power;
            background_liberal_influence[issue]+=power;
         }
      }
   }
}

void doActivityProstitution(vector<Creature *> &prostitutes, char &clearformess)
{
   for(int p=len(prostitutes)-1;p>=0;p--)
   {
      // Business once every three days or so
      if(LCSrandom(3)) continue;

      //char num[20];

      long fundgain=0;
      char caught=0;

      // Skill determies how much money you get
      int performance = prostitutes[p]->skill_roll(SKILL_SEDUCTION);
      if(performance>DIFFICULTY_HEROIC)
         fundgain=LCSrandom(201)+200;
      else
         fundgain=LCSrandom(10*performance)+10*performance;

      // Street sense check or deal with slimy people that reduce dignity and juice
      if(!LCSrandom(3) &&
         !(prostitutes[p]->skill_check(SKILL_STREETSENSE,DIFFICULTY_AVERAGE)))
      {
         addjuice(*prostitutes[p],-!LCSrandom(3), -20);
      }

      // Gain seduction and street sense
      prostitutes[p]->train(SKILL_SEDUCTION,MAX(10-prostitutes[p]->get_skill(SKILL_SEDUCTION),0));
      prostitutes[p]->train(SKILL_STREETSENSE,MAX(10-prostitutes[p]->get_skill(SKILL_STREETSENSE),0));


      if(!LCSrandom(50)) // Police sting?
      {
         if(!(prostitutes[p]->skill_check(SKILL_STREETSENSE,DIFFICULTY_AVERAGE))) // Street sense to avoid
         {
            if(clearformess) erase();
            else makedelimiter();

            set_color(COLOR_WHITE,COLOR_BLACK,1);
            move(8,1);
            addstr(prostitutes[p]->name, gamelog);
            addstr("は売春の容疑で逮捕された。", gamelog);
            gamelog.nextMessage();

            addjuice(*prostitutes[p],-7,-30);

            getkey();

            caught=1;

            removesquadinfo(*prostitutes[p]);
            prostitutes[p]->carid=-1;
            prostitutes[p]->location=find_police_station(*prostitutes[p]);
            prostitutes[p]->drop_weapons_and_clips(NULL);
            prostitutes[p]->activity.type=ACTIVITY_NONE;
            criminalize(*prostitutes[p],LAWFLAG_PROSTITUTION);
         }
         else
         {
            if(clearformess) erase();
            else makedelimiter();

            set_color(COLOR_WHITE,COLOR_BLACK,1);
            move(8,1);
            addstr(prostitutes[p]->name, gamelog);
            addstr("は売春であやうく逮捕されるところだった。", gamelog);
            gamelog.nextMessage();

            addjuice(*prostitutes[p],5,0);

            getkey();
         }
      }

      if(!caught)
      {
         prostitutes[p]->train(SKILL_STREETSENSE,MAX(5-prostitutes[p]->get_skill(SKILL_STREETSENSE),0));
         ledger.add_funds(fundgain,INCOME_PROSTITUTION);
         prostitutes[p]->income = fundgain;
      }
   }
}

void doActivityLearn(vector<Creature *> &students, char &clearformess)
{
   for(int s=len(students)-1;s>=0;s--)
   {
	   if(ledger.get_funds()<60) break;
	   ledger.subtract_funds(60,EXPENSE_TRAINING);
	   int skill[2] = {-1, -1};
	   int effectiveness[2] = {20, 20};
	   switch(students[s]->activity.type)
	   {
		  case ACTIVITY_STUDY_DEBATING:
			  skill[0] = SKILL_PERSUASION;
			  break;
		  case ACTIVITY_STUDY_MARTIAL_ARTS:
			  skill[0] = SKILL_HANDTOHAND;
			  break;
		  case ACTIVITY_STUDY_DRIVING:
			  skill[0] = SKILL_DRIVING;
			  break;
		  case ACTIVITY_STUDY_PSYCHOLOGY:
           skill[0] = SKILL_PSYCHOLOGY;
			  break;
		  case ACTIVITY_STUDY_FIRST_AID:
           skill[0] = SKILL_FIRSTAID;
			  break;
		  case ACTIVITY_STUDY_LAW:
	        skill[0] = SKILL_LAW;
			  break;
		  case ACTIVITY_STUDY_DISGUISE:
           skill[0] = SKILL_DISGUISE;
			  break;
		  case ACTIVITY_STUDY_SCIENCE:
           skill[0] = SKILL_SCIENCE;
			  break;
		  case ACTIVITY_STUDY_BUSINESS:
           skill[0] = SKILL_BUSINESS;
			  break;
	//case ACTIVITY_STUDY_COOKING:
        //   skill[0] = SKILL_COOKING;
        //   break;
		  case ACTIVITY_STUDY_GYMNASTICS:
           skill[0] = SKILL_DODGE;
			  break;
        case ACTIVITY_STUDY_LOCKSMITHING:
           skill[0] = SKILL_SECURITY;
           break;
		  case ACTIVITY_STUDY_MUSIC:
           skill[0] = SKILL_MUSIC;
			  break;
		  case ACTIVITY_STUDY_ART:
           skill[0] = SKILL_ART;
			  break;
		  case ACTIVITY_STUDY_TEACHING:
           skill[0] = SKILL_TEACHING;
			  break;
		  case ACTIVITY_STUDY_WRITING:
           skill[0] = SKILL_WRITING;
			  break;
	   }
	   bool worthcontinuing=false;
	   for(int i=0; i<2; i++)
		   if(skill[i]!=-1)
		   {  // rapid decrease in effectiveness as your skill gets higher.
            effectiveness[i] /= (students[s]->get_skill(skill[i])+1);
			   if(effectiveness[i]<1)
               effectiveness[i]=1;
		      students[s]->train(skill[i],effectiveness[i]);
            if(students[s]->get_skill(skill[i]) < students[s]->skill_cap(skill[i],true))
				   worthcontinuing=true;
		   }
	   if (!worthcontinuing)
	   {
		   students[s]->activity.type=ACTIVITY_NONE;
         set_color(COLOR_WHITE,COLOR_BLACK,1);
         move(8,1);
         addstr(students[s]->name, gamelog);
         addstr("は限界まで", gamelog);
         addstr(students[s]->heshe(), gamelog);
         addstr("を学んだ。", gamelog);
         gamelog.nextMessage();

         getkey();
	   }
   }
}

void doActivityTrouble(vector<Creature *> &trouble, char &clearformess)
{
   if(len(trouble))
   {
      long juiceval=0;
      char done=0;
      short crime=0;

      if(clearformess) erase();
      else makedelimiter();

      set_color(COLOR_WHITE,COLOR_BLACK,1);
      move(8,1);
      if(len(trouble)>1) addstr("反抗グループは",gamelog);
      else { addstr(trouble[0]->name,gamelog); addstr("は",gamelog); }

      int power=0;
      for(int t=0;t<len(trouble);t++)
         power+=trouble[t]->skill_roll(SKILL_PERSUASION)+
                trouble[t]->skill_roll(SKILL_STREETSENSE);

      int mod=1;
      if(LCSrandom(10)<power) mod++;
      if(LCSrandom(20)<power) mod++;
      if(LCSrandom(40)<power) mod++;
      if(LCSrandom(60)<power) mod++;
      if(LCSrandom(80)<power) mod++;
      if(LCSrandom(100)<power) mod++;

      do
      {
         switch(LCSrandom(10))
         {
            case 0:
               addstr("住宅街を走り回り、毛皮のコートにペンキをぶちまけた!", gamelog);
               juiceval=2;
               crime=LAWFLAG_ASSAULT;
               change_public_opinion(VIEW_LIBERALCRIMESQUAD,mod);
               change_public_opinion(VIEW_LIBERALCRIMESQUADPOS,mod>>1,0,70);
               public_interest[VIEW_ANIMALRESEARCH]+=mod;
               background_liberal_influence[VIEW_ANIMALRESEARCH]+=mod;
               done=1;
               break;
            case 1:
            {
               if(law[LAW_GAY]<2)
               {
                  addstr("教会で伝統的な結婚式を台無しにした!", gamelog);
                  change_public_opinion(VIEW_LIBERALCRIMESQUAD,mod);
                  change_public_opinion(VIEW_LIBERALCRIMESQUADPOS,mod,0,70);
                  public_interest[VIEW_GAY]+=mod;
                  background_liberal_influence[VIEW_GAY]+=mod;
                  juiceval=2;
                  crime=LAWFLAG_DISTURBANCE;
                  done=1;
               }
               break;
            }
            case 2:
            {
               if(law[LAW_ABORTION]<2)
               {
                  addstr("恐ろしい死を遂げた中絶医の写真を街中に張り出した!", gamelog);
                  change_public_opinion(VIEW_LIBERALCRIMESQUAD,mod);
                  change_public_opinion(VIEW_LIBERALCRIMESQUADPOS,mod,0,70);
                  public_interest[VIEW_WOMEN]+=mod;
                  background_liberal_influence[VIEW_WOMEN]+=mod;
                  juiceval=1;
                  done=1;
               }
               break;
            }
            case 3:
            {
               if(law[LAW_POLICEBEHAVIOR]<2)
               {
                  addstr("街へ向かい、警官による暴力を再現した!", gamelog);
                  change_public_opinion(VIEW_LIBERALCRIMESQUAD,mod);
                  change_public_opinion(VIEW_LIBERALCRIMESQUADPOS,mod,0,70);
                  public_interest[VIEW_POLICEBEHAVIOR]+=mod;
                  background_liberal_influence[VIEW_POLICEBEHAVIOR]+=mod;
                  juiceval=2;
                  crime=LAWFLAG_DISTURBANCE;
                  done=1;
               }
               break;
            }
            case 4:
            {
               if(law[LAW_NUCLEARPOWER]<2)
               {
                  if(len(trouble)>1)addstr("仮装して放射能ミュータントを演じた!", gamelog);
                  else addstr("仮装して放射能ミュータントを演じた!", gamelog);
                  change_public_opinion(VIEW_LIBERALCRIMESQUAD,mod);
                  change_public_opinion(VIEW_LIBERALCRIMESQUADPOS,mod,0,70);
                  public_interest[VIEW_NUCLEARPOWER]+=mod;
                  background_liberal_influence[VIEW_NUCLEARPOWER]+=mod;
                  juiceval=2;
                  crime=LAWFLAG_DISTURBANCE;
                  done=1;
               }
               break;
            }
            case 5:
            {
               if(law[LAW_POLLUTION]<2)
               {
                  addstr("会社員に偽物の汚染水を掛けた!", gamelog);
                  change_public_opinion(VIEW_LIBERALCRIMESQUAD,mod);
                  change_public_opinion(VIEW_LIBERALCRIMESQUADPOS,mod,0,70);
                  public_interest[VIEW_POLLUTION]+=mod;
                  background_liberal_influence[VIEW_POLLUTION]+=mod;
                  juiceval=2;
                  crime=LAWFLAG_DISTURBANCE;
                  done=1;
               }
               break;
            }
            case 6:
            {
               if(law[LAW_DEATHPENALTY]<2)
               {
                  addstr("死刑執行を絵で説明したビラをばら撒いた!", gamelog);
                  change_public_opinion(VIEW_LIBERALCRIMESQUAD,mod);
                  change_public_opinion(VIEW_LIBERALCRIMESQUADPOS,mod,0,70);
                  public_interest[VIEW_DEATHPENALTY]+=mod;
                  background_liberal_influence[VIEW_DEATHPENALTY]+=mod;
                  juiceval=1;
                  done=1;
               }
               break;
            }
            case 7:
            {
               addstr("CIAによる拷問を絵で説明したビラをばら撒いた!", gamelog);
               change_public_opinion(VIEW_LIBERALCRIMESQUAD,mod);
               change_public_opinion(VIEW_LIBERALCRIMESQUADPOS,mod,0,70);
               public_interest[VIEW_TORTURE]+=mod;
               background_liberal_influence[VIEW_TORTURE]+=mod;
               juiceval=1;
               done=1;
               break;
            }
            case 8:
            {
               addstr("企業のマークを焼き払い、資本主義を弾劾した!", gamelog);
               change_public_opinion(VIEW_LIBERALCRIMESQUAD,mod);
               change_public_opinion(VIEW_LIBERALCRIMESQUADPOS,mod,0,70);
               public_interest[VIEW_CORPORATECULTURE]+=mod;
               background_liberal_influence[VIEW_CORPORATECULTURE]+=mod;
               if(law[LAW_CORPORATE]==-2)
               {               // In extreme corporate culture cases this should give a flag burning charge! -- kviiri
                  juiceval=2;  // Done -- SlatersQuest
                  crime=LAWFLAG_BURNFLAG;
               }
               else juiceval=1;
               done=1;
               break;
            }
            case 9:
            {
               addstr("商店街の中心に搾取工場の模型を置いた!", gamelog);
               change_public_opinion(VIEW_LIBERALCRIMESQUAD,mod);
               change_public_opinion(VIEW_LIBERALCRIMESQUADPOS,mod,0,70);
               public_interest[VIEW_SWEATSHOPS]+=mod;
               background_liberal_influence[VIEW_SWEATSHOPS]+=mod;
               juiceval+=1;
               done=1;
               break;
            }
         }
      } while(!done);

      gamelog.nextMessage(); //Do this now so that it doesn't have to be done in every case up there.

      getkey();

      if(crime!=0)
      {
         for(int t=0;t<len(trouble);t++)
         {
            if(!LCSrandom(30) &&
               !(trouble[t]->skill_check(SKILL_STREETSENSE,DIFFICULTY_AVERAGE)))
            {
               if(clearformess) erase();
               else makedelimiter();

               if(!LCSrandom(4))
               {
                  newsstoryst *ns=new newsstoryst;
                  ns->type=NEWSSTORY_WANTEDARREST; // should probably create a NEWSSTORY_TROUBLEARREST and implement it fully
                  ns->loc=-1;                      // but this will have to do for now
                  ns->positive=0;
                  newsstory.push_back(ns);
                  sitestory=ns;
                  attemptarrest(*trouble[t],"騒ぎを起こしていると",clearformess);
               }
               else
               {
                  set_color(COLOR_WHITE,COLOR_BLACK,1);
                  move(8,1);
                  addstr(trouble[t]->name, gamelog);
                  addstr("は怒れる群集に詰め寄られた。", gamelog);
                  gamelog.nextMessage();

                  getkey();

                  bool wonfight = false;

                  if(trouble[t]->get_weapon().is_threatening())
                  {
                     if(clearformess) erase();
                     else makedelimiter();

                     set_color(COLOR_WHITE,COLOR_BLACK,1);
                     move(8,1);
                     addstr(trouble[t]->name, gamelog);
                     addstr("は", gamelog);
                     addstr(trouble[t]->get_weapon().get_name(), gamelog);
                     addstr("をちらつかせた!", gamelog);
                     gamelog.nextMessage();

                     getkey();

                     if(clearformess) erase();
                     else makedelimiter();

                     set_color(COLOR_WHITE,COLOR_BLACK,1);
                     move(8,1);
                     addstr("群集は逃げ出した!", gamelog);
                     gamelog.nextMessage();

                     getkey();

                     addjuice(*trouble[t],5,20);

                     wonfight = true;
                  }
                  else
                  {
                     for(int count=0;count<=LCSrandom(5)+2;count++)
                     {
                        if(clearformess) erase();
                        else makedelimiter();
                        if(trouble[t]->skill_roll(SKILL_HANDTOHAND)>LCSrandom(6)+count)
                        {
                           set_color(COLOR_CYAN,COLOR_BLACK,1);
                           move(8,1);
                           addstr(trouble[t]->name, gamelog);
                           switch(LCSrandom(8))
                           {
                           case 0:addstr("は近くにいる者の腕をへし折った!", gamelog);break;
                           case 1:addstr("は股間を蹴り上げた!", gamelog);break;
                           case 2:addstr("は顔面を殴った!", gamelog);break;
                           case 3:addstr("は耳を噛みちぎった!", gamelog);break;
                           case 4:addstr("はあごを強打した!", gamelog);break;
                           case 5:addstr("は後ろから掴まれたが振り払った!", gamelog);break;
                           case 6:addstr("はスローガンを叫んだ!", gamelog);break;
                           case 7:addstr("は2人の頭を掴みぶつけた!", gamelog);break;
                           }

                           gamelog.nextMessage();

                           getkey();

                           wonfight=true;
                        }
                        else
                        {
                           set_color(COLOR_YELLOW,COLOR_BLACK,1);
                           move(8,1);
                           addstr(trouble[t]->name, gamelog);
                           switch(LCSrandom(8))
                           {
                           case 0:addstr("は押さえつけられ3人の男に殴られた!", gamelog);break;
                           case 1:addstr("は殴られた!", gamelog);break;
                           case 2:addstr("は尖った石で殴られた!", gamelog);break;
                           case 3:addstr("は歩道に投げ飛ばされた!", gamelog);break;
                           case 4:addstr("はシャベルで顔を殴られた!", gamelog);break;
                           case 5:addstr("は首を掴まれた!", gamelog);break;
                           case 6:addstr("は何度も殴られた!", gamelog);break;
                           case 7:addstr("はパイプで腹を殴られた!", gamelog);break;
                           }

                           gamelog.nextMessage();

                           getkey();

                           count++; // fight goes faster when you're losing

                           wonfight=false;
                        }
                     }

                     if(wonfight)
                     {
                        if(clearformess) erase();
                        else makedelimiter();
                        set_color(COLOR_GREEN,COLOR_BLACK,1);
                        move(8,1);
                        addstr(trouble[t]->name, gamelog);
                        addstr("は詰め寄ってきた", gamelog);
                        if(law[LAW_FREESPEECH]==-2)
                           addstr("[きたない]", gamelog);
                        else addstr("クソ", gamelog);
                        addstr("野郎を全て打ちのめした!", gamelog);

                        gamelog.nextMessage();

                        getkey();

                        addjuice(*trouble[t],30,300);
                        if(trouble[t]->blood>70)trouble[t]->blood=70;
                     }
                  }

                  if(!wonfight)
                  {
                     if(clearformess) erase();
                     else makedelimiter();
                     set_color(COLOR_RED,COLOR_BLACK,1);
                     move(8,1);
                     addstr(trouble[t]->name, gamelog);
                     addstr("は群集に打ちのめされた。", gamelog);
                     gamelog.nextMessage();

                     trouble[t]->activity.type=ACTIVITY_CLINIC;

                     getkey();

                     addjuice(*trouble[t],-10,-50);
                     if(trouble[t]->blood>10)trouble[t]->blood=10;

                     if(!LCSrandom(5))
                     {
                        if(clearformess) erase();
                        else makedelimiter();
                        switch(LCSrandom(10))
                        {
                           case 0:
                              if(trouble[t]->special[SPECIALWOUND_LOWERSPINE]==1)
                              {
                                 move(8,1);
                                 addstr(trouble[t]->name, gamelog);
                                 addstr("の下部脊椎が折れた!", gamelog);
                                 gamelog.nextMessage();
                                 trouble[t]->special[SPECIALWOUND_LOWERSPINE]=0;

                                 getkey();
                              }
                              break;
                           case 1:
                              if(trouble[t]->special[SPECIALWOUND_UPPERSPINE]==1)
                              {
                                 move(8,1);
                                 addstr(trouble[t]->name, gamelog);
                                 addstr("の上部脊椎が折れた!", gamelog);
                                 gamelog.nextMessage();
                                 trouble[t]->special[SPECIALWOUND_UPPERSPINE]=0;

                                 getkey();
                              }
                              break;
                           case 2:
                              if(trouble[t]->special[SPECIALWOUND_NECK]==1)
                              {
                                 move(8,1);
                                 addstr(trouble[t]->name, gamelog);
                                 addstr("の首の骨が折れた!", gamelog);
                                 gamelog.nextMessage();
                                 trouble[t]->special[SPECIALWOUND_NECK]=0;

                                 getkey();
                              }
                              break;
                           case 3:
                              if(trouble[t]->special[SPECIALWOUND_TEETH]>0)
                              {
                                 move(8,1);
                                 addstr(trouble[t]->name);
                                 if(trouble[t]->special[SPECIALWOUND_TEETH]>1)addstr("の歯が道に落ちている。", gamelog);
                                 else addstr("の歯がペンチで引き抜かれた!", gamelog);
                                 gamelog.nextMessage();
                                 trouble[t]->special[SPECIALWOUND_TEETH]=0;

                                 getkey();
                              }
                              break;
                           default:
                           {
                              if(trouble[t]->special[SPECIALWOUND_RIBS]>0)
                              {
                                 int ribminus=LCSrandom(RIBNUM)+1;
                                 if(ribminus>trouble[t]->special[SPECIALWOUND_RIBS])ribminus=trouble[t]->special[SPECIALWOUND_RIBS];

                                 move(8,1);
                                 if(ribminus>1)
                                 {
                                    addstr(trouble[t]->name, gamelog);
                                    addstr("の肋骨", gamelog);
                                    addstr(ribminus, gamelog);
                                    addstr("本", gamelog);
                                    if(ribminus==trouble[t]->special[SPECIALWOUND_RIBS])
                                       addstr("全て", gamelog);
                                 }
                                 else if(trouble[t]->special[SPECIALWOUND_RIBS]>1)
                                 {
                                    addstr(trouble[t]->name, gamelog);
                                    addstr("の肋骨", gamelog);
                                 }
                                 else
                                 {
                                    addstr(trouble[t]->name);
                                    addstr("の最後の肋骨", gamelog);
                                 }

                                 addstr("が折れた!", gamelog);
                                 gamelog.nextMessage();

                                 getkey();

                                 trouble[t]->special[SPECIALWOUND_RIBS]-=ribminus;
                              }
                              break;
                           }
                        }
                     }
                  }
               }
            }
         }
      }

      for(int h=0;h<len(trouble);h++)
         addjuice(*trouble[h],juiceval,40);
   }
}

void doActivityTeach(vector<Creature *> &teachers, char &clearformess)
{
   for(int t=0;t<len(teachers);t++)
   {
      int skillarray[14];
      int cost=0, students=0;
      //Build a list of skills to train and determine the cost for running
      //a class depending on what the teacher is teaching
      switch(teachers[t]->activity.type)
      {
      case ACTIVITY_TEACH_POLITICS:
         cost=2;
         skillarray[0]=SKILL_LAW;
         skillarray[1]=SKILL_PERSUASION;
         skillarray[2]=SKILL_WRITING;
         skillarray[3]=SKILL_RELIGION;
         skillarray[4]=SKILL_BUSINESS;
         skillarray[5]=SKILL_SCIENCE;
         skillarray[6]=SKILL_STREETSENSE;
         skillarray[7]=SKILL_MUSIC;
         skillarray[8]=SKILL_ART;
         skillarray[9]=-1;
         break;
      case ACTIVITY_TEACH_COVERT:
         cost=6;
         skillarray[0]=SKILL_SECURITY;
         skillarray[1]=SKILL_COMPUTERS;
         skillarray[2]=SKILL_DISGUISE;
         skillarray[3]=SKILL_TAILORING;
         skillarray[4]=SKILL_STEALTH;
         skillarray[5]=SKILL_SEDUCTION;
         skillarray[6]=SKILL_PSYCHOLOGY;
         skillarray[7]=SKILL_DRIVING;
         skillarray[8]=-1;
         break;
      case ACTIVITY_TEACH_FIGHTING:
         cost=10;
         skillarray[0]=SKILL_KNIFE;
         skillarray[1]=SKILL_SWORD;
         skillarray[2]=SKILL_CLUB;
         skillarray[3]=SKILL_PISTOL;
         skillarray[4]=SKILL_RIFLE;
         skillarray[5]=SKILL_SHOTGUN;
         skillarray[6]=SKILL_HEAVYWEAPONS;
         skillarray[7]=SKILL_AXE;
         skillarray[8]=SKILL_SMG;
         skillarray[9]=SKILL_THROWING;
         skillarray[10]=SKILL_HANDTOHAND;
         skillarray[11]=SKILL_DODGE;
         skillarray[12]=SKILL_FIRSTAID;
         skillarray[13]=-1;
         break;
      }

      //Count potential students for this teacher to get an idea of efficiency
      for(int p=0;p<len(pool);p++)
      {
         //If they're at the location
         if(pool[p]->location==teachers[t]->location &&
            pool[p]->align==ALIGN_LIBERAL &&
            pool[p]->alive)
         {
            //Step through the array of skills to train
            for(int i=0;i<13;i++)           //Any reason why we aren't using a while(true) loop or something even more dynamic? --kviiri
            {
               //If no more skills to train, stop
               if(skillarray[i]==-1) break;
               //Otherwise, if the student has less skill than the teacher, train the student
               //proportional to the difference in skill between teacher and student times the
               //teacher's ability at teaching
               if(pool[p]->get_skill(skillarray[i])<teachers[t]->get_skill(skillarray[i])-1&&
                  pool[p]->get_skill(skillarray[i])<teachers[t]->get_skill(SKILL_TEACHING)+2&&
                  pool[p]->get_skill(skillarray[i])<pool[p]->skill_cap(skillarray[i],true))
               {
                  students++;
               }
            }
         }
      }

      //Check funds.
      if(ledger.get_funds()<min(students,10)*cost)
         continue; //Can't afford to teach them. Continue with next teacher.

      //Walk through and train people
      for(int p=0;p<len(pool);p++)
      {
         //If they're at the location
         if(pool[p]->location==teachers[t]->location &&
            pool[p]->align==ALIGN_LIBERAL &&
            pool[p]->alive)
         {
            //Step through the array of skills to train
            for(int i=0;i<13;i++)
            {
               //If no more skills to train, stop
               if(skillarray[i]==-1)break;
               //Otherwise, if the student has less skill than the teacher, train the student
               //proportional to the difference in skill between teacher and student times the
               //teacher's ability at teaching
               if(pool[p]->get_skill(skillarray[i])<teachers[t]->get_skill(skillarray[i])-1&&
                  pool[p]->get_skill(skillarray[i])<teachers[t]->get_skill(SKILL_TEACHING)+2&&
                  pool[p]->get_skill(skillarray[i])<pool[p]->skill_cap(skillarray[i],true))
               {
                  // Teach based on teacher's skill in the topic plus skill in teaching, minus
                  // student's skill in the topic
                  int teach=teachers[t]->get_skill(skillarray[i])+
                            teachers[t]->get_skill(SKILL_TEACHING)-
                            pool[p]->get_skill(skillarray[i]);
                  //at ten students, cost no longer goes up, but effectiveness goes down.
                  if (students > 10)
                  {
                     //teach = (teach * 10) / students; //teach at 50% speed with twice as many students.
                     teach = ((teach * 30 / students) + teach)/4; //62.5% speed with twice as many students.
                  }
                  if(teach<1)
                     teach=1;
                  // Cap at 10 points per day
                  if(teach>10)
                     teach=10;

                  pool[p]->train(skillarray[i],teach);

                  /*if(students<10)
                  {
                     students++;
                     ledger.subtract_funds(cost,EXPENSE_TRAINING);
                     if(students==10)cost=0;
                  }*/
               }
            }
         }
      }

      ledger.subtract_funds( cost*min(students, 10), EXPENSE_TRAINING );
      teachers[t]->train(SKILL_TEACHING,min(students, 10));
   }
}

void doActivityBury(vector<Creature *> &bury, char &clearformess)
{
   if(len(bury))
   {
      for(int p=len(pool)-1;p>=0;p--)
      {
         if(pool[p]->alive) continue;

         bool arrest_attempted = false;

         //MAKE BASE LOOT
         makeloot(*pool[p],location[bury[0]->base]->loot);

         for(int b=0;b<len(bury);b++)
         {
            if(!arrest_attempted && !(bury[b]->skill_check(SKILL_STREETSENSE,DIFFICULTY_EASY)))
            {
               arrest_attempted = true; // Only attempt one burial arrest per body

               newsstoryst *ns=new newsstoryst;
               ns->type=NEWSSTORY_BURIALARREST;
               ns->loc=-1;
               newsstory.push_back(ns);
               sitestory=ns;

               criminalize(*bury[b],LAWFLAG_BURIAL);
               char str[100];
               strcpy(str, pool[p]->name);
               strcat(str, "の遺体を埋めていると");
               attemptarrest(*bury[b],str,clearformess);

               // If a liberal is spotted they should not do more burials.
               bury.erase(bury.begin() + b--);

               break;
            }
         }

         //BURY (even if interrupted)
         delete_and_remove(pool,p);

         if(!len(bury)) break; //Stop burials if none are left doing them.
      }
   }

}

/* steal a car */
bool stealcar(Creature &cr,char &clearformess)
{
   music.play(MUSIC_CARTHEFT);
   clearformess=1;

   short cartype;

   if(carselect(cr,cartype))
   {
      int diff=vehicletype[cartype]->steal_difficultytofind()*2;

      Vehicle *v=NULL;

      int old=cartype;

      cr.train(SKILL_STREETSENSE,5);

      //THEFT SEQUENCE
      erase();
      set_color(COLOR_WHITE,COLOR_BLACK,1);
      move(0,0);
      addstr("車泥棒の冒険", gamelog);
      gamelog.nextMessage();
      printcreatureinfo(&cr);
      makedelimiter();

      set_color(COLOR_WHITE,COLOR_BLACK,0);
      move(10,0);
      addstr(cr.name, gamelog);
      addstr("は盗めそうな車を探している…", gamelog);

      getkey();

      //ROUGH DAY
      if(!cr.skill_check(SKILL_STREETSENSE,diff))
         do cartype=LCSrandom(len(vehicletype));
         while(cartype==old||LCSrandom(10)<vehicletype[cartype]->steal_difficultytofind());

      string carname=(v=new Vehicle(*vehicletype[cartype]))->fullname();

      move(11,0);
      addstr(cr.name, gamelog);
      if(old!=cartype)
      {
         addstr("は", gamelog);
         addstr(vehicletype[old]->longname(), gamelog);
         addstr("を見つけられなかった。だが、", gamelog);
      }
      else addstr("は", gamelog);
      addstr(v->longname(), gamelog);
      addstr("を見つけた。", gamelog);
      gamelog.nextMessage();

      getkey();

      //APPROACH?
      erase();
      set_color(COLOR_WHITE,COLOR_BLACK,1);
      move(0,0);
      addstr("車泥棒の冒険");
      printcreatureinfo(&cr);
      makedelimiter();

      set_color(COLOR_WHITE,COLOR_BLACK,0);
      move(10,0);
      addstr(cr.name, gamelog);
      addstr("は遠くから", gamelog);
      addstr(carname, gamelog);
      addstr("を見たが、誰も乗っていないようだ。", gamelog);

      gamelog.nextMessage();

      move(12,0);
      addstr("A - 運転席の方向のドアに近づく");
      move(13,0);
      addstr("Enter - 引き上げる");

      while(true)
      {
         int c=getkey();
         if(c=='a')break;
         if(c=='x'||c==ENTER||c==ESC||c==SPACEBAR){delete v;return false;}
      }

      //SECURITY?
      bool alarmon=false,sensealarm=LCSrandom(100)<v->sensealarmchance(),
           touchalarm=LCSrandom(100)<v->touchalarmchance();
      char windowdamage=0;

      for(bool entered=false;!entered;)
      {
         erase();
         set_color(COLOR_WHITE,COLOR_BLACK,1);
         move(0,0);
         addstr("車泥棒の冒険");
         printcreatureinfo(&cr);
         makedelimiter();

         if(alarmon)
         {
            set_color(COLOR_WHITE,COLOR_BLACK,1);
            move(10,0);
            if(sensealarm)addstr("VIPER");
            else addstr(carname);
            addstr(": ");
            set_color(COLOR_RED,COLOR_BLACK,1);
            if(sensealarm)addstr("車から離れなさい!   <ビー!!> <ビー!!>");
            else addstr("<ビー!!> <ビー!!> <ビー!!> <ビー!!>");
         }
         else if(sensealarm)
         {
            set_color(COLOR_WHITE,COLOR_BLACK,1);
            move(10,0);
            addstr("VIPER: ");
            set_color(COLOR_RED,COLOR_BLACK,1);
            addstr("こちらVIPER!   車から離れなさい!", gamelog);
            gamelog.nextMessage();
         }
         else
         {
            set_color(COLOR_WHITE,COLOR_BLACK,0);
            move(10,0);
            addstr(cr.name, gamelog);
            addstr("は", gamelog);
            addstr(carname, gamelog);
            addstr("に近づいた。", gamelog);
            gamelog.nextMessage();
         }

         move(12,0);
         set_color(COLOR_WHITE,COLOR_BLACK,0);
         addstr("A - 鍵を外す");
         set_color(COLOR_WHITE,COLOR_BLACK,0);
         move(13,0);
         addstr("B - 窓を壊す");
         move(14,0);
         if(!sensealarm)addstr("Enter - 引き上げる");
         else
         {
            if(!alarmon)
            {
               addstr("Enter - VIPER? ");
               addstr(cr.name);
               addstr("はあきらめた。");
            }
            else
            {
               addstr("Enter - その通り。VIPERは");
               addstr(cr.name);
               addstr("をあきらめさせた。");
            }
         }

         char method=-1;
         while(method==-1)
         {
            int c=getkey();
            if(c=='a')method=0;
            if(c=='b')method=1;
            if(c=='x'||c==ENTER||c==ESC||c==SPACEBAR){delete v;return false;} /* try again tomorrow */
         }

         //PICK LOCK
         if(method==0)
         {
            if(cr.skill_check(SKILL_SECURITY,DIFFICULTY_AVERAGE))
            {
               switch (fieldskillrate)
               {
                  case FIELDSKILLRATE_FAST:
                     cr.train(SKILL_SECURITY, 25);break;
                  case FIELDSKILLRATE_CLASSIC:
                     cr.train(SKILL_SECURITY, MAX(5 - cr.get_skill(SKILL_SECURITY), 0));break;
                  case FIELDSKILLRATE_HARD:
                     cr.train(SKILL_SECURITY, 0);break;
               }
               set_color(COLOR_WHITE,COLOR_BLACK,1);
               move(16,0);
               addstr(cr.name, gamelog);
               addstr("は車のドアをこじ開けた。", gamelog);
               gamelog.nextMessage();

               getkey();

               entered=true;
            }
            else
            {
               set_color(COLOR_WHITE,COLOR_BLACK,1);
               move(16,0);
               addstr(cr.name, gamelog);
               addstr("は運悪く鍵を外せなかった。", gamelog);
               gamelog.nextMessage();

               getkey();
            }
         }
         //BREAK WINDOW
         if(method==1)
         {
            int difficulty = static_cast<int>(DIFFICULTY_EASY / cr.get_weapon().get_bashstrengthmod()) - windowdamage;

            if(cr.attribute_check(ATTRIBUTE_STRENGTH,difficulty))
            {
               set_color(COLOR_WHITE,COLOR_BLACK,1);
               move(16,0);
               addstr(cr.name, gamelog);
               addstr("は窓を", gamelog);
               if(cr.get_weapon().get_bashstrengthmod()>1)
               {
                  addstr(cr.get_weapon().get_name(2), gamelog);
                  addstr("で", gamelog);
               }
               addstr("壊した。", gamelog);
               gamelog.nextMessage();
               windowdamage=10;

               getkey();

               entered=true;
            }
            else
            {
               set_color(COLOR_WHITE,COLOR_BLACK,1);
               move(16,0);
               addstr(cr.name, gamelog);
               addstr("は窓を", gamelog);
               if(cr.get_weapon().get_bashstrengthmod()>1)
               {
                  addstr(cr.get_weapon().get_name(2), gamelog);
                  addstr("で", gamelog);
               }
               addstr("壊そうとしたがヒビが入っただけだった。", gamelog);
               gamelog.nextMessage();
               windowdamage++;

               getkey();
            }
         }

         //ALARM CHECK
         int y=17;

         if(touchalarm||sensealarm)
         {
            if(!alarmon)
            {
               set_color(COLOR_YELLOW,COLOR_BLACK,1);
               move(y++,0);
               addstr("突然アラームが鳴り始めた!", gamelog);
               gamelog.nextMessage();

               getkey();

               alarmon=true;
            }
         }

         //NOTICE CHECK
         if(!LCSrandom(50)||(!LCSrandom(5)&&alarmon))
         {
            set_color(COLOR_RED,COLOR_BLACK,1);
            move(y++,0);
            addstr(cr.name, gamelog);
            addstr("は通行人に見つかった!", gamelog);
            gamelog.nextMessage();

            getkey();

            //FOOT CHASE
            chaseseq.clean();
            chaseseq.location=location[cr.location]->parent;
            newsstoryst *ns=new newsstoryst;
            ns->type=NEWSSTORY_CARTHEFT;
            newsstory.push_back(ns);
            sitestory=ns;
            makechasers(-1,5);

            if(footchase(cr)){
               mode=GAMEMODE_BASE;
               delete v;return false;} // Switched to return false; this will cause you to try again tomorrow
            else {
               mode=GAMEMODE_BASE;
               delete v;return false;}
         }
      }

      //START CAR
      char keys_in_car=LCSrandom(5)>0,key_search_total=0;
      int key_location=LCSrandom(5),nervous_counter=0;
      //char ignition_progress=0;

      for(bool started=false;!started;)
      {
         nervous_counter++;
         erase();
         set_color(COLOR_WHITE,COLOR_BLACK,1);
         move(0,0);
         addstr("リベラル車泥棒の冒険");
         printcreatureinfo(&cr);
         makedelimiter();

         int y=10;

         set_color(COLOR_WHITE,COLOR_BLACK,0);
         move(y++,0);
         addstr(cr.name, gamelog);
         addstr("は", gamelog);
         addstr(carname, gamelog);
         addstr("のハンドルの下に隠れている。", gamelog);
         gamelog.nextMessage();

         if(alarmon)
         {
            set_color(COLOR_WHITE,COLOR_BLACK,1);
            move(y++,0);
            if(sensealarm)addstr("VIPER");
            else addstr(carname);
            addstr(": ");
            set_color(COLOR_RED,COLOR_BLACK,1);
            if(sensealarm)addstr("車から降りなさい!   <ビー!!> <ビー!!>");
            else addstr("<ビー!!> <ビー!!> <ビー!!> <ビー!!>");
         }

         move((++y)++,0);
         set_color(COLOR_WHITE,COLOR_BLACK,0);
         addstr("A - キーを使わずにエンジンを掛ける");
         set_color(COLOR_WHITE,COLOR_BLACK,0);
         move(y++,0);
         addstr("B - やぶれかぶれでキーを探す");
         move(y++,0);
         if(!sensealarm)addstr("Enter - 引き上げる");
         else {addstr("Enter - VIPERはついに");addstr(cr.name);addstr("をあきらめさせた");}
         y++;

         char method=-1;
         while(method==-1)
         {
            int c=getkey();
            if(c=='a') method=0;
            if(c=='b') method=1;
            if(c=='x'||c==ENTER||c==ESC||c==SPACEBAR){delete v;return false;} // Call it a day and try again tomorrow
         }

         //HOTWIRE CAR
         if(method==0)
         {
            if(cr.skill_check(SKILL_SECURITY,DIFFICULTY_CHALLENGING))
            {
               switch (fieldskillrate)
               {
                  case FIELDSKILLRATE_FAST:
                     cr.train(SKILL_SECURITY, 50);break;
                  case FIELDSKILLRATE_CLASSIC:
                     cr.train(SKILL_SECURITY, MAX(10 - cr.get_skill(SKILL_SECURITY), 0));break;
                  case FIELDSKILLRATE_HARD:
                     cr.train(SKILL_SECURITY, 0);break;
               }
               set_color(COLOR_WHITE,COLOR_BLACK,1);
               move(y++,0);
               addstr(cr.name, gamelog);
               addstr("はエンジンを掛けた!", gamelog);
               gamelog.nextMessage();

               getkey();

               started=true;
            }
            else
            {
               set_color(COLOR_WHITE,COLOR_BLACK,1);
               move(y++,0);
               addstr(cr.name, gamelog);
               int flavor_text;
               if(cr.get_skill(SKILL_SECURITY) < 4)
                  flavor_text = LCSrandom(3);
               else flavor_text = LCSrandom(5);
               switch(flavor_text)
               {
                  case 0:addstr("はイグニッションをいじったが、車は動かなかった。", gamelog);break;
                  case 1:addstr("はステアリングコラムをいじったが、車は動かなかった。", gamelog);break;
                  case 2:addstr("は色々なワイヤーに触れたが、車は動かなかった。", gamelog);break;
                  case 3:addstr("は色々とエンジンを掛けようとしたが、車は動かなかった。", gamelog);break;
                  case 4:addstr("はどうにかしてダッシュライトをつけようとしたが、車は動かなかった。", gamelog);break;
               }
               gamelog.nextMessage();

               getkey();
            }
         }
         //KEYS
         if(method==1)
         {
            int difficulty;
            const char * location;

            if(!keys_in_car)
            {
               difficulty = DIFFICULTY_IMPOSSIBLE;
               location   = "銀河の中、エイリアンと一緒に、マジで";
            }
            else switch(key_location)
            {
            case 0:
            default:
               difficulty = DIFFICULTY_AUTOMATIC;
               location   = "イグニッションの中(チクショウめ)";
               break;
            case 1:
               difficulty = DIFFICULTY_EASY;
               location   = "日よけのアレの上";
               break;
            case 2:
               difficulty = DIFFICULTY_EASY;
               location   = "小物入れ";
               break;
            case 3:
               difficulty = DIFFICULTY_AVERAGE;
               location   = "運転席";
               break;
            case 4:
               difficulty = DIFFICULTY_HARD;
               location   = "後部座席";
               break;
            }
            if(cr.attribute_check(ATTRIBUTE_INTELLIGENCE,difficulty))
            {
               set_color(COLOR_GREEN,COLOR_BLACK,1);
               move(y++,0);
               if(law[LAW_FREESPEECH]==-2)addstr("[やったぞ]! ", gamelog); // Holy car keys Batman!
               else addstr("ヤバイ! ", gamelog);
               addstr(cr.name, gamelog);
               addstr("は", gamelog);
               addstr(location, gamelog);
               addstr("で鍵を見つけた!", gamelog);
               gamelog.nextMessage();

               getkey();

               started=true;
            }
            else
            {
               key_search_total++;
               set_color(COLOR_WHITE,COLOR_BLACK,1);
               move(y++,0);
               addstr(cr.name, gamelog);
               addstr(": <探している> ", gamelog);
               set_color(COLOR_GREEN,COLOR_BLACK,1);
               if(key_search_total==5)
                  addstr("まだここにいるべきか?", gamelog);
               else if(key_search_total==10)
                  addstr("ここにあるとは思えない…", gamelog);
               else if(key_search_total==15)
                  addstr("もしここにあるのならば、もう見つかっているはずだ。", gamelog);
               else if (key_search_total>15)
               {
                  switch(LCSrandom(5))
                  {
                  case 0:addstr("見つからない!", gamelog);break;
                  case 1:addstr("なぜこんなことを?", gamelog);break;
                  case 2:addstr("一体何をしているんだ?", gamelog);break;
                  case 3:addstr("ああ…", gamelog);break;
                  case 4:addstr("逮捕して欲しいのか?", gamelog);break;
                  }
               }
               else
               {
                  switch(LCSrandom(5))
                  {
                     case 0:addstr("ここにあればよいのだが…", gamelog);break;
                     case 1:
                        if(law[LAW_FREESPEECH]==-2)addstr("[まったく]! いったいどこに?!", gamelog);
                        else addstr("畜生め! いったいどこに?!", gamelog);
                        break;
                     case 2:addstr("さあ、出ておいで…", gamelog);break;
                     case 3:
                        if(law[LAW_FREESPEECH]==-2)addstr("[うんざりだ]…", gamelog);
                        else addstr("クソったれ…", gamelog);
                        break;
                     case 4:addstr("鍵なしでエンジンを掛ける技術があれば…", gamelog);break;
                  }
               }
               gamelog.nextMessage();

               getkey();
            }
         }

         //NOTICE CHECK
         if(!started&&(!LCSrandom(50)||(!LCSrandom(5)&&alarmon)))
         {
            set_color(COLOR_RED,COLOR_BLACK,1);
            move(y++,0);
            addstr(cr.name, gamelog);
            addstr("は通行人に見られた!", gamelog);
            gamelog.nextMessage();

            getkey();

            //FOOT CHASE
            chaseseq.clean();
            chaseseq.location=location[cr.location]->parent;
            newsstoryst *ns=new newsstoryst;
            ns->type=NEWSSTORY_CARTHEFT;
            newsstory.push_back(ns);
            sitestory=ns;
            makechasers(-1,5);

            if(footchase(cr)){
               mode=GAMEMODE_BASE;
               delete v;return 0;}
            else {
               mode=GAMEMODE_BASE;
               delete v;return 0;}
         }

         // Nervous message check
         else if (!started&&(LCSrandom(7)+5)<nervous_counter)
         {
            nervous_counter=0;
            move(++y,0);y++;
            set_color(COLOR_YELLOW,COLOR_BLACK,1);
            addstr(cr.name, gamelog);
            switch(LCSrandom(3))
            {
               case 0:addstr("は誰かが携帯電話で話す声を聞いた。", gamelog);break;
               case 1:addstr("はここに長く居ることに不安を感じた。", gamelog);break;
               case 2:addstr("は数ブロック向こうでパトカーが走っているのを見た。", gamelog);break;
            }
            gamelog.nextMessage();

            getkey();
         }
      }

      //CHASE SEQUENCE
         //CAR IS OFFICIAL, THOUGH CAN BE DELETE BY chasesequence()
      addjuice(cr,v->steal_juice(),100);

      vehicle.push_back(v);
      v->add_heat(14+v->steal_extraheat());
      v->set_location(cr.base);
      // Automatically assign this car to this driver, if no other one is present
      if(cr.pref_carid==-1)
      {
         cr.pref_carid = v->id();
         cr.pref_is_driver = true;
      }

      chaseseq.clean();
      chaseseq.location=location[cr.location]->parent;
      int chaselev=!LCSrandom(13-windowdamage);
      if(chaselev>0||(v->vtypeidname()=="POLICECAR"&&LCSrandom(2))) //Identify police cruiser. Temporary solution? -XML
      {
         v->add_heat(10);
         chaselev=1;
         newsstoryst *ns=new newsstoryst;
         ns->type=NEWSSTORY_CARTHEFT;
         newsstory.push_back(ns);
         sitestory=ns;
         makechasers(-1,chaselev);
         if(!chasesequence(cr,*v)) // Caught or killed in the chase. Do not need to delete vehicle.
            return 0;
      }

      return 1;
   }

   return 0;
}

bool carselect(Creature &cr,short &cartype)
{
   cartype=-1;

   vector<int> cart;
   for(int a=0;a<len(vehicletype);a++)
      if(vehicletype[a]->steal_difficultytofind()<10) cart.push_back(a);

   int page=0;

   while(true)
   {
      erase();

      set_color(COLOR_WHITE,COLOR_BLACK,1);
      move(0,0);
      addstr(cr.name);
      addstr("はどのような車を盗もうとするか?");
      set_color(COLOR_WHITE,COLOR_BLACK,0);
      move(1,0);
      addstr("----車種-----------------------------------------無用心な車の見つけ易さ---------");

      int y=2,difficulty;
      for(int p=page*19;p<len(cart)&&p<page*19+19;p++)
      {
         set_color(COLOR_WHITE,COLOR_BLACK,0);
         move(y,0);
         addchar(y+'A'-2);addstr(" - ");
         addstr(vehicletype[cart[p]]->longname());

         move(y++,49);
         difficulty=vehicletype[cart[p]]->steal_difficultytofind();
         switch(difficulty)
         {
            case 0:
               set_color(COLOR_GREEN,COLOR_BLACK,1);
               addstr("単純");
               break;
            case 1:
               set_color(COLOR_CYAN,COLOR_BLACK,1);
               addstr("とても容易");
               break;
            case 2:
               set_color(COLOR_CYAN,COLOR_BLACK,0);
               addstr("容易");
               break;
            case 3:
               set_color(COLOR_BLUE,COLOR_BLACK,1);
               addstr("平均の下");
               break;
            case 4:
               set_color(COLOR_WHITE,COLOR_BLACK,1);
               addstr("平均");
               break;
            case 5:
               set_color(COLOR_WHITE,COLOR_BLACK,0);
               addstr("平均の上");
               break;
            case 6:
               set_color(COLOR_YELLOW,COLOR_BLACK,1);
               addstr("困難");
               break;
            case 7:
               set_color(COLOR_MAGENTA,COLOR_BLACK,0);
               addstr("とても困難");
               break;
            case 8:
               set_color(COLOR_MAGENTA,COLOR_BLACK,1);
               addstr("非常に困難");
               break;
            case 9:
               set_color(COLOR_RED,COLOR_BLACK,0);
               addstr("ほぼ不可能");
               break;
            default:
               set_color(COLOR_RED,COLOR_BLACK,1);
               addstr("不可能");
               break;
         }
      }

      set_color(COLOR_WHITE,COLOR_BLACK,0);
      move(22,0);
      addstr("アルファベットキーで車種を選択する。");
      move(23,0);
      addpagestr();

      int c=getkey();

      //PAGE UP
      if((c==interface_pgup||c==KEY_UP||c==KEY_LEFT)&&page>0) page--;
      //PAGE DOWN
      if((c==interface_pgdn||c==KEY_DOWN||c==KEY_RIGHT)&&(page+1)*19<len(cart)) page++;

      if(c>='a'&&c<='s')
      {
         int p=page*19+c-'a';
         if(p<len(cart))
         {
            cartype=cart[p];
            return true;
         }
      }

      // Too easy to accidentally back out
      // Not a big problem if this page isn't skippable
      // (There's no immediate risk in picking a car)
      // - JDS
      //if(c=='x'||c==ENTER||c==ESC||c==SPACEBAR)break;
   }

   return false;
}

/* get a wheelchair */
void getwheelchair(Creature &cr,char &clearformess)
{
   if(clearformess) erase();
   else makedelimiter();

   if(LCSrandom(2))
   {
      set_color(COLOR_WHITE,COLOR_BLACK,1);
      move(8,1);
      addstr(cr.name, gamelog);
      addstr("は何とか車椅子を手に入れた。", gamelog);

      cr.flag|=CREATUREFLAG_WHEELCHAIR;
   }
   else
   {
      set_color(COLOR_WHITE,COLOR_BLACK,1);
      move(8,1);
      addstr(cr.name, gamelog);
      addstr("は車椅子を手に入れられなかった。明日にしよう…", gamelog);
   }
   gamelog.nextMessage();

   getkey();
}
