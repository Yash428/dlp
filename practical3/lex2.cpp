#include<iostream>
#include<fstream>
#include<map>
#include<vector>
using namespace std;

enum Token1_type {
    keyword, identifier, integer, floating, operator_symbol, punct, extra, error
};

class Token1 {
public:
    string Token1_name;
    Token1_type type;
    Token1() {}
    Token1(string name, Token1_type t) {
        Token1_name = name;
        type = t;
    }
};

class LA {
public:
    string file_text;
    map<string, Token1_type> t;
    int position;

    LA() {
        file_text = "";
        position = 0;
        assign_t();
    }

    void assign_t() {
        t["int"] = keyword;
        t["float"] = keyword;
        t["char"] = keyword;
        t["if"] = keyword;
        t["else"] = keyword;
        t["while"] = keyword;
        t["struct"] = keyword;
        t["break"] = keyword;
        t["do"] = keyword;
        t["return"] = keyword;
    }

    bool isBlank(char c) {
        return (c == ' ' || c == '\n' || c == '\r' || c == '\t');
    }

    string getNextWord() {
        int start = position;
        while (position < file_text.length() && (isalpha(file_text[position]) || isdigit(file_text[position]))) {
            position++;
        }
        return file_text.substr(start, position - start);
    }

    string getNextNumber() {
        int start = position;
        bool hasDecimal = false;
        while (position < file_text.length() && (isdigit(file_text[position]) || file_text[position] == '.')) {
            if (file_text[position] == '.') {
                if (hasDecimal) break;
                hasDecimal = true;
            }
            position++;
        }
        return file_text.substr(start, position - start);
    }



    vector<Token1> Token1ize() {
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
                    Token1s.push_back(Token1(word, keyword));
                } else {
                    Token1s.push_back(Token1(word, identifier));
                }
            }
            else if (isdigit(currentChar)) {
                string number = getNextNumber();
                if (number.find('.') != string::npos) {
                    Token1s.push_back(Token1(number, floating));
                } else {
                    Token1s.push_back(Token1(number, integer));
                }
            }
            else if (string("+-*/^&|=").find(currentChar) != string::npos) {
                Token1s.push_back(Token1(string(1, currentChar), operator_symbol));
                position++;
            }
            else if (string("(){};").find(currentChar) != string::npos) {
                Token1s.push_back(Token1(string(1, currentChar), punct));
                position++;
            }
            else {
                Token1s.push_back(Token1(string(1, currentChar), error));
                cout << "Lexical Error: Unrecognized symbol '" << currentChar << "'" << endl;
                position++;
            }
        }
        return Token1s;
    }
};

int main() {
    LA l;
    l.get("test1.c");
    vector<Token1> tokens = l.Token1ize();
    for (int i = 0; i < tokens.size(); i++) {
        cout << "Token: " << tokens[i].Token1_name << endl;
    }
    return 0;
}
