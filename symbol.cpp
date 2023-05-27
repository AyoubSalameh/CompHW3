#include "symbol.h"
#include "hw3_output.hpp"

extern table_stack table;
extern int yylineno;


///HELPER
static bool are_vectors_equal(vector<string>& a, vector<string>& b) {
    if(a.size() != b.size()) {
        return false;
    }
    for(int i = 0; i < a.size(); i++) {
        if(a[i] != b[i]) {
            return false;
        }
    }
    return true;
}

///********************* SYMBOL TABLE SCOPE ********************************///

///upon inserting, check if exists, if yes, exit program
bool symbol_table_scope::exists_in_scope(const symbol_table_entry& entry) {
    for(auto it = entries.begin(); it != entries.end(); it++) {
        if(it->name == entry.name) {
            if(it->is_func == false || entry.is_func == false) {
                output::errorDef(yylineno, entry.name); ///be careful
                exit(0);
            }
            //if we reach this, both are funcs
            if(it->is_override == false) {
                output::errorFuncNoOverride(yylineno, it->name);
                exit(0);
            }
            if(entry.is_override == false) {
                output::errorOverrideWithoutDeclaration(yylineno, it->name);
                exit(0);
            }
            //if we reach this, we know that both are override
            if(are_vectors_equal(it->params, entry.params)) {
                output::errorDef(yylineno, entry.name); ///be careful
                exit(0);
            }
        }
    }
    return false;
}

///called from insert to table stack, and called after checking exists_in_scope to all scopes
void symbol_table_scope::insert_to_scope(symbol_table_entry &entry) {
    entries.push_back(entry);
}


void symbol_table_scope::print_scope() {
    for(auto& entry : this->entries){
        if(entry.is_func) {
            output::printID(entry.name, 0, output::makeFunctionType(entry.type, entry.params))
        }
        else {
            output::printID(entry.name, entry.offset, entry.type);
        }
    }
}



///********************* TABLE STACK ********************************///
bool table_stack::symbol_exists(const symbol_table_entry& entry) {
    for(auto it = tables_stack.begin(); it != tables_stack.end(); it++) {
        it->exists_in_scope(entry);
    }
    return true;
}

void table_stack::insert_symbol(const string &n, string t, bool func, bool override, vector <string> &p) {
    //insert to table_stack
    int insert_offset = func ? 0 : offsets_stack.top();
    symbol_table_entry entry(n, t, insert_offset, func, override, p);

    this->symbol_exists(entry);

    //if we got here, the insertion is legal
    tables_stack.back().insert_to_scope(entry);

    if(!func){
        offsets_stack.pop();
        offsets_stack.push(insert_offset+1);
    }

}

void table_stack::open_scope(bool is_loop, string ret_type) {
    symbol_table_scope new_scope(is_loop, ret_type);
    tables_stack.push_back(new_scope);
    offsets_stack.push(offsets_stack.top());
}

void table_stack::close_scope() {
    output::endScope();
    symbol_table_scope to_close = tables_stack.back();
    to_close.print_scope();
    tables_stack.pop_back();
    offsets_stack.pop();
}