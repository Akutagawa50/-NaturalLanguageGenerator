#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
using namespace std;

bool isalpha(char c){   //アルファベットを判定する関数
    return c>=65&&c<=90 || c>=97&&c<=122;
}

char CapsTrans(char c){     //大文字を小文字に変換する関数
    if(c>=65 && c<=90) c+=32;
    return c;
}

int AlphaTrans(char c){     //アルファベット(小文字)をaを0としたときの番号を返す関数
    return c==' '? 26: (int)c - 97;
}

char NumberTrans(int x){    //0をaとしたときのアルファベットを返す関数
    return x==26? ' ':(char)(x+97);
}



int main(){
    int alphacnt[27]={0};
    int alpha2cnt[27][27]={0};
    

    ifstream ifs;
    ofstream ofs;
    ifs.open("originaltext.txt");               //入力用ファイルを開く
    if(!ifs){cerr << "Cannot open originaltxt" << endl; return -1;}
    ofs.open("generatedtxt.txt", ios::trunc);   //出力用ファイルを開く
    if(!ofs){cerr << "Cannot open generatedtxt" << endl; return -1;}

    char c;
    char c0='*';    //1つ前のアルファベットを保存する変数．初期値はアルファベットとスペース以外の値を入れておく
    while((c=ifs.get()) != EOF){
        if(isalpha(c)){
            c=CapsTrans(c);             //小文字に変換
            alphacnt[AlphaTrans(c)]++;  //出てきたアルファベットをカウント
            ofs << c;
        }
        else if(c=='\n'){
            ofs << c;
            continue;//連続カウントをしないために
        }
        else{
            if(c0==' ')continue;    //連続スペースは数えない
            c=' ';  //スペースに置換
            alphacnt[26]++; //spaceをカウント
            ofs << c;
        }

        if(c0!='*') //連続で並ぶパターンをカウント
            alpha2cnt[AlphaTrans(c0)][AlphaTrans(c)]++;
        c0=c;
    }
    /*
    for(int i=0; i<27; i++){
        cout << alphacnt[i] << ": '" << NumberTrans(i) << "'" << endl;
    }
    */
    for(int i=0; i<27; i++){
        cout << alphacnt[i] << ": '" << NumberTrans(i) << "'" << endl;  //1つだけのときを出力
        for(int j=0; j<27; j++){
           cout << alpha2cnt[i][j] << ": '" << NumberTrans(i) << NumberTrans(j) << "'" << endl;     //2つのときを出力
       }
   }
    return 0;
}

