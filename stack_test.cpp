#include <iostream>
#include "stack.h"

using namespace std;

int main() {
    Stack<int> s;

    cout << "Stack is empty? " << (s.empty() ? "Yes" : "No") << endl;

    // Test push()
    s.push(10);
    s.push(20);
    s.push(30);

    cout << "Stack size after pushes: " << s.size() << endl;
    cout << "Top element: " << s.top() << endl;

    // Test pop()
    s.pop();
    cout << "Stack size after pop: " << s.size() << endl;
    cout << "New top element: " << s.top() << endl;

    // Test exception handling
    try {
        while (!s.empty()) {
            s.pop();
        }
        s.pop();  // Should throw an exception
    } catch (const underflow_error& e) {
        cout << "Exception caught: " << e.what() << endl;
    }

    return 0;
}
