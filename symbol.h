#ifndef HW3_OUTPUT_CPP_SYMBOL_H
#define HW3_OUTPUT_CPP_SYMBOL_H
#include <string>
#include <stack>
#include <vector>

using namespace std;



bool type_compatible(const string& right, const string& left);

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
                       vector<string> p = vector<string>()) :
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
    ~symbol_table_scope() = default;

    bool exists_in_scope(const symbol_table_entry& entry);
    void insert_to_scope(symbol_table_entry& entry);
    //symbol_table_entry* get_symbol_entry(const string& symbol_name); ///this is mainly to check main
    void print_scope(); //end scope, and calls helper function
    //symbol_table_entry* getSymbol()

    ///added
    bool symbol_declared_in_scope(const symbol_table_entry& entry);
    symbol_table_entry* get_variable_in_scope(const string& name);
};

///********************* TABLE STACK ********************************///
class table_stack {
public:
    vector<symbol_table_scope> tables_stack;
    stack<int> offsets_stack;

    table_stack();
    ~table_stack() = default;

    void open_scope(bool is_loop = false, string ret_type = ""); //open a new empty scope
    void close_scope();
    void final_check();
    void insert_symbol(const string& n, string t, bool func = false, bool override = false,
                       vector<string> p = vector<string>());
    void insert_func_args(vector<string> types, vector<string> names, string retType);
    bool symbol_exists(const symbol_table_entry& entry);    ///used only in insert

    ///added need to check if func: if paramters are the same
    bool symbol_declared(const symbol_table_entry& entry);  ///havent used yet
    symbol_table_entry* get_variable(const string& name);
    symbol_table_entry* get_function(const string& name, vector<string> params = {});
    bool checkLoop();

};





#endif //HW3_OUTPUT_CPP_SYMBOL_H
