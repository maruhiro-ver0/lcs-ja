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

enum bouncer_reject_reason
{
   REJECTED_CCS,
   REJECTED_NUDE,
   REJECTED_WEAPONS,
   REJECTED_UNDERAGE,
   REJECTED_FEMALEISH,
   REJECTED_FEMALE,
   REJECTED_BLOODYCLOTHES,
   REJECTED_DAMAGEDCLOTHES,
   REJECTED_CROSSDRESSING,
   REJECTED_GUESTLIST,
   REJECTED_DRESSCODE,
   REJECTED_SECONDRATECLOTHES,
   REJECTED_SMELLFUNNY,
   NOT_REJECTED
};

void special_bouncer_greet_squad()
{
   // add a bouncer if there isn't one in the first slot
   if(!sitealarm && location[cursite]->renting!=RENTING_PERMANENT)
   {
      if(location[cursite]->renting==RENTING_CCS)
      {
         makecreature(encounter[0],CREATURE_CCS_VIGILANTE);
         makecreature(encounter[1],CREATURE_CCS_VIGILANTE);
      }
      else if(!encounter[0].exists || encounter[0].type!=CREATURE_BOUNCER)
      {
         makecreature(encounter[0],CREATURE_BOUNCER);
         makecreature(encounter[1],CREATURE_BOUNCER);
      }
   }
}

void special_bouncer_assess_squad()
{
   if(location[cursite]->renting==RENTING_PERMANENT) return;

   bool autoadmit=0;
   char sleepername[80];
   for(int e=0;e<ENCMAX;e++)encounter[e].exists=0;

   special_bouncer_greet_squad();

   for(int p=0;p<len(pool);p++)
   {
      if(pool[p]->base==cursite&&pool[p]->type==CREATURE_BOUNCER)
      {
         autoadmit=1;
         strcpy(sleepername,pool[p]->name);
         strcpy(encounter[0].name,sleepername);
         encounter[0].align=1;
         break;
      }
   }
   //clearmessagearea();
   set_color(COLOR_WHITE,COLOR_BLACK,1);
   move(16,1);
   if(autoadmit)
   {
      addstr("潜伏者の", gamelog);
      addstr(sleepername, gamelog);
      addstr("が薄ら笑いをしながら部隊を中にいれた。", gamelog);
      gamelog.newline();

      levelmap[locx][locy][locz].special=-1;
   }
   else
   {
      if(location[cursite]->renting==RENTING_CCS)
         addstr("保守のロクデナシに遮られた。", gamelog);
      else
         addstr("部隊はガードマンにチェックされた。", gamelog);
      gamelog.newline();
      levelmap[locx][locy][locz].special=SPECIAL_CLUB_BOUNCER_SECONDVISIT;
   }
   printencounter();

   getkey();

   char rejected=NOT_REJECTED;

   // Size up the squad for entry
   if(!autoadmit)
   {
      for(int s=0;s<6;s++)
      {
         if(activesquad->squad[s])
         {
            // Wrong clothes? Gone
            if(activesquad->squad[s]->is_naked() && activesquad->squad[s]->animalgloss!=ANIMALGLOSS_ANIMAL)
               if(rejected>REJECTED_NUDE)rejected=REJECTED_NUDE;
            if(!hasdisguise(*activesquad->squad[s]))
               if(rejected>REJECTED_DRESSCODE)rejected=REJECTED_DRESSCODE;
            // Busted, cheap, bloody clothes? Gone
            if(activesquad->squad[s]->get_armor().is_bloody())
               if(rejected>REJECTED_BLOODYCLOTHES)rejected=REJECTED_BLOODYCLOTHES;
            if(activesquad->squad[s]->get_armor().is_damaged())
               if(rejected>REJECTED_DAMAGEDCLOTHES)rejected=REJECTED_DAMAGEDCLOTHES;
            if(activesquad->squad[s]->get_armor().get_quality()!=1)
               if(rejected>REJECTED_SECONDRATECLOTHES)rejected=REJECTED_SECONDRATECLOTHES;
            // Suspicious weapons? Gone
            if(weaponcheck(*activesquad->squad[s])>0)
               if(rejected>REJECTED_WEAPONS)rejected=REJECTED_WEAPONS;
            // Fail a tough disguise check? Gone
            if(disguisesite(sitetype) && !(activesquad->squad[s]->skill_check(SKILL_DISGUISE,DIFFICULTY_CHALLENGING)))
               if(rejected>REJECTED_SMELLFUNNY)rejected=REJECTED_SMELLFUNNY;
            // Underage? Gone
            if(activesquad->squad[s]->age<18)
               if(rejected>REJECTED_UNDERAGE)rejected=REJECTED_UNDERAGE;
            // Not a gentleman by their definition?
            if(sitetype==SITE_BUSINESS_CIGARBAR &&
               (activesquad->squad[s]->gender_conservative!=GENDER_MALE ||
                activesquad->squad[s]->gender_liberal == GENDER_FEMALE) &&
                law[LAW_WOMEN]<1)
            {
               // Are you passing as a man? Are you skilled enough to pull it off?
               if(activesquad->squad[s]->gender_liberal == GENDER_FEMALE)
               {
                  // Not a man by your own definition either
                  if(rejected>REJECTED_FEMALE)rejected=REJECTED_FEMALE;
               }
               else if(disguisesite(sitetype) && !(activesquad->squad[s]->skill_check(SKILL_DISGUISE,DIFFICULTY_HARD)) && law[LAW_GAY]!=2)
               {
                  // Not skilled enough to pull it off
                  if(rejected>REJECTED_FEMALEISH)rejected=REJECTED_FEMALEISH;
               }
            }
            // High security in gentleman's club? Gone
            if(sitetype==SITE_BUSINESS_CIGARBAR && location[cursite]->highsecurity)
               if(rejected>REJECTED_GUESTLIST)rejected=REJECTED_GUESTLIST;
            if(location[cursite]->renting==RENTING_CCS && location[cursite]->type!=SITE_BUSINESS_BARANDGRILL)
               rejected=REJECTED_CCS;
         }
      }
      move(17,1);
      switch(rejected)
      {
      case REJECTED_CCS:
         set_color(COLOR_RED,COLOR_BLACK,1);
         switch(LCSrandom(11))
         {
         case 0:addstr("「すみませんが…ヘヘ…IDを見せてもらえますか? 」", gamelog);break;
         case 1:addstr("「おっと…入れると思っているのか? 」", gamelog);break;
         case 2:addstr("「このバカをつまみ出せ。ケッ。」", gamelog);break;
         case 3:addstr("「ゴミ箱の住民め、何のようだ? 」", gamelog);break;
         case 4:addstr("「蜂の巣をかき回したいのか。バカめ。」", gamelog);break;
         case 5:addstr("「さあ来い。俺を殴れ。やってみろ。」", gamelog);break;
         case 6:addstr("「俺に殺されたくはないだろう。」", gamelog);break;
         case 7:addstr("「やあ。遺言は書いたか? 」", gamelog);break;
         case 8:addstr("「ああ、トラブルが来た。トラブルは大好きだ。」", gamelog);break;
         case 9:addstr("「そこのプランターに埋めてやるぞ。」", gamelog);break;
         case 10:addstr("「血の色を検査してもよろしいでしょうか? 」", gamelog);break;
         }
         break;
      case REJECTED_NUDE:
         set_color(COLOR_RED,COLOR_BLACK,1);
         switch(LCSrandom(4))
         {
         case 0:addstr("「スカートなし、パンツなし、入場なし。」", gamelog);break;
         case 1:addstr("「何か服を着てくれ! もうイヤだ。」", gamelog);break;
         case 2:addstr("「ダメ! ダメだ、裸で来てはならない! 神よ!!」", gamelog);break;
		 case 3:addstr("「靴なし、スカートなし。それでは入れない。」", gamelog);break;
         }
         break;
      case REJECTED_UNDERAGE:
         set_color(COLOR_RED,COLOR_BLACK,1);
         switch(LCSrandom(5))
         {
         case 0:addstr("「ハハハ、数年後にまた来るんだな。」", gamelog);break;
         case 1:addstr("「子供用クラブを探してくれ。」", gamelog);break;
         case 2:addstr("「18には見えないな。」", gamelog);break;
         case 3:addstr("「子供部屋に帰るんだ。」", gamelog);break;
         case 4:addstr("「お母さんはどこ? 」", gamelog);break;
         }
         break;
      case REJECTED_FEMALE:
         set_color(COLOR_RED,COLOR_BLACK,1);
         switch(LCSrandom(4))
         {
         case 0:addstr("「お帰りください、マダム。当クラブは男性専用です。」", gamelog);break;
         case 1:addstr("「ここは手芸サークルではありません、マダム。」", gamelog);break;
         case 2:addstr("「失礼ですがマダム、ここは男性専用です。」", gamelog);break;
         case 3:addstr("「貴女の旦那はどちらへ? 」", gamelog);break;
         }
         break;
      case REJECTED_FEMALEISH:
         set_color(COLOR_RED,COLOR_BLACK,1);
         switch(LCSrandom(3))
         {
         case 0:addstr("「私には/本当の/男性には見えないのですが…」", gamelog);break;
         case 1:addstr("「わかっていると思いますが…『他の』男性はあなたとは違います。」", gamelog);break;
         case 2:addstr("「ううむ…入れるわけにはいきません、マダム、サー。どうやっても。」", gamelog);break;
         }
         break;
      case REJECTED_DRESSCODE:
         set_color(COLOR_RED,COLOR_BLACK,1);
         switch(LCSrandom(3))
         {
         case 0:addstr("「ドレスコードをチェックしてください。」", gamelog);break;
         case 1:addstr("「当クラブはドレスコードがあります。」", gamelog);break;
         case 2:addstr("「そのような服装では入れるわけにはいきません。」", gamelog);break;
         }
         break;
      case REJECTED_SMELLFUNNY:
         set_color(COLOR_RED,COLOR_BLACK,1);
         switch(LCSrandom(6))
         {
         case 0:addstr("「何だ、怪しい奴め。」", gamelog);break;
         case 1:addstr("「あなたは入れません。なぜなら、俺がそう言ったからだ。」", gamelog);break;
         case 2:addstr("「何か様子がおかしいのだが。」", gamelog);break;
         case 3:addstr("「シャワーを浴びてこい。」", gamelog);break;
         case 4:addstr("「他の客の嫌がらせに来たのか? 」", gamelog);break;
         case 5:
                if(law[LAW_FREESPEECH]==-2)addstr("「帰れ[不快な人]。」", gamelog);
                else if(law[LAW_FREESPEECH]==2)addstr("「帰れクソ野郎。」", gamelog);
                else addstr("「帰れバカ。」", gamelog);break;
         }
         break;
      case REJECTED_BLOODYCLOTHES:
         set_color(COLOR_RED,COLOR_BLACK,1);
         switch(LCSrandom(5))
         {
         case 0:addstr("「おい! その服はどうしたんだ? 」", gamelog);break;
         case 1:addstr("「絶対に入れません。服をきれいにしてください。」", gamelog);break;
         case 2:addstr("「ここはゴスクラブではない。血まみれの服はここまでだ。」", gamelog);break;
         case 3:addstr("「う、その服は洗うか…着替えるかしろ。」", gamelog);break;
         case 4:addstr("「服に何をこぼしたんだ? 」", gamelog);break;
         case 5:addstr("「その服の赤ワインをどうにかしてから来い。」", gamelog);break;
         }
         break;
      case REJECTED_DAMAGEDCLOTHES:
         set_color(COLOR_RED,COLOR_BLACK,1);
         switch(LCSrandom(2))
         {
         case 0:addstr("「おい! その服はどうしたんだ? 」", gamelog);break;
         case 1:addstr("「ここはゴスクラブではない。引き裂かれた服はここまでだ。」", gamelog);break;
         }
         break;
      case REJECTED_SECONDRATECLOTHES:
         set_color(COLOR_RED,COLOR_BLACK,1);
         switch(LCSrandom(2))
         {
         case 0:addstr("「その服は自分で作ったものだな。」", gamelog);break;
         case 1:addstr("「そのひどい服は流行っているのか。知らなかったな。」", gamelog);break;
         }
         break;
      case REJECTED_WEAPONS:
         set_color(COLOR_RED,COLOR_BLACK,1);
         switch(LCSrandom(5))
         {
         case 0:addstr("「武器の持ち込みは禁止されています。」", gamelog);break;
         case 1:addstr("「それを持ったまま入れるわけにはいかないな。」", gamelog);break;
         case 2:addstr("「それを持ち込ませるわけにはいかないな。」", gamelog);break;
         case 3:addstr("「武装して来たならば、ハイキングにでも行って来いと言うしかない。」", gamelog);break;
         case 4:addstr("「真の男は拳で戦うものだ。そしてお前はそうではない。入れるわけにはいかない。」", gamelog);break;
         }
         break;
      case REJECTED_GUESTLIST:
         set_color(COLOR_RED,COLOR_BLACK,1);
         addstr("「当クラブは紹介がなければ入れません。」", gamelog);
         break;
      case NOT_REJECTED:
         set_color(COLOR_GREEN,COLOR_BLACK,1);

         switch(LCSrandom(4))
         {
         case 0:addstr("「礼儀正しく。そして飲み過ぎないように。」", gamelog);break;
         case 1:addstr("「今扉を開けます。」", gamelog);break;
         case 2:addstr("「えー、了解。入ってください。」", gamelog);break;
         case 3:addstr("「お入りください。」", gamelog);break;
         }
         break;
      }
      gamelog.newline();

      getkey();
   }
   else encounter[0].exists=0;
   set_color(COLOR_WHITE,COLOR_BLACK,1);
   for(int dx=-1; dx<=1; dx++)
   for(int dy=-1; dy<=1; dy++)
   {
      if(levelmap[locx+dx][locy+dy][locz].flag & SITEBLOCK_DOOR)
      {
         if(rejected<NOT_REJECTED)
         {
            levelmap[locx+dx][locy+dy][locz].flag |= SITEBLOCK_LOCKED;
            levelmap[locx+dx][locy+dy][locz].flag |= SITEBLOCK_CLOCK;
         }
         else levelmap[locx+dx][locy+dy][locz].flag &= ~SITEBLOCK_DOOR;
      }
   }
   encounter[0].cantbluff=1;


}

void special_lab_cosmetics_cagedanimals()
{
   while(true)
   {
      clearmessagearea();

      set_color(COLOR_WHITE,COLOR_BLACK,1);
      move(16,1);
      addstr("ケージの中に白い毛のウサギが見える。", gamelog);
      gamelog.newline();
      move(17,1);
      addstr("解放するか? (Yes / No)");

      int c=getkey();

      if(c=='y')
      {
         char actual;

         if(unlock(UNLOCK_CAGE,actual))
         {
            int time=20+LCSrandom(10);
            if(time<1)time=1;
            if(sitealarmtimer>time||sitealarmtimer==-1)sitealarmtimer=time;

            sitecrime++;
            juiceparty(3,100);
            sitestory->crime.push_back(CRIME_FREE_RABBITS);
            criminalizeparty(LAWFLAG_VANDALISM);
         }

         if(actual)
         {
            alienationcheck(0);
            noticecheck(-1);
            levelmap[locx][locy][locz].special=-1;
         }

         return;
      }
      else if(c=='n')return;
   }
}



void special_readsign(int sign)
{
   clearmessagearea();
   set_color(COLOR_WHITE,COLOR_BLACK,1);

   switch(sign) //TODO: Log these?
   {
   case SPECIAL_SIGN_ONE:
      switch(location[cursite]->type)
      {
      default:
         move(16,1);
         addstr("『失敗しない最善の方法は成功することだ。』");
         break;
      case SITE_INDUSTRY_NUCLEAR:
         move(16,1);
         addstr("NPP原子力発電所へようこそ。資料館の");
         move(17,1);
         addstr("展示とお買い物をお楽しみください。");
         break;
      case SITE_RESIDENTIAL_TENEMENT:
      case SITE_RESIDENTIAL_APARTMENT:
      case SITE_RESIDENTIAL_APARTMENT_UPSCALE:
         move(16,1);
         addstr("管理人のオフィスは最初の扉を左です。");
         break;
      }
      break;
   case SPECIAL_SIGN_TWO:
      switch(location[cursite]->type)
      {
      default:
         move(16,1);
         addstr("『すばらしい仕事はすばらしい人々によって成し遂げられる。』");
         break;
      }
      break;
   case SPECIAL_SIGN_THREE:
      switch(location[cursite]->type)
      {
      default:
         move(16,1);
         addstr("従業員専用");
         break;
      }
      break;
   }

   getkey();
}



void special_nuclear_onoff()
{
   while(true)
   {
      clearmessagearea();

      set_color(COLOR_WHITE,COLOR_BLACK,1);
      if(law[LAW_NUCLEARPOWER]==2)
      {
         move(16,1);
         addstr("ここは核廃棄施設のコントロールルームだ。", gamelog);
         gamelog.newline();
         move(17,1);
         addstr("核廃棄物を放出するか? (Yes / No)");
      }
      else
      {
         move(16,1);
         addstr("ここは原子力発電所のコントロールルームだ。", gamelog);
         gamelog.newline();
         move(17,1);
         addstr("原子炉の設定をいじるか? (Yes / No)");
      }

      int c=getkey();

      if(c=='y')
      {
         clearmessagearea();
         levelmap[locx][locy][locz].special=-1;

         char max=DIFFICULTY_HARD;
         Creature* maxs=0;

         for(int p=0;p<6;p++)
         {
            if(activesquad->squad[p]!=NULL&&activesquad->squad[p]->alive)
            {
               if(activesquad->squad[p]->skill_check(SKILL_SCIENCE,max))
               {
                  maxs=activesquad->squad[p];
                  break;
               }
            }
         }

         if(maxs)
         {
            set_color(COLOR_WHITE,COLOR_BLACK,1);
            move(16,1);
            addstr(maxs->name, gamelog);
            addstr("は赤いボタンを押した!", gamelog);
            gamelog.newline();

            getkey();

            move(17,1);
            addstr(".", gamelog);

            getkey();

            addstr(".", gamelog);

            getkey();

            addstr(".", gamelog);

            getkey();

            if(law[LAW_NUCLEARPOWER]==2)
            {
               move(17,1);
               addstr("核廃棄物は州の水源に流れ込んだ!", gamelog);
               gamelog.newline();
               change_public_opinion(VIEW_NUCLEARPOWER,15,0,95);
               change_public_opinion(VIEW_LIBERALCRIMESQUADPOS,-50,0,0);

               getkey();

               juiceparty(40,1000); // Instant juice!
			      sitecrime+=25; //Shutdown Site

               sitestory->crime.push_back(CRIME_SHUTDOWNREACTOR);

            }
            else
            {
               move(16,1);
               addstr("耳をつんざくようなアラーム音が鳴り響いた!", gamelog);
               gamelog.newline();
               addstr("                "); // Remove remaining part of previous text.
               move(17,1);
               addstr("原子炉はオーバーヒートだ!", gamelog);
               gamelog.newline();
               change_public_opinion(VIEW_NUCLEARPOWER,15,0,95);

               getkey();

               juiceparty(100,1000); // Instant juice!
			      sitecrime+=50; //Shutdown Site

               sitestory->crime.push_back(CRIME_SHUTDOWNREACTOR);
            }
         }
         else
         {
            set_color(COLOR_WHITE,COLOR_BLACK,1);
            move(16,1);
            addstr("大きな警報音と様々な試みの失敗の後、", gamelog);
            move(17,1);
            addstr("部隊は脅迫メモを残して引き上げることにした。", gamelog);
            gamelog.newline();

            getkey();

            juiceparty(15,500);
         }
         sitealarm=1;
         alienationcheck(1);
         levelmap[locx][locy][locz].special=-1;
         sitecrime+=5;
         criminalizeparty(LAWFLAG_TERRORISM);

         return;
      }
      else if(c=='n')return;
   }
}



void special_lab_genetic_cagedanimals()
{
   while(true)
   {
      clearmessagearea();

      set_color(COLOR_WHITE,COLOR_BLACK,1);
      move(16,1);
      addstr("ケージの中に恐ろしく異様な姿の生き物が見える。", gamelog);
      gamelog.newline();
      move(17,1);
      addstr("解放するか? (Yes / No)");

      int c=getkey();

      if(c=='y')
      {
         char actual;

         if(unlock(UNLOCK_CAGE_HARD,actual))
         {
            int time=20+LCSrandom(10);
            if(time<1)time=1;
            if(sitealarmtimer>time||sitealarmtimer==-1)sitealarmtimer=time;

            sitecrime++;
            juiceparty(5,200);
            sitestory->crime.push_back(CRIME_FREE_BEASTS);
            criminalizeparty(LAWFLAG_VANDALISM);

            if(!LCSrandom(2))
            {
               clearmessagearea();

               set_color(COLOR_WHITE,COLOR_BLACK,1);
               move(16,1);
               addstr("ああ、思えばそれは保守的考えだったかもしれない…", gamelog);
               gamelog.newline();

               int numleft=LCSrandom(6)+1;
               for(int e=0;e<ENCMAX;e++)
               {
                  if(!encounter[e].exists)
                  {
                     makecreature(encounter[e],CREATURE_GENETIC);
                     numleft--;
                  }
                  if(numleft==0)break;
               }

               if(mode==GAMEMODE_CHASECAR||
                  mode==GAMEMODE_CHASEFOOT)printchaseencounter();
               else printencounter();

               getkey();

               sitealarm=1;
               alienationcheck(1);
            }
            else
            {
               alienationcheck(0);
            }
         }
         else if(actual)
         {
            noticecheck(-1);
         }

         if(actual)
         {
            levelmap[locx][locy][locz].special=-1;
         }

         return;
      }
      else if(c=='n')return;
   }
}



void special_policestation_lockup()
{
   while(true)
   {
      clearmessagearea();

      set_color(COLOR_WHITE,COLOR_BLACK,1);
      move(16,1);
      addstr("留置された人々がいる。", gamelog);
      gamelog.newline();
      move(17,1);
      addstr("解放するか? (Yes / No)");

      int c=getkey();

      if(c=='y')
      {
         char actual;

         if(unlock(UNLOCK_CELL,actual))
         {
            int numleft=LCSrandom(8)+2;
            for(int e=0;e<ENCMAX;e++)
            {
               if(!encounter[e].exists)
               {
                  makecreature(encounter[e],CREATURE_PRISONER);
                  numleft--;
               }
               if(numleft==0)break;
            }

            juiceparty(50,1000);
            sitecrime+=20;

            int time=20+LCSrandom(10);
            if(time<1)time=1;
            if(sitealarmtimer>time||sitealarmtimer==-1)sitealarmtimer=time;

            if(mode==GAMEMODE_CHASECAR||
                  mode==GAMEMODE_CHASEFOOT)printchaseencounter();
            else printencounter();
            refresh();

            partyrescue(SPECIAL_POLICESTATION_LOCKUP);
         }

         if(actual)
         {
            alienationcheck(1);
            noticecheck(-1,DIFFICULTY_HARD);
            levelmap[locx][locy][locz].special=-1;
            sitecrime+=2;
            sitestory->crime.push_back(CRIME_POLICE_LOCKUP);
            criminalizeparty(LAWFLAG_HELPESCAPE);
         }

         return;
      }
      else if(c=='n')return;
   }
}



void special_courthouse_lockup()
{
   while(true)
   {
      clearmessagearea();

      set_color(COLOR_WHITE,COLOR_BLACK,1);
      move(16,1);
      addstr("拘置された審理中の人々がいる。", gamelog);
      gamelog.newline();
      move(17,1);
      addstr("解放するか? (Yes / No)");

      int c=getkey();

      if(c=='y')
      {
         char actual;

         if(unlock(UNLOCK_CELL,actual))
         {
            int numleft=LCSrandom(8)+2;
            for(int e=0;e<ENCMAX;e++)
            {
               if(!encounter[e].exists)
               {
                  makecreature(encounter[e],CREATURE_PRISONER);
                  numleft--;
               }
               if(numleft==0)break;
            }

            juiceparty(50,1000);
            sitecrime+=20;

            int time=20+LCSrandom(10);
            if(time<1)time=1;
            if(sitealarmtimer>time||sitealarmtimer==-1)sitealarmtimer=time;

            if(mode==GAMEMODE_CHASECAR||
                  mode==GAMEMODE_CHASEFOOT)printchaseencounter();
            else printencounter();
            refresh();

            partyrescue(SPECIAL_COURTHOUSE_LOCKUP);
         }

         if(actual)
         {
            alienationcheck(1);
            noticecheck(-1,DIFFICULTY_HARD);
            levelmap[locx][locy][locz].special=-1;
            sitecrime+=3;
            sitestory->crime.push_back(CRIME_COURTHOUSE_LOCKUP);
            criminalizeparty(LAWFLAG_HELPESCAPE);
         }

         return;
      }
      else if(c=='n')return;
   }
}



void special_courthouse_jury()
{
   int p;
   if(sitealarm||sitealienate)
   {
      clearmessagearea();

      set_color(COLOR_WHITE,COLOR_BLACK,1);
      move(16,1);
      addstr("ここには少し前まで", gamelog);
      move(17,1);
      addstr("人がいたようだ。", gamelog);
      gamelog.newline();

      getkey();

      return;
   }

   while(true)
   {
      clearmessagearea();

      set_color(COLOR_WHITE,COLOR_BLACK,1);
      move(16,1);
      addstr("議論中の陪審員がいる!", gamelog);
      gamelog.newline();
      move(17,1);
      addstr("彼らに介入するか? (Yes / No)");

      int c=getkey();

      if(c=='y')
      {
         levelmap[locx][locy][locz].special=-1;

         char succeed=0;

         int maxattack=0;
         int maxp = -1;

         for(p=0;p<6;p++)
         {
            if(activesquad->squad[p]!=NULL)
            {
               if(activesquad->squad[p]->alive)
               {
                  if(activesquad->squad[p]->get_attribute(ATTRIBUTE_CHARISMA,true)+
                     activesquad->squad[p]->get_attribute(ATTRIBUTE_INTELLIGENCE,true)+
                     activesquad->squad[p]->get_skill(SKILL_PERSUASION)+
                     activesquad->squad[p]->get_skill(SKILL_LAW)>maxattack)
                  {
                     maxattack = activesquad->squad[p]->get_attribute(ATTRIBUTE_CHARISMA,true)+
                                 activesquad->squad[p]->get_attribute(ATTRIBUTE_INTELLIGENCE,true)+
                                 activesquad->squad[p]->get_skill(SKILL_PERSUASION)+
                                 activesquad->squad[p]->get_skill(SKILL_LAW);
                     maxp = p;
                  }
               }
            }
         }

         if(maxp > -1)
         {
            int p=maxp;

            activesquad->squad[p]->train(SKILL_PERSUASION,20);
            activesquad->squad[p]->train(SKILL_LAW,20);

            if(activesquad->squad[p]->skill_check(SKILL_PERSUASION,DIFFICULTY_HARD) &&
               activesquad->squad[p]->skill_check(SKILL_LAW,DIFFICULTY_CHALLENGING))succeed=1;

            if(succeed)
            {
               clearmessagearea();

               set_color(COLOR_WHITE,COLOR_BLACK,1);
               move(16,1);
               addstr(activesquad->squad[p]->name, gamelog);
               addstr("は12人の怒れる男のように振る舞い、", gamelog);
               addstr(" works the room like in Twelve Angry Men, and the jury ", gamelog);
               move(17,1);
               addstr("陪審員が", gamelog);//XXX: This is very awkward grammar.
               switch(LCSrandom(16))     // Fixed. -Fox
               {
                  case 0:addstr("殺人", gamelog);break;
                  case 1:addstr("傷害", gamelog);break;
                  case 2:addstr("窃盗", gamelog);break;
                  case 3:addstr("路上強盗", gamelog);break;
                  case 4:addstr("侵入窃盗", gamelog);break;
                  case 5:addstr("器物損壊", gamelog);break;
                  case 6:addstr("公共物破壊", gamelog);break;
                  case 7:addstr("文書による名誉毀損", gamelog);break;
                  case 8:addstr("口頭での名誉毀損", gamelog);break;
                  case 9:addstr("ソドミー法違反", gamelog);break;
                  case 10:addstr("司法妨害", gamelog);break;
                  case 11:addstr("不法侵入", gamelog);break;
                  case 12:addstr("公然猥褻", gamelog);break;
                  case 13:addstr("放火", gamelog);break;
                  case 14:addstr("逮捕抵抗", gamelog);break;
                  case 15:addstr("脱税", gamelog);break;
               }
               addstr("の容疑を有罪で一致するのを止めた。", gamelog);
               gamelog.newline();

               getkey();

               alienationcheck(0);
               noticecheck(-1);

               //INSTANT JUICE BONUS
               addjuice(*(activesquad->squad[p]),25,200);
            }
            else
            {
               clearmessagearea();

               set_color(COLOR_WHITE,COLOR_BLACK,1);
               move(16,1);
               addstr(activesquad->squad[p]->name, gamelog);

               addstr("は説得できなかった…", gamelog);
               gamelog.newline();

               getkey();

               int numleft=12;
               for(int e=0;e<ENCMAX;e++)
               {
                  if(!encounter[e].exists)
                  {
                     makecreature(encounter[e],CREATURE_JUROR);
                     numleft--;
                  }
                  if(numleft==0)break;
               }

               if(mode==GAMEMODE_CHASECAR||
                  mode==GAMEMODE_CHASEFOOT)printchaseencounter();
               else printencounter();
               refresh();

               sitealarm=1;
               sitealienate=2;
               sitecrime+=10;
               sitestory->crime.push_back(CRIME_JURYTAMPERING);

               criminalizeparty(LAWFLAG_JURY);
            }
         }

         return;
      }
      else if(c=='n')return;
   }
}



void special_prison_control(short prison_control_type)
{
   while(true)
   {
      clearmessagearea();

      set_color(COLOR_WHITE,COLOR_BLACK,1);
      move(16,1);
      addstr("ここは", gamelog);
      if(prison_control_type==SPECIAL_PRISON_CONTROL_LOW)
         addstr("低セキュリティ", gamelog);
      else if(prison_control_type==SPECIAL_PRISON_CONTROL_MEDIUM)
         addstr("中セキュリティ", gamelog);
      else if(prison_control_type==SPECIAL_PRISON_CONTROL_HIGH)
         addstr("高セキュリティ", gamelog);
      addstr("囚人管理室だ。", gamelog);
      gamelog.newline();
      move(17,1);
      addstr("囚人を解放するか? (Yes / No)");

      int c=getkey();

      if(c=='y')
      {
         int numleft=LCSrandom(8)+2;
         if(prison_control_type==SPECIAL_PRISON_CONTROL_LOW)
         {
            switch(law[LAW_DEATHPENALTY])
            {
               case -1: numleft=LCSrandom(6)+2;break;
               case -2: numleft=LCSrandom(3)+1;break;
            }
         }
         else if(prison_control_type==SPECIAL_PRISON_CONTROL_MEDIUM)
         {
            switch(law[LAW_DEATHPENALTY])
            {
               case 2: numleft=LCSrandom(4)+1;
               case 1: numleft=LCSrandom(6)+1;
            }
         }
         else if(prison_control_type==SPECIAL_PRISON_CONTROL_HIGH)
         {
            switch(law[LAW_DEATHPENALTY])
            {
               case  2: numleft=0;break;
               case  1: numleft=LCSrandom(4);break;
               case -1: numleft+=LCSrandom(4);break;
               case -2: numleft+=LCSrandom(4)+2;break;
            }
         }

         for(int e=0;e<ENCMAX;e++)
         {
            if(!encounter[e].exists)
            {
               makecreature(encounter[e],CREATURE_PRISONER);
               numleft--;
            }
            if(numleft==0)break;
         }

         int time=20+LCSrandom(10);
         if(time<1)time=1;
         if(sitealarmtimer>time||sitealarmtimer==-1)sitealarmtimer=time;

         if(mode==GAMEMODE_CHASECAR||
                  mode==GAMEMODE_CHASEFOOT)printchaseencounter();
         else printencounter();
         refresh();

         partyrescue(prison_control_type);

         alienationcheck(1);
         noticecheck(-1);
         levelmap[locx][locy][locz].special=-1;
         sitecrime+=30;
         juiceparty(50,1000);
         sitestory->crime.push_back(CRIME_PRISON_RELEASE);
         criminalizeparty(LAWFLAG_HELPESCAPE);

         return;
      }
      else if(c=='n')return;
   }
}



void special_intel_supercomputer()
{
   if(sitealarm||sitealienate)
   {
      clearmessagearea();

      set_color(COLOR_WHITE,COLOR_BLACK,1);
      move(16,1);
      addstr("セキュリティ保護のため", gamelog);
      move(17,1);
      addstr("コンピュータは停止している。", gamelog);
      gamelog.newline();

      getkey();

      return;
   }

   while(true)
   {
      clearmessagearea();

      set_color(COLOR_WHITE,COLOR_BLACK,1);
      move(16,1);
      addstr("情報局のスーパーコンピュータがある。", gamelog);
      gamelog.newline();
      move(17,1);
      addstr("ハックするか? (Yes / No)");

      int c=getkey();

      if(c=='y')
      {
         char actual;

         if(hack(HACK_SUPERCOMPUTER,actual))
         {
            clearmessagearea();

            //char *loot;
            set_color(COLOR_WHITE,COLOR_BLACK,1);
            move(16,1);
            addstr("部隊は機密情報を入手した", gamelog);
            if(endgamestate>=ENDGAME_CCS_APPEARANCE && endgamestate < ENDGAME_CCS_DEFEATED && ccsexposure<CCSEXPOSURE_LCSGOTDATA)
            {
               addstr("。", gamelog);
               move(17,1);
               addstr("そこにはCCSを支援する政府関係者のリストも含まれていた", gamelog);

               Item *it=new Loot(*loottype[getloottype("LOOT_CCS_BACKERLIST")]);
               activesquad->loot.push_back(it);

               ccsexposure=CCSEXPOSURE_LCSGOTDATA;
            }
            else
            {
               addstr("。", gamelog);
            }
            gamelog.newline();

            juiceparty(50,1000);

            Item *it=new Loot(*loottype[getloottype("LOOT_INTHQDISK")]);
            activesquad->loot.push_back(it);

            getkey();
         }

         if(actual)
         {
            int time=20+LCSrandom(10);
            if(time<1)time=1;
            if(sitealarmtimer>time||sitealarmtimer==-1)sitealarmtimer=time;

            alienationcheck(1);
            noticecheck(-1,DIFFICULTY_HARD);
            levelmap[locx][locy][locz].special=-1;
            sitecrime+=3;
            sitestory->crime.push_back(CRIME_HACK_INTEL);

            criminalizeparty(LAWFLAG_TREASON);
         }

         return;
      }
      else if(c=='n')return;
   }
}


void special_graffiti()
{
   clearmessagearea();

   set_color(COLOR_WHITE,COLOR_BLACK,1);
   move(16,1);
   addstr("部隊はリベラル落書きをした!", gamelog);
   gamelog.newline();

   if(!sitestory->claimed)
      sitestory->claimed=1;

   getkey();

   int time=20+LCSrandom(10);
   if(time<1)time=1;
   if(sitealarmtimer>time||sitealarmtimer==-1)sitealarmtimer=time;

   alienationcheck(0);
   noticecheck(-1,DIFFICULTY_HARD);
   levelmap[locx][locy][locz].flag|=SITEBLOCK_GRAFFITI;
   levelmap[locx][locy][locz].flag&=~(SITEBLOCK_GRAFFITI_CCS|SITEBLOCK_GRAFFITI_OTHER);
   if(!location[cursite]->highsecurity)
   {
      // Erase any previous semi-permanent graffiti here
      for(int i=0;i<len(location[cursite]->changes);i++)
      {
         if((location[cursite]->changes[i].x == locx) &&
            (location[cursite]->changes[i].y == locy) &&
            (location[cursite]->changes[i].z == locz) &&
            ((location[cursite]->changes[i].flag == SITEBLOCK_GRAFFITI) ||
             (location[cursite]->changes[i].flag == SITEBLOCK_GRAFFITI_CCS) ||
             (location[cursite]->changes[i].flag == SITEBLOCK_GRAFFITI_OTHER)))
         {
            location[cursite]->changes.erase(location[cursite]->changes.begin()+i);
            break;
         }
      }

      // Add new semi-permanent graffiti
      struct sitechangest change(locx,locy,locz,SITEBLOCK_GRAFFITI);
      location[cursite]->changes.push_back(change);
   }
   sitecrime++;
   for(int i=0;i<6;i++)
   {
      if(activesquad->squad[i])
         addjuice(*(activesquad->squad[i]),1,50);
   }

   criminalizeparty(LAWFLAG_VANDALISM);
   sitestory->crime.push_back(CRIME_TAGGING);

   return;
}


void special_sweatshop_equipment()
{
   while(true)
   {
      clearmessagearea();

      set_color(COLOR_WHITE,COLOR_BLACK,1);
      move(16,1);
      addstr("織機がある。", gamelog);
      gamelog.newline();
      move(17,1);
      addstr("破壊するか? (Yes / No)");

      int c=getkey();

      if(c=='y')
      {
         int time=20+LCSrandom(10);
         if(time<1)time=1;
         if(sitealarmtimer>time||sitealarmtimer==-1)sitealarmtimer=time;

         alienationcheck(0);
         noticecheck(-1,DIFFICULTY_HEROIC);
         levelmap[locx][locy][locz].special=-1;
         levelmap[locx][locy][locz].flag|=SITEBLOCK_DEBRIS;
         sitecrime++;
         juiceparty(5,100);
         sitestory->crime.push_back(CRIME_BREAK_SWEATSHOP);

         criminalizeparty(LAWFLAG_VANDALISM);

         return;
      }
      else if(c=='n')return;
   }
}



void special_polluter_equipment()
{
   while(true)
   {
      clearmessagearea();

      set_color(COLOR_WHITE,COLOR_BLACK,1);
      move(16,1);
      addstr("工場の設備がある。", gamelog);
      gamelog.newline();
      move(17,1);
      addstr("破壊するか? (Yes / No)");

      int c=getkey();

      if(c=='y')
      {
         int time=20+LCSrandom(10);
         if(time<1)time=1;
         if(sitealarmtimer>time||sitealarmtimer==-1)sitealarmtimer=time;

         change_public_opinion(VIEW_POLLUTION,2,1,70);

         alienationcheck(0);
         noticecheck(-1,DIFFICULTY_HEROIC);
         levelmap[locx][locy][locz].special=-1;
         levelmap[locx][locy][locz].flag|=SITEBLOCK_DEBRIS;
         sitecrime+=2;
         juiceparty(5,100);
         sitestory->crime.push_back(CRIME_BREAK_FACTORY);

         criminalizeparty(LAWFLAG_VANDALISM);

         return;
      }
      else if(c=='n')return;
   }
}



void special_house_photos()
{
   while(true)
   {
      clearmessagearea();

      set_color(COLOR_WHITE,COLOR_BLACK,1);
      move(16,1);
      addstr("金庫がある。", gamelog);
      gamelog.newline();
      move(17,1);
      addstr("開けるか? (Yes / No)");

      int c=getkey();

      if(c=='y')
      {
         char actual;

         if(unlock(UNLOCK_SAFE,actual))
         {
            bool empty=true;
            Item *it;

            if(deagle==false)
            {
               clearmessagearea();

               set_color(COLOR_WHITE,COLOR_BLACK,1);
               move(16,1);
               addstr("部隊はデザート・イーグルを見つけた。", gamelog);
               gamelog.newline();

               getkey();

               Weapon* de=new Weapon(*weapontype[getweapontype("WEAPON_DESERT_EAGLE")]);
               Clip r(*cliptype[getcliptype("CLIP_50AE")]);
               de->reload(r);
               activesquad->loot.push_back(de);

               it=new Clip(*cliptype[getcliptype("CLIP_50AE")],9);
               activesquad->loot.push_back(it);

               deagle=true;
               empty=false;
            }

            if(LCSrandom(2))
            {
               clearmessagearea();

               set_color(COLOR_WHITE,COLOR_BLACK,1);
               move(16,1);
               addstr("この男は本当に大量の$100札を持っていた。", gamelog);
               gamelog.newline();

               getkey();

               it=new Money(1000*(1+LCSrandom(10)));
               activesquad->loot.push_back(it);

               empty=false;
            }

            if(LCSrandom(2))
            {
               clearmessagearea();

               set_color(COLOR_WHITE,COLOR_BLACK,1);
               move(16,1);
               addstr("部隊は高価な宝石を解放した。", gamelog);
               gamelog.newline();

               getkey();

               it=new Loot(*loottype[getloottype("LOOT_EXPENSIVEJEWELERY")],3);
               activesquad->loot.push_back(it);

               empty=false;
            }

            if(!LCSrandom(3))
            {
               clearmessagearea();

               set_color(COLOR_WHITE,COLOR_BLACK,1);
               move(16,1);
               addstr("そこには…とてもヤバい写真があった。", gamelog);
               gamelog.newline();

               getkey();

               it=new Loot(*loottype[getloottype("LOOT_CEOPHOTOS")]);
               activesquad->loot.push_back(it);

               empty=false;
            }

            if(!LCSrandom(3))
            {
               clearmessagearea();

               set_color(COLOR_WHITE,COLOR_BLACK,1);
               move(16,1);
               addstr("そこにはいくつかのドラッグがあった。", gamelog);
               gamelog.newline();

               getkey();

               empty=false;
            }

            if(!LCSrandom(3))
            {
               clearmessagearea();

               set_color(COLOR_WHITE,COLOR_BLACK,1);
               move(16,1);
               addstr("ワォ、ラブレターの山だ。", gamelog);
               move(17,1);
               addstr("部隊はこれを持ち去った。");
               gamelog.newline();

               getkey();

               it=new Loot(*loottype[getloottype("LOOT_CEOLOVELETTERS")]);
               activesquad->loot.push_back(it);

               empty=false;
            }

            if(!LCSrandom(3))
            {
               clearmessagearea();

               set_color(COLOR_WHITE,COLOR_BLACK,1);
               move(16,1);
               addstr("深刻な脱税を示す文書があった。", gamelog);
               gamelog.newline();

               getkey();

               it=new Loot(*loottype[getloottype("LOOT_CEOTAXPAPERS")]);
               activesquad->loot.push_back(it);

               empty=false;
            }

            if(empty)
            {
               clearmessagearea();

               set_color(COLOR_WHITE,COLOR_BLACK,1);
               move(16,1);
               addstr("ワォ、何もない。チクショウ。", gamelog);
               gamelog.newline();

               getkey();
            }
            else
            {
               juiceparty(50,1000);
               sitecrime+=40;
               sitestory->crime.push_back(CRIME_HOUSE_PHOTOS);
               criminalizeparty(LAWFLAG_THEFT);

               int time=20+LCSrandom(10);
               if(time<1)time=1;
               if(sitealarmtimer>time||sitealarmtimer==-1)sitealarmtimer=time;
            }
         }

         if(actual)
         {
            alienationcheck(0);
            noticecheck(-1);
            levelmap[locx][locy][locz].special=-1;
         }

         return;
      }
      else if(c=='n')return;
   }
}


void special_armory()
{
   while(true)
   {
      clearmessagearea();

      set_color(COLOR_WHITE,COLOR_BLACK,1);
      move(16,1);
      addstr("武器庫がある。", gamelog);
      gamelog.newline();
      move(17,1);
      addstr("破壊して入るか? (Yes / No)");

      int c=getkey();

      if(c=='y')
      {
         clearmessagearea();

         sitealarm=1;
         move(16,1);
         set_color(COLOR_RED,COLOR_BLACK,1);
         addstr("警報が鳴り出した!", gamelog);
         gamelog.newline();

         getkey();

         bool empty=true;
         Item *it;

         if(m249==false && location[cursite]->type == SITE_GOVERNMENT_ARMYBASE)
         {
            clearmessagearea();

            set_color(COLOR_WHITE,COLOR_BLACK,1);
            move(16,1);
            addstr("大当たりだ! 部隊はM249機関銃を見つけた!", gamelog);
            gamelog.newline();

            getkey();

            Weapon* de=new Weapon(*weapontype[getweapontype("WEAPON_M249_MACHINEGUN")]);
            Clip r(*cliptype[getcliptype("CLIP_DRUM")]);
            de->reload(r);
            activesquad->loot.push_back(de);

            it=new Clip(*cliptype[getcliptype("CLIP_DRUM")],9);
            activesquad->loot.push_back(it);

            m249=true;
            empty=false;
         }

         if(LCSrandom(2))
         {
            clearmessagearea();

            set_color(COLOR_WHITE,COLOR_BLACK,1);
            move(16,1);
            addstr("部隊はM16自動小銃を見つけた。", gamelog);
            gamelog.newline();

            getkey();

            int num = 0;

            do
            {
               Weapon* de=new Weapon(*weapontype[getweapontype("WEAPON_AUTORIFLE_M16")]);
               Clip r(*cliptype[getcliptype("CLIP_ASSAULT")]);
               de->reload(r);
               activesquad->loot.push_back(de);

               it=new Clip(*cliptype[getcliptype("CLIP_ASSAULT")],5);
               activesquad->loot.push_back(it);
               num++;
            } while(num<2 || (LCSrandom(2) && num<5));

            empty=false;
         }

         if(LCSrandom(2))
         {
            clearmessagearea();

            set_color(COLOR_WHITE,COLOR_BLACK,1);
            move(16,1);
            addstr("部隊は何丁かのM4カービンを見つけた。", gamelog);
            gamelog.newline();

            getkey();

            int num = 0;

            do
            {
               Weapon* de=new Weapon(*weapontype[getweapontype("WEAPON_CARBINE_M4")]);
               Clip r(*cliptype[getcliptype("CLIP_ASSAULT")]);
               de->reload(r);
               activesquad->loot.push_back(de);

               it=new Clip(*cliptype[getcliptype("CLIP_ASSAULT")],5);
               activesquad->loot.push_back(it);
               num++;
            } while(num<2 || (LCSrandom(2) && num<5));

            empty=false;
         }

         if(LCSrandom(2))
         {
            clearmessagearea();

            set_color(COLOR_WHITE,COLOR_BLACK,1);
            move(16,1);
            addstr("部隊は何着かの防護服を見つけた。", gamelog);
            gamelog.newline();

            getkey();

            int num = 0;

            do
            {
               Armor* de;
               if(location[cursite]->type == SITE_GOVERNMENT_ARMYBASE)
                  de=new Armor(*armortype[getarmortype("ARMOR_ARMYARMOR")]);
               else
                  de=new Armor(*armortype[getarmortype("ARMOR_CIVILLIANARMOR")]);
               activesquad->loot.push_back(de);
               num++;
            } while(num<2 || (LCSrandom(2) && num<5));

            empty=false;
         }

         if(empty)
         {
            criminalizeparty(LAWFLAG_TREASON);

            clearmessagearea();

            set_color(COLOR_WHITE,COLOR_BLACK,1);
            move(16,1);
            addstr("罠だ! 武器庫は空だった。", gamelog);
            gamelog.newline();

            getkey();

            int numleft=LCSrandom(8)+2;
            for(int e=0;e<ENCMAX;e++)
            {
               if(!encounter[e].exists)
               {
                  if(location[cursite]->type == SITE_GOVERNMENT_ARMYBASE)
                     makecreature(encounter[e],CREATURE_SOLDIER);
                  else
                     makecreature(encounter[e],CREATURE_MERC);
                  numleft--;
               }
               if(numleft==0)break;
            }
         }
         else
         {
            juiceparty(50,1000);
            sitecrime+=40;
            sitestory->crime.push_back(CRIME_ARMORY);
            criminalizeparty(LAWFLAG_THEFT);
            criminalizeparty(LAWFLAG_TREASON);

            int time=20+LCSrandom(10);
            if(time<1)time=1;
            if(sitealarmtimer>time||sitealarmtimer==-1)sitealarmtimer=time;

            clearmessagearea();

            set_color(COLOR_WHITE,COLOR_BLACK,1);
            move(16,1);
            addstr("いたる所に警備兵がいる!", gamelog);
            gamelog.newline();

            getkey();

            int numleft=LCSrandom(4)+2;
            for(int e=0;e<ENCMAX;e++)
            {
               if(!encounter[e].exists)
               {
                  if(location[cursite]->type == SITE_GOVERNMENT_ARMYBASE)
                     makecreature(encounter[e],CREATURE_SOLDIER);
                  else
                     makecreature(encounter[e],CREATURE_MERC);
                  numleft--;
               }
               if(numleft==0)break;
            }
         }

         alienationcheck(0);
         noticecheck(-1);
         levelmap[locx][locy][locz].special=-1;

         return;
      }
      else if(c=='n')return;
   }
}



void special_corporate_files()
{
   while(true)
   {
      clearmessagearea();

      set_color(COLOR_WHITE,COLOR_BLACK,1);
      move(16,1);
      addstr("金庫がある。", gamelog);
      gamelog.newline();
      move(17,1);
      addstr("開けるか? (Yes / No)");

      int c=getkey();

      if(c=='y')
      {
         char actual;

         if(unlock(UNLOCK_SAFE,actual))
         {
            clearmessagearea();

            set_color(COLOR_WHITE,COLOR_BLACK,1);
            move(16,1);
            addstr("部隊はとても興味深いファイルを見つけた。", gamelog);
            gamelog.newline();

            Item *it=new Loot(*loottype[getloottype("LOOT_CORPFILES")]);
            activesquad->loot.push_back(it);
            it=new Loot(*loottype[getloottype("LOOT_CORPFILES")]);
            activesquad->loot.push_back(it);

            juiceparty(50,1000);
            sitecrime+=40;

            int time=20+LCSrandom(10);
            if(time<1)time=1;
            if(sitealarmtimer>time||sitealarmtimer==-1)sitealarmtimer=time;

            getkey();
         }

         if(actual)
         {
            alienationcheck(0);
            noticecheck(-1);
            levelmap[locx][locy][locz].special=-1;
            sitecrime+=3;
            sitestory->crime.push_back(CRIME_CORP_FILES);

            criminalizeparty(LAWFLAG_THEFT);
         }

         return;
      }
      else if(c=='n')return;
   }
}



void special_radio_broadcaststudio()
{
   while(true)
   {
      clearmessagearea();

      set_color(COLOR_WHITE,COLOR_BLACK,1);
      if(sitealarm||sitealienate)
      {
         move(16,1);
         addstr("ラジオのアナウンサーは機材をそのままにして逃げたようだ。", gamelog);
         gamelog.newline();
         addstr("スタジオを乗っ取るか? (Yes / No)");
      }
      else
      {
         move(16,1);
         addstr("ここはラジオ放送室だ。", gamelog);
         gamelog.newline();
         move(17,1);
         addstr("昼の放送に割り込むか? (Yes / No)");
      }

      int c=getkey();

      if(c=='y')
      {
         if(radio_broadcast())
         {
            sitestory->claimed=2;
            levelmap[locx][locy][locz].special=-1;
         }

         return;
      }
      else if(c=='n')return;
   }
}



void special_news_broadcaststudio()
{
   while(true)
   {
      clearmessagearea();

      set_color(COLOR_WHITE,COLOR_BLACK,1);
      if(sitealarm||sitealienate)
      {
         move(16,1);
         addstr("ケーブルテレビのキャスターは機材をそのままにして逃げたようだ。", gamelog);
         gamelog.newline();
         addstr("スタジオを乗っ取るか? (Yes / No)");
      }
      else
      {
         move(16,1);
         addstr("ここはケーブルテレビのスタジオだ。", gamelog);
         move(17,1);
         addstr("臨時ニュースを始めるか? (Yes / No)");
      }

      int c=getkey();

      if(c=='y')
      {
         if(news_broadcast())
         {
            sitestory->claimed=2;
            levelmap[locx][locy][locz].special=-1;
         }

         return;
      }
      else if(c=='n')return;
   }
}


void special_display_case()
{
   while(true)
   {
      clearmessagearea();

      set_color(COLOR_WHITE,COLOR_BLACK,1);
      move(16,1);
      addstr("展示ケースがある。", gamelog);
      move(17,1);
      addstr("破壊するか? (Yes / No)");

      int c=getkey();

      if(c=='y')
      {
         int time=20+LCSrandom(10);
         if(time<1)time=1;
         if(sitealarmtimer>time||sitealarmtimer==-1)sitealarmtimer=time;

         alienationcheck(0);
         noticecheck(-1,DIFFICULTY_HEROIC);
         levelmap[locx][locy][locz].special=-1;
         levelmap[locx][locy][locz].flag|=SITEBLOCK_DEBRIS;
         sitecrime++;
         juiceparty(5,100);
         sitestory->crime.push_back(CRIME_VANDALISM);

         criminalizeparty(LAWFLAG_VANDALISM);

         return;
      }
      else if(c=='n')return;
   }
}

void spawn_security()
{
   // add a bouncer if there isn't one in the first slot
   if(!sitealarm && !encounter[0].exists)
   {
      switch(location[cursite]->type)
      {
      default:
      case SITE_CORPORATE_HEADQUARTERS:
      case SITE_CORPORATE_HOUSE:
      case SITE_BUSINESS_ARMSDEALER:
      case SITE_BUSINESS_BANK:
      case SITE_INDUSTRY_NUCLEAR:
         makecreature(encounter[0], CREATURE_MERC);
         makecreature(encounter[1], CREATURE_MERC);
         break;
      case SITE_GOVERNMENT_POLICESTATION:
      case SITE_GOVERNMENT_COURTHOUSE:
      case SITE_OUTDOOR_PUBLICPARK:
         makecreature(encounter[0], CREATURE_COP);
         makecreature(encounter[1], CREATURE_COP);
         break;
      case SITE_GOVERNMENT_PRISON:
         makecreature(encounter[0], CREATURE_PRISONGUARD);
         makecreature(encounter[1], CREATURE_PRISONGUARD);
         makecreature(encounter[2], CREATURE_GUARDDOG);
         break;
      case SITE_GOVERNMENT_WHITE_HOUSE:
         makecreature(encounter[0], CREATURE_SECRET_SERVICE);
         makecreature(encounter[1], CREATURE_SECRET_SERVICE);
         makecreature(encounter[2], CREATURE_SECRET_SERVICE);
         makecreature(encounter[3], CREATURE_SECRET_SERVICE);
         break;
      case SITE_GOVERNMENT_INTELLIGENCEHQ:
         makecreature(encounter[0], CREATURE_AGENT);
         makecreature(encounter[1], CREATURE_AGENT);
         makecreature(encounter[2], CREATURE_GUARDDOG);
         break;
      case SITE_GOVERNMENT_ARMYBASE:
         makecreature(encounter[0], CREATURE_MILITARYPOLICE);
         makecreature(encounter[1], CREATURE_MILITARYPOLICE);
         break;
      case SITE_BUSINESS_BARANDGRILL:
      case SITE_RESIDENTIAL_BOMBSHELTER:
      case SITE_OUTDOOR_BUNKER:
         if(location[cursite]->renting==RENTING_CCS)
         {
            makecreature(encounter[0],CREATURE_CCS_VIGILANTE);
            makecreature(encounter[1],CREATURE_CCS_VIGILANTE);
         }
      }
   }
}

void special_security(bool metaldetect)
{
   char autoadmit=0;
   char sleepername[80];
   for(int e=0;e<ENCMAX;e++)encounter[e].exists=0;

   spawn_security();

   for(int p=0;p<len(pool);p++)
   {
      if(pool[p]->base==cursite)
      {
         autoadmit=1;
         if(pool[p]->type == encounter[0].type)
         {
            autoadmit=2;
            strcpy(sleepername,pool[p]->name);
            strcpy(encounter[0].name,sleepername);
            encounter[0].align=1;
            encounter[0].cantbluff=1;
            break;
         }
      }
   }
   //clearmessagearea();
   set_color(COLOR_WHITE,COLOR_BLACK,1);
   move(16,1);
   if(sitealarm)
   {
      addstr("セキュリティ検査は停止している。", gamelog);
      gamelog.newline();
      levelmap[locx][locy][locz].special=SPECIAL_NONE;
      return;
   }
   else if(autoadmit)
   {
      addstr("部隊はIDバッジをかざした。", gamelog);
      metaldetect=false;
      gamelog.newline();
      levelmap[locx][locy][locz].special=SPECIAL_SECURITY_SECONDVISIT;
   }
   else
   {
      if(metaldetect) addstr("部隊は金属探知機に足を踏み入れた。", gamelog);
      else addstr("扉はガードされている。", gamelog);
      gamelog.newline();
      levelmap[locx][locy][locz].special=SPECIAL_SECURITY_SECONDVISIT;
   }
   printencounter();

   getkey();

   char rejected=NOT_REJECTED;

   // Size up the squad for entry
   for(int s=0;s<6;s++)
   {
      if(activesquad->squad[s])
      {
         // Wrong clothes? Gone
         if(activesquad->squad[s]->is_naked() && activesquad->squad[s]->animalgloss!=ANIMALGLOSS_ANIMAL)
            if(rejected>REJECTED_NUDE)rejected=REJECTED_NUDE;

         if(autoadmit<1 && !hasdisguise(*activesquad->squad[s]))
            if(rejected>REJECTED_DRESSCODE)rejected=REJECTED_DRESSCODE;
         // Busted, cheap, bloody clothes? Gone
         if(autoadmit<2 && activesquad->squad[s]->get_armor().is_bloody())
            if(rejected>REJECTED_BLOODYCLOTHES)rejected=REJECTED_BLOODYCLOTHES;
         if(autoadmit<2 && activesquad->squad[s]->get_armor().is_damaged())
            if(rejected>REJECTED_DAMAGEDCLOTHES)rejected=REJECTED_DAMAGEDCLOTHES;
         if(autoadmit<2 && activesquad->squad[s]->get_armor().get_quality()!=1)
            if(rejected>REJECTED_SECONDRATECLOTHES)rejected=REJECTED_SECONDRATECLOTHES;
         // Suspicious weapons? Gone
         if(autoadmit<2 && weaponcheck(*activesquad->squad[s], metaldetect)>0)
            if(rejected>REJECTED_WEAPONS)rejected=REJECTED_WEAPONS;
         // Fail a tough disguise check? Gone
         if(autoadmit<1 && disguisesite(sitetype) && !(activesquad->squad[s]->skill_check(SKILL_DISGUISE,DIFFICULTY_CHALLENGING)))
            if(rejected>REJECTED_SMELLFUNNY)rejected=REJECTED_SMELLFUNNY;
         // Underage? Gone
         if(autoadmit<1 && activesquad->squad[s]->age<18)
            if(rejected>REJECTED_UNDERAGE)rejected=REJECTED_UNDERAGE;
      }
   }
   move(17,1);
   switch(rejected)
   {
   case REJECTED_NUDE:
      set_color(COLOR_RED,COLOR_BLACK,1);
      if(autoadmit) addstr("「ジーザス! 服を着るんだ! 」", gamelog);
      else switch(LCSrandom(4))
      {
      case 0:addstr("「ヌーディストは立ち入り禁止だ!!」", gamelog);break;
      case 1:addstr("「帰れ! おかしな奴め! 」", gamelog);break;
      case 2:addstr("「ジーザス!! 誰か警察を呼んでくれ! 」", gamelog);break;
	  case 3:addstr("「夢遊病なのか?!」", gamelog);break;
      }
      gamelog.newline();
      break;
   case REJECTED_UNDERAGE:
      set_color(COLOR_RED,COLOR_BLACK,1);
      switch(LCSrandom(4))
      {
      case 0:addstr("「子供はここには入れない。」", gamelog);break;
      case 1:addstr("「ここで働くには若すぎる。」", gamelog);break;
      case 2:addstr("「別の場所で遊びなさい。」", gamelog);break;
      case 3:addstr("「お母さんはどこへ? 」", gamelog);break;
      }
      gamelog.newline();
      break;
   case REJECTED_DRESSCODE:
      set_color(COLOR_RED,COLOR_BLACK,1);
      switch(LCSrandom(1))
      {
      case 0:addstr("「ここは社員専用だ。」", gamelog);break;
      }
      gamelog.newline();
      break;
   case REJECTED_SMELLFUNNY:
      set_color(COLOR_RED,COLOR_BLACK,1);
      switch(LCSrandom(4))
      {
      case 0:addstr("「あなたはここで働いていませんね? 」", gamelog);break;
      case 1:addstr("「うーむ…バッジを見せてもらえますか? 」", gamelog);break;
      case 2:addstr("「あなたは何か様子がおかしいのですが。」", gamelog);break;
      case 3:addstr("「新人か? ここではバッジが必要だ。」", gamelog);break;
      }
      gamelog.newline();
      break;
   case REJECTED_BLOODYCLOTHES:
      set_color(COLOR_RED,COLOR_BLACK,1);
      switch(LCSrandom(5))
      {
      case 0:addstr("「おい! その服はどうしたんだ? 」", gamelog);break;
      case 1:addstr("「ケガをしているのか?! 医療室はあっちだ! 」", gamelog);break;
      case 2:addstr("「服に血が! 」", gamelog);break;
      case 3:addstr("「血?! 何があったんだ…」", gamelog);break;
      case 4:addstr("「猫を殺したのか?!」", gamelog);break;
      case 5:addstr("「血まみれだ…? 」", gamelog);break;
      }
      gamelog.newline();
      break;
   case REJECTED_DAMAGEDCLOTHES:
      set_color(COLOR_RED,COLOR_BLACK,1);
      switch(LCSrandom(2))
      {
      case 0:addstr("「おい! その服はどうしたんだ? 」", gamelog);break;
      case 1:addstr("「そのボロボロの服はハロウィンの衣装か? 」", gamelog);break;
      }
      gamelog.newline();
      break;
   case REJECTED_SECONDRATECLOTHES:
      set_color(COLOR_RED,COLOR_BLACK,1);
      switch(LCSrandom(2))
      {
      case 0:addstr("「その服は自分で作ったものだな。」", gamelog);break;
      case 1:addstr("「その制服はできの悪い偽物だ。お前は誰だ? 」", gamelog);break;
      }
      gamelog.newline();
      break;
   case REJECTED_WEAPONS:
      set_color(COLOR_RED,COLOR_BLACK,1);
      if(metaldetect)
      {
         addstr("-ビー- -ビー- -ビー-", gamelog);
         sitealarm=1;
      }
      else switch(LCSrandom(5))
      {
      case 0:addstr("「離れろ! 」", gamelog);break;
      case 1:addstr("「おい、下がれ! 」", gamelog);break;
      case 2:addstr("「何もするな! 」", gamelog);break;
      case 3:addstr("「何をするつもりだ? 」", gamelog);break;
      case 4:addstr("「下がれ! 」", gamelog);break;
      }
      gamelog.newline();
      break;
   case NOT_REJECTED:
      set_color(COLOR_GREEN,COLOR_BLACK,1);

      switch(LCSrandom(4))
      {
      case 0:addstr("「そのまま進んでください。」", gamelog);break;
      case 1:addstr("「よい一日を。」", gamelog);break;
      case 2:addstr("「今日はいい天気ですね。」", gamelog);break;
      case 3:addstr("「入ってください。」", gamelog);break;
      }
      gamelog.newline();
      break;
   }

   getkey();

   set_color(COLOR_WHITE,COLOR_BLACK,1);
   for(int dx=-1; dx<=1; dx++)
   for(int dy=-1; dy<=1; dy++)
   {
      if(levelmap[locx+dx][locy+dy][locz].flag & SITEBLOCK_DOOR)
      {
         if(rejected<NOT_REJECTED)
         {
            levelmap[locx+dx][locy+dy][locz].flag |= SITEBLOCK_LOCKED;
            levelmap[locx+dx][locy+dy][locz].flag |= SITEBLOCK_CLOCK;
         }
         else levelmap[locx+dx][locy+dy][locz].flag &= ~SITEBLOCK_DOOR;
      }
   }
   encounter[0].cantbluff=1;
}

void special_security_checkpoint()
{
   special_security(false);
}

void special_security_metaldetectors()
{
   special_security(true);
}

void special_security_secondvisit()
{
   spawn_security();
}

void special_bank_vault()
{
   clearmessagearea();
   move(16,1);
   addstr("金庫室の扉は3層になっている: ダイヤル錠、電子錠、", gamelog);
   move(17,1);
   addstr("生体認証だ。", gamelog);
   gamelog.newline();

   getkey();

   clearmessagearea();
   move(16,1);
   addstr("セキュリティの専門家、コンピュータの専門家、", gamelog);
   move(17,1);
   addstr("そして銀行の管理者が必要だろう。", gamelog);
   gamelog.newline();

   getkey();

   for(int p=0;p<len(pool);p++)
   {
      if(pool[p]->type==CREATURE_BANK_MANAGER &&
         pool[p]->flag & CREATUREFLAG_SLEEPER &&
         pool[p]->base == cursite)
      {
         clearmessagearea();
         move(16,1);
         addstr("潜伏者の", gamelog);
         addstr(pool[p]->name, gamelog);
         addstr("は生体認証を突破できる。", gamelog);
         move(17,1);
         addstr("だが、他のロックを解除しなければならない。", gamelog);
         gamelog.newline();

         getkey();

         break;
      }
   }

   while(true)
   {
      clearmessagearea();
      move(16,1);
      addstr("金庫室の扉を開けるか? (Yes / No)");

      int c=getkey();

      if(c=='y')
      {
         char actual;

         clearmessagearea();
         set_color(COLOR_WHITE,COLOR_BLACK,1);
         move(16,1);
         addstr("最初のダイヤル錠は", gamelog);
         move(17,1);
         addstr("セキュリティの専門家が解除することができる。", gamelog);
         gamelog.newline();

         getkey();

         if(!unlock(UNLOCK_VAULT,actual))
         {
            clearmessagearea();
            set_color(COLOR_WHITE,COLOR_BLACK,1);
            move(16,1);
            addstr("部隊は扉の外で", gamelog);
            move(17,1);
            addstr("大金を夢見るだけだった…", gamelog);
            gamelog.newline();

            getkey();

            levelmap[locx][locy][locz].special=-1;
         }
         else
         {
            clearmessagearea();
            set_color(COLOR_WHITE,COLOR_BLACK,1);
            move(16,1);
            addstr("次の電子錠は", gamelog);
            move(17,1);
            addstr("コンピュータの専門家が解除できる。", gamelog);
            gamelog.newline();

            getkey();

            if(!hack(HACK_VAULT,actual))
            {
               clearmessagearea();
               set_color(COLOR_WHITE,COLOR_BLACK,1);
               move(16,1);
               addstr("部隊は金を味見できるくらいまでは近づけた!", gamelog);
               gamelog.newline();

               getkey();

               levelmap[locx][locy][locz].special=-1;
            }
            else
            {
               clearmessagearea();
               set_color(COLOR_WHITE,COLOR_BLACK,1);
               move(16,1);
               addstr("最後の生体認証には", gamelog);
               move(17,1);
               addstr("銀行の管理者が必要だ。", gamelog);
               gamelog.newline();

               getkey();

               Creature *manager = 0;
               bool canbreakin = false;

               for(int s=0;s<6;s++)
               {
                  Creature *c = activesquad->squad[s];

                  if(c)
                  {
                     if(c->type == CREATURE_BANK_MANAGER)
                     {
                        manager = c;
                        if(c->joindays < 30 && !(c->flag & CREATUREFLAG_KIDNAPPED))
                        {
                           clearmessagearea();
                           set_color(COLOR_WHITE,COLOR_BLACK,1);
                           move(16,1);
                           addstr(c->name, gamelog);
                           addstr("は金庫室の扉を開いた。", gamelog);
                           gamelog.newline();

                           getkey();

                           canbreakin = true;
                           break;
                        }
                     }

                     if(c->prisoner && c->prisoner->type == CREATURE_BANK_MANAGER)
                     {
                        clearmessagearea();
                        set_color(COLOR_WHITE,COLOR_BLACK,1);
                        move(16,1);
                        addstr("人質に金庫室の扉を開けさせた。", gamelog);
                        gamelog.newline();

                        getkey();

                        canbreakin = true;
                        break;
                     }
                  }
               }

               if(!canbreakin)
               {
                  for(int p=0;p<len(pool);p++)
                  {
                     if(pool[p]->base == cursite && pool[p]->type == CREATURE_BANK_MANAGER)
                     {
                        clearmessagearea();
                        set_color(COLOR_WHITE,COLOR_BLACK,1);
                        move(16,1);
                        addstr("潜伏者の", gamelog);
                        addstr(pool[p]->name, gamelog);
                        addstr("は金庫室の扉を開けた。", gamelog);
                        move(17,1);
                        addstr("そして、逮捕を避けるためLCSと行動する。", gamelog);
                        gamelog.newline();

                        getkey();

                        canbreakin = true;

                        pool[p]->location = pool[p]->base = activesquad->squad[0]->base;
                        pool[p]->flag &= ~CREATUREFLAG_SLEEPER;
                        pool[p]->activity.type = ACTIVITY_NONE;
                        pool[p]->crimes_suspected[LAWFLAG_BANKROBBERY]++;

                        break;
                     }
                  }
               }

               if(canbreakin)
               {
                  criminalizeparty(LAWFLAG_BANKROBBERY);
                  sitecrime+=20;
                  sitestory->crime.push_back(CRIME_BANKVAULTROBBERY);
                  levelmap[locx+1][locy][locz].flag &= ~SITEBLOCK_DOOR;
                  levelmap[locx-1][locy][locz].flag &= ~SITEBLOCK_DOOR;
                  levelmap[locx][locy+1][locz].flag &= ~SITEBLOCK_DOOR;
                  levelmap[locx][locy-1][locz].flag &= ~SITEBLOCK_DOOR;
                  levelmap[locx][locy][locz].special=-1;
               }
               else
               {
                  if(manager)
                  {
                     clearmessagearea();
                     set_color(COLOR_WHITE,COLOR_BLACK,1);
                     move(16,1);
                     addstr(manager->name, gamelog);
                     addstr("は認証を突破できなかった。", gamelog);
                     gamelog.newline();

                     getkey();
                  }
                  else
                  {
                     clearmessagearea();
                     set_color(COLOR_WHITE,COLOR_BLACK,1);
                     move(16,1);
                     addstr("部隊の誰も認証を突破できない。", gamelog);
                     gamelog.newline();

                     getkey();
                  }
               }
            }
         }

         if(actual)
         {
            alienationcheck(0);
            noticecheck(-1);
         }

         return;
      }
      else if(c=='n')return;
   }
}

void special_bank_teller()
{
   if(sitealarm||sitealienate||
      location[cursite]->siege.siege)
   {
      clearmessagearea(false);
      set_color(COLOR_WHITE,COLOR_BLACK,1);
      move(16,1);
      addstr("窓口は閉まっている。", gamelog);
      gamelog.newline();
      levelmap[locx][locy][locz].special=-1;

      getkey();
   }
   else
   {
      clearmessagearea(false);
      set_color(COLOR_WHITE,COLOR_BLACK,1);
      move(16,1);
      addstr("窓口は受付中だ。", gamelog);
      gamelog.newline();
      levelmap[locx][locy][locz].special=-1;

      getkey();

      for(int e=0;e<ENCMAX;e++)encounter[e].exists=0;
      makecreature(encounter[0],CREATURE_BANK_TELLER);
   }
}

void special_bank_money()
{
   static int swat_counter = 0;

   clearmessagearea(false);
   set_color(COLOR_GREEN,COLOR_BLACK,1);
   move(16,1);
   addstr("部隊は札束を鞄に詰め込んだ。", gamelog);
   gamelog.newline();

   levelmap[locx][locy][locz].special=-1;

   activesquad->loot.push_back(new Money(20000));
   sitecrime+=20;

   if(postalarmtimer <= 80) swat_counter = 0;

   if(!sitealarm && sitealarmtimer!=0) sitealarmtimer=0;
   else if(!sitealarm && !LCSrandom(2)) sitealarm=1;
   else if(sitealarm && postalarmtimer <= 60) postalarmtimer += 20;
   else if(sitealarm && postalarmtimer <= 80 && LCSrandom(2)) postalarmtimer = 81;
   else if(sitealarm && postalarmtimer > 80 && LCSrandom(2) && swat_counter < 2)
   {
      getkey();

      move(17,1);
      if(swat_counter > 0)
         addstr("別のSWAT隊が来た!!", gamelog);
      else
         addstr("SWAT隊が金庫室に押し寄せた!!", gamelog);
      gamelog.newline();
      swat_counter++;

      int swatnum = 9;
      for(int e=0;e<ENCMAX;e++)
      {
         if(!encounter[e].exists)
         {
            makecreature(encounter[e],CREATURE_SWAT);
            swatnum--;
            if(swatnum<=0) break;
         }
      }
   }

   getkey();
}

void special_oval_office()
{
   // Clear entire Oval Office area
   for(int dx=-1; dx<=1; dx++)
   for(int dy=-1; dy<=1; dy++)
   {
      if(levelmap[locx+dx][locy+dy][locz].special == SPECIAL_OVAL_OFFICE_NW ||
         levelmap[locx+dx][locy+dy][locz].special == SPECIAL_OVAL_OFFICE_NE ||
         levelmap[locx+dx][locy+dy][locz].special == SPECIAL_OVAL_OFFICE_SW ||
         levelmap[locx+dx][locy+dy][locz].special == SPECIAL_OVAL_OFFICE_SE)
      {
         levelmap[locx+dx][locy+dy][locz].special = -1;
      }
   }

   if(sitealarm)
   {
      for(int e=0;e<ENCMAX;e++)encounter[e].exists=0;

      clearmessagearea(false);
      set_color(COLOR_WHITE,COLOR_BLACK,1);
      mvaddstr(16,1,"大統領はここにはいない…",gamelog);
      printsitemap(locx,locy,locz);

      getkey();

      mvaddstr(17,1,"シークレット・サービスが部隊を待ち伏せていた!", gamelog);
      gamelog.newline();
      for(int e=0;e<6;e++)makecreature(encounter[e],CREATURE_SECRET_SERVICE);
      printencounter();

      getkey();

      enemyattack();
      creatureadvance();
   }
   else
   {
      for(int e=0;e<ENCMAX;e++)encounter[e].exists=0;

      clearmessagearea(false);
      set_color(COLOR_WHITE,COLOR_BLACK,1);
      mvaddstr(16,1,"執務室に大統領がいる。",gamelog);
      gamelog.newline();
      printsitemap(locx,locy,locz);
      for(int e=0;e<2;e++)makecreature(encounter[e],CREATURE_SECRET_SERVICE);
      encounter[2] = uniqueCreatures.President();
      printencounter();

      getkey();
   }
}

void special_ccs_boss()
{
   if(sitealarm||sitealienate||
      location[cursite]->siege.siege)
   {
      clearmessagearea(false);
      set_color(COLOR_WHITE,COLOR_BLACK,1);
      move(16,1);
      addstr("CCSのリーダーが待ち構えていた!", gamelog);
      gamelog.newline();
      levelmap[locx][locy][locz].special=-1;

      getkey();

      for(int e=0;e<ENCMAX;e++)encounter[e].exists=0;
      makecreature(encounter[0],CREATURE_CCS_ARCHCONSERVATIVE);
      makecreature(encounter[1],CREATURE_CCS_VIGILANTE);
      makecreature(encounter[2],CREATURE_CCS_VIGILANTE);
      makecreature(encounter[3],CREATURE_CCS_VIGILANTE);
      makecreature(encounter[4],CREATURE_CCS_VIGILANTE);
      makecreature(encounter[5],CREATURE_CCS_VIGILANTE);
   }
   else
   {
      clearmessagearea(false);
      set_color(COLOR_WHITE,COLOR_BLACK,1);
      move(16,1);
      addstr("CCSのリーダーがいる。", gamelog);
      gamelog.newline();
      levelmap[locx][locy][locz].special=-1;

      getkey();

      for(int e=0;e<ENCMAX;e++)encounter[e].exists=0;
      makecreature(encounter[0],CREATURE_CCS_ARCHCONSERVATIVE);
   }
}
