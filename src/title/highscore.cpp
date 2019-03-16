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

/* displays the high score board */
void viewhighscores(int musicoverride)
{
   if(musicoverride!=MUSIC_OFF) music.play(musicoverride);
   int s;
   loadhighscores();

   short validsum=0;
   for(s=0;s<SCORENUM;s++)
   {
      if(score[s].valid)validsum++;
   }

   if(!validsum)return;

   clear();

   set_color(COLOR_WHITE,COLOR_BLACK,1);
   move(0,0);
   addstr("リベラル・エリート");

   int y=2;
   for(s=0;s<SCORENUM;s++)
   {
      if(score[s].valid)
      {
         if(yourscore==s&&score[s].endtype==END_WON)set_color(COLOR_GREEN,COLOR_BLACK,1);
         else if(yourscore==s)set_color(COLOR_RED,COLOR_BLACK,1);
         else set_color(COLOR_WHITE,COLOR_BLACK,1);
         move(y,0);
         addstr(score[s].slogan);
         if(yourscore==s&&score[s].endtype==END_WON)set_color(COLOR_GREEN,COLOR_BLACK,0);
         else if(yourscore==s)set_color(COLOR_RED,COLOR_BLACK,0);
         else set_color(COLOR_WHITE,COLOR_BLACK,0);
         move(y+1,0);
         addstr(score[s].year);
         addstr("年");
         addstr(getmonth(score[s].month));
         addstr(" ");
         switch(score[s].endtype)
         {
            case END_WON:
               addstr("リベラル・クライム・スコードはこの国をリベラル化した。");
               if(yourscore==s&&musicoverride==MUSIC_OFF) music.play(MUSIC_VICTORY);
               break;
            case END_POLICE:
               addstr("リベラル・クライム・スコードは法の裁きにかけられた。");
               if(yourscore==s&&musicoverride==MUSIC_OFF) music.play(MUSIC_DEFEAT);
               break;
            case END_CIA:
               addstr("リベラル・クライム・スコードは抹消された。");
               if(yourscore==s&&musicoverride==MUSIC_OFF) music.play(MUSIC_DEFEAT);
               break;
            case END_HICKS:
               addstr("リベラル・クライム・スコードは暴徒よって破壊された。");
               if(yourscore==s&&musicoverride==MUSIC_OFF) music.play(MUSIC_DEFEAT);
               break;
            case END_CORP:
               addstr("リベラル・クライム・スコードはリストラされた。");
               if(yourscore==s&&musicoverride==MUSIC_OFF) music.play(MUSIC_DEFEAT);
               break;
            case END_DEAD:
               addstr("リベラル・クライム・スコードは志半ばに倒れた。");
               if(yourscore==s&&musicoverride==MUSIC_OFF) music.play(MUSIC_DEFEAT);
               break;
            case END_REAGAN:
               addstr("リベラル・クライム・スコードはレーガン化した。");
               if(yourscore==s&&musicoverride==MUSIC_OFF) music.play(MUSIC_REAGANIFIED);
               break;
            case END_PRISON:
               addstr("リベラル・クライム・スコードは獄死した。");
               if(yourscore==s&&musicoverride==MUSIC_OFF) music.play(MUSIC_DEFEAT);
               break;
            case END_EXECUTED:
               addstr("リベラル・クライム・スコードは処刑された。");
               if(yourscore==s&&musicoverride==MUSIC_OFF) music.play(MUSIC_DEFEAT);
               break;
            case END_DATING:
               addstr("リベラル・クライム・スコードは最後の余暇を楽しんだ。");
               if(yourscore==s&&musicoverride==MUSIC_OFF) music.play(MUSIC_DEFEAT);
               break;
            case END_HIDING:
               addstr("リベラル・クライム・スコードは永遠に隠れた。");
               if(yourscore==s&&musicoverride==MUSIC_OFF) music.play(MUSIC_DEFEAT);
               break;
            case END_DISBANDLOSS:
               addstr("リベラル・クライム・スコードは消滅した。");
               if(yourscore==s&&musicoverride==MUSIC_OFF) music.play(MUSIC_DEFEAT);
               break;
            case END_DISPERSED:
               addstr("リベラル・クライム・スコードは全滅した。");
               if(yourscore==s&&musicoverride==MUSIC_OFF) music.play(MUSIC_DEFEAT);
               break;
            case END_CCS:
               addstr("リベラル・クライム・スコードは犯罪集団に倒された。");
               if(yourscore==s&&musicoverride==MUSIC_OFF) music.play(MUSIC_DEFEAT);
               break;
            case END_FIREMEN:
               addstr("リベラル・クライム・スコードは焼却された。");
               if(yourscore==s&&musicoverride==MUSIC_OFF) music.play(MUSIC_DEFEAT);
               break;
            case END_STALIN:
               addstr("リベラル・クライム・スコードはスターリン化した。");
               if(yourscore==s&&musicoverride==MUSIC_OFF) music.play(MUSIC_STALINIZED);
               break;
         }

         move(y+2,0);
         addstr("教化: ");
         addstr(score[s].stat_recruits);

         move(y+3,0);
         addstr("死亡: ");
         addstr(score[s].stat_dead);

         move(y+2,20);
         addstr("殺害: ");
         addstr(score[s].stat_kills);

         move(y+3,20);
         addstr("誘拐: ");
         addstr(score[s].stat_kidnappings);

         move(y+2,40);
         addstr("$ 収入: ");
         addstr(score[s].stat_funds);

         move(y+3,40);
         addstr("$ 支出: ");
         addstr(score[s].stat_spent);

         move(y+2,60);
         addstr("国旗購入: ");
         addstr(score[s].stat_buys);

         move(y+3,60);
         addstr("国旗焼却: ");
         addstr(score[s].stat_burns);

         y+=4;
      }
   }

   set_color(COLOR_GREEN,COLOR_BLACK,1);

   //UNIVERSAL STATS
   move(22,0);
   addstr("万国リベラル統計:");

   move(23,0);
   addstr("教化: ");
   addstr(ustat_recruits);

   move(24,0);
   addstr("死亡: ");
   addstr(ustat_dead);

   move(23,20);
   addstr("殺害: ");
   addstr(ustat_kills);

   move(24,20);
   addstr("誘拐: ");
   addstr(ustat_kidnappings);

   move(23,40);
   addstr("$ 収入: ");
   addstr(ustat_funds);

   move(24,40);
   addstr("$ 支出: ");
   addstr(ustat_spent);

   move(23,60);
   addstr("国旗購入: ");
   addstr(ustat_buys);

   move(24,60);
   addstr("国旗焼却: ");
   addstr(ustat_burns);

   getkey();
}

/* loads the high scores file */
void loadhighscores()
{
   for(int s=0;s<SCORENUM;s++)score[s].valid=0;

   //LOAD FILE
   int loadversion;

   FILE *h=LCSOpenFile("score.dat", "rb", LCSIO_PRE_HOME);
   if(h!=NULL)
   {
      fread(&loadversion,sizeof(int),1,h);

      if(loadversion<lowestloadscoreversion)
      {
         LCSCloseFile(h);
         return;
      }

      fread(&ustat_recruits,sizeof(int),1,h);
      fread(&ustat_dead,sizeof(int),1,h);
      fread(&ustat_kills,sizeof(int),1,h);
      fread(&ustat_kidnappings,sizeof(int),1,h);
      fread(&ustat_funds,sizeof(int),1,h);
      fread(&ustat_spent,sizeof(int),1,h);
      fread(&ustat_buys,sizeof(int),1,h);
      fread(&ustat_burns,sizeof(int),1,h);
      fread(score,sizeof(highscorest),SCORENUM,h);

      LCSCloseFile(h);
   }
}

/* saves a new high score */
void savehighscore(char endtype)
{
   loadhighscores();

   //MERGE THE STATS
   ustat_recruits+=stat_recruits;
   ustat_dead+=stat_dead;
   ustat_kills+=stat_kills;
   ustat_kidnappings+=stat_kidnappings;
   ustat_funds+=ledger.total_income;
   ustat_spent+=ledger.total_expense;
   ustat_buys+=stat_buys;
   ustat_burns+=stat_burns;

   //PLACE THIS HIGH SCORE BY DATE IF NECESSARY
   yourscore=-1;

   for(int s=0;s<SCORENUM;s++)
   {
      if((endtype==END_WON&&score[s].endtype==END_WON&&
         year==score[s].year&&month==score[s].month&&
         ledger.total_expense+ledger.total_expense>score[s].stat_spent+score[s].stat_funds)||

         (endtype==END_WON&&score[s].endtype==END_WON
         &&(year<score[s].year ||
         (year==score[s].year && month<score[s].month)))||

         (endtype==END_WON&&score[s].endtype!=END_WON)||

         (endtype!=END_WON&&score[s].endtype!=END_WON&&
         ledger.total_expense+ledger.total_income>score[s].stat_spent+score[s].stat_funds)||

         score[s].valid==0)
      {
         for(int s2=SCORENUM-1;s2>=s+1;s2--)
         {
            score[s2]=score[s2-1];
         }

         strcpy(score[s].slogan,slogan);
         score[s].month=month;
         score[s].year=year;
         score[s].stat_recruits=stat_recruits;
         score[s].stat_dead=stat_dead;
         score[s].stat_kills=stat_kills;
         score[s].stat_kidnappings=stat_kidnappings;
         score[s].stat_funds=ledger.total_income;
         score[s].stat_spent=ledger.total_expense;
         score[s].stat_buys=stat_buys;
         score[s].stat_burns=stat_burns;
         score[s].valid=1;
         score[s].endtype=endtype;

         yourscore=s;
         break;
      }
   }

   FILE *h=LCSOpenFile("score.dat","wb",LCSIO_PRE_HOME);
   if(h!=NULL)
   {
      int lversion=version;
      fwrite(&lversion,sizeof(int),1,h);

      fwrite(&ustat_recruits,sizeof(int),1,h);
      fwrite(&ustat_dead,sizeof(int),1,h);
      fwrite(&ustat_kills,sizeof(int),1,h);
      fwrite(&ustat_kidnappings,sizeof(int),1,h);
      fwrite(&ustat_funds,sizeof(int),1,h);
      fwrite(&ustat_spent,sizeof(int),1,h);
      fwrite(&ustat_buys,sizeof(int),1,h);
      fwrite(&ustat_burns,sizeof(int),1,h);
      fwrite(score,sizeof(highscorest),SCORENUM,h);

      LCSCloseFile(h);
   }
}

