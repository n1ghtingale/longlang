%option noyywrap
%{
 #include<stdio.h>
 #include "calc.tab.h"
%}
%%
[\n]	{return 'newL';}
[\]	{ }
[+]	{return '+';}
[-]	{return '-';}
[*]	{return '*';}
[/]	{return '/';}
[%] {return '%';}
[=] {return '=';}


"NOT"   {return not;}
"SHOW"   {return show;}
"SHOWH"   {return showh;}
"TO"   {return to;}
"==" 	{return eql;}
"FOR"	{return for;}
"IF" 	{return if;}


[A-Z]	{return var;}
[(]	{return '(';}
[)]	{return ')';}


[0-9A-Fa-f]+h 	{yylval = strtol(yytext,NULL,16); return NUM;}
[0-9]+ 	{yylval = atol(yytext); return NUM;}
" " 	{ }
. 	{ return wrong; }
%%

