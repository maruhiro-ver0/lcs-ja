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

bool goodguyattack = false;

/* attack handling for each side as a whole */
void youattack()
{
   foughtthisround=1;

   short wasalarm=sitealarm;

   goodguyattack = true;

   for(int p=0;p<6;p++)
   {
      if(activesquad->squad[p]==NULL) continue;
      if(!activesquad->squad[p]->alive) continue;

      vector<int> super_enemies;
      vector<int> dangerous_enemies;
      vector<int> enemies;
      vector<int> non_enemies;

      for(int e=0;e<ENCMAX;e++)
      {
         if(encounter[e].alive&&encounter[e].exists)
         {
            if(encounter[e].enemy())
            {
               if(encounter[e].animalgloss==ANIMALGLOSS_TANK&&
                  encounter[e].stunned==0)
                  super_enemies.push_back(e);
               else if((encounter[e].is_armed()||
                       (encounter[e].type==CREATURE_COP&&encounter[e].align==ALIGN_MODERATE)||
                        encounter[e].type==CREATURE_SCIENTIST_EMINENT||
                        encounter[e].type==CREATURE_JUDGE_LIBERAL||
                        encounter[e].type==CREATURE_JUDGE_CONSERVATIVE||
                        encounter[e].type==CREATURE_CORPORATE_CEO||
                        encounter[e].type==CREATURE_POLITICIAN||
                        encounter[e].type==CREATURE_RADIOPERSONALITY||
                        encounter[e].type==CREATURE_NEWSANCHOR||
                        encounter[e].type==CREATURE_MILITARYOFFICER||
                        encounter[e].specialattack!=-1)&&
                        encounter[e].blood>=40&&
                        encounter[e].stunned==0)
                  dangerous_enemies.push_back(e);
               else enemies.push_back(e);
            }
            else non_enemies.push_back(e);
         }
      }

      if(!(len(super_enemies)+len(dangerous_enemies)+len(enemies))) return;

      int target;
      // If there are "super enemies", shoot at one of them unless we're using a persuasion-based attack
      if(len(super_enemies)&&
       ((activesquad->squad[p]->type!=CREATURE_SCIENTIST_EMINENT&&
         activesquad->squad[p]->type!=CREATURE_JUDGE_LIBERAL&&
         activesquad->squad[p]->type!=CREATURE_JUDGE_CONSERVATIVE&&
         activesquad->squad[p]->type!=CREATURE_CORPORATE_CEO&&
         activesquad->squad[p]->type!=CREATURE_POLITICIAN&&
         activesquad->squad[p]->type!=CREATURE_RADIOPERSONALITY&&
         activesquad->squad[p]->type!=CREATURE_NEWSANCHOR&&
         activesquad->squad[p]->type!=CREATURE_MILITARYOFFICER&&
        !activesquad->squad[p]->get_weapon().has_musical_attack())||
       (!activesquad->squad[p]->get_weapon().has_musical_attack()&&
         activesquad->squad[p]->is_armed())))
         target=pickrandom(super_enemies);
      // Else, if there are "dangerous enemies", shoot at one of them
      else if(len(dangerous_enemies))
         target=pickrandom(dangerous_enemies);
      // Else, if there are regular enemies, shoot at one of them
      else if(len(enemies)) target=pickrandom(enemies);
      // Else, we skipped a "super enemy" because it we're using a persuasion-based attack but it's the only enemy left so we have to pick it
      else target=pickrandom(super_enemies);

      char mistake=0;
      // 1% chance to accidentally hit bystanders
      if(len(non_enemies)&&!LCSrandom(100))
      {
         target=pickrandom(non_enemies);
         mistake=1;
      }

      char actual;
      short beforeblood=encounter[target].blood;
      if(encounter[target].align==1) mistake=1;
      attack(*activesquad->squad[p],encounter[target],mistake,actual);

      if(actual)
      {
         if(mistake)
         {
            alienationcheck(mistake);
            sitestory->crime.push_back(CRIME_ATTACKED_MISTAKE);
            sitecrime+=10;
         }
         else
         {
            sitecrime+=3;
            addjuice(*(activesquad->squad[p]),1,200);
         }
         sitestory->crime.push_back(CRIME_ATTACKED);
         // Charge with assault if first strike
         if(sitealarm && (!wasalarm||(beforeblood>encounter[target].blood && beforeblood==100)))
         {
            if(!activesquad->squad[p]->is_armed())
               criminalize(*activesquad->squad[p],LAWFLAG_ASSAULT);
            else criminalize(*activesquad->squad[p],LAWFLAG_ARMEDASSAULT);
         }
      }

      if(!encounter[target].alive)
      {
         delenc(target,1);
         if(!mistake)
         {
            for(int p=0;p<6;p++)
            {
               if(activesquad->squad[p]==NULL) continue;
               if(!activesquad->squad[p]->alive) continue;

               addjuice(*(activesquad->squad[p]),5,500);
            }
         }
      }
   }

   for(int e=0;e<ENCMAX;e++)
   {
      if(encounter[e].exists && encounter[e].alive && encounter[e].enemy())
      {
         sitealarm=1;
         break;
      }
   }

   //COVER FIRE
   if(location[cursite]->siege.siege)
   {
      for(int p=0;p<len(pool);p++)
      {
         if(!pool[p]->alive) continue;
         if(pool[p]->align!=1) continue;
         if(pool[p]->squadid!=-1) continue;
         if(pool[p]->location!=cursite) continue;

         // Juice check to engage in cover fire
         // 10% chance for every 10 juice, starting at
         // 10% chance for 0 juice -- caps out at 100%
         // chance to fire at 90 juice
         //if(LCSrandom(10)-pool[p]->juice/10>0)continue;

         if(pool[p]->get_weapon().get_attack(true,false,false))
         {
            char conf=0;
            if(pool[p]->get_weapon().get_ammoamount()>0) conf=1;
            if(pool[p]->get_weapon().get_attack(true,false,false)->uses_ammo)
               if(pool[p]->can_reload()) conf=1;

            if(conf)
            {
               vector<int> goodtarg,badtarg;

               for(int e=0;e<ENCMAX;e++)
               {
                  if(encounter[e].alive&&encounter[e].exists)
                  {
                     if(encounter[e].enemy())goodtarg.push_back(e);
                     else badtarg.push_back(e);
                  }
               }

               if(!len(goodtarg)) return;

               int target=pickrandom(goodtarg);

               char mistake=0;

               if(len(badtarg)&&!LCSrandom(10))
               {
                  target=pickrandom(badtarg);
                  mistake=1;
               }

               char actual;
               attack(*pool[p],encounter[target],mistake,actual);

               if(actual)
               {
                  if(mistake)
                  {
                     alienationcheck(mistake);
                     sitestory->crime.push_back(CRIME_ATTACKED_MISTAKE);
                     sitecrime+=10;
                  }

                  if(!pool[p]->is_armed())
                     criminalize(*pool[p],LAWFLAG_ASSAULT);
                  else criminalize(*pool[p],LAWFLAG_ARMEDASSAULT);
               }

               if(!encounter[target].alive) delenc(target,1);
            }
         }
      }
   }
}



void enemyattack()
{
   static const char *escape_crawling[] =
   {
      "はうめきながら這い出した…",
      "はすすり泣きをしながら這い出した…",
      "は血の跡をつけながら這い出した…",
      "は悲鳴を上げて這い出した…",
      "は泣きながら這い出した…",
      "は涙を流しながら這い出した…",
      "はすすり泣きをしながら這い出した…",
      "は祈りながら這い出した…",
      "は罵りながら這い出した…"
   };

   static const char *escape_running[] =
   {
      "は急いでこの場を去った!",
      "は悲鳴を上げて逃げ出した!",
      "は逃げ出した!",
      "は走り去った!",
      "は大声を上げて逃げた!",
      "はあわてて走り出した!",
      "は叫び声を上げ走り去った!",
   };


   foughtthisround=1;

   goodguyattack = false;

   bool armed=false;
   for(int i=0;i<6;i++)
   {
      if(activesquad->squad[i]==NULL) break;
      if(activesquad->squad[i]->is_armed()) armed=true;
   }

#ifdef NOENEMYATTACK
   return;
#endif

   int e2, e;
   char printed;
   for(e=0;e<ENCMAX;e++)
   {
      if(!encounter[e].exists) continue;
      if(!encounter[e].alive) continue;

      if(sitealarm==1&&encounter[e].type==CREATURE_BOUNCER&&encounter[e].align!=ALIGN_LIBERAL)
         conservatise(encounter[e]);
      if(encounter[e].enemy()) encounter[e].cantbluff=2;

      if(mode!=GAMEMODE_CHASECAR)
      {
         // Encountered creature will flee if:
         // (a) Non-Conservative, and not recently converted via music or some other mechanism
         // (b) Conservative, no juice, unarmed, non-tank/animal, enemy is armed, and fails a morale check based in part on injury level
         // (c) Conservative, and lost more than 55% blood
         // (d) There's a fire, they are not firefighters, and they fail a random check
         // Encountered creatures will never flee if they are tanks, animals, or so hurt they can't move
         char fire=0;
         if(mode==GAMEMODE_SITE)
         {
            if(levelmap[locx][locy][locz].flag & SITEBLOCK_FIRE_START ||
               levelmap[locx][locy][locz].flag & SITEBLOCK_FIRE_END)
               fire=1;
            else if(levelmap[locx][locy][locz].flag & SITEBLOCK_FIRE_PEAK)
               fire=2;
         }

         if(((!encounter[e].enemy()||
            (encounter[e].juice==0&&!encounter[e].is_armed()&&armed&&encounter[e].blood<signed(70+LCSrandom(61))))
            &&!(encounter[e].flag & CREATUREFLAG_CONVERTED))||(encounter[e].blood<45&&encounter[e].juice<200)
            ||((fire*LCSrandom(5)>=3)&&!(encounter[e].type==CREATURE_FIREFIGHTER)))
         {
            if(encounter[e].animalgloss==ANIMALGLOSS_NONE)
            {
               if(!incapacitated(encounter[e],0,printed))
               {
                  if(printed)
                  {
                     printparty();
                     if(mode==GAMEMODE_CHASECAR||
                        mode==GAMEMODE_CHASEFOOT) printchaseencounter();
                     else printencounter();

                     getkey();
                  }

                  clearmessagearea();

                  move(16,1);
                  addstr(encounter[e].name, gamelog);
                  if((encounter[e].wound[BODYPART_LEG_RIGHT] & WOUND_NASTYOFF)||
                     (encounter[e].wound[BODYPART_LEG_RIGHT] & WOUND_CLEANOFF)||
                     (encounter[e].wound[BODYPART_LEG_LEFT] & WOUND_NASTYOFF)||
                     (encounter[e].wound[BODYPART_LEG_LEFT] & WOUND_CLEANOFF)||
                     (encounter[e].blood<45))
                     addstr(pickrandom(escape_crawling), gamelog);
                  else addstr(pickrandom(escape_running), gamelog);

                  gamelog.newline();

                  delenc(e,0);
                  e--;

                  printparty();
                  if(mode==GAMEMODE_CHASECAR||
                     mode==GAMEMODE_CHASEFOOT) printchaseencounter();
                  else printencounter();

                  getkey();
               }

               continue;
            }
         }
      }

      vector<int> goodtarg,badtarg;

      if(encounter[e].enemy())
      {
         for(int p=0;p<6;p++) if(activesquad->squad[p]!=NULL)
            if(activesquad->squad[p]->alive) goodtarg.push_back(p);
      }
      else
      {
         for(e2=0;e2<ENCMAX;e2++)
         {
            if(!encounter[e2].exists) continue;
            if(!encounter[e2].alive) continue;
            if(encounter[e2].align!=-1) continue;

            goodtarg.push_back(e2);
         }
      }

      for(e2=0;e2<ENCMAX;e2++)
      {
         if(!encounter[e2].exists) continue;
         if(!encounter[e2].alive) continue;
         if(encounter[e2].enemy()) continue;

         badtarg.push_back(e2);
      }

      if(!len(goodtarg)) return;

      int target=pickrandom(goodtarg);

      char canmistake=1;

      int encnum=0;
      for(e2=0;e2<ENCMAX;e2++) if(encounter[e2].exists) encnum++;

      if((encounter[e].type==CREATURE_SCIENTIST_EMINENT||
          encounter[e].type==CREATURE_JUDGE_LIBERAL||
          encounter[e].type==CREATURE_JUDGE_CONSERVATIVE||
          encounter[e].type==CREATURE_CORPORATE_CEO||
          encounter[e].type==CREATURE_POLITICIAN||
          encounter[e].type==CREATURE_RADIOPERSONALITY||
          encounter[e].type==CREATURE_NEWSANCHOR||
          encounter[e].type==CREATURE_MILITARYOFFICER)&&encnum<ENCMAX) canmistake=0;

      char actual;
      if(canmistake)
      {
         if(encounter[e].enemy())
         {
            if(activesquad->squad[target]->prisoner!=NULL && !LCSrandom(2))
            {
               attack(encounter[e],*activesquad->squad[target]->prisoner,1,actual);
               if(!activesquad->squad[target]->prisoner->alive)
               {
                  if(activesquad->squad[target]->prisoner->squadid==-1)
                  {
                     clearmessagearea();
                     set_color(COLOR_WHITE,COLOR_BLACK,1);
                     move(16,1);
                     addstr(activesquad->squad[target]->name, gamelog);
                     addstr("は", gamelog);
                     addstr(activesquad->squad[target]->prisoner->name, gamelog);
                     addstr("を置いた。", gamelog);
                     gamelog.newline();

                     int prisonerType = activesquad->squad[target]->prisoner->type;

                     if(prisonerType==CREATURE_CORPORATE_CEO||
                        prisonerType==CREATURE_POLITICIAN||
                        prisonerType==CREATURE_RADIOPERSONALITY||
                        prisonerType==CREATURE_NEWSANCHOR||
                        prisonerType==CREATURE_SCIENTIST_EMINENT||
                        prisonerType==CREATURE_JUDGE_CONSERVATIVE||
                        prisonerType==CREATURE_MILITARYOFFICER) sitecrime+=30;

                     makeloot(*activesquad->squad[target]->prisoner,groundloot);

                     getkey();

                     delete_and_nullify(activesquad->squad[target]->prisoner);
                  }
               }
               continue;
            }
         }

         if(!LCSrandom(10)&&len(badtarg))
         {
            target=pickrandom(badtarg);
            if(encounter[target].flag & CREATUREFLAG_CONVERTED)
               attack(encounter[e],encounter[target],0,actual);
            else attack(encounter[e],encounter[target],1,actual);
            if(!encounter[target].alive) delenc(target,1);
            continue;
         }
      }

      if(encounter[e].enemy())
         attack(encounter[e],*activesquad->squad[target],0,actual);
      else attack(encounter[e],encounter[target],0,actual);
   }
}



/* attack handling for an individual creature and its target */
void attack(Creature &a,Creature &t,char mistake,char &actual,bool force_melee)
{
   actual=0;

   char str[200];

   clearmessagearea(true);  // erase the whole length and redraw map if applicable, since previous combat messages can be wider than 53 chars.
   if(goodguyattack) set_color(COLOR_GREEN,COLOR_BLACK,1);
   else set_color(COLOR_RED,COLOR_BLACK,1);

   //INCAPACITATED
   char incaprint;
   a.forceinc=0;
   if(incapacitated(a,0,incaprint))
   {
      if(incaprint)
      {
         printparty();
         if(mode==GAMEMODE_CHASECAR||
            mode==GAMEMODE_CHASEFOOT) printchaseencounter();
         else printencounter();

         getkey();
      }

      a.forceinc=1;

      return;
   }

   //SPECIAL ATTACK!
   int encnum=0;
   for(int e=0;e<ENCMAX;e++) if(encounter[e].exists) encnum++;

   if(!force_melee &&
    (((a.type==CREATURE_COP&&a.align==ALIGN_MODERATE&&a.enemy())||
       a.type==CREATURE_SCIENTIST_EMINENT||
       a.type==CREATURE_JUDGE_LIBERAL||
       a.type==CREATURE_JUDGE_CONSERVATIVE||
      (a.type==CREATURE_CORPORATE_CEO&&LCSrandom(2))||
       a.type==CREATURE_POLITICIAN||
       a.type==CREATURE_RADIOPERSONALITY||
       a.type==CREATURE_NEWSANCHOR||
       a.type==CREATURE_MILITARYOFFICER||
       a.get_weapon().has_musical_attack()) &&
      (a.get_weapon().has_musical_attack() || !a.is_armed() || a.align!=1)))
   {
      if(a.align==1||encnum<ENCMAX)
      {
         specialattack(a, t, actual);
         return;
      }
   }

   //RELOAD
   if((a.will_reload(mode==GAMEMODE_CHASECAR,force_melee)
    ||(a.has_thrown_weapon && len(a.extra_throwing_weapons)))
    &&!force_melee)
   {
      if(a.will_reload(mode==GAMEMODE_CHASECAR,force_melee))
      {
         a.reload(false);
         strcpy(str,a.name);
         strcat(str,"は装填した。");
      }
      else if(a.has_thrown_weapon && len(a.extra_throwing_weapons))
      {
         a.ready_another_throwing_weapon();
         strcpy(str,a.name);
         strcat(str,"は別の");
         strcat(str,a.get_weapon().get_name());
         strcat(str,"の準備をした。");
      }
      move(16,1);
      addstr(str, gamelog);
      gamelog.newline();

      printparty();
      if(mode==GAMEMODE_CHASECAR
       ||mode==GAMEMODE_CHASEFOOT) printchaseencounter();
      else printencounter();

      getkey();

      return;
   }
   else if(a.has_thrown_weapon) a.has_thrown_weapon = false;

   const attackst* attack_used = NULL;
   attack_used = a.get_weapon().get_attack(mode==GAMEMODE_CHASECAR,          //Force ranged if in a car.
                                           force_melee,
                                          (force_melee || !a.can_reload())); //No reload if force melee or unable to reload.

   if(attack_used==NULL) //No attack possible.
      return;            //Then bail, they can't fight

   bool melee=true;
   if(attack_used->ranged) melee=false;
   bool sneak_attack=false;

   strcpy(str,a.name);
   strcat(str,"は");
   if(mistake) strcat(str,"誤って");

   strcat(str,t.name);

   if(a.is_armed() && !attack_used->thrown)
   {
      strcat(str,"に");
      strcat(str,a.get_weapon().get_name(1));
   }
   if(!a.is_armed())
   {
      if(!a.animalgloss) //Move into WEAPON_NONE -XML
      {
         if(!LCSrandom(a.get_skill(SKILL_HANDTOHAND)+1))
            strcat(str,"に体当たり");
         else if(!LCSrandom(a.get_skill(SKILL_HANDTOHAND)))
            strcat(str,"を殴る");
         else if(!LCSrandom(a.get_skill(SKILL_HANDTOHAND)-1))
            strcat(str,"を掴む");
         else if(!LCSrandom(a.get_skill(SKILL_HANDTOHAND)-2))
            strcat(str,"を蹴る");
         else if(!LCSrandom(a.get_skill(SKILL_HANDTOHAND)-3))
            strcat(str,"を打つ");
         else if(!LCSrandom(a.get_skill(SKILL_HANDTOHAND)-4))
            strcat(str,"に跳び蹴り");
         else strcat(str,"を舞うように打つ");
      }
      else
      {
         if(a.specialattack==ATTACK_CANNON)
         {
            strcat(str,"に120mm砲弾を発射した");
            melee=false;
         }
         else if(a.specialattack==ATTACK_FLAME) strcat(str,"に火を吹いた");
         else if(a.specialattack==ATTACK_SUCK) strcat(str,"を突き刺す");
         else strcat(str,"に噛み付く");
      }
   }
   else
   {
      if(attack_used->can_backstab && a.align==ALIGN_LIBERAL && !mistake)
      {
         if(t.cantbluff<1 && sitealarm<1)
         {
            sneak_attack = true;
            strcat(str,"に密かに近づいた");
            if(sitealarmtimer>10 || sitealarmtimer<0) sitealarmtimer=10;
            t.cantbluff = 2;
         }
      }

      if(!sneak_attack)
      {
         strcat(str,attack_used->attack_description);
         sitealarm=1;
      }
   }

   move(16,1);
   addstr(str, gamelog);

   strcpy(str,"!");
   addstr(str, gamelog);
   gamelog.newline();

   getkey();

   if(goodguyattack) set_color(COLOR_GREEN,COLOR_BLACK,1);
   else set_color(COLOR_RED,COLOR_BLACK,1);
   /*
   strcpy(str, a.heshe(true)); // capitalize=true. Shorten the string so it doesn't spill over as much; we already said attacker's name on the previous line anyways.
   */
   strcpy(str, "");

   int bonus=0; // Accuracy bonus or penalty that does NOT affect damage or counterattack chance

   //SKILL EFFECTS
   int wsk=attack_used->skill;

   Creature* driver = getChaseDriver(t);
   Vehicle* vehicle = getChaseVehicle(t);
   Creature* adriver = getChaseDriver(a);
   Vehicle* avehicle = getChaseVehicle(a);
   
   // Basic roll
   int aroll=a.skill_roll(wsk);
   // In a car chase, the driver provides the defence roll instead of the victim.
   int droll= 0;
   if (mode!=GAMEMODE_CHASECAR)
   {
      droll = t.skill_roll(SKILL_DODGE)/2;
   }
   else
   {
      if (driver!=NULL && vehicle!=NULL)
      {  // without a vehicle or driver, you get a zero roll.
         droll = driver->skill_roll(PSEUDOSKILL_DODGEDRIVE);
      }
      if (adriver!=NULL && avehicle!=NULL)
      {
         bonus += avehicle->attackbonus(adriver->id == a.id);  // Attack bonus depends on attacker's car and whether attacker is distracted by driving.
      }
      else // shouldn't happen
      {
         bonus -= 10; // You're on the wrong side of a drive-by shooting?!
      }
   }
   
   if(sneak_attack)
   {
      droll=t.attribute_roll(ATTRIBUTE_WISDOM)/2;
      aroll+=a.skill_roll(SKILL_STEALTH);
      a.train(wsk,10);
   }
   else
   {
      if (driver!=NULL)
         driver->train(SKILL_DRIVING, aroll/2);
      else
         t.train(SKILL_DODGE,aroll*2);
      a.train(wsk,droll*2+5);
   }

   // Hostages interfere with attack
   if(t.prisoner!=NULL) bonus-=LCSrandom(10);
   if(a.prisoner!=NULL) aroll-=LCSrandom(10);

   //Injured people suck at attacking, are like fish in a barrel to attackers
   if(mode==GAMEMODE_CHASEFOOT)
   {
      // If in a foot chase, double the debilitating effect of injuries
      healthmodroll(aroll,a);
      healthmodroll(droll,t);
      healthmodroll(droll,t);
   }
   else if (mode==GAMEMODE_CHASECAR)
   {
      // In a car chase, the driver is applying dodge rolls even for crippled people.
      healthmodroll(aroll,a);
      if (driver != NULL)
      {// if there is no driver, we already rolled a zero, so don't worry about further penalties.
         healthmodroll(droll,*driver);
      }
   }
   else
   {  
      // Any other case (site fight) normal penalties.
      healthmodroll(aroll,a);
      healthmodroll(droll,t);
   }

   // Prevent negative rolls
   if(aroll<0) aroll=0;
   if(droll<0) droll=0;

   // Weapon accuracy bonuses and penalties
   bonus+=attack_used->accuracy_bonus;

   //USE BULLETS
   int bursthits=0; // Tracks number of hits.

   int thrownweapons=0; // Used by thrown weapons to remove the weapons at the end of the turn if needed

   if(!a.is_armed()) //Move into WEAPON_NONE -XML
   {
      // Martial arts multi-strikes
      bursthits=1+LCSrandom(a.get_skill(SKILL_HANDTOHAND)/3+1);
      if(bursthits>5) bursthits=5;
      if(a.animalgloss) bursthits=1; // Whoops, must be human to use martial arts fanciness
   }
   else
   {
      if(mode==GAMEMODE_SITE && LCSrandom(100) < attack_used->fire.chance_causes_debris)
      {// TODO - In a car chase, debris should make driving harder for one round, or require a drive skill check to avoid damage
         sitechangest change(locx,locy,locz,SITEBLOCK_DEBRIS);
         location[cursite]->changes.push_back(change);
      }
      if(mode==GAMEMODE_SITE && LCSrandom(100) < attack_used->fire.chance)
      {// TODO - In a car chase, apply vehicle damage, with drive skill check to partially mitigate
         // Fire!
         if(!(levelmap[locx][locy][locz].flag & SITEBLOCK_FIRE_END) ||
            !(levelmap[locx][locy][locz].flag & SITEBLOCK_FIRE_PEAK) ||
            !(levelmap[locx][locy][locz].flag & SITEBLOCK_FIRE_START) ||
            !(levelmap[locx][locy][locz].flag & SITEBLOCK_DEBRIS))
         {
            levelmap[locx][locy][locz].flag|=SITEBLOCK_FIRE_START;
            sitecrime+=3;
            addjuice(a,5,500);
            criminalizeparty(LAWFLAG_ARSON);
            sitestory->crime.push_back(CRIME_ARSON);
         }
      }

      for(int i=0;i<attack_used->number_attacks;i++)
      {
         if(attack_used->uses_ammo)
         {
            if(a.get_weapon().get_ammoamount() > 0)
               a.get_weapon().decrease_ammo(1);
            else break;
         }
         else if(attack_used->thrown)
         {
            if(a.count_weapons()-thrownweapons > 0)
               thrownweapons++;
            else break;
         }

         if(sneak_attack)
         {
            bursthits=1; // Backstab only hits once
            break;
         }
         // Each shot in a burst is increasingly less likely to hit
         if(aroll+bonus-i*attack_used->successive_attacks_difficulty > droll)
            bursthits++;
      }
   }

   //HIT!
   if(aroll+bonus>droll)
   {
      strcat(str,t.name);
      strcat(str, "の");
      int w;
      bool canhit=false;

      for(w=0;w<BODYPARTNUM;w++)
      {
         if(!(t.wound[w]&WOUND_CLEANOFF) && !(t.wound[w]&WOUND_NASTYOFF))
         {
            canhit=true;
            break;
         }
      }

      do
      {
         int offset=0;
         if(aroll>droll+5)
            offset=4;  // NICE SHOT; MORE LIKELY TO HIT BODY/HEAD
         if(aroll>droll+10 &&
            (!(t.wound[BODYPART_HEAD]&(WOUND_CLEANOFF|WOUND_NASTYOFF)) ||
             !(t.wound[BODYPART_BODY]&(WOUND_CLEANOFF|WOUND_NASTYOFF))))
            offset=8;  // NO LIMB HITS HERE YOU AWESOME PERSON
         if(sneak_attack)
            offset=10; // Backstab! 2/3 body, 1/3 head
         if(aroll>droll+15 &&
            !(t.wound[BODYPART_HEAD]&(WOUND_CLEANOFF|WOUND_NASTYOFF)))
            offset=12; // BOOM AUTOMATIC HEADSHOT MOTHA******
         //Weighted location roll:
         //200% chance to hit body
         //50% chance to hit head
         w=offset+LCSrandom(13-offset);

         switch(w)
         {
         case 12:w=BODYPART_HEAD; break;
         case 11:
         case 10:
         case 9:
         case 8:w=BODYPART_BODY; break;
         case 7:
         case 3:w=BODYPART_ARM_RIGHT; break;
         case 6:
         case 2:w=BODYPART_ARM_LEFT; break;
         case 5:
         case 1:w=BODYPART_LEG_RIGHT; break;
         case 4:
         case 0:w=BODYPART_LEG_LEFT; break;
         }
      } while(((t.wound[w]&WOUND_CLEANOFF) || (t.wound[w]&WOUND_NASTYOFF)) && canhit==true);

      if(t.animalgloss==ANIMALGLOSS_TANK)
         switch(w)
         {
         case BODYPART_HEAD:strcat(str,"砲塔"); break;
         case BODYPART_BODY:strcat(str,"前面"); break;
         case BODYPART_ARM_RIGHT:strcat(str,"右側面"); break;
         case BODYPART_ARM_LEFT:strcat(str,"左側面"); break;
         case BODYPART_LEG_RIGHT:strcat(str,"右キャタピラ"); break;
         case BODYPART_LEG_LEFT:strcat(str,"左キャタピラ"); break;
         }
      else if(t.animalgloss==ANIMALGLOSS_ANIMAL) // FIXME: What about Six-legged Pigs?
         switch(w)
         {
         case BODYPART_HEAD:strcat(str,"頭部"); break;
         case BODYPART_BODY:strcat(str,"胴体"); break;
         case BODYPART_ARM_RIGHT:strcat(str,"右前足"); break;
         case BODYPART_ARM_LEFT:strcat(str,"左前足"); break;
         case BODYPART_LEG_RIGHT:strcat(str,"右後足"); break;
         case BODYPART_LEG_LEFT:strcat(str,"左後足"); break;
         }
      else
         switch(w)
         {
         case BODYPART_HEAD:strcat(str,"頭部"); break;
         case BODYPART_BODY:strcat(str,"胴体"); break;
         case BODYPART_ARM_RIGHT:strcat(str,"右腕"); break;
         case BODYPART_ARM_LEFT:strcat(str,"左腕"); break;
         case BODYPART_LEG_RIGHT:strcat(str,"右足"); break;
         case BODYPART_LEG_LEFT:strcat(str,"左足");break;
         }
      strcat(str, "に");

      // show multiple hits
      if(bursthits>1 && a.is_armed()) // Only show if not melee
      {
         if(!a.is_armed()) //Move into WEAPON_NONE? -XML
            strcat(str,"強烈に");
         else strcat(str,attack_used->hit_description);

         switch(bursthits)
         {
         case 1: break;
         case 2: strcat(str,"2回"); break;
         case 3: strcat(str,"3回"); break;
         case 4: strcat(str,"4回"); break;
         case 5: strcat(str,"5回"); break;
         default: strcat(str,tostring(bursthits)+"回"); break;
         }
      }
      else if(attack_used->always_describe_hit)
      {
         strcat(str,attack_used->hit_description);
      }
      if(sneak_attack) strcat(str, "不意打ち");
      else strcat(str,"命中");

      char damtype=0;
      int damamount=0;
      char strengthmin=1;
      char strengthmax=1;
      int severtype=-1;

      char damagearmor=0;
      char armorpiercing=0;
      int extraarmor=0;

      if (!a.is_armed())
      {
         strengthmin=5;
         strengthmax=10;
         while(bursthits) //Put into WEAPON_NONE -XML
         {
            damamount+=LCSrandom(5+a.get_skill(SKILL_HANDTOHAND))+1+a.get_skill(SKILL_HANDTOHAND);
            bursthits--;
         }
         if(!a.animalgloss) damtype|=WOUND_BRUISED;
         else
         {
            if(a.specialattack==ATTACK_CANNON)
            {
               damamount=LCSrandom(5000)+5000;
               armorpiercing=20;
               damtype|=WOUND_BURNED;
               damtype|=WOUND_TORN;
               damtype|=WOUND_SHOT;
               damtype|=WOUND_BLEEDING;
               strengthmin=0;
               strengthmax=0;
            }
            else if(a.specialattack==ATTACK_FLAME) damtype|=WOUND_BURNED;
            else if(a.specialattack==ATTACK_SUCK) damtype|=WOUND_CUT;
            else damtype|=WOUND_TORN;
            severtype=WOUND_NASTYOFF;
         }
      }
      else
      {
         if(attack_used->bruises) damtype|=WOUND_BRUISED;
         if(attack_used->cuts) damtype|=WOUND_CUT;
         if(attack_used->burns) damtype|=WOUND_BURNED;
         if(attack_used->tears) damtype|=WOUND_TORN;
         if(attack_used->shoots) damtype|=WOUND_SHOT;
         if(attack_used->bleeding) damtype|=WOUND_BLEEDING;

         strengthmin=attack_used->strength_min;
         strengthmax=attack_used->strength_max;
         severtype=attack_used->severtype;
         int random=attack_used->random_damage;
         int fixed=attack_used->fixed_damage;
         if(sneak_attack) fixed+=100;
         if(bursthits >= attack_used->critical.hits_required
            && LCSrandom(100) < attack_used->critical.chance)
         {
            if(attack_used->critical.random_damage_defined)
               random=attack_used->critical.random_damage;
            if(attack_used->critical.fixed_damage_defined)
               fixed=attack_used->critical.fixed_damage;
            if(attack_used->critical.severtype_defined)
               severtype=attack_used->critical.severtype;
         }
         while(bursthits > 0)
         {
            damamount+=LCSrandom(random)+fixed;
            bursthits--;
         }
         damagearmor=attack_used->damages_armor;
         armorpiercing=attack_used->armorpiercing;
      }

      // Coarse combat lethality reduction.
      //damamount/=2;

      if(t.squadid!=-1&&t.hireid==-1) // Plot Armor: if the founder is hit, inflict
         damamount/=2;                // 1/2 damage, because founders are cool

      int mod=0;

      if(strengthmax>strengthmin)
      {
         // Melee attacks: Maximum strength bonus, minimum
         // strength to deliver full damage
         int strength=a.attribute_roll(ATTRIBUTE_STRENGTH);
         if(strength>strengthmax) strength=(strengthmax+strength)/2;
         mod+=strength-strengthmin;
         armorpiercing+=(strength-strengthmin)/4;
      }

      //SKILL BONUS FOR GOOD ROLL
      mod+=aroll-droll;

      //DO THE HEALTH MOD ON THE WOUND
      mod-=t.attribute_roll(ATTRIBUTE_HEALTH);

      //Health and poor accuracy will only avoid critical hits, not stop low-damage attacks
      if(mod<0) mod=0;
      
      // In a car chase, the vehicle itself provides bonus armor
      int vehicleHitLocation = 0;
      if (mode==GAMEMODE_CHASECAR && vehicle != NULL)
      {
         vehicleHitLocation = vehicle->gethitlocation(w);
         extraarmor = vehicle->armorbonus(vehicleHitLocation);
         // TODO damage vehicle itself
      }

      int cardmg = damamount;
      damagemod(t,damtype,damamount,w,armorpiercing,mod,extraarmor);
      
      // Report vehicle protection effect
      if (mode==GAMEMODE_CHASECAR && vehicle != NULL && extraarmor > 0)
      {
         strcat(str, "、");
         strcat(str, vehicle->shortname()+"の");
         strcat(str, vehicle->getpartname(vehicleHitLocation));
         // Could the vehicle have bounced that round on its own?
         if (damamount==0)
         {
            Creature testDummy; // Spawn nude test dummy to see if body armor was needed to prevent damage
            damagemod(testDummy,damtype,cardmg,w,armorpiercing,mod,extraarmor);
            
            if (cardmg < 2) //fudge factor of 1 armor level due to randomness
            {
               strcpy(str, "で遮蔽");
            }
            else
            {
               strcpy(str, "を貫通");
            }
         }
         else
         {
            strcpy(str, "を貫通");
         }
      }
      
      // Temporary debug output for the damage roll
      #ifdef SHOWMECHANICS
      {
         char str[200];
         clearmessagearea();
         move(16,1);
         addstr_f("(ATK %d, DEF %d, DAMMOD %d, DAMAGE %d, AP %d)",aroll,droll,mod,damamount,armorpiercing);

         getkey();
      }
      #endif
      // Bullets caught by armor should bruise instead of poke holes.
      if(damamount<4 && damtype & WOUND_SHOT)
      {
         damtype &= ~(WOUND_SHOT|WOUND_BLEEDING);
         damtype |= WOUND_BRUISED;
      }
      if(damamount>0)
      {
         Creature *target=0;

         if(t.squadid!=-1&&t.hireid==-1&& //if the founder is hit...
           (damamount>t.blood||damamount>=10)&& //and lethal or potentially crippling damage is done...
           (w==BODYPART_HEAD||w==BODYPART_BODY)) //to a critical bodypart...
         {
            //Oh Noes!!!! Find a liberal to jump in front of the bullet!!!
            for(int i=0;i<6;i++)
            {
               if(activesquad->squad[i]==NULL) break;
               if(activesquad->squad[i]==&t) break;
               if(activesquad->squad[i]->get_attribute(ATTRIBUTE_HEART,true)>8&&
                  activesquad->squad[i]->get_attribute(ATTRIBUTE_AGILITY,true)>4)
               {
                  target=activesquad->squad[i];

                  clearmessagearea();
                  set_color(COLOR_GREEN,COLOR_BLACK,1);

                  move(16,1);
                  addstr(target->name, gamelog);
                  addstr("が", gamelog);
                  if(!t.alive) addstr("悲しくも", gamelog);
                  else addstr("勇敢にも", gamelog);
                  addstr(t.name, gamelog);
                  if(!t.alive) addstr("の遺体", gamelog);
                  addstr("をかばった! ", gamelog);
                  gamelog.newline();

                  addjuice(*target,10,1000);//Instant juice!! Way to take the bullet!!

                  getkey();

                  break;
               }
            }
         }
         if(!target) target=&t;//If nobody jumps in front of the attack,

         target->wound[w]|=damtype;

         int severamount=100;

         switch(w)
         {
         case BODYPART_HEAD:severamount=100;break;
         case BODYPART_BODY:severamount=1000;break;
         case BODYPART_ARM_RIGHT:severamount=200;break;
         case BODYPART_ARM_LEFT:severamount=200;break;
         case BODYPART_LEG_RIGHT:severamount=400;break;
         case BODYPART_LEG_LEFT:severamount=400;break;
         }

         if(severtype!=-1 && damamount>=severamount)
            target->wound[w]|=(char)severtype;

         if(w!=BODYPART_HEAD && w!=BODYPART_BODY && target->blood-damamount<=0 &&
            target->blood>0)
         {
            do
            {
               if(LCSrandom(100) < attack_used->no_damage_reduction_for_limbs_chance)
                  break;
               else damamount>>=1;
            } while(target->blood-damamount<=0);
         }

         if(damagearmor) armordamage(target->get_armor(),w,damamount);

         target->blood-=damamount;

         levelmap[locx][locy][locz].flag|=SITEBLOCK_BLOODY;

         if((target->wound[BODYPART_HEAD] & WOUND_CLEANOFF)||
            (target->wound[BODYPART_BODY] & WOUND_CLEANOFF)||
            (target->wound[BODYPART_HEAD] & WOUND_NASTYOFF)||
            (target->wound[BODYPART_BODY] & WOUND_NASTYOFF)||
            target->blood<=0)
         {
            if((w==BODYPART_HEAD && target->wound[BODYPART_HEAD] & WOUND_NASTYOFF)||
               (w==BODYPART_BODY && target->wound[BODYPART_BODY] & WOUND_NASTYOFF))
               bloodblast(&target->get_armor());

            char alreadydead=!target->alive;

            if(!alreadydead)
            {
               target->die();

               if(t.align==-a.align)
                  addjuice(a,5+t.juice/20,1000); // Instant juice
               else addjuice(a,-(5+t.juice/20),-50);

               if(target->squadid!=-1)
               {
                  if(target->align==1) stat_dead++;
               }
               else if(target->enemy()&&(t.animalgloss!=ANIMALGLOSS_ANIMAL||law[LAW_ANIMALRESEARCH]==2))
               {
                  stat_kills++;
                  if(location[cursite]->siege.siege) location[cursite]->siege.kills++;
                  if(location[cursite]->siege.siege && t.animalgloss==ANIMALGLOSS_TANK) location[cursite]->siege.tanks--;
                  if(location[cursite]->renting==RENTING_CCS)
                  {
                     if(target->type==CREATURE_CCS_ARCHCONSERVATIVE) ccs_boss_kills++;
                     ccs_siege_kills++;
                  }
               }
               if(target->squadid==-1 &&
                 (target->animalgloss!=ANIMALGLOSS_ANIMAL||law[LAW_ANIMALRESEARCH]==2) &&
                 !sneak_attack)
               {
                  sitecrime+=10;
                  sitestory->crime.push_back(CRIME_KILLEDSOMEBODY);
                  if(a.squadid!=-1) criminalizeparty(LAWFLAG_MURDER);
               }
            }

            if(w==BODYPART_HEAD && target->wound[BODYPART_HEAD] & WOUND_CLEANOFF)
               strcat(str,"、切り落とされた!");
            else if(w==BODYPART_BODY && target->wound[BODYPART_BODY] & WOUND_CLEANOFF)
               strcat(str,"、真っ二つだ!");
            else if(w==BODYPART_HEAD && target->wound[BODYPART_HEAD] & WOUND_NASTYOFF)
               strcat(str,"、砕け散った!");
            else if(w==BODYPART_BODY && target->wound[BODYPART_BODY] & WOUND_NASTYOFF)
               strcat(str,"、バラバラになった!");
            else strcat(str,attack_used->hit_punctuation);
            move(17,1);
            //set_color(COLOR_WHITE,COLOR_BLACK,1);
            if(goodguyattack) set_color(COLOR_GREEN,COLOR_BLACK,1);
            else set_color(COLOR_RED,COLOR_BLACK,1);
            addstr(str, gamelog);
            gamelog.newline();

            getkey();

            if(!alreadydead)
            {
               severloot(t,groundloot);
               clearmessagearea();
               adddeathmessage(*target);

               getkey();

               if(target->prisoner!=NULL) freehostage(t,1);
            }
         }
         else
         {
            if(target->wound[w] & WOUND_CLEANOFF) strcat(str,"、切り落とされた!");
            else if(target->wound[w] & WOUND_NASTYOFF) strcat(str,"、ちぎれ飛んだ!");
            else strcat(str,attack_used->hit_punctuation);

            if(target->wound[w] & WOUND_NASTYOFF) bloodblast(&target->get_armor());

            if(goodguyattack) set_color(COLOR_GREEN,COLOR_BLACK,1);
            else set_color(COLOR_RED,COLOR_BLACK,1);
            move(17,1);
            //set_color(COLOR_WHITE,COLOR_BLACK,1);
            addstr(str, gamelog);
            gamelog.newline();

            printparty();
            if(mode==GAMEMODE_CHASECAR||
               mode==GAMEMODE_CHASEFOOT) printchaseencounter();
            else printencounter();

            getkey();

            //SPECIAL WOUNDS
            if(!(target->wound[w] & (WOUND_CLEANOFF|WOUND_NASTYOFF))&&
                !target->animalgloss)
            {
               char heavydam=0,breakdam=0,pokedam=0;
               if(damamount>=12) //JDS -- 2x damage needed
               {
                  if(damtype & WOUND_SHOT) heavydam=1;
                  if(damtype & WOUND_BURNED) heavydam=1;
                  if(damtype & WOUND_TORN) heavydam=1;
                  if(damtype & WOUND_CUT) heavydam=1;
               }

               if(damamount>=10) //JDS -- 2x damage needed
               {
                  if(damtype & WOUND_SHOT) pokedam=1;
                  if(damtype & WOUND_TORN) pokedam=1;
                  if(damtype & WOUND_CUT) pokedam=1;
               }

               if((damtype & WOUND_BRUISED)&&damamount>=50) breakdam=1;
               if((damtype & WOUND_SHOT)&&damamount>=50) breakdam=1;
               if((damtype & WOUND_TORN)&&damamount>=50) breakdam=1;
               if((damtype & WOUND_CUT)&&damamount>=50) breakdam=1;

               if(w==BODYPART_HEAD)
               {
                  clearmessagearea();
                  if(goodguyattack) set_color(COLOR_GREEN,COLOR_BLACK,1);
                  else set_color(COLOR_RED,COLOR_BLACK,1);

                  switch(LCSrandom(7))
                  {
                     case 0:
                        if((target->special[SPECIALWOUND_RIGHTEYE]||
                            target->special[SPECIALWOUND_LEFTEYE]||
                            target->special[SPECIALWOUND_NOSE])&&heavydam)
                        {
                           move(16,1);
                           addstr(target->name, gamelog);
                           if(damtype & WOUND_SHOT)addstr("の顔が吹き飛ばされた!", gamelog);
                           else if(damtype & WOUND_BURNED)addstr("の顔が焼き払われた!", gamelog);
                           else if(damtype & WOUND_TORN)addstr("の顔が引き裂かれた!", gamelog);
                           else if(damtype & WOUND_CUT)addstr("の顔が切り刻まれた!", gamelog);
                           else addstr("の顔がえぐり取られた!", gamelog);
                           gamelog.newline();

                           getkey();

                           target->special[SPECIALWOUND_RIGHTEYE]=0;
                           target->special[SPECIALWOUND_LEFTEYE]=0;
                           target->special[SPECIALWOUND_NOSE]=0;
                           if(target->blood>20)target->blood=20;
                        }
                        break;
                     case 1:
                        if(target->special[SPECIALWOUND_TEETH]>0)
                        {
                           int teethminus=LCSrandom(TOOTHNUM)+1;
                           if(teethminus>target->special[SPECIALWOUND_TEETH])
                              teethminus=target->special[SPECIALWOUND_TEETH];

                           move(16,1);
                           if(teethminus>1)
                           {
                              addstr(target->name, gamelog);
                              addstr("の", gamelog);
                              addstr(teethminus, gamelog);
                              addstr("本の歯", gamelog);
                              if(teethminus==target->special[SPECIALWOUND_TEETH])
                                 addstr("全て", gamelog);
                              addstr("が", gamelog);
                           }
                           else if(target->special[SPECIALWOUND_TEETH]>1)
                           {
                              addstr(target->name, gamelog);
                              addstr("の歯が1本", gamelog);
                           }
                           else
                           {
                              addstr(target->name, gamelog);
                              addstr("の最後の歯が", gamelog);
                           }

                           if(damtype & WOUND_SHOT)addstr("撃たれて吹き飛んだ!", gamelog);
                           else if(damtype & WOUND_BURNED)addstr("焼け落ちた!", gamelog);
                           else if(damtype & WOUND_TORN)addstr("えぐり取られた!", gamelog);
                           else if(damtype & WOUND_CUT)addstr("切り落とされた!", gamelog);
                           else addstr("抜け落ちた!", gamelog);
                           gamelog.newline();

                           getkey();

                           target->special[SPECIALWOUND_TEETH]-=teethminus;
                        }
                        break;
                     case 2:
                        if(target->special[SPECIALWOUND_RIGHTEYE]&&heavydam)
                        {
                           move(16,1);
                           addstr(target->name, gamelog);
                           if(damtype & WOUND_SHOT)addstr("の右目が吹き飛んだ!", gamelog);
                           else if(damtype & WOUND_BURNED)addstr("の右目が焼け落ちた!", gamelog);
                           else if(damtype & WOUND_TORN)addstr("の右目がちぎれ飛んだ!", gamelog);
                           else if(damtype & WOUND_CUT)addstr("の右目が切り刻まれた!", gamelog);
                           else addstr("の右目が飛び出した!", gamelog);
                           gamelog.newline();

                           getkey();

                           target->special[SPECIALWOUND_RIGHTEYE]=0;
                           if(target->blood>50)target->blood=50;
                        }
                        break;
                     case 3:
                        if(target->special[SPECIALWOUND_LEFTEYE]&&heavydam)
                        {
                           move(16,1);
                           addstr(target->name, gamelog);
                           if(damtype & WOUND_SHOT)addstr("の左目が吹き飛んだ!", gamelog);
                           else if(damtype & WOUND_BURNED)addstr("の左目が焼け落ちた!", gamelog);
                           else if(damtype & WOUND_TORN)addstr("の左目がちぎれ飛んだ!", gamelog);
                           else if(damtype & WOUND_CUT)addstr("の左目が切り刻まれた!", gamelog);
                           else addstr("の左目が飛び出した!", gamelog);
                           gamelog.newline();

                           getkey();

                           target->special[SPECIALWOUND_LEFTEYE]=0;
                           if(target->blood>50)target->blood=50;
                        }
                        break;
                     case 4:
                        if(target->special[SPECIALWOUND_TONGUE]&&heavydam)
                        {
                           move(16,1);
                           addstr(target->name, gamelog);
                           if(damtype & WOUND_SHOT)addstr("の舌が吹き飛んだ!", gamelog);
                           else if(damtype & WOUND_BURNED)addstr("の舌が焼け落ちた!", gamelog);
                           else if(damtype & WOUND_TORN)addstr("の舌がちぎれ飛んだ!", gamelog);
                           else if(damtype & WOUND_CUT)addstr("の舌が切り落とされた!", gamelog);
                           else addstr("の舌が引きちぎられた!", gamelog);
                           gamelog.newline();

                           getkey();

                           target->special[SPECIALWOUND_TONGUE]=0;
                           if(target->blood>50)target->blood=50;
                        }
                        break;
                     case 5:
                        if(target->special[SPECIALWOUND_NOSE]&&heavydam)
                        {
                           move(16,1);
                           addstr(target->name, gamelog);
                           if(damtype & WOUND_SHOT)addstr("の鼻が吹き飛んだ!", gamelog);
                           else if(damtype & WOUND_BURNED)addstr("の鼻が焼け落ちた!", gamelog);
                           else if(damtype & WOUND_TORN)addstr("の鼻がちぎれ飛んだ!", gamelog);
                           else if(damtype & WOUND_CUT)addstr("の鼻が切り落とされた!", gamelog);
                           else addstr("の鼻がえぐり取られた!", gamelog);
                           gamelog.newline();

                           getkey();

                           target->special[SPECIALWOUND_NOSE]=0;
                           if(target->blood>50)target->blood=50;
                        }
                        break;
                     case 6:
                        if(target->special[SPECIALWOUND_NECK]&&breakdam)
                        {
                           move(16,1);
                           addstr(target->name, gamelog);
                           if(damtype & WOUND_SHOT)addstr("の首の骨が砕けた!", gamelog);
                           else addstr("の首の骨が折れた!", gamelog);
                           gamelog.newline();

                           getkey();

                           target->special[SPECIALWOUND_NECK]=0;
                           if(target->blood>20)target->blood=20;
                        }
                        break;
                  }
               }
               if(w==BODYPART_BODY)
               {
                  clearmessagearea();
                  //set_color(COLOR_MAGENTA,COLOR_BLACK,1);
                  if (goodguyattack) set_color(COLOR_GREEN,COLOR_BLACK,1);
                  else set_color(COLOR_RED,COLOR_BLACK,1);

                  switch(LCSrandom(11))
                  {
                  case 0:
                     if(target->special[SPECIALWOUND_UPPERSPINE]&&breakdam)
                     {
                        move(16,1);
                        addstr(target->name, gamelog);
                        if(damtype & WOUND_SHOT) addstr("の上部脊椎か砕けた!", gamelog);
                        else addstr("の上部脊椎が折れた!", gamelog);
                        gamelog.newline();

                        getkey();

                        target->special[SPECIALWOUND_UPPERSPINE]=0;
                        if(target->blood>20) target->blood=20;
                     }
                     break;
                  case 1:
                     if(target->special[SPECIALWOUND_LOWERSPINE]&&breakdam)
                     {
                        move(16,1);
                        addstr(target->name, gamelog);
                        if(damtype & WOUND_SHOT)addstr("の下部脊椎が砕けた!", gamelog);
                        else addstr("の下部脊椎が折れた!", gamelog);
                        gamelog.newline();

                        getkey();

                        target->special[SPECIALWOUND_LOWERSPINE]=0;
                        if(target->blood>20) target->blood=20;
                     }
                     break;
                  case 2:
                     if(target->special[SPECIALWOUND_RIGHTLUNG]&&pokedam)
                     {
                        move(16,1);
                        addstr(target->name, gamelog);
                        if(damtype & WOUND_SHOT)addstr("の右肺を貫通した!", gamelog);
                        else if(damtype & WOUND_TORN)addstr("の右肺が引き裂かれた!", gamelog);
                        else addstr("の右肺が破裂した!", gamelog);
                        gamelog.newline();

                        getkey();

                        target->special[SPECIALWOUND_RIGHTLUNG]=0;
                        if(target->blood>20) target->blood=20;
                     }
                     break;
                  case 3:
                     if(target->special[SPECIALWOUND_LEFTLUNG]&&pokedam)
                     {
                        move(16,1);
                        addstr(target->name, gamelog);
                        if(damtype & WOUND_SHOT)addstr("の右肺を貫通した!", gamelog);
                        else if(damtype & WOUND_TORN)addstr("の左肺が引き裂かれた!", gamelog);
                        else addstr("の左肺が破裂した!", gamelog);
                        gamelog.newline();

                        getkey();

                        target->special[SPECIALWOUND_LEFTLUNG]=0;
                        if(target->blood>20) target->blood=20;
                     }
                     break;
                  case 4:
                     if(target->special[SPECIALWOUND_HEART]&&pokedam)
                     {
                        move(16,1);
                        addstr(target->name, gamelog);
                        if(damtype & WOUND_SHOT)addstr("の心臓を貫通した!", gamelog);
                        else if(damtype & WOUND_TORN)addstr("の心臓が引き裂かれた!", gamelog);
                        else addstr("の心臓が破裂した!", gamelog);
                        gamelog.newline();

                        getkey();

                        target->special[SPECIALWOUND_HEART]=0;
                        if(target->blood>3) target->blood=3;
                     }
                     break;
                  case 5:
                     if(target->special[SPECIALWOUND_LIVER]&&pokedam)
                     {
                        move(16,1);
                        addstr(target->name, gamelog);
                        if(damtype & WOUND_SHOT)addstr("の肝臓を貫通した!", gamelog);
                        else if(damtype & WOUND_TORN)addstr("の肝臓が引き裂かれた!", gamelog);
                        else addstr("の肝臓が破裂した!", gamelog);
                        gamelog.newline();

                        getkey();

                        target->special[SPECIALWOUND_LIVER]=0;
                        if(target->blood>50) target->blood=50;
                     }
                     break;
                  case 6:
                     if(target->special[SPECIALWOUND_STOMACH]&&pokedam)
                     {
                        move(16,1);
                        addstr(target->name, gamelog);
                        if(damtype & WOUND_SHOT)addstr("の胃を貫通した!", gamelog);
                        else if(damtype & WOUND_TORN)addstr("の胃が引き裂かれた!", gamelog);
                        else addstr("の胃が破裂した!", gamelog);
                        gamelog.newline();

                        getkey();

                        target->special[SPECIALWOUND_STOMACH]=0;
                        if(target->blood>50) target->blood=50;
                     }
                     break;
                  case 7:
                     if(target->special[SPECIALWOUND_RIGHTKIDNEY]&&pokedam)
                     {
                        move(16,1);
                        addstr(target->name, gamelog);
                        if(damtype & WOUND_SHOT)addstr("の右腎臓を貫通した!", gamelog);
                        else if(damtype & WOUND_TORN)addstr("の右腎臓が引き裂かれた!", gamelog);
                        else addstr("の右腎臓が破裂した!", gamelog);
                        gamelog.newline();

                        getkey();

                        target->special[SPECIALWOUND_RIGHTKIDNEY]=0;
                        if(target->blood>50) target->blood=50;
                     }
                     break;
                  case 8:
                     if(target->special[SPECIALWOUND_LEFTKIDNEY]&&pokedam)
                     {
                        move(16,1);
                        addstr(target->name, gamelog);
                        if(damtype & WOUND_SHOT)addstr("の左腎臓を貫通した!", gamelog);
                        else if(damtype & WOUND_TORN)addstr("の左腎臓が引き裂かれた!", gamelog);
                        else addstr("の左腎臓が破裂した!", gamelog);
                        gamelog.newline();

                        getkey();

                        target->special[SPECIALWOUND_LEFTKIDNEY]=0;
                        if(target->blood>50) target->blood=50;
                     }
                     break;
                  case 9:
                     if(target->special[SPECIALWOUND_SPLEEN]&&pokedam)
                     {
                        move(16,1);
                        addstr(target->name, gamelog);
                        if(damtype & WOUND_SHOT)addstr("の脾臓を貫通した!", gamelog);
                        else if(damtype & WOUND_TORN)addstr("の脾臓が引き裂かれた!", gamelog);
                        else addstr("の脾臓が破裂した!", gamelog);
                        gamelog.newline();

                        getkey();

                        target->special[SPECIALWOUND_SPLEEN]=0;
                        if(target->blood>50) target->blood=50;
                     }
                     break;
                  case 10:
                     if(target->special[SPECIALWOUND_RIBS]>0&&breakdam)
                     {
                        int ribminus=LCSrandom(RIBNUM)+1;
                        if(ribminus>target->special[SPECIALWOUND_RIBS]) ribminus=target->special[SPECIALWOUND_RIBS];

                        move(16,1);
                        if(ribminus>1)
                        {
                           addstr(target->name, gamelog);
                           addstr("の", gamelog);
                           addstr(ribminus, gamelog);
                           addstr("本の肋骨", gamelog);
                           if(ribminus==target->special[SPECIALWOUND_RIBS])
                              addstr("全て", gamelog);
                           addstr("が", gamelog);
                        }
                        else if(target->special[SPECIALWOUND_RIBS]>1)
                        {
                           addstr(target->name, gamelog);
                           addstr("の肋骨が1本", gamelog);
                        }
                        else
                        {
                           addstr(target->name, gamelog);
                           addstr("の最後の肋骨が", gamelog);
                        }

                        if(damtype & WOUND_SHOT)addstr("打ち抜かれた!", gamelog);
                        else addstr("折れた!", gamelog);
                        gamelog.newline();

                        getkey();

                        target->special[SPECIALWOUND_RIBS]-=ribminus;
                     }
                     break;
                  }
               }

               severloot(*target,groundloot);
            }

            //set_color(COLOR_WHITE,COLOR_BLACK,1);
         }
      }
      else
      {
         set_color(COLOR_YELLOW,COLOR_BLACK,1);
         strcat(str,"! だが効かなかった。");
         move(17,1);
         addstr(str, gamelog);
         gamelog.newline();

         printparty();
         if(mode==GAMEMODE_CHASECAR||
            mode==GAMEMODE_CHASEFOOT) printchaseencounter();
         else printencounter();

         getkey();
      }
   }
   else
   {
      set_color(COLOR_WHITE,COLOR_BLACK,1);

      if(melee && aroll<droll-10 && t.blood>70 && t.animalgloss==ANIMALGLOSS_NONE
         && t.is_armed() && t.get_weapon().get_attack(false,true,true) != NULL)
      {

         strcpy(str,t.name);
         strcat(str,"は身をかわして反撃した!");
         move(17,1);
         addstr(str, gamelog);
         gamelog.newline();

         getkey();

         goodguyattack = !goodguyattack;
         char actual_dummy;
         attack(t,a,0,actual_dummy,true);
         goodguyattack = !goodguyattack;
      }//TODO if missed person, but vehicle is large, it might damage the car. 
      else
      {
         if(sneak_attack)
         {
             strcpy(str, t.name);
             switch(LCSrandom(4))
             {
                 case 0: strcat(str,"はあと少しのところで気づいた!"); break;
                 case 1: strcat(str,"は見破った!"); break;
                 case 2: strcat(str,"は体をひねって攻撃を避けた!"); break;
                 default: strcat(str,"は飛び退き、大声で助けを呼んだ!"); break;
             }
             sitealarm=1;
         }
         else
         {
            if (mode==GAMEMODE_CHASECAR)
            {
               if (driver!=NULL)
                   strcpy(str, driver->name);
               switch(droll) // If no driver then droll is 0.
               {
                  case 1: strcpy(str, a.name); strcat(str,"は外した!"); break;
                  case 2: strcpy(str, a.name); strcat(str,"はあと少しのところで外した!"); break;
                  case 3: strcat(str,"は車線にも弾道にも車を合わせていられないようだ!"); break;
                  case 4: strcat(str,"はデタラメに蛇行した!"); break;
                  case 5: strcat(str,"は他の車に割り込み、攻撃は遮られた!"); break;
                  case 6: strcat(str,"は丘の道の向こう側に隠れた!"); break;
                  case 7: strcat(str,"はあと数秒のところで車線を変えた!"); break;
                  case 8: strcat(str,"が急加速して当たらなかった!"); break;
                  case 9: strcat(str,"は左に曲がるふりをして急に右に曲がった!"); break;
                  case 10: strcat(str,"は右に曲がるふりをして急に左に曲がった!"); break;
                  case 11: strcat(str,"は減速するふりをして急加速した!"); break;
                  case 12: strcat(str,"はトラックの反対側に回り込んだ!"); break;
                  case 13: strcat(str,"はタクシーの列を蛇行して通り抜けた!"); break;
                  case 14: strcat(str,"はホットドッグカートの後ろに回りこんだ!"); break;
                  case 15: strcat(str,"は弾を避けるため橋脚の間に潜り込んだ!"); break;
                  case 16: strcat(str,"は急カーブしてビルの陰に回りこんだ!"); break;
                  case 17: strcat(str,"は急発進して車の隙間に滑り込んだ!"); break;
                  case 18: strcat(str,"は弾を避けるため急カーブした!"); break;
                  default: strcpy(str, a.name); strcat(str,"は完全に外した!"); break; // You failed to hit someone who probably rolled a zero.  You should feel bad.
               }
            }else{
               strcpy(str, t.name);
               switch(droll)
               {
                  case 1: strcpy(str, a.name); strcat(str,"は外した!"); break;
                  case 2: strcpy(str, a.name); strcat(str,"はあと少しのところで外した!"); break;
                  case 3: strcat(str,"は反対方向に転がって避けた!"); break;
                  case 4: strcat(str,"はわずかのところで跳び退いた!"); break;
                  case 5: strcat(str,"はジャンプして避けた!"); break;
                  case 6: strcat(str,"は物陰に身を潜めた!"); break;
                  case 7: strcat(str,"はうまく物陰に隠れた!"); break;
                  case 8: strcat(str,"は転がって攻撃を避けた!"); break;
                  case 9: strcat(str,"はわずかのところで避けた!"); break;
                  case 10: strcat(str,"はジャンプして攻撃を避けた!"); break;
                  case 11: strcat(str,"は優雅に飛び込んで攻撃を避けた!"); break;
                  case 12: strcat(str,"は体をひねって攻撃を避けた!"); break;
                  case 13: strcat(str,"は回転して避けた!"); break;
                  case 14: strcat(str,"はマトリックス避けをした!"); break; // You saying I can dodge bullets?
                  case 15: strcat(str,"は難なく攻撃を避けた!"); break;
                  case 16: strcat(str,"はわずかに体を曲げて避けた!"); break;
                  case 17: strcat(str,"は堂々と避けた!"); break;
                  case 18: strcat(str,"はまるで睨みつけただけで攻撃を避けたようだ!"); break; //When you're ready, you won't have to.
                  default: strcpy(str, a.name); strcat(str,"は完全に外した!"); break; // You failed to hit someone who probably rolled a zero.  You should feel bad.
               }
            }
         }
         move(17,1);
         addstr(str, gamelog);
         gamelog.newline();
         printparty();
         if(mode==GAMEMODE_CHASECAR||
            mode==GAMEMODE_CHASEFOOT) printchaseencounter();
         else printencounter();

         getkey();
      }
   }

   for(;thrownweapons>0;thrownweapons--)
   {
      if(a.has_thrown_weapon)
         a.ready_another_throwing_weapon();
      a.drop_weapon(NULL);
   }

   actual=1;
   return;
}



/* modifies a combat roll based on the creature's critical injuries */
void healthmodroll(int &aroll,Creature &a)
{
   if(a.special[SPECIALWOUND_RIGHTEYE]!=1) aroll-=LCSrandom(2);
   if(a.special[SPECIALWOUND_LEFTEYE]!=1) aroll-=LCSrandom(2);
   if(a.special[SPECIALWOUND_RIGHTEYE]!=1&&
      a.special[SPECIALWOUND_LEFTEYE]!=1) aroll-=LCSrandom(20);
   if(a.special[SPECIALWOUND_RIGHTLUNG]!=1) aroll-=LCSrandom(8);
   if(a.special[SPECIALWOUND_LEFTLUNG]!=1) aroll-=LCSrandom(8);
   if(a.special[SPECIALWOUND_HEART]!=1) aroll-=LCSrandom(10);
   if(a.special[SPECIALWOUND_LIVER]!=1) aroll-=LCSrandom(5);
   if(a.special[SPECIALWOUND_STOMACH]!=1) aroll-=LCSrandom(5);
   if(a.special[SPECIALWOUND_RIGHTKIDNEY]!=1) aroll-=LCSrandom(5);
   if(a.special[SPECIALWOUND_LEFTKIDNEY]!=1) aroll-=LCSrandom(5);
   if(a.special[SPECIALWOUND_SPLEEN]!=1) aroll-=LCSrandom(4);
   if(a.special[SPECIALWOUND_LOWERSPINE]!=1) aroll-=LCSrandom(100);
   if(a.special[SPECIALWOUND_UPPERSPINE]!=1) aroll-=LCSrandom(200);
   if(a.special[SPECIALWOUND_NECK]!=1) aroll-=LCSrandom(300);
   if(a.special[SPECIALWOUND_RIBS]<RIBNUM) aroll-=LCSrandom(5);
   if(a.special[SPECIALWOUND_RIBS]<RIBNUM/2) aroll-=LCSrandom(5);
   if(a.special[SPECIALWOUND_RIBS]==0) aroll-=LCSrandom(5);
}



/* adjusts attack damage based on armor, other factors */
void damagemod(Creature &t,char &damtype,int &damamount,
               char hitlocation,char armorpenetration,int mod,int extraarmor)
{
   int armor=t.get_armor().get_armor(hitlocation);

   if(t.animalgloss==ANIMALGLOSS_TANK)
   {
      if(damtype!=WOUND_BURNED) armor=15;
      else armor=10;
   }


   //if(t.get_armor().get_quality()>1)
      armor-=t.get_armor().get_quality()-1;
   if(t.get_armor().is_damaged())
      armor-=1;

   if(armor<0) armor=0; // Possible from second-rate clothes
   armor += extraarmor; // Add vehicle armor 

   int mod2=armor+LCSrandom(armor+1)-armorpenetration;
   if(mod2>0) mod-=mod2*2;

   if(mod>10) mod=10; // Cap damage multiplier (every 5 points adds 1x damage)

   if(mod<=-20) damamount>>=8;  //Cars plus heavy armor can be really tough.
   else if(mod<=-14) damamount>>=7;
   else if(mod<=-8) damamount>>=6;
   else if(mod<=-6) damamount>>=5;
   else if(mod<=-4) damamount>>=4;
   else if(mod<=-3) damamount>>=3;
   else if(mod<=-2) damamount>>=2;
   else if(mod<=-1) damamount>>=1;
   else if(mod>=0) damamount=(int)((float)damamount * (1.0f + 0.2f*mod));

   // Firefighter's bunker gear reduces fire damage by 3/4
   if((damtype & WOUND_BURNED) && t.get_armor().has_fireprotection())
   {
      // Damaged gear isn't as effective as undamaged gear
      if(t.get_armor().is_damaged())
         damamount>>=1; // Only half as much damage reduction
      else
         damamount>>=2; // Full damage reduction
   }

   if(damamount<0)damamount=0;
}


void specialattack(Creature &a, Creature &t, char &actual)
{
   std::string s = "";
   static const char *judge_debate[]   =
   {
      "に死刑制度に関する討論を仕掛けてきた",
      "に同性愛者の権利に関する討論を仕掛けてきた",
      "に言論の自由に関する討論を仕掛けてきた",
      "に修正第2条に関する討論を仕掛けてきた"
   };

   static const char *conservative_ceo_debate[] =
   {
      "にデリバティブについて説明した",
      "にブードゥー経済学を正当化した",
      "にレーガン大統領を賛美した",
      "に減税に関する討論を仕掛けてきた",
      "に保守思想について説明した",
      "をディナーに誘った",
      "に副社長の座を提案した",
      "に$1000の紙幣を見せた",
      "に財政政策に関する討論を仕掛けてきた",
      "にストック・オプションを提供した"
   };

   static const char *other_ceo_debate[] =
   {
      "に財政政策に関する討論を仕掛けてきた",
      "にブードゥー経済学をあざ笑った",
      "にレーガン大統領を批判した",
      "に減税に関する討論を仕掛けてきた",
      "にリベラル思想について説明した"
   };

   static const char *conservative_politician_debate[] =
   {
      "に死刑制度に関する討論を仕掛けてきた",
      "に同性愛者の権利に関する討論を仕掛けてきた",
      "に言論の自由に関する討論を仕掛けてきた",
      "に修正第2条に関する討論を仕掛けてきた",
      "にブードゥー経済学を正当化した",
      "にレーガン大統領を賛美した",
      "に減税に関する討論を仕掛けてきた",
      "に保守思想について説明した",
      "をディナーに誘った",
      "に財政政策に関する討論を仕掛けてきた",
      "に暖かく話しかけた",
      "に微笑んだ"
   };

   static const char *other_politician_debate[] =
   {
      "に死刑制度に関する討論を仕掛けてきた",
      "に同性愛者の権利に関する討論を仕掛けてきた",
      "に言論の自由に関する討論を仕掛けてきた",
      "に修正第2条に関する討論を仕掛けてきた",
      "にブードゥー経済学をあざ笑った",
      "にレーガン大統領を批判した",
      "に減税に関する討論を仕掛けてきた",
      "にリベラル思想について説明した",
      "をディナーに誘った",
      "に財政政策に関する討論を仕掛けてきた",
      "に暖かく話しかけた",
      "に微笑んだ"
   };

   static const char *media_debate[] =
   {
      "にウィンクした",
      "に微笑んだ",
      "に作り笑いをした",
      "に暖かく話しかけた",
      "にスローガンを叫んだ"
   };

   static const char *military_debate[] =
   {
      "に忠誠の誓いをそらんじた",
      "に安全保障に関する討論を仕掛けてきた",
      "にテロに関する討論を仕掛けてきた",
      "に退役軍人について話した",
      "に防衛費について説明した"
   };

   static const char *police_debate[] =
   {
      "を説得しようとした",
      "に公正な裁判を約束した",
      "の話を聞こうとした",
      "の協力を得ようとした",
      "にハグを提案した",
      "にカウンセリングを勧めた",
      "にテディ・ベアを渡した"
   };

   int resist=0;
   char str[200];

   clearmessagearea();
   set_color(COLOR_WHITE,COLOR_BLACK,1);

   strcpy(str,a.name);
   strcat(str,"は");

   int attack=0;
   if(a.align!=1)
      attack=a.attribute_roll(ATTRIBUTE_WISDOM)+t.get_attribute(ATTRIBUTE_WISDOM,false);
   else if(a.align==1)
      attack=a.attribute_roll(ATTRIBUTE_HEART)+t.get_attribute(ATTRIBUTE_HEART,false);

   switch(a.type)
   {
      case CREATURE_JUDGE_CONSERVATIVE:
      case CREATURE_JUDGE_LIBERAL:
         strcat(str,t.name);
         strcat(str,pickrandom(judge_debate));
         strcat(str,"!");
         if(t.align==1)
            resist=t.skill_roll(SKILL_LAW)+
                   t.attribute_roll(ATTRIBUTE_HEART);
         else
            resist=t.skill_roll(SKILL_LAW)+
                   t.attribute_roll(ATTRIBUTE_WISDOM);
         attack+=a.skill_roll(SKILL_LAW);
         break;
      case CREATURE_SCIENTIST_EMINENT:
         strcat(str,t.name);
         switch(LCSrandom(3))
         {
            case 0:strcat(str,"に科学的方法論について討論を仕掛けてきた");break;
            case 1:if(a.align==-1)strcat(str,"に研究の有用性を説明した");
                   else strcat(str,"に研究倫理について説明した");break;
            case 2:strcat(str,"に科学的方法論について議論を仕掛けてきた");break;
         }
         strcat(str,"!");
         if(t.align==1)
            resist=t.skill_roll(SKILL_SCIENCE)+
                   t.attribute_roll(ATTRIBUTE_HEART);
         else
            resist=t.skill_roll(SKILL_SCIENCE)+
                   t.attribute_roll(ATTRIBUTE_WISDOM);
         attack+=a.skill_roll(SKILL_SCIENCE);
         break;
      case CREATURE_POLITICIAN:
         strcat(str,t.name);
         if(a.align==-1)
            strcat(str,pickrandom(conservative_politician_debate));
         else
            strcat(str,pickrandom(other_politician_debate));
         strcat(str,"!");
         if(t.align==1)
            resist=t.skill_roll(SKILL_LAW)+
                   t.attribute_roll(ATTRIBUTE_HEART);
         else
            resist=t.skill_roll(SKILL_LAW)+
                   t.attribute_roll(ATTRIBUTE_WISDOM);
         attack+=a.skill_roll(SKILL_LAW);
         break;
      case CREATURE_CORPORATE_CEO:
         strcat(str,t.name);
         if(a.align==-1)
            strcat(str,pickrandom(conservative_ceo_debate));
         else
            strcat(str,pickrandom(other_ceo_debate));
         strcat(str,"!");
         if(t.align==1)
            resist=t.skill_roll(SKILL_BUSINESS)+
                   t.attribute_roll(ATTRIBUTE_HEART);
         else
            resist=t.skill_roll(SKILL_BUSINESS)+
                   t.attribute_roll(ATTRIBUTE_WISDOM);
         attack+=a.skill_roll(SKILL_BUSINESS);
         break;
      case CREATURE_RADIOPERSONALITY:
      case CREATURE_NEWSANCHOR:
         strcat(str,t.name);
         strcat(str,pickrandom(media_debate));
         strcat(str,"!");
         if(t.align==1)
            resist=t.attribute_roll(ATTRIBUTE_HEART);
         else
            resist=t.attribute_roll(ATTRIBUTE_WISDOM);
         attack+=a.attribute_roll(ATTRIBUTE_CHARISMA);
         break;
      case CREATURE_MILITARYOFFICER:
         strcat(str,t.name);
         strcat(str,pickrandom(military_debate));
         strcat(str,"!");
         if(t.align==1)
            resist=t.attribute_roll(ATTRIBUTE_HEART);
         else
            resist=t.attribute_roll(ATTRIBUTE_WISDOM);
         attack+=a.attribute_roll(ATTRIBUTE_CHARISMA);
         break;
      case CREATURE_COP:
         if(a.enemy())
         {
            strcat(str,t.name);
            strcat(str,pickrandom(police_debate));
            strcat(str,"!");

            resist=t.attribute_roll(ATTRIBUTE_HEART);

            attack+=a.skill_roll(SKILL_PERSUASION);
            break;
         }
         //No break. If the cop is a liberal it will do a musical attack instead.
      default:
         if(a.get_weapon().has_musical_attack() || a.type==CREATURE_COP)
         {
            strcat(str,t.name);
            switch(LCSrandom(5))
            {
               case 0:strcat(str,"に歌を歌った");break;
               case 1:strcat(str,"に歌った");break;
               case 2:strcat(str,"に");
                      if(a.get_weapon().has_musical_attack())
                      {
                         strcat(str,a.get_weapon().get_name());
                         strcat(str,"を弾いた");
                      }
                      else // let's use a small enough instrument for anyone to carry in their pocket
                         strcat(str,"ハーモニカを吹いた");
                      break;
               case 3:if(a.align==1)strcat(str,"にプロテスト・ソングを歌った");
                      else strcat(str,"にカントリー・ソングを歌った");
                      break;
               case 4:strcat(str,"にロック・ソングを歌った");break;
            }
            strcat(str,"!");

            attack=a.skill_roll(SKILL_MUSIC);

            if(t.align==1)
               resist=t.attribute_roll(ATTRIBUTE_HEART);
            else resist=t.attribute_roll(ATTRIBUTE_WISDOM);
            if(resist>0)
               a.train(SKILL_MUSIC,LCSrandom(resist)+1);
            else a.train(SKILL_MUSIC,1);
         }
         break;
   }

   move(16,1);
   addstr(str, gamelog);
   gamelog.newline();

   if((t.animalgloss==ANIMALGLOSS_TANK||(t.animalgloss==ANIMALGLOSS_ANIMAL&&law[LAW_ANIMALRESEARCH]!=2))
    ||(a.enemy() && t.flag & CREATUREFLAG_BRAINWASHED))
   {
      move(17,1);
      addstr(s+t.name+"には効かない!", gamelog);
   }
   else if (a.align == t.align)
   {
      move (17,1);
      addstr(s+t.name+"は"+a.name+"と既に意見が一致している。");
   }
   else if(attack>resist)
   {
      t.stunned+=(attack-resist)/4;
      if(a.enemy())
      {
         if(t.juice>100)
         {
            move(17,1);
            addstr(s+t.name+"はジュースを失った!", gamelog);
            addjuice(t,-50,100);
         }
         else if(LCSrandom(15)>t.get_attribute(ATTRIBUTE_WISDOM,true) || t.get_attribute(ATTRIBUTE_WISDOM,true) < t.get_attribute(ATTRIBUTE_HEART,true))
         {
            move(17,1);
            addstr(s+t.name+"は知恵で汚された!", gamelog);
            t.adjust_attribute(ATTRIBUTE_WISDOM,+1);
         }
         else if(t.align==ALIGN_LIBERAL && t.flag & CREATUREFLAG_LOVESLAVE)
         {
            move(17,1);
            addstr(s+t.name+"は聞かずにはいられなかった!", gamelog);
         }
         else
         {
            if(a.align==-1)
            {
               move(17,1);
               addstr(s+t.name+"は保守に転向した", gamelog);
               t.stunned=0;
               if(t.prisoner!=NULL)
                  freehostage(t,0);
               addstr("!", gamelog);
            }
            else
            {
               move(17,1);
               addstr(s+t.name+"はこれ以上戦えない", gamelog);
               t.stunned=0;
               if(t.prisoner!=NULL)
                  freehostage(t,0);
               addstr("!", gamelog);
            }

            for(int e=0;e<ENCMAX;e++)
            {
               if(encounter[e].exists==0)
               {
                  encounter[e]=t;
                  encounter[e].exists=1;
                  if(a.align==-1)conservatise(encounter[e]);
                  encounter[e].cantbluff=2;
                  encounter[e].squadid=-1;
                  break;
               }
            }

            bool flipstart=0;
            for(int p=0;p<6;p++)
            {
               if(activesquad->squad[p]==&t)
               {
                  activesquad->squad[p]->die();
                  activesquad->squad[p]->location=-1;
                  activesquad->squad[p]=NULL;
                  flipstart=1;
               }
               if(flipstart&&p<5) activesquad->squad[p]=activesquad->squad[p+1];
            }
            if(flipstart) activesquad->squad[5]=NULL;
         }
      }
      else
      {
         if(t.juice>=100)
         {
            move(17,1);
            addstr(s+t.name+"は少しマシになった!", gamelog);
            addjuice(t,-50,99);
         }
         else if(!t.attribute_check(ATTRIBUTE_HEART,DIFFICULTY_AVERAGE) ||
            t.get_attribute(ATTRIBUTE_HEART,true) < t.get_attribute(ATTRIBUTE_WISDOM,true))
         {
            move(17,1);
            addstr(s+t.name+"の心が高まった!", gamelog);
            t.adjust_attribute(ATTRIBUTE_HEART,+1);
         }
         else
         {
            move(17,1);
            addstr(s+t.name+"はリベラルに転向した!", gamelog);
            t.stunned=0;

            liberalize(t);
            t.infiltration/=2;
            t.flag|=CREATUREFLAG_CONVERTED;
            t.cantbluff=0;
         }
      }
   }
   else
   {
      move(17,1);
      addstr(s+t.name+"にはまだ力がある。", gamelog);
   }

   gamelog.newline();

   printparty();
   if(mode==GAMEMODE_CHASECAR||
      mode==GAMEMODE_CHASEFOOT) printchaseencounter();
   else printencounter();

   getkey();

   return;
}


/* destroys armor, masks, drops weapons based on severe damage */
void severloot(Creature &cr,vector<Item *> &loot)
{
   int armok=2;
   if((cr.wound[BODYPART_ARM_RIGHT] & WOUND_NASTYOFF)||
      (cr.wound[BODYPART_ARM_RIGHT] & WOUND_CLEANOFF)) armok--;
   if((cr.wound[BODYPART_ARM_LEFT] & WOUND_NASTYOFF)||
      (cr.wound[BODYPART_ARM_LEFT] & WOUND_CLEANOFF)) armok--;
   if(cr.special[SPECIALWOUND_NECK]!=1) armok=0;
   if(cr.special[SPECIALWOUND_UPPERSPINE]!=1) armok=0;

   if(cr.is_armed() && armok==0)
   {
      clearmessagearea();
      set_color(COLOR_YELLOW,COLOR_BLACK,1);
      move(16,1);
      addstr(cr.get_weapon().get_name(1), gamelog);
      addstr("が", gamelog);
      move(17,1);
      addstr(cr.name, gamelog);
      addstr("の手から滑り落ちた。", gamelog);
      gamelog.newline();

      getkey();

      if(mode==GAMEMODE_SITE) cr.drop_weapons_and_clips(&loot);
      else cr.drop_weapons_and_clips(NULL);
   }

   if((((cr.wound[BODYPART_BODY] & WOUND_CLEANOFF)||
        (cr.wound[BODYPART_BODY] & WOUND_NASTYOFF))&&
         cr.get_armor().covers(BODYPART_BODY))||
       ((cr.wound[BODYPART_HEAD] & WOUND_NASTYOFF)&&
         cr.get_armor().is_mask()))
   {
      clearmessagearea();
      set_color(COLOR_YELLOW,COLOR_BLACK,1);
      move(16,1);
      addstr(cr.name, gamelog);
      addstr("の", gamelog);
      addstr(cr.get_armor().get_name(), gamelog);
      addstr("が破壊された。", gamelog);
      gamelog.newline();

      getkey();

      cr.strip(NULL);
   }
}



/* damages the selected armor if it covers the body part specified */
void armordamage(Armor &armor,int bp, int damamount)
{
   if(armor.covers(bp) && LCSrandom(armor.get_durability()) < damamount)
   {
      if (armor.is_damaged())
      {
         armor.decrease_quality(LCSrandom(armor.get_durability()) < LCSrandom(damamount)/armor.get_quality() ? 1:0);
      }
      else
      {
         armor.set_damaged(true);
      }
   }
}



/* blood explosions */
void bloodblast(Armor* armor)
{
   //GENERAL
   if(armor!=NULL)
      armor->set_bloody(true);

   if(mode!=GAMEMODE_SITE)
      return;

   levelmap[locx][locy][locz].flag|=SITEBLOCK_BLOODY2;

   //HIT EVERYTHING
   for(int p=0;p<6;p++)
   {
      if(activesquad->squad[p]==NULL) continue;
      if(!LCSrandom(2))
         activesquad->squad[p]->get_armor().set_bloody(true);
   }

   for(int e=0;e<ENCMAX;e++)
   {
      if(!encounter[e].exists) continue;
      if(!LCSrandom(2))
         encounter[e].get_armor().set_bloody(true);
   }

   //REFRESH THE SCREEN
   printsitemap(locx,locy,locz);
   refresh();
}



/* kills the specified creature from the encounter, dropping loot */
void delenc(short e,char loot)
{
   //MAKE GROUND LOOT
   if(mode!=GAMEMODE_SITE) loot=0;
   if(loot) makeloot(encounter[e],groundloot);

   //BURY IT
   for(int en=e;en<ENCMAX;en++)
   {
      if(!encounter[en].exists) break;
      if(en<ENCMAX-1) encounter[en]=encounter[en+1];
   }
   encounter[ENCMAX-1].exists=0;
}



/* generates the loot dropped by a creature when it dies */
void makeloot(Creature &cr,vector<Item *> &loot)
{
   cr.drop_weapons_and_clips(&loot);
   cr.strip(&loot);

   if(cr.money>0 && mode == GAMEMODE_SITE)
   {
      loot.push_back(new Money(cr.money));
      cr.money=0;
   }
}



/* abandoned liberal is captured by conservatives */
void capturecreature(Creature &t)
{
   t.activity.type=ACTIVITY_NONE;
   t.drop_weapons_and_clips(NULL);
   //t.strip(NULL);
   Armor clothes=Armor(*armortype[getarmortype("ARMOR_CLOTHES")]);
   t.give_armor(clothes,NULL);

   freehostage(t,2); // situation 2 = no message; this may want to be changed to 0 or 1
   if(t.prisoner)
   {
      if(t.prisoner->squadid==-1)
         delete t.prisoner;
      t.prisoner=NULL; // Stop hauling people
   }
   if(t.flag & CREATUREFLAG_JUSTESCAPED)
   {
      t.location=cursite;
      if(sitetype==SITE_GOVERNMENT_PRISON||
         sitetype==SITE_GOVERNMENT_COURTHOUSE)
      {
         Armor prisoner=Armor(*armortype[getarmortype("ARMOR_PRISONER")]);
         t.give_armor(prisoner,NULL);
      }
      if(sitetype==SITE_GOVERNMENT_PRISON)
      {
         // Clear criminal record?
         t.heat=0;
         for(int i=0;i<LAWFLAGNUM;i++)
            t.crimes_suspected[i]=0;
      }
   }
   else
      t.location = find_police_station(cursite);

   t.squadid=-1;
}



/* checks if the creature can fight and prints flavor text if they can't */
char incapacitated(Creature &a,char noncombat,char &printed)
{
   printed=0;

   if(a.animalgloss==ANIMALGLOSS_TANK)
   {
      if(a.blood<=20||(a.blood<=50&&(LCSrandom(2)||a.forceinc)))
      {
         a.forceinc=0;
         if(noncombat)
         {
            clearmessagearea();

            set_color(COLOR_WHITE,COLOR_BLACK,1);

            move(16,1);
            addstr(a.name, gamelog);
            switch(LCSrandom(3))
            {
            case 0: addstr("は煙を上げた…", gamelog); break;
            case 1: addstr("はくすぶっている…", gamelog); break;
            case 2: addstr("は燃え上がった…", gamelog); break;
            }

            gamelog.newline();

            printed=1;
         }
         return 1;
      }

      return 0;
   }

   if(a.animalgloss==ANIMALGLOSS_ANIMAL)
   {
      if(a.blood<=20||(a.blood<=50&&(LCSrandom(2)||a.forceinc)))
      {
         a.forceinc=0;
         if(noncombat)
         {
            clearmessagearea();
            set_color(COLOR_WHITE,COLOR_BLACK,1);

            move(16,1);
            addstr(a.name);
            switch(LCSrandom(3))
            {
            case 0: addstr("は苦しみ鳴いている…", gamelog); break;
            case 1: if(law[LAW_FREESPEECH]==-2) addstr("は床を[ピー]した。", gamelog);
                    else addstr("は床を台無しにした。", gamelog); break;
            case 2: addstr("は痛々しく吠えた…", gamelog); break;
            }

            gamelog.newline();

            printed=1;
         }
         return 1;
      }

      return 0;
   }

   if(a.blood<=20||(a.blood<=50&&(LCSrandom(2)||a.forceinc)))
   {
      a.forceinc=0;
      if(noncombat)
      {
         clearmessagearea();
         set_color(COLOR_WHITE,COLOR_BLACK,1);

         move(16,1);
         addstr(a.name);
         switch(LCSrandom(54))
         {
         case 0: addstr("はイエスの名を叫んだ。"); break;
         case 1: if(law[LAW_FREESPEECH]==-2) addstr("は床を[ピー]した。");
                 else addstr("は床を台無しにした。"); break;
         case 2: addstr("はうめき声を上げた。"); break;
         case 3: addstr("は泣き出した。"); break;
         case 4: addstr("は嘔吐した。"); break;
         case 5: addstr("は笑い出した…"); break;
         case 6: addstr("は痛みで叫び声を上げた。"); break;
         case 7: addstr("は母の名を叫んだ。"); break;
         case 8: addstr("は静かに祈った…"); break;
         case 9: addstr("は傷口を押さえた。"); break;
         case 10: addstr("は手を伸ばしうめき声を上げた。"); break;
         case 11: addstr("は痛みでうずくまった。"); break;
         case 12: addstr("は苦しそうにうめき声を上げた。"); break;
         case 13: addstr("は激しく息をした。"); break;
         case 14: addstr("は叫び祈った。"); break;
         case 15: addstr("は血を吐いた。"); break;
         case 16: if(mode!=GAMEMODE_CHASECAR) addstr("は壁にぶつかってよろめいた。");
                  else addstr("はドアにもたれかかった。"); break;
         case 17: addstr("は許しを乞った。"); break;
         case 18: addstr("は叫んだ。「なぜ見捨てるのだ? 」"); break;
         case 19: addstr("はつぶやいた。「なぜだ、主よ。なぜ? 」"); break;
         case 20: addstr("はささやいた。「私は死ぬのか? 」"); break;
         case 21: if(law[LAW_FREESPEECH]==-2) addstr("は苦しみ[床を濡らした]。");
                  else addstr("は苦しみ床に漏らした。"); break;
         case 22: addstr("は意味のないことをささやいた。"); break;
         case 23: if(a.special[SPECIALWOUND_RIGHTEYE]&&a.special[SPECIALWOUND_LEFTEYE])
                     addstr("は暗闇を見つめた。");
                  else if(a.special[SPECIALWOUND_RIGHTEYE]||a.special[SPECIALWOUND_LEFTEYE])
                     addstr("は片目で何かを見つめた。");
                  else addstr("は虚ろな目で見上げた。"); break;
         case 24: addstr("は静かに泣いた。"); break;
         case 25: addstr("は声が枯れるまで叫んだ。"); break;
         case 26: if(a.special[SPECIALWOUND_TEETH]>1) addstr("の歯が震えだした。");
                  else if(a.special[SPECIALWOUND_TEETH]==1) addstr("の歯が震えだした。");
                  else addstr("の歯肉が震えだした。"); break;
         case 27: addstr("は震えが止まらなくなった。"); break;
         case 28: addstr("は奇妙に落ち着いている。"); break;
         case 29: addstr("は少し眠りそうになった。"); break;
         case 30: addstr("はよだれを垂らした。"); break;
         case 31: addstr("は思い出の中に迷い込んだ。"); break;
         case 32: addstr("は恐怖で震えた。"); break;
         case 33: addstr("はうめいた。「怖い…」"); break;
         case 34: addstr("は泣き叫んだ。「こんなはずではなかった…」"); break;
         case 35: if(a.age<20 && !a.animalgloss) addstr("は泣き叫んだ。「母さん! 」");
                  else switch(a.type) {
                  case CREATURE_GENETIC:
                     addstr("はうめいた。「私の子孫はどうなる? 」"); break;
                  case CREATURE_GUARDDOG:
                     addstr("はうめいた。「私の子犬はどうなる? 」"); break;
                  default:
                     addstr("はうめいた。「私の子供はどうなる? 」"); break;
                  } break;
         case 36: addstr("は静かに震えた。"); break;
         case 37: addstr("は痛みで声を上げた。"); break;
         case 38: addstr("は神を疑いだした。"); break;
         case 39: addstr("は静かに死について考えた。"); break;
         case 40: addstr("は毛布を求めた。"); break;
         case 41: addstr("は静かに震えた。"); break;
         case 42: if(law[LAW_FREESPEECH]==-2)addstr("は[床を濡らした]。");
                  else addstr("は血の塊を吐いた。"); break;
         case 43: if(law[LAW_FREESPEECH]==-2)addstr("は[床を濡らした]。");
                  else addstr("は血の泡を吐き出した。"); break;
         case 44: addstr("は慈悲を求めた。"); break;
         case 45: addstr("はコーヒーを求めた。"); break;
         case 46: addstr("は諦めたように見えた。"); break;
         case 47: addstr("は手を伸ばしもがいた。"); break;
         case 48: addstr("は忍び笑いをした。"); break;
         case 49: addstr("は苦しげな表情をした。"); break;
         case 50: addstr("は神に問うた。"); break;
         case 51: addstr("はささやいた。「ママ、赤ちゃん。赤ちゃんはママが好き。」"); break;
         case 52: addstr("は子供時代のおもちゃを求めた。"); break;
         case 53: addstr("はうめいた。「でも教会に行かなければ…」"); break;
         }

         printed=1;
      }

      return 1;
   }
   else if(a.stunned)
   {
      if(noncombat)
      {
         a.stunned--;
         clearmessagearea();
         set_color(COLOR_WHITE,COLOR_BLACK,1);

         move(16,1);
         addstr(a.name, gamelog);
         switch(LCSrandom(11))
         {
         case 0: addstr("は怖気づいた。", gamelog); break;
         case 1: addstr("は自信を失った。", gamelog); break;
         case 2: addstr("は不安げにあたりを見渡した。", gamelog); break;
         case 3: addstr("は泣き出した。", gamelog); break;
         case 4: addstr("は尋ねた。「これは正しいのか? 」", gamelog); break;
         case 5: addstr("は助けを求めた。", gamelog); break;
         case 6: addstr("は判断できなくなった。", gamelog); break;
         case 7: addstr("は呆然としている。", gamelog); break;
         case 8: addstr("は静かに祈っている。", gamelog); break;
         case 9: addstr("は真実を求めた。", gamelog); break;
         case 10: addstr("は泣き出した。", gamelog); break;
         }

         gamelog.newline();

         printed=1;
      }
      return 1;
   }

   if(a.special[SPECIALWOUND_NECK]==2||
      a.special[SPECIALWOUND_UPPERSPINE]==2)
   {
      if(!noncombat)
      {
         clearmessagearea();
         set_color(COLOR_WHITE,COLOR_BLACK,1);

         move(16,1);
         addstr(a.name, gamelog);
         addstr("は", gamelog);
         switch(LCSrandom(5))
         {
         case 0: addstr("堂々と見ている。", gamelog); break;
         case 1: addstr("辛抱強く待っている。", gamelog); break;
         case 2: addstr("考え事をしながら座っている。", gamelog); break;
         case 3: addstr("静かに息をしている。", gamelog); break;
         case 4: addstr("状況について考えている。", gamelog); break;
         }

         gamelog.newline();

         printed=1;
      }

      return 1;
   }

   return 0;
}



/* describes a character's death */
void adddeathmessage(Creature &cr)
{
   set_color(COLOR_YELLOW,COLOR_BLACK,1);

   move(16,1);
   char str[200];

   if((cr.wound[BODYPART_HEAD] & WOUND_CLEANOFF)||
      (cr.wound[BODYPART_HEAD] & WOUND_NASTYOFF))
   {
      strcpy(str,cr.name);
      switch(LCSrandom(4))
      {
      case 0:
         strcat(str,"はかつて頭のあった場所に手を伸ばし、そして");
         addstr(str, gamelog);
         move(17,1);
         if(mode!=GAMEMODE_CHASECAR)
            addstr("倒れた。", gamelog);
         else addstr("前のめりになった。", gamelog);
         break;
      case 1:
         if(mode!=GAMEMODE_CHASECAR)
            strcat(str,"は頭が無いまましばらく立っていたが、");
         else strcat(str,"は頭が無いまましばらく座っていたが、");
         addstr(str, gamelog);
         move(17,1);
         addstr("ついに崩れ落ちた。", gamelog);
         break;
      case 2:
         strcat(str,"は首から大量の");
         if(law[LAW_FREESPEECH]==-2)strcat(str,"[赤い液体]");
         else strcat(str,"血");
         strcat(str,"を吹き上げ、");
         addstr(str, gamelog);
         move(17,1);
         if(mode!=GAMEMODE_CHASECAR)
            addstr("床に倒れた。", gamelog);
         else addstr("壁にもたれかかった。", gamelog);
         break;
      case 3:
         strcat(str,"は首の穴で最期の息をし、");
         addstr(str, gamelog);
         move(17,1);
         addstr("そして静かになった。", gamelog);
         break;
      }
   }
   else if((cr.wound[BODYPART_BODY] & WOUND_CLEANOFF)||
      (cr.wound[BODYPART_BODY] & WOUND_NASTYOFF))
   {
      strcpy(str,cr.name);
      switch(LCSrandom(2))
      {
      case 0:strcat(str,"はバラバラになって死んだ。"); break;
      case 1:strcat(str,"は肉体を吹き飛ばされ死んだ。"); break;
      }
      addstr(str, gamelog);
   }
   else
   {
      strcpy(str,cr.name);
      switch(LCSrandom(11))
      {
      case 0:
         strcat(str,"は断末魔の叫びを上げ");
         addstr(str, gamelog);
         move(17,1);
         addstr("息絶えた。", gamelog);
         break;
      case 1:
         strcat(str,"は呼吸が弱々しくなり、そして");
         addstr(str, gamelog);
         move(17,1);
         if(law[LAW_FREESPEECH]==-2)addstr("床を[ピー]した。", gamelog);
         else addstr("床を台無しにした。", gamelog);
         break;
      case 2:
         strcat(str,"は何かをつぶやき、");
         addstr(str, gamelog);
         move(17,1);
         addstr("そして息絶えた。", gamelog);
         break;
      case 3:
         strcat(str,"は叫んだ。「父よ! なぜ私を見捨てたのですか? 」");
         addstr(str, gamelog);
         move(17,1);
         addstr("そして倒れ死んだ。", gamelog);
         break;
      case 4:
         strcat(str,"は母を思い静かに泣いた。");
         addstr(str, gamelog);
         move(17,1);
         addstr("息が弱々しくなり、そして最期を迎えた。", gamelog);
         break;
      case 5:
         strcat(str,"は息を切らせ、");
         addstr(str, gamelog);
         move(17,1);
         addstr("血を吐き… そして静かになった。", gamelog);
         break;
      case 6:
         strcat(str,"の意識が遠くなり、");
         addstr(str, gamelog);
         move(17,1);
         addstr("そしてこの世を去った。", gamelog);
         break;
      case 7:
         strcat(str,"は汗を流しながらつぶやいた。");
         addstr(str, gamelog);
         move(17,1);
         if(law[LAW_FREESPEECH]==-2)addstr("イエスのように[すばらしく]生き、そして死する…", gamelog);
         else addstr("イエスのように生き、そして死する…", gamelog);
         break;
      case 8:
         strcat(str,"は大声で泣き叫んだ。");
         addstr(str, gamelog);
         move(17,1);
         addstr("そして、うずくまり動かなくなった。", gamelog);
         break;
      case 9:
         strcat(str,"は震えながら静かに祈りをささげた。");
         addstr(str, gamelog);
         move(17,1);
         addstr("そしてそのまま息絶えた。", gamelog);
         break;
      case 10:
         strcat(str,"は最期の言葉を言った: ");
         addstr(str, gamelog);
         move(17,1);
         switch(cr.align)
         {
         case ALIGN_LIBERAL:
         case ALIGN_ELITELIBERAL:
            addstr(slogan, gamelog); break;
         case ALIGN_MODERATE:
            addstr("\"どっちもくたばってしまえ…\"", gamelog); break;
         default:
            addstr("\"リベラルに屈するよりも死を選ぶ…\"", gamelog); break;
         }
         break;
      }
   }
   gamelog.newline();
}



/* pushes people into the current squad (used in a siege) */
void autopromote(int loc)
{
   if(!activesquad) return;

   int partysize=squadsize(activesquad),partyalive=squadalive(activesquad),libnum=0;

   if(partyalive==6) return;

   for(int pl=0;pl<len(pool);pl++)
   {
      if(pool[pl]->location!=loc) continue;
      if(pool[pl]->alive&&pool[pl]->align==1) libnum++;
   }

   if(partysize==libnum) return;

   char conf;
   for(int p=0;p<6;p++)
   {
      conf=0;
      if(activesquad->squad[p]==NULL) conf=1;
      else if(!activesquad->squad[p]->alive) conf=1;

      if(conf)
      {
         for(int pl=0;pl<len(pool);pl++)
         {
            if(pool[pl]->location!=loc) continue;
            if(pool[pl]->alive&&pool[pl]->squadid==-1&&
               pool[pl]->align==1)
            {
               if(activesquad->squad[p]!=NULL) activesquad->squad[p]->squadid=-1;
               activesquad->squad[p]=pool[pl];
               activesquad->squad[p]->squadid=activesquad->id;
               break;
            }
         }
      }
   }
}
