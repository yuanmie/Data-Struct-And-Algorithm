enum RBCOLOR{RED, BLACK};
#include <functional>
#include <cassert>
template<typename T, typename Comp = std::less<T> >
class RBTree{
private:
    Comp less;
  struct Node{
    Node* left;
    Node* right;
    Node* parent;
    RBCOLOR color;
    T key;
    Node(const T& k):key(k), left(nullptr), right(nullptr)
                    , parent(nullptr), color(BLACK){ }

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

    //父节点是祖父节点的左孩子
    if(current->parent == current->parent->parent->left){
      //case 1:uncle 节点是红色
      Node* uncle = current->parent->parent->right;
      if(uncle != nullptr && uncle->color == RED){
        uncle->color = BLACK;
        current->parent->color = BLACK;
        current->parent->parent->color = RED;
        current = current->parent->parent;
        continue;
      }

      //case 2: uncle 节点是黑色，且当前节点是右孩子
      if(current == current->parent->right){
          current = current->parent;
          leftRotate(current);
      }

      //case 3: uncle 节点是黑色， 当前节点是左孩子
      current->parent->color = BLACK;
      current->parent->parent->color = RED;
      rightRotate(current->parent->parent);
  }else{
       Node* uncle = current->parent->parent->left;
      //case 1:uncle 节点是红色
      if(uncle != nullptr && uncle->color == RED){
          uncle->color = BLACK;
          current->parent->color = BLACK;
          current->parent->parent->color = RED;
          current = current->parent->parent;
          continue;
      }

      //case 2:
      if(current->parent->left == current){
         current = current->parent;
          rightRotate(current);
      }

      //case 3:
      current->parent->color = BLACK;
      current->parent->parent->color = RED;
      leftRotate(current->parent->parent);
  }
  }

  //此节点为父节点，将颜色变为黑色
  root->color = BLACK;

}

void RB_DELETE_FIXUP(Node* x ){
    while (x != root && (x == nullptr || x->color == BLACK)){
        if (x == x->parent->left){
                Node* w = x->parent->right;
                if ( w != nullptr && w->color == RED){
                    w->color = BLACK;
                    x->parent->color = RED;
                    leftRotate(x->parent);
                    w = x->parent->right;
                }

            if (w != nullptr && (w->left == nullptr || w->left->color == BLACK)
                && (w->right == nullptr || w->right->color == BLACK)){
                w->color = RED;
                x = x->parent;
            }else{
                 if(w != nullptr && (w->right == nullptr || w->right->color == BLACK)){
                     w->left->color = BLACK;
                     w->color = RED;
                     rightRotate(w);
                     w = x->parent->right;
                 }

                 w->color = x->parent->color;
                 x->parent->color = BLACK;
                 w->right->color = BLACK;
                 leftRotate(x->parent);
                 x = root;
            }
        }else{
            Node* w = x->parent->left;
            if (w != nullptr && w->color == RED){
                w->color = BLACK;
                x->parent->color = RED;
                rightRotate(x->parent);
                w = x->parent->left;
            }

            if (w != nullptr && (w->left == nullptr || w->left->color == BLACK) && (w->right == nullptr || w->right->color == BLACK)){
                w->color = RED;
                x = x->parent;
            }else{
             if(w != nullptr && (w->left == nullptr || w->left->color == BLACK)){
                 w->right->color = BLACK;
                 w->color = RED;
                 leftRotate(w);
                 w = x->parent->left;
             }

             w->color = x->parent->color;
             x->parent->color = BLACK;
             w->left->color = BLACK;
             rightRotate(x->parent);
             x = root;
            }
        }
    }
    if(x != nullptr ){ x->color = BLACK; }

}
public:
    RBTree():root(nullptr){}

    void insert(const T& key){
      Node* current = root;
      Node* p = nullptr;

      while( current != nullptr ){
          p = current;
          // key less than curent's key
          if( less(key, current->key) ){
              current = current->left;
          }else{
              current = current->right;
          }
      }

      Node* newNode = new Node(key);
      newNode->parent = p;

      if( p == nullptr ){
          root = newNode;
      }else if( less(key, p->key) ){
          p->left = newNode;
      }else{
          p->right = newNode;
      }

      newNode->color = RED;
      insertFixUp(newNode);
  }

  void erase(const T& key){
      Node* x = find(key);
      RBCOLOR originColor = x->color;
      Node* fixNode = nullptr;
      if(x != nullptr){

        if(x->left == nullptr){
            fixNode = x->right;
          replace(x, x->right);
        }else if(x->right == nullptr){
            fixNode = x->left;
          replace(x, x->left);
        }else{
          Node* z = subtreeMin(x->right);
          fixNode = z->right;
          originColor = z->color;
          if(z->parent != x){
            replace(z, z->right);
            z->right = x->right;
            z->right->parent = z;
          }
          replace(x, z);
          z->left = x->left;
          z->left->parent = z;

          z->color = x->color;
        }
      }

      if (originColor == BLACK){
          RB_DELETE_FIXUP(fixNode);
      }
  }

  Node* find(const T& key){
      Node* current = root;
      while( current != nullptr){
          if (less(key, current->key)){
              current = current->left;
          }else if(less(current->key, key)){
              current = current->right;
          }else{
              return current;
          }
      }
      return nullptr;
  }

  void TreeOrder(){
    TreeOrder(root);
    printf("\n");
  }
  void TreeOrder(Node* node)
  {
      if(node == NULL) {return;}
    printf("\t%d(%d)", node->key, node->color);
      TreeOrder(node->left);
      TreeOrder(node->right);
  }
};

int main(){
    RBTree<int> s;
    s.insert(11);
    s.TreeOrder();
    s.insert(14);
    s.TreeOrder();
    s.insert(15);
    s.TreeOrder();
    s.insert(2);
    s.TreeOrder();
    s.insert(1);
    s.TreeOrder();
    s.insert(8);
    s.TreeOrder();
    s.insert(5);
    s.TreeOrder();
    s.insert(4);
    s.TreeOrder();
    s.insert(1);
    s.TreeOrder();
    s.erase(5);
    s.TreeOrder();

    return 0;
}
