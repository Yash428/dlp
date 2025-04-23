#include<iostream>
#include<bits/stdc++.h>
using namespace std;

int main()
{
    map<char, vector<string>> grammar;
    grammar['E'] = {"TA"};
    grammar['A'] = {"*TA", "/TA","#"};
    grammar['T'] = {"FB"} ;
    grammar['B'] = {"+FB", "-FB","#"};
    grammar['F'] = {"(E)", "number"};
    string input;

    cout<<"Add input String: ";
    cin>>input;
}
