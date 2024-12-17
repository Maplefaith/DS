#ifndef _EXPRESSION_EVALUATOR__H_
#define _EXPRESSION_EVALUATOR__H_
#include <iostream>
#include <stack>
#include <string>
#include <vector>
#include <cctype>
#include <stdexcept>
#include <sstream>

enum OperatorType { NONE = 0, ADD_SUB = 1, MUL_DIV = 2 };

class Layer
{
private:
    std::string operand;
    int isOperator;
    double number;

public:
    Layer(std::string _operand, int _isOperator):operand{_operand}, isOperator(_isOperator){
        if(this->isOperator == -1)number = std::stod(operand);
        else {this->isOperator = isValidOperator();}
    }
    int isValidOperator() const {
        if (operand == "+" || operand == "-") {
            return ADD_SUB;
        } else if (operand == "*" || operand == "/") {
            return MUL_DIV;
        }
        return NONE;
    }

    int getisOperator() const{
        return isOperator;
    }
    double getnumber() const{
        return number;
    }
    std::string getoperand()const{
        return operand;
    }
    ~Layer(){}
};


class Calculator
{
private:
    std::string input;
    std::vector<std::string> infix;
    std::vector<Layer> postfix;
    std::stack<Layer> stack;
    bool isValid;
    double out;
public:
    // 构造函数，内部调用partitionString()
    Calculator(std::string input): input(input), isValid(true) {
        if (!partitionString() || !infixToPostfix()) {isValid = false;}
    }
    // 判断是否是合理的科学计数法
    bool isvalidE(size_t &i)const
    {
        if(std::isdigit(input[i-1]) && (std::isdigit(input[i+1]) || (input[i+1]=='-' || input[i+1]=='+')))return true;
        return false;
    }
    // 判断负号
    bool isvalidminus()const
    {
        if(infix.empty() || infix.back()=="+" || infix.back()=="-" || infix.back()=="*"|| infix.back()=="/" || infix.back()=="(")return true;
        return false;
    }
    // 判断科学计数法里的符号
    bool isoperatorinE(char &ch) const{
        if(ch=='+' || ch=='-')return true;
        return false;
    }
    bool isoperator(char &op)const {
        if(op == '+' || op == '-' || op == '*' || op == '/' || op=='(' || op==')')return true;
        return false;
    }
    bool getisValid(){
        return isValid;
    }
    // 获取out的值
    double getresult(){
        return out;
    }
    // 拆解输入字符串input（负号拆分为"-1" "*"处理），有序存入infix；若拆解时得到不合规操作符，或出现不合理的科学计数法，就返回false；
    bool partitionString() {
        std::string number;
        bool hasminus = false; // 标识当前number中是否已经包含e或E
        bool hasE = false; // 标识当前number中是否已经包含-号

        char ch = input[0];
        for (size_t i = 0; i < input.size(); ++i) {
            ch = input[i];
            if (std::isspace(ch)) {
                continue; // 跳过空格
            }
            if (std::isdigit(ch) || ch == '.') { // 数字或小数点直接加入number字符串
                number += ch;
            } else if (ch == 'e' || ch == 'E') { // 科学计数法中的 e 或 E 前后必须跟合法数字，且不能重用e
                if (hasE || !isvalidE(i))return false;
                hasE = true;
                number += 'e'; // 加入 e 或 E 及其之后合法元素
                ++i;
                do{
                    number += input[i++];
                }
                while(std::isdigit(input[i]));
                if(input[i] == '.' || isoperatorinE(number.back()))return false; // e后出现小数点 '.' 或者 单个 '+' '-'
                i -= 1;
            } else if (isoperator(ch)) { // 合法运算符
                if(!hasminus && ch == '-' && number.empty() && (isvalidminus())) { // "-" 作为负号的转化
                    std::string mark="";
                    if(!infix.empty()) mark= infix.back();
                    infix.push_back("-1");
                    if(mark=="/")infix.push_back("/");
                    else infix.push_back("*");
                    hasminus=true;
                    // number+=ch;
                } else {
                    if(!number.empty()){
                        infix.push_back(number);
                        hasE = false;
                        number.clear();
                    }
                    hasminus = false;
                    infix.push_back(std::string(1, ch)); // 操作符加入中缀表达式
                    } 
            } else {
                return false; // 其他非法字符
            }
        }

        if (!number.empty()) infix.push_back(number);
        return true;
    }

    // 中缀表达式转换为后缀表达式，若出现括号不匹配，则返回false
    bool infixToPostfix() {
        std::stack<Layer> operators;

        for (const auto& token : infix) {
            if (std::isdigit(token[0]) || (token.size() > 1 && token[0]=='-')) {
                postfix.push_back(Layer(token, -1));  // 操作数直接加入后缀表达式
            } else if (token == "(") {
                operators.push(Layer(token, 0));     // 左括号压栈
            } else if (token == ")") {
                // 遇到右括号，弹出直到左括号
                while (!operators.empty() && operators.top().getoperand() != "(") {
                    postfix.push_back(operators.top());
                    operators.pop();
                }
                if (operators.empty()) return false;  // 括号不匹配
                operators.pop();  // 弹出左括号
            } else {
                // 遇到运算符
                Layer temp = Layer(token, 0);
                while (!operators.empty() && operators.top().getisOperator() >= temp.getisOperator()) {
                    postfix.push_back(operators.top());
                    operators.pop();
                }
                operators.push(temp);
            }
        }

        // 将剩余运算符压入后缀表达式
        while (!operators.empty()) {
            if (operators.top().getoperand() == "(") return false;  // 括号不匹配
            postfix.push_back(operators.top());
            operators.pop();
        }

        return true;
    }
    
    // 将拆解完的字符串postfix中的每一个元素（按照操作数operand和操作符operator的标签）按照顺序压入堆栈stack，按照通用的规则和优先级启动压出，并计算表达式；
    // 若被除数为0，返回false
    bool calculate() {
        for (const auto& token : postfix) {
            if (token.getisOperator()==-1) {
                // 将操作数压入stack
                stack.push(token);
            } else {
                // 从stack中弹出两个操作数
                if(stack.size()<2) return false;
                Layer right = stack.top(); stack.pop();
                Layer left = stack.top(); stack.pop();

                if(right.getisOperator()!=-1 || left.getisOperator()!=-1)return false;

                double result = 0.0;
                if (token.getoperand() == "+") result = left.getnumber() + right.getnumber();
                else if (token.getoperand() == "-") result = left.getnumber() - right.getnumber();
                else if (token.getoperand() == "*") result = left.getnumber() * right.getnumber();
                else {
                    if (right.getnumber() == 0) return false;  // 检查除数是否为0
                    result = left.getnumber() / right.getnumber();
                }
                // 将结果作为新的操作数压回栈
                stack.push(Layer(std::to_string(result), -1));
            }
        }
        if (stack.size() != 1 || stack.top().getisOperator()!=-1) return false;
        out = stack.top().getnumber();
        return true;
    }
    
};

#endif