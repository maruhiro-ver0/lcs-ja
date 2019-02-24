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

vector<Creature *> activatable_liberals()
{
   vector<Creature *> temppool;
   for(int p=0;p<len(pool);p++) if(pool[p]->is_active_liberal())
   {
      if(pool[p]->squadid!=-1)
      {
         int sq=getsquad(pool[p]->squadid);
         if(sq!=-1) if(squad[sq]->activity.type!=ACTIVITY_NONE) continue;
      }
      temppool.push_back(pool[p]);
   }
   return temppool;
}

/* base - activate the uninvolved */
void activate()
{
   vector<Creature *> temppool = activatable_liberals();

   if(!len(temppool)) return;

   sortliberals(temppool,activesortingchoice[SORTINGCHOICE_ACTIVATE]);

   int page=0;

   while(true)
   {
      music.play(MUSIC_ACTIVATE);
      erase();

      set_color(COLOR_WHITE,COLOR_BLACK,0);
      printfunds();

      move(0,0);
      addstr("部隊として行動しないリベラルの活動");
      move(1,0);
      addstr("----コードネーム---------スキル--健康-----位置----------------------------------");
      move(1,57);
      addstr("活動");

      int y=2;
      for(int p=page*19;p<len(temppool)&&p<page*19+19;p++,y++)
      {
         set_color(COLOR_WHITE,COLOR_BLACK,0);
         move(y,0);
         addchar(y+'A'-2);addstr(" - ");
         addstr(temppool[p]->name);

         char bright=0;
         int skill=0;
         for(int sk=0;sk<SKILLNUM;sk++)
         {
            skill+=temppool[p]->get_skill(sk);
            if(temppool[p]->get_skill_ip(sk)>=100+(10*temppool[p]->get_skill(sk))&&
               temppool[p]->get_skill(sk)<temppool[p]->skill_cap(sk,true))bright=1;
         }

         set_color(COLOR_WHITE,COLOR_BLACK,bright);

         move(y,25);
         addstr(skill);

         printhealthstat(*temppool[p],y,33,TRUE);

         if(mode==REVIEWMODE_JUSTICE)set_color(COLOR_YELLOW,COLOR_BLACK,1);
         else set_color(COLOR_WHITE,COLOR_BLACK,0);
         move(y,42);
         addstr(location[temppool[p]->location]->getname(true, true));

         move(y,57);
         // Let's add some color here...
         set_activity_color(temppool[p]->activity.type);
         addstr(getactivity(temppool[p]->activity));
      }

      set_color(COLOR_WHITE,COLOR_BLACK,0);
      move(22,0);
      addstr("アルファベットキーで活動を割り当てる。");
      move(23,0);
      addpagestr();
      addstr(" Tキーでソートする。");
      move(24,0);
      addstr("Zキーで簡単な活動を平行で行う。");

      int c=getkey();

      //PAGE UP
      if((c==interface_pgup||c==KEY_UP||c==KEY_LEFT)&&page>0) page--;
      //PAGE DOWN
      if((c==interface_pgdn||c==KEY_DOWN||c==KEY_RIGHT)&&(page+1)*19<len(temppool)) page++;

      if(c>='a'&&c<='s')
      {
         int p=page*19+c-'a';
         if(p<len(temppool)) activate(temppool[p]);
      }

      if(c=='t')
      {
         sorting_prompt(SORTINGCHOICE_ACTIVATE);
         sortliberals(temppool,activesortingchoice[SORTINGCHOICE_ACTIVATE],true);
      }

      if(c=='z') activatebulk();

      if(c=='x'||c==ENTER||c==ESC||c==SPACEBAR) break;
   }
}

int classlist=0;
void listclasses(Creature *cr)
{
   set_color(COLOR_WHITE,COLOR_BLACK,0);
   move(10,40);
   addstr("1日あたり$60かかる。何を学ぶか?");
   if(classlist==0)
   {
      set_color(COLOR_WHITE,COLOR_BLACK,cr->activity.type==ACTIVITY_STUDY_DEBATING);
      move(12,40);
      addstr("1 - 政治学");

      set_color(COLOR_WHITE,COLOR_BLACK,cr->activity.type==ACTIVITY_STUDY_BUSINESS);
      move(13,40);
      addstr("2 - 経済学");

      set_color(COLOR_WHITE,COLOR_BLACK,cr->activity.type==ACTIVITY_STUDY_PSYCHOLOGY);
      move(14,40);
      addstr("3 - 心理学");

      set_color(COLOR_WHITE,COLOR_BLACK,cr->activity.type==ACTIVITY_STUDY_LAW);
      move(15,40);
      addstr("4 - 法学");

      set_color(COLOR_WHITE,COLOR_BLACK,cr->activity.type==ACTIVITY_STUDY_SCIENCE);
      move(16,40);
      addstr("5 - 物理学");

      set_color(COLOR_WHITE,COLOR_BLACK,0);
      move(17,40);
      addstr("6 - その他");
   }
   else if(classlist==1)
   {
      set_color(COLOR_WHITE,COLOR_BLACK,cr->activity.type==ACTIVITY_STUDY_DRIVING);
      move(12,40);
      addstr("1 - 自動車教習所");

      set_color(COLOR_WHITE,COLOR_BLACK,cr->activity.type==ACTIVITY_STUDY_FIRST_AID);
      move(13,40);
      addstr("2 - 応急手当");

      set_color(COLOR_WHITE,COLOR_BLACK,cr->activity.type==ACTIVITY_STUDY_ART);
      move(14,40);
      addstr("3 - 絵画");

      set_color(COLOR_WHITE,COLOR_BLACK,cr->activity.type==ACTIVITY_STUDY_DISGUISE);
      move(15,40);
      addstr("4 - 演劇");

      set_color(COLOR_WHITE,COLOR_BLACK,cr->activity.type==ACTIVITY_STUDY_MARTIAL_ARTS);
      move(16,40);
      addstr("5 - カンフー");

      set_color(COLOR_WHITE,COLOR_BLACK,0);
      move(17,40);
      addstr("6 - その他");
   }
   else if(classlist==2)
   {
      set_color(COLOR_WHITE,COLOR_BLACK,cr->activity.type==ACTIVITY_STUDY_GYMNASTICS);
      move(12,40);
      addstr("1 - スポーツジム");

      set_color(COLOR_WHITE,COLOR_BLACK,cr->activity.type==ACTIVITY_STUDY_WRITING);
      move(13,40);
      addstr("2 - 文筆");

      set_color(COLOR_WHITE,COLOR_BLACK,cr->activity.type==ACTIVITY_STUDY_TEACHING);
      move(14,40);
      addstr("3 - 教育");

      set_color(COLOR_WHITE,COLOR_BLACK,cr->activity.type==ACTIVITY_STUDY_MUSIC);
      move(15,40);
      addstr("4 - 音楽");

      set_color(COLOR_WHITE,COLOR_BLACK,cr->activity.type==ACTIVITY_STUDY_LOCKSMITHING);
      move(16,40);
      addstr("5 - ロッククライミング");

      set_color(COLOR_WHITE,COLOR_BLACK,0);
      move(17,40);
      addstr("6 - その他");
   }
}

void updateclasschoice(Creature *cr, char choice)
{
   if(choice=='6')
   {
      classlist=(classlist+1)%3;
      listclasses(cr);
   }
   else
   {
      if(classlist==0)
      {
         switch(choice)
         {
            case '1':cr->activity.type=ACTIVITY_STUDY_DEBATING;break;
            case '2':cr->activity.type=ACTIVITY_STUDY_BUSINESS;break;
            case '3':cr->activity.type=ACTIVITY_STUDY_PSYCHOLOGY;break;
            case '4':cr->activity.type=ACTIVITY_STUDY_LAW;break;
            case '5':cr->activity.type=ACTIVITY_STUDY_SCIENCE;break;
         }
      }
      else if(classlist==1)
      {
         switch(choice)
         {
            case '1':cr->activity.type=ACTIVITY_STUDY_DRIVING;break;
            case '2':cr->activity.type=ACTIVITY_STUDY_FIRST_AID;break;
            case '3':cr->activity.type=ACTIVITY_STUDY_ART;break;
            case '4':cr->activity.type=ACTIVITY_STUDY_DISGUISE;break;
            case '5':cr->activity.type=ACTIVITY_STUDY_MARTIAL_ARTS;break;
         }
      }
      else if(classlist==2)
      {
         switch(choice)
         {
            case '1':cr->activity.type=ACTIVITY_STUDY_GYMNASTICS;break;
            case '2':cr->activity.type=ACTIVITY_STUDY_WRITING;break;
            case '3':cr->activity.type=ACTIVITY_STUDY_TEACHING;break;
            case '4':cr->activity.type=ACTIVITY_STUDY_MUSIC;break;
            case '5':cr->activity.type=ACTIVITY_STUDY_LOCKSMITHING;break;
         }
      }
      listclasses(cr);
   }
}

void activate(Creature *cr)
{
   int hostagecount=0,state=0,oldstate=0,choice=0;
   char havedead=0;
   for(int p=0;p<len(pool);p++)
   {
      if(pool[p]->alive&&pool[p]->align!=1&&pool[p]->location==cr->location) hostagecount++;
      if(!pool[p]->alive) havedead=1;
   }

   while(true)
   {
      erase();

      set_color(COLOR_WHITE,COLOR_BLACK,0);
      printfunds();

      move(0,0);
      if(cr->income)
      {
         addstr(cr->name);
         addstr("は昨日$");
         addstr(cr->income);
         addstr("を稼いだ。今日はどうするか?");
      }
      else
      {
         addstr("活動の選択: ");
         addstr(cr->name);
         addstr("は今日は何をするか?");
      }

      printcreatureinfo(cr);

      makedelimiter();

      if(!state) switch(cr->activity.type)
      {
      case ACTIVITY_COMMUNITYSERVICE:
      case ACTIVITY_TROUBLE:
      case ACTIVITY_GRAFFITI:
      case ACTIVITY_POLLS:
      case ACTIVITY_DOS_ATTACKS:
      case ACTIVITY_HACKING:
      case ACTIVITY_WRITE_LETTERS:
      case ACTIVITY_WRITE_GUARDIAN:
         state='a';
         break;
      case ACTIVITY_DONATIONS:
      case ACTIVITY_SELL_TSHIRTS:
      case ACTIVITY_SELL_ART:
      case ACTIVITY_SELL_MUSIC:
         state='b';
         break;
      case ACTIVITY_SELL_DRUGS:
      case ACTIVITY_PROSTITUTION:
      case ACTIVITY_CCFRAUD:
      case ACTIVITY_DOS_RACKET:
         state='c';
         break;
      case ACTIVITY_RECRUITING:
      case ACTIVITY_MAKE_ARMOR:
      case ACTIVITY_REPAIR_ARMOR:
      case ACTIVITY_STEALCARS:
      case ACTIVITY_WHEELCHAIR:
         state='d';
         break;
      case ACTIVITY_TEACH_POLITICS:
      case ACTIVITY_TEACH_COVERT:
      case ACTIVITY_TEACH_FIGHTING:
         state='t';
         break;
      case ACTIVITY_HOSTAGETENDING:
         state='i';
         break;
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
      case ACTIVITY_STUDY_WRITING:
      case ACTIVITY_STUDY_ART:
      case ACTIVITY_STUDY_MUSIC:
      case ACTIVITY_STUDY_TEACHING:
      case ACTIVITY_STUDY_LOCKSMITHING:
         state='l';
         break;
      case ACTIVITY_CLINIC:
         state='m';
         break;
      case ACTIVITY_HEAL:
         state='h';
         break;
      case ACTIVITY_BURY:
         state='z';
         break;
      case ACTIVITY_NONE:
         state='x';
         break;
      }
      oldstate=state;

      set_color(COLOR_WHITE,COLOR_BLACK,state=='a');
      mvaddstr(10,1,"A - リベラル主義を訴えかける");

      set_color(COLOR_WHITE,COLOR_BLACK,state=='b');
      mvaddstr(11,1,"B - 合法的な資金集めを行う");

      set_color(COLOR_WHITE,COLOR_BLACK,state=='c');
      mvaddstr(12,1,"C - 違法な資金集めを行う");

      set_color(COLOR_WHITE,COLOR_BLACK,state=='d');
      mvaddstr(13,1,"D - スカウトと調達を行う");

      set_color(COLOR_WHITE,COLOR_BLACK,state=='t');
      mvaddstr(14,1,"T - 他のリベラルを教育する");

      if(hostagecount>0)set_color(COLOR_WHITE,COLOR_BLACK,state=='i');
      else set_color(COLOR_BLACK,COLOR_BLACK,1);
      mvaddstr(15,1,"I - 捕らえた保守を尋問する");

      set_color(COLOR_WHITE,COLOR_BLACK,state=='l');
      mvaddstr(16,1,"L - 大学で学ぶ");

      if(clinictime(*cr)) set_color(COLOR_WHITE,COLOR_BLACK,state=='m');
      else set_color(COLOR_BLACK,COLOR_BLACK,1);
      mvaddstr(17,1,"M - 無料の診療所へ行く");

      if(cr->get_skill(SKILL_FIRSTAID)!=0)
         set_color(COLOR_WHITE,COLOR_BLACK,state=='h');
      else
         set_color(COLOR_BLACK,COLOR_BLACK,1);
      mvaddstr(18,1,"H - リベラルを治療する");

      if(havedead)set_color(COLOR_WHITE,COLOR_BLACK,state=='z');
      else set_color(COLOR_BLACK,COLOR_BLACK,1);
      mvaddstr(19,1,"Z - 遺体を処理する");

      siegest *siege=NULL;
      if(selectedsiege!=-1) siege=&location[selectedsiege]->siege;
      if(activesquad) if(activesquad->squad[0]->location!=-1) siege=&location[activesquad->squad[0]->location]->siege;
      char sieged=0;
      if(siege) sieged=siege->siege;
      /*char underattack=0;
      if(siege&&sieged) underattack=siege->underattack;*/

      if(!sieged)
         set_color(COLOR_WHITE,COLOR_BLACK,0);
      else
         set_color(COLOR_BLACK,COLOR_BLACK,1);
      mvaddstr(20,1,"E - リベラルに装備させる");

      if(state=='a'||state=='b'||state=='c'||state=='d')
      {
         set_color(COLOR_WHITE,COLOR_BLACK,0);
         mvaddstr(19,40,"? - ヘルプ");
      }

      set_color(COLOR_WHITE,COLOR_BLACK,0);
      mvaddstr(20,40,"Enter - 選択を決定する");

      set_color(COLOR_WHITE,COLOR_BLACK,state=='x');
      mvaddstr(21,1,"X - 今は何もしない");

      switch(state)
      {
      case 'a':
         set_color(COLOR_WHITE,COLOR_BLACK,cr->activity.type==ACTIVITY_COMMUNITYSERVICE);
         mvaddstr(10,40,"1 - 社会奉仕");

         set_color(COLOR_WHITE,COLOR_BLACK,cr->activity.type==ACTIVITY_TROUBLE);
         mvaddstr(11,40,"2 - 反抗");

         set_color(COLOR_WHITE,COLOR_BLACK,cr->activity.type==ACTIVITY_GRAFFITI);
         mvaddstr(12,40,"3 - 落書き");

         set_color(COLOR_WHITE,COLOR_BLACK,cr->activity.type==ACTIVITY_POLLS);
         mvaddstr(13,40,"4 - 世論調査");

         //set_color(COLOR_WHITE,COLOR_BLACK,cr->activity.type==ACTIVITY_DOS_ATTACKS);
         //mvaddstr(14,40,"5 - ウェブサイト荒らし");

         set_color(COLOR_WHITE,COLOR_BLACK,cr->activity.type==ACTIVITY_HACKING);
         mvaddstr(14,40,"5 - ハッキング");

         set_color(COLOR_WHITE,COLOR_BLACK,cr->activity.type==ACTIVITY_WRITE_LETTERS);
         mvaddstr(15,40,"6 - 新聞への投書");

         if(cr->location!=-1&&
            location[cr->location]->compound_walls & COMPOUND_PRINTINGPRESS)
         {
            set_color(COLOR_WHITE,COLOR_BLACK,cr->activity.type==ACTIVITY_WRITE_GUARDIAN);
            mvaddstr(16,40,"7 - リベラルガーディアンの記事を書く");
         }
         break;
      case 'b':
         set_color(COLOR_WHITE,COLOR_BLACK,cr->activity.type==ACTIVITY_DONATIONS);
         mvaddstr(10,40,"1 - 寄付金集め");

         set_color(COLOR_WHITE,COLOR_BLACK,cr->activity.type==ACTIVITY_SELL_TSHIRTS);
         move(11,40);
         if(cr->get_skill(SKILL_TAILORING)>=8)
            addstr("2 - リベラルTシャツの販売");
         else if(cr->get_skill(SKILL_TAILORING)>=4)
            addstr("2 - 刺繍入りシャツの販売");
         else
            addstr("2 - タイダイ染めTシャツの販売");

         set_color(COLOR_WHITE,COLOR_BLACK,cr->activity.type==ACTIVITY_SELL_ART);
         move(12,40);
         if(cr->get_skill(SKILL_ART)>=8)
            addstr("3 - リベラルアーツの販売");
         else if(cr->get_skill(SKILL_ART)>=4)
            addstr("3 - 絵画の販売");
         else
            addstr("3 - 似顔絵の販売");

         set_color(COLOR_WHITE,COLOR_BLACK,cr->activity.type==ACTIVITY_SELL_MUSIC);
         move(13,40);
         if(cr->get_skill(SKILL_MUSIC)>8)
            addstr("4 - リベラルミュージックの演奏");
         else
            addstr("4 - ストリートミュージックの演奏");
         break;
      case 'c':
         set_color(COLOR_WHITE,COLOR_BLACK,cr->activity.type==ACTIVITY_SELL_DRUGS);
         mvaddstr(10,40,"1 - スペシャルケーキの販売");

         set_color(COLOR_WHITE,COLOR_BLACK,cr->activity.type==ACTIVITY_PROSTITUTION);
#ifndef ZEROMORAL
         if(cr->age < 18)
            set_color(COLOR_BLACK, COLOR_BLACK, 1);    //Grayed out for minors
#endif
         mvaddstr(11,40,"2 - 売春");

         set_color(COLOR_WHITE,COLOR_BLACK,cr->activity.type==ACTIVITY_CCFRAUD);
         mvaddstr(12,40,"3 - クレジットカード番号の不正取得");

         /*set_color(COLOR_WHITE,COLOR_BLACK,cr->activity.type==ACTIVITY_DOS_RACKET);
         mvaddstr(13,40,"4 - 用心棒");*/
         break;
      case 'd':
         set_color(COLOR_WHITE,COLOR_BLACK,cr->activity.type==ACTIVITY_RECRUITING);
         mvaddstr(10,40,"1 - スカウト活動");

         set_color(COLOR_WHITE,COLOR_BLACK,cr->activity.type==ACTIVITY_MAKE_ARMOR);
         mvaddstr(11,40,"2 - 服の縫製");

         set_color(COLOR_WHITE,COLOR_BLACK,cr->activity.type==ACTIVITY_REPAIR_ARMOR);
         mvaddstr(12,40,"3 - 服の修繕");

         if(cr->canwalk()) {
            set_color(COLOR_WHITE,COLOR_BLACK,cr->activity.type==ACTIVITY_STEALCARS);
            mvaddstr(13,40,"4 - 自動車泥棒");
         } else {
            if(!(cr->flag&CREATUREFLAG_WHEELCHAIR)) set_color(COLOR_WHITE,COLOR_BLACK,cr->activity.type==ACTIVITY_WHEELCHAIR);
            else set_color(COLOR_BLACK,COLOR_BLACK,1);
            mvaddstr(13,40,"4 - 車椅子の調達");
         }
         break;
      case 't':
         set_color(COLOR_WHITE,COLOR_BLACK,0);
         move(10,40);
         addstr("リベラルに何を教育する?");

         set_color(COLOR_WHITE,COLOR_BLACK,cr->activity.type==ACTIVITY_TEACH_POLITICS);
         move(12,40);
         addstr("1 - 政治");

         set_color(COLOR_WHITE,COLOR_BLACK,cr->activity.type==ACTIVITY_TEACH_COVERT);
         move(13,40);
         addstr("2 - 秘密工作");

         set_color(COLOR_WHITE,COLOR_BLACK,cr->activity.type==ACTIVITY_TEACH_FIGHTING);
         move(14,40);
         addstr("3 - 戦闘");
         break;
      case 'l':
         listclasses(cr);
         break;
      }

      set_color(COLOR_WHITE,COLOR_BLACK,0);
      switch(cr->activity.type)
      {
      case ACTIVITY_COMMUNITYSERVICE:
         move(22,3);
         addstr(cr->name);
         addstr("は老人、地域の図書館、その他を手助けする。");
         move(23,1);
         addstr("  これこそがリベラルだ。");
         break;
      case ACTIVITY_TROUBLE:
         move(22,3);
         addstr(cr->name);
         addstr("は公共の場で騒ぎを起こす。");
         break;
      case ACTIVITY_GRAFFITI:
         move(22,3);
         addstr(cr->name);
         addstr("はスプレーで政治的な落書きをする。");
         move(23,1);
         addstr("  「アート(芸術)」と「ハート(心)」がリベラルを喚起するだろう。");
         break;
      case ACTIVITY_POLLS:
         move(22,3);
         addstr(cr->name);
         addstr("はインターネットで世論の動向を調査する。");
         move(23,1);
         addstr("  調査はリベラルアジェンダの動向を明らかにするだろう。");
         move(24,1);
         addstr("  「コンピュータ」のスキルと「知識」があればよりよい結果が得られる。");
         break;
      case ACTIVITY_DOS_ATTACKS:
         move(22,3);
         addstr(cr->name);
         addstr("は保守派のウェブサイトを攻撃する。");
         move(23,1);
         addstr("  「コンピュータ」のスキルがあればより効果があるだろう。");
         break;
      case ACTIVITY_HACKING:
         move(22,3);
         addstr(cr->name);
         addstr("はウェブサイトを攻撃し、プライベートネットワークをハックする。");
         move(23,1);
         addstr("  「コンピュータ」のスキルと「知識」があれば結果が得られる。");
         move(24,1);
         addstr("  ハッカーが複数いれば成功と発見の機会が増すだろう。");
         break;
      case ACTIVITY_WRITE_LETTERS:
         move(22,3);
         addstr(cr->name);
         addstr("は今起こっていることを投書する。");
         break;
      case ACTIVITY_WRITE_GUARDIAN:
         move(22,3);
         addstr(cr->name);
         addstr("はLCSの新聞記事を書く。");
         break;
      case ACTIVITY_DONATIONS:
         move(22,3);
         addstr(cr->name);
         addstr("はLCSへの寄付を呼びかける。");
         move(23,1);
         addstr("  「説得」力、人々の評価、そして着ている服が重要だ。");
         move(24,1);
         addstr("");
         break;
      case ACTIVITY_SELL_TSHIRTS:
         move(22,3);
         addstr(cr->name);
         if(cr->get_skill(SKILL_TAILORING)>=8)
            addstr("はリベラルスローガンのプリントされたシャツを販売する。");
         else if(cr->get_skill(SKILL_TAILORING)>=4)
            addstr("は刺繍をしたシャツを街頭で売る。");
         else addstr("はタイダイ染めのTシャツを街頭で売る。");
         break;
      case ACTIVITY_SELL_ART:
         move(22,3);
         addstr(cr->name);
         if(cr->get_skill(SKILL_ART)>=8)
            addstr("はリベラルアジェンダを表現した絵を描きそれを売る。");
         else if(cr->get_skill(SKILL_ART)>=4)
            addstr("は街頭で絵を描きそれを売る。");
         else addstr("は人々の似顔絵を描きそれを売る。");
         break;
      case ACTIVITY_SELL_MUSIC:
         move(22,3);
         addstr(cr->name);
         addstr("は街頭へ出向いてバケツでドラムの演奏をする。");
         move(23,1);
         addstr("  または、ギターがあればそれを弾く。");
         break;
      case ACTIVITY_RECRUITING:
         move(22,3);
         addstr(cr->name);
         addstr("はLCSに加わる者を探す。");
         break;
      case ACTIVITY_STEALCARS:
         move(22,3);
         addstr(cr->name);
         addstr("は自動車を探しそれを盗む。");
         break;
      case ACTIVITY_SELL_DRUGS:
         move(22,3);
         addstr(cr->name);
         addstr("はマジカルに光り輝くアダマンチウムの坑道への扉を開く");
         move(23,1);
         addstr("  大人のケーキを焼いてそれを売る。");
         break;
      case ACTIVITY_PROSTITUTION:
         move(22,3);
         addstr(cr->name);
         addstr("は金のために体を売る。");
         break;
      case ACTIVITY_CCFRAUD:
         move(22,3);
         addstr(cr->name);
         addstr("はオンラインで不正にクレジットカード番号を取得する。");
         break;
      case ACTIVITY_DOS_RACKET:
         move(22,3);
         addstr(cr->name);
         addstr("はウェブサイトを攻撃しない代わりに金を要求する。");
         move(23,1);
         addstr("");
         break;
      case ACTIVITY_TEACH_POLITICS:
         move(22,1);
         addstr("  スキルを高める: 文筆、説得、法律、ストリートセンス、科学、");
         move(23,1);
         addstr("    信仰、ビジネス、音楽、芸術");
         move(24,1);
         addstr("  1日あたり$20かかる。可能なリベラルは全員参加する。");
         break;
      case ACTIVITY_TEACH_COVERT:
         move(22,1);
         addstr("  スキルを高める: コンピュータ、セキュリティ、隠密、変装、裁縫、");
         move(23,1);
         addstr("    誘惑、心理学、運転");
         move(24,1);
         addstr("  1日あたり$60かかる。可能なリベラルは全員参加する。");
         break;
      case ACTIVITY_TEACH_FIGHTING:
         move(22,1);
         addstr("  スキルを高める: 全ての武器のスキル、格闘技、防御、応急手当");
         move(24,1);
         addstr("  1日あたり$100かかる。可能なリベラルは全員参加する。");
         break;
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
      case ACTIVITY_STUDY_WRITING:
      case ACTIVITY_STUDY_ART:
      case ACTIVITY_STUDY_MUSIC:
      case ACTIVITY_STUDY_TEACHING:
      case ACTIVITY_STUDY_LOCKSMITHING:
         move(22,3);
         addstr(cr->name);
         addstr("は大学で学ぶ。");
         move(23,1);
         addstr("1日あたり$60かかる。");
         break;
      }

      int c=getkey();

      if(c>='a'&&c<='z') state=c;
      if((c>='a'&&c<='z') || (c>='0'&&c<='9'))
      {
         choice=c;
         switch(state)
         {
         case 'a':
            switch(choice)
            {
            case '1':cr->activity.type=ACTIVITY_COMMUNITYSERVICE;break;
            case '2':cr->activity.type=ACTIVITY_TROUBLE;break;
            case '3':cr->activity.type=ACTIVITY_GRAFFITI;
               cr->activity.arg=-1;
               break;
            case '4':cr->activity.type=ACTIVITY_POLLS;break;
            //case '5':cr->activity.type=ACTIVITY_DOS_ATTACKS;break;
            case '5':cr->activity.type=ACTIVITY_HACKING;break;
            case '6':cr->activity.type=ACTIVITY_WRITE_LETTERS;break;
            case '7':
               if(cr->location!=-1&&
                  location[cr->location]->compound_walls & COMPOUND_PRINTINGPRESS)
               {
                  cr->activity.type=ACTIVITY_WRITE_GUARDIAN;break;
               }
            default:
               if(cr->get_attribute(ATTRIBUTE_WISDOM,true)>7||cr->juice<0)
                  cr->activity.type=ACTIVITY_COMMUNITYSERVICE;
               else if(cr->get_attribute(ATTRIBUTE_WISDOM,true)>4)
                  cr->activity.type=ACTIVITY_TROUBLE;
               else
               {
                  if(cr->get_skill(SKILL_COMPUTERS)>2)
                     cr->activity.type=ACTIVITY_HACKING;
                  else if(cr->get_skill(SKILL_ART)>1)
                  {
                     cr->activity.type=ACTIVITY_GRAFFITI;
                     cr->activity.arg=-1;
                  }
                  else
                     cr->activity.type=ACTIVITY_TROUBLE;
               }
            }
            break;
         case 'b':
            switch(choice)
            {
            case '1':cr->activity.type=ACTIVITY_DONATIONS;break;
            case '2':cr->activity.type=ACTIVITY_SELL_TSHIRTS;break;
            case '3':cr->activity.type=ACTIVITY_SELL_ART;break;
            case '4':cr->activity.type=ACTIVITY_SELL_MUSIC;break;
            default:
               if(cr->get_weapon().is_instrument())
                  cr->activity.type=ACTIVITY_SELL_MUSIC;
               else if(cr->get_skill(SKILL_ART)>1)
                  cr->activity.type=ACTIVITY_SELL_ART;
               else if(cr->get_skill(SKILL_TAILORING)>1)
                  cr->activity.type=ACTIVITY_SELL_TSHIRTS;
               else if(cr->get_skill(SKILL_MUSIC)>1)
                  cr->activity.type=ACTIVITY_SELL_MUSIC;
               else cr->activity.type=ACTIVITY_DONATIONS;
            }
            break;
         case 'c':
            switch(choice)
            {
            case '1':cr->activity.type=ACTIVITY_SELL_DRUGS;break;
            case '2':
#ifndef ZEROMORAL
               if(cr->age >= 18)
#endif
                  cr->activity.type=ACTIVITY_PROSTITUTION;break;
            case '3':cr->activity.type=ACTIVITY_CCFRAUD;break;
            //case '4':cr->activity.type=ACTIVITY_DOS_RACKET;break;
            default:
               if(cr->get_skill(SKILL_COMPUTERS)>1)
                  cr->activity.type=ACTIVITY_CCFRAUD;
#ifndef ZEROMORAL
               else if(cr->get_skill(SKILL_SEDUCTION)>1 && cr->age >= 18)
#else
               else if(cr->get_skill(SKILL_SEDUCTION)>1)
#endif
                  cr->activity.type=ACTIVITY_PROSTITUTION;
               else cr->activity.type=ACTIVITY_SELL_DRUGS;
            }
            break;
         case 'd':
            switch(choice)
            {
            case '1': { // Pick type to recruit
               activityst oact=cr->activity;
               cr->activity.type=ACTIVITY_NONE;
               recruitSelect(*cr);
               if(cr->activity.type==ACTIVITY_RECRUITING) break;
               else cr->activity=oact;
               break; }
            case '2': { // Pick clothing to make
               activityst oact=cr->activity;
               cr->activity.type=ACTIVITY_NONE;
               select_makeclothing(cr);
               if(cr->activity.type==ACTIVITY_MAKE_ARMOR) break;
               else cr->activity=oact;
               break; }
            case '3':cr->activity.type=ACTIVITY_REPAIR_ARMOR;break;
            case '4':
               if(cr->canwalk())
                  cr->activity.type=ACTIVITY_STEALCARS;
               else if(!(cr->flag & CREATUREFLAG_WHEELCHAIR))
                  cr->activity.type=ACTIVITY_WHEELCHAIR;
               break;
            default: break;
            }
            break;
         case 't':
            switch(choice)
            {
            case '1':cr->activity.type=ACTIVITY_TEACH_POLITICS;break;
            case '2':cr->activity.type=ACTIVITY_TEACH_COVERT;break;
            case '3':cr->activity.type=ACTIVITY_TEACH_FIGHTING;break;
            default:
               switch(cr->type)
               {
               // this first block are creatures with All Weapon Skills, Martial Arts, Dodge, and First Aid
               case CREATURE_ATHLETE:
               case CREATURE_BOUNCER: // for fighting skills
               case CREATURE_COP: // for fighting skills
               case CREATURE_CCS_ARCHCONSERVATIVE: // for fighting skills
               case CREATURE_CCS_MOLOTOV: // for fighting skills
               case CREATURE_CCS_SNIPER: // for fighting skills
               case CREATURE_CCS_VIGILANTE: // for fighting skills
               case CREATURE_DEATHSQUAD: // for fighting skills
               case CREATURE_DOCTOR: // for First Aid
               case CREATURE_FIREFIGHTER: // for fighting skills
               case CREATURE_GANGMEMBER: // for fighting skills
               case CREATURE_GANGUNIT: // for fighting skills
               case CREATURE_GUARDDOG:
               case CREATURE_GENETIC:
               case CREATURE_HARDENED_VETERAN: // for fighting skills
               case CREATURE_HICK:
               case CREATURE_MARTIALARTIST: // for fighting skills
               case CREATURE_MERC: // for fighting skills
               case CREATURE_MILITARYOFFICER: // for fighting skills
               case CREATURE_MILITARYPOLICE: // for fighting skills
               case CREATURE_MUTANT:
               case CREATURE_NURSE: // for First Aid
               case CREATURE_PRISONGUARD: // for fighting skills
               case CREATURE_SEAL: // for fighting skills
               case CREATURE_SECURITYGUARD: // for fighting skills
               case CREATURE_SOLDIER: // for fighting skills
               case CREATURE_SWAT: // for fighting skills
               case CREATURE_TANK: // fpr fighting skills
               case CREATURE_VETERAN: // for fighting skills
                  cr->activity.type=ACTIVITY_TEACH_FIGHTING;
                  break;
               // this second block are creatures with Computers, Security, Stealth, Disguise, Tailoring, Seduction, Psychology, & Driving
               case CREATURE_ACTOR: // for Disguise
               case CREATURE_AGENT: // for Driving & Psychology
               case CREATURE_AMATEURMAGICIAN:
               case CREATURE_BIKER: // for Driving
               case CREATURE_BUM:
               case CREATURE_CONSTRUCTIONWORKER: // for Driving
               case CREATURE_CRACKHEAD:
               case CREATURE_EDUCATOR: // for Psychology & Driving
               case CREATURE_FASHIONDESIGNER: // for Tailoring
               case CREATURE_GARBAGEMAN: // for Driving
               case CREATURE_HSDROPOUT:
               case CREATURE_LOCKSMITH: // for Security
               case CREATURE_MAILMAN:
               case CREATURE_PLUMBER:
               case CREATURE_PRISONER:
               case CREATURE_PROGRAMMER: // for Computers
               case CREATURE_PROSTITUTE: // for Seduction
               case CREATURE_PSYCHOLOGIST: // for Psychology
               case CREATURE_SECRET_SERVICE: // for Driving & Psychology
               case CREATURE_SEWERWORKER:
               case CREATURE_TAXIDRIVER: // for Driving
               case CREATURE_THIEF: // for Disguise, Security, & Stealth
               case CREATURE_TRUCKER: // for Driving
               case CREATURE_WORKER_FACTORY_CHILD:
               case CREATURE_WORKER_SERVANT:
               case CREATURE_WORKER_SWEATSHOP: // for Tailoring
                  cr->activity.type=ACTIVITY_TEACH_COVERT;
                  break;
               // this third block are creatures with Writing, Persuasion, Law, Street Sense, Science, Religion, Business, Music, & Art
               case CREATURE_AUTHOR: // for Writing & Persuasion
               case CREATURE_BANK_MANAGER: // for Business
               case CREATURE_BANK_TELLER:
               case CREATURE_CAMERAMAN: // for Art
               case CREATURE_CARSALESMAN: // for Business & Persuasion
               case CREATURE_CHEF:
               case CREATURE_CLERK:
               case CREATURE_COLLEGESTUDENT: // for Art, Music, Science, & Writing
               case CREATURE_CORPORATE_CEO: // for Business
               case CREATURE_CORPORATE_MANAGER: // for Business
               case CREATURE_CRITIC_ART: // for Writing, Persuasion, & Art
               case CREATURE_CRITIC_MUSIC: // for Writing, Persuasion, & Music
               case CREATURE_DANCER: // for Art & Music
               case CREATURE_ENGINEER: // for Science
               case CREATURE_FASTFOODWORKER:
			   case CREATURE_BAKER:
			   case CREATURE_BARISTA:
			   case CREATURE_BARTENDER:
			   case CREATURE_FOOTBALLCOACH: // for Persuasion
               case CREATURE_HAIRSTYLIST: // for Art
               case CREATURE_HIPPIE: // for Art & Music
               case CREATURE_JOURNALIST: // for Writing & Persuasion
               case CREATURE_JUDGE_CONSERVATIVE: // for Law & Writing
               case CREATURE_JUDGE_LIBERAL: // for Law & Writing
               case CREATURE_JUROR:
               case CREATURE_LANDLORD: // for Business
               case CREATURE_LAWYER: // for Law & Persuasion
               case CREATURE_MATHEMATICIAN: // for Science
               case CREATURE_MUSICIAN: // for Music
               case CREATURE_NEWSANCHOR:
               case CREATURE_NUN: // for Religion
               case CREATURE_OFFICEWORKER: // for Business
               case CREATURE_PAINTER: // for Art
               case CREATURE_PHOTOGRAPHER: // for Art
               case CREATURE_POLITICALACTIVIST: // for Persuasion, Law, & Writing
               case CREATURE_POLITICIAN: // for Law & Persuasion
               case CREATURE_PRIEST: // for Religion
               case CREATURE_RADIOPERSONALITY: // for Persuasion
               case CREATURE_RETIREE:
               case CREATURE_SCIENTIST_EMINENT: // for Science
               case CREATURE_SCIENTIST_LABTECH: // for Science
               case CREATURE_SCULPTOR: // for Art
               case CREATURE_SOCIALITE: // for Persuasion, Art, & Music
               case CREATURE_TEACHER:
               case CREATURE_TEENAGER:
               case CREATURE_TELEMARKETER: // for Persuasion
               case CREATURE_WORKER_FACTORY_NONUNION:
               case CREATURE_WORKER_FACTORY_UNION:
               case CREATURE_WORKER_JANITOR:
               case CREATURE_WORKER_SECRETARY: // for Writing
               case CREATURE_YOGAINSTRUCTOR:
               default:
                  cr->activity.type=ACTIVITY_TEACH_POLITICS;
                  break;
               }
               break;
            }
            break;
         case 'i':
            if(hostagecount>0)
            {
               activityst oact=cr->activity;
               cr->activity.type=ACTIVITY_NONE;
               select_tendhostage(cr);
               if(cr->activity.type==ACTIVITY_HOSTAGETENDING) break;
               else cr->activity=oact;
            }
            state=oldstate;
            break;
         case 'l':
            updateclasschoice(cr, choice);
            break;
         case 'm':
            if(clinictime(*cr)) cr->activity.type=ACTIVITY_CLINIC;
            else state=oldstate;
            break;
         case 'h':
            if(cr->get_skill(SKILL_FIRSTAID)) cr->activity.type=ACTIVITY_HEAL;
            else state=oldstate;
            break;
         case 'z':
            if(havedead) cr->activity.type=ACTIVITY_BURY;
            else state=oldstate;
            break;
         case 'e':
            if(!sieged)
            {
               //create a temp squad containing just this liberal
               int oldsquadid = cr->squadid;
               squadst *oldactivesquad = activesquad;
               activesquad=new squadst;
               strcpy(activesquad->name, "Temporary Squad");
               activesquad->id=cursquadid;
               activesquad->squad[0]=cr;
               cr->squadid = activesquad->id;
               //go to equipment screen
               equip(location[activesquad->squad[0]->location]->loot,-1);
               //once you're done, restore original squad status.
               delete activesquad;
               activesquad = oldactivesquad;
               cr->squadid = oldsquadid;
            }
            state=oldstate;
            break;
         /*case 'w':
            if(location[cr->location]->compound_walls==COMPOUND_PRINTINGPRESS)
            {
               activityst oact=cr->activity;
               cr->activity.type=ACTIVITY_NONE;
               if(select_view(cr,cr->activity.arg))
               {
                  cr->activity.type=ACTIVITY_WRITE_GUARDIAN;
                  break;
               }
               else cr->activity=oact;
            }
            state=oldstate;
            break;*/
         case 'x':
            cr->activity.type=ACTIVITY_NONE;
            break;
         default:
            state=oldstate;
            break;
         }
      }

      // Enter pressed
      if(c=='x'||c==ENTER||c==ESC||c==SPACEBAR) break;
      // ? Pressed
      if(c=='?')
         if(state=='a'||state=='b'||state=='c'||state=='d')
            HelpActivities(cr->activity.type); // Call activity help pages
   }
}


void activatebulk()
{
   vector<Creature *> temppool = activatable_liberals();

   if(!len(temppool)) return;

   int page=0,selectedactivity=0;

   while(true)
   {
      erase();

      set_color(COLOR_WHITE,COLOR_BLACK,0);
      printfunds();

      move(0,0);
      addstr("部隊として行動しないリベラルの活動");
      move(1,0);
      addstr("----コードネーム---------現在の活動---------------------------------------------");
      move(1,51);
      addstr("平行で行う活動");

      if(selectedactivity==0) set_color(COLOR_WHITE,COLOR_BLACK,1);
      else set_color(COLOR_WHITE,COLOR_BLACK,0);
      move(2,51);
      addstr("1 - リベラル主義の訴えかけ");
      if(selectedactivity==1) set_color(COLOR_WHITE,COLOR_BLACK,1);
      else set_color(COLOR_WHITE,COLOR_BLACK,0);
      move(3,51);
      addstr("2 - 合法的な資金集め");
      if(selectedactivity==2) set_color(COLOR_WHITE,COLOR_BLACK,1);
      else set_color(COLOR_WHITE,COLOR_BLACK,0);
      move(4,51);
      addstr("3 - 違法な資金集め");
      if(selectedactivity==3) set_color(COLOR_WHITE,COLOR_BLACK,1);
      else set_color(COLOR_WHITE,COLOR_BLACK,0);
      move(5,51);
      addstr("4 - 世論調査");
      if(selectedactivity==4) set_color(COLOR_WHITE,COLOR_BLACK,1);
      else set_color(COLOR_WHITE,COLOR_BLACK,0);
      move(6,51);
      addstr("5 - 自動車泥棒");
      if(selectedactivity==5) set_color(COLOR_WHITE,COLOR_BLACK,1);
      else set_color(COLOR_WHITE,COLOR_BLACK,0);
      move(7,51);
      addstr("6 - 社会奉仕");

      int y=2;
      for(int p=page*19;p<len(temppool)&&p<page*19+19;p++,y++)
      {
         set_color(COLOR_WHITE,COLOR_BLACK,0);
         move(y,0);
         addchar(y+'A'-2);addstr(" - ");
         addstr(temppool[p]->name);

         move(y,25);
         set_activity_color(temppool[p]->activity.type);
         addstr(getactivity(temppool[p]->activity));
         /*if(temppool[p]->activity.type==ACTIVITY_TROUBLE)
         {
         addstr(" ($");
         addstr(temppool[p]->activity.arg);
         addstr(")");
         }*/
      }

      set_color(COLOR_WHITE,COLOR_BLACK,0);
      move(22,0);
      addstr("割り当てる活動の数字キーを押す。");
      move(23,0);
      addpagestr();

      int c=getkey();

      //PAGE UP
      if((c==interface_pgup||c==KEY_UP||c==KEY_LEFT)&&page>0) page--;
      //PAGE DOWN
      if((c==interface_pgdn||c==KEY_DOWN||c==KEY_RIGHT)&&(page+1)*19<len(temppool)) page++;

      if(c>='a'&&c<='s')
      {
         int p=page*19+c-'a';
         if(p<len(temppool))
         {
            switch(selectedactivity)
            {
            case 0: //Activism
               if(temppool[p]->get_attribute(ATTRIBUTE_WISDOM,true)>7||temppool[p]->juice<0)
                  temppool[p]->activity.type=ACTIVITY_COMMUNITYSERVICE;
               else if(temppool[p]->get_attribute(ATTRIBUTE_WISDOM,true)>4)
                  temppool[p]->activity.type=ACTIVITY_TROUBLE;
               else
               {
                  if(temppool[p]->get_skill(SKILL_COMPUTERS)>2)
                     temppool[p]->activity.type=ACTIVITY_HACKING;
                  else if(temppool[p]->get_skill(SKILL_ART)>1)
                  {
                     temppool[p]->activity.type=ACTIVITY_GRAFFITI;
                     temppool[p]->activity.arg=-1;
                  }
                  else temppool[p]->activity.type=ACTIVITY_TROUBLE;
               }
               break;
            case 1: //Fundraising
               if(temppool[p]->get_weapon().is_instrument())
                  temppool[p]->activity.type=ACTIVITY_SELL_MUSIC;
               else if(temppool[p]->get_skill(SKILL_ART)>1)
                  temppool[p]->activity.type=ACTIVITY_SELL_ART;
               else if(temppool[p]->get_skill(SKILL_TAILORING)>1)
                  temppool[p]->activity.type=ACTIVITY_SELL_TSHIRTS;
               else if(temppool[p]->get_skill(SKILL_MUSIC)>1)
                  temppool[p]->activity.type=ACTIVITY_SELL_MUSIC;
               else temppool[p]->activity.type=ACTIVITY_DONATIONS;
               break;
            case 2: //Illegal Fundraising
               if(temppool[p]->get_skill(SKILL_COMPUTERS)>1)
                  temppool[p]->activity.type=ACTIVITY_CCFRAUD;
#ifndef ZEROMORAL
               else if(temppool[p]->get_skill(SKILL_SEDUCTION)>1 && temppool[p]->age >=18)
#else
               else if(temppool[p]->get_skill(SKILL_SEDUCTION)>1)
#endif
                  temppool[p]->activity.type=ACTIVITY_PROSTITUTION;
               else
                  temppool[p]->activity.type=ACTIVITY_SELL_DRUGS;
               break;
            case 3: //Check polls
               temppool[p]->activity.type=ACTIVITY_POLLS;
               break;
            case 4: //Steal cars
               temppool[p]->activity.type=ACTIVITY_STEALCARS;
               break;
            case 5: //Volunteer
               temppool[p]->activity.type=ACTIVITY_COMMUNITYSERVICE;
               break;
            }
         }
      }
      if(c>='1'&&c<='6')
         selectedactivity=c-'1';

      if(c=='x'||c==ENTER||c==ESC||c==SPACEBAR) break;
   }
}


/* base - activate - hostages */
void select_tendhostage(Creature *cr)
{
   vector<Creature *> temppool;

   for(int p=0;p<len(pool);p++)
   {
      if(pool[p]->align!=1&&
         pool[p]->alive&&
         pool[p]->location==cr->location)
      {
         temppool.push_back(pool[p]);
      }
   }

   if(!len(temppool))return;
   if(len(temppool)==1)
   {
      cr->activity.type=ACTIVITY_HOSTAGETENDING;
      cr->activity.arg=temppool[0]->id;
      return;
   }

   int page=0;

   while(true)
   {
      erase();

      set_color(COLOR_WHITE,COLOR_BLACK,0);
      move(0,0);
      addstr(cr->name);
      addstr("はどの捕虜を監視するか?");
      move(1,0);
      addstr("----コードネーム---------スキル--健康-----位置----------------------------------");
      move(1,57);
      addstr("捕らえてからの日数");

      int y=2;
      for(int p=page*19;p<len(temppool)&&p<page*19+19;p++,y++)
      {
         set_color(COLOR_WHITE,COLOR_BLACK,0);
         move(y,0);
         addchar(y+'A'-2);addstr(" - ");
         addstr(temppool[p]->name);

         char bright=0;
         int skill=0;
         for(int sk=0;sk<SKILLNUM;sk++)
         {
            skill+=temppool[p]->get_skill(sk);
            if(temppool[p]->get_skill_ip(sk)>=100+(10*temppool[p]->get_skill(sk))&&
               temppool[p]->get_skill(sk)<temppool[p]->skill_cap(sk,true))bright=1;
         }

         set_color(COLOR_WHITE,COLOR_BLACK,bright);

         move(y,25);
         addstr(skill);

         printhealthstat(*temppool[p],y,33,TRUE);

         if(mode==REVIEWMODE_JUSTICE)set_color(COLOR_YELLOW,COLOR_BLACK,1);
         else set_color(COLOR_WHITE,COLOR_BLACK,0);
         mvaddstr(y,42,location[temppool[p]->location]->getname(true, true));

         move(y,57);
         set_color(COLOR_MAGENTA,COLOR_BLACK,1);
         addstr(temppool[p]->joindays);
         addstr(" ");
         if(temppool[p]->joindays>1)addstr("日");
         else addstr("日");
      }

      set_color(COLOR_WHITE,COLOR_BLACK,0);
      move(22,0);
      addstr("アルファベットキーで保守を選択する");
      move(23,0);
      addpagestr();

      int c=getkey();

      //PAGE UP
      if((c==interface_pgup||c==KEY_UP||c==KEY_LEFT)&&page>0) page--;
      //PAGE DOWN
      if((c==interface_pgdn||c==KEY_DOWN||c==KEY_RIGHT)&&(page+1)*19<len(temppool)) page++;

      if(c>='a'&&c<='s')
      {
         int p=page*19+(int)(c-'a');
         if(p<len(temppool))
         {
            cr->activity.type=ACTIVITY_HOSTAGETENDING;
            cr->activity.arg=temppool[p]->id;
            return;
         }
      }

      if(c=='x'||c==ENTER||c==ESC||c==SPACEBAR) break;
   }
}


long select_hostagefundinglevel(Creature *cr,Creature *hs)
{
   long flevel=-1;

   erase();

   set_color(COLOR_WHITE,COLOR_BLACK,0);
   printfunds();
   move(0,0);
   addstr("Select a Funding Level for this Operation:");

   move(2,0);
   addstr("A - Don't spend anything.  ");
   addstr(cr->name);
   addstr(" is just on watch duty.");

   move(3,0);
   addstr("B - Don't spend anything.  ");
   addstr(cr->name);
   addstr(" will turn the prisoner over time.");

   move(4,0);
   addstr("C - $20 per day.  Enough for some props.");

   move(5,0);
   addstr("D - $50 per day.  ");
   addstr(cr->name);
   addstr(" will go for a thrifty indoctrination.");

   move(6,0);
   addstr("E - $100 per day.  ");
   addstr(cr->name);
   addstr(" needs enough freedom to be creative.");

   move(7,0);
   addstr("F - $500 per day.  It is imperative that the Conservative be turned quickly.");

   move(8,0);
   addstr("K - This Conservative has become a liability and needs to be terminated.");

   move(10,0);
   addstr("Enter - On second thought, this isn't a job for ");
   addstr(cr->name);
   addstr(".");

   do
   {
      int c=getkey();

      if(c=='a')flevel=0;
      if(c=='b')flevel=1;
      if(c=='c')flevel=20;
      if(c=='d')flevel=50;
      if(c=='e')flevel=100;
      if(c=='f')flevel=500;
      if(c=='k')flevel=666;
      if(c=='x'||c==ENTER||c==ESC||c==SPACEBAR) break;
   } while(flevel==-1);

   return flevel;
}

struct recruitData
{
   int type;
   char* name;
   int difficulty;
   recruitData(int type_,char* name_,int difficulty_) : type(type_),name(name_),difficulty(difficulty_) { }
};

recruitData recruitable_creatures[] = {
   recruitData(CREATURE_VETERAN, (char*)"退役軍人", 4),
   recruitData(CREATURE_ATHLETE, (char*)"スポーツ選手", 4),
   recruitData(CREATURE_COLLEGESTUDENT, (char*)"大学生", 1),
   recruitData(CREATURE_PROGRAMMER, (char*)"プログラマ", 4),
   recruitData(CREATURE_DANCER, (char*)"ダンサー", 4),
   recruitData(CREATURE_DOCTOR, (char*)"医者", 4),
   recruitData(CREATURE_FASHIONDESIGNER, (char*)"ファッションデザイナー", 6),
   recruitData(CREATURE_GANGMEMBER, (char*)"ギャング", 2),
   recruitData(CREATURE_HIPPIE, (char*)"ヒッピー", 1),
   recruitData(CREATURE_JOURNALIST, (char*)"ジャーナリスト", 4),
   recruitData(CREATURE_JUDGE_LIBERAL, (char*)"判事", 6),
   recruitData(CREATURE_LAWYER, (char*)"弁護士", 4),
   recruitData(CREATURE_LOCKSMITH, (char*)"錠前師", 6),
   recruitData(CREATURE_MARTIALARTIST, (char*)"格闘家", 4),
   recruitData(CREATURE_MUSICIAN, (char*)"音楽家", 4),
   recruitData(CREATURE_MUTANT, (char*)"ミュータント", 4),
   recruitData(CREATURE_PROSTITUTE, (char*)"売春婦", 2),
   recruitData(CREATURE_PSYCHOLOGIST, (char*)"精神科医", 4),
   recruitData(CREATURE_TAXIDRIVER, (char*)"タクシー運転手", 4),
   recruitData(CREATURE_TEACHER, (char*)"教師", 4)
};

// Return the difficulty of tracking this character type down, for the
// purpose of the activation menu. 0 is trivial, 10 is impossible.
int recruitFindDifficulty(int creatureType)
{
   for(int i=0; i<len(recruitable_creatures); i++)
      if(recruitable_creatures[i].type == creatureType)
         return recruitable_creatures[i].difficulty;
   return 10; // No recruitData; assume impossible to recruit
}

char* recruitName(int creatureType)
{
   for(int i=0; i<len(recruitable_creatures); i++)
      if(recruitable_creatures[i].type == creatureType)
         return recruitable_creatures[i].name;
   return (char*)"missingno";
}

void recruitSelect(Creature &cr)
{
   // Number of recruitable creatures
   int options = len(recruitable_creatures);
   for(int i=0; i<options; i++)
   {
      // Dynamic difficulty for certain creatures, recalculated each time the function is called
      if(recruitable_creatures[i].type == CREATURE_MUTANT)
      {
         if(law[LAW_NUCLEARPOWER] == -2 && law[LAW_POLLUTION] == -2)
            recruitable_creatures[i].difficulty = 2;
         else if(law[LAW_NUCLEARPOWER] == -2 || law[LAW_POLLUTION] == -2)
            recruitable_creatures[i].difficulty = 6;
         else
            recruitable_creatures[i].difficulty = 9;
      }
   }

   int page=0;
   while(true)
   {
      erase();
      set_color(COLOR_WHITE,COLOR_BLACK,1);
      move(0,0);
      addstr(cr.name);
      addstr("はどのようなタイプの人物をスカウトするか?");
      set_color(COLOR_WHITE,COLOR_BLACK,0);
      move(1,0);
      addstr("----タイプ---------------------------------------面会の難易度-------------------");

      int y=2,difficulty;
      for(int p=page*19;p<options&&p<page*19+19;p++)
      {
         set_color(COLOR_WHITE,COLOR_BLACK,0);
         move(y,0);
         addchar(y+'A'-2);addstr(" - ");
         addstr(recruitable_creatures[p].name);

         move(y,49);
         difficulty=recruitable_creatures[p].difficulty;
         switch(difficulty)
         {
         case 0:
            set_color(COLOR_GREEN,COLOR_BLACK,1);
            addstr("単純");
            break;
         case 1:
            set_color(COLOR_CYAN,COLOR_BLACK,1);
            addstr("とても容易");
            break;
         case 2:
            set_color(COLOR_CYAN,COLOR_BLACK,0);
            addstr("容易");
            break;
         case 3:
            set_color(COLOR_BLUE,COLOR_BLACK,1);
            addstr("平均の下");
            break;
         case 4:
            set_color(COLOR_WHITE,COLOR_BLACK,1);
            addstr("平均");
            break;
         case 5:
            set_color(COLOR_WHITE,COLOR_BLACK,0);
            addstr("平均の上");
            break;
         case 6:
            set_color(COLOR_YELLOW,COLOR_BLACK,1);
            addstr("困難");
            break;
         case 7:
            set_color(COLOR_MAGENTA,COLOR_BLACK,0);
            addstr("とても困難");
            break;
         case 8:
            set_color(COLOR_MAGENTA,COLOR_BLACK,1);
            addstr("非常に困難");
            break;
         case 9:
            set_color(COLOR_RED,COLOR_BLACK,0);
            addstr("ほぼ不可能");
            break;
         default:
            set_color(COLOR_RED,COLOR_BLACK,1);
            addstr("不可能");
            break;
         }

         y++;
      }

      set_color(COLOR_WHITE,COLOR_BLACK,0);
      move(22,0);
      addstr("アルファベットキーで職業を選択する。");
      move(23,0);
      addpagestr();

      int c=getkey();

      //PAGE UP
      if((c==interface_pgup||c==KEY_UP||c==KEY_LEFT)&&page>0)page--;
      //PAGE DOWN
      if((c==interface_pgdn||c==KEY_DOWN||c==KEY_RIGHT)&&(page+1)*19<options)page++;

      if(c>='a'&&c<='s')
      {
         int p=page*19+(int)(c-'a');
         if(p<options)
         {
            cr.activity.type = ACTIVITY_RECRUITING;
            cr.activity.arg = recruitable_creatures[p].type;
            break;
         }
      }

      if(c=='x'||c==ENTER||c==ESC||c==SPACEBAR) break;
   }

   return;
}

/* base - activate - make clothing */
void select_makeclothing(Creature *cr)
{
   vector<int> armortypei;
   for(int a=0;a<len(armortype);a++)
   {
      if(armortype[a]->get_make_difficulty() == 0)
         continue;

      if(armortype[a]->deathsquad_legality()
         && (law[LAW_POLICEBEHAVIOR]!=-2 || law[LAW_DEATHPENALTY]!=-2))
         continue;

      armortypei.push_back(a);
   }

   int page=0;

   while(true)
   {
      erase();

      set_color(COLOR_WHITE,COLOR_BLACK,1);
      move(0,0);
      addstr(cr->name);
      addstr("は何を作るか? (注意: その服を持っていれば半分のコストで作れる)");
      set_color(COLOR_WHITE,COLOR_BLACK,0);
      move(1,0);
      addstr("----名前-----------------------------難易度-----------------コスト--------------");

      int y=2,difficulty;
      for(int p=page*19;p<len(armortypei)&&p<page*19+19;p++,y++)
      {
         difficulty=armor_makedifficulty(*armortype[armortypei[p]],cr);
         if(difficulty<0) difficulty=0;

         set_color(COLOR_WHITE,COLOR_BLACK,0);
         move(y,0);
         addchar(y+'A'-2);addstr(" - ");
         addstr(armortype[armortypei[p]]->get_name());

         move(y,37);
         switch(difficulty)
         {
         case 0:
            set_color(COLOR_GREEN,COLOR_BLACK,1);
            addstr("単純");
            break;
         case 1:
            set_color(COLOR_CYAN,COLOR_BLACK,1);
            addstr("とても容易");
            break;
         case 2:
            set_color(COLOR_CYAN,COLOR_BLACK,0);
            addstr("容易");
            break;
         case 3:
            set_color(COLOR_BLUE,COLOR_BLACK,1);
            addstr("平均の下");
            break;
         case 4:
            set_color(COLOR_WHITE,COLOR_BLACK,1);
            addstr("平均");
            break;
         case 5:
            set_color(COLOR_WHITE,COLOR_BLACK,0);
            addstr("平均の上");
            break;
         case 6:
            set_color(COLOR_YELLOW,COLOR_BLACK,1);
            addstr("困難");
            break;
         case 7:
            set_color(COLOR_MAGENTA,COLOR_BLACK,0);
            addstr("とても困難");
            break;
         case 8:
            set_color(COLOR_MAGENTA,COLOR_BLACK,1);
            addstr("非常に困難");
            break;
         case 9:
            set_color(COLOR_RED,COLOR_BLACK,0);
            addstr("ほぼ不可能");
            break;
         default:
            set_color(COLOR_RED,COLOR_BLACK,1);
            addstr("不可能");
            break;
         }

         set_color(COLOR_GREEN,COLOR_BLACK,1);
         string price = '$'+tostring(armortype[armortypei[p]]->get_make_price());
         move(y,64-len(price));
         addstr(price);
      }

      set_color(COLOR_WHITE,COLOR_BLACK,0);
      move(22,0);
      addstr("アルファベットキーで作る服を選択する。");
      move(23,0);
      addpagestr();

      int c=getkey();

      //PAGE UP
      if((c==interface_pgup||c==KEY_UP||c==KEY_LEFT)&&page>0)page--;
      //PAGE DOWN
      if((c==interface_pgdn||c==KEY_DOWN||c==KEY_RIGHT)&&(page+1)*19<len(armortypei))page++;

      if(c>='a'&&c<='s')
      {
         int p=page*19+c-'a';
         if(p<len(armortypei))
         {
            cr->activity.type=ACTIVITY_MAKE_ARMOR;
            cr->activity.arg=armortypei[p]; //Use id name of armor type instead? -XML
            return;
         }
      }

      if(c=='x'||c==ENTER||c==ESC||c==SPACEBAR) break;
   }
}

int armor_makedifficulty(Armor& type, Creature *cr)
{
   return armor_makedifficulty(*armortype[getarmortype(type.get_itemtypename())], cr);
}

int armor_makedifficulty(ArmorType& type,Creature *cr) //Make class method? -XML
{
   int basedif=type.get_make_difficulty()-cr->get_skill(SKILL_TAILORING)+3;
   return MAX(basedif,0);
}


/* base - activate - trouble */
long select_troublefundinglevel(Creature *cr)
{
   long flevel=-1;

   erase();

   set_color(COLOR_WHITE,COLOR_BLACK,0);
   printfunds();
   move(0,0);
   addstr("Select a Funding Level for this Operation:");

   move(2,0);
   addstr("A - Don't spend anything.  ");
   addstr(cr->name);
   addstr(" just needs something constructive to do.");

   move(3,0);
   addstr("B - $20 per day.  Some minor purchases are needed.");

   move(4,0);
   addstr("C - $50 per day.  Disobedience costs money.");

   move(5,0);
   addstr("D - $100 per day.  Enough to be really disobedient.");

   move(6,0);
   addstr("E - $500 per day.  The Machine will buckle under the weight of");
   move(7,0);
   addstr("    ");
   addstr(cr->name);
   addstr("'s Numerous and Varied Liberal Acts.");

   move(9,0);
   addstr("Enter - On second thought, this isn't a job for ");
   addstr(cr->name);
   addstr(".");

   do
   {
      int c=getkey();

      if(c=='a')flevel=0;
      if(c=='b')flevel=20;
      if(c=='c')flevel=50;
      if(c=='d')flevel=100;
      if(c=='e')flevel=500;
      if(c=='x'||c==ENTER||c==ESC||c==SPACEBAR) break;
   } while(flevel==-1);

   return flevel;
}



/* base - activate - select a topic to write about */
char select_view(Creature *cr,int &v)
{
   int page=0;

   while(true)
   {
      erase();

      set_color(COLOR_WHITE,COLOR_BLACK,1);
      move(0,0);
      addstr("Write a news story if the LCS makes the news on the selected topic today, or");
      move(1,0);
      addstr("write editorials if there is no current news but there is public interest.");
      set_color(COLOR_WHITE,COLOR_BLACK,0);
      move(2,0);
      addstr("ﾄﾄﾄﾄTOPICﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄINTERESTﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄ");

      int y=3,x=0;
      for(int p=page*18;p<VIEWNUM-3&&p<page*18+18;p++,y++)
      {
         set_color(COLOR_WHITE,COLOR_BLACK,0);
         move(y,x);
         addchar((p-page*18)+'A');addstr(" - ");
         addstr(getview(p,false));

         move(y,44);
         if(public_interest[p]>100)
         {
            set_color(COLOR_RED,COLOR_BLACK,1);
            addstr("Extremely Controversial");
         }
         else if(public_interest[p]>50)
         {
            set_color(COLOR_YELLOW,COLOR_BLACK,1);
            addstr("Dinner Table Topic");
         }
         else if(public_interest[p]>10)
         {
            set_color(COLOR_WHITE,COLOR_BLACK,1);
            addstr("Significant Interest");
         }
         else if(public_interest[p]>0)
         {
            set_color(COLOR_WHITE,COLOR_BLACK,0);
            addstr("Minor Discussion");
         }
         else
         {
            set_color(COLOR_BLACK,COLOR_BLACK,1);
            addstr("Exhausted");
         }
      }

      set_color(COLOR_WHITE,COLOR_BLACK,0);
      move(22,0);
      addstr("Press a Letter to select a Topic");
      move(23,0);
      addpagestr();

      int c=getkey();

      //PAGE UP
      if((c==interface_pgup||c==KEY_UP||c==KEY_LEFT)&&page>0) page--;
      //PAGE DOWN
      if((c==interface_pgdn||c==KEY_DOWN||c==KEY_RIGHT)&&(page+1)*16<VIEWNUM-3) page++;

      if(c>='a'&&c<='a'+18)
      {
         int p=page*18+c-'a';
         if(p<VIEWNUM-3)
         {
            v=p;
            return 1;
         }
      }

      if(c=='x'||c==ENTER||c==ESC||c==SPACEBAR) break;
   }

   return 0;
}

