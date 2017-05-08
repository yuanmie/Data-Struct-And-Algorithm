/*
red-black tree, 中文为红黑树, 一种平衡二叉搜索树
时间复杂度：
insert操作：log(n)
delete操作： log(n)
find操作：log(n)
参考算法导论实现， 没有用哨兵节点
*/
#include <functional>
#include <cassert>

//定义红黑树节点的2中状态
enum RBCOLOR{RED, BLACK};

template<typename T, typename Comp = std::less<T> >
class RBTree{
private:
    Comp less; //比较函数，默认是小于
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

//左旋操作
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

//右旋操作
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

//替换操作，用v取代u
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
//查找子树中最小的节点
Node* subtreeMin(Node *node){
  assert(node != nullptr);
  while( node->left != nullptr ){
      node = node->left;
  }
  return node;
}

//查找子树中最大的节点
Node* subtreeMax(Node *node){
  assert(node != nullptr);
  while( node->right != nullptr ){
      node = node->right;
  }
  return node;
}

//释放树占用的资源
void releaseTree(Node* node){
  if(node == NULL) return;
  releaseTree(node->left);
  releaseTree(node->right);
  delete node;
}

//insert操作所需的平衡操作
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

       //case 2: uncle 节点是黑色，且当前节点是左孩子
      if(current->parent->left == current){
         current = current->parent;
          rightRotate(current);
      }

     //case 3: uncle 节点是黑色， 当前节点是右孩子
      current->parent->color = BLACK;
      current->parent->parent->color = RED;
      leftRotate(current->parent->parent);
  }
  }

  //此节点为父节点，将颜色变为黑色
  root->color = BLACK;

}

/*删除操作所需的平衡操作
比较麻烦的情况是x为空的情况，故需要做一些处理。在下面的注释中说明
*/
void RB_DELETE_FIXUP(Node* x, Node* x_parent, bool isLeftChild){
    while (x != root && (x == nullptr || x->color == BLACK)){
        //判断x是否为左孩子节点
        if(x != nullptr){
            isLeftChild = (x == x->parent->left);
        }
        //x为左孩子
        if (isLeftChild){
            Node* w = nullptr;
            //设置x_parent 的值
            x_parent = (x == nullptr ) ? x_parent : x->parent;
            //取得uncle节点
                if(x != nullptr ){
                    w = x->parent->right;
                }else{
                    w = x_parent->right;
                }
                //case 1：uncle节点的颜色为红色
                if ( w != nullptr && w->color == RED){
                    w->color = BLACK;
                    x_parent->color = RED;
                    leftRotate(x_parent);
                    //旋转可能改变x的值，需要更新一下
                    x_parent = (x == nullptr ) ? x_parent : x->parent;
                    w = x_parent->right;
                }

                //case 2： uncle节点的左孩子节点和右孩子节点为黑色（空节点的颜色为黑色）
            if (w != nullptr && (w->left == nullptr || w->left->color == BLACK)
                && (w->right == nullptr || w->right->color == BLACK)){
                w->color = RED;
                x_parent = (x == nullptr ) ? x_parent : x->parent;
                x = x_parent;
            }else{
                //case 3: uncle节点的右孩子节点的颜色为黑色
                 if(w != nullptr && (w->right == nullptr || w->right->color == BLACK)){
                     if (w->left != nullptr ) w->left->color = BLACK;
                     w->color = RED;
                     rightRotate(w);
                     x_parent = (x == nullptr ) ? x_parent : x->parent;
                     w = x_parent->right;
                 }
                 //case 4:uncle节点是黑色的， 且w的右孩子节点为红色的
                 x_parent = (x == nullptr ) ? x_parent : x->parent;
                 if (w != nullptr ) {
                     w->color = x_parent->color;
                     if(w->right != nullptr ) w->right->color = BLACK;
                 }
                 x_parent->color = BLACK;

                 leftRotate(x_parent);
                 x = root;
            }
        }else{
            //x为右孩子节点。交换上面代码的left和right即可
            Node* w = nullptr;
            x_parent = (x == nullptr ) ? x_parent : x->parent;
                if(x != nullptr ){
                    w = x->parent->left;
                }else{
                    w = x_parent->left;
                }
                //case 1：uncle节点的颜色为红色
                if ( w != nullptr && w->color == RED){
                    w->color = BLACK;
                    x_parent->color = RED;
                    rightRotate(x_parent);
                    //旋转可能改变x的值，需要更新一下
                    x_parent = (x == nullptr ) ? x_parent : x->parent;
                    w = x_parent->left;
                }

//case 2： uncle节点的左孩子节点和右孩子节点为黑色（空节点的颜色为黑色）
            if (w != nullptr && (w->left == nullptr || w->left->color == BLACK)
                && (w->right == nullptr || w->right->color == BLACK)){
                w->color = RED;
                x_parent = (x == nullptr ) ? x_parent : x->parent;
                x = x_parent;
            }else{
                //case 3: uncle节点的左孩子节点的颜色为黑色
                 if(w != nullptr && (w->left == nullptr || w->left->color == BLACK)){
                     if (w->right != nullptr ) w->right->color = BLACK;
                     w->color = RED;
                     leftRotate(w);
                     x_parent = (x == nullptr ) ? x_parent : x->parent;
                     w = x_parent->left;
                 }
                 //case 4:uncle节点是黑色的， 且w的右孩子节点为红色的
                 x_parent = (x == nullptr ) ? x_parent : x->parent;
                 if (w != nullptr ) {
                     w->color = x_parent->color;
                     if(w->left != nullptr ) w->left->color = BLACK;
                 }
                 x_parent->color = BLACK;

                 rightRotate(x_parent);
                 x = root;
            }
        }
    }
    if(x != nullptr ){ x->color = BLACK; }

}
public:
    RBTree():root(nullptr){}

    //插入操作
    void insert(const T& key){
      Node* current = root;
      Node* p = nullptr;

      while( current != nullptr ){
          p = current;
          // 插入的键值比当前节点小，进入左子树
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

//删除操作
  void erase(const T& key){
      Node* x = find(key);
      Node* x_parent = nullptr;
      RBCOLOR originColor = RED;
      Node* fixNode = nullptr;
      bool isLeftChild  = true;
      if(x != nullptr){
          originColor = x->color;
        if(x->left == nullptr){
            x_parent = x->parent; //处理孩子节点为nullptr的情况
            fixNode = x->right;

            //因为没有使用哨兵节点，需要对fixnode为空的情况进行处理
            if(x_parent == nullptr ){
                root = fixNode;
            }else{
                if(x_parent->left == x) {
                    isLeftChild = true;
                }
                else {
                    isLeftChild = false;
                }
            }
          replace(x, x->right);
        }else if(x->right == nullptr){
            x_parent = x->parent; //处理孩子节点为nullptr的情况
            fixNode = x->left;

            //因为没有使用哨兵节点，需要对fixnode为空的情况进行处理
            if(x_parent == nullptr ){
                root = fixNode;
            }else{
                if(x_parent->left == x) {
                    isLeftChild = true;
                }
                else {
                    isLeftChild = false;
                }
            }

          replace(x, x->left);
        }else{
          Node* z = subtreeMin(x->right);
          fixNode = z->right;
          x_parent = z->parent; //处理孩子节点为nullptr的情况

          //因为没有使用哨兵节点，需要对fixnode为空的情况进行处理
          if(x_parent == nullptr ){
              root = fixNode;
          }else{
              if(x_parent->left == z) {
                  isLeftChild = true;

              }
              else {
                  isLeftChild = false;

              }
          }
          originColor = z->color;
          if(z->parent != x){
            replace(z, z->right);
            z->right = x->right;
            z->right->parent = z;
          }
          //特殊情况，fixNode 为空，x_parent指向被删除节点
          if(z->parent == x) {
              x_parent = z;
          }
          replace(x, z);
          z->left = x->left;
          z->left->parent = z;

          z->color = x->color;
        }

        //释放被删除节点的资源
        delete x;
      }

      if (originColor == BLACK){
          RB_DELETE_FIXUP(fixNode, x_parent, isLeftChild);
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
    // s.erase(11);
    // s.TreeOrder();
    s.erase(1);
    s.TreeOrder();
    s.erase(1);
    s.TreeOrder();
    s.erase(4);
    s.TreeOrder();
    s.erase(8);
    s.TreeOrder();
    s.erase(11);
    s.TreeOrder();
    s.erase(14);
    s.TreeOrder();
    s.erase(5);
    s.TreeOrder();
    s.erase(15);
    s.TreeOrder();
    s.erase(2);
    s.TreeOrder();
    return 0;
}
