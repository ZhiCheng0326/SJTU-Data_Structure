/*
input : begin if then else end
output: matched!

input: begin if then
output: matched failed!

Using stack to check balanced statements for "begin-end" and "if-then-else"in Pascal language.
*/
#include <cstring>
#include <iostream>
#include <fstream>

using namespace std;

template <class T>
struct Node
{
    Node<T> *next;
    int data;
};

template <class T>
class Stack
{
    public:
        Stack(){top=NULL;};
        Node<T> *getTop(){return top;};
        void push(T x);
        T pop();
        bool isEmpty(){return (top == NULL);};
        ~Stack();

    private:
        Node<T> *top;

};

template <class T>
void Stack<T>::push(T x)
{
    Node<T> *temp = new Node<T>;
    temp->data = x;
    if(isEmpty()){
        temp->next = NULL;
    }
    else{
        temp->next = top;

    }
    top = temp;
}

template <class T>
T Stack<T>::pop()
{
    T x;
    if(!isEmpty()){
        Node<T> *temp = top->next;
        x = top->data;
        delete top;
        top = temp;
    }
    else{
        cout << "Pop failed: Empty Stack"<<endl;
    }
    return x;
}

template <class T>
Stack<T>::~Stack()
{
    Node<T> *temp = top;
    while(top){
        top = top->next;
        delete temp;
        temp = top;
    }
}

//return 0 means absent, 10 means first element of left array, 20 means first element of right array
int searchArr(char *word)
{
    char *left[3] = {"begin", "if","\0"};              //pointer array
    char *right[4] = {"end", "then", "else", "\0"};    //pointer array
    char **itr;
    int index = 0;

    for(itr = left; *itr != "\0"; ++itr){
        if (!(strcmp(*itr,word))){
            return (1*10 + index);
        }
        ++index;
    }
    index = 0;
    for(itr = right; *itr != "\0"; ++itr){
        if(!(strcmp(*itr,word))){
            return (2*10 + index);
        }
        ++index;
    }
    return 0;
}

template <class T>
bool checkMatch(int loc, Stack<T> &sa, bool &prevThen)
{
    int category = loc/10;
    int pos = loc%10;
    if(category == 1 ){
        sa.push(loc);
    }
    else if(category == 2 && ( !sa.isEmpty()|| prevThen) ){
        if(pos == 0 && pos ==(sa.getTop()->data)%10 ){          //check begin-end
            sa.pop();
        }
        else if(pos == 1 && pos ==(sa.getTop()->data)%10){      //check if-then
            sa.pop();
            prevThen = true;
        }
        else if(pos == 2 && prevThen){                          //check if-then-else
            prevThen = false;
        }
        else{
            return 0;
        }
    }
    else{
        return 0;
    }
    return 1;
}

template <class T>
void outputResult(Stack<T> &sa, bool matched, ofstream &outfile)
{
    if(!(sa.isEmpty()) || !matched){
       cout << "Match failed!"<<endl;
    }
    else{
        cout << "Matched!" << endl;
    }
}

int main()
{
    Stack<int> sa;

    char x[6];                      //to store the match word
    bool prevThen = false;          //true means "if-then" statement exist
    bool matched = true;

    ifstream infile("match.in");
    ofstream outfile("match.out");

    while(infile >> x){
        int loc = searchArr(x);
        if(!loc) continue;             //skip unnecessary word
        matched = checkMatch(loc, sa, prevThen);
        if(!matched) break;
    }

    outputResult(sa, matched, outfile);

    infile.close();
    outfile.close();
    return 0;
}
