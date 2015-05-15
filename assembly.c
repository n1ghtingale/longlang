#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include "syntax.h"

const int MAX_MNEMONIC_LENGTH = 7;

void emit_header(FILE *out, char *name){
	fprintf(out, "%s\n", name);
}

void emit_instr_format(FILE *out, char *instr, char *operands_format, ...) {
	fprintf(out, "    %s", instr);

	int argument_offset = MAX_MNEMONIC_LENGTH - strlen(instr) + 4;
    while (argument_offset > 0) {
        fprintf(out, " ");
        argument_offset--;
    }

    va_list argptr;
    va_start(argptr, operands_format);
    vfprintf(out, operands_format, argptr);
    va_end(argptr);

    fputs("\n", out);
}

void emit_instr(FILE *out, char *instr, char *operands) {
    // TODO: fix duplication with emit_instr_format.
    // The assembler requires at least 4 spaces for indentation.
    fprintf(out, "    %s", instr);

    int argument_offset = MAX_MNEMONIC_LENGTH - strlen(instr) + 4;
    while (argument_offset > 0) {
        fprintf(out, " ");
        argument_offset--;
    }

    fprintf(out, "%s\n", operands);
}

void write_header(FILE *out){
	emit_header(out, ".data\nLC0:    .ascii \"%d\\n\\0\"\nLC1:    .ascii \"%x\\n\\0\"\n.text\n    .global _main\n_main:\n");
    	emit_instr(out, "pushl", "%ebp");
    	emit_instr(out, "movl", "%esp, %ebp");
	emit_instr(out, "sub", "$104, %esp");
}

void write_footer(FILE *out){
	emit_instr(out, "pushl", "%eax");
	emit_instr(out, "leave", "");
	emit_instr(out, "ret", "");
}

void write_syntax(FILE *out, Syntax *syntax){
	if(syntax->type == IMMEDIATE){
	    emit_instr_format(out, "mov", "$%d, %%eax", syntax->immediate->value);
	} else if (syntax->type == VARIABLE) {
            emit_instr_format(out, "mov", "-%%d(%ebp), %eax", 4*(syntax->variable->var_index+1));
	} else if (syntax->type == BINARY_OPERATOR){
		BinaryExpression *binary_syntax = syntax->binary_expression;
		//reserve space for temporary 
		write_syntax(out, binary_syntax->left);

		emit_instr(out, "sub", "$4, %esp");
		emit_instr(out, "mov", "%eax, 0(%esp)");
		
		write_syntax(out, binary_syntax->right);
		
		if(binary_syntax->binary_type == MULTIPLICATION){
		    emit_instr(out, "mull", "0(%esp)");
		    //emit_instr(out, "mull", "%ebx");
		    emit_instr(out, "add", "$4, %esp");
		} else if (binary_syntax->binary_type == DIVISION) {
		    //edx:eax / 0(%esp)
	            emit_instr(out, "mov", "$0, %edx");
	            emit_instr(out, "xchg", "0(%esp), %eax");
	            emit_instr(out, "divl", "0(%esp)");

		    emit_instr(out, "add", "$4, %esp");
		} else if (binary_syntax->binary_type == MOD) {
		    emit_instr(out, "mov", "$0, %edx");
	            emit_instr(out, "xchg", "0(%esp), %eax");
	            emit_instr(out, "divl", "0(%esp)");
	            emit_instr(out, "mov", "%edx, %eax");

		    emit_instr(out, "add", "$4, %esp");
		} else if (binary_syntax->binary_type == ADDITION){
		    emit_instr(out, "add", "0(%esp), %eax");
		    //emit_instr(out, "add", "%ebx, %eax");
		    //TODO: check if this instruction redundant
		    emit_instr(out, "add", "$4, %esp");
		} else if (binary_syntax->binary_type == SUBTRACTION) {
		    emit_instr(out, "sub", "%eax, 0(%esp)");
            	    emit_instr(out, "mov", "0(%esp), %eax");
		    emit_instr(out, "add", "$4, %esp");
		}
	} else if (syntax->type == ASSIGNMENT) {
	    write_syntax(out, syntax->assignment->expression);

	    emit_instr_format(out, "mov", "%%eax, -%d(%%ebp)", 4*(syntax->assignment->var_index+1));
	} else if (syntax->type = SHOW_STATEMENT){
	    if(syntax->show_statement->decOrHex == 'd'){
	    	emit_instr_format(out, "pushl", "%%eax, -%d(%%ebp)", 4*(syntax->show_statement->var->variable->var_index+1));
	    	emit_instr(out, "pushl", "$format");
        	emit_instr(out, "call", "_printf");
	    } else if (syntax->show_statement->decOrHex == 'h') {

	    }
	}
}

void write_assembly(Syntax *syntax){
	FILE *out = fopen("out.s", "wb");

	write_header(out);
	write_syntax(out, syntax);
	write_footer(out);
}