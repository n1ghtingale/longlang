all: longlang

longlang: lex.yy.c longlang.tab.c syntax.c stack.c assembly.c
	export BISON_SIMPLE=../bison.simple
	flex longlang.l
	bison -d longlang.y
	gcc -o longlang.exe lex.yy.c longlang.tab.c syntax.c stack.c assembly.c

clean:
	$(RM) longlang.exe