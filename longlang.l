%option noyywrap
%{
 #include<stdio.h>
 #include "longlang.tab.h"
%}
%%
[\n]	{return newL;}
[+]	{return '+';}
[-]	{return '-';}
[*]	{return '*';}
[/]	{return '/';}
[%] {return '%';}
[=] {return '=';}


"SHOW"   {return show;}
"SHOWH"   {return showH;}
"TO"   {return to;}
"==" 	{return eql;}
"FOR"	{return FOR;}
"IF" 	{return IF;}


[A-Z]	{return var;}
[(]	{return '(';}
[)]	{return ')';}


[0-9A-Fa-f]+h 	{yylval = strtol(yytext,NULL,16); return NUM;}
[0-9]+ 	{yylval = atoi(yytext); return CONST;}
" " 	{ }
. 	{ return wrong; }
%%

