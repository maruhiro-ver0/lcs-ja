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

/* unlock attempt */
char unlock(short type,char &actual)
{
   int p;
   int difficulty=0;

   switch(type)
   {
      case UNLOCK_DOOR:
         if(securityable(location[cursite]->type) == 1)
            difficulty=DIFFICULTY_CHALLENGING;
         else if(securityable(location[cursite]->type) > 1)
            difficulty=DIFFICULTY_HARD;
         else
            difficulty=DIFFICULTY_EASY;
         break;
      case UNLOCK_CAGE:       difficulty=DIFFICULTY_VERYEASY;break;
      case UNLOCK_CAGE_HARD:  difficulty=DIFFICULTY_AVERAGE;break;
      case UNLOCK_CELL:       difficulty=DIFFICULTY_FORMIDABLE;break;
      case UNLOCK_ARMORY:     difficulty=DIFFICULTY_HEROIC;break;
      case UNLOCK_SAFE:       difficulty=DIFFICULTY_HEROIC;break;
      case UNLOCK_VAULT:      difficulty=DIFFICULTY_HEROIC;break;
   }

   int maxattack=-1;

   for(p=0;p<6;p++)
   {
      if(activesquad->squad[p]!=NULL)
      {
         if(activesquad->squad[p]->alive)
         {
            if(activesquad->squad[p]->get_skill(SKILL_SECURITY)>maxattack)
            {
               maxattack=activesquad->squad[p]->get_skill(SKILL_SECURITY);
            }
         }
      }
   }

   vector<int> goodp;

   for(p=0;p<6;p++)
   {
      if(activesquad->squad[p]!=NULL)
      {
         if(activesquad->squad[p]->alive)
         {
            if(activesquad->squad[p]->get_skill(SKILL_SECURITY)==maxattack)
            {
               goodp.push_back(p);
            }
         }
      }
   }

   if(len(goodp))
   {
      int p=pickrandom(goodp);

	//lock pick succeeded.
      if(activesquad->squad[p]->skill_check(SKILL_SECURITY,difficulty))
      {
         //skill goes up in proportion to the chance of you failing.
         if(maxattack<=difficulty)
         {
            switch (fieldskillrate)
            {
               case FIELDSKILLRATE_FAST:
                  activesquad->squad[p]->train(SKILL_SECURITY, 10 * difficulty);break;
               case FIELDSKILLRATE_CLASSIC:
                  activesquad->squad[p]->train(SKILL_SECURITY, 1 + (difficulty - maxattack));break;
               case FIELDSKILLRATE_HARD:
                  activesquad->squad[p]->train(SKILL_SECURITY, 0);break;
            }
         }
         clearmessagearea(false);
         set_color(COLOR_WHITE,COLOR_BLACK,1);
         move(16,1);
         addstr(activesquad->squad[p]->name, gamelog);
         switch(type)
         {
            case UNLOCK_DOOR:addstr("は鍵を外した", gamelog);break;
            case UNLOCK_CAGE_HARD:
            case UNLOCK_CAGE:addstr("はケージを開けた", gamelog);break;
            case UNLOCK_SAFE:addstr("は金庫を壊した", gamelog);break;
            case UNLOCK_ARMORY:addstr("は武器庫を開けた", gamelog);break;
            case UNLOCK_CELL:addstr("牢を開けた", gamelog);break;
            case UNLOCK_VAULT:addstr("は金庫室の扉を開けた", gamelog);break;
         }
         addstr("!", gamelog);
         gamelog.newline();
         for(int j=0;j<6;j++) //If people witness a successful unlock, they learn a little bit.
         {
            if(j==p) continue;
            if(activesquad->squad[j]!=NULL&&
               activesquad->squad[j]->alive&&
               activesquad->squad[j]->get_skill(SKILL_SECURITY)<difficulty)
            {
               if(activesquad->squad[j]->alive)
               {
                  switch (fieldskillrate)
                  {
                     case FIELDSKILLRATE_FAST:
                        activesquad->squad[j]->train(SKILL_SECURITY, 5 * difficulty);break;
                     case FIELDSKILLRATE_CLASSIC:
                        activesquad->squad[j]->train(SKILL_SECURITY, difficulty - activesquad->squad[j]->get_skill(SKILL_SECURITY));break;
                     case FIELDSKILLRATE_HARD:
                        activesquad->squad[j]->train(SKILL_SECURITY, 0);break;
                  }
               }
            }
         }

         getkey();

         actual=1;
         return 1;
      }
      else
      {
         clearmessagearea(false);
         set_color(COLOR_WHITE,COLOR_BLACK,1);
         move(16,1);

         int i;
         //gain some experience for failing only if you could have succeeded.
         for(i=0;i<3;i++)
         {
            if(activesquad->squad[p]->skill_check(SKILL_SECURITY,difficulty))
            {
               switch (fieldskillrate)
               {
                  case FIELDSKILLRATE_FAST:
                     activesquad->squad[p]->train(SKILL_SECURITY, 50);break;
                  case FIELDSKILLRATE_CLASSIC:
                     activesquad->squad[p]->train(SKILL_SECURITY, 10);break;
                  case FIELDSKILLRATE_HARD:
                     activesquad->squad[p]->train(SKILL_SECURITY, 10);break;
               }

               addstr(activesquad->squad[p]->name, gamelog);
               addstr("は鍵を外そうとしたが、まったく歯が立たなかった。", gamelog);
               gamelog.newline();
               break;
            }
         }

         if(i==3)
         {
            addstr(activesquad->squad[p]->name, gamelog);
            addstr("は鍵を外せなかった。", gamelog);
            gamelog.newline();
         }

         getkey();

         actual=1;
         return 0;
      }
   }
   else
   {
      clearmessagearea();
      set_color(COLOR_WHITE,COLOR_BLACK,1);
      move(16,1);
      addstr("それをできる者がいない。", gamelog);
      gamelog.newline();

      getkey();
   }

   actual=0;
   return 0;
}


/* bash attempt */
char bash(short type,char &actual)
{
   int difficulty=0,p=0;
   bool crowable=false;

   switch(type)
   {
   case BASH_DOOR:
      if(!securityable(location[cursite]->type))
      {
         difficulty=DIFFICULTY_EASY; // Run down dump
         crowable=true;
      }
      else if(location[cursite]->type!=SITE_GOVERNMENT_PRISON&&
              location[cursite]->type!=SITE_GOVERNMENT_INTELLIGENCEHQ)
      {
         difficulty=DIFFICULTY_CHALLENGING; // Respectable place
         crowable=true;
      }
      else
      {
         difficulty=DIFFICULTY_FORMIDABLE; // Very high security
         crowable=false;
      }
      break;
   }

   if(crowable)
   {
      //if(!squadhasitem(*activesquad,ITEM_WEAPON,WEAPON_CROWBAR))
      //{
         crowable=false;

         for(int p=0;p<6;p++)
         {
            if(activesquad->squad[p]!=NULL)
            {
               if (activesquad->squad[p]->get_weapon().auto_breaks_locks())
                  crowable = true;
            }
         }

         if(!crowable) //didn't find in hands of any squad member
         {
            for(int l=0;l<len(activesquad->loot);l++)
            {
               if(activesquad->loot[l]->is_weapon())
               {
                  Weapon *w = static_cast<Weapon*>(activesquad->loot[l]); //cast -XML
                  if (w->auto_breaks_locks())
                     crowable = true;
               }
            }
         }
      //}
   }

   int maxattack=0, maxp=0;

   if(!crowable)
   {
      for(p=0;p<6;p++)
      {
         if(activesquad->squad[p]!=NULL)
         {
            if(activesquad->squad[p]->alive)
            {
               if(activesquad->squad[p]->get_attribute(ATTRIBUTE_STRENGTH,true)*
                  activesquad->squad[p]->get_weapon().get_bashstrengthmod()>maxattack)
               {
                  maxattack=static_cast<int>(activesquad->squad[p]->get_attribute(ATTRIBUTE_STRENGTH,true)*
                                             activesquad->squad[p]->get_weapon().get_bashstrengthmod());
                  maxp = p;
               }
            }
         }
      }
   }

   difficulty = static_cast<int>(difficulty/activesquad->squad[maxp]->get_weapon().get_bashstrengthmod());

   if(crowable||activesquad->squad[maxp]->attribute_check(ATTRIBUTE_STRENGTH,difficulty))
   {
      clearmessagearea(false);
      set_color(COLOR_WHITE,COLOR_BLACK,1);
      move(16,1);
      addstr(activesquad->squad[maxp]->name, gamelog);
      addstr("は", gamelog);
      switch(type)
      {
      case BASH_DOOR:
         if(crowable) addstr("バールで扉を壊した", gamelog);
         else if(activesquad->squad[maxp]->get_weapon().get_bashstrengthmod()>1)
            addstr("扉を叩き壊した", gamelog);
         else if(activesquad->squad[maxp]->flag&CREATUREFLAG_WHEELCHAIR)
            addstr("扉に体当たりして壊した", gamelog);
         else addstr("扉を蹴り壊した", gamelog);
         break;
      }
      addstr("!", gamelog);
      gamelog.newline();

      getkey();

      int timer = 5;
      if(crowable) timer = 20;

      if(sitealarmtimer<0 || sitealarmtimer>timer)
         sitealarmtimer=timer;
      else sitealarmtimer=0;

      //Bashing doors in secure areas sets off alarms
      if((location[cursite]->type==SITE_GOVERNMENT_PRISON ||
          location[cursite]->type==SITE_GOVERNMENT_INTELLIGENCEHQ) &&
          sitealarm==0)
      {
         sitealarm=1;
         move(17,1);
         set_color(COLOR_RED,COLOR_BLACK,1);
         addstr("アラームが鳴り出した!", gamelog);
         gamelog.newline();

         getkey();
      }

      actual=1;
      return 1;
   }
   else
   {
      clearmessagearea(false);
      set_color(COLOR_WHITE,COLOR_BLACK,1);
      move(16,1);
      addstr(activesquad->squad[maxp]->name, gamelog);
      addstr("は", gamelog);
      switch(type)
      {
         case BASH_DOOR:
            if(activesquad->squad[maxp]->flag&CREATUREFLAG_WHEELCHAIR)
               addstr("扉に体当たりして壊した", gamelog);
            else addstr("扉を蹴り壊した", gamelog);
            break;
      }
      addstr("!", gamelog);
      gamelog.newline();

      getkey();

      if(sitealarmtimer<0) sitealarmtimer=25;
      else if(sitealarmtimer>10) sitealarmtimer-=10;
      else sitealarmtimer=0;

      actual=1;
      return 0;
   }

   actual=0;
   return 0;
}


/* computer hack attempt */
char hack(short type,char &actual)
{
   int difficulty=0;
   int p;

   switch(type)
   {
   case HACK_SUPERCOMPUTER:difficulty=DIFFICULTY_HEROIC;break;
   case HACK_VAULT:difficulty=DIFFICULTY_CHALLENGING;break;
   }

   int maxattack=0,maxblindattack=-3,hacker=-1,blind=-1;

   for(p=0;p<6;p++) if(activesquad->squad[p]!=NULL)
      if(activesquad->squad[p]->alive && activesquad->squad[p]->get_skill(SKILL_COMPUTERS))
      {
         int roll = activesquad->squad[p]->skill_roll(SKILL_COMPUTERS);
         if(!activesquad->squad[p]->special[SPECIALWOUND_RIGHTEYE]&&
            !activesquad->squad[p]->special[SPECIALWOUND_LEFTEYE])
         {  // we got a blind person here
            roll-=3; // blindness handicaps you by 3, highest roll you can get is 15 instead of 18
            if(roll>maxblindattack) maxblindattack=roll,blind=p; // best blind hacker so far
         }
         else
         {  // we got someone who can see here
            if(roll>maxattack) maxattack=roll,hacker=p; // best hacker with eyeballs so far
         }
      }

   if(blind>-1&&(hacker==-1||(maxblindattack>maxattack&&maxblindattack>0)))
      hacker=blind,maxattack=maxblindattack,blind=true; // the best hacker is a blind person
   else if(blind>-1&&hacker==-1&&maxblindattack<=0)
      blind=true; // we only have a blind hacker, and their roll with the handicap is 0 or less
   else blind=false; // either our hacker has eyeballs or there is no hacker at all

   if(hacker > -1)
   {
      activesquad->squad[hacker]->train(SKILL_COMPUTERS,difficulty);

      if(maxattack>difficulty)
      {
         clearmessagearea();
         set_color(COLOR_WHITE,COLOR_BLACK,1);
         move(16,1);
         addstr(activesquad->squad[hacker]->name, gamelog);
         addstr("は", gamelog);
         if(blind)
            addstr("何も見ないで", gamelog);
         switch(type)
         {
         case HACK_SUPERCOMPUTER:addstr("トップシークレットファイルをディスクに焼いた", gamelog);break;
         case HACK_VAULT:addstr("第2層のセキュリティを無効化した", gamelog);break;
         }
         addstr("!", gamelog);
         gamelog.newline();

         getkey();

         actual=1;
         return 1;
      }
      else
      {
         clearmessagearea();
         set_color(COLOR_WHITE,COLOR_BLACK,1);
         move(16,1);
         addstr(activesquad->squad[hacker]->name, gamelog);
         switch(type)
         {
         case HACK_SUPERCOMPUTER:addstr("はスーパーコンピュータのセキュリティを突破", gamelog);break;
         case HACK_VAULT:addstr("は金庫室の電子ロックを解除", gamelog);break;
         }
         if(blind) addstr("する方法を見ることが", gamelog);
         addstr("できなかった。", gamelog);
         gamelog.newline();

         getkey();

         actual=1;
         return 0;
      }
   }
   else
   {
      clearmessagearea();
      set_color(COLOR_WHITE,COLOR_BLACK,1);
      move(16,1);
      addstr("それをできる者がいない。", gamelog);
      gamelog.newline();
      if(blind)
      {  // your only hacker was blind and had a skill roll, after the handicap, of 0 or less
         getkey();

         move(17,1);
         addstr("あなたが送り込んだ盲目のハッカーを含めて。", gamelog);
         gamelog.newline();
      }

      getkey();
   }

   actual=0;
   return 0;
}



/* run a radio broadcast */
char radio_broadcast()
{
   sitealarm=1;

   int enemy=0;
   for(int e=0;e<ENCMAX;e++)
   {
      if(encounter[e].exists&&encounter[e].alive)
      {
         if(encounter[e].align==-1)enemy++;
      }
   }

   if(enemy>0)
   {
      clearmessagearea();
      set_color(COLOR_WHITE,COLOR_BLACK,1);
      move(16,1);
      addstr("保守が放送室に駆けつけてきた。", gamelog);
      move(17,1);
      addstr("放送は不可能だ。", gamelog);
      gamelog.newline();

      getkey();
      return 0;
   }

   criminalizeparty(LAWFLAG_DISTURBANCE);

   clearmessagearea();
   set_color(COLOR_WHITE,COLOR_BLACK,1);
   move(16,1);
   addstr("部隊はマイクを手に取り、", gamelog);
   move(17,1);
   int viewhit=LCSrandom(VIEWNUM);
   switch(viewhit)
   {
      case VIEW_GAY:                    addstr("同性愛者の権利について議論した。", gamelog);break;
      case VIEW_DEATHPENALTY:           addstr("死刑制度について論じた。", gamelog);break;
      case VIEW_TAXES:                  addstr("税法について議論した。", gamelog);break;
      case VIEW_NUCLEARPOWER:           addstr("原子力を批判した。", gamelog);break;
      case VIEW_ANIMALRESEARCH:         addstr("恐るべき動物実験ついて議論した。", gamelog);break;
      case VIEW_POLICEBEHAVIOR:         addstr("警官による暴行の事例を説明した。", gamelog);break;
      case VIEW_TORTURE:                addstr("囚人への虐待と拷問について論じた。", gamelog);break;
      case VIEW_PRISONS:                addstr("刑務所制度の問題点について論じた。", gamelog);break;
      case VIEW_INTELLIGENCE:           addstr("プライバシー法について討論した。", gamelog);break;
      case VIEW_FREESPEECH:             addstr("言論の自由について話をした。", gamelog);break;
      case VIEW_GENETICS:               addstr("遺伝子研究への懸念について論じた。", gamelog);break;
      case VIEW_JUSTICES:               addstr("保守的裁判記録について話をした。", gamelog);break;
      case VIEW_GUNCONTROL:             addstr("銃規制について話をした。", gamelog);break;
      case VIEW_SWEATSHOPS:             addstr("搾取工場の詳細を明らかにした。", gamelog);break;
      case VIEW_POLLUTION:              addstr("工場による汚染のトークショーを行った。", gamelog);break;
      case VIEW_CORPORATECULTURE:       addstr("企業文化に関するジョークを披露した。", gamelog);break;
      case VIEW_CEOSALARY:              addstr("CEOの高額すぎる報酬の例を示した。", gamelog);break;
      case VIEW_WOMEN:                  addstr("中絶について議論した。", gamelog);break;// "Performs an abortion live on the air."
                                                                            // Get [LAWFLAG_SPEECH], [LAWFLAG_MURDER], [LAWFLAG_DISTURBANCE] -- LK
      case VIEW_CIVILRIGHTS:            addstr("アファーマティブ・アクションについて討論した。", gamelog);break;
      case VIEW_DRUGS:                  addstr("薬物について率直な話をした。", gamelog);break;
      case VIEW_IMMIGRATION:            addstr("移民問題について論じた。", gamelog);break;
      case VIEW_MILITARY:               addstr("現代の軍国主義の話をした。", gamelog);break;
      case VIEW_AMRADIO:                addstr("AMラジオショーについて議論した。", gamelog);break;
      case VIEW_CABLENEWS:              addstr("ケーブルニュースの話をした。", gamelog);break;
      case VIEW_LIBERALCRIMESQUAD:      addstr("リベラル・クライム・スコードを人々に知らしめようとした。", gamelog);break;
      default:
      case VIEW_LIBERALCRIMESQUADPOS:   addstr("リベラル・クライム・スコードのすばらしさを称えた。", gamelog);break;
      case VIEW_CONSERVATIVECRIMESQUAD: addstr("コンサバ・クライム・スコードを悪魔化した。", gamelog);break;
   }
   gamelog.newline();

   getkey();

   int segmentpower=0,partysize=squadalive(activesquad),p=0;

   for(p=0;p<6;p++)
   {
      if(activesquad->squad[p]!=NULL)
      {
         if(!activesquad->squad[p]->alive)continue;

         segmentpower+=activesquad->squad[p]->get_attribute(ATTRIBUTE_INTELLIGENCE,true);
         segmentpower+=activesquad->squad[p]->get_attribute(ATTRIBUTE_HEART,true);
         segmentpower+=activesquad->squad[p]->get_attribute(ATTRIBUTE_CHARISMA,true);
         segmentpower+=activesquad->squad[p]->get_skill(SKILL_MUSIC);
         segmentpower+=activesquad->squad[p]->get_skill(SKILL_RELIGION);
         segmentpower+=activesquad->squad[p]->get_skill(SKILL_SCIENCE);
         segmentpower+=activesquad->squad[p]->get_skill(SKILL_BUSINESS);
         segmentpower+=activesquad->squad[p]->get_skill(SKILL_PERSUASION);
         activesquad->squad[p]->train(SKILL_PERSUASION,50);
      }
   }

   // LCS colors enhance the broadcast significantly
   //if(activesquad->stance==SQUADSTANCE_BATTLECOLORS)
   //   segmentpower = (segmentpower * 3) / 2;

   int segmentbonus=segmentpower/4;
   if(partysize>1)segmentpower/=partysize;
   segmentpower+=segmentbonus;

   clearmessagearea();

   set_color(COLOR_WHITE,COLOR_BLACK,1);
   move(16,1);
   if(segmentpower<25)addstr("部隊のトークはまるで狂っているように聞こえた。", gamelog);
   else if(segmentpower<35)addstr("ショーは本当にひどいものだった。", gamelog);
   else if(segmentpower<45)addstr("とても退屈な時間になった。", gamelog);
   else if(segmentpower<55)addstr("平凡なラジオ放送だった。", gamelog);
   else if(segmentpower<70)addstr("ショーはうまくいった。", gamelog);
   else if(segmentpower<85)addstr("部隊のショーはすばらしいものだった。", gamelog);
   else if(segmentpower<100)addstr("それは示唆とユーモアに富んだものになった。", gamelog);
   else addstr("それはAMラジオでかつてない程のすばらしい時間となった。", gamelog);
   gamelog.newline();

   getkey();

   //CHECK PUBLIC OPINION
   change_public_opinion(VIEW_LIBERALCRIMESQUAD,10);
   change_public_opinion(VIEW_LIBERALCRIMESQUADPOS,(segmentpower-50)/2);
   if(viewhit!=VIEW_LIBERALCRIMESQUAD)change_public_opinion(viewhit,(segmentpower-50)/2,1);
   else change_public_opinion(viewhit,segmentpower/2);

   //PRISONER PARTS
   for(p=0;p<6;p++)
   {
      if(activesquad->squad[p]!=NULL)
      {
         if(activesquad->squad[p]->prisoner!=NULL && activesquad->squad[p]->prisoner->alive)
         {
            if(activesquad->squad[p]->prisoner->type==CREATURE_RADIOPERSONALITY)
            {
               viewhit=LCSrandom(VIEWNUM);
               clearmessagearea();

               set_color(COLOR_WHITE,COLOR_BLACK,1);
               move(16,1);
               addstr("人質の", gamelog);
               addstr(activesquad->squad[p]->prisoner->name, gamelog);
               addstr("に", gamelog);
               move(17,1);
               switch(viewhit)
               {
                  case VIEW_GAY:                    addstr("同性愛者の権利について議論をさせた。", gamelog);break;
                  case VIEW_DEATHPENALTY:           addstr("死刑制度について論じさせた。", gamelog);break;
                  case VIEW_TAXES:                  addstr("税法について議論させた。", gamelog);break;
                  case VIEW_NUCLEARPOWER:           addstr("原子力を批判させた。", gamelog);break;
                  case VIEW_ANIMALRESEARCH:         addstr("恐るべき動物実験ついて議論させた。", gamelog);break;
                  case VIEW_POLICEBEHAVIOR:         addstr("警官による暴行の事例を説明させた。", gamelog);break;
                  case VIEW_TORTURE:                addstr("囚人への虐待と拷問について論じさせた。", gamelog);break;
                  case VIEW_PRISONS:                addstr("刑務所制度の問題点について論じさせた。", gamelog);break;
                  case VIEW_INTELLIGENCE:           addstr("プライバシー法について討論させた。", gamelog);break;
                  case VIEW_FREESPEECH:             addstr("言論の自由について話をさせた。", gamelog);break;
                  case VIEW_GENETICS:               addstr("遺伝子研究への懸念について論じさせた。", gamelog);break;
                  case VIEW_JUSTICES:               addstr("保守的裁判記録について話をさせた。", gamelog);break;
                  case VIEW_GUNCONTROL:             addstr("銃規制について話をさせた。", gamelog);break;
                  case VIEW_SWEATSHOPS:             addstr("搾取工場の詳細を明らかにさせた。", gamelog);break;
                  case VIEW_POLLUTION:              addstr("工場による汚染のトークショーを行わせた。", gamelog);break;
                  case VIEW_CORPORATECULTURE:       addstr("企業文化に関するジョークを披露させた。", gamelog);break;
                  case VIEW_CEOSALARY:              addstr("CEOの高額すぎる報酬の例を示させた。", gamelog);break;
                  case VIEW_WOMEN:                  addstr("中絶について議論させた。", gamelog);break;// "Performs an abortion live on the air."
                                                                                      // Get [LAWFLAG_SPEECH], [LAWFLAG_MURDER], [LAWFLAG_DISTURBANCE] -- LK
                  case VIEW_CIVILRIGHTS:            addstr("アファーマティブ・アクションについて討論させた。", gamelog);break;
                  case VIEW_DRUGS:                  addstr("薬物について率直な話をさせた。", gamelog);break;
                  case VIEW_IMMIGRATION:            addstr("移民問題について論じさせた。", gamelog);break;
                  case VIEW_MILITARY:               addstr("現代の軍国主義の話をさせた。", gamelog);break;
                  case VIEW_AMRADIO:                addstr("AMラジオショーについて議論させた。", gamelog);break;
                  case VIEW_CABLENEWS:              addstr("ケーブルニュースの話をさせた。", gamelog);break;
                  case VIEW_LIBERALCRIMESQUAD:      addstr("リベラル・クライム・スコードを人々に知らせさせた。", gamelog);break;
                  default:
                  case VIEW_LIBERALCRIMESQUADPOS:   addstr("リベラル・クライム・スコードのすばらしさを称えさせた。", gamelog);break;
                  case VIEW_CONSERVATIVECRIMESQUAD: addstr("コンサバ・クライム・スコードを悪魔化させた。", gamelog);break;
               }
               gamelog.newline();

               int usegmentpower=10; //FAME BONUS
               usegmentpower+=activesquad->squad[p]->prisoner->get_attribute(ATTRIBUTE_INTELLIGENCE,true);
               usegmentpower+=activesquad->squad[p]->prisoner->get_attribute(ATTRIBUTE_HEART,true);
               usegmentpower+=activesquad->squad[p]->prisoner->get_attribute(ATTRIBUTE_CHARISMA,true);
               usegmentpower+=activesquad->squad[p]->prisoner->get_skill(SKILL_PERSUASION);

               if(viewhit!=VIEW_LIBERALCRIMESQUAD)change_public_opinion(viewhit,(usegmentpower-10)/2,1,80);
               else change_public_opinion(viewhit,usegmentpower/2);

               segmentpower+=usegmentpower;

               getkey();
            }
            else
            {
               clearmessagearea();

               set_color(COLOR_WHITE,COLOR_BLACK,1);
               move(16,1);
               addstr("人質の", gamelog);
               addstr(activesquad->squad[p]->prisoner->name, gamelog);
               addstr("は何も話さなかった。", gamelog);
               gamelog.newline();

               getkey();
            }
         }
      }
   }

   if(sitealienate>=1&&segmentpower>=40)
   {
      sitealienate=0;

      clearmessagearea();

      set_color(COLOR_WHITE,COLOR_BLACK,1);
      move(16,1);
      addstr("局の穏健派はショーを評価した。", gamelog);
      gamelog.newline();
      move(17,1);
      addstr("彼らはもはや敵視していないようだ。", gamelog);
      gamelog.newline();

      getkey();
   }

   //POST-SECURITY BLITZ IF IT SUCKED
   if(segmentpower<90)
   {
      clearmessagearea();

      set_color(COLOR_WHITE,COLOR_BLACK,1);
      move(16,1);
      addstr("放送が終了すると警備員が現れた!", gamelog);
      gamelog.newline();

      getkey();

      int numleft=LCSrandom(8)+2;
      for(int e=0;e<ENCMAX;e++)
      {
         if(!encounter[e].exists)
         {
            makecreature(encounter[e],CREATURE_SECURITYGUARD);
            numleft--;
         }
         if(numleft==0)break;
      }
   }
   else
   {
      clearmessagearea();

      set_color(COLOR_WHITE,COLOR_BLACK,1);
      move(16,1);
      addstr("警備員も部屋でショーに聞き入っていたようだ。", gamelog);
      move(17,1);
      addstr("部隊は脱出することができた。", gamelog);
      gamelog.newline();

      getkey();
   }

   return 1;
}



/* run a tv broadcast */
char news_broadcast()
{
   sitealarm=1;
   int p;

   int enemy=0;
   for(int e=0;e<ENCMAX;e++)
   {
      if(encounter[e].exists&&encounter[e].alive)
      {
         if(encounter[e].align==-1)enemy++;
      }
   }

   if(enemy>0)
   {
      clearmessagearea();
      set_color(COLOR_WHITE,COLOR_BLACK,1);
      move(16,1);
      addstr("保守が放送室に駆けつけてきた。", gamelog);
      move(17,1);
      addstr("放映は不可能だ。", gamelog);
      gamelog.newline();

      getkey();

      return 0;
   }

   criminalizeparty(LAWFLAG_DISTURBANCE);

   clearmessagearea();
   set_color(COLOR_WHITE,COLOR_BLACK,1);
   move(16,1);
   addstr("部隊はカメラの前に立ち、", gamelog);
   move(17,1);
   int viewhit=LCSrandom(VIEWNUM);
   switch(viewhit)
   {
      case VIEW_GAY:                    addstr("同性愛者の権利について議論した。", gamelog);break;
      case VIEW_DEATHPENALTY:           addstr("死刑制度について論じた。", gamelog);break;
      case VIEW_TAXES:                  addstr("税法について議論した。", gamelog);break;
      case VIEW_NUCLEARPOWER:           addstr("原子力を批判した。", gamelog);break;
      case VIEW_ANIMALRESEARCH:         addstr("恐るべき動物実験ついて議論した。", gamelog);break;
      case VIEW_POLICEBEHAVIOR:         addstr("警官による暴行の事例を説明した。", gamelog);break;
      case VIEW_TORTURE:                addstr("囚人への虐待と拷問について論じた。", gamelog);break;
      case VIEW_PRISONS:                addstr("刑務所制度の問題点について論じた。", gamelog);break;
      case VIEW_INTELLIGENCE:           addstr("プライバシー法について討論した。", gamelog);break;
      case VIEW_FREESPEECH:             addstr("言論の自由について話をした。", gamelog);break;
      case VIEW_GENETICS:               addstr("遺伝子研究への懸念について論じた。", gamelog);break;
      case VIEW_JUSTICES:               addstr("保守的裁判記録について話をした。", gamelog);break;
      case VIEW_GUNCONTROL:             addstr("銃規制について話をした。", gamelog);break;
      case VIEW_SWEATSHOPS:             addstr("搾取工場の詳細を明らかにした。", gamelog);break;
      case VIEW_POLLUTION:              addstr("工場による汚染のトークショーを行った。", gamelog);break;
      case VIEW_CORPORATECULTURE:       addstr("企業文化に関するジョークを披露した。", gamelog);break;
      case VIEW_CEOSALARY:              addstr("CEOの高額すぎる報酬の例を示した。", gamelog);break;
      case VIEW_WOMEN:                  addstr("中絶について議論した。", gamelog);break;// "Performs an abortion live on the air."
                                                                            // Get [LAWFLAG_SPEECH], [LAWFLAG_MURDER], [LAWFLAG_DISTURBANCE] -- LK
      case VIEW_CIVILRIGHTS:            addstr("アファーマティブ・アクションについて討論した。", gamelog);break;
      case VIEW_DRUGS:                  addstr("薬物について率直な話をした。", gamelog);break;
      case VIEW_IMMIGRATION:            addstr("移民問題について論じた。", gamelog);break;
      case VIEW_MILITARY:               addstr("現代の軍国主義の話をした。", gamelog);break;
      case VIEW_AMRADIO:                addstr("AMラジオショーについて議論した。", gamelog);break;
      case VIEW_CABLENEWS:              addstr("ケーブルニュースの話をした。", gamelog);break;
      case VIEW_LIBERALCRIMESQUAD:      addstr("リベラル・クライム・スコードを人々に知らしめようとした。", gamelog);break;
      default:
      case VIEW_LIBERALCRIMESQUADPOS:   addstr("リベラル・クライム・スコードのすばらしさを称えた。", gamelog);break;
      case VIEW_CONSERVATIVECRIMESQUAD: addstr("コンサバ・クライム・スコードを悪魔化した。", gamelog);break;
   }
   gamelog.newline();

   getkey();

   int segmentpower=0,partysize=squadalive(activesquad);
   for(p=0;p<6;p++)
   {
      if(activesquad->squad[p]!=NULL)
      {
         if(!activesquad->squad[p]->alive)continue;

         segmentpower+=activesquad->squad[p]->get_attribute(ATTRIBUTE_INTELLIGENCE,true);
         segmentpower+=activesquad->squad[p]->get_attribute(ATTRIBUTE_HEART,true);
         segmentpower+=activesquad->squad[p]->get_attribute(ATTRIBUTE_CHARISMA,true);
         segmentpower+=activesquad->squad[p]->get_skill(SKILL_MUSIC);
         segmentpower+=activesquad->squad[p]->get_skill(SKILL_RELIGION);
         segmentpower+=activesquad->squad[p]->get_skill(SKILL_SCIENCE);
         segmentpower+=activesquad->squad[p]->get_skill(SKILL_BUSINESS);
         segmentpower+=activesquad->squad[p]->get_skill(SKILL_PERSUASION);
         activesquad->squad[p]->train(SKILL_PERSUASION,50);
      }
   }

   // LCS colors enhance the broadcast significantly
   if(activesquad->stance==SQUADSTANCE_BATTLECOLORS)
      segmentpower = (segmentpower * 3) / 2;

   int segmentbonus=segmentpower/4;
   if(partysize>1)segmentpower/=partysize;
   segmentpower+=segmentbonus;

   clearmessagearea();

   set_color(COLOR_WHITE,COLOR_BLACK,1);
   move(16,1);
   if(segmentpower<25)addstr("部隊の映像はまるで狂っているように見えた。", gamelog);
   else if(segmentpower<35)addstr("ショーは本当にひどいものだった。", gamelog);
   else if(segmentpower<45)addstr("とても退屈な時間になった。", gamelog);
   else if(segmentpower<55)addstr("平凡なテレビ放送だった。", gamelog);
   else if(segmentpower<70)addstr("ショーはうまくいった。", gamelog);
   else if(segmentpower<85)addstr("部隊のショーはすばらしいものだった。", gamelog);
   else if(segmentpower<100)addstr("それは示唆とユーモアに富んだものになった。", gamelog);
   else addstr("それはケーブルテレビでかつてない程のすばらしい時間となった。", gamelog);
   gamelog.newline();

   getkey();

   //CHECK PUBLIC OPINION
   change_public_opinion(VIEW_LIBERALCRIMESQUAD,10);
   change_public_opinion(VIEW_LIBERALCRIMESQUADPOS,(segmentpower-50)/10);
   if(viewhit!=VIEW_LIBERALCRIMESQUAD)change_public_opinion(viewhit,(segmentpower-50)/5,1);
   else change_public_opinion(viewhit,segmentpower/10);

   //PRISONER PARTS
   for(p=0;p<6;p++)
   {
      if(activesquad->squad[p]!=NULL)
      {
         if(activesquad->squad[p]->prisoner!=NULL && activesquad->squad[p]->prisoner->alive)
         {
            if(activesquad->squad[p]->prisoner->type==CREATURE_NEWSANCHOR)
            {
               viewhit=LCSrandom(VIEWNUM);
               clearmessagearea();

               set_color(COLOR_WHITE,COLOR_BLACK,1);
               move(16,1);
               addstr("人質の", gamelog);
               addstr(activesquad->squad[p]->prisoner->name, gamelog);
               addstr("に", gamelog);
               move(17,1);
               switch(viewhit)
               {
                  case VIEW_GAY:                    addstr("同性愛者の権利について議論をさせた。", gamelog);break;
                  case VIEW_DEATHPENALTY:           addstr("死刑制度について論じさせた。", gamelog);break;
                  case VIEW_TAXES:                  addstr("税法について議論させた。", gamelog);break;
                  case VIEW_NUCLEARPOWER:           addstr("原子力を批判させた。", gamelog);break;
                  case VIEW_ANIMALRESEARCH:         addstr("恐るべき動物実験ついて議論させた。", gamelog);break;
                  case VIEW_POLICEBEHAVIOR:         addstr("警官による暴行の事例を説明させた。", gamelog);break;
                  case VIEW_TORTURE:                addstr("囚人への虐待と拷問について論じさせた。", gamelog);break;
		            case VIEW_PRISONS:                addstr("刑務所制度の問題点について論じさせた。", gamelog);break;
                  case VIEW_INTELLIGENCE:           addstr("プライバシー法について討論させた。", gamelog);break;
                  case VIEW_FREESPEECH:             addstr("言論の自由について話をさせた。", gamelog);break;
                  case VIEW_GENETICS:               addstr("遺伝子研究への懸念について論じさせた。", gamelog);break;
                  case VIEW_JUSTICES:               addstr("保守的裁判記録について話をさせた。", gamelog);break;
                  case VIEW_GUNCONTROL:             addstr("銃規制について話をさせた。", gamelog);break;
                  case VIEW_SWEATSHOPS:             addstr("搾取工場の詳細を明らかにさせた。", gamelog);break;
                  case VIEW_POLLUTION:              addstr("工場による汚染のトークショーを行わせた。", gamelog);break;
                  case VIEW_CORPORATECULTURE:       addstr("企業文化に関するジョークを披露させた。", gamelog);break;
                  case VIEW_CEOSALARY:              addstr("CEOの高額すぎる報酬の例を示させた。", gamelog);break;
                  case VIEW_WOMEN:                  addstr("中絶について議論させた。", gamelog);break;// "Performs an abortion live on the air."
                                                                                      // Get [LAWFLAG_SPEECH], [LAWFLAG_MURDER], [LAWFLAG_DISTURBANCE] -- LK
                  case VIEW_CIVILRIGHTS:            addstr("アファーマティブ・アクションについて討論させた。", gamelog);break;
                  case VIEW_DRUGS:                  addstr("薬物について率直な話をさせた。", gamelog);break;
                  case VIEW_IMMIGRATION:            addstr("移民問題について論じさせた。", gamelog);break;
                  case VIEW_MILITARY:               addstr("現代の軍国主義の話をさせた。", gamelog);break;
                  case VIEW_AMRADIO:                addstr("AMラジオショーについて議論させた。", gamelog);break;
                  case VIEW_CABLENEWS:              addstr("ケーブルニュースの話をさせた。", gamelog);break;
                  case VIEW_LIBERALCRIMESQUAD:      addstr("リベラル・クライム・スコードを人々に知らせさせた。", gamelog);break;
                  default:
                  case VIEW_LIBERALCRIMESQUADPOS:   addstr("リベラル・クライム・スコードのすばらしさを称えさせた。", gamelog);break;
                  case VIEW_CONSERVATIVECRIMESQUAD: addstr("コンサバ・クライム・スコードを悪魔化させた。", gamelog);break;
               }
               gamelog.newline();

               int usegmentpower=10; //FAME BONUS
               usegmentpower+=activesquad->squad[p]->prisoner->get_attribute(ATTRIBUTE_INTELLIGENCE,true);
               usegmentpower+=activesquad->squad[p]->prisoner->get_attribute(ATTRIBUTE_HEART,true);
               usegmentpower+=activesquad->squad[p]->prisoner->get_attribute(ATTRIBUTE_CHARISMA,true);
               usegmentpower+=activesquad->squad[p]->prisoner->get_skill(SKILL_PERSUASION);

               if(viewhit!=VIEW_LIBERALCRIMESQUAD)change_public_opinion(viewhit,(usegmentpower-10)/2);
               else change_public_opinion(viewhit,usegmentpower/2,1);

               segmentpower+=usegmentpower;

               getkey();
            }
            else
            {
               clearmessagearea();

               set_color(COLOR_WHITE,COLOR_BLACK,1);
               move(16,1);
               addstr("人質の", gamelog);
               addstr(activesquad->squad[p]->prisoner->name, gamelog);
               addstr("は何もしようとしなかった。", gamelog);
               gamelog.newline();

               getkey();
            }
         }
      }
   }

   if(sitealienate>=1&&segmentpower>=40)
   {
      sitealienate=0;

      clearmessagearea();

      set_color(COLOR_WHITE,COLOR_BLACK,1);
      move(16,1);
      addstr("局の穏健派はショーを評価した。", gamelog);
      gamelog.newline();
      move(17,1);
      addstr("彼らはもはや敵視していないようだ。", gamelog);
      gamelog.newline();

      getkey();
   }

   //POST - SECURITY BLITZ IF IT SUCKED
   if(segmentpower<85 && segmentpower>=25)
   {
      clearmessagearea();

      set_color(COLOR_WHITE,COLOR_BLACK,1);
      move(16,1);
      addstr("放送が終了すると警備員が現れた!", gamelog);
      gamelog.newline();

      getkey();

      int numleft=LCSrandom(8)+2;
      for(int e=0;e<ENCMAX;e++)
      {
         if(!encounter[e].exists)
         {
            makecreature(encounter[e],CREATURE_SECURITYGUARD);
            numleft--;
         }
         if(numleft==0)break;
      }
   }
   else
   {
      clearmessagearea();

      set_color(COLOR_WHITE,COLOR_BLACK,1);
      move(16,1);
      addstr("ショーはとても", gamelog);
      if(segmentpower<50)
         addstr("面白かった", gamelog);
      else
         addstr("素晴らしかった", gamelog);
      addstr("ので、警備員も部屋で見入っていたようだ。", gamelog);
      move(17,1);
      addstr("部隊は脱出することができた。", gamelog);
      gamelog.newline();

      getkey();
   }

   return 1;
}



/* rescues people held at the activeparty's current location */
void partyrescue(short special)
{
   int freeslots=0,p,pl;
   for(p=0;p<6;p++)
   {
      if(activesquad->squad[p]==NULL)freeslots++;
   }
   int hostslots=0;
   for(p=0;p<6;p++)
   {
      if(activesquad->squad[p]!=NULL)
      {
         if(activesquad->squad[p]->alive&&activesquad->squad[p]->prisoner==NULL)
         {
            hostslots++;
         }
      }
   }

   vector<Creature*> waiting_for_rescue;
   for(pl=0;pl<len(pool);pl++)
   {
      if(pool[pl]->location==cursite&&
         !(pool[pl]->flag & CREATUREFLAG_SLEEPER)&&
         !(special==SPECIAL_PRISON_CONTROL_LOW&&!(pool[pl]->sentence>0&&!pool[pl]->deathpenalty))&& //Low is for normal time-limited sentences.
         !(special==SPECIAL_PRISON_CONTROL_MEDIUM&&!(pool[pl]->sentence<0&&!pool[pl]->deathpenalty))&& //Medium is for life sentences.
         !(special==SPECIAL_PRISON_CONTROL_HIGH&&!pool[pl]->deathpenalty)) //High is for death sentences.
            waiting_for_rescue.push_back(pool[pl]);
   }

   for(pl=0;pl<len(waiting_for_rescue);pl++)
   {
      if(LCSrandom(2)&&freeslots)
      {
         for(int p=0;p<6;p++)
         {
            if(activesquad->squad[p]==NULL)
            {
               activesquad->squad[p]=waiting_for_rescue[pl];
               activesquad->squad[p]->squadid=activesquad->id;
               criminalize(*activesquad->squad[p],LAWFLAG_ESCAPED);
               activesquad->squad[p]->flag|=CREATUREFLAG_JUSTESCAPED;
               break;
            }
         }
         hostslots++;
         freeslots--;

         clearmessagearea();

         set_color(COLOR_WHITE,COLOR_BLACK,1);
         move(16,1);
         addstr("あなたは", gamelog);
         addstr(waiting_for_rescue[pl]->name, gamelog);
         addstr("を保守から救った。", gamelog);
         gamelog.newline();

         printparty();

         getkey();

         waiting_for_rescue[pl]->location=-1;
         waiting_for_rescue[pl]->base=activesquad->squad[0]->base;

         waiting_for_rescue.erase(waiting_for_rescue.begin()+pl);
         --pl;
      }
   }
   for(pl=0;pl<len(waiting_for_rescue);pl++)
   {
      if(hostslots)
      {
         for(int p=0;p<6;p++)
         {
            if(activesquad->squad[p]!=NULL)
            {
               if(activesquad->squad[p]->alive&&activesquad->squad[p]->prisoner==NULL)
               {
                  activesquad->squad[p]->prisoner=waiting_for_rescue[pl];
                  waiting_for_rescue[pl]->squadid=activesquad->id;
                  criminalize(*waiting_for_rescue[pl],LAWFLAG_ESCAPED);
                  waiting_for_rescue[pl]->flag|=CREATUREFLAG_JUSTESCAPED;

                  clearmessagearea();

                  set_color(COLOR_WHITE,COLOR_BLACK,1);
                  move(16,1);
                  addstr("あなたは", gamelog);
                  addstr(waiting_for_rescue[pl]->name, gamelog);
                  addstr("を保守から救った。", gamelog);
                  gamelog.newline();

                  getkey();

                  clearmessagearea();
                  move(16,1);
                  addstr(waiting_for_rescue[pl]->name, gamelog);
                  addstr("は", gamelog);
                  switch(LCSrandom(3))
                  {
                     case 0:addstr("拷問を受けていた", gamelog);break;
                     case 1:addstr("ひどく殴られていた", gamelog);break;
                     case 2:addstr("ハンガーストライキをしていた", gamelog);break;
                  }
                  move(17,1);
                  addstr("ので、", gamelog);
                  addstr(activesquad->squad[p]->name, gamelog);
                  addstr("はリベラルを運ばなければならない。", gamelog);
                  gamelog.newline();

                  waiting_for_rescue[pl]->location=-1;
                  waiting_for_rescue[pl]->base=activesquad->squad[p]->base;

                  printparty();

                  getkey();

                  waiting_for_rescue.erase(waiting_for_rescue.begin()+pl);
                  --pl;
                  break;
               }
            }
         }

         hostslots--;
      }
      if(!hostslots)break;
   }

   if(len(waiting_for_rescue)==1)
   {
      clearmessagearea();
      set_color(COLOR_YELLOW,COLOR_BLACK,1);
      move(16,1);
      addstr("誰も", gamelog);
      addstr(waiting_for_rescue[0]->name, gamelog);
      addstr("を運べない。", gamelog);
      gamelog.newline();
      set_color(COLOR_WHITE,COLOR_BLACK,1);
      move(17,1);
      addstr("後でまだ戻ってこなければならないだろう。", gamelog);
      gamelog.newline();

      getkey();
   }
   else if(len(waiting_for_rescue)>1)
   {
      clearmessagearea();
      set_color(COLOR_YELLOW,COLOR_BLACK,1);
      move(16,1);
      addstr("誰も残された者たちを運べない。", gamelog);
      gamelog.newline();
      set_color(COLOR_WHITE,COLOR_BLACK,1);
      move(17,1);
      addstr("後でまだ戻ってこなければならないだろう。", gamelog);
      gamelog.newline();

      getkey();
   }
}



/* everybody reload! */
void reloadparty(bool wasteful)
{
   for(int p=0;p<6;p++)
   {
      if(activesquad->squad[p]==NULL)continue;
      if(!activesquad->squad[p]->alive)continue;

      if(activesquad->squad[p]->has_thrown_weapon)
      {
         activesquad->squad[p]->ready_another_throwing_weapon();
      }
      else if(activesquad->squad[p]->can_reload())
      {
         activesquad->squad[p]->reload(wasteful);
      }
   }
}
