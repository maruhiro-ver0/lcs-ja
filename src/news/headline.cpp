#include <externs.h>

std::string getLastNameForHeadline(char* fullName)
{
   int i=0;
   int j=-1;
   char lastName[20];
   // Parse through full name to get the last name
   for(i=0; fullName[i]!=0; i++)
   {
      // Start recording last name at the space between first and last
      if(fullName[i]==' ')
      {
         j=0;
      }
      // When recording last name, transcribe in uppercase
      else if(j >= 0)
      {
         lastName[j++] = toupper(fullName[i]);
      }
   }
   lastName[j] = 0; // To finish, NULL terminate the transcribed string

   // Write to std::string
   std::string ret = lastName;
   return ret;
}

void displaystoryheader(newsstoryst& ns, bool liberalguardian, int& y, int header, char *story)
{
   switch(ns.type)
   {
   case NEWSSTORY_PRESIDENT_IMPEACHED:
      displaycenterednewsfont(getLastNameForHeadline(oldPresidentName), 5);
      displaycenterednewsfont("IMPEACHED",13);
      strcat(story,"『大統領 弾劾』");
      break;
   case NEWSSTORY_PRESIDENT_BELIEVED_DEAD:
      displaycenterednewsfont(getLastNameForHeadline(oldPresidentName), 5);
      displaycenterednewsfont("BELIEVED DEAD",13);
      strcat(story,"『大統領 死亡か』");
      break;
   case NEWSSTORY_PRESIDENT_FOUND_DEAD:
      displaycenterednewsfont(getLastNameForHeadline(oldPresidentName), 5);
      displaycenterednewsfont("FOUND DEAD",13);
      strcat(story,"『大統領 死去』");
      break;
   case NEWSSTORY_PRESIDENT_FOUND:
      displaycenterednewsfont(getLastNameForHeadline(oldPresidentName), 5);
      displaycenterednewsfont("RESCUED",13);
      strcat(story,"『大統領 救出される』");
      break;
   case NEWSSTORY_PRESIDENT_KIDNAPPED:
      displaycenterednewsfont(getLastNameForHeadline(oldPresidentName), 5);
      displaycenterednewsfont("KIDNAPPED",13);
      strcat(story,"『大統領 誘拐される』");
      break;
   case NEWSSTORY_PRESIDENT_MISSING:
      displaycenterednewsfont(getLastNameForHeadline(oldPresidentName), 5);
      displaycenterednewsfont("MISSING",13);
      strcat(story,"『大統領 失踪』");
      break;
   case NEWSSTORY_PRESIDENT_ASSASSINATED:
      displaycenterednewsfont(getLastNameForHeadline(oldPresidentName), 5);
      displaycenterednewsfont("ASSASSINATED",13);
      strcat(story,"『大統領 暗殺』");
      break;
   case NEWSSTORY_CCS_NOBACKERS:
      displaycenterednewsfont("FBI HUNTS CCS",5);
      y=13;
      strcat(story,"『FBI CCSを追求』");
      break;
   case NEWSSTORY_CCS_DEFEATED:
      displaycenterednewsfont("RAIDS END CCS",5);
      y=13;
      strcat(story,"『CCSの終焉』");
      break;
   case NEWSSTORY_NUDITYARREST:
   case NEWSSTORY_CARTHEFT:
   case NEWSSTORY_WANTEDARREST:
   case NEWSSTORY_DRUGARREST:
   case NEWSSTORY_GRAFFITIARREST:
   case NEWSSTORY_BURIALARREST:
      displaycenterednewsfont("POLICE KILLED",5);
      y=13;
      strcat(story,"『警察官 殺害される』");
      break;
   case NEWSSTORY_SQUAD_ESCAPED:
   case NEWSSTORY_SQUAD_FLEDATTACK:
      displaycenterednewsfont("LCS ESCAPES",5);
      displaycenterednewsfont("POLICE SIEGE",13);
      strcat(story,"『LCSメンバー 脱走』");
      break;
   case NEWSSTORY_SQUAD_DEFENDED:
   case NEWSSTORY_SQUAD_BROKESIEGE:
      displaycenterednewsfont("LCS FIGHTS",5);
      displaycenterednewsfont("OFF COPS",13);
      strcat(story,"『LCS 警察と戦闘』");
      break;
   case NEWSSTORY_SQUAD_KILLED_SIEGEATTACK:
   case NEWSSTORY_SQUAD_KILLED_SIEGEESCAPE:
      if(!liberalguardian)
      {
         displaycenterednewsfont("LCS SIEGE",5);
         displaycenterednewsfont("TRAGIC END",13);
         strcat(story,"『LCS包囲網 悲惨な結末』");
      }
      else
      {
         displaycenterednewsfont("POLICE KILL",5);
         displaycenterednewsfont("LCS MARTYRS",13);
         strcat(story,"『LCSメンバー殉死』");
      }
      break;
   case NEWSSTORY_CCS_SITE:
   case NEWSSTORY_CCS_KILLED_SITE:
      if(newscherrybusted<2)
      {
         displaycenterednewsfont("CONSERVATIVE",5);
         displaycenterednewsfont("CRIME SQUAD",13);
         strcat(story,"『コンサバティブ・クライム・スコード』");
      }
      else
      {
         if(ns.positive)
         {
            displaycenterednewsfont("CCS STRIKES",5);//AGAIN?
            strcat(story,"『CCSの襲撃』");
         }
         else
         {
            displaycenterednewsfont("CCS RAMPAGE",5);
            strcat(story,"『CCSの凶行』");
         }
         y=13;
      }
      break;
   default:
      if(ns.positive)
      {
         if(newscherrybusted||liberalguardian)
         {

            if(!liberalguardian)
            {
               if(ns.priority>250)
               {
                  y=13;
                  displaycenterednewsfont("UNSTOPPABLE",5);
                  strcat(story,"『止められない』");
               }
               else
               {
                  y=13;
                  displaycenterednewsfont("LCS STRIKES",5);
                  strcat(story,"『LCSの襲撃』");
               }
            }
            else
            {
               y=13;
               if(ns.priority>150)
               {
                  change_public_opinion(header,5,1); // Bonus for big story
                  switch(header)
                  {
                  case VIEW_TAXES:
                  case VIEW_SWEATSHOPS:
                  case VIEW_CEOSALARY:
                     displaycenterednewsfont("CLASS WAR",5);
                     strcat(story,"『階級闘争』");
                     break;
                  case VIEW_NUCLEARPOWER:
                     displaycenterednewsfont("MELTDOWN RISK",5);
                     strcat(story,"『メルトダウンの危険性』");
                     break;
                  case VIEW_POLICEBEHAVIOR:
                     displaycenterednewsfont("LCS VS COPS",5);
                     strcat(story,"『LCS 対 警察』");
                     break;
                  case VIEW_DEATHPENALTY:
                     displaycenterednewsfont("PRISON WAR",5);
                     strcat(story,"『刑務所戦争』");
                     break;
                  case VIEW_INTELLIGENCE:
                     displaycenterednewsfont("LCS VS CIA",5);
                     strcat(story,"『LCS 対 CIA』");
                     break;
                  case VIEW_ANIMALRESEARCH:
                  case VIEW_GENETICS:
                     displaycenterednewsfont("EVIL RESEARCH",5);
                     strcat(story,"『恐るべき研究』");
                     break;
                  case VIEW_FREESPEECH:
                  case VIEW_GAY:
                  case VIEW_JUSTICES:
                     displaycenterednewsfont("NO JUSTICE",5);
                     strcat(story,"『司法の機能不全』");
                     break;
                  case VIEW_POLLUTION:
                     displaycenterednewsfont("POLLUTER HIT",5);
                     strcat(story,"『公害』");
                     break;
                  case VIEW_CORPORATECULTURE:
                     displaycenterednewsfont("LCS HITS CORP",5);
                     strcat(story,"『LCS 警察署を襲撃』");
                     break;
                  case VIEW_AMRADIO:
                     displaycenterednewsfont("LCS HITS AM",5);
                     strcat(story,"『LCS AMラジオ局を襲撃』");
                     break;
                  case VIEW_CABLENEWS:
                     displaycenterednewsfont("LCS HITS TV",5);
                     strcat(story,"『LCS テレビ局を襲撃』");
                     break;
                  default:
                     displaycenterednewsfont("HEROIC STRIKE",5);
                     strcat(story,"『英雄的襲撃』");
                  }
               }
               else
               {
                  displaycenterednewsfont("LCS STRIKES",5);
                  strcat(story,"『LCSの襲撃』");
               }
            }
         }
         else
         {
            displaycenterednewsfont("LIBERAL CRIME",5);
            displaycenterednewsfont("SQUAD STRIKES",13);
            strcat(story,"『リベラル・クライム・スコードの襲撃』");
         }
      }
      else
      {
         if(newscherrybusted||liberalguardian)
         {
            if(!liberalguardian)
            {
               displaycenterednewsfont("LCS RAMPAGE",5);
               strcat(story,"『LCSの凶行』");
            }
            else
            {
               displaycenterednewsfont("LCS SORRY",5);
               strcat(story,"『LCSの謝罪』");
            }
            y=13;
         }
         else
         {
            displaycenterednewsfont("LIBERAL CRIME",5);
            displaycenterednewsfont("SQUAD RAMPAGE",13);
            strcat(story,"『リベラル・クライム・スコードの凶行』");
         }
      }
      break;
   }
}
