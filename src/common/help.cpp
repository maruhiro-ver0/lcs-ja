#include <externs.h>

/**
ACTIVITY_VISIT, TODO
ACTIVITY_RECRUITING, TODO
ACTIVITY_HOSTAGETENDING, TODO
ACTIVITY_DOS_RACKET, TODO
ACTIVITY_MAKE_ARMOR, TODO
ACTIVITY_WHEELCHAIR, TODO
ACTIVITY_BURY, TODO
ACTIVITY_WRITE_BLOG, TODO
ACTIVITY_TEACH_GENERALED, TODO
ACTIVITY_TEACH_POLITICS, TODO
ACTIVITY_TEACH_SURVIVAL, TODO
ACTIVITY_TEACH_FIGHTING, TODO
ACTIVITY_TEACH_COVERT, TODO
ACTIVITY_CLINIC, TODO
ACTIVITY_HEAL, TODO
ACTIVITY_SLEEPER_LIBERAL, TODO
ACTIVITY_SLEEPER_CONSERVATIVE, TODO
ACTIVITY_SLEEPER_SPY, TODO
ACTIVITY_SLEEPER_RECRUIT, TODO
ACTIVITY_SLEEPER_SCANDAL, TODO
ACTIVITY_SLEEPER_EMBEZZLE, TODO
ACTIVITY_SLEEPER_STEAL, TODO
ACTIVITY_SLEEPER_JOINLCS, TODO
*/
// {{{ Various voids
// Help pages are drawn here.

// NOTE: This will probably need updating if there are any fundamental code
// changes that will change gameplay.
void help(const char* string)
{
   clear();
}

// Generates help page on activities.
// Just supply Activity type.
void HelpActivities(int activityType)
{
   // I have actually created a screen editor to help me create the code
   // for the help. It can probably be used all over the place for formatting
   // large pieces of text.
   //
   // Could you possibly put this in ../../dev/ ? -- LK

   if(activityType == ACTIVITY_NONE)
   {
      return;
   }

   clear();
   set_color(COLOR_WHITE,COLOR_BLACK,0);
   move(0,0);
   addstr("リベラル・ヘルプ");

   switch(activityType)
   {
// }}}
// {{{ Liberal activism
// {{{ ACTIVITY_COMMUNITYSERVICE
   case ACTIVITY_COMMUNITYSERVICE:
      move(2,0);
      addstr("===社会奉仕===");
      move(4,0);
      addstr("  世論への小さな影響がある。ジュースが増す。");
      break;
// }}}
// {{{ ACTIVITY_TROUBLE
   case ACTIVITY_TROUBLE:
      move(2,0);
      addstr("===リベラル反抗===");
      move(4,0);
      addstr("リベラル的反抗は違法なリベラル活動の形態で、世論にプラスの影響を与える。");
      move(5,0);
      addstr("有罪となった場合には短い刑期がある。この場合もジュースが増す。");
      move(7,0);
      addstr("誘惑、魅力、敏捷性、心、腕力、知識が高いと世論に与える影響も大きい。");
      move(9,0);
      addstr("敏捷性、知識、説得、ストリートセンスが高いと警察の追跡を振る切ることができる。");
      move(10,0);
      addstr("怒った群衆から暴力を受ける可能性もある。");
      break;
// }}}
// {{{ ACTIVITY_GRAFFITI
   case ACTIVITY_GRAFFITI:
      move(2,0);
      addstr("===落書き===");
      move(4,0);
      addstr("政治的落書きをスプレーで描くことは軽犯罪で、有罪となった場合には短い刑期が課せ");
      move(5,0);
      addstr("られる。世論にプラスの影響を与える。もしスプレー缶がなければ、手に入れるのに1");
      move(6,0);
      addstr("日掛かる。");
      move(8,0);
      addstr("心と芸術が高いと世論への影響も大きい。");
      break;
// }}}
// {{{ ACTIVITY_POLLS
   case ACTIVITY_POLLS:
      move(2,0);
      addstr("===世論調査===");
      move(4,0);
      addstr("世論調査は人々が様々な問題に対してどのように考えているかを知る合法的な活動であ");
      move(5,0);
      addstr("る。他のリベラル活動とは異なり、世論調査は世論に影響を与えない。単に世論を知る");
      move(6,0);
      addstr("だけである。コンピュータのスキルがと知識があればより正確な結果が得られる。");
      break;
// }}}
// {{{ ACTIVITY_DOS_ATTACKS
   case ACTIVITY_DOS_ATTACKS:
      move(2,0);
      addstr("===Harassing Websites===");
      move(4,0);
      addstr(" Harassing Websites is an illegal activity and a form of Liberal Activism. It ");
      move(5,0);
      addstr(" is a weaker version of Hacking. Resulting in much shorter prison sentences, ");
      move(6,0);
      addstr(" and is much less likely to provoke a raid by the Police or other law  ");
      move(7,0);
      addstr(" enforcement. Harassing websites only requires a Computers skill of 1.");
      move(9,0);
      addstr(" Utilizes only the Computers skill.");
      break;
// }}}
// {{{ ACTIVITY_HACKING
   case ACTIVITY_HACKING:
      move(2,0);
      addstr("===ハッキング===");
      move(4,0);
      addstr("ハッキングは高度で違法なリベラル活動で、世論にプラスの影響を与える。これはとて");
      move(5,0);
      addstr("も長い刑期が課せられる。");
      move(7,0);
      addstr("ハッキングを成功させるには高いコンピュータのスキルと知識が必要だ。成果を出すた");
      move(8,0);
      addstr("めには最低でも6は必要である。グループで行えばさらに効果が高まる。");
      move(10,0);
      addstr("ハッキングに成功しても、コンピュータのスキルと知識があれば犯罪になることを回避");
      move(11,0);
      addstr("できる可能性がある。もし犯罪になれば、アジトを発見される危険性が高まる。また、");
      move(12,0);
      addstr("ハッキングに成功するとジュースが上がる。");
      move(14,0);
      addstr("あなたのハッカーがファイルを見つけることがあるが、それをリベラルガーディアンの");
      move(15,0);
      addstr("特別記事にして世論に影響を与えることができる。");
      break;
// }}}
// {{{ ACTIVITY_WRITE_LETTERS
   case ACTIVITY_WRITE_LETTERS:
      move(2,0);
      addstr("===新聞への投書===");
      move(4,0);
      addstr("新聞への投書は合法的なリベラル活動で、文筆のスキルを高め、そして文筆のスキルが");
      move(5,0);
      addstr("高いほど世論に大きな影響を与えられる。投書の主な目的はリベラルガーディアンの記");
      move(6,0);
      addstr("事を書くスキルを上げるためである。リベラルガーディアンは投書よりも大きな影響を");
      move(7,0);
      addstr("与えられ、そして完全に合法である。");
      move(9,0);
      addstr("リベラルガーディアンの記事を書くのとは異なり、投書は自分自身で新聞を発行するた");
      move(10,0);
      addstr("めに大金を投じて印刷機を購入する必要はない。そして、リベラルガーディアンの記事");
      move(11,0);
      addstr("を書くよりも文筆のスキルが速く高まる。");
      move(13,0);
      addstr("リベラルガーディアンの記事を書くためには、メイン画面でZキーを押して新聞を印刷し");
      move(14,0);
      addstr("たい場所を決定し、$3,000を投じて印刷機を購入する必要がある。さらに、その印刷機");
      move(15,0);
      addstr("のあるアジトにいる必要がある。");
      break;
// }}}
// {{{ ACTIVITY_WRITE_GUARDIAN
   case ACTIVITY_WRITE_GUARDIAN:
      move(2,0);
      addstr("===リベラルガーディアンの記事を書く===");
      move(4,0);
      addstr(" Writing for the Liberal Guardian is a legal (or illegal depending on the ");
      move(5,0);
      addstr(" free speech laws) activity and a form of Liberal Activism that boosts the");
      move(6,0);
      addstr(" Writing skill very slowly and is more effective at influencing Public ");
      move(7,0);
      addstr(" Opinion the higher the Writing skill is. Writing for the Liberal Guardian ");
      move(8,0);
      addstr(" has three times the impact on Public Opinion that Write to Newspapers has.");
      move(10,0);
      addstr("Items that prompt a special edition");
      move(11,0);
      addstr(">     Police Records - Found in the Police Station.");
      move(12,0);
      addstr(">     Secret Corporate Files - Found in the Corporate Headquarters, or");
      move(13,0);
      addstr("      obtained through Hacking.");
      move(14,0);
      addstr(">     CEO Photos - Found in the CEO Residence.");
      move(15,0);
      addstr(">     Intel. HQ Data Disk - Found in the Intelligence HQ.");
      move(16,0);
      addstr(">     Cable News Memos - obtained through Hacking.");
      move(17,0);
      addstr(">     Research Papers - obtained through Hacking.");
      move(18,0);
      addstr(">     Judge Corruption Evidence - obtained through Hacking.");
      move(19,0);
      addstr(">     AM Radio Memos - obtained through Hacking.");
      move(20,0);
      addstr(" All of the above items can be delivered to the LCS from sleepers in the ");
      move(21,0);
      addstr(" appropriate location or from hackers.");
      break;
// }}}
// }}}
// {{{ Legal fund raising
// {{{ ACTIVITY_DONATIONS
   case ACTIVITY_DONATIONS:
      move(2,0);
      addstr("===寄付金集め===");
      move(4,0);
      addstr(" Income depends on persuasion. ");
      move(5,0);
      addstr(" This activity generates very little income when the country is very ");
      move(6,0);
      addstr(" Liberal, as people will have little reason to turn to the LCS. ");
      move(8,0);
      addstr(" This activity trains persuasion.");
      break;
// }}}
// {{{ ACTIVITY_SELL_TSHIRTS
   case ACTIVITY_SELL_TSHIRTS:
      move(2,0);
      addstr("===Tシャツの販売===");
      move(4,0);
      addstr(" Income depends on tailoring and business skills.");
      move(5,0);
      addstr("  The income is lower if the public mood is Liberal.");
      move(7,0);
      addstr(" This activity trains tailoring and business and may.");
      move(8,0);
      addstr(" have a positive political effect if done well enough.");
      break;
// }}}
// {{{ ACTIVITY_SELL_ART
   case ACTIVITY_SELL_ART:
      move(2,0);
      addstr("===アートの販売===");
      move(4,0);
      addstr(" Income depends on art skill and is lower if the country");
      move(5,0);
      addstr(" is very Liberal.");
      move(7,0);
      addstr(" This activity trains art, and may have a positive political");
      move(8,0);
      addstr(" effect if done well enough.");
      break;
// }}}
// {{{ ACTIVITY_SELL_MUSIC
   case ACTIVITY_SELL_MUSIC:
      move(2,0);
      addstr("===ストリートミュージックの演奏===");
      move(4,0);
      addstr(" Income depends on music skill. ");
      move(6,0);
      addstr(" An equipped guitar will increase income substantially and speed skill gains.");
      move(7,0);
      addstr(" Income is lower if the public mood is Liberal.");
      move(9,0);
      addstr(" This activity trains music, and may have a positive political");
      move(10,0);
      addstr(" effect if done well enough.");
      break;
// }}}
// }}}
// {{{ Illegal fund raising
// {{{ ACTIVITY_SELL_DRUGS
   case ACTIVITY_SELL_DRUGS:
      move(2,0);
      addstr("===ケーキの販売===");
      move(4,0);
      addstr(" Selling brownies on the street is an illegal way to make money. Money earned is ");
      move(5,0);
      addstr(" based upon the activists persuasion, street sense and business skill.");
      move(7,0);
      addstr(" It raises persuasion, street sense, and business. Street sense is used ");
      move(8,0);
      addstr(" to avoid being caught. If caught and tried, the severity of the crime can vary ");
      move(9,0);
      addstr(" greatly based upon circumstances. ");
      move(11,0);
      addstr(" The more Conservative that the drug laws are, the more money you will make. However, ");
      move(12,0);
      addstr(" the consequences of being convicted will increase as well. ");
      break;
// }}}
// {{{ ACTIVITY_PROSTITUTION
   case ACTIVITY_PROSTITUTION:
      move(2,0);
      addstr("===売春===");
      move(4,0);
      addstr(" Prostitution is an activity which raises money illegally. The amount of money");
      move(5,0);
      addstr(" made is based on seduction. The Seduction skill is trained and it also");
      move(6,0);
      addstr(" decreases your Juice every time you do it. Prostitution is quite lucrative ");
      move(7,0);
      addstr(" with seduction that is over 10.");
      move(9,0);
      addstr(" Street sense will help you evade being criminalized and caught.");
      break;
// }}}
// {{{ ACTIVITY_CCFRAUD
   case ACTIVITY_CCFRAUD:
      move(2,0);
      addstr("===カード番号の不正取得===");
      move(4,0);
      addstr(" To steal credit card numbers you need to have someone who has a computer ");
      move(5,0);
      addstr(" skill of at least 2. The more computer skill your hacker has the more money ");
      move(6,0);
      addstr(" you will make. This activity trains computer skill.");
      break;
// }}}
// {{{ ACTIVITY_REPAIR_ARMOR
   case ACTIVITY_REPAIR_ARMOR:
      move(2,0);
      addstr("===服の修繕===");
      move(4,0);
      addstr(" Repairing clothing will repair damaged armor and remove blood stains if there ");
      move(5,0);
      addstr(" are any. ");
      move(7,0);
      addstr(" The chance of repairing the clothing is dependant on the quality of ");
      move(8,0);
      addstr(" the clothing and the tailoring skill of the activist.");
      break;
// }}}
// }}}
// {{{ Stealing {cars,wheelchairs}
   case ACTIVITY_STEALCARS:
      move(2,0);
      addstr("===自動車泥棒===");
      move(4,0);
      addstr(" Stealing a car will have the Liberal attempt to steal a car from the street. ");
      move(5,0);
      addstr(" if successful, the car will be added to your garage. ");
      move(7,0);
      addstr(" Street sense determines the chances of finding a specific type of car, ");
      move(8,0);
      addstr(" security determines the successfulness of any attempt to break into or hotwire ");
      move(9,0);
      addstr(" the car. ");
      move(11,0);
      addstr(" Strength determines the chances of effectively breaking a car window, intelligence ");
      move(12,0);
      addstr(" determines the ease of which the car keys are found. ");
      break;
// }}}
// {{{ default
   default:
      move(2,0);
      addstr("===THE GREAT UNKNOWN===");
      move(4,0);
      addstr("There is no help on this topic yet, as the help system is quite new.");
      move(5,0);
      addstr("However, if you want to help us, you could write one, and send it to us!");
      break;
// }}}
   }

   set_color(COLOR_WHITE,COLOR_BLACK,0);
   move(23,0);
   addstr("   何かキーを押す - 1つ前の画面に戻る");

   getkey();
}
