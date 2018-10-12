//class LongInt operation in singly linked list
//class LongInt which can perform addition, cin and cout
//assuming all the LongInt data is reversed, eg: 12305 store in linked list as 50321
#include <cstring>
#include <iostream>

using namespace std;

struct Node
{
    Node *next;
    char data;
};

class SinglyLinkedList
{
    public:
        SinglyLinkedList(){this->head = NULL; this->rear = NULL;};
        void create(char p);
        void clear();
        Node *getHead()const {return head;}
        void setHead(Node *p){head = p;}
        ~SinglyLinkedList(){clear();};

    private:
        Node *head;
        Node *rear;
};

void SinglyLinkedList::create(char p)
{
    Node *temp = new Node;
    temp->data = p;
    head ? rear->next = temp : head = temp;
    rear = temp;
    rear->next = NULL;
}

void SinglyLinkedList::clear()
{
    Node *curr = head;
    Node *prev = head;
    while(curr != NULL){
        curr = curr->next;
        delete prev;
        prev = curr;
    }
}

class LongInt
{
    friend LongInt operator+(const LongInt &n1,const LongInt &n2);
    friend ostream &operator <<(ostream &os, const LongInt &n);
    friend istream &operator >>(istream &is, LongInt &n);

    public:
        LongInt(char *temp);
        LongInt(){};
        LongInt(const LongInt &c);
        LongInt &operator=(const LongInt &right);
        int getLen()const{return len;}
        void setLen(int x){len = x;}
        ~LongInt(){}

    private:
        SinglyLinkedList lis;
        int len = 0;

};

LongInt::LongInt(char *temp)            //constructor
{
    len = strlen(temp);
    for(int i=0; i<len; ++i){
        lis.create(temp[i]);
    }
}

LongInt::LongInt(const LongInt &right)      //copy constructor
{
    lis.setHead(right.lis.getHead());
    len = right.len;
}

LongInt& LongInt::operator=(const LongInt &right)
{
    lis.clear();                        //delete the current list
    lis.setHead(right.lis.getHead());
    len = right.len;
    return *this;
}

LongInt operator+(const LongInt &n1,const LongInt &n2)
{
    LongInt longTemp;
    longTemp.len = (n1.getLen() >= n2.getLen() ? n1.getLen()+1 : n2.getLen()+1);
    Node *curr1 = n1.lis.getHead();
    Node *curr2 = n2.lis.getHead();
    Node *curr3 = NULL;
    Node *head3 = NULL;
    int addTens = 0;
    char sum;

    for(int i=0; i<longTemp.len; ++i){
        Node *temp = new Node;
        sum = ((!curr1 && !curr2 && addTens) ? '1' : '0');
        if(!curr1 && curr2){                        //if exp2 longer than exp1
            sum = curr2->data + addTens;
            curr2 = curr2->next;                    //traverse eqn 2
        }
        else if(!curr2 && curr1){                   //if exp1 longer than exp2
            sum = curr1->data + addTens;
            curr1 = curr1->next;                    //traverse eqn 1
        }
        else if(curr1 && curr2){
            sum = curr1->data + curr2->data - '0' + addTens;
            curr1 = curr1->next;                    //traverse eqn 1
            curr2 = curr2->next;                    //traverse eqn 2
        }
        temp->data = (sum > '9' ? sum - 10 : sum);  //minus 10 if sum >9
        addTens = (sum > '9' ? 1 : 0);              //addTens = 1 if sum >9
        head3 ? curr3->next = temp : head3 = temp;  //form
        curr3 = temp;
    }
    curr3->next = NULL;                             //rear->next = NULL
    longTemp.lis.setHead(head3);
    return longTemp;                                //return LongInt type
}

ostream &operator <<(ostream &os, const LongInt &n)
{
    Node *temp = n.lis.getHead();
    while(temp->next){
        os << temp->data;
        temp = temp->next;
    }
    if(temp->data != '0'){                          //ignore if last value is zero
        os<<temp->data;
    }
    return os;
}
istream &operator >>(istream &is, LongInt &n)
{
    char x;
    x = is.get();
    int len = 0;
    while(x != '\n'){
        n.lis.create(x);
        x = is.get();
        ++len;
    }
    n.setLen(len);
    return is;
}

//test case
int main()
{
    LongInt a = "111111111111111111";
    LongInt b = "88888888888888888888888";
    LongInt c = a+b;
    LongInt d;
    cout << "a+b = " << c <<endl;
    cout << "Please enter a number for d: ";
    cin >> d;
    cout << "d+b = " << d + b;
}
