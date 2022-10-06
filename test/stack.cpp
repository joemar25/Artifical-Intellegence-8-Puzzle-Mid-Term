
#include <iostream>
#include <stack>

using namespace std;

int main()
{
    // Push - This adds a data value to the top of the stack.
    // Pop  - This removes the data value on top of the stack
    // Peek - This returns the top data value of the stack
    stack<char> st;

    // PUSH
    cout << "Pushing a and b into the stack" << endl;
    st.push('a');
    st.push('b');

    // TOP
    cout << "The top element is: " << st.top() << endl;

    // POP
    cout << "Popping an element" << endl;
    st.pop();
    cout << "The top element is: " << st.top() << endl;

    // EMPTY
    cout << "Checking if the stack is empty: ";
    cout << st.empty() << endl;

    // SIZE
    cout << "Size of the stack: " << st.size() << endl;

    cout << "Popping another element" << endl;
    st.pop();

    cout << "Size of the stack: " << st.size() << endl;
    cout << "Checking if the stack is empty: ";
    cout << st.empty() << endl;
    return 0;
}
