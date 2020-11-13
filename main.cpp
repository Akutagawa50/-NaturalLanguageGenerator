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

int AlphaTrans(char c){     //アルファベット(小文字)をaを0としたときの番号を返す関数
    return (int)c - 97;
}

char NumberTrans(int x){    //0をaとしたときのアルファベットを返す関数
    return x==26? ' ':(char)(x+97);
}



int main(){
    int alphacnt[27]={0};
    int soatalpha[27][2]={0};

    ifstream ifs;
    ofstream ofs;
    ifs.open("originaltext.txt");               //入力用ファイルを開く
    if(!ifs){cerr << "Cannot open originaltxt" << endl; return -1;}
    ofs.open("generatedtxt.txt", ios::trunc);   //出力用ファイルを開く
    if(!ofs){cerr << "Cannot open generatedtxt" << endl; return -1;}

    char c;
    while((c=ifs.get()) != EOF){
        if(isalpha(c)){
            c=CapsTrans(c);             //小文字に変換
            alphacnt[AlphaTrans(c)]++;  //出てきたアルファベットをカウント
            ofs << c;
        }
        else if(c=='\n')
            ofs << c;
        else{
            alphacnt[26]++; //spaceをカウント
            ofs <<' ';
        }
        
    }

    for(int i=0; i<27; i++){
        //cout << "'" << NumberTrans(i) << "': " << alphacnt[i] << endl;
        cout << alphacnt[i] << ": '" << NumberTrans(i) << "'" << endl;
    }
    return 0;
}

