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

#include <externs.h>

// Finds a location with the corresponding type and returns
// its index in the location array
int findlocation(int type, int city=-1)
{
   if(!multipleCityMode) city=-1;
   for(int i=0;i<len(location);i++)
      if(location[i]->type==type&&(location[i]->city==city||city==-1)) return i;
   return -1;
}

int findlocation_id(int id)
{
   for(int i=0;i<len(location);i++)
      if(location[i]->id==id) return i;
   return -1;
}

// Locations - Construct a new location with the specified parameters
Location::Location(char type_, int parent_)
 : type(type_),city(-1),parent(parent_),renting(RENTING_NOCONTROL),needcar(false),hidden(false),upgradable(false)
{
   if(this->parent!=-1)
   {
      this->needcar = location[this->parent]->needcar;
      this->mapped = location[this->parent]->mapped;
      this->area = location[this->parent]->area;
      this->city = location[this->parent]->city;
   }
   if(this->city < 0 && multipleCityMode)
      this->city=this->type;
   initlocation(*this);
}

Location* Location::addchild(char type_)
{
   Location *newloc = new Location(type_, findlocation(this->type, this->city));
   location.push_back(newloc);
   return newloc;
}

void Location::init()
{
   haveflag=0;
   newrental=0;
   heat=0;
   heat_protection=0;
   closed=0;
   mapped=0;
   highsecurity=0;
   initOtherRNG(mapseed);
   changes.clear();
   compound_walls=0;
   compound_stores=0;
   front_business=-1;
}

/* Settings for shortname_ (true is 1 and false is 0, by the way):
 * -1: entire name is long, no matter what
 *  0: first part of place name is long, and if there's a city at the end it's short
 *  1: first part of the name is short unless the place itself is a city in which case it's long, and if there's a city at the end it's short
 *  2: entire name is short, no matter what */
string Location::getname(signed char shortname_, bool include_city)
{
   string str;
   if(!multipleCityMode) include_city=false;

   if((shortname_>=1&&type!=city)||shortname_>=2) {
      if(this->front_business!=-1)
         str=this->front_shortname;
      else
         str=this->shortname;
   } else {
      if(this->front_business!=-1)
         str=this->front_name;
      else
         str=this->name;
   }

   if(include_city&&type!=city) {
      string cityname=location[findlocation(city, city)]->getname(shortname_+2);
      if(str=="Downtown")
         return str+" "+cityname;
      if(str=="University District"||str=="U-District"||str=="Industrial District"||str=="I-District"||
         str=="Shopping"||str=="Outskirts"||str=="Seaport Area"||str=="Seaport"||str=="Outskirts & Orange County"||
         str=="都心部"||str=="大学周辺"||str=="工業地区"||str=="都市の外れ"||str=="ショッピング")
         return cityname+" "+str;
      if(str=="City Outskirts")
         return cityname+" Outskirts";
      if(str=="Arlington")
         return str+(shortname_<0?", Virginia":", VA");
      if(str=="Hollywood"||str=="Greater Hollywood")
         return str+(shortname_<0?", California":", CA");
      if(str== "Manhattan"||str=="Manhattan Island"||str=="Brooklyn & Queens"||str=="Long Island"||str=="The Bronx")
         return str+(shortname_<0?", New York":", NY");
      str+=", "+cityname;
   }
   return str;
}

string Location::city_description()
{
   switch(type)
   {
   case SITE_CITY_SEATTLE: return "LCS誕生の地";
   case SITE_CITY_LOS_ANGELES: return "ハリウッドとビジネス";
   case SITE_CITY_NEW_YORK: return "ウォールストリートと巨大メディア";
   case SITE_CITY_WASHINGTON_DC: return "この国の首都";
   case SITE_CITY_CHICAGO: return "マフィアの本拠地";
   case SITE_CITY_DETROIT: return "アメリカの殺人事件のトップ";
   case SITE_CITY_ATLANTA: return "南部の誇り";
   case SITE_CITY_MIAMI: return "常夏の楽園";
   default: return "";
   }
}

bool Location::can_be_fortified()
{
   if(!upgradable) return false;
   switch(type)
   {
   default:
      return !fortified();
   case SITE_OUTDOOR_BUNKER:
   case SITE_BUSINESS_BARANDGRILL:
      return false;
   }
}

bool Location::fortified()
{
   switch(type)
   {
   default:
      return compound_walls & COMPOUND_BASIC;
   case SITE_OUTDOOR_BUNKER:
      return true;
   }
}

bool Location::can_be_trapped()
{
   if(!upgradable) return false;
   return !trapped();
}

bool Location::can_install_tanktraps()
{
   if(!upgradable) return false;
   switch(type)
   {
   default:
      return !tank_traps();
   case SITE_BUSINESS_BARANDGRILL:
   case SITE_OUTDOOR_BUNKER:
   case SITE_RESIDENTIAL_BOMBSHELTER:
      return false;
   }
}

bool Location::tank_traps()
{
   switch(type)
   {
   default:
      return compound_walls & COMPOUND_TANKTRAPS;
   case SITE_OUTDOOR_BUNKER:
   case SITE_RESIDENTIAL_BOMBSHELTER:
      return true;
   }
}

bool Location::can_have_businessfront()
{
   if(!upgradable) return false;
   switch(type)
   {
   default:
      return !has_business_front();
   case SITE_BUSINESS_BARANDGRILL:
   case SITE_OUTDOOR_BUNKER:
   case SITE_RESIDENTIAL_BOMBSHELTER:
      return false;
   }
}

bool Location::has_business_front()
{
   return front_business!=-1||
          type==SITE_BUSINESS_BARANDGRILL;
}

bool Location::bomb_resistant()
{
   return type==SITE_RESIDENTIAL_BOMBSHELTER;
}

bool Location::part_of_justice_system()
{
   return type==SITE_GOVERNMENT_POLICESTATION||
          type==SITE_GOVERNMENT_COURTHOUSE||
          type==SITE_GOVERNMENT_PRISON;
}

bool Location::duplicatelocation()
{
   for(int l=0;l<len(location);l++)
   {
      if(location[l]==this)
         continue;

      if(type!=SITE_RESIDENTIAL_SHELTER&&!strcmp(location[l]->name,this->name))
         return true;

      if(location[l]->front_business!=-1&&this->front_business!=-1&&
        !strcmp(location[l]->front_shortname,this->front_shortname))
         return true;
   }
   return 0;
}

void Location::update_heat_protection()
{
   int l;
   for(l=0;l<len(location);l++)
   {
      if(location[l]==this)
         break;
   }
   if(l==len(location))
   {
      heat_protection=0;
      return;
   }
   int numpres=0;
   heat_protection=0;
   for(int p=0;p<len(pool);p++)
   {
      if(pool[p]->location!=l) continue; // People not at this base don't count
      if(!pool[p]->alive) continue; // Dead people don't count
      numpres++;
   }

   // Determine how effective your current safehouse
   // is at keeping the police confused
   switch(location[l]->type)
   {
   case SITE_INDUSTRY_WAREHOUSE:
      if(location[l]->front_business!=-1)
         heat_protection+=12; // Business front -- high protection
      else
         heat_protection+=0; // Abandoned warehouse -- no protection
      break;
   case SITE_RESIDENTIAL_SHELTER:
      heat_protection+=0; // Homeless shelter -- no protection
      break;
   case SITE_RESIDENTIAL_TENEMENT:
      heat_protection+=4; // Lower class housing -- low protection
      break;
   case SITE_RESIDENTIAL_APARTMENT:
      heat_protection+=8; // Middle class housing -- medium protection
      break;
   case SITE_RESIDENTIAL_BOMBSHELTER:
   case SITE_OUTDOOR_BUNKER:
   case SITE_BUSINESS_BARANDGRILL:
   case SITE_RESIDENTIAL_APARTMENT_UPSCALE:
      heat_protection+=12; // Upper class housing -- high protection
      break;
   }

   if(law[LAW_FLAGBURNING]==-2&&location[l]->haveflag) heat_protection+=6; // More protection if the flag is sacred
   else if(law[LAW_FLAGBURNING]!=-2&&location[l]->haveflag) heat_protection+=2; // Some if the flag isn't
   else if(law[LAW_FLAGBURNING]==-2&&!(location[l]->haveflag)) heat_protection-=2; // Lose some if it is and you have no flag
   else { } // None if it isn't and you have no flag

   if(heat_protection<0) heat_protection=0;

   heat_protection*=5;
   if(heat_protection>95) heat_protection=95;
}

void Location::rename(const char* name_, const char* shortname_)
{
   strcpy(this->name, name_);
   strcpy(this->shortname, shortname_);
}

/* daily - seeds and names a site (will re-seed and rename if used after start) */
void initlocation(Location &loc)
{  // NOTE: make sure to keep code here matching code in updateworld_laws() in monthly.cpp for when names are changed
   loc.init();

   char str[80];

   switch(loc.type)
   {
   case SITE_CITY_SEATTLE: loc.rename("シアトル", "SEA"); break;
   case SITE_CITY_LOS_ANGELES: loc.rename("ロサンゼルス", "LA"); break;
   case SITE_CITY_NEW_YORK: loc.rename("ニューヨーク", "NYC"); break;
   case SITE_CITY_CHICAGO: loc.rename("シカゴ", "CHI"); break;
   case SITE_CITY_DETROIT: loc.rename("デトロイト", "DET"); break;
   case SITE_CITY_ATLANTA: loc.rename("アトランタ", "ATL"); break;
   case SITE_CITY_MIAMI: loc.rename("マイアミ", "MI"); break;
   case SITE_CITY_WASHINGTON_DC: loc.rename("ワシントンDC", "DC"); break;
   case SITE_DOWNTOWN: loc.rename("都心部", "都心部"); break;
   case SITE_UDISTRICT: loc.rename("大学周辺", "大学周辺"); break;
   case SITE_COMMERCIAL: loc.rename("ショッピング", "ｼｮｯﾋﾟﾝｸﾞ"); break;
   case SITE_INDUSTRIAL: loc.rename("工業地区", "工業地区"); break;
   case SITE_OUTOFTOWN: loc.rename("都市の外れ", "都市外"); break;
   case SITE_TRAVEL: loc.rename("旅行", "旅行"); break;
   case SITE_GOVERNMENT_POLICESTATION:
      if(law[LAW_POLICEBEHAVIOR]==-2&&law[LAW_DEATHPENALTY]==-2) {
         loc.rename("死の部隊の司令部", "部隊司令");
      } else {
         loc.rename("警察署", "警察署");
      } break;
   case SITE_GOVERNMENT_COURTHOUSE:
      if(law[LAW_DEATHPENALTY]==-2) {
         loc.rename("最後の審判の館", "審判の館");
      } else {
         loc.rename("裁判所", "裁判所");
      } break;
   case SITE_GOVERNMENT_FIRESTATION:
      if(law[LAW_FREESPEECH]==-2) {
         loc.rename("焚書課司令部", "焚書課");
         loc.hidden = false;
      } else {
         loc.rename("消防署", "消防署");
         loc.hidden = true;
      } break;
   case SITE_GOVERNMENT_PRISON:
      if(law[LAW_PRISONS]==-2)
      {
         switch(LCSrandom(5))
         {
            case 0:strcpy(loc.name,"幸福の");break;
            case 1:strcpy(loc.name,"陽気な");break;
            case 2:strcpy(loc.name,"静寂の");break;
            case 3:strcpy(loc.name,"緑の");break;
            case 4:strcpy(loc.name,"花蜜の");break;
         }
         switch(LCSrandom(5))
         {
            case 0:strcat(loc.name,"谷");break;
            case 1:strcat(loc.name,"草原");break;
            case 2:strcat(loc.name,"丘");break;
            case 3:strcat(loc.name,"林");break;
            case 4:strcat(loc.name,"森");break;
         }
         strcat(loc.name," 強制労働キャンプ");
         strcpy(loc.shortname,"ｷｬﾝﾌﾟ");
      }
      else
      {
         lastname(loc.name,true);
         strcat(loc.name," 刑務所");
         strcpy(loc.shortname,"刑務所");
      }
      break;
   case SITE_INDUSTRY_NUCLEAR:
      if(law[LAW_NUCLEARPOWER]==2) {
         loc.rename("核廃棄所", "廃棄所");
      } else {
         loc.rename("原子力発電所", "原発");
      } break;
   case SITE_GOVERNMENT_INTELLIGENCEHQ:
      if(law[LAW_PRIVACY]==-2 && law[LAW_POLICEBEHAVIOR]==-2) {
         loc.rename("愛情省", "愛情省");
      } else {
         loc.rename("中央情報局", "中央情報局");
      } break;
   case SITE_GOVERNMENT_ARMYBASE:
      if(law[LAW_MILITARY]==-2) {
         loc.rename("平和省", "平和省");
      } else {
         lastname(loc.name,true);
         strcat(loc.name," 陸軍基地");
         strcpy(loc.shortname,"基地");
      } break;
   case SITE_GOVERNMENT_WHITE_HOUSE:
      loc.rename("ホワイトハウス", "ﾎﾜｲﾄﾊｳｽ");
      break;
   case SITE_CORPORATE_HEADQUARTERS:
      loc.rename("企業本社","本社");
      break;
   case SITE_BUSINESS_BANK:
      loc.rename("アメリカ・バンク", "銀行");
      break;
   case SITE_BUSINESS_PAWNSHOP:
      lastname(loc.name,true);
      if(law[LAW_GUNCONTROL]==ALIGN_ELITELIBERAL)
         strcat(loc.name," 質店");
      else
         strcat(loc.name," 質と銃");
      strcpy(loc.shortname,"質店");
      break;
   case SITE_CORPORATE_HOUSE:
      if(law[LAW_CORPORATE]==-2&&law[LAW_TAX]==-2)
         loc.rename("CEOの城", "CEO城");
      else
         loc.rename("CEOの邸宅", "CEO邸宅");
      break;
   case SITE_RESIDENTIAL_SHELTER:
      loc.rename("ホームレス・シェルター", "ｼｪﾙﾀｰ");
      break;
   case SITE_INDUSTRY_WAREHOUSE:
      do {
         strcpy(loc.name,"閉鎖された");
         /*lastname(loc.name,true);
         strcat(loc.name," ");*/

         switch(LCSrandom(10))
         {
         case 0:
            strcat(loc.name,"食肉工場");
            strcpy(loc.shortname,"食肉工場");
            break;
         case 1:
            strcat(loc.name,"倉庫");
            strcpy(loc.shortname,"倉庫");
            break;
         case 2:
            strcat(loc.name,"製紙工場");
            strcpy(loc.shortname,"製紙工場");
            break;
         case 3:
            strcat(loc.name,"セメント工場");
            strcpy(loc.shortname,"ｾﾒﾝﾄ工場");
            break;
         case 4:
            strcat(loc.name,"肥料工場");
            strcpy(loc.shortname,"肥料工場");
            break;
         case 5:
            strcat(loc.name,"工作機械工場");
            strcpy(loc.shortname,"機械工場");
            break;
         case 6:
            strcat(loc.name,"製鉄所");
            strcpy(loc.shortname,"製鉄所");
            break;
         case 7:
            strcat(loc.name,"パック工場");
            strcpy(loc.shortname,"ﾊﾟｯｸ工場");
            break;
         case 8:
            strcat(loc.name,"おもちゃ工場");
            strcpy(loc.shortname,"ｵﾓﾁｬ工場");
            break;
         case 9:
            strcat(loc.name,"ビル");
            strcpy(loc.shortname,"ﾋﾞﾙ");
            break;
         }
      } while(loc.duplicatelocation());
      break;
   case SITE_INDUSTRY_POLLUTER:
      switch(LCSrandom(5))
      {
      case 0:
         loc.rename("アルミ工場", "ｱﾙﾐ工場");
         break;
      case 1:
         loc.rename("プラスチック工場", "ﾌﾟﾗ工場");
         break;
      case 2:
         loc.rename("石油精製所", "石油所");
         break;
      case 3:
         loc.rename("自動車工場", "車工場");
         break;
      case 4:
         loc.rename("化学工場", "化学工場");
         break;
      }
      break;
   case SITE_MEDIA_CABLENEWS:
      loc.rename("ケーブルニュース局", "ﾆｭｰｽ局");
      break;
   case SITE_MEDIA_AMRADIO:
      loc.rename("AMラジオ局", "ﾗｼﾞｵ局");
      break;
   case SITE_RESIDENTIAL_APARTMENT_UPSCALE:
      do {
         lastname(loc.name,true);
         strcpy(loc.shortname,loc.name);
         strcat(loc.name," マンション");
         strcat(loc.shortname,"ﾏﾝｼｮﾝ");
      } while(loc.duplicatelocation());
      break;
   case SITE_RESIDENTIAL_APARTMENT:
      do {
         lastname(loc.name,true);
         strcpy(loc.shortname,loc.name);
         strcat(loc.name," アパート");
         strcat(loc.shortname,"ｱﾊﾟｰﾄ");
      } while(loc.duplicatelocation());
      break;
   case SITE_RESIDENTIAL_TENEMENT:
      do {
         do {
            lastname(loc.name,true);
         } while(len(loc.name)>7);
         strcat(loc.name,"通り団地");
         strcpy(loc.shortname, "団地");
      } while(loc.duplicatelocation());
      break;
   case SITE_HOSPITAL_UNIVERSITY:
      loc.rename("大学病院", "病院");
      break;
   case SITE_HOSPITAL_CLINIC:
      loc.rename("無料診療所", "診療所");
      break;
   case SITE_LABORATORY_GENETIC:
      lastname(loc.name,true);
      strcat(loc.name," 遺伝子研究所");
      strcpy(loc.shortname,"遺伝子研究所");
      break;
   case SITE_LABORATORY_COSMETICS:
      lastname(loc.name,true);
      strcat(loc.name," 化粧品研究所");
      strcpy(loc.shortname,"化粧品研究所");
      break;
   case SITE_BUSINESS_CARDEALERSHIP:
      generate_name(loc.name,GENDER_WHITEMALEPATRIARCH);
      strcat(loc.name," 中古車販売店");
      strcpy(loc.shortname,"中古車店");
      break;
   case SITE_BUSINESS_DEPTSTORE:
      lastname(loc.name,true);
      strcat(loc.name," 百貨店");
      strcpy(loc.shortname,"百貨店");
      break;
   case SITE_BUSINESS_HALLOWEEN:
      loc.rename("The Oubliette", "Oubliette");
      break;
   case SITE_INDUSTRY_SWEATSHOP:
      lastname(loc.name,true);
      strcat(loc.name," 縫製工場");
      strcpy(loc.shortname,"縫製工場");
      break;
   case SITE_BUSINESS_CRACKHOUSE:
      do {
         lastname(loc.name,true);
         strcat(loc.name,"通り");
         if(law[LAW_DRUGS]==2)
         {
            switch(LCSrandom(4))
            {
            case 0:
               strcat(loc.name,"癒しの薬局");
               strcpy(loc.shortname,"薬局");
               break;
            case 1:
               strcat(loc.name,"コーヒーハウス");
               strcpy(loc.shortname,"ｺｰﾋｰﾊｳｽ");
               break;
            case 2:
               strcat(loc.name,"マリファナ・ラウンジ");
               strcpy(loc.shortname,"ﾗｳﾝｼﾞ");
               break;
            case 3:
               strcat(loc.name,"大麻調剤所");
               strcpy(loc.shortname,"調剤所");
               break;
            }
         }
         else
         {
            strcat(loc.name,"コカイン窟");
            strcpy(loc.shortname,"ｺｶｲﾝ窟");
         }
      } while(loc.duplicatelocation());
      break;
   case SITE_BUSINESS_JUICEBAR:
      strcpy(loc.name,"");
      switch(LCSrandom(5))
      {
         case 0:strcat(loc.name,"ナチュラル");break;
         case 1:strcat(loc.name,"ハーモニー");break;
         case 2:strcat(loc.name,"レスト");break;
         case 3:strcat(loc.name,"ヘルシー");break;
         case 4:strcat(loc.name,"ニュー ユー");break;
      }
      strcat(loc.name,"・");
      switch(LCSrandom(5))
      {
         case 0:strcat(loc.name,"ダイエット");break;
         case 1:strcat(loc.name,"メソッド");break;
         case 2:strcat(loc.name,"プラン");break;
         case 3:strcat(loc.name,"オレンジ");break;
         case 4:strcat(loc.name,"キャロット");break;
      }
      strcat(loc.name," ジュースバー");
      strcpy(loc.shortname,"ｼﾞｭｰｽﾊﾞｰ");
      break;
   case SITE_BUSINESS_VEGANCOOP:
      strcpy(loc.name,"");
      switch(LCSrandom(5))
      {
         case 0:strcat(loc.name,"アスパラガス");break;
         case 1:strcat(loc.name,"トーフ");break;
         case 2:strcat(loc.name,"ブロッコリー");break;
         case 3:strcat(loc.name,"ダイコン");break;
         case 4:strcat(loc.name,"ナス");break;
      }
      strcat(loc.name,"の");
      switch(LCSrandom(5))
      {
         case 0:strcat(loc.name,"森");break;
         case 1:strcat(loc.name,"虹");break;
         case 2:strcat(loc.name,"庭");break;
         case 3:strcat(loc.name,"畑");break;
         case 4:strcat(loc.name,"草原");break;
      }
      strcat(loc.name," ヴィーガンコープ");
      strcpy(loc.shortname,"ｳﾞｨｰｶﾞﾝｺｰﾌﾟ");
      break;
   case SITE_BUSINESS_INTERNETCAFE:
      strcpy(loc.name,"");
      switch(LCSrandom(5))
      {
         case 0:strcat(loc.name,"エレクトリック");break;
         case 1:strcat(loc.name,"ワイヤード");break;
         case 2:strcat(loc.name,"ナノ");break;
         case 3:strcat(loc.name,"マイクロ");break;
         case 4:strcat(loc.name,"テクノ");break;
      }
      strcat(loc.name,"・");
      switch(LCSrandom(5))
      {
         case 0:strcat(loc.name,"パンダ");break;
         case 1:strcat(loc.name,"トロル");break;
         case 2:strcat(loc.name,"ラテ");break;
         case 3:strcat(loc.name,"ユニコーン");break;
         case 4:strcat(loc.name,"ピクシー");break;
      }
      strcat(loc.name," インターネットカフェ");
      strcpy(loc.shortname,"ﾈｯﾄｶﾌｪ");
      break;
   case SITE_BUSINESS_CIGARBAR:
      lastname(str,true);
      strcpy(loc.name,"The ");
      strcat(loc.name,str);
      strcat(loc.name," ジェントルメンズ・クラブ");
      strcpy(loc.shortname,"ｼｶﾞｰ･ﾊﾞｰ");
      break;
   case SITE_BUSINESS_LATTESTAND:
      strcpy(loc.name,"");
      switch(LCSrandom(5))
      {
         case 0:strcat(loc.name,"フロッシー");break;
         case 1:strcat(loc.name,"ミルキー");break;
         case 2:strcat(loc.name,"カフェイン");break;
         case 3:strcat(loc.name,"モーニング");break;
         case 4:strcat(loc.name,"イブニング");break;
      }
      strcat(loc.name,"・");
      switch(LCSrandom(5))
      {
         case 0:strcat(loc.name,"マグ");break;
         case 1:strcat(loc.name,"カップ");break;
         case 2:strcat(loc.name,"ジョルト");break;
         case 3:strcat(loc.name,"ワンダー");break;
         case 4:strcat(loc.name,"イクスプレス");break;
      }
      strcat(loc.name," ラテスタンド");
      strcpy(loc.shortname,"ﾗﾃｽﾀﾝﾄﾞ");
      break;
   case SITE_OUTDOOR_PUBLICPARK:
      lastname(loc.name,true);
      strcat(loc.name," 公園");
      strcpy(loc.shortname,"公園");
      break;
   case SITE_RESIDENTIAL_BOMBSHELTER:
      loc.rename("核シェルター", "核ｼｪﾙﾀｰ");
      break;
   case SITE_BUSINESS_BARANDGRILL:
      loc.rename("デザートイーグル バー&グリル", "ﾊﾞｰ&ｸﾞﾘﾙ");
      break;
   case SITE_OUTDOOR_BUNKER:
      loc.rename("ロバート・E・リー バンカー", "ﾊﾞﾝｶｰ");
      break;
   case SITE_BUSINESS_ARMSDEALER:
      loc.rename("ブラック・マーケット", "ﾌﾞﾗｯｸﾏｰｹｯﾄ");
      break;
   }
}

/* transfer all loot from some source (such as a squad or another location) to a location, and deal with money properly */
void Location::getloot(vector<Item *>& loot)
{
   for(int l=len(loot)-1;l>=0;l--)
      if(loot[l]->is_money())
      {
         Money* m = static_cast<Money*>(loot[l]); //cast -XML
         ledger.add_funds(m->get_amount(),INCOME_THIEVERY);
         delete loot[l];
      }
      else
      {  // Empty squad inventory into base inventory
         this->loot.push_back(loot[l]);
      }
   loot.clear();
}
