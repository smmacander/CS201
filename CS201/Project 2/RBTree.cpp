#include <iostream>
#include <string>
using namespace std;

template <class keytype, class valuetype>
class RBTree{
    struct node{
        int key, value;
        bool color;
        int rank;
        node *left, *right, *p;
    };
    node *root; //root of the tree
    node *nil; //arbitrary node of the tree
    int treeSize; //size of the tree
    void DestroyRecursive(node node); //helper function to recursively destroy
    public:
        RBTree();  //Default Constructor. The Tree should be empty
        RBTree(keytype k[], valuetype V[], int s); //For this constructor the tree should be built using the arrays K and V containing s items of keytype and valuetype
        ~RBTree();  //Destructor for the class.
        valuetype * search(keytype k); //Traditional search.  Should return a pointer to the valuetype stored with the key.  If the key is not stored in the tree then the function should return NULL.
        void insert(keytype k, valuetype v); //Inserts the node with key k and value v into the tree.
        int remove(keytype k); //Returns the rank of the key k in the tree. Returns 0 if the key k is not found. The smallest item in the tree is rank 1.
        int rank(keytype k); //Returns the rank of the key k in the tree. Returns 0 if the key k is not found. The smallest item in the tree is rank 1.
        keytype select(int pos); //Order Statistics. Returns the key of the node at position pos in the tree.  Calling with pos = 1 should return the smallest key in the tree, pos = n should return the largest.
        keytype * successor(keytype k); //Returns a pointer to the key after k in the tree. Should return NULL if no successor exists.
        keytype * predecessor(keytype k); //Returns a pointer to the key before k in the tree. Should return NULL if no successor exists.
        int size(); //returns the number of nodes in a tree
        void preorder(); //Prints the keys of the tree in a preorder traversal.
        void inorder(); //Prints the keys of the tree in an inorder traversal.
        void postorder(); //Prints the keys of the tree in a postorder traversal.
};

template <class keytype, class valuetype>
RBTree<keytype, valuetype>::RBTree(){
    treeSize = 0;
}

template <class keytype, class valuetype>
RBTree<keytype, valuetype>::RBTree(keytype k[], valuetype V[], int s){
    for(int i = 0; i < s; i++){
        insert(k[i], V[i]);
    }
}

template <class keytype, class valuetype>
void RBTree<keytype, valuetype>::DestroyRecursive(node node){
    if(node){
        DestroyRecursive(node->left);
        DestroyRecursive(node->right);
        delete node;
    }
}

template <class keytype, class valuetype>
RBTree<keytype, valuetype>::~RBTree(){
    DestroyRecursive(root);
}

template <class keytype, class valuetype>
valuetype RBTree<keytype, valuetype>:: *search(keytype k){
    node currentNode = root;
    while (currentNode != NULL){
        if (k > currentNode->key)
            currentNode = currentNode->right;
        
        else if (k < currentNode->key)
            currentNode = currentNode->left;
        else
            return currentNode->value;
    }
    return NULL;
}

struct node{
    int key, value;
    bool color;
    int rank;
    node *left, *right, *p;
};