%{
#include <stdlib.h>
#include <stdio.h>
#include "prog.tab.h"
%}

%option noyywrap

%%
[0-9]+    return num;
"+"		  return PLUS;
%%	