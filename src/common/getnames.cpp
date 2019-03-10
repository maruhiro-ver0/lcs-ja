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

std::string getactivity(activityst &act)
{
   switch(act.type)
   {
   case ACTIVITY_HOSTAGETENDING:
      {
         std::string str="の尋問";
         int pl=getpoolcreature(act.arg);
         if(pl!=-1) return pool[pl]->name+str;
         else return "バグ"+str;
      }
   case ACTIVITY_RECRUITING:
      return "スカウト活動";
   case ACTIVITY_REPAIR_ARMOR:
      return "服の修繕";
   case ACTIVITY_WHEELCHAIR:
      return "車椅子の調達";
   case ACTIVITY_STEALCARS:
      return "自動車泥棒";
   case ACTIVITY_POLLS:
      return "世論調査";
   case ACTIVITY_MAKE_ARMOR:
      return armortype[act.arg]->get_shortname()+"の作成";
   case ACTIVITY_TROUBLE:
      return "反抗";
   case ACTIVITY_PROSTITUTION:
      return "売春";
   case ACTIVITY_COMMUNITYSERVICE:
      return "社会奉仕";
   case ACTIVITY_GRAFFITI:
      return "落書き";
   case ACTIVITY_CCFRAUD:
      return "カード番号の不正取得";
   case ACTIVITY_DOS_RACKET:
      return "ウェブサイトへのゆすり";
   case ACTIVITY_DOS_ATTACKS:
      return "ウェブサイトへの攻撃";
   case ACTIVITY_HACKING:
      return "ハッキング";
   case ACTIVITY_SELL_TSHIRTS:
      return "Tシャツの販売";
   case ACTIVITY_SELL_ART:
      return "アートの販売";
   case ACTIVITY_TEACH_POLITICS:
      return "政治の教育";
   case ACTIVITY_TEACH_FIGHTING:
      return "戦闘の教育";
   case ACTIVITY_TEACH_COVERT:
      return "秘密工作の教育";
   case ACTIVITY_SELL_MUSIC:
      return "音楽の販売";
   case ACTIVITY_BURY:
      return "遺体の遺棄";
   case ACTIVITY_DONATIONS:
      return "募金の呼びかけ";
   case ACTIVITY_SELL_DRUGS:
      return "ケーキの販売";
   case ACTIVITY_VISIT:
      return location[act.arg]->getname(!location[act.arg]->is_city())+"への訪問";
   case ACTIVITY_HEAL:
      return "怪我の治療";
   case ACTIVITY_NONE:
      return "何もしない";
   case ACTIVITY_WRITE_LETTERS:
      return "新聞に投書";
   case ACTIVITY_WRITE_GUARDIAN:
      return "記事を書く";
   case ACTIVITY_CLINIC:
      return "無料診療所へ行く";
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
   case ACTIVITY_STUDY_ART:
   case ACTIVITY_STUDY_MUSIC:
   case ACTIVITY_STUDY_TEACHING:
   case ACTIVITY_STUDY_WRITING:
   case ACTIVITY_STUDY_LOCKSMITHING:
      return "授業に出席";
   case ACTIVITY_SLEEPER_LIBERAL:
      return "リベラル主義の宣伝";
   case ACTIVITY_SLEEPER_CONSERVATIVE:
      return "保守派との討論";
   case ACTIVITY_SLEEPER_SPY:
      return "スパイ活動";
   case ACTIVITY_SLEEPER_RECRUIT:
      return "スパイの調達";
   case ACTIVITY_SLEEPER_JOINLCS:
      return "活動を止める";
   case ACTIVITY_SLEEPER_SCANDAL:
      return "スキャンダルを起こす";
   case ACTIVITY_SLEEPER_EMBEZZLE:
      return "資金の横領";
   case ACTIVITY_SLEEPER_STEAL:
      return "備品を盗む";
   default:
      return "開発チームにバグを報告する";
   }
}

std::string gettitle(Creature &cr)
{
   if(cr.align==-1)
   {
      if(cr.juice<=-50)
      {
         if(law[LAW_FREESPEECH]==-2) return "社会の[ピー]";
         else return "社会のゴミ";
      }
      else if(cr.juice<=-10) return "保守の落伍者";
      else if(cr.juice<0) return "保守の厄介者";
      else if(cr.juice<10) return "愚かな保守";
      else if(cr.juice<50) return "誤った考えを持つ者";
      else if(cr.juice<100)
      {
         if(law[LAW_FREESPEECH]==-2) return "強固な保守";
         else return "強固な保守";
      }
      else if(cr.juice<200)
      {
         if(law[LAW_FREESPEECH]==-2) return "心を持たない[不快な者]";
         else return "心を持たないロクデナシ";
      }
      else if(cr.juice<500) return "狂った自警団員";
      else if(cr.juice<1000) return "保守強硬派";
      else return "悪の権化";
   }
   else if(cr.align==0)
   {
      if(cr.juice<=-50)
      {
         if(law[LAW_FREESPEECH]==-2) return "社会の[ピー]";
         else return "社会のゴミ";
      }
      else if(cr.juice<=-10) return "落伍者";
      else if(cr.juice<0) return "非リベラルの厄介者";
      else if(cr.juice<10) return "非リベラル";
      else if(cr.juice<50) return "努力家";
      else if(cr.juice<100) return "尊敬すべき者";
      else if(cr.juice<200) return "実直な市民";
      else if(cr.juice<500) return "偉大な人";
      else if(cr.juice<1000) return "平和をもたらす者";
      else return "平和賞受賞者";
   }
   else
   {
      if(cr.juice<=-50)
      {
         if(law[LAW_FREESPEECH]==-2) return "社会の[ピー]";
         else return "社会のゴミ";
      }
      else if(cr.juice<=-10) return "落伍者";
      else if(cr.juice<0) return "厄介者";
      else if(cr.juice<10) return "市民";
      else if(cr.juice<50) return "活動家";
      else if(cr.juice<100) return "社会の危険因子";
      else if(cr.juice<200) return "革命家";
      else if(cr.juice<500) return "都市型ゲリラ";
      else if(cr.juice<1000) return "自由の守護者";
      else return "エリート・リベラル";
   }
}

std::string getview(short view,bool shortname)
{
   if(shortname) switch(view)
   {
   case VIEW_STALIN: return "スターリン主義";
   case VIEW_MOOD: return "世論";
   case VIEW_GAY: return "LGBTQの権利";
   case VIEW_DEATHPENALTY: return "死刑制度";
   case VIEW_TAXES: return "税金";
   case VIEW_NUCLEARPOWER: return "原子力";
   case VIEW_ANIMALRESEARCH: return "動物虐待";
   case VIEW_POLICEBEHAVIOR: return "警察";
   case VIEW_TORTURE: return "拷問";
   case VIEW_PRISONS: return "刑務所";
   case VIEW_INTELLIGENCE: return "プライバシー";
   case VIEW_FREESPEECH: return "言論の自由";
   case VIEW_GENETICS: return "遺伝子研究";
   case VIEW_JUSTICES: return "司法制度";
   case VIEW_GUNCONTROL: return "銃規制";
   case VIEW_SWEATSHOPS: return "労働組合";
   case VIEW_POLLUTION: return "環境問題";
   case VIEW_CORPORATECULTURE: return "企業";
   case VIEW_CEOSALARY: return "CEOの報酬";
   case VIEW_WOMEN: return "女性の権利";
   case VIEW_CIVILRIGHTS: return "市民の権利";
   case VIEW_DRUGS: return "薬物";
   case VIEW_IMMIGRATION: return "移民";
   case VIEW_MILITARY: return "軍隊";
   case VIEW_AMRADIO: return "AMラジオ";
   case VIEW_CABLENEWS: return "ケーブルニュース";
   //case VIEW_POLITICALVIOLENCE: return "political violence";
   case VIEW_LIBERALCRIMESQUAD:
   case VIEW_LIBERALCRIMESQUADPOS: return "LCS";
   case VIEW_CONSERVATIVECRIMESQUAD: return "CCS";
   default: return "バグ";
   }
   else switch(view)
   {
   case VIEW_STALIN: return "スターリン主義";
   case VIEW_MOOD: return "世論";
   case VIEW_GAY: return "LGBTQの権利";
   case VIEW_DEATHPENALTY: return "残酷な刑罰";
   case VIEW_TAXES: return "税制度";
   case VIEW_NUCLEARPOWER: return "メルトダウン";
   case VIEW_ANIMALRESEARCH: return "動物虐待";
   case VIEW_POLICEBEHAVIOR: return "警察官の職権乱用";
   case VIEW_TORTURE: return "拷問";
   case VIEW_PRISONS: return "刑務所";
   case VIEW_INTELLIGENCE: return "プライバシー権";
   case VIEW_FREESPEECH: return "言論の自由";
   case VIEW_GENETICS: return "遺伝子組換えの危険性";
   case VIEW_JUSTICES: return "司法制度";
   case VIEW_GUNCONTROL: return "銃乱射事件";
   case VIEW_SWEATSHOPS: return "労働者の権利";
   case VIEW_POLLUTION: return "環境問題";
   case VIEW_CORPORATECULTURE: return "企業腐敗";
   case VIEW_CEOSALARY: return "高額なCEOの報酬";
   case VIEW_WOMEN: return "男女平等";
   case VIEW_CIVILRIGHTS: return "人種の平等";
   case VIEW_DRUGS: return "薬物に関する抑圧的な法律";
   case VIEW_IMMIGRATION: return "移民の権利";
   case VIEW_MILITARY: return "軍事支出";
   case VIEW_AMRADIO: return "AMラジオのプロパガンダ";
   case VIEW_CABLENEWS: return "ケーブルニュースのウソ";
   //case VIEW_POLITICALVIOLENCE: return "The Need For Action";
   case VIEW_LIBERALCRIMESQUAD: return "我々は何者か";
   case VIEW_LIBERALCRIMESQUADPOS: return "なぜ我々はロックか";
   case VIEW_CONSERVATIVECRIMESQUAD: return "CCSのテロリズム";
   default: return "ソフトのバグ";
   }
}



std::string getlaw(int l)
{
   switch(l)
   {
   case LAW_ABORTION:return "中絶の権利";
   case LAW_ANIMALRESEARCH:return "動物の権利"; // a.k.a. "Animal Research"
   case LAW_POLICEBEHAVIOR:return "警察権の規制"; // a.k.a. "Police Behavior"
   case LAW_PRIVACY:return "プライバシー権"; // a.k.a. "Privacy"
   case LAW_DEATHPENALTY:return "死刑制度"; // a.k.a. "Capital Punishment"
   case LAW_NUCLEARPOWER:return "原子力政策";
   case LAW_POLLUTION:return "公害";
   case LAW_LABOR:return "労働法"; // a.k.a. "Workers' Rights"
   case LAW_GAY:return "同性愛者の権利"; // a.k.a. "Homosexual Rights"
   case LAW_CORPORATE:return "会社法"; // a.k.a. "Corporate Ethics"
   case LAW_FREESPEECH:return "言論の自由"; // a.k.a. "Freedom of Speech"
   case LAW_FLAGBURNING:return "国旗焼却";
   case LAW_GUNCONTROL:return "銃規制";
   case LAW_TAX:return "税制度"; // a.k.a. "Tax Law"
   case LAW_WOMEN:return "女性の権利";
   case LAW_CIVILRIGHTS:return "市民の権利";
   case LAW_DRUGS:return "薬物規制"; // a.k.a. "Drug Law"
   case LAW_IMMIGRATION:return "移民政策";
   case LAW_ELECTIONS:return "選挙制度";
   case LAW_MILITARY:return "軍事支出";
   case LAW_PRISONS:return "受刑者の権利";
   case LAW_TORTURE:return "人権";
   default:return "バグ";
   }
}

std::string cityname()
{
   static const char *city_names[] =
   {
      /* City population < 100,000 = listed once if the city is somehow important
         (i.e., biggest city in a U.S. state or territory, or most important city in a
          metropolitan area with over 200,000 people)
         100,000 < City population <   200,000 = listed once
         200,000 < City population <   400,000 = listed twice
         400,000 < City population <   600,000 = listed 3 times
         600,000 < City population < 1,000,000 = listed 4 times
       1,000,000 < City population < 5,000,000 = listed 5 times
       5,000,000 < City population = city listed 6 times and each of its 5 its boroughs listed 1-2 times
       Anyway, for states/territories without big cities their biggest city is listed once.  */
      "アビリーン TX",
      "アグアディヤ PR", // city in Puerto Rico
      "アクロン OH",
      "オールバニ NY",
      "アルバカーキ NM", "アルバカーキ NM", "アルバカーキ NM",
      "アレクサンドリア VA",
      "アレンタウン PA",
      "アマリロ TX",
      "アナハイム CA", "アナハイム CA", "アナハイム CA",
      "アンカレッジ AK", "アンカレッジ AK", "アンカレッジ AK",
      "アナーバー MI",
      "アンティオック CA",
      "アップルトン WI",
      "アーリントン TX", "アーリントン TX", "アーリントン TX",
      "アーバダ CO",
      "アシュビル NC",
      "アトランティックシティ NJ",
      "アセンズ GA",
      "アトランタ GA", "アトランタ GA", "アトランタ GA",
      "オーガスタ GA",
      "オーロラ CO", "オーロラ CO", "オーロラ CO",
      "オーロラ IL",
      "オースティン TX", "オースティン TX", "オースティン TX", "オースティン TX",
      "ベーカーズフィールド CA", "ベーカーズフィールド CA", "ベーカーズフィールド CA",
      "ボルチモア MD", "ボルチモア MD", "ボルチモア MD", "ボルチモア MD",
      "バーンスタブル MA",
      "バトンルージュ LA", "バトンルージュ LA",
      "バヤモン PR", "バヤモン PR", // city in Puerto Rico
      "ベルビュー WA",
      "ベリンハム WA",
      "ボーモント TX",
      "バークレー CA",
      "ビリングス MT",
      "ビロクシ MS",
      "ビンガムトン NY",
      "バーミングハム AL", "バーミングハム AL",
      "ボイシ ID", "ボイシ ID",
      "ボストン MA", "ボストン MA", "ボストン MA", "ボストン MA",
      "ボルダー CO",
      "ブレマートン WA",
      "ブリッジポート CT",
      "ブロークンアロー OK",
      "ブルックリン NY", "ブルックリン NY",
      "ブラウンズビル TX",
      "バッファロー NY", "バッファロー NY",
      "バーバンク CA",
      "バーリントン VT",
      "ケンブリッジ MA",
      "カグアス PR", // city in Puerto Rico
      "カントン OH",
      "ケープコーラル FL",
      "カールスバッド CA",
      "カロライナ PR", // city in Puerto Rico
      "キャロルトン TX",
      "ケーリー NC",
      "シーダーラピッズ IA",
      "センテニアル CO",
      "シャンペーン IL",
      "チャンドラー AZ", "チャンドラー AZ",
      "チャールストン SC",
      "チャールストン WV",
      "シャーロット NC", "シャーロット NC", "シャーロット NC", "シャーロット NC",
      "シャーロットアマリー VI", // biggest city in U.S. Virgin Islands
      "シャーロッツビル VA",
      "チャタヌーガ TN",
      "チェサピーク VA", "チェサピーク VA",
      "シャイアン WY",
      "シカゴ IL", "シカゴ IL", "シカゴ IL", "シカゴ IL", "シカゴ IL",
      "チコ CA",
      "チュラビスタ CA", "チュラビスタ CA",
      "シンシナティ OH", "シンシナティ OH",
      "クラークスビル TN",
      "クリアウォーター FL",
      "クリーブランド OH", "クリーブランド OH", "クリーブランド OH",
      "カレッジステーション TX",
      "コロラドスプリングス CO", "コロラドスプリングス CO", "コロラドスプリングス CO",
      "コロンビア MO",
      "コロンビア SC",
      "コロンバス GA", "コロンバス, GA",
      "コロンバス OH", "コロンバス OH", "コロンバス OH", "コロンバス OH",
      "コンコード CA",
      "コーラルスプリングス FL",
      "コロナ CA",
      "コーパスクリスティ TX", "コーパスクリスティ TX", "コーパスクリスティ TX",
      "コスタメサ CA",
      "クレストビュー FL",
      "ダラス TX", "ダラス TX", "ダラス TX", "ダラス TX", "ダラス TX",
      "デイリーシティ CA",
      "ダベンポート IA",
      "デイトン OH",
      "デイトナビーチ FL",
      "デデド GU", // biggest city in Guam
      "デントン TX",
      "デンバー CO", "デンバー CO", "デンバー CO", "デンバー CO",
      "デモイン IA", "デモイン IA",
      "デトロイト MI", "デトロイト MI", "デトロイト MI", "デトロイト MI",
      "ダウニー CA",
      "ダルース MN",
      "ダーラム NC", "ダーラム NC",
      "エルカホン CA",
      "エルモンテ CA",
      "エルパソ TX", "エルパソ TX", "エルパソ TX", "エルパソ TX",
      "エルジン IL",
      "エルクグローブ CA",
      "エルクハート IN",
      "エリザベス NJ",
      "エリー PA",
      "エスコンディード CA",
      "ユージーン OR",
      "エバンズビル IN",
      "エバレット WA",
      "フェアフィールド CA",
      "ファーゴ ND",
      "フェイエットビル AR",
      "ファイエットビル NC", "ファイエットビル NC",
      "フリント MI",
      "フローレンス SC",
      "フォンタナ CA", "フォンタナ CA",
      "フォートコリンズ CO",
      "フォートローダーデール FL",
      "フォートスミス AR",
      "フォートウェイン IN", "フォートウェイン IN",
      "フォートワース TX", "フォートワース TX", "フォートワース TX", "フォートワース TX",
      "フリーモント CA", "フリーモント CA",
      "フレズノ CA", "フレズノ CA", "フレズノ CA",
      "フリスコ TX",
      "フラートン TX",
      "ゲインズビル FL",
      "ガーデングローブ CA",
      "ガーランド TX", "ガーランド TX",
      "ギルバート AZ", "ギルバート AZ",
      "グレンデール AZ", "グレンデール AZ",
      "グレンデール CA",
      "グランドプレーリー TX",
      "グランドラピッズ MI",
      "グリーリー CO",
      "グリーンベイ WI",
      "グリーンズボロ NC", "グリーンズボロ NC",
      "グリーンビル SC",
      "グレシャム OR",
      "ヘイガーズタウン MD",
      "ハンプトン VA",
      "ハリスバーグ PA",
      "ハートフォード CT",
      "ヘイワード CA",
      "ヘムステッド NY",
      "ヘンダーソン NV", "ヘンダーソン NV",
      "ハイアリア FL", "ハイアリア FL",
      "ヒッコリー NC",
      "ハイポイント NC",
      "ハリウッド CA",
      "ハリウッド FL",
      "ホノルル HI", "ホノルル HI", "ホノルル HI",
      "ホーマ LA",
      "ヒューストン TX", "ヒューストン TX", "ヒューストン TX", "ヒューストン TX", "ヒューストン TX",
      "ハンティントン WV",
      "ハンティントンビーチ CA",
      "ハンツビル AL",
      "インディペンデンス MO",
      "インディアナポリス IN", "インディアナポリス IN", "インディアナポリス IN", "インディアナポリス IN",
      "イングルウッド CA",
      "アーバイン CA", "アーバイン CA",
      "アービング TX", "アービング TX",
      "ジャクソン MS",
      "ジャクソンビル FL", "ジャクソンビル FL", "ジャクソンビル FL", "ジャクソンビル FL",
      "ジャージーシティ NJ", "ジャージーシティ NJ",
      "ジョンソンシティ TN",
      "ジョリエット IL",
      "カラマズー MI",
      "カンザスシティ KS",
      "カンザスシティ MO", "カンザスシティ MO", "カンザスシティ MO",
      "ケント WA",
      "キリーン TX",
      "キングスポート TN",
      "ノックスビル TN",
      "ラファイエット IN",
      "ラファイエット LA",
      "レイクチャールズ LA",
      "レイクハバスシティ AZ",
      "レイクランド FL",
      "レイクウッド CO",
      "ランカスター CA",
      "ランカスター PA",
      "ランシング MI",
      "ラレド TX", "ラレド TX",
      "ラスクルーセス NM",
      "ラスベガス NV", "ラスベガス NV", "ラスベガス NV", "ラスベガス NV",
      "ルイスビル TX",
      "レキシントン KY", "レキシントン KY", "レキシントン KY",
      "リンカーン NE", "リンカーン NE",
      "リトルロック AR",
      "ロングビーチ CA", "ロングビーチ CA", "ロングビーチ CA",
      "ロングアイランド NY", "ロングアイランド NY", "ロングアイランド NY", "ロングアイランド NY",
      "ロングビュー TX",
      "ロサンゼルス CA", "ロサンゼルス CA", "ロサンゼルス CA", "ロサンゼルス CA", "ロサンゼルス CA",
      "ルイビル KY", "ルイビル KY", "ルイビル KY", "ルイビル KY",
      "ローウェル MA",
      "ラボック TX", "ラボック TX",
      "リンチバーグ VA",
      "メイコン GA",
      "マディソン WI", "マディソン WI",
      "マンチェスター NH",
      "マンハッタン NY", "マンハッタン NY",
      "マヤグエス PR", // city in Puerto Rico
      "マッカレン TX",
      "マッキニー TX",
      "メドフォード OR",
      "メンフィス TN", "メンフィス TN", "メンフィス TN", "メンフィス TN",
      "マーセド CA",
      "メサ AZ", "メサ AZ", "メサ AZ",
      "メスキート TX",
      "マイアミ FL", "マイアミ FL", "マイアミ FL",
      "マイアミガーデンズ FL",
      "ミッドランド TX",
      "ミルウォーキー WI", "ミルウォーキー WI", "ミルウォーキー WI",
      "ミネアポリス MN", "ミネアポリス MN", "ミネアポリス MN",
      "ミラマー FL",
      "モービル AL",
      "モデスト CA", "モデスト CA",
      "モンゴメリー AL", "モンゴメリー AL",
      "モレノバレー CA", "モレノバレー CA",
      "マーフリーズボロ TN",
      "マリエータ CA",
      "マートルビーチ SC",
      "ネイパービル IL",
      "ネイプルズ FL",
      "ナッシュビル TN", "ナッシュビル TN", "ナッシュビル TN", "ナッシュビル TN",
      "ニューヘイブン CT",
      "ニューロンドン CT",
      "ニューオーリンズ LA", "ニューオーリンズ LA", "ニューオーリンズ LA",
      "ニューヨーク NY", "ニューヨーク NY", "ニューヨーク NY", "ニューヨーク NY", "ニューヨーク NY", "ニューヨーク NY",
      "ニューアーク NJ", "ニューアーク NJ",
      "ニューポート RI",
      "ニューポートニューズ VA",
      "ノーフォーク VA", "ノーフォーク VA",
      "ノーマン OK",
      "ノースチャールストン SC",
      "ノースラスベガス NV", "ノースラスベガス NV",
      "ノーウォーク CA",
      "オークランド CA", "オークランド CA", "オークランド CA",
      "オカラ FL",
      "オーシャンサイド CA",
      "オデッサ TX",
      "オグデン UT",
      "オクラホマシティ OK", "オクラホマシティ OK", "オクラホマシティ OK", "オクラホマシティ OK",
      "オレイサ KS",
      "オリンピア WA",
      "オマハ NE", "オマハ NE", "オマハ NE",
      "オンタリオ CA",
      "オレンジ CA",
      "オーランド FL", "オーランド FL",
      "オーバーランドパーク KS",
      "オックスナード CA", "オックスナード CA",
      "パームベイ FL",
      "パームデール CA",
      "パサデナ CA",
      "パサデナ TX",
      "パターソン NJ",
      "パーランド TX",
      "ペンブロークパインズ FL",
      "ペンサコーラ FL",
      "ピオリア IL",
      "ピオリア AZ",
      "フィラデルフィア PA", "フィラデルフィア PA", "フィラデルフィア PA", "フィラデルフィア PA", "フィラデルフィア PA",
      "フェニックス AZ", "フェニックス AZ", "フェニックス AZ", "フェニックス AZ", "フェニックス AZ",
      "ピッツバーグ PA", "ピッツバーグ PA", "ピッツバーグ PA",
      "プレイノ TX", "プレイノ TX",
      "ポモナ CA",
      "ポンパノビーチ FL",
      "ポンセ PR", // city in Puerto Rico
      "ポートセントルーシー FL",
      "ポートランド ME",
      "ポートランド OR", "ポートランド OR", "ポートランド OR", "ポートランド OR",
      "ポキプシー NY",
      "プレスコット AZ",
      "プロビデンス RI",
      "プロボ UT",
      "プエブロ CO",
      "クイーンズ NY", "クイーンズ NY",
      "ローリー NC", "ローリー NC", "ローリー NC",
      "ランチョクカモンガ CA",
      "レディング PA",
      "リノ NV", "リノ NV",
      "リアルト CA",
      "リチャードソン TX",
      "リッチランド WA",
      "リッチモンド CA",
      "リッチモンド VA", "リッチモンド VA",
      "リバーサイド CA", "リバーサイド CA", "リバーサイド CA",
      "ロアノーク VA",
      "ロチェスター MN",
      "ロチェスター NY", "ロチェスター NY",
      "ロックフォード IL",
      "ローズビル CA",
      "ラウンドロック TX",
      "サクラメント CA", "サクラメント CA", "サクラメント CA",
      "サイパン MP", // biggest city in Northern Mariana Islands
      "セイラム OR",
      "サリナス CA",
      "ソールズベリー MD",
      "ソルトレイクシティ UT",
      "サンアントニオ TX", "サンアントニオ TX", "サンアントニオ TX", "サンアントニオ TX", "サンアントニオ TX",
      "サンバーナーディーノ CA", "サンバーナーディーノ CA",
      "サンディエゴ CA", "サンディエゴ CA", "サンディエゴ CA", "サンディエゴ CA", "サンディエゴ CA",
      "サンフランシスコ CA", "サンフランシスコ CA", "サンフランシスコ CA", "サンフランシスコ CA",
      "サンノゼ CA", "サンノゼ CA", "サンノゼ CA", "サンノゼ CA",
      "サンフアン PR", "サンフアン PR", // biggest city in Puerto Rico
      "サンルイスオビスポ CA",
      "サンマテオ CA",
      "サンタアナ CA", "サンタアナ CA", "サンタアナ CA",
      "サンタクララ CA",
      "サンタクラリタ CA",
      "サンタクルーズ CA",
      "サンタマリア CA",
      "サンタローザ CA",
      "サラソータ FL",
      "サバンナ GA",
      "スコッツデール AZ", "スコッツデール AZ",
      "スクラントン PA",
      "シアトル WA", "シアトル WA", "シアトル WA", "シアトル WA",
      "シュリーブポート LA", "シュリーブポート LA",
      "スーフォールズ SD",
      "シミバレー CA",
      "サウスベンド IN",
      "スパータンバーグ SC",
      "スポケーン WA", "スポケーン WA",
      "スプリングフィールド IL",
      "スプリングフィールド MA",
      "スプリングフィールド MO",
      "セントルイス MO", "セントルイス MO", "セントルイス MO",
      "セントポール MN", "セントポール MN",
      "セントピーターズバーグ FL", "セントピーターズバーグ FL",
      "スタンフォード CT",
      "スタテンアイランド NY",
      "スターリングハイツ MI",
      "ストックトン CA", "ストックトン CA",
      "サニーベール CA",
      "サプライズ AZ",
      "シラキュース NY",
      "タコマ WA", "タコマ WA",
      "タフナ AS", // biggest city in American Samoa
      "タラハシー FL",
      "タンパ FL", "タンパ FL", "タンパ FL",
      "テメキュラ CA",
      "テンピ AZ",
      "ブロンクス NY", "ブロンクス NY",
      "ソーントン CO",
      "サウザンドオークス CA",
      "トレド OH", "トレド OH",
      "トピカ KS",
      "トーランス CA",
      "トレントン NJ",
      "タスカルーサ AL",
      "ツーソン AZ", "ツーソン AZ", "ツーソン AZ",
      "タルサ OK", "タルサ OK", "タルサ OK",
      "タイラー TX",
      "ユーティカ NY",
      "バレーホ CA",
      "バンクーバー WA",
      "ベンチュラ CA",
      "ビクタービル CA",
      "バージニアビーチ VA", "バージニアビーチ VA", "バージニアビーチ VA",
      "バイセイリア CA",
      "ウェーコ TX",
      "ウォーレン MI",
      "ワシントン DC", "ワシントン DC", "ワシントン DC", "ワシントン DC",
      "ウォーターバリー CT",
      "ウェストコビーナ CA",
      "ウェストジョーダン UT",
      "ウェストパームビーチ FL",
      "ウェストバレーシティ UT",
      "ウェストミンスター CO",
      "ホワイトプレインズ NY",
      "ウィチタ KS", "ウィチタ KS", "ウィチタ KS",
      "ウィチタフォールズ TX",
      "ウィルミントン DE",
      "ウィルミントン NC",
      "ウィンストンセーラム NC", "ウィンストンセーラム NC",
      "ウースター MA",
      "ヤキマ WA",
      "ヨンカーズ NY",
      "ヨーク PA",
      "ヤングスタウン OH",
      "ユマ AZ"
   };
   return pickrandom(city_names);
}

/* Allow the player to enter a name with an optional default */
void enter_name(int y,int x,char *name,int len,const char* defname)
{
   refresh();
   keypad(stdscr,FALSE);
   raw_output(FALSE);
   echo();
   curs_set(1);
   mvgetnstr(y,x,name,len-1); //-1 because 'len' is normally the full space available and we need one for a terminator.
   curs_set(0);
   noecho();
   raw_output(TRUE);
   keypad(stdscr,TRUE);
   if((defname!=NULL)&&(strncmp(name,"",len-1)==0)) strncpy(name,defname,len-1);
   name[len-1]='\0';
}

std::string getlawflag(int type)
{
   switch(type)
   {
   case LAWFLAG_TREASON:return "国家反逆";
   case LAWFLAG_TERRORISM:return "テロ";
   case LAWFLAG_MURDER:return "一級殺人";
   case LAWFLAG_KIDNAPPING:return "誘拐";
   case LAWFLAG_BANKROBBERY:return "銀行強盗";
   case LAWFLAG_ARSON:return "放火";
   case LAWFLAG_BURNFLAG:return(law[LAW_FLAGBURNING]==-2?"国旗不敬":"国旗焼却");
   case LAWFLAG_SPEECH:return "煽動";
   case LAWFLAG_BROWNIES:return "違法薬物取引";
   case LAWFLAG_ESCAPED:return "脱獄";
   case LAWFLAG_HELPESCAPE:return "逃走援助";
   case LAWFLAG_JURY:return "陪審員買収";
   case LAWFLAG_RACKETEERING:return "詐欺";
   case LAWFLAG_EXTORTION:return "恐喝";
   case LAWFLAG_ARMEDASSAULT:return "銃器使用";
   case LAWFLAG_ASSAULT:return "武器使用";
   case LAWFLAG_CARTHEFT:return "自動車窃盗";
   case LAWFLAG_CCFRAUD:return "カード番号不正取得";
   case LAWFLAG_THEFT:return "窃盗";
   case LAWFLAG_PROSTITUTION:return "売春";
   case LAWFLAG_HIREILLEGAL:return(law[LAW_IMMIGRATION]<1?"不法移民雇用":"不法雇用");
   //case LAWFLAG_GUNUSE:return "違法な武器の使用";
   //case LAWFLAG_GUNCARRY:return "違法な武器の運搬";
   case LAWFLAG_COMMERCE:return "業務妨害";
   case LAWFLAG_INFORMATION:return "違法アクセス";
   case LAWFLAG_BURIAL:return "死体遺棄";
   case LAWFLAG_BREAKING:return "不法侵入";
   case LAWFLAG_VANDALISM:return "器物損壊";
   case LAWFLAG_RESIST:return "逮捕抵抗";
   case LAWFLAG_DISTURBANCE:return "治安妨害";
   case LAWFLAG_PUBLICNUDITY:return "公然猥褻";
   case LAWFLAG_LOITERING:return "浮浪";
   default:return "バグ";
   }
}

// shortname defaults to false
std::string getmonth(int month, bool shortname)
{
   switch(month)
   {
   case  1:return (shortname?"1月":"1月");
   case  2:return (shortname?"2月":"2月");
   case  3:return (shortname?"3月":"3月");
   case  4:return (shortname?"4月":"4月");
   case  5:return "5月";
   case  6:return "6月";
   case  7:return "7月";
   case  8:return (shortname?"8月":"8月");
   case  9:return (shortname?"9月":"9月");
   case 10:return (shortname?"10月":"10月");
   case 11:return (shortname?"11月":"11月");
   case 12:return (shortname?"12月":"12月");
   default:return (shortname?"バグ":"バグ月");
   }
}

std::string getalign(signed char alignment,bool capitalize)
{
   switch(alignment)
   {
   case ALIGN_ARCHCONSERVATIVE: return "保守強硬";
   case ALIGN_CONSERVATIVE: return "保守";
   case ALIGN_MODERATE: return (capitalize?"穏健":"穏健");
   case ALIGN_LIBERAL: return "リベラル";
   case ALIGN_ELITELIBERAL: return "エリートリベラル";
   case ALIGN_STALINIST: return "スターリン主義";
   default: return "バグ";
   }
}
