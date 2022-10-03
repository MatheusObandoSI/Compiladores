obmc: obmc.l obmc.y obmc.h
	bison -d obmc.y
	flex -o obmc.lex.c obmc.l
	cc -o $@ obmc.tab.c obmc.lex.c obmc.c