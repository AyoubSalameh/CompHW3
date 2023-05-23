#ifndef HW3_OUTPUT_CPP_SYMBOL_H
#define HW3_OUTPUT_CPP_SYMBOL_H
#include <string>
#include <stack>
#include <vector>

using namespace std;


///********************* SYMBOL TABLE ENTRY ********************************///
class symbol_table_entry {
public:
    string name;
    string type;  //if func, this means the return type
    int offset;

    bool is_func = false;
    bool is_override = false;
    vector<string> params;

public:
    symbol_table_entry(const string& n, string t, int o, bool func = false, bool override = false,
                       vector<string>& p = vector<string>()) :
                       name(n), type(t), offset(o), is_func(func), is_override(override), params(p)
    {}
    ~symbol_table_entry() = default;
};


///********************* SYMBOL TABLE SCOPE ********************************///
class symbol_table_scope {
public:
    vector<symbol_table_entry> entries;
    bool is_loop;
    string func_ret_type;

    symbol_table_scope(bool loop, string ret): is_loop(loop), func_ret_type(ret) {}
    ~symbol_table_scope();      //add print scope in implementation

    bool exists(const symbol_table_entry& entry);
    void insert(symbol_table_entry& entry);
    symbol_table_entry* get_symbol_entry(const string& symbol_name); ///this is mainly to check main
    void print_scope(); //end scope, and calls helper function
    //symbol_table_entry* getSymbol()
};


///********************* TABLE STACK ********************************///
class table_stack {
public:
    vector<symbol_table_scope> tables_stack;
    stack<int> offsets_stack;

    table_stack(); //adding print and printi and global stack scope\scope 0
    ~table_stack() = default;

    void open_scope(bool is_loop = false, string ret_type = ""); //open a new empty scope upon
    void close_scope();
    void insert_symbol(const string& n, string t, bool func = false, bool override = false,
                       vector<string>& p = vector<string>());
    bool symbol_exists(const string& name);


};




#endif //HW3_OUTPUT_CPP_SYMBOL_H
