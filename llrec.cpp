#include "llrec.h"

//*********************************************
// Provide your implementation of llpivot below
//*********************************************

// given linked list (head), create list with values <= pivot in smaller
// place values > pivot into larger, head NULL on return

void llpivot(Node *&head, Node *&smaller, Node *&larger, int pivot) {
    smaller = larger = NULL;
    Node *smallerTail = NULL, *largerTail = NULL;
    llpivotTail(head, smaller, larger, pivot, smallerTail, largerTail);
}

void llpivotTail(Node *&head, Node *&smaller, Node *&larger, int pivot, Node *&smallerTail, Node *&largerTail) {
    // base case - end of list
    if (head == NULL) {
        return;
    }

    Node* nextNode = head->next; // store next node
    head->next = NULL; // detach current node

    // node value less than or equal to pivot
    if (head->val <= pivot) {
        // check if smaller empty
        if (smaller == NULL) {
            smaller = smallerTail = head; // first node
        }
        // smaller not empty
        else {
            smallerTail->next = head; // append to end of list
            smallerTail = head; // move tail forward
        }
    }
    // node value more than pivot
    else {
        // check if larger empty
        if (larger == NULL) {
            larger = largerTail = head; // first node
        }
        // larger not empty
        else {
            largerTail->next = head; // append to end of list
            largerTail = head; // move tail forward
        }
    }

    head = nextNode; // move head forward
    // recursive call
    llpivotTail(head, smaller, larger, pivot, smallerTail, largerTail);
}
