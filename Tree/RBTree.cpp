enum RBCOLOR{RED, BLACK};

template<typename T>
class RBTree{
private:
  struct Node{
    Node* left;
    Node* right;
    Node* parent;
    RBCOLOR color;
    T key;
    Node(const T& k):key(k), left(null), right(null)
                    , parent(null), color(BLACk){ }
                    
    Node(const T& k, Node* l, Node* r, Node* p, RBCOLOR c)
        :key(k), left(l), right(r), parent(p), color(c){}          
  }*root;
  
  void leftRotate(Node *x){
      Node* y = x->right;
      if( y != nullptr){
          x->right = y->left;
          if(y->left != nullptr){ y->left->parent = x;}
          y->parent = x->parent;
      }

      if( x->parent == nullptr) { root = y;}
      else if( x == x->parent->left ) { x->parent->left = y;}
      else { x->parent->right = y;}

      x->parent = y;
      if(y != nullptr ) { y->left = x;}
  }

  void rightRotate(Node* x){
      Node *y = x->left;
      if( y != nullptr ){
          x->left = y->right;
          if ( y->right != nullptr ) {
              y->right->parent = x;
          }
          y->parent = x->parent;
      }

      if( x->parent == nullptr) { root = y;}
      else if( x == x->parent->left ) { x->parent->left = y;}
      else { x->parent->right = y;}

      x->parent = y;
      if(y != nullptr ) { y->right = x;}
  }
  
  void replace(Node* u, Node* v){
    if ( u->parent == nullptr ) { root = v;}
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

void releaseTree(Node* node){
  if(node == NULL) return;
  releaseTree(node->left);
  releaseTree(node->right);
  delete node;
}

void insertFixUp(Node* n){
  Node* current = n;
  //如果父节点不为空，且父节点的颜色为红色
  while(current->parent != nullptr && current->parent->color == RED){
    Node* parent = n->parent;
    Node* grandparent = n->parent->parent;
    
    //父节点是祖父节点的左孩子
    if(parent == grandparent->left){
      //case 1:uncle 节点是红色
      Node* uncle = grandparent->right;
      if(uncle != nullptr && uncle->color == RED){
        uncle->color = BLACK;
        parent->color = BLACK;
        grandparent->color = RED;
        current = grandparent;
        continue;
      }
    }
  }
  
  //此节点为父节点，将颜色变为黑色
  n->color = BLACK;
  
}
public:
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

      newNode->color = RED;
      insertFixUp(newNode);
  }
};