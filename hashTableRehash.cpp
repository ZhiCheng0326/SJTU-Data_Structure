//when active node number greater than half of the size, carry out rehash
//when nodes marked with deleted greater than the number set by user, carry out rehash
#include <iostream>
#include <fstream>

using namespace std;

template <class T>
class closeHashTable
{   
    private:
        struct node{
            T data;
            int state; //0-empty, 1-active, 2-deleted
            node(){state = 0;}
        };

        node* array;
        int size;
        int active=0;                   //number of active node
        int deleted=0;                  //number of deleted node
        int maxDeleted;                 //max number of deleted node input by User
        int(*key)(const T &x);
        static int defaultKey(const int &k){return k;}

    
    public:
        closeHashTable(int length = 101, int fromUser=1, int (*f)(const T &x)= defaultKey)
        {
            size = isPrime(length) ? length: nextPrime(length); //if size = length if it is prime number, else size = next prime number
            array = new node[size];
            key = f;
            maxDeleted = fromUser;
        }
        ~closeHashTable(){delete []array;}
        bool insert(const T &x);
        bool remove(const T &x);
        void doubleSpace();             //double space of array
        void rehash();
        bool isPrime(int x);
        int nextPrime(int x);
        int getSize(){return size;}
        int getDeleted(){return deleted;} //return number of delete node marked

};      

template <class T>
bool closeHashTable<T>::insert(const T &x)
{
    int initPos, pos;

    initPos = pos = key(x) % size;
    do{
        if(array[pos].state != 1){
            array[pos].state = 1;
            array[pos].data = x;
            ++active;
            if(active >= size/2){
                doubleSpace();
            }
            return true;                //true indicates insert successful
        }
        if(array[pos].state ==1 && array[pos].data == x){
            return true;                //true indicates insert successful
        }
        pos = (pos+1) % size;
    }while (initPos!=pos);

    return false;
}

template <class T>
bool closeHashTable<T>::remove(const T &x)
{
    int initPos, pos;
    initPos = pos = key(x) % size;
    do{
        if(array[pos].state == 0){return false;}

        if(array[pos].state == 1 && array[pos].data == x){
            array[pos].state = 2;
            ++deleted;
            --active;
            if(deleted > maxDeleted){
                rehash();
            }
            return true;
        }
        pos = (pos+1)% size;
    }while (initPos!=pos);

    return false;
}

template <class T>
void closeHashTable<T>::doubleSpace()
{
    node *temp = array;

    size = nextPrime(size*2);       //make sure size of hash table is prime 
    array = new node[size];
    maxDeleted *=2;
    active = 0;                      //reset active zero
    for(int i = 0; i<size; ++i){
        if(temp[i].state == 1){
            insert(temp[i].data);   //number of active nodes will be added here
        }
    }
    delete []temp;
}

template <class T>
void closeHashTable<T>::rehash()
{
    deleted = 0;            //reset deleted to zero
    node *temp = array;
    array = new node[size];
    for(int i=0; i< size; ++i){
        if(temp[i].state ==1){
            insert(temp[i].data);
        }
    }
    delete []temp;
}

template<class T>
bool closeHashTable<T>::isPrime(int x)
{
    if(x==2){               //prime number start from 2
        return true;
    }
    else if(x<2){
        return false;
    }
    else{
        for(int j=2; j<x; ++j){
            if(x%j==0) {
                return false;
            }
        }
        return true;
    }
}

template <class T>
int closeHashTable<T>::nextPrime(int x)
{
    int i = x+1;
    while(true){
        if(isPrime(i)){
            return i;
        }
        ++i;
    }
}

int main()
{
    ifstream infile("ht.in");
    ofstream outfile("ht.out");

    int size, maxDeleted, x;
    infile >> size >> maxDeleted;                   //size = 11, maxDeleted = 2
    closeHashTable <int> HT(size, maxDeleted);      //input: 11 12 13 14 15 16 17 18 19

    while(infile >> x){
        HT.insert(x);
    }

    outfile << HT.getSize() << endl;                //output: 23 (next prime number of (11*2))
    outfile << HT.getDeleted() << endl;             //output: 0

    outfile << endl;
    HT.remove(13);
    HT.remove(14);
    HT.remove(15);
    HT.remove(16);

    outfile << HT.getSize() << endl;                //output: 23
    outfile << HT.getDeleted() << endl;             //output: 4 (doesn't reset to zero because the maxDeleted had been *2)

    HT.remove(17);      

    outfile << endl;
    outfile << HT.getSize() << endl;                //output: 23
    outfile << HT.getDeleted() << endl;             //output: 0  (maxDeleted is now 4, the 5th remove will run rehash function)    

    infile.close();
    outfile.close();

    system("pause");
    return 0;

}