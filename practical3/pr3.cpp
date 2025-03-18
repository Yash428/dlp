#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_set>
#include <cctype>

using namespace std;

// Maximum length of identifiers and constants
const int MAX_TOKEN_LEN = 100;

// List of C keywords
const unordered_set<string> keywords = {
    "auto", "break", "case", "char", "const", "continue", "default", "do", "double",
    "else", "enum", "extern", "float", "for", "goto", "if", "int", "long", "register",
    "return", "short", "signed", "sizeof", "static", "struct", "switch", "typedef",
    "union", "unsigned", "void", "volatile", "while"
};

// Symbol table
vector<string> symbol_table;

// Function to check if a string is a keyword
bool is_keyword(const string &str) {
    return keywords.find(str) != keywords.end();
}

// Function to add an identifier to the symbol table
void add_to_symbol_table(const string &name) {
    symbol_table.push_back(name);
}

// Function to check if an identifier is already in the symbol table
bool is_in_symbol_table(const string &name) {
    for (const auto &entry : symbol_table) {
        if (entry == name) {
            return true;
        }
    }
    return false;
}

// Function to classify and print tokens
void print_token(const string &token, const string &type) {
    cout << "Token: " << token << "\t\tType: " << type << endl;
}

// Function to handle lexical analysis
void lexical_analyzer(ifstream &file) {
    char ch;
    string token;
    bool in_string = false;

    while (file.get(ch)) {
        // Skip whitespace characters
        if (isspace(ch) && !in_string) {
            continue;
        }

        // Handle identifiers and keywords
        if (isalpha(ch) || ch == '_') {
            token = "";
            while (isalnum(ch) || ch == '_') {
                token += ch;
                file.get(ch);
            }
            file.unget(); // Put back the non-alphanumeric character

            if (is_keyword(token)) {
                print_token(token, "Keyword");
            } else {
                print_token(token, "Identifier");
                if (!is_in_symbol_table(token)) {
                    add_to_symbol_table(token);
                }
            }
        }
        // Handle numbers (constants)
        else if (isdigit(ch)) {
            token = "";
            while (isdigit(ch) || ch == '.') {
                token += ch;
                file.get(ch);
            }
            file.unget(); // Put back the non-digit character
            print_token(token, "Constant");
        }
        // Handle strings
        else if (ch == '"') {
            token = "\"";
            in_string = true;
            while (file.get(ch) && ch != '"') {
                token += ch;
            }
            if (ch == '"') {
                token += ch;
            }
            in_string = false;
            print_token(token, "String");
        }
        // Handle comments
        else if (ch == '/') {
            file.get(ch);
            if (ch == '/') { // Single-line comment
                while (file.get(ch) && ch != '\n');
            } else if (ch == '*') { // Multi-line comment
                while (file.get(ch)) {
                    if (ch == '*' && file.get(ch) == '/') {
                        break;
                    }
                }
            } else {
                file.unget();
                print_token("/", "Operator");
            }
        }
        // Handle operators and punctuation
        else if (ispunct(ch)) {
            token = ch;
            file.get(ch);
            if (ch == '=' || ch == '+' || ch == '-' || ch == '&' || ch == '|') { // Handle multi-character operators
                token += ch;
            } else {
                file.unget();
            }
            if (string("+-*/%=&|<>!").find(token[0]) != string::npos) {
                print_token(token, "Operator");
            } else {
                print_token(token, "Punctuation");
            }
        }
        // Handle invalid characters
        else {
            cout << "Error: Invalid character '" << ch << "'" << endl;
        }
    }
}

// Function to print the symbol table
void print_symbol_table() {
    cout << "\nSymbol Table:" << endl;
    for (const auto &entry : symbol_table) {
        cout << "Identifier: " << entry << endl;
    }
}

int main() {
    ifstream file;
    string filename = "test.c";

    file.open(filename);
    if (!file.is_open()) {
        cout << "Error: Unable to open file " << filename << endl;
        return 1;
    }

    cout << "Tokenized Output:" << endl;
    lexical_analyzer(file);
    print_symbol_table();

    file.close();
    return 0;
}
