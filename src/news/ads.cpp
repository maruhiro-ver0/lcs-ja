#include <externs.h>

void displaysinglead(bool liberalguardian,char addplace[2][3],short* storyx_s,short* storyx_e,int& it2)
{
   int x,y;
   do x=LCSrandom(2),y=LCSrandom(3); while(addplace[x][y]);

   char choice=LCSrandom(6)+1; // choose an ad from 1 to 6 that isn't already taken
   for(int x2=0;x2<2;x2++) for(int y2=0;y2<3;y2++) // loop thru ad places to see ads already up
      if(addplace[x2][y2]==choice) choice=LCSrandom(6)+1,x2=0,y2=-1; // choose again and restart loop if already taken
   addplace[x][y]=choice; // we got an ad chosen that isn't a duplicate

   int sx=0,ex=0,sy=0,ey=0;
   if(x==0) sx=0,ex=23+LCSrandom(4);
   if(x==1) sx=57-LCSrandom(4),ex=79;
   if(y==0) sy=2,ey=9;
   if(y==1) sy=10,ey=17;
   if(y==2) sy=18,ey=24;

   int ch='?';
   switch(LCSrandom(6))
   {
   case 0: ch=CH_LIGHT_SHADE; break;
   case 1: ch=CH_MEDIUM_SHADE; break;
   case 2: ch=CH_DARK_SHADE; break;
   case 3: ch=CH_FULL_BLOCK; break;
   case 4: ch=CH_BOX_DRAWINGS_LIGHT_VERTICAL_AND_HORIZONTAL; break;
   case 5: ch='*'; break;
   }

   for(y=sy;y<=ey;y++)
   {
      if(storyx_s[y]<ex&&ex<43) storyx_s[y]=ex+2;
      if(storyx_e[y]>sx&&sx>43) storyx_e[y]=sx-2;

      if(ey==9&&y==9) continue;
      if(ey==17&&y==17) continue;
      for(x=sx;x<=ex;x++)
         if(y==sy||y==8||y==16||y==24||x==sx||x==ex)
            mvaddch(y,x,ch);
   }

   //AD CONTENT
   {
      short storyx_s[25],storyx_e[25];
      for(it2=0;it2<25;it2++) storyx_s[it2]=40,storyx_e[it2]=40;
      for(it2=sy+1;it2<=ey-1;it2++) storyx_s[it2]=sx+1,storyx_e[it2]=ex-1;

      char ad[500];
      if(!liberalguardian)
      { // regular newspaper (not Liberal Guardian)
         switch(choice) // should be 6 choices from 1 to 6
         { // location[]->name?
         case 1:
            strcpy(ad,"&c今なら無料&r");
            strcat(ad,"&c経営委託プログラム&r&r");
            strcat(ad,"&c詳しくはお電話を&r");
            break;
         case 2:
            strcpy(ad,"&c上質な皮製椅子&r&r");
            strcat(ad,"&cスペシャルプライス&r");
            strcat(ad,"&c今なら $");
            strcat(ad,LCSrandom(201)+400);
            strcat(ad,"&r");
            break;
         case 3:
            strcpy(ad,"&cフリーマーケット パリ&r&r");
            strcat(ad,"&c大セール&r");
            strcat(ad,"&c50% OFF&r");
            break;
         case 4:
            strcat(ad,"&c乗用車&r");
            strcpy(ad,"&c新品同様&r");
            strcat(ad,"&c");
            strcat(ad,year-LCSrandom(15));
            strcat(ad," ");
//          strcat(ad,cartype);
//TODO: leading zeros, etc.
            strcat(ad,"Lexus GS 300&r");
            strcat(ad,"&cSedan 4D&r");
            strcat(ad,"&cたったの $");
            strcat(ad,LCSrandom(16)+15);
            strcat(ad,"&r");
            break;
         case 5:
            strcpy(ad,"&cスパ&r");
            strcat(ad,"&c美容と健康&r");
            strcat(ad,"&cそしてフィットネス&r&r");
            strcat(ad,"&c毎日営業中&r");
            break;
         case 6:
            {
               strcpy(ad,"&c");
               switch(LCSrandom(5))
               { // less explicit personals in regular newspaper than Liberal Guardian
                  case 0:strcat(ad,"出会いを探せ");break;
                  case 1:strcat(ad,"出会いを求めよ");break;
                  case 2:strcat(ad,"ひとりですか?");break;
                  case 3:strcat(ad,"出会いを見つける");break;
                  case 4:strcat(ad,"ソウルメイト募集中");break;
               }
               char str[10];
               strcat(ad,"&r&r");
               strcat(ad,"&c");
               sexdesc(str);
               strcat(ad,str);
               strcat(ad," ");
               sexwho(str);
               strcat(ad,str);
               strcat(ad," ");
               sexseek(str);
               strcat(ad,str);
               strcat(ad,"&r");
               strcat(ad,"&c");
               sextype(str);
               strcat(ad,str);
               strcat(ad," w/ ");
               sexwho(str);
               strcat(ad,str);
               strcat(ad,"&r");
               break;
            }
         default:
            strcpy(ad,"&c要デバッグ&r&r");
            strcat(ad,"&cこれは&r");
            strcat(ad,"&cおそらく&r");
            strcat(ad,"&cバグだ!&r");
            break;
         }
      }
      else
      { // Liberal Guardian Ads
         switch(choice)  // should be 6 choices from 1 to 6
         {
         case 1:
            strcpy(ad,"&cオーガニックが欲しい?&r&r");
            strcat(ad,"&cお求めは&r");
            strcat(ad,"&cヴィーガンコープへ&r");
            break;
         case 2:
            strcpy(ad,"&c自由を守る弁護士&r");
            strcat(ad,"&c");
            strcat(ad,LCSrandom(11)+20);
            strcat(ad,"年の実績&r&r");
            strcat(ad,"&c今すぐお電話&r");
            break;
         case 3:
            strcpy(ad,"&c中絶病院&r&r");
            strcat(ad,"&c歩いて行けます&r");
            strcat(ad,"&c理由は問いません&r");
            strcat(ad,"&cオープン 24/7&r");
            break;
         case 4:
            strcpy(ad,"&cマリファナ薬局&r&r");
            strcat(ad,"&cID、処方箋は必要なし!&r");
            strcat(ad,"&c現金でどうぞ&r");
            break;
         case 5:
            strcpy(ad,"&cお悩みですか?&r&r");
            strcat(ad,"&cお近くの&r");
            strcat(ad,"&cサブジーニアス教会を&r");
            strcat(ad,"&cお訪ねください&r");
            break;
         case 6:
            {
               strcpy(ad,"&c");
               switch(LCSrandom(5))
               { // more explicit personals in Liberal Guardian than regular newspaper
                  case 0:strcat(ad,"Sexを探せ");break;
                  case 1:strcat(ad,"Sexを求めよ");break;
                  case 2:strcat(ad,"Sexしたいですか?");break;
                  case 3:strcat(ad,"Sexを見つける");break;
                  case 4:strcat(ad,"Sexパートナー募集中");break;
               }
               char str[10];
               strcat(ad,"&r&r");
               strcat(ad,"&c");
               sexdesc(str);
               strcat(ad,str);
               strcat(ad," ");
               sexwho(str);
               strcat(ad,str);
               strcat(ad," ");
               sexseek(str);
               strcat(ad,str);
               strcat(ad,"&r");
               strcat(ad,"&c");
               sextype(str);
               strcat(ad,str);
               strcat(ad," w/ ");
               sexwho(str);
               strcat(ad,str);
               strcat(ad,"&r");
               break;
            }
         default:
            strcpy(ad,"&c要デバッグ&r&r");
            strcat(ad,"&cこれは&r");
            strcat(ad,"&cおそらく&r");
            strcat(ad,"&cバグだ!&r");
            break;
         }
      }

      displaynewsstory(ad,storyx_s,storyx_e,sy+1);
   }
}


void displayads(newsstoryst& ns, bool liberalguardian, short* storyx_s, short* storyx_e,int& it2)
{
   int adnumber=0;
   if(!liberalguardian)
   {
      if(ns.page>=10)adnumber++;
      if(ns.page>=20)adnumber+=LCSrandom(2)+1;
      if(ns.page>=30)adnumber+=LCSrandom(2)+1;
      if(ns.page>=40)adnumber+=LCSrandom(2)+1;
      if(ns.page>=50)adnumber+=LCSrandom(2)+1;
   }
   else
   {
      if(ns.guardianpage>=2)adnumber++;
      if(ns.guardianpage>=3)adnumber+=LCSrandom(2)+1;
      if(ns.guardianpage>=4)adnumber+=LCSrandom(2)+1;
      if(ns.guardianpage>=5)adnumber+=LCSrandom(2)+1;
      if(ns.guardianpage>=6)adnumber+=LCSrandom(2)+1;
   }
   char addplace[2][3]={{0,0,0},{0,0,0}};
   for(adnumber=(adnumber>6?6:adnumber);adnumber>0;adnumber--)
      displaysinglead(liberalguardian,addplace,storyx_s,storyx_e,it2);
}
