/*
BM算法
*/
#include <string>
#include <cstdio>
#include <vector>
#include <iostream>

using std::cout;
using std::string;
using std::vector;
using std::endl;

class BM{
public:
    BM(string p):pat(p){
        M = pat.length();
        r = new int[M];

        for(int i = 0; i < M; i++){
            r[pat[i]] = i;
        }
    }

    ~BM(){
        delete[] r;
    }

    int search(string text){
        int textLen = text.length();
        int skip = 0;
        for(int i = 0; i < textLen; i += skip){
            skip = 0;
            for(int j = M-1; j >= 0; j--){
                if(text[i + j] != pat[j]){
                    skip = j - r[pat[j]];
                    if(skip < 1) skip = 1;
                }
            }

            if(skip == 0) return i;
        }

        return -1;
    }
private:
        int *r;
        int M; // pat length
        string pat;
};

int main(){
    string pat("AABAA");
    string text("AABABcAABAA");
    BM BM(pat);
    int index = BM.search(text);
    printf("found? index is %d\n", index);
    cout << text << endl;
    for(int i = 0; i < index; i++)  cout << " ";
    cout << pat << endl;
}
