#include <iostream>
#include <fstream>
#include <functional>
#include "llrec.h"
using namespace std;

/**
 * Reads integers (separated by whitespace) from a file
 * into a linked list.
 *
 * @param[in] filename
 *  The name of the file containing the data to read
 * @return
 *  Pointer to the linked list (or NULL if empty or the
 *  file is invalid)
 */
Node* readList(const char* filename);

/**
 * Prints the integers in a linked list pointed to
 * by head.
 */
void print(Node* head);

/**
 * Deallocates the linked list nodes
 */
void dealloc(Node* head);


Node* readList(const char* filename)
{
    Node* h = NULL;
    ifstream ifile(filename);
    int v;
    if( ! (ifile >> v) ) return h;
    h = new Node(v, NULL);
    Node *t = h;
    while ( ifile >> v ) {
        t->next = new Node(v, NULL);
        t = t->next;
    }
    return h;
}

void print(Node* head)
{
    while(head) {
        cout << head->val << " ";
        head = head->next;
    }
    cout << endl;
}

void dealloc(Node* head)
{
    Node* temp;
    while(head) {
        temp = head->next;
        delete head;
        head = temp;
    }
}

// -----------------------------------------------
//   Add any helper functions or
//   function object struct declarations
// -----------------------------------------------

struct isEven {
    bool operator()(int value) {
        return value % 2 == 0; // remove even nums
    }
};

int main(int argc, char* argv[])
{
    if(argc < 2) {
        cout << "Please provide an input file" << endl;
        return 1;
    }

    // -----------------------------------------------
    // Feel free to update any code below this point
    // -----------------------------------------------

    // list: 8 9 12 19 6 8

    // test pivot code
    cout << "=== TEST PIVOT ===" << endl;
    
    Node* head = readList(argv[1]);
    cout << "Original list: ";
    print(head);

    Node* smaller = NULL;
    Node* larger = NULL;
    int pivot = 10;

    cout << "Pivot of: " << pivot << endl;

    llpivot(head, smaller, larger, pivot);
    head = NULL;
    cout << ">> smaller list: ";
    print(smaller);
    cout << ">> larger list: ";
    print(larger);

    dealloc(smaller);
    dealloc(larger);

    // test filter code
    cout << endl;
    cout << "=== TEST FILTER ===" << endl;

    head = readList(argv[1]);
    cout << "Original list: ";
    print(head);

    head = llfilter(head, isEven()); // filter out even nums
    cout << ">> filtered list (removed evens): ";
    print(head);
    cout << endl;

    // free remaining list memory
    dealloc(head);
    
    return 0;

}
