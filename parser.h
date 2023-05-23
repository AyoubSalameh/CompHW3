#ifndef HW3_OUTPUT_CPP_PARSER_H
#define HW3_OUTPUT_CPP_PARSER_H
#include <string>
#include <vector>

class Node {
public:
    std::string name;

    Node(const std::string s= ""): name(s) {}
    Node(const Node* node) : name(node.name) {}
    virtual ~Node()
};

class Type : public Node {
public:
    std::string type;
    Type(std::string t) : type(t) {}
};

class Exp: public Node {
public:
    std::string type;
    //bool is_var;

    Exp(Exp* e) : type(e->type), Node(e) {};
};

class ExpList : public Node {
public:
    std::vector<Exp*> expressions;
};

class Call : public Node {
public:
    std::string type;

};

class Statement : public Node {
public:

};

class Statements : public Node {
public:

};

class Program : public Node{
    /*
public:
    Program() {}
    ~Program() = default
     */
};

class Funcs : public Node{
    /*
public:
    Funcs() {}
    ~Funcs() = default
     */
};

class OverRide: public Node{
public:
    bool isOverRide;
    OverRide(bool answer = false): isOverRide(answer) {}
};

class RetType : public Node{
public:
    std::string type;
    RetType(std::string t) : type(t) {}
};

class FormalDecl : public Node{
public:
    std::string type;
    FormalDecl(Type* t, Node* node) : type(t->type), Node(node) {}
};

class FormalsList : public Node{
    std::vector<FormalDecl> param_list;
    FormalsList(FormalDecl* dec, FormalsList* list);
    FormalsList(FormalDecl* dec);
};

class Formals: public Node{
    std::vector<FormalDecl> param_list;
    Formals(FormalsList* fl) : param_list(fl->param_list) {}
    Formals() {}
F
};

class FuncDecl : public Node {
public:
    FuncDecl(OverRide* override, RetType* rt, Node* id, Formals* params);//TODO
};


#define YYSTYPE Node*



#endif //HW3_OUTPUT_CPP_PARSER_H
