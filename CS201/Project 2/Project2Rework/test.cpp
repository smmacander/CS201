#include <iostream>
#include <cstdlib>
using namespace std;

template <class keytype, class valuetype>
struct treeNode{
    keytype key;
    valuetype value;
    char color;
    int size;
    treeNode *left, *right, *parent;
    treeNode<keytype, valuetype>(keytype k, valuetype v){ 
        this->key = k; 
        this->value = v;
        this->left = NULL;
        this->right = NULL;
        this->parent = NULL;
        this->color = 'b';
        this->size = 1;
    };
    treeNode<keytype, valuetype>(){
        this->left = NULL;
        this->right = NULL;
        this->parent = NULL;
        this->color = 'b';
        this->size = 0;
    };
};

template <class keytype, class valuetype>
class RBTree{
    private:
        treeNode<keytype, valuetype> *nil;
        treeNode<keytype, valuetype> *root;
        int treeSize;
        void RBInsert(RBTree<keytype, valuetype> T, treeNode *z);

    public:
        RBTree(); //Default Constructor. The tree should be empty
        RBTree(keytype k[], valuetype V[], int s); //For this constructor thetree should be built using the arrays   K and V containing s items of keytypeand valuetype.
        void insert(keytype k, valuetype v); //Inserts the node with key k and value v into the tree.
};

template<class keytype, class valuetype>
RBTree<keytype, valuetype>::RBTree(){
    treeSize = 0;
    nil = new treeNode<keytype, valuetype>();
    nil->color = 'b';
    nil->left = nullptr;
    nil->right = nullptr;
    nil->parent = nullptr;
    nil->size = 0;
    root = nil;
}

template<class keytype, class valuetype>
RBTree<keytype, valuetype>::RBTree(keytype k[], valuetype V[], int s){
    treeSize = 0;
    treeNode<keytype, valuetype> *nil = new treeNode<keytype, valuetype>();
    nil->color = 'b';
    nil->left = nullptr;
    nil->right = nullptr;
    nil->parent = nullptr;
    nil->size = 0;
    root = nil;
    for(int i = 0; i < s; i++){
        insert(k[i], V[i]);
    }
};

template<class keytype, class valuetype>
void RBTree<keytype, valuetype>::insert(keytype k, valuetype v){
    treeNode<keytype, valuetype> *z = new treeNode<keytype, valuetype>(k, v);
    RBInsert(this, z);
};
