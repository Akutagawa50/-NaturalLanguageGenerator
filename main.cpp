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
    int alphacnt[27]={0};           //1文字の個数を記憶する変数
    int alpha2cnt[27][27]={0};      //2文字の個数を記憶する変数
    int alpha3cnt[27][27][27]={0};  //3文字の個数を記憶する変数
    
    ifstream ifs;
    ofstream ofs;
    ifs.open("originaltext.txt");               //入力用ファイルを開く
    if(!ifs){cerr << "Cannot open originaltext" << endl; return -1;}
    ofs.open("convertedtext.txt", ios::trunc);   //出力用ファイルを開く
    if(!ofs){cerr << "Cannot open convertedtext" << endl; return -1;}

    int M=0;    //全体の文字数を記憶する変数
    char c;
    char c0='*';    //1つ前のアルファベットを保存する変数．初期値はアルファベットとスペース以外の値を入れておく
    char c00='*';   //2つ前のアルファベットを保存する変数．
    while((c=ifs.get()) != EOF){
        M++;    //文字数をカウント
        if(isalpha(c)){
            c=CapsTrans(c);             //小文字に変換
            alphacnt[AlphaTrans(c)]++;  //出てきたアルファベットをカウント
            ofs << c;
        }
        else if(c=='\n'){
            ofs << c;
            continue;//改行を連続カウントに含めないため
        }
        else{
            if(c0==' '){M--; continue;}    //連続スペースは数えない
            c=' ';  //スペースに置換
            alphacnt[26]++; //spaceをカウント
            ofs << c;
        }

        if(c00!='*')//3連続で並ぶパターンをカウント
            alpha3cnt[AlphaTrans(c00)][AlphaTrans(c0)][AlphaTrans(c)]++;
        c00=c0;

        if(c0!='*') //2連続で並ぶパターンをカウント
            alpha2cnt[AlphaTrans(c0)][AlphaTrans(c)]++;
        c0=c;
    }
    //それぞれの結果をする
    for(int i=0; i<27; i++){
        cout << (double)alphacnt[i]/M * 100.0 << ": '" << NumberTrans(i)<< "'" << endl;  //1つだけのときを出力
        for(int j=0; j<27; j++){
           //cout << alpha2cnt[i][j] << ": '" << NumberTrans(i) << NumberTrans(j) << "'" << endl;     //2つのときを出力
           for(int k=0; k<27; k++){
               //cout << alpha3cnt[i][j][k] << ": '" << NumberTrans(i) << NumberTrans(j) << NumberTrans(k) << "'" << endl;
           }
       }
    }
    ifs.close();
    ofs.close();

    //自然言語生成の準備をする
    ifs.open("convertedtext.txt");               //入力用ファイルを開く
    if(!ifs){cerr << "Cannot open convertedtext" << endl; return -1;}
    ofs.open("generatedtext.txt", ios::trunc);   //出力用ファイルを開く
    if(!ofs){cerr << "Cannot open generatedtext" << endl; return -1;}
    
    srand((unsigned)time(NULL));    //乱数の開始を時刻で決める
    int k = rand() % M-1;             //0~M-1までの乱数を取得
    ifs.seekg(k, ios_base::beg);    //k番目まで移動
    ofs << (char)ifs.get();
    char A = (char)ifs.get();
    ofs << A;
    
    for(int i=0; i<100; i++){
        k = rand() % M; //0~M-1までの乱数を取得
        for(int j=k; j<M; j++){       //k番目より後ろのAを探す
            ifs.seekg(j, ios_base::beg);
            char buf=ifs.get();
            if(buf==A){         //Aがあったら出力して抜ける
                A=ifs.get();    //Aの次の文字を代入
                ifs.seekg(j, ios_base::beg);    //もとの位置に戻す
                ofs << A;
                break;
            }   
        }
    }
    
    ifs.close();
    ofs.close();
    return 0;
}

