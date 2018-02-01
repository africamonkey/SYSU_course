#include <bits/stdc++.h>
#include "poly.h"

using namespace std;

int display_menu() {
    puts("Polynomial Calculator (Demo)");
    puts("1: Input a polynomial");
    puts("2: Polynomial addition");
    puts("3: Polynomial subtraction");
    puts("4: Polynomial multiplication with a constant");
    puts("5: Subtitude x into Polynomial");
    puts("6: View all polynomial");
    puts("7: Polynomial multiplication with another polynomial");
    puts("8: Polynomial equalness judgement");
    puts("9: Derivative on polynomial");
    puts("0: quit");
    puts("");
    printf("Please enter your choice: ");
    int x;
    cin >> x;
    return x;
}

map < string, poly > m;

poly getpoly() {
    poly p;
    int first = 1;
    while (!p.valid()) {
        if (first)
            printf("Please enter a variable name or a polynomial: ");
        else
            printf("Please re-enter a variable name or a polynomial: ");
        string nam;
        stringstream stream; stream.clear();
        cin >> nam;
        if (m.find(nam) != m.end()) {
            cout << "ok! " << m[nam] << endl;
            return m[nam];
        }
        stream << nam;
        stream >> p;
        first = 0;
    }
    cout << "ok! " << p << endl;
    return p;
}

void savepoly(int has, poly ret = poly()) {
    puts("Please enter your choice: ");
    puts("0: back to main menu");
    if (has == 1) puts("1: save the result into a variable");
    int x;
    cin >> x;
    if (x == 0 || has == 0) return;
    //do save result
    string nam;
    printf("Please input a variable name: ");
    cin >> nam;
    m[nam] = ret;
    puts("success!");
}

int main() {
    m.clear();
    while (1) {
        int op = display_menu();
        switch (op) {
            case 0: {
                puts("bye");
                return 0;
                break;
            }
            case 1: {
                printf("Please input an assignment (variable=polynomial): ");
                string nam = "";
                cin >> nam;
                int found = -1;
                for (int i = 0; i < nam.length(); ++i)
                    if (nam[i] == '=') {
                        found = i;
                        break;
                    }
                if (found == -1) {
                    cerr << "error: we cannot find '=' in your input" << endl;
                } else {
                    string st = nam.substr(found + 1, nam.length() - 1 - found);
                    stringstream stream; stream.clear();
                    stream << st;
                    poly p;
                    stream >> p;
                    nam = nam.substr(0, found);
                    if (p.valid()) {
                        m[nam] = p;
                        cout << "ok! " << nam << " = " << p << endl;
                    }
                }
                savepoly(0);
                break;
            }
            case 2: {
                poly p = getpoly();
                poly q = getpoly();
                poly ret = p + q;
                cout << ret << endl;
                savepoly(1, ret);
                break;
            }
            case 3: {
                poly p = getpoly();
                poly q = getpoly();
                poly ret = p - q;
                cout << ret << endl;
                savepoly(1, ret);
                break;
            }
            case 4: {
                poly p = getpoly();
                printf("please enter an integer: ");
                int q; cin >> q;
                poly ret = p * q;
                cout << ret << endl;
                savepoly(1, ret);
                break;
            }
            case 5: {
                poly p = getpoly();
                printf("please enter an integer: ");
                int q; cin >> q;
                int ret = p.solve(q);
                cout << ret << endl;
                savepoly(0);
                break;
            }
            case 6: {
                for (map< string, poly > :: iterator it = m.begin(); it != m.end(); ++it) {
                    cout << it->first << " : " << it->second << endl;
                }
                savepoly(0);
                break;
            }
            case 7: {
                poly p = getpoly();
                poly q = getpoly();
                poly ret = p * q;
                cout << ret << endl;
                savepoly(1, ret);
                break;
            }
            case 8: {
                poly p = getpoly();
                poly q = getpoly();
                int ret = p == q;
                cout << (ret ? "equal": "not equal") << endl;
                savepoly(0);
                break;
            }
            case 9: {
                poly p = getpoly();
                poly ret = p.derivative();
                cout << ret << endl;
                savepoly(1, ret);
                break;
            }
        }
    }
}
