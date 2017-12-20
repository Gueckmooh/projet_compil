    #include <assert.h>
    #include <stdio.h>
    #include <stdlib.h>
    #include "ast.h"
    #include "list.h"
    #include "knorm.h"
    #include "alpha_conv.h"
    #include "reduce_nested_let.h"


    int knorm_var_counter, alpha_var_counter;



    void print_term(ptree t);

    void print_binary(char *op, ptree t1, ptree t2) {
        printf("(");
        print_term(t1);
        printf(" %s ", op);
        print_term(t2);
        printf(")");
    }

    void print_id(id i) {
        printf("%s", i);
    }

    void print_unary(char *op, ptree t) {
        printf("(");
        printf("%s ", op);
        print_term(t);
        printf(")");
    }

    // precondition: list is not empty
    void print_list(plist l, char *sep, void f(void *)) {
        assert(l && !is_empty(l));
        plist cur = l;
        f(head(cur));
        cur = tail(cur);
        while (!is_empty(cur)) {
            printf("%s", sep);
            f(head(cur));
            cur = tail(cur);
        }
    }

    void print_term(ptree t) {
        assert(t);
        switch (t->code) {
            case T_UNIT:
                printf("()");
                break;
            case T_BOOL:
                printf("%s", t->params.b?"true":"false");
                break;
            case T_INT:
                printf("%d", t->params.i);
                break;
            case T_FLOAT:
                printf("%.2f", t->params.f);
                break;
            case T_LET:
                printf("(");
                printf("let %s = ", t->params.tlet.v);
                print_term( t->params.tlet.t1);
                printf(" in ");
                print_term( t->params.tlet.t2);
                printf(")");
                break;
            case T_VAR:
                printf("%s", t->params.v);
                break;
            case T_ADD:
                print_binary("+",
                        t->params.tbinary.t1,
                        t->params.tbinary.t2);
                break;
            case T_SUB:
                print_binary("-",
                        t->params.tbinary.t1,
                        t->params.tbinary.t2);
                break;
            case T_FADD:
                print_binary("+.",
                        t->params.tbinary.t1,
                        t->params.tbinary.t2);
                break;
            case T_FSUB:
                print_binary("-.",
                        t->params.tbinary.t1,
                        t->params.tbinary.t2);
                break;
            case T_FMUL:
                print_binary("*.",
                        t->params.tbinary.t1,
                        t->params.tbinary.t2);
                break;
            case T_FDIV:
                print_binary("/.",
                        t->params.tbinary.t1,
                        t->params.tbinary.t2);
                break;
            case T_LE:
                print_binary("<=",
                        t->params.tbinary.t1,
                        t->params.tbinary.t2);
                break;
            case T_EQ:
                print_binary("=",
                        t->params.tbinary.t1,
                        t->params.tbinary.t2);
                break;
            case T_NEG:
                print_unary("-", t->params.t);
                break;
            case T_FNEG:
                print_unary("-.", t->params.t);
                break;
            case T_NOT:
                assert(t->code == T_NOT);
                assert(t->params.t->code != T_NOT);
                print_unary("not", t->params.t);
                break;
            case T_PUT:
                printf("(");
                print_term(t->params.tternary.t1);
                printf(".(");
                print_term(t->params.tternary.t2);
                printf(") <- ");
                print_term(t->params.tternary.t3);
                printf(")");
                break;
            case T_GET:
                print_term(t->params.tbinary.t1);
                printf(".(");
                print_term(t->params.tbinary.t2);
                printf(")");
                break;
            case T_ARRAY:
                printf("(Array.create ");
                print_term(t->params.tbinary.t1);
                printf(" ");
                print_term(t->params.tbinary.t2);
                printf(")");
                break;
            case T_IF:
                printf("(if ");
                print_term(t->params.tternary.t1);
                printf(" then ");
                print_term(t->params.tternary.t2);
                printf(" else ");
                print_term(t->params.tternary.t3);
                printf(")");
                break;
            case T_LETREC:
                printf("(let rec %s ",
                        t->params.tletrec.fd->var);
            print_list(t->params.tletrec.fd->args, " ",
                       (void *)print_id);
                printf(" = ");
                print_term(t->params.tletrec.fd->body);
                printf(" in ");
                print_term(t->params.tletrec.t);
                printf(")");
                break;
             case T_TUPLE:
                printf("(");
                print_list(t->params.ttuple.l, ", ",
                          (void *)print_term);
                // TODO - revoir type
                printf(")");
                break;
             case T_APP:
                printf("(");
                print_term(t->params.tapp.t);
                printf(" ");
                print_list(t->params.tapp.l, " " ,
                          (void *)print_term);
                printf(")");
                break;
             case T_LETTUPLE:
                printf("(let (");
                print_list(t->params.lettuple.l, ", ",
                          (void *)print_id);
                printf(") = ");
                print_term(t->params.lettuple.t1);
                printf(" in ");
                print_term(t->params.lettuple.t2);
                printf(")");
                break;
           default:
                printf("%d ", t->code);
                assert(false);
        }
    }

    // BONJOUR JE SUIS DANS LE MAIN
    // SILVOUPLAIT BOUGEZ MOI DANS UNE AUTRE FONCTION
        void write_term(FILE* output,ptree t);

    void write_binary(FILE* output,char *op, ptree t1, ptree t2) {
        fprintf(output,"(");
        write_term(output,t1);
        fprintf(output," %s ", op);
        write_term(output,t2);
        fprintf(output,")");
    }

    void write_id(FILE* output,id i) {
        fprintf(output,"%s", i);
    }

    void write_unary(FILE* output,char *op, ptree t) {
        fprintf(output,"(");
        fprintf(output,"%s ", op);
        write_term(output,t);
        fprintf(output,")");
    }

    // precondition: list is not empty
    void write_list(FILE* output,plist l, char *sep, void f(void *)) {
        assert(l && !is_empty(l));
        plist cur = l;
        f(head(cur));
        cur = tail(cur);
        while (!is_empty(cur)) {
            fprintf(output,"%s", sep);
            f(head(cur));
            cur = tail(cur);
        }
    }

    void write_term(FILE* output,ptree t) {
        assert(t);
        switch (t->code) {
            case T_UNIT:
                fprintf(output,"()");
                break;
            case T_BOOL:
                fprintf(output,"%s", t->params.b?"true":"false");
                break;
            case T_INT:
                fprintf(output,"%d", t->params.i);
                break;
            case T_FLOAT:
                fprintf(output,"%.2f", t->params.f);
                break;
            case T_LET:
                fprintf(output,"(");
                fprintf(output,"let %s = ", t->params.tlet.v);
                write_term(output, t->params.tlet.t1);
                fprintf(output," in ");
                write_term(output, t->params.tlet.t2);
                fprintf(output,")");
                break;
            case T_VAR:
                fprintf(output,"%s", t->params.v);
                break;
            case T_ADD:
                write_binary(output,"+",
                        t->params.tbinary.t1,
                        t->params.tbinary.t2);
                break;
            case T_SUB:
                write_binary(output,"-",
                        t->params.tbinary.t1,
                        t->params.tbinary.t2);
                break;
            case T_FADD:
                write_binary(output,"+.",
                        t->params.tbinary.t1,
                        t->params.tbinary.t2);
                break;
            case T_FSUB:
                write_binary(output,"-.",
                        t->params.tbinary.t1,
                        t->params.tbinary.t2);
                break;
            case T_FMUL:
                write_binary(output,"*.",
                        t->params.tbinary.t1,
                        t->params.tbinary.t2);
                break;
            case T_FDIV:
                write_binary(output,"/.",
                        t->params.tbinary.t1,
                        t->params.tbinary.t2);
                break;
            case T_LE:
                write_binary(output,"<=",
                        t->params.tbinary.t1,
                        t->params.tbinary.t2);
                break;
            case T_EQ:
                write_binary(output,"=",
                        t->params.tbinary.t1,
                        t->params.tbinary.t2);
                break;
            case T_NEG:
                write_unary(output,"-", t->params.t);
                break;
            case T_FNEG:
                write_unary(output,"-.", t->params.t);
                break;
            case T_NOT:
                assert(t->code == T_NOT);
                assert(t->params.t->code != T_NOT);
                write_unary(output,"not", t->params.t);
                break;
            case T_PUT:
                fprintf(output,"(");
                write_term(output,t->params.tternary.t1);
                fprintf(output,".(");
                write_term(output,t->params.tternary.t2);
                fprintf(output,") <- ");
                write_term(output,t->params.tternary.t3);
                fprintf(output,")");
                break;
            case T_GET:
                write_term(output,t->params.tbinary.t1);
                fprintf(output,".(");
                write_term(output,t->params.tbinary.t2);
                fprintf(output,")");
                break;
            case T_ARRAY:
                fprintf(output,"(Array.create ");
                write_term(output,t->params.tbinary.t1);
                fprintf(output," ");
                write_term(output,t->params.tbinary.t2);
                fprintf(output,")");
                break;
            case T_IF:
                fprintf(output,"(if ");
                write_term(output,t->params.tternary.t1);
                fprintf(output," then ");
                write_term(output,t->params.tternary.t2);
                fprintf(output," else ");
                write_term(output,t->params.tternary.t3);
                fprintf(output,")");
                break;
            case T_LETREC:
                fprintf(output,"(let rec %s ",
                        t->params.tletrec.fd->var);
            write_list(output,t->params.tletrec.fd->args, " ",
                       (void *)write_id);
                fprintf(output," = ");
                write_term(output,t->params.tletrec.fd->body);
                fprintf(output," in ");
                write_term(output,t->params.tletrec.t);
                fprintf(output,")");
                break;
             case T_TUPLE:
                fprintf(output,"(");
                write_list(output,t->params.ttuple.l, ", ",
                          (void *)write_term);
                // TODO - revoir type
                fprintf(output,")");
                break;
             case T_APP:
                fprintf(output,"(");
                write_term(output,t->params.tapp.t);
                fprintf(output," ");
                write_list(output,t->params.tapp.l, " " ,
                          (void *)write_term);
                fprintf(output,")");
                break;
             case T_LETTUPLE:
                fprintf(output,"(let (");
                write_list(output,t->params.lettuple.l, ", ",
                          (void *)write_id);
                fprintf(output,") = ");
                write_term(output,t->params.lettuple.t1);
                fprintf(output," in ");
                write_term(output,t->params.lettuple.t2);
                fprintf(output,")");
                break;
           default:
                fprintf(output,"%d ", t->code);
                assert(false);
        }
    }




    extern FILE *yyin;
    extern int yydebug;
    extern int yyparse(ptree *ast);



    int parsecall(ptree* p, char* fichier){
    	FILE *file;

    	file = fopen(fichier,"r");
        yyin = file;
        if (file == NULL){
            fprintf(stderr,"Erreur : impossible d'ouvrir le fichier");
            return 1;
        }

        if (yyparse(p) != 0){
            fprintf(stderr,"Erreur : Parsing Error");
            return 1;
        }

        return 0;

    }

    int parseprint(ptree p, char* fichier){
        FILE *file;
        file = fopen(fichier,"w");
        if (file == NULL){
            fprintf(stderr,"Erreur : impossible d'ouvrir le fichier");
            return 1;
        }
        write_term(file,p);
            return 0;

    }

    int main(int argc, char **argv) {
    	//FILE *file;
        if (argc < 2) {
            printf("usage: %s file name outputname\n", argv[0]);
            return 0;
        }
        ptree p = malloc(sizeof(ptree));
        parsecall(&p,argv[1]);
        print_term(p);
	//printf("_________\n");
    parseprint(p,argv[2]);
    //printf("___ ___ ___ \n");
        /*
    	file = fopen(argv[1], "r");
        if (file == NULL) {
            printf("cannot open file %s\n", argv[1]);
            return 0;
        }


        /// parsing

        yyin = file;

        // yydebug = 1;
        ptree p;
        if (yyparse(&p) != 0) {
            printf("parse error");
            return 0;
        }
        */

        /// global -> je fais
        knorm_var_counter = 0;
        alpha_var_counter = 0;
        print_term(p);

        /// fonctions pour knorm, alpha et reduce let

        printf("\n\n");
        print_term(knorm(p));
        printf("\n\n");
        print_term(alpha_convert(knorm(p), empty()));
        printf("\n\n");
        print_term(reduce_nested_let(alpha_convert(knorm(p), empty())));
        printf("\n\n");
        print_term(reduce_nested_let(p));
        printf("\n\n");
        return 0;
    }
