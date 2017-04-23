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


        translate = new string[R];
        buildTransTable(translate, root, "");
    }

    ~Huffman(){
        //release huffman tree
        releaseTree(root);
        delete[] translate;
    }



    string compress(){
        string result("");
        int len = key.length();
        for(int i = 0; i < len; i++){
            result.append(translate[key[i]]);
        }
        return result;
    }

    string expand(string code){
        string result("");
        int codeLen = code.length();
        int index = 0;
        Node* node = root;
        while(index < codeLen){
            if(code[index] == '0'){
                node = node->left;
            }else if(code[index] == '1'){
                node = node->right;
            }else{
                //error
                cout << "error" << "\n";
            }
            if(node->isLeaf()){
                result.append(string(1,node->content));
                node = root;
            }
            ++index;
        }
        return result;
    }


private:
    void buildTransTable(string* trans, Node* node, string result){
        assert(node != NULL);
        if(node->isLeaf()){
            trans[node->content] = result;
            return;
         }
         buildTransTable(trans, node->left, result + "0");
         buildTransTable(trans, node->right, result + "1");
    }

    void releaseTree(Node* node){
        if(node == NULL) return;
        releaseTree(node->left);
        releaseTree(node->right);
        delete node;
    }

    string *translate;
    Node* root;
    string key;
};

int main(){
    Huffman huff("abca");
    cout << "the key is: abca" << endl;
    string code = huff.compress();
    cout << "after compress, the code is: " << code << endl;
    string key = huff.expand(code);
    cout <<"after express, the key is: " << key << endl;
    Huffman h("it was the best of times it was the worst of times\n");
    cout << "the key is: it was the best of times it was the worst of times\n" << endl;
     code = h.compress();
     cout << "after compress, the code is: " << code << endl;
     key = h.expand(code);
    cout <<"after express, the key is: " << key << endl;
    return 0;
}
