#include <unistd.h>
#include <cstdio>
#include "cool-tree.h"
#include "utilities.h"
#include "cool-parse.h"
#include <fstream>  
#include "semant.cc"

std::FILE *token_file = stdin;
extern Classes parse_results;
extern Program ast_root;

extern int curr_lineno;
const char *curr_filename = "<stdin>";
extern int parse_errors;

// Debug flags
extern int yy_flex_debug;
extern int cool_yydebug;
int lex_verbose = 0;

extern int cool_yyparse();

int main(int argc, char **argv)
{
    yy_flex_debug = 0;
    cool_yydebug = 0;
    lex_verbose  = 0;

    for (int i = 1; i < argc; i++) {
        token_file = std::fopen(argv[i], "r");
        if (token_file == NULL) {
            std::cerr << "Error: can not open file " << argv[i] << std::endl;
            std::exit(1);
        }
        curr_lineno = 1;

        cool_yyparse();
        if (parse_errors != 0) {
            std::cerr << "Error: parse errors\n";
            std::exit(1);
        }

        if (ast_root)
        {
            //ast_root->dump_with_types(std::cerr, 1);

            std::ofstream out4("out/ast.txt");
            if (out4.is_open()) {
                ast_root->dump_with_types(out4, 1);
                out4.close();
        }
        }
           
        else
            std::cerr << "Error: ast_root is NULL\n";

        std::ofstream out("out/stringtable.txt");
        if (out.is_open()){
            stringtable.print(out);
            out.close();
        }

        std::ofstream out2("out/inttable.txt");
        if (out2.is_open()){
           
            inttable.print(out2);
            out2.close();
        }

        std::ofstream out3("out/idtable.txt");
        if (out3.is_open()){
            
            idtable.print(out3);
            out3.close();
        }
         //booltable.print(out);

        std::fclose(token_file);
    }
    semant();
    if (semant_errors != 0) {
        std::cerr << "Code have some semantic errors\n";
        std::exit(1);
    }

    return 0;
}
