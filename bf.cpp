#pragma GCC optimize("Ofast")

#include <iostream>
#include <string>
#include <vector>
#include <stack>

using namespace std;

int main() {

    string instructions, s;

    while (cin >> s) {
        if (s == "0") break;
        instructions += s;
    }
    
    vector <unsigned> line(1000, 0);
    
    auto ptr = line.begin();
    auto it = instructions.begin();
    
    stack <string::iterator> loop;
    
    while (it != instructions.end()) {
        if (*it == '<') {
            if (ptr == line.begin()) {
                throw runtime_error("Tried to access location less than 0");
            }
            ptr--;
        } else if (*it == '>') {
            ptr++;
            if (ptr == line.end()) {
                line.push_back(0);
                ptr = prev(line.end());
            }
        } else if (*it == '+') {
            ++(*ptr);
        } else if (*it == '-') {
            --(*ptr);
        } else if (*it == '.') {
            cout << (char)(*ptr);
        } else if (*it == ',') {
            char c;
            cin >> c;
            *ptr = c;
        } else if (*it == ']') {
            if (loop.size() == 0) {
                throw runtime_error("Unmatched brackets");
            }
            if (*ptr != 0) {
                it = loop.top();
            } else {
                loop.pop();
            }
        } else if (*it == '[') {
            loop.push(it);
            if (*ptr == 0) {
                auto n = it;
                ++it;
                while (it != instructions.end()) {
                    if (*it == '[') {
                        loop.push(it);
                    } else if (*it == ']') {
                        if (loop.size() == 0) {
                            throw runtime_error("Unmatched brackets");
                        }
                        auto temp = loop.top();
                        loop.pop();
                        if (n == temp)
                            break;
                    }
                    ++it;
                }
            }
        }
        ++it;
    }
    return 0;
}
