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

/* TODO
make it less likely to be raided based on:
        - the number of sleepers.
        - how effective said sleepers are.
        - what action each sleeper is doing (promoting liberalism decreases chance while promoting conservatism increases chance)
        - what the sleeper does for a living (police officers are more influential than janitors, for instance)

make it more likely to be raided:
        - when a liberal hacks or steals credit cards.
        - dead bodies in the base. [DONE]
*/


/* siege - gives up on sieges with empty locations */
/* Work in progress. It works, but needs to be called in more places. */
/* Currently, it only works when you confront a siege and then fail. */
void resolvesafehouses()
{
   for(int l=0;l<len(location);l++)
   {
      if(location[l]->renting>=0&&location[l]->siege.siege)
      {
         cleangonesquads();
         selectedsiege = l; // hack for calling giveup()
         giveup();
      }
   }
}


/* siege - updates upcoming sieges */
void siegecheck(char canseethings)
{
   if(disbanding)return;

// Upkeep - even base-less should be considered.
// XXX - candidate to create nice function?
  // Cleanse record on things that aren't illegal right now
  for(int p=0;p<len(pool);p++)
  {
    if(law[LAW_FLAGBURNING]>0)pool[p]->crimes_suspected[LAWFLAG_BURNFLAG]=0;
    if(law[LAW_DRUGS]>0)pool[p]->crimes_suspected[LAWFLAG_BROWNIES]=0;
    if(law[LAW_IMMIGRATION]==2)pool[p]->flag &= ~CREATUREFLAG_ILLEGALALIEN;
    if(law[LAW_FREESPEECH]>-2)pool[p]->crimes_suspected[LAWFLAG_SPEECH]=0;
  }
  if(law[LAW_FREESPEECH]>-2)offended_firemen=0;

   //FIRST, THE COPS
   int numpres;
   for(int l=0;l<len(location);l++)
   {
      if(location[find_police_station(l)]->closed)
      {
         location[l]->heat = static_cast<int>(location[l]->heat * 0.95);
         continue;
      }
      if(location[l]->siege.siege)continue;
      if(location[l]->renting==RENTING_NOCONTROL)continue;
      numpres=0;

      if(location[l]->siege.timeuntillocated==-2)
      {
         //IF JUST SIEGED, BUY SOME TIME
         location[l]->siege.timeuntillocated=-1;
      }
      else
      {
         //HUNTING
         if(location[l]->siege.timeuntillocated>0)
         {
            if(location[l]->front_business==-1||LCSrandom(2))
            {
               location[l]->siege.timeuntillocated--;
               // Hunt faster if location is extremely hot
               if(location[l]->heat > 100)
               {
                  int hunt_speed;
                  hunt_speed = location[l]->heat / 50;
                  while(hunt_speed&&location[l]->siege.timeuntillocated>1)
                  {
                     location[l]->siege.timeuntillocated--;
                     hunt_speed--;
                  }
               }
            }
         }

         //CHECK FOR CRIMINALS AT THIS BASE
         int crimes=0;
         //int heatprotection=0;
         for(int p=0;p<len(pool);p++)
         {
            // Sleepers and people not at this base don't count
            if(pool[p]->location!=l || pool[p]->flag & CREATUREFLAG_SLEEPER)continue;

            if(!pool[p]->alive) // Corpses attract attention
            {
               crimes += 5;
               continue;
            }
            if(pool[p]->flag & CREATUREFLAG_KIDNAPPED && pool[p]->align!=1)
            {
               crimes += 5*pool[p]->joindays; // Kidnapped persons increase heat
               continue;
            }
            if(pool[p]->align!=1)continue; // Non-liberals don't count other than that
            numpres++;

            // Accumulate heat from liberals who have it, but let them bleed it off in the process
            if(pool[p]->heat > 0)
            {
               crimes += pool[p]->heat/10 + 1;
               pool[p]->heat -= MIN(4,pool[p]->heat);
            }
         }

         // Determine how effective your current safehouse
         // is at keeping the police confused
         location[l]->update_heat_protection();

         // Let the place cool off if not accumulating heat
         if(crimes < location[l]->heat)
         {
            location[l]->heat -= 1;

            if(location[l]->heat < 0)
               location[l]->heat = 0;
         }
         else
         {
            // Update location heat
            if(crimes > location[l]->heat) location[l]->heat += (crimes-location[l]->heat)/10 + 1;

            // Begin planning siege if high heat on location
            if(location[l]->heat > location[l]->heat_protection &&
               LCSrandom(500) < location[l]->heat &&
               !(location[l]->siege.timeuntillocated>=0)) //Do not re-plan siege.
            {
               // Set time until siege is carried out
               location[l]->siege.timeuntillocated += 2 + LCSrandom(6);
            }
         }

         // Sleepers at the police department may give a warning just before police raids
         if(location[l]->siege.timeuntillocated==1)
         {
            int policesleeperwarning=0;
            for(int pl=0;pl<len(pool);pl++)
            {
               if(pool[pl]->flag & CREATUREFLAG_SLEEPER &&
                  pool[pl]->location!=-1 &&
                  location[pool[pl]->location]->type==SITE_GOVERNMENT_POLICESTATION &&
                  location[pool[pl]->location]->city==location[l]->city)
               {
                  //if(pool[pl]->infiltration*100>LCSrandom(50))
                  {
                     policesleeperwarning=1;
                     break;
                  }
               }
            }
            if(policesleeperwarning)
            {
               erase();
               set_color(COLOR_WHITE,COLOR_BLACK,1);
               move(8,1);
               addstr("あなたは警察署の潜伏者から", gamelog);
               addstr(location[l]->getname());
               addstr("への", gamelog);
               move(9,1);
               addstr("襲撃が迫っているとの警告を受けた。", gamelog);
               gamelog.newline();

               if(location[l]->siege.escalationstate>=1)
               {
                  move(11,1);
                  addstr("攻撃には州兵は投入されるだろう。", gamelog);
               }
               if(location[l]->siege.escalationstate>=2)
               {
                  move(12,1);
                  addstr("アジトの出入口には戦車が待ち構えているだろう。", gamelog);
               }
               if(location[l]->siege.escalationstate>=3)
               {
                  move(13,1);
                  addstr("包囲の間、航空機による空爆があり、", gamelog);
                  move(14,1);
                  addstr("最終的には海軍対テロ特殊部隊SEAL Team 6による攻撃が行われるだろう。", gamelog);
               }
               gamelog.nextMessage(); //Write out buffer to prepare for next message.

               move (15,1);
               addstr("ESCを押すと対策を熟慮する…");
               int c;
               do c=getkey(); while(c!='x'&&c!=ESC);
            }
         }

         //COPS RAID THIS LOCATION
         if(!location[l]->siege.timeuntillocated)
         {
            location[l]->siege.timeuntillocated=-2;
            /*location[l]->heat-=250;
            if(location[l]->heat<0)*/location[l]->heat=0;

            if(numpres>0)
            {
               music.play(MUSIC_SIEGE);
               erase();
               set_color(COLOR_WHITE,COLOR_BLACK,1);

               move(8,1);
               addstr("警官隊が", gamelog);
               addstr(location[l]->getname(), gamelog);
               addstr("を包囲している!", gamelog);
               gamelog.newline();
               location[l]->siege.underattack=0;

               getkey();

               //MENTION ESCALATION STATE
               if(location[l]->siege.escalationstate>=1)
               {
                  move(9,1);
                  addstr("通常のSWATに代わり州兵が配備されている。", gamelog);
                  gamelog.nextMessage();

                  getkey();
               }
               if(location[l]->siege.escalationstate>=2)
               {
                  move(10,1);
                  if(location[l]->compound_walls & COMPOUND_TANKTRAPS)
                     addstr("対戦車障害物がM1エイブラムスの行く手を阻んでいる。", gamelog);
                  else addstr("M1エイブラムス戦車がアジトの外で待ち構えている。", gamelog);
                  gamelog.nextMessage();

                  getkey();
               }
               if(location[l]->siege.escalationstate>=3)
               {
                  move(11,1);
                  addstr("ジェット爆撃機が頭上を飛行する音が聞こえる。", gamelog);
                  gamelog.nextMessage();

                  getkey();
               }

               // "You are wanted for blahblah and other crimes."
               statebrokenlaws(l);

               location[l]->siege.siege=1;
               location[l]->siege.siegetype=SIEGE_POLICE;
               location[l]->siege.lights_off=0;
               location[l]->siege.cameras_off=0;
            }
            else
            {
               erase();
               set_color(COLOR_WHITE,COLOR_BLACK,1);

               move(8,1);
               addstr("警官隊は誰もいない", gamelog);
               addstr(location[l]->getname(), gamelog);
               addstr("に侵入した。", gamelog);
               gamelog.newline();

               getkey();

               int y=9;

               for(int p=len(pool)-1;p>=0;p--)
               {
                  if(pool[p]->location!=l) continue;
                  if(!pool[p]->alive)
                  {
                     move(y,1);y++;
                     addstr(pool[p]->name, gamelog);
                     addstr("の遺体が見つかった。", gamelog);
                     gamelog.newline();

                     getkey();

                     delete_and_remove(pool,p);
                     continue;
                  }
                  if(pool[p]->align!=1)
                  {
                     move(y,1);y++;
                     addstr(pool[p]->name, gamelog);
                     addstr("が救出された。", gamelog);
                     gamelog.newline();

                     getkey();

                     delete_and_remove(pool,p);
                     continue;
                  }
               }

               gamelog.newline();

               delete_and_clear(location[l]->loot);

               for(int v=len(vehicle)-1;v>=0;v--)
                  if(vehicle[v]->get_location()==l)
                     delete_and_remove(vehicle,v);
            }
         }

         //OTHER OFFENDABLE ENTITIES
            //CORPS
         if(location[l]->heat&&location[l]->siege.timeuntilcorps==-1&&!location[l]->siege.siege&&offended_corps&&!LCSrandom(600)&&numpres>0)
         {
            location[l]->siege.timeuntilcorps=LCSrandom(3)+1;
            // *JDS* CEO sleepers may give a warning before corp raids
            int ceosleepercount=0;
            for(int pl=0;pl<len(pool);pl++)
            {
               if(pool[pl]->flag & CREATUREFLAG_SLEEPER&&
                  pool[pl]->type==CREATURE_CORPORATE_CEO)
               {
                  ceosleepercount=1;
               }
            }
            if(ceosleepercount||!LCSrandom(5))
            {
               erase();
               set_color(COLOR_WHITE,COLOR_BLACK,1);
               move(8,1);
               addstr("", gamelog);
               if(ceosleepercount)addstr("潜伏者のCEOの警告", gamelog);
               else addstr("匿名の情報", gamelog);
               addstr("によると、", gamelog);
               move(9,1);
               addstr("企業体に雇われた民間傭兵による", gamelog);
               if(ceosleepercount)addstr(location[l]->getname(), gamelog);
               else addstr("LCS", gamelog);
               addstr("の攻撃の準備がある。", gamelog);
               gamelog.nextMessage();

               getkey();
            }
         }
         else if(location[l]->siege.timeuntilcorps>0)location[l]->siege.timeuntilcorps--; // Corp raid countdown!
         else if(location[l]->siege.timeuntilcorps==0&&!location[l]->siege.siege&&offended_corps&&numpres>0)
         {
            music.play(MUSIC_SIEGE);
            location[l]->siege.timeuntilcorps=-1;
            // Corps raid!
            erase();
            set_color(COLOR_WHITE,COLOR_BLACK,1);

            move(8,1);
            addstr("企業体の民間傭兵による", gamelog);
            addstr(location[l]->getname(), gamelog);
            addstr("の襲撃だ!", gamelog);
            gamelog.nextMessage();

            getkey();

            location[l]->siege.siege=1;
            location[l]->siege.siegetype=SIEGE_CORPORATE;
            location[l]->siege.underattack=1;
            location[l]->siege.lights_off=0;
            location[l]->siege.cameras_off=0;
            offended_corps=0;
         }
         else if(location[l]->siege.timeuntilcorps==0)location[l]->siege.timeuntilcorps=-1; // Silently call off foiled corp raids

            //CONSERVATIVE CRIME SQUAD
         bool ccs_active = endgamestate>=ENDGAME_CCS_APPEARANCE && endgamestate<ENDGAME_CCS_DEFEATED;
         bool target_interesting = endgamestate>=ENDGAME_CCS_SIEGES || location[l]->compound_walls & COMPOUND_PRINTINGPRESS;
         if(ccs_active && target_interesting)
         {
            if(location[l]->heat&&location[l]->siege.timeuntilccs==-1&&!location[l]->siege.siege&&!LCSrandom(60)&&numpres>0)
            {
               location[l]->siege.timeuntilccs=LCSrandom(3)+1;
               // CCS sleepers may give a warning before raids
               int ccssleepercount=0;
               for(int pl=0;pl<len(pool);pl++)
               {
                  if(pool[pl]->flag & CREATUREFLAG_SLEEPER&&
                     (pool[pl]->type==CREATURE_CCS_VIGILANTE || pool[pl]->type==CREATURE_CCS_ARCHCONSERVATIVE ||
                      pool[pl]->type==CREATURE_CCS_MOLOTOV || pool[pl]->type==CREATURE_CCS_SNIPER))
                  {
                     ccssleepercount=1;
                     break;
                  }
               }
               if(ccssleepercount>0)
               {
                  erase();
                  set_color(COLOR_WHITE,COLOR_BLACK,1);
                  move(8,1);
                  addstr("あなたは潜伏者からCCSによる", gamelog);
                  move(9,1);
                  addstr(location[l]->name, gamelog);
                  addstr("の攻撃が近いとの警告を受けた。", gamelog);
                  gamelog.nextMessage();

                  getkey();
               }
            }
            else if(location[l]->siege.timeuntilccs>0)location[l]->siege.timeuntilccs--; // CCS raid countdown!
            else if(location[l]->siege.timeuntilccs==0&&!location[l]->siege.siege&&numpres>0)
            {
               music.play(MUSIC_SIEGE);
               location[l]->siege.timeuntilccs=-1;
               // CCS raid!
               erase();
               set_color(COLOR_WHITE,COLOR_BLACK,1);

               move(8,1);
               addstr("甲高いトラックのエンジン音が", gamelog);
               addstr(location[l]->getname(), gamelog);
               addstr("に迫っている!", gamelog);
               gamelog.newline();

               getkey();

               if(!(location[l]->compound_walls & COMPOUND_TANKTRAPS) &&
                  !LCSrandom(5))
               {
                  // CCS Carbombs safehouse!!
                  erase();
                  set_color(COLOR_RED,COLOR_BLACK,1);

                  move(8,1);
                  addstr("トラックが建物に突っ込み爆発した!", gamelog);
                  gamelog.nextMessage();

                  getkey();

                  erase();
                  set_color(COLOR_WHITE,COLOR_BLACK,1);

                  move(0,1);
                  addstr("CCSの自動車爆弾による被害報告");

                  move(2,1);
                  addstr("死亡: ");
                  int killed_y = 2;
                  int killed_x = 7;

                  move(6,1);
                  addstr("負傷: ");
                  int injured_y = 6;
                  int injured_x = 7;

                  for(int i=0;i<len(pool);i++)
                  {
                     if(pool[i]->location==l)
                     {
                        if(LCSrandom(2))
                        {
                           int namelength=len(pool[i]->name);
                           pool[i]->blood-=LCSrandom(101-pool[i]->juice/10)+10;
                           if(pool[i]->blood<0)
                           {
                              if(killed_x+namelength>78)
                              {
                                 killed_y++;
                                 killed_x=1;
                                 //Add limit for killed_y.
                              }
                              move(killed_y,killed_x);
                              pool[i]->die();
                              set_alignment_color(pool[i]->align,false);
                              addstr(pool[i]->name);
                              addstr("、");
                              killed_x+=namelength+2;
                           }
                           else
                           {
                              if(injured_x+namelength>78)
                              {
                                 injured_y++;
                                 injured_x=1;
                                 //Add limit for injured_y.
                              }
                              move(injured_y,injured_x);
                              set_alignment_color(pool[i]->align,false);
                              addstr(pool[i]->name);
                              addstr("、");
                              injured_x+=namelength+2;
                           }
                           //set_alignment_color(pool[i]->align,false);
                           //addstr(pool[i]->name);
                        }
                     }
                  }

                  getkey();
               }
               else
               {
                  // CCS Raids safehouse
                  erase();
                  set_color(COLOR_RED,COLOR_BLACK,1);

                  move(8,1);
                  addstr("CCSメンバーはトラックから飛び降り、出入口で発砲した!", gamelog);
                  gamelog.nextMessage();

                  getkey();

                  location[l]->siege.siege=1;
                  location[l]->siege.siegetype=SIEGE_CCS;
                  location[l]->siege.underattack=1;
                  location[l]->siege.lights_off=0;
                  location[l]->siege.cameras_off=0;
               }
            }
            else if(location[l]->siege.timeuntilccs==0)location[l]->siege.timeuntilccs=-1; // Silently call off foiled ccs raids
         }


            //CIA
         if(location[l]->heat&&location[l]->siege.timeuntilcia==-1&&!location[l]->siege.siege&&offended_cia&&!LCSrandom(300)&&numpres>0)
         {
            location[l]->siege.timeuntilcia=LCSrandom(3)+1;
            // *JDS* agent sleepers may give a warning before cia raids
            int agentsleepercount=0;
            for(int pl=0;pl<len(pool);pl++)
            {
               if(pool[pl]->flag & CREATUREFLAG_SLEEPER&&
                  pool[pl]->type==CREATURE_AGENT)
               {
                  //if(pool[pl]->infiltration*100>LCSrandom(100))
                  {
                     agentsleepercount=1;
                     break;
                  }
               }
            }
            if(agentsleepercount)
            {
               erase();
               set_color(COLOR_WHITE,COLOR_BLACK,1);
               move(8,1);
               addstr("潜伏者の諜報員によると、CIAは", gamelog);
               move(9,1);
               addstr(location[l]->getname(), gamelog);
               addstr("の攻撃計画を実行しようとしている。", gamelog);
               gamelog.nextMessage();

               getkey();
            }
         }
         else if(location[l]->siege.timeuntilcia>0)location[l]->siege.timeuntilcia--; // CIA raid countdown!
         else if(location[l]->siege.timeuntilcia==0&&!location[l]->siege.siege&&offended_cia&&numpres>0)
         {
            music.play(MUSIC_SIEGE);
            location[l]->siege.timeuntilcia=-1;
            // CIA raids!
            erase();
            set_color(COLOR_WHITE,COLOR_BLACK,1);

            move(8,1);
            addstr("印が何もない黒いバンが", gamelog);
            addstr(location[l]->getname(), gamelog);
            addstr("を包囲している!", gamelog);
            gamelog.newline();

            if(location[l]->compound_walls & COMPOUND_CAMERAS)
            {
               move(9,1);
               addstr("高度な技術を駆使し、", gamelog);
               move(10,1);
               addstr("明かりを消しカメラを停止させた!", gamelog);
               gamelog.nextMessage();
            }
            else if(location[l]->compound_walls & COMPOUND_GENERATOR)
            {
               move(9,1);
               addstr("高度な技術を駆使し、", gamelog);
               move(10,1);
               addstr("発電機を停止させ明かりを消した!", gamelog);
               gamelog.nextMessage();
            }
            else
            {
               move(9,1);
               addstr("明かりが消えた!", gamelog);
               gamelog.nextMessage();
            }

            getkey();

            location[l]->siege.siege=1;
            location[l]->siege.siegetype=SIEGE_CIA;
            location[l]->siege.underattack=1;
            location[l]->siege.lights_off=1;
            location[l]->siege.cameras_off=1;
         }
         else if(location[l]->siege.timeuntilcia==0)location[l]->siege.timeuntilcia=-1; // Silently call off foiled cia raids

            //HICKS
         if(!location[l]->siege.siege&&offended_amradio&&attitude[VIEW_AMRADIO]<=35&&!LCSrandom(600)&&numpres>0)
         {
            music.play(MUSIC_SIEGE);
            erase();
            set_color(COLOR_WHITE,COLOR_BLACK,1);

            move(8,1);
            addstr("AMラジオへの対抗に怒る群集が", gamelog);
            move(9,1);
            addstr(location[l]->getname(), gamelog);
            addstr("を襲撃しようとしている!", gamelog);
            gamelog.nextMessage();

            getkey();

            location[l]->siege.siege=1;
            location[l]->siege.siegetype=SIEGE_HICKS;
            location[l]->siege.underattack=1;
            location[l]->siege.lights_off=0;
            location[l]->siege.cameras_off=0;
            offended_amradio=0;
         }
         if(!location[l]->siege.siege&&offended_cablenews&&attitude[VIEW_CABLENEWS]<=35&&!LCSrandom(600)&&numpres>0)
         {
            music.play(MUSIC_SIEGE);
            erase();
            set_color(COLOR_WHITE,COLOR_BLACK,1);

            move(8,1);
            addstr("ケーブルニュースへの対抗に怒る群集が", gamelog);
            move(9,1);
            addstr("are storming the ", gamelog);
            addstr(location[l]->getname(), gamelog);
            addstr("に襲撃しようとしている!", gamelog);
            gamelog.nextMessage();

            getkey();

            location[l]->siege.siege=1;
            location[l]->siege.siegetype=SIEGE_HICKS;
            location[l]->siege.underattack=1;
            location[l]->siege.lights_off=0;
            location[l]->siege.cameras_off=0;
            offended_cablenews=0;
         }
         //Firemen
         if(law[LAW_FREESPEECH]==-2 && location[l]->siege.timeuntilfiremen==-1 && !location[l]->siege.siege &&
            offended_firemen && numpres>0 && location[l]->compound_walls & COMPOUND_PRINTINGPRESS && !LCSrandom(90))
         {
            location[l]->siege.timeuntilfiremen=LCSrandom(3)+1;

            // Sleeper Firemen can warn you of an impending raid
            int firemensleepercount=0;
            for(int pl=0;pl<len(pool);pl++)
               if(pool[pl]->flag & CREATUREFLAG_SLEEPER &&
                  pool[pl]->type==CREATURE_FIREFIGHTER &&
                  location[pool[pl]->location]->city==location[l]->city)
                  firemensleepercount++;
            if(LCSrandom(firemensleepercount+1)>0||!LCSrandom(10))
            {
               erase();
               set_color(COLOR_WHITE,COLOR_BLACK,1);
               move(8,1);
               if(firemensleepercount) addstr("潜伏者の焚書官によると、", gamelog);
               else addstr("秘密情報によると、", gamelog);
               move(9,1);
               addstr("焚書課が", gamelog);
               addstr(location[l]->name, gamelog);
               addstr("を焼き払う計画がある。", gamelog);
               gamelog.nextMessage();

               getkey();
            }

         } else if(location[l]->siege.timeuntilfiremen>0) location[l]->siege.timeuntilfiremen--;
         else if(law[LAW_FREESPEECH]==-2 && location[l]->siege.timeuntilfiremen==0 && !location[l]->siege.siege&&numpres>0)
         {
            music.play(MUSIC_SIEGE);
            location[l]->siege.timeuntilfiremen=-1;
            // Firemen raid!
            erase();
            set_color(COLOR_WHITE,COLOR_BLACK,1);

            move(8,1);
            addstr("炎が", gamelog);
            addstr(location[l]->getname(), gamelog);
            addstr("に迫る!", gamelog);
            gamelog.newline();

            move(9,1);
            addstr("回転灯を炎で照らしながら、大勢の武装した焚書官が現れた。", gamelog);
            gamelog.newline();

            getkey();

            erase();

            set_color(COLOR_WHITE,COLOR_BLACK,1);
            move(1,1);
            addstr("サイレンと金切り声が聞こえる:", gamelog);
            gamelog.newline();

            move(3,1);
            addstr("投降せよ!", gamelog);
            gamelog.newline();

            move(4,1);
            addstr("受け入れることのできない要求が響き渡る。", gamelog);
            gamelog.newline();

            move(6,1);
            addstr("おとなしく投降するならば危害は加えない。", gamelog);
            gamelog.nextMessage();

            getkey();

            location[l]->siege.siege=1;
            location[l]->siege.siegetype=SIEGE_FIREMEN;
            location[l]->siege.underattack=1;
            location[l]->siege.lights_off=0;
            location[l]->siege.cameras_off=0;
            offended_firemen=0;
         }
         else if(law[LAW_FREESPEECH]==-2 && location[l]->siege.timeuntilfiremen==0)
         {
            location[l]->siege.timeuntilfiremen=-1;
            erase();
            set_color(COLOR_WHITE,COLOR_BLACK,1);

            move(8,1);
            addstr("焚書官は誰もいない", gamelog);
            addstr(location[l]->getname(), gamelog);
            addstr("に侵入した。", gamelog);
            gamelog.newline();

            getkey();

            int y=9;

            for(int p=len(pool)-1;p>=0;p--)
            {
               if(pool[p]->location!=l)continue;
               if(!pool[p]->alive)
               {
                  move(y++,1);
                  addstr(pool[p]->name, gamelog);
                  addstr("の遺体が見つかった。", gamelog);
                  gamelog.newline();

                  getkey();

                  delete_and_remove(pool,p);
                  continue;
               }
               if(pool[p]->align!=1)
               {
                  move(y++,1);
                  addstr(pool[p]->name, gamelog);
                  addstr("が救出された。", gamelog);
                  gamelog.newline();

                  getkey();

                  delete_and_remove(pool,p);
                  continue;
               }
            }
            delete_and_clear(location[l]->loot);

            if(location[l]->compound_walls & COMPOUND_PRINTINGPRESS)
            {
               move(10,1);
               addstr("印刷機は破壊され焼却された。", gamelog);
               gamelog.newline();
               location[l]->compound_walls &= ~COMPOUND_PRINTINGPRESS;
               offended_firemen=0;
            }

            if(location[l]->front_business!=-1)
            {
               move(12,1);
               addstr("ビジネスオフィスを偽装する設備は破壊された。", gamelog);
               gamelog.newline();
               location[l]->front_business=-1;
            }
            gamelog.newline();
         }
         else if (law[LAW_FREESPEECH]<=-1 && location[l]->siege.timeuntilfiremen==0)
            location[l]->siege.timeuntilfiremen=-1,offended_firemen=0;
      }
   }
}



/* siege - updates sieges in progress */
void siegeturn(char clearformess)
{
   if(disbanding)return;

   // Count people at each location
   int l;
   //int hs=-1;
   int* liberalcount = new int[len(location)];
   char* food_prep   = new char[len(location)];

   // Clear food_prep and liberalcount lists
   std::memset(food_prep,0,len(location));
   std::memset(liberalcount,0,sizeof(int)*len(location));

   for(int p=0;p<len(pool);p++)
   {
      if(!pool[p]->alive)continue; // Dead people don't count
      if(pool[p]->align!=1)continue; // Non-liberals don't count
      if(pool[p]->location==-1)continue; // Vacationers don't count
      liberalcount[pool[p]->location]++;
   }

   for(l=0;l<len(location);l++) if(location[l]->siege.siege)
      {
         //resolve sieges with no people
         if(liberalcount[l]==0)
         {
            erase();
            set_color(COLOR_WHITE,COLOR_BLACK,1);

            move(8,1);
            addstr("保守は誰もいない", gamelog);
            addstr(location[l]->getname(), gamelog);
            addstr("に侵入した。", gamelog);
            gamelog.newline();

            if(location[l]->siege.siegetype==SIEGE_CCS&&location[l]->type==SITE_INDUSTRY_WAREHOUSE)
               location[l]->renting=RENTING_CCS; // CCS Captures warehouse

            getkey();

            int y=9;

            for(int p=len(pool)-1;p>=0;p--)
            {
               if(pool[p]->location!=l) continue;
               if(!pool[p]->alive)
               {
                  move(y++,1);
                  addstr(pool[p]->name);
                  addstr("の遺体が見つかった。", gamelog);
                  gamelog.newline();

                  getkey();

                  delete_and_remove(pool,p);
                  continue;
               }
               if(pool[p]->align!=1)
               {
                  move(y++,1);
                  addstr(pool[p]->name);
                  addstr("が救出された。", gamelog);
                  gamelog.newline();

                  getkey();

                  delete_and_remove(pool,p);
                  continue;
               }
            }
            delete_and_clear(location[l]->loot);

            for(int v=len(vehicle)-1;v>=0;v--) if(vehicle[v]->get_location()==l) delete_and_remove(vehicle,v);

            gamelog.newline();

            location[l]->siege.siege=0;
         }

         if(!location[l]->siege.underattack)
         {
            // Seperate logging message.
            gamelog.record("包囲されながら日が過ぎた…");
            gamelog.newline();

            //EAT
            bool starving=false;
            int eaters=numbereating(l);
            if(location[l]->compound_stores==0&&eaters>0)
            {
               starving=true;
               if(clearformess) erase();
               else makedelimiter();
               set_color(COLOR_WHITE,COLOR_BLACK,1);
               move(8,1);
               addstr("飢え死にしそうだ!", gamelog);
               gamelog.newline();

               getkey();
            }
            if(location[l]->compound_stores>=eaters) location[l]->compound_stores-=eaters;
            else location[l]->compound_stores=0;

            //ATTACK!
            char attack=0;

            for(int p=0;p<len(pool);p++)
            {
               if(!pool[p]->alive||pool[p]->location!=l) continue;

               if(starving) pool[p]->blood-=LCSrandom(8)+4;

               // Check if liberal starved to death.
               if(pool[p]->blood<=0)
               {
                  pool[p]->die();

                  if(clearformess) erase();
                  else makedelimiter();
                  set_color(COLOR_WHITE,COLOR_BLACK,1);
                  move(8,1);
                  addstr(pool[p]->name , gamelog);
                  addstr("は飢えて死んだ。", gamelog);
                  gamelog.newline();

                  getkey();
               }
            }

            if(!LCSrandom(12))attack=1;

            if(attack)
            {
               if(clearformess) erase();
               else makedelimiter();
               set_color(COLOR_WHITE,COLOR_BLACK,1);
               move(8,1);
               addstr("警官隊が迫り来る!", gamelog);
               gamelog.newline();

               getkey();

               location[l]->siege.underattack=1;
            }
            else
            {
               char no_bad=1;

               //CUT LIGHTS
               if(!location[l]->siege.lights_off &&
                  !(location[l]->compound_walls & COMPOUND_GENERATOR) && !LCSrandom(10))
               {
                  no_bad=0;

                  if(clearformess) erase();
                  else makedelimiter();
                  set_color(COLOR_WHITE,COLOR_BLACK,1);
                  move(8,1);
                  addstr("警官隊は明かりを消した!", gamelog);
                  gamelog.newline();

                  getkey();

                  location[l]->siege.lights_off=1;
               }

               //SNIPER
               if(!(location[l]->compound_walls & COMPOUND_BASIC) && !LCSrandom(5))
               {
                  no_bad=0;

                  vector<int> pol;
                  for(int p=0;p<len(pool);p++) if(pool[p]->alive&&pool[p]->location==l) pol.push_back(p);

                  if(len(pol))
                  {
                     if(clearformess) erase();
                     else makedelimiter();
                     set_color(COLOR_WHITE,COLOR_BLACK,1);
                     move(8,1);
                     int targ=pickrandom(pol);
                     if((int)LCSrandom(50)>pool[targ]->juice)
                     {
                        addstr("スナイパーが", gamelog);
                        addstr(pool[targ]->name, gamelog);
                        addstr("を狙撃した!", gamelog);
                        gamelog.newline();

                        if(pool[targ]->align==1) stat_dead++,liberalcount[l]--;

                        removesquadinfo(*pool[targ]);

                        pool[targ]->die();
                     }
                     else
                     {
                        addstr("スナイパーはわずかのところで", gamelog);
                        addstr(pool[targ]->name, gamelog);
                        addstr("を外した!", gamelog);
                        gamelog.newline();
                     }

                     getkey();
                  }
               }

               if(location[l]->siege.escalationstate>=3 && !LCSrandom(3))
               {
                  no_bad=0;

                  //AIR STRIKE!
                  bool hit=true;

                  if(clearformess) erase();
                  else makedelimiter();
                  set_color(COLOR_WHITE,COLOR_BLACK,1);
                  move(8,1);
                  addstr("爆撃機の迫り来る音が聞こえる!", gamelog);
                  gamelog.newline();

                  getkey();

                  bool hasAAGun = location[l]->compound_walls & COMPOUND_AAGUN;
                  bool hasGenerator = location[l]->compound_walls & COMPOUND_GENERATOR;

                  if(hasAAGun)
                  {
                     if(clearformess) erase();
                     else makedelimiter();
                     move(8,1);
                     addstr("雷のような対空砲の音がアジトに響き渡った!", gamelog);
                     gamelog.newline();

                     getkey();

                     if(clearformess) erase();
                     else makedelimiter();
                     move(8,1);
                     if(LCSrandom(5))
                     {
                        hit=false;
                        if(LCSrandom(2)) addstr("爆撃機には命中しなかった。だが、爆撃機は近づくのをためらうだろう!", gamelog);
                        else
                        {
                           addstr("命中! 爆撃機の内の1機が墜落した。", gamelog);
                           gamelog.newline();

                           getkey();

                           if(clearformess) erase();
                           else makedelimiter();
                           move(8,1);
                           addstr("一部始終がテレビ中継されている。リベラル・クライム・スコードのメンバー全員が20ジュースを得た!", gamelog);
                           for(int p=0;p<len(pool);p++) addjuice(*pool[p],20,1000);
                        }
                        gamelog.newline();

                        getkey();
                     }
                     else
                     {
                        addstr("熟練パイロットは通り抜けた!", gamelog);
                        gamelog.newline();

                        getkey();
                     }
                  }

                  if(hit)
                  {
                     if(clearformess) erase();
                     else makedelimiter();
                     move(8,1);
                     addstr("爆発がアジトを揺さぶる!", gamelog);
                     gamelog.newline();

                     getkey();

                     if(hasAAGun && !LCSrandom(3))
                     {
                        if(clearformess) erase();
                        else makedelimiter();
                        move(8,1);
                        addstr("対空砲に直撃した!", gamelog);
                        gamelog.newline();

                        getkey();

                        if(clearformess) erase();
                        else makedelimiter();
                        move(8,1);
                        addstr("残されたものは破片だけだった…", gamelog);
                        gamelog.newline();

                        getkey();

                        location[l]->compound_walls&=~COMPOUND_AAGUN;
                     }
                     else if(hasGenerator && !LCSrandom(3))
                     {
                        if(clearformess) erase();
                        else makedelimiter();
                        move(8,1);
                        addstr("発電機が破壊された!", gamelog);
                        gamelog.newline();

                        getkey();

                        if(clearformess) erase();
                        else makedelimiter();
                        move(8,1);
                        addstr("明かりが消え真っ暗になった。", gamelog);
                        gamelog.newline();

                        getkey();

                        location[l]->compound_walls&=~COMPOUND_GENERATOR;
                        location[l]->siege.lights_off=1;
                     }
                     if(!LCSrandom(2))
                     {
                        vector<int> pol;
                        for(int p=0;p<len(pool);p++) if(pool[p]->alive&&pool[p]->location==l) pol.push_back(p);

                        if(len(pol))
                        {
                           if(clearformess) erase();
                           else makedelimiter();
                           set_color(COLOR_WHITE,COLOR_BLACK,1);
                           move(8,1);
                           int targ=pickrandom(pol);
                           if((int)LCSrandom(100)>pool[targ]->juice)
                           {
                              addstr(pool[targ]->name, gamelog);
                              addstr("は空爆で死んだ!", gamelog);
                              gamelog.newline();

                              if(pool[targ]->align==1) stat_dead++,liberalcount[l]--;

                              removesquadinfo(*pool[targ]);

                              pool[targ]->die();
                           }
                           else
                           {
                              addstr(pool[targ]->name, gamelog);
                              addstr("は少しのところで死を間逃れた!", gamelog);
                              gamelog.newline();
                           }

                           getkey();
                        }
                     }
                     else
                     {
                        if(clearformess) erase();
                        else makedelimiter();
                        move(8,1);
                        addstr("幸いなことに死傷者はいなかった。", gamelog);
                        gamelog.newline();

                        getkey();
                     }
                  }
               }

               if((location[l]->compound_walls & COMPOUND_TANKTRAPS) &&
                  location[l]->siege.escalationstate>=3 && !LCSrandom(15))
               {
                  no_bad=0;

                  //ENGINEERS
                  if(clearformess) erase();
                  else makedelimiter();
                  set_color(COLOR_WHITE,COLOR_BLACK,1);
                  move(8,1);
                  addstr("対戦車障害物は工兵に除去された。", gamelog);
                  gamelog.newline();

                  getkey();

                  if(clearformess) move(9,1);
                  else
                  {
                     makedelimiter();
                     move(8,1);
                  }
                  addstr("戦車がアジトの出入口まで移動してきた。", gamelog);
                  gamelog.newline();

                  getkey();

                  location[l]->compound_walls&=~COMPOUND_TANKTRAPS;
               }

               //NEED GOOD THINGS TO BALANCE THE BAD

               // ELITE REPORTER SNEAKS IN
               if(!LCSrandom(20)&&no_bad&&liberalcount[l]>0)
               {
                  char repname[200];
                  generate_name(repname);

                  set_color(COLOR_WHITE,COLOR_BLACK,0);

                  erase();
                  move(1,1);
                  switch(LCSrandom(5))
                  {
                     case 0:addstr("ニュース番組", gamelog);break;
                     case 1:addstr("ニュース雑誌", gamelog);break;
                     case 2:addstr("ウェブサイト", gamelog);break;
                     case 3:addstr("ゴシップ誌", gamelog);break;
                     case 4:addstr("新聞", gamelog);break;
                  }
                  addstr("『");
                  switch(LCSrandom(12))
                  {
                     case 0:addstr("デイリー", gamelog);break;
                     case 1:addstr("ナイトリー", gamelog);break;
                     case 2:addstr("カレント", gamelog);break;
                     case 3:addstr("プレシング", gamelog);break;
                     case 4:addstr("ソーシャリスト", gamelog);break;
                     case 5:addstr("アメリカ", gamelog);break;
                     case 6:addstr("ナショナル", gamelog);break;
                     case 7:addstr("ユニオン", gamelog);break;
                     case 8:addstr("フォーリン", gamelog);break;
                     case 9:addstr("アソシエイテッド", gamelog);break;
                     case 10:addstr("インターナショナル", gamelog);break;
                     case 11:addstr("カウンティ", gamelog);break;
                  }
                  addstr("・", gamelog);
                  switch(LCSrandom(11))
                  {
                     case 0:addstr("レポーター", gamelog);break;
                     case 1:addstr("イシュー", gamelog);break;
                     case 2:addstr("テイク", gamelog);break;
                     case 3:addstr("コンスティテューション", gamelog);break;
                     case 4:addstr("タイム", gamelog);break;
                     case 5:addstr("ポスト", gamelog);break;
                     case 6:addstr("ニュース", gamelog);break;
                     case 7:addstr("アフェア", gamelog);break;
                     case 8:addstr("ステートマン", gamelog);break;
                     case 9:addstr("スター", gamelog);break;
                     case 10:addstr("インクアイラー", gamelog);break;
                  }
                  addstr("』のエリート記者", gamelog);
                  addstr(repname, gamelog);
                  addstr("が", gamelog);
                  move(2,1);
                  addstr("アジトに飛び込んできた!", gamelog);
                  gamelog.newline();

                  getkey();

                  int best=0;
                  for(int p=0,bestvalue=-1000;p<len(pool);p++)
                  {
                     if(!pool[p]->alive||pool[p]->align!=1||pool[p]->location!=l) continue;

                     int sum=pool[p]->get_attribute(ATTRIBUTE_INTELLIGENCE, true)
                            +pool[p]->get_attribute(ATTRIBUTE_HEART, true)
                            +pool[p]->get_skill(SKILL_PERSUASION)
                            +pool[p]->juice;

                     if(sum>bestvalue) best=p,bestvalue=sum;
                  }

                  move(4,1);
                  addstr(pool[best]->name, gamelog);
                  addstr("はインタビューを受けることにした。", gamelog);
                  gamelog.newline();

                  getkey();

                  move(6,1);
                  addstr("インタビューは多岐にわたり、様々な話題で会話がなされた。", gamelog);
                  gamelog.newline();

                  getkey();

                  int segmentpower=pool[best]->attribute_roll(ATTRIBUTE_INTELLIGENCE)
                                  +pool[best]->attribute_roll(ATTRIBUTE_HEART)
                                  +pool[best]->skill_roll(SKILL_PERSUASION)
                                  +pool[best]->skill_roll(SKILL_PERSUASION)
                                  +pool[best]->skill_roll(SKILL_PERSUASION);

                  move(8,1);
                  if(segmentpower<15)
                  {
                     addstr(repname, gamelog);
                     addstr("はインタビューを途中で打ち切り、", gamelog);
                     move(9,1);
                     addstr("『", gamelog);
                     switch(LCSrandom(11))
                     {
                        case 0: addstr("炎上", gamelog); break;
                        case 1: if(law[LAW_FREESPEECH]==-2) addstr("間抜けな", gamelog);
                                else addstr("イカレた", gamelog); break;
                        case 2: addstr("狂気の", gamelog); break;
                        case 3: addstr("狂った", gamelog); break;
                        case 4: addstr("愚かな", gamelog); break;
                        case 5: addstr("馬鹿な", gamelog); break;
                        case 6: addstr("空っぽの", gamelog); break;
                        case 7: addstr("おかしな", gamelog); break;
                        case 8: addstr("未熟な", gamelog); break;
                        case 9: addstr("ヤク中", gamelog); break;
                        case 10: addstr("酔っ払い", gamelog); break;
                     }
                     addstr(" ", gamelog);
                     switch(LCSrandom(10))
                     {
                        case 0: addstr("リベラル", gamelog); break;
                        case 1: addstr("ソーシャリスト", gamelog); break;
                        case 2: addstr("アナーキスト", gamelog); break;
                        case 3: addstr("コミュニスト", gamelog); break;
                        case 4: addstr("マルキスト", gamelog); break;
                        case 5: addstr("グリーン", gamelog); break;
                        case 6: addstr("エリート", gamelog); break;
                        case 7: addstr("ゲリラ", gamelog); break;
                        case 8: addstr("コマンドー", gamelog); break;
                        case 9: addstr("ソルジャー", gamelog); break;
                     }
                     addstr("』と呼ばれる", gamelog);
                     move(10,1);
                     addstr("ブロードウェイミュージカルの記事と差し替えられた。", gamelog);
                     gamelog.newline();
                  }
                  else if(segmentpower<20)
                  {
                     addstr("だが、インタビューは退屈で、", gamelog);
                     addstr(repname, gamelog);
                     addstr("は寝てしまった。", gamelog);
                     gamelog.newline();
                  }
                  else if(segmentpower<25)
                  {
                     addstr("だが、その間ずっと", gamelog);
                     addstr(pool[best]->name, gamelog);
                     addstr("はイライラした様子だった。", gamelog);
                     gamelog.newline();
                  }
                  else if(segmentpower<30)
                  {
                     addstr(pool[best]->name, gamelog);
                     addstr("の話はいまいちだった。", gamelog);
                     gamelog.newline();
                  }
                  else if(segmentpower<45)
                  {
                     addstr(pool[best]->name, gamelog);
                     addstr("はLCSの考えをうまく表現できた。", gamelog);
                     gamelog.newline();
                  }
                  else if(segmentpower<60)
                  {
                     addstr("議論はエキサイティングでダイナミックなものだった。", gamelog);
                     move(9,1);
                     addstr("ケーブルニュースやAMラジオさえも数日間これを話題にした。", gamelog);
                     gamelog.newline();
                  }
                  else
                  {
                     addstr(repname);
                     addstr("は後にピューリッツァー賞を受賞する。", gamelog);
                     move(9,1);
                     addstr("これは事実上全てのアメリカ人が", gamelog);
                     addstr(pool[best]->name, gamelog);
                     addstr("の言葉に動かされたことになる。", gamelog);
                     gamelog.newline();
                  }

                  getkey();

                  //CHECK PUBLIC OPINION
                  change_public_opinion(VIEW_LIBERALCRIMESQUAD,20);
                  change_public_opinion(VIEW_LIBERALCRIMESQUADPOS,(segmentpower-25)/2,segmentpower+50);
                  for(int v=0;v<5;v++) change_public_opinion(LCSrandom(VIEWNUM-3),(segmentpower-25)/2);
               }
            }
            gamelog.newline(); // single blank line after every siege day
         } // end if(!location[l]->siege.underattack)
      } // end for(l=0;l<len(location);l++) if(location[l]->siege.siege)
   delete[] liberalcount;
   delete[] food_prep;
}



/* siege - handles giving up */
void giveup()
{
   int loc=-1;
   if(selectedsiege!=-1)loc=selectedsiege;
   if(activesquad!=NULL)loc=activesquad->squad[0]->location;
   if(loc==-1)return;

   if(location[loc]->renting>1)location[loc]->renting=RENTING_NOCONTROL;

   //IF POLICE, END SIEGE
   if(location[loc]->siege.siegetype==SIEGE_POLICE ||
      location[loc]->siege.siegetype==SIEGE_FIREMEN)
   {
      music.play(MUSIC_SIEGE);
      int polsta=find_police_station(loc);

      //END SIEGE
      erase();
      set_color(COLOR_WHITE,COLOR_BLACK,1);
      move(1,1);
      if(location[loc]->siege.siegetype==SIEGE_POLICE && location[loc]->siege.escalationstate == 0)
         addstr("警察は", gamelog);
      else if(location[loc]->siege.siegetype==SIEGE_POLICE && location[loc]->siege.escalationstate >= 1)
         addstr("兵士は", gamelog);
      else addstr("焚書官は", gamelog);
      addstr("部隊の武器を含む全てを差し押さえた。", gamelog);
      gamelog.newline();

      int kcount=0,pcount=0,icount=0,p;
      char kname[100],pname[100],pcname[100];
      for(p=len(pool)-1;p>=0;p--)
      {
         if(pool[p]->location!=loc||!pool[p]->alive) continue;

         if(pool[p]->flag&CREATUREFLAG_ILLEGALALIEN) icount++;

         if(pool[p]->flag&CREATUREFLAG_MISSING&&pool[p]->align==-1)
         {
            kcount++;
            strcpy(kname,pool[p]->propername);
            if(pool[p]->type==CREATURE_RADIOPERSONALITY) offended_amradio=1;
            if(pool[p]->type==CREATURE_NEWSANCHOR) offended_cablenews=1;
            //clear interrogation data if deleted
            delete pool[p]->activity.intr();
         }
      }

      //CRIMINALIZE POOL IF FOUND WITH KIDNAP VICTIM OR ALIEN
      if(kcount) criminalizepool(LAWFLAG_KIDNAPPING,-1,loc);
      if(icount) criminalizepool(LAWFLAG_HIREILLEGAL,-1,loc);

      if(location[loc]->siege.siegetype==SIEGE_FIREMEN&&location[loc]->compound_walls&COMPOUND_PRINTINGPRESS)
         criminalizepool(LAWFLAG_SPEECH,-1,loc); // Criminalize pool for unacceptable speech

      //LOOK FOR PRISONERS (MUST BE AFTER CRIMINALIZATION ABOVE)
      for(p=len(pool)-1;p>=0;p--)
      {
         if(pool[p]->location!=loc||!pool[p]->alive) continue;

         if(iscriminal(*pool[p])&&!(pool[p]->flag&CREATUREFLAG_MISSING&&pool[p]->align==-1))
         {
            pcount++;
            strcpy(pname,pool[p]->propername);
            strcpy(pcname,pool[p]->name);
         }
      }

      if(kcount==1)
      {
         move(3,1);
         addstr(kname);
         addstr("はリハビリを受け回復した。", gamelog);
         gamelog.newline();
      }
      if(kcount>1)
      {
         move(3,1);
         addstr("誘拐の犠牲者達はリハビリを受け回復した。", gamelog);
         gamelog.newline();
      }
      if(pcount==1)
      {
         move(5,1);
         addstr(pname, gamelog);
         if(strcmp(pname,pcname))
         {
            addstr("、別名", gamelog);
            addstr(pcname, gamelog);
            addstr("、", gamelog);
         }
         move(6,1);
         addstr("は警察署に連行された。", gamelog);
         gamelog.newline();
      }
      if(pcount>1)
      {
         move(5,1);
         addstr(pcount, gamelog);
         addstr("人のリベラルが警察署に連行された。", gamelog);
         gamelog.newline();
      }
      if(ledger.get_funds()>0)
      {
         if(ledger.get_funds()<=2000 || location[loc]->siege.siegetype==SIEGE_FIREMEN)
         {
            move(8,1);
            addstr("幸いなことに、資金は無事だった。", gamelog);
            gamelog.newline();
         }
         else
         {
            move(8,1);
            int confiscated = LCSrandom(LCSrandom(ledger.get_funds()-2000)+1)+1000;
            if(ledger.get_funds()-confiscated > 50000)
               confiscated += ledger.get_funds() - 30000 - LCSrandom(20000) - confiscated;
            addstr_fl(gamelog,"LCSの資金 $%d が差し押さえられた。",confiscated);
            gamelog.newline();
            ledger.subtract_funds(confiscated,EXPENSE_CONFISCATED);
         }
      }
      if(location[loc]->siege.siegetype==SIEGE_FIREMEN)
      {
         if(location[loc]->compound_walls & COMPOUND_PRINTINGPRESS)
         {
            move(10,1);
            addstr("印刷機は破壊され焼却された。", gamelog);
            gamelog.newline();
            location[loc]->compound_walls &= ~COMPOUND_PRINTINGPRESS;
         }
      }
      else
      {
         if(location[loc]->compound_walls)
         {
            move(10,1);
            addstr("アジトの設備は撤去された。", gamelog);
            gamelog.newline();
            location[loc]->compound_walls=0;
         }
      }
      if(location[loc]->front_business!=-1)
      {
         move(12,1);
         addstr("ビジネスオフィスを偽装する設備は破壊された。", gamelog);
         gamelog.newline();
         location[loc]->front_business=-1;
      }

      getkey();

      if(location[loc]->siege.siegetype==SIEGE_FIREMEN)
         offended_firemen=0; // Firemen do not hold grudges

      for(p=len(pool)-1;p>=0;p--)
      {
         if(pool[p]->location!=loc) continue;

         //ALL KIDNAP VICTIMS FREED REGARDLESS OF CRIMES
         if((pool[p]->flag & CREATUREFLAG_MISSING)||
            !pool[p]->alive)
         {
            // Clear actions for anybody who was tending to this person
            for(int i=0;i<len(pool);i++)
               if(pool[i]->alive&&pool[i]->activity.type==ACTIVITY_HOSTAGETENDING&&pool[i]->activity.arg==pool[p]->id)
                  pool[i]->activity.type=ACTIVITY_NONE;

            removesquadinfo(*pool[p]);
            delete_and_remove(pool,p);
            continue;
         }

         //TAKE SQUAD EQUIPMENT
         if(pool[p]->squadid!=-1)
         {
            int sq=getsquad(pool[p]->squadid);
            if(sq!=-1)delete_and_clear(squad[sq]->loot);
         }

         pool[p]->drop_weapons_and_clips(NULL);

         if(iscriminal(*pool[p]))
         {
            removesquadinfo(*pool[p]);
            pool[p]->location=polsta;
            pool[p]->activity.type=ACTIVITY_NONE;
         }
      }

      location[loc]->siege.siege=0;
   }
   else
   {
      //OTHERWISE IT IS SUICIDE
      int killnumber=0;
      for(int p=len(pool)-1;p>=0;p--)
      {
         if(pool[p]->location!=loc) continue;

         if(pool[p]->alive&&pool[p]->align==1) stat_dead++;

         killnumber++;
         removesquadinfo(*pool[p]);
         pool[p]->die();
         pool[p]->location=-1;
      }

      if(location[loc]->siege.siegetype==SIEGE_CCS&&location[loc]->type==SITE_INDUSTRY_WAREHOUSE)
         location[loc]->renting=RENTING_CCS; // CCS Captures warehouse

      erase();
      set_color(COLOR_WHITE,COLOR_BLACK,1);
      move(1,1);
      addstr(location[loc]->getname(), gamelog);
      addstr("にいた全員が殺害された。", gamelog);
      gamelog.newline();
      if(!endcheck(-2)) music.play(MUSIC_SIEGE); // play correct music for if we lost the game or didn't lose it

      getkey();

      newsstoryst *ns=new newsstoryst;
      ns->type=NEWSSTORY_MASSACRE;
      ns->loc=loc;
      ns->crime.push_back(location[loc]->siege.siegetype);
      ns->crime.push_back(killnumber);
      newsstory.push_back(ns);

      //MUST SET cursite TO SATISFY endcheck() CODE
      int tmp=cursite;
      cursite=loc;
      endcheck();
      cursite=tmp;

      location[loc]->siege.siege=0;
   }

   //CONFISCATE MATERIAL
   delete_and_clear(location[loc]->loot);
   for(int v=len(vehicle)-1;v>=0;v--)
      if(vehicle[v]->get_location()==loc)
         delete_and_remove(vehicle,v);

   gamelog.newline();

}



/* siege - checks how many days of food left at the site */
int fooddaysleft(int loc)
{
   int eaters=numbereating(loc);
   if(eaters==0) return -1;
   return location[loc]->compound_stores/eaters+((location[loc]->compound_stores%eaters)>eaters/2);
}



/* siege - checks how many people are eating at the site */
int numbereating(int loc)
{
   int eaters=0;
   for(int p=0;p<len(pool);p++) //Must be here, alive, Liberal, and not a sleeper, to count as an eater
      if(pool[p]->location==loc&&pool[p]->alive&&pool[p]->align==1&&!(pool[p]->flag&CREATUREFLAG_SLEEPER)) eaters++;
   return eaters;
}

// Siege -- Mass combat outside safehouse
char sally_forth_aux(int loc)
{
   int p;
   reloadparty();
   siegest siege = location[loc]->siege;
   cursite = loc;

   for(int e=0;e<ENCMAX;e++) encounter[e].exists=0;

   switch(siege.siegetype)
   {
   case SIEGE_CIA:
   case SIEGE_HICKS:
   case SIEGE_CORPORATE:
   case SIEGE_CCS:
   case SIEGE_FIREMEN:
   default:
      // So yeah, WTF is the reason there isn't a break statement here???
      // If everything ends up in the SIEGE_POLICE case we shouldn't even have a switch statement here at all.
   case SIEGE_POLICE: // Currently only police sieges should allow this
      // SWAT teams
      if(siege.escalationstate==0)
         for(int e=0;e<ENCMAX-9;e++)
            makecreature(encounter[e],CREATURE_SWAT);
      // Military
      else if(siege.escalationstate>=1)
         for(int e=0;e<ENCMAX-9;e++)
            makecreature(encounter[e],CREATURE_SOLDIER);
      // M1 Tank
      if(siege.escalationstate>=2 && !(location[loc]->compound_walls & COMPOUND_TANKTRAPS))
         makecreature(encounter[ENCMAX-9],CREATURE_TANK);
      break;
   }

   mode=GAMEMODE_CHASEFOOT;
   music.play(MUSIC_DEFENSE);
   bool ranaway = false;

   while(true)
   {
      // Count heroes
      int partysize=0,partyalive=0;
      for(p=0;p<len(pool);p++) if(pool[p]->align==1&&pool[p]->location==cursite&&!(pool[p]->flag&CREATUREFLAG_SLEEPER))
      {
         partysize++;
         if(pool[p]->alive) partyalive++;
      }

      // Count bad guys
      int encsize=0;
      for(int e=0;e<ENCMAX;e++) if(encounter[e].exists) encsize++;

      // Let's roll
      autopromote(loc);
      erase();

      set_color(COLOR_WHITE,COLOR_BLACK,0);
      move(0,0);
      addstr(location[loc]->getname());

      // Player's party
      if(partyalive==0) party_status=-1;
      printparty();

      if(partyalive>0)
      {
         // Options
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

         set_color(COLOR_WHITE,COLOR_BLACK,0);
         move(9,1);
         addstr("D - 脱出する");
         move(10,1);
         addstr("E - 装備");
         move(11,1);
         addstr("F - 戦う!");
         move(12,1);
         addstr("G - 投降する");
      }
      else
      {
         endcheck(-2); // play the right music in case we're dead
         set_color(COLOR_WHITE,COLOR_BLACK,0);
         move(9,1);
         addstr("C - 保守的判断を反省する");
      }

      // Enemies
      printencounter();

      // check if we fought the previous loop; if so, add a blank gamelog line
      if(foughtthisround) gamelog.newline();
      foughtthisround=0;

      int c=getkey();

      // Reflecting on your poor judgment
      if(partyalive==0&&c=='c'&&!endcheck())
      {
         mode=GAMEMODE_BASE;
         return 0;
      }

      // Providing orders
      if(partyalive>0)
      {
         // Reorder
         if(c=='o'&&partysize>1) orderparty();

         // View status
         if(c=='0') party_status=-1;

         // Character info
         if(c>='1'&&c<='6') if(activesquad->squad[c-'1']!=NULL)
         {
            if(party_status==c-'1')fullstatus(party_status);
            else party_status=c-'1';
         }

         // Surrender
         if(c=='g') giveup();

         // Run away
         if(c=='d')
         {
            if(encounter[0].exists&&encounter[0].type==CREATURE_COP)
            {
               sitestory->crime.push_back(CRIME_FOOTCHASE);
               criminalizeparty(LAWFLAG_RESIST);
            }
            evasiverun();
            enemyattack();
            creatureadvance();
            ranaway = true;
         }

         if(c=='f')
         {
            youattack();
            enemyattack();
            creatureadvance();
         }

         if(c=='e') equip(location[loc]->loot,-1);

         // Check for victory
         partysize=0,partyalive=0;
         for(p=0;p<len(pool);p++) if(pool[p]->align==1&&pool[p]->location==cursite&&!(pool[p]->flag&CREATUREFLAG_SLEEPER))
         {
            partysize++;
            if(pool[p]->alive) partyalive++;
         }

         int baddiecount=0;
         for(int e=0;e<ENCMAX;e++) if(encounter[e].enemy()&&encounter[e].alive&&encounter[e].exists) baddiecount++;

         if(partyalive&&!baddiecount)
         {
            for(int p=0;p<len(pool);p++) for(int w=0;w<BODYPARTNUM;w++) pool[p]->wound[w]&=~WOUND_BLEEDING;
            mode=GAMEMODE_BASE;
            if(ranaway)
            {
               music.play(MUSIC_CONQUER);
               set_color(COLOR_WHITE,COLOR_BLACK,1);
               clearmessagearea();
               move(16,1);
               addstr("これで自由だ!", gamelog);
               gamelog.nextMessage();

               getkey();

               escapesiege(false);
               return 1;
            }
            else
            {
               music.play(MUSIC_CONQUER);
               set_color(COLOR_WHITE,COLOR_BLACK,1);
               clearmessagearea();
               move(16,1);
               addstr("包囲網は崩壊した!", gamelog);
               gamelog.nextMessage();

               getkey();

               conquertext();
               escapesiege(true);
               return 2;
            }
         }
      }
   }
   mode=GAMEMODE_BASE;
   return 1;
}

/* siege - prepares for exiting the siege to fight the attackers head on */
void sally_forth()
{  //GIVE INFO SCREEN
   music.play(MUSIC_DEFENSE);
   erase();
   set_color(COLOR_RED,COLOR_BLACK,1);
   move(1,30);
   addstr("包囲網: 脱出か死か");

   set_color(COLOR_WHITE,COLOR_BLACK,0);
   move(3,15);
   addstr("あなたは今、アジトを囲む保守派の包囲網から脱出し");
   move(4,11);
   addstr("ようとしている。敵の準備は整っている。そして、あなた");
   move(5,11);
   addstr("は彼らを倒すか、それともここから逃げ出すかして生き延");
   move(6,11);
   addstr("びなければならない。");
   move(8,11);
   addstr("あなたの部隊は可能ならば6人まで増強される。");
   move(9,11);
   addstr("もしリベラルが多数いるならば、彼らから援護射撃を得ら");
   move(10,11);
   addstr("れるだろう。");

   int loc=-1;
   if(selectedsiege!=-1)loc=selectedsiege;
   if(activesquad!=NULL)loc=activesquad->squad[0]->location;
   if(loc==-1)return;

   set_color(COLOR_RED,COLOR_BLACK,1);
   move(23,18);
   addstr("何かキーを押すと保守の侵略者と立ち向かう");

   // Seperate logging text
   gamelog.log("リベラル達は果敢にも包囲網に立ち向かう。");

   getkey();

   if(location[loc]->siege.siegetype==SIEGE_CCS&&location[loc]->type==SITE_INDUSTRY_WAREHOUSE)
      location[loc]->renting=RENTING_CCS; // CCS Captures warehouse -- this will be reversed if you fight them off

   //CRIMINALIZE
   if(location[loc]->siege.siegetype==SIEGE_POLICE) criminalizepool(LAWFLAG_RESIST,-1,loc);

   //DELETE ALL SQUADS IN THIS AREA UNLESS THEY ARE THE activesquad
   for(int sq=len(squad)-1;sq>=0;sq--)
      if(squad[sq]!=activesquad&&squad[sq]->squad[0])
         if(squad[sq]->squad[0]->location==loc)
         {
            if(activesquad)
            {
               for(int p=0;p<6;p++)
               {
                  if(!squad[sq]->squad[p]) continue;
                  squad[sq]->squad[p]->squadid=-1;
               }
               delete_and_remove(squad,sq);
            }
            else activesquad=squad[sq];
         }

   // No squads at the location? Form a new one.
   if(!activesquad)
   {
      squad.push_back(new squadst);
      squad.back()->id=cursquadid++;
      strcpy(squad.back()->name,location[selectedsiege]->getname(true));
      strcat(squad.back()->name," Defense");
      int i=0;
      for(int p=0;p<len(pool);p++)
         if(pool[p]->location==selectedsiege&&pool[p]->alive&&pool[p]->align==1)
         {
            squad.back()->squad[i]=pool[p];
            pool[p]->squadid=squad.back()->id;
            if(++i>=6) break;
         }
      activesquad = squad.back();
   }

   //MAKE SURE PARTY IS ORGANIZED
   autopromote(loc);

   //START FIGHTING
   newsstoryst *ns=new newsstoryst;
   ns->type=NEWSSTORY_SQUAD_ESCAPED;
   ns->positive=1;
   ns->loc=loc;
   ns->siegetype=location[loc]->siege.siegetype;
   newsstory.push_back(ns);
   sitestory = ns;
   char result = sally_forth_aux(loc);
   if(result==2) ns->type=NEWSSTORY_SQUAD_BROKESIEGE;
   // If you fail, make sure the safehouse isn't under siege anymore by
   // forcing you to "give up".
   if(result==0)
   {
      gamelog.log("あなたは敗れた。");
      resolvesafehouses();
   }
}


/* siege - prepares for entering site mode to fight the siege */
void escape_engage()
{
   music.play(MUSIC_DEFENSE);
   //GIVE INFO SCREEN
   erase();
   set_color(COLOR_RED,COLOR_BLACK,1);
   move(1,30);
   addstr("防衛戦: 脱出か死か");

   set_color(COLOR_WHITE,COLOR_BLACK,0);
   move(3,15);
   addstr("今、保守の軍勢と戦いが始まる。");
   move(4,11);
   addstr("あなたはリベラルのアジトにいる。そして、そこに保守の");
   move(5,11);
   addstr("部隊が押し入ろうとしている。リベラル・クライム・スコ");
   move(6,11);
   addstr("ードはアジトの出入口から離れた場所にいる。");
   move(7,11);
   addstr("あなたがすべきことは、部隊を安全に脱出させるか、それ");
   move(8,11);
   addstr("とも保守をここから追い出すかだ。どちらを選んでも、リ");
   move(9,11);
   addstr("ベラルが持ち運んでいないアジトに残した装備は破壊され");
   move(10,11);
   addstr("る可能性がある。可能な限り守らなければならない。");
   move(11,11);
   addstr("あなたの部隊が可能ならば6人に増強されたことに気づくだ");
   move(12,11);
   addstr("ろう。それ以上のリベラルがいるならば、彼らは部隊の背後");
   move(13,11);
   addstr("で行動する。");
   move(14,11);
   addstr("新しいキー R - 再編成 を押すとそれが反映され、武装した");
   move(15,11);
   addstr("背後のメンバーが援護射撃を行う。全員で6人の場合は、6人");
   move(16,11);
   addstr("が部隊として行動する。6人未満ならば、全員がそうしなけ");
   move(17,11);
   addstr("ればならない。");

   int loc=-1;
   if(selectedsiege!=-1) loc=selectedsiege;
   if(activesquad!=NULL) loc=activesquad->squad[0]->location;
   if(loc==-1) return;

   if(location[loc]->compound_walls&COMPOUND_CAMERAS)
   {
      move(18,16);
      addstr("監視カメラが捕らえた部隊は M - 地図 上に表示される。");
   }
   if(location[loc]->compound_walls&COMPOUND_TRAPS)
   {
      move(19,16);
      addstr("ブービートラップは敵には効くが、味方には影響しない。");
   }

   set_color(COLOR_RED,COLOR_BLACK,1);
   move(23,11);
   addstr("何かキーを押すと保守の侵略者と立ち向かう");

   // Seperate logging text
   gamelog.log("リベラル達はアジトで保守に立ち向かう");

   getkey();

   if(location[loc]->siege.siegetype==SIEGE_CCS&&location[loc]->type==SITE_INDUSTRY_WAREHOUSE)
      location[loc]->renting=RENTING_CCS; // CCS Captures warehouse -- this will be reversed if you fight them off

   //CRIMINALIZE
   if(location[loc]->siege.siegetype==SIEGE_POLICE) criminalizepool(LAWFLAG_RESIST,-1,loc);

   //DELETE ALL SQUADS IN THIS AREA UNLESS THEY ARE THE activesquad
   for(int sq=len(squad)-1;sq>=0;sq--)
      if(squad[sq]!=activesquad&&squad[sq]->squad[0])
         if(squad[sq]->squad[0]->location==loc)
         {
            if(activesquad)
            {
               for(int p=0;p<6;p++)
               {
                  if(!squad[sq]->squad[p]) continue;
                  squad[sq]->squad[p]->squadid=-1;
               }
               delete_and_remove(squad,sq);
            }
            else activesquad = squad[sq];
         }

   // No squads at the location? Form a new one.
   if(!activesquad)
   {
      squad.push_back(new squadst);
      squad.back()->id=cursquadid++;
      strcpy(squad.back()->name,location[selectedsiege]->getname(true));
      strcat(squad.back()->name," Defense");
      int i=0;
      for(int p=0;p<len(pool);p++) if(pool[p]->location==selectedsiege&&pool[p]->alive&&pool[p]->align==1)
      {
         squad.back()->squad[i]=pool[p];
         pool[p]->squadid=squad.back()->id;
         if(++i>=6) break;
      }
      activesquad = squad.back();
   }

   //MAKE SURE PARTY IS ORGANIZED
   autopromote(loc);

   //START FIGHTING
   newsstoryst *ns=new newsstoryst;
   if(location[loc]->siege.underattack) ns->type=NEWSSTORY_SQUAD_FLEDATTACK;
   else ns->type=NEWSSTORY_SQUAD_ESCAPED;
   ns->positive=1;
   ns->loc=loc;
   ns->siegetype=location[loc]->siege.siegetype;
   newsstory.push_back(ns);
   mode_site(loc);
}

/* siege - what happens when you escaped the siege */
void escapesiege(char won)
{
   //TEXT IF DIDN'T WIN
   if(!won)
   {
      music.play(MUSIC_CONQUER);
      //GIVE INFO SCREEN
      erase();
      set_color(COLOR_YELLOW,COLOR_BLACK,1);
      move(1,37);
      addstr("脱出!", gamelog);
      gamelog.nextMessage();

      set_color(COLOR_WHITE,COLOR_BLACK,0);
      move(3,15);
      addstr("保守はリベラル・クライム・スコードにとどめを刺し");
      move(4,11);
      addstr("たと考えているだろう。だが、それは保守の考えが浅はか");
      move(5,11);
      addstr("であることを自ら証明しているのと同じである。");
      move(6,15);
      addstr("しかし、よいことばかりではない。脱出できた代わりに、");
      move(7,11);
      addstr("後に残したものは全て失われた。あなたは新しいアジトで");
      move(8,11);
      addstr("一からやり直さなければならない。幸いなことに、資金は");
      move(9,11);
      addstr("全てあなたの元に残されている。");
      move(10,11);
      addstr("フライトはあなたに再編成のための時間を与えてくれた。");
      move(11,11);
      addstr("しかし、保守は間違いなく次の襲撃に備えているだろう。");

      int homes=-1;
      if(activesquad)
         if(activesquad->squad[0]!=NULL)
            homes=find_homeless_shelter(*activesquad->squad[0]);

      set_color(COLOR_YELLOW,COLOR_BLACK,1);
      move(13,11);
      addstr("何かキーを押すと解散してしばらく身を潜める。");

      // Seperate logging text
      gamelog.log("リベラルは解散ししばらく身を潜めた。");

      getkey();

      //dump retrieved loot in homeless shelter - is there anywhere better to put it?
      if(activesquad&&homes!=-1) location[homes]->getloot(activesquad->loot);

      activesquad=NULL; //active squad cannot be disbanded in removesquadinfo,
                        //but we need to disband current squad as the people are going to be 'away'.

      //GET RID OF DEAD, etc.
      if(location[cursite]->renting>1)location[cursite]->renting=RENTING_NOCONTROL;

      for(int p=len(pool)-1;p>=0;p--)
      {
         if(pool[p]->location!=cursite) continue;
         if(!pool[p]->alive)
         {
            delete_and_remove(pool,p);
            continue;
         }

         //BASE EVERYONE LEFT AT HOMELESS SHELTER
         removesquadinfo(*pool[p]);
         pool[p]->hiding=LCSrandom(3)+2;
         if(pool[p]->align==1) // not a hostage
            pool[p]->location=-1;
         else // hostages don't go into hiding, just shove em into the homeless shelter
            pool[p]->location=homes;
         pool[p]->base=homes;
      }
      delete_and_clear(location[cursite]->loot);

      for(int v=len(vehicle)-1;v>=0;v--)
         if(vehicle[v]->get_location()==cursite)
            delete_and_remove(vehicle,v);

      location[cursite]->compound_walls=0;
      location[cursite]->compound_stores=0;
      location[cursite]->front_business=-1;
      initlocation(*location[cursite]);
   }

   //SET UP NEW SIEGE CHARACTERISTICS, INCLUDING TIMING
   location[cursite]->siege.siege=0;
   if(won&&location[cursite]->siege.siegetype==SIEGE_POLICE)
   {
      location[cursite]->siege.timeuntillocated=LCSrandom(4)+4;
      location[cursite]->siege.escalationstate++;
      if(police_heat<4) police_heat++;
   }
}



/* siege - flavor text when you fought off the raid */
void conquertext()
{
   //GIVE INFO SCREEN
   music.play(MUSIC_CONQUER);
   erase();
   set_color(COLOR_GREEN,COLOR_BLACK,1);
   move(1,26);
   addstr("* * * * *   勝利   * * * * *", gamelog);
   gamelog.newline();

   if(location[cursite]->siege.siegetype==SIEGE_POLICE)
   {
      set_color(COLOR_WHITE,COLOR_BLACK,0);
      move(3,15);
      addstr("保守の操り人形たちは押し戻された -- しばらくの間", gamelog);
      move(4,11);
      addstr("だが。彼らが再編成するまでにこのアジトを放棄し、安全", gamelog);
      move(5,11);
      addstr("な新しいアジトに移ったほうがよいだろう。", gamelog);
   }
   else
   {
      set_color(COLOR_WHITE,COLOR_BLACK,0);
      move(3,15);
      addstr("保守の操り人形たちは押し戻された。", gamelog);
      move(4,11);
      addstr("だが、リベラル・アジェンダを実現するその日まで、真の", gamelog);
      move(5,11);
      addstr("安全はないのだ。", gamelog);
   }
   gamelog.nextMessage();

   move(7,19);
   addstr("Cキーでリベラルを続ける。");

   while(getkey()!='c');
}



/* siege - flavor text when you crush a CCS safe house */
void conquertextccs()
{
   music.play(MUSIC_CONQUER);
   //GIVE INFO SCREEN
   erase();
   set_color(COLOR_GREEN,COLOR_BLACK,1);
   move(1,26);
   addstr("* * * * *   勝利   * * * * *", gamelog);
   gamelog.newline();

   if(ccs_kills<3)
   {
      set_color(COLOR_WHITE,COLOR_BLACK,0);
      move(3,15);
      if(ccs_siege_kills>10)
      {
         addstr("銃声がまだ耳に残っている。部隊は勝利に歓喜した。", gamelog);
         move(4,11);
         addstr("", gamelog);
      }
      else
      {
         addstr("CCSの大尉の亡骸が足元に横たわっている。部隊は撤収を", gamelog);
         move(4,11);
         addstr("始めた。");
      }
      addstr("CCSの設立者はここにはいなかった。だが、", gamelog);
      move(5,11);
      addstr("彼らの力は大きく損なわれたであろう。落ち着きを取り戻", gamelog);
      move(6,11);
      addstr("した後、ここを将来のリベラル基地にしなければならない。", gamelog);
   }
   else
   {
      move(3,15);
      if(ccs_siege_kills>10)
      {
         addstr("銃声がまだ耳に残っている。部隊は最終的な勝利に歓", gamelog);
         move(4,11);
         addstr("喜した。", gamelog);

         move(6,15);
         addstr("アジトに残されたものの調査が進むに連れ、ここが", gamelog);
         move(7,11);
         addstr("CCSの最後のアジトである確信がますます強くなった。", gamelog);
      }
      else
      {
         addstr("CCS設立者の亡骸が横たわっている。部隊は撤収を始", gamelog);
         move(4,11);
         addstr("めた。", gamelog);

         move(6,15);
         addstr("設立者が自身の基地の中央で死んだ今、敵の士気と自", gamelog);
         move(7,11);
         addstr("信は粉々に砕け散った。", gamelog);
      }
      gamelog.newline();

      move(9,15);
      addstr("CCSは完全に崩壊した。これからは革命に注力すべきではな", gamelog);
      move(10,15);
      addstr("いだろうか。", gamelog);
      gamelog.newline();

      move(12,5);
      addstr("コンサバ・クライム・スコードを殲滅した全員が+200のジュースを得た。", gamelog);

      for(int p=0;p<len(pool);p++) addjuice(*pool[p],200,1000);
   }
   gamelog.nextMessage();

   move(15,19);
   addstr("Cキーでリベラルを続ける。");

   while(getkey()!='c');
}



/* siege - "you are wanted for _______ and other crimes..." */
void statebrokenlaws(int loc)
{
   music.play(MUSIC_SIEGE);
   short breakercount[LAWFLAGNUM]={0};
   int typenum=0,criminalcount=0,kidnapped=0;
   char kname[100];

   for(int p=0;p<len(pool);p++)
   {
      if(!pool[p]->alive||pool[p]->location!=loc) continue;

      if(pool[p]->flag&CREATUREFLAG_KIDNAPPED)
      {
         strcpy(kname,pool[p]->propername);
         kidnapped++;
      }

      if(iscriminal(*pool[p])) criminalcount++;

      for(int i=0;i<LAWFLAGNUM;i++) if(pool[p]->crimes_suspected[i]) breakercount[i]++;
   }
   for(int i=0;i<LAWFLAGNUM;i++) if(breakercount[i]) typenum++;

   erase();

   set_color(COLOR_WHITE,COLOR_BLACK,1);
   move(1,1);
   if(location[loc]->siege.underattack) addstr("叫び声が聞こえる:", gamelog);
   else addstr("メガホンの怒鳴り声が聞こえる:", gamelog);
   gamelog.newline();

   move(3,1);
   if(location[loc]->siege.escalationstate>=2&&publicmood(-1)<20)
      addstr("神の御名において、お前たちのたくらみを終わらせる!", gamelog);
   else addstr("お前たちは包囲されている!", gamelog);
   gamelog.newline();

   move(4,1);

   //KIDNAP VICTIM
   if(kidnapped)
   {
      addstr(kname, gamelog);
      if(kidnapped>1) addstr("、その他", gamelog);
      addstr("を解放しろ!", gamelog);
   }
   //TREASON
   else if(breakercount[LAWFLAG_TREASON])
      addstr("国家反逆", gamelog);
   //TERRORISM
   else if(breakercount[LAWFLAG_TERRORISM])
      addstr("テロ", gamelog);
   //MURDERER
   else if(breakercount[LAWFLAG_MURDER])
      addstr("一級殺人", gamelog);
   //KIDNAPPER
   else if(breakercount[LAWFLAG_KIDNAPPING])
      addstr("誘拐", gamelog);
   //BANK ROBBER
   else if(breakercount[LAWFLAG_BANKROBBERY])
      addstr("銀行強盗", gamelog);
   //ARSONIST
   else if(breakercount[LAWFLAG_ARSON])
      addstr("放火", gamelog);
   //BURN FLAG
   else if(breakercount[LAWFLAG_BURNFLAG])
   {
      if(law[LAW_FLAGBURNING]==-2)addstr("国旗不敬", gamelog);
      else if(law[LAW_FLAGBURNING]==-1)addstr("国旗焼却罪", gamelog);
      else addstr("国旗焼却", gamelog);
   }
   //SPEECH
   else if(breakercount[LAWFLAG_SPEECH])
      addstr("扇動", gamelog);
   //BROWNIES
   else if(breakercount[LAWFLAG_BROWNIES])
      addstr("違法薬物取引", gamelog);
   //ESCAPED
   else if(breakercount[LAWFLAG_ESCAPED])
      addstr("脱獄", gamelog);
   //HELP ESCAPED
   else if(breakercount[LAWFLAG_HELPESCAPE])
      addstr("逃走援助", gamelog);
   //JURY
   else if(breakercount[LAWFLAG_JURY])
      addstr("陪審員買収", gamelog);
   //RACKETEERING
   else if(breakercount[LAWFLAG_RACKETEERING])
      addstr("詐欺", gamelog);
   //EXTORTION
   else if(breakercount[LAWFLAG_EXTORTION])
      addstr("恐喝", gamelog);
   //ASSAULT
   else if(breakercount[LAWFLAG_ARMEDASSAULT])
      addstr("傷害", gamelog);
   //ASSAULT
   else if(breakercount[LAWFLAG_ASSAULT])
      addstr("暴行", gamelog);
   //CAR THEFT
   else if(breakercount[LAWFLAG_CARTHEFT])
      addstr("自動車窃盗", gamelog);
   //CC FRAUD
   else if(breakercount[LAWFLAG_CCFRAUD])
      addstr("カード番号不正取得", gamelog);
   //THIEF
   else if(breakercount[LAWFLAG_THEFT])
      addstr("窃盗", gamelog);
   //PROSTITUTION
   else if(breakercount[LAWFLAG_PROSTITUTION])
      addstr("売春", gamelog);
   //HIRE ILLEGAL
   else if(breakercount[LAWFLAG_HIREILLEGAL])
      addstr((law[LAW_IMMIGRATION]<1?"不法移民雇用":"不法雇用"), gamelog);
   //GUN USE
   /*else if(breakercount[LAWFLAG_GUNUSE])
      addstr("違法な武器の使用", gamelog);
   //GUN CARRY
   else if(breakercount[LAWFLAG_GUNCARRY])
      addstr("違法な武器の運搬", gamelog);*/
   //COMMERCE
   else if(breakercount[LAWFLAG_COMMERCE])
      addstr("業務妨害", gamelog);
   //INFORMATION
   else if(breakercount[LAWFLAG_INFORMATION])
      addstr("情報システムへの違法アクセス", gamelog);
   //UNLAWFUL BURIAL
   else if(breakercount[LAWFLAG_BURIAL])
      addstr("死体遺棄", gamelog);
   //BREAKING
   else if(breakercount[LAWFLAG_BREAKING])
      addstr("不法侵入", gamelog);
   //VANDALISM
   else if(breakercount[LAWFLAG_VANDALISM])
      addstr("器物損壊", gamelog);
   //RESIST
   else if(breakercount[LAWFLAG_RESIST])
      addstr("逮捕抵抗", gamelog);
   //DISTURBANCE
   else if(breakercount[LAWFLAG_DISTURBANCE])
      addstr("治安妨害", gamelog);
   //PUBLIC NUDITY
   else if(breakercount[LAWFLAG_PUBLICNUDITY])
      addstr("公然猥褻", gamelog);
   //LOITERING
   else if(breakercount[LAWFLAG_LOITERING])
      addstr("浮浪", gamelog);
   //THEY WERE LOOKING FOR SOMEONE ELSE
   else addstr("正義に背く行為", gamelog);

   if(!kidnapped)
   {
      if(typenum>1) addstr("、その他の罪", gamelog);
      addstr("の容疑がある。", gamelog);
   }
   gamelog.nextMessage();

   getkey();
}


void statebrokenlaws(Creature & cr)
{
   bool kidnapped=(cr.flag&CREATUREFLAG_KIDNAPPED),criminal=false,breakercount[LAWFLAGNUM];

   for(int i=0;i<LAWFLAGNUM;i++)
      if(cr.crimes_suspected[i]) breakercount[i]=true,criminal=true;
      else breakercount[i]=false;

   if(!criminal&&!kidnapped) return;

   set_color(COLOR_YELLOW,COLOR_BLACK,1);

   //KIDNAP VICTIM
   if(kidnapped)
      addstr("リハビリ");
   //TREASON
   else if(breakercount[LAWFLAG_TREASON])
      addstr("国家反逆");
   //TERRORISM
   else if(breakercount[LAWFLAG_TERRORISM])
      addstr("テロ");
   //MURDERER
   else if(breakercount[LAWFLAG_MURDER])
      addstr("殺人");
   //KIDNAPPER
   else if(breakercount[LAWFLAG_KIDNAPPING])
      addstr("誘拐");
   //BANK ROBBER
   else if(breakercount[LAWFLAG_BANKROBBERY])
      addstr("銀行強盗");
   //ARSONIST
   else if(breakercount[LAWFLAG_BANKROBBERY])
      addstr("放火");
   //BURN FLAG
   else if(breakercount[LAWFLAG_BURNFLAG])
      addstr(law[LAW_FLAGBURNING]==-2?"国旗不敬":"国旗焼却");
   //SPEECH
   else if(breakercount[LAWFLAG_SPEECH])
      addstr("煽動");
   //BROWNIES
   else if(breakercount[LAWFLAG_BROWNIES])
      addstr("違法薬物取引");
   //ESCAPED
   else if(breakercount[LAWFLAG_ESCAPED])
      addstr("脱獄");
   //HELP ESCAPED
   else if(breakercount[LAWFLAG_HELPESCAPE])
      addstr("逃走援助");
   //JURY
   else if(breakercount[LAWFLAG_JURY])
      addstr("陪審員買収");
   //RACKETEERING
   else if(breakercount[LAWFLAG_RACKETEERING])
      addstr("詐欺");
   //EXTORTION
   else if(breakercount[LAWFLAG_EXTORTION])
      addstr("恐喝");
   //ASSAULT
   else if(breakercount[LAWFLAG_ARMEDASSAULT])
      addstr("傷害");
   //ASSAULT
   else if(breakercount[LAWFLAG_ASSAULT])
      addstr("暴行");
   //CAR THEFT
   else if(breakercount[LAWFLAG_CARTHEFT])
      addstr("自動車窃盗");
   //CC FRAUD
   else if(breakercount[LAWFLAG_CCFRAUD])
      addstr("カード番号不正取得");
   //THIEF
   else if(breakercount[LAWFLAG_THEFT])
      addstr("窃盗");
   //PROSTITUTION
   else if(breakercount[LAWFLAG_PROSTITUTION])
      addstr("売春");
   //HIRE ILLEGAL
   else if(breakercount[LAWFLAG_HIREILLEGAL])
      addstr(law[LAW_IMMIGRATION]<1?"不法移民雇用":"不法雇用");
   //GUN USE
   /*else if(breakercount[LAWFLAG_GUNUSE])
      addstr("FIRING ILLEGAL WEAPONS");
   //GUN CARRY
   else if(breakercount[LAWFLAG_GUNCARRY])
      addstr("CARRYING ILLEGAL WEAPONS");*/
   //COMMERCE
   else if(breakercount[LAWFLAG_COMMERCE])
      addstr("業務妨害");
   //INFORMATION
   else if(breakercount[LAWFLAG_INFORMATION])
      addstr("不法アクセス");
   //UNLAWFUL BURIAL
   else if(breakercount[LAWFLAG_BURIAL])
      addstr("死体遺棄");
   //BREAKING
   else if(breakercount[LAWFLAG_BREAKING])
      addstr("不法侵入");
   //VANDALISM
   else if(breakercount[LAWFLAG_VANDALISM])
      addstr("器物損壊");
   //RESIST
   else if(breakercount[LAWFLAG_RESIST])
      addstr("逮捕抵抗");
   //DISTURBANCE
   else if(breakercount[LAWFLAG_DISTURBANCE])
      addstr("治安妨害");
   //PUBLIC NUDITY
   else if(breakercount[LAWFLAG_PUBLICNUDITY])
      addstr("公然猥褻");
   //LOITERING
   else if(breakercount[LAWFLAG_LOITERING])
      addstr("浮浪");
   addstr("の容疑");
}
