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

/* select new game options */
void setup_newgame()
{
   music.play(MUSIC_NEWGAME);
   bool classicmode   = false;
   bool strongccs     = false;
   bool nightmarelaws = false;
   multipleCityMode   = false;
   stalinmode         = false;

   clear();
   while(true)
   {
      set_color(COLOR_WHITE,COLOR_BLACK,1);
      move(4,6);
      addstr("リベラル・クライム・スコードの新規開始: 上級ルールの選択");
      move(7,0);
      set_color(COLOR_WHITE,COLOR_BLACK,0);
      if(classicmode)
         addstr("[X]");
      else addstr("[ ]");
      addstr(" A - クラシックモード: コンサバ・クライム・スコードは出現しない");
      move(9,0);
      if(!classicmode)
         set_color(COLOR_WHITE,COLOR_BLACK,0);
      else set_color(COLOR_BLACK,COLOR_BLACK,1);
      if(strongccs)
         addstr("[X]");
      else addstr("[ ]");
      addstr(" B - 心に火を灯せ: CSSは初めから活動的で強力");
      move(11,0);
      set_color(COLOR_WHITE,COLOR_BLACK,0);
      if(nightmarelaws)
         addstr("[X]");
      else addstr("[ ]");
      addstr(" C - ナイトメアモード: リベラル主義は忘れられた。もう遅すぎるのか?");
      move(13,0);
      set_color(COLOR_WHITE,COLOR_BLACK,0);
      if(multipleCityMode)
         addstr("[X]");
      else addstr("[ ]");
      addstr(" D - 全米LCS: 複数の都市に渡る上級プレー");
      move(15,0);
      if(nocourtpurge)
         addstr("[X]");
      else addstr("[ ]");
      addstr(" E - マラソンモード: リベラルの合衆国憲法改正を阻止する");
      #ifdef ALLOWSTALIN
      move(17,0);
      if(stalinmode)
         addstr("[X]");
      else addstr("[ ]");
      addstr(" F - スターリンモード: スターリン・コムラド・スコードを有効にする (未完成)");
      move(21,4);
      #else // ALLOWSTALIN
      move(19,4);
      #endif // ALLOWSTALIN
      addstr("何かキーを押すと続く…");

      int c=getkey();

      if(c=='a')
      {
         classicmode=!classicmode;
         continue;
      }
      if(c=='b')
      {
         strongccs=!strongccs;
         continue;
      }
      if(c=='c')
      {
         nightmarelaws=!nightmarelaws;
         continue;
      }
      if(c=='d')
      {
          multipleCityMode=!multipleCityMode;
          continue;
      }
      if(c=='e')
      {
          nocourtpurge=!nocourtpurge;
          notermlimit=!notermlimit;
          continue;
      }
      #ifdef ALLOWSTALIN
      if(c=='f')
      {
          stalinmode=!stalinmode;
          continue;
      }
      #endif
      break;
   }
   if(nightmarelaws)
   {
      for(int l=0;l<LAWNUM;l++)
         law[l]=ALIGN_ARCHCONSERVATIVE;
      for(int a=0;a<VIEWNUM-3;a++)
         attitude[a]=LCSrandom(20);
      for(int s=0;s<SENATENUM;s++)
      {
         if(s<55) senate[s]=ALIGN_ARCHCONSERVATIVE;
         else if(s<70) senate[s]=ALIGN_CONSERVATIVE;
         else if(s<80) senate[s]=ALIGN_MODERATE;
         else if(s<97) senate[s]=ALIGN_LIBERAL;
         else senate[s]=ALIGN_ELITELIBERAL;
      }

      for(int h=0;h<HOUSENUM;h++)
      {
         if(h<220) house[h]=ALIGN_ARCHCONSERVATIVE;
         else if(h<350) house[h]=ALIGN_CONSERVATIVE;
         else if(h<400) house[h]=ALIGN_MODERATE;
         else if(h<425) house[h]=ALIGN_LIBERAL;
         else house[h]=ALIGN_ELITELIBERAL;
      }

      for(int c=0;c<COURTNUM;c++)
      {
         if(c<5) court[c]=ALIGN_ARCHCONSERVATIVE;
         else if(c<7) court[c]=ALIGN_CONSERVATIVE;
         else if(c<8) court[c]=ALIGN_MODERATE;
         else if(c<8) court[c]=ALIGN_LIBERAL;
         else court[c]=ALIGN_ELITELIBERAL;
         do
         {
            if(court[c]==ALIGN_ARCHCONSERVATIVE)
               generate_name(courtname[c],GENDER_WHITEMALEPATRIARCH);
            else generate_name(courtname[c]);
         } while(len(courtname[c])>20);
      }
   }
   if(classicmode)
      endgamestate=ENDGAME_CCS_DEFEATED;
   else if(strongccs)
   {
      endgamestate=ENDGAME_CCS_ATTACKS;
      //attitude[VIEW_POLITICALVIOLENCE]=90;
   }

   clear();
   while(true)
   {
      set_color(COLOR_WHITE,COLOR_BLACK,1);
      move(4,6);
      addstr("リベラル・クライム・スコードの新規開始: あなたのアジェンダ");
      move(7,0);
      set_color(COLOR_WHITE,COLOR_BLACK,0);
      if(wincondition==WINCONDITION_ELITE)
         addstr("[X]");
      else addstr("[ ]");
      addstr(" A - 完全主義(クラシック) - 全ての法をエリートリベラルに!");
      move(9,0);
      if(!classicmode)
         set_color(COLOR_WHITE,COLOR_BLACK,0);
      else set_color(COLOR_BLACK,COLOR_BLACK,1);
      if(wincondition==WINCONDITION_EASY)
         addstr("[X]");
      else addstr("[ ]");
      addstr(" B - 民主党モード - 多くの法をエリートリベラルに、一部はリベラルに");
      move(13,4);
      set_color(COLOR_WHITE,COLOR_BLACK,0);
      addstr("何かキーを押すと続く…");

      int c=getkey();

      if(c=='a')
      {
         wincondition=WINCONDITION_ELITE;
         continue;
      }
      if(c=='b')
      {
         wincondition=WINCONDITION_EASY;
         continue;
      }
      break;
   }

   clear();
   while(true)
   {
      set_color(COLOR_WHITE,COLOR_BLACK,1);
      move(4,6);
      addstr("リベラル・クライム・スコードの新規開始: 学びの場");
      set_color(COLOR_WHITE,COLOR_BLACK,0);
      move(5,6);
      addstr("(セキュリティ、隠密、変装、そして運転に影響する)");
      move(8,0);
      if(fieldskillrate==FIELDSKILLRATE_FAST)
         addstr("[X]");
      else addstr("[ ]");
      addstr(" A - 高速 - 詰め込み教育は保守的だ!");
      move(10,0);
      if(fieldskillrate==FIELDSKILLRATE_CLASSIC)
         addstr("[X]");
      else addstr("[ ]");
      addstr(" B - クラシック - 上達には実践が必要");
      move(12,0);
      if(fieldskillrate==FIELDSKILLRATE_HARD)
         addstr("[X]");
      else addstr("[ ]");
      addstr(" C - ハードモード - 学び取るか、逮捕されるか!");
      move(16,4);
      set_color(COLOR_WHITE,COLOR_BLACK,0);
      addstr("何かキーを押すと続く…");

      int c=getkey();

      if(c=='a')
      {
         fieldskillrate=FIELDSKILLRATE_FAST;
         continue;
      }
      if(c=='b')
      {
         fieldskillrate=FIELDSKILLRATE_CLASSIC;
         continue;
      }
      if(c=='c')
      {
         fieldskillrate=FIELDSKILLRATE_HARD;
         continue;
      }
      break;
   }
}

enum recruits
{
   RECRUITS_GANG,
   RECRUITS_NONE
};

/* creates your founder */
void makecharacter()
{
   Creature *newcr=new Creature;
   newcr->align=1;

#ifdef BLIND
   newcr->special[SPECIALWOUND_RIGHTEYE]=1;
   newcr->special[SPECIALWOUND_LEFTEYE]=1;
#endif
#ifdef SPINE
   newcr->special[SPECIALWOUND_UPPERSPINE]=1;
   newcr->special[SPECIALWOUND_LOWERSPINE]=1;
#endif
#ifdef NOFACE
   newcr->special[SPECIALWOUND_TONGUE]=1;
   newcr->special[SPECIALWOUND_RIGHTEYE]=1;
   newcr->special[SPECIALWOUND_LEFTEYE]=1;
   newcr->special[SPECIALWOUND_NOSE]=1;
#endif
#ifdef NOWALK
   newcr->special[SPECIALWOUND_UPPERSPINE]=1;
   newcr->special[SPECIALWOUND_LOWERSPINE]=1;
   newcr->special[SPECIALWOUND_NECK]=1;
   newcr->wound[BODYPART_LEG_RIGHT]=1;
   newcr->wound[BODYPART_LEG_LEFT]=1;
#endif
#ifdef INTERNAL
   newcr->special[SPECIALWOUND_RIGHTLUNG]=1;
   newcr->special[SPECIALWOUND_LEFTLUNG]=1;
   newcr->special[SPECIALWOUND_HEART]=1;
   newcr->special[SPECIALWOUND_LIVER]=1;
   newcr->special[SPECIALWOUND_STOMACH]=1;
   newcr->special[SPECIALWOUND_LEFTKIDNEY]=1;
   newcr->special[SPECIALWOUND_RIGHTKIDNEY]=1;
   newcr->special[SPECIALWOUND_SPLEEN]=1;
#endif

   newcr->set_attribute(ATTRIBUTE_HEART,8);
   newcr->set_attribute(ATTRIBUTE_WISDOM,1);
   newcr->set_attribute(ATTRIBUTE_INTELLIGENCE,3);
   newcr->set_attribute(ATTRIBUTE_AGILITY,5);
   newcr->set_attribute(ATTRIBUTE_STRENGTH,4);
   newcr->set_attribute(ATTRIBUTE_HEALTH,6);
   newcr->set_attribute(ATTRIBUTE_CHARISMA,4);
   for(int sk=0;sk<SKILLNUM;sk++)newcr->set_skill(sk,0);

   char first[3][80];
   char last[80];
   bool male = LCSrandom(2); // whether or not starting gender is male
   char gender = newcr->gender_liberal = newcr->gender_conservative = (male ? GENDER_MALE : GENDER_FEMALE);
   do {
      firstname(first[0], GENDER_NEUTRAL);
      firstname(first[1], GENDER_MALE);
      firstname(first[2], GENDER_FEMALE);
      lastname(last);
   } while(strcmp(first[0],last) == 0 && strcmp(first[1],last) == 0 && strcmp(first[2],last) == 0);

   {
      Armor a(*armortype[getarmortype("ARMOR_CLOTHES")]);
      newcr->give_armor(a,NULL);
   }

   bool choices=true;

   while(true)
   {
      clear();

      set_color(COLOR_WHITE,COLOR_BLACK,1);
      move(4,6);
      addstr("リベラル・クライム・スコードの設立者");

      move(7,2);
      addstr("ファーストネーム: ");
      addstr(first[(int)gender]);
      move(7,52);
      set_color(COLOR_BLACK,COLOR_BLACK,1);
      addstr(" (Aを押すと両親が考え直す)");

      move(9,2);
      set_color(COLOR_WHITE,COLOR_BLACK,1);
      addstr("ラストネーム: ");
      addstr(last);
      move(9,49);
      set_color(COLOR_BLACK,COLOR_BLACK,1);
      addstr("(Bを押すと別の家族に生まれる)");

      move(11,2);
      set_color(COLOR_WHITE,COLOR_BLACK,1);
      addstr("性別: ");
      if(newcr->gender_conservative == GENDER_MALE)
      {
         set_color(COLOR_CYAN,COLOR_BLACK,1);
         addstr("男性");
      }
      else if(newcr->gender_conservative == GENDER_FEMALE)
      {
         set_color(COLOR_MAGENTA,COLOR_BLACK,1);
         addstr("女性");
      }
      else
      {
         set_color(COLOR_YELLOW,COLOR_BLACK,1);
         addstr("不明");
      }
      move(11,41);
      set_color(COLOR_BLACK,COLOR_BLACK,1);
      addstr("(Cを押すと生まれたときの性別が変わる)");

      move(13,2);
      set_color(COLOR_WHITE,COLOR_BLACK,1);
      addstr("経歴: ");
      if(choices)
      {
         set_color(COLOR_GREEN,COLOR_BLACK,1);
         addstr("選択する");
      }
      else
      {
         set_color(COLOR_RED,COLOR_BLACK,1);
         addstr("運命は変えられない");
      }
      move(13,47);
      set_color(COLOR_BLACK,COLOR_BLACK,1);
      addstr("(Dを押すと子供時代を切り替える)");
      if(!multipleCityMode)
      {
         move(15,2);
         set_color(COLOR_WHITE,COLOR_BLACK,1);
         addstr("都市: ");
         addstr(lcityname);
         move(15,55);
         set_color(COLOR_BLACK,COLOR_BLACK,1);
         addstr("(Eを押すと場所が代わる)");
      }

      move(19-multipleCityMode*2,4);
      set_color(COLOR_WHITE,COLOR_BLACK,0);
      addstr("準備が整ったらその他のキーを押すこと…");

      int c=getkey();

      if(c=='a')
      {
         do {
            firstname(first[(int)gender],newcr->gender_conservative);
         } while(strcmp(first[(int)gender],last) == 0);
         continue;
      }
      if(c=='b')
      {
         do {
            lastname(last);
         } while(strcmp(first[0],last) == 0 && strcmp(first[1],last) == 0 && strcmp(first[2],last) == 0);
         continue;
      }
      if(c=='c')
      {
         if((newcr->gender_conservative == GENDER_FEMALE && !male) ||
            (newcr->gender_conservative == GENDER_NEUTRAL && male))
            newcr->gender_conservative = GENDER_MALE;
         else if((newcr->gender_conservative == GENDER_MALE && !male) ||
            (newcr->gender_conservative == GENDER_FEMALE && male))
            newcr->gender_conservative = GENDER_NEUTRAL;
         else
            newcr->gender_conservative = GENDER_FEMALE;

         gender = newcr->gender_liberal = newcr->gender_conservative;
         continue;
      }
      if(c=='d')
      {
         choices = !choices;
         continue;
      }
      if(c=='e' && !multipleCityMode)
      {
         strcpy(lcityname,cityname());
         continue;
      }
      break;
   }

   strcpy(newcr->propername,first[(int)gender]);
   strcat(newcr->propername,"・");
   strcat(newcr->propername,last);

   int c;
   bool hasmaps=false;
   bool makelawyer=false;
   bool gaylawyer=false;
   Vehicle * startcar = NULL;
   char recruits = RECRUITS_NONE;
   char base = SITE_RESIDENTIAL_SHELTER;

   for(int q=0;q<10;q++)
   {
      clear();
      set_color(COLOR_WHITE,COLOR_BLACK,1);
      move(0,0);
      addstr("革命の内側: 悲しみの子供時代");
      set_color(COLOR_WHITE,COLOR_BLACK,0);

      //A - Thief
      //B - Fighter
      //C - Student
      //D - Generalist/Sleepers
      //E - Recruiter

      char selection = LCSrandom(5);

      switch(q)
      {

/*
        - The anniversary of Hitler's suicide. - SKILL_PISTOL 1 (lol)
        - Indira Gandhi Killed
*/

         case 0:
            move(2,0);addstr("1984年、私は生まれた。この年は…");

            move(5,0);
            if(choices || selection == 0)
               addstr("A - ポーランドのポピールスズコ神父が政府に拉致された年だ。");
            //ATTRIBUTE_AGILITY 2
            // Oct. 19, 1984
            move(7,0);
            if(choices || selection == 1)
               addstr("B - ロナルド・レーガン大統領暗殺未遂から3年目の年だ。");
            //ATTRIBUTE_STRENGTH 2
            // Mar. 3, 1984
            move(9,0);
            if(choices || selection == 2)
               addstr("C - マッキントッシュが発表された年だ。");
            //ATTRIBUTE_INTELLIGENCE 2
            // Jan. 24, 1984
            move(11,0);
            if(choices || selection == 3)
               addstr("D - アパルトヘイトに反対したデズモンド・ツツがノーベル平和賞を受賞した年だ。");
            //ATTRIBUTE_HEART 2
            // Oct. 16, 1984
            move(13,0);
            if(choices || selection == 4)
               addstr("E - ニカラグアのサンディニスタ民族解放戦線が選挙で勝利した年だ。");
            //ATTRIBUTE_CHARISMA 2
            // Sept. 4, 1984
                        //move(14,0);
                        //if(choices || selection == 5)
               //addstr("F - the United Nations condemned Iraq's use of chemical weapons.");
            //ATTRIBUTE_HEALTH 2
                        //March 30, 1984

            move(17,0);
            addstr("医者は私は");
            set_color(COLOR_WHITE,COLOR_BLACK,1);
            if(newcr->gender_conservative == GENDER_MALE)
               addstr("男の子");
            else if(newcr->gender_conservative == GENDER_FEMALE)
               addstr("女の子");
            else
               addstr("インターセクシャル");
            set_color(COLOR_WHITE,COLOR_BLACK,0);
            addstr("だと言った。");

            move(19,0);
            addstr("両親は");
            if(newcr->gender_conservative == GENDER_NEUTRAL)
            {
               addstr("それを認めなかった。");
               move(20,0);
               addstr("彼らは");
            }

            addstr("私を");
            set_color(COLOR_WHITE,COLOR_BLACK,1);
            addstr(newcr->propername);
            set_color(COLOR_WHITE,COLOR_BLACK,0);
            addstr("と名づけた。");

            break;

                // My first memory was...
                        // my father burning my back with a cigarette
                // When he was really into the sauce...
                        //
                // XXX: Needs an option to have the founder have been in the Army -- LK
                // XXX: Something I forgot.

         case 1:
            move(2,0);addstr("幼いとき、私は…");
            move(5,0);
            if(choices || selection == 0)
               addstr("A - 両親から厳しくされ、おもちゃも隠された。だが、どこにあるのか私にはわかっていた。"); // Toy box
            //SKILL_SECURITY 1
            //ATTRIBUTE_AGILITY 1
            move(7,0);
            if(choices || selection == 1)
               addstr("B - 父によくぶたれた。私は何よりも早くげんこつを覚えた。");
            //SKILL_HANDTOHAND 1
            //ATTRIBUTE_HEALTH 1
            move(9,0);
            if(choices || selection == 2)
               addstr("C - 部屋を与えられた。静かに勉強できるように。一人でだ。");
            //SKILL_WRITING 1
            //ATTRIBUTE_INTELLIGENCE 1
            move(11,0);
            if(choices || selection == 3)
               addstr("D - 両親は私のことでよく言い争っていた。だが、暴力を振るわれることはなかった。");
            //SKILL_PERSUASION 1
            //ATTRIBUTE_HEART 1
            move(13,0);
            if(choices || selection == 4)
               addstr("E - 父に厳しく教育された。彼が考えるような人間になるために。");
            //SKILL_PSYCHOLOGY 1
            //ATTRIBUTE_CHARISMA 1

            /*switch(c)
            {
            case 'e':
               move(17,4);
               addstr("\"The worst has happened. Someone wanted to kill and killed");
               move(18,4);
               addstr("not only the a man, not only a Pole, not only a priest.");
               move(19,4);
               addstr("Someone wanted to kill the hope that it is possible to avoid");
               move(20,4);
               addstr("violence in Polish political life.\"");
               move(21,8);
               addstr("- Solidarity Leader Lech Walesa");
               break;
            default:
               break;
            }*/
            break;
         case 2:
            move(2,0);addstr("小学校に入学すると私は…");
            move(5,0);
            if(choices || selection == 0)
               addstr("A - イタズラばかりしていて、いつも何か企んでいた。");
            //SKILL_DISGUISE 1
            //ATTRIBUTE_AGILITY 1
            move(7,0);
            if(choices || selection == 1)
               addstr("B - ずっと怒りを抑えていた。その代わりとして動物をいじめていた。");
            //SKILL_PSYCHOLOGY 1
            //ATTRIBUTE_STRENGTH 1
            //ATTRIBUTE_AGILITY 1
            //ATTRIBUTE_HEART -1 <--- !
            move(9,0);
            if(choices || selection == 2)
               addstr("C - クラスで一番だった。いつも懸命に勉強していた。");
            //ATTRIBUTE_INTELLIGENCE 1
            //SKILL_WRITING 1
            move(11,0);
            if(choices || selection == 3)
               addstr("D - 自分を抑えることができずケンカばかりしていた。");
            //SKILL_HANDTOHAND 1
            //ATTRIBUTE_STRENGTH 1
            move(13,0);
            if(choices || selection == 4)
               addstr("E - クラスの人気者で友達もたくさんいた。");
            //SKILL_PERSUASION 1
            //ATTRIBUTE_CHARISMA 1
            break;
         case 3:
            move(2,0);addstr("私が10のとき…");
            move(5,0);
            if(choices || selection == 0)
               addstr("A - 両親が離婚した。私が何か言うと話すと両親はいつも言い争った。私は黙るしかなかった。");
            //SKILL_STEALTH 1
            move(7,0);
            if(choices || selection == 1)
               addstr("B - 両親が離婚した。暴力が原因だった。");
            //SKILL_HANDTOHAND 1
            move(9,0);
            if(choices || selection == 2)
               addstr("C - 両親が離婚した。険悪な雰囲気だった。書類を投げつけられたこともある!");
            //SKILL_LAW 1
            move(11,0);
            if(choices || selection == 3)
               addstr("D - 両親が離婚した。母が弁護士と寝たのだ。");
            //SKILL_SEDUCTION 1
            move(13,0);
            if(choices || selection == 4)
               addstr("E - 両親が離婚した。日記を読むと今でも心が痛む。");
            //SKILL_WRITING 1
            break;
         case 4:
            move(2,0);addstr("中学に入ると私は…");
            move(5,0);
            if(choices || selection == 0)
               addstr("A - 科学部に入った。私はこの世界の仕組みを知りたかった。");
            //SKILL_SCIENCE 2
            //ATTRIBUTE_INTELLIGENCE 2
            move(7,0);
            if(choices || selection == 1)
               addstr("B - グランジ・バンドでギターをやった。だが、ひどいものだった。");
            //SKILL_MUSIC 2
            //ATTRIBUTE_CHARISMA 2
            move(9,0);
            if(choices || selection == 2)
               addstr("C - たくさん絵を描いた。この世界をよりすばらしく描きたかったのだ。");
            //SKILL_ART 2
            //ATTRIBUTE_HEART 2
            move(11,0);
            if(choices || selection == 3)
               addstr("D - 家で残酷なビデオゲームばかりしていた。完全に引きこもりだった。");
            //SKILL_COMPUTERS 2
            //ATTRIBUTE_AGILITY 2
            move(13,0);
            if(choices || selection == 4)
               addstr("E - 剣術に取り付かれ筋力トレーニングを始めた。");
            //SKILL_SWORD 2
            //ATTRIBUTE_STRENGTH 2
            break;
         case 5:
            move(2,0);addstr("何もかもが悪くなり始めた…");
            move(5,0);
            if(choices || selection == 0)
               addstr("A - 初めて車を盗んだ。そして数ブロック走らせて事故を起こした。");
            //SKILL_DRIVING 1
            //SKILL_SECURITY 1
            move(7,0);
            if(choices || selection == 1)
               addstr("B - 父と暮らすようになった。彼はベトナム帰りの飲んだくれだ。");
            //SKILL_SHOTGUN 1
            //SKILL_RIFLE 1
            //SKILL_PSYCHOLOGY 1
            move(9,0);
            if(choices || selection == 2)
               addstr("C - そして完全にゴスになった。友人もなく、一人で服を作っていた。");
            //SKILL_TAILORING 2
            move(11,0);
            if(choices || selection == 3)
               addstr("D - そのとき宗教的なカウンセリングを受けたが、ストレスが増すだけだった。");
            //SKILL_RELIGION 1
            //SKILL_PSYCHOLOGY 1
            move(13,0);
            if(choices || selection == 4)
               addstr("E - そこで私は教師のアシスタントになろうとした。だが、逆に目を付けられただけだった。");
            //SKILL_TEACHING 2
            break;
         case 6:
            move(2,0);addstr("ああ、あのときが最悪だった…");
            move(5,0);
            if(choices || selection == 0)
               addstr("A - 14のときパトカーを盗んだ。それで少年院に6ヶ月間入った。");
            //SKILL_DRIVING 1
            //SKILL_SECURITY 1
            //ATTRIBUTE_INTELLIGENCE 1
            move(7,0);
            if(choices || selection == 1)
               addstr("B - 前の母が元夫である父をショットガンで撃ったのだ。");//XXX: Sounds... Sexual...
            //SKILL_SHOTGUN 2
            //ATTRIBUTE_AGILITY 1
            move(9,0);
            if(choices || selection == 2)
               addstr("C - I tried wrestling for a quarter, desperate to fit in.");
            //ATTRIBUTE_STRENGTH 1
            //SKILL_HANDTOHAND 2
            move(11,0);
            if(choices || selection == 3)
               addstr("D - 付き合っているのがバレた。私は同性愛を「治す」必要があった。");
            //SKILL_SEDUCTION 1
            //SKILL_RELIGION 1
            //ATTRIBUTE_HEART 1
            move(13,0);
            if(choices || selection == 4)
               addstr("E - 私は他人を支配しようとした。私は自分自身のはみ出しもののグループを作った。");
            //SKILL_PERSUASION 2
            //ATTRIBUTE_CHARISMA 1
            break;
         case 7:
            move(2,0);addstr("家を飛び出したとき、私はまだ15だった。そして…");
            move(5,0);
            if(choices || selection == 0)
               addstr("A - 盗みに入るようになった。金持ちの家だけだ。連中のガラクタにはもう飽き飽きだ。");
            //SKILL_SECURITY 1
            //SKILL_STEALTH 1
            //ATTRIBUTE_AGILITY 1
            move(7,0);
            if(choices || selection == 1)
               addstr("B - ギャングと町をうろつき暴力に明け暮れていた。");
            //ATTRIBUTE_STRENGTH 1
            //SKILL_HANDTOHAND 2
            move(9,0);
            if(choices || selection == 2)
               addstr("C - ファーストフード店の劣悪な環境で働いた。微笑みながら人にエサをやるようだった。");
            //ATTRIBUTE_CHARISMA 1
            //SKILL_BUSINESS 2
            move(11,0);
            if(choices || selection == 3)
               addstr("D - 体を売っていた。生きるためには金が必要だ。");
            //ATTRIBUTE_HEART -1
            //ATTRIBUTE_CHARISMA 2
            //SKILL_SEDUCTION 2
            move(13,0);
            if(choices || selection == 4)
               addstr("E - 左翼団体に志願した。だが本当は違った。わかるだろう?");
            //ATTRIBUTE_INTELLIGENCE 1
            //SKILL_LAW 1
            //SKILL_PERSUASION 1
            break;
         case 8:
            move(2,0);addstr("人生は続く。18の誕生日に私は…");
            move(5,0);
            if(choices || selection == 0)
               addstr("A - スポーツカーを手に入れた。持ち主は怒っているだろう。");
            move(7,0);
            if(choices || selection == 1)
               addstr("B - 自分のためにアサルトライフルを買った。");
            move(9,0);
            if(choices || selection == 2)
               addstr("C - ただ祝った。何千ドルも無駄にせずにすんだ!");
            move(11,0);
            if(choices || selection == 3)
               addstr("D - パーティーでクールな法学部生と出会った。それ以来つきあっている。");//XXX: No Seduction?
            move(13,0);
            if(choices || selection == 4)
               addstr("E - 苦労していくつかの主要都市の秘密の地図を手に入れた。");
            break;
         case 9:
            move(2,0);addstr("そして幾年かが過ぎ、今では…");
            move(5,0);
            if(choices || selection == 0)
               addstr("A - 企業に盗みに入っている。私はまだまだ秘密を知っている。");
            //ATTRIBUTE_INTELLIGENCE 2
            //ATTRIBUTE_AGILITY 2
            //SKILL_SECURITY 2
            //SKILL_STEALTH 2
            // +Downtown apartment
            // +$500 (one month rent)
            move(7,0);
            if(choices || selection == 1)
               addstr("B - 暴力犯だ。誰も私を変えることも止めることもできない。");
            //SKILL_RIFLE 2
            //SKILL_PISTOL 2
            //SKILL_STREETSENSE 2
            //ATTRIBUTE_AGILITY 2
            //ATTRIBUTE_HEALTH 2
            //ATTRIBUTE_STRENGTH 2
            // +Crack house (with stockpiled rations)
            // +A crew (four gang members with knives and pistols)
            move(9,0);
            if(choices || selection == 2)
               addstr("C - 大学に通っている。私にはこの国には助けが必要だとわかっている。");
            //SKILL_SCIENCE 2
            //SKILL_COMPUTERS 2
            //SKILL_WRITING 2
            //SKILL_TEACHING 2
            //SKILL_BUSINESS 1
            //SKILL_LAW 1
            //ATTRIBUTE_INTELLIGENCE 4
            // +University apartment
            // +$200 (one month rent)
            move(11,0);
            if(choices || selection == 3)
               addstr("D - 一人で生きている。他の人と同じように。だが、もう耐えられない。");
            //SKILL_FIRSTAID 2
            //SKILL_STREETSENSE 2
            //ATTRIBUTE_INTELLIGENCE 1
            //ATTRIBUTE_AGILITY 1
            //ATTRIBUTE_HEALTH 2
            // +Homeless shelter
            // +1 all stats (except Wisdom)
            move(13,0);
            if(choices || selection == 4)
               addstr("E - 宣言書を書き、構想を練っている。私は導く準備ができている。");
            //ATTRIBUTE_CHARISMA 2
            //ATTRIBUTE_INTELLIGENCE 2
            //SKILL_LAW 1
            //SKILL_PERSUASION 2
            //SKILL_WRITING 1
            // +Industrial apartment
            // +$100 (one month rent)
            // +50 juice
            move(17,0);
            addstr("私は");
            if(!multipleCityMode) addstr(lcityname);
            else addstr("Seattle, WA");
            addstr("にいる。そして変革の時は来た。");
            break;
      }

      do
      {
         c=getkey();
         if(!choices) c='a'+selection;
      } while(c<'a'||c>'e');

      switch(q)
      {
         case 0:
            // Oct. 19, 1984
            if(c=='a')
            {
               newcr->adjust_attribute(ATTRIBUTE_AGILITY,+2);
               newcr->birthday_month = 10;
               newcr->birthday_day = 19;
            }
            // Mar. 3, 1984
            if(c=='b')
            {
               newcr->adjust_attribute(ATTRIBUTE_STRENGTH,+2);
               newcr->birthday_month = 3;
               newcr->birthday_day = 3;
            }
            // Jan. 24, 1984
            if(c=='c')
            {
               newcr->adjust_attribute(ATTRIBUTE_INTELLIGENCE,+2);
               newcr->birthday_month = 1;
               newcr->birthday_day = 24;
            }
            // Oct. 16, 1984
            if(c=='d')
            {
               newcr->adjust_attribute(ATTRIBUTE_HEART,+2);
               newcr->birthday_month = 10;
               newcr->birthday_day = 16;
            }
            // Sep. 4, 1984
            if(c=='e')
            {
               newcr->adjust_attribute(ATTRIBUTE_CHARISMA,+2);
               newcr->birthday_month = 9;
               newcr->birthday_day = 4;
            }
            newcr->age = year - 1984;
            // Don't count this year in founder's age if starting before birthday
            if(month < newcr->birthday_month ||
               (month==newcr->birthday_month && day<newcr->birthday_day))
            {
               newcr->age--;
            }
            break;
         case 1:
            if(c=='a')
            {
               newcr->set_skill(SKILL_SECURITY,newcr->get_skill(SKILL_SECURITY)+(1));
               newcr->adjust_attribute(ATTRIBUTE_AGILITY,+1);
            }
            if(c=='b')
            {
               newcr->set_skill(SKILL_HANDTOHAND,newcr->get_skill(SKILL_HANDTOHAND)+(1));
               newcr->adjust_attribute(ATTRIBUTE_HEALTH,+1);
            }
            if(c=='c')
            {
               newcr->adjust_attribute(ATTRIBUTE_INTELLIGENCE,+1);
               newcr->set_skill(SKILL_WRITING,newcr->get_skill(SKILL_WRITING)+(1));
            }
            if(c=='d')
            {
               newcr->set_skill(SKILL_PERSUASION,newcr->get_skill(SKILL_PERSUASION)+(1));
               newcr->adjust_attribute(ATTRIBUTE_HEART,+1);
            }
            if(c=='e')
            {
               newcr->set_skill(SKILL_PSYCHOLOGY,newcr->get_skill(SKILL_PSYCHOLOGY)+(1));
               newcr->adjust_attribute(ATTRIBUTE_CHARISMA,+1);
            }
            break;
         case 2:
            if(c=='a')
            {
               newcr->set_skill(SKILL_DISGUISE,newcr->get_skill(SKILL_DISGUISE)+(1));
               newcr->adjust_attribute(ATTRIBUTE_AGILITY,+1);
            }
            if(c=='b')
            {
               newcr->set_skill(SKILL_PSYCHOLOGY,newcr->get_skill(SKILL_PSYCHOLOGY)+(1));
               newcr->adjust_attribute(ATTRIBUTE_AGILITY,+1);
               newcr->adjust_attribute(ATTRIBUTE_HEART,-1);
               newcr->adjust_attribute(ATTRIBUTE_STRENGTH,+1);
            }
            if(c=='c')
            {
               newcr->adjust_attribute(ATTRIBUTE_INTELLIGENCE,+1);
               newcr->set_skill(SKILL_WRITING,newcr->get_skill(SKILL_WRITING)+(1));
            }
            if(c=='d')
            {
               newcr->adjust_attribute(ATTRIBUTE_STRENGTH,+1);
               newcr->set_skill(SKILL_HANDTOHAND,newcr->get_skill(SKILL_HANDTOHAND)+(1));
            }
            if(c=='e')
            {
               newcr->set_skill(SKILL_PERSUASION,newcr->get_skill(SKILL_PERSUASION)+(1));
               newcr->adjust_attribute(ATTRIBUTE_CHARISMA,+1);
            }
            break;
         case 3:
            if(c=='a')
            {
               newcr->set_skill(SKILL_STEALTH,newcr->get_skill(SKILL_STEALTH)+(1));
            }
            if(c=='b')
            {
               newcr->set_skill(SKILL_HANDTOHAND,newcr->get_skill(SKILL_HANDTOHAND)+(1));
            }
            if(c=='c')
            {
               newcr->set_skill(SKILL_LAW,newcr->get_skill(SKILL_LAW)+(1));
            }
            if(c=='d')
            {
               newcr->set_skill(SKILL_SEDUCTION,newcr->get_skill(SKILL_SEDUCTION)+(1));
            }
            if(c=='e')
            {
               newcr->set_skill(SKILL_WRITING,newcr->get_skill(SKILL_WRITING)+1);
            }
            break;
         case 4:
            if(c=='a')
            {
               newcr->set_skill(SKILL_SCIENCE,newcr->get_skill(SKILL_SCIENCE)+(2));
               newcr->adjust_attribute(ATTRIBUTE_INTELLIGENCE,+2);
            }
            if(c=='b')
            {
               newcr->set_skill(SKILL_MUSIC,newcr->get_skill(SKILL_MUSIC)+(2));
               newcr->adjust_attribute(ATTRIBUTE_CHARISMA,+2);
            }
            if(c=='c')
            {
               newcr->set_skill(SKILL_ART,newcr->get_skill(SKILL_ART)+(2));
               newcr->adjust_attribute(ATTRIBUTE_HEART,+2);
            }
            if(c=='d')
            {
               newcr->set_skill(SKILL_COMPUTERS,newcr->get_skill(SKILL_COMPUTERS)+(2));
               newcr->adjust_attribute(ATTRIBUTE_AGILITY,+2);
            }
            if(c=='e')
            {
               newcr->adjust_attribute(ATTRIBUTE_STRENGTH,+2);
               newcr->set_skill(SKILL_SWORD,newcr->get_skill(SKILL_SWORD)+(2));
            }
            break;
         case 5:
            if(c=='a')
            {
               newcr->set_skill(SKILL_DRIVING,newcr->get_skill(SKILL_DRIVING)+(1));
               newcr->set_skill(SKILL_SECURITY,newcr->get_skill(SKILL_SECURITY)+(1));
            }
            if(c=='b')
            {
               newcr->set_skill(SKILL_SHOTGUN,newcr->get_skill(SKILL_SHOTGUN)+(1));
               newcr->set_skill(SKILL_RIFLE,newcr->get_skill(SKILL_RIFLE)+(1));
               newcr->set_skill(SKILL_PSYCHOLOGY,newcr->get_skill(SKILL_PSYCHOLOGY)+(1));
            }
            if(c=='c')
            {
               newcr->set_skill(SKILL_TAILORING,newcr->get_skill(SKILL_TAILORING)+(2));
            }
            if(c=='d')
            {
               newcr->set_skill(SKILL_RELIGION,newcr->get_skill(SKILL_RELIGION)+(1));
               newcr->set_skill(SKILL_PSYCHOLOGY,newcr->get_skill(SKILL_PSYCHOLOGY)+(1));
            }
            if(c=='e')
            {
               newcr->set_skill(SKILL_TEACHING,newcr->get_skill(SKILL_TEACHING)+(2));
            }
            break;
         case 6:
            if(c=='a')
            {
               newcr->set_skill(SKILL_DRIVING,newcr->get_skill(SKILL_DRIVING)+(1));
               newcr->set_skill(SKILL_SECURITY,newcr->get_skill(SKILL_SECURITY)+(1));
               newcr->adjust_attribute(ATTRIBUTE_INTELLIGENCE,+1);
            }
            if(c=='b')
            {
               newcr->set_skill(SKILL_SHOTGUN,newcr->get_skill(SKILL_SHOTGUN)+(2));
               newcr->adjust_attribute(ATTRIBUTE_AGILITY,+1);
            }
            if(c=='c')
            {
               newcr->adjust_attribute(ATTRIBUTE_STRENGTH,+1);
               newcr->set_skill(SKILL_HANDTOHAND,newcr->get_skill(SKILL_HANDTOHAND)+(2));
            }
            if(c=='d')
            {
               newcr->set_skill(SKILL_SEDUCTION,newcr->get_skill(SKILL_SEDUCTION)+(1));
               newcr->set_skill(SKILL_RELIGION,newcr->get_skill(SKILL_RELIGION)+(1));
               newcr->adjust_attribute(ATTRIBUTE_HEART,+1);
               gaylawyer=true;
            }
            if(c=='e')
            {
               newcr->set_skill(SKILL_PERSUASION,newcr->get_skill(SKILL_PERSUASION)+(2));
               newcr->adjust_attribute(ATTRIBUTE_CHARISMA,+1);
            }
            break;
         case 7:
            if(c=='a')
            {
               newcr->set_skill(SKILL_SECURITY,newcr->get_skill(SKILL_SECURITY)+(1));
               newcr->set_skill(SKILL_STEALTH,newcr->get_skill(SKILL_STEALTH)+(1));
               newcr->adjust_attribute(ATTRIBUTE_AGILITY,+1);
            }
            if(c=='b')
            {
               newcr->adjust_attribute(ATTRIBUTE_STRENGTH,+1);
               newcr->set_skill(SKILL_HANDTOHAND,newcr->get_skill(SKILL_HANDTOHAND)+(2));
            }
            if(c=='c')
            {
               newcr->adjust_attribute(ATTRIBUTE_CHARISMA,+1);
               newcr->set_skill(SKILL_BUSINESS,newcr->get_skill(SKILL_BUSINESS)+(2));
            }
            if(c=='d')
            {
               newcr->adjust_attribute(ATTRIBUTE_HEART,-1);
               newcr->adjust_attribute(ATTRIBUTE_CHARISMA,+2);
               newcr->set_skill(SKILL_SEDUCTION,newcr->get_skill(SKILL_SEDUCTION)+(2));
            }
            if(c=='e')
            {
               newcr->adjust_attribute(ATTRIBUTE_INTELLIGENCE,+1);
               newcr->set_skill(SKILL_LAW,newcr->get_skill(SKILL_LAW)+(1));
               newcr->set_skill(SKILL_PERSUASION,newcr->get_skill(SKILL_PERSUASION)+(1));
            }
            break;
         case 8:
            if(c=='a')
            {
               startcar = new Vehicle(*vehicletype[getvehicletype("SPORTSCAR")]);
               // Add heat to the starting vehicle because it is stolen.
               // This is so that you can't immediately sell it at full price.
               startcar->add_heat(10);
               vehicle.push_back(startcar);
               newcr->pref_carid = startcar->id();
            }
            if(c=='b')
            {
               Weapon neww(*weapontype[getweapontype("WEAPON_AUTORIFLE_AK47")]);
               Clip newc(*cliptype[getcliptype("CLIP_ASSAULT")],9);
               newcr->give_weapon(neww,NULL);
               newcr->take_clips(newc,9);
            }
            if(c=='c')
            {
               ledger.force_funds(1000);
            }
            if(c=='d')
            {
               makelawyer=true;
            }
            if(c=='e')
            {
               hasmaps=true;
            }
            break;
         case 9:
            if(c=='a')
            {
               newcr->adjust_attribute(ATTRIBUTE_INTELLIGENCE,+2);
               newcr->adjust_attribute(ATTRIBUTE_AGILITY,+2);
               newcr->set_skill(SKILL_SECURITY,newcr->get_skill(SKILL_SECURITY)+(2));
               newcr->set_skill(SKILL_STEALTH,newcr->get_skill(SKILL_STEALTH)+(2));
               newcr->type = CREATURE_THIEF;
               newcr->type_idname = "CREATURE_THIEF";
               base = SITE_RESIDENTIAL_APARTMENT_UPSCALE;
               ledger.force_funds(ledger.get_funds()+500);

               Armor newa(*armortype[getarmortype("ARMOR_BLACKCLOTHES")]);
               newcr->give_armor(newa,NULL);
            }
            if(c=='b')
            {
               newcr->set_skill(SKILL_RIFLE,newcr->get_skill(SKILL_RIFLE)+(2));
               newcr->set_skill(SKILL_PISTOL,newcr->get_skill(SKILL_PISTOL)+(2));
               newcr->set_skill(SKILL_STREETSENSE,newcr->get_skill(SKILL_STREETSENSE)+(2));
               newcr->adjust_attribute(ATTRIBUTE_AGILITY,+2);
               newcr->adjust_attribute(ATTRIBUTE_HEALTH,+2);
               newcr->adjust_attribute(ATTRIBUTE_STRENGTH,+2);
               newcr->type = CREATURE_GANGMEMBER;
               newcr->type_idname = "CREATURE_GANGMEMBER";
               base = SITE_BUSINESS_CRACKHOUSE;
               recruits = RECRUITS_GANG;
            }
            if(c=='c')
            {
               newcr->adjust_attribute(ATTRIBUTE_INTELLIGENCE,+4);
               newcr->set_skill(SKILL_SCIENCE,newcr->get_skill(SKILL_SCIENCE)+(2));
               newcr->set_skill(SKILL_COMPUTERS,newcr->get_skill(SKILL_COMPUTERS)+(2));
               newcr->set_skill(SKILL_WRITING,newcr->get_skill(SKILL_WRITING)+(2));
               newcr->set_skill(SKILL_TEACHING,newcr->get_skill(SKILL_TEACHING)+(2));
               newcr->set_skill(SKILL_BUSINESS,newcr->get_skill(SKILL_BUSINESS)+(1));
               newcr->set_skill(SKILL_LAW,newcr->get_skill(SKILL_LAW)+(1));
               newcr->type = CREATURE_COLLEGESTUDENT;
               newcr->type_idname = "CREATURE_COLLEGESTUDENT";
               base = SITE_RESIDENTIAL_APARTMENT;
               ledger.force_funds(ledger.get_funds()+200);
            }
            if(c=='d')
            {
               newcr->adjust_attribute(ATTRIBUTE_INTELLIGENCE,+1);
               newcr->adjust_attribute(ATTRIBUTE_AGILITY,+1);
               newcr->adjust_attribute(ATTRIBUTE_HEALTH,+2);
               newcr->set_skill(SKILL_FIRSTAID,newcr->get_skill(SKILL_FIRSTAID)+(2));
               newcr->set_skill(SKILL_STREETSENSE,newcr->get_skill(SKILL_STREETSENSE)+(2));
               newcr->type = CREATURE_HSDROPOUT;
               newcr->type_idname = "CREATURE_HSDROPOUT";
               base = SITE_RESIDENTIAL_SHELTER;

               newcr->adjust_attribute(ATTRIBUTE_HEART,+1);
               newcr->adjust_attribute(ATTRIBUTE_INTELLIGENCE,+1);
               newcr->adjust_attribute(ATTRIBUTE_AGILITY,+1);
               newcr->adjust_attribute(ATTRIBUTE_STRENGTH,+1);
               newcr->adjust_attribute(ATTRIBUTE_HEALTH,+1);
               newcr->adjust_attribute(ATTRIBUTE_CHARISMA,+1);
            }
            if(c=='e')
            {
               newcr->adjust_attribute(ATTRIBUTE_CHARISMA,+2);
               newcr->adjust_attribute(ATTRIBUTE_INTELLIGENCE,+2);
               newcr->set_skill(SKILL_LAW,newcr->get_skill(SKILL_LAW)+(1));
               newcr->set_skill(SKILL_WRITING,newcr->get_skill(SKILL_WRITING)+(1));
               newcr->set_skill(SKILL_PERSUASION,newcr->get_skill(SKILL_PERSUASION)+(2));
               newcr->type = CREATURE_POLITICALACTIVIST;
               newcr->type_idname = "CREATURE_POLITICALACTIVIST";
               base = SITE_RESIDENTIAL_TENEMENT;
               ledger.force_funds(ledger.get_funds()+50);
               newcr->juice+=50;
            }
            break;
      }
   }

   clear();
   set_color(COLOR_WHITE,COLOR_BLACK,1);
   move(4,2);
   addstr("新たな保守の時代", gamelog);
   gamelog.newline();

   set_color(COLOR_WHITE,COLOR_BLACK,0);
   move(6,2);
   addstr(year, gamelog);
   addstr("年", gamelog);
   move(8,2);
   gamelog.newline();
   addstr("保守派の大統領", gamelog);
   char president[80];
   generate_name(president,GENDER_WHITEMALEPATRIARCH);
   addstr(president, gamelog);
   addstr("は70%台後半の支持率の内に2期目を終え、", gamelog);
   move(9,2);
   gamelog.newline();
   addstr("その意思を保守強硬派の", gamelog);
   addstr(execname[EXEC_PRESIDENT], gamelog);
   addstr("に引き継いだ。", gamelog);
   gamelog.nextMessage();

   move(11,2);
   addstr("保守派が大勝した上下両院、保守派が多数を占める合衆国最高裁判所、", gamelog);
   move(12,2);
   gamelog.newline();
   addstr("そしてマスコミは新たな保守の時代の始まりを歓迎した。", gamelog);
   gamelog.nextMessage();

   move(14,2);
   set_color(COLOR_RED,COLOR_BLACK,1);
   addstr(execname[EXEC_PRESIDENT], gamelog);
   addstr("大統領は自身の過激な保守強硬的政策をただちに", gamelog);
   move(15,2);
   gamelog.newline();
   addstr("実行するよう議会に迫った。", gamelog);
   set_color(COLOR_WHITE,COLOR_BLACK,0);
   addstr("左派には自由主義の正気と正義の危機に", gamelog);
   gamelog.newline();
   move(16,2);
   addstr("立ち向かう力は残されていなかった。", gamelog);
   gamelog.nextMessage();

   move(18,2);
   addstr("この暗黒の時代に、リベラル・クライム・スコードが動き出す…", gamelog);
   gamelog.nextMessage();

   getkey();

   clear();
   set_color(COLOR_WHITE,COLOR_BLACK,1);
   move(0,0);
   addstr("あなたは人々からどのように呼ばれるか?");
   set_color(COLOR_WHITE,COLOR_BLACK,0);
   move(1,0);
   addstr("本当の名前の代わりの名前を入力する。");

   enter_name(2,0,newcr->name,CREATURE_NAMELEN,newcr->propername);

   pool.push_back(newcr);

   make_world(hasmaps);

   squadst *newsq=new squadst;
   newsq->id=0;cursquadid++;
   newsq->squad[0]=newcr;
   newcr->squadid=0;
   strcpy(newsq->name,"The Liberal Crime Squad");
   for(int l=0;l<len(location);l++)
   {
      if(location[l]->type==base)
      {
         newcr->base=l;
         newcr->location=l;
         if(startcar) startcar->set_location(l);
         switch(base)
         {
         case SITE_RESIDENTIAL_APARTMENT_UPSCALE:location[l]->renting=500;break;
         case SITE_RESIDENTIAL_APARTMENT:location[l]->renting=200;break;
         case SITE_RESIDENTIAL_TENEMENT:location[l]->renting=100;break;
         case SITE_BUSINESS_CRACKHOUSE:
            location[l]->renting=RENTING_PERMANENT;
            location[l]->compound_stores+=100;
            break;
         }
         location[l]->newrental=1;

         switch(recruits)
         {
         case RECRUITS_GANG:
            for(int i=0;i<4;i++)
            {
               Creature* recruit = new Creature;
               makecreature(*recruit,CREATURE_GANGMEMBER);
               if(recruit->get_weapon().get_itemtypename() == "WEAPON_AUTORIFLE_AK47" ||
                  recruit->get_weapon().get_itemtypename() == "WEAPON_SMG_MP5" ||
                 !recruit->is_armed())
               {
                  Weapon w(*weapontype[getweapontype("WEAPON_SEMIPISTOL_9MM")]);
                  recruit->give_weapon(w,NULL);
                  Clip c(*cliptype[getcliptype("CLIP_9")],4);
                  recruit->take_clips(c,4);
                  recruit->reload(false);
               }

               recruit->align=ALIGN_LIBERAL;
               recruit->set_attribute(ATTRIBUTE_HEART,
                                      recruit->get_attribute(ATTRIBUTE_HEART,false)+
                                      recruit->get_attribute(ATTRIBUTE_WISDOM,false)/2);
               recruit->set_attribute(ATTRIBUTE_WISDOM,
                                      recruit->get_attribute(ATTRIBUTE_WISDOM,false)/2);

               recruit->namecreature();
               strcpy(recruit->name,recruit->propername);

               recruit->location=l;
               recruit->base=l;

               recruit->hireid=newcr->id;

               newsq->squad[i+1]=recruit;
               recruit->squadid=newsq->id;
               pool.push_back(recruit);
            }
            break;
         }

         #ifdef GIVEBLOODYARMOR
         Armor *newa= new Armor(*armortype[getarmortype("ARMOR_CLOTHES")]);
         newa->set_bloody(true);
         location[l]->loot.push_back(newi);
         #endif

         #ifdef HIGHFUNDS
         ledger.force_funds(100000);
         #endif

         break;
      }
   }
   //newcr->juice=0;
   squad.push_back(newsq);
   activesquad=newsq;

   if(makelawyer)
   {
      Creature* lawyer=new Creature;
      makecreature(*lawyer,CREATURE_LAWYER);
      // Make sure lawyer is of the appropriate gender for dating the main character;
      // opposite sex by default, same sex if the option was chosen that mentions
      // homosexuality
      if(gaylawyer)
      {
         lawyer->gender_conservative=lawyer->gender_liberal=newcr->gender_conservative;

         // neutral founder gets neutral partner
      }
      else
      {
         if(newcr->gender_conservative==GENDER_MALE)
            lawyer->gender_liberal=lawyer->gender_conservative=GENDER_FEMALE;

         if(newcr->gender_conservative==GENDER_FEMALE)
            lawyer->gender_liberal=lawyer->gender_conservative=GENDER_MALE;

         // neutral founder gets random partner
      }

      // Ensure the lawyer has good heart/wisdom stats
      if(lawyer->get_attribute(ATTRIBUTE_HEART,false)<newcr->get_attribute(ATTRIBUTE_HEART,false)-2)
         lawyer->adjust_attribute(ATTRIBUTE_HEART,-2);

      lawyer->set_attribute(ATTRIBUTE_WISDOM,1);

      lawyer->namecreature();
      lawyer->flag|=CREATUREFLAG_SLEEPER;
      lawyer->flag|=CREATUREFLAG_LOVESLAVE;
      lawyer->align=ALIGN_LIBERAL;
      lawyer->infiltration=0.3f;
      lawyer->age=28;

      location[lawyer->worklocation]->mapped=1;
      lawyer->hireid=newcr->id;
      pool.push_back(lawyer);
      lawyer->location=lawyer->base=lawyer->worklocation;
   }

   uniqueCreatures.initialize();
}
