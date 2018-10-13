//Josephus prob solved by Circular Doubly Linked List with iterator.

#include <iostream>

using namespace std;

struct Node
{
    Node *next;
    Node *prev;
    int data;
};

class Itr
{
     private:
        Node  *current;

     public:
        Itr(Node *p) {current = p;}
        Node *getNode(){return current;}                //return current node pointing by pointer
        void setCurr(Node *c){current = c;}
        void operator++() {current = current->next; }   //for iteration
};

class cirDoublyLinkedList
{
    public:
        cirDoublyLinkedList(){this->head = NULL; this->rear = NULL;};
        void create(int d);                             //create a list of data
        void removeNode(Node *temp);                    //remove the given Node
        Itr start() {return Itr(head);}
        ~cirDoublyLinkedList(){delete lastNode;};
        Node *lastNode;

    private:
        int length = 0;
        Node *head;
        Node *rear;
};

void cirDoublyLinkedList::create(int d)                 //create a circle of d number elements.
{
    Node *temp;
    for(int i=1; i<=d; ++i){
        temp = new Node;
        temp->data = i;
        if(head == NULL){
            head = temp;
            rear = temp;
        }
        else{
            temp->prev = rear;
            rear->next = temp;
            rear = temp;
        }
        ++length;
    }
    rear->next = head;  //connect tail to head
    head->prev = rear;  //connect head to tail
}

void cirDoublyLinkedList::removeNode(Node *temp)
{
    temp->prev->next = temp->next;
    temp->next->prev = temp->prev;
    --length;
    delete temp;
}

int Josephus(cirDoublyLinkedList &lA, int len)
{
    Itr p = lA.start();
    int counter = 1;
    while(len>1){
        ++p;
        ++counter;
        if(counter == 3){
            Node *temp = p.getNode()->next;         //store the next node
            lA.removeNode(p.getNode());             //remove the 3rd node
            --len;
            p.setCurr(temp);                        //set Itr pointer to the next node
            counter = 1;
        }
    }
    lA.lastNode = p.getNode();                      //keep the lastNode to be deleted by destructor
    return p.getNode()->data;
}

int main()
{
    int n = 7;                      //set number of nodes in the Josephus circle
    cirDoublyLinkedList ListA;
    ListA.create(n);
    int ans = Josephus(ListA,n);    //conduct the Josephus process
    cout << ans;                    //output the last person left in the Josephus circle
}
