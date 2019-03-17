#include <externs.h>

void squadstory_text_location(newsstoryst& ns,bool liberalguardian,bool ccs,char* story)
{
   strcat(story,"  発生現場は");
   std::string placename=location[ns.loc]->getname();
   if(placename.substr(0,4)=="The ")
      placename=placename.substr(4);
   int posand=placename.find('&');
   if(posand!=(int)string::npos)
      placename=placename.substr(0,posand)+"and"+placename.substr(posand+1);
   switch(location[ns.loc]->type)
   {
   case SITE_CITY_SEATTLE:
   case SITE_CITY_LOS_ANGELES:
   case SITE_CITY_NEW_YORK:
   case SITE_CITY_CHICAGO:
   case SITE_CITY_DETROIT:
   case SITE_CITY_ATLANTA:
   case SITE_CITY_MIAMI:
   case SITE_CITY_WASHINGTON_DC:
      break;
   case SITE_DOWNTOWN:
   case SITE_COMMERCIAL:
   case SITE_UDISTRICT:
   case SITE_OUTOFTOWN:
   case SITE_INDUSTRIAL:
   case SITE_TRAVEL:
      if(placename=="Shopping"||placename=="ショッピング")
      {
         placename="ショッピングモール";
      }
      else if(placename=="Travel"||placename=="旅行")
      {
         placename="旅行会社";
      }
      else if(placename=="Outskirts and Orange County")
      {
         placename="オレンジ郡";
      }
      else if(placename=="Brooklyn and Queens")
      {
         placename="ロングアイランド";
      }
      else if(placename=="Greater Hollywood")
      {
         placename="ハリウッド";
      }
      else if(placename=="Manhattan Island")
      {
         placename="マンハッタン";
      }
      else if(placename=="Arlington")
         ;
      else if(placename=="National Mall")
         ;
      else if(placename!="Downtown"&&placename!="都心部")
         ;
      break;
   case SITE_BUSINESS_PAWNSHOP:
      if(placename.find("'s")!=string::npos)
      {
         if(liberalguardian&&!ccs)strcat(story,"よく知られた");
      }
      else
      {
         if(liberalguardian&&!ccs)strcat(story,"よく知られた");
      }
      break;
   case SITE_RESIDENTIAL_APARTMENT:
   case SITE_BUSINESS_CARDEALERSHIP:
   case SITE_BUSINESS_DEPTSTORE:
   case SITE_OUTDOOR_PUBLICPARK:
      if(liberalguardian&&!ccs)strcat(story,"よく知られた");
      break;
   default:
      if(liberalguardian&&!ccs)strcat(story,"よく知られた");
      break;
   }
   if(ccs)
   {
      switch(location[ns.loc]->type)
      {
      case SITE_RESIDENTIAL_APARTMENT_UPSCALE:
         strcat(story,"大学寮");break;
      case SITE_BUSINESS_CIGARBAR:
         strcat(story,"ラッキーレディー・ストリップクラブ");break;
      case SITE_LABORATORY_COSMETICS:
         strcat(story,"動物保護シェルター");break;
      case SITE_LABORATORY_GENETIC:
         strcat(story,"倫理研究所委員会本部");break;
      case SITE_GOVERNMENT_POLICESTATION:
         strcat(story,"Seedy Back Alley(tm)");break;
      case SITE_GOVERNMENT_COURTHOUSE:
         strcat(story,"中絶病院");break;
      case SITE_GOVERNMENT_PRISON:
         strcat(story,"リハビリセンター");break;
      case SITE_GOVERNMENT_INTELLIGENCEHQ:
         strcat(story,"WikiLeaks本部");break;
      case SITE_INDUSTRY_SWEATSHOP:
         strcat(story,"労働組合本部");break;
      case SITE_INDUSTRY_POLLUTER:
         strcat(story,"平和と緑のオフィス");break;
      case SITE_INDUSTRY_NUCLEAR:
         strcat(story,"ホイールド・ピーズ美術館");break;
      case SITE_CORPORATE_HEADQUARTERS:
         strcat(story,"福祉補助機関");break;
      case SITE_CORPORATE_HOUSE:
         strcat(story,"税金収集機関");break;
      case SITE_MEDIA_AMRADIO:
         strcat(story,"公共ラジオ局");break;
      case SITE_MEDIA_CABLENEWS:
         strcat(story,"ネットワークニュース局");break;
      case SITE_GOVERNMENT_ARMYBASE:
         strcat(story,"緑と平和の機関");break;
      case SITE_GOVERNMENT_FIRESTATION:
         strcat(story,"アメリカ市民自由連合支所");break;
      case SITE_BUSINESS_BANK:
         strcat(story,"リチャード・ドーキンス フードバンク");break;
      default:
         strcat(story,placename);break;
      }
      strcat(story,"。");
   }
   else strcat(story,placename);
   if(liberalguardian&&!ccs)
   {
      switch(location[ns.loc]->type)
      {
      case SITE_RESIDENTIAL_APARTMENT_UPSCALE:
         strcat(story,"、自己中心的な富裕層の住処");break;
      case SITE_BUSINESS_CIGARBAR:
         strcat(story,"、悪しき保守思想の巣窟");break;
      case SITE_LABORATORY_COSMETICS:
         strcat(story,"、保守派の動物虐待者の居所");break;
      case SITE_LABORATORY_GENETIC:
         strcat(story,"、危険な保守派の遺伝子研究所");break;
      case SITE_GOVERNMENT_POLICESTATION:
         strcat(story,"、この国で最も抑圧的な保守派警察権力の本部");break;
      case SITE_GOVERNMENT_COURTHOUSE:
         strcat(story,"、保守派による無数の不正義の場所");break;
      case SITE_GOVERNMENT_PRISON:
         strcat(story,"、無実の人々が保守派の看守に虐待されている場所");break;
      case SITE_GOVERNMENT_INTELLIGENCEHQ:
         strcat(story,", 世界中で最もプライバシーを侵害している保守派の機関の1つ");break;
      case SITE_GOVERNMENT_ARMYBASE:
         strcat(story,"、保守派の拷問者と戦争屋の群れの中");break;
      case SITE_INDUSTRY_SWEATSHOP:
         strcat(story,"、保守による強制労働と人権侵害の工場");break;
      case SITE_INDUSTRY_POLLUTER:
         strcat(story,"、有害な煙を街に蔓延される保守の工場");break;
      case SITE_INDUSTRY_NUCLEAR:
         strcat(story,"、保守の核のゴミの貯蔵庫としても知られる場所");break;
      case SITE_CORPORATE_HEADQUARTERS:
         strcat(story,"、邪悪な保守思想の殿堂");break;
      case SITE_CORPORATE_HOUSE:
         strcat(story,"、もし保守の手の中になければ百人もの人々が暮せる建造物");break;
      case SITE_MEDIA_AMRADIO:
      case SITE_MEDIA_CABLENEWS:
         strcat(story,"、極めて保守に偏向した番組で知られる放送局");break;
      case SITE_BUSINESS_BANK:
         strcat(story,"、経済的不平等を象徴する場所");break;
      default:
         break;
      }
      strcat(story,"。");
   }
   else if(!ccs)
      strcat(story,"。");
}

void squadstory_text_opening(newsstoryst& ns,bool liberalguardian,bool ccs,char* story)
{
   if(ns.type==NEWSSTORY_SQUAD_SITE)
   {
      if(!newscherrybusted&&!liberalguardian)
      {
         if(ns.positive)
         {
            strcat(story,"警察の発表によると、昨日リベラル・クライム・スコードを自称するグループによる政治的アピールと思われる突然の行動があった。");
            strcat(story,"&r");
         }
         else
         {
            strcat(story,"警察の発表によると、昨日リベラル・クライム・スコードを自称する犯罪グループによる事件が発生した。");
         }
      }
      else
      {
         if(ns.positive)
         {
            strcat(story,"再びリベラル・クライム・スコードの襲撃があった。");
            strcat(story,"&r");
         }
         else
         {
            if(!liberalguardian)
               strcat(story,"リベラル・クライム・スコードが凶行に及んだ。");
            else
               strcat(story,"リベラル・クライム・スコードの行動は悲劇な結果となった。");
            strcat(story,"&r");
         }
      }
   }
   else if(ns.type==NEWSSTORY_CCS_SITE)
   {
      if(newscherrybusted<2)
      {
         if(ns.positive&&!liberalguardian)
         {
            strcat(story,"警察の発表によると、昨日M16自動小銃を携帯した自警団、自称コンサバディブ・クライム・スコードによる政治的アピールと思われる突然の行動があった。");
            strcat(story,"&r");
         }
         else
         {
            strcat(story,"警察の発表によると、昨日M16自動小銃を携帯した田舎者、自称コンサバディブ・クライム・スコードによる暴力事件があった。");
         }
      }
      else
      {
         if(ns.positive&&!liberalguardian)
         {
            strcat(story,"再びコンサバティブ・クライム・スコードの襲撃があった。");
            strcat(story,"&r");
         }
         else
         {
            strcat(story,"コンサバティブ・クライム・スコードが凶行に及んだ。");
            strcat(story,"&r");
         }
      }
   }
   else if(ns.type==NEWSSTORY_CCS_KILLED_SITE)
   {
      if(newscherrybusted<2)
      {
         if(ns.positive&&!liberalguardian)
         {
            strcat(story,"警察の発表によると、昨日M16自動小銃を携帯した自警団、自称コンサバディブ・クライム・スコードをによる政治的アピールと思われる突然の行動があった。");
            strcat(story,"&r");
         }
         else
         {
            strcat(story,"警察の発表によると、M16自動小銃を携帯した");
            switch(LCSrandom(4))
            {
            case 0:strcat(story,"哀れで");break;
            case 1:strcat(story,"無価値で");break;
            case 2:strcat(story,"無秩序で");break;
            case 3:strcat(story,"");break;
            }
            switch(LCSrandom(4))
            {
            case 0:strcat(story,"暴力的な");break;
            case 1:strcat(story,"血に飢えた");break;
            case 2:strcat(story,"残忍な");break;
            case 3:strcat(story,"救いようのない");break;
            }
            strcat(story,"M16自動小銃を携帯した");
            switch(LCSrandom(3))
            {
            case 0:strcat(story,"田舎者");break;
            case 1:strcat(story,"赤っ首");break;
            case 2:strcat(story,"負け犬");break;
            }
            strcat(story,"、自称コンサバティブ・クライム・スコードによる");
            switch(LCSrandom(3))
            {
            case 0:strcat(story,"自殺的襲撃");break;
            case 1:strcat(story,"恐るべき殺人");break;
            case 2:strcat(story,"血に飢えた");break;
            }
            strcat(story,"事件があった。");
            strcat(story,"&r");
         }
      }
      else
      {
         if(ns.positive&&!liberalguardian)
         {
            strcat(story,"コンサバ・クライム・スコードの襲撃が再びあり、悲惨な結末となった。");
            strcat(story,"&r");
         }
         else
         {
            strcat(story,"コンサバ・クライム・スコードの襲撃が再びあり、当然の結末となった。");
            strcat(story,"&r");
         }
      }
   }
   else
   {
      if(!newscherrybusted&&!liberalguardian)
      {
         if(ns.positive)
         {
            strcat(story,"警察の発表によると、昨日リベラル・クライム・スコードを自称するグループによる政治的アピールと思われる突然の行動があった。");
            strcat(story,"&r");
         }
         else
         {
            strcat(story,"警察の発表によると、昨日リベラル・クライム・スコードを自称する犯罪グループによる自殺的襲撃事件が発生した。");
            strcat(story,"&r");
         }
      }
      else
      {
         if(ns.positive)
         {
            strcat(story,"リベラル・クライム・スコードの襲撃が再びあり、悲惨な結末となった。");
            strcat(story,"&r");
         }
         else
         {
            if(!liberalguardian)
               strcat(story,"リベラル・クライム・スコードの襲撃が再びあった。");
            else
               strcat(story,"リベラル・クライム・スコードの行動は悲劇な結果となった。");//XXX: Rewrite me -- LK
            strcat(story,"&r");
         }
      }
   }

   squadstory_text_location(ns,liberalguardian,ccs,story);

   if(ns.type==NEWSSTORY_SQUAD_KILLED_SITE)
   {
      if(liberalguardian)strcat(story,"悲しむべきことにLCSの集団は悪の軍勢に葬り去られた。 ");
      else if(ns.positive)strcat(story,"LCSのメンバーは全員が逮捕または死亡した。 ");
      else strcat(story,"幸いなことに、LCSの凶行は勇敢な市民によって阻止された。 ");
   }
   if(ns.type==NEWSSTORY_CCS_KILLED_SITE)
   {
      if(ns.positive&&!liberalguardian)strcat(story,"CCSのメンバーは全員が逮捕または死亡した。 ");
      else strcat(story,"幸いなことに、CCSの凶行は勇敢な市民によって阻止された。 ");
   }
   strcat(story,"&r");
}
