parser:syntax.y lexical.l semantic.c main.c
	bison -d syntax.y
	flex lexical.l
	gcc syntax.tab.c semantic.c main.c -lfl -o parser