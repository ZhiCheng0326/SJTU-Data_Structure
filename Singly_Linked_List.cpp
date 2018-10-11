//Singly Linked List with functions including append, prepend, delete, insert
#include <cstring>
#include <iostream>

using namespace std;

struct Node
{
    Node *next;
    int data;
};

class SinglyLinkedList
{
    public:
        SinglyLinkedList(){this->head = NULL; this->rear = NULL;};
        void appendNode(int d);
        void prependNode(int d);
        void removeNode(int pos);
        void insertNode(int d, int pos);
        void printList();
        ~SinglyLinkedList();

    private:
        int length = 0;
        Node *head;
        Node *rear;
};

SinglyLinkedList::~SinglyLinkedList()
{
    Node *curr = head;
    Node *prev = head;
    while(curr != NULL){
        curr = curr->next;
        delete prev;
        prev = curr;
    }
}

void SinglyLinkedList::appendNode(int d)
{
    Node *temp = new Node;
    temp->data = d;
    if(head == NULL){
        head = temp;
    }
    else{
        rear->next = temp;
    }
    rear = temp;
    rear->next = NULL;
    ++length;
}
void SinglyLinkedList::prependNode(int d)
{
    Node *temp = new Node;
    temp->data = d;
    temp->next = head;
    head = temp;
    ++length;
}

void SinglyLinkedList::removeNode(int pos)
{
    Node *temp = head;
    int cnt = 1;

    if(head == NULL || pos < 1 || pos > length){
        cout << "OUT OF BOUND" << endl;
    }

    else if(pos==1){
        head = head->next;                  //remove head
        delete temp;
        --length;
    }
    else{
        while(cnt+1 != pos){                //loop until the next node is target node
            temp = temp->next;
            ++cnt;
        }
        if (pos == length){                 //remove tail
            rear = temp;
            rear->next = NULL;
            delete temp->next;
        }
        else{                               //remove in between node
            Node* wantedNode = temp->next;
            temp->next = wantedNode->next;
            delete wantedNode;
        }
        --length;
    }
}

void SinglyLinkedList::insertNode(int d, int pos)
{
     Node *temp = head;
     Node *newNode = new Node;
     newNode->data = d;
     int cnt = 1;

     if(pos < 1 || pos > length+1){         //check is it out of range
        cout << "OUT OF BOUND" << endl;
     }
     else if(pos == 1){                     //insert at head
        prependNode(d);
    }
     else if(pos == length+1){              //insert at tail
        appendNode(d);
     }
     else{                                  //insert in between
        while(cnt+1 != pos){                //loop until the next node is the target node
            temp = temp->next;
            ++cnt;
        }
        newNode->next = temp->next;         //do rerouting work
        temp->next = newNode;
        ++length;
     }
}

void SinglyLinkedList::printList()          //show the whole list
{
    Node *curr = head;
    while(curr->next != NULL){
        cout << curr->data << "->";
        curr = curr->next;
    }
    cout << curr->data << endl;
    cout << "Number of nodes : " << length << endl;
}

int main()
{
    SinglyLinkedList ListA;
    for(int i=1; i<=10; ++i){               //form a list from 1 to 10
        ListA.appendNode(i);
    }
    ListA.printList();
    ListA.removeNode(5);                    //remove the 5th node
    ListA.printList();
    ListA.insertNode(40,1);                 //insert number 40 into 1st node
    ListA.printList();
    system("pause");
}
