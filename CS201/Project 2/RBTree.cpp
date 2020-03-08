#include <iostream>
#include <string>
using namespace std;

template <class keytype, class valuetype>
struct node{
        keytype key;
        valuetype value;
        char color;
        int size;
        node *left, *right, *parent;
        node<keytype, valuetype>(keytype k, valuetype v){ 
            this->key = k; 
            this->value = v;
            this->left = NULL;
            this->right = NULL;
            this->parent = NULL;
            this->color = 'b';
        }
        node<keytype, valuetype>(){
            this->left = NULL;
            this->right = NULL;
            this->parent = NULL;
            this->color = 'b';
        };
};

template <class keytype, class valuetype>
class RBTree{
    private:
        node<keytype, valuetype> *root; //root of the tree
        node<keytype, valuetype> *nil; //arbitrary node of the tree
        int treeSize; //size of the tree
        void DestroyRecursive(node<keytype, valuetype> *node); //helper function to recursively destroy
        void InsertFixUp(node<keytype, valuetype> *node); //helper function to restore the red-black properties
        void LeftRotate(node<keytype, valuetype> *node); //helper function to restore the red-black properties
        void RightRotate(node<keytype, valuetype> *node); //helper function to restore the red-black properties
        void printInorder(node<keytype, valuetype> *node); //helper function to recrusively print out Inorder traversal of currentNode
        void printPreorder(node<keytype, valuetype> *node); //helper function to recrusively print out preorder traversal of currentNode
        void printPostorder(node<keytype, valuetype> *node); //helper function to recrusively print out postorder traversal of currentNode
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
    nil->color = 'b';
    root = NULL;
    treeSize = 0;
}

template <class keytype, class valuetype>
RBTree<keytype, valuetype>::RBTree(keytype k[], valuetype V[], int s){
    nil->color = 'b';
    root = NULL;
    treeSize = 0;
    for(int i = 0; i < s; i++){
        //cout << "k: " << k[i] << " v: " << V[i] << endl;
        insert(k[i], V[i]);
    }
}

template <class keytype, class valuetype>
void RBTree<keytype, valuetype>::DestroyRecursive(node<keytype, valuetype> *node){
    if(node == nullptr)
        return;
    DestroyRecursive(node->left);
    DestroyRecursive(node->right);
    delete node;
}

template <class keytype, class valuetype>
RBTree<keytype, valuetype>::~RBTree(){
    DestroyRecursive(root);
}

template <class keytype, class valuetype>
valuetype * RBTree<keytype, valuetype>::search(keytype k){
    if(root == NULL){
        return NULL;
    }
    node<keytype, valuetype> *currentNode = root;
    while (currentNode != NULL){
        if (k > currentNode->key)
            currentNode = currentNode->right;
        
        else if (k < currentNode->key)
            currentNode = currentNode->left;
        else
            return &currentNode->value;
    }
    return NULL;
}

template <class keytype, class valuetype>
void RBTree<keytype, valuetype> :: insert(keytype k, valuetype v){
    node<keytype, valuetype> *z = new node<keytype, valuetype>(k, v);
    z->left = nil;
    z->right = nil;
    z->parent = nil;
    z->size = 1;
    node<keytype, valuetype> *y = nil;
    node<keytype, valuetype> *x = root;
    while(x != nil){
        y = x;
        if(z->key < x->key){
            x = x->left;
        }
        else{x = x->right;}
    }
    z->parent = y;
    if(y == nil){
        root = z;
    }
    else if(z->key < y->key){
        y->left = z;
    }
    else{y->right = z;}
    z->left = nil;
    z->right = nil;
    z->color = 'r';
    treeSize++;
    InsertFixUp(z);
}

template <class keytype, class valuetype>
void RBTree<keytype, valuetype> :: InsertFixUp(node<keytype, valuetype> *z){
    cout << "Bout to fix key: " << z->key << endl;
    cout << nil->color << endl;
    while(z->parent->color == 'r'){
        if(z->parent == z->parent->parent->left){
            node<keytype, valuetype> *y = z->parent->parent->right;
            if(y->color == 'r'){
                z->parent->color = 'b';
                y->color = 'b';
                z->parent->parent->color = 'r';
                z = z->parent->parent;
            } 
            else{
                if(z == z->parent->right){
                    z = z->parent;
                    LeftRotate(z);
                }
                z->parent->color = 'b';
                z->parent->parent->color = 'r';
                RightRotate(z->parent->parent);
            }
        }
        else{
            node<keytype, valuetype> *y = z->parent->parent->left;
            if(y->color == 'r'){
                z->parent->color = 'b';
                y->color = 'b';
                z->parent->parent->color = 'r';
                z = z->parent->parent;
            } 
            else{
                if(z == z->parent->left){
                    z = z->parent;
                    RightRotate(z);
                }
                z->parent->color = 'b';
                z->parent->parent->color = 'r';
                LeftRotate(z->parent->parent);
            }   
        }   
    }
}

template <class keytype, class valuetype>
void RBTree<keytype, valuetype> :: LeftRotate(node<keytype, valuetype> *x){
    node<keytype, valuetype> *y = x->right;
    x->right = y->left;
    if(y->left != nil){
        y->left->parent = x;
    }
    y->parent = x->parent;
    if(x->parent == nil){
        root = y;
    }
    else if(x == x->parent->left){
        x->parent->left = y;
    }
    else{x->parent->right = y;}
    y->left = x;
    x->parent = y;
    y->size = x->size;
    x->size = x->left->size + x->right->size + 1;
}

template <class keytype, class valuetype>
void RBTree<keytype, valuetype> :: RightRotate(node<keytype, valuetype> *x){
    node<keytype, valuetype> *y = x->left;
    x->left = y->right;
    if(y->right != nil){
        y->right->parent = x;
    }
    y->parent = x->parent;
    if(x->parent == nil){
        root = y;
    }
    else if(x == x->parent->right){
        x->parent->left = y;
    }
    else{x->parent->left = y;}
    y->right = x;
    x->parent = y;
    y->size = x->size;
    x->size = x->left->size + x->right->size + 1;
}

template <class keytype, class valuetype>
int RBTree<keytype, valuetype> :: rank(keytype k){
    return 0;
}

template <class keytype, class valuetype>
void RBTree<keytype, valuetype> :: inorder(){
    printInorder(root);
    cout << endl;
}

template <class keytype, class valuetype>
void RBTree<keytype, valuetype> :: printInorder(node<keytype, valuetype> *x){
    if (x == nil){
        return;
    }
    printInorder(x->left);
    cout << x->key << " ";
    printInorder(x->right);
}

template <class keytype, class valuetype>
void RBTree<keytype, valuetype> :: preorder(){
    printPreorder(root);
    cout << endl;
}

template <class keytype, class valuetype>
void RBTree<keytype, valuetype> :: printPreorder(node<keytype, valuetype> *x){ 
    if (x == NULL) 
        return; 

    cout << x->key << " "; 
    printPreorder(x->left);  
    printPreorder(x->right); 
}

template <class keytype, class valuetype>
void RBTree<keytype, valuetype> :: postorder(){
    printPostorder(root);
    cout << endl;
}


template <class keytype, class valuetype>
void RBTree<keytype, valuetype> :: printPostorder(node<keytype, valuetype> *x){ 
    if (x == NULL) 
        return; 

    printPreorder(x->left);  
    printPreorder(x->right); 
    cout << x->key << " ";
}
