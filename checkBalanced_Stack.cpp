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

struct Node
{
    Node *next;
    int data;
};

class Stack
{
    public:
        Stack(){top=NULL;};
        Node *getTop(){return top;};
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
        cout << "Pop failed: Empty Stack"<<endl;
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


bool checkMatch(int loc, Stack &sa, bool &prevThen)
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

int main()
{
    Stack sa;

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

    if(!(sa.isEmpty()) || !matched){
       outfile << "Match failed!"<<endl;
    }
    else{
        outfile << "Matched!" << endl;
    }
    infile.close();
    outfile.close();
    return 0;
}
/*  Notes:
    char **p = wordlist;
    cout << *(p+1) <<endl;
    cout << strcmp(x,*p);
*/
