

#include <iostream>
#include <string>
#include <windows.h>
//#include "Stack.h"
#include <conio.h>

using namespace std;
/***********************
  header.h
************************/


template <typename T, int N>
class Stack
{
private:
    T elements[N];
    int topIndex;

public:
    Stack();
    void push(const T& value);
    T pop();
    T top();
    bool empty() const;
};


/**************************
   header.cpp
***************************/

template<typename T, int N>
Stack<T, N>::Stack()
{
    topIndex = -1;
}

template<typename T, int N>
void Stack<T, N>::push(const T& value)
{
    if (topIndex < N - 1)
    {
        elements[++topIndex] = value;  // first Add then Insert
    }
    else
    {
        //cout << "Stack is full";
    }
}

template<typename T, int N>
T Stack<T, N>::pop()
{
    if (!empty())
    {
        return elements[topIndex--];
    }
    else
    {
        //cout << "Stack is empty";
        return T();
    }
}

template<typename T, int N>
T Stack<T, N>::top()
{
    if (!empty())
    {
        return elements[topIndex];
    }
    else
    {
        //cout << "Stack is empty";
        return T();
    }
}

template<typename T, int N>
bool Stack<T, N>::empty() const
{
    return topIndex == -1;
}

bool isValidExpression(const string& expression)
{
    bool Flag = true;
    for (char c : expression)
    {
        // Check if the character valid 
        if (c != '&' && c != '|' && c != '!' && c != '^' && c != '>' && c != '<' && c != '(' && c != ')' && c != ' ' && !(c >= 'A' && c <= 'Z') && !(c >= 'a' && c <= 'z'))
        {
            Flag = false;
        }
    }
    return Flag;  // All characters are valid operators
}

int getPrecedence(char op)
{
    if (op == '!' || op == '>')
    {
        return 3;
    }
    else if (op == '&' || op == '|')
    {
        return 2;
    }
    else if (op == '^' || op == '<')
    {
        return 1;
    }
    return 0;
}

void reverseBoolArray(bool arr[], int size)
{
    int start = 0;
    int end = size - 1;

    while (start < end)
    {
        // Swap elements at start and end indices
        bool temp = arr[start];
        arr[start] = arr[end];
        arr[end] = temp;

        // Move towards the center of the array
        start++;
        end--;
    }
}

bool evaluateExpression(const string& expression, const bool* values, int numVariables)
{
    Stack<bool, 100> operandStack;
    Stack<char, 100> operatorStack;

    for (char c : expression)
    {
        if (c == ' ')
        {
            continue;
        }

        if (c == '(')
        {
            operatorStack.push(c);
        }
        else if (c == ')')
        {
            while (!operatorStack.empty() && operatorStack.top() != '(')
            {
                char op = operatorStack.pop();
                bool right = operandStack.pop();
                bool left = operandStack.pop();
                if (op == '&')
                {
                    operandStack.push(left && right);
                }
                else if (op == '|')
                {
                    operandStack.push(left || right);
                }
                else if (op == '^')
                {
                    operandStack.push(left != right);
                }
                else if (op == '!')
                {
                    operandStack.push(!right);
                }
                else if (op == '<')
                {
                    operandStack.push((!left || right) && (!right || left));
                }
                else if (op == '>')
                {
                    operandStack.push(!left || right);
                }
            }
            if (!operatorStack.empty() && operatorStack.top() == '(')
            {
                operatorStack.pop(); // Remove the opening parenthesis
            }
        }
        else if (c == '&' || c == '|' || c == '^' || c == '!' || c == '-' || c == '<' || c == '>')
        {
            while (!operatorStack.empty() && getPrecedence(c) <= getPrecedence(operatorStack.top()))
            {
                char op = operatorStack.pop();
                // cout << " op : " << op << endl;
                bool right = operandStack.pop();
                // cout << " right : " << right << endl;
                bool left = operandStack.pop();
                //cout << " left : " << left << endl;
                if (op == '&')
                {
                    operandStack.push(left && right);
                }
                else if (op == '|')
                {
                    operandStack.push(left || right);
                }
                else if (op == '^')
                {
                    operandStack.push(left != right);
                }
                else if (op == '!')
                {
                    operandStack.push(!right);
                }
                else if (op == '<')
                {
                    operandStack.push((!left || right) && (!right || left));
                }
                else if (op == '>')
                {
                    operandStack.push(!left || right);
                }
            }
            operatorStack.push(c);
        }
        else if (isalpha(c))
        {
            int index = c - 'A';
            operandStack.push(values[index]);
        }
    }

    while (!operatorStack.empty())
    {
        char op = operatorStack.pop();
        bool right = operandStack.pop();
        bool left = operandStack.pop();
        if (op == '&')
        {
            operandStack.push(left && right);
        }
        else if (op == '|')
        {
            operandStack.push(left || right);
        }
        else if (op == '^')
        {
            operandStack.push(left != right);
        }
        else if (op == '!')
        {
            operandStack.push(!right);
        }
        else if (op == '<')
        {
            operandStack.push((!left || right) && (!right || left));
        }
        else if (op == '>')
        {
            operandStack.push(!left || right);
        }
    }
    return operandStack.top();
}

bool isValidExpression(const string& expression);
int getPrecedence(char op);
void reverseBoolArray(bool arr[], int size);
bool evaluateExpression(const string& expression, const bool* values, int numVariables);
std::string removeSpecialCharacters(const std::string& input)
{
    std::string result;

    for (char ch : input) {
        if (std::isalpha(ch)) {
            result.push_back(ch);
        }
    }

    return result;
}
bool isValidString(const std::string& input)
{
    if (input.empty() || input[0] != 'A') {
        return false;  // Doesn't start with 'A'
    }

    for (std::size_t i = 1; i < input.length(); ++i) {
        if (!std::isupper(input[i]) || input[i] != input[i - 1] + 1) {
            return false;  // Not an uppercase consecutive character
        }
    }

    return true;  // All conditions satisfied
}

/***********************************
   main.cpp
************************************/

int main()
{
    //HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    system("color 1F");
    bool flag = true;
    
    do
    {
        system("color 1F");
        cout << "\t\t\t\t\t____________________" << endl;
        cout << "\t\t\t\t\t|__-Truth Table-__ | " << endl;
        cout << "\t\t\t\t\t|__________________|" << endl << endl;
        cout << "_Instruction for User__" << endl;
        cout << "\tOperator\t\tSymbol\n\n";
        cout << "\tAND\t\t\t&\n";
        cout << "\tOR\t\t\t|\n";
        cout << "\tNOT\t\t\t!\n";
        cout << "\tXOR\t\t\t^\n";
        cout << "\tImplies\t\t\t>\n";
        cout << "\tDouble Implies\t\t<\n\n";
        string expression;
        bool inputflage=false;
        labe1:
        //do
        //{
            // SetConsoleTextAttribute(hConsole, 13);
             //cout << "\n\n\tUse only above given operator:  "<<endl;
            cout << "Enter  Expression: ";
            getline(cin, expression);
            string input = removeSpecialCharacters(expression);
            
            inputflage=isValidString(input);
            /*if (!inputflage)
            {
                cout << "Enter consective variable" << endl;
                goto labe1;
            }*/
            if (!isValidExpression(expression))
            {
                cout << "Enter valid input " << endl;
                goto labe1;
            }
        //} while (!isValidExpression(expression)&&inputflage);
        // SetConsoleTextAttribute(hConsole, 15);
         // Count the number of unique variables in the expression
        string uniqueVars = "";
        for (int i = 0; i < expression.length(); i++)
        {
            char c = expression[i];
            if (isalpha(c) && uniqueVars.find(c) == string::npos) // if has alphabate and not occour in unqueVars String
            {
                uniqueVars += c;
            }
        }
        //cout << "str: " << uniqueVars << endl;
        int numVariables = uniqueVars.size();
        bool values[26] = { 0 }; // Assuming up to 26 variables (A to Z)

        //SetConsoleTextAttribute(hConsole, 14);
        cout << "************************************************\n\n";
        cout << "Truth Table for Expression: " << expression << endl;

        // Print the header with variable names
        cout << "\n----------------------------------------------\n\n";
        //SetConsoleTextAttribute(hConsole, 15);
        for (int i = 0; i < uniqueVars.length(); i++)
        {
            char ch = uniqueVars[i];
            cout << "\t| " << ch << " | ";
        }
        //SetConsoleTextAttribute(hConsole, 11);
        cout << "  Result\n";
        //SetConsoleTextAttribute(hConsole, 15);
        // Iterate through all possible combinations of variable values
        for (int i = 0; i < pow(2, numVariables); i++)
        {
            for (int j = 0; j < numVariables; j++)
            {
                int power = 1;
                int index = uniqueVars[j] - 'A';
                for (int k = 0; k < j; k++)
                {
                    power *= 2;
                }
                values[index] = (i / power) % 2;
            }
            reverseBoolArray(values, numVariables);
            bool result = evaluateExpression(expression, values, numVariables);

            // Print the variable values and the result
            for (int j = 0; j < numVariables; j++)
            {
                cout << "\t| " << values[uniqueVars[j] - 'A'] << " | ";
            }
            // SetConsoleTextAttribute(hConsole, 11);
            cout << "   " << result << endl;
            // SetConsoleTextAttribute(hConsole, 15);
        }
        cout << "\n----------------------------------------------\n";
        cout << "\n\n\t\t Enter any Key For Continue\n\t\t OR ESC to exit ... ";
        char ch = _getch();
        if (ch == 27)
        {
            flag = false;
        }
        system("CLS");
    } while (flag);
    system("color 1F");
    cout << "\n\n\n\n\t\t\t\t";
    string thanks = "\n\n\n\n\t\t\t\tThanks For Using Our Truth Table...!\n\t\t\t\tBy Syed Asad Raza & Sharaz";
    for (int i = 0; i < thanks.length(); i++)
    {
        Sleep(200);
        cout << thanks[i];
    }
    cout << "\n\n\n";
    return 0;
}
