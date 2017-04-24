/*
splay tree:伸展树
时间复杂度：
均摊成本为O(logN);
*/
#include <functional>
#include <cassert>
#include <cstdio>

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

  void splay(Node* x){
      while( x->parent != nullptr){
          if( x->parent->parent == nullptr){
              if( x == x->parent->left ){
                  rightRotate(x->parent);
              }else{
                  leftRotate(x->parent);
              }
          }else if( x == x->parent->left && x->parent == x->parent->parent->left){
              rightRotate(x->parent->parent);
              rightRotate(x->parent);
          }else if( x == x->parent->right && x->parent == x->parent->parent->right){
              leftRotate(x->parent->parent);
              leftRotate(x->parent);
          }else if( x == x->parent->left && x->parent == x->parent->parent->right){
              rightRotate(x->parent);
              leftRotate(x->parent);
          }else{
              leftRotate(x->parent);
              rightRotate(x->parent);
          }
           
      }
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

public:
    SplayTree():root(nullptr), size(0){ }
    ~SplayTree(){
      releaseTree(root);
    }

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

    void erase(const T& key){
      Node* x = find(key);
      if(x != nullptr){
        splay(x);
        
        if(x->left == nullptr){
          replace(x, x->right);
        }else if(x->right == nullptr){
          replace(x, x->left);
        }else{
          Node* z = subtreeMin(x->right);
          if(z->parent != x){
            replace(z, z->right);
            z->right = x->right;
            z->right->parent = z;
          }
          replace(x, z);
          z->left = x->left;
          z->left->parent = z;
          
        }
        delete x;
        --size;
      }
  }
  
    void TreeOrder(){
      TreeOrder(root);
      printf("\n");
    }
    void TreeOrder(Node* node)
    {
    	if(node == NULL) {return;}
      printf("\t%d", node->key);
    	TreeOrder(node->left);
    	TreeOrder(node->right);
    }
};

int main()
{
  SplayTree<int> st;
  st.insert(5);
  st.TreeOrder();
  st.insert( 20);
  st.TreeOrder();
  st.insert( 15);
  st.TreeOrder();
  st.insert( 30);
  st.TreeOrder();
  st.insert( 25);
  st.TreeOrder();
  st.insert( 35);
  st.TreeOrder();

  st.erase(20);
  printf("\nafter delete 20:\n");
  st.TreeOrder();
  return 0;
}