#include <externs.h>

/* pick a descriptor acronym */
void sexdesc(char *str)
{
   strcpy(str,"");

   switch(LCSrandom(4))
   { // Descriptors
   case 0:strcat(str,"DTE");break;
   case 1:strcat(str,"ND");break;
   case 2:strcat(str,"NS");break;
   case 3:strcat(str,"VGL");break;

   default:strcat(str,"FOO");break;
   }
}

/* what kind of person? */
void sexwho(char *str)
{
   strcpy(str,"");

   switch(LCSrandom(35))
   { // Who
   case 0:strcat(str,"BB");break;
   case 1:strcat(str,"BBC");break;
   case 2:strcat(str,"BF");break;
   case 3:strcat(str,"BHM");break;
   case 4:strcat(str,"BiF");break;
   case 5:strcat(str,"BiM");break;
   case 6:strcat(str,"BBW");break;
   case 7:strcat(str,"BMW");break; // lol big mexican woman
   case 8:strcat(str,"CD");break;
   case 9:strcat(str,"DWF");break;
   case 10:strcat(str,"DWM");break;
   case 11:strcat(str,"FTM");break;
   case 12:strcat(str,"GAM");break;
   case 13:strcat(str,"GBM");break;
   case 14:strcat(str,"GF");break;
   case 15:strcat(str,"GG");break;
   case 16:strcat(str,"GHM");break;
   case 17:strcat(str,"GWC");break;
   case 18:strcat(str,"GWF");break;
   case 19:strcat(str,"GWM");break;
   case 20:strcat(str,"MBC");break;
   case 21:strcat(str,"MBiC");break;
   case 22:strcat(str,"MHC");break;
   case 23:strcat(str,"MTF");break;
   case 24:strcat(str,"MWC");break;
   case 25:strcat(str,"SBF");break;
   case 26:strcat(str,"SBM");break;
   case 27:strcat(str,"SBiF");break;
   case 28:strcat(str,"SBiM");break;
   case 29:strcat(str,"SSBBW");break;
   case 30:strcat(str,"SWF");break;
   case 31:strcat(str,"SWM");break;
   case 32:strcat(str,"TG");break;
   case 33:strcat(str,"TS");break;
   case 34:strcat(str,"TV");break;

   default:strcat(str,"BAR");break;
   }
}

/* seeking acronym */
void sexseek(char *str)
{
   strcpy(str,"");

   switch(LCSrandom(2))
   { // ISO
   case 0:strcat(str,"ISO");break;
   case 1:strcat(str,"LF");break;
   default:strcat(str,"BAZ");break;
   }
}

/* what type of sex? */
void sextype(char *str)
{
   strcpy(str,"");

   switch(LCSrandom(14))
   { // TYPE
   case 0:strcat(str,"225");break;
   case 1:strcat(str,"ATM");break;
   case 2:strcat(str,"BDSM");break;
   case 3:strcat(str,"CBT");break;
   case 4:strcat(str,"BJ");break;
   case 5:strcat(str,"DP");break;
   case 6:strcat(str,"D/s");break;
   case 7:strcat(str,"GB");break;
   case 8:strcat(str,"HJ");break;
   case 9:strcat(str,"OTK");break;
   case 10:strcat(str,"PNP");break;
   case 11:strcat(str,"TT");break;
   case 12:strcat(str,"SWS");break;
   case 13:strcat(str,"W/S");break;
   default:strcat(str,"LOL");break;
   }
}

/* generate a vanity plate for the squad. */
/*void vanity(char *str)
{
   strcpy(str,"");

   switch(LCSrandom(20))
   {
   case 0:strcat(str,"ABORTN");break;
   case 1:strcat(str,"LCS-"LCSrandom(50)+1);break;
   case 2:strcat(str,"LIB4LYFE");break;
   case 3:strcat(str,"");break;
   case 4:strcat(str,"");break;
   case 5:strcat(str,"");break;
   case 6:strcat(str,"");break;
   case 7:strcat(str,"");break;
   case 8:strcat(str,"");break;
   case 9:strcat(str,"");break;
   case 10:strcat(str,"");break;
   case 11:strcat(str,"");break;
   case 12:strcat(str,"");break;
   case 13:strcat(str,"");break;
   case 14:strcat(str,"");break;
   case 15:strcat(str,"");break;
   case 16:strcat(str,"");break;
   case 17:strcat(str,"");break;
   case 18:strcat(str,"");break;
   case 19:strcat(str,"");break;
   }
}
*/

/* return a letter, number, or one of either. */
void chooseLetterOrNumber(char *str, int type)
{
    strcpy(str,"");

    if(type == 1) // Choose a letter.
    {
        char randChar = 'a' + LCSrandom(26);
        addstr(&randChar);
    } else if(type == 2) // Choose a number.
    {
        char randNum = LCSrandom(10);
        addstr(&randNum);
    } else if(type == 3) {// Choose one of either.
        if(LCSrandom(36) > 25) {
            char randNum = LCSrandom(10);
            addstr(&randNum);
        } else {
        char randChar = 'a' + LCSrandom(26);
        addstr(&randChar);
        }
    } else {
        addstr("-ERR-");
    }
}

/* generate a non-vanity plate for the squad. */
void plate(char *str)
{
   strcpy(str,"");

   switch(LCSrandom(8)) // Actual license plate formats.
   {
   case 0: // 123 ABC
         // CT,WA
      chooseLetterOrNumber(str, 2);
      chooseLetterOrNumber(str, 2);
      chooseLetterOrNumber(str, 2);
      strcat(str," ");
      chooseLetterOrNumber(str, 1);
      chooseLetterOrNumber(str, 1);
      chooseLetterOrNumber(str, 1);
      break;
   case 1: // 12A B34
         // CT,MA
      chooseLetterOrNumber(str, 2);
      chooseLetterOrNumber(str, 2);
      chooseLetterOrNumber(str, 1);
      strcat(str," ");
      chooseLetterOrNumber(str, 1);
      chooseLetterOrNumber(str, 2);
      chooseLetterOrNumber(str, 2);
      break;
   case 2: // 123 4567
         // NH
      chooseLetterOrNumber(str, 2);
      chooseLetterOrNumber(str, 2);
      chooseLetterOrNumber(str, 2);
      strcat(str," ");
      chooseLetterOrNumber(str, 2);
      chooseLetterOrNumber(str, 2);
      chooseLetterOrNumber(str, 2);
      chooseLetterOrNumber(str, 2);
      break;
   case 3: // ABC 1234
         // PA, NY, MI, MD
      chooseLetterOrNumber(str, 1);
      chooseLetterOrNumber(str, 1);
      chooseLetterOrNumber(str, 1);
      strcat(str," ");
      chooseLetterOrNumber(str, 2);
      chooseLetterOrNumber(str, 2);
      chooseLetterOrNumber(str, 2);
      chooseLetterOrNumber(str, 2);
      break;
   case 4: // 12A34
         // School Buses.
      chooseLetterOrNumber(str, 2);
      chooseLetterOrNumber(str, 2);
      chooseLetterOrNumber(str, 1);
      chooseLetterOrNumber(str, 2);
      chooseLetterOrNumber(str, 2);
      break;
   case 5: // A 12345
         // Trucks, etc.
      chooseLetterOrNumber(str, 1);
      strcat(str," ");
      chooseLetterOrNumber(str, 2);
      chooseLetterOrNumber(str, 2);
      chooseLetterOrNumber(str, 2);
      chooseLetterOrNumber(str, 2);
      chooseLetterOrNumber(str, 2);
      break;
   case 6: // 1AB 234
         // CT, MA
      chooseLetterOrNumber(str, 2);
      chooseLetterOrNumber(str, 1);
      chooseLetterOrNumber(str, 1);
      strcat(str," ");
      chooseLetterOrNumber(str, 2);
      chooseLetterOrNumber(str, 2);
      chooseLetterOrNumber(str, 2);
      break;
   case 7: // ABC 123
         // VT, MD
      chooseLetterOrNumber(str, 1);
      chooseLetterOrNumber(str, 1);
      chooseLetterOrNumber(str, 1);
      strcat(str," ");
      chooseLetterOrNumber(str, 2);
      chooseLetterOrNumber(str, 2);
      chooseLetterOrNumber(str, 2);
      break;
   }
}

/* pick a random state, or give the name of the specified state */
const char* statename(int i)
{
   if(i < 0 || i >= 50) i = LCSrandom(50);

   switch(i)
   {
   case 0:return "アラバマ州";
   case 1:return "アラスカ州";
   case 2:return "アーカンソー州";
   case 3:return "アリゾナ州";
   case 4:return "カリフォルニア州";
   case 5:return "コロラド州";
   case 6:return "コネチカット州";
   case 7:return "デラウェア州";
   case 8:return "フロリダ州";
   case 9:return "ジョージア州";
   case 10:return "ハワイ州";
   case 11:return "アイダホ州";
   case 12:return "イリノイ州";
   case 13:return "インディアナ州";
   case 14:return "アイオワ州";
   case 15:return "カンザス州";
   case 16:return "ケンタッキー州";
   case 17:return "ルイジアナ州";
   case 18:return "メイン州";
   case 19:return "メリーランド州";
   case 20:return "マサチューセッツ州";
   case 21:return "ミシガン州";
   case 22:return "ミネソタ州";
   case 23:return "ミシシッピ州";
   case 24:return "ミズーリ州";
   case 25:return "モンタナ州";
   case 26:return "ネブラスカ州";
   case 27:return "ネバダ州";
   case 28:return "ニューハンプシャー州";
   case 29:return "ニュージャージー州";
   case 30:return "ニューメキシコ州";
   case 31:return "ニューヨーク州";
   case 32:return "ノースカロライナ州";
   case 33:return "ノースダコタ州";
   case 34:return "オハイオ州";
   case 35:return "オクラホマ州";
   case 36:return "オレゴン州";
   case 37:return "ペンシルベニア州";
   case 38:return "ロードアイランド州";
   case 39:return "サウスカロライナ州";
   case 40:return "サウスダコタ州";
   case 41:return "テネシー州";
   case 42:return "テキサス州";
   case 43:return "ユタ州";
   case 44:return "バーモント州";
   case 45:return "バージニア州";
   case 46:return "ワシントン州";
   case 47:return "ウェストバージニア州";
   case 48:return "ウィスコンシン州";
   case 49:return "ワイオミング州";

   default:return "ホーホク州"; // The Areas of My Expertise -- John Hodgman
   }
}

/* endgame - converts an integer into a roman numeral for amendments */
void romannumeral(int amendnum)
{
   while(amendnum>=1000)
   {
      amendnum-=1000;
      addchar('M');
   }
   if(amendnum>=900)
   {
      amendnum-=900;
      addchar('C');
      addchar('M');
   }
   if(amendnum>=500)
   {
      amendnum-=500;
      addchar('D');
   }
   if(amendnum>=400)
   {
      amendnum-=400;
      addchar('C');
      addchar('D');
   }
   while(amendnum>=100)
   {
      amendnum-=100;
      addchar('C');
   }
   if(amendnum>=90)
   {
      amendnum-=90;
      addchar('X');
      addchar('C');
   }
   if(amendnum>=50)
   {
      amendnum-=50;
      addchar('L');
   }
   if(amendnum>=40)
   {
      amendnum-=40;
      addchar('X');
      addchar('L');
   }
   while(amendnum>=10)
   {
      amendnum-=10;
      addchar('X');
   }
   if(amendnum>=9)
   {
      amendnum-=9;
      addchar('I');
      addchar('X');
   }
   if(amendnum>=5)
   {
      amendnum-=5;
      addchar('V');
   }
   if(amendnum>=4)
   {
      amendnum-=4;
      addchar('I');
      addchar('V');
   }
   while(amendnum>=1)
   {
      amendnum-=1;
      addchar('I');
   }
}

// Sets the interval according to a string that is either a number or two
// number separated by a dash. Returns false and does not change the
// interval if the given string is not a valid interval.
bool Interval::set_interval(const string& interval)
{
   if(!len(interval) ||
      interval.find_first_not_of("1234567890-")!=string::npos)
      return false;

   size_t dashpos=interval.find('-',1);
   if(dashpos==string::npos) // Just a constant.
   {
      if(!valid(interval)) return false;
      max=min=atoi(interval);
   }
   else
   {
      string smin=interval.substr(0,dashpos),smax=interval.substr(dashpos+1);
      if(!valid(smin)||!valid(smax)) return false;
      int tmin=atoi(smin),tmax=atoi(smax);
      if(tmin>tmax) return false;
      min=tmin,max=tmax;
   }
   return true;
}

#ifndef DONT_INCLUDE_SDL
/* helper function for initsongs() */
void MusicClass::loadsong(int i,const char* filename)
{  // the reason it prints progress on the screen is because it might be a little slow sometimes so this reassures the user progress is being made
   clear();
   if(oggsupport)
   {
      mvaddstr(12,0,"Loading Ogg Vorbis music ("+tostring(i+1)+"/"+tostring(MUSIC_OFF)+"): "+artdir+"ogg/"+filename+".ogg");
      mvaddstr(13,0,string("(with ")+artdir+"midi/"+filename+".mid as MIDI fallback)");
   }
   else mvaddstr(12,0,"Loading MIDI music ("+tostring(i+1)+"/"+tostring(MUSIC_OFF)+"): "+artdir+"midi/"+filename+".mid");
   refresh();
   if(oggsupport) songs[i]=Mix_LoadMUS((string(artdir)+"ogg/"+filename+".ogg").c_str()); // only attempt loading Ogg if we have Ogg support
   if(!songs[i]||!oggsupport) // it failed to load Ogg Vorbis music or Ogg support doesn't exist, let's try MIDI instead
   {
      if(oggsupport) gamelog.log(string("SDL_mixer function Mix_LoadMUS() failed to load ")+artdir+"ogg/"+filename+".ogg:  "+Mix_GetError()); // Ogg Vorbis music failed to load
      songs[i]=Mix_LoadMUS((string(artdir)+"midi/"+filename+".mid").c_str());
   }
   if(!songs[i]) // there was an error with Mix_LoadMUS() when called on the MIDI file
      gamelog.log(string("SDL_mixer function Mix_LoadMUS() failed to load ")+artdir+"midi/"+filename+".mid:  "+Mix_GetError()); // MIDI music failed to load
}
#endif // DONT_INCLUDE_SDL

/* initialize SDL, SDL_mixer, and songs */
void MusicClass::init()
{
#ifndef DONT_INCLUDE_SDL
   if(songsinitialized) return; // only initialize once
   if(SDL_Init(SDL_INIT_AUDIO)!=0) // initialize what we need from SDL for audio
   {  // SDL failed to initialize, so log it and exit
      addstr(string("Unable to initialize SDL:  ")+SDL_GetError(),gamelog);
      gamelog.nextMessage();

      getkey();

      endwin();
      exit(EXIT_FAILURE);
   }
   if(Mix_OpenAudio(44100,MIX_DEFAULT_FORMAT,2,4096)!=0) // initialize the audio mixer at 44.1 kHz with a large buffer size, since we're just playing music not sound effects
   {  // SDL_mixer failed to initialize, so log it and exit
      addstr(string("Unable to initialize SDL_mixer:  ")+Mix_GetError(),gamelog);
      gamelog.nextMessage();

      getkey();

      SDL_Quit();
      endwin();
      exit(EXIT_FAILURE);
   }
   if((Mix_Init(MIX_INIT_OGG|MIX_INIT_FLUIDSYNTH)&MIX_INIT_OGG)!=MIX_INIT_OGG) // initialize Ogg Vorbis support (and FluidSynth if it's there for better MIDI quality)
   {  // Ogg Vorbis support failed to load, we'll use MIDI instead
      gamelog.log("Ogg Vorbis support failed to load. MIDI music will be used instead if possible.");
      gamelog.nextMessage();
      oggsupport=false;
   }
   else oggsupport=true; // we have Ogg Vorbis support!
   // titlemode.ogg or .mid - Also sprach Zarathustra, introduction by Richard Strauss
   loadsong(MUSIC_TITLEMODE,"titlemode"); // load title mode music
   // newgame.ogg or .mid- The Liberty Bell March by John Philip Sousa
   loadsong(MUSIC_NEWGAME,"newgame"); // load new game music
   // basemode.ogg or .mid - The Stars and Stripes Forever by John Philip Sousa
   loadsong(MUSIC_BASEMODE,"basemode"); // load regular base mode music
   // siege.ogg or .mid- The Planets, 1st Movement "Mars" by Gustav Holst
   loadsong(MUSIC_SIEGE,"siege"); // load base mode while under siege music
   // activate.ogg or .mid - Piano Sonata #11, 3rd Movement "Rondo Alla Turca" by Wolfgang Amadeus Mozart
   loadsong(MUSIC_ACTIVATE,"activate"); // load activate Liberals music
   // sleepers.ogg or .mid - Toccata and Fugue in D Minor, BWV 565 by Johann Sebastian Bach
   loadsong(MUSIC_SLEEPERS,"sleepers"); // load activate Sleepers music
   // stopevil.ogg or .mid - Hungarian Dance #5 by Johannes Brahms (based on the csardas "Bartfai emlek" by Bela Keler)
   loadsong(MUSIC_STOPEVIL,"stopevil"); // load go forth to stop evil music
   // reviewmode.ogg or .mid - Symphony #94, 2nd Movement "Surprise Symphony" by Joseph Haydn
   loadsong(MUSIC_REVIEWMODE,"reviewmode"); // load review mode music
   // liberalagenda.ogg or .mid - Beautiful Dreamer by Stephen Foster
   loadsong(MUSIC_LIBERALAGENDA,"liberalagenda"); // load status of the Liberal agenda music
   // disbanded.ogg or .mid - La Cucaracha, a traditional Mexican folk song originally from Spain
   loadsong(MUSIC_DISBANDED,"disbanded"); // load disbanded music
   // finances.ogg or .mid - Minuet in G Major by Christian Petzold (falsely attributed to Johann Sebastian Bach until 1970)
   loadsong(MUSIC_FINANCES,"finances"); // load finance report music
   // cartheft.ogg or .mid - The Ride of the Valkyries by Richard Wanger
   loadsong(MUSIC_CARTHEFT,"cartheft"); // load car theft music
   // elections.ogg or .mid - Habanera from Carmen by Georges Bizet
   loadsong(MUSIC_ELECTIONS,"elections"); // load elections music
   // shopping.ogg or .mid - The Entertainer by Scott Joplin
   loadsong(MUSIC_SHOPPING,"shopping"); // load shopping music
   // sitemode.ogg or .mid - Dance of the Sugar Plum Fairy by Pyotr Ilyich Tchaikovsky
   loadsong(MUSIC_SITEMODE,"sitemode"); // load site mode music
   // suspicious.ogg or .mid - Hall of the Mountain King by Edvard Grieg
   loadsong(MUSIC_SUSPICIOUS,"suspicious"); // load suspicious music
   // alarmed.ogg or .mid - 5th Symphony, 1st Movement by Ludwig van Beethoven
   loadsong(MUSIC_ALARMED,"alarmed"); // load alarmed music
   // heavycombat.ogg or .mid - 6th Symphony "Pastorale", 4th Movement by Ludwig van Beethoven
   loadsong(MUSIC_HEAVYCOMBAT,"heavycombat"); // load massive Conservative response music
   // defense.ogg or .mid - Danse Macabre by Camille Saint-Saens
   loadsong(MUSIC_DEFENSE,"defense"); // load escaping/engaging a siege music
   // conquer.ogg or .mid - Infernal Galop / Can-Can from Orpheus in the Underworld by Jacques Offenbach
   loadsong(MUSIC_CONQUER,"conquer"); // load success in conquering a siege or safehouse or the CCS music
   // carchase.ogg or .mid - The William Tell Overture by Gioacchino Antonio Rossini
   loadsong(MUSIC_CARCHASE,"carchase"); // load car chase music
   // footchase.ogg or .mid - The Maple Leaf Rag by Scott Joplin
   loadsong(MUSIC_FOOTCHASE,"footchase"); // load foot chase music
   // interrogation.ogg or .mid - Night on Bald Mountain by Modest Mussorgsky
   loadsong(MUSIC_INTERROGATION,"interrogation"); // load interrogation music
   // trial.ogg or .mid - Hungarian Rhapsody #2 by Franz Liszt
   loadsong(MUSIC_TRIAL,"trial"); // load trial music
   // recruiting.ogg or .mid - Dance of the Hours by Amilcare Ponchielli
   loadsong(MUSIC_RECRUITING,"recruiting"); // load recruiting music
   // dating.ogg or .mid - The Blue Danube Waltz by Johann Strauss Jr.
   loadsong(MUSIC_DATING,"dating"); // load dating music
   // newspaper.ogg or .mid - Eine Kleine Nachtmusik, 1st Movement by Wolfgang Amadeus Mozart
   loadsong(MUSIC_NEWSPAPER,"newspaper"); // load newspaper music
   // lacops.ogg or .mid - The Flight of the Bumblebee by Nikolai Rimsky-Korsakov
   loadsong(MUSIC_LACOPS,"lacops"); // load LA cops beating black man and getting caught on video music
   // newscast.ogg or .mid - La Marseillaise, The French National Anthem by Claude Joseph Rouget de Lisle
   loadsong(MUSIC_NEWSCAST,"newscast"); // load newscast where smart liberal guest gets some words in edgewise music
   // glamshow.ogg or .mid - Das Deutschlandlied, The German National Anthem by Joseph Haydn
   loadsong(MUSIC_GLAMSHOW,"glamshow"); // load glamorous TV show about lifestyles of the rich and famous music
   // anchor.ogg or .mid - I Am the Very Model of a Modern Major-General by Sir Arthur Seymour Sullivan
   loadsong(MUSIC_ANCHOR,"anchor"); // load handsome charismatic new Conservative cable news anchor music
   // abort.ogg or .mid - Tarantella Napoletana, a traditional Italian folk song from Naples
   loadsong(MUSIC_ABORT,"abort"); // load failed partial birth abortion on trashy daytime talk show music
   // victory.ogg or .mid - The Star-Spangled Banner, The U.S. National Anthem by John Stafford Smith
   loadsong(MUSIC_VICTORY,"victory"); // load victory music
   // defeat.ogg or .mid - Piano Sonata #2, 3rd Movement "Funeral March" by Frederic Francois Chopin
   loadsong(MUSIC_DEFEAT,"defeat"); // load defeat music
   // reagainified.ogg or .mid - Dixie, The Confederate National Anthem by Daniel Decatur Emmett
   loadsong(MUSIC_REAGANIFIED,"reaganified"); // load Reaganified music
   // stalinized.ogg or .mid - The Soviet (and now Russian) National Anthem by Alexander Vasilyevich Alexandrov
   loadsong(MUSIC_STALINIZED,"stalinized"); // load Stalinized music
   clear();
   refresh();
   songsinitialized=true;
#endif // DONT_INCLUDE_SDL
}

/* shut down SDL, SDL_mixer, and songs */
void MusicClass::quit()
{
#ifndef DONT_INCLUDE_SDL
   if(!songsinitialized) return; // only shut down once
   music.play(MUSIC_OFF);
   for(int c=0;c<MUSIC_OFF;c++) if(songs[c]) Mix_FreeMusic(songs[c]);
   while(Mix_Init(0)) Mix_Quit();
   Mix_CloseAudio();
   SDL_Quit();
   songsinitialized=false;
#endif // DONT_INCLUDE_SDL
}

/* play music specified by a MusicMode */
void MusicClass::play(int _musicmode)
{
#ifndef DONT_INCLUDE_SDL
   if(!songsinitialized) init(); // if it hasn't been initialized already, do it now

   if(_musicmode==MUSIC_CURRENT) return; // keep playing current music if that's what's requested
   if(_musicmode==MUSIC_RANDOM) _musicmode=LCSrandom(MUSIC_OFF); // play a random song if that's what's requested
   if(_musicmode==MUSIC_PREVIOUS) _musicmode=previous; // restore previous setting if that's what's requested
   if(musicmode==_musicmode) return; // already playing the right music
   previous=musicmode; // store previous setting
   musicmode=_musicmode; // set musicmode to input

   Mix_HaltMusic(); // stop any music that we're playing

   if(musicmode<0||musicmode>=MUSIC_OFF)
   {
      musicmode=MUSIC_OFF; // just in case we had odd input, make sure we keep track that music is off
      return; // return without playing music
   }

   if(!songs[musicmode]) // there was an error with Mix_LoadMUS() back when it was called on this song
      return; // we can't play music if it isn't loaded, might as well return

   if(Mix_PlayMusic(songs[musicmode],-1)!=0) // start playing the music, and have it loop indefinitely
      gamelog.log(string("SDL_mixer function Mix_PlayMusic() failed:  ")+Mix_GetError()); // Music failed to play

   enableIf(isEnabled());
#endif // DONT_INCLUDE_SDL
}
