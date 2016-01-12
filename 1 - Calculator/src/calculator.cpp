#include <iostream>
#include "random.h"
#include "cmath"
#include "mystack.h"
#include <console.h>
#include <string>
#include "myvector.h"

using namespace std;

//in this vector i will save polish record of formula
MyVector<string> polishRecord;

// rate of operators
int operandsRate(const char ch) {
    switch (ch) {
    case '^':
        return 3;
    case '*':
    case '/':
        return 2;
    case '+':
    case '-':
        return 1;
    }
    //in case of scope
    return 0;
}

//checking whether the number
bool isNumber(char ch) {
    return (('0' <= ch) && (ch <= '9')) || (ch == '.');
}
//checking whether the operator
bool isOperator(char ch) {
    return (ch == '+' || ch == '-' || ch == '/' || ch == '*' || ch == '^');
}

//writes a Polish record
void PolishRecord(string expression) {
    //buffer stack that save operators before put them to output
    MyStack<char> operators;
    //buffer string that save numbers and operators before put them to the PolishRecord vector
    string output("");
    for (int i = 0; i < expression.length(); ++i) {
        // checking whether formual[i] is number or "-" on first position or first "-" in the scope
        if (isNumber(expression[i]) || (expression[i] == '-' && i == 0) || (i > 0 && expression[i - 1] == '(' && expression[i] == '-')) {
            // checking is formula[i] the last character in number
            if (i + 1 == expression.length() || isOperator(expression[i + 1]) || expression[i + 1] == '(' || expression[i + 1] == ')') {
                output = output + expression[i];
                polishRecord.pushBack(output);
                output = "";
            }
            else {
                output = output + expression[i];
            }
            //checking whether open scope (pushing it to stack)
        }
        else if (expression[i] == '(') {
            operators.push('(');
            //checking whether close scope
        }
        else if (expression[i] == ')') {
            while (operators.top() != '(') {
                output = output + operators.top();
                operators.pop();
                polishRecord.pushBack(output);
                output = "";
            }
            operators.pop();
            //compare rate of operator at formula[i] and at the top of the Stack of operators and push it to the vector
        }
        else if (isOperator(expression[i])) {
            while (!operators.empty() && (operandsRate(operators.top()) >= operandsRate(expression[i]))) {
                output = output + operators.top();
                operators.pop();
                polishRecord.pushBack(output);
                output = "";
            }
            operators.push(expression[i]);
        }
        else {
            throw "Error incoming data";
        }
    }
    // checking char that left in the stack
    while (operators.size() > 0) {
        output = output + operators.top();
        operators.pop();
        polishRecord.pushBack(output);
        output = "";
    }
}

//reading polish record and calculate it
void calculate(MyVector<string>& polishRecord) {
    /* buffer stack of operands where we push two operand that we met in record
    and then using this operand when met in record operator */
    MyStack<double> operands;
    for (int i = 0; i < polishRecord.size(); i++) {
        if (isNumber(polishRecord[i][0])) {
            //if token is number convert string to double and push it to stack operands
            operands.push(stod(polishRecord[i]));
        }
        //if token is operator -  make action that means this operator with two first numbers in operands stack
        else if (isOperator(polishRecord[i][0])) {
            char t = polishRecord[i][0];
            double one = operands.top();
            operands.pop();
            double two = operands.top();
            operands.pop();
            double result;
            switch (t) {
            case '+':
                result = one + two;
                break;
            case '-':
                result = two - one;
                break;
            case '/':
                result = two / one;
                break;
            case '*':
                result = two * one;
                break;
            case '^':
                result = pow(two, one);
                break;
            }
            //pushing result of action(number) to the operands stack
            operands.push(result);
        }
    }
    //when cycle finished all operators where used and in operands stack where one number(result of expression)
    double result = operands.top();
    cout<<result<<endl;
}

int main() {

    string expression;
    cout << "Enter your expression: " << endl;
    //read expression and put it to string formula
    getline(cin,expression);
    //make a polish record
    PolishRecord(expression);
    //calculate polish record
    calculate(polishRecord);

    return 0;
}
