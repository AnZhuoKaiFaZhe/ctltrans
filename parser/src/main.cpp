#include <iostream>
#include <types.hpp>
#include <vector>
#include <Tree.hpp>
#include <fstream>

extern Tree<ASTNode>* ParseQuery(const std::string&);
extern void SetVerbosity(unsigned int lvl);

int Check(std::string readline)
{
    for(int n=0;n<readline.length();n++)
    {
        if(readline[n]!=9&&readline[n]!=32&&readline[n]!=13)
        {
            return 1;
        }
    }
    return 0;
}
int main(int argc,char** argv) {
    SetVerbosity(2); // 0 = NONE, 1 = ERRORS_ONLY, 2 = ALL

    //读取文件
    std::ifstream in(argv[1]);
    std::string formula;
    if(!in.is_open()){
        std::cout<<"can not open file"<<"\n";
        return 0;
    }
    while (!in.eof()) {
        getline(in, formula);
        if (Check(formula)) {
            auto *q = ParseQuery(formula);
            q->PrintFormula();
            formula = "";
            printf("\n");
            delete q;
        }
    }
    return 0;
}
