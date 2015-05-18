#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include "syntax.h"

const int MAX_MNEMONIC_LENGTH = 7;
int label_count = 2;

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

void emit_label(FILE *out, char *label) { fprintf(out, "%s:\n", label); }

void write_header(FILE *out){
	emit_header(out, ".data\n.LC0:    .ascii \"%d\\n\\0\"\n.LC1:    .ascii \"%x\\n\\0\"\n.text\n    .global _main\n_main:\n");
    	emit_instr(out, "pushl", "%ebp");
    	emit_instr(out, "movl", "%esp, %ebp");
	emit_instr(out, "sub", "$104, %esp");
}

void write_footer(FILE *out){
	emit_instr(out, "pushl", "$0");
	emit_instr(out, "leave", "");
	emit_instr(out, "ret", "");
}

char *gen_label(char *prefix);

void write_syntax(FILE *out, Syntax *syntax){
	printf("write_syntax\n");
	if(syntax->type == IMMEDIATE){
	    printf("case gen immediate\n");
	    emit_instr_format(out, "mov", "$%d, %%eax", syntax->immediate->value);
	} else if (syntax->type == VARIABLE) {
	    printf("case gen var\n");
            emit_instr_format(out, "mov", "-%d(%%ebp), %%eax", 4*(syntax->variable->var_index+1));
	} else if (syntax->type == BINARY_OPERATOR){
		printf("case gen binary\n");
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
		} else if (binary_syntax->binary_type == COMPARISION) {
		    emit_instr(out, "xor", "0(%esp), %eax");
		    emit_instr(out, "add", "$4, %esp");
		}
	} else if (syntax->type == ASSIGNMENT) {
	    printf("case gen assignment\n");
	    write_syntax(out, syntax->assignment->expression);

	    emit_instr_format(out, "mov", "%%eax, -%d(%%ebp)", 4*(syntax->assignment->var_index+1));
	} else if (syntax->type == SHOW_STATEMENT){
	    printf("case get SHOW statement");
	    if(syntax->show_statement->decOrHex == 'd'){
	    	emit_instr_format(out, "pushl", "-%d(%%ebp)", 4*(syntax->show_statement->var->variable->var_index+1));
	    	emit_instr(out, "pushl", "$.LC0");
        	emit_instr(out, "call", "_printf");
	    } else if (syntax->show_statement->decOrHex == 'h') {
	    	emit_instr_format(out, "pushl", "-%d(%%ebp)", 4*(syntax->show_statement->var->variable->var_index+1));
	    	emit_instr(out, "pushl", "$.LC1");
        	emit_instr(out, "call", "_printf");
	    }
	} 
	else if (syntax->type == IF_STATEMENT){
	    char *label;
	    printf("case if statement kaa");
	    write_syntax(out, syntax->if_statement->condition);
	    emit_instr(out, "test", "%eax, %eax");
	    label = gen_label("LC");
	    emit_instr_format(out, "jne", "%s", label);
	    write_syntax(out, syntax->if_statement->then);
	    emit_label(out, label);
	    //emit_instr(out, "call", "_printf");
	} else if (syntax->type ==  FOR_STATEMENT) {
	    char *start_label;
	    char *end_label;
	    if(syntax->for_statement->startNum->type == IMMEDIATE){
	    	emit_instr_format(out, "mov", "$%d, %%edi", syntax->for_statement->startNum->immediate->value);
	    } else if (syntax->for_statement->startNum->type == VARIABLE) {
	    	emit_instr_format(out, "mov", "-%d(%%ebp), %%edi", 4*(syntax->for_statement->startNum->variable->var_index+1));
	    }
	    if(syntax->for_statement->stopNum->type == IMMEDIATE){
	    	emit_instr_format(out, "mov", "$%d, %%esi", syntax->for_statement->stopNum->immediate->value);
	    } else if (syntax->for_statement->stopNum->type == VARIABLE) {
                emit_instr_format(out, "mov", "-%d(%%ebp), %%esi", 4*(syntax->for_statement->stopNum->variable->var_index+1));
	    }
	    start_label = gen_label("LC");
	    end_label = gen_label("LC");
	    emit_label(out, start_label);
	    emit_instr(out, "cmp", "%edi, %esi");
	    //confuse which jump condition to use.
	    emit_instr_format(out, "jg", "%s", end_label);
	    write_syntax(out, syntax->for_statement->expression);
	    emit_instr(out, "inc", "%esi");
	    emit_instr_format(out, "jmp", "%s", start_label);
	    emit_label(out, end_label);
	} else if (syntax->type == INPUT) {
	    //printf("gen INPUT\n");
	    List *lines = syntax->input->lines;
	    int i;
            for (i = list_length(lines)-1; i >= 0; i--) {
            	//printf("*");
                write_syntax(out, list_get(lines, i));
            }
	} else if(syntax->type = MINUS){
		printf("gen minus\n");
		write_syntax(out,syntax->minus->expression);
		emit_instr(out, "xor", "%ebx, %ebx");
		emit_instr(out, "sub", "%eax, %ebx");
		emit_instr(out, "mov", "%ebx, %eax");
	} else {
	    printf("last case\n");
	}
	/*else if(syntax->type = MINUS){
		write_syntax(out,syntax->expression);
		emit_instr(out, "sub", "0(%esp), %eax");
	}*/
}
char *gen_label(char *prefix) {
    // We assume we never write more than 6 chars of digits, plus a '.' and '_'.
    size_t buffer_size = strlen(prefix) + 8;
    char *buffer = malloc(buffer_size);

    snprintf(buffer, buffer_size, ".%s_%d", prefix, label_count);
    label_count++;

    return buffer;
}

void write_assembly(Syntax *syntax){
	FILE *out = fopen("out.s", "wb");

	write_header(out);
	write_syntax(out, syntax);
	write_footer(out);
}