#include <iostream>
#include <fstream>

using namespace std;

template <class T>
struct Node
{

    Node<T> *left = NULL;
    Node<T> *right = NULL;
    T data;
};

template <class T>
class bTree
{
    public:
        bTree(){root = NULL;}
        
        void addLeaf(T key);
        int getLen(){return getLen(root);}
        bool checkComplete();
        

    private:
        Node<T> *root = NULL;
        int getLen(Node<T> *temp);
        bool checkComplete(int index, Node<T> *temp, int len);
        void addLeaf(T key, Node<T> *leaf);
};

template <class T>
void bTree<T>::addLeaf(T key, Node<T> *leaf)        //leaf added in the form of binary search tree
{
    if(key < leaf->data){
        if(leaf->left == NULL){
            leaf->left = new Node<T>;
            leaf->left->data = key;
        }
        else{
            addLeaf(key, leaf->left);
        }
    }
    else if(key >= leaf->data){
        if(leaf->right == NULL){
            leaf->right = new Node<T>;
            leaf->right->data = key;
        }
        else{
            addLeaf(key, leaf->right);
        }
    }
}

template <class T>
void bTree<T>::addLeaf(T key)
{
    if(root == NULL){
        root = new Node<T>;
        root ->data = key;
    }
    else{
        addLeaf(key, root);
    }
}

template <class T>
int bTree<T>::getLen(Node<T> *temp)
{
    if (temp == NULL){
        return 0;
    }
    return (1 + getLen(temp->left) + getLen(temp->right));

}

template <class T>
bool bTree<T>::checkComplete()
{
    int num = getLen();                   //get number of leaves
    return checkComplete(0,root,num);

}

template <class T>
bool bTree<T>::checkComplete(int index, Node<T> *temp, int len)
{

    if(temp == NULL){
        return true;
    }
    else if(index >= len){
        return false;
    }
    else{
        return (checkComplete(2*index+1, temp->left, len) && checkComplete(2*index+2, temp->right, len));
    }
}

int main()
{
    bTree<int> treeA;
    ifstream infile("complete.in");
    ofstream outfile("complete.out");

    int n;
    while(infile >> n){
        treeA.addLeaf(n);              //leaves added in the form of binary tree
    }

    bool x = treeA.checkComplete();   //check whether is it complete tree
    outfile << x << endl;

    infile.close();
    outfile.close();
    system("pause");
}

/*
input: 9 3 2 4 10
output: true
input: 3 1 4 5 9
output: false
*/

//while adding leaves, smaller leaves at left side, larger leaves at right side

//if index >= number of leaves in the tree, it is not a complete tree
//traverse through left sub-tree with 2*index+1
//traverse through right sub-tree with 2*index+2
