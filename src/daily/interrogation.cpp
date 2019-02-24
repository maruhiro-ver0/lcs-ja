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

#include <externs.h>

// Macro dumps interrogation data to screen for debug
#ifdef INTERROGATION_DEBUG
   #define DEBUG_VARIABLE_DUMP(text,value) { mvaddstr(20,0,text); addstr(value); addchar(' '); }
#else
   #define DEBUG_VARIABLE_DUMP(text,value)
#endif

enum InterrogationTechnqiues
{
   TECHNIQUE_TALK,
   TECHNIQUE_RESTRAIN,
   TECHNIQUE_BEAT,
   TECHNIQUE_PROPS,
   TECHNIQUE_DRUGS,
   TECHNIQUE_KILL
};

// Clear sidebar
void clear_interrogation_sidebar()
{
   for(int i=4;i<23;i++)
      mvaddstr(i,40,"                                  "); // 34 spaces
}

// Shows the interrogation data at the right side of the screen
void show_interrogation_sidebar( Creature * cr, Creature * a )
{
   clear_interrogation_sidebar();
   int y=4;
   map<long,struct float_zero>& rapport = cr->activity.intr()->rapport;
   move(y,40);
   set_color(COLOR_WHITE,COLOR_BLACK,0);
   addstr("捕虜: ");
   set_color(COLOR_RED,COLOR_BLACK,1);
   addstr(cr->name);
   move(y+=2,40);
   set_color(COLOR_WHITE,COLOR_BLACK,0);
   addstr("体力: ");
   printhealthstat(*cr,y,48,0);
   set_color(COLOR_WHITE,COLOR_BLACK,0);
   move(++y,40);
   addstr("心: ");
   addstr(cr->get_attribute(ATTRIBUTE_HEART,true));
   move(++y,40);
   addstr("知恵: ");
   addstr(cr->get_attribute(ATTRIBUTE_WISDOM,true));
   move(++y,40);
   addstr("体力: ");
   addstr(cr->get_attribute(ATTRIBUTE_HEALTH,true));

   move(y=13,40);
   set_color(COLOR_WHITE,COLOR_BLACK,0);
   addstr("尋問官: ");
   set_color(COLOR_GREEN,COLOR_BLACK,1);
   addstr(a->name);
   move(y+=2,40);
   set_color(COLOR_WHITE,COLOR_BLACK,0);
   addstr("体力: ");
   printhealthstat(*a,y,48,0);
   set_color(COLOR_WHITE,COLOR_BLACK,0);
   move(++y,40);
   addstr("心理学: ");
   addstr(a->get_skill(SKILL_PSYCHOLOGY));
   move(++y,40);
   set_color(COLOR_WHITE,COLOR_BLACK,0);
   addstr("心: ");
   addstr(a->get_attribute(ATTRIBUTE_HEART,true));
   move(++y,40);
   addstr("知恵: ");
   addstr(a->get_attribute(ATTRIBUTE_WISDOM,true));
   move(++y,40);
   addstr("服装: ");
   addstr(a->get_armor().get_name());
   move(y+=2,40);

   // What would 4, 2, 0, -2, -3, and/or -5 mean? (Some of these may not exist) -- LK
   // These are greater than and less than comparisons, so they are testing ranges -Fox
   if(rapport[a->id]>3)
   {
      addstr("保守は");
      addstr(a->name);
      addstr("に");
      move(++y,40);
      addstr("唯一の友であるかのようにすがっている。");
   }
   else if(rapport[a->id]>1)
   {
      addstr("保守は");
      addstr(a->name);
      addstr("に好意を持っている。");
   }
   else if(rapport[a->id]>-1)
   {
      addstr("保守は");
      addstr(a->name);
      addstr("に");
      move(++y,40);
      addstr("対して反抗的だ。");
   }
   else if(rapport[a->id]>-4)
   {
      addstr("保守は");
      addstr(a->name);
      addstr("を憎んでいる。");
   }
   else
   {
      addstr("保守は");
      addstr(a->name);
      addstr("を");
      move(++y,40);
      addstr("殺してしまいたいと思っているに違いない。");
   }
}

/* hostage tending */
void tendhostage(Creature *cr,char &clearformess)
{
   music.play(MUSIC_INTERROGATION);
   vector<Creature *> temppool;
   int p;
   Creature *a=NULL;

   interrogation* &intr=cr->activity.intr();
   bool (&techniques)[6]=intr->techniques;
   int& druguse = intr->druguse;
   map<long,struct float_zero>& rapport = intr->rapport;

   //Find all tenders who are set to this hostage
   for(p=0;p<len(pool);p++)
   {
      if(!pool[p]->alive) continue;
      if(pool[p]->activity.type==ACTIVITY_HOSTAGETENDING&&pool[p]->activity.arg==cr->id)
      {
         //If they're in the same location as the hostage,
         //include them in the interrogation
         if(pool[p]->location==cr->location&&pool[p]->location!=-1)
            temppool.push_back(pool[p]);
         //If they're someplace else, take them off the job
         else pool[p]->activity.type=ACTIVITY_NONE;
      }
   }

   if(cr->location==-1)
   {
      delete cr;
      return;
   }

   //possible hostage escape attempt if unattended or unrestrained
   if(!len(temppool)||!techniques[TECHNIQUE_RESTRAIN])
   {
      //CHECK FOR HOSTAGE ESCAPE
      if(LCSrandom(200)+25*len(temppool)<
         cr->get_attribute(ATTRIBUTE_INTELLIGENCE,true)+
         cr->get_attribute(ATTRIBUTE_AGILITY,true)+
         cr->get_attribute(ATTRIBUTE_STRENGTH,true)&&
         cr->joindays>=5)
      {
         for(int p=0;p<len(pool);p++)
         {
            if(pool[p]==cr)
            {
               if(clearformess) erase();
               else makedelimiter();

               set_color(COLOR_WHITE,COLOR_BLACK,1);
               move(8,1);
               addstr(cr->name, gamelog);
               addstr("は脱走した!", gamelog);
               gamelog.nextMessage();
               location[cr->location]->siege.timeuntillocated=3;

               getkey();

               //clear activities for tenders
               for(int i=0;i<len(pool);i++)
               {
                  if(!pool[i]->alive) continue;
                  if(pool[i]->activity.type==ACTIVITY_HOSTAGETENDING&&pool[i]->activity.arg==cr->id)
                     pool[i]->activity.type=ACTIVITY_NONE;
               }

               //delete interrogation data
               delete intr;
               delete_and_remove(pool,p);
               break;
            }
         }
         return;
      }

      if(!len(temppool)) return;
   }

   clearformess=1;

   erase();
   set_color(COLOR_WHITE,COLOR_BLACK,1);
   move(0,0);
   addstr(cr->name);
   addstr("への教育: ");
   addstr(cr->joindays);
   addstr("日目");

   getkey();

   set_color(COLOR_WHITE,COLOR_BLACK,0);

   char turned=0;

   int y=3;

   {
      //each day, the attack roll is initialized to the number of days of the stay with
      //the LCS -- they will eventually break, but also eventually become too traumatized
      //to continue
      int p,business=0,religion=0,science=0,attack=0;

      int* _attack = new int[len(temppool)];

      for(p=0;p<len(temppool);p++)
      {
         _attack[p] = 0;
         if(temppool[p])
            if(temppool[p]->alive)
            {
               if(temppool[p]->get_skill(SKILL_BUSINESS)>business)
                  business=temppool[p]->get_skill(SKILL_BUSINESS);
               if(temppool[p]->get_skill(SKILL_RELIGION)>religion)
                  religion=temppool[p]->get_skill(SKILL_RELIGION);
               if(temppool[p]->get_skill(SKILL_SCIENCE)>science)
                  science=temppool[p]->get_skill(SKILL_SCIENCE);

               _attack[p] = (temppool[p]->get_attribute(ATTRIBUTE_HEART,true)-
                             temppool[p]->get_attribute(ATTRIBUTE_WISDOM,true)+
                             temppool[p]->get_skill(SKILL_PSYCHOLOGY)*2);

               _attack[p] += temppool[p]->get_armor().get_interrogation_basepower();

               if(_attack[p]<0) _attack[p]=0;
               if(_attack[p]>attack) attack=_attack[p];
            }
      }

      vector<int> goodp;

      for(p=0;p<len(temppool);p++)
         if(temppool[p])
            if(temppool[p]->alive&&_attack[p]==attack)
               goodp.push_back(p);
      a=temppool[pickrandom(goodp)];

      attack+=len(temppool);
      attack+=cr->joindays;

      attack+=business-cr->get_skill(SKILL_BUSINESS);
      attack+=religion-cr->get_skill(SKILL_RELIGION);
      attack+=science-cr->get_skill(SKILL_SCIENCE);
      attack+=a->skill_roll(SKILL_PSYCHOLOGY)-cr->skill_roll(SKILL_PSYCHOLOGY);

      attack+=cr->attribute_roll(ATTRIBUTE_HEART);
      attack-=cr->attribute_roll(ATTRIBUTE_WISDOM)*2;

      while(true)
      {
         y=2;
         if(techniques[TECHNIQUE_KILL])
         {
            set_color(COLOR_RED,COLOR_BLACK,1);
            move(y,0);y+=2;addstr("操り人形の処刑         ");
         }
         else
         {
            set_color(COLOR_YELLOW,COLOR_BLACK,1);
            move(y,0);y+=2;addstr("リベラル尋問 方針の選択");
         }
         if(techniques[TECHNIQUE_KILL])set_color(COLOR_BLACK,COLOR_BLACK,1);
         else set_color(COLOR_WHITE,COLOR_BLACK,techniques[TECHNIQUE_TALK]);
         move(y++,0);addstr("A - ");
         if(!techniques[TECHNIQUE_TALK]) addstr("対話しない  ");
         else addstr("対話を試みる");
         if(!techniques[TECHNIQUE_KILL])set_color(COLOR_WHITE,COLOR_BLACK,techniques[TECHNIQUE_RESTRAIN]);
         move(y++,0);addstr("B - ");
         if(!techniques[TECHNIQUE_RESTRAIN]) addstr("身体的拘束を行わない");
         else addstr("身体的拘束を行う    ");
         if(!techniques[TECHNIQUE_KILL])set_color(COLOR_WHITE,COLOR_BLACK,techniques[TECHNIQUE_BEAT]);
         move(y++,0);addstr("C - ");
         if(!techniques[TECHNIQUE_BEAT]) addstr("暴行を加えない");
         else addstr("暴行を加える  ");
         if(!techniques[TECHNIQUE_KILL])set_color(COLOR_WHITE,COLOR_BLACK,techniques[TECHNIQUE_PROPS]);
         move(y,0);addstr("D - ");
         if(!techniques[TECHNIQUE_PROPS])addstr("道具に金を掛ける  ");
         else addstr("道具に金を掛けない");
         move(y++,27);
         addstr("($250)");
         if(!techniques[TECHNIQUE_KILL])set_color(COLOR_WHITE,COLOR_BLACK,techniques[TECHNIQUE_DRUGS]);
         move(y,0);addstr("E - ");
         if(!techniques[TECHNIQUE_DRUGS])addstr("幻覚剤を使わない");
         else addstr("幻覚剤を使う    ");
         move(y,28);y+=2;
         addstr("($50)");
         if(techniques[TECHNIQUE_KILL])set_color(COLOR_RED,COLOR_BLACK,1);
         else set_color(COLOR_WHITE,COLOR_BLACK,0);
         move(y,0);y+=2;addstr("K - 捕虜を殺害する");
         set_color(COLOR_WHITE,COLOR_BLACK,0);
         move(y++,0);addstr("Enterキーで方針を確定する");

         show_interrogation_sidebar(cr,a);

         int c=getkey();
         if(c>='a'&&c<='e') techniques[c-'a']=!techniques[c-'a'];
         if(c=='k') techniques[TECHNIQUE_KILL]=!techniques[TECHNIQUE_KILL];
         if(c=='x'||c==ENTER||c==ESC||c==SPACEBAR) break;
      }

      if(techniques[TECHNIQUE_PROPS]&&ledger.get_funds()>=250)
         ledger.subtract_funds(250,EXPENSE_HOSTAGE);
      else techniques[TECHNIQUE_PROPS]=0;
      if(techniques[TECHNIQUE_DRUGS]&&ledger.get_funds()>=50)
         ledger.subtract_funds(50,EXPENSE_HOSTAGE);
      else techniques[TECHNIQUE_DRUGS]=0;

      if(techniques[TECHNIQUE_KILL]) // Kill the Hostage
      {
         erase();
         set_color(COLOR_WHITE,COLOR_BLACK,1);
         move(0,0);
         addstr(cr->name, gamelog);
         addstr("への最後の教育: ", gamelog);
         addstr(cr->joindays, gamelog);
         addstr("日目", gamelog);
         gamelog.newline();

         a=NULL;

         for(int i=0;i<len(temppool);i++)
            if(LCSrandom(50)<temppool[i]->juice||
               LCSrandom(9)+1>=temppool[i]->get_attribute(ATTRIBUTE_HEART,0))
            {  a=temppool[i]; break; }

         if(a)
         {
            //delete interrogation information
            delete intr;
            set_color(COLOR_MAGENTA,COLOR_BLACK,0);
            cr->die();
            stat_kills++;
            move(y++,0);
            addstr(a->name, gamelog);
            addstr("は", gamelog);
            addstr(cr->name, gamelog);
            addstr("を", gamelog);
            switch(LCSrandom(5))
            {
            case 0: addstr("絞殺した。", gamelog); break;
            case 1: addstr("殴り殺した。", gamelog); break;
            case 2: addstr("目の前でレーガンの写真を焼いて殺した。", gamelog); break;
            case 3: addstr("税金は高くなっていると言って殺した。", gamelog); break;
            case 4: addstr("両親は中絶を望んでいると言って殺した。", gamelog); break;
            }
            //show_interrogation_sidebar(cr,a);

            getkey();

            if(LCSrandom(a->get_attribute(ATTRIBUTE_HEART,false))>LCSrandom(3))
            {
               gamelog.newline();
               set_color(COLOR_GREEN,COLOR_BLACK,1);
               move(y++,0);
               addstr(a->name, gamelog);
               addstr("は吐き気を感じた。そして", gamelog);
               a->adjust_attribute(ATTRIBUTE_HEART,-1);
               move(y++,0);
               switch(LCSrandom(4))
               {
               case 0: addstr("ゴミ箱に嘔吐した。", gamelog); break;
               case 1: addstr("大量の酒を飲み眠った。", gamelog); break;
               case 2: addstr("うずくまり泣いた。", gamelog); break;
               case 3: addstr("床に倒れこんだ。", gamelog); break;
               }
            }
            else if(!LCSrandom(3))
            {
               gamelog.newline();
               set_color(COLOR_CYAN,COLOR_BLACK,1);
               move(y++,0);
               addstr(a->name, gamelog);
               addstr("はより冷酷になった。", gamelog);
               a->adjust_attribute(ATTRIBUTE_WISDOM,+1);
            }
            gamelog.nextMessage();
         }
         else
         {
            set_color(COLOR_YELLOW,COLOR_BLACK,0);
            move(y++,0);
            addstr("ここには", gamelog);
            addstr(cr->name, gamelog);
            addstr("を殺せるほど冷酷な者はいない。", gamelog);
            gamelog.nextMessage();

            //Interrogation will continue as planned, with
            //these restrictions:
            techniques[TECHNIQUE_TALK]=0; //don't talk to them today
            techniques[TECHNIQUE_BEAT]=0; //don't beat them today
            techniques[TECHNIQUE_DRUGS]=0; //don't administer drugs

            //Food and restraint settings will be applied as normal
         }
         //show_interrogation_sidebar(cr,a);

         getkey();

         set_color(COLOR_WHITE,COLOR_BLACK,0);
         move(24,0);
         addstr("何かキーを押すと続ける。");

         getkey();

         if(!cr->alive)
         {
            for(int p=0;p<len(pool);p++)
            {
               if(!pool[p]->alive) continue;
               if(pool[p]->activity.type==ACTIVITY_HOSTAGETENDING&&pool[p]->activity.arg==cr->id)
                  pool[p]->activity.type=ACTIVITY_NONE;
            }
            delete[] _attack;
            return;
         }
      }

      erase();
      set_color(COLOR_WHITE,COLOR_BLACK,1);
      move(0,0);
      addstr(cr->name, gamelog);
      addstr("への教育: ", gamelog);
      addstr(cr->joindays, gamelog);
      addstr("日目", gamelog);
      gamelog.newline();

      move((y=2)++,0);
      addstr("操り人形", gamelog);
      if(techniques[TECHNIQUE_RESTRAIN]) // Restraint
      {
         addstr("は手足を鎖でつながれた状態で奥の部屋にいる。", gamelog);
         //move(y++,0);
         //addstr("", gamelog);
         gamelog.newline();

         attack+=5;
      }
      else
      {
         addstr("は独房に改装した奥の部屋に閉じ込められている。", gamelog);
         //move(y++,0);
         //addstr("", gamelog);
         gamelog.newline();
      }
      //show_interrogation_sidebar(cr,a);

      getkey();

      if(techniques[TECHNIQUE_DRUGS]) // Hallucinogenic drugs
      {
         move(++y,0);

         addstr("危険な幻覚剤の影響を受けている。", gamelog);
         gamelog.newline();

         int drugbonus=10+a->get_armor().get_interrogation_drugbonus(); // we won't apply this JUST yet

         //Possible permanent health damage
         if(LCSrandom(50)<++druguse)
         {
            cr->adjust_attribute(ATTRIBUTE_HEALTH,-1);
            move(++y,0);

            getkey();

            addstr(cr->name, gamelog);
            addstr("は口から泡を吹き白目を剥いている。", gamelog);
            gamelog.newline();
            move(++y,0);

            getkey();

            Creature* doctor=a; // the lead interrogator is doctor by default
            int maxskill=doctor->get_skill(SKILL_FIRSTAID);
            for(int i=0;i<len(temppool);i++) // search for the best doctor
               if(temppool[i]->get_skill(SKILL_FIRSTAID)>maxskill)
                  maxskill=(doctor=temppool[i])->get_skill(SKILL_FIRSTAID); // we found a doctor

            if(cr->get_attribute(ATTRIBUTE_HEALTH,false)<=0 || !maxskill) // he's dead, Jim
            {
               if(maxskill)
               { // we have a real doctor but the patient is still dead anyway
                  addstr(doctor->name, gamelog);
                  addstr("はAEDを使った。だが", gamelog);
                  addstr(cr->name, gamelog);
                  addstr("は死んでしまった。", gamelog);
               }
               else
               {
                  addstr(doctor->name, gamelog);
                  if(law[LAW_FREESPEECH]==-2)
                     addstr("はパニック発作で殴られ、そして[悪臭がした]。", gamelog);
                  else
                  {
                     addstr("はパニック発作で殴られ、そして", gamelog);
                     addstr(doctor->hisher(), gamelog);
                     addstr("糞まみれになった。", gamelog);
                  }
               }
               gamelog.newline();
               move(++y,0);

               getkey();

               set_color(COLOR_YELLOW,COLOR_BLACK,1);
               if(maxskill)
               {
                  addstr("弱った", gamelog);
                  addstr(cr->name, gamelog);
                  addstr("には致死量だったのだ。", gamelog);
               }
               else
               {
                  addstr(cr->name, gamelog);
                  addstr("は", gamelog);
                  addstr(doctor->name, gamelog);
                  addstr("の未熟な応急手当のせいで助からなかった。", gamelog);
               }
               gamelog.newline();
               cr->die();
            }
            else
            {
               addstr(doctor->name, gamelog);
               if(doctor->skill_check(SKILL_FIRSTAID,DIFFICULTY_CHALLENGING)) // is the doctor AWESOME?
               {
                  doctor->train(SKILL_FIRSTAID,5*max(10-doctor->get_skill(SKILL_FIRSTAID),0),10); // can train up to 10
                  addstr("は手際よくAEDを使って心停止から回復させた。", gamelog); // not long enough for near-death experience
                  gamelog.newline();
                  move(++y,0);

                  getkey();

                  addstr(doctor->name, gamelog);
                  addstr("の技術で", gamelog);
                  addstr(cr->name, gamelog);
                  addstr("をあらゆる健康被害から救うことができた。", gamelog);
                  cr->adjust_attribute(ATTRIBUTE_HEALTH,+1); // no permanent health damage from a skilled doctor
                  techniques[TECHNIQUE_DRUGS]=(druguse=drugbonus=0); // drugs eliminated from the system (zeroing out 3 variables with 1 line of code)
               }
               else
               {
                  doctor->train(SKILL_FIRSTAID,5*max(5-doctor->get_skill(SKILL_FIRSTAID),0),5); // can train up to 5
                  addstr("は不器用にAEDを使って心停止から回復させた。", gamelog);
                  gamelog.newline();
                  move(++y,0);

                  getkey();

                  addstr(cr->name, gamelog);
                  if(cr->get_skill(SKILL_RELIGION)) // the patient was out long enough to have a near-death experience
                     addstr("は臨死体験をして神と出会った。", gamelog);
                  else addstr("は臨死体験をしてジョン・レノンと出会った。", gamelog);
                  drugbonus*=2; // the near-death experience doubles the drug bonus, since the hostage is spaced out afterwards
               }
               rapport[doctor->id]+=0.5f; // rapport bonus for having life saved by doctor
               gamelog.newline();
            }
         }
         attack+=drugbonus; // now we finally apply the drug bonus
         move(++y,0);
         //show_interrogation_sidebar(cr,a);

         getkey();
      }

      if(techniques[TECHNIQUE_BEAT]&&!turned&&cr->alive) // Beating
      {
         move(++y,0);

         int forceroll=0;
         bool tortured=0;

         for(int i=0;i<len(temppool);i++)
         {
            //add interrogator's strength to beating strength
            forceroll+=temppool[i]->attribute_roll(ATTRIBUTE_STRENGTH);
            //reduce rapport with each interrogator
            rapport[temppool[i]->id]-=0.4f;
         }

         //Torture captive if lead interrogator has low heart
         //and you funded using extra supplies
         //
         //Yeah, you kinda don't want this to happen
         if(!(a->attribute_check(ATTRIBUTE_HEART,DIFFICULTY_EASY))&&techniques[TECHNIQUE_PROPS])
         {
            tortured = true;
            //Torture more devastating than normal beating
            forceroll*=5;
            //Extremely bad for rapport with lead interrogator
            rapport[a->id]-=3;

            addstr(a->name, gamelog);
            switch(LCSrandom(6))
            {
            case 0:addstr("はアブグレイブ刑務所を再現した", gamelog);break;
            case 1:addstr("は金属のケーブルで操り人形を鞭打った", gamelog);break;
            case 2:addstr("は捕虜の頭を水の中に押し込んだ", gamelog);break;
            case 3:addstr("は指の爪の間に針を押し込んだ", gamelog);break;
            case 4:addstr("は金属バットで捕虜を殴った", gamelog);break;
            case 5:addstr("はベルトで捕虜を鞭打った", gamelog);break;
            }
            addstr("。悲鳴", gamelog);
            move(++y,0);
            addstr("「", gamelog);
            for(int i=0;i<2;i++)
            {
               switch(LCSrandom(10))
               {
               case 0:addstr("お前を憎む", gamelog);break;
               case 1:addstr("心が痛まないのか?", gamelog);break;
               case 2:addstr("皆がお前を憎んでいる", gamelog);break;
               case 3:addstr("神はお前を憎んでいる", gamelog);break;
               case 4:addstr("やめてくれ", gamelog);break;
               case 5:addstr("これがリベラルか", gamelog);break;
               case 6:addstr("心を入れ替えろ、豚め", gamelog);break;
               case 7:addstr("殺してやる", gamelog);break;
               case 8:addstr("私を愛しているのか?", gamelog);break;
               case 9:addstr("私はお前の神だ", gamelog);break;
               }
               if(i<1) addstr("! ", gamelog);
            }
            addstr("! 」", gamelog);
            gamelog.newline();
            if(cr->get_attribute(ATTRIBUTE_HEART,true)>1) cr->adjust_attribute(ATTRIBUTE_HEART,-1);
            if(cr->get_attribute(ATTRIBUTE_WISDOM,true)>1) cr->adjust_attribute(ATTRIBUTE_WISDOM,-1);
         }
         else
         {
            if(len(temppool)==1)
            {
               addstr(temppool[0]->name, gamelog);
               addstr("は", gamelog);
            }
            else if(len(temppool)==2)
            {
               addstr(temppool[0]->name, gamelog);
               addstr("と", gamelog);
               addstr(temppool[1]->name, gamelog);
               addstr("は", gamelog);
            }
            else
            {
               addstr(cr->name);
               addstr("の護衛は", gamelog);
            }
            addstr("操り人形を", gamelog);
            if(techniques[TECHNIQUE_PROPS])
            {
               switch(LCSrandom(6))
               {
               case 0:addstr("巨大な象のぬいぐるみで", gamelog);break;
               case 1:addstr("南部連合国旗を被って", gamelog);break;
               case 2:addstr("レーガンの等身大ポップで", gamelog);break;
               case 3:addstr("欽定訳聖書で", gamelog);break;
               case 4:addstr("札束で", gamelog);break;
               case 5:addstr("壁にある保守のプロパガンダで", gamelog);break;
               }
            }
            addstr("殴った。", gamelog);
            move(++y,0);
            switch(LCSrandom(4))
            {
            case 0:addstr("悲鳴", gamelog);break;
            case 1:addstr("大声", gamelog);break;
            case 2:addstr("叫び", gamelog);break;
            case 3:addstr("怒鳴り声", gamelog);break;
            }
            addstr("「", gamelog);
            for(int i=0;i<3;i++)
            {
               switch(LCSrandom(20))
               {
               case 0:addstr("マクドナルド", gamelog);break;
               case 1:addstr("マイクロソフト", gamelog);break;
               case 2:addstr("ビルゲイツ", gamelog);break;
               case 3:addstr("ウォルマート", gamelog);break;
               case 4:addstr("ジョージ・W・ブッシュ", gamelog);break;
               case 5:addstr("エクソンモービル", gamelog);break;
               case 6:addstr("トリクルダウン", gamelog);break;
               case 7:addstr("伝統的家族", gamelog);break;
               case 8:addstr("保守主義", gamelog);break;
               case 9:addstr("麻薬戦争", gamelog);break;
               case 10:addstr("テロとの戦い", gamelog);break;
               case 11:addstr("ロナルド・レーガン", gamelog);break;
               case 12:addstr("ラッシュ・リンボー", gamelog);break;
               case 13:addstr("減税", gamelog);break;
               case 14:addstr("軍事支出", gamelog);break;
               case 15:addstr("アン・コールター", gamelog);break;
               case 16:addstr("規制緩和", gamelog);break;
               case 17:addstr("警察", gamelog);break;
               case 18:addstr("大企業", gamelog);break;
               case 19:addstr("通信傍受", gamelog);break;

               }
               if(i<2) addstr("! ", gamelog);
            }
            addstr("! 」", gamelog);
            gamelog.newline();
         }
         y++;

         cr->blood-=(5 + LCSrandom(5)) * (1+techniques[TECHNIQUE_PROPS]);

         //show_interrogation_sidebar(cr,a);

         getkey();

         if(!(cr->attribute_check(ATTRIBUTE_HEALTH,forceroll)))
         {
            if(cr->skill_check(SKILL_RELIGION,forceroll))
            {
               move(y++,0);
               addstr(cr->name, gamelog);
               if(!techniques[TECHNIQUE_DRUGS])
               {
                  switch(LCSrandom(2))
                  {
                  case 0:addstr("は祈った…", gamelog);break;
                  case 1:addstr("は神に助けを求めた。", gamelog);break;
                  }
                  gamelog.newline();
               }
               else
               {
                  switch(LCSrandom(2))
                  {
                  case 0:addstr("は神の幻覚にすがった。", gamelog);break;
                  case 1:addstr("は神秘的な体験と思っているようだ。", gamelog);break;
                  }
                  gamelog.newline();
               }
            }
            else if(forceroll >
                    cr->get_attribute(ATTRIBUTE_WISDOM,true)*3+
                    cr->get_attribute(ATTRIBUTE_HEART,true)*3+
                    cr->get_attribute(ATTRIBUTE_HEALTH,true)*3)
            {
               move(y++,0);
               addstr(cr->name, gamelog);
               switch(LCSrandom(4))
               {
               case 0:addstr("は絶望し、", gamelog);
                  if(techniques[TECHNIQUE_DRUGS])addstr("ジョン・レノンの慈悲", gamelog);
                  else if(cr->get_skill(SKILL_RELIGION))addstr("神の慈悲", gamelog);
                  else addstr("母の助け", gamelog);
                  addstr("を求め叫んだ。", gamelog);
                  break;
               case 1:
                  if(techniques[TECHNIQUE_RESTRAIN]) addstr("は拘束されうなだれている。", gamelog);
                  else addstr("は部屋の隅でうずくまり動けないでいる。", gamelog);break;
               case 2:
                  if(techniques[TECHNIQUE_DRUGS] && !LCSrandom(5)) addstr("は絶望し吠えるような声を上げた。", gamelog);
                  else addstr("は絶望し叫んだ。", gamelog);break;
               case 3:
                  if(techniques[TECHNIQUE_DRUGS] && !LCSrandom(3)) addstr("はリンゴを疑った。", gamelog);
                  else addstr("は死を疑った。", gamelog);
                  break;
               }
               gamelog.newline();
               if(cr->get_attribute(ATTRIBUTE_HEART,false)>1) cr->adjust_attribute(ATTRIBUTE_HEART,-1);

               if(LCSrandom(2)&&cr->juice>0) { if((cr->juice-=forceroll)<0) cr->juice=0; }
               else if(cr->get_attribute(ATTRIBUTE_WISDOM,false)>1)
               {
                  cr->set_attribute(ATTRIBUTE_WISDOM,cr->get_attribute(ATTRIBUTE_WISDOM,false)-(forceroll/10));
                  if(cr->get_attribute(ATTRIBUTE_WISDOM,false)<1) cr->set_attribute(ATTRIBUTE_WISDOM,1);
               }

               if(location[cr->worklocation]->mapped==0 && !LCSrandom(5))
               {
                  //show_interrogation_sidebar(cr,a);

                  getkey();

                  move(y++,0);
                  addstr(a->name, gamelog);
                  addstr("は哀れな捕虜から情報を引き出した。", gamelog);
                  gamelog.newline();
                  move(y++,0);

                  getkey();

                  if(location[cr->worklocation]->type<=SITE_RESIDENTIAL_SHELTER)
                     addstr("残念ながらLCSには役に立たないものだった。", gamelog);
                  else
                  {
                     addstr("その情報を元に", gamelog);
                     addstr(location[cr->worklocation]->name, gamelog);
                     addstr("の詳細な地図を作った。", gamelog);
                  }
                  gamelog.newline();
                  location[cr->worklocation]->mapped=1;
                  location[cr->worklocation]->hidden=0;
               }
            }
            else
            {
               move(y++,0);
               addstr(cr->name, gamelog);
               addstr("は何かを伝えようとしている。", gamelog);
               gamelog.newline();

               if(cr->juice>0) if((cr->juice-=forceroll)<0) cr->juice=0;

               if(cr->get_attribute(ATTRIBUTE_WISDOM,false)>1)
               {
                  cr->set_attribute(ATTRIBUTE_WISDOM,cr->get_attribute(ATTRIBUTE_WISDOM,false)-(forceroll/10+1));
                  if(cr->get_attribute(ATTRIBUTE_WISDOM,false)<1) cr->set_attribute(ATTRIBUTE_WISDOM,1);
               }
            }

            if(!(cr->attribute_check(ATTRIBUTE_HEALTH,forceroll/3)))
            {
               //show_interrogation_sidebar(cr,a);

               getkey();

               move(y++,0);
               if(cr->get_attribute(ATTRIBUTE_HEALTH,false)>1)
               {
                  cr->adjust_attribute(ATTRIBUTE_HEALTH,-1);
                  addstr(cr->name, gamelog);
                  addstr("は重症を負っている。", gamelog);
                  gamelog.newline();
               }
               else
               {
                  cr->set_attribute(ATTRIBUTE_HEALTH,0);
                  addstr(cr->name, gamelog);
                  addstr("の弱った体は暴行によって崩れ落ちた。", gamelog);
                  gamelog.newline();
                  cr->die();
               }
            }
         }
         else
         {
            move(y++,0);
            addstr(cr->name, gamelog);
            addstr("は耐え忍んでいる。", gamelog);
            gamelog.newline();
         }
         //show_interrogation_sidebar(cr,a);

         getkey();

         if(tortured && cr->alive)
         {
            if(LCSrandom(a->get_attribute(ATTRIBUTE_HEART,false))>LCSrandom(3))
            {
               set_color(COLOR_GREEN,COLOR_BLACK,1);
               move(y++,0);
               addstr(a->name, gamelog);
               addstr(" feels sick to the stomach afterward and ", gamelog);
               a->adjust_attribute(ATTRIBUTE_HEART,-1);
               move(y++,0);
               switch(LCSrandom(4))
               {
                  case 0:addstr("ゴミ箱に嘔吐した。", gamelog);break;
                  case 1:addstr("大量の酒を飲み眠った。", gamelog);break;
                  case 2:addstr("うずくまり泣いた。", gamelog);break;
                  case 3:addstr("床に倒れこんだ。", gamelog);break;
               }
               gamelog.newline();
            }
            else if(!LCSrandom(3))
            {
               set_color(COLOR_CYAN,COLOR_BLACK,1);
               move(y++,0);
               addstr(a->name, gamelog);
               addstr("はより冷酷になった。", gamelog);
               gamelog.newline();
               a->adjust_attribute(ATTRIBUTE_WISDOM,+1);
            }
            set_color(COLOR_WHITE,COLOR_BLACK,1);
         }
      }

      // Verbal Interrogation
      if(techniques[TECHNIQUE_TALK]&&cr->alive)
      {
         float rapport_temp = rapport[a->id];

         if(!techniques[TECHNIQUE_RESTRAIN])attack += 5;
         attack += int(rapport[a->id] * 3);

         move((++y)++,0);
         addstr(a->name, gamelog);
         addstr("は", gamelog);
         addstr(cr->name, gamelog);

         if(techniques[TECHNIQUE_PROPS])//props
         {
            attack += 10;
            switch(LCSrandom(9))
            {
            case 0:addstr("と残酷なビデオゲームをプレーした", gamelog);break;
            case 1:addstr("に種の起源を読み聞かせた", gamelog);break;
            case 2:addstr("の目の前で国旗を焼き払った", gamelog);break;
            case 3:addstr("と丹念に作られたポリティカル・ファンタジーを探索した", gamelog);break;
            case 4:addstr("と物議を呼んだアバンギャルド映画を観た", gamelog);break;
            case 5:addstr("と「バイブルブラック」をプレーした", gamelog);break;// Yes, this is a porno.
            case 6:addstr("とエメット・ティルのドキュメンタリーを観た", gamelog);break;
            case 7:addstr("とマイケル・ムーアの映画を観た", gamelog);break;
            case 8:addstr("とリベラルなラジオ番組を聴いた", gamelog);break;
            }
            gamelog.newline();
         }
         else
         {
            switch(LCSrandom(4))
            {
            case 0:addstr(getview(LCSrandom(VIEWNUM-3),true), gamelog);
                   addstr("の話をした", gamelog);break;
            case 1:addstr(getview(LCSrandom(VIEWNUM-3),true), gamelog);
                   addstr("の議論をした", gamelog);break;
            case 2:addstr("のリベラル的側面を明らかにしようとした", gamelog);break;
            case 3:addstr("を仲間に引き込もうとした", gamelog);break;
            }
         }
         addstr("。", gamelog);
         gamelog.newline();

         //Hallucinogenic drugs:
         //Re-interprets lead interrogator
         if(techniques[TECHNIQUE_DRUGS])
         {
            //show_interrogation_sidebar(cr,a);

            getkey();

            move(y++,0);
            if(cr->skill_check(SKILL_PSYCHOLOGY,DIFFICULTY_CHALLENGING))
            {
               switch(LCSrandom(4))
               {
               case 0:addstr(cr->name);
                     addstr("は薬物による幻覚を呆然と見ている。", gamelog);
                     break;
               case 1:addstr(cr->name);
                     addstr("は自分のイニシャルを何度もつぶやいている。", gamelog);
                     break;
               case 2:addstr(cr->name);
                     addstr("は数字を数え続けている。", gamelog);
                     break;
               case 3:addstr(cr->name);
                     addstr("は幻覚に対して冷静になろうとしている。", gamelog);
                     break;
               }
               gamelog.newline();
            }
            else if((rapport[a->id]>1 && !LCSrandom(3)) || !LCSrandom(10))
            {
               rapport_temp=10;
               switch(LCSrandom(4))
               {
               case 0:
                  addstr(cr->name, gamelog);
                  addstr("は幻覚作用で", gamelog);
                  addstr(a->name, gamelog);
                  addstr("を天使だと思っているようだ。", gamelog);
                  break;
               case 1:
                  addstr(cr->name);
                  addstr("は", gamelog);
                  addstr(a->name, gamelog);
                  addstr("がロナルド・レーガンだと思い喜んでいる!", gamelog);
                  break;
               case 2:
                  addstr(cr->name, gamelog);
                  addstr("は口ごもり、", gamelog);
                  addstr(a->name, gamelog);
                  techniques[TECHNIQUE_RESTRAIN] ? addstr("を抱きしめたいと言った", gamelog) : addstr("を抱きしめた", gamelog);
                  addstr("。", gamelog);
                  break;
               case 3:
                  addstr(cr->name, gamelog);
                  addstr("は", gamelog);
                  addstr(a->name, gamelog);
                  addstr("がカラフルであり続けることを望んだ。", gamelog);
                  break;
               }
               gamelog.newline();
            }
            else if((rapport[a->id]<-1 && LCSrandom(3)) || !LCSrandom(5))
            {
               attack=0;
               switch(LCSrandom(4))
               {
               case 0:
                  addstr(cr->name, gamelog);
                  addstr("は", gamelog);
                  addstr(a->name, gamelog);
                  addstr("がエイリアンに変身した恐怖で叫んだ。", gamelog);
                  break;
               case 1:
                  addstr(cr->name, gamelog);
                  addstr("は", gamelog);
                  if(!techniques[TECHNIQUE_RESTRAIN]) addstr("うずくまり、", gamelog);
                  addstr("悪夢が覚めることを望んだ。", gamelog);
                  break;
               case 2:
                  addstr(cr->name, gamelog);
                  addstr("は", gamelog);
                  addstr(a->name, gamelog);
                  addstr("が様々な悪魔に変身するのを見た。", gamelog);
                  break;
               case 3:
                  if(rapport[a->id]<-3)
                  {
                     addstr(cr->name, gamelog);
                     addstr("はヒトラーがここに来て", gamelog);
                     addstr(a->name, gamelog);
                     addstr("を殺害することを望んだ。", gamelog);
                  }
                  else
                  {
                     addstr(cr->name, gamelog);
                     addstr("は", gamelog);
                     addstr(a->name, gamelog);
                     addstr("にヒトラーの幻覚を見て叫んだ。", gamelog);
                  }
                  break;
               }
               gamelog.newline();
            }
            else
            {
               switch(LCSrandom(4))
               {
               case 0:
                  addstr(cr->name, gamelog);
                  addstr("は渦巻く光が", gamelog);
                  addstr(a->name, gamelog);
                  addstr("から発していると言った。", gamelog);
                  break;
               case 1:
                  addstr(cr->name, gamelog);
                  addstr("は変化する色から目を背けられない。", gamelog);
                  break;
               case 2:
                  addstr(cr->name, gamelog);
                  addstr("は", gamelog);
                  addstr(a->name, gamelog);
                  addstr("が変身した姿を見て大笑いした。", gamelog);
                  break;
               case 3:
                  addstr(cr->name, gamelog);
                  addstr("は犬のように吠えてうなった。", gamelog);
                  break;
               }
               gamelog.newline();
            }
         }

         //show_interrogation_sidebar(cr,a);

         getkey();

         if(cr->get_skill(SKILL_PSYCHOLOGY)>a->get_skill(SKILL_PSYCHOLOGY))
         {
            move(y++,0);
            switch(LCSrandom(4))
            {
            case 0:addstr(cr->name, gamelog);
                  addstr("は", gamelog);
                  addstr(a->name, gamelog);
                  addstr("と心理ゲームをした。", gamelog);
                  break;
            case 1:addstr(cr->name, gamelog);
                  addstr("はこれがどのような意味があるかわかっていた。そして考えを変えなかった。", gamelog);
                  break;
            case 2:addstr(cr->name, gamelog);
                  addstr("はリベラルの母がこれを許すのかと尋ねた。", gamelog);
                  break;
            case 3:addstr(cr->name, gamelog);
                  addstr("はこのような尋問には耐えられそうだ。", gamelog);
                  break;
            }
         }
         //Attempt to convert when the target is brutally treated will
         //just alienate them and make them cynical
         else if(techniques[TECHNIQUE_BEAT] || rapport_temp < -2)
         {
            move(y++,0);
            addstr(cr->name, gamelog);
            switch(LCSrandom(7))
            {
            case 0:addstr("は気にもせず何かつぶやいている。", gamelog);break;
            case 1:addstr("は何かささやいただけだった。", gamelog);break;
            case 2:addstr("は絶望し泣いた。", gamelog);break;
            case 3:addstr("はこの世界への希望を失った。", gamelog);break;
            case 4:addstr("との溝がさらに深まっただけだった。", gamelog);break;
            case 5:addstr("はおびえて", gamelog);addstr(a->name);addstr("と話すことができない。");break;
            case 6:addstr("はLCSをさらに憎むようになった。", gamelog);break;
            }
            gamelog.newline();
            if(a->skill_check(SKILL_SEDUCTION,DIFFICULTY_CHALLENGING))
            {
               //show_interrogation_sidebar(cr,a);

               getkey();

               move(y++,0);
               addstr(a->name, gamelog);
               switch(LCSrandom(7))
               {
               case 0:addstr("は保守の操り人形を慰めた。", gamelog);break;
               case 1:addstr("はチョコレートを分け合った。", gamelog);break;
               case 2:addstr("は泣きすがるために肩を貸した。", gamelog);break;
               case 3:addstr("は", gamelog);addstr(cr->name, gamelog);addstr("の痛みに理解を示した。", gamelog);break;
               case 4:addstr("は哀れな保守に心を開いた。", gamelog);break;
               case 5:addstr("は捕らわれの身であることを受け入れられるように手助けした。", gamelog);break;
               case 6:addstr("の忍耐と親切さが保守を混乱させている。", gamelog);break;
               }
               gamelog.newline();
               rapport[a->id]+=0.7f;
               if(rapport[a->id]>3)
               {
                  //show_interrogation_sidebar(cr,a);

                  getkey();

                  move(y++,0);
                  addstr(cr->name, gamelog);
                  switch(LCSrandom(7))
                  {
                  case 0:addstr("は", gamelog);
                         addstr(a->name, gamelog);
                         addstr("の同情にすがった。", gamelog); break;
                  case 1:addstr("は", gamelog);
                         addstr(a->name, gamelog);
                         addstr("に助けを求めた。", gamelog); break;
                  case 2:addstr("は自分は変わると約束した。", gamelog); break;
                  case 3:addstr("は幼年期の苦しみを明かした。", gamelog); break;
                  case 4:addstr("は", gamelog);
                         addstr(a->name, gamelog);
                         addstr("の親切さに感謝した。", gamelog); break;
                  case 5:addstr("は", gamelog);
                         addstr(a->name, gamelog);
                         addstr("の腕の中で泣いた。", gamelog); break;
                  case 6:addstr("は", gamelog);
                         addstr(a->name, gamelog);
                         addstr("に好意を持つようになった。", gamelog); break;
                  }
                  gamelog.newline();

                  if(rapport[a->id]>5) turned=1;
               }
            }

            if(cr->get_attribute(ATTRIBUTE_HEART,false)>1) cr->adjust_attribute(ATTRIBUTE_HEART,-1);
         }
         //Failure to break religious convictions
         else if(cr->get_skill(SKILL_RELIGION)>a->get_skill(SKILL_RELIGION)+a->get_skill(SKILL_PSYCHOLOGY) && !techniques[TECHNIQUE_DRUGS])
         {
            move(y++,0);
            switch(LCSrandom(4))
            {
            case 0:addstr(a->name);
                  addstr("は", gamelog);
                  addstr(cr->name, gamelog);
                  addstr("の宗教的信念を揺るがすことができなかった。", gamelog);
                  break;
            case 1:addstr("神が力を与える限り、", gamelog);addstr(cr->name, gamelog);
                  addstr("が崩れることはないだろう。", gamelog);
                  break;
            case 2:addstr(a->name, gamelog);
                  addstr("の", gamelog);
                  addstr(cr->name, gamelog);
                  addstr("の信仰への疑いは全て無駄だった。", gamelog);
                  break;
            case 3:addstr(cr->name, gamelog);
                  addstr("は保守的信仰心を穏やかに語った。", gamelog);
                  break;
            }
            gamelog.newline();

            a->train(SKILL_RELIGION,cr->get_skill(SKILL_RELIGION)*4);
         }
         //Failure to persuade entrenched capitalists
         else if(cr->get_skill(SKILL_BUSINESS)>a->get_skill(SKILL_BUSINESS)+a->get_skill(SKILL_PSYCHOLOGY) && !techniques[TECHNIQUE_DRUGS])
         {
            move(y++,0);
            switch(LCSrandom(4))
            {
            case 0:addstr(cr->name, gamelog);
                  addstr("は", gamelog);
                  addstr(a->name, gamelog);
                  addstr("の悲観的な経済観に動かされることはないだろう。", gamelog);
                  break;
            case 1:addstr(cr->name, gamelog);
                  addstr("はLCSが巨大企業に買収されて停止することを望んだ。", gamelog);
                  break;
            case 2:addstr(cr->name, gamelog);
                  addstr("は", gamelog);
                  addstr(a->name, gamelog);
                  addstr("に共産主義がなぜ失敗したかを説明した。", gamelog);
                  break;
            case 3:addstr(cr->name, gamelog);
                  addstr("はレーガノミクスについて支離滅裂につぶやいた。", gamelog);
                  break;
            }
            gamelog.newline();

            a->train(SKILL_BUSINESS,cr->get_skill(SKILL_BUSINESS)*4);
         }
         //Failure to persuade scientific minds
         else if(cr->get_skill(SKILL_SCIENCE)>a->get_skill(SKILL_SCIENCE)+a->get_skill(SKILL_PSYCHOLOGY) && !techniques[TECHNIQUE_DRUGS])
         {
            move(y++,0);
            switch(LCSrandom(4))
            {
            case 0:addstr(cr->name, gamelog);
                  addstr("は", gamelog);
                  addstr(a->name, gamelog);
                  addstr("の心の病を疑った。", gamelog);
                  break;
            case 1:addstr(cr->name, gamelog);
                  addstr("は原子力はなぜクリーンかを語った。", gamelog);
                  break;
            case 2:addstr(cr->name, gamelog);
                  addstr("は", gamelog);
                  addstr(a->name, gamelog);
                  addstr("にアルバート・アインシュタインのような顔をした。", gamelog);
                  break;
            case 3:addstr(cr->name, gamelog);
                  addstr("は", gamelog);
                  addstr(a->name, gamelog);
                  addstr("の科学に対する無知蒙昧さを嘆いた。", gamelog);
                  break;
            }
            gamelog.newline();

            a->train(SKILL_SCIENCE,cr->get_skill(SKILL_SCIENCE)*4);
         }
         //Target is swayed by Liberal Reason -- skilled interrogators, time held,
         //and rapport contribute to the likelihood of this
         else if(!(cr->attribute_check(ATTRIBUTE_WISDOM,attack/6)))
         {
            if(cr->juice>0)
            {
               cr->juice-=attack;
               if(cr->juice<0) cr->juice=0;
            }

            if(cr->get_attribute(ATTRIBUTE_HEART,false)<10)
               cr->adjust_attribute(ATTRIBUTE_HEART,+1);
            //Improve rapport with interrogator
            rapport[a->id]+=1.5;

            //Join LCS??
            //1) They were liberalized
            if(cr->get_attribute(ATTRIBUTE_HEART,true)>cr->get_attribute(ATTRIBUTE_WISDOM,true)+4) turned=1;
            //2) They were befriended
            if(rapport[a->id]>4) turned=1;

            move(y++,0);
            addstr(cr->name, gamelog);
            switch(LCSrandom(5))
            {
            case 0:addstr("の保守の信念が揺らいだ。", gamelog);break;
            case 1:addstr("はリベラルについて静かに考えている。", gamelog);break;
            case 2:addstr("はリベラルを理解し始めた。", gamelog);break;
            case 3:addstr("はリベラルへの理解を打ち明けた。", gamelog);break;
            case 4:addstr("はLCSの理想への共感をしぶしぶと認めた。", gamelog);break;
            }
            gamelog.newline();
            if(location[cr->worklocation]->mapped==0 && !LCSrandom(5))
            {
               move((++y)++,0);
               addstr(cr->name, gamelog);
               addstr("は", gamelog);
               addstr(location[cr->worklocation]->name, gamelog);
               addstr("の詳細な情報を明らかにした。", gamelog);
               gamelog.newline();
               move(y++,0);
               if(location[cr->worklocation]->type<=SITE_RESIDENTIAL_SHELTER)
               {
                  addstr("残念ながらLCSには役に立たないものだった。", gamelog);
               }
               else
               {
                  addstr(a->name, gamelog);
                  addstr("はそれを元に詳細な地図を作った。", gamelog);
               }
               gamelog.newline();
               location[cr->worklocation]->mapped=1;
               location[cr->worklocation]->hidden=0;
            }
         }
         //Target is not sold on the LCS arguments and holds firm
         //This is the worst possible outcome if you use props
         else if(!(cr->skill_check(SKILL_PERSUASION,a->get_attribute(ATTRIBUTE_HEART, true))) || techniques[TECHNIQUE_PROPS])
         {
            //Not completely unproductive; builds rapport
            rapport[a->id]+=0.2f;

            move(y++,0);
            addstr(cr->name, gamelog);
            addstr("はしっかりとしている。", gamelog);
            gamelog.newline();
         }
         //Target actually wins the argument so successfully that the Liberal
         //interrogator's convictions are the ones that are shaken
         else
         {
            //Consolation prize is that they end up liking the
            //liberal more
            rapport[a->id]+=0.5f;

            a->adjust_attribute(ATTRIBUTE_WISDOM,+1);

            move(y++,0);
            addstr(cr->name, gamelog);
            addstr("と", gamelog);
            addstr(a->name, gamelog);
            addstr("の立場が逆転した!", gamelog);
            gamelog.newline();

            //show_interrogation_sidebar(cr,a);
            getkey();

            move(y++,0);
            addstr(a->name, gamelog);
            addstr("は知恵で汚された!", gamelog);
            gamelog.newline();
         }

         //show_interrogation_sidebar(cr,a);
         getkey();
      }

      //Lead interrogator gets bonus experience
      if(!techniques[TECHNIQUE_KILL])
      {
         a->train(SKILL_PSYCHOLOGY,attack/2+1);
         //Others also get experience
         for(int i=0;i<len(temppool);i++) temppool[i]->train(SKILL_PSYCHOLOGY,attack/4+1);
      }

      //Possibly suicidal when heart is down to 1 and prisoner has already been
      //captive for a week without rescue
      if(!turned&&cr->alive&&cr->get_attribute(ATTRIBUTE_HEART,false)<=1&&LCSrandom(3)&&cr->joindays>6)
      {
         move(++y,0);

         //can't commit suicide if restrained
         if(LCSrandom(6)||techniques[TECHNIQUE_RESTRAIN])
         {
            set_color(COLOR_MAGENTA,COLOR_BLACK,0);
            addstr(cr->name, gamelog);
            //can't cut self if restrained
            switch(LCSrandom(5-techniques[TECHNIQUE_RESTRAIN]))
            {
            case 0: addstr("は死についてつぶやいた。", gamelog); break;
            case 1: addstr("は暗くふさぎこんでいる。", gamelog); break;
            case 2: addstr("は助かる望みを失った。", gamelog); break;
            case 3: addstr("は神と和解しようとしている。", gamelog); break;
            case 4: addstr("は自らを傷つけて血を流している。", gamelog); cr->blood-=LCSrandom(15)+10; break;
            }
            gamelog.newline();
         }
         else
         {
            set_color(COLOR_RED,COLOR_BLACK,1);
            addstr(cr->name, gamelog);
            addstr("は自ら命を絶った。", gamelog);
            gamelog.newline(); //TODO: Next message?
            cr->die();
         }
         y++;
         //show_interrogation_sidebar(cr,a);

         getkey();
      }

      //Death
      if(cr->alive==0||cr->blood<1)
      {
         //delete interrogation information
         delete intr;
         cr->die();

         stat_kills++;
         move(++y,0);
         set_color(COLOR_RED,COLOR_BLACK,1);
         addstr(cr->name, gamelog);
         addstr("は", gamelog);
         if(a)
         {
            addstr(a->name, gamelog);
            addstr("の尋問中に", gamelog);
         }
         else addstr("死んだ。", gamelog);
         set_color(COLOR_WHITE,COLOR_BLACK,0);
         y++;
         //show_interrogation_sidebar(cr,a);

         getkey();

         if(a)
         {
            if(LCSrandom(a->get_attribute(ATTRIBUTE_HEART,false)))
            {
               gamelog.newline();
               set_color(COLOR_GREEN,COLOR_BLACK,1);
               move(++y,0);
               addstr(a->name, gamelog);
               addstr("は吐き気を感じた。そして", gamelog);
               a->adjust_attribute(ATTRIBUTE_HEART,-1);
               move(++y,0);
               switch(LCSrandom(4))
               {
                  case 0:addstr("ゴミ箱に嘔吐した。", gamelog);break;
                  case 1:addstr("大量の酒を飲み眠った。", gamelog);break;
                  case 2:addstr("うずくまり泣いた。", gamelog);break;
                  case 3:addstr("床に倒れこんだ。", gamelog);break;
               }
            }
            else if(!LCSrandom(3))
            {
               gamelog.newline();
               set_color(COLOR_CYAN,COLOR_BLACK,1);
               move(++y,0);
               addstr(a->name, gamelog);
               addstr("はより冷酷になった。", gamelog);
               a->adjust_attribute(ATTRIBUTE_WISDOM,+1);
            }
         }
      }
      gamelog.nextMessage();
      delete[] _attack;
   }
   #ifdef AUTOENLIGHTEN
   turned=1;// Lucky!
   #endif

   if(turned&&cr->alive)
   {
      //clear_interrogation_sidebar();
      //delete interrogation information
      delete intr;
      set_color(COLOR_WHITE,COLOR_BLACK,1);
      move(++y,0);
      addstr("操り人形を啓蒙することができた! あなたのリベラルランクが上昇した!", gamelog);
      if(cr->get_attribute(ATTRIBUTE_HEART,true)>7 &&
         cr->get_attribute(ATTRIBUTE_WISDOM,true)>2 &&
        !LCSrandom(4) && (cr->flag & CREATUREFLAG_KIDNAPPED))
      {
         move(++y,0);
         gamelog.newline();
         addstr("その心変わりならば、警察も誘拐されたとは考えないだろう。", gamelog);
         //Actually liberalized -- they'll clean up the kidnapping story
         cr->flag&=~CREATUREFLAG_MISSING;
         cr->flag&=~CREATUREFLAG_KIDNAPPED;
      }
      cr->flag|=CREATUREFLAG_BRAINWASHED;

      for(int p=0;p<len(pool);p++)
         if(pool[p]->activity.type==ACTIVITY_HOSTAGETENDING&&pool[p]->activity.arg==cr->id)
            pool[p]->activity.type=ACTIVITY_NONE;

      y+=2;
      liberalize(*cr,false);
      cr->hireid=a->id;
      stat_recruits++;

      if(location[cr->worklocation]->mapped==0 || location[cr->worklocation]->hidden==1)
      {
         gamelog.newline();
         move(y,0);
         addstr(cr->name, gamelog);
         addstr("は", gamelog);
         addstr(location[cr->worklocation]->name, gamelog);
         addstr("の詳細な情報を明らかにした。", gamelog);
         gamelog.newline();
         move(++y,0);
         if(location[cr->worklocation]->type<=SITE_RESIDENTIAL_SHELTER)
            addstr("残念ながらLCSには役に立たないものだった。", gamelog);
         else
         {
            addstr(a->name, gamelog);
            addstr("はその情報を元に地図を作ることができた。", gamelog);
         }
         location[cr->worklocation]->mapped=1;
         location[cr->worklocation]->hidden=0;
         y+=2;
      }

      if(cr->flag & CREATUREFLAG_MISSING && !(cr->flag & CREATUREFLAG_KIDNAPPED))
      {
         getkey();

         erase();
         set_color(COLOR_WHITE,COLOR_BLACK,1);
         move(y=1,0);
         gamelog.newline();
         addstr("失踪した", gamelog);
         addstr(cr->name, gamelog);
         addstr("の行方は知られていない。", gamelog);
         sleeperize_prompt(*cr,*a,y+=2);
         cr->flag&=~CREATUREFLAG_MISSING;
         gamelog.nextMessage();

         return;
      }
   }

   if(cr->align==1||!cr->alive) for(int p=0;p<len(pool);p++)
   {
      if(!pool[p]->alive) continue;
      if(pool[p]->activity.type==ACTIVITY_HOSTAGETENDING&&pool[p]->activity.arg==cr->id)
         pool[p]->activity.type=ACTIVITY_NONE;
   }

   gamelog.nextMessage();

   set_color(COLOR_WHITE,COLOR_BLACK,0);
   move(24,0);
   addstr("何かキーを押すと続く。");

   getkey();
}
