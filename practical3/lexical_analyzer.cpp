#include<iostream>
#include<cctype>
#include<bits/stdc++.h>

using namespace std;

enum class Token1_type{
    keyword, identifier, integer,floating,operator_symbol,punct,extra
};

class Token1{
public:
    string Token1_name;
    Token1_type type;
    Token1(){}
    Token1(string name, Token1_type t){
        Token1_name = name;
        type = t;
    }
};

class LA{
public:
    string file_text;
    map<string,Token1_type> t;
    size_t position;
    LA(){
        file_text = "";
        position = 0;
    }

    void assign_t()
    {
        t["int"] = Token1_type::keyword;
        t["float"] = Token1_type::keyword;
        t["char"]= Token1_type::keyword;
        t["if"]= Token1_type::keyword;
        t["else"]= Token1_type::keyword;
        t["if"]= Token1_type::keyword;
        t["while"]= Token1_type::keyword;
        t["struct"]= Token1_type::keyword;
        t["break"]= Token1_type::keyword;
        t["do"]= Token1_type::keyword;
        t["return"]= Token1_type::keyword;
    }
    bool isBlank(char c){
        return (c==' '|| c=='\n'||c=='\r'||c=='\t');
    }
    // we have functions for digit, alhpabet and alphanumeric

    string getNextWord()
    {
        size_t start = position;
        while (position < file_text.length() && isalnum(file_text[position])) {
            position++;
        }
        return file_text.substr(start, position - start);
    }

    string getNextNumber()
    {
        size_t start = position;
        bool hasDecimal = false;
        while (position < file_text.length() && (isdigit(file_text[position]) || file_text[position] == '.')) {
            if (file_text[position] == '.') {
                if (hasDecimal)
                    break;
                hasDecimal = true;
            }
            position++;
        }
        return file_text.substr(start, position - start);
    }

    void get(string file_path){
        ifstream is(file_path);
        string s;
        while(getline(is,s)){
            if(s[0]=='#')
                continue;
            file_text = file_text + s;
        }
        is.close();
        cout<<"Scanned Code: "<<endl;
        cout<<file_text<<endl;
    }

    vector<Token1> Token1ize(){
        vector<Token1> Token1s;
        while (position < file_text.length()) {
            char currentChar = file_text[position];

            if (isBlank(currentChar)) {
                position++;
                continue;
            }

            if (isalpha(currentChar)) {
                string word = getNextWord();
                if (t.find(word) != t.end()) {
                    Token1s.emplace_back(Token1_type::keyword, word);
                }
                else {
                    Token1s.emplace_back(Token1_type::identifier, word);
                }
            }

            else if (isdigit(currentChar)) {
                string number = getNextNumber();
                if (number.find('.') != string::npos) {
                    Token1s.emplace_back(Token1_type::floating, number);
                }
                else {
                    Token1s.emplace_back(Token1_type::integer, number);
                }
            }

            else if (currentChar == '+' || currentChar == '-' || currentChar == '*' || currentChar == '/' || currentChar == '^' ||currentChar == '&' || currentChar == '|' || currentChar == '=') {
                Token1s.emplace_back(Token1_type::operator_symbol,string(1, currentChar));
                position++;
            }

            else if (currentChar == '(' || currentChar == ')' || currentChar == '{' || currentChar == '}' || currentChar == ';') {
                Token1s.emplace_back(Token1_type::punct, string(1, currentChar));
                position++;
            }

            else {
                Token1s.emplace_back(Token1_type::extra, string(1, currentChar));
                position++;
            }
        }
        return Token1s;
    }
};

int main()
{
    LA l;
    l.get("test1.c");
}

