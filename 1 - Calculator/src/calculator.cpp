#include <iostream>
#include "random.h"
#include "cmath"
#include "stack.h"
#include <console.h>

using namespace std;

//in this vector i will save polish record of formula
Vector<string> result;

// rate of operators
int rateOfOperands(const char ch)
{
    switch(ch){
    case '^': return 3;
    case '*':
    case '/': return 2;
    case '+':
    case '-': return 1;
    }
    //in case of scope
    return 0;
}


//checking whether the number
bool isNumber(char ch)
{
    return (('0' <= ch) && (ch <= '9')) || (ch == '.');
}
//checking whether the operator
bool isOperator(char ch)
{
    return (ch == '+' || ch == '-' || ch == '/' || ch == '*' || ch == '^');
}

//writes a Polish record
void PolishRecord(string formula){
    Stack<char> operators;
    string output("");
    for (int i = 0; i < formula.length(); ++i){
        // checking whether formual[i] is number
        if (isNumber(formula[i]) || (formula[i] == '-' && i == 0) || (i > 0 && formula[i - 1] == '(' && formula[i] == '-')){
            // checking is formula[i] the last character in number
            if(i + 1 == formula.length() || isOperator(formula[i + 1]) || formula[i + 1] == '(' || formula[i + 1] == ')'){
                output = output + formula[i];
                result.add(output);
                output = "";
            } else {
                output = output + formula[i];
            }
            //checking whether open scope
        }else if (formula[i] == '(') {
            operators.push('(');
            //checking whether close scope
        }else if (formula[i] == ')') {
            while (operators.top() != '(') {
                output = output + operators.pop();
                result.add(output);
                output = "";
            }
            operators.pop();
            //compare rate of operator at formula[i] and at the top of the Stack of operators and push it to the vector
        }else if (isOperator(formula[i])) {
            while (!operators.isEmpty() && (rateOfOperands(operators.top()) >= rateOfOperands(formula[i]))) {
                output = output + operators.pop();
                result.add(output);
                output = "";
            }
            operators.push(formula[i]);
        } else {
            throw "Error incoming data";
        }
    }
    // checking char that left at the stack
    if (operators.size() > 0) {
        for (int i = 0; i < operators.size(); ++i) {
            output = output + operators.pop();
            result.add(output);
            output = "";
        }
        if(operators.size()>0){
            output = output + operators.pop();
            result.add(output);
        }
    }
}
//reading and calculate poland record
void calculate(Vector<string> & PolRecord){
    Stack<double> operands;
    for(int i(0); i < PolRecord.size(); i++){
        if(isNumber(PolRecord[i][0])){
            operands.push(stringToDouble(PolRecord[i]));
        }else if(isOperator(PolRecord[i][0])){
            char t = PolRecord[i][0];
            double one = operands.pop();
            double two = operands.pop();
            double result;
            switch (t) {
            case '+':
                result = one + two;
                break;
            case '-' :
                result = two - one;
                break;
            case '/':
                result = two / one;
                break;
            case '*':
                result = two * one;
                break;
            case '^':
                result = pow(two,one);
                break;
            }
            operands.push(result);
        }
    }
    double result = operands.pop();
    cout<<result<<endl;
}

int main(){

    string formula;
    cout<<"Enter you expression: "<< endl;
    getline(cin,formula);
    PolishRecord(formula);
    calculate(result);

    return 0;
}
