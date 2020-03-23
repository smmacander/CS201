#include <iostream>
#include <cstdlib>
using namespace std;
#define COUNT 5

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
        void RBInsert(RBTree<keytype, valuetype> *T, treeNode<keytype, valuetype> *z);
        void RBInsertFixUp(RBTree<keytype, valuetype> *T, treeNode<keytype, valuetype> *z);
        void LeftRotate(RBTree<keytype, valuetype> *T, treeNode<keytype, valuetype> *x);
        void RightRotate(RBTree<keytype, valuetype> *T, treeNode<keytype, valuetype> *x);
        void RBDelete(RBTree<keytype, valuetype> *T, treeNode<keytype, valuetype> *z);
        void RBDeleteFixUp(RBTree<keytype, valuetype> *T, treeNode<keytype, valuetype> *x);
        void RBTransplant(RBTree<keytype, valuetype> *T, treeNode<keytype, valuetype> *u, treeNode<keytype, valuetype> *v);
        void PreOrderTreeWalk(treeNode<keytype, valuetype> *x);
        void InOrderTreeWalk(treeNode<keytype, valuetype> *x);
        void PostOrderTreeWalk(treeNode<keytype, valuetype> *x);
        treeNode<keytype, valuetype> * TreeSearch(treeNode<keytype, valuetype> *x, keytype k);
        int OSRank(RBTree<keytype, valuetype> *T, treeNode<keytype, valuetype> *x);
        treeNode<keytype, valuetype> * OSSelect(treeNode<keytype, valuetype> *x, int i);
        treeNode<keytype, valuetype> * TreeMinimum(treeNode<keytype, valuetype> *x);
        treeNode<keytype, valuetype> * TreeMaximum(treeNode<keytype, valuetype> *x);
        treeNode<keytype, valuetype> * TreeSuccessor(treeNode<keytype, valuetype> *x);
        treeNode<keytype, valuetype> * TreePredecessor(treeNode<keytype, valuetype> *x);
        treeNode<keytype, valuetype> * copy(treeNode <keytype, valuetype> *root); //helper function to copy data in operators
        void chop(treeNode <keytype, valuetype> *n); //helper function to chop data in operators
        void sizeSwap(treeNode <keytype, valuetype> *a, treeNode <keytype, valuetype> *b); 

    public:
        RBTree(); //Default Constructor. The tree should be empty
        RBTree(keytype k[], valuetype V[], int s); //For this constructor thetree should be built using the arrays   K and V containing s items of keytypeand valuetype.
        RBTree(const RBTree<keytype, valuetype>& source); //copy constructor
        RBTree<keytype, valuetype>& operator=(const RBTree<keytype, valuetype>& other); //copy assignment operator
        valuetype * search(keytype k); //Traditional search.  Should return a pointer to the valuetype stored with the key.  If the key is not stored in the tree then the function should return NULL.
        void insert(keytype k, valuetype v); //Inserts the node with key k and value v into the tree.
        int remove(keytype k); //Removes the node with key kand returns 1.  If key k is not found then removeshould return 0.
        int rank(keytype k); //Returns the rank of the key k in the tree.  Returns 0 if the key k is not found. The smallest item in the tree is rank 1.
        keytype select(int pos); //Order Statistics. Returns the key of the node at position pos in the tree.  Calling with pos = 1 should return the smallest key in the tree, pos = n should return the largest.
        keytype *successor(keytype k); //Returns a pointer to the key after k in the tree.  Should return NULL if no successor exists.
        keytype *predecessor(keytype k); //Returns a pointer to the key before k in the tree.  Should return NULL if no predecessor exists.
        int size(); //returns the number of nodes in the tree.
        void preorder(); //Prints the keys of the tree in a preorder traversal.
        void inorder(); //Prints the keys of the tree in an inorder traversal.
        void postorder(); //Prints the keys of the tree in a postorder traversal.
        void print2DUtil(treeNode<keytype, valuetype> *root, int space); //Utility to print the tree
        void print2D(treeNode<keytype, valuetype> *root);
        void print2DMain();
};

template <class keytype, class valuetype>
void RBTree<keytype, valuetype> :: print2DMain(){
    print2D(root);
}

template <class keytype, class valuetype>
void RBTree<keytype, valuetype> :: print2DUtil(treeNode<keytype, valuetype> *root, int space)  
{  
    // Base case  
    if (root == nil)  
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
    cout<<root->key<<","<<root->size<<"\n";  
  
    // Process left child  
    print2DUtil(root->left, space);  
}  

template <class keytype, class valuetype>
void RBTree<keytype, valuetype> :: print2D(treeNode<keytype, valuetype> *root)  
{  
    // Pass initial space count as 0  
    print2DUtil(root, 0);  
}  


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
    root->parent = nil;
}

template<class keytype, class valuetype>
RBTree<keytype, valuetype>::RBTree(keytype k[], valuetype V[], int s){
    treeSize = 0;
    nil = new treeNode<keytype, valuetype>();
    nil->color = 'b';
    nil->left = nullptr;
    nil->right = nullptr;
    nil->parent = nullptr;
    nil->size = 0;
    root = nil;
    root->parent = nil;
    for(int i = 0; i < s; i++){
        insert(k[i], V[i]);
    }
};

template <class keytype, class valuetype>
RBTree<keytype, valuetype> :: RBTree(const RBTree<keytype, valuetype> &RBTree){
    treeSize = 0;
    nil = new treeNode<keytype, valuetype>();
    nil->left = nullptr;
    nil->right = nullptr;
    nil->parent = nullptr;
    nil->size = 0;
    nil->color = 'b';
    root = new treeNode<keytype, valuetype>();
    root = copy(RBTree.root);
}

template <class keytype, class valuetype>
RBTree<keytype, valuetype>& RBTree<keytype, valuetype> :: operator=(const RBTree<keytype, valuetype>& other){
    if(this != &other){
        treeSize = 0;
        chop(root);
        nil = new treeNode<keytype, valuetype>();
        nil->left = nullptr;
        nil->right = nullptr;
        nil->parent = nullptr;
        nil->size = 0;
        nil->color = 'b';
        root = new treeNode<keytype, valuetype>();
        root = copy(other.root);
    }
    return *this;
}

template<class keytype, class valuetype>
valuetype * RBTree<keytype, valuetype>::search(keytype k){
    return &(TreeSearch(root, k)->value);
}

template<class keytype, class valuetype>
treeNode<keytype, valuetype> * RBTree<keytype, valuetype>::TreeSearch(treeNode<keytype, valuetype> *x, keytype k){
    if(x == nil || k == x->key) return x;
    if(k < x->key) return TreeSearch(x->left, k);
    else return TreeSearch(x->right, k);
}

template<class keytype, class valuetype>
void RBTree<keytype, valuetype>::insert(keytype k, valuetype v){
    treeNode<keytype, valuetype> *z = new treeNode<keytype, valuetype>(k, v);
    //cout << "Inserting K: " << k << ", v: " << v << endl;
    z->left = nil;
    z->right = nil;
    z->parent = nil;
    RBInsert(this, z);
    treeSize++;
    //cout << "Inserting: " << k << endl;
    //print2DMain();
    //for(int i = 0; i <= 100; i++) cout << "#";
};

template<class keytype, class valuetype>
void RBTree<keytype, valuetype>::RBInsert(RBTree<keytype, valuetype> *T, treeNode<keytype, valuetype> *z){
    treeNode<keytype, valuetype> *x, *y = new treeNode<keytype, valuetype>;
    y = T->nil;
    x = T->root;
    while(x != T->nil){
        y = x;
        x->size++;
        if(z->key < x->key) x = x->left;
        else x = x->right;
    }
    z->parent = y;
    if(y == T->nil) T->root = z;
    else if(z->key < y->key) y->left = z;
    else y->right = z;
    z->left = T->nil;
    z->right = T->nil;
    z->color = 'r';
    RBInsertFixUp(T, z);
}

template<class keytype, class valuetype>
void RBTree<keytype, valuetype>::RBInsertFixUp(RBTree<keytype, valuetype> *T, treeNode<keytype, valuetype> *z){
    while(z->parent->color == 'r'){
        treeNode<keytype, valuetype> *y = new treeNode<keytype, valuetype>;
        if(z->parent == z->parent->parent->left){
            y = z->parent->parent->right;
            if(y->color == 'r'){
                z->parent->color = 'b';
                y->color = 'b';
                z->parent->parent->color = 'r';
                z = z->parent->parent;
            }
            else{
                if(z == z->parent->right){
                    z = z->parent;
                    LeftRotate(T, z);
                }
                z->parent->color = 'b';
                z->parent->parent->color = 'r';
                RightRotate(T, z->parent->parent);
            }
        }
        else{
            y = z->parent->parent->left;
            if(y->color == 'r'){
                z->parent->color = 'b';
                y->color = 'b';
                z->parent->parent->color = 'r';
                z = z->parent->parent;
            }
            else{
                if(z == z->parent->left){
                    z = z->parent;
                    RightRotate(T, z);
                }
                z->parent->color = 'b';
                z->parent->parent->color = 'r';
                LeftRotate(T, z->parent->parent);
            }
        }
    }
    T->root->parent->size = 0;
    T->root->color = 'b';
}

template <class keytype, class valuetype>
void RBTree<keytype, valuetype>::LeftRotate(RBTree<keytype, valuetype> *T, treeNode<keytype, valuetype> *x){
    //cout << "Left Rotate being performed" << endl;
    treeNode<keytype, valuetype> *y = new treeNode<keytype, valuetype>;
    y = x->right;                               //set y
    x->right = y->left;                         //turn y's left subtree into x's right subtree
    if(y->left != T->nil) y->left->parent = x;
    y->parent = x->parent;                      //link x's parent to y
    if(x->parent == T->nil) T->root = y;
    else if(x == x->parent->left) x->parent->left = y;
    else x->parent->right = y;
    y->left = x;                                //put x on y's left
    x->parent = y;
    y->size = x->size;
    x->size = x->left->size + x->right->size + 1;
}

template <class keytype, class valuetype>
void RBTree<keytype, valuetype>::RightRotate(RBTree<keytype, valuetype> *T, treeNode<keytype, valuetype> *x){
    //cout << "Right Rotate being performed" << endl
    treeNode<keytype, valuetype> *y = new treeNode<keytype, valuetype>;
    y = x->left;                                //set y
    x->left = y->right;                         //turn y's right subtree into x's left subtree
    if(y->right != T->nil) y->right->parent = x;
    y->parent = x->parent;                      //link x's parent to y
    if(x->parent == T->nil) T->root = y;
    else if(x == x->parent->right) x->parent->right = y;
    else x->parent->left = y;
    y->right = x;                               //put x on y's right
    x->parent = y;
    y->size = x->size;
    x->size = x->right->size + x->left->size + 1;
}

template <class keytype, class valuetype>
int RBTree<keytype, valuetype>::remove(keytype k){
    treeNode<keytype, valuetype> *a = new treeNode<keytype, valuetype>;
    a = TreeSearch(root, k);
    if(a != NULL){
        RBDelete(this, a);
        //cout << "Deleting: " << k << endl;
        //print2DMain();
        return 1;
    }
    return 0;
}

template <class keytype, class valuetype>
void RBTree<keytype, valuetype>::RBDelete(RBTree<keytype, valuetype> *T, treeNode<keytype, valuetype> *z){
    treeNode<keytype, valuetype> *y = new treeNode<keytype, valuetype>;
    y = z;
    char yOriginalColor = y->color;
    //print2DMain();
    //cout << "Decrementing: " << endl;
    while(y->size != 0){
        //cout << "|| size: " << y->size << " key: " << y->key << "|| " << endl;
        y->size--;
        y = y->parent;
    }
    //print2DMain();
    y = z;
    treeNode<keytype, valuetype> *x = new treeNode<keytype, valuetype>;
    if(z->left == T->nil){
        x = z->right;
        RBTransplant(T, z, z->right);
    }
    else if(z->right == T->nil){
        x = z->left;
        RBTransplant(T, z, z->left);
    }
    else{
        y = TreeMinimum(z->right);
        treeNode<keytype, valuetype> *w = new treeNode<keytype, valuetype>;
        w = y->parent;
        while(w != z){
            w->size--;
            w = w->parent;
        }
        yOriginalColor = y->color;
        x = y->right;
        if(y->parent == z) x->parent = y;
        else{
            RBTransplant(T, y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }
        RBTransplant(T, z, y);
        y->left = z->left;
        y->left->parent = y;
        y->color = z->color;
    }
    if(yOriginalColor == 'b') RBDeleteFixUp(T, x);
    treeSize--;
    T->root->parent->size = 0;
}

template <class keytype, class valuetype>
void RBTree<keytype, valuetype>::RBTransplant(RBTree<keytype, valuetype> *T, treeNode<keytype, valuetype> *u, treeNode<keytype, valuetype> *v){
    sizeSwap(u, v);
    if(u->parent == T->nil) T->root = v;
    else if(u == u->parent->left) u->parent->left = v;
    else u->parent->right = v;
    v->parent = u->parent;
    T->root->parent->size = 0;
}

template <class keytype, class valuetype>
void RBTree<keytype, valuetype>::RBDeleteFixUp(RBTree<keytype, valuetype> *T, treeNode<keytype, valuetype> *x){
    while(x != T->root && x->color == 'b'){
        treeNode<keytype, valuetype> *w;
        if(x == x->parent->left){
            w = x->parent->right;
            if(w->color == 'r'){
                w->color = 'b';
                x->parent->color = 'r';
                LeftRotate(T, x->parent);
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
                    RightRotate(T, w);
                    w = x->parent->right;
                }
                w->color = x->parent->color;
                x->parent->color = 'b';
                w->right->color = 'b';
                LeftRotate(T, x->parent);
                x = T->root;
            }
        }
        else{
            w = x->parent->left;
            if(w->color == 'r'){
                w->color = 'b';
                x->parent->color = 'r';
                RightRotate(T, x->parent);
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
                    LeftRotate(T, w);
                    w = x->parent->left;
                }
                w->color = x->parent->color;
                x->parent->color = 'b';
                w->left->color = 'b';
                RightRotate(T, x->parent);
                x = T->root;
            }
        }
    }
    x->color = 'b';
}

template <class keytype, class valuetype>
treeNode<keytype, valuetype> * RBTree<keytype, valuetype>::TreeMaximum(treeNode<keytype, valuetype> *x){
    while(x->right != nil) x = x->right;
    return x;
}

template <class keytype, class valuetype>
treeNode<keytype, valuetype> * RBTree<keytype, valuetype>::TreeMinimum(treeNode<keytype, valuetype> *x){
    while(x->left != nil) x = x->left;
    return x;
}


template <class keytype, class valuetype>
int RBTree<keytype, valuetype>::rank(keytype k){
    return OSRank(this, TreeSearch(root, k));
}

template <class keytype, class valuetype>
int RBTree<keytype, valuetype>::OSRank(RBTree<keytype, valuetype> *T, treeNode<keytype, valuetype> *x){
    int r = x->left->size + 1;
    treeNode<keytype, valuetype> *y = x;
    while(y != T->root){
        if(y == y->parent->right){
            r = r + y->parent->left->size + 1;
        }
        y = y->parent;
    }
    return r;
}

template <class keytype, class valuetype>
keytype RBTree<keytype, valuetype>::select(int pos){
    if(OSSelect(root, pos) != nullptr) return (OSSelect(root, pos))->key;
    else return 0;
}

template <class keytype, class valuetype>
treeNode<keytype, valuetype> * RBTree<keytype, valuetype>::OSSelect(treeNode<keytype, valuetype> *x, int i){
    while(x->size != 0){
        int r = x->left->size + 1;
        //cout << "i: " << i << " == r: " << r << endl;
        if(i == r) return x;
        else if (i < r) return OSSelect(x->left, i);
        else{

            return OSSelect(x->right, i - r);
        }
    }
    return x;
}

template <class keytype, class valuetype>
keytype * RBTree<keytype, valuetype>::successor(keytype k){
    treeNode<keytype, valuetype> *z = TreeMaximum(root);
    if(z->key == k) return NULL;
    treeNode<keytype, valuetype> *a = new treeNode<keytype, valuetype>;
    a = TreeSearch(root, k);
    if(a->size == 0){
        return NULL;
    }
    keytype *succKey = &(TreeSuccessor(a))->key;
    return succKey;
}

template <class keytype, class valuetype>
treeNode<keytype, valuetype> * RBTree<keytype, valuetype>::TreeSuccessor(treeNode<keytype, valuetype> *x){
    if(x->right != nil) return TreeMinimum(x->right);
    treeNode<keytype, valuetype> *y = x->parent;
    while(y != nil && x == y->right){
        x = y;
        y = y->parent;
    }
    return y;
}

template <class keytype, class valuetype>
keytype * RBTree<keytype, valuetype>::predecessor(keytype k){
    treeNode<keytype, valuetype> *z = TreeMinimum(root);
    if(z->key == k) return NULL;
    treeNode<keytype, valuetype> *a = new treeNode<keytype, valuetype>;
    a = TreeSearch(root, k);
    if(a->size == 0){
        return NULL;
    }
    keytype *predKey = &(TreePredecessor(a))->key;
    return predKey;
}

template <class keytype, class valuetype>
treeNode<keytype, valuetype> * RBTree<keytype, valuetype>::TreePredecessor(treeNode<keytype, valuetype> *x){
    if(x->left != nil) return TreeMaximum(x->left);
    treeNode<keytype, valuetype> *y = x->parent;
    while(y != nil && x == y->left){
        x = y;
        y = y->parent;
    }
    return y;
}

template <class keytype, class valuetype>
int RBTree<keytype, valuetype>::size(){
    return treeSize;
}

template <class keytype, class valuetype>
void RBTree<keytype, valuetype>::preorder(){
    PreOrderTreeWalk(root);
}

template <class keytype, class valuetype>
void RBTree<keytype, valuetype>::PreOrderTreeWalk(treeNode<keytype, valuetype> *x){
    if(x != nil){
        cout << x->key << " ";
        PreOrderTreeWalk(x->left);
        PreOrderTreeWalk(x->right);
    }
}

template <class keytype, class valuetype>
void RBTree<keytype, valuetype>::inorder(){
    InOrderTreeWalk(root);
}

template <class keytype, class valuetype>
void RBTree<keytype, valuetype>::InOrderTreeWalk(treeNode<keytype, valuetype> *x){
    if(x != nil){
        InOrderTreeWalk(x->left);
        cout << x->key << " ";
        InOrderTreeWalk(x->right);
    }
}

template <class keytype, class valuetype>
void RBTree<keytype, valuetype>::postorder(){
    PostOrderTreeWalk(root);
}

template <class keytype, class valuetype>
void RBTree<keytype, valuetype>::PostOrderTreeWalk(treeNode<keytype, valuetype> *x){
    if(x != nil){
        PostOrderTreeWalk(x->left);
        PostOrderTreeWalk(x->right);
        cout << x->key << " ";
    }
}

template <class keytype, class valuetype>
treeNode<keytype, valuetype> * RBTree<keytype, valuetype> :: copy(treeNode <keytype, valuetype> *root){
    treeNode<keytype, valuetype> *newRoot;
    if(root->size != 0){
        newRoot = new treeNode<keytype, valuetype>(root->key, root->value);
        newRoot->color = root->color;
        newRoot->left  = copy(root->left); 
        newRoot->right = copy(root->right); 
    } else return nil;
    return newRoot; 
}

template <class keytype, class valuetype>
void RBTree<keytype, valuetype> :: chop(treeNode <keytype, valuetype> *n){
    if(n){
        chop(n->left);
        chop(n->right);
        delete n;
    }
}

template <class keytype, class valuetype>
void RBTree<keytype, valuetype> :: sizeSwap(treeNode <keytype, valuetype> *a, treeNode <keytype, valuetype> *b){
    int tempSize = a->size;
    a->size = b->size;
    b->size = tempSize;
}