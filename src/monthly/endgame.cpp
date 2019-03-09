/*
Copyright (c) 2002,2003,2004 by Tarn Adams                                          //
                                                                                    //
This file is part of Liberal Crime Squad.                                           //
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

/*
    TODO: I'm not sure if anything in here should be logged. Perhaps only the notification
       that the country has become arch-conservative... --Addictgamer
*/

/* endgame - attempts to pass a constitutional amendment to help win the game */
void tossjustices(char canseethings)
{
   int j;
   if(canseethings)
   {
      music.play(MUSIC_ELECTIONS);
      clear();

      set_color(COLOR_WHITE,COLOR_BLACK,1);

      move(12,6);
      addstr("エリート・リベラル議会によるエリート・リベラル発議!");

      getkey();
   }

   //STATE THE AMENDMENT
   if(canseethings)
   {
      int tossnum=0;
      for(j=0;j<COURTNUM;j++) if(court[j]!=ALIGN_ELITELIBERAL) tossnum++;

      amendmentheading();

      move(2,5);
      addstr("以下の市民だった者");
      if(tossnum!=1)addstr("たち");
      addstr("を保守強硬派とする: ");

      int y=4;

      for(j=0;j<COURTNUM;j++) if(court[j]!=ALIGN_ELITELIBERAL)
      {
         move(y++,0);
         addstr(courtname[j]);
      }

      move(y+1,4);
      addstr("前記の市民だった者");
      if(tossnum!=1)addstr("たち");
      addstr("は最高裁判所の職に尽くしていなかった。");
      move(y+2,0);
      addstr("よって、前記の市民だった者");
      if(tossnum!=1)addstr("たち");
      addstr("は、大統領が裁判所に代わり");
      move(y+3,0);
      addstr("上院の助言と承認を得て選出した保守の国");
      if(tossnum!=1)addstr("々");
      addstr("に追放する。");

      move(24,0);
      addstr("Cキーを押して開票状況を見る。");

      while(getkey()!='c');
   }

   if(ratify(2,-1,-1,1,canseethings))
   {
      //BLAST JUSTICES
      for(int j=0;j<COURTNUM;j++) if(court[j]!=ALIGN_ELITELIBERAL)
      {
         do generate_name(courtname[j]); while(len(courtname[j])>20);
         court[j]=ALIGN_ELITELIBERAL;
      }

      amendnum++;
   }

   if(canseethings)
   {
      move(24,0);
      addstr("何かキーを押して起こったことを省みる。");

      getkey();
   }
}

/* endgame - attempts to pass a constitutional amendment to help win the game */
void amendment_termlimits(char canseethings)
{
   if(termlimits)return; // Durr~! Don't pass this amendment if it's already passed!
   if(canseethings)
   {
      music.play(MUSIC_ELECTIONS);
      clear();

      set_color(COLOR_WHITE,COLOR_BLACK,1);

      move(12,6);
      addstr("全国委員会による合衆国憲法改正発議!");

      getkey();
   }

   //STATE THE AMENDMENT
   if(canseethings)
   {
      amendmentheading();

      move(2,4);
      addstr("保守政治家の保身的性質、および民主主義における腐敗の蔓延を鑑み、全ての上");
      move(3,0);
      addstr("下両院議員の任期は一期に制限する。");
      move(4,0);
      addstr("これは憲法改正後に上下両院が解散した後、ただちに適用される。");

      move(24,0);
      addstr("Cキーを押して開票状況を見る。");

      while(getkey()!='c');
   }

   if(ratify(2,-1,-1,0,canseethings))
   {
      termlimits = true;
      if(canseethings)
      {
         move(24,0);
         addstr("何かキーを押して新たな選挙を見る!                                            ");

         getkey();
      }
      elections_senate(0,canseethings);
      elections_senate(1,canseethings);
      elections_senate(2,canseethings);
      elections_house(canseethings);

      amendnum++;
   }
   else if(canseethings)
   {
      move(24,0);
      addstr("何かキーを押して起こったことを省みる。");

      getkey();
   }
}

/* endgame - attempts to pass a constitutional amendment to lose the game */
void reaganify(char canseethings)
{
   if(canseethings)
   {
      music.play(MUSIC_ELECTIONS);
      set_color(COLOR_WHITE,COLOR_BLACK,1);

      clear();
      move(12,3);
      addstr("保守強硬派議会による保守強硬発議!");

      getkey();

      //STATE THE AMENDMENT
      amendmentheading();
      move(2,4);
      addstr("エリート・リベラルの脅威による社会の後退という現実を鑑み、我々は合衆国憲法");
      move(3,0);
      addstr("の廃止を発議する。");
      move(4,0);
      addstr("かつての合衆国は、アメリカ連合国(CONFEDERATED STATES OF AMERICA)として再建国さ");
      move(5,0);
      addstr("れ、新たな境界線は指導的神学者によって決定される。");
      move(7,0);
      addstr("ロナルド・レーガンは国王となる。死してなお永遠に。");
      move(9,0);
      addstr("配下の愛情大臣ストロム・サーモンド、平和大臣ジェシー・ヘルムズ、そして真理大臣");
      move(10,0);
      addstr("ジェリー・ファルエルは終身位階とする。");
      move(12,0);
      addstr("上記の者が死去した後は名目上の地位を保ち、実際の意思決定は敬愛すべき財界首脳た");
      move(13,0);
      addstr("ちによって選出された財界代表者によってなされる。");
      move(15,0);
      addstr("人々はイエスに救いを求めてもよい。彼はただ耳を傾けるだけだからだ。");
      move(17,0);
      addstr("皆様よい一日を。");

      move(19,0);
      addstr("Cキーを押して開票状況を見る。");

      while(getkey()!='c');
   }

   if(ratify(-2,-1,-1,1,canseethings))
   {
      music.play(MUSIC_REAGANIFIED);
      if(canseethings)
      {
         move(24,0);
         addstr("何かキーを押して最後の瞬間に起こったことを見る。");

         getkey();
      }

      amendnum = 1; // Constitution repealed...

      //REAGANIFY
      if(canseethings)
      {
         strcpy(execname[EXEC_PRESIDENT],"ロナルド・レーガン");
         strcpy(execname[EXEC_VP],"ストロム・サーモンド");
         strcpy(execname[EXEC_STATE],"ジェシー・ヘルムズ");
         strcpy(execname[EXEC_ATTORNEY],"ジェリー・ファルエル");
         for(int e=0;e<EXECNUM;e++) exec[e]=ALIGN_ARCHCONSERVATIVE;
         for(int l=0;l<LAWNUM;l++) law[l]=ALIGN_ARCHCONSERVATIVE;
         liberalagenda(-1);
         savehighscore(END_REAGAN);
      }
      else
      {
         switch(cantseereason)
         {
            case 1:
               //DATING AND REAGANIFIED
               set_color(COLOR_WHITE,COLOR_BLACK,1);

               clear();
               move(12,15);
               addstr("この国の崩壊が迫る中、あなたは休暇を過ごしていた。");

               getkey();

               set_color(COLOR_WHITE,COLOR_BLACK,0);
               clear();
               move(12,13);
               addstr("保守派はこの世界を自分たちの思い通りに変えてしまった。");

               getkey();

               set_color(COLOR_BLACK,COLOR_BLACK,1);
               clear();
               move(12,8);
               addstr("あなたはいずれ捕らえられるだろう。もはやどうすることもできない。");

               getkey();

               savehighscore(END_DATING);
               break;
            case 2:
               //HIDING AND REAGANIFIED
               set_color(COLOR_WHITE,COLOR_BLACK,1);

               clear();
               move(12,15);
               addstr("この国の崩壊が迫る中、あなたは行方を眩ませていた。");

               getkey();

               set_color(COLOR_WHITE,COLOR_BLACK,0);
               clear();
               move(12,13);
               addstr("保守派はこの世界を自分たちの思い通りに変えてしまった。");

               getkey();

               set_color(COLOR_BLACK,COLOR_BLACK,1);
               clear();
               move(12,8);
               addstr("あなたはいずれ捕らえられるだろう。もはやどうすることもできない。");

               getkey();

               savehighscore(END_HIDING);
               break;
            case 3:
               //IF YOU ARE ALL IN PRISON, JUST PASS AWAY QUIETLY
               set_color(COLOR_WHITE,COLOR_BLACK,1);

               clear();
               move(12,22);
               addstr("投獄されている間にこの国は後退した。");

               getkey();

               set_color(COLOR_WHITE,COLOR_BLACK,0);
               clear();
               move(12,19);
               addstr("あなたの良心が解放されることはないだろう。");

               getkey();

               set_color(COLOR_BLACK,COLOR_BLACK,1);
               clear();
               move(12,32);
               addstr("光は消え去った…");

               getkey();

               savehighscore(END_PRISON);
               break;
            case 4:
               //DISBANDED AND REAGANIFIED
               set_color(COLOR_WHITE,COLOR_BLACK,1);

               clear();
               move(12,16);
               addstr("姿を消し平穏な日々を送っていた。だがもう限界だ。");

               getkey();

               set_color(COLOR_WHITE,COLOR_BLACK,0);
               clear();
               move(12,13);
               addstr("保守派はこの世界を自分たちの思い通りに変えてしまった。");

               getkey();

               set_color(COLOR_BLACK,COLOR_BLACK,1);
               clear();
               move(12,8);
               addstr("あなたはいずれ捕らえられるだろう。もはやどうすることもできない。");

               getkey();

               savehighscore(END_DISBANDLOSS);
               break;
         }
      }
      reset();
      viewhighscores(MUSIC_REAGANIFIED);
      end_game();
   }
   else
   {
      if(canseethings)
      {
         move(24,0);
         addstr("何かキーを押して安堵のため息をつく。                                         ");

         getkey();
      }
   }
}



/* endgame - attempts to pass a constitutional amendment to lose the game */
void stalinize(char canseethings)
{
   if(canseethings)
   {
      music.play(MUSIC_ELECTIONS);
      set_color(COLOR_WHITE,COLOR_BLACK,1);

      clear();
      move(12,11);
      addstr("スターリン主義議会によるスターリン主義発議!");

      getkey();

      //STATE THE AMENDMENT
      amendmentheading();

      move(2,4);
      addstr("プロレタリアートがブルジョワジー似非左翼エリート・リベラルに搾取されている");
      move(3,0);
      addstr("状況を鑑み、我々は合衆国憲法の廃止を発議する。");
      move(5,0);
      addstr("かつての合衆国は、アメリカ人民共和国(PEOPLE'S REPUBLIC OF AMERICA)として再建国");
      move(6,0);
      addstr("され、新たな境界線はスターリン主義者賢人によって決定される。");
      move(8,0);
      addstr("ヨシフ・スターリンは書記長兼首相となる。死してなお永遠に。");
      move(10,0);
      addstr("配下の共和国外務人民委員長ヴャチェスラフ・モロトフ、共和国内務人民委員長ラヴレ");
      move(11,0);
      addstr("ンチー・ベリヤは終身位階とする。");
      move(13,0);
      addstr("上記の者が死去した後は名目上の地位を保ち、実際の意思決定はスターリン党支持者に");
      move(14,0);
      addstr("よって選出されたスターリン党指導者によってなされる。");
      move(16,0);
      addstr("異議申し立てを行う者は、全て新たに併合したカナダの強制収容所に送られるか、運が");
      move(17,0);
      addstr("良ければ処刑される。");
      move(19,0);
      addstr("よい一日を。");

      move(24,0);
      addstr("Cキーを押して開票状況を見る。");

      while(getkey()!='c');
   }

   if(ratify(3,-2,-2,1,canseethings))
   {
      music.play(MUSIC_STALINIZED);
      if(canseethings)
      {
         move(24,0);
         addstr("何かキーを押して最後の瞬間に起こったことを見る。");

         getkey();
      }

      amendnum = 1; // Constitution repealed...

      //STALINIZE
      if(canseethings)
      {
         strcpy(execname[EXEC_PRESIDENT],"ヨシフ・スターリン");
         strcpy(execname[EXEC_VP],"ヨシフ・スターリン");
         strcpy(execname[EXEC_STATE],"ヴャチェスラフ・モロトフ");
         strcpy(execname[EXEC_ATTORNEY],"ラヴレンチー・ベリヤ");
         for(int e=0;e<EXECNUM;e++) exec[e]=ALIGN_STALINIST;
         for(int l=0;l<LAWNUM;l++) law[l]=stalinview(l,true)?ALIGN_ELITELIBERAL:ALIGN_ARCHCONSERVATIVE;
         liberalagenda(-2);
         savehighscore(END_STALIN);
      }
      else
      {
         switch(cantseereason)
         {
            case 1:
               //DATING AND STALINIZED
               set_color(COLOR_WHITE,COLOR_BLACK,1);

               clear();
               move(12,15);
               addstr("この国の崩壊が迫る中、あなたは休暇を過ごしていた。");

               getkey();

               set_color(COLOR_WHITE,COLOR_BLACK,0);
               clear();
               move(12,8);
               addstr("スターリン主義者はこの世界を自分たちの思い通りに変えてしまった。");

               getkey();

               set_color(COLOR_BLACK,COLOR_BLACK,1);
               clear();
               move(12,8);
               addstr("あなたはいずれ捕らえられるだろう。もはやどうすることもできない。");

               getkey();

               savehighscore(END_DATING);
               break;
            case 2:
               //HIDING AND STALINIZED
               set_color(COLOR_WHITE,COLOR_BLACK,1);

               clear();
               move(12,15);
               addstr("この国の崩壊が迫る中、あなたは行方を眩ませていた。");

               getkey();

               set_color(COLOR_WHITE,COLOR_BLACK,0);
               clear();
               move(12,8);
               addstr("スターリン主義者はこの世界を自分たちの思い通りに変えてしまった。");

               getkey();

               set_color(COLOR_BLACK,COLOR_BLACK,1);
               clear();
               move(12,8);
               addstr("あなたはいずれ捕らえられるだろう。もはやどうすることもできない。");

               getkey();

               savehighscore(END_HIDING);
               break;
            case 3:
               //IF YOU ARE ALL IN PRISON, YOU END UP IN A GULAG, COMRADE
               set_color(COLOR_WHITE,COLOR_BLACK,1);

               clear();
               move(12,22);
               addstr("投獄されている間にこの国は後退した。");

               getkey();

               set_color(COLOR_WHITE,COLOR_BLACK,0);
               clear();
               move(12,13);
               addstr("あなたは新たに併合されたカナダの強制収容所に送られる。");

               getkey();

               set_color(COLOR_BLACK,COLOR_BLACK,1);
               clear();
               move(12,26);
               addstr("光の届かないツンドラの地に…");

               getkey();

               savehighscore(END_PRISON);
               break;
            case 4:
               //DISBANDED AND STALINIZED
               set_color(COLOR_WHITE,COLOR_BLACK,1);

               clear();
               move(12,16);
               addstr("姿を消し平穏な日々を送っていた。だがもう限界だ。");

               getkey();

               set_color(COLOR_WHITE,COLOR_BLACK,0);
               clear();
               move(12,8);
               addstr("スターリン主義者はこの世界を自分たちの思い通りに変えてしまった。");

               getkey();

               set_color(COLOR_BLACK,COLOR_BLACK,1);
               clear();
               move(12,8);
               addstr("あなたはいずれ捕らえられるだろう。もはやどうすることもできない。");

               getkey();

               savehighscore(END_DISBANDLOSS);
               break;
         }
      }
      reset();
      viewhighscores(MUSIC_STALINIZED);
      end_game();
   }
   else
   {
      if(canseethings)
      {
         move(24,0);
         addstr("何かキーを押して安堵のため息をつく。                                         ");

         getkey();
      }
   }
}


/* endgame - checks if a constitutional amendment is ratified */
char ratify(int level,int lawview,int view,char congress,char canseethings)
{
   if(canseethings)
   {
      music.play(MUSIC_ELECTIONS);
      clear();

      set_color(COLOR_WHITE,COLOR_BLACK,1);

      move(0,0);
      addstr("批准手続:");
   }

   //THE STATE VOTE WILL BE BASED ON VIEW OF LAW
   int mood=publicmood(lawview);
   //OR OF A PARTICULAR ISSUE
   if(view>=0) mood=attitude[view];

   //CONGRESS
   bool ratified=false;

   int y=0;

   if(congress)
   {
      ratified=true;

      if(canseethings)
      {
         move(0,62);
         addstr("下院");

         move(0,70);
         addstr("上院");

         move(24,0);
         addstr("何かキーを押して開票状況を見る。                                             ");

         getkey();
      }

      bool yeswin_h=false,yeswin_s=false;
      int yesvotes_h=0,yesvotes_s=0,vote,s=0;

      for(int l=0;l<HOUSENUM;l++)
      {
         vote=house[l];
         if(vote>=-1&&vote<=1) vote+=LCSrandom(3)-1;

         if(level==vote) yesvotes_h++;

         if(l==HOUSENUM-1) if(yesvotes_h>=HOUSESUPERMAJORITY) yeswin_h=true;

         if(canseethings)
         {
            if(l==HOUSENUM-1&&yeswin_h) set_color(COLOR_WHITE,COLOR_BLACK,1);
            else if(l==HOUSENUM-1) set_color(COLOR_BLACK,COLOR_BLACK,1);
            else set_color(COLOR_WHITE,COLOR_BLACK,0);
            move(2,62);
            addstr("賛成");
            addstr(yesvotes_h);

            if(l==HOUSENUM-1&&!yeswin_h) set_color(COLOR_WHITE,COLOR_BLACK,1);
            else if(l==HOUSENUM-1) set_color(COLOR_BLACK,COLOR_BLACK,1);
            else set_color(COLOR_WHITE,COLOR_BLACK,0);
            move(3,62);
            addstr("反対");
            addstr(l+1-yesvotes_h);
         }

         if(l%4==0&&s<SENATENUM)
         {
            vote=senate[s++];
            if(vote>=-1&&vote<=1) vote+=LCSrandom(3)-1;

            if(level==vote) yesvotes_s++;
         }

         if(l==HOUSENUM-1&&yesvotes_s>=SENATESUPERMAJORITY) yeswin_s=true;

         if(canseethings)
         {
            if(l==HOUSENUM-1&&yeswin_s) set_color(COLOR_WHITE,COLOR_BLACK,1);
            else if(l==HOUSENUM-1) set_color(COLOR_BLACK,COLOR_BLACK,1);
            else set_color(COLOR_WHITE,COLOR_BLACK,0);
            move(2,70);
            addstr("賛成");
            addstr(yesvotes_s);

            if(l==HOUSENUM-1&&!yeswin_s) set_color(COLOR_WHITE,COLOR_BLACK,1);
            else if(l==HOUSENUM-1) set_color(COLOR_BLACK,COLOR_BLACK,1);
            else set_color(COLOR_WHITE,COLOR_BLACK,0);
            move(3,70);
            addstr("反対");
            addstr(s-yesvotes_s);

            if(l%5==0) pause_ms(10);
         }
      }

      if(!yeswin_h||!yeswin_s) ratified=false;

      y+=4;
   }
   else ratified=true;

   if(level==3) level=-2; // special case for Stalinists: do this after Congress but before the states

   //STATES
   if(ratified)
   {
      ratified=false;

      int yesstate=0;

      if(canseethings)
      {
         set_color(COLOR_WHITE,COLOR_BLACK,1);

         for(int s=0;s<50;s++)
         {
            if(s<17) move(5+s,0);
            else if(s<34) move(5+s-17,27);
            else move(5+s-34,54);
            addstr(statename(s));
         }

         move(24,0);
         addstr("何かキーを押して開票状況を見る。                                             ");

         getkey();
      }

      int vote,smood;
      for(int s=0;s<STATENUM;s++)
      {
         smood=mood;

         // State biases.
         int multiplier = 5+LCSrandom(3);
         switch(s)
         {
            case 0:smood-=3*multiplier;break;  // Alabama
            case 1:smood-=4*multiplier;break;  // Alaska
            case 2:smood-=1*multiplier;break;  // Arkansas
            case 3:smood-=2*multiplier;break;  // Arizona
            case 4:smood+=4*multiplier;break;  // California
            case 5:break;                      // Colorado
            case 6:smood+=3*multiplier;break;  // Connecticut
            case 7:smood+=3*multiplier;break;  // Delaware
            case 8:break;                      // Florida
            case 9:smood-=2*multiplier;break;  // Georgia
            case 10:smood+=4*multiplier;break; // Hawaii
            case 11:smood-=5*multiplier;break; // Idaho
            case 12:smood+=4*multiplier;break; // Illinois
            case 13:smood-=1*multiplier;break; // Indiana
            case 14:smood+=1*multiplier;break; // Iowa
            case 15:smood-=3*multiplier;break; // Kansas
            case 16:smood-=3*multiplier;break; // Kentucky
            case 17:smood-=1*multiplier;break; // Louisiana
            case 18:smood+=2*multiplier;break; // Maine
            case 19:smood+=3*multiplier;break; // Maryland
            case 20:smood+=6*multiplier;break; // Massachusetts
            case 21:smood+=2*multiplier;break; // Michigan
            case 22:smood+=2*multiplier;break; // Minnesota
            case 23:smood-=4*multiplier;break; // Mississippi
            case 24:smood-=1*multiplier;break; // Missouri
            case 25:smood-=2*multiplier;break; // Montana
            case 26:smood-=3*multiplier;break; // Nebraska
            case 27:break;                     // Nevada
            case 28:smood+=1*multiplier;break; // New Hampshire
            case 29:smood+=3*multiplier;break; // New Jersey
            case 30:smood+=1*multiplier;break; // New Mexico
            case 31:smood+=5*multiplier;break; // New York
            case 32:smood-=1*multiplier;break; // North Carolina
            case 33:smood-=3*multiplier;break; // North Dakota
            case 34:break;                     // Ohio
            case 35:smood-=4*multiplier;break; // Oklahoma
            case 36:smood+=3*multiplier;break; // Oregon
            case 37:smood+=2*multiplier;break; // Pennsylvania
            case 38:smood+=4*multiplier;break; // Rhode Island
            case 39:smood-=5*multiplier;break; // South Carolina
            case 40:smood-=3*multiplier;break; // South Dakota
            case 41:smood-=2*multiplier;break; // Tennessee
            case 42:smood-=4*multiplier;break; // Texas
            case 43:smood-=6*multiplier;break; // Utah
            case 44:smood+=5*multiplier;break; // Vermont
            case 45:break;                     // Virginia
            case 46:smood+=3*multiplier;break; // Washington
            case 47:smood-=2*multiplier;break; // West Virginia
            case 48:smood+=2*multiplier;break; // Wisconsin
            case 49:smood-=5*multiplier;break; // Wyoming
         }

         vote=-2;
         if(LCSrandom(100)<smood)vote++;
         if(LCSrandom(100)<smood)vote++;
         if(LCSrandom(100)<smood)vote++;
         if(LCSrandom(100)<smood)vote++;
         if(vote==1&&!LCSrandom(2)) vote=2;
         if(vote==-1&&!LCSrandom(2)) vote=-2;

         if(canseethings)
         {
            set_color(COLOR_WHITE,COLOR_BLACK,1);
            if(s<17) move(5+s,22);
            else if(s<34) move(5+s-17,49);
            else move(5+s-34,76);
         }
         if(vote==level)
         {
            yesstate++;
            if(canseethings) addstr("賛成");
         }
         else if(canseethings) addstr("反対");

         if(canseethings)
         {
            if(s==STATENUM-1&&yesstate>=STATESUPERMAJORITY) set_color(COLOR_WHITE,COLOR_BLACK,1);
            else if(s==STATENUM-1) set_color(COLOR_BLACK,COLOR_BLACK,1);
            else set_color(COLOR_WHITE,COLOR_BLACK,0);
            move(23,50);
            addstr("賛成");
            addstr(yesstate);

            if(s==STATENUM-1&&yesstate<STATESUPERMAJORITY) set_color(COLOR_WHITE,COLOR_BLACK,1);
            else if(s==STATENUM-1) set_color(COLOR_BLACK,COLOR_BLACK,1);
            else set_color(COLOR_WHITE,COLOR_BLACK,0);
            move(23,60);
            addstr("反対");
            addstr(s+1-yesstate);

            pause_ms(50);
         }
      }

      if(yesstate>=STATESUPERMAJORITY) ratified=true;
   }

   if(canseethings)
   {
      set_color(COLOR_WHITE,COLOR_BLACK,1);
      move(23,0);
      if(ratified) addstr("合衆国憲法改正 可決");
      else addstr("合衆国憲法改正 否決");
   }

   return ratified;
}



/* endgame - header for announcing constitutional amendments */
void amendmentheading()
{
   clear();

   set_color(COLOR_WHITE,COLOR_BLACK,1);

   mvaddstr(0,0,"合衆国憲法改正発議 ");
   romannumeral(amendnum);
   addstr(":");
}
