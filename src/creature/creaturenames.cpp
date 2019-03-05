// Note: this file is encoded in the PC-8 / Code Page 437 / OEM-US character set
// (The same character set used by Liberal Crime Squad when it is running)
// Certain special characters won't display correctly unless your text editor is
// set to use that character set, such as this e with an accent: e'

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

// Add an age estimate to a person's name
void add_age(Creature& person)
{
   // Who knows how old the purple gorilla/tank/flaming bunny/dog is?
   if(person.animalgloss!=ANIMALGLOSS_NONE)
   {
      addstr(" (?)");
      return;
   }

   // For humans, estimate their age and gender
   addstr(" (");

   // Almost precise estimates of child and teen ages
   if(person.age<20)
   {
      // Inaccuracy in estimating age should be the same every
      // time a character is queried. I'm using the day of the
      // month the character was born on to determine this.
      addstr(person.age+person.birthday_day%3-1);
      addstr("?");
   }
   // More rough estimates of everyone else
   else
   {
      if(person.age<30)
         addstr("20代");
      else if(person.age<40)
         addstr("30代");
      else if(person.age<50)
         addstr("40代");
      else if(person.age<60)
         addstr("50代");
      else if(person.age<70)
         addstr("60代");
      else if(person.age<80)
         addstr("70代");
      else if(person.age<90)
         addstr("80代");
      else
         addstr("かなりの高齢");
   }

   // Assess their gender Liberally but allow ambiguity since you don't know them well enough yet
   if(person.gender_liberal == GENDER_MALE)
      addstr("、男性");
   else if(person.gender_liberal == GENDER_FEMALE)
      addstr("、女性");
   else
      addstr("、性別不明");

   // Note if there's some conflict with Conservative society's perceptions
   if(person.gender_liberal != person.gender_conservative && person.gender_liberal != GENDER_NEUTRAL)
      addstr("?");

   addstr(")");
}


/* rolls up a proper name for a creature */
void Creature::namecreature()
{
   if(!dontname)
   {
      generate_name(name, gender_liberal);
      strcpy(propername,name);
      dontname = true;
   }
}



/* fills a string with a proper name */
void generate_name(char *str, char gender)
{
   char first[80];
   char last[80];

   generate_name(first,last,gender);
   strcpy(str,first);
   strcat(str,"・");
   strcat(str,last);
}



/* get a first and last name for the same person */
void generate_name(char *first, char *last, char gender)
{
   do {
      firstname(first, gender);
      lastname(last, gender == GENDER_WHITEMALEPATRIARCH);
   } while(strcmp(first,last) == 0);
}



/* get a first, middle, and last name for the same person */
void generate_long_name(char *first, char *middle, char *last, char gender)
{
   // pick either male or female so we can have 75% chance of first and middle names having matching genders
   if(gender == GENDER_NEUTRAL)
      gender = (LCSrandom(2)?GENDER_MALE:GENDER_FEMALE);
   do {
      firstname(first, gender);
      if(LCSrandom(2)) // middle name is a first name
         firstname(middle,(gender == GENDER_WHITEMALEPATRIARCH || LCSrandom(2)?gender:GENDER_NEUTRAL)); // 25% chance for middle name of other gender unless white male patriarch
      else // middle name is a last name
         lastname(middle, gender == GENDER_WHITEMALEPATRIARCH);
      lastname(last, gender == GENDER_WHITEMALEPATRIARCH);
   } while(strcmp(first,middle) == 0 && strcmp(first,last) == 0 && strcmp(middle,last) == 0);
}



/* gets a random first name */
void firstname(char *str, char gender)
{
   static const char *male_first_names[] =
   {
   "アーロン",   "アブドル",   "アブナー",   "アブラハム",
   "アダム",   "アドナン",   "アードルフ",   "アドルフ",
   "アハメド",   "アイダン",   "アリ",   "アラン",
   "アルベルト",   "アレック",   "アレハンドロ",   "アレクサンダー",
   "アレクセイ",   "アルフ",   "アルフィー",   "アルフォンス",
   "アルフレッド",   "アラン",   "アレン",   "アルフォンス",
   "アルバロ",   "アルビン",   "アンドラス",   "アンドレ",
   "アンドレイ",   "アンドリュー",   "アンディ",   "アンジェロ",
   "アンガス",   "アンサニー",   "アントニオ",   "アントニー",
   "アーチボルド",   "アーキー",   "アリー",   "アーノルド",
   "アールパード",   "アート",   "アーサー",   "アッチラ",
   "オーガスト",   "オースティン",   "アビ",   "アクセル",
   "バール",   "バラク",   "バシャー",   "バジル",
   "ベントラン",   "バルネー",   "バリー",   "バート",
   "バーソロミュー",   "ボー",   "ベラ",   "ベン",
   "ベネディクト",   "ベニト",   "ベンジャミン",   "ベニー",
   "ブノワ",   "バーナード",   "バーニー",   "ベルト",
   "バートランド",   "ビラル",   "ビル",   "ビリーボブ",
   "ブレーク",   "ボブ",   "ボフミル",   "ボレスワフ",
   "ボーリス",   "ブラッド",   "ブラッドレー",   "ブランドン",
   "ブレンドン",   "ブレント",   "ブライアン",   "ブロンコ",
   "ブルース",   "ブルータス",   "ブリアン",   "ババ",
   "バスター",   "バイロン",   "カイン",   "カル",
   "カルビン",   "カール",   "カルロス",   "カシミール",
   "カシウス",   "セシル",   "セザール",   "チャド",
   "カイム",   "チャールズ",   "チャーリー",   "チャンシー",
   "チェスター",   "チャック",   "チャッキー",   "クリスチャン",
   "クリストファー",   "キーラン",   "シッド",   "クロード",
   "クラウディウス",   "クリフ",   "クリフォード",   "クライブ",
   "クライブン",   "クロビス",   "クライド",   "コリン",
   "コルトン",   "コンラッド",   "コッパー",   "クレイグ",
   "クサバ",   "サイラス",   "デイル",   "ダラス",
   "デミアン",   "ダモン",   "ダン",   "ダンフォース",
   "ダニエル",   "ダニー",   "ダグ",   "ダグウッド",
   "デイブ",   "デイビッド",   "デイビー",   "ディーン",
   "ディーパック",   "デニス",   "デンゼル",   "デラク",
   "デリク",   "デリック",   "デクスター",   "ディック",
   "ディエゴ",   "ディルバート",   "ディネシュ",   "ディンク",
   "ディーノ",   "ディワカール",   "ドブロミル",   "ドック",
   "ドム",   "ドミニク",   "ドン",   "ドナルド",
   "ドノバン",   "ダグ",   "ダグラス",   "ダスティン",
   "ダスティー",   "ドウェイン",   "ドワイト",   "ディラン",
   "アール",   "エド",   "エディー",   "エドガー",
   "エドアルド",   "エドワード",   "エドウィン",   "エマヌエル",
   "エメット",   "イーライ",   "エリア",   "エリアン",
   "エリアス",   "エリオ",   "エリオット",   "エルマー",
   "エルビス",   "エミール",   "エミリアーノ",   "エンリコ",
   "エンリケ",   "エンゾ",   "エリック",   "エリク",
   "アーネスト",   "アーニー",   "エルンスト",   "イーサン",
   "ユージーン",   "エバン",   "エボ",   "エゼキエル",
   "エズラ",   "ファビオ",   "フィリックス",   "フェルディナンド",
   "フェレンツ",   "フェルナンド",   "フィデル",   "フィッシャー",
   "フロイド",   "フォレスト",   "フランセスコ",   "フランシス",
   "フランシスコ",   "フランク",   "フランクリン",   "フランツ",
   "フレッド",   "フレディ",   "フレデリック",   "フリッツ",
   "ガボール",   "ガブリエル",   "ギャレット",   "ガレス",
   "ガース",   "ゲイリー",   "ジョージ",   "ジェラルド",
   "ヘラルド",   "ゲーザ",   "ギルバート",   "ジョバンニ",
   "グルン",   "グレン",   "グラハム",   "グレッグ",
   "グレゴリー",   "ガス",   "グスタフ",   "ガイ",
   "ジェルジュ",   "ジュラ",   "ハーフェズ",   "ヘイガー",
   "アキーム",   "ハミード",   "ハンク",   "ハンニバル",
   "ハンズ",   "ハロルド",   "ハリー",   "ハーベイ",
   "ハインリヒ",   "ヘンリー",   "ハーブ",   "ハーバート",
   "ヘルマン",   "ヒロ",   "ヒロシ",   "ホーマー",
   "ハワード",   "ホーウィー",   "ヒュー",   "ヒューゴ",
   "ハンター",   "イアン",   "イーゴリ",   "アイク",
   "イムレ",   "イングマール",   "アイラ",   "アービング",
   "アイザック",   "イスラエル",   "イジュトバン",   "イワン",
   "ジャック",   "ヤコビ",   "ジャコボ",   "ジェイク",
   "ジャミル",   "ジェームス",   "ヤノス",   "ジャレド",
   "ジェイソン",   "ハビエル",   "ジェイ",   "ジェブ",
   "ジェデダイア",   "ジェフ",   "ジェファーソン",   "ジェフリー",
   "エレミヤ",   "ジェレミー",   "イェルン",   "ジェローム",
   "ジェリー",   "ジェシー",   "ジーザス",   "ジム",
   "ジンボ",   "ジミ",   "ジミー",   "ジンユアン",
   "ジョー",   "ジョエル",   "ジョーイ",   "ヨハン",
   "ジョン",   "ジョニー",   "ジャン",   "ジョナサン",
   "ジョルジ",   "ホセ",   "ヨゼフ",   "ジョセフ",
   "ジョシュ",   "ジョシュア",   "ジョーワル",   "ヨージェフ",
   "ファン",   "ユダ",   "ジュード",   "ジュリアン",
   "ユリウス",   "ジャスティン",   "ケレン",   "カメル",
   "ケイン",   "カール",   "カーロイ",   "キース",
   "ケン",   "ケニー",   "ケンジ",   "ケネス",
   "ケビン",   "カリル",   "カーク",   "コフィ",
   "コンスタンティン",   "カート",   "クワイサイ",   "カイル",
   "ラックラン",   "ラジョス",   "ラマー",   "ランス",
   "ランスロット",   "ラリー",   "ラースロー",   "ローレンス",
   "レニー",   "レオ",   "レオン",   "レオナルド",
   "ルロワ",   "レフ",   "リーバイ",   "レックス",
   "リアム",   "リーナス",   "ライオネル",   "ロイド",
   "ロタール",   "ルイ",   "ロウェル",   "ルーカス",
   "ルシファー",   "ルシウス",   "ラディック",   "ルイージ",
   "ルイス",   "ルーク",   "ルーサー",   "ライル",
   "マルコム",   "マンフレッド",   "マニー",   "マヌエル",
   "マーク",   "マルコ",   "マーカス",   "マーダック",
   "マービン",   "マルク",   "マルコス",   "マリオ",
   "マーティン",   "マートン",   "マーティー",   "メイソン",
   "マット",   "マシュー",   "マッテオ",   "マティアス",
   "モーリス",   "モーリー",   "マクシミリアン",   "メフメト",
   "メルビン",   "マイケル",   "ミック",   "ミッキー",
   "ミゲル",   "マイク",   "マイキー",   "ミハイル",
   "マイルス",   "ミルトン",   "ミロスラフ",   "ミッチ",
   "ミッチェル",   "ミット",   "モウ",   "ムハンマド",
   "モリス",   "モーゼ",   "モシェ",   "ムムターズ",
   "マレー",   "ムスタファ",   "マイロン",   "ナポレオン",
   "ネイト",   "ネイサン",   "ナサニエル",   "ネッド",
   "ニール",   "ナイル",   "ネルソン",   "ニュート",
   "ニュートン",   "ニコラス",   "ニック",   "ノア",
   "ノーム",   "ノルム",   "ノーマン",   "オラフ",
   "オリバー",   "オーラル",   "オサマ",   "オスカー",
   "オーティス",   "オットー",   "オーウェン",   "パブロ",
   "パスカル",   "パトリック",   "パットン",   "ポール",
   "ペドロ",   "パーシバル",   "パーシー",   "パルベーズ",
   "ピート",   "ピーター",   "ペテロ",   "フィル",
   "フィリップ",   "フィリップス",   "フェリペ",   "ピエール",
   "ピアズ",   "プレスコット",   "プレストン",   "クエンティン",
   "クインシー",   "クサイ",   "ラドスラフ",   "ラファエル",
   "ラルフ",   "ロルフ",   "ランドール",   "ランディー",
   "レイン",   "ランサム",   "ラファエロ",   "ラウル",
   "レイ",   "レイモンド",   "レジナルド",   "レジス",
   "レクス",   "リカルド",   "リッチ",   "リチャード",
   "リッチー",   "リック",   "リッキー",   "リンゴ",
   "ロブ",   "ロバート",   "ロビー",   "ロッド",
   "ロドニー",   "ロジャー",   "ロメオ",   "ロン",
   "ロナルド",   "ローリー",   "ロイ",   "ルビン",
   "ルドルフ",   "ルードルフ",   "ルディ",   "ルーファス",
   "ルパート",   "ラッシュ",   "ラス",   "ラッセル",
   "ライアン",   "サダム",   "サンビル",   "サムソン",
   "サムエル",   "サンダー",   "シャーンドル",   "サンフォード",
   "スコット",   "ショーン",   "セバスチャン",   "サージ",
   "セルゲイ",   "セルジョ",   "セス",   "シェーン",
   "ショウン",   "ショーン",   "シェルドン",   "シャーロック",
   "シャーマン",   "シェロッド",   "シド",   "サイモン",
   "サニー",   "スパイク",   "スピロ",   "スタン",
   "スタニスラウス",   "スタニスラフ",   "スタンレー",   "ステファン",
   "スティーブ",   "スティーブン",   "スチュワート",   "スチュ",
   "ステュアート",   "タマス",   "テッド",   "テディー",
   "テレンス",   "テツオ",   "テオ",   "セオドア",
   "トーマ",   "トーマス",   "ソアー",   "ティベリウス",
   "ティム",   "ティモシー",   "タイタス",   "トビー",
   "トッド",   "トム",   "トミー",   "トニー",
   "トシロー",   "トラビス",   "トレイボン",   "トレバー",
   "タッカー",   "タイラー",   "タイロン",   "タイソン",
   "ウダイ",   "ユーサー",   "バシリー",   "ビクター",
   "ビクトル",   "ビンス",   "ビンセント",   "ブラド",
   "ウラジミール",   "ウラジスラフ",   "ブラスティミル",   "ビャチェスラフ",
   "ドウェイン",   "ウォーリー",   "ウォルト",   "ワルター",
   "ウェイン",   "ウェンデル",   "ウィルヘルム",   "ウィル",
   "ウィリアム",   "ウィリー",   "ビリー",   "ウィンストン",
   "ボイチェフ",   "ウルフ",   "ウッドロウ",   "ウッディー",
   "ワイアット",   "ザンダー",   "シャビエル",   "ヤコブ",
   "ヤン",   "ヤセル",   "ヨシ",   "ユセフ",
   "ザッカリー",   "ザック",   "ザイド",   "ズビグネフ",
   "ゼブロン",   "ジーク",   "ゾルタン",   "ジグモンド"
   };

   static const char *female_first_names[] =
   {
   "アビー",   "アビゲイル",   "エイダ",   "アドリアナ",
   "アドリアーナ",   "アドレアナ",   "アガサ",   "アニエス",
   "アイコ",   "アイリーン",   "アルバータ",   "エイリーン",
   "アレクサンドラ",   "アレクサ",   "アレグサンドラ",   "アリス",
   "アリシア",   "アリソン ",   "アリスン",   "アラニヤ",
   "アロラ",   "アリスン",   "アリッサ",   "アマンダ",
   "アンバー",   "アメリア",   "アメリ",   "アメリカ",
   "エイミー",   "アンナ",   "アナスタシア",   "アンドレア",
   "アンジェラ",   "アンジェリカ",   "アンジェリーナ",   "アンジェリーク",
   "アンジー",   "アニサ",   "アニタ",   "アン",
   "アンナ",   "アニー",   "アンマリー",   "アネリ",
   "アニス",   "アニヤ",   "エイプリル",   "アリアドネ",
   "アリアナ",   "アリアンナ",   "アスマ",   "アストリッド",
   "アテナ",   "オードラ",   "オードリー",   "アウラ",
   "オータム",   "エバ",   "アイラ",   "アイン",
   "バーブ",   "バーバラ",   "バービー",   "ビー",
   "ビアトリス",   "ベアトリクス",   "ビビ",   "ベッカ",
   "ベッキー",   "ベラ",   "ベル",   "バーナデット",
   "バーナディン",   "バーニス",   "バーサ",   "ベス",
   "ベサン",   "ベサニー",   "ベティ",   "ビアンカ",
   "ブランチ",   "ボニータ",   "ボニー",   "ブリー",
   "ブレンダ",   "ブリアナ",   "ブリアン",   "ブリジット",
   "ブリギッド",   "ブリジッテ",   "ブリトニー",   "ブルターニュ",
   "ブリトニー",   "ブルック",   "ブルックリン",   "カミラ",
   "カミーラ",   "キャンディス",   "キャンディ",   "カレーナ",
   "カリーナ",   "カーラ",   "カルメン",   "キャロル",
   "キャロライナ",   "キャロライン",   "キャス",   "カサンドラ",
   "ケイト",   "キャサリン",   "キャスリーン",   "キャシー",
   "セシリア",   "セリーヌ",   "チャリティ",   "シャーリーン",
   "シャーリーズ",   "シャーロット",   "チャスティティ",   "チェルシー",
   "チェリー",   "シェリル",   "クロエ",   "クリスティナ",
   "クリスティーン",   "クリスティ",   "シンディー",   "シンディ",
   "クレア",   "クララ",   "クラリッサ",   "クラリティ",
   "クローデット",   "クラウディア",   "クレファス",   "クレオパトラ",
   "コレット",   "コリーン",   "コンスウェラ",   "コンテッサ",
   "コリーヌ",   "コルネリア",   "クリスタル",   "シビル",
   "シンシア",   "デイジー",   "ダコタ",   "ダニエラ",
   "ダニエル",   "ダフネ",   "ドーン",   "デビー",
   "デブラ",   "デリラ",   "ダニエレ",   "デニス",
   "デザレイ",   "ダイアナ",   "ダイアン",   "ディミトラ",
   "ディナ",   "ダナ",   "ドーラ",   "ドリーン",
   "ドリス",   "ドロテア",   "ドロシー",   "ドロッチャ",
   "エボニー",   "イディス",   "エドナ",   "エレイン",
   "エカテリーナ",   "イレーヌ",   "エリナ",   "エレナ",
   "エリノア",   "エリザ",   "エリザベス",   "エレン",
   "エロイース",   "エルシー",   "エルビラ",   "エミリー",
   "エマ",   "エンティサ",   "エリカ",   "エーリカ",
   "エリン",   "エリス",   "エルマ",   "エルジェベート",
   "エスメラルダ",   "エスタ",   "ユードラ",   "ユーフェミア",
   "イーバ",   "イブ",   "フェイス",   "ファニー",
   "ファティマ",   "フェイ",   "フェリシア",   "フェリシティ",
   "フィオナ",   "フロー",   "フローラ",   "フローレンス",
   "フロリダ",   "フラン",   "フランシン",   "フリーダ",
   "ギャビー",   "ガブリエラ",   "ガブリエル",   "ギャラクシナ",
   "ガナ",   "ガビア",   "ジョージア",   "ガートルード",
   "ジーナ",   "ジョバンナ",   "グロリア",   "ゴルダ",
   "グレイス",   "グレタ",   "グレッチェン",   "グベン",
   "グエンドリン",   "ギネス",   "ヘイリー",   "ハラ",
   "ヘイリー",   "ハンナ",   "ハーモニー",   "ハリエット",
   "ハーレイ",   "ヘーゼル",   "ヘザー",   "ヘレン",
   "ヘレナ",   "ヘルガ",   "ヒルダ",   "ホリー",
   "ホーリー",   "オナー",   "イーダ",   "イロナ",
   "イルゼ",   "イングリッド",   "イレーネ",   "アイリス",
   "イザベル",   "イサベラ",   "イザベル",   "アイラ",
   "イバナ",   "アイビー",   "イジー",   "ジャクリン",
   "ジェイダ",   "ジェイド",   "ジェーン",   "ジャネット",
   "ジャネ",   "ジャニス",   "ジャニュエリ",   "ジャケリネ",
   "ジャスミン",   "ジャスマン",   "ジェン",   "ジェニファー",
   "ジェニー",   "ジェシカ",   "ジル",   "ジリアン",
   "ジョアン",   "ジョアナ",   "ジョディ",   "ジョーディ",
   "ジョセフィーヌ",   "ジョイ",   "ジューディス",   "ジュディ",
   "ジュリア",   "ジュリアーナ",   "ジュリー",   "ジュリエット",
   "ジュリエッタ",   "ジューン",   "ジャスティナ",   "ジャスティン",
   "ケイトリン",   "ケイリー",   "カレン",   "カリーナ",
   "カーラ",   "カルメン",   "カタリーン",   "ケイト",
   "ケイトリン",   "カテリーナ",   "カサリン",   "キャスリン",
   "キャシー",   "ケイティ",   "カトリーナ",   "ケイ",
   "ケイラ",   "ケイリー",   "キーリー",   "ケイシャ",
   "キキ",   "キルスティン",   "クララ",   "クリステル",
   "クリステン",   "クリスティ",   "クリスティン",   "クリスタル",
   "レイシー",   "レイニー",   "ラナ",   "ラーラ",
   "ラリサ",   "ラトーヤ",   "ローラ",   "ローレン",
   "ローリー",   "ラベンダー",   "リア",   "レア",
   "リーラ",   "レイア",   "ライラ",   "レナ",
   "レクシー",   "レイナ",   "リリアナ",   "リリス",
   "リリー",   "リリ",   "リナ",   "リンダ",
   "リサ",   "リブ",   "リズ",   "リーザ",
   "リザベス",   "リズベス",   "リジー",   "ロイス",
   "ロニーナ",   "ロレッタ",   "ロレーヌ",   "ローリィ",
   "ルアンヌ",   "ルアン",   "ルイーザ",   "ルイーズ",
   "ルカ",   "ルシア",   "ルーシー",   "ルッキ",
   "ルイサ",   "ルナ",   "リディア",   "リン",
   "リーン",   "リネット",   "ライラ",   "マドンナ",
   "マグス",   "ミリアム",   "マンディ",   "マンゴー",
   "マヌエラ",   "マーシャ",   "マーシー",   "マーガレット",
   "マルガレーテ",   "マルガリータ",   "マージ",   "マーギット",
   "マリア",   "マリアン",   "マリアーナ",   "マレリン",
   "マリーベル",   "メアリー",   "マリエル",   "マリリン",
   "マリナ",   "マリオン",   "マーレ",   "マリーナ",
   "マリーン",   "マーシャ",   "マータ",   "マーサ",
   "マーティナ",   "マリー",   "メリーアン",   "マチルダ",
   "モーラ",   "モーリン",   "マクシン",   "マヤ",
   "マユミ",   "メイジー",   "メディア",   "メグ",
   "メーガン",   "ミーガン",   "メグミ",   "メラニー",
   "メリンダ",   "メリッサ",   "メロディ",   "メルバニ",
   "メルセデス",   "ミリサ",   "ミア",   "ミシェル",
   "ミッシェル",   "ミカ",   "ミレナ",   "ミリー",
   "ミミ",   "マイナル",   "ミンディ",   "ミニー",
   "ミランダ",   "モリー",   "モニカ",   "モニーク",
   "モーラ",   "ナデジダ",   "ナディア",   "ナディヌ",
   "ナージャ",   "ナン",   "ナンシー",   "ナオミ",
   "ナタリア",   "ナタリー",   "ナターシャ",   "ネル",
   "ネリ",   "ネリー",   "ニコル",   "ニコレット",
   "ニーナ",   "ノエミ",   "ノラ",   "ノーマ",
   "オクトーバー",   "オルガ",   "オリビア",   "オプラ",
   "オルリー",   "パム",   "パメラ",   "パンドラ",
   "パトリシア",   "パティ",   "ポーラ",   "ポーレット",
   "ポーリン",   "ピーチ",   "パール",   "ペギー",
   "ペネロープ",   "ペニー",   "ペチュニア",   "フィービィー",
   "フィリス",   "パイパー",   "ピロシュカ",   "ポリーナ",
   "ポリー",   "プラーシュ",   "プリシラ",   "プルーデンス",
   "レイチェル",   "ラシェル",   "レイチェル",   "ラッチェル",
   "ラガド",   "ラモナ",   "ラーナ",   "ラニア",
   "ラファエラ",   "ラクエル",   "レイリン",   "レベッカ",
   "レジーナ",   "ルネ",   "リタ",   "ロミ",
   "ローザ",   "ロザリー",   "ロザリンド",   "ロザリンダ",
   "ロザーナ",   "ロザンヌ",   "ロベルタ",   "ローズ",
   "ローズマリー",   "ロージー",   "ロクサーヌ",   "ロクサン",
   "ロズ",   "ルツ",   "ルーサン",   "サブリナ",
   "サブリゼ",   "サジダ",   "サリー",   "サマンサ",
   "サミア",   "サミラ",   "サンドラ",   "サラ",
   "サーラ",   "サティア",   "セバ",   "セルマ",
   "セレナ",   "シャニークワ",   "シャナ",   "シャロン",
   "シェナン",   "シェリー",   "シャーリー",   "シャーン",
   "シャン",   "シルビア",   "ソフィア",   "ソフィー",
   "ソーナリ",   "ソニア",   "ゾフィア",   "ゾフィー",
   "ソラヤ",   "ステイシー",   "スティシィ",   "ステフ",
   "ステファニー",   "スハ",   "サマー",   "スー",
   "スーザン",   "スザンナ",   "スザンヌ",   "スージー",
   "スベトラーナ",   "シルビー",   "タバサ",   "タビサ",
   "タマラ",   "ヤマヤ",   "タミー",   "タラ",
   "タワンダ",   "テレサ",   "テリ",   "テッサ",
   "タチアナ",   "テリーサ",   "ザイラ",   "ティア",
   "ティフ",   "ティファニー",   "ティーファ",   "ティナ",
   "トニー",   "トーリ",   "トリシア",   "トリッシュ",
   "トルディ",   "タイラ",   "バレンティナ",   "バレリア",
   "バレリ",   "バンパイラ",   "バネッサ",   "ビーナス",
   "ベレナ",   "ベロニカ",   "ベスナ",   "バージニア",
   "ビッキー",   "ビキー",   "ビクトリア",   "バイオレット",
   "ビサラ",   "ビビアン",   "ボニータ",   "ワンダ",
   "ウェンディ",   "ウーピー",   "ウィルヘルミーナ",   "ウィロー",
   "ウィルマ",   "ウィニフレッド",   "ジニア",   "エカテリーナ",
   "ヨーコ",   "ヨランダ",   "ユリア",   "イボンヌ",
   "ザハワ",   "ザリーナ",   "ゼナ",   "ゼルダ",
   "ゾーイ",   "ゾフィア",   "ジョーフィア",   "ズザナ"
   };

   // these names should not appear in the male or female
   // or great white male patriarch first name lists, only here
   static const char *gender_neutral_first_names[] =
   {
   "エイドリアン",   "アキラ",   "アレックス",   "アレクシス",
   "アリ",   "エンジェル",   "エリアル",   "アシュレイ",
   "ビバリー",   "ビリー",   "ブレア",   "ボビー",
   "ボビー",   "ブレット",   "ブリート",   "カメロン",
   "カミーユ",   "ケイシー",   "チャス",   "チャズ",
   "クリス",   "コディー",   "コーリー",   "コートニー",
   "ダナ",   "フランキー",   "ハイデン",   "ヒラリー",
   "ケリー",   "ジャッキー",   "ジェイミー",   "ジェイデン",
   "ジーン",   "ジェス",   "ジョ",   "ジョーダン",
   "ジョイス",   "ジュン",   "ケルシー",   "ケルジー",
   "ケネディ",   "キム",   "キンバリー",   "キンバリー",
   "クリス",   "リー",   "レス",   "レスリー",
   "レズリー",   "リンジー",   "リンゼー",   "ローガン",
   "ルー",   "マディソン",   "マオ",   "マックス",
   "メル",   "モーガン",   "ナット",   "ニッキ",
   "ニッキー",   "ノエル",   "オーリー",   "ページ",
   "ペイジ",   "パリ",   "パット",   "ランマ",
   "レイブン",   "ライリー",   "ロビン",   "ローワン",
   "サム",   "サンディ",   "サシャ",   "シャロン",
   "シドニー",   "スティーブ",   "テイラー",   "テリー",
   "トレイシー",   "バル",   "ユェンピン",   "ユリ"
   };

   // these Arch-Conservative names also all appear under the male names list too
   // and NONE of them are female or gender-neutral
   // (no "Chris", that can be short for Christine or Christina)
   static const char *great_white_male_patriarch_first_names[] =
   {
   "アラン",   "アンディ",   "アーサー",   "ベン",
   "ビル",   "ボブ",   "ブラド",   "ブライアン",
   "カール",   "コリン",   "ダン",   "デイブ",
   "デニス",   "ディック",   "ドナルド",   "ダグ",
   "エド",   "エドワード",   "エリック",   "フランク",
   "ゲイリー",   "グレッグ",   "ハリー",   "ヘンリー",
   "ジェームス",   "ジェイソン",   "ジェフ",   "ジェリー",
   "ジェシー",   "ジム",   "ジョー",   "ジョン",
   "ジョシュ",   "ケン",   "ケビン",   "カイル",
   "ラリー",   "ルーク",   "マーク",   "マット",
   "マイク",   "ニック",   "ポール",   "ピーター",
   "レイ",   "リック",   "ロジャー",   "ロン",
   "ライアン",   "スコット",   "スティーブ",   "テッド",
   "ティム",   "トム",   "トミー",   "ウォルト"
   };

   strcpy(str,"");

   int roll, nametable;

   // If we don't care if the name is male or female, pick one randomly
   // This ensures gender balance in the names chosen
   if(gender == GENDER_NEUTRAL)
      gender = (LCSrandom(2)?GENDER_MALE:GENDER_FEMALE);

   // For white male Arch-Conservative politicians
   if(gender == GENDER_WHITEMALEPATRIARCH)
      nametable = GENDER_WHITEMALEPATRIARCH;

   // Assign a name from the available names for each gender
   if(gender == GENDER_MALE)
   {
      // Roll on the number of gender-specific names,
      // plus the number of gender-neutral names
      roll = LCSrandom(len(male_first_names) +
                       len(gender_neutral_first_names));
      // Decide whether to use a gender-specific name
      // or a gender-neutral name
      if(roll >= len(gender_neutral_first_names))
         nametable = GENDER_MALE;
      else
         nametable = GENDER_NEUTRAL;
   }
   else if(gender == GENDER_FEMALE)
   {
      // (Same here, just use the number of female names instead)
      roll = LCSrandom(len(female_first_names) +
                       len(gender_neutral_first_names));
      if(roll >= len(gender_neutral_first_names))
         nametable = GENDER_FEMALE;
      else
         nametable = GENDER_NEUTRAL;
   }

   if(nametable == GENDER_MALE)
      strcat(str, pickrandom(male_first_names));
   else if(nametable == GENDER_FEMALE)
      strcat(str, pickrandom(female_first_names));
   else if(nametable == GENDER_NEUTRAL)
      strcat(str, pickrandom(gender_neutral_first_names));
   else if(nametable == GENDER_WHITEMALEPATRIARCH)
      strcat(str, pickrandom(great_white_male_patriarch_first_names));
   else
      strcat(str, "エラール");
}
/* gets a random last name */
void lastname(char *str, bool archconservative)
//{{{ Last Name
{
   // note: every last name should only occur ONCE in either this list
   // or the Arch-Conservative list
   static const char *regular_last_names[] =
   {
   "アビー", "アボット", "アブズグ", "アブラモビッチ",
   "アダムソン", "アドキンス", "アフリカ", "アギレラ",
   "アハメド", "アーン", "アランソン", "オルコット",
   "アルダ", "アリ", "アランショー", "アレー",
   "アルバレス", "アンドレス", "アニストン", "アナン",
   "アントラー", "アップルトン", "アラファト", "アームステッド",
   "アーナズ", "アートフィールド", "アシュモア", "アル＝アサド",
   "アサンジ", "エアーズ", "エイクロイド", "アズレ",
   "バコール", "ベーコン", "ベアード", "ボールドウィン",
   "バルゴ", "バログ", "バーラーニ", "バロー",
   "バーウィック", "ボーモント", "ベッカー", "ベンディクス",
   "バイデン", "バーキン", "ビトン", "ブランチャード",
   "ブリッツァ", "ボガート", "ボッグス", "ボルジャー",
   "ブッカー", "ボサンケ", "ブラッドベリ", "ブラッドリー",
   "ブラッドショー", "ブランディス", "ブリュースター", "ブレイヤー",
   "ブライトマン", "ブリスコー", "ブラウンリー", "ブライアント",
   "バックマン", "バックナー", "バグビー", "バンプ",
   "バントン", "バーグホフ", "ブッチャー", "バトラー",
   "バット", "バターマン", "バットマン", "カーベリー",
   "カー", "カーソン", "カーター", "カートライト",
   "カストロ", "カバレロ", "カビル", "チェンバレン",
   "チャン", "チャンドラー", "チェン", "チャニング",
   "チャオ", "チャウ", "チャベス", "チアン",
   "チュン", "チルドレス", "チャイルズ", "チルトン",
   "チウ", "チョ", "チョウイ", "チョムスキー",
   "チャウ", "チュ", "チャブ", "ツォン",
   "クラビン", "クリントン", "クルーニー", "コッフィ",
   "コーエン", "コルコード.", "コロンブ", "コナー",
   "コーパースミス", "コープランド", "コッポラ", "コルデロ",
   "コスグローブ", "コトレル", "コート", "クラフト",
   "クリッチュリー", "クロフト", "クロムウェル", "クロス",
   "クロウ", "クロウソン", "クルーズ", "クオモ",
   "カーニュー", "カトラス", "カトラー", "Dahan",
   "Damon", "Danes", "Dangerfield", "Dante",
   "Darnand", "Dash", "Dawkins", "Daveson",
   "Day", "Dean", "Delgado", "DeLorean",
   "Dench", "De Niro", "Dent", "Dentz",
   "Di'az", "DiMeo", "Domi'nguez", "Dorgan",
   "Dorsey", "Doucette", "Douglas", "Downey",
   "Downing", "Drummond", "Duell", "Dukakis",
   "Duval", "Earle", "Ebert", "Edwards",
   "Einstein", "English", "Escobar", "Ericson",
   "Eubanks", "al-Fadil", "Fairbanks", "Fairchild",
   "Falco", "Falstaff", "Farkas", "Farnsworth",
   "Farr", "Faulkner", "Feingold", "Fekete",
   "Fenoglio", "Fiddlebottom", "Filler", "Fimple",
   "Fingleton", "Finn", "Flo'rez", "Fortmuller",
   "France", "Frank", "Franken", "Frost",
   "Friend", "Fudge", "Fulsom", "Furley",
   "Fushimi", "Galindo", "Gao", "Garci'a",
   "Garnier", "Gatien", "Gelbart", "Gephardt",
   "Gilbert", "Gillmouth", "Gilpin", "Ginsberg",
   "Ginsburg", "Godwin", "Gleaves", "Goldberg",
   "Goldstein", "Go'mez", "Gonza'lez", "Goodman",
   "Gore", "Gorbachev", "Govorov", "Grant",
   "Grayson", "Green", "Greenberg", "Grijalva",
   "Grover", "Gu", "Guo", "Gupta",
   "Gutie'rrez", "Guy", "Hala'sz", "Hall",
   "Hammond", "Han", "Hann", "Hannemann",
   "Hatcher", "Hawking", "Hayashi", "Hayes",
   "Haymer", "He", "Headley", "Heath",
   "Hellmann", "Helton", "Hemingway", "Hendren",
   "Hendrix", "Hepburn", "Hepditch", "Hewson",
   "Heyduke", "Hiaasen", "Hilliard", "Himelstein",
   "Ho", "Hoddinott", "Holder", "Honda",
   "Hong", "Hooker", "Hope", "Hopper",
   "Hornberger", "Horva'th", "Houghton", "Houseman",
   "Howard", "Howe", "Hsu", "Hu",
   "Huang", "Huffington", "Hunnicutt", "Hussein",
   "Hutchison", "Hwang", "Ibarra", "Incledon",
   "Inking", "Inoue", "Irvin", "Irving",
   "Iscariot", "Issacson", "Ito^", "Ivanson",
   "Ives", "Jang", "Jefferson", "Jeong",
   "Jimison", "Jolie", "Jordan", "Joyce",
   "Juha'sz", "Justice", "Kagan", "Kaltenbrunner",
   "Kang", "Kao", "Kardashian", "Karzai",
   "Kato^", "Keaton", "Keats", "Keene",
   "Keitel", "Kennedy", "Kershaw", "Kesten",
   "Kilbourne", "Kilmer", "Kim", "Kimura",
   "Kindale", "Kinslow", "Kiss", "Kitchen",
   "Kobayashi", "Kokernot", "Koprowski", "Kova'cs",
   "Krasow", "Krieger", "Krishna", "Krugman",
   "Kucinich", "Kunstler", "Kurosawa", "Kwok",
   "Kwon", "bin Laden", "Lakatos", "Lam",
   "LaSaga", "Lauder", "Law", "Lee",
   "Leeves", "Lengyel", "Lenin", "Lennon",
   "Levy", "Lewinsky", "Leyden", "Li",
   "Lim", "Lin", "Lincoln", "Linville",
   "Lipman", "Liu", "Lo", "Loeb",
   "Logsdon", "Lombard", "London", "Lo'pez",
   "Lovecraft", "Lowcourt", "Lowerly", "Lucas",
   "Luna", "Luo", "Lushington", "Luzinski",
   "Lyles", "Lynam", "Van Lynden", "Lyons",
   "Ma", "MacKinnon", "MacLeod", "MacNeil",
   "Macy", "Maddow", "Malach", "Malkovich",
   "Malone", "Mandela", "Mann", "Manning",
   "Mansfield", "March", "Marsden", "Marsh",
   "Marshall", "Marx", "Mathers", "Matheson",
   "Mathewson", "Matthews", "Matsumoto", "Maxwell",
   "McAdams", "McAllister", "McBroom", "McCorkell",
   "McFadden", "McFatridge", "McFaul", "McFly",
   "McGee", "McGovern", "McGrath", "McGraw",
   "McGuinness", "McIntosh", "McIntyre", "McKenzie",
   "McKinney", "McLeod", "McMurray", "McNabb",
   "McPhail", "McPherson", "McQueen", "Meek",
   "Meffert", "Meir", "Mele'ndez", "Mene'ndez",
   "Me'sza'ros", "Metzger", "Mifune", "Milburn",
   "Miyamoto", "Mizrahi", "Mohammed", "Molna'r",
   "Mondale", "Montag", "Montalvo", "Molotov",
   "Moon", "Moore", "Morales", "Morrison",
   "Morrow", "Morton", "Mosley", "Mu:ller",
   "Murrell", "Muscat", "Musharraf", "Muskhelishvili",
   "Mussa", "Myatt", "Nader", "Nagel",
   "Nagelberg", "Nagy", "Nakagawa", "Nakahara",
   "Nakamura", "Nallet", "Nance", "Nash",
   "Nathanson", "Necker", "Ne'meth", "Nettles",
   "Neuwirth", "Nevinson", "Newberry", "Newhook",
   "Ng", "Nicolle", "Nickson", "O",
   "Obama", "Obeid", "Oberlander", "Ochs",
   "Ogden", "Oh", "Ola'h", "Olbermann",
   "Olde", "Olds", "Oldsmar", "Ollerenshaw",
   "Orlando", "Ortiz", "Osborne", "Pacino",
   "Paltrow", "Paoletti", "Palm", "Papp",
   "Park", "Parking", "Parr", "Patel",
   "Patterson", "Pearson", "Peck", "Pegg",
   "Pelosi", "Pelton", "Pendergrass", "Penn",
   "Peretz", "Pe'rez", "Pert", "Petermann",
   "Pfeiffer", "Pickett", "Picketty", "Piercey",
   "Pitt", "Pommerencke", "Pomper", "Porcaro",
   "Porter", "Postman", "Pound", "Powers",
   "Probst", "Proudfoot", "Puente", "Purcell",
   "Putin", "Quaid", "Queen", "Quennell",
   "Quick", "Quilico", "Quilliam", "Quilty",
   "Quincey", "Quinlivan", "Quinn", "Quirk",
   "Rabban", "Rackard", "Ra'cz", "Radman",
   "Rainey", "Rami'rez", "Ramos", "Randell",
   "Rangel", "Ransom", "Rappaport", "Raskin",
   "Rastrelli", "Rather", "Ratzenberger", "Ravenhill",
   "Rawls", "Read", "Reading", "Reasoner",
   "Van Rechteren", "Redford", "Redman", "Redwine",
   "Reed", "Reekers", "Reid", "Rendell",
   "Rexford", "Ricci", "Richter", "Rideout",
   "Riffle", "Rivera", "Rivers", "Rodham",
   "Rodri'guez", "Rojo", "Roland", "Roosevelt",
   "Rose", "Rosenberg", "Ross", "Rota",
   "Rothstein", "Roy", "Roylance", "Rudkin",
   "Rush", "Rushworth", "LaRussa", "Russell",
   "Ryman", "Sabella", "Saddler", "Sadler",
   "Saito^", "Sa'nchez", "Sanders", "Sansome",
   "Santiago", "Santos", "Sasaki", "Sato^",
   "Savedra", "Saxton", "Scales", "Scardino",
   "Schmitt", "Schneider", "Schro:der", "Schmidt",
   "Schumacher", "Schumer", "Schuster", "Scully",
   "Scurfield", "Sealock", "Seay", "Seinfeld",
   "Sellers", "Semin", "Seo", "Serling",
   "Sewall", "Sexton", "Shackleton", "Shagwell",
   "al-Shamie", "Sharpe", "Sharpton", "Shedd",
   "Sheen", "Shelton", "Shengde", "Shepard",
   "Shepardson", "Sheppard", "Shew", "Shields",
   "Shiller", "Shimazu", "Shimizu", "Shin",
   "Shipman", "Shipp", "Sho", "Shrapnal",
   "Shrum", "Schulz", "Shumway", "Shurin",
   "Sidebottom", "Siegel", "Siever", "da Silva",
   "Silverman", "Silverstein", "Simmons", "Simms",
   "Simon", "Singh", "al-Sisi", "Skidmore",
   "Skirrow", "Skutnik", "Skye", "Skyler",
   "Slaten", "Smalley", "Smallwood", "Smart",
   "Smyth", "Snead", "Snook", "Snowden",
   "Soli's", "Sommer", "Somner", "Song",
   "Soren", "Sotomayor", "Souter", "Spacey",
   "Spielberg", "Spasov", "Spitzer", "Stalin",
   "Stang", "Stark", "Starkweather", "Stassen",
   "Stelling", "Stephenson", "Sternin", "Stevens",
   "Stevenson", "Stewart", "Stockton", "Storm",
   "Storms", "Stiver", "Strain", "Straley",
   "Straub", "Stripe", "Strossen", "Suave",
   "Suiter", "Sulaiman", "Sun", "Surnow",
   "Susman", "Suzuki", "Swain", "Swaine",
   "Swift", "Swit", "Symington", "Symonds",
   "Szabo'", "Tabb", "Tailboys", "Taka'cs",
   "Takahashi", "Takayoshi", "Talbert", "Talbot",
   "Talbott", "Talty", "Tanaka", "Tanner",
   "Tarantino", "Tatters", "Taubman", "Tayo",
   "Teige", "Tell", "Tennent", "Tenney",
   "Tenpenny", "Terrill", "Testore", "Tetley",
   "Thalberg", "Thomaz", "Thomson", "Thorne",
   "Threepwood", "Thurgood", "Thurlow", "Tickell",
   "Tillett", "Tillinghast", "Tillson", "Tillsley",
   "Timmonds", "Tippett", "Tisdall", "Tishman",
   "Titcomb", "Tobin", "Todd", "Todhunter",
   "Toft", "Tolbert", "Tolkien", "Tolson",
   "Tonelli", "Toogood", "Tooke", "Toole",
   "To'th", "Towne", "Townsend", "Trafford",
   "Travolta", "Trebek", "Trotsky", "Truman",
   "Truong", "Tsui", "Tubbs", "Tubman",
   "Twain", "Tymchyshyn", "Ulmer", "Underhill",
   "Underdown", "Underwood", "Updike", "Usher",
   "Ussher", "Valdez", "Vallance", "Vance",
   "Varga", "Vasilevsky", "Venus", "Villa",
   "Villanueva", "Viscuso", "Voland", "Vulcar",
   "Wade", "Wadsworth", "Walden", "Walwyn",
   "Wang", "Ward", "Warman", "Warr",
   "Warren", "Washington", "Watanabe", "Waxman",
   "Weathers", "Webber", "Weber", "Weeks",
   "Weller", "Wellstone", "Wendt", "Westlake",
   "Weston", "Weygand", "Whitehead", "Whitley",
   "Wickes", "Willett", "Williamson", "Willman",
   "Winchester", "Winfrey", "Winkelman", "Winslow",
   "Winter", "Wiseman", "Wolfe", "Wong",
   "Woodrow", "Woods", "Wu", "Wuornos",
   "Xu", "Xue", "Yamada", "Yamaguchi",
   "Yamamoto", "Yang", "Yankovic", "Yee",
   "Yeltsin", "Yerkovich", "Yi", "Yim",
   "Yoo", "Yoon", "Yoshida", "Youngblood",
   "Yu", "Yue", "Zachary", "Zadora",
   "Zakharov", "Zale", "Zapata", "Zappa",
   "Zedner", "Zedong", "Zhang", "Zhao",
   "Zhou", "Zhu", "Zicree", "Zito",
   "Zlotoff", "Zondervan", "Zucker", "Zumbach"
   };

   // these names are approved for use by Arch-Conservatives,
   // but will also sometimes appear as names for regular people too
   // last names for famous conservatives, fascists, European royalty, billionaires,
   // serial killers, and common, generic WASPy Anglo-Saxon names go here,
   // but be sure to exclude last names of famous liberals and communists,
   // instead those go in the previous list (otherwise we end up with
   // Arch-Conservatives with names like Bill Clinton!)
   static const char *archconservative_last_names[] =
   {
   "Adams", "Adelson", "Agnew", "Akin",
   "Alexander", "Alito", "Allen", "Ames",
   "Anderson", "Armey", "Armstrong", "Arnold",
   "Ashcroft", "Atwater", "Bachmann", "Bailey",
   "Baker", "Bakker", "Banks", "Barr",
   "Bates", "Baxter", "Beck", "Bennett",
   "Berkowitz", "Bernadotte", "Bezos", "Bianchi",
   "Bilderberg", "Black", "Blankenship", "Blum",
   "Boehner", "Bolton", "Bonaparte", "Bourbon",
   "Boyd", "Bozell", "Braganza", "Brandt",
   "Braun", "Breitbart", "Bremer", "Brooks",
   "Brown", "Buchanan", "Buckley", "Bundy",
   "Buono", "Burns", "Burr", "Burton",
   "Bush", "Byrd", "Callahan", "Cameron",
   "Campbell", "Cantor", "Carey", "Carlson",
   "Carlyle", "Carnegie", "Carpenter", "Chaffee",
   "Chambers", "Cheney", "Churchill", "Clark",
   "Clay", "Cobb", "Colbert", "Cole",
   "Coleman", "Collins", "Colt", "Cook",
   "Cooper", "Corll", "Coughlin", "Coulter",
   "Cox", "Crane", "Crockett", "Cruz",
   "Cunningham", "Dahmer", "Danson", "Darby",
   "Davidson", "Davis", "Decker", "Deere",
   "Delaney", "DeLay", "DeMint", "Diehl",
   "Discordia", "Disney", "Dixon", "Dobbs",
   "Dobson", "Dole", "Doyle", "Drake",
   "D'Souza", "Duke", "Duffield", "Dunham",
   "Dunlap", "Earp", "Ellison", "Evans",
   "Falwell", "Fawkes", "Fenderson", "Fields",
   "Fischer", "Fisher", "Fitzgerald", "Fitzpatrick",
   "Flake", "Flanders", "Fletcher", "Forbes",
   "Ford", "Foster", "Fox", "Franco",
   "Franklin", "Friedman", "Gacy", "Gallagher",
   "Galt", "Gates", "Gein", "Getty",
   "Gibson", "Gingrich", "Giuliani", "Glu:cksburg",
   "Gohmert", "Goldwater", "Goode", "Goodyear",
   "Graham", "Grammer", "Gray", "Gregg",
   "Griffin", "Grimaldi", "Hagee", "Hamilton",
   "Hannity", "Hanover", "Hansen", "Hapsburg",
   "Harper", "Harris", "Hastert", "Heidnik",
   "Heller", "Helms", "Henderson", "Henley",
   "Hess", "Hill", "Hinn", "Hitler",
   "Hoffmann", "Hogan", "Hohenzollern", "Holliday",
   "Holmes", "Hoover", "Hopkins", "Huckabee",
   "Hudson", "Hughes", "Jackson", "James",
   "Jameson", "Jenkins", "Johnson", "Jones",
   "Judge", "Kemper", "Kent", "Keyes",
   "King", "Kissinger", "Koch", "Koresh",
   "Kraft", "Krauthammer", "Kristol", "Kuklinski",
   "Lake", "Langley", "Lewis", "Limbaugh",
   "Little", "Logan", "Lott", "Lowe",
   "Luxembourg", "Lynch", "MacArthur", "MacGyver",
   "Mahoney", "McCain", "McCarthy", "McConnell",
   "McDonald", "McKinley", "McLaughlin", "McVeigh",
   "Medici", "Meyer", "Miller", "Mitchell",
   "Monroe", "Montana", "Morgan", "Morris",
   "Mullin", "Murphy", "Murray", "Mussolini",
   "Murdoch", "Myers", "Nelson", "Ness",
   "Newman", "Nielson", "Nixon", "North",
   "Novak", "Oakley", "O'Connor", "O'Keefe",
   "Orange", "O'Reilly", "Osman", "Osteen",
   "Palin", "Palmer", "Parker", "Paul",
   "Pendleton", "Perry", "Perot", "Peterson",
   "Phelps", "Pierce", "Pinkerton", "Potter",
   "Powell", "Presley", "Pryor", "Quayle",
   "Rader", "Rand", "Reagan", "Rehnquist",
   "Reynolds", "Rhodes", "Rice", "Richardson",
   "Roberts", "Robertson", "Robinson", "Rockefeller",
   "Romanov", "Romney", "Rothschild", "Rove",
   "Rubio", "Rumsfeld", "Rutherford", "Sanford",
   "Santorum", "Savage", "Savoy", "Sawyer",
   "Saxe-Coburg-Gotha", "Scalia", "Schlafly", "Scott",
   "Shanahan", "Shaw", "Shawcross", "Shelby",
   "Sherman", "Short", "Shuttleworth", "Simpson",
   "Skinner", "Smith", "Smithers", "Snow",
   "Snyder", "Sowell", "Spears", "Spencer",
   "Starr", "Sterling", "Stone", "Strauss",
   "Stuart", "Sullivan", "Sutcliffe", "Swaggart",
   "Swanson", "Sweeney", "Taft", "Taitz",
   "Taylor", "Templeton", "Thatcher", "Thomas",
   "Thompson", "Thurmond", "Trudeau", "Trump",
   "Tucker", "Tudor", "Turner", "Tyler",
   "Unruh", "Upton", "Voight", "Wagner",
   "Walker", "Wallace", "Walsh", "Walton",
   "Warner", "Watson", "Wayne", "Webster",
   "West", "Wettin", "White", "Whitman",
   "Wilcox", "Williams", "Wilson", "Windsor",
   "Wittelsbach", "Wood", "Wright", "Yates",
   "Yoder", "Young", "Zimmerman", "Zuckerberg"
   };

   strcpy(str,"");

   // For non-Arch-Conservatives, pick from ALL last names
   if(!archconservative)
   {
      // Roll on the number of non-Arch-Conservative last names,
      // plus the number of regular last names
      int roll = LCSrandom(len(regular_last_names) +
                           len(archconservative_last_names));
      // Decide whether to use an Arch-Conservative last name
      // or a regular last name
      archconservative = (roll >= len(regular_last_names));
   }
   // Now the archconservative variable might be true even if the function wasn't called that way,
   // but if it WAS called that way it's definitely true... this way non-Arch-Conservatives get
   // random last names out of all the last names, while Arch-Conservatives are limited to their own
   // last names

   if(archconservative)
      strcat(str, pickrandom(archconservative_last_names));
   else
      strcat(str, pickrandom(regular_last_names));
}



/* convert to half width katakana */
char *to_half(char *str)
{
   static const struct
   {
      char *full;
      char *half;
   }
   kana[] =
   {
      { "＝", "=" },
      { "・", "･" },
      { "ー", "ｰ" },
      { "ァ", "ｧ" },
      { "ア", "ｱ" },
      { "ィ", "ｨ" },
      { "イ", "ｲ" },
      { "ゥ", "ｩ" },
      { "ウ", "ｳ" },
      { "ェ", "ｪ" },
      { "エ", "ｴ" },
      { "ォ", "ｫ" },
      { "オ", "ｵ" },
      { "カ", "ｶ" },
      { "ガ", "ｶﾞ" },
      { "キ", "ｷ" },
      { "ギ", "ｷﾞ" },
      { "ク", "ｸ" },
      { "グ", "ｸﾞ" },
      { "ケ", "ｹ" },
      { "ゲ", "ｹﾞ" },
      { "コ", "ｺ" },
      { "ゴ", "ｺﾞ" },
      { "サ", "ｻ" },
      { "ザ", "ｻﾞ" },
      { "シ", "ｼ" },
      { "ジ", "ｼﾞ" },
      { "ス", "ｽ" },
      { "ズ", "ｽﾞ" },
      { "セ", "ｾ" },
      { "ゼ", "ｾﾞ" },
      { "ソ", "ｿ" },
      { "ゾ", "ｿﾞ" },
      { "タ", "ﾀ" },
      { "ダ", "ﾀﾞ" },
      { "チ", "ﾁ" },
      { "ヂ", "ﾁﾞ" },
      { "ッ", "ｯ" },
      { "ツ", "ﾂ" },
      { "ヅ", "ﾂﾞ" },
      { "テ", "ﾃ" },
      { "デ", "ﾃﾞ" },
      { "ト", "ﾄ" },
      { "ド", "ﾄﾞ" },
      { "ナ", "ﾅ" },
      { "ニ", "ﾆ" },
      { "ヌ", "ﾇ" },
      { "ネ", "ﾈ" },
      { "ノ", "ﾉ" },
      { "ハ", "ﾊ" },
      { "バ", "ﾊﾞ" },
      { "パ", "ﾊﾟ" },
      { "ヒ", "ﾋ" },
      { "ビ", "ﾋﾞ" },
      { "ピ", "ﾋﾟ" },
      { "フ", "ﾌ" },
      { "ブ", "ﾌﾞ" },
      { "プ", "ﾌﾟ" },
      { "ヘ", "ﾍ" },
      { "ベ", "ﾍﾞ" },
      { "ペ", "ﾍﾟ" },
      { "ホ", "ﾎ" },
      { "ボ", "ﾎﾞ" },
      { "ポ", "ﾎﾟ" },
      { "マ", "ﾏ" },
      { "ミ", "ﾐ" },
      { "ム", "ﾑ" },
      { "メ", "ﾒ" },
      { "モ", "ﾓ" },
      { "ャ", "ｬ" },
      { "ヤ", "ﾔ" },
      { "ュ", "ｭ" },
      { "ユ", "ﾕ" },
      { "ョ", "ｮ" },
      { "ヨ", "ﾖ" },
      { "ラ", "ﾗ" },
      { "リ", "ﾘ" },
      { "ル", "ﾙ" },
      { "レ", "ﾚ" },
      { "ロ", "ﾛ" },
      { "ワ", "ﾜ" },
      { "ヲ", "ｦ" },
      { "ン", "ﾝ" },
      { "ヴ", "ｳﾞ" },
      { NULL, NULL }
   }, *t;
   static char wide_str[256];
   char *p=str;

   strcpy(wide_str,"");

   while(*p!=0)
   {
      for(t=kana;t->half!=NULL;t++)
      {
         if(memcmp(p,t->full,strlen(t->full))==0)
         {
            break;
         }
      }

      if(t->half!=NULL)
      {
         strcat(wide_str,t->half);
         p+=strlen(t->full);
      }
      else
      {
         wide_str[strlen(wide_str)+1]=0;
         wide_str[strlen(wide_str)]=*p;
         p++;
      }
   }

   return wide_str;
}
