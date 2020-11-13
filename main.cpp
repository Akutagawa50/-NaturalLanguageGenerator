#include <iostream>
#include <fstream>
#include <cctype>
#include <cstdlib>
#include <ctime>
using namespace std;

char CapsTrans(char c){     //大文字を小文字に変換する関数
    if(c>=65 && c<=90) c+=32;
    return c;
}

int main(){
    ifstream ifs;
    ofstream ofs;
    ifs.open("originaltext.txt");               //入力用ファイルを開く
    if(!ifs){cerr << "Cannot open originaltxt" << endl; return -1;}
    ofs.open("generatedtxt.txt", ios::trunc);   //出力用ファイルを開く
    if(!ofs){cerr << "Cannot open generatedtxt" << endl; return -1;}

    char c;
    while((c=ifs.get()) != EOF){
        if(isalpha(c) || c == '\n')
            ofs << CapsTrans(c);
        else
            ofs <<' ';
        
    }

    return 0;
}

