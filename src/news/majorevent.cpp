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

/* news - constructs non-LCS related event stories */
void constructeventstory(char *story,short view,char positive)
{
   strcpy(story,"");

   if(positive)
   {
      switch(view)
      {
         case VIEW_WOMEN:
         {
            char str[200],str2[200],gen[50];
            strcpy(story,cityname());
            strcat(story," - 『病院で殺人』昨日、");
            if(law[LAW_ABORTION]==-2) strcat(story,"違法な中絶殺人を日常的に行っている医師が");
            else if(law[LAW_ABORTION]==-1) strcat(story,"違法な中絶を日常的に行っている医師が");
            else if(law[LAW_ABORTION]==0) strcat(story,"脱法的な中絶を日常的に行っている医師が");
            else strcat(story,"中絶を日常的に行っている医師が");
            lastname(str,true); strcat(story,str);
            strcat(story,"病院の外で射殺された。");
            strcat(story,"警察によると、");
            char dstr[200],dstr2[200];
            char gn=(LCSrandom(2)?GENDER_MALE:GENDER_FEMALE);
            generate_name(dstr,dstr2,gn);
            strcat(story,dstr);
            strcat(story,"医師は");
            strcat(story,dstr2);
            strcpy(gen,(gn==GENDER_FEMALE?"自分の":"自分の"));
            strcat(story,gen);
            strcat(story,"車に向かって歩いているところを、");//TODO: Add more variety, not just in the parking lot.
            strcat(story,"近くにいた車から狙われたようだ。");
            strcat(story,dstr2);
            strcat(story,"は");
            strcat(story,LCSrandom(15)+3);
            strcat(story,"発撃たれ、駐車場で即死した。");
            strcat(story,"容疑者の");
            generate_name(str,str2);
            strcat(story,str);
            strcat(story,"・");
            strcat(story,str2);
            strcat(story,"が拘束された。&r");
            strcat(story,"  目撃者によると、");
            strcat(story,str2);
            strcat(story,"は発砲後も現場にとどまり、");
            strcat(story,"立ちすくむ人々の前で聖書の一節を叫んだ。その後、");
            strcat(story,"携帯電話の通報で駆けつけた警察官に逮捕された。");
            strcat(story,str2);
            strcat(story,"は");
            if(law[LAW_WOMEN]==-2)
            {
               strcat(story,"自分がFBIの自警主義者であり、");
               strcat(story,"中絶医師を逮捕することに反対し追跡していたことを認めた。&r");
            }
            else
            {
               strcat(story,"抵抗せず投降し、");
               strcat(story,"神の御業はなしとげられたと言ったと伝えられている。&r");
            }
            strcat(story,"  ");
            strcat(story,dstr2);
            strcat(story,"には");
            char spouse=(LCSrandom(2)?GENDER_MALE:GENDER_FEMALE);
            if(law[LAW_GAY]<=1)
               spouse=(gn==GENDER_FEMALE?GENDER_MALE:GENDER_FEMALE);
            strcat(story,(spouse==GENDER_FEMALE?"妻":"夫"));
            strcat(story,"と");
            switch(LCSrandom(4))
            {
            case 0: strcat(story,"2");break;
            case 1: strcat(story,"3");break;
            case 2: strcat(story,"4");break;
            case 3: strcat(story,"5");break;
            }
            strcat(story,"人の子供がいた。&r");
            break;
         }
         case VIEW_GAY:
         {
            strcpy(story,cityname());
            strcat(story," - 『ヘイトクライム』昨日、");
            if(law[LAW_GAY]==-2) strcat(story,"性的逸脱者として知られる");
            else if(law[LAW_GAY]==-1) strcat(story,"同性愛者として知られる");
            else strcat(story,"同性愛者の");
            char dstr[200],dstr2[200];
            generate_name(dstr,dstr2);
            strcat(story,dstr);
            strcat(story,"・");
            strcat(story,dstr2);
            strcat(story,"が");
            switch(LCSrandom(3))
            {
            case 0: strcat(story,"トラックに引きずられ");break;
            case 1: strcat(story,"生きたまま焼かれ");break;
            case 2: strcat(story,"何度も殴打され");break;
            }
            strcat(story,"殺害された。");
            strcat(story,"警察によると、4人の容疑者が車による逃走の末に逮捕された。");
            strcat(story,"氏名はまだ発表されていない。");
            strcat(story,"&r");
            strcat(story,"  高速道路での目撃者によると、");
            strcat(story,"容疑者は追跡するするパトカーに対して乱暴に蛇行しながら");
            switch(LCSrandom(3))
            {
            case 0:
               if(law[LAW_FREESPEECH]==-2) strcat(story,"[ジュース箱]を投げつけていた");
               else strcat(story,"ビールのカンを投げつけていた");
               break;
            case 1:
               if(law[LAW_FREESPEECH]==-2) strcat(story,"窓から[自分で放出していた]");
               else if(law[LAW_FREESPEECH]==2) strcat(story,"窓からションベンしていた");
               else strcat(story,"窓から放尿していた");
               break;
            case 2: strcat(story,"体当たりしていた"); break;
            }
            strcat(story,"。");
            strcat(story,"追跡は");
            switch(LCSrandom(5))
            {
            case 0: strcat(story,"容疑者の車のガソリンが切れる"); break;
            case 1: strcat(story,"容疑者の車がバキュームカートに衝突する"); break;
            case 2: strcat(story,"容疑者の車が溝に転落する"); break;
            case 3: strcat(story,"容疑者の車が市民に取り囲まれる"); break;
            case 4: strcat(story,"容疑者の車が渋滞に巻き込まれる"); break;
            }
            strcat(story,"まで続き、その後に拘束された。この追跡によるけが人はいなかった。");
            strcat(story,"&r");
            strcat(story,"  当局者はこの事件を");
            if(law[LAW_GAY]==-2&&law[LAW_FREESPEECH]!=-2)
            {
               strcat(story,"、");
               strcat(story,dstr);
               strcat(story,"・");
               strcat(story,dstr2);
               strcat(story,"はホモであるが");
            }
            else if(law[LAW_GAY]==-2)strcat(story,"、ゲイは逸脱者であることは当然として、");
            strcat(story,"ヘイトクライム(憎悪犯罪)として重く受け止めている。");
            strcat(story,"&r");
            break;
         }
         case VIEW_DEATHPENALTY:
         {
            strcat(story,statename());
            strcat(story," - 『司法の死』無実の市民が電気椅子で処刑された。");
            strcat(story,"昨日の");
            switch(LCSrandom(2))
            {
            case 0: strcat(story,"午前"); break;
            case 1: strcat(story,"午後"); break;
            }
            strcat(story,LCSrandom(12)+1);
            strcat(story,"時");
            strcat(story,LCSrandom(60));
            strcat(story,"分、");
            char jstr[200];
            lastname(jstr,true);
            strcat(story,jstr);
            strcat(story,"刑務所で");
            char dstr[200],dstr2[200],dstr3[200];
            generate_long_name(dstr,dstr2,dstr3);
            strcat(story,dstr);
            strcat(story,"・");
            strcat(story,dstr2);
            strcat(story,"・");
            strcat(story,dstr3);
            strcat(story,"の死刑が執行された。");
            strcat(story,"&r");
            strcat(story,"  ");
            strcat(story,dstr3);
            strcat(story,"は");
            strcat(story,year-LCSrandom(11)-10);
            strcat(story,"年に13件の連続殺人で有罪判決を受けていた。");
            strcat(story,"しかしその後、");
            switch(LCSrandom(3))
            {
            case 0: strcat(story,"別の受刑者の自白"); break;
            case 1: strcat(story,"DNAの不一致"); break;
            case 2:
               strcat(story,dstr3);
               strcat(story,"に自白を強要したという警察官の告白");
               break;
            }
            strcat(story,"を含むいくつもの無罪を示す証拠が発見された。");
            strcat(story,"それにも関わらず刑は執行された。");
            strcat(story,"関係者は次のように話していたという。");
            strcat(story,"「");
            switch(LCSrandom(3))
            {
            case 0: strcat(story,"死刑囚が有色人種であることを忘れてはならない。彼らの性質は皆知っているはずだ。"); break;
            case 1:
               strcat(story,"死刑囚には常に3つの呼び名がある。");
               strcat(story,"暗殺者、連続殺人犯、いずれにせよ──有罪。");
               strcat(story,"もう終わったことだ。");
               break;
            case 2: strcat(story,"家族が終結を望んでいた。私たちには再審を待つ時間がない。"); break;
            }
            strcat(story,"」");
            strcat(story,"&r");
            strcat(story,"  死刑執行の日の夜、全米でろうそくを持った集会が行われ、本日の昼にも集会が予定されている。");
            strcat(story,"この悲劇に救いを見つけるとすれば、それは我々の国ではこのような人々は簡単に死刑になるということを知らしめたことだろう。");
            strcat(story,"&r");
            break;
         }
         case VIEW_INTELLIGENCE:
         {
            strcat(story,"ワシントン DC - 『FBIファイル』FBIはあなたを監視し続けている。");
            strcat(story,"我々の新聞社はFBI、連邦捜査局の情報源からいくつものファイルを受け取った。");
            strcat(story,"そのファイルには、デモ参加者、労働組合員、リベラル派団体のメンバー──");
            switch(LCSrandom(2))
            {
            case 0:strcat(story,"「不適切な歌詞」の歌の購入者"); break;
            case 1:strcat(story,"ホームレス支援者"); break;
            }
            strcat(story,"の情報さえ記載されていた。");
            strcat(story,"&r");
            strcat(story,"  さらに、はっきりとは書かれていないものの、「望ましくない者への対応」の計画も含まれていた。");
            strcat(story,"&r");
            strcat(story,"  当初FBIはコメントを避けたが、この情報を見ると");
            strcat(story,"「ええ。知っての通り、これは機密であり、そしてこれは機密だ。");
            strcat(story,"このファイルがある者を扱い、ある者を扱わないというのは憶測に過ぎない。");
            strcat(story,"告発者についてあれこれ言う前にこのことを考えた方がよい。」と述べた。");
            strcat(story,"&r");
            break;
         }
         case VIEW_FREESPEECH:
         {
            strcpy(story,cityname());
            strcat(story," - 『禁書指定』宗教団体の圧力を受け、市は図書館からある子供向けの本を撤去した。");
            strcat(story,"&r");
            strcat(story,"  その本は、有名な");
            switch(LCSrandom(11))
            {
            case 0: strcat(story,"イギリス"); break;
            case 1: strcat(story,"インド"); break;
            case 2: strcat(story,"中国"); break;
            case 3: strcat(story,"ルワンダ"); break;
            case 4: strcat(story,"パレスチナ"); break;
            case 5: strcat(story,"エジプト"); break;
            case 6: strcat(story,"フランス"); break;
            case 7: strcat(story,"ドイツ"); break;
            case 8: strcat(story,"イラク"); break;
            case 9: strcat(story,"ボリビア"); break;
            case 10: strcat(story,"コロンビア"); break;
            default: strcat(story,"エルボニア"); break; // Dilbert
            }
            strcat(story,"の作家、");
            char dstr[200],nstr[200];
            generate_name(nstr,dstr);
            char c[2]={0,0};
            c[0]='A'+LCSrandom(26);
            strcat(story,c);
            strcat(story,".");
            c[0]='A'+LCSrandom(26);
            strcat(story,c);
            lastname(dstr);
            strcat(story,dstr);
            strcat(story,"によるシリーズ3作目");
            strcat(story,"『");
            strcat(story,nstr);
            strcat(story,"・");
            strcat(story,dstr);
            strcat(story,"と");
            switch(LCSrandom(7))
            {
            case 0: strcat(story,"不思議な"); break;
            case 1: strcat(story,"魔法の"); break;
            case 2: strcat(story,"黄金の"); break;
            case 3: strcat(story,"見えない"); break;
            case 4: strcat(story,"素敵な"); break;
            case 5: strcat(story,"愉快な"); break;
            case 6: strcat(story,"秘密の"); break;
            }
            switch(LCSrandom(5))
            {
            case 0: strcat(story,"こと"); break;
            case 1: strcat(story,"もの"); break;
            case 2: strcat(story,"事"); break;
            case 3: strcat(story,"物"); break;
            case 4: strcat(story,"何か"); break;
            }
            strcat(story,"』だ。");
            strcat(story,"このシリーズは世界中の子供たちに愛読されているが、");
            strcat(story,"一部の保守派は");
            switch(LCSrandom(5))
            {
            case 0: strcat(story,"地獄の悪魔が書いた悪魔崇拝を称える"); break;
            case 1: strcat(story,"子供が両親を殺し人生を憎む"); break;
            case 2: strcat(story,"学校での暴力を助長し、コカイン使用への道を開く"); break;
            case 3: strcat(story,"殺人妄想を呼び起こす悪魔思想を植えつける"); break;
            case 4: strcat(story,"悪魔を呼び出す方法を教える"); break;
            }
            strcat(story,"本だと考えており、");
            switch(LCSrandom(3))
            {
            case 0: strcat(story,"クラスで罵った子供"); break;
            case 1: strcat(story,"両親の前で呪文を唱えた子供"); break;
            case 2:
               switch(LCSrandom(2))
               {
               case 0: strcat(story,"双子の"); break;
               }
               switch(LCSrandom(4))
               {
               case 0: strcat(story,"兄"); break;
               case 1: strcat(story,"姉"); break;
               case 2: strcat(story,"弟"); break;
               case 3: strcat(story,"妹"); break;
               }
               strcat(story,"を");
               switch(LCSrandom(5))
               {
               case 0: strcat(story,"押した"); break;
               case 1: strcat(story,"叩いた"); break;
               case 2: strcat(story,"打った"); break;
               case 3: strcat(story,"ばかにした"); break;
               case 4: strcat(story,"転ばせた"); break;
               }
               strcat(story,"子供");
               break;
            }
            strcat(story,"を含む事件がこの本の問題を示す証拠だと考えている。");
            strcat(story,"&r");
            strcat(story,"  昨日この本の撤去が通知されたとき、多くの子供が涙した。");
            strcat(story,"ある子供は「");
            switch(LCSrandom(2))
            {
            case 0:
               strcat(story,"ママ、");
               strcat(story,nstr);
               strcat(story,"は死んじゃったの? ");
               break;
            case 1:
               strcat(story,"ママ、どうして");
               strcat(story,nstr);
               strcat(story,"は殺されたの? ");
               break;
            }
            strcat(story,"」と尋ねていた。");
            strcat(story,"&r");
            break;
         }
         case VIEW_JUSTICES:
         {
            strcpy(story,cityname());
            strcat(story," - 『法廷侮辱』保守派の連邦裁判所判事");
            char dstr[200],dstr2[200];
            generate_name(dstr,dstr2,GENDER_WHITEMALEPATRIARCH);
            strcat(story,dstr);
            strcat(story,"・");
            strcat(story,"は");
            strcat(story,dstr2);
            if(law[LAW_FREESPEECH]==-2) strcat(story,"[市民の奉仕者]を買った件の責任を取り辞任した。");
            else strcat(story,"買春を行った件の責任を取り辞任した。");
            strcat(story,"&r");

            strcat(story,"  かつて");
            switch(LCSrandom(2))
            {
            case 0: strcat(story,"地方の連邦ビルに十戒のモニュメントを置いて連邦政府に反抗した"); break;
            case 1: strcat(story,"「人種的分離は近年誰もが認めるように悪い方法ではない」と述べた"); break;
            }
            strcat(story,dstr2);
            char pstr[200],pstr2[200];
            generate_name(pstr,pstr2);
            strcat(story,pstr);
            strcat(story,"・");
            strcat(story,pstr2);
            strcat(story,"は、先週ホテルにいるところをおとり捜査の警察官に発見された。");
            strcat(story,"関係者によると、ホテルの部屋に突入した警察官は");
            switch(LCSrandom(3))
            {
            case 0:strcat(story,"「2人でできることの中で、想像しうる限りで最も変質的な、背筋に悪寒が走るような放蕩」"); break;
            case 1:
               if(law[LAW_FREESPEECH]==-2)strcat(story,"判事の[市民への奉仕者]への[トイレで行うような行為]");
               else if(law[LAW_FREESPEECH]==2)strcat(story,"判事の売春婦への放尿");
               else strcat(story,"判事の売春婦への排出"); break; // Himself? Maybe themselves would work better? -- LK
            case 2:                                                                        // No, the judge is a white male Arch-Conservative patriarch. -- yetisyny
               if(law[LAW_FREESPEECH]==-2)strcat(story,"[市民への奉仕者]が判事の[近く]でカウボーイのように叫んでいるところ");
               else strcat(story,"売春婦が判事の上でカウボーイのように叫んでいるところ"); break;
            }
            strcat(story,"を目撃した。");
            strcat(story,"  伝えるところによると、");
            strcat(story,pstr2);
            strcat(story,"は警察官に対して黙秘の代わりに");
            switch(LCSrandom(3))
            {
            case 0: strcat(story,"金銭を渡そうとしていた"); break;
            case 1: strcat(story,"一緒に加わる提案をしていた"); break;
            case 2: strcat(story,"「好意」を渡そうとしていた"); break;
            }
            strcat(story,"。");
            strcat(story,"&r");
            strcat(story,"  ");
            strcat(story,dstr2);
            strcat(story,"からのコメントはまだないが、補佐官は数週間後のバイブル・リトリートには「全能の神が全てを解決して」参加できるだろうと述べた。");
            strcat(story,"&r");
            break;
         }
         case VIEW_AMRADIO:
         {
            strcpy(story,cityname());
            strcat(story," - 『AMラジオの内部崩壊』2日前の夜、よく知られたラジオ・パーソナリティ");
            char dstr[200],dstr2[200];
            generate_name(dstr,dstr2,GENDER_WHITEMALEPATRIARCH);
            strcat(story,dstr);
            strcat(story,"・");
            strcat(story,dstr2);
            strcat(story,"の意味不明な暴言により、全国放送のラジオ番組『");
            switch(LCSrandom(3))
            {
            case 0: strcat(story,"ストレート"); break;
            case 1: strcat(story,"リアル"); break;
            case 2: strcat(story,"トゥルー"); break;
            }
            switch(LCSrandom(3))
            {
            case 0: strcat(story,"トーク"); break;
            case 1: strcat(story,"チャット"); break;
            case 2: strcat(story,"ディスカッション"); break;
            }
            strcat(story,"』が15分間中断した。");
            strcat(story,"&r");
            strcat(story,"  ");
            strcat(story,dstr2);
            strcat(story,"のトークは視聴者の期待通りに");
            strcat(story,"「リベラルメディア」と「エリートリベラルアジェンダ」への攻撃から始まった。");
            strcat(story,"だが、「");
            switch(LCSrandom(4))
            {
            case 0: strcat(story,"そしてグレイがこの惑星を征服して全てが終わる。"); break;
            case 1: strcat(story,"リベラル・チュパカブラが私たちの血を山羊のように吸うのだ! 山羊のように! 山羊のように! "); break;
            case 2: strcat(story,"透明な棒が体を突き抜けるようだ…未来と愛し合うように。"); break;
            case 3:
               strcat(story,"そして人種的逆差別の最もよい例が");
               if(presparty!=CONSERVATIVE_PARTY) strcat(story,"今の大統領だ! "); // Limbaugh
               else strcat(story,"リベラルメディアだ! ");
               break;
            }
            strcat(story,"」と発言したとき、かつての番組のファン");
            char nstr[200],nstr2[200];
            generate_name(nstr,nstr2);
            strcat(story,nstr);
            strcat(story,"・");
            strcat(story,nstr2);
            strcat(story,"には「");
            switch(LCSrandom(3))
            {
            case 0:strcat(story,"古きヒーロー");break;
            case 1:strcat(story,"古きアイドル");break;
            case 2:strcat(story,"レジェンド");break;
            }
            strcat(story,"は");
            switch(LCSrandom(3))
            {
            case 0:
               strcat(story,"");
               strcat(story,""); // the AM personality's a white male patriarch

               if(law[LAW_FREESPEECH]==2)strcat(story,"気が狂っていた");
               else if(law[LAW_FREESPEECH]==-2)strcat(story,"気[に変調をきたしていた]");
               else strcat(story,"おかしくなっていた");
               break;
            case 1: strcat(story,"我を忘れていた"); break;
            case 2: strcat(story,"隣のアート・ベルの番組に少し長く聞き入ってたのだろう"); break;
            }
            strcat(story,"。そこからどんどん悪くなる。」ことがわかっていた。");
            strcat(story,"&r");
            strcat(story,"  ");
            strcat(story,dstr2);
            strcat(story,"は番組の後で謝罪したが、");
            strcat(story,"ダメージは避けられない。");
            strcat(story,"昨日の調査結果によると、");
            strcat(story,"熱心な視聴者の半数が");                    // XXX How many of them switch should
            strcat(story,"よりまともな番組を求めて去っていった。");                        //     depend on [LAW_FREESPEECH]
            strcat(story,"その内の大半は");
            strcat(story,"FM放送に切り替えると述べていた。");
            strcat(story,"&r");
            break;
         }
         case VIEW_GUNCONTROL:
         {
            int schtype = LCSrandom(4);
            strcpy(story,cityname());
            strcat(story," - 『乱射事件』地元の");
            switch(schtype)
            {
            case 0: strcat(story,"小学校の児童"); break;
            case 1: strcat(story,"中学校の生徒"); break;
            case 2: strcat(story,"高校の生徒"); break;
            case 3: strcat(story,"大学の学生"); break;
            }
            strcat(story,"が");
            if(law[LAW_FREESPEECH]==-2) strcat(story,"[恐ろしい騒ぎ]の犠牲となった");
            else strcat(story,"銃乱射事件の犠牲となった");
            strcat(story,"。");
            char jstr[200];
            lastname(jstr,true);
            strcat(story,jstr);
            switch(schtype)
            {
            case 0: strcat(story,"小学校の"); break;
            case 1: strcat(story,"中学校の"); break;
            case 2: strcat(story,"高校の"); break;
            case 3: strcat(story,"大学の"); break;
            }
            char dstr[200],dstr2[200],dg;
            dg = (LCSrandom(2)==1?GENDER_MALE:GENDER_FEMALE);
            generate_name(dstr,dstr2,dg);
            strcat(story,dstr);
            strcat(story,"・");
            strcat(story,dstr2);
            strcat(story,"(");
            //6->11,10->15,14->19,18->23
            strcat(story,6+(schtype*4)+LCSrandom(6)); //generate an age that would roughly correspond to the schtype
            strcat(story, "歳)は、何丁もの銃を使い同じ");
            switch(schtype)
            {
            case 0: strcat(story,"クラスの児童"); break;
            case 1:
            case 2: strcat(story,"クラスの生徒"); break;
            case 3: strcat(story,"学部の学生"); break;
            }
            strcat(story,"10人以上と");
            switch(schtype)
            {
            case 0:
            case 1:
            case 2: strcat(story,"教師"); break;
            case 3: strcat(story,"講師"); break;
            }
            strcat(story,"2人を");
            if(law[LAW_FREESPEECH]==-2)strcat(story,"[脅かした]");
            else strcat(story,"射殺した");
            strcat(story, "。");
            strcat(story,dstr2);
            strcat(story, "が");
            if(schtype!=3) strcat(story,"学校");
            else strcat(story,"大学");
            strcat(story, "に到着したのは授業の最中だった。その後、平然と教室に向かい、そこにいた");
            switch(schtype)
            {
            case 0: strcat(story,"児童と教師"); break;
            case 1:
            case 2: strcat(story,"生徒と教師"); break;
            case 3: strcat(story,"学生と講師"); break;
            }
            if(law[LAW_FREESPEECH]==-2) strcat(story,"を[脅かした]");
            else strcat(story,"に銃を乱射した");
            strcat(story,"。");
            strcat(story,"銃を取り上げようとした");
            switch(schtype)
            {
            case 0: strcat(story,"児童"); break;
            case 1:
            case 2: strcat(story,"生徒"); break;
            case 3: strcat(story,"学生"); break;
            }
            strcat(story,"もいたが、同じように");
            if(law[LAW_FREESPEECH]==-2) strcat(story,"[傷つけられた]");
            else strcat(story,"撃たれた。");
            strcat(story,"。&r");
            strcat(story, "  警察官が駆けつけたとき、既に");
            if(law[LAW_FREESPEECH]==-2) strcat(story, "[多数が傷つけられていた]。");
            else
            {
               strcat(story, 2+LCSrandom(30));
               strcat(story, "人が死亡し、");
               strcat(story, "10以上が負傷していた。");
            }
            strcat(story,dstr);
            strcat(story, "はその後まもなく");
            if(law[LAW_FREESPEECH]==-2)strcat(story, "[深い眠りについた]");
            else strcat(story, "自殺した");
            strcat(story,"。&r");
            strcat(story,"  捜査当局は現在");
            switch(schtype)
            {
            case 0: strcat(story,"児童"); break;
            case 1:
            case 2: strcat(story,"生徒"); break;
            case 3: strcat(story,"学生"); break;
            }
            strcat(story,"の遺留品を調査中だが、日記に銃と死への強い関心をうかがわせる記述があるとの発表があった。&r");
            break;
         }
         case VIEW_PRISONS:
         {
            strcpy(story,cityname());
            strcat(story," - 『内側の実情』元受刑者が鉄格子の向こう側の恐るべき実態を詳細に描いた本を書いた。");
            strcat(story,"刑務所の話は大量に提供され大量に消費されてきたが、");
            char dstr[200],dstr2[200];
            generate_name(dstr,dstr2); // allow either gender (look up "Orange is the New Black" online to see why)
            strcat(story,dstr);
            strcat(story,"・");
            strcat(story,dstr2);
            strcat(story,"の力作『");
            switch(LCSrandom(6))
            {
            case 0: strcat(story,"悪夢"); break;
            case 1: strcat(story,"本能"); break;
            case 2: strcat(story,"野獣"); break;
            case 3: strcat(story,"アメリカ"); break;
            case 4: strcat(story,"孤独"); break;
            case 5: strcat(story,"苦痛"); break;//Painful Soap, anyone?
            }
            strcat(story,"の");
            switch(LCSrandom(8))
            {
            case 0: strcat(story,"箱"); break;
            case 1: strcat(story,"石鹸"); break;//Nightmare Soap, anyone?
            case 2: strcat(story,"パンク"); break;
            case 3: strcat(story,"子供"); break;
            case 4: strcat(story,"牢"); break;
            case 5: strcat(story,"シャンク"); break;
            case 6: strcat(story,"封鎖"); break;
            case 7:
               if(law[LAW_FREESPEECH]==-2) strcat(story,"傲慢");
               else strcat(story,"傲慢"); break;
            case 8:strcat(story,"シャワー"); break;
            }
            strcat(story,"』ほど強烈なものはない。&r");
            strcat(story,"  一部を紹介する。「");//TODO: Add more excerpts, more variety.
            strcat(story,"鉄格子が目の前にあり、ガチャンという大きな音がした");
            strcat(story,"──私は今、そこに捕らわれたのだ。フットボール選手のような3人が");
            strcat(story,"暗い欲望をむき出しにした眼差しで、呆然とした、酔っ払いの、なすすべのない10代を見つめていた。");
            strcat(story,"私はマットレスに押さえつけられた。勇敢に戦うか、それとも怖気づいてなされるままにするか? ");
            strcat(story,"一方は片目を失い、もう一方は");
            if(law[LAW_GAY]==-2)strcat(story,"GRIDS(ゲイ関連免疫不全症候群)");// Gay Related Immunodeficiency Syndrome, an obsoleted/politically incorrect name for "AIDS".
            else strcat(story,"AIDS");
            strcat(story,"に感染するだろう。");
            if(law[LAW_FREESPEECH]==-2)strcat(story,"[難しい]");
            else strcat(story,"ろくでもない");
            strcat(story,"選択肢だ。だがあと数秒で決断しなければならない。");
            strcat(story,"」");
            strcat(story,"&r");
            break;
         }
      }
   }
   else
   {
      switch(view)
      {
         case VIEW_DEATHPENALTY:
         {
            strcpy(story,cityname());
            strcat(story," - 『奴らを吊るせ』昨夜は両親もよく眠れただろう。");
            strcat(story,"発表によると、警察は地域を不安に陥れていた子供を狙った連続殺人の有力な容疑者を逮捕した。");
            char dstr[200],dstr2[200],dstr3[200];
            generate_long_name(dstr,dstr2,dstr3);
            strcat(story,dstr);
            strcat(story,"・");
            strcat(story,dstr2);
            strcat(story,"・");
            strcat(story,dstr3);
            strcat(story,"が昨日の午後に拘束されたとき、");
            switch(LCSrandom(5))
            {
            case 0: strcat(story,"他の被害者の一部"); break;
            case 1: strcat(story,"血まみれのオモチャ"); break;
            case 2: strcat(story,"子供のDNAが付着した服"); break;
            case 3: strcat(story,"中学校の卒業アルバム7冊"); break;
            case 4: strcat(story,"小さな荷物2つ"); break;
            }
            strcat(story,"を持っていた。");
            strcat(story,"この2年間で20人以上の子供が行方不明になり、その後");
            if(law[LAW_FREESPEECH]==-2)
               strcat(story,"[よい状態で]発見されていた");
            else
            {
               switch(LCSrandom(5))
               {
               case 0: strcat(story,"悪魔の印が彫られた"); break;
               case 1: strcat(story,"性的暴行を受けた"); break;
               case 2: strcat(story,"歯を抜き取られた"); break;
               case 3: strcat(story,"指を全て切り落とされた"); break;
               case 4: strcat(story,"目を失った"); break;
               }
               strcat(story,"遺体となって発見されていた");
            }
            strcat(story,"。情報筋によると、");
            switch(LCSrandom(5))
            {
            case 0: strcat(story,"殺害される直前の被害者が警察に通報した"); break;
            case 1: strcat(story,"容疑者が遺体に住所のようなものを刻んでいた"); break;
            case 2: strcat(story,"容疑者が被害者を車に誘っているところを通行人が目撃した"); break;
            case 3: strcat(story,"血の跡が容疑者の車のトランクに続いていた"); break;
            case 4: strcat(story,"水路で発見された被害者が生存していた"); break;
            }
            strcat(story,"ことが逮捕のきっかけとなった。");
            strcat(story,"&r");
            strcat(story,"  検察は既にこの事件について");
            if(law[LAW_DEATHPENALTY]==2)
               strcat(story,"終身刑");
            else
               strcat(story,"死刑");
            strcat(story,"を求めることを表明している。");
            strcat(story,"&r");
            break;
         }
         case VIEW_ANIMALRESEARCH:
         {
            strcpy(story,cityname());
            strcat(story," - 『猿で動物実験』");
            if(law[LAW_ANIMALRESEARCH]==2)
            {
               switch(LCSrandom(5))
               {
               case 0:strcat(story,"ロシア");break;
               case 1:strcat(story,"北朝鮮");break;
               case 2:strcat(story,"キューバ");break;
               case 3:strcat(story,"イラン");break;
               case 4:strcat(story,"中国");break;
               }
               strcat(story,"の");
            }
            strcat(story,"研究者たちが素晴らしい新薬を開発した。");
            switch(LCSrandom(5))
            {
            case 0:
               if(law[LAW_FREESPEECH]==-2)strcat(story,"シリ");
               else strcat(story,"アナル");break;
            case 1:strcat(story,"コロ");break;
            case 2:strcat(story,"ラクタ");break;
            case 3:strcat(story,"パー");break;
            case 4:strcat(story,"ローバ");break;
            }
            switch(LCSrandom(5))
            {
            case 0:strcat(story,"ネフリン");break;
            case 1:strcat(story,"タックス");break;
            case 2:strcat(story,"ザック");break;
            case 3:strcat(story,"チウム");break;
            case 4:strcat(story,"ドレネ");break;
            }
            strcat(story,"と呼ばれるこの薬は、");
            switch(LCSrandom(5))
            {
            case 0:strcat(story,"チンパンジーの知能を増幅させた");break;
            case 1:
               if(law[LAW_FREESPEECH]==-2)strcat(story,"[チンパンジーの生殖を助けた]");
               else strcat(story,"チンパンジーの勃起不全を治した");break;
            case 2:strcat(story,"チンパンジーが念力でブロックを動かせるようにした");break;
            case 3:strcat(story,"チンパンジーが短距離を飛べるようにした");break;
            case 4:strcat(story,"若いチンパンジーの集中力を増幅させた");break;
            }
            strcat(story,"ということだ。");
            strcat(story,"&r");
            strcat(story,"  ボノボと同様にチンパンジーは我々と最も近いいとこのような種だ。");
            strcat(story,"昨日の会見では実験の倫理的問題を問う記者がいたが、");
            strcat(story,"研究チームの広報官はこう答えた。「大きな問題はありません。チンパンジーは回復力の高い生き物です。");
            switch(LCSrandom(3))
            {
            case 0:strcat(story,"生き残ったものは皆元気です");break;
            case 1:strcat(story,"素早く行えば、脳を取り出されたことにも気づきません");break;
            case 2:strcat(story,"研究対象の悲鳴を消すと、他のチンパンジーはとても落ち着いていました");break;
            }
            strcat(story,"。我々はとても経験のある研究チームです。");
            strcat(story,"あなたの懸念は理解できますが、根拠のないものです。");
            strcat(story,"メディアはこの新薬がもたらす莫大な恩恵に注目すべきと考えます。");
            strcat(story,"」");
            strcat(story,"&r");
            strcat(story,"  人間を対象とした最初の段階の試験は数ヵ月後に始まる予定だ。");
            strcat(story,"&r");
            break;
         }
         case VIEW_INTELLIGENCE:
         {
            strcat(story,"ワシントン DC - 『惨事を回避』昨日、CIAはアメリカ本土で発生する可能性のあったテロを回避したと発表した。");
            strcat(story,"&r");
            strcat(story,"  広報官によると、");
            switch(LCSrandom(3))
            {
            case 0:strcat(story,"白人至上主義者が");break;
            case 1:strcat(story,"イスラム教原理主義者が");break;
            case 2:strcat(story,"地方の高校でのけ者にされたゴスが");break;
            }
            switch(LCSrandom(9))
            {
            case 0:
               if(law[LAW_FREESPEECH]==-2)strcat(story,"[アパートに向かって]飛行機を[離陸させる]");
               else strcat(story,"高層ビルに向かって飛行機を飛ばす");break;
            case 1:
               if(law[LAW_FREESPEECH]==-2)strcat(story,"連邦政府ビルで肥料[を植物に][与える]");
               else strcat(story,"連邦政府ビルで肥料爆弾を爆発させる");break;
            case 2:
               if(law[LAW_FREESPEECH]==-2)strcat(story,"[招かざる客]を軍艦に[見せつける]");
               else strcat(story,"爆発物を積んだモーターボートを軍艦に突入させる");break;
            case 3:
               if(law[LAW_FREESPEECH]==-2)strcat(story,"[子供にブーブーを与える]");
               else strcat(story,"スクールバスに爆発物をしかける");break;
            case 4:
               if(law[LAW_FREESPEECH]==-2)strcat(story,"主要な橋[で交通渋滞を引き起こす]");
               else strcat(story,"主要な橋の一部を吹き飛ばす");break;
            case 5:
               if(law[LAW_FREESPEECH]==-2)strcat(story,"大統領を[バケーションに連れ出す]");
               else strcat(story,"大統領を誘拐する");break;
            case 6:
               if(law[LAW_FREESPEECH]==-2)strcat(story,"大統領を[傷つける]");
               else strcat(story,"大統領を暗殺する");break;
            case 7:
               if(law[LAW_FREESPEECH]==-2)strcat(story,"議会議事堂を[荒らす]");
               else strcat(story,"議会議事堂を爆破する");break;
            case 8:
               if(law[LAW_FREESPEECH]==-2)strcat(story,"ニューヨークに[花火]をしかける");
               else strcat(story,"ニューヨークに核爆弾をしかける");break;
            }
            strcat(story,"計画があったが、収集した膨大な情報を元に実行の数日前に阻止することができた。");
            strcat(story,"&r");
            strcat(story,"  広報官はさらに述べた。「");
            strcat(story,"情報源と方法は言えないが、市民の敵がアメリカの家族に危害を加えるまえに無力化する協力をしてくれた連邦議会とその議長に感謝したい。");
            strcat(story,"しかし、まだやらなければならないことは他にもある。");
            strcat(story,"CIAは新たな時代のテロリズムと戦うため、さらなる協力について議会に要求を送るつもりだ。");
            strcat(story,"」");
            strcat(story,"&r");
            break;
         }
         case VIEW_GENETICS:
         {
            strcpy(story,cityname());
            strcat(story," - 『組み替え食品への不干渉』昨日、遺伝子組み換え食品産業界が近日発売される商品のための大きなイベントを開催した。");
            strcat(story,"30以上の企業がブースを構え、興味を持つ参加者と対話した。");
            strcat(story,"&r");
            strcat(story,"  参加企業の1つ、");
            switch(LCSrandom(5))
            {
            case 0:strcat(story,"アルタード・");break;
            case 1:strcat(story,"ジェネテック・");break;
            case 2:strcat(story,"DNA ");break;
            case 3:strcat(story,"プロテオミック・");break;
            case 4:strcat(story,"ゲノミック・");break;
            }
            switch(LCSrandom(5))
            {
            case 0:strcat(story,"フーズ");break;
            case 1:strcat(story,"アグリカルチャー");break;
            case 2:strcat(story,"ミール");break;
            case 3:strcat(story,"ファーム");break;
            case 4:strcat(story,"リビング");break;
            }
            strcat(story,"は、午後に自社の製品『");
            switch(LCSrandom(5))
            {
            case 0:strcat(story,"メガ");break;
            case 1:strcat(story,"壮大");break;
            case 2:strcat(story,"大王");break;
            case 3:strcat(story,"フランケン");break;
            case 4:strcat(story,"超");break;
            }
            switch(LCSrandom(5))
            {
            case 0:strcat(story,"米");break;
            case 1:strcat(story,"豆");break;
            case 2:strcat(story,"トウモロコシ");break;
            case 3:strcat(story,"小麦");break;
            case 4:strcat(story,"ジャガイモ");break;
            }
            strcat(story,"』をPowerPointでプレゼンテーションした。");
            strcat(story,"広報担当者によると、");
            strcat(story,"この素晴らしい製品は");
            switch(LCSrandom(5))
            {
            case 0:strcat(story,"一口ごとに寿命を数分延ばす");break;
            case 1:strcat(story,"消化すると枝毛が直り、髪もつややかで量が増す");break;
            case 2:strcat(story,"暗闇の中でも物が見えるようになる");break;
            case 3:strcat(story,"常食すると緩やかに最適体重に近づく");break;
            case 4:strcat(story,"カゼを治す");break;
            }
            strcat(story,"ということだ。");
            strcat(story,"&r");
            strcat(story,"  広報担当者たちは業界に寄せられる安全性への疑念をいつもどおり一蹴した。");
            strcat(story,"ある人物はこう言った。「");
            strcat(story,"見てください。これらの製品は安全です。これで");
            switch(LCSrandom(4))
            {
            case 0:strcat(story,"暴れて人を殺す");break;
            case 1:strcat(story,"青くなって爆発する");break;
            case 2:strcat(story,"謎の言葉で話し出しサタンを崇拝する");break;
            case 3:strcat(story,"腸が破裂する");break;
            }
            strcat(story,"というのは全く");
            if(law[LAW_FREESPEECH]==-2) switch(LCSrandom(5))
            {
            case 0:strcat(story,"バカげた話");break;
            case 1:strcat(story,"のたわ言");break;
            case 2:strcat(story,"ホースラディッシュみたいな話");break;
            case 3:strcat(story,"スカンクウィードみたいな話");break;
            case 4:strcat(story,"ゴミみたいな話");break;
            }
            else switch(LCSrandom(3))
            {
            case 0:strcat(story,"馬のクソみたいな話");break; // McCain
            case 1:strcat(story,"牛のクソみたいな話");break;
            case 2:strcat(story,"クソみたいな話");break;
            }
            strcat(story,"です。私たちの企業は危険な製品を売っていると非難されなければならないのでしょうか? ");
            strcat(story,"いいえ。それはバカげています。確かに危険性はありますが、");
            strcat(story,"業界団体は高い倫理基準で活動しています。それは言うまでもありません。");
            strcat(story,"」");
            strcat(story,"&r");
            break;
         }
         case VIEW_JUSTICES:
         {
            strcpy(story,cityname());
            strcat(story," - 『司法の混乱』昨日、自白した連続殺人犯");
            char dstr[200],dstr2[200],dstr3[200];
            generate_long_name(dstr,dstr2,dstr3);
            strcat(story,dstr);
            strcat(story,"・");
            strcat(story,dstr2);
            strcat(story,"・");
            strcat(story,dstr3);
            strcat(story,"の有罪判決が連邦裁判所で覆された。");
            strcat(story,"悪名高い控訴裁判所のリベラル派");
            char jstr[200],jstr2[200];
            char gn=(LCSrandom(2)==1?GENDER_MALE:GENDER_FEMALE);
            generate_name(jstr,jstr2,gn);
            strcat(story,jstr);
            strcat(story,"・");
            strcat(story,jstr2);
            strcat(story,"判事は、");
            strcat(story,dstr3);
            strcat(story,"の自白が強要されたものでないと認められたにも関わらず、");
            char gen[20];
            strcpy(gen,(gn==GENDER_FEMALE?"彼女":"彼"));
            switch(LCSrandom(7))
            {
            case 0:strcat(story,"10歳の目撃証言");break;
            case 1:strcat(story,gen);strcat(story,"の警察の腐敗に対する感情");break;
            case 2:strcat(story,gen);strcat(story,"犯罪は巨大な右翼集団によるものだという信念");break; // Clinton
            case 3:
               strcat(story,gen);
               strcat(story,"の");
               strcat(story,dstr3);
               strcat(story,"に再起の機会を与えるべきという信念");
               break;
            case 4:
               strcat(story,gen);
               strcat(story,"の個人的なリベラル的信念");break;
            case 5:
               strcat(story,gen);
               strcat(story,"が");
               strcat(story,dstr3);                       // I know Charles Manson.
               strcat(story,"の家族と親しいということ");  // Charles Manson was a friend of mine.
               break;                                     // And you, sir, are no Charles Manson!
            case 6:strcat(story,gen);strcat(story,"マジック・エイトの占いの結果");break;
            }
            strcat(story,"を元に判決を下した。&r");

            strcat(story,"  10年前、");
            strcat(story,dstr3);
            strcat(story,"は");
            char sstr[200];
            lastname(sstr);
            strcat(story,sstr);
            strcat(story,"殺害で有罪となった。");
            strcat(story,"徹底した探索の結果、犠牲者の血の付いた凶器を持った");
            strcat(story,dstr3);
            strcat(story,"が発見された。");
            strcat(story,dstr3);
            strcat(story,"は罪を認め終身刑となったが、こう述べた。");
            strcat(story,"「これで助かった。");
            strcat(story,"もし刑務所を出たら、また人を殺してしまうだろう。」&r");
            strcat(story,"弁護側は、現在の経済不振による資金不足で、州は再審を要求しないだろうと述べた。&r");
            break;
         }
         case VIEW_POLLUTION:
            strcpy(story,cityname());
            strcat(story," - Pollution might not be so bad after all.  The ");
            switch(LCSrandom(6))
            {
            case 0:strcat(story,"American");break;
            case 1:strcat(story,"United");break;
            case 2:strcat(story,"Patriot");break;
            case 3:strcat(story,"Family");break;
            case 4:strcat(story,"Children's");break;
            case 5:strcat(story,"National");break;
            }
            strcat(story," ");
            switch(LCSrandom(6))
            {
            case 0:strcat(story,"Heritage");break;
            case 1:strcat(story,"Enterprise");break;
            case 2:strcat(story,"Freedom");break;
            case 3:strcat(story,"Liberty");break;
            case 4:strcat(story,"Charity");break;
            case 5:strcat(story,"Equality");break;
            }
            strcat(story," ");
            switch(LCSrandom(6))
            {
            case 0:strcat(story,"Partnership");break;
            case 1:strcat(story,"Institute");break;
            case 2:strcat(story,"Consortium");break;
            case 3:strcat(story,"Forum");break;
            case 4:strcat(story,"Center");break;
            case 5:strcat(story,"Association");break;
            }
            strcat(story," recently released a wide-ranging report detailing recent trends ");
            strcat(story,"and the latest science on the issue.  ");
            strcat(story,"Among the most startling of the think tank's findings is that ");
            switch(LCSrandom(6))
            {
            case 0:strcat(story,"a modest intake of radioactive waste");break;
            case 1:strcat(story,"a healthy dose of radiation");break;
            case 2:strcat(story,"a bath in raw sewage");break;
            case 3:strcat(story,"watching animals die in oil slicks");break;
            case 4:strcat(story,"inhaling carbon monoxide");break;
            case 5:strcat(story,"drinking a cup of fracking fluid a day");break;
            }
            strcat(story," might actually ");
            switch(LCSrandom(6))
            {
            case 0:strcat(story,"purify the soul");break;
            case 1:strcat(story,"increase test scores");break;
            case 2:strcat(story,"increase a child's attention span");break;
            case 3:strcat(story,"make children behave better");break;
            case 4:strcat(story,"make shy children fit in");break;
            case 5:strcat(story,"cure everything from abdominal ailments to zygomycosis");break;
            }
            strcat(story,".");
            strcat(story,"&r");
            strcat(story,"   When questioned about the science behind these results, ");
            strcat(story,"a spokesperson stated that, \"");
            switch(LCSrandom(4))
            {
            case 0:strcat(story,"Research is complicated, and there are always two ways to think about things");break;
            case 1:strcat(story,"The jury is still out on pollution.  You really have to keep an open mind");break;
            case 2:strcat(story,"They've got their scientists, and we have ours.  The issue of pollution is wide open as it stands today");break;
            case 3:strcat(story,"I just tried it myself and I feel like a million bucks!  *Coughs up blood*  I'm OK, that's just ketchup");break;
            }
            strcat(story,".  You have to realize that ");
            switch(LCSrandom(4))
            {
            case 0:strcat(story,"the elitist liberal media often distorts");break;
            case 1:strcat(story,"the vast left-wing education machine often distorts");break;
            case 2:strcat(story,"the fruits, nuts, and flakes of the environmentalist left often distort");break;
            case 3:strcat(story,"leftists suffering from the mental disorder chemophobia often distort");break;
            }
            strcat(story," these issues to their own advantage.  ");
            strcat(story,"All we've done is introduced a little clarity into the ongoing debate.  ");
            strcat(story,"Why is there contention on the pollution question?  It's because ");
            strcat(story,"there's work left to be done.  We should study much more ");
            strcat(story,"before we urge any action.  Society really just ");
            strcat(story,"needs to take a breather on this one.  We don't see why there's such a rush to judgment here.  ");
            strcat(story,"&r");
            break;
         case VIEW_CORPORATECULTURE:
            strcpy(story,cityname());
            strcat(story," - Several major companies have announced ");
            strcat(story,"at a joint news conference here that they ");
            strcat(story,"will be expanding their work forces considerably ");
            strcat(story,"during the next quarter.  Over thirty thousand jobs ");
            strcat(story,"are expected in the first month, with ");
            strcat(story,"tech giant ");
            switch(LCSrandom(10))
            {
            case 0:strcat(story,"Ameri");break;
            case 1:strcat(story,"Gen");break;
            case 2:strcat(story,"Oro");break;
            case 3:strcat(story,"Amelia");break;
            case 4:strcat(story,"Vivo");break;
            case 5:strcat(story,"Benji");break;
            case 6:strcat(story,"Amal");break;
            case 7:strcat(story,"Ply");break;
            case 8:strcat(story,"Seli");break;
            case 9:strcat(story,"Rio");break;
            }
            switch(LCSrandom(10))
            {
            case 0:strcat(story,"tech");break;
            case 1:strcat(story,"com");break;
            case 2:strcat(story,"zap");break;
            case 3:strcat(story,"cor");break;
            case 4:strcat(story,"dyne");break;
            case 5:strcat(story,"bless");break;
            case 6:strcat(story,"chip");break;
            case 7:strcat(story,"co");break;
            case 8:strcat(story,"wire");break;
            case 9:strcat(story,"rex");break;
            }
            strcat(story," increasing its payrolls by over ten thousand workers alone.  ");
            strcat(story,"Given the state of the economy recently and in ");
            strcat(story,"light of the tendency ");
            strcat(story,"of large corporations to export jobs overseas these days, ");
            strcat(story,"this welcome news is bound to be a pleasant surprise to those in the unemployment lines.  ");
            strcat(story,"The markets reportedly responded to the announcement with mild interest, ");
            strcat(story,"although the dampened movement might be expected due to the uncertain ");
            strcat(story,"futures of some of the companies in the tech sector.  On the whole, however, ");
            strcat(story,"analysts suggest that not only does the expansion speak to the health ");
            strcat(story,"of the tech industry but is also indicative of a full economic recover.&r");
            break;
         case VIEW_AMRADIO:
         {  //THIS ONE IS SHORTER BECAUSE OF DOUBLE HEADLINE
            strcpy(story,cityname());
            strcat(story," - Infamous FM radio shock jock ");
            char dstr[200],dstr2[200];
            generate_name(dstr,dstr2,GENDER_WHITEMALEPATRIARCH);
            strcat(story,dstr);
            strcat(story," ");
            strcat(story,dstr2);
            strcat(story," has brought radio entertainment to a new low.  During yesterday's ");
            strcat(story,"broadcast of the program \"");
            strcat(story,dstr);
            strcat(story,"'s ");
            switch(LCSrandom(5))
            {
            case 0:strcat(story,"Morning");break;
            case 1:strcat(story,"Commuter");break;
            case 2:strcat(story,"Jam");break;
            case 3:strcat(story,"Talk");break;
            case 4:strcat(story,"Radio");break;
            }
            strcat(story," ");
            switch(LCSrandom(5))
            {
            case 0:strcat(story,"Swamp");break;
            case 1:strcat(story,"Jolt");break;
            case 2:strcat(story,"Club");break;
            case 3:strcat(story,"Show");break;
            case 4:strcat(story,"Fandango");break;
            }
            strcat(story,"\", ");
            strcat(story,dstr2);
            strcat(story," reportedly ");
            switch(LCSrandom(5))
            {
            case 0:
               if(law[LAW_FREESPEECH]==-2)strcat(story,"[had consensual intercourse in the missionary position]");
               else if(law[LAW_FREESPEECH]==2)strcat(story,"fucked");
               else strcat(story,"had intercourse");break;
            case 1:
               if(law[LAW_FREESPEECH]==-2)strcat(story,"encouraged listeners to call in and [urinate]");
               else if(law[LAW_FREESPEECH]==2)strcat(story,"encouraged listeners to call in and take a piss");
               else strcat(story,"encouraged listeners to call in and relieve themselves");break;
            case 2:
               if(law[LAW_FREESPEECH]==2)strcat(story,"screamed \"fuck the police those goddamn motherfuckers.  I got a fucking ticket this morning and I'm fucking pissed as shit.\"");
               else if(law[LAW_FREESPEECH]==-2)strcat(story,"screamed \"[darn] the police those [big dumb jerks]. I got a [stupid] ticket this morning and I'm [so angry].\"");
               else strcat(story,"screamed \"f*ck the police those g*dd*mn m*th*f*ck*rs.  I got a f*cking ticket this morning and I'm f*cking p*ss*d as sh*t.\"");break;
            case 3:
               if(law[LAW_FREESPEECH]==-2 && law[LAW_WOMEN]==-2)strcat(story,"[fed] from [an indecent] woman");
               else if(law[LAW_FREESPEECH]!=-2 && law[LAW_WOMEN]==-2)strcat(story,"breastfed from an exposed woman");
               else if(law[LAW_FREESPEECH]==-2 && law[LAW_WOMEN]!=-2)strcat(story,"[fed] from a [woman]");
               else strcat(story,"breastfed from a lactating woman");break;
            case 4:
               if(law[LAW_FREESPEECH]==-2)strcat(story,"[had fun]");
               else strcat(story,"masturbated");break;
            }
            strcat(story," on the air.  Although ");
            strcat(story,dstr2);
            strcat(story," later apologized, ");
            strcat(story,"the FCC received ");
            if(law[LAW_FREESPEECH]==-2) strcat(story,"thousands of");
            else if(law[LAW_FREESPEECH]==-1) strcat(story,"several hundred");
            else if(law[LAW_FREESPEECH]==0) strcat(story,"hundreds of");
            else if(law[LAW_FREESPEECH]==1) strcat(story,"dozens of");
            else strcat(story,"some");
            strcat(story," complaints ");
            strcat(story,"from irate listeners ");
            if(law[LAW_FREESPEECH]==-2) strcat(story,"across the nation. ");
            else if(law[LAW_FREESPEECH]==-1) strcat(story,"from all over the state. ");
            else if(law[LAW_FREESPEECH]==0) strcat(story,"within the county. ");
            else if(law[LAW_FREESPEECH]==1) strcat(story,"in neighboring towns. ");
            else strcat(story,"within the town. ");
            strcat(story," A spokesperson for the FCC ");
            strcat(story,"stated that the incident is under investigation.");
            strcat(story,"&r");
            break;
         }
         case VIEW_GUNCONTROL:
         {
            strcpy(story,cityname());
            char jstr[200],jstr2[200],jstr3[200],jstr4[200],jstr5[200],jg1,jg2,tg2[10];
            jg1=(LCSrandom(2)?GENDER_MALE:GENDER_FEMALE);
            jg2=(LCSrandom(2)?GENDER_MALE:GENDER_FEMALE);
            generate_long_name(jstr,jstr2,jstr3,jg1);
            generate_name(jstr4,jstr5,jg2);
            strcat(story," - In a surprising turn, a ");
            if (law[LAW_FREESPEECH]==-2) strcat(story, "[hurting spree]"); else strcat(story,"mass shooting");
            strcat(story," was prevented by a bystander with a gun.");
            strcat(story," After ");
            strcat(story,jstr);
            strcat(story," ");
            strcat(story,jstr2);
            strcat(story," opened fire at the ");
            strcat(story,jstr3);
            switch(LCSrandom(4))
            {
            case 0:strcat(story," Mall");break;
            case 1:strcat(story," Theater");break;
            case 2:strcat(story," High School");break;
            case 3:strcat(story," University");break;
            }
            strcat(story,", ");
            strcat(story,jstr4);
            strcat(story," ");
            strcat(story,jstr5);
            strcat(story," sprung into action. ");
            strcat(story,"The citizen pulled a concealed handgun and fired once at the shooter, ");
            strcat(story,"forcing ");
            strcat(story,jstr2);
            strcat(story," to take cover while others called the police.&r");
            strcat(story,"  Initially, ");
            if(jg2==GENDER_FEMALE)
            {
               if(LCSrandom(4)<law[LAW_WOMEN]+2) // 0% chance at law[LAW_WOMEN]==-2, 100% chance at law[LAW_WOMEN]==2
                  strcpy(tg2,"Ms. ");
               else
                  strcpy(tg2,(LCSrandom(2)?"Mrs. ":"Miss "));
            }
            else strcpy(tg2,"Mr. ");
            strcat(story,tg2);
            strcat(story,jstr5);
            strcat(story," attempted to talk down the shooter, but as ");
            strcat(story,jstr2);
            strcat(story," became more agitated, the heroic citizen was forced to engage the shooter in a ");
            if(law[LAW_FREESPEECH]==-2) strcat(story, "firefight, [putting the attacker to sleep] ");
            else strcat(story,"firefight, killing the attacker ");
            strcat(story,"before ");
            strcat(story,(jg1==GENDER_FEMALE?"she ":"he "));
            strcat(story,"could hurt anyone else.&r");
            strcat(story,"  The spokesperson for the police department said, \"We'd have a yet another ");
            if(law[LAW_FREESPEECH]==-2) strcat(story,"[hurting spree]");
            else strcat(story,"mass shooting");
            strcat(story," if not for ");
            strcat(story,tg2);
            strcat(story,jstr5);
            strcat(story,"'s heroic actions.\"");
            break;
         }
         case VIEW_PRISONS:
         {
            strcpy(story,cityname());
            strcat(story," - The hostage crisis at the ");
            char jstr[200];
            lastname(jstr,true);
            strcat(story,jstr);
            strcat(story," Correctional Facility ended tragically yesterday with the ");
            strcat(story,"death of both the prison guard being held hostage and ");
            char ggn=(LCSrandom(2)==1?GENDER_MALE:GENDER_FEMALE);
            strcat(story,(ggn==GENDER_FEMALE?"her":"his"));
            strcat(story," captor.");
            strcat(story,"&r");
            if(law[LAW_FREESPEECH]==-2)strcat(story,"   Two weeks ago, convicted [reproduction fiend] ");
            else strcat(story,"   Two weeks ago, convicted rapist ");
            char dstr[200],dstr2[200];
            char dgn=(LCSrandom(2)==1?GENDER_MALE:GENDER_FEMALE);
            generate_name(dstr,dstr2,dgn);
            strcat(story,dstr);
            strcat(story," ");
            strcat(story,dstr2);
            strcat(story,", an inmate at ");
            strcat(story,jstr);
            strcat(story,", overpowered ");
            char gstr[200],gstr2[200];
            generate_name(gstr,gstr2,ggn);
            strcat(story,gstr);
            strcat(story," ");
            strcat(story,gstr2);
            strcat(story," and barricaded ");
            strcat(story,(dgn==GENDER_FEMALE?"herself":"himself"));
            strcat(story," with the guard in a prison tower.  ");
            strcat(story,"Authorities locked down the prison and ");
            strcat(story,"attempted to negotiate by phone for ");
            strcat(story,LCSrandom(18)+5);
            strcat(story," days, but talks were cut short when ");
            strcat(story,dstr2);
            strcat(story," reportedly screamed into the receiver \"");
            switch(LCSrandom(4))
            {
            case 0:
               if(law[LAW_FREESPEECH]==2)strcat(story,"Ah, fuck this shit.  This punk bitch is fuckin' dead!");
               else if(law[LAW_FREESPEECH]==-2)strcat(story,"Ah, [no way.]  This [police officer will be harmed!]");
               else strcat(story,"Ah, f*ck this sh*t.  This punk b*tch is f*ckin' dead!");
               break;
            case 1:
               if(law[LAW_FREESPEECH]==2)strcat(story,"Fuck a muthafuckin' bull.  I'm killin' this pig shit.");
               else if(law[LAW_FREESPEECH]==-2)strcat(story,"[Too late.]  [I am going to harm this police officer.]");
               else strcat(story,"F*ck a m*th*f*ck*n' bull.  I'm killin' this pig sh*t.");
               break;
            case 2:
               if(law[LAW_FREESPEECH]==2)strcat(story,"Why the fuck am I talkin' to you?  I'd rather kill this pig.");
               else if(law[LAW_FREESPEECH]==-2)strcat(story,"Why [am I] talkin' to you?  I'd rather [harm this police officer.]");
               else strcat(story,"Why the f*ck am I talkin' to you?  I'd rather kill this pig.");
               break;
             case 3:
               if(law[LAW_FREESPEECH]==2)strcat(story,"Imma kill all you bitches, startin' with this mothafucker here.");
               else if(law[LAW_FREESPEECH]==-2)strcat(story,"[I will harm all police officers], startin' with this [one] here.");
               else strcat(story,"Imma kill all you b*tches, startin' with this m*th*f*ck*r here.");
               break;
           }
            strcat(story,"\"");
            strcat(story,"  The tower was breached in an attempt to reach ");
            strcat(story,"the hostage, but ");
            strcat(story,dstr2);
            strcat(story," had already ");
            if(law[LAW_FREESPEECH]==-2)strcat(story,"[harmed] the guard");
            else if(law[LAW_FREESPEECH]==-1)strcat(story,"killed the guard");
            else switch(LCSrandom(15))
            {
            case 0:strcat(story,"slit the guard's throat with a shank");break;
            case 1:strcat(story,"strangled the guard to death with a knotted bed sheet");break;
            case 2:strcat(story,"chewed out the guard's throat");break;
            case 3:strcat(story,"smashed the guard's skull with the toilet seat from ");
                   strcat(story,(dgn==GENDER_FEMALE?"her":"his"));
                   strcat(story," cell");break;
            case 4:strcat(story,"shot the guard with ");
                   strcat(story,(ggn==GENDER_FEMALE?"her":"his"));
                   strcat(story," own gun");break;
            case 5:strcat(story,"poisoned the guard with drugs smuggled into the prison by the ");
                   strcat(story,(LCSrandom(2)?"Crips":"Bloods"));break;
            case 6:strcat(story,"hit all 36 pressure points of death on the guard");break;
            case 7:strcat(story,"electrocuted the guard with high-voltage wires");break;
            case 8:strcat(story,"thrown the guard out the top-storey window");break;
            case 9:strcat(story,"taken the guard to the execution chamber and finished ");
                   strcat(story,(ggn==GENDER_FEMALE?"her":"him"));
                   strcat(story," off");break;
            case 10:strcat(story,"tricked another guard into shooting the guard dead");break;
            case 11:strcat(story,"burnt the guard to a crisp using a lighter and some gasoline");break;
            case 12:strcat(story,"eaten the guard's liver with some fava beans and a nice chianti");break;
            case 13:strcat(story,"performed deadly experiments on the guard unheard of since Dr. Mengele");break;
            case 14:strcat(story,"sacrificed the guard on a makeshift ");
                    strcat(story,(LCSrandom(2)?"Satanic":"neo-pagan"));
                    strcat(story," altar");break;
            }
            strcat(story,".  The prisoner was ");
            if(law[LAW_FREESPEECH]==-2)strcat(story,"[also harmed]");
            else strcat(story,"beaten to death");
            strcat(story," while \"resisting capture\", according to a prison spokesperson.");
            strcat(story,"&r");
            break;
         }
      }
   }
}



#define PICTURE_MUTANT_BEAST  0
#define PICTURE_CEO           1
#define PICTURE_BOOK          2
#define PICTURE_MELTDOWN      3
#define PICTURE_GENETICS      4
#define PICTURE_RIVERFIRE     5
#define PICTURE_DOLLARS       6
#define PICTURE_TINKYWINKY    7
#define PICTURE_OIL           8
#define PICTURE_TERRORISTS    9
#define PICTURE_KKK           10
#define PICTURE_TSHIRT        11

void displaymajoreventstory(newsstoryst& ns,char* story,short* storyx_s,short* storyx_e)
{
   if(ns.positive)
   {
      switch(ns.view)
      {
         case VIEW_WOMEN:
            displaycenterednewsfont("CLINIC MURDER",5);
            constructeventstory(story,ns.view,ns.positive);
            displaynewsstory(story,storyx_s,storyx_e,13);
            break;
         case VIEW_GAY:
            displaycenterednewsfont("CRIME OF HATE",5);
            constructeventstory(story,ns.view,ns.positive);
            displaynewsstory(story,storyx_s,storyx_e,13);
            break;
         case VIEW_DEATHPENALTY:
            displaycenterednewsfont("JUSTICE DEAD",5);
            constructeventstory(story,ns.view,ns.positive);
            displaynewsstory(story,storyx_s,storyx_e,13);
            break;
            /*
         case VIEW_MILITARY:
            displaycenterednewsfont("CASUALTIES MOUNT",5);
            displaycenteredsmallnews("Is the latest military invasion yet another quagmire?",12);
            strcpy(story,"");
            generatefiller(story,200);
            displaynewsstory(story,storyx_s,storyx_e,13);
            break;
            */
            /*
         case VIEW_POLITICALVIOLENCE:
            displaycenterednewsfont("NIGHTMARE",5);
            constructeventstory(story,ns.view,ns.positive);
            generatefiller(story,200);
            displaynewsstory(story,storyx_s,storyx_e,13);
            break;
            */
         case VIEW_GUNCONTROL:
            displaycenterednewsfont("MASS SHOOTING",5);
            constructeventstory(story,ns.view,ns.positive);
            displaynewsstory(story,storyx_s,storyx_e,13);
            break;
         case VIEW_TAXES:
         {
            displaycenterednewsfont("REAGAN FLAWED",5);//XXX: "Reagan was wrong" or something?
            char str[80];
            strcpy(str,"新刊『");
            switch(LCSrandom(5))
            {
               case 0:strcat(str,"影の");break;
               case 1:strcat(str,"闇の");break;
               case 2:strcat(str,"地の底の");break;
               case 3:strcat(str,"オーウェル的");break;
               case 4:strcat(str,"断崖の");break;
            }
            switch(LCSrandom(5))
            {
               case 0:strcat(str,"俳優");break;
               case 1:strcat(str,"領主");break;
               case 2:strcat(str,"皇帝");break;
               case 3:strcat(str,"操り人形");break;
               case 4:strcat(str,"白痴");break;
            }
            strcat(str,"』: レーガン元大統領の知られざる側面に切り込む一冊。");
            displaycenteredsmallnews(str,12);
            displaynewspicture(PICTURE_BOOK,13);
            break;
         }
         case VIEW_NUCLEARPOWER:
            displaycenterednewsfont("MELTDOWN",5);
            displaycenteredsmallnews("原子力発電所が破滅的メルトダウンに見舞われた。",12);
            displaynewspicture(PICTURE_MELTDOWN,13);
            break;
         case VIEW_ANIMALRESEARCH:
            displaycenterednewsfont("HELL ON EARTH",5);
            displaycenteredsmallnews("研究所から逃げ出したミュータント・アニマルが30人を殺傷した。",12);
            displaynewspicture(PICTURE_MUTANT_BEAST,13);
            break;
         case VIEW_PRISONS:
            displaycenterednewsfont("ON THE INSIDE",5);
            constructeventstory(story,ns.view,ns.positive);
            displaynewsstory(story,storyx_s,storyx_e,13);
            break;
         case VIEW_INTELLIGENCE:
            displaycenterednewsfont("THE FBI FILES",5);
            constructeventstory(story,ns.view,ns.positive);
            displaynewsstory(story,storyx_s,storyx_e,13);
            break;
         case VIEW_FREESPEECH:
            displaycenterednewsfont("BOOK BANNED",5);
            constructeventstory(story,ns.view,ns.positive);
            displaynewsstory(story,storyx_s,storyx_e,13);
            break;
         case VIEW_GENETICS:
            displaycenterednewsfont("KILLER FOOD",5);
            displaycenteredsmallnews("遺伝子組み換え食品で百人を超える人々が健康被害を被った。",12);
            displaynewspicture(PICTURE_GENETICS,13);
            break;
         case VIEW_JUSTICES:
            displaycenterednewsfont("IN CONTEMPT",5);
            constructeventstory(story,ns.view,ns.positive);
            displaynewsstory(story,storyx_s,storyx_e,13);
            break;
         case VIEW_SWEATSHOPS:
            displaycenterednewsfont("CHILD'S PLEA",5);
            displaycenteredsmallnews("ある店のTシャツから搾取工場で働く子供のメモが見つかった。",12);
            displaynewspicture(PICTURE_TSHIRT,13);
            break;
         case VIEW_POLLUTION:
            displaycenterednewsfont("RING OF FIRE",5);
            displaycenteredsmallnews("オハイオ川が再び炎で包まれた。",12);
            displaynewspicture(PICTURE_RIVERFIRE,13);
            break;
         case VIEW_CORPORATECULTURE:
            displaycenterednewsfont("BELLY UP",5);
            displaycenteredsmallnews("企業の倒産件数が記録を更新した。",12);// random company name
            displaynewspicture(PICTURE_DOLLARS,13);
            break;
         case VIEW_CEOSALARY:
         {
            displaycenterednewsfont("AMERICAN CEO",5);
            char str[80];
            strcpy(str,"このよく知られたCEOは");
            switch(LCSrandom(10))
            {
               case 0:
                  if(law[LAW_FREESPEECH]==-2&&law[LAW_WOMEN]!=-2)strcat(str,"日常的に[働く女性]を招いている。");
                  else if(law[LAW_FREESPEECH]==-2&&law[LAW_WOMEN]==-2)strcat(str,"日常的に[精子バンクに寄付]している。");
                  else strcat(str,"日常的に売春婦を招いている。");
                  break;
               case 1:
                  strcat(str,"占い師に助言を求めている。");
                  break;
               case 2:
                  strcat(str,"KKKに数百万ドルを寄付している。");
                  break;
               case 3:
                  strcat(str,"20年以上税金を逃れている。");
                  break;
               case 4:
                  strcat(str,"妻と離婚した。");
                  break;
               case 5:
                  strcat(str,"自分の会社が何をしているのか知らない。");
                  break;
               case 6:
                  strcat(str,"輸入した外来ワームの昆虫園を持っている。");
                  break;
               case 7:
                  strcat(str,"ハイテク・ボンデージギアに大金を費やしている。");
                  break;
               case 8:
                  strcat(str,"オフィスのトイレに監視カメラを導入した。");
                  break;
               case 9:
                  strcat(str,"外国に自分の奴隷を所有している。");
                  break;
            }
            displaycenteredsmallnews(str,12);
            displaynewspicture(PICTURE_CEO,13);
            break;
         }
         case VIEW_AMRADIO:
            displaycenterednewsfont("AM IMPLOSION",5);
            constructeventstory(story,ns.view,ns.positive);
            displaynewsstory(story,storyx_s,storyx_e,13);
            break;
                }
        }
   else
   {
      switch(ns.view)
      {
         case VIEW_GAY:
            displaycenterednewsfont("KINKY WINKY",5);
            displaycenteredsmallnews("キンキー・ウィンキー  ジェリー・ファルエルが真実を明らかにした。まただ。",12);
            displaynewspicture(PICTURE_TINKYWINKY,13);
            break;
         case VIEW_DEATHPENALTY:
            displaycenterednewsfont("LET'S FRY 'EM",5);
            constructeventstory(story,ns.view,ns.positive);
            displaynewsstory(story,storyx_s,storyx_e,13);
            break;
            /*
         case VIEW_MILITARY:
            displaycenterednewsfont("BIG VICTORY",5);
            displaycenteredsmallnews("Our boys defend freedom once again, defeating an evil dictator.",13);
            strcpy(story,"");
            generatefiller(story,200);
            displaynewsstory(story,storyx_s,storyx_e,15);
            break;
            */
            /*
         case VIEW_POLITICALVIOLENCE:
            displaycenterednewsfont("END IN TEARS",5);
            constructeventstory(story,ns.view,ns.positive);
            generatefiller(story,200);
            displaynewsstory(story,storyx_s,storyx_e,13);
            break;
            */
         case VIEW_GUNCONTROL:
            displaycenterednewsfont("ARMED CITIZEN",5);
            displaycenterednewsfont("SAVES LIVES",13);
            constructeventstory(story,ns.view,ns.positive);
            displaynewsstory(story,storyx_s,storyx_e,21);
            break;
         case VIEW_TAXES:
         {
            displaycenterednewsfont("REAGAN THE MAN",5);
            char str[80];
            strcpy(str,"新刊『");
            switch(LCSrandom(5))
            {
               case 0:strcat(str,"偉大な");break;
               case 1:strcat(str,"気高い");break;
               case 2:strcat(str,"真実の");break;
               case 3:strcat(str,"混じり気のない");break;
               case 4:strcat(str,"黄金の");break;
            }
            switch(LCSrandom(5))
            {
               case 0:strcat(str,"リーダーシップ");break;
               case 1:strcat(str,"勇気");break;
               case 2:strcat(str,"先駆者");break;
               case 3:strcat(str,"コミュニケーター");break;
               case 4:strcat(str,"信念");break;
            }
            strcat(str,"』: レーガン元大統領と最も偉大な世代の人々が絶賛する一冊。");
            displaycenteredsmallnews(str,12);
            displaynewspicture(PICTURE_BOOK,13);
            break;
         }
         case VIEW_NUCLEARPOWER:
            displaycenterednewsfont("OIL CRUNCH",5);
            displaycenteredsmallnews("米国の対外政策への対抗措置として、OPECは原油の大幅な減産を決定した。",12);
            displaynewspicture(PICTURE_OIL,13);
            break;
         case VIEW_ANIMALRESEARCH:
            displaycenterednewsfont("APE EXPLORERS",5);
            constructeventstory(story,ns.view,ns.positive);
            displaynewsstory(story,storyx_s,storyx_e,13);
            break;
         case VIEW_POLICEBEHAVIOR:
            if(law[LAW_FREESPEECH]==-2)displaycenterednewsfont("[JERKS]",5);
            else displaycenterednewsfont("BASTARDS",5);
            displaynewspicture(PICTURE_TERRORISTS,13);
            break;
         case VIEW_PRISONS:
            displaycenterednewsfont("HOSTAGE SLAIN",5);
            constructeventstory(story,ns.view,ns.positive);
            displaynewsstory(story,storyx_s,storyx_e,13);
            break;
         case VIEW_INTELLIGENCE:
            displaycenterednewsfont("DODGED BULLET",5);
            constructeventstory(story,ns.view,ns.positive);
            displaynewsstory(story,storyx_s,storyx_e,13);
            break;
         case VIEW_FREESPEECH:
            displaycenterednewsfont("HATE RALLY",5);
            displaycenteredsmallnews("言論の自由の支持者は白人至上主義者の集会を開催するために戦っている。",12);
            displaynewspicture(PICTURE_KKK,13);
            break;
         case VIEW_GENETICS:
            displaycenterednewsfont("GM FOOD FAIRE",5);
            constructeventstory(story,ns.view,ns.positive);
            displaynewsstory(story,storyx_s,storyx_e,13);
            break;
         case VIEW_JUSTICES:
            displaycenterednewsfont("JUSTICE AMOK",5);
            constructeventstory(story,ns.view,ns.positive);
            displaynewsstory(story,storyx_s,storyx_e,13);
            break;
         case VIEW_SWEATSHOPS:
            displaycenterednewsfont("THEY ARE HERE",5);
            if(month>=8&&month<=11)displaycenteredsmallnews("秋ファッションが全国のストアで展開中。",12);
            else displaycenteredsmallnews("秋を先取りしたファッションが全国のストアで展開中。",12);
            displaynewspicture(PICTURE_TSHIRT,13);
            break;
         case VIEW_POLLUTION:
            displaycenterednewsfont("LOOKING UP",5);
            constructeventstory(story,ns.view,ns.positive);
            displaynewsstory(story,storyx_s,storyx_e,13);
            break;
         case VIEW_CORPORATECULTURE:
            displaycenterednewsfont("NEW JOBS",5);
            constructeventstory(story,ns.view,ns.positive);
            displaynewsstory(story,storyx_s,storyx_e,13);
            break;
         case VIEW_AMRADIO:
            displaycenterednewsfont("THE DEATH",5);
            displaycenterednewsfont("OF CULTURE",13);
            constructeventstory(story,ns.view,ns.positive);
            displaynewsstory(story,storyx_s,storyx_e,21);
            break;
      }
   }
}

void run_television_news_stories()
{
   char del;
   for(int n=len(newsstory)-1;n>=0;n--)
   {
      del=0;
      if(newsstory[n]->type==NEWSSTORY_MAJOREVENT)
      {
         if(newsstory[n]->positive)
         {
            switch(newsstory[n]->view)
            {
               case VIEW_POLICEBEHAVIOR:
                  music.play(MUSIC_LACOPS);
                  movie.loadmovie("lacops.cmv");
                  movie.playmovie(0,0);

                  set_color(COLOR_WHITE,COLOR_BLACK,1);
                  move(19,13);
                  addstr("+----------------------------------------------------+");
                  move(20,13);
                  addstr("|   ロサンゼルスで再び警官が黒人男性に暴行を加えた。 |");
                  move(21,13);
                  addstr("|   今回の事件は通行人によって撮影され、ニュースで   |");
                  move(22,13);
                  addstr("|   も大きく取り上げられた。                         |");
                  move(23,13);
                  addstr("+----------------------------------------------------+");

                  getkey();

                  del=1;
                  break;
               case VIEW_CABLENEWS:
               {
                  music.play(MUSIC_NEWSCAST);
                  char str[80];
                  strcpy(str,"今夜のケーブルニュースチャンネル: ");
                  char bname[80];
                  generate_name(bname,GENDER_WHITEMALEPATRIARCH);
                  strcat(str,bname);
                  strcat(str,"の");

                  switch(LCSrandom(5))
                  {
                  case 0:strcat(str,"クロス");break;
                  case 1:strcat(str,"ハード");break;
                  case 2:strcat(str,"ライトニング");break;
                  case 3:strcat(str,"ワシントン");break;
                  case 4:strcat(str,"キャピタル");break;
                  }
                  switch(LCSrandom(5))
                  {
                  case 0:strcat(str,"・ファイア");break;
                  case 1:strcat(str,"・ボール");break;
                  case 2:strcat(str,"・トーク");break;
                  case 3:strcat(str,"・インサイダー");break;
                  case 4:strcat(str,"・ギャング");break;
                  }

                  clear();
                  set_color(COLOR_WHITE,COLOR_BLACK,1);
                  move(0,39-((len(str)-1)>>1));
                  addstr(str);

                  move(16,20);
                  addstr(bname);
                  move(17,20);
                  switch(LCSrandom(3))
                  {
                  case 0:addstr("ワシントン DC");break;
                  case 1:addstr("ニューヨーク NY");break;
                  case 2:addstr("アトランタ GA");break;
                  }

                  move(16,41);
                  generate_name(bname);
                  addstr(bname);
                  move(17,41);
                  switch(LCSrandom(4))
                  {
                  case 0:addstr("ユージーン OR");break;
                  case 1:addstr("サンフランシスコ CA");break;
                  case 2:addstr("ケンブリッジ MA");break;
                  case 3:addstr("イサカ NY");break;
                  }

                  movie.loadmovie("newscast.cmv");
                  movie.playmovie(1,1);

                  set_color(COLOR_WHITE,COLOR_BLACK,1);
                  move(19,13);
                  addstr("+----------------------------------------------------+");
                  move(20,13);
                  addstr("|   ケーブルニュースが誤って明朗なリベラルゲストに   |");
                  move(21,13);
                  addstr("|   最後まで発言させてしまった。全米の大勢の視聴者   |");
                  move(22,13);
                  addstr("|   がこれを聞いていた。                             |");
                  move(23,13);
                  addstr("+----------------------------------------------------+");

                  getkey();

                  del=1;
                  break;
               }
            }
         }
         else
         {
            switch(newsstory[n]->view)
            {
               case VIEW_CEOSALARY:
                  music.play(MUSIC_GLAMSHOW);
                  movie.loadmovie("glamshow.cmv");
                  movie.playmovie(0,0);

                  set_color(COLOR_WHITE,COLOR_BLACK,1);
                  move(19,13);
                  addstr("+----------------------------------------------------+");
                  move(20,13);
                  addstr("|   セレブの生活を魅力的に紹介するテレビ番組が今週   |");
                  move(21,13);
                  addstr("|   から始まる。全米で電撃的に宣伝されており、人気   |");
                  move(22,13);
                  addstr("|   が出るに違いない。                               |");
                  move(23,13);
                  addstr("+----------------------------------------------------+");

                  getkey();

                  del=1;
                  break;
               case VIEW_CABLENEWS:
                  music.play(MUSIC_ANCHOR);
                  movie.loadmovie("anchor.cmv");
                  movie.playmovie(0,0);

                  set_color(COLOR_WHITE,COLOR_BLACK,1);
                  move(19,13);
                  addstr("+----------------------------------------------------+");
                  move(20,13);
                  addstr("|  有力ケーブルニュースチャンネルが新しいニュース番  |");
                  move(21,13);
                  addstr("|  組のために魅力的なキャスターを雇った。巧みな宣伝  |");
                  move(22,13);
                  addstr("|  も行われている。これは全米で視聴されるだろう。    |");
                  move(23,13);
                  addstr("+----------------------------------------------------+");

                  getkey();

                  del=1;
                  break;
               case VIEW_WOMEN:
                  music.play(MUSIC_ABORT);
                  clear();

                  movie.loadmovie("abort.cmv");
                  movie.playmovie(0,0);

                  set_color(COLOR_WHITE,COLOR_BLACK,1);
                  move(19,13);
                  addstr("+----------------------------------------------------+");
                  move(20,13);
                  addstr("|   有名な午後のトークショーで失敗した部分出産中絶   |");
                  move(21,13);
                  addstr("|   の話題が取り上げられた。スタジオの聴衆と全米の   |");
                  move(22,13);
                  addstr("|   視聴者は嫌悪感を抱いただろう。                   |");
                  move(23,13);
                  addstr("+----------------------------------------------------+");

                  getkey();

                  del=1;
                  break;
            }
         }
      }
      if(del) delete_and_remove(newsstory,n);
   }
}
