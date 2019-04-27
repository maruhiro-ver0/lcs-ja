all:
	cd src; make -f Makefile

install:
	cp -p ./src/crimesquad /usr/local/bin
	rm -r -f /usr/local/share/lcs
	mkdir /usr/local/share/lcs
	mkdir /usr/local/share/lcs/art
	cp -p -r art/ /usr/local/share/lcs

lcs_win32_jp.zip:
	rm -r -f lcs_win32_jp
	mkdir lcs_win32_jp
	mkdir lcs_win32_jp/art
	cp -p art/*.* lcs_win32_jp/art
	cp -p src/crimesquad.exe docs/CrimeSquadManual.txt ./pdcurses.dll ./COPYING lcs_win32_jp/
	zip -u -9 lcs_win32_jp.zip lcs_win32_jp/*
	zip -u -9 lcs_win32_jp.zip lcs_win32_jp/art/*
	rm -r -f lcs_win32_jp

clean:
	cd src; make clean
	rm -r -f lcs_win32_jp
	rm -f *.zip
