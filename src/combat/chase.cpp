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

enum CarChaseStatus
{
   CARCHASE_CONTINUE,
   CARCHASE_GOTOFOOTCHASE,
   CARCHASE_SURRENDER,
   CARCHASE_EVERYONEDEAD,
   CARCHASE_ESCAPED
};

bool chasesequence()
{
   int p=0,chasenum=0,v2=0;

   reloadparty();

   //NOTE: THIS FUNCTION RETURNS 1 IF ANYBODY ESCAPES
      //IT CAN DELETE CREATURES AND VEHICLES, BUT SHOULD NOT DELETE SQUADS
         //AS SQUADS MAY BE FICTITIOUS AND WILL BE DELETED LATER ANYWAY

   //BAIL IF NO CHASERS
   for(int e=0;e<ENCMAX;e++) if(encounter[e].exists) chasenum++;
   if(!chasenum)
   {
      gamelog.newline();
      return 1;
   }

   chaseseq.friendcar.clear();
   for(p=0;p<6;p++)
   {
      if(activesquad->squad[p]==NULL) continue;

      if(activesquad->squad[p]->carid!=-1)
      {
         int v=id_getcar(activesquad->squad[p]->carid);
         if(v!=-1)
         {
            for(v2=0;v2<len(chaseseq.friendcar);v2++) if(chaseseq.friendcar[v2]->id()==vehicle[v]->id()) break;
            if(v2==len(chaseseq.friendcar)) chaseseq.friendcar.push_back(vehicle[v]);
         }
      }
   }

   mode=GAMEMODE_CHASECAR;
   music.play(MUSIC_CARCHASE);

   clear();
   set_color(COLOR_WHITE,COLOR_BLACK,1);
   move(0,0);
   addstr("この場所から引き上げるとき、保守に付けられているのを感じた!", gamelog);
   gamelog.newline(); //New line.

   getkey();

   if(location[chaseseq.location]->parent!=-1)
      chaseseq.location=location[chaseseq.location]->parent;

   short obstacle=-1;

   while(true)
   {
      int partysize=squadsize(activesquad),partyalive=squadalive(activesquad),encsize=0;
      for(int e=0;e<ENCMAX;e++) if(encounter[e].exists) encsize++;

      clear();

      set_color(COLOR_WHITE,COLOR_BLACK,0);
      mvaddstr(0,0,location[chaseseq.location]->getname());

      //PRINT PARTY
      if(partyalive==0) party_status=-1;
      printparty();

      if(partyalive>0)
      {
         //PRINT DRIVING SITUATION AND INSTRUCTIONS
         if(partysize>1)set_color(COLOR_WHITE,COLOR_BLACK,0);
         else set_color(COLOR_BLACK,COLOR_BLACK,1);
         move(9,40);
         addstr("O - リベラルの順序を変更する");
         if(partysize>0&&(party_status==-1||partysize>1))set_color(COLOR_WHITE,COLOR_BLACK,0);
         else set_color(COLOR_BLACK,COLOR_BLACK,1);
         move(10,40);
         addstr("# - リベラルの状態を表示する");
         if(party_status!=-1)set_color(COLOR_WHITE,COLOR_BLACK,0);
         else set_color(COLOR_BLACK,COLOR_BLACK,1);
         move(11,40);
         addstr("0 - 部隊の状態を表示する");

         int y=12;
         if(obstacle==-1)
         {
            set_color(COLOR_WHITE,COLOR_BLACK,0);
            move(9,1);
            addstr("D - 奴らを巻く!");
            move(10,1);
            addstr("E - 装備");
            move(11,1);
            addstr("F - 戦う!");
         }
         else
         {
            switch(obstacle)
            {
               case CARCHASE_OBSTACLE_FRUITSTAND:
                  set_color(COLOR_MAGENTA,COLOR_BLACK,1);
                  move(9,1);
                  //LIMIT :------------------------------------:
                  addstr("オンボロのフルーツスタンドに向かっている!", gamelog);
                  gamelog.newline(); //Newline!
                  move(10,1);
                  addstr("D - 急転換で避ける!");
                  move(11,1);
                  addstr("F - 安全第一でそのまま突っ込む!");
                  break;
               case CARCHASE_OBSTACLE_TRUCKPULLSOUT:
                  set_color(COLOR_MAGENTA,COLOR_BLACK,1);
                  move(9,1);
                  //LIMIT :------------------------------------:
                  addstr("トラックが車線を塞ごうとしている!", gamelog);
                  gamelog.newline(); //Newline.
                  move(10,1);
                  addstr("D - 加速!");
                  move(11,1);
                  addstr("F - 減速!");
                  break;
               case CARCHASE_OBSTACLE_CROSSTRAFFIC:
                  set_color(COLOR_MAGENTA,COLOR_BLACK,1);
                  move(9,1);
                  //LIMIT :------------------------------------:
                  addstr("赤信号だ!", gamelog);
                  gamelog.newline(); //Newline...
                  move(10,1);
                  addstr("D - そのまま進む!");
                  move(11,1);
                  addstr("F - 減速してターン!");
                  break;
               case CARCHASE_OBSTACLE_CHILD:
                  set_color(COLOR_MAGENTA,COLOR_BLACK,1);
                  move(9,1);
                  //LIMIT :------------------------------------:
                  addstr("ボールを追いかける子供が!", gamelog);
                  gamelog.newline(); //Newline.
                  move(10,1);
                  addstr("D - 急転換で避ける!");
                  move(11,1);
                  addstr("F - 急ブレーキをかける!");
                  break;
            }
         }
         move(y,1);
         addstr("B - 車を捨てて逃げる!");
         if(chaseseq.canpullover)
         {
            move(y+1,1);
            addstr("P - 車を止める");
         }
      }
      else
      {
         //DESTROY ALL CARS BROUGHT ALONG WITH PARTY
         delete_and_clear(chaseseq.friendcar,vehicle);

         for(p=0;p<6;p++)
         {
            if(activesquad->squad[p]==NULL) continue;

            activesquad->squad[p]->die();
            activesquad->squad[p]->location=-1;
            activesquad->squad[p]=NULL;
         }
         endcheck(-2); // play the right music in case we're dead

         set_color(COLOR_WHITE,COLOR_BLACK,0);
         move(9,1);
         addstr("C - 運転技術のなさを反省する");
      }

      //PRINT ENEMIES
      printchaseencounter();

      int c=getkey();

      if(partyalive==0&&c=='c')
      {
         if(!endcheck())
         {
            mode=GAMEMODE_BASE;
            gamelog.nextMessage(); //Next message.
            return 0;
         }
      }

      if(partyalive>0)
      {
         if(c=='o'&&partysize>1)orderparty();

         if(c=='0')party_status=-1;

         if(c>='1'&&c<='6')
         {
            if(activesquad->squad[c-'1']!=NULL)
            {
               if(party_status==c-'1') fullstatus(party_status);
               else party_status=c-'1';
            }
         }

         if(c=='b')
         {
            delete_and_clear(chaseseq.friendcar,vehicle);

            for(int p=0;p<6;p++)
            {
               if(activesquad->squad[p]==NULL) continue;
               activesquad->squad[p]->carid=-1;
            }

            return footchase();
         }
         else if(c=='p')
         {
            if(chaseseq.canpullover)
            {
               chase_giveup();
               mode=GAMEMODE_BASE;
               gamelog.nextMessage(); //Next message.
               return 0;
            }
         }
         else if(obstacle==-1)
         {
            if(c=='d')
            {
               if(encounter[0].exists&&
                  encounter[0].type==CREATURE_COP)
               {
                  if(chaseseq.location) sitestory->crime.push_back(CRIME_CARCHASE);
                  criminalizeparty(LAWFLAG_RESIST);
               }
               evasivedrive();
               enemyattack();
               youattack();
               creatureadvance();
               if(drivingupdate(obstacle))
               {
                  partysize=squadsize(activesquad),partyalive=squadalive(activesquad);
                  if(partyalive>0) return footchase();
               }
            }

            if(c=='f')
            {
               if(encounter[0].exists&&
                  encounter[0].type==CREATURE_COP)
               {
                  if(chaseseq.location) sitestory->crime.push_back(CRIME_CARCHASE);
                  criminalizeparty(LAWFLAG_RESIST);
               }
               youattack();
               enemyattack();
               creatureadvance();
               if(drivingupdate(obstacle))
               {
                  partysize=squadsize(activesquad),partyalive=squadalive(activesquad);
                  if(partyalive>0) return footchase();
               }
            }

            if(c=='e') equip(activesquad->loot,-1);
         }
         else
         {
            switch(obstacle)
            {
            case CARCHASE_OBSTACLE_CHILD:
            case CARCHASE_OBSTACLE_CROSSTRAFFIC:
            case CARCHASE_OBSTACLE_TRUCKPULLSOUT:
            case CARCHASE_OBSTACLE_FRUITSTAND:
               if(c=='d')
               {
                  if(obstacledrive(obstacle,0))
                  {
                     partysize=squadsize(activesquad),partyalive=squadalive(activesquad);
                     if(partyalive>0) return footchase();
                  }
                  creatureadvance();
                  drivingupdate(obstacle);
               }
               if(c=='f')
               {
                  if(obstacledrive(obstacle,1))
                  {
                     partysize=squadsize(activesquad),partyalive=squadalive(activesquad);
                     if(partyalive>0) return footchase();
                  }
                  creatureadvance();
                  if(drivingupdate(obstacle))
                  {
                     partysize=squadsize(activesquad),partyalive=squadalive(activesquad);
                     if(partyalive>0) return footchase();
                  }
               }
               break;
            }
         }

         //HAVE YOU LOST ALL OF THEM?
            //THEN LEAVE
         partysize=squadsize(activesquad),partyalive=squadalive(activesquad);
         int baddiecount=0;
         for(int e=0;e<ENCMAX;e++)
         {
            if(encounter[e].carid!=-1&&
               encounter[e].enemy()&&
               encounter[e].alive&&
               encounter[e].exists)baddiecount++;
         }
         if(partyalive>0&&baddiecount==0)
         {
            set_color(COLOR_WHITE,COLOR_BLACK,1);
            clearmessagearea();
            move(16,1);
            addstr("どうやら逃げ切ったようだ!", gamelog);
            gamelog.newline(); //New line.

            getkey();

            for(int p=0;p<len(pool);p++)
               for(int w=0;w<BODYPARTNUM;w++)
                  pool[p]->wound[w]&=~WOUND_BLEEDING;
            mode=GAMEMODE_BASE;
            //Make sure all possible exits of the chase have the nextMessage() call
            //to ensure that the gamelog is split properly into blocks.
            gamelog.nextMessage();
            return 1;
         }
      }
   }

   mode=GAMEMODE_BASE;
   //Make sure all possible exits of the chase have the nextMessage() call
   //to ensure that the gamelog is split properly into blocks.
   gamelog.nextMessage();
   return 1;
}

bool footchase()
{
   //NOTE: THIS FUNCTION RETURNS 1 IF ANYBODY ESCAPES
   //IT SHOULD NOT DELETE SQUADS OR CREATURES
   //SQUADS MAY BE FICTITIOUS AND BOTH WILL BE DELETED LATER ANYWAY
   int p;
   reloadparty();

   //NUKE ALL CARS
   delete_and_clear(chaseseq.enemycar);

   //BAIL IF NO CHASERS
   int chasenum=0;
   for(int e=0;e<ENCMAX;e++)
   {
      if(encounter[e].exists) chasenum++;
      encounter[e].carid=-1;
   }
   if(chasenum==0) return 1;

   mode=GAMEMODE_CHASEFOOT;
   music.play(MUSIC_FOOTCHASE);

   clear();
   set_color(COLOR_WHITE,COLOR_BLACK,1);
   move(0,0);
   addstr("建物を出ると、保守に付けられているのを感じた!", gamelog);
   gamelog.newline(); //New line.

   getkey();

   while(true)
   {
      int partysize=squadsize(activesquad),partyalive=squadalive(activesquad),encsize=0;
      for(int e=0;e<ENCMAX;e++) if(encounter[e].exists) encsize++;

      clear();

      set_color(COLOR_WHITE,COLOR_BLACK,0);
      mvaddstr(0,0,location[chaseseq.location]->getname());

      //PRINT PARTY
      if(partyalive==0) party_status=-1;
      printparty();

      if(partyalive>0)
      {
         //PRINT DRIVING SITUATION AND INSTRUCTIONS
         if(partysize>1) set_color(COLOR_WHITE,COLOR_BLACK,0);
         else set_color(COLOR_BLACK,COLOR_BLACK,1);
         move(9,40);
         addstr("O - リベラルの順序を変更する");
         if(partysize>0&&(party_status==-1||partysize>1))set_color(COLOR_WHITE,COLOR_BLACK,0);
         else set_color(COLOR_BLACK,COLOR_BLACK,1);
         move(10,40);
         addstr("# - リベラルの状態を表示する");
         if(party_status!=-1)set_color(COLOR_WHITE,COLOR_BLACK,0);
         else set_color(COLOR_BLACK,COLOR_BLACK,1);
         move(11,40);
         addstr("0 - 部隊の状態を表示する");

         set_color(COLOR_WHITE,COLOR_BLACK,0);
         move(9,1);
         addstr("D - 奴らを巻く!");
         move(10,1);
         addstr("E - 装備");
         move(11,1);
         addstr("F - 戦う!");
         if(chaseseq.canpullover)
         {
            move(12,1);
            addstr("G - 投降する");
         }
      }
      else
      {
         //DESTROY ALL CARS BROUGHT ALONG WITH PARTY
         delete_and_clear(chaseseq.friendcar,vehicle);

         for(p=0;p<6;p++)
         {
            if(activesquad->squad[p]==NULL)continue;

            activesquad->squad[p]->die();
            activesquad->squad[p]->location=-1;
            activesquad->squad[p]=NULL;
         }
         endcheck(-2); // play the right music in case we're dead

         set_color(COLOR_WHITE,COLOR_BLACK,0);
         move(9,1);
         addstr("C - 逃げ足の遅さを反省する");
      }

      //PRINT ENEMIES
      printchaseencounter();

      // check if we fought the previous loop; if so, add a blank gamelog line
      if(foughtthisround)gamelog.newline();
      foughtthisround=0;

      int c=getkey();

      if(partyalive==0&&c=='c')
      {
         if(!endcheck())
         {
            mode=GAMEMODE_BASE;
            gamelog.nextMessage(); //Output this message, preparing for next.
            return 0;
         }
      }

      if(partyalive>0)
      {
         if(c=='o'&&partysize>1) orderparty();

         if(c=='0') party_status=-1;

         if(c>='1'&&c<='6')
         {
            if(activesquad->squad[c-'1']!=NULL)
            {
               if(party_status==c-'1') fullstatus(party_status);
               else party_status=c-'1';
            }
         }

         if(c=='g')
         {
            if(chaseseq.canpullover)
            {
               chase_giveup();
               mode=GAMEMODE_BASE;
               gamelog.nextMessage(); //Get ready for the next message.
               return 0;
            }
         }
         if(c=='d')
         {
            if(encounter[0].exists&&
               encounter[0].type==CREATURE_COP)
            {
               sitestory->crime.push_back(CRIME_FOOTCHASE);
               criminalizeparty(LAWFLAG_RESIST);
            }
            evasiverun();
            enemyattack();
            creatureadvance();
         }

         if(c=='f')
         {
            if(encounter[0].exists&&
               encounter[0].type==CREATURE_COP)
            {
               sitestory->crime.push_back(CRIME_FOOTCHASE);
               criminalizeparty(LAWFLAG_RESIST);
            }
            youattack();
            enemyattack();
            creatureadvance();
         }

         if(c=='e') equip(activesquad->loot,-1);

         //HAVE YOU LOST ALL OF THEM?
            //THEN LEAVE
         partysize=squadsize(activesquad),partyalive=squadalive(activesquad);
         int baddiecount=0;
         for(int e=0;e<ENCMAX;e++)
         {
            if(encounter[e].enemy()&&
               encounter[e].alive&&
               encounter[e].exists)baddiecount++;
         }
         if(partyalive>0&&baddiecount==0)
         {
            set_color(COLOR_WHITE,COLOR_BLACK,1);
            clearmessagearea();
            move(16,1);
            addstr("どうやら逃げ切ったようだ!", gamelog);
            gamelog.newline(); //New line.

            getkey();

            for(int p=0;p<len(pool);p++)
               for(int w=0;w<BODYPARTNUM;w++)
                  pool[p]->wound[w]&=~WOUND_BLEEDING;
            mode=GAMEMODE_BASE;
            gamelog.newline();
            return 1;
         }
      }
   }

   mode=GAMEMODE_BASE;
   //All possible exits of the chase should be covered by a nextMessage() call.
   gamelog.nextMessage();
   return 1;
}


#define DRIVING_RANDOMNESS 13
void evasivedrive()
{
   int e;
   vector<long> yourrolls,theirrolls,theirrolls_id,theirrolls_drv;
   long yourworst=10000;
   for(int p=0;p<6;p++)
   {
      if(activesquad->squad[p]==NULL) continue;
      if(activesquad->squad[p]->alive&&
         activesquad->squad[p]->is_driver)
      {
         int v=id_getcar(activesquad->squad[p]->carid);
         yourrolls.push_back(driveskill(*activesquad->squad[p],*(vehicle[v]))+LCSrandom(DRIVING_RANDOMNESS));
         
         switch (fieldskillrate)
         {
            case FIELDSKILLRATE_FAST:
               activesquad->squad[p]->train(SKILL_DRIVING,LCSrandom(20));break;
            case FIELDSKILLRATE_CLASSIC:
               activesquad->squad[p]->train(SKILL_DRIVING,LCSrandom(20));break;
            case FIELDSKILLRATE_HARD:
               activesquad->squad[p]->train(SKILL_DRIVING,LCSrandom(MAX(1, 20 - activesquad->squad[p]->get_skill(SKILL_DRIVING))));break;
         }
         if(yourworst>yourrolls.back()) yourworst=yourrolls.back();
      }
   }
   if(!len(yourrolls)) yourrolls.push_back(0); //error -- and for this you get a 0

   for(e=0;e<ENCMAX;e++)
   {
      if(encounter[e].carid!=-1&&
         encounter[e].enemy()&&
         encounter[e].alive&&
         encounter[e].exists&&
         encounter[e].is_driver)
      {
         for(int v=0;v<len(chaseseq.enemycar);v++)
         {
            if(chaseseq.enemycar[v]->id()==encounter[e].carid)
            {
               theirrolls.push_back(driveskill(encounter[e],*chaseseq.enemycar[v])+LCSrandom(DRIVING_RANDOMNESS));
               theirrolls_id.push_back(encounter[e].carid);
               theirrolls_drv.push_back(encounter[e].id);
            }
         }
      }
      else if(encounter[e].carid==-1) encounter[e].exists=false;
   }

   clearmessagearea();
   set_color(COLOR_WHITE,COLOR_BLACK,1);
   move(16,1);
   switch(LCSrandom(4))
   {
   case 0:
      addstr("アクセルを目いっぱい踏み込んだ!", gamelog);
      gamelog.newline(); //Newline.
      break;
   case 1:
      addstr("コーナーで急カーブした!", gamelog);
      gamelog.newline(); //New line.
      break;
   case 2:
      addstr("空き地を渡り向こうの通りへと駆け抜けた!", gamelog);
      gamelog.newline(); //New line.
      break;
   case 3:
      if(yourworst>15)
         addstr("向かってくる車を蛇行して大胆にかわした!", gamelog);
      else
         addstr("追跡する車に挑発的なジェルチャーをした!", gamelog);
      gamelog.newline(); //new line.
      break;
   }

   getkey();

   int cnt;
   for(int i=0;i<len(theirrolls);i++)
   {
      cnt=pickrandom(yourrolls);
      if(theirrolls[i]<cnt)
      {
         clearmessagearea();
         set_color(COLOR_CYAN,COLOR_BLACK,1);
         move(16,1);
         for(e=0;e<ENCMAX;e++)
         {
            if(encounter[e].id==theirrolls_drv[i])
            {
               addstr(encounter[e].name, gamelog);
               break;
            }
         }
         switch(LCSrandom(cnt/5))
         {
         default:
            addstr("は追いつけなかった!", gamelog);
            gamelog.newline(); //New line.
            break;
         case 1:
            addstr("はスリップした!", gamelog);
            gamelog.newline(); //New line.
            break;
         case 2:
            addstr("は危険を感じ追うのをやめた。", gamelog);
            gamelog.newline(); //New line.
            break;
         case 3:
            addstr("は衝突寸前で急ブレーキをかけた!", gamelog);
            gamelog.newline(); //New line.
            break;
         }

         for(e=0;e<ENCMAX;e++)
         {
            if(encounter[e].carid==theirrolls_id[i])
            {
               for(int e2=e;e2<ENCMAX-1;e2++) encounter[e2]=encounter[e2+1];
               encounter[ENCMAX-1].exists=0;
               encounter[ENCMAX-1].carid=-1;
               e--;
            }
         }
         for(int v=0;v<len(chaseseq.enemycar);v++)
         {
            if(chaseseq.enemycar[v]->id()==theirrolls_id[i])
            {
               delete_and_remove(chaseseq.enemycar,v);
               break;
            }
         }

         printchaseencounter();

         getkey();
      }
      else
      {
         clearmessagearea();
         set_color(COLOR_YELLOW,COLOR_BLACK,1);
         move(16,1);
         for(int e=0;e<ENCMAX;e++)
         {
            if(encounter[e].id==theirrolls_drv[i])
            {
               addstr(encounter[e].name, gamelog);
               break;
            }
         }
         addstr("はまだ追っている!", gamelog);
         gamelog.newline(); //Blarg. Newline.

         getkey();
      }
   }
}



void evasiverun()
{
   vector<int> yourspeed;
   yourspeed.resize(6);
   int yourworst=10000,yourbest=0,wheelchair=0,notwheelchair=0,theirbest=0,theirworst=10000;
   for(int p=0;p<6;p++)
   {
      if(activesquad->squad[p]==NULL) continue;
      if(activesquad->squad[p]->alive)
      {
         if(activesquad->squad[p]->flag & CREATUREFLAG_WHEELCHAIR)
         {
            yourspeed[p]=0;
            wheelchair++;
         }
         else
         {
            yourspeed[p]=activesquad->squad[p]->attribute_roll(ATTRIBUTE_AGILITY)+
                         activesquad->squad[p]->attribute_roll(ATTRIBUTE_HEALTH);

            //healthmodroll(yourspeed[p],*activesquad->squad[p]);

            notwheelchair++;
         }
         if(yourworst>yourspeed[p]) yourworst=yourspeed[p];
         if(yourbest<yourspeed[p]) yourbest=yourspeed[p];
      }
   }

   if(yourworst>14)
   {
      yourworst+=LCSrandom(5);

      clearmessagearea();
      set_color(COLOR_WHITE,COLOR_BLACK,1);
      move(16,1);

      switch(LCSrandom(yourworst/5))
      {
      default:
         addstr("いきなり路地に駆け込んだ!", gamelog);
         gamelog.newline(); //New line.
         break;
      case 1:
         addstr("全速力で逃げた!", gamelog);
         gamelog.newline(); //New line.
         break;
      case 2:
         addstr("世界記録の速さでフェンスをよじ登った!", gamelog);
         gamelog.newline(); //New line.
         break;
      case 3:
         addstr("小さなビルを駆け上がり、屋根伝いに逃げた!", gamelog);
         gamelog.newline(); //New line.
      }

      getkey();
   }

   for(int e=0;e<ENCMAX;e++)
   {
      if(!encounter[e].exists) continue;

      int chaser=encounter[e].attribute_roll(ATTRIBUTE_AGILITY)+
                 encounter[e].attribute_roll(ATTRIBUTE_HEALTH);

      //healthmodroll(chaser,encounter[e]);

      if(theirbest<chaser) theirbest=chaser;
      if(theirworst>chaser) theirworst=chaser;

      if(encounter[e].type == CREATURE_TANK && LCSrandom(10))
      {
         clearmessagearea();
         set_color(COLOR_YELLOW,COLOR_BLACK,1);
         move(16,1);
         addstr(encounter[e].name, gamelog);
         switch(LCSrandom(4))
         {
         case 0:
            addstr("は何もないかのようにレンガの壁をなぎ倒した!", gamelog);
            gamelog.newline(); //New line.
            break;
         case 1:
            addstr("は両側の壁を壊しながら路地に突っ込んできた!", gamelog);
            gamelog.newline(); //Blarg.
            break;
         case 2:
            addstr("は自動車を破壊しながら道路をまっすぐ進んだ!", gamelog);
            gamelog.newline(); //Newline.
            break;
         case 3:
            addstr("は近くにあるあらゆる物を破壊しながら進んだ!", gamelog);
            gamelog.newline(); //I wish these were all contained in addstr.
            break;
         }

         getkey();
      }
      else if(chaser<yourworst)
      {
         clearmessagearea();
         set_color(COLOR_CYAN,COLOR_BLACK,1);
         move(16,1);
         addstr(encounter[e].name, gamelog);
         if(encounter[e].type == CREATURE_TANK)
         {
            addstr("は深みにはまって動けない!", gamelog);
            gamelog.newline(); //New line.
         }
         else
         {
            addstr("は追いつけなかった!", gamelog);
            gamelog.newline(); //Another new line.
         }

         delenc(e--,0);

         printchaseencounter();

         getkey();
      }
      else
      {
         clearmessagearea();
         set_color(COLOR_YELLOW,COLOR_BLACK,1);
         move(16,1);
         addstr(encounter[e].name, gamelog);
         addstr("はまだ追っている!", gamelog);
         gamelog.newline(); //New line.

         getkey();
      }
   }

   //This last loop can be used to have fast people in
   //your squad escape one by one just as the enemy
   //falls behind one by one
   int othersleft=0;
   for(int p=5;p>=0;p--)
   {
      if(!encounter[0].exists) break;
      if(activesquad->squad[p]==NULL) continue;
      if(activesquad->squad[p]->alive)
      {
         if(yourspeed[p]>theirbest)
         {
            if(p==0 && othersleft==0) break;
            clearmessagearea();
            set_color(COLOR_CYAN,COLOR_BLACK,1);
            move(16,1);
            addstr(activesquad->squad[p]->name, gamelog);
            addstr("は逃げ切った!", gamelog);
            gamelog.newline(); //New line.

            getkey();

            //Unload hauled hostage or body when they get back to the safehouse
            if(activesquad->squad[p]->prisoner!=NULL)
            {
               //If this is an LCS member or corpse being hauled (marked as in the squad)
               if(activesquad->squad[p]->prisoner->squadid!=-1)
               {
                  //Take them out of the squad
                  removesquadinfo(*activesquad->squad[p]->prisoner);
                  //Set base and current location to squad's safehouse
                  activesquad->squad[p]->prisoner->location=activesquad->squad[p]->base;
                  activesquad->squad[p]->prisoner->base=activesquad->squad[p]->base;
               }
               else //A kidnapped conservative
               {
                  //Convert them into a prisoner
                  kidnaptransfer(*activesquad->squad[p]->prisoner);
                  delete activesquad->squad[p]->prisoner;
               }
               activesquad->squad[p]->prisoner=NULL;
            }

            removesquadinfo(*activesquad->squad[p]);

            printparty();
         }
         else if(yourspeed[p]<theirbest-10)
         {
            clearmessagearea();
            set_color(COLOR_CYAN,COLOR_BLACK,1);
            move(16,1);
            addstr(activesquad->squad[p]->name, gamelog);
            switch(encounter[0].type)
            {
            case CREATURE_COP:
               addstr("は取り押さえられた。そして", gamelog);
               if(law[LAW_POLICEBEHAVIOR]>=ALIGN_LIBERAL)
               {
                  addstr("地面に押し付けられ、障害を負った!", gamelog);
                  gamelog.newline(); //...Newline.
               }
               else
               {
                  if(activesquad->squad[p]->blood<=10)
                  {
                     addstr("地面に叩きつけられ死んだ!", gamelog);
                     gamelog.newline(); //Not another newline!
                  }
                  else
                  {
                     addstr("地面に叩きつけられ、何度も殴られた!", gamelog);
                     gamelog.newline(); //Yet another newline...
                  }
                  activesquad->squad[p]->blood-=10;
               }
               break;
            case CREATURE_DEATHSQUAD:
               addstr("は取り押さえられた。そして", gamelog);
               addstr("地面に叩きつけられ、頭を撃ち抜かれた!", gamelog);
               gamelog.newline(); //New line.
               activesquad->squad[p]->blood=0;
               break;
            case CREATURE_TANK:
               addstr("は戦車にひき殺された!", gamelog);
               gamelog.newline(); //New line.
               activesquad->squad[p]->blood=0;
               break;
            default:
               addstr("は取り押さえられた。そして", gamelog);
               if(activesquad->squad[p]->blood<=60)
               {
                  addstr("地面に叩きつけられ、死ぬまで殴打された!", gamelog);
                  gamelog.newline(); //New line.
               }
               else
               {
                  addstr("地面に叩きつけられ、激しく何度も殴られた!", gamelog);
                  gamelog.newline(); //New line.
               }
               activesquad->squad[p]->blood-=60;
               break;
            }
            if(activesquad->squad[p]->blood<=0)
               activesquad->squad[p]->die();

            capturecreature(*activesquad->squad[p]);
            for(int i=p+1, j=p;i<6;i++, j++)
               activesquad->squad[j]=activesquad->squad[i];
            activesquad->squad[5]=NULL;
            // Death squads don't mess around, and don't fall behind when executing your people
            // Tanks don't stop either.
            if(encounter[0].type!=CREATURE_DEATHSQUAD&&
               encounter[0].type!=CREATURE_TANK)delenc(0,0);

            printparty();
            printchaseencounter();

            getkey();
         }
         else othersleft++;
      }
   }
}

int driveskill(Creature &cr,Vehicle &v)
{
   int driveskill=cr.skill_roll(PSEUDOSKILL_ESCAPEDRIVE);
   healthmodroll(driveskill,cr);
   if(driveskill<0) driveskill=0;
   driveskill*=static_cast<int>(cr.blood/50.0);
   return driveskill;
}

Vehicle* getChaseVehicle(const Creature &c)
{
   Vehicle* found = NULL;
   int v2 = 0;
   //addstr("Searching for chase vehicle for ", gamelog);
   //addstr(c.name, gamelog);
   if (mode==GAMEMODE_CHASECAR && c.carid != -1)
   {
      for(v2=0;v2<len(chaseseq.friendcar);v2++) 
         if(chaseseq.friendcar[v2]->id()==c.carid)
         {
            //addstr_fl(gamelog,"  Found friendcar with ID %d at index %d",c.carid, v2);
            found = chaseseq.friendcar[v2]; 
            break;
         }

      for(v2=0;v2<len(chaseseq.enemycar);v2++) 
         if(chaseseq.enemycar[v2]->id()==c.carid) 
         {
            //addstr_fl(gamelog,"  Found enemycar with ID %d at index %d",c.carid, v2);
            found = chaseseq.enemycar[v2];
            break;
         }
   }
   //gamelog.newline();
   return found;
}
Creature* getChaseDriver(const Creature &c)
{
   Creature* found = NULL;
   
   if (mode==GAMEMODE_CHASECAR && c.carid != -1)
   {
      //addstr_fl(gamelog,"Searching for %s's driver.  ", c.name);
      int v = c.carid;
      // Check to see if the car we are in is being driven by an LCS member
      for (int p=0;p<6;p++)
      {
         if(activesquad->squad[p]==NULL) continue;
         if (activesquad->squad[p]->carid == v
             && activesquad->squad[p]->is_driver)
         {
            //addstr_fl(gamelog,"  Found LCS driver %s in carID %d",activesquad->squad[p]->name, v);
            found = activesquad->squad[p];
         }
      }
      // Check to see if the car we are in is being driven by an encounter creature.
      for(int p=0;p<ENCMAX;p++)
      {
         if (!encounter[p].exists) continue;
         if (encounter[p].carid == v
             && encounter[p].is_driver)
         {
            //addstr_fl(gamelog,"  Found encounter driver %s in carID %d",encounter[p].name, v);
            found = &encounter[p];
         }
      }
   }
   //gamelog.newline();
   return found;
}

bool drivingupdate(short &obstacle)
{
   //CHECK TO SEE WHICH CARS ARE BEING DRIVEN
   vector<int> passenger;
   int driver,v,p;
   for(v=len(chaseseq.friendcar)-1;v>=0;v--)
   {
      passenger.clear();
      driver=-1;
      for(p=0;p<6;p++)
      {
         if(activesquad->squad[p]==NULL) continue;
         if(activesquad->squad[p]->carid==chaseseq.friendcar[v]->id())
         {
            if(activesquad->squad[p]->is_driver)
            {
               if(activesquad->squad[p]->canwalk()) driver=p;
               else activesquad->squad[p]->is_driver=0;
            }
            passenger.push_back(p);
         }
      }

      if(len(passenger)&&driver==-1)
      {
         //MAKE BEST DRIVING PASSENGER INTO A DRIVER
         vector<int> goodp;
         int max=0;
         for(p=0;p<len(passenger);p++)
            if(driveskill(*activesquad->squad[passenger[p]],*chaseseq.friendcar[v])>max&&activesquad->squad[passenger[p]]->canwalk())
               max=driveskill(*activesquad->squad[passenger[p]],*chaseseq.friendcar[v]);
         for(p=0;p<len(passenger);p++)
            if(driveskill(*activesquad->squad[passenger[p]],*chaseseq.friendcar[v])==max&&activesquad->squad[passenger[p]]->canwalk())
               goodp.push_back(passenger[p]);

         if(len(goodp))
         {
            int p=pickrandom(goodp);
            activesquad->squad[p]->is_driver=1;
            driver=p;

            clearmessagearea();
            set_color(COLOR_YELLOW,COLOR_BLACK,1);
            move(16,1);
            addstr(activesquad->squad[p]->name, gamelog);
            addstr("が運転を引き継いだ。", gamelog);
            gamelog.newline(); //New line.
            printparty();

            getkey();
         }
      }
      if(driver==-1)
      {
         crashfriendlycar(v);
         sitestory->crime.push_back(CRIME_CARCHASE);
         return 1;
      }
   }

   for(v=len(chaseseq.enemycar)-1;v>=0;v--)
   {
      passenger.clear();
      driver=-1;
      for(p=0;p<ENCMAX;p++)
      {
         if(!encounter[p].exists) continue;
         if(encounter[p].carid==chaseseq.enemycar[v]->id())
         {
            if(encounter[p].is_driver)
            {
               if(encounter[p].canwalk()) driver=p;
               else encounter[p].is_driver=0;
            }
            passenger.push_back(p);
         }
      }
      // Enemies don't take over the wheel when driver incapacitated
      if(driver==-1)
      {
         crashenemycar(v);
         sitestory->crime.push_back(CRIME_CARCHASE);
      }
   }

   //SET UP NEXT OBSTACLE
   if(!LCSrandom(3)) obstacle=LCSrandom(CARCHASE_OBSTACLENUM);
   else obstacle=-1;

   return 0;
}



void makechasers(long sitetype,long sitecrime)
{
   for(int e=0;e<ENCMAX;e++) encounter[e].exists=0;

   if(!sitecrime) return;

   short encslot=0;
   int n;

   string cartype; //Temporary (transitionally) solution. -XML
   long pnum;

   chaseseq.canpullover=0;
   // 50% of CCS harassing your teams once they reach the
   // "attacks" stage (but not for activities, which are
   // law enforcement response specific)
   if(endgamestate<ENDGAME_CCS_DEFEATED&&
      endgamestate>=ENDGAME_CCS_ATTACKS&&
      LCSrandom(2)&&sitetype!=-1)
   {
      cartype="SUV"; //A CCS property, not a vehicle property. Temporary solution -XML
      pnum=LCSrandom(sitecrime/5 + 1)+1;
      if(pnum>12) pnum=12;
      for(n=0;n<pnum;n++)
         makecreature(encounter[encslot++],CREATURE_CCS_VIGILANTE);
   }
   else
   {
      switch(sitetype)
      {
         case SITE_GOVERNMENT_ARMYBASE:
            cartype="HMMWV"; //Site property? Temporary solution. -XML
            pnum=LCSrandom(sitecrime/5 + 1)+3;
            if(pnum>6)pnum=6;
            for(n=0;n<pnum;n++)
               makecreature(encounter[encslot++],CREATURE_SOLDIER);
            break;
         case SITE_GOVERNMENT_WHITE_HOUSE:
            cartype="AGENTCAR"; //Site property? Temporary solution. -XML
            pnum=LCSrandom(sitecrime/5 + 1)+1;
            if(pnum>6)pnum=6;
            for(n=0;n<pnum;n++)
               makecreature(encounter[encslot++],CREATURE_SECRET_SERVICE);
            break;
         case SITE_GOVERNMENT_INTELLIGENCEHQ:
            cartype="AGENTCAR"; //Site property? Temporary solution. -XML
            pnum=LCSrandom(sitecrime/5 + 1)+1;
            if(pnum>6)pnum=6;
            for(n=0;n<pnum;n++)
               makecreature(encounter[encslot++],CREATURE_AGENT);
            break;
         case SITE_CORPORATE_HEADQUARTERS:
         case SITE_CORPORATE_HOUSE:
            if(LCSrandom(2))cartype="SUV"; //Site property? Temporary solution. -XML
            else cartype="JEEP"; //Site property? Temporary solution. -XML
            pnum=LCSrandom(sitecrime/5 + 1)+1;
            if(pnum>6)pnum=6;
            for(n=0;n<pnum;n++)
               makecreature(encounter[encslot++],CREATURE_MERC);
            break;
         case SITE_MEDIA_AMRADIO:
         case SITE_MEDIA_CABLENEWS:
            cartype="PICKUP"; //Site property? Temporary solution. -XML
            pnum=LCSrandom(sitecrime/3 + 1)+1;
            if(pnum>18)pnum=18;
            for(n=0;n<pnum;n++)
               makecreature(encounter[encslot++],CREATURE_HICK);
            break;
         case SITE_BUSINESS_CRACKHOUSE:
            cartype="STATIONWAGON"; //Site property? Temporary solution. -XML
            pnum=LCSrandom(sitecrime/3 + 1)+1;
            if(pnum>18)pnum=18;
            for(n=0;n<pnum;n++)
               makecreature(encounter[encslot++],CREATURE_GANGMEMBER);
            break;
         default:
            chaseseq.canpullover=1;
            cartype="POLICECAR"; //Police property? Temporary solution. -XML
            pnum=LCSrandom(sitecrime/5 + 1)+1;
            if(pnum>6)pnum=6;
            for(n=0;n<pnum;n++)
            {
               if(law[LAW_DEATHPENALTY]==-2&&
                  law[LAW_POLICEBEHAVIOR]==-2){makecreature(encounter[encslot++],CREATURE_DEATHSQUAD);chaseseq.canpullover=0;}
               else if(law[LAW_POLICEBEHAVIOR]<=-1)makecreature(encounter[encslot++],CREATURE_GANGUNIT);
               else makecreature(encounter[encslot++],CREATURE_COP);
            }
            break;
      }
   }

   for(n=0;n<pnum;n++) conservatise(encounter[n]);

   //ASSIGN CARS TO CREATURES
   int carnum;
   if(pnum<=2) carnum=1;
   else if(pnum<=3) carnum=LCSrandom(2)+1;
   else if(pnum<=5) carnum=LCSrandom(2)+2;
   else if(pnum<=7) carnum=LCSrandom(2)+3;
   else carnum=4;

   for(int c=0;c<carnum;c++)
   {
      Vehicle *v=new Vehicle(*vehicletype[getvehicletype(cartype)]); //If car type is unknown, due to change in xml file, the game will crash here. -XML
      chaseseq.enemycar.push_back(v);

      for(n=0;n<pnum;n++)
         if(encounter[n].carid==-1)
         {
            encounter[n].carid=v->id();
            encounter[n].is_driver=1;
            break;
         }
   }

   long load[4]={0,0,0,0};

   for(n=0;n<pnum;n++)
      if(encounter[n].carid==-1)
      {
         int v;
         do
         {
            v=LCSrandom(len(chaseseq.enemycar));
            encounter[n].carid=chaseseq.enemycar[v]->id();
            encounter[n].is_driver=0;
         } while(load[v]>=4);
         load[v]++;
      }
}



bool obstacledrive(short obstacle,char choice)
{
   switch(obstacle)
   {
      case CARCHASE_OBSTACLE_CROSSTRAFFIC:
         if(choice==0)
         {
            if(dodgedrive()) return 1;
         }
         else if(choice==1)
         {
            clearmessagearea();
            set_color(COLOR_YELLOW,COLOR_BLACK,1);
            move(16,1);
            addstr("減速してハンドルを切った。", gamelog);
            gamelog.newline(); //New line.

            getkey();

            if(!LCSrandom(3))
            {
               set_color(COLOR_YELLOW,COLOR_BLACK,1);
               move(17,1);
               addstr("追っ手が近づいてきた!", gamelog);
               gamelog.newline(); //New line.

               getkey();

               enemyattack();
               youattack();
            }
         }
         break;
      case CARCHASE_OBSTACLE_TRUCKPULLSOUT:
         if(choice==0)
         {
            if(dodgedrive()) return 1;
         }
         else if(choice==1)
         {
            clearmessagearea();
            set_color(COLOR_YELLOW,COLOR_BLACK,1);
            move(16,1);
            addstr("減速して慎重にトラックをかわした。", gamelog);
            gamelog.newline(); //New line.

            getkey();

            if(!LCSrandom(3))
            {
               set_color(COLOR_YELLOW,COLOR_BLACK,1);
               move(17,1);
               addstr("追っ手が近づいてきた!", gamelog);
               gamelog.newline(); //New line.

               getkey();

               enemyattack();
               youattack();
            }
         }
         break;
      case CARCHASE_OBSTACLE_FRUITSTAND:
         if(choice==0)
         {
            if(dodgedrive()) return 1;
         }
         else if(choice==1)
         {
            clearmessagearea();
            set_color(COLOR_YELLOW,COLOR_BLACK,1);
            move(16,1);
            addstr("フロントガラスに果物をぶちまけた!", gamelog);
            gamelog.newline(); //New line.

            getkey();

            if(!LCSrandom(5))
            {
               set_color(COLOR_RED,COLOR_BLACK,1);
               move(17,1);
               addstr("店員をはね飛ばした!", gamelog);
               gamelog.newline(); //All this logging and lining...

               getkey();

               criminalizeparty(LAWFLAG_MURDER);
            }
         }
         break;
      case CARCHASE_OBSTACLE_CHILD:
         if(choice==0)
         {
            if(dodgedrive()) return 1;
         }
         else if(choice==1)
         {
            clearmessagearea();
            set_color(COLOR_YELLOW,COLOR_BLACK,1);
            move(16,1);
            addstr("減速して慎重に子供をかわした。", gamelog);
            gamelog.newline(); //New line.

            getkey();

            if(!LCSrandom(3))
            {
               set_color(COLOR_RED,COLOR_BLACK,1);
               move(17,1);
               addstr("保守は雨あられのように撃ち始めた!", gamelog);
               gamelog.newline(); //New line.

               getkey();

               enemyattack();
               youattack();
            }
            else
            {
               set_color(COLOR_GREEN,COLOR_BLACK,1);
               move(17,1);
               addstr("どちらの側も子供に危害を加えないようにしている…", gamelog);
               gamelog.newline(); //New line.

               getkey();
            }
         }
         break;
   }
   return 0;
}

bool dodgedrive()
{
   int v;
   clearmessagearea();
   set_color(COLOR_YELLOW,COLOR_BLACK,1);
   move(16,1);
   addstr("蛇行して避けた!", gamelog);
   gamelog.newline(); //New line.

   getkey();

   int driver;
   for(v=len(chaseseq.friendcar)-1;v>=0;v--)
   {
      driver=-1;
      for(int p=0;p<6;p++)
      {
         if(!activesquad->squad[p]) continue;
         if(activesquad->squad[p]->carid==chaseseq.friendcar[v]->id())
         {
            if(activesquad->squad[p]->is_driver)
            {
               driver=p;
               break;
            }
         }
      }

      if(driver!=-1)
      {
         if(!activesquad->squad[driver]->skill_check(PSEUDOSKILL_ESCAPEDRIVE, DIFFICULTY_EASY))
         {
            crashfriendlycar(v);
            sitestory->crime.push_back(CRIME_CARCHASE);
            return 1;
         }
      }
   }

   for(v=len(chaseseq.enemycar)-1;v>=0;v--)
   {
      driver=-1;
      for(int p=0;p<ENCMAX;p++)
      {
         if(!encounter[p].exists) continue;
         if(encounter[p].carid==chaseseq.enemycar[v]->id())
         {
            if(encounter[p].is_driver)
            {
               driver=p;
               break;
            }
         }
      }

      if(driver!=-1)
         if(!encounter[driver].skill_check(PSEUDOSKILL_ESCAPEDRIVE, DIFFICULTY_EASY))
         {
            crashenemycar(v);
            sitestory->crime.push_back(CRIME_CARCHASE);
         }
   }
   return 0;
}

void crashfriendlycar(int v)
{
	static const char *car_crash_modes[] =
	{
		"はビルに衝突した!",
		"は横滑りしてクラッシュした!",
		"は停められていた車と衝突して横転した!"
	};
	static const char *car_crash_fatalities[] =
	{
   	"車の中で激しく打ち付けられた。",
		"の遺体がフロントガラスに叩きつけられた。",
		"は車から投げ出され即死した。",
	};

   //CRASH CAR
   clearmessagearea();
   set_color(COLOR_MAGENTA,COLOR_BLACK,1);
   move(16,1);
   addstr("あなたの", gamelog);
   addstr(chaseseq.friendcar[v]->fullname(), gamelog);
   addstr(pickrandom(car_crash_modes), gamelog);
   gamelog.newline(); //New line it.
   printparty();

   getkey();

   int victimsum=0;

   for(int p=0;p<6;p++)
   {
      if(!activesquad->squad[p]) continue;
      if(activesquad->squad[p]->carid==chaseseq.friendcar[v]->id())
      {
         // Inflict injuries on Liberals
         for(int w=0;w<BODYPARTNUM;w++)
            // If limb is intact
            if(!(activesquad->squad[p]->wound[w] & (WOUND_CLEANOFF | WOUND_NASTYOFF)))
            {
               // Inflict injuries
               if(LCSrandom(2))
               {
                  activesquad->squad[p]->wound[w] |= (WOUND_TORN|WOUND_BLEEDING);
                  activesquad->squad[p]->blood -= 1 + LCSrandom(25);
               }
               if(!LCSrandom(3))
               {
                  activesquad->squad[p]->wound[w] |= (WOUND_CUT|WOUND_BLEEDING);
                  activesquad->squad[p]->blood -= 1 + LCSrandom(25);
               }
               if(LCSrandom(2) || activesquad->squad[p]->wound[w] == 0)
               {
                  activesquad->squad[p]->wound[w] |= WOUND_BRUISED;
                  activesquad->squad[p]->blood -= 1 + LCSrandom(10);
               }
            }

         // Kill off hostages
         if(activesquad->squad[p]->prisoner)
         {
            // Instant death
            if(activesquad->squad[p]->prisoner->alive)
            {
               clearmessagearea();
               set_color(COLOR_RED,COLOR_BLACK,1);
               move(16,1);
               addstr(activesquad->squad[p]->prisoner->name, gamelog);
               addstr(pickrandom(car_crash_fatalities), gamelog);
               gamelog.newline(); //New line.
               printparty();

               getkey();
            }
            activesquad->squad[p]->prisoner->die();
            victimsum++;

            // Record death if living Liberal is hauled
            if(activesquad->squad[p]->prisoner->squadid!=-1)
            {
               if(activesquad->squad[p]->prisoner->alive&&
                  activesquad->squad[p]->prisoner->align==1)stat_dead++;

               activesquad->squad[p]->prisoner->die();
               activesquad->squad[p]->prisoner->location=-1;
            }
            // Otherwise just kill them off and be done with it
            else delete activesquad->squad[p]->prisoner;
            activesquad->squad[p]->prisoner=NULL;
         }

         // Handle squad member death
         if(activesquad->squad[p]->blood <= 0)
         {
            // Inform the player
            clearmessagearea();
            set_color(COLOR_RED,COLOR_BLACK,1);
            move(16,1);
            addstr(activesquad->squad[p]->name, gamelog);
            switch(LCSrandom(3))
            {
               case 0:addstr("は運転席で気を失い、そして死んだ。", gamelog);break;
               case 1:addstr("は衝突で押しつぶされ死んだ。", gamelog);break;
               case 2:addstr("は車から抜け出そうともがいたが押しつぶされ死んだ。", gamelog);break;
            }
            gamelog.newline(); //New line.
            printparty();

            getkey();

            // Mark as dead
            activesquad->squad[p]->die();
            victimsum++;

            // Account for deaths for high score
            if(activesquad->squad[p]->align == ALIGN_LIBERAL)stat_dead++;

            // Remove dead Liberal from squad
            activesquad->squad[p]=NULL;
         }
         else
         {
            // Inform the player of character survival
            clearmessagearea();
            set_color(COLOR_YELLOW,COLOR_BLACK,1);
            move(16,1);
            addstr(activesquad->squad[p]->name, gamelog);
            switch(LCSrandom(3))
            {
               case 0:
                  addstr("は", gamelog);
                  if(activesquad->squad[p]->is_armed())
                     addstr(activesquad->squad[p]->get_weapon().get_shortname(), gamelog);
                  else addstr("車のフレーム", gamelog);
                  addstr("を掴み、どうにか", gamelog);
                  if(activesquad->squad[p]->flag & CREATUREFLAG_WHEELCHAIR)
                     addstr("車椅子", gamelog);
                  else addstr("足", gamelog);
                  addstr("を抜き出した。", gamelog);
                  break;
               case 1:
                  addstr("は痛みで苦しんでいるが生きている。今はまだ。", gamelog);
                  break;
               case 2:addstr("は痛みで震えながら車から這い出した。", gamelog);
                  activesquad->squad[p]->drop_weapon(NULL);
                  break;
            }
            gamelog.newline(); //New line.
            printparty();

            getkey();
         }
      }
   }

   //CONSOLIDATE SQUAD
   for(int i=0;i<5;i++)
   {
      bool flipstart=0;
      for(int pt=0;pt<6;pt++)
      {
         if(activesquad->squad[pt]==NULL&&!flipstart)flipstart=1;
         if(flipstart&&pt<5)activesquad->squad[pt]=activesquad->squad[pt+1];
      }
      if(flipstart)activesquad->squad[5]=NULL;
   }

   //GET RID OF CARS
   delete_and_clear(chaseseq.friendcar,vehicle);
   for(int p=0;p<6;p++)
   {
      if(!activesquad->squad[p]) continue;
      activesquad->squad[p]->carid=-1;
   }
}

void crashenemycar(int v)
{
   int victimsum=0;

   for(int p=ENCMAX-1;p>=0;p--)
   {
      if(!encounter[p].exists) continue;
      if(encounter[p].carid==chaseseq.enemycar[v]->id())
      {
         victimsum++;
         delenc(p,0);
      }
   }

   //CRASH CAR
   clearmessagearea();
   set_color(COLOR_CYAN,COLOR_BLACK,1);
   move(16,1);
   addstr(chaseseq.enemycar[v]->fullname(), gamelog);
   switch(LCSrandom(3))
   {
      case 0:addstr("はビルに衝突した。", gamelog);break;
      case 1:
         addstr("は横滑りしてクラッシュした。", gamelog);
         move(17,1);
         if(victimsum>1)addstr("乗車していた全員が車道に投げ出された。", gamelog);
         else if(victimsum==1)addstr("運転手は車だった塊の中に閉じ込められた。", gamelog);
         break;
      case 2:addstr("停められていた車と衝突して横転した。", gamelog);break;
   }
   gamelog.newline(); //New line.

   delete_and_remove(chaseseq.enemycar,v);

   printchaseencounter();

   getkey();
}

void chase_giveup()
{
   int p;
   int ps=find_police_station(chaseseq.location);

   delete_and_clear(chaseseq.friendcar,vehicle);
   int hostagefreed=0;
   for(p=0;p<6;p++)
   {
      if(!activesquad->squad[p]) continue;
      activesquad->squad[p]->squadid=-1;
      activesquad->squad[p]->carid=-1;
      activesquad->squad[p]->location=ps;
      activesquad->squad[p]->drop_weapons_and_clips(NULL);
      activesquad->squad[p]->activity.type=ACTIVITY_NONE;
      if(activesquad->squad[p]->prisoner)
      {
         if(activesquad->squad[p]->prisoner->squadid==-1) hostagefreed++;
         freehostage(*activesquad->squad[p],2);
      }
      activesquad->squad[p]=NULL;
   }
   for(p=0;p<len(pool);p++)
      for(int w=0;w<BODYPARTNUM;w++)
         pool[p]->wound[w]&=~WOUND_BLEEDING;

   clearmessagearea();
   clearcommandarea();
   set_color(COLOR_MAGENTA,COLOR_BLACK,1);
   move(16,1);
   if(mode!=GAMEMODE_CHASECAR)addstr("あなたは逃げるのをやめ、逮捕された。", gamelog);
   else addstr("あなたは止められ逮捕された。", gamelog);
   gamelog.newline(); //New line.
   if(hostagefreed)
   {
      move(17,1);
      addstr("人質の", gamelog);
      if(hostagefreed>1)
         addstr("達は解放された。", gamelog);
      else addstr("は解放された。", gamelog);
      gamelog.newline(); //New line.
   }

   getkey();
}

/* the next two functions force a chase sequence with a specific liberal */
bool footchase(Creature &cr)
{
   long oldsqid=cr.squadid;
   Creature *crp=&cr;
   squadst *sq=new squadst;
   sq->squad[0]=&cr;
   sq->squad[0]->squadid=cursquadid;cursquadid++;
   cr.squadid=sq->squad[0]->squadid;
   cr.carid=-1;

   squadst *oact=activesquad;
   short ops=party_status;
   activesquad=sq;
   party_status=0;
   bool ret=footchase();

   party_status=ops;

   delete sq;

   if(ret) cr.squadid=oldsqid;
   else if(oldsqid!=-1)
   {
      activesquad=squad[getsquad(oldsqid)];
      for(int i=0;i<6;i++)
      {
         if(activesquad->squad[i]) if(activesquad->squad[i]==crp)
         {
            for(int j=i+1;j<6;j++,i++) activesquad->squad[i]=activesquad->squad[j];
            activesquad->squad[5]=NULL;
            break;
         }
      }
   }
   activesquad=oact;
   return ret;
}

bool chasesequence(Creature &cr,Vehicle &v)
{
   long oldsqid=cr.squadid;
   squadst *sq=new squadst;
   sq->squad[0]=&cr;
   sq->squad[0]->squadid=cursquadid;
   sq->id=cursquadid;cursquadid++;
   cr.carid=v.id();
   cr.is_driver=1;

   squadst *oact=activesquad;
   short ops=party_status;
   activesquad=sq;
   party_status=0;
   bool ret=chasesequence();
   party_status=ops;

   delete sq;

   if(ret)
   {
      cr.squadid=oldsqid;
      cr.carid=-1;
   }
   else if(oldsqid!=-1)
   {
      activesquad=squad[getsquad(oldsqid)];
      for(int i=0;i<6;i++)
         if(activesquad->squad[i]) if(activesquad->squad[i]==&cr)
         {
            for(int j=i+1;j<6;j++,i++) activesquad->squad[i]=activesquad->squad[j];
            activesquad->squad[5]=NULL;
            break;
         }
   }
   activesquad=oact;
   gamelog.nextMessage(); //Next message.
   return ret;
}
