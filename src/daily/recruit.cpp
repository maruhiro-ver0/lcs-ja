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

//#include <includes.h>
#include <externs.h>

/* recruit struct constructor */
recruitst::recruitst() : timeleft(0), level(0), eagerness1(0), task(0)
{
   //Has heard of the LCS
   if((int)LCSrandom(100)<attitude[VIEW_LIBERALCRIMESQUAD])
   {
      //Likes the LCS
      if((int)LCSrandom(100)<attitude[VIEW_LIBERALCRIMESQUADPOS])
         eagerness1=3;
      //Doesn't like the LCS
      else eagerness1=0;
   }
   else eagerness1=2;
}

recruitst::~recruitst()
{
   delete recruit;
}

char recruitst::eagerness()
{
   char eagerness_temp=eagerness1;
   //Moderates are decidedly less interested
   if(recruit->align==0) eagerness_temp-=2;
   //Conservatives are extremely uninterested
   if(recruit->align==-1) eagerness_temp-=4;
   return eagerness_temp;
}

static void getissueeventstring(char* str)
{
   switch(LCSrandom(VIEWNUM-3))
   {
   case VIEW_DRUGS: strcat(str,"マリファナと健康に関する研究論文"); break;
   case VIEW_MILITARY: strcat(str,"軍隊の残虐行為の歴史に関する本"); break;
   case VIEW_IMMIGRATION: strcat(str,"移民の生活を扱ったリアリティ・テレビ番組"); break;
   case VIEW_CIVILRIGHTS: strcat(str,"公民権闘争のドキュメンタリー"); break;
   case VIEW_WOMEN: strcat(str,"女性の権利闘争のドキュメンタリー"); break;
   case VIEW_GAY: strcat(str,"同性愛者の権利闘争のドキュメンタリー"); break;
   case VIEW_DEATHPENALTY: strcat(str,"死刑の乱用に関する研究論文"); break;
   case VIEW_TAXES: strcat(str,"トリクルダウンの欠陥に関する論文"); break;
   case VIEW_NUCLEARPOWER: strcat(str,"チェルノブイリの立ち入り禁止地域の視察ビデオ"); break;
   case VIEW_ANIMALRESEARCH: strcat(str,"動物実験のドキュメンタリー"); break;
   case VIEW_POLICEBEHAVIOR: strcat(str,"警官の暴行を録画したビデオ"); break;
   case VIEW_TORTURE: strcat(str,"軍の取り調べに関する政府の報告書"); break;
   case VIEW_PRISONS: strcat(str,"受刑者の扱いに関するドキュメンタリー"); break;
   case VIEW_INTELLIGENCE: strcat(str,"プライバシー権のドキュメンタリー"); break;
   case VIEW_FREESPEECH: strcat(str,"発禁処分された本"); break;
   case VIEW_GENETICS: strcat(str,"遺伝子工学の事故に関するビデオ"); break;
   case VIEW_JUSTICES: strcat(str,"判決を調査した論文"); break;
   case VIEW_GUNCONTROL: strcat(str,"学校での銃乱射事件をプロファイリングした本"); break;
   case VIEW_SWEATSHOPS: strcat(str,"規制外の搾取労働を録画したビデオ"); break;
   case VIEW_POLLUTION: strcat(str,"環境問題に関する政府から流出した報告書"); break;
   case VIEW_CORPORATECULTURE: strcat(str,"企業文化下の生活に関するドキュメンタリー"); break;
   case VIEW_CEOSALARY: strcat(str,"リベラル・シンクタンクが調査したCEOの報酬"); break;
   case VIEW_AMRADIO: strcat(str,"保守派ラジオ司会者の暴言集"); break;
   case VIEW_CABLENEWS: strcat(str,"保守派ケーブルニュースの流出メモ"); break;
   //case VIEW_POLITICALVIOLENCE: strcat(str,"a documentary about progress made by direct action"); break;
   }
}

/* recruiting */
char recruitment_activity(Creature &cr,char &clearformess)
{
   clearformess=1;
   int ocursite = cursite;
   cursite = cr.location;

   int type = cr.activity.arg;
   int difficulty = recruitFindDifficulty(type);
   char* name = recruitName(type);

   if(type>=0)
   {
      music.play(MUSIC_RECRUITING);
      cr.train(SKILL_STREETSENSE,5);

      erase();
      set_color(COLOR_WHITE,COLOR_BLACK,1);
      mvaddstr(0,0,"リベラルスカウトの冒険");
      printcreatureinfo(&cr);
      makedelimiter();

      set_color(COLOR_WHITE,COLOR_BLACK,0);
      mvaddstr_f(10,0,"%sは%sを尋ねまわった…", cr.name, name);

      getkey();

      int recruitCount = 0;

      if(difficulty < 10)
         // Generate recruitment candidates
         for(recruitCount=0; recruitCount<5; recruitCount++)
         {
            if(recruitCount==0 || cr.skill_roll(SKILL_STREETSENSE)>(difficulty+recruitCount*2))
            {
               makecreature(encounter[recruitCount], type);
               encounter[recruitCount].namecreature();
            }
            else break;
         }

      if(recruitCount == 0) {
         mvaddstr_f(11, 0, "%sは%sを見つけられなかった。", cr.name, name);

         getkey();

         cursite = ocursite;
         return 0;
      } else if(recruitCount == 1) {
         mvaddstr_f(11, 0, "%sはどうにか", cr.name);
         set_alignment_color(encounter[0].align);
         addstr(encounter[0].name);
         add_age(encounter[0]);
         set_color(COLOR_WHITE,COLOR_BLACK,0);
         addstr("と会うことができた。");

         getkey();

         erase();
         set_color(COLOR_WHITE,COLOR_BLACK,1);
         mvaddstr(0,0,"リベラルスカウトの冒険");
         printcreatureinfo(&encounter[0]);
         makedelimiter();
         talk(cr, 0);
      } else {
         while(true)
         {
            erase();
            set_color(COLOR_WHITE,COLOR_BLACK,1);
            mvaddstr(0,0,"リベラルスカウトの冒険");
            printcreatureinfo(&cr);
            makedelimiter();

            set_color(COLOR_WHITE,COLOR_BLACK,0);
            mvaddstr_f(10, 0, "%sは複数の人物と会うことができた。", cr.name);
            for(int i=0; i<recruitCount; i++) {
               set_color(COLOR_WHITE,COLOR_BLACK,0);
               mvaddstr_f(12+i, 0, "%c - ", 'a'+i);
               set_alignment_color(encounter[i].align);
               addstr(encounter[i].name);
               add_age(encounter[i]);
            }
            set_color(COLOR_WHITE,COLOR_BLACK,0);
            mvaddstr(12+recruitCount+1, 0, "EnterまたはEscキーで今日は切り上げる。");

            int c=getkey();

            if(c == ENTER || c == ESC) break;
            c -= 'a';
            if(c >= 0 && c < ENCMAX-1 && encounter[c].exists)
            {
               int id=encounter[c].id;
               erase();
               set_color(COLOR_WHITE,COLOR_BLACK,1);
               mvaddstr(0,0,"リベラルスカウトの冒険");
               printcreatureinfo(&encounter[c]);
               makedelimiter();

               talk(cr, c);
               if(encounter[c].id == id) delenc(c, 0);
               recruitCount--;
               if(recruitCount <= 0) break;
            }
         }
      }
   }
   cursite = ocursite;
   return 1;
}

/* daily - recruit - recruit meeting */
char completerecruitmeeting(recruitst &r,int p,char &clearformess)
{
   music.play(MUSIC_RECRUITING);
   clearformess=1;

   erase();
   set_color(COLOR_WHITE,COLOR_BLACK,1);
   move(0,0);
   if(pool[p]->meetings++>5 && LCSrandom(pool[p]->meetings-5))
   {
      addstr(pool[p]->name, gamelog);
      addstr("はダブルブッキングしてしまい、", gamelog);
      addstr(r.recruit->name, gamelog);
      addstr("との", gamelog);
      move(1,0);
      addstr("面会できなかった。", gamelog);
      gamelog.newline();

      move(3,0);
      addstr("おちつけ、", gamelog);
      addstr(pool[p]->name, gamelog);
      addstr("!", gamelog);
      gamelog.nextMessage();

      getkey();

      return 1;
   }
   addstr(r.recruit->name, gamelog);
   addstr("との対話、", gamelog);
   addstr(r.recruit->get_type_name(), gamelog);
   addstr("、", gamelog);
   addstr(location[r.recruit->location]->name, gamelog);
   gamelog.newline();

   set_color(COLOR_WHITE,COLOR_BLACK,0);
   printfunds();

   printcreatureinfo(r.recruit);
   makedelimiter();

   move(10,0);
   addstr(r.recruit->name);
   switch(r.eagerness())
   {
   case 1: addstr("にはさらなる説得が必要だろう。"); break;
   case 2: addstr("はもっとよく知りたいようだ。"); break;
   case 3: addstr("はすべきことがわかってきたようだ。"); break;
   default: if(r.eagerness()>=4) addstr("はリベラル蜂起のために戦う準備ができたようだ。");
            else addstr("は失望しているようだ。"); break;
   }
   move(11,0);
   addstr(pool[p]->name);
   addstr("はどうするか?");

   move(13,0);
   if(ledger.get_funds()<50) set_color(COLOR_BLACK,COLOR_BLACK,1);
   addstr("A - 興味を保つために$50を費やして本などを与える");
   set_color(COLOR_WHITE,COLOR_BLACK,0);
   move(14,0);
   addstr("B - ただ注意深く話し、政治の議論を行う");

   move(15,0);
   if(subordinatesleft(*pool[p]) && r.eagerness()>=4)
   {
      addstr("C - ");
      addstr(r.recruit->name);
      addstr("にLCSのメンバーに加わるように勧める");
   }
   else if(!subordinatesleft(*pool[p]))
   {
      set_color(COLOR_BLACK,COLOR_BLACK,1);
      addstr("C - メンバーにするには、");
      addstr(pool[p]->name);
      addstr("にはもっとジュースが必要だ");
      set_color(COLOR_WHITE,COLOR_BLACK,0);
   }
   else
   {
      set_color(COLOR_BLACK,COLOR_BLACK,1);
      addstr("C - ");
      addstr(r.recruit->name);
      addstr("はLCSに加わる準備ができていない");
      set_color(COLOR_WHITE,COLOR_BLACK,0);
   }

   move(16,0);
   addstr("D - 対話を打ち切る");

   int y=18;

   while(true)
   {
      int c=getkey();

      if(c=='c' && subordinatesleft(*pool[p]) && r.eagerness()>=4)
      {
         move(y,0);
         addstr(pool[p]->name, gamelog);
         addstr("は", gamelog);
         addstr(r.recruit->name, gamelog);
         addstr("にリベラル・クライム・スコードに加わるように勧めた。", gamelog);
         gamelog.newline();

         getkey();

         set_color(COLOR_GREEN,COLOR_BLACK,1);
         move(y+=2,0);

         addstr(r.recruit->name, gamelog);
         addstr("はそれを受け入れ、活動の開始を強く望んだ。", gamelog);
         gamelog.nextMessage();

         liberalize(*r.recruit,false);

         getkey();

         erase();
         sleeperize_prompt(*r.recruit,*pool[p],6);

         r.recruit->hireid=pool[p]->id;

         pool[p]->train(SKILL_PERSUASION,25);

         pool.push_back(r.recruit);
         r.recruit = NULL;
         stat_recruits++;

         return 1;
      }
      if(c=='b' || (c=='a' && ledger.get_funds()>=50))
      {
         if(c=='a')
            ledger.subtract_funds(50,EXPENSE_RECRUITMENT);

         pool[p]->train(SKILL_PERSUASION,
            max(12-pool[p]->get_skill(SKILL_PERSUASION),5));
         pool[p]->train(SKILL_SCIENCE,
            max(r.recruit->get_skill(SKILL_SCIENCE)-pool[p]->get_skill(SKILL_SCIENCE),0));
         pool[p]->train(SKILL_RELIGION,
            max(r.recruit->get_skill(SKILL_RELIGION)-pool[p]->get_skill(SKILL_RELIGION),0));
         pool[p]->train(SKILL_LAW,
            max(r.recruit->get_skill(SKILL_LAW)-pool[p]->get_skill(SKILL_LAW),0));
         pool[p]->train(SKILL_BUSINESS,
            max(r.recruit->get_skill(SKILL_BUSINESS)-pool[p]->get_skill(SKILL_BUSINESS),0));

         int lib_persuasiveness = pool[p]->get_skill(SKILL_BUSINESS)+
                                  pool[p]->get_skill(SKILL_SCIENCE)+
                                  pool[p]->get_skill(SKILL_RELIGION)+
                                  pool[p]->get_skill(SKILL_LAW)+
                                  pool[p]->get_attribute(ATTRIBUTE_INTELLIGENCE,true);

         int recruit_reluctance = 5 +
                                  r.recruit->get_skill(SKILL_BUSINESS)+
                                  r.recruit->get_skill(SKILL_SCIENCE)+
                                  r.recruit->get_skill(SKILL_RELIGION)+
                                  r.recruit->get_skill(SKILL_LAW)+
                                  r.recruit->get_attribute(ATTRIBUTE_WISDOM,true)+
                                  r.recruit->get_attribute(ATTRIBUTE_INTELLIGENCE,true);

         if(lib_persuasiveness>recruit_reluctance) recruit_reluctance=0;
         else recruit_reluctance-=lib_persuasiveness;

         int difficulty=recruit_reluctance;

         char str[75];
         strcpy(str,"");
         if(c=='a')
         {
            difficulty-=5;

            move(y++,0);
            addstr(pool[p]->name, gamelog);
            addstr("は", gamelog);
            getissueeventstring(str);
            addstr(str, gamelog);
            addstr("を共に見た。", gamelog);
            gamelog.newline();

            getkey();
         }
         else
         {
            move(y++,0);
            addstr(pool[p]->name, gamelog);
            addstr("は", gamelog);
            addstr(pool[p]->hisher(), gamelog);
            addstr(getview(LCSrandom(VIEWNUM-3),true), gamelog);
            addstr("に対する考え方を述べた。", gamelog);
            gamelog.newline();

            getkey();
         }

         // Liberals with juice increase difficulty as if their Wisdom were increased by said juice
         if(r.recruit->juice>=10)
         {
            if(r.recruit->juice<50) //Activist
               difficulty+=1;
            else if(r.recruit->juice<100) //Socialist Threat
               difficulty+=static_cast<int>(2+0.1*r.recruit->get_attribute(ATTRIBUTE_WISDOM, false));
            else if(r.recruit->juice<200) //Revolutionary
               difficulty+=static_cast<int>(3+0.2*r.recruit->get_attribute(ATTRIBUTE_WISDOM, false));
            else if(r.recruit->juice<500) //Urban Commando
               difficulty+=static_cast<int>(4+0.3*r.recruit->get_attribute(ATTRIBUTE_WISDOM, false));
            else if(r.recruit->juice<1000) //Liberal Guardian
               difficulty+=static_cast<int>(5+0.4*r.recruit->get_attribute(ATTRIBUTE_WISDOM, false));
            else //Elite Liberal
               difficulty+=static_cast<int>(6+0.5*r.recruit->get_attribute(ATTRIBUTE_WISDOM, false));
         }
         if(difficulty>18) difficulty=18; // difficulty above 18 is impossible, we don't want that

         if(pool[p]->skill_check(SKILL_PERSUASION,difficulty))
         {
            set_color(COLOR_CYAN,COLOR_BLACK,1);
            if(r.level<127) r.level++;
            if(r.eagerness1<127) r.eagerness1++;
            move(y++,0);
            addstr(r.recruit->name, gamelog);
            addstr("は", gamelog);
            addstr(pool[p]->name, gamelog);
            addstr("の考え方に洞察力を感じたようだ。", gamelog);
            gamelog.newline();
            move(y++,0);
            addstr("2人は次の晩に再び合う約束をした。", gamelog);
            gamelog.nextMessage();
         }
         else if(pool[p]->skill_check(SKILL_PERSUASION,difficulty)) // Second chance to not fail horribly
         {
            if(r.level<127) r.level++;
            if(r.eagerness1>-128) r.eagerness1--;
            move(y++,0);
            addstr(r.recruit->name, gamelog);
            addstr("は", gamelog);
            addstr(pool[p]->name, gamelog);
            addstr("の意見に疑問を持っているようだ。", gamelog);
            gamelog.newline();
            move(y++,0);
            addstr("2人は次の晩に再び合う約束をした。", gamelog);
            gamelog.nextMessage();
         }
         else
         {
            set_color(COLOR_MAGENTA,COLOR_BLACK,1);
            move(y++,0);
            if(r.recruit->talkreceptive() && r.recruit->align==ALIGN_LIBERAL)
            {
               addstr(r.recruit->name, gamelog);
               addstr("は", gamelog);
               addstr(pool[p]->name, gamelog);
               addstr("がこの問題を本当は理解していないと思っているようだ。", gamelog);
               gamelog.newline();
               move(y++,0);
               addstr("恐らく", gamelog);
               addstr(pool[p]->name, gamelog);
               addstr("にはもっと経験が必要だ。", gamelog);
               gamelog.nextMessage();
            }
            else
            {
               addstr(pool[p]->name, gamelog);
               addstr("は危険な印象を与えてしまったようだ。", gamelog);
               gamelog.newline();
               move(y++,0);
               addstr("これは大きな誤りだった。もう会うことはないだろう。", gamelog);
               gamelog.nextMessage();
            }

            getkey();

            return 1;
         }

         getkey();

         return 0;
      }
      if(c=='d') return 1;
   }
}
