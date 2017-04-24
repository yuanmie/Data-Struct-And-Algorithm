template<typename T>
class AVL{
public:
  AVL():root(nullptr){ }
  ~AVL(){
    //release all resource
  }
private:
  struct Node{
    T key;
    Node* left;
    Node* right;
    int height;
    
    public Node(T k):key(k), left(nullptr), right(nullptr), height(0){ }
    public Node(T k, Node* l, Node* r):key(k), left(l), right(r),height(0){ }
  }* root;
  
  public int height(Node* node){
    if(node != nullptr){ return node->heigth; }
    return 0;
  }
};