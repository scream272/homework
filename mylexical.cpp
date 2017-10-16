#ifndef THOMPSON_H
#define THOMPSON_H

#include <iostream>
#include<stdio.h>
#include<stack>
#include<string>

using namespace std;
#define MAX  100

//节点，定义成结构体，以便于后面扩展
struct state{
        char StateName[MAX];
};
//边 空转换符用‘#’表示
struct edge{
        state StartState;
        state EndState;
        char TransSymbol;
};
//NFA单元
struct cell{
        edge EdgeSet[MAX];
        int EdgeCount;
        state StartState;
        state EndState;
};

//全局变量声明
int EDGE_NUM = 0;
int START_NUM = 0;
int CELL_NUM = 0;
//函数声明
void input(string&);
int check_legal(string);
int check_character(string);
int check_parentthesis(string);
int is_letter(char);
string add_join_symbol(string);
//中缀转后缀
string postfix(string);
//优先级 in stack priority
int isp(char);
//优先级 in coming priority
int scp(char);
cell express_to_NFA(string);
cell do_Unite(cell,cell);
cell do_Join(cell,cell);
cell do_Star(cell);
cell do_Cell(char);
//将一个单元的边的集合复制到另一个单元
void cell_EdgeSet_Copy(cell&,cell);
state new_StateNode();
void Display(cell);
#endif

#include "Thompson.h"
int main(){
        

        string Regular_Expression = "(a|b)*abb";
        cell NFA_Cell;
        
        input(Regular_Expression);
        
        Regular_Expression = add_join_symbol(Regular_Expression);
        Regular_Expression = postfix(Regular_Expression);
        NFA_Cell = express_to_NFA(Regular_Expression);
        Display(NFA_Cell);

        return 0;
}
cell express_to_NFA(string expression){
        int length = expression.size();
        char element;
        cell Cell,Left,Right;
        stack<cell> STACK;

        for(int i = 0; i < length; i++){
                element = expression.at(i);
                switch(element){
                        case '|':
                                Right = STACK.top();
                                STACK.pop();
                                Left = STACK.top();
                                STACK.pop();
                                Cell = do_Unite(Left, Right);
                                STACK.push(Cell);
                                break;

                        case '*':
                                Left = STACK.top();
                                STACK.pop();
                                Cell = do_Star(Left);
                                STACK.push(Cell);
                                break;

                        case '+':
                                Right =STACK.top();
                                STACK.pop();
                                Left = STACK.top();
                                STACK.pop();
                                Cell = do_Unite(Left, Right);
                                STACK.push(Cell);
                                break;
                        
                        default:
                                Cell = do_Cell(element);
                                STACK.push(Cell);
                }
        }
}

cell do_Unite(cell Left, cell Right){
        cell NewCell;
        NewCell.EdgeCount = 0;
        edge Edge1, Edge2, Edge3, Edge4;

        state StartState = new_StateNode();
        satae EndState = new_StateNode();

        Edge1.StartState = StartState;
        Edge1.EndState = Left.EdgeSet[0].StartState;
        Edge1.TransSymbol = '#';
        Edge2.StartState = StartState;
        Edge2.EndState = Right.EdgeSet[0].StartState;
        Edge2.TransSymbol = '#';
        Edge3.StartState = Left.EdgeSet[Left.EdgeCount - 1].StartState;
        Edge3.EndState = EndState;
        Edge3.TransSymbol = '#';
        Edge4.StartState = Right.EdgeSet[Right.EdgeCount - 1].StartState;
        Edge4.EndState = EndState;
        Edge4.TransSymbol = '#';

        cell_EdgeSet_Copy(NewCell, Left);
        cell_EdgeSet_Copy(NewCell, Right);

        NewCell.EdgeSet[NewCell.EdgeCount++] = Edge1;
        NewCell.EdgeSet[NewCell.EdgeCount++] = Edge2;
        NewCell.EdgeSet[NewCell.EdgeCount++] = Edge3;
        NewCell.EdgeSet[NewCell.EdgeCount++] = Edge4;

        NewCell.StartState = StartState;
        NewCell.EndState = EndState;
        return NewCell;
}
cell do_join(cell Left, cell Right){




}

string add_join_symbol(string add_string){
        int length = add_string.size();
        int return_string_length = 0;
        char *return_string = new char[2 * length];
        char first, second;
        for(int i = 0; i < length - 1; i++){
                first = add_string.at(i);
                second = add_string.at(i + 1);
        
        }

}
