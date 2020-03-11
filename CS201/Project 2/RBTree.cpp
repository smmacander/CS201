#include <iostream>
#include <string>
using namespace std;
#define COUNT 5

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
            this->size = 1;
        }
        node<keytype, valuetype>(){
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
        node<keytype, valuetype> *nil; //arbitrary node of the tree
        int treeSize; //size of the tree
        void destroyRecursive(node<keytype, valuetype> *node); //helper function to recursively destroy
        void insertFixUp(node<keytype, valuetype> *node); //helper function to restore the red-black properties
        void LeftRotate(node<keytype, valuetype> *node); //helper function to restore the red-black properties
        void RightRotate(node<keytype, valuetype> *node); //helper function to restore the red-black properties
        void printInorder(node<keytype, valuetype> *node); //helper function to recrusively print out Inorder traversal of currentNode
        void printPreorder(node<keytype, valuetype> *node); //helper function to recrusively print out preorder traversal of currentNode
        void printPostorder(node<keytype, valuetype> *node); //helper function to recrusively print out postorder traversal of currentNode
        node<keytype, valuetype> * findNode(keytype k); //helper function that doesn't specifically return a pointer to the value type like search().
        keytype selectHelper(node<keytype, valuetype> *x, int i); //helper function to recursively select the value at position
        node<keytype, valuetype> nodeSelectHelper(node<keytype, valuetype> *x, int i); //helper function to recursively select the value at position
        void transplant(node<keytype, valuetype> *u, node<keytype, valuetype> *v); // helper function for transplanting when deleting
        node<keytype, valuetype> * minimum(node<keytype, valuetype> *x); //helper function to find the minimum node of the tree
        node<keytype, valuetype> * maximum(node<keytype, valuetype> *x); //helper function to find the maximum node of the tree
        void deleteFixUp(node<keytype, valuetype> *x); //helper function to restore the red-black properties after deletion
        void copy(node <keytype, valuetype> *n); //helper function to copy data in operators
        void chop(node <keytype, valuetype> *n); //helper function to chop data in operators
        
    public:
        node<keytype, valuetype> *root; //root of the tree
        RBTree();  //Default Constructor. The Tree should be empty
        RBTree(keytype k[], valuetype V[], int s); //For this constructor the tree should be built using the arrays K and V containing s items of keytype and valuetype
        ~RBTree();  //Destructor for the class.
        RBTree(const RBTree<keytype, valuetype>& source); //copy constructor
        RBTree<keytype, valuetype>& operator=(const RBTree<keytype, valuetype>& other); //copy assignment operator
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
        void print2DUtil(node<keytype, valuetype> *root, int space); //Utility to print the tree
        void print2D(node<keytype, valuetype> *root);  
        void inOrderTreeWalkInsert(node<keytype, valuetype> *x); //helper for copy assignment operator/constructor
};

template <class keytype, class valuetype>
RBTree<keytype, valuetype>::RBTree(){
    treeSize = 0;
    nil = new node<keytype, valuetype>();
    nil->color = 'b';
    nil->left = nullptr;
    nil->right = nullptr;
    nil->parent = nullptr;
    nil->size = 0;
    root = nil;
}

template <class keytype, class valuetype>
RBTree<keytype, valuetype>::RBTree(keytype k[], valuetype V[], int s){
    nil = new node<keytype, valuetype>();
    treeSize = 0;
    nil->color = 'b';
    nil->left = nullptr;
    nil->right = nullptr;
    nil->parent = nullptr;
    nil->size = 0;
    root = nil;
    for(int i = 0; i < s; i++){
        //cout << "k: " << k[i] << " v: " << V[i] << endl;
        insert(k[i], V[i]);
    }
}

template <class keytype, class valuetype>
RBTree<keytype, valuetype>::~RBTree(){
    //chop(root);
}

template <class keytype, class valuetype>
RBTree<keytype, valuetype> :: RBTree(const RBTree<keytype, valuetype> &RBTree){
    treeSize = 0;
    nil = new node<keytype, valuetype>();
    nil->left = nullptr;
    nil->right = nullptr;
    nil->parent = nullptr;
    nil->size = 0;
    nil->color = 'b';
    root = nil;
    copy(RBTree.root);
}

template <class keytype, class valuetype>
RBTree<keytype, valuetype>& RBTree<keytype, valuetype> :: operator=(const RBTree<keytype, valuetype>& other){
    if(this != &other){
        treeSize = 0;
        chop(root);
        nil = new node<keytype, valuetype>();
        nil->left = nullptr;
        nil->right = nullptr;
        nil->parent = nullptr;
        nil->size = 0;
        nil->color = 'b';
        root = nil;
        copy(other.root);
    }
    return *this;
}

template <class keytype, class valuetype>
valuetype * RBTree<keytype, valuetype>::search(keytype k){
    node<keytype, valuetype> *a = findNode(k);
    if(a == nullptr){
        return nullptr;
    } 
    else{
        return &(findNode(k))->value;
    }
}

template <class keytype, class valuetype>
node<keytype, valuetype> * RBTree<keytype, valuetype>::findNode(keytype k){
    if(root == nil){
        return nil;
    }
    node<keytype, valuetype> *currentNode = root;
    while (currentNode != nil){
        if (k > currentNode->key)
            currentNode = currentNode->right;
        
        else if (k < currentNode->key)
            currentNode = currentNode->left;
        else
            return currentNode;
    }
    return nullptr;
}

template <class keytype, class valuetype>
void RBTree<keytype, valuetype> :: insert(keytype k, valuetype v){
    node<keytype, valuetype> *z = new node<keytype, valuetype>(k, v);
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
    insertFixUp(z);
}

template <class keytype, class valuetype>
void RBTree<keytype, valuetype> :: insertFixUp(node<keytype, valuetype> *z){
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
    root->color = 'b';
}

template <class keytype, class valuetype>
int RBTree<keytype, valuetype> :: remove(keytype k){
    node<keytype, valuetype> *z = findNode(k);
    if(z){
        node<keytype, valuetype> *y = z;
        node<keytype, valuetype> *x = new node<keytype, valuetype>;
        char yOriginalColor = y->color;
        if(z->left == nil){
            x = z->left;
            transplant(z, z->right);
        }
        else if(z->right == nil){
            x = z->left;
            transplant(z,z->left);
        }
        else{
            y = minimum(root);
            yOriginalColor = y->color;
            x = y->right;
            if(y->parent == z){
                x->parent = y;
            }
            else{
                transplant(y, y->right);
                y->right = z->right;
                y->right->parent;
            }
            transplant(z, y);
            y->left = z->left;
            y->left->parent = y;
            y->color = z->color;
        }
        if(yOriginalColor == 'b'){
            deleteFixUp(x);
        }
        treeSize--;
        return 1;
    }
    else{
        return 0;
    }
}

template <class keytype, class valuetype>
void RBTree<keytype, valuetype> :: transplant(node<keytype, valuetype> *u, node<keytype, valuetype> *v){
    if(u->parent == nil){
        root = v;
    }
    else if(u == u->parent->left){
        u->parent->left = v;
    }
    else{u->parent->right = v;}
    v->parent = u->parent;
}

template <class keytype, class valuetype>
node<keytype, valuetype> * RBTree<keytype, valuetype> :: minimum(node<keytype, valuetype> *x){
    while(x->left != nil){
        x = x->left;
    }
    return x;
}

template <class keytype, class valuetype>
node<keytype, valuetype> * RBTree<keytype, valuetype> :: maximum(node<keytype, valuetype> *x){
    while(x->right != nil){
        x = x->right;
    }
    return x;
}


template <class keytype, class valuetype>
void RBTree<keytype, valuetype> :: deleteFixUp(node<keytype, valuetype> *x){
    while(x!=root && x->color == 'b'){
        node<keytype, valuetype> *w = x->parent->right;
        if(x == x->parent->left){
            if(w->color == 'r'){
                w->color = 'b';
                x->parent->color = 'r';
                LeftRotate(x->parent);
                w = x->parent->right;
            }
            if(w->left->color == 'b' && w->right->color == 'b'){
                w->color = 'r';
                x = x->parent;
            }
            else{
                if(w->right->color == 'b'){
                    w->left->color = 'b';
                    w->color = 'r';
                    RightRotate(w);
                    w = x->parent->right;
                }
                w->color = x->parent->color;
                x->parent->color = 'b';
                w->right->color = 'b';
                LeftRotate(x->parent);
                x = root;
            }   
        }
        else{
            if(w->color == 'r'){
                w->color = 'b';
                x->parent->color = 'r';
                RightRotate(x->parent);
                w = x->parent->left;
            }
            if(w->right->color == 'b' && w->left->color == 'b'){
                w->color = 'r';
                x = x->parent;
            }
            else{
                if(w->left->color == 'b'){
                    w->right->color = 'b';
                    w->color = 'r';
                    LeftRotate(w);
                    w = x->parent->left;
                }
                w->color = x->parent->color;
                x->parent->color = 'b';
                w->right->color = 'b';
                RightRotate(x->parent);
                x = root;
            }   
        }
    }
    x->color = 'b';
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
    node<keytype, valuetype> *x = findNode(k);
    if(x){
        int r = x->left->size + 1;
        node<keytype, valuetype> *y = x;
    while(y != root){
        if(y == y->parent->right){
            r += y->parent->left->size + 1;
        }
        y = y->parent;
    }
    return r;
    }
    else{return 0;}
}

template <class keytype, class valuetype>
keytype RBTree<keytype, valuetype> :: select(int pos){
    return selectHelper(root, pos);
}

template <class keytype, class valuetype>
keytype * RBTree<keytype, valuetype>::successor(keytype k){
    node<keytype, valuetype> *x = findNode(k);
    if(x == nullptr){
        return NULL;
    } 
    if(x->right != nil){
        node<keytype, valuetype> *a = minimum(x->right);
        return &x->key;
    }
    node<keytype, valuetype> *y = x->parent;
    while(y != nil && x == y->right){
        x = y;
        y = y->parent;
    }
    return &y->key;
}

template <class keytype, class valuetype>
keytype * RBTree<keytype, valuetype>::predecessor(keytype k){
    node<keytype, valuetype> *x = findNode(k);
    if(x == nullptr){
        return NULL;
    } 
    if(x->left != nil){
        node<keytype, valuetype> *a = maximum(x->left);
        return &x->key;
    }
    node<keytype, valuetype> *y = x->parent;
    while(y != nil && x == y->left){
        x = y;
        y = y->parent;
    }
    return &y->key;
}

template <class keytype, class valuetype>
keytype RBTree<keytype, valuetype> :: selectHelper(node<keytype, valuetype> *x, int pos){
    if(x && x->left){
        int r = x->left->size + 1;
        if(pos == r){
            return x->key;
        }
        else if(pos < r){
            return(selectHelper(x->left, pos));
        }
        else{return selectHelper(x->right, pos - r);}
    }
    else{return root->key;}
}

template <class keytype, class valuetype>
node<keytype, valuetype> RBTree<keytype, valuetype> :: nodeSelectHelper(node<keytype, valuetype> *x, int pos){
    int r = x->left->size + 1;
    if(pos == r){
        return x;
    }
    else if(pos < r){
        return(selectHelper(x->left, pos));
    }
    else{return selectHelper(x->right, pos - r);}
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
    if(x != nil){
        cout << x->key << " ";
    }
    printInorder(x->right);
}

template <class keytype, class valuetype>
int RBTree<keytype, valuetype> :: size(){
    return treeSize;
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

    if(x != nil){
        cout << x->key << " ";
    }
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
    if(x != nil){
        cout << x->key << " ";
    }
}

template <class keytype, class valuetype>
void RBTree<keytype, valuetype> :: print2DUtil(node<keytype, valuetype> *root, int space)  
{  
    // Base case  
    if (root == NULL)  
        return;  
  
    // Increase distance between levels  
    space += COUNT;  
  
    // Process right child first  
    print2DUtil(root->right, space);  
  
    // Print current node after space  
    // count  
    cout<<endl;  
    for (int i = COUNT; i < space; i++)  
        cout<<" ";  
    cout<<root->key<<"\n";  
  
    // Process left child  
    print2DUtil(root->left, space);  
}  

template <class keytype, class valuetype>
void RBTree<keytype, valuetype> :: print2D(node<keytype, valuetype> *root)  
{  
    // Pass initial space count as 0  
    print2DUtil(root, 0);  
}  

template <class keytype, class valuetype>
void RBTree<keytype, valuetype> :: copy(node <keytype, valuetype> *n){
    if(n->key){
        insert(n->key, n->value);
        copy(n->left);
        copy(n->right);
    }
}

template <class keytype, class valuetype>
void RBTree<keytype, valuetype> :: chop(node <keytype, valuetype> *n){
    if(n){
        chop(n->left);
        chop(n->right);
        delete n;
    }
}
