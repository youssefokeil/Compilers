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
    map <string, TokenType> reserved ={
        {"if",IF},
        {"else", ElSE},
        {"then", THEN},
        {"end",END},
        {"repeat",REPEAT},
        {"until",UNTIL},
        {"read",READ},
        {"write",WRITE}
    };

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

    map <TokenType, string> enumToString = {
        {SEMICOLON, "SEMICOLON"},
        {IF, "IF"},
        {ElSE,"ELSE"},
        {THEN, "THEN"},
        {END, "END"},
        {REPEAT, "REPEAT"},
        {UNTIL, "UNTIL"},
        {IDENTIFIER, "IDENTIFIER"},
        {ASSIGN, "ASSIGN"},
        {READ, "READ"},
        {WRITE, "WRITE"},
        {LESSTHAN, "LESSTHAN"},
        {EQUAL, "EQUAL"},
        {PLUS, "PLUS"},
        {MINUS, "MINUS"},
        {MULT, "MULT"},
        {DIV, "DIV"},
        {OPENBRACKET, "OPENBRACKET"},
        {CLOSEDBRACKET, "CLOSEDBRACKET"},
        {NUMBER, "NUMBER"},
        {ERROR, "ERROR"}
    };

    
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

        // substring the remaining of the input
        remaining = input.substr(position);

        // match number
        if(regex_search(remaining, match, numberPattern,regex_constants::match_continuous)){
            string lexeme = match.str();
            // change position to skip the lexeme
            position += lexeme.length(); 
            tokenRecord.token_type=TokenType::NUMBER;
            tokenRecord.num_val= stoi(lexeme);

            return tokenRecord;
        }

        // match alphanumeric
        else if(regex_search(remaining, match, identifierPattern,regex_constants::match_continuous)){
            string lexeme = match.str();
            // change position to skip the lexeme
            position += lexeme.length();
            if (reserved.find(lexeme) == reserved.end()) {//not reserved
                tokenRecord.token_type=TokenType::IDENTIFIER;
                tokenRecord.string_val = lexeme;
            }
            else {
                tokenRecord.token_type= reserved[lexeme];
                tokenRecord.string_val = lexeme;
            }
            return tokenRecord;
        }

        // matching symbols only
        else{
            //advance forward
            position++; //i know it makes logical sense to be after the switch-case
            int start = position-1;
            switch(c){
                case ';':
                    return {TokenType::SEMICOLON, ";", 0};
                // matching the ':='    
                case ':':

                    if(input[position]!='='){
                        while (input[position]!=' '&&!isAtEnd()) //||input[position]!= '\n' crashes for some reason
                            position++;
                    return {TokenType::ERROR, input.substr(start,position-start), 0};
                }
                    position++;
                    return {TokenType::ASSIGN, ":=", 0};

                case '<':
                    return {TokenType::LESSTHAN, "<", 0};

                case '+':
                    return {TokenType::PLUS, "+", 0};

                case '=':
                    return {TokenType::EQUAL, "=", 0};

                case '-':
                    return {TokenType::MINUS, "-", 0};

                case '*':
                    return {TokenType::MULT, "*", 0};

                case '/':
                    return {TokenType::DIV, "/", 0};
                case '(':
                    return {TokenType::OPENBRACKET, "(", 0};
                case ')':
                    return {TokenType::CLOSEDBRACKET, ")", 0};
                // I'll handle errors
                default:
                    while (input[position]!=' '&&!isAtEnd())//||input[position]!= '\n', same here
                        position++;
                    return {TokenType::ERROR, input.substr(start, position-start), 0};
            }
        }
    }
};

int main(int argc, char* argv[]){
    if (argc != 3) {
        cout << "Usage: " << argv[0] << " <input_file> <output_file>" << endl;
        return 1;
    }
    //Open input file
    ifstream inputFile(argv[1]);
    if (!inputFile.is_open()) {
        cerr << "Error: Could not open " << argv[1] << endl;
        return 1;
    }
    //Read file
    string input((istreambuf_iterator<char>(inputFile)),
                istreambuf_iterator<char>());
    inputFile.close();


    // string input;
    // input = "joe & ; := :x <  =  *  ( ) :XX : if 123 if & then end repeat until read write 123abc";

    Scanner s(input);
    // cout<<input<<endl;
    vector<pair<string,string>> output;
    TokenRecord tr;

    while (!s.isAtEnd()) {
        tr = s.getNextToken();
        // cout << "Token String Value: " << tr.string_val <<endl;
        // cout << "Token Num Value: " << tr.num_val << endl;
        // cout << "Token Type:" << tr.token_type << endl;
        output.push_back({(tr.token_type==NUMBER?to_string(tr.num_val):tr.string_val),s.enumToString[tr.token_type]});//stringval is the first field, unless its a number, stringify numval, second field is the Token type(string(Enum))
    }

    //Write output
    ofstream outputFile(argv[2]);
    if (!outputFile.is_open()) {
        cout << "Error: Could not create " << argv[2] << endl;
        return 1;
    }
    for (int i = 0; i < output.size(); i++) {
        outputFile << output[i].first << " " << output[i].second << endl;
    }
    outputFile.close();

    cout << "Tokenization complete" << endl;


    // for (int i = 0; i < output.size(); i++) {
    //     cout<<output[i].first<<" ";
    //     cout<<output[i].second;
    //     cout<<endl;
    // }

    return 0;
}
