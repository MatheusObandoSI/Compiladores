obmc: obmc.l obmc.y obmc.h
	bison -d obmc.y
	flex -o obmc.lex.c obmc.l
	cc -o $@ obmc.tab.c obmc.lex.c obmc.c

clean:
	rm -f obmc \
	obmc.lex.c obmc.tab.h obmc.tab.c
