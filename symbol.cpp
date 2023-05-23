#include "symbol.h"
#include "hw3_output.hpp"

extern table_stack table;


///********************* SYMBOL TABLE SCOPE ********************************///
bool symbol_table_scope::exists(const symbol_table_entry& entry) {
    for(auto it = entries.begin(); it != entries.end(); it++) {
        if(it->name == entry.name) {
            if(it->is_override == false || entry.is_override == false) {
                return true ///meaning we cant add another
            }
        }
    }
    return false;
}


void symbol_table_scope::insert(symbol_table_entry &entry) {
    bool answer = this->exists(entry);
    if(answer == true);


    if(!this-)
}