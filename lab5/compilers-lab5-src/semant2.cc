#include "utilities.h"
#include "cool-parse.h"

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

void check(Expression First, Expression Second, class__class* cls) 
{
    auto f_type = First;
    if (dynamic_cast<int_const_class*>(First) != nullptr) {
        f_type = dynamic_cast<int_const_class*>(First);
        if (dynamic_cast<int_const_class*>(Second) == nullptr) {
            std::cerr << "Error: Invalid type conversion at class \"" << cls->get_name()->get_string()
                      << "\" at file " << cls->get_filename()->get_string() << ':' << cls->get_line_number() << '\n';
        semant_errors++;
        }

    }
    if (dynamic_cast<string_const_class*>(First) != nullptr) {
        f_type = dynamic_cast<string_const_class*>(First);
        if (dynamic_cast<string_const_class*>(Second) == nullptr) {
            std::cerr << "Error: Invalid type conversion at class \"" << cls->get_name()->get_string()
                      << "\" at file " << cls->get_filename()->get_string() << ':' << cls->get_line_number() << '\n';
            semant_errors++;
        }

    }
    if (dynamic_cast<bool_const_class*>(First) != nullptr) {
        f_type = dynamic_cast<bool_const_class*>(First);
        if (dynamic_cast<bool_const_class*>(Second) == nullptr) {
        std::cerr << "Error: Invalid type conversion at class \"" << cls->get_name()->get_string()
                  << "\" at file " << cls->get_filename()->get_string() << ':' << cls->get_line_number() << '\n';
            semant_errors++;
        }

    }
}

void full_types_checker(Expression expr_check, class__class* cls, IdTable table) 
{
    if (dynamic_cast<no_expr_class*>(expr_check) != nullptr)
        return;
    if (dynamic_cast<assign_class*>(expr_check) != nullptr)
    {
        auto assing_class_test = dynamic_cast<assign_class*>(expr_check);
        if (table.lookup_string(assing_class_test->get_name()->get_string()) == nullptr) 
        {
            std::cerr << "Error: Variable \"" << assing_class_test->get_name()->get_string() 
                      << "\" was not declared at " << cls->get_filename()->get_string() << ':' 
                      << cls->get_line_number() << " this scope \n";
            semant_errors++;
        }
        full_types_checker(assing_class_test->get_expr(), cls, table);
        return;
    }
    if (dynamic_cast<cond_class*>(expr_check) != nullptr)
    {
        auto cond_expr_test = dynamic_cast<cond_class*>(expr_check);
        full_types_checker(cond_expr_test->get_pred(), cls, table);
        full_types_checker(cond_expr_test->get_then_expr(), cls, table);
        full_types_checker(cond_expr_test->get_els_expr(), cls, table);
        return;
    }
    if (dynamic_cast<loop_class*>(expr_check) != nullptr)
    {
        auto loop_expr_test = dynamic_cast<loop_class*>(expr_check);
        full_types_checker(loop_expr_test->get_pred(), cls, table);
        full_types_checker(loop_expr_test->get_body(), cls, table);
        return;
    }
    if (dynamic_cast<let_class*>(expr_check) != nullptr)
    {
        auto let_expr_test = dynamic_cast<let_class*>(expr_check);
        full_types_checker(let_expr_test->get_init(), cls, table);
        full_types_checker(let_expr_test->get_body(), cls, table);
        return;
    }
    if (dynamic_cast<plus_class*>(expr_check) != nullptr)
    {
        auto for_expr_test = dynamic_cast<plus_class*>(expr_check);
        auto First = for_expr_test->get_first();
        auto Second = for_expr_test->get_second();
        check(First, Second, cls);
        return;
    }
    if(dynamic_cast<sub_class*>(expr_check) != nullptr)
    {
        auto for_expr_test = dynamic_cast<sub_class*>(expr_check);
        auto First = for_expr_test->get_first();
        auto Second = for_expr_test->get_second();
        check(First, Second, cls);
        return;
    }
    if (dynamic_cast<mul_class*>(expr_check) != nullptr)
    {                    
        auto for_expr_test = dynamic_cast<mul_class*>(expr_check);
        auto First = for_expr_test->get_first();
        auto Second = for_expr_test->get_second();
        check(First, Second, cls);
        return;
    }
    if (dynamic_cast<divide_class*>(expr_check) != nullptr)
    {
        auto for_expr_test = dynamic_cast<divide_class*>(expr_check);
        auto First = for_expr_test->get_first();
        auto Second = for_expr_test->get_second();
        check(First, Second, cls);
        return;
    }
    if (dynamic_cast<lt_class*>(expr_check) != nullptr)
    {
        auto for_expr_test = dynamic_cast<lt_class*>(expr_check);
        auto First = for_expr_test->get_first();
        auto Second = for_expr_test->get_second();
        check(First, Second, cls);
        return;
    }
    if (dynamic_cast<eq_class*>(expr_check) != nullptr)
    {
        auto for_expr_test = dynamic_cast<eq_class*>(expr_check);
        auto First = for_expr_test->get_first();
        auto Second = for_expr_test->get_second();
        check(First, Second, cls);
        return;
    }
    if (dynamic_cast<leq_class*>(expr_check) != nullptr)
    {
        auto for_expr_test = dynamic_cast<leq_class*>(expr_check);
        auto First = for_expr_test->get_first();
        auto Second = for_expr_test->get_second();
        check(First, Second, cls);
        return;
    }
    if (dynamic_cast<object_class*>(expr_check) != nullptr) {
        auto obj_class_test = dynamic_cast<object_class*>(expr_check);
        if (table.lookup_string(obj_class_test->get_name()->get_string()) == nullptr) {
            std::cerr << "Error: Object \"" << obj_class_test->get_name()->get_string() 
            << "\" not found at" << cls->get_filename()->get_string() << ':'
            << cls->get_line_number() <<  "this scope \n";
            semant_errors++;
            return;
        }
    }
    if (dynamic_cast<isvoid_class*>(expr_check) != nullptr) {
        full_types_checker((dynamic_cast<isvoid_class*>(expr_check))->get_expr(), cls, table);
        return;
    }
    if (dynamic_cast<new__class*>(expr_check) != nullptr) {
        if (table.lookup_string((dynamic_cast<new__class*>(expr_check))->get_name()->get_string()) == nullptr)
        {
            std::cerr << "Error: Could not find class \"" << 
            (dynamic_cast<new__class*>(expr_check))->get_name()->get_string() << "\" at this scope " 
            << cls->get_filename()->get_string() << ':' << cls->get_line_number() <<  "\n";
            semant_errors++;
        }
        return;
    }
    if (dynamic_cast<dispatch_class*>(expr_check) != nullptr) {
            if ((dynamic_cast<int_const_class*>(dynamic_cast<dispatch_class*>(expr_check)->get_expr()) != 0) ||
            (dynamic_cast<string_const_class*>(dynamic_cast<dispatch_class*>(expr_check)->get_expr()) != 0) ||
            (dynamic_cast<bool_const_class*>(dynamic_cast<dispatch_class*>(expr_check)->get_expr()) != 0)) {
            std::cerr << "Error: Standart classes has no methods \"" <<
            (dynamic_cast<dispatch_class*>(expr_check))->get_name()->get_string() << "\" at this scope " 
            << cls->get_filename()->get_string() << ':' << cls->get_line_number() <<  "\n";
            semant_errors++;
            return;
            }
        if (table.lookup_string((dynamic_cast<dispatch_class*>(expr_check))->get_name()->get_string()) == nullptr)
        {
            std::cerr << "Error: Could not find class with method \"" << 
            (dynamic_cast<dispatch_class*>(expr_check))->get_name()->get_string() << "\" at this scope " 
            << cls->get_filename()->get_string() << ':' << cls->get_line_number() <<  "\n";
            semant_errors++;
        }
        for (int i = 0; (dynamic_cast<dispatch_class*>(expr_check))->get_expr_act()->more(i); i++)
        {
            auto disp_expr_check = (dynamic_cast<dispatch_class*>(expr_check))->get_expr_act();
            for (int j = 0; disp_expr_check->more(j); j++)
            {
                auto inner_disp_expr_check = dynamic_cast<Expression_class*>(disp_expr_check->nth(j));
                full_types_checker(inner_disp_expr_check, cls, table);
            }
        }
        return;
    }
    if (dynamic_cast<static_dispatch_class*>(expr_check) != nullptr) {
        if ((dynamic_cast<int_const_class*>(dynamic_cast<static_dispatch_class*>(expr_check)->get_expr()) != 0) ||
            (dynamic_cast<string_const_class*>(dynamic_cast<static_dispatch_class*>(expr_check)->get_expr()) != 0) ||
            (dynamic_cast<bool_const_class*>(dynamic_cast<static_dispatch_class*>(expr_check)->get_expr()) != 0)) {
            std::cerr << "Error: Standart classes has no methods \"" <<
            (dynamic_cast<static_dispatch_class*>(expr_check))->get_name()->get_string() << "\" at this scope " 
            << cls->get_filename()->get_string() << ':' << cls->get_line_number() <<  "\n";
            semant_errors++;
            return;
            }
        if (table.lookup_string((dynamic_cast<static_dispatch_class*>(expr_check))->get_name()->get_string()) == nullptr)
        {
            std::cerr << "Error: Could not find class with method \"" << 
            (dynamic_cast<static_dispatch_class*>(expr_check))->get_name()->get_string() << "\" at this scope " 
            << cls->get_filename()->get_string() << ':' << cls->get_line_number() <<  "\n";
            semant_errors++;
        }
        for (int i = 0; (dynamic_cast<static_dispatch_class*>(expr_check))->get_expr_act()->more(i); i++)
        {
            auto disp_expr_check = (dynamic_cast<static_dispatch_class*>(expr_check))->get_expr_act();
            for (int j = 0; disp_expr_check->more(j); j++)
            {
                auto inner_disp_expr_check = dynamic_cast<Expression_class*>(disp_expr_check->nth(j));
                full_types_checker(inner_disp_expr_check, cls, table);
            }
        }
        return;
    }
}

void semant() {
    bool have_main = false;
    auto cand = static_cast<program_class*>(ast_root);
    auto test = cand->get_programm_classes();
    auto classes = dynamic_cast<class__class*>(cand->get_programm_classes());
    int cls_size = 0;
    for(int i = test->first(); test->more(i); i = test->next(i)){
        auto subject = dynamic_cast<class__class*>(test->nth(i));
        Features n_features = subject->get_features();
        // Unique ID check
        if (my_table.lookup_string(subject->get_name()->get_string())) {
            std::cerr << "Error: Class \"" << subject->get_name()->get_string() <<
                         "\" is not a unique name for class at " << 
                         subject->get_filename() << ":" << subject->get_line_number() << '\n';
                         semant_errors++;
        }
        my_table.add_string(subject->get_name()->get_string());
        // parents check
        if (!subject->get_parent()->equal_string("Object", 6)) {
            auto parent_check = subject->get_parent();
            IdTable inner_table;
            bool cycles_tested;
            for (int j = i; j >= 0; j--) {
                auto test_class = dynamic_cast<class__class*>(test->nth(j));
                if (test_class->get_name()->equal_string(subject->get_name()->get_string(), subject->get_name()->get_len())) {
                    std::cerr << "Error: No cycle inherits allowed at class \"" << subject->get_name()->get_string() << "\" at " <<
                                  subject->get_filename() << ":" << subject->get_line_number() << '\n';
                    semant_errors++;                    
                    break;
                }
                if (test_class->get_name()->equal_string(parent_check->get_string(), parent_check->get_len())) {
                    if (!test_class->get_parent()->equal_string("Object", 6)) {
                        parent_check = test_class->get_parent();
                    }
                    else {
                        cycles_tested = true;
                    }
                }
                if (j == 0 && !cycles_tested) {
                    std::cerr << "Error: Could not find parents classes to \"" << subject->get_parent()->get_string() << "\" at " <<
                                  subject->get_filename() << ":" << subject->get_line_number() << '\n';
                    semant_errors++;
                    break;
                }
            }
        }
        for (int f = n_features->first(); n_features->more(f); f = n_features->next(f))
        {   
            //methods and attributes check
            auto type_check = dynamic_cast<method_class*>(n_features->nth(f));
            if (type_check != nullptr) {
                auto feature_on_check = dynamic_cast<method_class*>(n_features->nth(f));
                auto test_feature = feature_on_check->get_name();
                if (test_feature->equal_string("main", 4))
                    have_main = true;
                if (my_table.lookup_string(test_feature->get_string()) != nullptr)
                {
                    std::cerr << "Error: Not unique feature name " << '\"' << test_feature->get_string() << '\"' <<
                                " at " << subject->get_filename() << ":" << subject->get_line_number() << '\n';
                    semant_errors++;
                }
                auto expr_check = feature_on_check->get_expr();
                my_table.add_string(test_feature->get_string());
                full_types_checker(expr_check, subject, my_table);
                // method formals type check
                if (feature_on_check->get_formals() != nullptr)
                {
                    auto formals_check = dynamic_cast<Formals>(feature_on_check->get_formals());
                    for (int fc = formals_check->first(); formals_check->more(fc); fc = formals_check->next(fc))
                    {
                        auto inner_formal = dynamic_cast<formal_class*>(formals_check->nth(fc));
                        if (my_table.lookup_string(inner_formal->get_name()->get_string()) != nullptr) 
                        {
                            Symbol parent_check = subject->get_parent();
                            for (int for_feat = 0; n_features->more(for_feat); for_feat++) {
                                if (dynamic_cast<attr_class*>(n_features->nth(for_feat)) != nullptr) {
                                    auto feat_on_check = dynamic_cast<attr_class*>(n_features->nth(for_feat));
                                    if (feat_on_check->get_name()->equal_string(inner_formal->get_name()->get_string(), inner_formal->get_name()->get_len())) 
                                    {
                                        if (!feat_on_check->get_type()->equal_string(inner_formal->get_type()->get_string(), inner_formal->get_type()->get_len())) {
                                            std::cerr << "Error: Foraml attribute have another type in \"" << subject->get_name()->get_string() << "\" at " 
                                            << subject->get_filename()->get_string() << ':' << subject->get_line_number() << '\n';
                                            semant_errors++;
                                        }
                                    }
                                }
                            }
                            for (;!parent_check->equal_string("Object", 6);) {
                                class__class* prnt;
                                for (int par_check = i; par_check >= 0; par_check--) {
                                    prnt = dynamic_cast<class__class*>(test->nth(par_check));
                                    if (prnt->get_name()->equal_string(parent_check->get_string(), parent_check->get_len())) {
                                        break;
                                    }
                                }
                                auto cls_fthrs = dynamic_cast<Features>(prnt->get_features());
                                for (int cls_fthrs_tst = 0; cls_fthrs->more(cls_fthrs_tst);cls_fthrs_tst++) {
                                    if (dynamic_cast<attr_class*>(n_features->nth(cls_fthrs_tst)) != nullptr) {
                                    auto feat_on_check = dynamic_cast<attr_class*>(n_features->nth(cls_fthrs_tst));
                                    if (feat_on_check->get_name()->equal_string(inner_formal->get_name()->get_string(), inner_formal->get_name()->get_len())) 
                                    {
                                        if (!feat_on_check->get_type()->equal_string(inner_formal->get_type()->get_string(), inner_formal->get_type()->get_len())) {
                                            std::cerr << "Error: Foraml attribute have another type in \"" << subject->get_name()->get_string() << "\" at " 
                                            << subject->get_filename()->get_string() << ':' << subject->get_line_number() << '\n';
                                            semant_errors++;
                                        }
                                    }
                                }
                                }
                                parent_check = prnt->get_parent();
                            }
                        }
                    }
                }
            }
            else
            {
                // attributes check
                auto n_attr = dynamic_cast<attr_class*>(n_features->nth(f));
                auto test_attr = n_attr->get_name();
                my_table.lookup_string(subject->get_parent()->get_string());
                for (int inner_check = my_table.get_index() - 1; inner_check > 0 && !my_table.lookup(inner_check)->equal_string(subject->get_name()->get_string(), subject->get_name()->get_len());inner_check--) {
                    if (my_table.lookup(inner_check)->equal_string(test_attr->get_string(), test_attr->get_len())) {
                        std::cerr << "Error: Variable \"" << test_attr->get_string() << "\" was declared in this class before at" 
                                  << subject->get_filename()->get_string() << ':' << subject->get_line_number() << '\n';
                        semant_errors++;
                    }
                }
                if (!subject->get_parent()->equal_string("Object", 6)) {
                    Symbol parent_is = subject->get_parent();
                    for (;!parent_is->equal_string("Object", 6);) {
                        bool was_found = false;
                        int attr_test = 0;
                        for(;!dynamic_cast<class__class*>(test->nth(attr_test))->get_name()->equal_string(parent_is->get_string(), parent_is->get_len())
                             && test->more(attr_test); attr_test++) { }
                        if (!test->more(attr_test)) {
                        std::cerr << "Error: No class with variale \"" << test_attr->get_string() << "\" exist at " 
                                  << subject->get_filename()->get_string() << ':' << subject->get_line_number() << '\n';
                        semant_errors++;
                        was_found = true;
                        }
                        else {
                            auto attribute_find = dynamic_cast<class__class*>(test->nth(attr_test))->get_features();
                            for (int check = 0; attribute_find->more(check); check++) {
                                if (dynamic_cast<attr_class*>(attribute_find->nth(check)) != nullptr)
                                    if (dynamic_cast<attr_class*>(attribute_find->nth(check))->get_name()->equal_string(test_attr->get_string(), test_attr->get_len())) {
                                    std::cerr << "Error: Variable \"" << test_attr->get_string() << "\" has redefenition in derived class at " 
                                              << subject->get_filename()->get_string() << ':' << subject->get_line_number() << '\n';
                                              semant_errors++;
                                    was_found = true;
                                    break;
                                }
                            }
                            if (was_found)
                                break;
                            else 
                                parent_is = dynamic_cast<class__class*>(test->nth(attr_test))->get_parent();
                        }
                    }
                }
                my_table.add_string(test_attr->get_string());
            }
        }
    }
    if (!have_main) {
        std::cerr << "Error: Could not find \"main\" method in any class\n";
        semant_errors++;
    }
}