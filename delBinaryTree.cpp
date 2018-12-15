#include <iostream>

using namespace std;

template <class T>
struct tNode
{
    tNode<T> *left = NULL;
    tNode<T> *right = NULL;
    T data;
};


template <class T>
class binaryTree
{
    public:
        binaryTree(){root = NULL;};
        
        void insert(T key);
        void delLeaf(T key);
        void delLesser(T key){delLesser(root,key);}
        void delLarger(T key){delLarger(root,key);}
        void delInRange(T low, T high){delInRange(root, low, high);};
        void printTree(){printTree(root);}

    private:
        tNode<T> *root;

        void insert(tNode<T> *leaf, T key);
        tNode<T>* delLeaf(tNode<T> *leaf, T key);
        void delLesser(tNode<T> *leaf, T key);
        void delLarger(tNode<T> *leaf, T key);
        void delInRange(tNode<T> *leaf, T low, T high);
        void printTree(tNode<T> *root);
};

template <class T>
void binaryTree<T>::insert(T key)
{
    if(root == NULL){
        root = new tNode<T>;
        root->data = key;
    }
    else{
        insert(root, key);
    }
}

template <class T>
void binaryTree<T>::insert(tNode<T> *leaf, T key)
{

    if (key < leaf->data){
        if(leaf->left == NULL){
            leaf->left = new tNode<T>;
            leaf->left->data = key;
        }
        else{
            insert(leaf->left, key);
        }
    }

    else if(key >= leaf->data){
        if(leaf->right == NULL){
            leaf->right = new tNode<T>;
            leaf->right->data = key;
        }
        else{
            insert(leaf->right, key);
        }
    }
}

template <class T>
void binaryTree<T>::printTree(tNode<T> *leaf)    //pre order traverse
{
    if(leaf){
        cout << leaf->data <<endl;
        printTree(leaf->left);
        printTree(leaf->right);
    }
}

template <class T>
void binaryTree<T>::delLeaf(T key)
{
    if (root->data == key && (!root->left || !root->right)){
        root = delLeaf(root, key);
    }
    else{
        tNode<T> *temp = delLeaf(root, key);
    }
}

template <class T>
tNode<T>* binaryTree<T>::delLeaf(tNode<T> *leaf, T key)
{
    if(leaf == NULL){
        return leaf;
    }
    else if(key < leaf->data){                  
        leaf->left = delLeaf(leaf->left, key);
    }
    else if(key > leaf->data){
        leaf->right = delLeaf(leaf->right,key);
    }
    else{
        if(!leaf->right && !leaf->left){            //no child
            delete leaf;
            leaf = NULL;
        }
        else if(leaf->right && leaf->left){         //2 children
            tNode<T> *temp = leaf->right;
            while(temp->left !=NULL){
                temp = temp->left;
            }
            leaf->data = temp->data;
            leaf->right = delLeaf(leaf->right,temp->data);
        }
        else if(!leaf->right){                      //has only left child
            tNode<T> *temp = leaf;
            leaf = leaf->left;
            delete temp;
        }
        else if(!leaf->left){                       //has only right child
            tNode<T> *temp = leaf;
            leaf= leaf->right;
            delete temp;
        }
    }
    return leaf;
}

template <class T>
void binaryTree<T>::delLesser(tNode<T> *leaf, T key)
{
    if(leaf != NULL){
        if(leaf->data < key){
            while(leaf->left !=NULL){                               
                leaf = delLeaf(leaf, leaf->left->data);             //delete only the left branches
            }
            delLesser(leaf->right, key);                            //check for right branches
            delLeaf(leaf->data);                                    //delete the parent root < key and start looping from root
        }
        else{
            delLesser(leaf->left, key);
        }
    }
  
}

template <class T>
void binaryTree<T>::delLarger(tNode<T> *leaf, T key)
{
    if(leaf != NULL){
        if(leaf->data > key){
            while(leaf->right !=NULL){                               
                leaf = delLeaf(leaf, leaf->right->data);             //delete only the right branches
            }
            delLarger(leaf->left, key);                              //check for left branches
            delLeaf(leaf->data);                                     //delete the parent root > key and start looping from root
        }
        else{
            delLarger(leaf->right, key);
        }
    }
  
}

template <class T>
void binaryTree<T>::delInRange(tNode<T> *leaf, T low, T high)
{
    if(leaf != NULL){
        if(leaf->data < low){
            delInRange(leaf->right, low, high);
        }
        else if(leaf->data > high){
            delInRange(leaf->left, low, high);
        }
        else{
            delLeaf(leaf->data);
            delInRange(root, low, high);
        }
    }
}

int main()
{
    binaryTree<int> bT;

    bT.insert(50);
    bT.insert(30);
    bT.insert(20);
    bT.insert(40);
    bT.insert(70);
    bT.insert(60);
    bT.insert(80);

    bT.printTree();             //output: 50 30 20 40 70 60 80

    cout <<endl;

    // bT.delLesser(45);           //output: 50 70 60 80
    // bT.delLarger(55);           //output: 50 30 20 40 
    // bT.delInRange(30, 70);      //output: 80 20 

    bT.printTree();

    system("pause");
    return 0;
}