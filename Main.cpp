#include <iostream>
#include <stack>
#include <string>
#include <unordered_map>
#include <cmath>

using namespace std;

int precedence(char op) {
    if(op == '+' || op == '-') return 1;
    if(op == '*' || op == '/') return 2;
    if(op == '^') return 3;
    return 0;
}

string infixToPostfix(string s) {
    stack<char> st;
    string result;
    for (int i = 0; i < s.length(); i++) {
        char c = s[i];
        if (isalnum(c)) result += c;
        else if (c == '(') st.push(c);
        else if (c == ')') {
            while (!st.empty() && st.top() != '(') {
                result += st.top();
                st.pop();
            }
            st.pop();
        }
        else {
            while (!st.empty() && precedence(st.top()) >= precedence(c)) {
                result += st.top();
                st.pop();
            }
            st.push(c);
        }
    }
    while (!st.empty()) {
        result += st.top();
        st.pop();
    }
    return result;
}

string infixToPrefix(string s) {
    reverse(s.begin(), s.end());
    for (int i = 0; i < s.length(); i++) {
        if (s[i] == '(') s[i] = ')';
        else if (s[i] == ')') s[i] = '(';
    }
    string result = infixToPostfix(s);
    reverse(result.begin(), result.end());
    return result;
}

int evaluatePostfix(string s) {
    unordered_map<char, int> values;
    for (char c : s) {
        if (isalpha(c) && values.find(c) == values.end()) {
            cout << "Enter the value for " << c << ": ";
            cin >> values[c];
        }
    }

    stack<int> st;
    for (int i = 0; i < s.length(); i++) {
        if (isalpha(s[i])) {
            st.push(values[s[i]]);
        } else {
            if (st.size() < 2) {
                cout << "Error: Invalid postfix expression\n";
                return -1;
            }
            int val1 = st.top(); st.pop();
            int val2 = st.top(); st.pop();
            switch (s[i]) {
                case '+': st.push(val2 + val1); break;
                case '-': st.push(val2 - val1); break;
                case '*': st.push(val2 * val1); break;
                case '/': st.push(val2 / val1); break;
                case '^': st.push(pow(val2, val1)); break;
                default:
                    cout << "Error: Unknown operator " << s[i] << endl;
                    return -1;
            }
        }
    }

    if (st.size() == 1) {
        return st.top();
    } else {
        cout << "Error: Invalid postfix expression\n";
        return -1;
    }
}

int multiply(int a, int b) {
    if (b == 0) return 0;
    return a + multiply(a, b - 1);
}

int power(int base, int exp) {
    if (exp == 0) return 1;
    return base * power(base, exp - 1);
}

int main() {
    int choice;
    string expression;
    int a, b;

    do {
        cout << "Menu:\n";
        cout << "1. Infix to Postfix\n";
        cout << "2. Infix to Prefix\n";
        cout << "3. Evaluate Postfix Expression\n";
        cout << "4. Recursive Multiply\n";
        cout << "5. Recursive Power\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter infix expression: ";
                cin >> expression;
                cout << "Postfix: " << infixToPostfix(expression) << endl;
                break;
            case 2:
                cout << "Enter infix expression: ";
                cin >> expression;
                cout << "Prefix: " << infixToPrefix(expression) << endl;
                break;
            case 3:
                cout << "Enter postfix expression: ";
                cin >> expression;
                cout << "Result: " << evaluatePostfix(expression) << endl;
                break;
            case 4:
                cout << "Enter two numbers: ";
                cin >> a >> b;
                cout << "Product: " << multiply(a, b) << endl;
                break;
            case 5:
                cout << "Enter base and exponent: ";
                cin >> a >> b;
                cout << "Power: " << power(a, b) << endl;
                break;
            case 6:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice\n";
        }
    } while (choice != 6);

    return 0;
}
