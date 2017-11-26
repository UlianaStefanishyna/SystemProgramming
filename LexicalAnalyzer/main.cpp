
/**
 * @author Uliana Stefanishyna
 */
#include <iostream>
#include <vector>
using namespace std;


int main(){
    string str = "intmain (void) {flat b, a12]; int n; ...}";
    vector<string> vkeyWords {"int", "main", "void", "float"};
    vector<pair<string,string>> vparsed;
    pair<string,string> push;
    string word = "";
    bool fword = false, fnumber = false;
    int ch = 0;
    unsigned i = 0;
    while(i < str.size()){
        //current character (ASCII)
        ch = str[i];

        //block for any words
        if(((ch >= 65) && (ch <= 90)) || ((ch >= 97) && (ch <=122)) || (ch == 35) || (ch == 95) || (ch == 36)){
            if((!fword) && (ch == 35)){
                cout << "Error!!! Variable begins with character \'#\'" << endl;
                return 0;
            }
            if((fnumber) && (!fword)){
                cout << "Error!!! Variable begins with number" << endl;
                return 0;
            }
            word += str[i];
            fword = true;
        }
        else{
            if((ch >= 48) && (ch <= 57)){
                if(fword){
                    word += str[i];
                    fnumber = false;
                }
                else{
                    word += str[i];
                    fnumber = true;
                }
            }
            else{
                //parse word to container
                //if current char is not letter or number - check on keyword
                if(fword){
                    push.first = word;
                    if((word == vkeyWords[0]) || (word == vkeyWords[1]) || (word == vkeyWords[2]) || (word == vkeyWords[3])){
                        push.second = "keyword";
                    }
                    else{
                        push.second = "variable";
                    }
                    word = "";
                    fword = false;
                    vparsed.push_back(push);
                }

                //parse number to container
                if(fnumber){
                    push.first = word;
                    push.second = "number";
                    word = "";
                    fnumber = false;
                    vparsed.push_back(push);
                }

                //parse other characters
                switch (ch) {

                case ';': push.first = ";"; push.second = "semicolon - end of expression"; vparsed.push_back(push);break;
                case '(': push.first = "("; push.second = "opened parenthes"; vparsed.push_back(push);      break;
                case ')': push.first = ")"; push.second = "closed parenthes"; vparsed.push_back(push);      break;
                case '[': push.first = "["; push.second = "Opened bracket"; vparsed.push_back(push); break;
                case ']': push.first = "]"; push.second = "Closed bracket"; vparsed.push_back(push); break;
                case '{': push.first = "{"; push.second = "Opened brace"; vparsed.push_back(push); break;
                case '}': push.first = "}"; push.second = "Closed brace"; vparsed.push_back(push); break;
                case '.': push.first = "."; push.second = "Separator (dot)"; vparsed.push_back(push); break;
                case ',': push.first = ","; push.second = "Comma"; vparsed.push_back(push); break;
                case ' ': break;
                default: cout << "Error!!! Wrong character" << endl;
                    return 0;
                }
            }
        }
        push.first = "";
        push.second = "";
        i++;
    }

    for(unsigned j = 0; j < vparsed.size(); j++)
        cout << vparsed[j].first << "\t->\t" << vparsed[j].second << endl;

    return 0;
}
