#include <string>
#include <cstdio>
#include <vector>
#include <iostream>
#include <utility>
#include <queue>
#include <cassert>

using std::cout;
using std::string;
using std::vector;
using std::endl;

struct Node{
    char content;
    Node* left;
    Node* right;
    int freq;
    Node(char c, int f):content(c), freq(f),left(NULL), right(NULL){

    }

    Node(char c, int f, Node* l, Node* r):content(c), freq(f),left(l), right(r){
    }

    bool isLeaf(){
        return left == NULL && right == NULL;
    }
};

class Huffman{
public:
    Huffman(string text):key(text){
        int len = key.length();
        int R = 256;
        char frequent[R] = {0};
        for(int i = 0; i < len; i++){
            ++frequent[key[i]];
        }

        auto comp = [](const Node* one, const Node* other){
            return one->freq > other->freq;
        };

        std::priority_queue<Node*, vector<Node*>, decltype(comp)> pq(comp);
        bool view[R] = {0};
        for(int i = 0; i < len; i++){
            if(view[key[i]]) continue;
            view[key[i]] = true;
            Node* newNode = new Node(key[i], frequent[key[i]], NULL, NULL);
            pq.push(newNode);
        }

        while(pq.size() > 1){

            Node* left = pq.top();
            pq.pop();

            Node *right = pq.top();
            pq.pop();

            Node *parent = new Node('0', left->freq + right->freq, left, right);
            pq.push(parent);
        }

        root = pq.top();
        pq.pop();

        debug();
        string translate[256];
        buildTransTable(translate, root, "");

        for(int i = 0; i < len; i++){
            cout << translate[key[i]] << endl;
        }
    }

    void buildTransTable(string* trans, Node* node, string result){
        assert(node != NULL);
        if(node->isLeaf()){
            cout << node->content << "   " << result << endl;
            trans[node->content] = result;
            return;
         }
         buildTransTable(trans, node->left, result + "0");
         buildTransTable(trans, node->right, result + "1");
    }

    void debug(){
        mydisplay(root);
    }

    void mydisplay(Node* node){
        if(node == NULL) return;
        mydisplay(node->left);
        cout <<node->freq << " ---- " << node->content << endl;

        mydisplay(node->right);
    }


private:


    Node* root;
    string key;
};

int main(){
    Huffman huff("abca");
    Huffman h("it was the best fo times it was the worst of times\n");
    return 0;
}
