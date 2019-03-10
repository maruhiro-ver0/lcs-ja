EXE = crimesquad
OBJS = \
	basemode/activate.o \
	basemode/activate_sleepers.o \
	basemode/baseactions.o \
	basemode/basemode.o \
	basemode/reviewmode.o \
	combat/chase.o \
	combat/fight.o \
	combat/haulkidnap.o \
	common/commonactions.o \
	common/commondisplay.o \
	common/consolesupport.o \
	common/equipment.o \
	common/getnames.o \
	common/help.o \
	basemode/liberalagenda.o \
	common/misc.o \
	common/stringconversion.o \
	common/translateid.o \
	creature/creaturetype.o \
	daily/activities.o \
	daily/daily.o \
	daily/date.o \
	daily/interrogation.o \
	daily/recruit.o \
	daily/shopsnstuff.o \
	daily/siege.o \
	locations/locations.o \
	locations/world.o \
	monthly/endgame.o \
	monthly/justice.o \
	monthly/lcsmonthly.o \
	monthly/monthly.o \
	monthly/sleeper_update.o \
	news/news.o \
	sitemode/advance.o \
	sitemode/mapspecials.o \
	sitemode/miscactions.o \
	sitemode/newencounter.o \
	sitemode/shop.o \
	sitemode/sitedisplay.o \
	sitemode/sitemap.o \
	sitemode/sitemode.o \
	sitemode/stealth.o \
	sitemode/talk.o \
	title/highscore.o \
	title/initfile.o \
	title/newgame.o \
	title/saveload.o \
	title/titlescreen.o \
	politics/law.o \
	politics/politics.o \
	news/ads.o \
	news/headline.o \
	news/layout.o \
	news/majorevent.o \
	news/squadstory_text.o \
	items/armor.o \
	items/armortype.o \
	items/clip.o \
	items/cliptype.o \
	items/item.o \
	items/itemtype.o \
	items/loot.o \
	items/loottype.o \
	items/money.o \
	items/weapon.o \
	items/weapontype.o \
	creature/creature.o \
	creature/creaturenames.o \
	creature/creaturetypes.o \
	vehicle/vehicle.o \
	vehicle/vehicletype.o \
	cmarkup/Markup.o \
	log/log.o \
	compat.o \
	configfile.o \
	cursesgraphics.o \
	cursesmovie.o \
	game.o \
	lcsio.o
CC = g++
#CFLAGS = -w -I$(shell pwd) -I./pdcurses/ -DNOMINMAX -DMARKUP_STL $(shell sdl2-config --cflags) 
#LDFLAGS = -L./pdcurses/ -lpdcurses -lSDL2_mixer $(shell sdl2-config --libs)
CFLAGS = -w -I$(shell pwd) -DNOMINMAX -DMARKUP_STL -DDONT_INCLUDE_SDL
LDFLAGS = -lpdcurses

$(EXE): $(OBJS)
	$(CC) -o $(EXE) $(OBJS) $(LDFLAGS)
.cpp.o:
	$(CC) $(CFLAGS) -E -c $< | iconv -f UTF-8 -t cp932 | sed 's/[\x80-\xff]\\/&\\/g' | $(CC) $(CFLAGS) -c -xc++ -o $@ -

clean:
	rm -f $(OBJS) $(EXE) $(EXE).exe
