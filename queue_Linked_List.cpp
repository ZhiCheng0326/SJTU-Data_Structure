#include <iostream>

using namespace std;

template <class T>
struct Node
{
    Node<T> *next;
    T data;
};

class segmentationFault
{
     public:
         segmentationFault(): message( "Attempted to access unauthorized address" ) { }
         const char *what() const { return message; }
     private:
         const char *message;
};

template <class T>
class SinglyLinkedList
{
    friend bool valid(Node<T>*head, char *message);       //check for exception

    public:
        SinglyLinkedList(){this->head = NULL; this->rear = NULL;};
        void appendNode(T d);               //add node at the back
        void delHead();                     //remove first node
        int getSize(){return len;}          //return size of list
        void printList();
        ~SinglyLinkedList();

    private:
        int len = 0;
        Node<T> *head;
        Node<T> *rear;
};

template <class T>
bool valid(Node<T> *head, char *message)
{
    bool flag = true;
    try{
        if (head == NULL){
            throw segmentationFault();
        }
    }
    catch(segmentationFault Ex){
        cerr << message << Ex.what() << endl;
        flag = false;
    }
    return flag;
}

template <class T>
void SinglyLinkedList<T>::appendNode(T d)
{
    Node<T> *temp = new Node<T>;
    temp->data = d;
    if(head == NULL){
        head = temp;
    }
    else{
        rear->next = temp;
    }
    rear = temp;
    rear->next = NULL;
    ++len;
}

template <class T>
void SinglyLinkedList<T>::delHead()
{
    Node<T> *temp = head;
    if(valid(head, "From delHead(): ")){
        head = head->next;                      //remove head
        delete temp;
        --len;
    }
}

template <class T>
void SinglyLinkedList<T>::printList()          //show the whole list
{
    Node<T> *curr = head;
    if(head != NULL){
        while(curr->next != NULL){
            cout << curr->data << "->";
            curr = curr->next;
        }
    cout << curr->data << endl;
    }
    else{
        cout << "Empty list" << endl;
    }
}

template <class T>
SinglyLinkedList<T>::~SinglyLinkedList()
{
    Node<T> *curr = head;
    Node<T> *prev = head;
    while(curr != NULL){
        curr = curr->next;
        delete prev;
        prev = curr;
    }
}

template<class T>
class Queue
{
    public:
        Queue(){};
        void enqueue(T x){L1.appendNode(x);};
        void dequeue(){L1.delHead();};
        int queueSize(){return L1.getSize();};
        bool isEmpty(){return !L1.getSize();};
        void printQueue(){L1.printList();};
        ~Queue(){};

    private:
        SinglyLinkedList<T> L1;
};

int main()
{
    Queue<int> qA;
    qA.enqueue(5);
    qA.enqueue(6);
    qA.enqueue(7);
    qA.printQueue();    //5->6->7
    qA.dequeue();       //remove 5
    qA.dequeue();       //remove 6
    qA.dequeue();       //remove 7
    qA.dequeue();       //remove failed

//    qA.printQueue();  //cout << "empty list"
    return 0;

}
