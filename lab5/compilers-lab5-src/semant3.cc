#include "utilities.h"
#include "cool-parse.h"
#include <set>
#include <iostream>

extern Classes parse_results;
extern Program ast_root;
extern IdTable idtable;
extern IntTable inttable;
extern StrTable stringtable;
int semant_errors = 0;

typedef struct {
    Symbol* name_of_class;
    IdTable class_idtable;
} class_tables;

IdTable my_table;

bool check_inheritance_cycle(Class_ c, Classes all_classes) {
    std::set<Symbol> visited;
    Symbol current = c->get_name();

    while (!current->equal_string("Object", 6)) {
        if (visited.count(current)) {
            return true;
        }
        visited.insert(current);

        bool found = false;
        for (int i = all_classes->first(); all_classes->more(i); i = all_classes->next(i)) {
            Class_ cls = dynamic_cast<class__class*>(all_classes->nth(i));
            if (cls->get_name()->equal_string(current->get_string(), current->get_len())) {
                current = cls->get_parent();
                found = true;
                break;
            }
        }

        if (!found) {
            return false;
        }
    }
    return false;
}

void check(Expression First, Expression Second, class__class* cls) {
    auto f_type = First;
    if (dynamic_cast<int_const_class*>(First) != nullptr) {
        if (dynamic_cast<int_const_class*>(Second) == nullptr) {
            std::cerr << "Error: Invalid type conversion at class \"" << cls->get_name()->get_string()
                      << "\" at file " << cls->get_filename()->get_string() << ':' << cls->get_line_number() << '\n';
            semant_errors++;
        }
    }
    if (dynamic_cast<string_const_class*>(First) != nullptr) {
        if (dynamic_cast<string_const_class*>(Second) == nullptr) {
            std::cerr << "Error: Invalid type conversion at class \"" << cls->get_name()->get_string()
                      << "\" at file " << cls->get_filename()->get_string() << ':' << cls->get_line_number() << '\n';
            semant_errors++;
        }
    }
    if (dynamic_cast<bool_const_class*>(First) != nullptr) {
        if (dynamic_cast<bool_const_class*>(Second) == nullptr) {
            std::cerr << "Error: Invalid type conversion at class \"" << cls->get_name()->get_string()
                      << "\" at file " << cls->get_filename()->get_string() << ':' << cls->get_line_number() << '\n';
            semant_errors++;
        }
    }
}

void full_types_checker(Expression expr_check, class__class* cls, IdTable table) {
    if (dynamic_cast<no_expr_class*>(expr_check) != nullptr)
        return;

    if (dynamic_cast<assign_class*>(expr_check) != nullptr) {
        auto assign = dynamic_cast<assign_class*>(expr_check);
        if (table.lookup_string(assign->get_name()->get_string()) == nullptr) {
            std::cerr << "Error: Variable \"" << assign->get_name()->get_string()
                      << "\" was not declared at " << cls->get_filename()->get_string() << ':'
                      << cls->get_line_number() << " this scope \n";
            semant_errors++;
        }
        full_types_checker(assign->get_expr(), cls, table);
        return;
    }

    if (dynamic_cast<cond_class*>(expr_check) != nullptr) {
        auto cond = dynamic_cast<cond_class*>(expr_check);
        full_types_checker(cond->get_pred(), cls, table);
        full_types_checker(cond->get_then_expr(), cls, table);
        full_types_checker(cond->get_els_expr(), cls, table);
        return;
    }

    if (dynamic_cast<loop_class*>(expr_check) != nullptr) {
        auto loop = dynamic_cast<loop_class*>(expr_check);
        full_types_checker(loop->get_pred(), cls, table);
        full_types_checker(loop->get_body(), cls, table);
        return;
    }

    if (dynamic_cast<let_class*>(expr_check) != nullptr) {
        auto let_expr = dynamic_cast<let_class*>(expr_check);
        full_types_checker(let_expr->get_init(), cls, table);
        full_types_checker(let_expr->get_body(), cls, table);
        return;
    }

    if (auto binop = dynamic_cast<binary_op_class*>(expr_check)) {
        auto First = binop->get_first();
        auto Second = binop->get_second();
        check(First, Second, cls);
        return;
    }

    if (dynamic_cast<object_class*>(expr_check) != nullptr) {
        auto obj = dynamic_cast<object_class*>(expr_check);
        if (table.lookup_string(obj->get_name()->get_string()) == nullptr) {
            std::cerr << "Error: Object \"" << obj->get_name()->get_string()
                      << "\" not found at " << cls->get_filename()->get_string() << ':'
                      << cls->get_line_number() << " this scope \n";
            semant_errors++;
        }
        return;
    }

    if (dynamic_cast<isvoid_class*>(expr_check) != nullptr) {
        full_types_checker(dynamic_cast<isvoid_class*>(expr_check)->get_expr(), cls, table);
        return;
    }

    if (dynamic_cast<new__class*>(expr_check) != nullptr) {
        auto new_expr = dynamic_cast<new__class*>(expr_check);
        if (table.lookup_string(new_expr->get_name()->get_string()) == nullptr) {
            std::cerr << "Error: Could not find class \"" << new_expr->get_name()->get_string()
                      << "\" at this scope " << cls->get_filename()->get_string()
                      << ':' << cls->get_line_number() << "\n";
            semant_errors++;
        }
        return;
    }

    if (dynamic_cast<dispatch_class*>(expr_check) != nullptr || dynamic_cast<static_dispatch_class*>(expr_check) != nullptr) {
        auto disp = dynamic_cast<dispatch_class*>(expr_check);
        if (!disp) disp = dynamic_cast<static_dispatch_class*>(expr_check);
        if (!disp) return;

        if (table.lookup_string(disp->get_name()->get_string()) == nullptr) {
            std::cerr << "Error: Could not find class with method \"" << disp->get_name()->get_string()
                      << "\" at this scope " << cls->get_filename()->get_string()
                      << ':' << cls->get_line_number() << "\n";
            semant_errors++;
        }

        Expressions actuals = disp->get_expr_act();
        for (int i = 0; actuals->more(i); i = actuals->next(i)) {
            auto inner = dynamic_cast<Expression_class*>(actuals->nth(i));
            full_types_checker(inner, cls, table);
        }
        return;
    }
}

void semant() {
    bool have_main = false;
    auto program = static_cast<program_class*>(ast_root);
    Classes classes = program->get_programm_classes();

    for (int i = classes->first(); classes->more(i); i = classes->next(i)) {
        auto subject = dynamic_cast<class__class*>(classes->nth(i));
        Features n_features = subject->get_features();

        // Unique name check
        if (my_table.lookup_string(subject->get_name()->get_string())) {
            std::cerr << "Error: Class \"" << subject->get_name()->get_string()
                      << "\" is not a unique name for class at "
                      << subject->get_filename() << ":" << subject->get_line_number() << '\n';
            semant_errors++;
        }
        my_table.add_string(subject->get_name()->get_string());

        // Inheritance cycle check
        if (check_inheritance_cycle(subject, classes)) {
            std::cerr << "Error: Inheritance cycle detected in class \""
                      << subject->get_name()->get_string()
                      << "\" at " << subject->get_filename()->get_string()
                      << ':' << subject->get_line_number() << '\n';
            semant_errors++;
        }

        // Check for 'main' method presence
        for (int j = n_features->first(); n_features->more(j); j = n_features->next(j)) {
            auto feature = n_features->nth(j);
            if (auto method = dynamic_cast<method_class*>(feature)) {
                if (method->get_name()->equal_string("main", 4)) {
                    have_main = true;
                }
            }
        }

        // Type checking
        IdTable class_scope;
        for (int j = n_features->first(); n_features->more(j); j = n_features->next(j)) {
            auto feature = n_features->nth(j);
            if (auto attr = dynamic_cast<attr_class*>(feature)) {
                class_scope.add_string(attr->get_name()->get_string());
                full_types_checker(attr->get_init(), subject, class_scope);
            }
            if (auto method = dynamic_cast<method_class*>(feature)) {
                for (int k = method->get_formals()->first(); method->get_formals()->more(k); k = method->get_formals()->next(k)) {
                    auto formal = method->get_formals()->nth(k);
                    class_scope.add_string(formal->get_name()->get_string());
                }
                full_types_checker(method->get_expr(), subject, class_scope);
            }
        }
    }

    if (!have_main) {
        std::cerr << "Error: No class with 'main' method found.\n";
        semant_errors++;
    }

    if (semant_errors > 0) {
        std::cerr << "Compilation halted due to semantic errors.\n";
        exit(1);
    }
