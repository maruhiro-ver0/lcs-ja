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

void mode_title()
{
   //title screen
   clear();

   char str[100];

   set_color(COLOR_GREEN,COLOR_BLACK,1);
   strcpy(str,"Liberal Crime Squad");
   move(2,39-((len(str)-1)>>1));
   addstr(str);

   set_color(COLOR_WHITE,COLOR_BLACK,1);
   strcpy(str,"Inspired by the 1983 version of Oubliette");
   move(4,39-((len(str)-1)>>1));
   addstr(str);

   if(loaded)
   {
      move(6,39-((len(slogan)-1)>>1));
      addstr(slogan);

      move(7,10);

      addstr("教化したリベラル: ");
      addstr(stat_recruits);

      move(8,10);
      addstr("殉死したリベラル: ");
      addstr(stat_dead);

      move(9,10);
      addstr("殺害した保守: ");
      addstr(stat_kills);

      move(7,47);
      addstr("収入: ");
      addstr(ledger.total_income);

      move(8,47);
      addstr("支出: ");
      addstr(ledger.total_expense);

      move(9,47);
      addstr("捕らえた保守: ");
      addstr(stat_kidnappings);
   }
   else switch(LCSrandom(32))
   {
   case 0:
      strcpy(str,"『不公正な法が存在する。我々はそれに従うべきか、それとも改めるべきか。");
      move(6,39-((len(str)-1)>>1));
      addstr(str);
      strcpy(str,"そして、改めるまでは従うべきか、それともすぐさま破るべきか。");
      move(7,39-((len(str)-1)>>1));
      addstr(str);
      strcpy(str,"…そう、法を破れ。』");
      move(8,39-((len(str)-1)>>1));
      addstr(str);
      strcpy(str,"──ヘンリー・デイビッド・ソロー");
      move(9,39-((len(str)-1)>>1));
      addstr(str);
      break;
   case 1:
      strcpy(str,"『人には公正な法に従う法的なだけでなく道徳的な義務がある。");
      move(6,39-((len(str)-1)>>1));
      addstr(str);
      strcpy(str,"そして逆に、人には不公正な法に従わない道徳的な義務がある。』");
      move(7,39-((len(str)-1)>>1));
      addstr(str);
      strcpy(str,"──マーチン・ルーサー・キング Jr.");
      move(8,39-((len(str)-1)>>1));
      addstr(str);
      break;
   case 2:
      strcpy(str,"『市民の不服従は我々の問題ではない。我々の問題は市民の服従である…");
      move(6,39-((len(str)-1)>>1));
      addstr(str);
      strcpy(str,"法を超越した抵抗は民主主義からの脱却ではない。");
      move(7,39-((len(str)-1)>>1));
      addstr(str);
      strcpy(str,"それは民主主義にとって絶対的に不可欠なものである。』");
      move(8,39-((len(str)-1)>>1));
      addstr(str);
      strcpy(str,"──ハワード・ジン");
      move(9,39-((len(str)-1)>>1));
      addstr(str);
      break;
   case 3:
      strcpy(str,"『我々は理解しなければならない。マルクスやアダム・スミスのように。");
      move(6,39-((len(str)-1)>>1));
      addstr(str);
      strcpy(str,"企業は公共の利益には関心がない…");
      move(7,39-((len(str)-1)>>1));
      addstr(str);
      strcpy(str,"もし我々が抵抗しなければ、もし我々が行動しなければ、それは魂の死だ。』");
      move(8,39-((len(str)-1)>>1));
      addstr(str);
      strcpy(str,"──クリス・ヘッジズ");
      move(9,39-((len(str)-1)>>1));
      addstr(str);
      break;
   case 4:
      strcpy(str,"『政府が無法化し腐敗したとき、市民の不服従は神聖な責務となる…");
      move(6,39-((len(str)-1)>>1));
      addstr(str);
      strcpy(str,"悪に協力しないことは、善に協力することと同様の責務である。』");
      move(7,39-((len(str)-1)>>1));
      addstr(str);
      strcpy(str,"──マハトマ・ガンディー");
      move(8,39-((len(str)-1)>>1));
      addstr(str);
      break;
   case 5:
      strcpy(str,"『市民の不服従の主たる目的は、他者を奮起させ、参加と行動を促すことにある。");
      move(6,39-((len(str)-1)>>1));
      addstr(str);
      strcpy(str,"もっとも、それは良い方策であることも、そうでないこともある。』");
      move(7,39-((len(str)-1)>>1));
      addstr(str);
      strcpy(str,"──ノーム・チョムスキー");
      move(8,39-((len(str)-1)>>1));
      addstr(str);
      break;
   case 6:
      strcpy(str,"『我々の敵は革新的で機智に富んでいる。そして我々もそうだ。");
      move(6,39-((len(str)-1)>>1));
      addstr(str);
      strcpy(str,"我々の敵は国と国民を害する新しい方法を常に考えている。そして我々もそうだ。』");
      move(7,39-((len(str)-1)>>1));
      addstr(str);
      strcpy(str,"──ジョージ・W・ブッシュ");
      move(8,39-((len(str)-1)>>1));
      addstr(str);
      break;
   case 7:
      strcpy(str,"『一人を殺せば、それは惨劇だ。");
      move(6,39-((len(str)-1)>>1));
      addstr(str);
      strcpy(str,"一千万人を殺せば、それは統計上の数字だ。』");
      move(7,39-((len(str)-1)>>1));
      addstr(str);
      strcpy(str,"──ヨシフ・スターリン");
      move(8,39-((len(str)-1)>>1));
      addstr(str);
      break;
   case 8:
      strcpy(str,"『テネシーにはこんな諺がある…テキサスにはある");
      move(6,39-((len(str)-1)>>1));
      addstr(str);
      strcpy(str,"たぶんテネシーにも…それは、一度だけ私を騙した");
      move(7,39-((len(str)-1)>>1));
      addstr(str);
      strcpy(str,"恥を…恥を知れ。私を騙した…君は二度目は騙されない。』");
      move(8,39-((len(str)-1)>>1));
      addstr(str);
      strcpy(str,"──ジョージ・W・ブッシュ");
      move(9,39-((len(str)-1)>>1));
      addstr(str);
      break;
   case 9:
      strcpy(str,"『探し出され、書かれ、説明されたこの壮大なストーリーは");
      move(6,39-((len(str)-1)>>1));
      addstr(str);
      strcpy(str,"私の夫が大統領に就任して以来ずっと企てられている");
      move(7,39-((len(str)-1)>>1));
      addstr(str);
      strcpy(str,"広大な右翼勢力の陰謀です。』");
      move(8,39-((len(str)-1)>>1));
      addstr(str);
      strcpy(str,"──ヒラリー・クリントン");
      move(9,39-((len(str)-1)>>1));
      addstr(str);
      break;
   case 10:
      strcpy(str,"『しかし、私は馬の前に荷台を置くような");
      move(6,39-((len(str)-1)>>1));
      addstr(str);
      strcpy(str,"本末転倒なことはしたくない。");
      move(7,39-((len(str)-1)>>1));
      addstr(str);
      strcpy(str,"我々にはまだ戦略がないのだ。』");
      move(8,39-((len(str)-1)>>1));
      addstr(str);
      strcpy(str,"──バラク・オバマ");
      move(9,39-((len(str)-1)>>1));
      addstr(str);
      break;
   case 11:
      strcpy(str,"『平均的な人がどれほど愚かか知っているだろう?");
      move(6,39-((len(str)-1)>>1));
      addstr(str);
      strcpy(str,"さらに、定義によると、半分の人々は");
      move(7,39-((len(str)-1)>>1));
      addstr(str);
      strcpy(str,"それよりもさらに愚かなのだ。』");
      move(8,39-((len(str)-1)>>1));
      addstr(str);
      strcpy(str,"──J.R. \"ボブ\" ドブス");
      move(9,39-((len(str)-1)>>1));
      addstr(str);
      break;
   case 12:
      strcpy(str,"『我々のさらなる自由と民主主義は");
      move(6,39-((len(str)-1)>>1));
      addstr(str);
      strcpy(str,"後戻りできないと私は信じている──");
      move(7,39-((len(str)-1)>>1));
      addstr(str);
      strcpy(str,"だが変えることはできる。』");
      move(8,39-((len(str)-1)>>1));
      addstr(str);
      strcpy(str,"──ダン・クエール");
      move(9,39-((len(str)-1)>>1));
      addstr(str);
      break;
   case 13:
      strcpy(str,"『私たちは彼らの国を侵略し、リーダーを殺害し、国民をキリスト教に改宗させ");
      move(6,39-((len(str)-1)>>1));
      addstr(str);
      strcpy(str,"なければならない。ヒトラーとその幹部のみ探し出し罰したのは不十分だった。");
      move(7,39-((len(str)-1)>>1));
      addstr(str);
      strcpy(str,"かつて私たちはドイツを絨毯爆撃し、市民を殺戮したはずだ。』");
      move(8,39-((len(str)-1)>>1));
      addstr(str);
      strcpy(str,"──アン・コールター");
      move(9,39-((len(str)-1)>>1));
      addstr(str);
      break;
   case 14:
      strcpy(str,"『反革命主義者を無慈悲に一掃せよ。");
      move(6,39-((len(str)-1)>>1));
      addstr(str);
      strcpy(str,"強制収容所に疑わしい人物を収容せよ…");
      move(7,39-((len(str)-1)>>1));
      addstr(str);
      strcpy(str,"怠け者は撃ち殺せ。過去の働きは無関係だ。』");
      move(8,39-((len(str)-1)>>1));
      addstr(str);
      strcpy(str,"──レフ・トロツキー");
      move(9,39-((len(str)-1)>>1));
      addstr(str);
      break;
   case 15:
      strcpy(str,"『フェーゲラインに会わせろ!");
      move(6,39-((len(str)-1)>>1));
      addstr(str);
      strcpy(str,"もし無断で離れたのならば、それは敵前逃亡だ! 反逆罪!");
      move(7,39-((len(str)-1)>>1));
      addstr(str);
      strcpy(str,"フェーゲラインを連れて来い! フェーゲライン! フェーゲライン! 』");
      move(8,39-((len(str)-1)>>1));
      addstr(str);
      strcpy(str,"──アドルフ・ヒトラー");
      move(9,39-((len(str)-1)>>1));
      addstr(str);
      break;
   case 16:
      strcpy(str,"『親愛なるアメリカ国民の皆様。本日、これを報告できることを喜ばしく思います。");
      move(6,39-((len(str)-1)>>1));
      addstr(str);
      strcpy(str,"私はロシアを永遠に非合法化する法案に署名しました。");
      move(7,39-((len(str)-1)>>1));
      addstr(str);
      strcpy(str,"我々は5分後に空爆を開始します。』");
      move(8,39-((len(str)-1)>>1));
      addstr(str);
      strcpy(str,"──ロナルド・レーガン");
      move(9,39-((len(str)-1)>>1));
      addstr(str);
      break;
   case 17:
      strcpy(str,"『小さな町に行くと…25年間続いた仕事はなくなり、その代わりもない…");
      move(6,39-((len(str)-1)>>1));
      addstr(str);
      strcpy(str,"人々は苦しみ、銃や宗教にすがったとしても、私は驚かない。』");
      move(7,39-((len(str)-1)>>1));
      addstr(str);
      strcpy(str,"──バラク・オバマ");
      move(8,39-((len(str)-1)>>1));
      addstr(str);
      break;
   case 18:
      strcpy(str,"『平和的な革命など存在しない。");
      move(6,39-((len(str)-1)>>1));
      addstr(str);
      strcpy(str,"「左の頬をも向ける」革命など存在しない。");
      move(7,39-((len(str)-1)>>1));
      addstr(str);
      strcpy(str,"非暴力革命とは、そのようなものではないのだ。』");
      move(8,39-((len(str)-1)>>1));
      addstr(str);
      strcpy(str,"──マルコム X");
      move(9,39-((len(str)-1)>>1));
      addstr(str);
      break;
   case 19:
      strcpy(str,"『政治とは流血のない戦争であり");
      move(6,39-((len(str)-1)>>1));
      addstr(str);
      strcpy(str,"戦争とは流血の政治である。』");
      move(7,39-((len(str)-1)>>1));
      addstr(str);
      strcpy(str,"──毛沢東");
      move(8,39-((len(str)-1)>>1));
      addstr(str);
      break;
   case 20:
      strcpy(str,"『私が地上に平和をもたらすために来たと考えてはならない。");
      move(6,39-((len(str)-1)>>1));
      addstr(str);
      strcpy(str,"私は平和ではなく剣をもたらすために来たのだ。");
      move(7,39-((len(str)-1)>>1));
      addstr(str);
      strcpy(str,"私は人を父に、娘を母に、義理の娘を姑に向かわせるために来たのだ…』");
      move(8,39-((len(str)-1)>>1));
      addstr(str);
      strcpy(str,"──イエス・キリスト");
      move(9,39-((len(str)-1)>>1));
      addstr(str);
      break;
   case 21:
      strcpy(str,"\"What signify a few lives lost in a century or two?  The");
      move(6,39-((len(str)-1)>>1));
      addstr(str);
      strcpy(str,"tree of liberty must be refreshed from time to time with");
      move(7,39-((len(str)-1)>>1));
      addstr(str);
      strcpy(str,"the blood of patriots and tyrants.  It is its natural manure.\"");
      move(8,39-((len(str)-1)>>1));
      addstr(str);
      strcpy(str,"──Thomas Jefferson");
      move(9,39-((len(str)-1)>>1));
      addstr(str);
      break;
   case 22:
      strcpy(str,"\"Is it better to be loved or feared?  One might want to be");
      move(6,39-((len(str)-1)>>1));
      addstr(str);
      strcpy(str,"both, but because it is hard to unite them in one person, it");
      move(7,39-((len(str)-1)>>1));
      addstr(str);
      strcpy(str,"is far safer to be feared than loved, if you cannot be both.\"");
      move(8,39-((len(str)-1)>>1));
      addstr(str);
      strcpy(str,"──Niccolo Machiavelli");
      move(9,39-((len(str)-1)>>1));
      addstr(str);
      break;
   case 23:
      strcpy(str,"\"People that are really very weird");
      move(6,39-((len(str)-1)>>1));
      addstr(str);
      strcpy(str,"can get into sensitive positions and");
      move(7,39-((len(str)-1)>>1));
      addstr(str);
      strcpy(str,"have a tremendous impact on history.\"");
      move(8,39-((len(str)-1)>>1));
      addstr(str);
      strcpy(str,"──Dan Quayle");
      move(9,39-((len(str)-1)>>1));
      addstr(str);
      break;
   case 24:
      strcpy(str,"\"The supreme art of war is to subdue the enemy without");
      move(6,39-((len(str)-1)>>1));
      addstr(str);
      strcpy(str,"fighting... If you know the enemy and know yourself");
      move(7,39-((len(str)-1)>>1));
      addstr(str);
      strcpy(str,"you need not fear the results of a hundred battles.\"");
      move(8,39-((len(str)-1)>>1));
      addstr(str);
      strcpy(str,"──Sun Tzu");
      move(9,39-((len(str)-1)>>1));
      addstr(str);
      break;
   case 25:
      strcpy(str,"\"Only two things are infinite, the");
      move(6,39-((len(str)-1)>>1));
      addstr(str);
      strcpy(str,"universe and human stupidity, and");
      move(7,39-((len(str)-1)>>1));
      addstr(str);
      strcpy(str,"I'm not sure about the former.\"");
      move(8,39-((len(str)-1)>>1));
      addstr(str);
      strcpy(str,"──Albert Einstein");
      move(9,39-((len(str)-1)>>1));
      addstr(str);
      break;
   case 26:
      strcpy(str,"\"As Putin rears his head and comes into the airspace of");
      move(6,39-((len(str)-1)>>1));
      addstr(str);
      strcpy(str,"the United States of America, where ──where do they");
      move(7,39-((len(str)-1)>>1));
      addstr(str);
      strcpy(str,"go?  It's Alaska.  It's just right over the border.\"");
      move(8,39-((len(str)-1)>>1));
      addstr(str);
      strcpy(str,"──Sarah Palin");
      move(9,39-((len(str)-1)>>1));
      addstr(str);
      break;
   case 27:
      strcpy(str,"\"The production of too many useful things results in too many useless people.");
      move(6,39-((len(str)-1)>>1));
      addstr(str);
      strcpy(str,"The only antidote to mental suffering is physical pain.");
      move(7,39-((len(str)-1)>>1));
      addstr(str);
      strcpy(str,"If anything is certain, it is that I myself am not a Marxist.\"");
      move(8,39-((len(str)-1)>>1));
      addstr(str);
      strcpy(str,"──Karl Marx");
      move(9,39-((len(str)-1)>>1));
      addstr(str);
      break;
   case 28:
      strcpy(str,"\"If ignorant of the almighty Time Cube Creation Truth, you");
      move(6,39-((len(str)-1)>>1));
      addstr(str);
      strcpy(str,"deserve to be killed.  Killing you is not immoral ──but");
      move(7,39-((len(str)-1)>>1));
      addstr(str);
      strcpy(str,"justified to save life on Earth for future generations.\"");
      move(8,39-((len(str)-1)>>1));
      addstr(str);
      strcpy(str,"──Gene Ray");
      move(9,39-((len(str)-1)>>1));
      addstr(str);
      break;
   case 29:
      strcpy(str,"\"These hangman rope sneak deadly gangsters, judges & police, trick, trap, rob,");
      move(6,39-((len(str)-1)>>1));
      addstr(str);
      strcpy(str,"wreck, butcher, and murder the people to keep them terrorized in gangster");
      move(7,39-((len(str)-1)>>1));
      addstr(str);
      strcpy(str,"Frankenstein earphone radio slavery for the Communist gangster government.\"");
      move(8,39-((len(str)-1)>>1));
      addstr(str);
      strcpy(str,"──Francis E. Dec");
      move(9,39-((len(str)-1)>>1));
      addstr(str);
      break;
   case 30:
      strcpy(str,"\"If a political party tried to abolish Social Security, unemployment insurance,");
      move(6,39-((len(str)-1)>>1));
      addstr(str);
      strcpy(str,"labor laws, or farm programs, you'd not hear of them again.  A tiny splinter");
      move(7,39-((len(str)-1)>>1));
      addstr(str);
      strcpy(str,"group thinks they can do it.  Their number is negligible and they are stupid.\"");
      move(8,39-((len(str)-1)>>1));
      addstr(str);
      strcpy(str,"──Dwight D. Eisenhower");
      move(9,39-((len(str)-1)>>1));
      addstr(str);
      break;
   case 31:
      strcpy(str,"\"If we see that Germany is winning we ought to help");
      move(6,39-((len(str)-1)>>1));
      addstr(str);
      strcpy(str,"Russia and if Russia is winning we ought to help Germany,");
      move(7,39-((len(str)-1)>>1));
      addstr(str);
      strcpy(str,"and that way let them kill as many as possible.\"");
      move(8,39-((len(str)-1)>>1));
      addstr(str);
      strcpy(str,"──Harry S. Truman");
      move(9,39-((len(str)-1)>>1));
      addstr(str);
      break;
   }

   strcpy(str,"v3.9 Copyright (C) 2002-4, Tarn Adams");
   move(11,39-((len(str)-1)>>1));
   addstr(str);
   strcpy(str,"A Bay 12 Games Production");
   move(12,39-((len(str)-1)>>1));
   addstr(str);
   strcpy(str,"http://bay12games.com/lcs/");
   move(13,39-((len(str)-1)>>1));
   addstr(str);
   strcpy(str,"v" PACKAGE_VERSION " Maintained by the Open Source Community");
   move(15,39-((len(str)-1)>>1));
   addstr(str);
   strcpy(str,"http://sourceforge.net/projects/lcsgame/");
   move(16,39-((len(str)-1)>>1));
   addstr(str);
   strcpy(str,"http://www.bay12games.com/forum/index.php?board=3.0");
   move(17,39-((len(str)-1)>>1));
   addstr(str);
   strcpy(str,"http://lcs.wikidot.com/");
   move(18,39-((len(str)-1)>>1));
   addstr(str);
   strcpy(str,"ESC - 終了する。終了すると自動的に保存される");
   move(20,39-((len(str)-1)>>1));
   addstr(str);
   strcpy(str,"その他のキー - リベラルアジェンダを追求する!");
   move(22,39-((len(str)-1)>>1));
   addstr(str);
   move(24,79);
   addstr("+");

   int c=0;
   do
   {
      if(c=='m') music.enableIf(!music.isEnabled());
      if(music.isEnabled()) strcpy(str,"M - 音楽を止める");
      else strcpy(str,"M - 音楽を鳴らす");
      move(21,39-((len(str)-1)>>1));
      addstr(str);
      if(c==ESC) end_game();

      c=getkey();
   } while(c=='m'||c==ESC);

   viewhighscores();

   if(!loaded)
   {
      setup_newgame();
      makecharacter();
   }
   mode=GAMEMODE_BASE;
   mode_base();

   savegame("save.dat");
}
