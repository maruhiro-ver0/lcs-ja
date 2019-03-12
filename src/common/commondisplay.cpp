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

// Sets the text color to the thematic color for the given alignment
// extended_range forces colors to be set on a 5 point scale instead
// of just basic liberal-moderate-conservative
void set_alignment_color(signed char alignment, bool extended_range)
{
   switch(alignment)
   {
   case ALIGN_ARCHCONSERVATIVE:
      set_color(COLOR_RED,COLOR_BLACK,1);
      break;
   case ALIGN_CONSERVATIVE:
      if(extended_range)
         set_color(COLOR_MAGENTA,COLOR_BLACK,1);
      else set_color(COLOR_RED,COLOR_BLACK,1);
      break;
   case ALIGN_MODERATE:
      set_color(COLOR_YELLOW,COLOR_BLACK,1);
      break;
   case ALIGN_LIBERAL:
      if(extended_range)
         set_color(COLOR_CYAN,COLOR_BLACK,1);
      else set_color(COLOR_GREEN,COLOR_BLACK,1);
      break;
   case ALIGN_ELITELIBERAL:
      set_color(COLOR_GREEN,COLOR_BLACK,1);
      break;
   case ALIGN_STALINIST:
      set_color(COLOR_RED,COLOR_BLACK,1);
      break;
   default: // This should not happen! Set a strange color to indicate an error!
      set_color(COLOR_YELLOW,COLOR_RED,1,1); // blinking yellow on red background
      break;
   }
}


// Sets the text color per activity type
void set_activity_color(long activity_type)
{
   switch(activity_type)
   {
      // Liberal actvism
   case ACTIVITY_SLEEPER_LIBERAL:
   case ACTIVITY_TROUBLE:
   case ACTIVITY_GRAFFITI:
   case ACTIVITY_DOS_ATTACKS:
   case ACTIVITY_HACKING:
   case ACTIVITY_WRITE_LETTERS:
   case ACTIVITY_WRITE_GUARDIAN:
      set_color(COLOR_GREEN,COLOR_BLACK,1);
      break;

      // Recruitment
   case ACTIVITY_RECRUITING:
      set_color(COLOR_GREEN,COLOR_BLACK,0);
      break;

      // Less exciting liberal activities
   case ACTIVITY_SLEEPER_SPY:
   case ACTIVITY_COMMUNITYSERVICE:
   case ACTIVITY_POLLS:
      set_color(COLOR_BLUE,COLOR_BLACK,1);
      break;

      // Stealing things
   case ACTIVITY_SLEEPER_STEAL:
   case ACTIVITY_WHEELCHAIR:
   case ACTIVITY_STEALCARS:
      set_color(COLOR_CYAN,COLOR_BLACK,0);
      break;

      // Illegal fundraising
   case ACTIVITY_SLEEPER_EMBEZZLE:
   case ACTIVITY_SELL_DRUGS:
   case ACTIVITY_PROSTITUTION:
   case ACTIVITY_CCFRAUD:
   case ACTIVITY_DOS_RACKET:
      set_color(COLOR_RED,COLOR_BLACK,1);
      break;

      // Legal fundraising
   case ACTIVITY_DONATIONS:
   case ACTIVITY_SELL_TSHIRTS:
   case ACTIVITY_SELL_ART:
   case ACTIVITY_SELL_MUSIC:
      set_color(COLOR_CYAN,COLOR_BLACK,1);
      break;

      // Clothing/garment stuff
   case ACTIVITY_REPAIR_ARMOR:
   case ACTIVITY_MAKE_ARMOR:
      set_color(COLOR_CYAN,COLOR_BLACK,0);
      break;

      // Teaching
   case ACTIVITY_TEACH_POLITICS:
   case ACTIVITY_TEACH_FIGHTING:
   case ACTIVITY_TEACH_COVERT:
   //and studying
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
   case ACTIVITY_STUDY_MUSIC:
   case ACTIVITY_STUDY_TEACHING:
   case ACTIVITY_STUDY_WRITING:
   case ACTIVITY_STUDY_LOCKSMITHING:
      set_color(COLOR_MAGENTA,COLOR_BLACK,1);
      break;

      // Interrogating
   case ACTIVITY_HOSTAGETENDING:
      set_color(COLOR_YELLOW,COLOR_BLACK,1);
      break;

      // Dealing with your injuries
   case ACTIVITY_CLINIC:
      set_color(COLOR_RED,COLOR_BLACK,0);
      break;

      // Doing something Conservative
   case ACTIVITY_SLEEPER_CONSERVATIVE:
      set_color(COLOR_RED,COLOR_BLACK,1);
      break;

      // Dealing with the dead
   case ACTIVITY_BURY:
      set_color(COLOR_BLACK,COLOR_BLACK,1);
      break;

      // Nothing terribly important
   case ACTIVITY_HEAL: // Identical to none in practice
   case ACTIVITY_NONE:
      set_color(COLOR_WHITE,COLOR_BLACK,0);
      break;

      // Going somewhere
   case ACTIVITY_VISIT:
      set_color(COLOR_YELLOW,COLOR_BLACK,1);
      break;

      // Quitting being a sleeper to join the LCS
   case ACTIVITY_SLEEPER_JOINLCS:
      set_color(COLOR_RED,COLOR_BLACK,1);
      break;

   default: // This should not happen! Set a strange color to indicate an error!
      set_color(COLOR_YELLOW,COLOR_RED,1); // yellow on red background
      break;
   }
}

/* location and squad header */
void locheader()
{
   if(activesquad!=NULL && activesquad->squad[0]->location!=-1)
   {
      if(location[activesquad->squad[0]->location]->siege.siege)
      {
         if(location[activesquad->squad[0]->location]->siege.underattack)set_color(COLOR_RED,COLOR_BLACK,1);
         else set_color(COLOR_YELLOW,COLOR_BLACK,1);
      }
      else set_color(COLOR_WHITE,COLOR_BLACK,0);
   }
   else if(selectedsiege!=-1)
   {
      if(location[selectedsiege]->siege.siege)
      {
         if(location[selectedsiege]->siege.underattack)set_color(COLOR_RED,COLOR_BLACK,1);
         else set_color(COLOR_YELLOW,COLOR_BLACK,1);
      }
      else set_color(COLOR_WHITE,COLOR_BLACK,0);
   }
   else set_color(COLOR_WHITE,COLOR_BLACK,0);
   move(0,0);

   addstr(year);
   addstr("年 ");
   addstr(getmonth(month,true));
   addstr(" ");
   addstr(day);
   addstr("日 ");

   if(activesquad!=NULL && activesquad->squad[0]->location!=-1)
   {
      addstr(location[activesquad->squad[0]->location]->getname(false, true));
      addstr(" ");
   }
   else
   {
      if(selectedsiege==-1)
      {
         addstr("部隊なし");
         addstr(" ");
      }
      else
      {
         addstr(location[selectedsiege]->getname(false, true));
         addstr(" ");
      }
   }

   if(activesquad==NULL && selectedsiege==-1)
   {
      set_color(COLOR_BLACK,COLOR_BLACK,1);
      move(3,6);
      addstr("新しい部隊を編成する方法:");
      move(4,6);
      addstr("1) R - 配置の確認と部隊の編成");
      move(5,6);
      addstr("2) Zキーで新しい部隊を編成する");
      set_color(COLOR_WHITE,COLOR_BLACK,0);
   }

   printfunds();

   if(activesquad!=NULL)
   {
      std::string str=getactivity(activesquad->activity);
      set_activity_color(activesquad->activity.type);
      if(activesquad->activity.type==ACTIVITY_NONE)
      {
         bool haveact=false,multipleact=false;
         for(int p=0;p<6;p++)
         {
            if(activesquad->squad[p]==NULL) continue;
            const std::string str2=getactivity(activesquad->squad[p]->activity);
            set_activity_color(activesquad->squad[p]->activity.type);
            if(haveact&&str!=str2) multipleact=true;
            str=str2,haveact=true;
         }
         if(multipleact)
         {
            str="個別に活動";
            set_color(COLOR_WHITE,COLOR_BLACK,1);
         }
      }
      mvaddstr(0,41,str);
   }
}

/* party info at top of screen */
void printparty()
{
   Creature *party[6]={NULL,NULL,NULL,NULL,NULL,NULL};
   if(activesquad!=NULL)
      for(int p=0;p<6;p++)party[p]=activesquad->squad[p];

   set_color(COLOR_WHITE,COLOR_BLACK,0);

   for(int i=2;i<8;i++)
   {
      move(i,0);
      addstr("                                                                                "); // 80 spaces
   }

   if(party_status!=-1&&party[party_status]==NULL)party_status=-1;

   if(party_status!=-1)
   {
      printcreatureinfo(party[party_status]);

      set_color(COLOR_WHITE,COLOR_BLACK,1);
      move(1,0);
      addstr(party_status+1);
   }
   else
   {
      char str[200];

      move(1,0);
      addstr("#-コードネーム---------スキル--武器-----------防具-----------健康-----移動手段--"); // 80 characters

      for(int p=0;p<6;p++)
      {
         set_color(COLOR_WHITE,COLOR_BLACK,0);
         move(p+2,0);
         addstr("                                                                                "); // 80 spaces
         mvaddchar(p+2,0,'1'+p);

         if(party[p]!=NULL)
         {
            if(party[p]->prisoner!=NULL)set_color(COLOR_MAGENTA,COLOR_BLACK,1);
            else set_color(COLOR_WHITE,COLOR_BLACK,0);
            move(p+2,2);
            addstr(to_half(party[p]->name));
            if(party[p]->prisoner!=NULL)addstr("+H");

            int skill=0;
            char bright=0;
            for(int sk=0;sk<SKILLNUM;sk++)
            {
               skill+=(int)party[p]->get_skill(sk);
               if(party[p]->get_skill_ip(sk)>=100+(10*party[p]->get_skill(sk))&&
                  party[p]->get_skill(sk)<party[p]->skill_cap(sk,true))bright=1;
            }

            set_color(COLOR_WHITE,COLOR_BLACK,bright);
            move(p+2,23);
            addstr(skill);
            addstr("/");
            int wsk = SKILL_HANDTOHAND;
            if(party[p]->get_weapon().has_musical_attack())
               wsk=SKILL_MUSIC;
            else if (party[p]->has_thrown_weapon && len(party[p]->extra_throwing_weapons))
               wsk=party[p]->extra_throwing_weapons[0]->get_attack(false,false,false)->skill;
            else wsk=party[p]->get_weapon().get_attack(false,false,false)->skill;
            addstr(party[p]->get_skill(wsk));

            move(p+2,31);
            if(mode!=GAMEMODE_SITE)set_color(COLOR_WHITE,COLOR_BLACK,0);
            else switch(weaponcheck(*party[p]))
            {
               case -1:
               case 0:set_color(COLOR_GREEN,COLOR_BLACK,1);break;
               case 1:set_color(COLOR_YELLOW,COLOR_BLACK,1);break;
               case 2:set_color(COLOR_RED,COLOR_BLACK,1);break;
            }
            if(party[p]->has_thrown_weapon && len(party[p]->extra_throwing_weapons))
               addstr(party[p]->extra_throwing_weapons[0]->get_shortname(0));
            else addstr(party[p]->get_weapon().get_shortname(0));
            //set_color(COLOR_WHITE,COLOR_BLACK,0);
            if(party[p]->get_weapon().get_ammoamount()>0)
            {
               //set_color(COLOR_WHITE,COLOR_BLACK,0);
               addstr(" (");
               addstr(party[p]->get_weapon().get_ammoamount());
               addstr(")");
            }
            else if(party[p]->get_weapon().uses_ammo())
            {
               set_color(COLOR_BLACK,COLOR_BLACK,1);
               if(len(party[p]->clips))
               {
                  addstr(" (");
                  addstr(party[p]->count_clips());
                  addstr(")");
               }
               else
                  addstr(" (XX)");
            }
            else if(party[p]->get_weapon().is_throwable() && !party[p]->has_thrown_weapon)
               addstr(" (1)");
            else if(party[p]->has_thrown_weapon && len(party[p]->extra_throwing_weapons))
            {
               set_color(COLOR_BLACK,COLOR_BLACK,1);
               addstr(" (");
               addstr(party[p]->count_weapons()-party[p]->is_armed());
               addstr(")");
            }

            if(mode!=GAMEMODE_SITE)
            {
               int fg = COLOR_WHITE;
               int bg = COLOR_BLACK;
               int in = 1;
               if(party[p]->get_armor().is_bloody())
                  {bg = COLOR_RED;  in = 1;}
               if(party[p]->get_armor().get_quality() > party[p]->get_armor().get_quality_levels())
                  {fg = COLOR_BLACK;}
               else if(party[p]->get_armor().is_damaged())
                  {fg = COLOR_YELLOW; in = 1;}
               else if(party[p]->get_armor().get_quality() >1)
                  {fg = COLOR_YELLOW; in = (bg==COLOR_RED);}
               if (fg == COLOR_WHITE && bg == COLOR_BLACK)
                  in = 0;
               set_color(fg,bg,in);
            }
            else
            {
               switch(hasdisguise(*party[p]))
               {
               case 1:set_color(COLOR_GREEN,COLOR_BLACK,1);break;
               case 2:set_color(COLOR_YELLOW,COLOR_BLACK,1);break;
               default:
                  if(party[p]->get_armor().get_stealth_value() > 1)
                     set_color(COLOR_BLACK,COLOR_BLACK,1);
                  else set_color(COLOR_RED,COLOR_BLACK,1);
                  break;
               }
               if(sitealarmtimer>=0 || sitealarm==1)
                  if(party[p]->get_armor().get_stealth_value() > 1)
                     set_color(COLOR_BLACK,COLOR_BLACK,1);
            }
            mvaddstr(p+2,46,party[p]->get_armor().get_shortname());

            printhealthstat(*party[p],p+2,61,TRUE);

            set_color(COLOR_WHITE,COLOR_BLACK,0);
            move(p+2,70);

            long v=-1;
            if(showcarprefs==1)v=id_getcar(party[p]->pref_carid);
            else v=id_getcar(party[p]->carid);
            if(v!=-1&&showcarprefs!=-1)
            {
               strcpy(str,vehicle[v]->shortname());
               if(showcarprefs==1?party[p]->pref_is_driver:party[p]->is_driver)strcat(str,"-D");
            }
            else
            {
               int legok=2;
               if((party[p]->wound[BODYPART_LEG_RIGHT] & WOUND_NASTYOFF)||
                  (party[p]->wound[BODYPART_LEG_RIGHT] & WOUND_CLEANOFF))legok--;
               if((party[p]->wound[BODYPART_LEG_LEFT] & WOUND_NASTYOFF)||
                  (party[p]->wound[BODYPART_LEG_LEFT] & WOUND_CLEANOFF))legok--;
               if(party[p]->flag & CREATUREFLAG_WHEELCHAIR)strcpy(str,"車椅子");
               else if(legok>=1)strcpy(str,"徒歩");
               else strcpy(str,"歩行不能");
            }
            addstr(str);
         }
      }
   }

   makedelimiter();
}


/* location info at top of screen */
void printlocation(long loc)
{
   if(location[loc]->siege.siege)
   {
      if(!location[loc]->siege.underattack)
      {
         set_color(COLOR_YELLOW,COLOR_BLACK,1);
         mvaddstr(2,1,"ここは警官隊に包囲されている。");
      }
      else
      {
         set_color(COLOR_RED,COLOR_BLACK,1);
         switch(location[loc]->siege.siegetype)
         {
         case SIEGE_POLICE:
            mvaddstr(2,1,"警官隊がこの場所を攻撃中だ!");break;
         case SIEGE_CIA:
            mvaddstr(2,1,"CIAがこの場所を攻撃中だ!");break;
         case SIEGE_HICKS:
            mvaddstr(2,1,"群集がこの場所を攻撃中だ!");break;
         case SIEGE_CORPORATE:
            mvaddstr(2,1,"企業がこの場所を攻撃中だ!");break;
         case SIEGE_CCS:
            mvaddstr(2,1,"CCSがこの場所を攻撃中だ!");break;
         case SIEGE_FIREMEN:
            mvaddstr(2,1,"焚書課がこの場所を攻撃中だ!");break;
         }
      }
   }
   else
   {
      set_color(COLOR_WHITE,COLOR_BLACK,0);
      mvaddstr(2,1,"包囲されていない… 今は。");
   }

   if(location[loc]->can_be_upgraded())
   {
      if(numbereating(loc)>0)
      {
         if(fooddaysleft(loc))
         {
            if(fooddaysleft(loc)<4)
            {
               if(!location[loc]->siege.siege)set_color(COLOR_WHITE,COLOR_BLACK,0);
               else set_color(COLOR_YELLOW,COLOR_BLACK,1);
               mvaddstr(3,1,"ここには数日分の食料しかない。");
            }
         }
         else
         {
            if(!location[loc]->siege.siege)set_color(COLOR_WHITE,COLOR_BLACK,0);
            else set_color(COLOR_RED,COLOR_BLACK,1);
            mvaddstr(3,1,"ここには十分な食料がない。");
         }
      }

      if(location[loc]->compound_walls & COMPOUND_BASIC)
      {
         set_color(COLOR_WHITE,COLOR_BLACK,1);
         mvaddstr(4,1,"要塞化");
      }

      if(location[loc]->compound_walls & COMPOUND_PRINTINGPRESS)
      {
         set_color(COLOR_BLUE,COLOR_BLACK,1);
         mvaddstr(4,31,"印刷機");
      }

      if(location[loc]->front_business!=-1)
      {
         set_color(COLOR_MAGENTA,COLOR_BLACK,1);
         mvaddstr(4,54,"ビジネス・オフィス");
      }

      if(location[loc]->compound_walls & COMPOUND_CAMERAS)
      {
         if(location[loc]->siege.siege&&location[loc]->siege.cameras_off)
         {
            set_color(COLOR_RED,COLOR_BLACK,0);
            mvaddstr(5,1,"カメラ OFF");
         }
         else
         {
            set_color(COLOR_GREEN,COLOR_BLACK,1);
            mvaddstr(5,1,"カメラ ON");
         }
      }

      if(location[loc]->compound_walls & COMPOUND_TRAPS)
      {
         set_color(COLOR_RED,COLOR_BLACK,1);
         mvaddstr(5,16,"ブービートラップ");
      }

      if(location[loc]->compound_walls & COMPOUND_AAGUN)
      {
         set_color(COLOR_CYAN,COLOR_BLACK,1);
         mvaddstr(5,33,"対空砲");
      }

      if(location[loc]->compound_walls & COMPOUND_TANKTRAPS)
      {
         set_color(COLOR_YELLOW,COLOR_BLACK,1);
         mvaddstr(5,46,"対戦車障害物");
      }

      if(location[loc]->siege.siege&&location[loc]->siege.lights_off)
      {
         set_color(COLOR_WHITE,COLOR_BLACK,0);
         mvaddstr(5,60,"消灯");
      }
      else if(location[loc]->compound_walls & COMPOUND_GENERATOR)
      {
         set_color(COLOR_WHITE,COLOR_BLACK,1);
         mvaddstr(5,61,"発電機");
      }

      int eaters=numbereating(loc),days=fooddaysleft(loc);

      if(eaters>0)
      {
         if(days>=1)
         {
            set_color(COLOR_WHITE,COLOR_BLACK,0);
            mvaddstr(6,50,days);
            addstr("食分の食料");
         }
         else if(days==0)
         {
            set_color(COLOR_RED,COLOR_BLACK,0);
            mvaddstr(6,50,"十分な食料がない");
         }
      }
      set_color(COLOR_WHITE,COLOR_BLACK,0);
      mvaddstr(6,1,location[loc]->compound_stores);
      addstr("日/人分の食料");
      if(location[loc]->compound_stores!=1)addstr("");

      set_color(COLOR_WHITE,COLOR_BLACK,0);
      mvaddstr(6,30,eaters);
      addstr("人");
   }
}


/* character info at top of screen */
void printcreatureinfo(Creature *cr, unsigned char knowledge)
{
   char str[200];

   makedelimiter(1);

   set_color(COLOR_WHITE,COLOR_BLACK,0);
   mvaddstr(1,2,cr->name);
   addstr("、");
   addstr(gettitle(*cr));

   if(cr->prisoner!=NULL)
   {
      addstr("、");
      switch(cr->prisoner->type)
      {
      case CREATURE_POLITICIAN:addstr("罵る政治家");break;
      case CREATURE_CORPORATE_CEO:addstr("身悶えするCEO");break;
      case CREATURE_RADIOPERSONALITY:addstr("泣き叫ぶラジオ・パーソナリティ");break;
      case CREATURE_NEWSANCHOR:addstr("ごますりニュースキャスター");break;
      case CREATURE_SCIENTIST_EMINENT:addstr("怯える高名な科学者");break;
      case CREATURE_JUDGE_CONSERVATIVE:addstr("怒れる首吊り判事");break;
      default:
         addstr(cr->prisoner->name);
         break;
      }
      addstr("を連れている");
   }

   mvaddstr(2,0,"心:     ");
   if(knowledge>0)
      addstr(cr->get_attribute(ATTRIBUTE_HEART,true));
   else addstr("?");
   mvaddstr(3,0,"知識:   ");
   if(knowledge>0)
      addstr(cr->get_attribute(ATTRIBUTE_INTELLIGENCE,true));
   else addstr("?");
   mvaddstr(4,0,"知恵:   ");
   if(knowledge>0)
      addstr(cr->get_attribute(ATTRIBUTE_WISDOM,true));
   else addstr("?");
   mvaddstr(5,0,"体力:   ");
   if(knowledge>1)
      addstr(cr->get_attribute(ATTRIBUTE_HEALTH,true));
   else addstr("?");
   mvaddstr(2,11,"敏捷性: ");
   if(knowledge>1)
      addstr(cr->get_attribute(ATTRIBUTE_AGILITY,true));
   else addstr("?");
   mvaddstr(3,11,"腕力:   ");
   if(knowledge>1)
      addstr(cr->get_attribute(ATTRIBUTE_STRENGTH,true));
   else addstr("?");
   mvaddstr(4,11,"魅力:   ");
   if(knowledge>0)
      addstr(cr->get_attribute(ATTRIBUTE_CHARISMA,true));
   else addstr("?");
   mvaddstr(5,11,"移動:   ");
   long v=-1;
   if(showcarprefs==1)v=id_getcar(cr->pref_carid);
   else v=id_getcar(cr->carid);
   if(v!=-1&&showcarprefs!=-1)
   {
      strcpy(str,vehicle[v]->shortname());
      char d;
      if(showcarprefs==1)d=cr->pref_is_driver;
      else d=cr->is_driver;
      if(d)strcat(str,"-D");
   }
   else
   {
      int legok=2;
      if((cr->wound[BODYPART_LEG_RIGHT] & WOUND_NASTYOFF)||
         (cr->wound[BODYPART_LEG_RIGHT] & WOUND_CLEANOFF))legok--;
      if((cr->wound[BODYPART_LEG_LEFT] & WOUND_NASTYOFF)||
         (cr->wound[BODYPART_LEG_LEFT] & WOUND_CLEANOFF))legok--;
      if(cr->flag & CREATUREFLAG_WHEELCHAIR)strcpy(str,"車椅子");
      else if(legok>=1)strcpy(str,"徒歩");
      else strcpy(str,"歩行不能");
   }
   addstr(str);
   move(6,0);
   if(mode!=GAMEMODE_SITE) set_color(COLOR_WHITE,COLOR_BLACK,0);
   else switch(weaponcheck(*cr))
   {
      case -1:
      case 0:set_color(COLOR_GREEN,COLOR_BLACK,1);break;
      case 1:set_color(COLOR_YELLOW,COLOR_BLACK,1);break;
      case 2:set_color(COLOR_RED,COLOR_BLACK,1);break;
   }
   addstr("武器:   ");
   addstr(cr->get_weapon_string(1));


   move(7,0);
   if(mode!=GAMEMODE_SITE)
   {
      int fg = COLOR_WHITE;
      int bg = COLOR_BLACK;
      int in = 1;
      if(cr->get_armor().is_bloody())
         {bg = COLOR_RED;  in = 0;}
      if(cr->get_armor().get_quality() > cr->get_armor().get_quality_levels())
         {fg = COLOR_BLACK;}
      else if(cr->get_armor().is_damaged())
         {fg = COLOR_YELLOW; in = 1;}
      else if(cr->get_armor().get_quality() >1)
         {fg = COLOR_YELLOW; in = (bg==COLOR_RED);}
      if (fg == COLOR_WHITE && bg == COLOR_BLACK)
         in = 0;
      set_color(fg,bg,in);
   }
   else
   {
      switch(hasdisguise(*cr))
      {
      case 1:set_color(COLOR_GREEN,COLOR_BLACK,1);break;
      case 2:set_color(COLOR_YELLOW,COLOR_BLACK,1);break;
      default:
         if(cr->get_armor().get_stealth_value() > 1)
            set_color(COLOR_BLACK,COLOR_BLACK,1);
         else set_color(COLOR_RED,COLOR_BLACK,1);
      }
      if(sitealarmtimer>=0 || sitealarm==1)
         if(cr->get_armor().get_stealth_value() > 1)
            set_color(COLOR_BLACK,COLOR_BLACK,1);
   }
   addstr("服装:   ");
   addstr(cr->get_armor_string(false));

   set_color(COLOR_WHITE,COLOR_BLACK,0);

   char used[SKILLNUM];
   memset(used,0,sizeof(char)*SKILLNUM);

   int snum=5;
   char printed=1;

   while(snum>0&&printed)
   {
      printed=0;

      int max=0;
      long maxs=-1;
      for(int s=0;s<SKILLNUM;s++)
      {
         if((cr->get_skill(s)*10000+cr->get_skill_ip(s))>max && !used[s])
         {
            max=(cr->get_skill(s)*10000+cr->get_skill_ip(s));
            maxs=s;
         }
      }

      if(maxs!=-1)
      {
         used[maxs]=1;
         printed=1;

         // Maxed skills are cyan
         if(cr->skill_cap(maxs,true)!=0 && cr->get_skill(maxs)>=cr->skill_cap(maxs,true))set_color(COLOR_CYAN,COLOR_BLACK,1);
         // About to level up skills are white
         else if(cr->get_skill_ip(maxs)>=100+(10*cr->get_skill(maxs))&&
            cr->get_skill(maxs)<cr->skill_cap(maxs,true))set_color(COLOR_WHITE,COLOR_BLACK,1);
         // <1 skills are dark gray
         else if(cr->get_skill(maxs)<1)set_color(COLOR_BLACK,COLOR_BLACK,1);
         // >=1 skills are light gray
         else set_color(COLOR_WHITE,COLOR_BLACK,0);

         move(3+5-snum,31);
         if(knowledge>5-snum)
            addstr(Skill::get_name(maxs));
         else addstr("???????");
         addstr(": ");
         if(knowledge>7-snum)
            addstr(cr->get_skill(maxs));
         else addchar('?');

         if(snum==5&&printed)
         {
            set_color(COLOR_WHITE,COLOR_BLACK,0);
            move(2,31);
            addstr("特技:");
         }
      }

      snum--;
   }

   int woundsum=0;
   for(int w=0;w<BODYPARTNUM;w++)
      if(cr->wound[w]!=0)woundsum++;

   printhealthstat(*cr,1,49,FALSE);

   if(woundsum>0)
   {
      for(int w=0;w<BODYPARTNUM;w++)
      {
         if(cr->wound[w] & WOUND_BLEEDING)set_color(COLOR_RED,COLOR_BLACK,1);
         else set_color(COLOR_WHITE,COLOR_BLACK,0);

         move(2+w,49);
         switch(w)
         {
         case BODYPART_HEAD:addstr("頭部:");break;
         case BODYPART_BODY:addstr("胴:");break;
         case BODYPART_ARM_RIGHT:addstr(cr->animalgloss==ANIMALGLOSS_NONE?"右腕:":"右前足:");break;
         case BODYPART_ARM_LEFT:addstr(cr->animalgloss==ANIMALGLOSS_NONE?"左腕:":"左前足:");break;
         case BODYPART_LEG_RIGHT:addstr(cr->animalgloss==ANIMALGLOSS_NONE?"右足:":"右後足:");break;
         case BODYPART_LEG_LEFT:addstr(cr->animalgloss==ANIMALGLOSS_NONE?"左足:":"左後足:");break;
         }

         move(2+w,61);
         if(cr->wound[w] & WOUND_NASTYOFF)addstr("損壊");
         else if(cr->wound[w] & WOUND_CLEANOFF)addstr("切除");
         else
         {
            int sum=0;

            if(cr->wound[w] & WOUND_SHOT)sum++;
            if(cr->wound[w] & WOUND_CUT)sum++;
            if(cr->wound[w] & WOUND_BRUISED)sum++;
            if(cr->wound[w] & WOUND_BURNED)sum++;
            if(cr->wound[w] & WOUND_TORN)sum++;

            if(sum==0)
            {
               set_color(COLOR_GREEN,COLOR_BLACK,1);
               if(cr->animalgloss==ANIMALGLOSS_ANIMAL)
                  addstr("動物");
               else addstr("リベラル");
            }

            if(cr->wound[w] & WOUND_SHOT){addstr("撃 ");sum--;if(sum>0)addstr(",");}
            if(cr->wound[w] & WOUND_BRUISED){addstr("打 ");sum--;if(sum>0)addstr(",");}
            if(cr->wound[w] & WOUND_CUT){addstr("切 ");sum--;if(sum>0)addstr(",");}
            if(cr->wound[w] & WOUND_TORN){addstr("裂 ");sum--;if(sum>0)addstr(",");}
            if(cr->wound[w] & WOUND_BURNED){addstr("火 ");sum--;if(sum>0)addstr(",");}
         }
      }
      set_color(COLOR_WHITE,COLOR_BLACK,0);
   }
}


/* full character sheet (with surrounding interface) */
void fullstatus(int p)
{
   if(activesquad==NULL)return;

   const int pagenum=3;
   int page=0;

   while(true)
   {
      clear();

      set_color(COLOR_GREEN,COLOR_BLACK,1);
      move(0,0);
      addstr("リベラルのプロフィール");

      if(page==0) printliberalstats(*activesquad->squad[p]);
      else if(page==1) printliberalskills(*activesquad->squad[p]);
      else if(page==2) printliberalcrimes(*activesquad->squad[p]);

      move(23,0);
      addstr("N - コードネーム変更      G - 性別のラベルを変更");
      if(activesquad->squad[1]!=NULL)
         addstr("    ←/→ - 他のリベラルを見る");
      move(24,0);
      addstr("何かキーを押すと闘争を続ける");
      addstr("                        ↑/↓ - 詳細");

      int c=getkey();

      if(activesquad->squad[1]!=NULL&&((c==KEY_LEFT)||(c==KEY_RIGHT)))
      {
         int sx=(c==KEY_LEFT)?-1:1;
         do p=(p+6+sx)%6; while(activesquad->squad[p]==NULL);
      }
      else if(c==KEY_DOWN)
      {
         page++;
         page%=pagenum;
      }
      else if(c==KEY_UP)
      {
         page--;
         if(page<0) page=pagenum-1;
         page%=pagenum;
      }
      else if(c=='n')
      {
         set_color(COLOR_WHITE,COLOR_BLACK,0);
         mvaddstr(23,0,"新しいコードネームは何か?                                                       "); // 80 characters
         mvaddstr(24,0,"                                                                                "); // 80 spaces

         enter_name(24,0,activesquad->squad[p]->name,CREATURE_NAMELEN,activesquad->squad[p]->propername);
      }
      else if(c=='g')
      {
         activesquad->squad[p]->gender_liberal++;
         if(activesquad->squad[p]->gender_liberal>2)
            activesquad->squad[p]->gender_liberal=0;
      }
      else break;
   }
}


/* Full screen character sheet, skills only edition */
void printliberalskills(Creature &cr)
{
   // Add name
   set_color(COLOR_WHITE,COLOR_BLACK,0);
   move(2,0);
   if(strcmp(cr.propername,cr.name)!=0)
      addstr("コードネーム: ");
   else addstr("氏名: ");
   set_color(COLOR_WHITE,COLOR_BLACK,1);
   addstr(cr.name);
   set_color(COLOR_WHITE,COLOR_BLACK,0);
   addstr("、");
   addstr(gettitle(cr));
   addstr(" (");
   addstr(cr.get_type_name());
   addstr(")");

   // Add all skills
   for(int s=0;s<SKILLNUM;s++)
   {
      if(s%3==0 && s<9)
      {
         set_color(COLOR_WHITE,COLOR_BLACK,0);
         move(4,27*(s/3));
         addstr("スキル");
         move(4,15+27*(s/3));
         addstr("現在  最大");
      }

      // Maxed skills are cyan
      if(cr.skill_cap(s,true)!=0 && cr.get_skill(s)>=cr.skill_cap(s,true))set_color(COLOR_CYAN,COLOR_BLACK,1);
      // About to level up skills are white
      else if(cr.get_skill_ip(s)>=100+(10*cr.get_skill(s))&&
         cr.get_skill(s)<cr.skill_cap(s,true))set_color(COLOR_WHITE,COLOR_BLACK,1);
      // <1 skills are dark gray
      else if(cr.get_skill(s)<1)set_color(COLOR_BLACK,COLOR_BLACK,1);
      // >=1 skills are light gray
      else set_color(COLOR_WHITE,COLOR_BLACK,0);

      move(5+s/3,27*(s%3));
      addstr(Skill::get_name(s));
      addstr(": ");
      move(5+s/3,14+27*(s%3));
      addstr_f("%2d.",cr.get_skill(s));
      if(cr.get_skill_ip(s)<100+(10*cr.get_skill(s)))
      {
         if((cr.get_skill_ip(s)*100)/(100+(10*cr.get_skill(s)))!=0)
         {
            if((cr.get_skill_ip(s)*100)/(100+(10*cr.get_skill(s)))<10)
               addstr("0");
            addstr((cr.get_skill_ip(s)*100)/(100+(10*cr.get_skill(s))));
         }
         else addstr("00");
      }
      else addstr("99+");

      if(cr.skill_cap(s,true)==0 || cr.get_skill(s)<cr.skill_cap(s,true))
         set_color(COLOR_BLACK,COLOR_BLACK,1);
      move(5+s/3,20+27*(s%3));
      addstr_f("%2d.00",cr.skill_cap(s,true));
   }
   set_color(COLOR_WHITE,COLOR_BLACK,0);
}


/* full screen character sheet */
void printliberalstats(Creature &cr)
{
   set_color(COLOR_WHITE,COLOR_BLACK,0);

   // Add name
   move(2,0);
   addstr("氏名: ");
   set_color(COLOR_WHITE,COLOR_BLACK,1);
   addstr(cr.name);
   set_color(COLOR_WHITE,COLOR_BLACK,0);
   if(strcmp(cr.propername,cr.name)!=0)
   {
      //The names do not match, print real name as well
      addstr(" (");
      addstr(cr.propername);
      addstr(")");
   }
   addstr("、");
   addstr(gettitle(cr));
   addstr(" (");
   addstr(cr.get_type_name());
   addstr(")");
   move(3,0);

   // Add birthdate
   if(cr.birthday_month < month ||
      (cr.birthday_month == month && cr.birthday_day <= day))
      addstr(year-cr.age);
   else addstr(year-1-cr.age);
   addstr("年");
   addstr(getmonth(cr.birthday_month));
   addstr(cr.birthday_day);
   addstr("日生まれ");
   // Add age
   addstr(" (");
   addstr(cr.age);
   addstr("歳、");
   // Assess their gender in an Elite Liberal way
   if(cr.gender_liberal == GENDER_MALE)
      addstr(cr.animalgloss==ANIMALGLOSS_NONE?"男性":"オス");
   else if(cr.gender_liberal == GENDER_FEMALE)
      addstr(cr.animalgloss==ANIMALGLOSS_NONE?"女性":"メス");
   else addstr("クィア");
   // DON'T Note if there's some conflict with Conservative society's perceptions
   //if(cr.gender_liberal != cr.gender_conservative && cr.gender_liberal != GENDER_NEUTRAL)
   //   addstr("*");
   addstr(")");

   move(3,46);
   statebrokenlaws(cr);
   set_color(COLOR_WHITE,COLOR_BLACK,0);

   // Add juice
   move(10,12);
   addstr("ジュース: ");
   addstr(cr.juice);
   if(cr.juice<1000)
   {
      move(11,12);addstr("次:       ");
      if(cr.juice<0)addstr("0");
      else if(cr.juice<10)addstr("10");
      else if(cr.juice<50)addstr("50");
      else if(cr.juice<100)addstr("100");
      else if(cr.juice<200)addstr("200");
      else if(cr.juice<500)addstr("500");
      else addstr("1000");
   }
   // Add attributes
   move(5,0);addstr("心:     ");
   addstr(cr.get_attribute(ATTRIBUTE_HEART,true));
   move(6,0);addstr("知識:   ");
   addstr(cr.get_attribute(ATTRIBUTE_INTELLIGENCE,true));
   move(7,0);addstr("知恵:   ");
   addstr(cr.get_attribute(ATTRIBUTE_WISDOM,true));
   move(8,0);addstr("体力:   ");
   addstr(cr.get_attribute(ATTRIBUTE_HEALTH,true));
   move(9,0);addstr("敏捷性: ");
   addstr(cr.get_attribute(ATTRIBUTE_AGILITY,true));
   move(10,0);addstr("腕力:   ");
   addstr(cr.get_attribute(ATTRIBUTE_STRENGTH,true));
   move(11,0);addstr("魅力:   ");
   addstr(cr.get_attribute(ATTRIBUTE_CHARISMA,true));

   // Add highest skills
   char used[SKILLNUM];
   memset(used,0,sizeof(char)*SKILLNUM);

   int skills_max=16;
   char printed=1;

   move(5,28);
   addstr("スキル");
   move(5,43);
   addstr("現在  最大");
   for(int skills_shown=0;skills_shown<skills_max&&printed;skills_shown++)
   {
      printed=0;

      int max=0;
      long maxs=-1;
      for(int s=0;s<SKILLNUM;s++)
      {
         if((cr.get_skill(s)*10000+cr.get_skill_ip(s))>max && !used[s])
         {
            max=(cr.get_skill(s)*10000+cr.get_skill_ip(s));
            maxs=s;
         }
      }

      if(maxs!=-1)
      {
         used[maxs]=1;
         printed=1;

         // Maxed skills are cyan
         if(cr.skill_cap(maxs,true)!=0 && cr.get_skill(maxs)>=cr.skill_cap(maxs,true))set_color(COLOR_CYAN,COLOR_BLACK,1);
         // About to level up skills are white
         else if(cr.get_skill_ip(maxs)>=100+(10*cr.get_skill(maxs))&&
            cr.get_skill(maxs)<cr.skill_cap(maxs,true))set_color(COLOR_WHITE,COLOR_BLACK,1);
         // <1 skills are dark gray
         else if(cr.get_skill(maxs)<1)set_color(COLOR_BLACK,COLOR_BLACK,1);
         // >=1 skills are light gray
         else set_color(COLOR_WHITE,COLOR_BLACK,0);

         move(6+skills_shown,28);
         addstr(Skill::get_name(maxs));
         addstr(": ");
         move(6+skills_shown,42);
         addstr_f("%2d.",cr.get_skill(maxs));
         if(cr.get_skill_ip(maxs)<100+(10*cr.get_skill(maxs)))
         {
            if((cr.get_skill_ip(maxs)*100)/(100+(10*cr.get_skill(maxs)))!=0)
            {
               if((cr.get_skill_ip(maxs)*100)/(100+(10*cr.get_skill(maxs)))<10)
                  addchar('0');
               addstr((cr.get_skill_ip(maxs)*100)/(100+(10*cr.get_skill(maxs))));
            }
            else addstr("00");
         }
         else addstr("99+");

         if(cr.skill_cap(maxs,true)==0 || cr.get_skill(maxs)<cr.skill_cap(maxs,true))
            set_color(COLOR_BLACK,COLOR_BLACK,1);
         move(6+skills_shown,48);
         addstr_f("%2d.00",cr.skill_cap(maxs,true));
      }
   }

   set_color(COLOR_WHITE,COLOR_BLACK,0);

   // Add weapon
   move(13,0);
   addstr("武器:   ");
   addstr(cr.get_weapon_string(0));

   // Add clothing
   move(14,0);
   addstr("服装:   ");
   addstr(cr.get_armor_string(true));


   // Add vehicle
   move(15,0);
   addstr("自動車: ");
   long v=-1;
   if(showcarprefs==1)v=id_getcar(cr.pref_carid);
   else v=id_getcar(cr.carid);
   if(v!=-1&&showcarprefs!=-1)
   {
      addstr(vehicle[v]->shortname());
      char d;
      if(showcarprefs==1)d=cr.pref_is_driver;
      else d=cr.is_driver;
      if(d)addstr("-D");
   }
   else
   {
      int legok=2;
      if((cr.wound[BODYPART_LEG_RIGHT] & WOUND_NASTYOFF)||
         (cr.wound[BODYPART_LEG_RIGHT] & WOUND_CLEANOFF))legok--;
      if((cr.wound[BODYPART_LEG_LEFT] & WOUND_NASTYOFF)||
         (cr.wound[BODYPART_LEG_LEFT] & WOUND_CLEANOFF))legok--;
      if(cr.flag & CREATUREFLAG_WHEELCHAIR)addstr("車椅子");
      else if(legok>=1)addstr("徒歩");
      else addstr("歩行不能");
   }

   // Add recruit stats
   if(cr.flag!=CREATUREFLAG_BRAINWASHED)
   {
      move(18,0);
      addstr("スカウト ");
      addstr(maxsubordinates(cr)-subordinatesleft(cr));
      addstr("人 / 最大 ");
      addstr(maxsubordinates(cr));
      addstr("人 ");
   }
   else
   {
      move(18,0);
      addstr("啓蒙された者は");
      addstr("スカウトできない");
   }
   // Any meetings with potential recruits scheduled?
   if(scheduledmeetings(cr))
   {
      move(18,55);
      addstr("面会の約束: ");
      addstr(scheduledmeetings(cr));
      addstr("人");
   }
   // Add seduction stats
   move(19,0);
   int lovers = loveslaves(cr);
   if(cr.flag & CREATUREFLAG_LOVESLAVE)
      lovers++;
   if(lovers)
   {
      addstr(lovers);
      addstr("人の愛人");
      if(lovers>1)addstr("");
   }
   // Any dates with potential love interests scheduled?
   if(scheduleddates(cr))
   {
      move(19,55);
      addstr("デートの約束: ");
      addstr(scheduleddates(cr));
      addstr("人");
   }

   // Add wound status
   for(int w=0;w<BODYPARTNUM;w++)
   {
      if(cr.wound[w] & WOUND_BLEEDING)set_color(COLOR_RED,COLOR_BLACK,1);
      else set_color(COLOR_WHITE,COLOR_BLACK,0);

      move(5+w,55);
      switch(w)
      {
      case BODYPART_HEAD:addstr("頭部:");break;
      case BODYPART_BODY:addstr("胴体:");break;
      case BODYPART_ARM_RIGHT:addstr(cr.animalgloss==ANIMALGLOSS_NONE?"右腕:":"右前足:");break;
      case BODYPART_ARM_LEFT:addstr(cr.animalgloss==ANIMALGLOSS_NONE?"左腕:":"左前足:");break;
      case BODYPART_LEG_RIGHT:addstr(cr.animalgloss==ANIMALGLOSS_NONE?"右足:":"右後足:");break;
      case BODYPART_LEG_LEFT:addstr(cr.animalgloss==ANIMALGLOSS_NONE?"左足:":"左後足:");break;
      }

      move(5+w,66);
      if(cr.wound[w] & WOUND_NASTYOFF)addstr("損壊");
      else if(cr.wound[w] & WOUND_CLEANOFF)addstr("切断");
      else
      {
         int sum=0;

         if(cr.wound[w] & WOUND_SHOT)sum++;
         if(cr.wound[w] & WOUND_CUT)sum++;
         if(cr.wound[w] & WOUND_BRUISED)sum++;
         if(cr.wound[w] & WOUND_BURNED)sum++;
         if(cr.wound[w] & WOUND_TORN)sum++;

         if(sum==0)
         {
            set_color(COLOR_GREEN,COLOR_BLACK,1);
            if(cr.animalgloss==ANIMALGLOSS_ANIMAL)
               addstr("動物");
            else addstr("リベラル");
         }

         if(cr.wound[w] & WOUND_SHOT){addstr("被弾");sum--;if(sum>0)addstr("、");}
         if(cr.wound[w] & WOUND_BRUISED){addstr("打撲");sum--;if(sum>0)addstr("、");}
         if(cr.wound[w] & WOUND_CUT){addstr("切傷");sum--;if(sum>0)addstr("、");}
         if(cr.wound[w] & WOUND_TORN){addstr("裂傷");sum--;if(sum>0)addstr("、");}
         if(cr.wound[w] & WOUND_BURNED){addstr("火傷");sum--;if(sum>0)addstr("、");}
      }
   }
   set_color(COLOR_WHITE,COLOR_BLACK,0);

   //SPECIAL WOUNDS
   set_color(COLOR_RED,COLOR_BLACK,0);

   int y=12;
   int x=55;
   if(cr.special[SPECIALWOUND_HEART]!=1)
   {
      move(y++,x);
      addstr("心臓破裂");
   }
   if(cr.special[SPECIALWOUND_RIGHTLUNG]!=1)
   {
      move(y++,x);
      addstr("右肺損壊");
   }
   if(cr.special[SPECIALWOUND_LEFTLUNG]!=1)
   {
      move(y++,x);
      addstr("左肺損壊");
   }
   if(cr.special[SPECIALWOUND_NECK]!=1)
   {
      move(y++,x);
      addstr("首の骨折");
   }
   if(cr.special[SPECIALWOUND_UPPERSPINE]!=1)
   {
      move(y++,x);
      addstr("上部脊椎骨折");
   }
   if(cr.special[SPECIALWOUND_LOWERSPINE]!=1)
   {
      move(y++,x);
      addstr("下部脊椎骨折");
   }
   if(cr.special[SPECIALWOUND_RIGHTEYE]!=1)
   {
      move(y++,x);
      addstr("右目を欠損");
   }
   if(cr.special[SPECIALWOUND_LEFTEYE]!=1)
   {
      move(y++,x);
      addstr("左目を欠損");
   }
   if(cr.special[SPECIALWOUND_NOSE]!=1)
   {
      move(y++,x);
      addstr("鼻を欠損");
   }
   if(cr.special[SPECIALWOUND_TONGUE]!=1)
   {
      move(y++,x);
      addstr("舌を欠損");
   }
   if(cr.special[SPECIALWOUND_TEETH]!=TOOTHNUM)
   {
      move(y++,x);
      if(cr.special[SPECIALWOUND_TEETH]==0)addstr("全歯を欠損");
      else if(cr.special[SPECIALWOUND_TEETH]==TOOTHNUM-1)addstr("歯を1本欠損");
      else if(cr.special[SPECIALWOUND_TEETH]<TOOTHNUM)addstr("歯を欠損");
   }
   if(cr.special[SPECIALWOUND_LIVER]!=1)
   {
      move(y++,x);
      addstr("肝臓を損傷");
   }
   if(cr.special[SPECIALWOUND_RIGHTKIDNEY]!=1)
   {
      move(y++,x);
      addstr("右腎臓を損傷");
   }
   if(cr.special[SPECIALWOUND_LEFTKIDNEY]!=1)
   {
      move(y++,x);
      addstr("左腎臓を損傷");
   }
   if(cr.special[SPECIALWOUND_STOMACH]!=1)
   {
      move(y++,x);
      addstr("胃を損傷");
   }
   if(cr.special[SPECIALWOUND_SPLEEN]!=1)
   {
      move(y++,x);
      addstr("脾臓破裂");
   }
   if(cr.special[SPECIALWOUND_RIBS]!=RIBNUM)
   {
      move(y++,x);
      if(cr.special[SPECIALWOUND_RIBS]==0)addstr("全肋骨を骨折");
      else if(cr.special[SPECIALWOUND_RIBS]==RIBNUM-1)addstr("肋骨を1本骨折");
      else if(cr.special[SPECIALWOUND_RIBS]<RIBNUM)addstr("肋骨を骨折");
   }

   set_color(COLOR_WHITE,COLOR_BLACK,0);
}

/* Full screen character sheet, crime sheet */
void printliberalcrimes(Creature &cr)
{
   // Add name
   set_color(COLOR_WHITE,COLOR_BLACK,0);
   if(strcmp(cr.propername,cr.name)!=0)
      mvaddstr(2,0,"コードネーム: ");
   else mvaddstr(2,0,"氏名: ");
   set_color(COLOR_WHITE,COLOR_BLACK,1);
   addstr(cr.name);
   set_color(COLOR_WHITE,COLOR_BLACK,0);
   addstr("、");
   addstr(gettitle(cr));
   addstr(" (");
   addstr(cr.get_type_name());
   addstr(")");
   // Show outstanding convictions in addition to untried crimes
   if(cr.deathpenalty)
   {
      set_color(COLOR_RED,COLOR_BLACK,1);
      if(location[cr.location]->type==SITE_GOVERNMENT_PRISON)
         mvaddstr(3,0,"死刑囚監房に服役中");
      else mvaddstr(3,0,"死刑を求刑");
   }
   else if(cr.sentence<0)
   {
      set_color(COLOR_RED,COLOR_BLACK,1);
      if(location[cr.location]->type==SITE_GOVERNMENT_PRISON)
         mvaddstr(3,0,"終身刑で服役中");
      else mvaddstr(3,0,"終身刑を求刑");
   }
   else if(cr.sentence>0)
   {
      set_color(COLOR_YELLOW,COLOR_BLACK,1);
      mvaddstr(3,0,"");
      addstr(cr.sentence);
      addstr("ヶ月");
      if(location[cr.location]->type==SITE_GOVERNMENT_PRISON)
         addstr("服役");
      else addstr("の禁固刑を求刑");
   }

   // Add all crimes
   for(int i = 0;i < LAWFLAGNUM; i++)
   {
      if(i%2==0 && i<4)
      {
         set_color(COLOR_WHITE,COLOR_BLACK,0);
         mvaddstr(4,40*(i/2),"犯罪");
         mvaddstr(4,30+40*(i/2),"件数");
      }

      // Commited crimes are yellow
      if(cr.crimes_suspected[i] > 0)
         set_color(COLOR_YELLOW,COLOR_BLACK,1);
      else set_color(COLOR_BLACK,COLOR_BLACK,1);

      mvaddstr(5+i/2,40*(i%2),getlawflag(i)+": ");
      mvaddstr_f(5+i/2,30+40*(i%2),"%2d",cr.crimes_suspected[i]);
   }

   set_color(COLOR_WHITE,COLOR_BLACK,0);
}

/* draws a horizontal line across the screen */
void makedelimiter(int y,int x)
{
   set_color(COLOR_WHITE,COLOR_BLACK,0);
   if(mode==GAMEMODE_SITE&&y==8&&x==0&&mapshowing) // special case: there is a map on the right in site mode
      mvaddstr(y,x,"-----------------------------------------------------+-------------------------+"); // 80 characters
   else // normal delimiter
      mvaddstr(y,x,"--------------------------------------------------------------------------------"); // 80 characters
}

/* prints a character's health description (One Leg, Liberal, NearDETH...) */
void printhealthstat(Creature &g,int y,int x,char smll)
{
   short woundsum=0;
   bool bleeding=false;
   for(int w=0;w<BODYPARTNUM;w++)
   {
      if(g.wound[w]!=0)woundsum++;
      if(g.wound[w] & WOUND_BLEEDING)bleeding=true;
   }

   int armok=2,legok=2;
   if((g.wound[BODYPART_ARM_RIGHT] & WOUND_NASTYOFF)||
      (g.wound[BODYPART_ARM_RIGHT] & WOUND_CLEANOFF))armok--;
   if((g.wound[BODYPART_ARM_LEFT] & WOUND_NASTYOFF)||
      (g.wound[BODYPART_ARM_LEFT] & WOUND_CLEANOFF))armok--;
   if((g.wound[BODYPART_LEG_RIGHT] & WOUND_NASTYOFF)||
      (g.wound[BODYPART_LEG_RIGHT] & WOUND_CLEANOFF))legok--;
   if((g.wound[BODYPART_LEG_LEFT] & WOUND_NASTYOFF)||
      (g.wound[BODYPART_LEG_LEFT] & WOUND_CLEANOFF))legok--;

   move(y,x);
   if(bleeding)set_color(COLOR_RED,COLOR_BLACK,1);
   else set_color(COLOR_WHITE,COLOR_BLACK,1);
   if(!g.alive)
   {
      set_color(COLOR_BLACK,COLOR_BLACK,1);
      addstr("死亡");
   }
   else if(g.blood<=20)
   {
      if(smll)addstr("瀕死");
      else addstr("瀕死");
   }
   else if(g.blood<=50)
   {
      if(smll)addstr("重傷");
      else addstr("重傷");
   }
   else if(g.blood<=75)
   {
      addstr("負傷");
   }
   else if(g.blood<100)
   {
      if(smll)addstr("軽傷");
      else addstr("軽傷");
   }
   else if(g.special[SPECIALWOUND_NECK]==2)
   {
      if(!bleeding)set_color(COLOR_GREEN,COLOR_BLACK,0);
      if(smll)addstr("首骨折");
      else addstr("首骨折");
   }
   else if(g.special[SPECIALWOUND_UPPERSPINE]==2)
   {
      if(!bleeding)set_color(COLOR_GREEN,COLOR_BLACK,0);
      if(smll)addstr("四肢麻痺");
      else addstr("四肢麻痺");
   }
   else if(g.special[SPECIALWOUND_LOWERSPINE]==2)
   {
      if(!bleeding)set_color(COLOR_GREEN,COLOR_BLACK,0);
      if(smll)addstr("対麻痺");
      else addstr("対麻痺");
   }
   else if(g.special[SPECIALWOUND_RIGHTEYE]==0&&
      g.special[SPECIALWOUND_LEFTEYE]==0&&
      g.special[SPECIALWOUND_NOSE]==0)
   {
      if(!bleeding)set_color(COLOR_GREEN,COLOR_BLACK,0);
      if(smll)addstr("顔面喪失");
      else addstr("顔面喪失");
   }
   else if(legok==0&&armok==0)
   {
      if(!bleeding)set_color(COLOR_GREEN,COLOR_BLACK,0);
      addstr("手足喪失");
   }
   else if((legok==1&&armok==0)||(armok==1&&legok==0))
   {
      if(!bleeding)set_color(COLOR_GREEN,COLOR_BLACK,0);
      addstr("片足");
   }
   else if(legok==2&&armok==0)
   {
      if(!bleeding)set_color(COLOR_GREEN,COLOR_BLACK,0);
      addstr("両腕喪失");
   }
   else if(legok==0&&armok==2)
   {
      if(!bleeding)set_color(COLOR_GREEN,COLOR_BLACK,0);
      addstr("両足喪失");
   }
   else if(legok==1&&armok==1)
   {
      if(!bleeding)set_color(COLOR_GREEN,COLOR_BLACK,0);
      if(smll)addstr("片腕片足");
      else addstr("片腕片足");
   }
   else if(armok==1)
   {
      if(!bleeding)set_color(COLOR_GREEN,COLOR_BLACK,0);
      addstr("片腕");
   }
   else if(legok==1)
   {
      if(!bleeding)set_color(COLOR_GREEN,COLOR_BLACK,0);
      addstr("片足");
   }
   else if(g.special[SPECIALWOUND_RIGHTEYE]==0&&
      g.special[SPECIALWOUND_LEFTEYE]==0)
   {
      if(!bleeding)set_color(COLOR_GREEN,COLOR_BLACK,0);
      addstr("全盲");
   }
   else if((g.special[SPECIALWOUND_RIGHTEYE]==0||
      g.special[SPECIALWOUND_LEFTEYE]==0)&&
      g.special[SPECIALWOUND_NOSE]==0)
   {
      if(!bleeding)set_color(COLOR_GREEN,COLOR_BLACK,0);
      if(smll)addstr("顔面損傷");
      else addstr("顔面損傷");
   }
   else if(g.special[SPECIALWOUND_NOSE]==0)
   {
      if(!bleeding)set_color(COLOR_GREEN,COLOR_BLACK,0);
      if(smll)addstr("鼻喪失");
      else addstr("鼻喪失");
   }
   else if(g.special[SPECIALWOUND_RIGHTEYE]==0||
      g.special[SPECIALWOUND_LEFTEYE]==0)
   {
      if(!bleeding)set_color(COLOR_GREEN,COLOR_BLACK,0);
      if(smll)addstr("片目");
      else addstr("片目");
   }
   else if(g.special[SPECIALWOUND_TONGUE]==0)
   {
      if(!bleeding)set_color(COLOR_GREEN,COLOR_BLACK,0);
      if(smll)addstr("舌喪失");
      else addstr("舌喪失");
   }
   else if(g.special[SPECIALWOUND_TEETH]==0)
   {
      if(!bleeding)set_color(COLOR_GREEN,COLOR_BLACK,0);
      addstr("全歯喪失");
   }
   else if(g.special[SPECIALWOUND_TEETH]<TOOTHNUM)
   {
      if(!bleeding)set_color(COLOR_GREEN,COLOR_BLACK,0);
      if(smll)addstr("歯喪失");
      else addstr("歯喪失");
   }
   else
   {
      if(g.align==-1)
      {
         set_color(COLOR_RED,COLOR_BLACK,1);
         if(smll)addstr("保守");
         else addstr("保守派");
      }
      else if(g.align==0)
      {
         set_color(COLOR_WHITE,COLOR_BLACK,1);
         addstr("穏健派");
      }
      else
      {
         set_color(COLOR_GREEN,COLOR_BLACK,1);
         if(g.animalgloss==ANIMALGLOSS_ANIMAL)
            addstr("動物");
         else addstr("リベラル");
      }
   }
}

/*
This function prints the cash the player has with optional prefix as
well as screen coordinates.

Please note that offsetx is the offset from the right of the screen, y is
the offset from the top as always.
*/
void printfunds(int y, int offsetx, const char* prefix)
{
   char moneystr[50],prefixbuffer[50];

   if(prefix==NULL)
      strncpy(prefixbuffer,"",50);
   else strncpy(prefixbuffer,prefix,50);

   strcpy(moneystr,ledger.get_funds());

   //Save screen coordinates for later.
   int begy,begx;
   getyx(stdscr,begy,begx);

   //Save color and brightness information for later.
   short colorpair,front,back;

   attr_t attrs;
   attr_get(&attrs,&colorpair,NULL);
   bool dim=(attrs & WA_DIM)!=0;
   pair_content(colorpair,&front,&back);

   //Move, set color, and write.
   move(y,80-len(moneystr)-len(prefixbuffer)-offsetx);
   addstr(prefixbuffer);
   addstr(moneystr);

   //Recover old settings
   move(begy,begx);
   set_color(front,back,dim);
}

/* prints a short blurb showing how to page forward */
void addnextpagestr()
{
   if(interface_pgup=='[')
      addstr("] - 後");
   else if(interface_pgup=='.')
      addstr(": - 後");
   else addstr("PGDN - 後");
}

/* prints a short blurb showing how to page back */
void addprevpagestr()
{
   if(interface_pgup=='[')
      addstr("[ - 前");
   else if(interface_pgup=='.')
      addstr("; - 前");
   else addstr("PGUP - 前");
}

/* prints a long blurb showing how to page forward and back */
void addpagestr()
{
   if(interface_pgup=='[')
      addstr("[]で別のリベラルページを表示する。");
   else if(interface_pgup=='.')
      addstr(";:で別のリベラルページを表示する。");
   else addstr("PGUP/PGDNで別のリベラルページを表示する。");
}

static char sbuf[81]; // used by addstr_f(), mvaddstr_f(), addstr_fl(), and mvaddstr_fl()
#define FORMAT_OUTPUT  va_list args; \
                       va_start(args,format); \
                       vsnprintf(sbuf,81,format,args); \
                       va_end(args);

/*	addstr with formatted output	*/
int addstr_f(const char * format, ...)
{
   FORMAT_OUTPUT
   return addstr(sbuf);
}

/*	mvaddstr with formatted output	*/
int mvaddstr_f(int y, int x, const char * format, ...)
{
   FORMAT_OUTPUT
   return mvaddstr(y,x,sbuf);
}


/*	addstr with formatted output and logging	*/
int addstr_fl(Log &log, const char * format, ...)
{
   FORMAT_OUTPUT
   return addstr(sbuf,log);
}

/*	mvaddstr with formatted output and logging	*/
int mvaddstr_fl(int y, int x, Log &log, const char * format, ...)
{
   FORMAT_OUTPUT
   return mvaddstr(y,x,sbuf,log);
}
