%option noyywrap
%{
 #include<stdio.h>
 #include "longlang.tab.h"
%}
%%
[\n]	{return NEWL;}
[+]	{return '+';}
[-]	{return '-';}
[*]	{return '*';}
[/]	{return '/';}
[%] {return '%';}
[=] {return '=';}


"SHOW"   {return SHOW;}
"SHOWH"   {return SHOWH;}
"TO"   {return TO;}
"==" 	{return EQL;}
"FOR"	{return FOR;}
"IF" 	{return IF;}
"A" 	{yylval=0 return VAR;}
"B" 	{yylval=1 return VAR;}
"C" 	{yylval=2 return VAR;}
"D" 	{yylval=3 return VAR;}
"E" 	{yylval=4 return VAR;}
"F" 	{yylval=5 return VAR;}
"G" 	{yylval=6 return VAR;}
"H" 	{yylval=7 return VAR;}
"I" 	{yylval=8 return VAR;}
"J" 	{yylval=9 return VAR;}
"K" 	{yylval=10 return VAR;}
"L" 	{yylval=11 return VAR;}
"M" 	{yylval=12 return VAR;}
"N" 	{yylval=13 return VAR;}
"O" 	{yylval=14 return VAR;}
"P" 	{yylval=15 return VAR;}
"Q" 	{yylval=16 return VAR;}
"R" 	{yylval=17 return VAR;}
"S" 	{yylval=18 return VAR;}
"T" 	{yylval=19 return VAR;}
"U" 	{yylval=20 return VAR;}
"V" 	{yylval=21 return VAR;}
"W" 	{yylval=22 return VAR;}
"X" 	{yylval=23 return VAR;}
"Y" 	{yylval=24 return VAR;}
"Z" 	{yylval=25 return VAR;}


[(]	{return '(';}
[)]	{return ')';}


[0-9A-Fa-f]+h 	{yylval = strtol(yytext,NULL,16); return NUM;}
[0-9]+ 	{yylval = atoi(yytext); return CONST;}
" " 	{ }
. 	{ return WRONG; }
%%