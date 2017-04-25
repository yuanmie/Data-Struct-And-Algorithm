#include <functional>
#include <algorithm>
#include <iostream>
#include <cassert>
using namespace std;

template<typename T, typename Comp = std::less<T> >
class AVL{
private:
  struct Node{
    T key;
    Node* left;
    Node* right;
    int height;
    
    Node(T k):key(k), left(nullptr), right(nullptr), height(0){ }
    Node(T k, Node* l, Node* r):key(k), left(l), right(r),height(0){ }
  }* root;
public:
  AVL():root(nullptr){ }
  ~AVL(){
    //release all resource
  }
  
  void insert(const T& key){
    insert(root, key);
  }
  
  void erase(const T& key){
    Node* x = find(key);
    if(x == nullptr ){ return; }
    root = erase(root, x);
  }
  
  Node* find(const T& key){
      return _find(key);
  }
  
  void TreeOrder(){
    TreeOrder(root);
    printf("\n");
  }

  
  int height(){
    return height(root);
  }
private:

  Comp less;
  
  int height(Node* node){
    if(node != nullptr){ return node->height; }
    return 0;
  }
  Node* _find(const T& key){
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
  
  void TreeOrder(Node* node)
  {
    if(node == nullptr) {return;}
    printf("\t%d", node->key);
    TreeOrder(node->left);
    TreeOrder(node->right);
  }
  //first case:LL
  Node* leftleftRotate(Node* x){
    Node* l = x->left;
    x->left = l->right;
    l->right = x;
    
    x->height = std::max(height(x->left), height(x->right)) + 1;
    l->height = std::max(height(l->left), x->height) + 1;
    
    return l;
  }
  
  //second case:RR
  Node* rightrightRotate(Node* x){
    Node* r = x->right;
    x->right = r->left;
    r->left = x;
    
    x->height = std::max(height(x->left), height(x->right)) + 1;
    r->height = std::max(x->height, height(r->right)) + 1;
    
    return r;
  }
  
  //third case:LR
  Node* leftrightRotate(Node* x){
    x->left = rightrightRotate(x->left);
    return leftleftRotate(x);
  }
  
  //fourth case:RL
  Node* rightleftRotate(Node* x){
    x->right = leftleftRotate(x->right);
    return rightrightRotate(x);
  }
  
  Node* insert(Node*& treeRoot, const T& key){
    if(treeRoot == nullptr){
      Node* newNode = new Node(key);
      treeRoot = newNode;
      return treeRoot;
    }else if(less(key, treeRoot->key)){
      treeRoot->left = insert(treeRoot->left, key);
      if(height(treeRoot->left) - height(treeRoot->right) == 2){
        if(less(key, treeRoot->left->key)){
          leftleftRotate(treeRoot);
        }else{
          leftrightRotate(treeRoot);
        }
      }
    //  balance(treeRoot);
    }else if(less(treeRoot->key, key)){
      treeRoot->right = insert(treeRoot->right, key);
      if(height(treeRoot->right) - height(treeRoot->left) == 2){
        if(less(key, treeRoot->left->key)){
          rightleftRotate(treeRoot);
        }else{
          rightrightRotate(treeRoot);
        }
      }
      //balance(treeRoot);
    }else{
      
    }
    treeRoot->height = std::max(height(treeRoot->left), height(treeRoot->right)) + 1;
  }
  
  Node* erase(Node* treeRoot, Node* x){
    if(treeRoot == nullptr || x == nullptr){
      return nullptr;
    }
    
    if(less(x->key, treeRoot->key)){
        treeRoot->left = erase(treeRoot->left, x);
    }else if(less(treeRoot->key, x->key)){
        treeRoot->right = erase(treeRoot->right, x);
    }else{
      
        if( (treeRoot->left != nullptr) && (treeRoot->right != nullptr) ){
          if(height(treeRoot->left) > height(treeRoot->right)){
            Node* subtree_max = subtreeMax(treeRoot->left);
            treeRoot->key = subtree_max->key;
            treeRoot->left = erase(treeRoot->left, subtree_max);
          }else{
            Node* subtree_min = subtreeMin(treeRoot->right);
            treeRoot->key = subtree_min->key;
            treeRoot->right = erase(treeRoot->right, subtree_min);
          }
        }else{
          Node* tmp = treeRoot;
          treeRoot = (treeRoot->left == nullptr) ? treeRoot->right : treeRoot->left;
          delete tmp;
        }
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
};





static int arr[]= {3,2,1,4,5,6,7,16,15,14,13,12,11,10,8,9};
#define TBL_SIZE(a) ( (sizeof(a)) / (sizeof(a[0])) )

int main()
{
    int i,ilen;
    AVL<int>* tree=new AVL<int>();

    cout << "== add: ";
    ilen = TBL_SIZE(arr);
    for(i=0; i<ilen; i++)
    {
        cout << arr[i] <<" ";
        tree->insert(arr[i]);
        cout << "\n== order: " ;
        tree->TreeOrder();
    }


    i = 8;
    cout << "\n== erase root: " << i;
    tree->erase(i);

    cout << "\n== height: " << tree->height() ;
    cout << "\n== order: " ;
    tree->TreeOrder();
  

  

    return 0;
}