#ifndef TREE_HPP
#define TREE_HPP
#include <vector>
#include <iostream>
#include "types.hpp"
#include <functional>



//// N-Tree implementation
template<typename T>
struct Tree {
    T root;
    std::vector<Tree<T>> children;
    struct Tree<T> * next= nullptr;
    Tree() = delete;
    int FlagTemp=0;

    explicit Tree(const T &r) : root(r), children{} {}

    explicit Tree(T &&r) : root{std::forward<T>(r)}, children{} {}

    /** * Moves the provided subtree into this tree's children */
    inline void emplace(Tree<T> &&t) { children.emplace_back(std::forward(t)); }

    /** * Copies the provided subtree into this tree's children */
    void insert(const Tree<T> &t) {
        children.push_back(t);
    }

    void join(const Tree<T> *t) {
        children.push_back(*t);
    }

    template<typename F>
    void tree_accumulate(std::function<F(T &, const F &)> f, F start_val) {
        auto r = f(root, start_val);
        for (auto &c : children) c.tree_accumulate(f, r);
    }

    void Print(ASTNode &n){
        if(n.type==NodeType_t::All_Until){
            if(FlagTemp==0){
                printf("A");
                FlagTemp=1;
                PrintFormula();
            }
            else if(FlagTemp==1){
                children[0].midOrder();
                printf("U ");
                children[1].midOrder();
                FlagTemp=0;
            }
        }
        else if(n.type==NodeType_t::Exist_Until){
            if(FlagTemp==0){
                printf("E");
                FlagTemp=1;
                PrintFormula();
            }
            else if(FlagTemp==1){
                children[0].midOrder();
                printf("U ");
                children[1].midOrder();
                FlagTemp=0;
            }
        }
        else if(n.type==NodeType_t::Exist_Global){
            if(FlagTemp==0){
                printf("E");
                FlagTemp=1;
                PrintFormula();
            }
            else if(FlagTemp==1){
                printf("G");
                FlagTemp=2;
            }
            else{
                FlagTemp=0;
                children[0].midOrder();
            }
        }
        else if(n.type==NodeType_t::Exist_Next){
            if(FlagTemp==0){
                printf("E");
                FlagTemp=1;
                PrintFormula();
            }
            else if(FlagTemp==1){
                printf("X");
                FlagTemp=2;
            }
            else{
                FlagTemp=0;
                children[0].midOrder();
            }
        }
        else if(n.type==NodeType_t::Exist_Future){
            if(FlagTemp==0){
                printf("E");
                FlagTemp=1;
                PrintFormula();
            }
            else if(FlagTemp==1){
                printf("F");
                FlagTemp=2;
            }
            else{
                FlagTemp=0;
                children[0].midOrder();
            }
        }
        else if(n.type==NodeType_t::All_Global){
            if(FlagTemp==0){
                printf("A");
                FlagTemp=1;
                PrintFormula();
            }
            else if(FlagTemp==1){
                printf("G");
                FlagTemp=2;
            }
            else{
                FlagTemp=0;
                children[0].midOrder();
            }
        }
        else if(n.type==NodeType_t::All_Next){
            if(FlagTemp==0){
                printf("A");
                FlagTemp=1;
                PrintFormula();
            }
            else if(FlagTemp==1){
                printf("X");
                FlagTemp=2;
            }
            else{
                FlagTemp=0;
                children[0].midOrder();
            }
        }
        else if(n.type==NodeType_t::All_Future){
            if(FlagTemp==0){
                printf("A");
                FlagTemp=1;
                PrintFormula();
            }
            else if(FlagTemp==1){
                printf("F");
                FlagTemp=2;
            }
            else{
                FlagTemp=0;
                children[0].midOrder();
            }
        }
    }
    void PrintFormula(){PrintFormulaWays(root);}
    void PrintFormulaWays(ASTNode &n) {
            if (children.size() == 2) {
                if(n.type!=NodeType_t::Implies&&n.type!=NodeType_t::LogicAnd&&n.type!=NodeType_t::LogicOr){
                    printf("(");
                    Print(n);
                    printf(")");
                } else{
                    children[0].midOrder();
                    std::cout<<n.token<<" ";
                    children[1].midOrder();
                }
            }
            else if(children.size() == 1){
                if(n.type==NodeType_t::Not){
                    std::cout<<"~";
                    children[0].midOrder();
                } else{
                    printf("(");
                    Print(root);
                    children[0].midOrder();
                    printf(")");
                }

            }
            else{
                std::cout<<n.token<<" ";
            }
    }

    void midOrder() {
        if (children.size() <= 1) {
            PrintFormulaWays(root);
            for (auto &c : children) c.midOrder();
        }
        else if(children.size() == 2){
            PrintFormulaWays(root);
        }
    }
        void tree_apply_xianxu(std::function<void(T &)> f) {
            f(root);
            for (auto &c : children) c.tree_apply_xianxu(f);
        }

        void tree_apply_reverse(std::function<void(T &)> f) {
            for (auto &c : children) c.tree_apply(f);
            f(root);
        }
        void tree_apply(std::function<void(const T &)> f) const {
            f(*this);
            for (auto &c : children) c.tree_apply(f);
        }
        void tree_apply(std::function<void(const Tree<T> &)> f) const {
            f(*this);
            for (auto &c : children) c.tree_apply(f);
        }
        void tree_apply(std::function<void(Tree<T> &)> f) {
            f(*this);
            for (auto &c : children) { c.tree_apply(f); }
        }
    bool isDisjunction(){ if (root.type==NodeType_t::LogicOr&&isLiteral(children[1].root.type)&&isLiteral(children[0].root.type)||isLiteral(root.type))return true; else return false;}
};
    template<typename T>
    void apply_tree_func_on_non_tree(T *orig, std::function<T *(T *)> getnext, std::function<void(T *)> f) {
        T *n = getnext(orig);
        if (n) apply_tree_func_on_non_tree(n, getnext, f);
        f(orig);
    }
#endif //TREE_HPP

