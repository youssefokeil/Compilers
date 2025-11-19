#include <iostream>
#include "tokens.h"
#include <regex>
#include <string>
#include<bits/stdc++.h>
using namespace std;

class Scanner{
    const regex numberPattern{"^[0-9]+\\b"};
    const regex identifierPattern{"^[a-zA-Z][a-zA-Z0-9_]*\\b"}; //notice that this will match reserved words too
    const regex reservedWordsPattern{"\\b(if|then|end|repeat|until|read|write)\\b"};

    string input;
    int position;
    char c;
    smatch match;
    string remaining; //substring
public:
    Scanner(const string& code){
        position =0;
        input = code;
    }

    // checks if we finished out 
    bool isAtEnd(){
        return (position >= input.length());
    }
    
    // get the next token from a string, this will be used later in the parser
    TokenRecord getNextToken(){
        // peeking at current position
        c = input[position];
        TokenRecord tokenRecord;


        // skip white spaces in the beginning, includes tabs, space and new line
        while((c == ' ' || c == '\n' || c == '\t' || c == '\r') && !isAtEnd()){
            position++;
            if(!isAtEnd())
                c = input[position]; 
            else break;
        }
        cout << "Position: " << position <<endl;
        // substring the remaining of the input
        remaining = input.substr(position);

        // match number
        if(regex_search(remaining, match, numberPattern,regex_constants::match_continuous)){
            string lexeme = match.str();
            // change position to skip the lexeme
            position += lexeme.length(); 
            tokenRecord.token_type=TokenType::NUMBER;
            tokenRecord.num_val= stoi(lexeme);
            cout << "Position: " << position <<endl;
            cout<<"num"<<endl;
            return tokenRecord;
        }

        // match alphanumeric
        else if(regex_search(remaining, match, identifierPattern,regex_constants::match_continuous)){
            string lexeme = match.str();
            // change position to skip the lexeme
            position += lexeme.length(); 
            tokenRecord.token_type=TokenType::IDENTIFIER;
            tokenRecord.string_val = lexeme;

            cout<< "position: "<<position<<endl;
            return tokenRecord;
        }

        TokenRecord tr;
        tr.token_type=TokenType::UNTIL;
        return tr;

        
    }
};

int main(){
    string input;
    input = " joe \n 123 ";
    Scanner s(input);
    
    TokenRecord tr= s.getNextToken();
    cout << "Token Value: " << tr.string_val <<endl;
    cout << "Token Type:" << TokenType(tr.token_type) << endl;

    TokenRecord tr2 = s.getNextToken();
    cout << "Token Value: " << tr2.num_val <<endl;
    cout << "Token Type:" << TokenType(tr2.token_type)<<endl;

    return 0;
}
