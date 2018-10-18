/*
input : Postfix Notation(each value or operator separated with space)
output: Sum

Using a stack storing int data for calculation on given postfix notation
*/
#include <cstring>
#include <iostream>

using namespace std;

struct Node
{
    Node *next;
    int data;
};

class Stack
{
    public:
        Stack(){top=NULL;};
        void push(int x);
        int pop();
        bool isEmpty(){return (top == NULL);};
        ~Stack();

    private:
        Node *top;

};

void Stack::push(int x)
{
    Node *temp = new Node;
    temp->data = x;
    if(isEmpty()){
        temp->next = NULL;
    }
    else{
        temp->next = top;

    }
    top = temp;
}

int Stack::pop()
{
    int x;
    if(!isEmpty()){
        Node *temp = top->next;
        x = top->data;
        delete top;
        top = temp;
    }
    else{
        cout << "Pop failed: Empty Stack";
    }
    return x;
}

Stack::~Stack()
{
    Node *temp = top;
    while(top){
        top = top->next;
        delete temp;
        temp = top;
    }
}

bool validOperator(char op);
int operation(int a, int b, char op);

int eval(Stack &s)
{
    char x,c;
    int a,b,operand,ans;
    while((x=cin.get()) != '\n'){
        if(isdigit(x)){
            operand = x-'0';
            while((c=cin.get()) != ' '){
                operand = operand*10 + (c-'0');     //operand might more than one digit
            }
            s.push(operand);
        }
        else if(validOperator(x)){                  //if not digit, check if it is valid operator
            b = s.pop();
            a = s.pop();                            //pop the two top most operand
            ans = operation(a,b,x);                 //perform calculation
            s.push(ans);
        }
    }
    return (s.pop());
}

bool validOperator(char op)
{
    if( op == '+' || op == '-' || op == '*' || op == '/' ){
        return true;
    }
    else{
        return false;
    }
}

int operation(int a, int b, char op)
{
    switch(op){
        case '+':
            return a+b;
        case '-':
            return a-b;
        case '*':
            return a*b;
        case '/':
            return a/b;
    }
}

//input: 5 7 2 3 * - * 8 2 / +
//output: 9
//input: 3 5 1 - * 10 -
//output: 2
int main()
{
    Stack nums;
    int ans = eval(nums);
    cout << ans;
    return 0;
}
