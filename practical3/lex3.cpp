#include<iostream>
#include<fstream>
#include<bits/stdc++.h>
using namespace std;

bool isPunctuator(char ch){
    vector<char> puncts = {'+','-','*','/',',',';','>','<','=','(',')','[',']','{' ,'}','&','|'};
    for (int i=0;i<puncts.size();i++){
        if(puncts[i]==ch){
            return true;
        }
    }
    return false;
}

bool validIdentifier(string str){
    if(isPunctuator(str[0])==true){
        return false;
    }
    if(str[0]>='0' && str[0]<='9'){
        return false;
    }

    int i,len = str.length();
    if (len == 1){
        return true;
    }
    else{
        for (i = 1;i<len;i++){
            if (isPunctuator(str[i]) == true){
                return false;
            }
        }
    }
    return true;
}

bool isOperator(char ch){
    vector<char> operators = {'+','-','*','/','>','<','=','|','&',' '};
    for(int i=0;i<operators.size();i++){
        if(operators[i]==ch){
            return true;
        }
    }
    return false;
}

bool isKeyword(string s){
    vector<string> keywords = {"if","else","while","do","break","continue","int","double","float","return","char",
                                "case","long","short","typedef","switch","void","unsigned",
                                "static","struct","sizeof","const","enum","union","bool"};
    for(int i=0;i<keywords.size();i++){
        if(s==keywords[i]){
            return true;
        }
    }
    return false;
}

bool isNumber(string str)
{
    int i, len = str.length(),numOfDecimal = 0;
    if (len == 0){
        return false;
    }
    for (i = 0 ; i < len ; i++){
        if (numOfDecimal > 1 && str[i] == '.'){
            return false;
        }
        else if (numOfDecimal <= 1){
            numOfDecimal++;
        }
        if((str[i]>='0' && str[i]<='9') && (str[i] !='-' && !(i>0))){
            return true;
        }
    }
    return false;
}

string subString(string s,int l,int r){
    return s.substr(l, r-l+1);
}


void tokenize(string str)
{
    int left = 0, right = 0;
    int len = str.length();
    while (right<=len && left<=right){
        if (isPunctuator(str[right]) == false){
                right++;
        }
        if (isPunctuator(str[right]) == true && left == right){
            if (isOperator(str[right]) == true){
                std::cout<< str[right] <<" IS AN OPERATOR\n";
            }

            right++;
            left = right;
        }
        else if (isPunctuator(str[right]) == true && left != right || (right == len && left != right)){
            string sub = subString(str, left, right - 1);

            if(isKeyword(sub)){
                cout<< sub <<" IS A KEYWORD\n";
            }
            else if (isNumber(sub)){
                cout<< sub <<" IS A NUMBER\n";
            }
            else if (validIdentifier(sub) == true && isPunctuator(str[right - 1]) == false){
                cout<< sub <<" IS A VALID IDENTIFIER\n";
            }
            else if (validIdentifier(sub) == false && isPunctuator(str[right - 1]) == false){
                         cout<< sub <<" IS NOT A VALID IDENTIFIER\n";
            }
            left = right;
        }
    }
}

string get(string file_path){
    ifstream is(file_path);
    string s;
    string file_text;
    while(getline(is,s)){
        if(s[0]=='#')
            continue;
        string temp = s;
        temp.erase(remove(temp.begin(), temp.end(), ' '), temp.end());
        temp = temp.substr(0,2);
        if(temp=="//"){
            continue;
        }
        file_text = file_text + s;
    }
    is.close();
    cout<<"Scanned Code: "<<endl;
    cout<<file_text<<endl;
    return file_text;
}

int main() {
    string text = get("test1.c");
    tokenize(text);
    return 0;
}
