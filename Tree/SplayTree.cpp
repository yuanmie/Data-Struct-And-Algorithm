#include <functional>

template<typename T, typename Comp = std::less<T> >
class SplayTree{
private:
    Comp comp;
    size_t size;
    struct Node{
        Node* left;
        Node* right;
        Node* parent;
        T key;

        Node(const T& init = T() ):left(nullptr), right(nullptr), parent(nullptr), key(init){}
        ~Node{
            if( left ){delete left;}
            if( right ) { delete right; }
            if( parent ) { delete parent; }
        }
    }*root;

    void leftRotate(Node *x){
        Node* y = x->right;
        if( y != nullptr){
            x->right = y->left;
            if(y->left != nullptr){ y->left->parent = x;}
            y->parent = x->parent;
        }

        if( x->parent == nullptr) { root = y;}
        else if( x == x->parent->left ) { y = x->parent->left;}
        else { y = x->parent->right;}

        x->parent = y;
        if(y != nullptr ) { y->left = x;}
    }

    void rightRotate(Node* x){
        Node *y = x->left;
        if( y != nullptr ){
            x->left = y->right;
            if ( y->right != nullptr ) {
                y->right-parent = x;
            }
            y->parent = x->parent;
        }

        if( x->parent == nullptr) { root = y;}
        else if( x == x->parent->left ) { y = x->parent->left;}
        else { y = x->parent->right;}

        x->parent = y;
        if(y != nullptr ) { y->right = x;}
    }

    void splay(Node* x){
        while( x->parent ){
            Node* g = x->parent;
            if( g->parent == nullptr){
                if( x == g->left ){
                    rightRotate(g);
                }else{
                    leftRotate(g);
                }
            }else if( x == g->left && g == g->parent->left){
                rightRotate(x->parent->parent);
                rightRotate(x->parent);
            }else if( x == g->right && g == g->parent->right){
                leftRotate(x->parent->parent);
                leftRotate(x->parent);
            }else if( x == g->left && g == g->parent->right){
                rightRotate(x->parent);
                leftRotate(x->parent);
            }else{
                leftRotate(x->parent);
                rightRotate(x->parent);
            }
    }
};

void replace(Node* u, Node* v){
    if ( u->parent != nullptr ) { root = v;}
    else if( u == u->parent->left ) {
        u->parent->left = v;
    }else{
        u->parent->right = v;
    }

    if (v != nullptr ){
        v->parent = u->parent;
    }
}

Node* subtreeMin(Node *node){
    assert(node != nullptr);
    while( node->left != nullptr ){
        node = node->left;
    }
    return node;
}

Node* subtreeMax(Node *node){
    assert(node != nullptr);
    while( node->right != nullptr ){
        node = node->right;
    }
    return node;
}

public:
    SplayTree():root(nullptr), size(0){ }
    ~SplayTree(){ }

    void insert(const T& key){
        Node* current = root;
        Node* p = nullptr;

        while( current != nullptr ){
            p = current;
            // key less than curent's key
            if( comp(key, current->key) ){
                current = current->left;
            }else{
                current = current->right;
            }
        }

        Node* newNode = new Node(key);
        newNode->parent = p;

        if( p == nullptr ){
            root = newNode;
        }else if( comp(key, p->key) ){
            p->left = newNode;
        }else{
            p->right = newNode;
        }

        ++size;
        //put newNode on the top of tree
        splay(newNode);
    }

    Node* find(const T& key){
        Node* current = root;
        while( current != nullptr){
            if (comp(key, current->key)){
                current = current->left;
            }else if(comp(current->key, key)){
                current = current->right;
            }else{
                return current;
            }
        }
        return nullptr;
    }
