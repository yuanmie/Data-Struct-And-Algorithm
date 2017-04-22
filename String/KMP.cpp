/*
KMP算法
*/
#include <string>
#include <cstdio>
#include <vector>
using std::string;
using std::vector;

class KMP{
public:
    KMP(string p):pat(p){
        M = pat.length();
        int x = 0; //restart status
        dfa[pat[0]][0] = 1;
        for(int j = 1; j < M; j++){
            for(int charIndex = 0; charIndex < R; charIndex++){
                dfa[charIndex][j] = dfa[charIndex][x];
            }
            dfa[ pat[j] ][j] = j + 1;
            x = dfa[pat[j]][x];  // This is difficult to understand
        }
    }

    int search(string text){
        int textLen = text.length();
        int j = 0;
        int i = 0;
        for(i = 0; i < textLen && j < M; i++){
            j = dfa[text[i]][j];
        }

        //match
        if(j == M){
            return i - M;
        }
        return -1;
    }
private:
        static const  int R= 256;
        int dfa[R][R] = {{0}}; //init as 0
        int M; // pat length
        string pat;
};

int main(){
    string pat("AABAA");
    string text("AABABcAABAA");
    KMP kmp(pat);
    int index = kmp.search(text);
    printf("found? index is %d", index);
}
