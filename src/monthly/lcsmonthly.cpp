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

//TODO: Log the monthly report? --Addictgamer

/* monthly - reports the guardian's power to the player */
void guardianupdate(char size, int power)
{
   music.play(MUSIC_NEWSPAPER);
   clear();

   set_color(COLOR_WHITE,COLOR_BLACK,0);
   move(5,2);
   if(size)
   {
      addstr("The monthly Liberal Guardian newspaper", gamelog);
   }
   else
   {
      addstr("The monthly Liberal Guardian online newsletter", gamelog);
   }

   addstr(" is published.", gamelog);
   gamelog.newline();

   move(7,2);
   if(power<0)
   {
      addstr("The only readers are Conservatives, who seem to think it's funny.", gamelog);
   }
   else if(power==0)
   {
      addstr("Unfortunately, nobody seems interested.", gamelog);
   }
   else if(power<5)
   {
      addstr("Very few people seem to be interested.", gamelog);
   }
   else if(power<50)
   {
      addstr("A fair number of people are reading it.", gamelog);
   }
   else if(power<100)
   {
      addstr("Many people are reading it.", gamelog);
   }
   else if(power<250)
   {
      addstr("The response is very strong. People are changing their minds.", gamelog);
   }
   else
   {
      addstr("The response is electric. Everyone is talking about this month's ", gamelog);
      move(8,2);
      addstr("Liberal Guardian.",  gamelog);
   }
   gamelog.nextMessage();

   getkey();

   return;
}



/* monthly - lets the player choose a special edition for the guardian */
int choosespecialedition(char &clearformess)
{
   //Temporary, maybe put special edition definition into an xml file. -XML
	static const string document_types[] =
	{  // This list MUST be in alphabetical order for binary_search() to work right
      "LOOT_AMRADIOFILES",
      "LOOT_CABLENEWSFILES",
      "LOOT_CCS_BACKERLIST",
      "LOOT_CEOLOVELETTERS",
      "LOOT_CEOPHOTOS",
      "LOOT_CEOTAXPAPERS",
      "LOOT_CORPFILES",
      "LOOT_INTHQDISK",
      "LOOT_JUDGEFILES",
      "LOOT_POLICERECORDS",
      "LOOT_PRISONFILES",
      "LOOT_RESEARCHFILES",
      "LOOT_SECRETDOCUMENTS"
	};
	static const vector<string> dox(document_types,document_types+len(document_types));

   int page=0;

   //char havetype[LOOTNUM];
   //for(int l=0;l<LOOTNUM;l++)havetype[l]=0;
   vector<bool> havetype(len(loottype),false);
   vector<int> loottypeindex;

   //FIND ALL LOOT TYPES
   for(int loc=0;loc<len(location);loc++)
   {
      if(location[loc]->renting==RENTING_NOCONTROL) continue;

      consolidateloot(location[loc]->loot);
      for(int l=0;l<len(location[loc]->loot);l++)
      {
         if(!location[loc]->loot[l]->is_loot()) continue;
         if(!binary_search(dox.begin(),dox.end(),location[loc]->loot[l]->get_itemtypename())) continue;

         if(!havetype[getloottype(location[loc]->loot[l]->get_itemtypename())])
         {
            loottypeindex.push_back(getloottype(location[loc]->loot[l]->get_itemtypename()));
            havetype[getloottype(location[loc]->loot[l]->get_itemtypename())]=true;
         }
      }
   }
   for(int sq=0;sq<len(squad);sq++)
   {
      consolidateloot(squad[sq]->loot);
      for(int l=0;l<len(squad[sq]->loot);l++)
      {
         if(!squad[sq]->loot[l]->is_loot()) continue;
         if(!binary_search(dox.begin(),dox.end(),squad[sq]->loot[l]->get_itemtypename())) continue;

         if(!havetype[getloottype(squad[sq]->loot[l]->get_itemtypename())])
         {
            loottypeindex.push_back(getloottype(squad[sq]->loot[l]->get_itemtypename()));
            havetype[getloottype(squad[sq]->loot[l]->get_itemtypename())]=true;
         }
      }
   }

   if(!len(loottypeindex)) return -1;

   clearformess=1;

   //PICK ONE
   while(true)
   {
      music.play(MUSIC_NEWSPAPER);
      clear();

      set_color(COLOR_WHITE,COLOR_BLACK,0);
      move(0,0);
      addstr("リベラルガーディアンに特別記事を掲載するか?");

      int x=1,y=10;
      char str[200];

      for(int l=page*18;l<len(loottypeindex)&&l<page*18+18;l++)
      {
         str[0]=l-page*18+'A';
         str[1]='\x0';
         strcat(str," - ");
         strcat(str,loottype[loottypeindex[l]]->get_name());

         move(y,x);
         addstr(str);

         x+=26;
         if(x>53) x=1,y++;
      }

      //PAGE UP
      if(page>0)
      {
         move(17,1);
         addprevpagestr();
      }
      //PAGE DOWN
      if((page+1)*18<len(loottype))
      {
         move(17,53);
         addnextpagestr();
      }

      move(24,1);
      addstr("Enter - 今月は掲載しない");

      int c=getkey();

      if(c>='a'&&c<='r')
      {
         int slot=c-'a'+page*18;

         if(slot>=0&&slot<len(loottypeindex))
         {
            //DELETE THE ITEM
            for(int loc=0;loc<len(location);loc++)
            {
               if(location[loc]->renting==RENTING_NOCONTROL) continue;

               for(int l=0;l<len(location[loc]->loot);l++)
               {
                  if(!location[loc]->loot[l]->is_loot()) continue;

                  if(getloottype(location[loc]->loot[l]->get_itemtypename())==loottypeindex[slot])
                  {
                     location[loc]->loot[l]->decrease_number(1);
                     if(location[loc]->loot[l]->empty())
                     	delete_and_remove(location[loc]->loot,l);
                     return loottypeindex[slot];
                  }
               }
            }
            for(int sq=0;sq<len(squad);sq++)
            {
               for(int l=0;l<len(squad[sq]->loot);l++)
               {
                  if(!squad[sq]->loot[l]->is_loot()) continue;

                  if(getloottype(squad[sq]->loot[l]->get_itemtypename())==loottypeindex[slot])
                  {
                     squad[sq]->loot[l]->decrease_number(1);
                     if(squad[sq]->loot[l]->empty())
                        delete_and_remove(squad[sq]->loot,l);
                     return loottypeindex[slot];
                  }
               }
            }

            //WHOOPS!
            return loottypeindex[slot];
         }
      }

      if(c=='x'||c==ENTER||c==ESC||c==SPACEBAR) return -1;

      //PAGE UP
      if((c==interface_pgup||c==KEY_UP||c==KEY_LEFT)&&page>0) page--;
      //PAGE DOWN
      if((c==interface_pgdn||c==KEY_DOWN||c==KEY_RIGHT)&&(page+1)*18<len(loottype)) page++;

   }

   return -1;
}



/* monthly - guardian - prints liberal guardian special editions */
void printnews(short li,short newspaper)
{
   music.play(MUSIC_NEWSPAPER);
   if(law[LAW_FREESPEECH]==-2)offended_firemen=1;
   clear();
   set_color(COLOR_WHITE,COLOR_BLACK,1);

   if(loottype[li]->get_idname()=="LOOT_CEOPHOTOS") // Tmp -XML
   {
      move(6,1);
      addstr("リベラルガーディアンに有名なCEOが", gamelog);
      move(7,1);
      change_public_opinion(VIEW_LIBERALCRIMESQUAD,10);
      change_public_opinion(VIEW_LIBERALCRIMESQUADPOS,10);
      switch(LCSrandom(10))
      {
         case 0:
            addstr("動物と猥褻な行為を行っている", gamelog);
            change_public_opinion(VIEW_ANIMALRESEARCH,15);
            break;
         case 1:addstr("墓から掘り起こした死体と寝ている", gamelog);break;
         case 2:
            addstr("人殺しに加わっている", gamelog);
            change_public_opinion(VIEW_POLICEBEHAVIOR,15);
            change_public_opinion(VIEW_JUSTICES,10);
            break;
         case 3:addstr("ボンデージを着てキュウリを何本も挿している", gamelog);break;
         case 4:addstr("評判の悪い政治家とディープキスをしている", gamelog);break;
         case 5:
            addstr("CEOの製品を検査するFDAの職員とよろしくしている", gamelog);
            change_public_opinion(VIEW_GENETICS,10);
            change_public_opinion(VIEW_POLLUTION,10);
            break;
         case 6:addstr("自分自身を去勢している", gamelog);break;
         case 7:addstr("白人至上主義者の集会でナチの旗を振っている", gamelog);break;
         case 8:
            addstr("従業員をアイロンで拷問している", gamelog);
            change_public_opinion(VIEW_SWEATSHOPS,10);
            break;
         case 9:addstr("排泄物プレイをしている", gamelog);break;
      }
      addstr("写真の特別記事を掲載した。", gamelog);
      gamelog.newline();
      move(9,1);
      addstr("主要なネットワークと新聞社は、数週間に渡りこの話題を取り上げた。", gamelog);
      gamelog.newline();
      move(10,1);
      addstr("このことには企業も神経を尖らせている。", gamelog);
      gamelog.nextMessage();

      change_public_opinion(VIEW_CEOSALARY,50);
      change_public_opinion(VIEW_CORPORATECULTURE,50);
      offended_corps=1;
   }
   else if(loottype[li]->get_idname()=="LOOT_CEOLOVELETTERS")
   {
      move(6,1);
      addstr("リベラルガーディアンに有名なCEOの", gamelog);
      move(7,1);
      change_public_opinion(VIEW_LIBERALCRIMESQUAD,10);
      change_public_opinion(VIEW_LIBERALCRIMESQUADPOS,10);
      switch(LCSrandom(8))
      {
         case 0:
            addstr("自分の犬宛ての", gamelog);
            change_public_opinion(VIEW_ANIMALRESEARCH,15);
            break;
         case 1:
            addstr("汚職で無罪を言い渡した判事への", gamelog);
            change_public_opinion(VIEW_JUSTICES,15);
            break;
         case 2:
            addstr("不倫相手のゲイの愛人への", gamelog);
            change_public_opinion(VIEW_GAY,15);
            break;
         case 3:addstr("自分自身への情熱的な", gamelog);break;
         case 4:
            addstr("恐らく奴隷状態にある自分の使用人への", gamelog);
            change_public_opinion(VIEW_SWEATSHOPS,10);
            break;
         case 5:
            addstr("CEOの製品を検査するFDAの職員への", gamelog);
            change_public_opinion(VIEW_GENETICS,10);
            change_public_opinion(VIEW_POLLUTION,10);
            break;
         case 6:addstr("よく知られたフェチ男への", gamelog);break;
         case 7:addstr("性的な行為と引き換えに便宜を図ることを約束する", gamelog);break;
      }
      addstr("ラブレターの特別記事を掲載した。", gamelog);
      gamelog.newline();
      move(9,1);
      addstr("主要なネットワークと新聞社は、数週間に渡りこの話題を取り上げた。", gamelog);
      gamelog.newline();
      move(10,1);
      addstr("このことには企業も神経を尖らせている。", gamelog);
      gamelog.nextMessage();

      change_public_opinion(VIEW_CEOSALARY,50);
      change_public_opinion(VIEW_CORPORATECULTURE,50);
      offended_corps=1;
   }
   else if(loottype[li]->get_idname()=="LOOT_CEOTAXPAPERS")
   {
      move(6,1);
      addstr("リベラルガーディアンに", gamelog);
      move(7,1);
      change_public_opinion(VIEW_LIBERALCRIMESQUAD,10);
      change_public_opinion(VIEW_LIBERALCRIMESQUADPOS,10);
      switch(LCSrandom(1))
      {
         default:
            addstr("脱税を繰り返していることを示す", gamelog);
            change_public_opinion(VIEW_TAXES,25);
            break;
      }
      addstr("CEOの納税告知書に関する特別記事を掲載した。", gamelog);
      gamelog.newline();
      move(9,1);
      addstr("主要なネットワークと新聞社は、数週間に渡りこの話題を取り上げた。", gamelog);
      gamelog.newline();
      move(10,1);
      addstr("このことには企業も神経を尖らせている。", gamelog);
      gamelog.nextMessage();

      change_public_opinion(VIEW_CEOSALARY,50);
      change_public_opinion(VIEW_CORPORATECULTURE,50);
      offended_corps=1;
   }
   else if(loottype[li]->get_idname()=="LOOT_CORPFILES")
   {
      move(6,1);
      addstr("リベラルガーディアンに", gamelog);
      move(7,1);

      change_public_opinion(VIEW_LIBERALCRIMESQUAD,newspaper*10);
      change_public_opinion(VIEW_LIBERALCRIMESQUADPOS,newspaper*10);
      switch(LCSrandom(5))
      {
         case 0:
            addstr("研究所で生み出された遺伝子操作モンスターの文書", gamelog);
            change_public_opinion(VIEW_GENETICS,50);
            break;
         case 1:
            addstr("「ホモ作業員」というタイトルのゲイの従業員のリスト", gamelog);
            change_public_opinion(VIEW_GAY,50);
            break;
         case 2:
            addstr("「妊婦を始末しろ。私が始末する。」と書かれたメモ", gamelog);
            change_public_opinion(VIEW_WOMEN,50);
            break;
         case 3:
            addstr("海外の搾取工場について楽しげに書かれた文書", gamelog);
            change_public_opinion(VIEW_SWEATSHOPS,50);
            break;
         case 4:
            addstr("複雑な税金逃れの手法が書かれた文書", gamelog);
            change_public_opinion(VIEW_TAXES,50);
            break;
      }
      addstr("に関する特別記事を掲載した。", gamelog);
      gamelog.newline();
      move(9,1);
      addstr("主要なネットワークと新聞社は、数週間に渡りこの話題を取り上げた。", gamelog);
      gamelog.newline();
      move(10,1);
      addstr("このことには企業も神経を尖らせている。", gamelog);
      gamelog.nextMessage();

      change_public_opinion(VIEW_CEOSALARY,50);
      change_public_opinion(VIEW_CORPORATECULTURE,50);
      offended_corps=1;
   }
   else if(loottype[li]->get_idname()=="LOOT_CCS_BACKERLIST")
   {
      move(5,1);
      addstr("リベラルガーディアンに千ページを超えるCCSに関する文書を掲載した。そこには政府", gamelog);
      gamelog.newline();
      move(6,1);
      addstr("内のコンサバ・クライム・スコードの支持者や支援者の氏名や役職の極めて詳細な情", gamelog);
      gamelog.newline();
      move(7,1);
      addstr("報も含まれている。", gamelog);
      gamelog.newline();
      move(8,1);
      addstr("複数のセクションで、司法管轄外の暗殺部隊の創設に関する広範囲な計画を明らかに", gamelog);
      gamelog.newline();
      move(9,1);
      addstr("した。暗殺部隊は警察の上位に位置し、法を破っていないリベラルさえも捕らえ、そ", gamelog);
      gamelog.newline();
      move(10,1);
      addstr("して敵が存在しないときは市民のエネルギーを押さえ込むために働くだろう。", gamelog);
      gamelog.newline();

      move(12,1);
      addstr("スキャンダルはこの国の保守の中心にまで達した。この発見の影響は数ヶ月間では感", gamelog);
      gamelog.newline();
      move(13,1);
      addstr("じられないかもしれない。", gamelog);
      gamelog.newline();
      move(14,1);
      addstr("だが、1つだけ明らかなのは、この発見に大衆はすぐに反応し、AMラジオやケーブルニ", gamelog);
      gamelog.newline();
      move(15,1);
      addstr("ュースさえもすぐさまCCSを非難し始めたということだ。", gamelog);
      gamelog.newline();

      move(17,1);
      addstr("これはコンサバ・クライム・スコードの終わりの始まりとなるだろう。", gamelog);
      gamelog.nextMessage();

      change_public_opinion(VIEW_INTELLIGENCE,50);
      change_public_opinion(VIEW_CONSERVATIVECRIMESQUAD,100);
      ccsexposure = CCSEXPOSURE_EXPOSED;
   }
   else if(loottype[li]->get_idname()=="LOOT_INTHQDISK"
           || loottype[li]->get_idname()=="LOOT_SECRETDOCUMENTS")
   {
      move(6,1);
      addstr("リベラルガーディアンにCIAや他の情報機関による", gamelog);
      move(7,1);

      change_public_opinion(VIEW_LIBERALCRIMESQUAD,10);
      change_public_opinion(VIEW_LIBERALCRIMESQUADPOS,10);
      switch(LCSrandom(6))
      {
         case 0:addstr("政府転覆計画", gamelog);break;
         case 1:
            addstr("リベラル連邦主義者判事の暗殺計画", gamelog);
            change_public_opinion(VIEW_JUSTICES,50);
            break;
         case 2:addstr("無実の市民の個人情報", gamelog);break;
         case 3:
            addstr("無実の市民による「有害な言論」の記録", gamelog);
            change_public_opinion(VIEW_FREESPEECH,50);
            break;
         case 4:
            addstr("同性愛者の市民の監視記録", gamelog);
            change_public_opinion(VIEW_GAY,50);
            break;
         case 5:
            addstr("中絶賛成派グループの行動記録", gamelog);
            change_public_opinion(VIEW_WOMEN,50);
            break;
              }
      addstr("が記述されたファイルに関する特別記事を掲載した。", gamelog);
      gamelog.newline();
      move(9,1);
      addstr("主要なネットワークと新聞社は、数週間に渡りこの話題を取り上げた。", gamelog);
      gamelog.newline();
      move(10,1);
      addstr("このことには政府関係者も神経を尖らせている。", gamelog);
      gamelog.nextMessage();

      change_public_opinion(VIEW_INTELLIGENCE,50);
      offended_cia=1;
   }
   else if(loottype[li]->get_idname()=="LOOT_POLICERECORDS")
   {
      move(6,1);
      addstr("リベラルガーディアンに警察による", gamelog);
      move(7,1);

      change_public_opinion(VIEW_LIBERALCRIMESQUAD,10);
      change_public_opinion(VIEW_LIBERALCRIMESQUADPOS,10);
      switch(LCSrandom(6))
      {
         case 0:
            addstr("人権侵害", gamelog);
            change_public_opinion(VIEW_TORTURE,15);
            break;
         case 1:
            addstr("取り調べにおける拷問", gamelog);
            change_public_opinion(VIEW_TORTURE,50);
            break;
         case 2:
            addstr("組織的なプライバシーの侵害", gamelog);
            change_public_opinion(VIEW_INTELLIGENCE,15);
            break;
         case 3:
            addstr("自白の強要", gamelog);
            break;
         case 4:
            addstr("広範囲に及ぶ汚職", gamelog);
            break;
         case 5:
            addstr("看守が主催した囚人同士の剣闘士のような戦い", gamelog);
            change_public_opinion(VIEW_DEATHPENALTY,50);
            change_public_opinion(VIEW_PRISONS,20);
            break;
      }
      addstr("を示す文書に関する特別記事を掲載した。", gamelog);
      move(9,1);
      gamelog.newline();
      addstr("主要なネットワークと新聞社は、数週間に渡りこの話題を取り上げた。", gamelog);
      gamelog.nextMessage();

      change_public_opinion(VIEW_POLICEBEHAVIOR,50);
   }
   else if(loottype[li]->get_idname()=="LOOT_JUDGEFILES")
   {
      move(6,1);
      addstr("リベラルガーディアンに、保守派判事の", gamelog);
      move(7,1);

      change_public_opinion(VIEW_LIBERALCRIMESQUAD,10);
      change_public_opinion(VIEW_LIBERALCRIMESQUADPOS,10);
      switch(LCSrandom(2))
      {
         case 0:addstr("殺人事件を無罪にする賄賂の", gamelog);break;
         case 1:addstr("地位と引き換えに保守的な判決を約束した", gamelog);break;
      }
      gamelog.newline();
      addstr("証拠を示す特別記事を掲載した。", gamelog);
      move(8,1);
      addstr("主要なネットワークと新聞社は、数週間に渡りこの話題を取り上げた。", gamelog);
      gamelog.nextMessage();

      change_public_opinion(VIEW_JUSTICES,50);
   }
   else if(loottype[li]->get_idname()=="LOOT_RESEARCHFILES")
   {
      move(6,1);
      addstr("リベラルガーディアンに", gamelog);
      move(7,1);

      change_public_opinion(VIEW_LIBERALCRIMESQUAD,10);
      change_public_opinion(VIEW_LIBERALCRIMESQUADPOS,10);
      switch(LCSrandom(4))
      {
         case 0:addstr("恐るべき動物虐待が行われたことを示す", gamelog);
            change_public_opinion(VIEW_ANIMALRESEARCH,50);break;
         case 1:addstr("拷問が猫に与える効果の", gamelog);
            change_public_opinion(VIEW_ANIMALRESEARCH,50);break;
         case 2:addstr("事故で生み出した遺伝子操作モンスターの隠蔽を示す", gamelog);
            change_public_opinion(VIEW_GENETICS,50);break;
         case 3:addstr("遺伝子研究の被験者が死亡した", gamelog);
            change_public_opinion(VIEW_GENETICS,50);break;
      }
      addstr("論文に関する特別記事を掲載した。", gamelog);
      gamelog.newline();
      move(9,1);
      addstr("主要なネットワークと新聞社は、数週間に渡りこの話題を取り上げた。", gamelog);
      gamelog.nextMessage();
   }
   else if(loottype[li]->get_idname()=="LOOT_PRISONFILES")
   {
      move(6,1);
      addstr("リベラルガーディアンに刑務所内での", gamelog);
      move(7,1);

      change_public_opinion(VIEW_LIBERALCRIMESQUAD,10);
      change_public_opinion(VIEW_LIBERALCRIMESQUADPOS,10);
      change_public_opinion(VIEW_PRISONS,50);
      switch(LCSrandom(4))
      {
         case 0:addstr("看守による人権侵害", gamelog);break;
         case 1:
            addstr("囚人への拷問", gamelog);
            change_public_opinion(VIEW_TORTURE,50);
            break;
         case 2:addstr("職員の間の広範囲に及ぶ汚職", gamelog);break;
         case 3:
            addstr("看守が主催した囚人同士の剣闘士のような戦い", gamelog);
      }
      addstr("を示す文書に関する特別記事を掲載した。", gamelog);
      gamelog.newline();
      move(9,1);
      addstr("主要なネットワークと新聞社は、数週間に渡りこの話題を取り上げた。", gamelog);
      gamelog.nextMessage();

      change_public_opinion(VIEW_DEATHPENALTY,50);
   }
   else if(loottype[li]->get_idname()=="LOOT_CABLENEWSFILES")
   {
      move(6,1);
      addstr("リベラルガーディアンにケーブルテレビ局の", gamelog);
      move(7,1);

      change_public_opinion(VIEW_LIBERALCRIMESQUAD,10);
      change_public_opinion(VIEW_LIBERALCRIMESQUADPOS,10);
      switch(LCSrandom(4))
      {
         case 0:addstr("自身のニュースを「保守思想の先陣」と呼ぶ", gamelog);break;
         case 1:addstr("リベラル政治家の否定的な放送を命令する", gamelog);break;
         case 2:addstr("リベラル派の人物の嘘のスキャンダルをでっち上げる", gamelog);break;
         case 3:addstr("女優に「よりセクシーになるか、それとも辞めるか」を迫る", gamelog);
            break;
      }
      addstr("メモの特別記事を掲載した。", gamelog);
      gamelog.newline();
      move(9,1);
      addstr("主要なネットワークと新聞社は、数週間に渡りこの話題を取り上げた。", gamelog);
      gamelog.newline();
      move(10,1);
      addstr("このことには保守派も神経を尖らせている。", gamelog);
      gamelog.nextMessage();

      change_public_opinion(VIEW_CABLENEWS,50);
      offended_cablenews=1;
   }
   else if(loottype[li]->get_idname()=="LOOT_AMRADIOFILES")
   {
      move(6,1);
      addstr("リベラルガーディアンにAMラジオ局の", gamelog);
      move(7,1);

      change_public_opinion(VIEW_LIBERALCRIMESQUAD,10);
      change_public_opinion(VIEW_LIBERALCRIMESQUADPOS,10);
      switch(LCSrandom(3))
      {
         case 0:addstr("視聴者を「何を考えるか命令される羊」と呼ぶ", gamelog);break;
         case 1:addstr("「嘘でもよい。本当のことなど必要ない」と書かれた", gamelog);break;
         case 2:addstr("リベラル派の人物の嘘のスキャンダルをでっち上げる", gamelog);break;
      }
      addstr("原稿の特別記事を掲載した。", gamelog);
      gamelog.newline();
      move(9,1);
      addstr("主要なネットワークと新聞社は、数週間に渡りこの話題を取り上げた。", gamelog);
      gamelog.newline();
      move(10,1);
      addstr("このことには保守派も神経を尖らせている。", gamelog);
      gamelog.nextMessage();

      change_public_opinion(VIEW_AMRADIO,50);
      offended_cablenews=1;
   }

   getkey();
}


/* monthly - LCS finances report */
void fundreport(char &clearformess)
{
   if(disbanding) return;
   music.play(MUSIC_FINANCES);

   clearformess=true;

   int page=0;
   bool showledger=false;
   std::string num;
   static const char dotdotdot[]=". . . . . . . . . . . . . . . . . . . . . . . . . . . . . . ";

   int expenselines = 0;
   for(int i=0;i<EXPENSETYPENUM;i++)
      if (ledger.expense[i])
         expenselines++;

   while(true)
   {
      clear();

      int y=2,totalmoney=0,dailymoney=0,numpages=1;

      set_color(COLOR_WHITE,COLOR_BLACK,1);
      mvaddstr(0,0,"リベラル・クライム・スコード: 収支報告");

      for(int i=0;i<INCOMETYPENUM;i++)
      {
         if(ledger.income[i])
         {
            showledger=true;
            if(page==numpages-1)
            {
               set_color(COLOR_WHITE,COLOR_BLACK,0);
               mvaddstr(y,0,dotdotdot);
               set_color(COLOR_GREEN,COLOR_BLACK,0);
               num="+$"+tostring(ledger.income[i]);
               mvaddstr(y,60-len(num),num);
               if(ledger.dailyIncome[i])
                  num=" (+$"+tostring(ledger.dailyIncome[i])+")";
               else
               {
                  set_color(COLOR_WHITE,COLOR_BLACK,0);
                  num=" ($0)";
               }
               mvaddstr(y,73-len(num),num);
               set_color(COLOR_WHITE,COLOR_BLACK,0);
               switch(i)
               {
               case INCOME_BROWNIES: mvaddstr(y,0,"ケーキの販売"); break;
               case INCOME_CARS: mvaddstr(y,0,"自動車の売却"); break;
               case INCOME_CCFRAUD: mvaddstr(y,0,"カード番号取得"); break;
               case INCOME_DONATIONS: mvaddstr(y,0,"寄付"); break;
               case INCOME_SKETCHES: mvaddstr(y,0,"絵の販売"); break;
               case INCOME_EMBEZZLEMENT: mvaddstr(y,0,"横領"); break;
               case INCOME_EXTORTION: mvaddstr(y,0,"恐喝"); break;
               case INCOME_HUSTLING: mvaddstr(y,0,"窃盗"); break;
               case INCOME_PAWN: mvaddstr(y,0,"備品の売却"); break;
               case INCOME_PROSTITUTION: mvaddstr(y,0,"売春"); break;
               case INCOME_BUSKING: mvaddstr(y,0,"ストリートミュージック"); break;
               case INCOME_THIEVERY: mvaddstr(y,0,"盗品"); break;
               case INCOME_TSHIRTS: mvaddstr(y,0,"Tシャツの販売"); break;
               default: mvaddstr(y,0,"その他の収入"); break;
               }
            }
            totalmoney+=ledger.income[i];
            dailymoney+=ledger.dailyIncome[i];

            if(++y>=23) y=2,numpages++;
         }
      }

      // If expenses are too long to fit on this page, start them on the next page so it isn't broken in half unnecessarily
      if(y+expenselines>=23 && y>2) y=2,numpages++;

      for(int i=0;i<EXPENSETYPENUM;i++)
      {
         if(ledger.expense[i])
         {
            showledger=true;
            if(page==numpages-1)
            {
               set_color(COLOR_WHITE,COLOR_BLACK,0);
               mvaddstr(y,0,dotdotdot);
               set_color(COLOR_RED,COLOR_BLACK,0);
               num="-$"+tostring(ledger.expense[i]);
               mvaddstr(y,60-len(num),num);
               if(ledger.dailyExpense[i])
                  num=" (-$"+tostring(ledger.dailyExpense[i])+")";
               else
               {
                  set_color(COLOR_WHITE,COLOR_BLACK,0);
                  num=" ($0)";
               }
               mvaddstr(y,73-len(num),num);
               set_color(COLOR_WHITE,COLOR_BLACK,0);
               switch(i)
               {
               case EXPENSE_TROUBLEMAKING: mvaddstr(y,0,"活動"); break;
               case EXPENSE_CONFISCATED: mvaddstr(y,0,"押収"); break;
               case EXPENSE_DATING: mvaddstr(y,0,"デート"); break;
               case EXPENSE_SKETCHES: mvaddstr(y,0,"絵の販売"); break;
               case EXPENSE_FOOD: mvaddstr(y,0,"食料品"); break;
               case EXPENSE_HOSTAGE: mvaddstr(y,0,"捕虜の尋問"); break;
               case EXPENSE_LEGAL: mvaddstr(y,0,"訴訟費用"); break;
               case EXPENSE_MANUFACTURE: mvaddstr(y,0,"内製"); break;
               case EXPENSE_CARS: mvaddstr(y,0,"自動車の購入"); break;
               case EXPENSE_SHOPPING: mvaddstr(y,0,"物品の購入"); break;
               case EXPENSE_RECRUITMENT: mvaddstr(y,0,"スカウト"); break;
               case EXPENSE_RENT: mvaddstr(y,0,"家賃"); break;
               case EXPENSE_COMPOUND: mvaddstr(y,0,"アジトの改修"); break;
               case EXPENSE_TRAINING: mvaddstr(y,0,"訓練"); break;
               case EXPENSE_TRAVEL: mvaddstr(y,0,"旅行"); break;
               case EXPENSE_TSHIRTS: mvaddstr(y,0,"Tシャツの販売"); break;
               default: mvaddstr(y,0,"その他"); break;
               }
            }
            totalmoney-=ledger.expense[i];
            dailymoney-=ledger.dailyExpense[i];

            if(++y>=23) y=2,numpages++;
         }
      }

      if(showledger)
      {
         if(page==numpages-1) makedelimiter(y);

         if(++y>=23) y=2,numpages++;

         if(page==numpages-1)
         {
            set_color(COLOR_WHITE,COLOR_BLACK,1);
            mvaddstr(y,0,"今月の収支 (本日):");
            if(totalmoney>0) { set_color(COLOR_GREEN,COLOR_BLACK,1); num="+"; }
            else if(totalmoney<0) { set_color(COLOR_RED,COLOR_BLACK,1); num="-"; }
            else { set_color(COLOR_WHITE,COLOR_BLACK,1); num=""; }
            num+="$"+tostring(abs(totalmoney));
            mvaddstr(y,60-len(num),num);
            if(dailymoney>0)
            {
               set_color(COLOR_GREEN,COLOR_BLACK,1);
               num=" (+$"+tostring(abs(dailymoney))+")";
            }
            else if(dailymoney<0)
            {
               set_color(COLOR_RED,COLOR_BLACK,1);
               num=" (-$"+tostring(abs(dailymoney))+")";
            }
            else
            {
               set_color(COLOR_WHITE,COLOR_BLACK,1);
               num=" ($0)";
            }
            mvaddstr(y,73-len(num),num);
         }

         if(++y>=23) y=2,numpages++;
      }

      if (y>2) y++; // Blank line between income/expenses and assets if not starting a new page
      if (y+7>=23) y=2, numpages++; //Start a new page if the liquid assets won't fit on the rest of the current page.
      // tally up liquid assets
      long weaponValue=0,armorValue=0,clipValue=0,lootValue=0;
      for(int j=0;j<len(location);j++)
         for(int i=0;i<len(location[j]->loot);i++)
         {
            Item* item=location[j]->loot[i];
            if(item->is_weapon()) weaponValue+=item->get_fencevalue()*item->get_number();
            if(item->is_armor()) armorValue+=item->get_fencevalue()*item->get_number();
            if(item->is_clip()) clipValue+=item->get_fencevalue()*item->get_number();
            if(item->is_loot()) lootValue+=item->get_fencevalue()*item->get_number();
         }

      if(page==numpages-1)
      {
         set_color(COLOR_WHITE,COLOR_BLACK,0);
         mvaddstr(y,0,dotdotdot);
         mvaddstr(y,0,"現金");
         set_color(ledger.get_funds()?COLOR_GREEN:COLOR_WHITE,COLOR_BLACK,0);
         num="$"+tostring(ledger.get_funds());
         mvaddstr(y,60-len(num),num);
      }

      if(++y>=23) y=2,numpages++;

      if(page==numpages-1)
      {
         set_color(COLOR_WHITE,COLOR_BLACK,0);
         mvaddstr(y,0,dotdotdot);
         mvaddstr(y,0,"道具と武器");
         set_color(weaponValue?COLOR_GREEN:COLOR_WHITE,COLOR_BLACK,0);
         num="$"+tostring(weaponValue);
         mvaddstr(y,60-len(num),num);
      }

      if(++y>=23) y=2,numpages++;

      if(page==numpages-1)
      {
         set_color(COLOR_WHITE,COLOR_BLACK,0);
         mvaddstr(y,0,dotdotdot);
         mvaddstr(y,0,"衣服と鎧");
         set_color(armorValue?COLOR_GREEN:COLOR_WHITE,COLOR_BLACK,0);
         num="$"+tostring(armorValue);
         mvaddstr(y,60-len(num),num);
      }

      if(++y>=23) y=2,numpages++;

      if(page==numpages-1)
      {
         set_color(COLOR_WHITE,COLOR_BLACK,0);
         mvaddstr(y,0,dotdotdot);
         mvaddstr(y,0,"弾薬");
         set_color(clipValue?COLOR_GREEN:COLOR_WHITE,COLOR_BLACK,0);
         num="$"+tostring(clipValue);
         mvaddstr(y,60-len(num),num);
      }

      if(++y>=23) y=2,numpages++;

      if(page==numpages-1)
      {
         set_color(COLOR_WHITE,COLOR_BLACK,0);
         mvaddstr(y,0,dotdotdot);
         mvaddstr(y,0,"その他の略奪品");
         set_color(lootValue?COLOR_GREEN:COLOR_WHITE,COLOR_BLACK,0);
         num="$"+tostring(lootValue);
         mvaddstr(y,60-len(num),num);
      }

      if(++y>=23) y=2,numpages++;

      if(page==numpages-1) makedelimiter(y);

      if(++y>=23) y=2,numpages++;

      if(page==numpages-1)
      {
         set_color(COLOR_WHITE,COLOR_BLACK,1);
         mvaddstr(y,0,"全資産:");
         long netWorth=ledger.get_funds()+weaponValue+armorValue+clipValue+lootValue;
         set_color(netWorth?COLOR_GREEN:COLOR_WHITE,COLOR_BLACK,1);
         num="$"+tostring(netWorth);
         mvaddstr(y,60-len(num),num);
      }

      set_color(COLOR_WHITE,COLOR_BLACK,0);
      if(numpages>1)
      {
         mvaddstr(24,0,"報告書をよく読んだならばEnterキーを押すこと。");
         addpagestr();

         while(true)
         {
            int c=getkey();

            if(c=='x'||c==ENTER||c==ESC||c==SPACEBAR)
            {
               music.play(MUSIC_PREVIOUS);
               return;
            }

            //PAGE UP
            if(c==interface_pgup||c==KEY_UP||c==KEY_LEFT) { page--; if(page<0) page=numpages-1; break; }
            //PAGE DOWN
            if(c==interface_pgdn||c==KEY_DOWN||c==KEY_RIGHT) { page++; if(page>=numpages) page=0; break; }
         }
      }
      else
      {
         mvaddstr(24,0,"報告書をよく読んだならば何かキーを押すこと。 ");

         getkey();

         music.play(MUSIC_PREVIOUS);
         return;
      }
   }
}
