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

/* monthly - hold trial on a liberal */
void trial(Creature &g)
{
   music.play(MUSIC_TRIAL);
   // If their old base is no longer under LCS control, wander back to the
   // homeless shelter instead.
   if(location[g.base]->renting<0) g.base=find_homeless_shelter(g);
   g.location=g.base;
   bool breaker[LAWFLAGNUM]={0};

   clear();

   set_color(COLOR_WHITE,COLOR_BLACK,1);
   move(1,1);
   addstr(g.name, gamelog);
   addstr("の裁判が始まった。", gamelog);
   gamelog.newline();

   getkey();

   set_color(COLOR_WHITE,COLOR_BLACK,0);

   if(!iscriminal(g)) criminalize(g,LAWFLAG_LOITERING);

   int typenum=0,scarefactor=0;
   // *JDS* Scarefactor is the severity of the case against you; if you're a really
   // nasty person with a wide variety of major charges against you, then scarefactor
   // can get up there

   for(int i=0;i<LAWFLAGNUM;i++) if(g.crimes_suspected[i])
   {
      typenum++;
      scarefactor+=lawflagheat(i)*g.crimes_suspected[i];
      breaker[i]=1;
   }

   //CHECK FOR SLEEPERS
   bool autoconvict=0;
   Creature *sleeperjudge=NULL;
   Creature *sleeperlawyer=NULL;
   int maxsleeperskill=0;
   for(int p=0;p<len(pool);p++)
      if(pool[p]->alive&&(pool[p]->flag&CREATUREFLAG_SLEEPER)&&location[pool[p]->location]->city==location[g.location]->city)
      {
         if(pool[p]->type==CREATURE_JUDGE_CONSERVATIVE||pool[p]->type==CREATURE_JUDGE_LIBERAL)
            if(pool[p]->infiltration*100>=LCSrandom(100)) sleeperjudge=pool[p];
         if(pool[p]->type==CREATURE_LAWYER)
            if(pool[p]->get_skill(SKILL_LAW)+pool[p]->get_skill(SKILL_PERSUASION)>=maxsleeperskill)
            {
               sleeperlawyer=pool[p];
               maxsleeperskill=pool[p]->get_skill(SKILL_LAW)+sleeperlawyer->get_skill(SKILL_PERSUASION);
            }
      }

   //STATE CHARGES
   set_color(COLOR_WHITE,COLOR_BLACK,0);
   move(3,1);
   if(sleeperjudge)
   {
      addstr("潜伏者", gamelog);
      addstr(sleeperjudge->name, gamelog);
      addstr("は笑みを隠しながら罪状を読み上げた:", gamelog);
      g.confessions=0; //Made sleeper judge prevent these lunatics from testifying
   }
   else addstr("判事は罪状を読み上げた:", gamelog);
   gamelog.newline();
   set_color(COLOR_RED,COLOR_BLACK,1);
   move(5,1);
   addstr("被告人", gamelog);
   addstr(g.propername, gamelog);
   addstr("には", gamelog);
   int x=2,y=5;
   while((typenum--)>0)
   {
      if((x++)>=2) { x=0; move(++y,1); }
      //////////////////////////////////////////////////////////////////////////
      //                                Treason                               //
      //////////////////////////////////////////////////////////////////////////
      // Technically, treason is exposing state secrets, or somesuch.         //
      // Illegal Immigrants cannot commit treason, because treason can only   //
      // be committed by `those owing allegiance to the United States`.       //
      //////////////////////////////////////////////////////////////////////////

      // The above is already respected by LCS; treason occurs from exposing
      // intelligence secrets, and illegal immigrants are not taken to trial.
      //    - Jonathan S. Fox

      // Oh, right. Forgot about that. Even if the law is L+?
      if(breaker[LAWFLAG_TREASON])
      {
         if(g.crimes_suspected[LAWFLAG_TREASON]>1)
         {
            addstr(g.crimes_suspected[LAWFLAG_TREASON], gamelog);
            addstr("件の", gamelog);
         }
         addstr("国家反逆", gamelog);
         breaker[LAWFLAG_TREASON]=0;
      }
      else if(breaker[LAWFLAG_TERRORISM])
      {
         if(g.crimes_suspected[LAWFLAG_TERRORISM]>1)
         {
            addstr(g.crimes_suspected[LAWFLAG_TERRORISM], gamelog);
            addstr("件の", gamelog);
         }
         addstr("テロ", gamelog);
         breaker[LAWFLAG_TERRORISM]=0;
      }
      else if(breaker[LAWFLAG_MURDER])//XXX: How about the addition of a `manslaughter` charge? -- LK
      {                               //     Manslaughter is murder without forethought or malice, IIRC. -- LK
                                      // Well, I can't think of an instance of this in LCS besides fruit stand employees. -Fox
                                      // Possibly people you accidentally kill when shooting at conservatives. -- LK
         if(g.crimes_suspected[LAWFLAG_MURDER]>1)
         {
            addstr(g.crimes_suspected[LAWFLAG_MURDER], gamelog);
            addstr("件の", gamelog);
         }
         addstr("殺人", gamelog);
         breaker[LAWFLAG_MURDER]=0;
      }
      else if(breaker[LAWFLAG_KIDNAPPING])
      {
         if(g.crimes_suspected[LAWFLAG_KIDNAPPING]>1)
         {
            addstr(g.crimes_suspected[LAWFLAG_KIDNAPPING], gamelog);
            addstr("件の", gamelog);
         }
         addstr("誘拐", gamelog);
         breaker[LAWFLAG_KIDNAPPING]=0;
      }
      else if(breaker[LAWFLAG_BANKROBBERY])
      {
         if(g.crimes_suspected[LAWFLAG_BANKROBBERY]>1)
         {
            addstr(g.crimes_suspected[LAWFLAG_BANKROBBERY], gamelog);
            addstr("件の", gamelog);
         }
         addstr("銀行強盗", gamelog);
         breaker[LAWFLAG_BANKROBBERY]=0;
      }
      else if(breaker[LAWFLAG_ARSON])
      {
         if(g.crimes_suspected[LAWFLAG_ARSON]>1)
         {
            addstr(g.crimes_suspected[LAWFLAG_ARSON], gamelog);
            addstr("件の", gamelog);
         }
         addstr("放火", gamelog);
         breaker[LAWFLAG_ARSON]=0;
      }
      else if(breaker[LAWFLAG_BURNFLAG] && law[LAW_FLAGBURNING] <= 0)
      {
         if(g.crimes_suspected[LAWFLAG_BURNFLAG]>1)
         {
            addstr(g.crimes_suspected[LAWFLAG_BURNFLAG]);
            addstr("件の", gamelog);
         }
         if(law[LAW_FLAGBURNING]==-2)
            addstr("国旗不敬", gamelog);
         else if(law[LAW_FLAGBURNING]==-1)
            addstr("国旗焼却罪", gamelog);
         else if(law[LAW_FLAGBURNING]==0)
            addstr("国旗焼却", gamelog);
         breaker[LAWFLAG_BURNFLAG]=0;
      }
      else if(breaker[LAWFLAG_SPEECH])
      {
         if(g.crimes_suspected[LAWFLAG_SPEECH]>1)
         {
            addstr(g.crimes_suspected[LAWFLAG_SPEECH], gamelog);
            addstr("件の", gamelog);
         }
         addstr("煽動", gamelog);
         breaker[LAWFLAG_SPEECH]=0;
      }
      else if(breaker[LAWFLAG_BROWNIES])
      {
         if(g.crimes_suspected[LAWFLAG_BROWNIES]>1)
         {
            addstr(g.crimes_suspected[LAWFLAG_BROWNIES], gamelog);
            addstr("件の", gamelog);
         }
         addstr("違法薬物取引", gamelog);
         breaker[LAWFLAG_BROWNIES]=0;
         //x=2;
      }
      else if(breaker[LAWFLAG_ESCAPED])
      {
         if(g.crimes_suspected[LAWFLAG_ESCAPED]>1)
         {
            addstr(g.crimes_suspected[LAWFLAG_ESCAPED], gamelog);
            addstr("件の", gamelog);
         }
         addstr("脱獄", gamelog);
         breaker[LAWFLAG_ESCAPED]=0;
         //autoconvict=1; // *Impossible* to beat this charge if this line isn't commented out
      }
      else if(breaker[LAWFLAG_HELPESCAPE])
      {
         if(g.crimes_suspected[LAWFLAG_HELPESCAPE]>1)
         {
            addstr(g.crimes_suspected[LAWFLAG_HELPESCAPE], gamelog);
            addstr("件の", gamelog);
         }
         addstr("逃走援助", gamelog);
         breaker[LAWFLAG_HELPESCAPE]=0;
         x=2;
      }
      else if(breaker[LAWFLAG_JURY])
      {
         if(g.crimes_suspected[LAWFLAG_JURY]>1)
         {
            addstr(g.crimes_suspected[LAWFLAG_JURY], gamelog);
            addstr("件の", gamelog);
         }
         addstr("陪審員買収", gamelog);
         breaker[LAWFLAG_JURY]=0;
      }
      else if(breaker[LAWFLAG_RACKETEERING])
      {
         addstr("詐欺", gamelog);
         breaker[LAWFLAG_RACKETEERING]=0;
      }
      else if(breaker[LAWFLAG_EXTORTION])
      {
         if(g.crimes_suspected[LAWFLAG_EXTORTION]>1)
         {
            addstr(g.crimes_suspected[LAWFLAG_EXTORTION], gamelog);
            addstr("件の", gamelog);
         }
         addstr("恐喝", gamelog);
         breaker[LAWFLAG_EXTORTION]=0;
      }
      else if(breaker[LAWFLAG_ARMEDASSAULT])
      {
         if(g.crimes_suspected[LAWFLAG_ARMEDASSAULT]>1)
         {
            addstr(g.crimes_suspected[LAWFLAG_ARMEDASSAULT], gamelog);
            addstr("件の", gamelog);
         }
         addstr("銃器使用", gamelog);
         breaker[LAWFLAG_ARMEDASSAULT]=0;
      }
      else if(breaker[LAWFLAG_ASSAULT])
      {
         if(g.crimes_suspected[LAWFLAG_ASSAULT]>1)
         {
            addstr(g.crimes_suspected[LAWFLAG_ASSAULT], gamelog);
            addstr("件の", gamelog);
         }
         addstr("武器使用", gamelog);
         breaker[LAWFLAG_ASSAULT]=0;
      }
      else if(breaker[LAWFLAG_CARTHEFT])
      {
         if(g.crimes_suspected[LAWFLAG_CARTHEFT]>1)
         {
            addstr(g.crimes_suspected[LAWFLAG_CARTHEFT], gamelog);
            addstr("件の", gamelog);
         }
         addstr("自動車窃盗", gamelog);// If chase lasts more than 20 `turns` then
         breaker[LAWFLAG_CARTHEFT]=0;// this should be `Grand Theft Auto` -- LK
      }                              // We'll just make it grand theft auto anyway :) -Fox
      else if(breaker[LAWFLAG_CCFRAUD])
      {
         if(g.crimes_suspected[LAWFLAG_CCFRAUD]>1)
         {
            addstr(g.crimes_suspected[LAWFLAG_CCFRAUD], gamelog);
            addstr("件の", gamelog);
         }
         addstr("カード番号不正取得", gamelog);
         breaker[LAWFLAG_CCFRAUD]=0;
      }
      else if(breaker[LAWFLAG_THEFT])
      {
         if(g.crimes_suspected[LAWFLAG_THEFT]>1)
         {
            addstr(g.crimes_suspected[LAWFLAG_THEFT], gamelog);
            addstr("件の", gamelog);
         }
         addstr("窃盗", gamelog);
         breaker[LAWFLAG_THEFT]=0;
      }
      else if(breaker[LAWFLAG_PROSTITUTION])
      {
         if(g.crimes_suspected[LAWFLAG_PROSTITUTION]>1)
         {
            addstr(g.crimes_suspected[LAWFLAG_PROSTITUTION], gamelog);
            addstr("件の", gamelog);
         }
         addstr("売春", gamelog);
         breaker[LAWFLAG_PROSTITUTION]=0;
      }
      else if(breaker[LAWFLAG_HIREILLEGAL])
      {
         if(g.crimes_suspected[LAWFLAG_HIREILLEGAL]>1)
         {
            addstr(g.crimes_suspected[LAWFLAG_HIREILLEGAL], gamelog);
            addstr("件の", gamelog);
            addstr((law[LAW_IMMIGRATION]<1?"不法移民雇用":"不法雇用"), gamelog);
         }
         else addstr((law[LAW_IMMIGRATION]<1?"不法移民雇用":"不法雇用"), gamelog);
         breaker[LAWFLAG_HIREILLEGAL]=0;
         x=2;
      }
      /*else if(breaker[LAWFLAG_GUNUSE])
      {
         if(g.crimes_suspected[LAWFLAG_GUNUSE]>1)
         {
            addstr(g.crimes_suspected[LAWFLAG_GUNUSE]);
            addstr(" counts of ");
         }
         addstr("firing an illegal weapon");
         breaker[LAWFLAG_GUNUSE]=0;
         x=2;
      }
      else if(breaker[LAWFLAG_GUNCARRY])
      {
         if(g.crimes_suspected[LAWFLAG_GUNCARRY]>1)
         {
            addstr(g.crimes_suspected[LAWFLAG_GUNCARRY]);
            addstr(" counts of ");
         }
         addstr("possession of an illegal weapon");
         breaker[LAWFLAG_GUNCARRY]=0;
         x=2;
      }*/
      else if(breaker[LAWFLAG_COMMERCE])
      {
         if(g.crimes_suspected[LAWFLAG_COMMERCE]>1)
         {
            addstr(g.crimes_suspected[LAWFLAG_COMMERCE], gamelog);
            addstr("件の", gamelog);
         }
         addstr("業務妨害", gamelog);
         breaker[LAWFLAG_COMMERCE]=0;
         x=2;
      }
      else if(breaker[LAWFLAG_INFORMATION])
      {
         if(g.crimes_suspected[LAWFLAG_INFORMATION]>1)
         {
            addstr(g.crimes_suspected[LAWFLAG_INFORMATION], gamelog);
            addstr("件の", gamelog);
         }
         addstr("情報システムへの違法アクセス", gamelog);
         breaker[LAWFLAG_INFORMATION]=0;
         x=2;
      }
      else if(breaker[LAWFLAG_BURIAL])
      {
         if(g.crimes_suspected[LAWFLAG_BURIAL]>1)
         {
            addstr(g.crimes_suspected[LAWFLAG_BURIAL], gamelog);
            addstr("件の", gamelog);
         }
         addstr("死体遺棄", gamelog);
         breaker[LAWFLAG_BURIAL]=0;
      }
      else if(breaker[LAWFLAG_BREAKING])
      {
         if(g.crimes_suspected[LAWFLAG_BREAKING]>1)
         {
            addstr(g.crimes_suspected[LAWFLAG_BREAKING], gamelog);
            addstr("件の", gamelog);
         }
         addstr("不法侵入", gamelog);
         breaker[LAWFLAG_BREAKING]=0;
      }
      else if(breaker[LAWFLAG_VANDALISM])
      {
         if(g.crimes_suspected[LAWFLAG_VANDALISM]>1)
         {
            addstr(g.crimes_suspected[LAWFLAG_VANDALISM], gamelog);
            addstr("件の", gamelog);
         }
         addstr("器物損壊", gamelog);
         breaker[LAWFLAG_VANDALISM]=0;
      }
      else if(breaker[LAWFLAG_RESIST])
      {
         addstr("逮捕抵抗", gamelog);
         breaker[LAWFLAG_RESIST]=0;
      }
      else if(breaker[LAWFLAG_DISTURBANCE])
      {
         if(g.crimes_suspected[LAWFLAG_DISTURBANCE]>1)
         {
            addstr(g.crimes_suspected[LAWFLAG_DISTURBANCE], gamelog);
            addstr("件の", gamelog);
         }
         addstr("治安妨害", gamelog);
         breaker[LAWFLAG_DISTURBANCE]=0;
      }
      else if(breaker[LAWFLAG_PUBLICNUDITY])
      {
         if(g.crimes_suspected[LAWFLAG_PUBLICNUDITY]>1)
         {
            addstr(g.crimes_suspected[LAWFLAG_PUBLICNUDITY], gamelog);
            addstr("件の", gamelog);
         }
         addstr("公然猥褻", gamelog);
         breaker[LAWFLAG_PUBLICNUDITY]=0;
      }
      else if(breaker[LAWFLAG_LOITERING])
      {
         addstr("浮浪", gamelog);
         breaker[LAWFLAG_LOITERING]=0;
      }

      if(typenum>1) addstr("、", gamelog);
      if(typenum==1) addstr("、および", gamelog);
      if(typenum==0) addstr("の容疑がある。", gamelog);

      getkey();
   }
   gamelog.newline();

   if(g.confessions)
   {
      move(y+=2,1);

      if(g.confessions>1)
      {
         addstr(g.confessions, gamelog);
         addstr("人のLCS正式メンバーは", gamelog);
      }
      else addstr("LCS正式メンバーは", gamelog);
      addstr(g.name, gamelog);
      addstr("について不利な証言をした。", gamelog);
      gamelog.newline();

      getkey();
   }

   //CHOOSE DEFENSE
   set_color(COLOR_WHITE,COLOR_BLACK,0);
   move(y+2,1);
   addstr("どのように弁護する?");

   char attorneyname[200];
   unsigned long oldseed[RNG_SIZE];
   copyRNG(oldseed,seed);
   copyRNG(seed,attorneyseed);
   generate_name(attorneyname);
   copyRNG(seed,oldseed);

   y+=4;
   move(y++,1);
   addstr("A - 官選弁護士を使う");
   move(y++,1);
   addstr("B - 自己弁護する!");
   move(y++,1);
   addstr("C - 罪を認める");
   if(ledger.get_funds()<5000) set_color(COLOR_BLACK,COLOR_BLACK,1);
   move(y++,1);
   addstr("D - $5000でリベラル派弁護士の");
   addstr(attorneyname);
   addstr("雇う");
   if(sleeperlawyer)
   {
      set_color(COLOR_WHITE,COLOR_BLACK,0);
      move(y++,1);
      addstr("E - 潜伏者の");
      addstr(sleeperlawyer->name);
      addstr("の推薦するボランティア法律家を受け入れる");
   }
   if(ledger.get_funds()<5000) set_color(COLOR_WHITE,COLOR_BLACK,0);

   //SAV - added in display of skills and relevant attributes to help
   // decide when to defend self.
   move(++y,5);
   addstr("心:   ");
   addstr(g.get_attribute(ATTRIBUTE_HEART,true));
   move(y,25);
   addstr("説得: ");
   addstr(g.get_skill(SKILL_PERSUASION));
   move(++y,5);
   addstr("魅力: ");
   addstr(g.get_attribute(ATTRIBUTE_CHARISMA,true));
   move(y++,25);
   addstr("法律: ");
   addstr(g.get_skill(SKILL_LAW));
   move(y++,5);
   addstr("知識: ");
   addstr(g.get_attribute(ATTRIBUTE_INTELLIGENCE,true));
   // End SAV's adds

   short defense;
   int c;
   while(true)
   {
      c=getkey();
      if(c=='a') { defense=0; break; }
      if(c=='b') { defense=1; break; }
      if(c=='c') { defense=2; break; }
      if(c=='d'&&ledger.get_funds()>=5000)
      {
         ledger.subtract_funds(5000,EXPENSE_LEGAL);
         defense=3;
         break;
      }
      if(c=='e'&&sleeperlawyer)
      {
         defense=4;
         strcpy(attorneyname,sleeperlawyer->name);
         break;
      }
   }

   //TRIAL
   if(defense!=2)
   {
      int prosecution=0;
      clear();

      set_color(COLOR_WHITE,COLOR_BLACK,1);
      move(1,1);
      addstr(g.name, gamelog);
      addstr("が法廷に立つ。");

      //TRIAL MESSAGE
      set_color(COLOR_WHITE,COLOR_BLACK,0);
      move(3,1);
      addstr("裁判が始まった。最初は陪審員の選任だ。", gamelog);
      gamelog.newline();

      getkey();

      //JURY MAKEUP MESSAGE
      set_color(COLOR_WHITE,COLOR_BLACK,0);
      move(5,1);
      int jury=LCSrandom(61)-(60*publicmood(-1))/100; // Political leanings of the population determine your jury
      if(sleeperjudge) jury-=20;
      if(defense==3) // Hired $5000 ace attorney
      {
         if(LCSrandom(10))
         {
            addstr(attorneyname, gamelog);
            addstr("は陪審員を", gamelog);
            addstr(g.name, gamelog);
            addstr("にとって有利な状況に持ち込んだ!", gamelog);
            gamelog.newline();
            if(jury>0) jury=0;
            jury-=30;
         }
         else
         {
            set_color(COLOR_RED,COLOR_BLACK,1);
            addstr(attorneyname, gamelog);
            addstr("の保守派の大敵が検察だ!!!", gamelog);
            gamelog.newline();
            jury=0;
            prosecution+=100; // DUN DUN DUN!!
         }
      }
      else if(jury<=-29)
      {
         set_color(COLOR_GREEN,COLOR_BLACK,1);
         switch(LCSrandom(4))
         {
            case 0:addstr("陪審員の一人は");addstr(g.name);addstr("の子供時代からの親友だ。", gamelog);break;
            case 1:addstr("陪審員は燃えるリベラルだ。", gamelog);break;
            case 2:addstr("陪審員の何人かはほぼ社会主義者だ。", gamelog);break;
            case 3:addstr("陪審員の一人は誰も見ていないとき秘密のリベラル・ハンドサインをした。", gamelog);break;
         }
         gamelog.newline();
      }
      else if(jury<=-15) addstr("陪審員はややリベラル寄りだ。", gamelog);
      else if(jury<15) addstr("陪審員はほぼ穏健派だ。", gamelog);
      else if(jury<29) addstr("陪審員はやや保守的だ。", gamelog);
      else
      {
         set_color(COLOR_YELLOW,COLOR_BLACK,1);
         switch(LCSrandom(4))
         {
            case 0:addstr("結成以来これほど保守派の陪審員が集まったことはない。", gamelog);break;
            case 1:addstr("陪審員の一人は保守の活動家だ。", gamelog);break;
            case 2:addstr("陪審員の何人かはKKKのメンバーだ。", gamelog);break;
            case 3:addstr("陪審員はぞっとするほど保守的だ。", gamelog);break;
         }
      }
      gamelog.newline();

      // Debug jury bias
      #ifdef SHOWMECHANICS
      {
         addstr(" (");
         if(jury>=0) addchar('+');
         addstr(jury);
         addstr(" to convict)");
      }
      #endif

      getkey();

      //PROSECUTION MESSAGE
      // *JDS* The bigger your record, the stronger the evidence
      prosecution+=40+LCSrandom(101)+scarefactor+(20*g.confessions);
      if(sleeperjudge) prosecution>>=1;
      if(defense==3) prosecution-=60;

      set_color(COLOR_WHITE,COLOR_BLACK,0);
      move(7,1);

      if(autoconvict)
      {
         addstr(g.name, gamelog);
         addstr("の有罪に異議はなかった。", gamelog);
         gamelog.newline();
      }
      else
      {
         if(prosecution<=50) addstr("検察の主張はひどいものだ。", gamelog);
         else if(prosecution<=75) addstr("検察は通常通り主張した。", gamelog);
         else if(prosecution<=125) addstr("検察の主張は強固なものだ。", gamelog);
         else if(prosecution<=175) addstr("検察の主張には隙がない。", gamelog);
         else addstr("検察の主張は極めて強力だ。", gamelog);
         gamelog.newline();
      }

      // Debug prosecution power
      #ifdef SHOWMECHANICS
      {
         addstr(" (+");
         addstr(prosecution/2);
         addstr(" to +");
         addstr(prosecution);
         addstr(" to convict)");
      }
      #endif

      getkey();

      jury+=LCSrandom(prosecution/2+1)+prosecution/2;

      //DEFENSE MESSAGE
      set_color(COLOR_WHITE,COLOR_BLACK,0);
      move(9,1);

      int defensepower=0;
      if(defense==0||defense==3||defense==4)
      {
         if(autoconvict)
         {
            addstr("堂々と弁護したが、結果を変えることはできなかった。", gamelog);
            gamelog.newline();
         }
         else
         {
            if(defense==0) defensepower=LCSrandom(71);    // Court-appointed attorney
            else if(defense==3) defensepower=LCSrandom(71)+80; // Ace Liberal attorney
            else if(defense==4)
            {
               // Sleeper attorney
               defensepower=LCSrandom(71)+sleeperlawyer->get_skill(SKILL_LAW)*2
                                         +sleeperlawyer->get_skill(SKILL_PERSUASION)*2;
               sleeperlawyer->train(SKILL_LAW,prosecution/4);
               sleeperlawyer->train(SKILL_PERSUASION,prosecution/4);
            }

            if(defensepower<=5) addstr("弁護士はほとんど何も言えなかった。", gamelog);
            else if(defensepower<=15) addstr("弁護士は終了間際に思わず「私のクライアントは有罪だ! 」と言ってしまった。", gamelog);
            else if(defensepower<=25) addstr("弁護はまったくひどいものだった。", gamelog);
            else if(defensepower<=50) addstr("弁護は決め手に欠くものだった。", gamelog);
            else if(defensepower<=75) addstr("弁護はかなりうまくいった。", gamelog);
            else if(defensepower<=100) addstr("弁護はとてもうまくいった。", gamelog);
            else if(defensepower<=145)
            {
               if(prosecution<100) addstr("弁護士は検察の主張を素人のようにしてしまった。", gamelog);
               else addstr("弁護は極めて強固なものだった。", gamelog);
            }
            else
            {
               if(prosecution<100)
               {
                  addstr(attorneyname, gamelog);
                  addstr("の弁護を聞いた陪審員は立ち上がり、", gamelog);
                  move(10,1);
                  addstr("協議が始まっていないのに「無罪だ! 」と叫んだ。", gamelog);
                  if(defense==4) addjuice(*sleeperlawyer,10,500); // Bow please
               }
               else
               {
                  addstr(attorneyname, gamelog);
                  addstr("の弁護は完璧だった。", gamelog);
               }
            }
            gamelog.newline();
         }
      }
      if(defense==1)
      {
         // *JDS* LEGAL SELF-REPRESENTATION: To succeed here, you really need to have two skills be
         // high: persuasion and law, with law being 1.5 times as influential. You can't have
         // just one or just the other. Even if you're a very persuasive person, the court will eat
         // you alive if you can't sound intelligent when talking about the relevant charges, and you
         // won't be able to fool the jury into letting you go if you aren't persuasive, as no
         // matter how encyclopedic your legal knowledge is, it's all in the pitch.
         //
         // If either your persuasion or your law roll is too low, you'll end up getting a negative
         // result that will drag down your defense. So try not to suck in either area.
         defensepower=5*(g.skill_roll(SKILL_PERSUASION)-3)+
                      10*(g.skill_roll(SKILL_LAW)-3);
         g.train(SKILL_PERSUASION,50);
         g.train(SKILL_LAW,50);

         addstr(g.name, gamelog);
         if(defensepower<=0)
         {
            addstr("は致命的なミスをしてしまった。", gamelog);
            gamelog.newline();
            addjuice(g,-10,-50); // You should be ashamed
         }
         else if(defensepower<=25) addstr("の弁護は本当にひどいものだった。", gamelog);
         else if(defensepower<=50) addstr("の弁護は悪くなかったが、いくつかのミスがあった。", gamelog);
         else if(defensepower<=75) addstr("の弁護はかなりうまくいった。", gamelog);
         else if(defensepower<=100) addstr("は陪審員にとてもよい印象を与えた。", gamelog);
         else if(defensepower<=150) addstr("の弁護は極めて強力だった。", gamelog);
         else
         {
            addstr("の弁護は陪審員、判事、そして検察さえも自由への渇望で涙するものだった。", gamelog);
            addjuice(g,50,1000); // That shit is legend
         }
         gamelog.newline();
      }

      // Debug defense power
      #ifdef SHOWMECHANICS
      {
         addstr(" (");
         addstr(defensepower);
         addstr(", need ");
         addstr(jury+1);
         addstr(" to acquit)");
      }
      #endif

      getkey();

      //DELIBERATION MESSAGE
      set_color(COLOR_WHITE,COLOR_BLACK,0);
      move(12,1);
      addstr("陪審員は協議のため離れた。", gamelog);
      gamelog.newline();

      getkey();

      //JURY RETURN MESSAGE
      clear();
      set_color(COLOR_WHITE,COLOR_BLACK,0);
      move(1,1);
      addstr("陪審員は協議から戻ってきた。", gamelog);
      gamelog.newline();

      getkey();

      bool keeplawflags=false;

      //HUNG JURY
      if(defensepower==jury)
      {
         set_color(COLOR_YELLOW,COLOR_BLACK,1);
         move(3,1);
         addstr("だが、評決することができなかった!", gamelog);
         gamelog.newline();

         getkey();

         //RE-TRY
         if(LCSrandom(2)||scarefactor>=10||g.confessions)
         {
            set_color(COLOR_WHITE,COLOR_BLACK,0);
            move(5,1);
            addstr("判決は来月に持ち越された。", gamelog);
            gamelog.newline();

            getkey();

            g.location=find_courthouse(g);
            keeplawflags=true;
         }
         //NO RE-TRY
         else
         {
            set_color(COLOR_WHITE,COLOR_BLACK,0);
            move(5,1);
            addstr("検察は判決の来月への持ち越しを拒否した。", gamelog);
            gamelog.newline();
            if(g.sentence==0)
            {
               set_color(COLOR_GREEN,COLOR_BLACK,1);
               move(7,1);
               addstr(g.name, gamelog);
               addstr("は自由の身となった!", gamelog);
            }
            else
            {
               set_color(COLOR_WHITE,COLOR_BLACK,0);
               move(7,1);
               addstr(g.name, gamelog);
               addstr("はこれ以前の刑のために刑務所へ戻った", gamelog);
               if(!g.deathpenalty && g.sentence>1 && (LCSrandom(2)||sleeperjudge))
               {
                  g.sentence--;
                  addstr("。経過した1ヶ月が服役期間とみなされた", gamelog);
               }
               else addstr("。", gamelog);
               if(g.deathpenalty)
               {
                  g.sentence=3;
                  move(9,1);
                  addstr("死刑執行は現在から3ヵ月後と決定された。", gamelog);
               }
            }
            gamelog.nextMessage();

            getkey();
         }
      }
      //ACQUITTAL!
      else if(!autoconvict&&defensepower>jury)
      {
         set_color(COLOR_GREEN,COLOR_BLACK,1);
         move(3,1);
         addstr("無罪!", gamelog);
         gamelog.newline();

         getkey();

         if(g.sentence==0)
         {
            set_color(COLOR_GREEN,COLOR_BLACK,1);
            move(5,1);
            addstr(g.name, gamelog);
            addstr("は自由の身となった!", gamelog);
         }
         else
         {
            set_color(COLOR_WHITE,COLOR_BLACK,0);
            move(5,1);
            addstr(g.name, gamelog);
            addstr("はこれ以前の刑のために刑務所へ戻った", gamelog);
            if(!g.deathpenalty && g.sentence>1 && (LCSrandom(2)||sleeperjudge))
            {
               g.sentence--;
               addstr("。経過した1ヶ月が服役期間とみなされた", gamelog);
            }
            else addstr("。", gamelog);
            if(g.deathpenalty)
            {
               g.sentence=3;
               move(7,1);
               addstr("死刑執行は現在から3ヵ月後と決定された。", gamelog);
            }
         }
         gamelog.nextMessage();

         // Juice sleeper
         if(defense==4) addjuice(*sleeperlawyer,10,100);
         // Juice for self-defense
         if(defense==1) addjuice(g,10,100);

         getkey();
      }
      //LENIENCE
      else
      {
         // De-Juice sleeper
         if(defense==4) addjuice(*sleeperlawyer,-5,0);

         // Juice for getting convicted of something :)
         addjuice(g,25,200);

         // Check for lenience; sleeper judge will always be merciful
         if(defensepower/3>=jury/4||sleeperjudge) penalize(g,1);
         else penalize(g,0);
      }
      //CLEAN UP LAW FLAGS
      if(!keeplawflags) for(int i=0;i<LAWFLAGNUM;i++) g.crimes_suspected[i]=0;
      //Clean up heat, confessions
      g.heat=0,g.confessions=0;
      //PLACE PRISONER
      if(g.sentence!=0) imprison(g);
      else
      {
         Armor clothes(*armortype[getarmortype("ARMOR_CLOTHES")]);
         g.give_armor(clothes,NULL);
      }
   }
   //GUILTY PLEA
   // How about "nolo" (Nolo contendere) -- LK
   // I would imagine this would disregard the strength of the defense. -- LK
   else
   {
      clear();
      set_color(COLOR_WHITE,COLOR_BLACK,0);
      move(1,1);
      addstr("裁判所はそれを受け入れた。", gamelog);
      gamelog.nextMessage();

      getkey();

      // Check for lenience; sleeper judge will always be merciful
      if(sleeperjudge||LCSrandom(2)) penalize(g,1);
      else penalize(g,0);
      //CLEAN UP LAW FLAGS
      for(int i=0;i<LAWFLAGNUM;i++) g.crimes_suspected[i]=0;
      //Clean up heat, confessions
      g.heat=0,g.confessions=0;
      //PLACE PRISONER
      if(g.sentence!=0) imprison(g);
      else
      {
         Armor clothes(*armortype[getarmortype("ARMOR_CLOTHES")]);
         g.give_armor(clothes,NULL);
      }
   }
}



/* monthly - sentence a liberal */
void penalize(Creature &g,char lenient)
{
   set_color(COLOR_RED,COLOR_BLACK,1);
   move(3,1);
   addstr("有罪!", gamelog);
   gamelog.newline();

   getkey();

   short oldsentence=g.sentence;
   char olddeathpenalty=g.deathpenalty;
   g.sentence=0,g.deathpenalty=0;

   if(!lenient&&((g.crimes_suspected[LAWFLAG_MURDER])||(g.crimes_suspected[LAWFLAG_TREASON])||
      ((g.crimes_suspected[LAWFLAG_BURNFLAG])&&law[LAW_FLAGBURNING]==-2)||
      law[LAW_DEATHPENALTY]==-2))
   {
      if(law[LAW_DEATHPENALTY]==-2) g.deathpenalty=1;
      if(law[LAW_DEATHPENALTY]==-1) g.deathpenalty=LCSrandom(3);
      if(law[LAW_DEATHPENALTY]==0) g.deathpenalty=LCSrandom(2);
      if(law[LAW_DEATHPENALTY]==1) g.deathpenalty=!LCSrandom(5);
      if(law[LAW_DEATHPENALTY]==2) g.deathpenalty=0;
   }

   for(int l=0;l<LAWFLAGNUM;l++) if(g.crimes_suspected[l]>10) g.crimes_suspected[l]=10;

   //CALC TIME
   if(!g.deathpenalty)
   {
      if(!(g.sentence<0))
      {
         g.sentence+=(36+LCSrandom(18))*g.crimes_suspected[LAWFLAG_KIDNAPPING];
         g.sentence+=(1+LCSrandom(4))*g.crimes_suspected[LAWFLAG_THEFT];
         //g.sentence+=(4+LCSrandom(12))*(!!g.crimes_suspected[LAWFLAG_GUNUSE])+ // Extra for first incident only
         //            (2+LCSrandom(4)*g.crimes_suspected[LAWFLAG_GUNUSE]);      // Generally
         //g.sentence+=(1+LCSrandom(4))*(!!g.crimes_suspected[LAWFLAG_GUNCARRY]);
         g.sentence+=(6+LCSrandom(7))*g.crimes_suspected[LAWFLAG_CARTHEFT];
         g.sentence+=(1+LCSrandom(13))*g.crimes_suspected[LAWFLAG_INFORMATION];
         g.sentence+=(1+LCSrandom(13))*g.crimes_suspected[LAWFLAG_COMMERCE];
         g.sentence+=(6+LCSrandom(25))*g.crimes_suspected[LAWFLAG_CCFRAUD];
         g.sentence+=(3+LCSrandom(12))*g.crimes_suspected[LAWFLAG_BURIAL];
         g.sentence+=(1+LCSrandom(6))*g.crimes_suspected[LAWFLAG_PROSTITUTION];
         g.sentence+=1*g.crimes_suspected[LAWFLAG_DISTURBANCE];
         g.sentence+=1*g.crimes_suspected[LAWFLAG_PUBLICNUDITY];
         //g.sentence+=1*g.crimes_suspected[LAWFLAG_LOITERING];
         g.sentence+=1*g.crimes_suspected[LAWFLAG_HIREILLEGAL];
         g.sentence+=(12+LCSrandom(100))*g.crimes_suspected[LAWFLAG_RACKETEERING];

         // How illegal is marijuana?
         if(law[LAW_DRUGS]==-2) g.sentence+=(3+LCSrandom(360))*g.crimes_suspected[LAWFLAG_BROWNIES]; //insanely illegal
         else if(law[LAW_DRUGS]==-1) g.sentence+=(3+LCSrandom(120))*g.crimes_suspected[LAWFLAG_BROWNIES]; //very illegal
         else if(law[LAW_DRUGS]==0) g.sentence+=(3+LCSrandom(12))*g.crimes_suspected[LAWFLAG_BROWNIES]; //moderately illegal
         // else not illegal

         g.sentence+=1*g.crimes_suspected[LAWFLAG_BREAKING];
         g.sentence+=(60+LCSrandom(181))*g.crimes_suspected[LAWFLAG_TERRORISM];
         g.sentence+=(30+LCSrandom(61))*g.crimes_suspected[LAWFLAG_BANKROBBERY];
         g.sentence+=(30+LCSrandom(61))*g.crimes_suspected[LAWFLAG_JURY];
         g.sentence+=(30+LCSrandom(61))*g.crimes_suspected[LAWFLAG_HELPESCAPE];
         g.sentence+=(3+LCSrandom(16))*g.crimes_suspected[LAWFLAG_ESCAPED];
         g.sentence+=(1+LCSrandom(1))*g.crimes_suspected[LAWFLAG_RESIST];
         g.sentence+=(6+LCSrandom(1))*g.crimes_suspected[LAWFLAG_EXTORTION];

         g.sentence+=(4+LCSrandom(3))*g.crimes_suspected[LAWFLAG_SPEECH];
         g.sentence+=1*g.crimes_suspected[LAWFLAG_VANDALISM];
         g.sentence+=(12+LCSrandom(12))*g.crimes_suspected[LAWFLAG_ARSON];
         g.sentence+=(12+LCSrandom(1))*g.crimes_suspected[LAWFLAG_ARMEDASSAULT];
         g.sentence+=(3+LCSrandom(1))*g.crimes_suspected[LAWFLAG_ASSAULT];
      }
      if(law[LAW_FLAGBURNING]==-2)
      {
         if(!LCSrandom(2)) g.sentence+=(120+LCSrandom(241))*g.crimes_suspected[LAWFLAG_BURNFLAG];
         else if(g.crimes_suspected[LAWFLAG_BURNFLAG])g.sentence=-1*g.crimes_suspected[LAWFLAG_BURNFLAG];
      }
      else if(law[LAW_FLAGBURNING]==-1) g.sentence+=36*g.crimes_suspected[LAWFLAG_BURNFLAG];
      else if(law[LAW_FLAGBURNING]==0) g.sentence+=1*g.crimes_suspected[LAWFLAG_BURNFLAG];

      if((LCSrandom(4)-g.crimes_suspected[LAWFLAG_MURDER])>0)
      {
         if(!(g.sentence<0)) g.sentence+=(120+LCSrandom(241))*g.crimes_suspected[LAWFLAG_MURDER];
      }
      else
      {
         if(g.sentence<0) g.sentence-=-1*g.crimes_suspected[LAWFLAG_MURDER];
         else if(g.crimes_suspected[LAWFLAG_MURDER])
            g.sentence=-1*g.crimes_suspected[LAWFLAG_MURDER];
      }
      if(g.sentence<0) g.sentence-=1*g.crimes_suspected[LAWFLAG_TREASON];
      else if(g.crimes_suspected[LAWFLAG_TREASON]) g.sentence=-1*g.crimes_suspected[LAWFLAG_TREASON];
      if(lenient&&g.sentence!=-1) g.sentence/=2;
      if(lenient&&g.sentence==-1) g.sentence=240+LCSrandom(120);
   }
   //LENIENCY AND CAPITAL PUNISHMENT DON'T MIX
   else if(g.deathpenalty&&lenient) g.deathpenalty=0,g.sentence=-1;

   //MENTION LENIENCY
   if(lenient)
   {
      set_color(COLOR_WHITE,COLOR_BLACK,0);
      move(5,1);
      addstr("結審の前に陪審員は寛大な処置を求めた。", gamelog);
      gamelog.newline();

      getkey();
   }

   //MENTION SENTENCE
   if(olddeathpenalty)
   {
      g.deathpenalty=1;
      g.sentence=3;
      set_color(COLOR_RED,COLOR_BLACK,1);
      move(7,1);
      addstr(g.propername, gamelog);
      addstr("は刑務所に戻り死刑執行を待つこと。", gamelog);
      gamelog.newline();

      getkey();

      set_color(COLOR_WHITE,COLOR_BLACK,0);
      move(9,1);
      addstr("死刑執行は現在から3ヵ月後と決定された。", gamelog);

      getkey();
   }
   else if(g.deathpenalty)
   {
      g.sentence=3;
      set_color(COLOR_YELLOW,COLOR_RED,1);
      move(7,1);
      addstr(g.propername, gamelog);
      addstr("に死刑判決を言い渡す!", gamelog);
      gamelog.newline();

      getkey();

      set_color(COLOR_WHITE,COLOR_BLACK,0);
      move(9,1);
      addstr("死刑執行は現在から3ヵ月後と決定された。", gamelog);

      getkey();
   }
   // Don't give a time-limited sentence if they already have a life sentence.
   else if ((g.sentence>=0 && oldsentence<0) ||
            (g.sentence==0 && oldsentence>0))
   {
      g.sentence=oldsentence;
      set_color(COLOR_WHITE,COLOR_BLACK,0);
      move(7,1);
      addstr(g.propername, gamelog);
      addstr("に追加の刑はない。", gamelog);
      move(8,1);
      addstr("刑務所に戻ること", gamelog);
      if(g.sentence>1 && lenient)
      {
         g.sentence--;
         addstr("。経過した1ヶ月は服役期間とみなす", gamelog);
      }
      else addstr("。", gamelog);

      getkey();
   }
   else if(g.sentence==0)
   {
      set_color(COLOR_WHITE,COLOR_BLACK,0);
      move(7,1);
      addstr(g.propername, gamelog);
      addstr("、これは警告と考えること。釈放する。", gamelog);

      getkey();
   }
   else
   {
      if(g.sentence>=36)g.sentence-=g.sentence%12;

      set_color(COLOR_WHITE,COLOR_BLACK,0);
      move(7,1);
      addstr(g.propername, gamelog);
      addstr("に", gamelog);
      if(g.sentence>1200) g.sentence/=-1200;

      if(g.sentence<=-1)
      {
         if(g.sentence<-1)
         {
            addstr(-(g.sentence), gamelog);
            addstr("回の終身刑を言い渡す", gamelog);
            gamelog.newline();

            // Don't bother saying this if the convicted already has one or
            // more life sentences. Makes the 'consecutively' and 'concurrently'
            // statements later easier to tack on.
            if(oldsentence>=0)
            {
               addstr("。", gamelog);

               getkey();

               move(9,1);
               addstr("よい一日を、", gamelog);
               addstr(g.propername, gamelog);
            }
         }
         else addstr("終身刑をを言い渡す", gamelog);
      }
      else if(g.sentence>=36)
      {
         addstr("懲役", gamelog);
         addstr(g.sentence/12, gamelog);
         addstr("年を言い渡す", gamelog);
      }
      else
      {
         addstr("懲役", gamelog);
         addstr(g.sentence, gamelog);
         addstr("ヶ月を言い渡す", gamelog);
         if(g.sentence>1)addstr("", gamelog);
      }

      // Mash together compatible sentences.
      if((g.sentence>0 && oldsentence>0) ||
         (g.sentence<0 && oldsentence<0))
      {
         move(8,1);
         if(lenient)
         {
            if(ABS(oldsentence)>ABS(g.sentence))
               g.sentence=oldsentence;
            addstr("(刑期は平行となった)", gamelog);
         }
         else
         {
            g.sentence+=oldsentence;
            addstr("(刑期は合計された)", gamelog);
         }
      }

      addstr("。", gamelog);

      //dejuice boss
      int boss=getpoolcreature(g.hireid);
      if(boss!=-1&&pool[boss]->juice>50)
      {
         int juice=g.juice/10;
         if(juice<5) juice=5;
         addjuice(*pool[boss],-juice,0);
      }

      getkey();
   }
   gamelog.nextMessage();
}



/* monthly - move a liberal to jail */
void imprison(Creature &g)
{
   g.location=find_site_index_in_city(SITE_GOVERNMENT_PRISON,location[g.location]->city);
}



/* monthly - advances a liberal's prison time or executes them */
//RETURNS IF SCREEN WAS ERASED
char prison(Creature &g)
{
   static const char *cruel_and_unusual_execution_methods[] =
   {
      "斬首",
      "四つ裂き",
      "腹裂き",
      "千切り",
      "ライオンの餌にする刑",
      "剣闘士デスマシンとの連戦",
      "火あぶり",
      "はりつけ",
      "頭部圧砕",
      "公開ピラニアプール",
      "ロナルド・レーガンの強制ケツ吸い",
      "全身にピーナッツバターを塗りネズミの餌にする刑",
      "火蟻の巣に首まで埋めるの刑",
      "頭部をトラックに轢かせるの刑",
      "下水タンクで溺死",
      "巨大シュレッダー",
      "人体実験",
      "血抜き",
      "化学兵器の検体とするの刑",
      "家具メーカーへの売却",
      "CEOのおもちゃとして売却",
      "外国の奴隷トレーダーに売却",
      "恐怖のBay 12 Curses gamesへの暴露"
   };

   static const char *standard_execution_methods[] =
   {
      "毒物注射",
      "絞首刑",
      "銃殺刑",
      "電気椅子"
   };

   static const char *supposedly_painless_execution_method =
      "毒物注射";

   char showed=0;

   // People not on death row or about to be released can have a scene in prison
   if(!g.deathpenalty && g.sentence!=1)
   {
      if(law[LAW_PRISONS]==2)
      {
         //Liberal therapy.
         if(!LCSrandom(5)) reeducation(g);
      }
      else if(law[LAW_PRISONS]==-2)
      {
         //Labor camp.
         if(!LCSrandom(5)) laborcamp(g);
      }
      else
      {
         //Normal prison.
         if(!LCSrandom(5)) prisonscene(g);
      }
   }

   if(g.sentence>0)
   {
      //COMMUTE DEATH IN RIGHT CLIMATE
      if(g.deathpenalty&&law[LAW_DEATHPENALTY]==2)
      {
         clear();
         set_color(COLOR_WHITE,COLOR_BLACK,0);
         move(8,1);
         addstr(g.name, gamelog);
         addstr("の死刑は終身刑になった。", gamelog);
         move(9,1);
         addstr("死刑制度が廃止されたためだ。", gamelog);
         gamelog.nextMessage();

         getkey();

         g.sentence=-1;
         g.deathpenalty=0;
         return 1;
      }

      //ADVANCE SENTENCE
      g.sentence--;
      if(g.sentence==0)
      {
         //EXECUTE
         if(g.deathpenalty)
         {
            clear();
            set_color(COLOR_RED,COLOR_BLACK,1);
            move(8,1);
            addstr("恥辱:", gamelog);
            gamelog.newline();
            move(9,1);
            addstr("本日、保守の機械人形は", gamelog);
            addstr(g.name, gamelog);
            gamelog.record("を"); //Log this for formatting purposes.
            move(10,1);
            if(law[LAW_DEATHPENALTY]==-2)
               addstr(pickrandom(cruel_and_unusual_execution_methods), gamelog);
            else if(law[LAW_DEATHPENALTY]==-1||law[LAW_DEATHPENALTY]==0)
               addstr(pickrandom(standard_execution_methods), gamelog);
            else
               addstr(supposedly_painless_execution_method, gamelog);
            addstr("で処刑した。", gamelog);

            getkey();

            //dejuice boss
            int boss=getpoolcreature(g.hireid);
            if(boss!=-1)
            {
               gamelog.newline();
               set_color(COLOR_WHITE,COLOR_BLACK,0);
               move(12,1);
               addstr(pool[boss]->name, gamelog);
               addstr("はリベラル・クライム・スコードを失望させた。", gamelog);
               gamelog.newline();
               move(14,1);
               addstr("自分の部下を守れないものが誰を守れるというのか?", gamelog);

               getkey();

               addjuice(*pool[boss],-50,-50);
            }
            gamelog.nextMessage();

            g.die();
            stat_dead++;
            showed=1;
         }
         //SET FREE
         else
         {
            clear();
            set_color(COLOR_WHITE,COLOR_BLACK,0);
            move(8,1);
            addstr(g.name, gamelog);
            addstr("は刑期を終えた。", gamelog);
            gamelog.newline();
            move(9,1);
            addstr("心に傷を負ったことは疑いないが、リベラルが帰ってきた。", gamelog);
            gamelog.nextMessage();

            getkey();

            Armor clothes(*armortype[getarmortype("ARMOR_CLOTHES")]);
            g.give_armor(clothes,NULL);
            // If their old base is no longer under LCS control, wander back to the
            // homeless shelter instead.
            if(location[g.base]->renting<0) g.base=find_homeless_shelter(g);
            g.location=g.base;
            showed=1;
         }
      }
      //NOTIFY OF IMPENDING THINGS
      else if(g.sentence==1)
      {
         if(g.deathpenalty)
         {
            clear();
            set_color(COLOR_YELLOW,COLOR_BLACK,1);
            move(8,1);
            addstr(g.name, gamelog);
            addstr("の死刑執行は来月だ。", gamelog);
            gamelog.nextMessage();

            getkey();

            showed=1;
         }
         else
         {
            clear();
            set_color(COLOR_WHITE,COLOR_BLACK,1);
            move(8,1);
            addstr(g.name, gamelog);
            addstr("は来月刑期を終える。", gamelog);
            gamelog.nextMessage();

            getkey();

            showed=1;
         }
      }
      else
      {
         if(g.deathpenalty)
         {
            clear();
            set_color(COLOR_YELLOW,COLOR_BLACK,1);
            move(8,1);
            addstr(g.name, gamelog);
            addstr("の死刑執行は", gamelog);
            addstr(g.sentence, gamelog);
            addstr("ヶ月後だ。", gamelog);
            gamelog.nextMessage();

            getkey();

            showed=1;
         }
      }
   }

   return showed;
}

void reeducation(Creature &g)
{
   static const char *reeducation_experiences[] =
   {
      "は刑務所で社会復帰プログラムを受けた。",
      "は刑務所で政治的多様性の壁絵を描いている。",
      "は刑務所でリベラルのセラピストから定期的に治療を受けている。",
      "は刑務所でグループ・セラピーを受けた。",
      "は刑務所内で様々な政治的立場の人々と歌を歌っている。",
      "は刑務所で保守と友人になることを勧められた。",
      "は刑務所内で再犯防止プログラムを受けた。",
      "は刑務所内で政治犯罪被害者に関するビデオを見た。"
   };

   clear();
   set_color(COLOR_WHITE,COLOR_BLACK,1);
   move(8,1);
   addstr(g.name, gamelog);
   addstr(pickrandom(reeducation_experiences), gamelog);
   gamelog.newline();

   getkey();

   move(10,1);
   if(!g.attribute_check(ATTRIBUTE_HEART,DIFFICULTY_FORMIDABLE))
   {
      if(g.juice>0 && LCSrandom(2))
      {
         addstr(g.name, gamelog);
         addstr("はLCSの活動を悪く思い、ジュースを失った!", gamelog);
         addjuice(g,-50,0);
      }
      else if(LCSrandom(15)>g.get_attribute(ATTRIBUTE_WISDOM,true)
           || g.get_attribute(ATTRIBUTE_WISDOM,true) < g.get_attribute(ATTRIBUTE_HEART,true))
      {
         addstr(g.name, gamelog);
         addstr("は少し知恵が増した…", gamelog);
         g.adjust_attribute(ATTRIBUTE_WISDOM,+1);
      }
      else if(g.align==ALIGN_LIBERAL && g.flag & CREATUREFLAG_LOVESLAVE && LCSrandom(4))
      {
         addstr(g.name, gamelog);
         addstr("はただ", gamelog);
         addstr(pool[g.hireid]->name, gamelog);
         addstr("といるためにLCSに忠誠を誓っている。", gamelog);
      }
      else
      {
         addstr(g.name, gamelog);
         addstr("はリベラル・クライム・スコードを辞めた!", gamelog);

         //Rat out contact
         int contact = getpoolcreature(g.hireid);
         if(contact >= 0)
         {
            criminalize(*pool[contact],LAWFLAG_RACKETEERING);
            pool[contact]->confessions++;
         }

         g.die();
         g.location=-1;
      }
   }
   else
   {
      addstr(g.name, gamelog);
      addstr("は気を保っている。", gamelog);
   }
   gamelog.nextMessage();

   getkey();

   clear();

   return;
}

void laborcamp(Creature &g)
{
   int escaped = 0;
   const char *experience;
   // Escape attempt!
   if(g.hireid == -1 && !LCSrandom(3))
   {
      escaped = 2;
      experience = "は収容所で他の囚人と看守を打ちのめした!";
   }
   else if(g.skill_check(SKILL_DISGUISE, DIFFICULTY_HEROIC) && !LCSrandom(10))
   {
      escaped = 1;
      experience = "は電気工事の作業着を着て、工事作業者に紛れて車で収容所から脱出した。";
      g.give_armor(*armortype[getarmortype("ARMOR_WORKCLOTHES")],NULL);
   }
   else if(g.skill_check(SKILL_SECURITY, DIFFICULTY_CHALLENGING) && g.skill_check(SKILL_STEALTH, DIFFICULTY_HARD) && !LCSrandom(10))
   {
      escaped = 1;
      experience = "は足輪の鍵をこじ開けて密かに抜け出した!";
   }
   else if(g.skill_check(SKILL_SCIENCE, DIFFICULTY_HARD) && !LCSrandom(10))
   {
      escaped = 1;
      experience = "は薬物で仮死状態になり、ゴミと一緒に収容所の外に出た!";
   }

   static const char *labor_camp_experiences[] =
   {
      "は収容所で危険な機械の操作をさせられている。",
      "は収容所でサディスティックな看守に殴られている。",
      "は収容キャンプで重い荷物を運ばされている。",
      "は収容所で重労働をさせられている。",
      "は収容所で他の囚人とひどいケンカばかりしている。",
      "は収容所で暴動を起こしたがすぐに鎮圧された。",
      "は収容所で暴動を起こしたがすぐに鎮圧された。"
   };

   if(!escaped)experience=pickrandom(labor_camp_experiences);

   clear();
   set_color(COLOR_WHITE,COLOR_BLACK,1);
   move(8,1);
   addstr(g.name, gamelog);
   addstr(experience, gamelog);
   gamelog.newline();

   getkey();

   move(10,1);
   if(escaped)
   {
      int prison = g.location;
      addstr(g.name, gamelog);
      addstr("は収容所から脱走した!", gamelog);
      addjuice(g,50,1000);
      criminalize(g, LAWFLAG_ESCAPED);
      g.location = find_homeless_shelter(g);

      if(escaped==2)
      {
         int num_escaped = 0;
         for(int p=0;p<len(pool);p++)
         {
            if(pool[p]->location == prison && !(pool[p]->flag & CREATUREFLAG_SLEEPER))
            {
               criminalize(*pool[p], LAWFLAG_ESCAPED);
               pool[p]->location = g.location;
               num_escaped++;
            }
         }
         if(num_escaped == 1)
         {
            gamelog.nextMessage();
            mvaddstr(11,1, "他のLCSメンバーも脱走した!", gamelog);
         }
         else if(num_escaped > 1)
         {
            gamelog.nextMessage();
            mvaddstr(11,1, "LCSが再び立ち上がる! 他の複数のLCSメンバーも脱走した!", gamelog);
         }
      }
   }
   else if(!LCSrandom(4))
   {
      if(g.get_attribute(ATTRIBUTE_HEALTH, true) > 1)
      {
         addstr(g.name, gamelog);
         addstr("はそのとき重傷を負った。", gamelog);
         addjuice(g,-40,0);
         addjuice(g,-10,-50);
      }
      else
      {
         addstr(g.name, gamelog);
         addstr("は死体となって見つかった。", gamelog);

         g.die();
         g.location=-1;
      }
   }
   else
   {
      addstr(g.name, gamelog);
      addstr("はどうにか負傷せずにすんだ。", gamelog);
   }
   gamelog.nextMessage();

   getkey();

   clear();

   return;
}

void prisonscene(Creature &g)
{
   int escaped = 0;
   int effect = 0;
   const char *experience;
   if(g.juice + int(g.hireid==-1)*300 > 500)
   {
      // Escape attempt!
      if(g.hireid == -1 && !LCSrandom(10))
      {
         escaped = 2;
         experience = "は数十人の受刑者と共にLCSのスローガンを叫び暴動を引き起こした!";
      }
      else if(g.skill_check(SKILL_COMPUTERS, DIFFICULTY_HARD) && !LCSrandom(5))
      {
         escaped = 2;
         experience = "は密かに持ち込まれた携帯電話で監獄の扉を開くウィルスを作成した!";
      }
      else if(g.skill_check(SKILL_DISGUISE, DIFFICULTY_HARD) && !LCSrandom(5))
      {
         escaped = 1;
         experience = "は密かに持ち込まれた普段着で監獄の外を平然と歩いている。";
         g.give_armor(*armortype[getarmortype("ARMOR_CLOTHES")],NULL);
      }
      else if(g.skill_check(SKILL_SECURITY, DIFFICULTY_CHALLENGING) && g.skill_check(SKILL_STEALTH, DIFFICULTY_CHALLENGING) && !LCSrandom(5))
      {
         escaped = 1;
         experience = "は深夜に独房の扉をこじ開け、刑務所の外側のフェンスを切断した!";
      }
      else if(g.skill_check(SKILL_SCIENCE, DIFFICULTY_AVERAGE) && g.skill_check(SKILL_HANDTOHAND, DIFFICULTY_EASY) && !LCSrandom(5))
      {
         escaped = 1;
         experience = "は密かに持ち込まれた薬物をわざと過剰に摂取し、その後病室を抜け出した!";
      }
   }

   static const char *good_experiences[] =
   {
      "は毎日他の受刑者にLCSの宣伝をしている。",
      "は刑務所内のシリアルレイピストを叩きのめすグループを結成した。",
      "は他の受刑者から様々な技術を学んだ。",
      "は刑務所内でL-C-Sの刺青をした。",
      "は刑務所内で新しい抵抗の歌を思いついた。"
   };
   static const char *bad_experiences[] =
   {
      "は刑務所のひどい食事のせいで数日間体調を崩した。",
      "は刑務所のジムで運動しすぎた。",
      "は他の受刑者から何度も性的暴行を受けている。",
      "は刑務所長に政治的活動の停止を誓う手紙を書かされた。",
      "は便宜を得るため他の受刑者を密告した。"
   };
   static const char *general_experiences[] =
   {
      "は看守に怒鳴り独房に送られた。",
      "は刑務所に密かに持ち込まれたドラッグでハイになっている。",
      "は刑務所の図書館で本ばかり読んでいる。",
      "は刑務所でケンカして便所掃除の罰を受けた。",
      "は監獄を抜け出す方法を常に考えている。"
   };

   if(escaped==0)
   {
      if(g.attribute_check(ATTRIBUTE_HEART,DIFFICULTY_HARD)) {
         effect = 1;
         if(LCSrandom(2) > 0) experience = pickrandom(good_experiences);
         else experience = pickrandom(general_experiences);
      } else if(g.attribute_check(ATTRIBUTE_HEART,DIFFICULTY_CHALLENGING)) {
         effect = 0;
         experience = pickrandom(general_experiences);
      } else {
         effect = -1;
         if(LCSrandom(2) > 0) experience = pickrandom(bad_experiences);
         else experience = pickrandom(general_experiences);
      }
   }

   clear();
   set_color(COLOR_WHITE,COLOR_BLACK,1);
   move(8,1);
   addstr(g.name, gamelog);
   addstr(experience, gamelog);
   gamelog.newline();

   getkey();

   move(10,1);
   if(escaped)
   {
      int prison = g.location;
      addstr(g.name, gamelog);
      addstr("は脱獄に成功した!", gamelog);
      addjuice(g,50,1000);
      criminalize(g, LAWFLAG_ESCAPED);
      g.location = find_homeless_shelter(g);

      if(escaped==2)
      {
         int num_escaped = 0;
         for(int p=0;p<len(pool);p++)
         {
            if(pool[p]->location == prison && !(pool[p]->flag & CREATUREFLAG_SLEEPER))
            {
               criminalize(*pool[p], LAWFLAG_ESCAPED);
               pool[p]->location = g.location;
               num_escaped++;
            }
         }
         if(num_escaped == 1)
         {
            gamelog.nextMessage();
            mvaddstr(11,1, "他のLCSメンバーも脱走した!", gamelog);
         }
         else if(num_escaped > 1)
         {
            gamelog.nextMessage();
            mvaddstr(11,1, "LCSが再び立ち上がる! 他の複数のLCSメンバーも脱走した!", gamelog);
         }
      }
   }
   else if(effect > 0)
   {
      addstr(g.name, gamelog);
      addstr("は犯罪者として鍛えられ、ジュースを獲得した。", gamelog);
      addjuice(g,20,1000);
   }
   else if(effect < 0)
   {
      addstr(g.name, gamelog);
      addstr("はジュースを少し失った。", gamelog);
      addjuice(g,-20,-30);
   }
   else
   {
      addstr(g.name, gamelog);
      addstr("はそれでも大丈夫のようだ。", gamelog);
   }
   gamelog.nextMessage();

   getkey();

   clear();

   return;
}
