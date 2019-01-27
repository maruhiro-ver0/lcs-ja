#include <externs.h>

void squadstory_text_location(newsstoryst& ns,bool liberalguardian,bool ccs,char* story)
{
   strcat(story,"  それは");
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
      strcat(story,"で行われた。");
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
         strcat(story,"、極めて保守に偏向した番組で知られる場所");break;
      case SITE_BUSINESS_BANK:
         strcat(story,"、経済的不平等を象徴する場所");break;
      default:
         break;
      }
      strcat(story,"で行われた。");
   }
   else if(!ccs)
      strcat(story,"で行われた。");
}

void squadstory_text_opening(newsstoryst& ns,bool liberalguardian,bool ccs,char* story)
{
   if(ns.type==NEWSSTORY_SQUAD_SITE)
   {
      if(!newscherrybusted&&!liberalguardian)
      {
         if(ns.positive)
         {
            strcat(story,"警察の発表によると、昨日リベラル・クライム・スコードを自称するグループによる政治的アピールらしい突然の行動があった。");
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
            strcat(story,"リベラル・クライム・スコードが再び現れた。");
            strcat(story,"&r");
         }
         else
         {
            if(!liberalguardian)
               strcat(story,"リベラル・クライム・スコードが凶行に及んだ。");
            else
               strcat(story,"リベラル・クライム・スコードによる作戦は悲しい結果を引き起こした。");
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
            strcat(story,"A group of M16-wielding vigilantes calling itself the Conservative Crime Squad ");
            strcat(story,"burst onto the scene of political activism yesterday, according ");
            strcat(story,"to a spokesperson from the police department.");
            strcat(story,"&r");
         }
         else
         {
            strcat(story,"A group of worthless M16-toting hicks calling itself the Conservative Crime Squad ");
            strcat(story,"went on a rampage yesterday, according ");
            strcat(story,"to a spokesperson from the police department.");
         }
      }
      else
      {
         if(ns.positive&&!liberalguardian)
         {
            strcat(story,"The Conservative Crime Squad has struck again.  ");
            strcat(story,"&r");
         }
         else
         {
            strcat(story,"The Conservative Crime Squad has gone on another rampage.  ");
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
            strcat(story,"A group of M16-wielding vigilantes calling themselves the Conservative Crime Squad ");
            strcat(story,"burst briefly onto the scene of political activism yesterday, according ");
            strcat(story,"to a spokesperson from the police department.  ");
            strcat(story,"&r");
         }
         else
         {
            strcat(story,"A group of ");
            switch(LCSrandom(4))
            {
            case 0:strcat(story,"pathetic, ");break;
            case 1:strcat(story,"worthless, ");break;
            case 2:strcat(story,"disheveled, ");break;
            case 3:strcat(story,"inbred, ");break;
            }
            switch(LCSrandom(4))
            {
            case 0:strcat(story,"violent, ");break;
            case 1:strcat(story,"bloodthirsty, ");break;
            case 2:strcat(story,"savage, ");break;
            case 3:strcat(story,"");break;
            }
            strcat(story,"M16-toting ");
            switch(LCSrandom(3))
            {
            case 0:strcat(story,"hicks ");break;
            case 1:strcat(story,"rednecks ");break;
            case 2:strcat(story,"losers ");break;
            }
            strcat(story,"calling themselves the Conservative Crime Squad went on a ");
            switch(LCSrandom(3))
            {
            case 0:strcat(story,"suicidal ");break;
            case 1:strcat(story,"homicidal ");break;
            case 2:strcat(story,"bloodthirsty ");break;
            }
            strcat(story,"rampage yesterday, according to a spokesperson from the police department.  ");
            strcat(story,"&r");
         }
      }
      else
      {
         if(ns.positive&&!liberalguardian)
         {
            strcat(story,"The Conservative Crime Squad has struck again, albeit with a tragic end.  ");
            strcat(story,"&r");
         }
         else
         {
            strcat(story,"The Conservative Crime Squad has gone on another rampage, and they got what they deserved.  ");
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
            strcat(story,"A group calling itself the Liberal Crime Squad ");
            strcat(story,"burst briefly onto the scene of political activism yesterday, according ");
            strcat(story,"to a spokesperson from the police department.  ");
            strcat(story,"&r");
         }
         else
         {
            strcat(story,"A group of thugs calling itself the Liberal Crime Squad ");
            strcat(story,"went on a suicidal rampage yesterday, according ");
            strcat(story,"to a spokesperson from the police department.  ");
            strcat(story,"&r");
         }
      }
      else
      {
         if(ns.positive)
         {
            strcat(story,"The Liberal Crime Squad has struck again, albeit with a tragic end.  ");
            strcat(story,"&r");
         }
         else
         {
            if(!liberalguardian)
               strcat(story,"The Liberal Crime Squad has gone on a rampage, and they got what they deserved.  ");
            else
               strcat(story,"A Liberal Crime Squad operation went horribly wrong, and came to a tragic end.  ");//XXX: Rewrite me -- LK
            strcat(story,"&r");
         }
      }
   }

   squadstory_text_location(ns,liberalguardian,ccs,story);

   if(ns.type==NEWSSTORY_SQUAD_KILLED_SITE)
   {
      if(liberalguardian)strcat(story,"Unfortunately, the LCS group was defeated by the forces of evil.  ");
      else if(ns.positive)strcat(story,"Everyone in the LCS group was arrested or killed.  ");
      else strcat(story,"Fortunately, the LCS thugs were stopped by brave citizens.  ");
   }
   if(ns.type==NEWSSTORY_CCS_KILLED_SITE)
   {
      if(ns.positive&&!liberalguardian)strcat(story,"Everyone in the CCS group was arrested or killed.  ");
      else strcat(story,"Fortunately, the CCS thugs were stopped by brave citizens.  ");
   }
   strcat(story,"&r");
}
