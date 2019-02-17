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

         mvaddstr(4,57, "最");
         mvaddstr(5,57, "高");
         mvaddstr(6,57, "裁");
         mvaddstr(7,57, "判");
         mvaddstr(8,57, "所");
         mvaddstr(10,57, "裁");
         mvaddstr(11,57, "判");
         mvaddstr(12,57, "官");

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
                  else if(won==-1)addstr("女性は所有物とみなされ、合意のない性交も合法である。");
                  else if(law[l]==ALIGN_ARCHCONSERVATIVE)
                     addstr("女性は2等市民である。");
                  else if(law[l]==-1)addstr("差別禁止法は性差には適用されない。");
                  else if(law[l]==0)addstr("男女は通常は法的に平等だが、それが強制されることはない。");
                  else if(law[l]==1)addstr("女性には差別に対抗する具体的な手段が存在する。");
                  else if(won!=1||wincondition!=WINCONDITION_ELITE)addstr("男女平等は普遍的に尊重されている。");
                  else addstr("二分された性別はもはや存在しない。性別による分断は終わった。");
                  break;
               case LAW_CIVILRIGHTS:
                  if(won==-2)addstr("Entire ethnic groups are branded \"enemies of the state\".");
                  else if(won==-1)addstr("Slavery has been reintroduced, along with an apartheid system.");
                  else if(law[l]==ALIGN_ARCHCONSERVATIVE)
                     addstr("Civil rights laws have been repealed, ostensibly to promote \"states' rights\".");
                  else if(law[l]==-1)addstr("Racial discrimination is prohibited in name only.");
                  else if(law[l]==0)addstr("Pervasive racial inequality exists, although overt discrimination is illegal.");
                  else if(law[l]==1)addstr("Affirmative action is in place to counteract racial discrimination.");
                  else if(won!=1||wincondition!=WINCONDITION_ELITE)addstr("Racial equality is guaranteed and vigorously enforced.");
                  else addstr("The very idea of \"race\" has been universally discarded as pseudoscience.");
                  break;
               case LAW_DRUGS:
                  if(won==-2)addstr("Vodka is the only legal recreational drug in the People's Republic of America.");
                  else if(won==-1)addstr("Talking about recreational drugs is punishable by death.");
                  else if(law[l]==ALIGN_ARCHCONSERVATIVE)
                     addstr("Violent criminals are released to make room for drug offenders.");
                  else if(law[l]==-1)addstr("Prisons are filled with the targets of a war on drugs.");
                  else if(law[l]==0)addstr("Recreational drugs are prohibited unless medically prescribed.");
                  else if(law[l]==1)addstr("Marijuana is regulated and taxed, but harder drugs are illegal.");
                  else if(won!=1||wincondition!=WINCONDITION_ELITE)addstr("Recreational drugs all are regulated and taxed like alcohol and tobacco.");
                  else addstr("The government distributes free recreational drugs to anyone who wants them.");
                  break;
               case LAW_IMMIGRATION:
                  if(won==-2)addstr("All Americans must carry around an internal passport, or be shot on sight.");
                  else if(won==-1)addstr("Private border militiamen shoot suspected foreigners on sight.");
                  else if(law[l]==ALIGN_ARCHCONSERVATIVE)
                     addstr("Immigration is illegal, and noncitizens are shipped to Mexico at gunpoint.");
                  else if(law[l]==-1)addstr("The National Guard has been deployed to the borders to slow immigration.");
                  else if(law[l]==0)addstr("Great expense is taken to slow immigration, without success.");
                  else if(law[l]==1)addstr("The government works to accommodate potential immigrants but deports criminals.");
                  else if(won!=1||wincondition!=WINCONDITION_ELITE)addstr("Immigration is unregulated, and new immigrants are welcomed warmly.");
                  else addstr("There are open borders, and no distinctions between citizens and non-citizens.");
                  break;
               case LAW_ELECTIONS:
                  if(won==-2)addstr("Only Stalinist Party members may run in elections, and they all run unopposed.");
                  else if(won==-1)addstr("Instead of elections, political offices are auctioned off to the highest bidder.");
                  else if(law[l]==ALIGN_ARCHCONSERVATIVE)
                  addstr("Virtually no ethics restrictions exist on political officeholders.");
                  else if(law[l]==-1)addstr("Elections are mostly unregulated, but basic ethics restrictions are in place.");
                  else if(law[l]==0)addstr("Moderate campaign finance reform is implemented.");
                  else if(law[l]==1)addstr("Election financing is transparent and well-regulated.");
                  else if(won!=1||wincondition!=WINCONDITION_ELITE)addstr("Election expenses are publicly funded, and voting is by ranked list.");
                  else addstr("There is proportional representation, and over a dozen major political parties.");
                  break;
               case LAW_MILITARY:
                  if(won==-2)addstr("The military promotes Stalinism throughout the world by using force.");
                  else if(won==-1)addstr("The massive military kills dissenters at home and conquers poor nations abroad.");
                  else if(law[l]==ALIGN_ARCHCONSERVATIVE)
                  addstr("Out-of-control military spending funds several ongoing wars around the world.");
                  else if(law[l]==-1)addstr("Massive investment is put into the military, which always seems to be at war.");
                  else if(law[l]==0)addstr("Military spending is growing each year to fund overseas military adventures.");
                  else if(law[l]==1)addstr("The military is not a major priority, and mostly does peacekeeping missions.");
                  else if(won!=1||wincondition!=WINCONDITION_ELITE)addstr("The military has been weakened significantly, as there is little need for it.");
                  else addstr("The military has been abolished, and the entire world is at peace.");
                  break;
               case LAW_TORTURE:
                  if(won==-2)addstr("The Internal Affairs Commissariat constantly invents new methods of torture.");
                  else if(won==-1)addstr("The new Inquisition tortures heretics, blasphemers, and non-Christians to death.");
                  else if(law[l]==ALIGN_ARCHCONSERVATIVE)
                     addstr("Military and intelligence interrogators regularly engage in torture.");
                  else if(law[l]==-1)addstr("The line between standard interrogation and torture is severely blurred.");
                  else if(law[l]==0)addstr("Torture allegations still occasionally crop up, despite an official ban.");
                  else if(law[l]==1)addstr("The government strongly enforces a ban on torture.");
                  else if(won!=1||wincondition!=WINCONDITION_ELITE)addstr("The nation is a respected international leader on Moral Interrogation Practices.");
                  else addstr("Terrorism ended after the government formally apologized to terrorist leaders.");
                  break;
               case LAW_PRISONS:
                  if(won==-2)addstr("The former nation of Canada has been annexed and filled with Stalinist gulags.");
                  else if(won==-1)addstr("Prisoners must fight to the death in corporate-sponsored gladiatorial bouts.");
                  else if(law[l]==ALIGN_ARCHCONSERVATIVE)
                     addstr("Prisoners are often subject to torture and slave labor.");
                  else if(law[l]==-1)addstr("Prisoners suffer from horrible conditions and lack of basic rights.");
                  else if(law[l]==0)addstr("Prisoners receive basic rights and services, but reports of abuse are common.");
                  else if(law[l]==1)addstr("The prisons are regulated to protect prisoners' rights and safety.");
                  else if(won!=1||wincondition!=WINCONDITION_ELITE)addstr("The prisons are targeted at rehabilitation, rather than punishment.");
                  else addstr("Instead of prison, criminals voluntarily attend free support groups.");
                  break;
	           case LAW_TAX:
                  if(won==-2)addstr("Having any money whatsoever is punishable by 20 years in a gulag.");
                  else if(won==-1)addstr("There are no taxes, yet most people have no money.");
                  else if(law[l]==ALIGN_ARCHCONSERVATIVE)
                     addstr("The tax code is a nightmare designed to maintain class structure.");
                  else if(law[l]==-1)addstr("A flat tax is in effect, and there is no capital gains or inheritance tax.");
                  else if(law[l]==0)addstr("Taxes are moderate, but the code is full of loopholes.");
                  else if(law[l]==1)addstr("The wealthy are heavily taxed under a progressive taxation system.");
                  else if(won!=1||wincondition!=WINCONDITION_ELITE)addstr("Rich people are virtually unheard of, due to taxation.");
                  else addstr("Money no longer exists, everything is free, and everyone enjoys lives of luxury.");
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
                  if(won==-2)addstr("Everyone lives in constant fear of the Stalinist Party's Secret Police.");
                  else if(won==-1)addstr("Privatized police get bonuses on their paychecks for every person they kill.");
                  else if(law[l]==ALIGN_ARCHCONSERVATIVE)
                     addstr("Law enforcement is given free reign.");
                  else if(law[l]==-1)addstr("Even the worst police misconduct only earns slap-on-the-wrist punishments.");
                  else if(law[l]==0)addstr("Law enforcement is regulated to prevent extreme misconduct.");
                  else if(law[l]==1)addstr("Law enforcement has heavy oversight and freedom-of-information requirements.");
                  else if(won!=1||wincondition!=WINCONDITION_ELITE)addstr("All law enforcement positions are subject to election and recall.");
                  else addstr("With no police, criminals follow the honor system and turn themselves in.");
                  break;
               case LAW_PRIVACY:
                  if(won==-2)addstr("Citizens have to spy on each other and report to the Stalinist Party.");
                  else if(won==-1)addstr("Very detailed reports on each citizen are easily accessible to corporations.");
                  else if(law[l]==ALIGN_ARCHCONSERVATIVE)
                     addstr("Any corporation requesting private information is granted unrestricted access.");
                  else if(law[l]==-1)addstr("Privacy laws are full of loopholes and security backdoors are in everything.");
                  else if(law[l]==0)addstr("Basic safeguards for medical and financial privacy are in place but ineffective.");
                  else if(law[l]==1)addstr("All areas of privacy are protected with strong, effective safeguards.");
                  else if(won!=1||wincondition!=WINCONDITION_ELITE)addstr("Individual privacy is sacred, and state-of-the-art safeguards are mandatory.");
                  else addstr("All large organizations are prohibited from keeping any data about anyone.");
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
                  else if(law[l]==0)addstr("工場は適度な公害対策に従っている。");
                  else if(law[l]==1)addstr("工場は厳格な公害対策に従っている。");
                  else if(won!=1||wincondition!=WINCONDITION_ELITE)addstr("工場はゼロ容認の公害対策に従っている。");
                  else addstr("公害は存在せず自然が回復した。");
                  break;
               case LAW_LABOR:
                  if(won==-2)addstr("The state has nationalized all industries and assigns everyone jobs.");
                  else if(won==-1)addstr("People are bred in pens to be farmed out to corporations like beasts.");
                  else if(law[l]==ALIGN_ARCHCONSERVATIVE)
                     addstr("There is no weekend, children are forced to work, and workers can't afford food.");
                  else if(law[l]==-1)addstr("Working conditions are deplorable and there is no minimum wage.");
                  else if(law[l]==0)addstr("Workers are underpaid, have lousy benefits, and get fired if they complain.");
                  else if(law[l]==1)addstr("Workers are fairly compensated, have good benefits, and are difficult to fire.");
                  else if(won!=1||wincondition!=WINCONDITION_ELITE)addstr("There are universal workers' rights and a high guaranteed minimum income.");
                  else addstr("Wage slavery has been abolished, and robots have been built to do all the work.");
                  break;
               case LAW_GAY:
                  if(won==-2)addstr("Homosexuals are executed regularly for their \"bourgeoisie decadence\".");
                  else if(won==-1)addstr("Homosexuals are executed regularly for \"promoting the Gay Agenda\".");
                  else if(law[l]==ALIGN_ARCHCONSERVATIVE)
                     addstr("Homosexuals are routinely persecuted with no recourse.");
                  else if(law[l]==-1)addstr("Homosexuals are not tolerated.");
                  else if(law[l]==0)addstr("Homosexuals are grudgingly tolerated but have few equal rights.");
                  else if(law[l]==1)addstr("Homosexuals have many rights shared by heterosexuals.");
                  else if(won!=1||wincondition!=WINCONDITION_ELITE)addstr("Homosexuals have equal rights that are vigorously protected.");
                  else addstr("All sexual orientations are accepted, and most people are polyamorous.");
                  break;
               case LAW_CORPORATE:
                  if(won==-2)addstr("All forms of private enterprise are punishable by death.");
                  else if(won==-1)addstr("Corporations under the King run the country in a feudal system.");
                  else if(law[l]==ALIGN_ARCHCONSERVATIVE)
                     addstr("Corporations essentially run the country in a feudal system.");
                  else if(law[l]==-1)addstr("Corporate culture is corrupt and there is a great disparity in wages.");
                  else if(law[l]==0)addstr("Corporations are moderately regulated, although wages are still unfair.");
                  else if(law[l]==1)addstr("Corporations are stiffly regulated, and executive compensation is reasonable.");
                  else if(won!=1||wincondition!=WINCONDITION_ELITE)addstr("Corporations are subject to intense regulation, and there is a maximum wage law.");
                  else addstr("Corporations have been abolished, along with the rest of capitalism.");
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
            mvaddstr(23,0,"The country has achieved Liberal status!");
         else mvaddstr(23,0,"The country has achieved Elite Liberal status!");
         mvaddstr(24,0,"Press 'L' to view the high score list.");

         int c=getkey();

         if(c==interface_pgdn||c==KEY_DOWN||c==KEY_RIGHT) page++;
         else if(c==interface_pgup||c==KEY_UP||c==KEY_LEFT) page--;
         else if(c=='l') break;
      }
      else if(won==-1)
      {
         set_color(COLOR_RED,COLOR_BLACK,1);
         mvaddstr(23,0,"The country has been Reaganified.");
         mvaddstr(24,0,"Press 'L' to view the high score list.");

         int c=getkey();

         if(c==interface_pgdn||c==KEY_DOWN||c==KEY_RIGHT) page++;
         else if(c==interface_pgup||c==KEY_UP||c==KEY_LEFT) page--;
         else if(c=='l') break;
      }
      else if(won==-2)
      {
         set_color(COLOR_RED,COLOR_BLACK,1);
         mvaddstr(23,0,"The country has been Stalinized.");
         mvaddstr(24,0,"Press 'L' to view the high score list.");

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
      mvaddstr(0,0,"Are you sure you want to disband?");

      set_color(COLOR_WHITE,COLOR_BLACK,0);
      mvaddstr(2,0,"Disbanding scatters the Liberal Crime Squad, sending all of its members");
      mvaddstr(3,0,"into hiding, free to pursue their own lives.  You will be able to observe");
      mvaddstr(4,0,"the political situation in brief, and wait until a resolution is reached.");

      mvaddstr(6,0,"If at any time you determine that the Liberal Crime Squad will be needed");
      mvaddstr(7,0,"again, you may return to the homeless shelter to restart the campaign.");

      mvaddstr(9,0,"Do not make this decision lightly.  If you do need to return to action,");
      mvaddstr(10,0,"only the most devoted of your former members will return.");

      set_color(COLOR_WHITE,COLOR_BLACK,1);
      mvaddstr(13,0,"Type this Liberal phrase to confirm (press a wrong letter to rethink it):");

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
