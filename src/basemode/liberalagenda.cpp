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

enum Pages
{
   PAGE_LEADERS,
   PAGE_ISSUES_A,
   PAGE_ISSUES_B,
   //PAGE_POLLS_A,
   //PAGE_POLLS_B
   PAGENUM
};

/* base - liberal agenda */
bool liberalagenda(signed char won)
{
   int page=0, y;

   while(true)
   {
      erase();
      if(won==1)
      {
         set_color(COLOR_GREEN,COLOR_BLACK,1);
         move(0,0);
         addstr("リベラル・アジェンダの勝利");
         music.play(MUSIC_VICTORY);
      }
      else if(won==-1||won==-2)
      {
         set_color(COLOR_RED,COLOR_BLACK,1);
         move(0,0);
         addstr("リベラル・アジェンダの敗北");
         if(won==-1) music.play(MUSIC_REAGANIFIED);
         if(won==-2) music.play(MUSIC_STALINIZED);
      }
      else
      {
         set_color(COLOR_WHITE,COLOR_BLACK,1);
         move(0,0);
         addstr("リベラル・アジェンダの状況");
         music.play(MUSIC_LIBERALAGENDA);
      }

      if(page<0) page=PAGENUM-1;
      if(page>=PAGENUM) page=0;

      switch(page)
      {
      case PAGE_LEADERS:
      {

         move(1,0);
         addstr("+-----------------+ ---------+ ---------+");
         move(2,0);
         addstr("|       概要      |  議題 A  |  議題 B  |");
         move(3,0);
         addstr("+                 +-------------------------------------------------------------");

         signed char align=exec[EXEC_PRESIDENT];
         set_alignment_color(align,true);
         move(5,0);
         if(won==-1) addstr("国王: ");
         else if(won==-2) addstr("書記長: ");
         else
         {
            addstr("大統領 ");
            if(execterm==1)addstr("(1期目):");
            else addstr("(2期目):");
         }
         if(won==-2) move(5,30);
         else move(5,25);
         addstr(execname[EXEC_PRESIDENT]);

         align=exec[EXEC_VP];
         set_alignment_color(align,true);
         move(6,0);
         if(won==-1) addstr("愛情大臣: ");
         else if(won==-2) addstr("首相: ");
         else addstr("副大統領: ");
         if(won==-2) move(6,30);
         else move(6,25);
         addstr(execname[EXEC_VP]);

         align=exec[EXEC_STATE];
         set_alignment_color(align,true);
         move(7,0);
         if(won==-1) addstr("平和大臣: ");
         else if(won==-2) addstr("外務委員長: ");
         else addstr("国務長官: ");
         if(won==-2) move(7,30);
         else move(7,25);
         addstr(execname[EXEC_STATE]);

         align=exec[EXEC_ATTORNEY];
         set_alignment_color(align,true);
         move(8,0);
         if(won==-1) addstr("真理大臣: ");
         else if(won==-2) addstr("内務委員長: ");
         else addstr("司法長官: ");
         if(won==-2) move(8,30);
         else move(8,25);
         addstr(execname[EXEC_ATTORNEY]);

         if(won==-1)
         {
            set_color(COLOR_RED,COLOR_BLACK,1);
            move(10,0);
            addstr("CEOおよびテレビ宣教師議会");
         }
         else if(won==-2)
         {
            set_color(COLOR_RED,COLOR_BLACK,1);
            move(10,0);
            addstr("スターリン党議会");
         }
         else
         {
            int housemake[6]={0,0,0,0,0,0};
            for(int h=0;h<HOUSENUM;h++) housemake[house[h]+2]++;
            if(housemake[5]+MIN(housemake[0],housemake[4])>=HOUSEMAJORITY) align=ALIGN_STALINIST; // Stalinists have a majority (perhaps with help from extremists on both sides)
            else if(housemake[0]>=HOUSEMAJORITY) align=ALIGN_ARCHCONSERVATIVE; // Arch-Conservatives have a majority
            else if(housemake[4]>=HOUSEMAJORITY) align=ALIGN_ELITELIBERAL; // Elite Liberals have a majority
            else if(housemake[0]+housemake[1]>=HOUSEMAJORITY) align=ALIGN_CONSERVATIVE; // Conservatives plus Arch-Conservatives have a majority
            else if(housemake[3]+housemake[4]>=HOUSEMAJORITY) align=ALIGN_LIBERAL; // Liberals plus Elite Liberals have a majority
            else align=ALIGN_MODERATE; // nobody has a majority
            set_alignment_color(align,true);
            mvaddstr(10,0,"下院: ");
            if(stalinmode) addstr("ｽﾀｰﾘﾝ"+tostring(housemake[5])+", ");
            addstr("ﾘﾍﾞﾗﾙ+"+tostring(housemake[4])+", ");
            addstr("ﾘﾍﾞﾗﾙ"+tostring(housemake[3])+", ");
            addstr("穏健"+tostring(housemake[2])+", ");
            addstr("保守"+tostring(housemake[1])+", ");
            addstr("保守+"+tostring(housemake[0]));

            int senatemake[6]={0,0,0,0,0,0};
            for(int s=0;s<SENATENUM;s++) senatemake[senate[s]+2]++;
            senatemake[exec[EXEC_VP]+2]++; // Vice President is tie-breaking vote in the Senate
            if(senatemake[5]+MIN(senatemake[0],senatemake[4])>=SENATEMAJORITY) align=ALIGN_STALINIST; // Stalinists have a majority (perhaps with help from extremists on both sides)
            else if(senatemake[0]>=SENATEMAJORITY) align=ALIGN_ARCHCONSERVATIVE; // Arch-Conservatives have a majority
            else if(senatemake[4]>=SENATEMAJORITY) align=ALIGN_ELITELIBERAL; // Elite Liberals have a majority
            else if(senatemake[0]+senatemake[1]>=SENATEMAJORITY) align=ALIGN_CONSERVATIVE; // Conservatives plus Arch-Conservatives have a majority
            else if(senatemake[3]+senatemake[4]>=SENATEMAJORITY) align=ALIGN_LIBERAL; // Liberals plus Elite Liberals have a majority
            else align=ALIGN_MODERATE; // nobody has a majority
            set_alignment_color(align,true);
            senatemake[exec[EXEC_VP]+2]--; // Vice President isn't actually a Senator though
            mvaddstr(11,0,"上院: ");
            if(stalinmode) addstr("ｽﾀｰﾘﾝ"+tostring(senatemake[5])+", ");
            addstr("ﾘﾍﾞﾗﾙ+"+tostring(senatemake[4])+", ");
            addstr("ﾘﾍﾞﾗﾙ"+tostring(senatemake[3])+", ");
            addstr("穏健"+tostring(senatemake[2])+", ");
            addstr("保守"+tostring(senatemake[1])+", ");
            addstr("保守+"+tostring(senatemake[0]));
         }

         if(won==-1||won==-2) set_color(COLOR_RED,COLOR_BLACK,1);
         else if(won==1) set_color(COLOR_GREEN,COLOR_BLACK,1);
         else
         {
            int courtmake[6]={0,0,0,0,0,0};
            for(int s=0;s<COURTNUM;s++) courtmake[court[s]+2]++;
            if(courtmake[5]+MIN(courtmake[0],courtmake[4])>=COURTMAJORITY) align=ALIGN_STALINIST; // Stalinists have a majority (perhaps with help from extremists on both sides)
            else if(courtmake[0]>=COURTMAJORITY) align=ALIGN_ARCHCONSERVATIVE; // Arch-Conservatives have a majority
            else if(courtmake[4]>=COURTMAJORITY) align=ALIGN_ELITELIBERAL; // Elite Liberals have a majority
            else if(courtmake[0]+courtmake[1]>=COURTMAJORITY) align=ALIGN_CONSERVATIVE; // Conservatives plus Arch-Conservatives have a majority
            else if(courtmake[3]+courtmake[4]>=COURTMAJORITY) align=ALIGN_LIBERAL; // Liberals plus Elite Liberals have a majority
            else align=ALIGN_MODERATE; // nobody has a majority
            set_alignment_color(align,true);
         }

         mvaddstr(5,57, "最");
         mvaddstr(6,57, "高");
         mvaddstr(7,57, "裁");
         mvaddstr(8,57, "判");
         mvaddstr(9,57, "所");
         mvaddstr(10,57, "判");
         mvaddstr(11,57, "事");

         if(won==-1)
         {
            mvaddstr(7,62,"企業倫理委員会");
            mvaddstr(8,62,"      に");
            mvaddstr(9,62,"置き換えられた");
         }
         else if(won==-2)
         {
            mvaddstr(7,62, "スターリン主義者");
            mvaddstr(8,62, "による公開裁判に");
            mvaddstr(9,62, "置き換えられた");
         }
         else
         {
            y=4;
            for(int c=0;c<COURTNUM;c++,y++)
            {
               set_alignment_color(court[c],true);
               mvaddstr(y,60,courtname[c]);
            }
         }
         for(int l=0;l<LAWNUM;l++)
         {
            if(won==-1||won==-2)
               set_alignment_color(ALIGN_ARCHCONSERVATIVE,true);
            else if(won==1&&wincondition==WINCONDITION_ELITE)
               set_alignment_color(ALIGN_ELITELIBERAL,true);
            else set_color(COLOR_BLACK,COLOR_BLACK,1);
            mvaddstr(14+l/3,l%3*26,"|-----|");
            if(won==-1||won==-2)
               set_alignment_color(ALIGN_ARCHCONSERVATIVE,true);
            else set_alignment_color(law[l],true);
            addstr(getlaw(l));
            mvaddchar(14+l/3,l%3*26 + 3 - law[l],'O');
         }
         break;
      }

      case PAGE_ISSUES_A:
      case PAGE_ISSUES_B:
      {
         if(page==PAGE_ISSUES_A)
         {
            move(1,0);
            addstr("+---------------- +----------+ ---------+");
            move(2,0);
            addstr("|       概要      |  議題 A  |  議題 B  |");
            move(3,0);
            addstr("------------------+          +--------------------------------------------------");
         }
         else
         {
            move(1,0);
            addstr("+---------------- +--------- +----------+");
            move(2,0);
            addstr("|       概要      |  議題 A  |  議題 B  |");
            move(3,0);
            addstr("-----------------------------+          +---------------------------------------");
         }

         int y=4,startinglaw=0;
         if(page==PAGE_ISSUES_B) startinglaw=18;
         for(int l=startinglaw;l<startinglaw+18&&l<LAWNUM;l++,y++)
         {
            if(won==-1||won==-2)
               set_alignment_color(ALIGN_ARCHCONSERVATIVE,true);
            else set_alignment_color(law[l],true);

            move(y,0);

            switch(l)
            {
               case LAW_WOMEN:
                  if(won==-2)addstr("女性は通常男性の代わりに軍隊に召集される。");
                  else if(won==-1)addstr("女性は所有物とみなされ、強姦も合法である。");
                  else if(law[l]==ALIGN_ARCHCONSERVATIVE)
                     addstr("女性は2等市民である。");
                  else if(law[l]==-1)addstr("差別禁止法は性差には適用されない。");
                  else if(law[l]==0)addstr("男女は通常は法的に平等だが、それが強制されることはない。");
                  else if(law[l]==1)addstr("女性には差別に対抗する具体的な手段が存在する。");
                  else if(won!=1||wincondition!=WINCONDITION_ELITE)addstr("男女平等は普遍的に尊重されている。");
                  else addstr("二分された性別はもはや存在しない。性別による分断は終わった。");
                  break;
               case LAW_CIVILRIGHTS:
                  if(won==-2)addstr("あらゆる民族集団が「州の敵」である。");
                  else if(won==-1)addstr("奴隷制が人種隔離政策と共に復活した。");
                  else if(law[l]==ALIGN_ARCHCONSERVATIVE)
                     addstr("「州権」強化という名目で公民権は無効化された。");
                  else if(law[l]==-1)addstr("人種差別禁止は有名無実となっている。");
                  else if(law[l]==0)addstr("人種差別は広範囲に存在するが、明らかな差別は法で禁止されている。");
                  else if(law[l]==1)addstr("アファーマティブ・アクションが人種差別に対抗する手段として行われている。");
                  else if(won!=1||wincondition!=WINCONDITION_ELITE)addstr("人種的平等は保障され、積極的に推進されている。");
                  else addstr("「人種」という概念そのものが疑似科学として破棄された。");
                  break;
               case LAW_DRUGS:
                  if(won==-2)addstr("アメリカ人民共和国ではウォッカが唯一の合法的な娯楽目的のドラッグである。");
                  else if(won==-1)addstr("娯楽目的の薬物使用について言及した者は死刑とする。");
                  else if(law[l]==ALIGN_ARCHCONSERVATIVE)
                     addstr("暴力犯が薬物提供者の収容所を作るために解放された。");
                  else if(law[l]==-1)addstr("刑務所は薬物戦争の標的となった者で溢れている。");
                  else if(law[l]==0)addstr("医療目的でない薬物の使用は禁止されている。");
                  else if(law[l]==1)addstr("マリファナは規定され税金が掛けられている。しかしハードドラッグは違法である。");
                  else if(won!=1||wincondition!=WINCONDITION_ELITE)addstr("娯楽のための薬物はアルコールやタバコのように規定され税金が掛けられている。");
                  else addstr("誰でも娯楽目的で自由に使用できる薬物を政府が広めている。");
                  break;
               case LAW_IMMIGRATION:
                  if(won==-2)addstr("全国民は国内パスポートの携帯が義務付けられている。携帯していない者は射殺される");
                  else if(won==-1)addstr("国境では民兵が疑わしい外国人を発見し次第射殺している。");
                  else if(law[l]==ALIGN_ARCHCONSERVATIVE)
                     addstr("移民は違法である。そして市民でない者は銃を突きつけられメキシコに送られている。");
                  else if(law[l]==-1)addstr("移民の流入を抑えるために州兵が国境に展開されている。");
                  else if(law[l]==0)addstr("移民規制のために多額の資金が投入されている。だが効果はない。");
                  else if(law[l]==1)addstr("政府は潜在的な移民の受け入れを行っている。だが犯罪者は国外退去させている。");
                  else if(won!=1||wincondition!=WINCONDITION_ELITE)addstr("移民に関する規定は存在しない。そして新しい移民は歓迎される。");
                  else addstr("国境が開放され、市民と市民でないものの差は存在しない。");
                  break;
               case LAW_ELECTIONS:
                  if(won==-2)addstr("スターリン党の党員のみで選挙を行う。野党は存在しない。");
                  else if(won==-1)addstr("選挙ではなく最も高値で競り落としたものが政治家となる。");
                  else if(law[l]==ALIGN_ARCHCONSERVATIVE)
                  addstr("選挙には倫理的な制約が事実上存在しない。");
                  else if(law[l]==-1)addstr("選挙にはほぼ規制がないが、倫理的な制約が存在する。");
                  else if(law[l]==0)addstr("穏やかな選挙資金制度改革が行われている。");
                  else if(law[l]==1)addstr("選挙資金は透明で適切に制限されている。");
                  else if(won!=1||wincondition!=WINCONDITION_ELITE)addstr("選挙資金は公的に賄われ、投票は一覧表から行われている。");
                  else addstr("選挙は比例代表制で行われ、10以上の主要な政党が存在する。");
                  break;
               case LAW_MILITARY:
                  if(won==-2)addstr("軍が軍事力によってスターリン主義を世界中に広めている。");
                  else if(won==-1)addstr("平和主義者を殺害するためや貧しい国々を征服するために巨額の軍事費が投じられている。");
                  else if(law[l]==ALIGN_ARCHCONSERVATIVE)
                  addstr("制御不能の軍事費が世界中の紛争に供給されている。");
                  else if(law[l]==-1)addstr("軍備に多額の費用が投じられ、常に戦争状態のようである。");
                  else if(law[l]==0)addstr("軍事支出は海外での軍事的冒険のため年々増加している。");
                  else if(law[l]==1)addstr("軍事は優先事項ではなく、費用の大半が平和維持活動に費やされている。");
                  else if(won!=1||wincondition!=WINCONDITION_ELITE)addstr("軍備は明らかに縮小され、必要最小限のもののみとなっている。");
                  else addstr("軍は廃止され、全世界に平和が訪れた。");
                  break;
               case LAW_TORTURE:
                  if(won==-2)addstr("内務人民委員が新しい拷問を発明し続けている。");
                  else if(won==-1)addstr("新たな異端審問官が異端者、冒涜者、非キリスト教徒を拷問で殺害している。");
                  else if(law[l]==ALIGN_ARCHCONSERVATIVE)
                     addstr("軍と情報機関では拷問が正式に行われている。");
                  else if(law[l]==-1)addstr("正当な取り調べと拷問の境界線は非常に曖昧になっている。");
                  else if(law[l]==0)addstr("公式には禁止されているにも関わらす、拷問の疑惑が突如発生することがある。");
                  else if(law[l]==1)addstr("政府は拷問を強く禁止している。");
                  else if(won!=1||wincondition!=WINCONDITION_ELITE)addstr("国は取り調べにおける倫理の実践で国際的なリーダーとして評価されている。");
                  else addstr("政府が拷問についてテロリストの指導者に謝罪した後にテロリズムは終結した。");
                  break;
               case LAW_PRISONS:
                  if(won==-2)addstr("併合されたカナダには強制労働収容所がいたる所にある。");
                  else if(won==-1)addstr("囚人は企業がスポンサーのコロシアムで剣闘士として死ぬまで戦う。");
                  else if(law[l]==ALIGN_ARCHCONSERVATIVE)
                     addstr("囚人に対してしばしば拷問や奴隷的使役が行われている。");
                  else if(law[l]==-1)addstr("囚人はひどい条件に置かれ、基本的権利が侵害されている。");
                  else if(law[l]==0)addstr("囚人には基本的権利があるが、しばしば虐待の報告がある。");
                  else if(law[l]==1)addstr("刑務所には囚人の権利と安全を守る規定がある。");
                  else if(won!=1||wincondition!=WINCONDITION_ELITE)addstr("刑務所は罰よりもリハビリに重点が置かれている。");
                  else addstr("犯罪を犯した者は、刑務所の代わりに支援団体に自発的に参加する。");
                  break;
	           case LAW_TAX:
                  if(won==-2)addstr("いかなる理由でも通貨を所有する者は20年間の強制労働の罰が与えられる。");
                  else if(won==-1)addstr("税金は存在しないが、ほとんどの者には金がない。");
                  else if(law[l]==ALIGN_ARCHCONSERVATIVE)
                     addstr("税法は階級構造を固定化するために設計された悪夢のようである。");
                  else if(law[l]==-1)addstr("事実上の一律課税で、キャピタルゲイン税や相続税は存在しない。");
                  else if(law[l]==0)addstr("税金は適切だが、法律のいたる所に抜け穴がある。");
                  else if(law[l]==1)addstr("累進課税により裕福な人々にはより重い税金が課せられる。");
                  else if(won!=1||wincondition!=WINCONDITION_ELITE)addstr("裕福な人々にはかつてないほど課税されている。");
                  else addstr("通貨はもはや存在しない。全ては無料で、あらゆる人々は贅沢を楽しんでいる。");
                  break;
               case LAW_ABORTION:
                  if(won==-2)addstr("強制的な中絶を人口抑制のため実施する。");
                  else if(won==-1)addstr("中絶、避妊、そして性交渉の合意は全て死刑に相当する重罪である。");
                  else if(law[l]==ALIGN_ARCHCONSERVATIVE)
                     addstr("中絶は殺人と同様の重罪であり、いかなる理由においても許されない。");
                  else if(law[l]==-1)addstr("中絶は強姦、近親相姦、母体保護の場合を除き禁止されている。");
                  else if(law[l]==0)addstr("中絶は妊娠3ヶ月以内に限られている。そして多額の費用が掛かる。");
                  else if(law[l]==1)addstr("中絶は合法である。だが、中絶を税金で賄うことは禁止されている。");
                  else if(won!=1||wincondition!=WINCONDITION_ELITE)addstr("中絶の権利は強く保護されている。そして貧しい女性には政府の補助がある。");
                  else addstr("中絶は妊娠のあらゆる期間で容易に可能である。");
                  break;
               case LAW_ANIMALRESEARCH:
                  if(won==-2)addstr("「敵認定」の人々に対するあらゆる人体実験が推奨される。");
                  else if(won==-1)addstr("貧しい人々に対するあらゆる形態の試験が推奨される。");
                  else if(law[l]==ALIGN_ARCHCONSERVATIVE)
                     addstr("動物は自由に実験できる所有物である。");
                  else if(law[l]==-1)addstr("動物実験は科学者グループによって自主管理される。");
                  else if(law[l]==0)addstr("動物実験には資格と許可が必要である。");
                  else if(law[l]==1)addstr("動物実験は目的と与える苦痛により厳しく制限される。");
                  else if(won!=1||wincondition!=WINCONDITION_ELITE)addstr("動物も人と変わりがなく、市民権が与えられる。");
                  else addstr("全ての種は人と同様の権利がある。バクテリアでさえも。");
                  break;
               case LAW_POLICEBEHAVIOR:
                  if(won==-2)addstr("あらゆる人々がスターリン党秘密警察の恐怖の中で生きている。");
                  else if(won==-1)addstr("民営化された警察が人々を殺害するたびにボーナスを受け取っている。");
                  else if(law[l]==ALIGN_ARCHCONSERVATIVE)
                     addstr("法執行機関には無制限の権利が与えられている。");
                  else if(law[l]==-1)addstr("重大な問題行為を行った警官でさえも軽い罰を受けるのみである。");
                  else if(law[l]==0)addstr("法執行機関の極端な行為は禁止されている。");
                  else if(law[l]==1)addstr("法執行機関は強力に監視され、情報公開が求められる。");
                  else if(won!=1||wincondition!=WINCONDITION_ELITE)addstr("法執行機関の全ての地位は選挙とリコールの対象となる。");
                  else addstr("警察は存在せず、犯罪者は無監督制度に従い自らを更正する。");
                  break;
               case LAW_PRIVACY:
                  if(won==-2)addstr("市民は互いに監視し合いスターリン党に報告している。");
                  else if(won==-1)addstr("企業は市民の詳細な情報に簡単にアクセスできる。");
                  else if(law[l]==ALIGN_ARCHCONSERVATIVE)
                     addstr("あらゆる企業は個人情報への無制限のアクセスが認められている。");
                  else if(law[l]==-1)addstr("プライバシー法には欠陥が多数あり、いたる所にセキュリティ上の裏口がある。");
                  else if(law[l]==0)addstr("医療および経済的プライバシーは基本的に保護されているが実際には効果がない。");
                  else if(law[l]==1)addstr("あらゆる分野のプライバシーは強力かつ実効的に保護されている。");
                  else if(won!=1||wincondition!=WINCONDITION_ELITE)addstr("プライバシーは不可侵であり、最高水準の保護が義務付けられている。");
                  else addstr("全ての組織は、あらゆる人々のいかなるデータの保持も禁止されている。");
                  break;
               case LAW_DEATHPENALTY:
                  if(won==-2)addstr("敵認定された者は必ず死刑判決とする。");
                  else if(won==-1)addstr("貧しい者やマイノリティーによる犯罪は必ず死刑判決となる。");
                  else if(law[l]==ALIGN_ARCHCONSERVATIVE)
                     addstr("死刑は軽犯罪にも適用できる。");
                  else if(law[l]==-1)addstr("死刑は多くの州で実際に適用されている。");
                  else if(law[l]==0)addstr("死刑制度は存在するが存続が議論されている。");
                  else if(law[l]==1)addstr("死刑は極端な場合のみ適用される。");
                  else if(won!=1||wincondition!=WINCONDITION_ELITE)addstr("死刑は残虐な刑罰とみなされ、決して適用されない。");
                  else addstr("死刑やその他の厳しすぎる刑罰は既に廃止された。");
                  break;
               case LAW_NUCLEARPOWER:
                  if(won==-2)addstr("原子力施設は定期的にメルトダウンしているが、建造は続いている。");
                  else if(won==-1)addstr("原子力施設があらゆる場所に存在し、ガンの発症が急増している。");
                  else if(law[l]==ALIGN_ARCHCONSERVATIVE)
                     addstr("原子力の利用は管理や規制がなく急速に拡大している。");
                  else if(law[l]==-1)addstr("原子力はエネルギー源としてよく利用され、産業界によって自主管理されている。");
                  else if(law[l]==0)addstr("原子力はエネルギー源としてしばしば利用され、そして適切に管理されている。");
                  else if(law[l]==1)addstr("原子力は厳しく管理され、利用はまれである。");
                  else if(won!=1||wincondition!=WINCONDITION_ELITE)addstr("原子力利用は違法であり、核廃棄物の処理が進んでいる。");
                  else addstr("原子力利用は禁止され、核兵器は国連の査察官に監視されている。");
                  break;
               case LAW_POLLUTION:
                  if(won==-2)addstr("国営工場の汚染はすさまじく、労働者は全員ガンを発症している。");
                  else if(won==-1)addstr("工業地帯では汚染による子供の病気が当たり前である。");
                  else if(law[l]==ALIGN_ARCHCONSERVATIVE)
                     addstr("工場は必要ならば汚染させてもよい。");
                  else if(law[l]==-1)addstr("工場は自主的な公害対策に従っている。");
                  else if(law[l]==0)addstr("工場は穏やかな公害対策に従っている。");
                  else if(law[l]==1)addstr("工場は厳格な公害対策に従っている。");
                  else if(won!=1||wincondition!=WINCONDITION_ELITE)addstr("工場はゼロ容認の公害対策に従っている。");
                  else addstr("公害は存在せず自然が回復した。");
                  break;
               case LAW_LABOR:
                  if(won==-2)addstr("全ての企業が国有化され、あらゆる人々に労働が割り当てられている。");
                  else if(won==-1)addstr("人々が企業の家畜として売買されている。");
                  else if(law[l]==ALIGN_ARCHCONSERVATIVE)
                     addstr("週末の休暇がなく、子供も労働を強制され、そして食料を買う余裕もない。");
                  else if(law[l]==-1)addstr("労働環境は悲惨で最低賃金は存在しない。");
                  else if(law[l]==0)addstr("労働者は低い賃金で働いていて、不満を言えば解雇される。");
                  else if(law[l]==1)addstr("労働者には適切な給料が支払われ、解雇は困難である。");
                  else if(won!=1||wincondition!=WINCONDITION_ELITE)addstr("普遍的な労働者の権利と十分な最低賃金が保障されている。");
                  else addstr("賃金奴隷は廃止され、ロボットがあらゆる労働を行っている。");
                  break;
               case LAW_GAY:
                  if(won==-2)addstr("同性愛者は「ブルジョワ的退廃」として定期的に処刑されている。");
                  else if(won==-1)addstr("「ゲイ・アジェンダ推進」の名の下に同性愛者は定期的に処刑されている。");
                  else if(law[l]==ALIGN_ARCHCONSERVATIVE)
                     addstr("同性愛者は日常的に迫害されている。");
                  else if(law[l]==-1)addstr("同性愛は容認されていない。");
                  else if(law[l]==0)addstr("同性愛はしぶしぶ容認されているが、権利は対等ではない。");
                  else if(law[l]==1)addstr("同性愛者には異性愛者と多数の権利を共有している。");
                  else if(won!=1||wincondition!=WINCONDITION_ELITE)addstr("同性愛者は同等の権利を有し、それらは強力に保護されている。");
                  else addstr("全ての性的指向が受け入れられ、ほとんどの人々が多重的な性的関係を持っている。");
                  break;
               case LAW_CORPORATE:
                  if(won==-2)addstr("あらゆる形態の私企業は死刑で罰する。");
                  else if(won==-1)addstr("企業は国王の下で国を封建制で支配している。");
                  else if(law[l]==ALIGN_ARCHCONSERVATIVE)
                     addstr("企業は国を封建制で実質的に支配している。");
                  else if(law[l]==-1)addstr("企業文化は腐敗し、賃金には大きな不均衡がある。");
                  else if(law[l]==0)addstr("企業には緩やかな規制があるが、賃金はいまだ不公正である。");
                  else if(law[l]==1)addstr("企業には強い規制があり、役員報酬は適度に抑えられている。");
                  else if(won!=1||wincondition!=WINCONDITION_ELITE)addstr("企業には強力な規制が課せられ、役員報酬は法律で制限されている。");
                  else addstr("資本主義の終焉と共に企業は廃止された。");
                  break;
               case LAW_FREESPEECH:
                  if(won==-2)addstr("反革命的言論は死刑に相当する重罪である。");
                  else if(won==-1)addstr("容認できない発言しようと*考える*ことさえも死刑に相当する重罪である。");
                  else if(law[l]==ALIGN_ARCHCONSERVATIVE)
                     addstr("容認できない言論を取り締まることは武装部隊の任務である。");
                  else if(law[l]==-1)addstr("支持されない意見を発する人々は、しばしば嫌がらせや不当な扱いを受ける。");
                  else if(law[l]==0)addstr("言論の自由はわずかな例外はあるが法で認められ、そして広く受け入れられている。");
                  else if(law[l]==1)addstr("言論の自由は法的に保障され、公に推奨されている。");
                  else if(won!=1||wincondition!=WINCONDITION_ELITE)addstr("言論の自由は強力に保障され、例外なく支持されている。");
                  else addstr("言論の自由は絶対であり、視点の多様性が賞賛されている。");
                  break;
               case LAW_FLAGBURNING:
                  if(won==-2)addstr("アメリカ旧政府の旗は燃料である。");
                  else if(won==-1)addstr("国旗焼却を扱った絵や文章にも死刑が適用される。");
                  else if(law[l]==ALIGN_ARCHCONSERVATIVE)
                     addstr("国旗焼却は殺人と同等の重犯罪である。");
                  else if(law[l]==-1)addstr("国旗焼却は重罪で積極的に起訴される。");
                  else if(law[l]==0)addstr("国旗焼却は罪を問われるが、重大な犯罪とはみなされない。");
                  else if(law[l]==1)addstr("国旗焼却は違法ではないが、反愛国的であると非難される。");
                  else if(won!=1||wincondition!=WINCONDITION_ELITE)addstr("国旗焼却は抗議の手段として支持されている。");
                  else addstr("国旗焼却は7月4日の独立記念日に自由を称えるため伝統的に行われるようになった。");
                  break;
               case LAW_GUNCONTROL:
                  if(won==-2)addstr("銃を所有する者は全て銃殺される。");
                  else if(won==-1)addstr("不良少年がAK-47を携帯し、あてもなく路地をさまよっている。");
                  else if(law[l]==ALIGN_ARCHCONSERVATIVE)
                     addstr("機関砲、戦車、ミサイル等を含むあらゆる武器を自由に売買できる。");
                  else if(law[l]==-1)addstr("軍用武器は禁止されている。だが、それに近い武器は所有できる。");
                  else if(law[l]==0)addstr("軍用武器の所有は事実上全て禁止されている。");
                  else if(law[l]==1)addstr("ほとんどの武器は法執行機関以外に販売することができない。");
                  else if(won!=1||wincondition!=WINCONDITION_ELITE)addstr("公共の場での武器の携帯および売買は違法である。");//XXX: Should guns be legal in private, too? -- LK
                  else addstr("全ての武器製作者は廃業し、現存する銃も廃棄する。"); //They are illegal in private under Elite Liberal victory conditions - yetisyny
                  break;
            }
         }
         break;
      }
      }

      if(won==1)
      {
         set_color(COLOR_GREEN,COLOR_BLACK,1);
         if(wincondition==WINCONDITION_EASY)
            mvaddstr(23,0,"この国はリベラルに到達した!");
         else mvaddstr(23,0,"この国はエリート・リベラルに到達した");
         mvaddstr(24,0,"Lキーでハイスコアを表示する。");

         int c=getkey();

         if(c==interface_pgdn||c==KEY_DOWN||c==KEY_RIGHT) page++;
         else if(c==interface_pgup||c==KEY_UP||c==KEY_LEFT) page--;
         else if(c=='l') break;
      }
      else if(won==-1)
      {
         set_color(COLOR_RED,COLOR_BLACK,1);
         mvaddstr(23,0,"この国はレーガン化した。");
         mvaddstr(24,0,"Lキーでハイスコアを表示する。");

         int c=getkey();

         if(c==interface_pgdn||c==KEY_DOWN||c==KEY_RIGHT) page++;
         else if(c==interface_pgup||c==KEY_UP||c==KEY_LEFT) page--;
         else if(c=='l') break;
      }
      else if(won==-2)
      {
         set_color(COLOR_RED,COLOR_BLACK,1);
         mvaddstr(23,0,"この国はスターリン化した。");
         mvaddstr(24,0,"Lキーでハイスコアを表示する。");

         int c=getkey();

         if(c==interface_pgdn||c==KEY_DOWN||c==KEY_RIGHT) page++;
         else if(c==interface_pgup||c==KEY_UP||c==KEY_LEFT) page--;
         else if(c=='l') break;
      }
      else
      {
         move(23,0);
         if(stalinmode)
         {
            set_color(COLOR_RED,COLOR_BLACK,1);
            addstr("スターリン主義  ");
         }
         set_color(COLOR_GREEN,COLOR_BLACK,1);
         addstr("エリート・リベラル  ");
         if(!stalinmode)
         {
            set_color(COLOR_WHITE,COLOR_BLACK,0);
            addstr("-  ");
         }
         set_color(COLOR_CYAN,COLOR_BLACK,1);
         addstr("リベラル  ");
         if(!stalinmode)
         {
            set_color(COLOR_WHITE,COLOR_BLACK,0);
            addstr("-  ");
         }
         set_color(COLOR_YELLOW,COLOR_BLACK,1);
         addstr("穏健  ");
         if(!stalinmode)
         {
            set_color(COLOR_WHITE,COLOR_BLACK,0);
            addstr("-  ");
         }
         set_color(COLOR_MAGENTA,COLOR_BLACK,1);
         addstr("保守  ");
         if(!stalinmode)
         {
            set_color(COLOR_WHITE,COLOR_BLACK,0);
            addstr("-  ");
         }
         set_color(COLOR_RED,COLOR_BLACK,1);
         addstr("保守強硬");
         set_color(COLOR_WHITE,COLOR_BLACK,0);
         //mvaddstr(23,0,"Once these are Green, the country will have achieved Elite Liberal status.");
         mvaddstr(24,0,"D - 解散して時を待つ     ←/→ - 別のページを見る     その他のキー - 戻る");

         int c=getkey();

         if(c==interface_pgdn||c==KEY_DOWN||c==KEY_RIGHT) page++;
         else if(c==interface_pgup||c==KEY_UP||c==KEY_LEFT) page--;
         else if(c=='d') return confirmdisband();
         else break;
      }
   }
   return false;
}



/* base - liberal agenda - disband */      // The (current) issue that the masses are most
bool confirmdisband()                      // concerned should be (slightly) more likely
{                                          // to be the phrase. (Issue, not the CCS, etc.)
   static const char *issue_phrases[] =    //    -- LK
   {  /////////////////////////////////////////////////////////////////////////////////////////
      // Liberal Phrase           // Conservative Equivalent  // Stalinist Equivalent        //
      /////////////////////////////////////////////////////////////////////////////////////////
      "Corporate Accountability", // Deregulation             // Nationalized Industry       //
      "Free Speech",              // Child Safety             // Ideological Purity          //
      "Gay Marriage",             // Sanctity of Marriage     // Bourgeoisie Decadence       //
      "Abortion Rights",          // Right to Life            // Population Control          //
      "Separation Clause",        // Under God                // Opiate of the Masses        //
      "Racial Equality",          // Emmett Till              // Kulaks                      //
      "Gun Control",              // Second Amendment         // Firing Squad                //
      "Campaign Finance Reform",  // Freedom to Campaign      // People's Republic           //
      "Animal Rights",            // Animal Abuse             // Capitalist Pig-Dogs         //
      "Worker's Rights",          // Right to Work            // Canadian Gulags             //
      "Police Responsibility",    // Rodney King              // Secret Police               // /* XXX: "Civilian" Police (Note to self) -- LK */
      "Global Warming",           // Self-Regulation          // Five-Year Plan              //
      "Immigration Reform",       // Border Control           // Iron Curtain                // /* XXX: "Nicer" Term (Note to self) -- LK */
      "Human Rights",             // National Security        // Reeducation                 // /* XXX: 2+2 = 5? (Note to self) -- LK */
      "Woman's Suffrage",         // Traditional Gender Roles // Honey Trap                  //
      "Right To Privacy",         // Wiretapping              // Stasi                       //
      "Medical Marijuana",        // War on Drugs             // Vodka                       //
      "Flag Burning",             // Patriotism               // Hammer and Sickle           // /* XXX: Towards the beginning of 1984, at Winston's job. (Note to self) -- LK */
      "Life Imprisonment",        // Zero Tolerance           // Mass Grave                  //
      "Conflict Resolution",      // Preemptive Strike        // Mutual Assured Destruction  //
      "Radiation Poisoning",      // Nuclear Power            // Chernobyl                   //
      "Tax Bracket"               // Flat Tax                 // Proletariat                 //
   }; /////////////////////////////////////////////////////////////////////////////////////////

   string word=pickrandom(issue_phrases);

   for(int pos=0;pos<len(word);)
   {
      erase();

      set_color(COLOR_WHITE,COLOR_BLACK,1);
      mvaddstr(0,0,"本当に解散するか?");

      set_color(COLOR_WHITE,COLOR_BLACK,0);
      mvaddstr(2,0,"リベラル・クライム・スコードを解散すると、全てのメンバーは隠れ、自由に自分自身");
      mvaddstr(3,0,"の人生を追い求める。あなたは政治情勢の概要を見ることができ、そして結論がでるま");
      mvaddstr(4,0,"で待つことになる。");

      mvaddstr(6,0,"もし、リベラル・クライム・スコードが再び必要になったならば、いつでもホームレス");
      mvaddstr(7,0,"・シェルターからやり直すことができる。");

      mvaddstr(9,0,"これは気軽に選択してはならない。もし活動が必要になっても、主要なメンバーしか戻");
      mvaddstr(10,0,"ってこないだろう。");

      set_color(COLOR_WHITE,COLOR_BLACK,1);
      mvaddstr(13,0,"了解したならば次のリベラルフレーズを入力すること。(別のキーを押すと再考する):");

      for(int x=0;x<len(word);x++)
      {
         if(x==pos) set_color(COLOR_GREEN,COLOR_BLACK,0);
         else if(x<pos) set_color(COLOR_GREEN,COLOR_BLACK,1);
         else set_color(COLOR_WHITE,COLOR_BLACK,0);
         mvaddchar(15,x,word[x]);
      }

      if(getkey()==::tolower(word[pos]))
      {
         pos++;
         if(word[pos]==' '||word[pos]=='\''||word[pos]=='-') pos++;
      }
      else return false;
   }
   //SET UP THE DISBAND
   for(int p=len(pool)-1;p>=0;p--)
   {
      if(!pool[p]->alive) delete_and_remove(pool,p);
      else if(!(pool[p]->flag&CREATUREFLAG_SLEEPER))
      {
         removesquadinfo(*pool[p]);
         pool[p]->hiding=-1;
      }
   }
   cleangonesquads();
   disbandtime=year;
   return true;
}
