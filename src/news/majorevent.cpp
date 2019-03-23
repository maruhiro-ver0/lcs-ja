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
            strcat(story," - 病院で殺人  昨日、");
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
            strcat(story," - ヘイトクライム  昨日、");
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
            strcat(story," - 司法の死  無実の市民が電気椅子で処刑された。");
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
            strcat(story,"ワシントン DC - FBIファイル  FBIはあなたを監視し続けている。");
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
            strcat(story," - 禁書指定  宗教団体の圧力を受け、市は図書館からある子供向けの本を撤去した。");
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
            strcat(story," - 保守派の連邦裁判所判事");
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
            strcat(story," - 2日前の夜、よく知られたラジオ・パーソナリティ");
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
            strcat(story," - ");
            strcat(story, "地元の");
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
            strcat(story," - 元受刑者が鉄格子の向こう側の恐るべき実態を詳細に描いた本を書いた。");
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
            strcat(story," - Perhaps parents can rest easier tonight.  ");
            strcat(story,"The authorities have apprehended their primary suspect in the ");
            strcat(story,"string of brutal child killings that has kept everyone in the area on edge, ");
            strcat(story,"according to a spokesperson for the police department here.  ");
            char dstr[200],dstr2[200],dstr3[200];
            generate_long_name(dstr,dstr2,dstr3);
            strcat(story,dstr);
            strcat(story," ");
            strcat(story,dstr2);
            strcat(story," ");
            strcat(story,dstr3);
            strcat(story," was detained yesterday afternoon, reportedly in possession of ");
            switch(LCSrandom(5))
            {
            case 0: strcat(story,"pieces of another victim"); break;
            case 1: strcat(story,"bloody toys"); break;
            case 2: strcat(story,"a child's clothing stained with DNA evidence"); break;
            case 3: strcat(story,"seven junior high school yearbooks"); break;
            case 4: strcat(story,"two small backpacks"); break;
            }
            strcat(story,".  Over twenty children in the past two years have gone missing, ");
            strcat(story,"only to turn up later");
            if(law[LAW_FREESPEECH]==-2)
               strcat(story," [in a better place]");
            else
            {
               strcat(story," dead and ");
               switch(LCSrandom(5))
               {
               case 0: strcat(story,"carved with satanic symbols"); break;
               case 1: strcat(story,"sexually mutilated"); break;
               case 2: strcat(story,"missing all of their teeth"); break;
               case 3: strcat(story,"missing all of their fingers"); break;
               case 4: strcat(story,"without eyes"); break;
               }
            }
            strcat(story,".  Sources say that the police got a break in the case when ");
            switch(LCSrandom(5))
            {
            case 0: strcat(story,"a victim called 911 just prior to being slain while still on the phone"); break;
            case 1: strcat(story,"the suspect allegedly carved an address into one of the bodies"); break;
            case 2: strcat(story,"an eye witness allegedly spotted the suspect luring a victim into a car"); break;
            case 3: strcat(story,"a blood trail was found on a road that led them to the suspect's car trunk"); break;
            case 4: strcat(story,"they found a victim in a ditch, still clinging to life"); break;
            }
            strcat(story,".");
            strcat(story,"&r");
            strcat(story,"   The district attorney's office has already repeatedly said it will be ");
            strcat(story,"seeking ");
            if(law[LAW_DEATHPENALTY]==2)
               strcat(story,"life imprisonment in this case.");
            else
               strcat(story,"the death penalty in this case.");
            strcat(story,"&r");
            break;
         }
         case VIEW_ANIMALRESEARCH:
         {
            strcpy(story,cityname());
            strcat(story," - Researchers ");
            if(law[LAW_ANIMALRESEARCH]==2)
            {
               strcat(story,"from ");
               switch(LCSrandom(5))
               {
               case 0:strcat(story,"Russia");break;
               case 1:strcat(story,"North Korea");break;
               case 2:strcat(story,"Cuba");break;
               case 3:strcat(story,"Iran");break;
               case 4:strcat(story,"China");break;
               }
               strcat(story," report that they have discovered an amazing new wonder drug. ");
            }
            else
               strcat(story,"here report that they have discovered an amazing new wonder drug.  ");
            strcat(story,"Called ");
            switch(LCSrandom(5))
            {
            case 0:
               if(law[LAW_FREESPEECH]==-2)strcat(story,"Bum-Bum");
               else strcat(story,"Anal");break;
            case 1:strcat(story,"Colo");break;
            case 2:strcat(story,"Lacta");break;
            case 3:strcat(story,"Pur");break;
            case 4:strcat(story,"Loba");break;
            }
            switch(LCSrandom(5))
            {
            case 0:strcat(story,"nephrin");break;
            case 1:strcat(story,"tax");break;
            case 2:strcat(story,"zac");break;
            case 3:strcat(story,"thium");break;
            case 4:strcat(story,"drene");break;
            }
            strcat(story,", the drug apparently ");
            switch(LCSrandom(5))
            {
            case 0:strcat(story,"boosts intelligence in chimpanzees");break;
            case 1:
               if(law[LAW_FREESPEECH]==-2)strcat(story,"[helps chimpanzees reproduce]");
               else strcat(story,"corrects erectile dysfunction in chimpanzees");break;
            case 2:strcat(story,"allows chimpanzees to move blocks with their minds");break;
            case 3:strcat(story,"allows chimpanzees to fly short distances");break;
            case 4:strcat(story,"increases the attention span of young chimpanzees");break;
            }
            strcat(story,".  ");
            strcat(story,"&r");
            strcat(story,"   Along with bonobos, chimpanzees are our closest cousins");
            strcat(story,".  ");
            strcat(story,"Fielding questions about the ethics of their experiments from reporters during a press conference yesterday, ");
            strcat(story,"a spokesperson for the research team stated that, \"It really isn't so bad as all that.  Chimpanzees are very resilient creatures.  ");
            switch(LCSrandom(3))
            {
            case 0:strcat(story,"The ones that survived are all doing very well");break;
            case 1:strcat(story,"They hardly notice when you drill their brains out, if you're fast");break;
            case 2:strcat(story,"When we started muffling the screams of our subjects, the other chimps all calmed down quite a bit");break;
            }
            strcat(story,".  We have a very experienced research team.  ");
            strcat(story,"While we understand your concerns, any worries are entirely unfounded.  ");
            strcat(story,"I think the media should be focusing on the enormous benefits of this drug.");
            strcat(story,"\"");
            strcat(story,"&r");
            strcat(story,"   The first phase of human trials is slated to begin in a few months.");
            strcat(story,"&r");
            break;
         }
         case VIEW_INTELLIGENCE:
         {
            strcat(story,"Washington, DC - The CIA announced yesterday that it has averted a terror attack that ");
            strcat(story,"would have occurred on American soil.");
            strcat(story,"&r");
            strcat(story,"   According to a spokesperson for the agency, ");
            switch(LCSrandom(3))
            {
            case 0:strcat(story,"white supremacists");break;
            case 1:strcat(story,"Islamic fundamentalists");break;
            case 2:strcat(story,"outcast goths from a suburban high school");break;
            }
            strcat(story," planned to ");
            switch(LCSrandom(9))
            {
            case 0:
               if(law[LAW_FREESPEECH]==-2)strcat(story,"[land] planes [on apartment buildings]");
               else strcat(story,"fly planes into skyscrapers");break;
            case 1:
               if(law[LAW_FREESPEECH]==-2)strcat(story,"[put] fertilizer [on plants] at a federal building");
               else strcat(story,"detonate a fertilizer bomb at a federal building");break;
            case 2:
               if(law[LAW_FREESPEECH]==-2)strcat(story,"[show up uninvited on] a warship");
               else strcat(story,"ram a motorboat loaded with explosives into a warship");break;
            case 3:
               if(law[LAW_FREESPEECH]==-2)strcat(story,"[give children owies and boo-boos]");
               else strcat(story,"detonate explosives on a school bus");break;
            case 4:
               if(law[LAW_FREESPEECH]==-2)strcat(story,"[cause a traffic jam on] a major bridge");
               else strcat(story,"blow out a section of a major bridge");break;
            case 5:
               if(law[LAW_FREESPEECH]==-2)strcat(story,"[take] the president [on vacation]");
               else strcat(story,"kidnap the president");break;
            case 6:
               if(law[LAW_FREESPEECH]==-2)strcat(story,"[hurt] the president");
               else strcat(story,"assassinate the president");break;
            case 7:
               if(law[LAW_FREESPEECH]==-2)strcat(story,"[vandalize] the Capitol Building");
               else strcat(story,"destroy the Capitol Building");break;
            case 8:
               if(law[LAW_FREESPEECH]==-2)strcat(story,"detonate [fireworks] in New York");
               else strcat(story,"detonate a nuclear bomb in New York");break;
            }
            strcat(story,".  However, intelligence garnered from deep within the mysterious ");
            strcat(story,"terrorist organization allowed the plot to be foiled just days before it ");
            strcat(story,"was to occur.");
            strcat(story,"&r");
            strcat(story,"   The spokesperson further stated, \"");
            strcat(story,"I won't compromise our sources and methods, but let me just say ");
            strcat(story,"that we are grateful to the Congress and this Administration for ");
            strcat(story,"providing us with the tools we need to neutralize these enemies of ");
            strcat(story,"civilization before they can destroy American families.  ");
            strcat(story,"However, let me also say that there's more that needs to be done.  ");
            strcat(story,"The Head of the Agency will be sending a request to Congress ");
            strcat(story,"for what we feel are the essential tools for combating terrorism in ");
            strcat(story,"this new age.");
            strcat(story,"\"");
            strcat(story,"&r");
            break;
         }
         case VIEW_GENETICS:
         {
            strcpy(story,cityname());
            strcat(story," - The genetic foods industry staged a major event here yesterday ");
            strcat(story,"to showcase its upcoming products.  Over thirty companies set up ");
            strcat(story,"booths and gave talks to wide-eyed onlookers.");
            strcat(story,"&r");
            strcat(story,"   One such corporation, ");
            switch(LCSrandom(5))
            {
            case 0:strcat(story,"Altered");break;
            case 1:strcat(story,"Gene-tech");break;
            case 2:strcat(story,"DNA");break;
            case 3:strcat(story,"Proteomic");break;
            case 4:strcat(story,"Genomic");break;
            }
            strcat(story," ");
            switch(LCSrandom(5))
            {
            case 0:strcat(story,"Foods");break;
            case 1:strcat(story,"Agriculture");break;
            case 2:strcat(story,"Meals");break;
            case 3:strcat(story,"Farming");break;
            case 4:strcat(story,"Living");break;
            }
            strcat(story,", presented their product, \"");
            switch(LCSrandom(5))
            {
            case 0:strcat(story,"Mega");break;
            case 1:strcat(story,"Epic");break;
            case 2:strcat(story,"Overlord");break;
            case 3:strcat(story,"Franken");break;
            case 4:strcat(story,"Transcendent");break;
            }
            strcat(story," ");
            switch(LCSrandom(5))
            {
            case 0:strcat(story,"Rice");break;
            case 1:strcat(story,"Beans");break;
            case 2:strcat(story,"Corn");break;
            case 3:strcat(story,"Wheat");break;
            case 4:strcat(story,"Potatoes");break;
            }
            strcat(story,"\", during an afternoon PowerPoint presentation.  ");
            strcat(story,"According to the public relations representative speaking, ");
            strcat(story,"this amazing new product actually ");
            switch(LCSrandom(5))
            {
            case 0:strcat(story,"extends human life by a few minutes every bite");break;
            case 1:strcat(story,"mends split-ends upon digestion.  Hair is also made glossier and thicker");break;
            case 2:strcat(story,"allows people to see in complete darkness");break;
            case 3:strcat(story,"causes a person to slowly attain their optimum weight with repeated use");break;
            case 4:strcat(story,"cures the common cold");break;
            }
            strcat(story,".");
            strcat(story,"&r");
            strcat(story,"   Spokespeople for the GM corporations were universal ");
            strcat(story,"in their dismissal of the criticism which often follows the industry.  ");
            strcat(story,"One in particular said, \"");
            strcat(story,"Look, these products are safe.  That thing about the ");
            switch(LCSrandom(4))
            {
            case 0:strcat(story,"guy going on a killing spree");break;
            case 1:strcat(story,"gal turning blue and exploding");break;
            case 2:strcat(story,"guy speaking in tongues and worshiping Satan");break;
            case 3:strcat(story,"gal having a ruptured intestine");break;
            }
            strcat(story," is just a load of ");
            if(law[LAW_FREESPEECH]==-2) switch(LCSrandom(5))
            {
            case 0:strcat(story,"hooey");break;
            case 1:strcat(story,"poppycock");break;
            case 2:strcat(story,"horse radish");break;
            case 3:strcat(story,"skunk weed");break;
            case 4:strcat(story,"garbage");break;
            }
            else switch(LCSrandom(3))
            {
            case 0:strcat(story,"horseshit");break; // McCain
            case 1:strcat(story,"bullshit");break;
            case 2:strcat(story,"shit");break;
            }
            strcat(story,".  Would we stake the reputation of our company on unsafe products?  ");
            strcat(story,"No.  That's just ridiculous.  I mean, sure companies have put unsafe products out, ");
            strcat(story,"but the GM industry operates at a higher ethical standard.  That goes without saying.");
            strcat(story,"\"");
            strcat(story,"&r");
            break;
         }
         case VIEW_JUSTICES:
         {
            strcpy(story,cityname());
            strcat(story," - The conviction of confessed serial killer ");
            char dstr[200],dstr2[200],dstr3[200];
            generate_long_name(dstr,dstr2,dstr3);
            strcat(story,dstr);
            strcat(story," ");
            strcat(story,dstr2);
            strcat(story," ");
            strcat(story,dstr3);
            strcat(story," was overturned by a federal judge yesterday.  ");
            strcat(story,"Justice ");
            char jstr[200],jstr2[200];
            char gn=(LCSrandom(2)==1?GENDER_MALE:GENDER_FEMALE);
            generate_name(jstr,jstr2,gn);
            strcat(story,jstr);
            strcat(story," ");
            strcat(story,jstr2);
            strcat(story," of the notoriously liberal circuit of appeals here ");
            strcat(story,"made the decision based on ");
            char gen[20];
            strcpy(gen,(gn==GENDER_FEMALE?"her":"his"));
            switch(LCSrandom(7))
            {
            case 0:strcat(story,"ten-year-old eyewitness testimony");break;
            case 1:strcat(story,gen);strcat(story," general feeling about police corruption");break;
            case 2:strcat(story,gen);strcat(story," belief that the crimes were a vast right-wing conspiracy");break; // Clinton
            case 3:
               strcat(story,gen);
               strcat(story," belief that ");
               strcat(story,dstr3);
               strcat(story," deserved another chance");
               break;
            case 4:
               strcat(story,gen);
               strcat(story," personal philosophy of liberty");break;
            case 5:
               strcat(story,gen);
               strcat(story," close personal friendship with the ");
               strcat(story,dstr3);      // I know Charles Manson.
               strcat(story," family");  // Charles Manson was a friend of mine.
               break;                    // And you, sir, are no Charles Manson!
            case 6:strcat(story,gen);strcat(story," consultations with a Magic 8-Ball");break;
            }
            strcat(story,", despite the confession of ");
            strcat(story,dstr3);
            strcat(story,", which even Justice ");
            strcat(story,jstr2);
            strcat(story," grants was not coerced in any way.&r");

            strcat(story,"   Ten years ago, ");
            strcat(story,dstr3);
            strcat(story," was convicted of the now-infamous ");
            char sstr[200];
            lastname(sstr);
            strcat(story,sstr);
            strcat(story," slayings.  ");
            strcat(story,"After an intensive manhunt, ");
            strcat(story,dstr3);
            strcat(story," was found with the murder weapon, ");
            strcat(story,"covered in the victims' blood.  ");
            strcat(story,dstr3);
            strcat(story," confessed and was sentenced to life, saying \"");
            strcat(story,"Thank you for saving me from myself.  ");
            strcat(story,"If I were to be released, I would surely kill again.\"&r");
            strcat(story,"   A spokesperson for the district attorney ");
            strcat(story,"has stated that the case will not be retried, due ");
            strcat(story,"to the current economic doldrums that have left the state ");
            strcat(story,"completely strapped for cash.&r");
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
