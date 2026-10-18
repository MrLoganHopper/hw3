#include "llrec.h"

//*********************************************
// Provide your implementation of llpivot below
//*********************************************

void llpivot(Node*& head, Node*& smaller, Node*& larger, int pivot)
{
    // Base case: empty input, so both output lists are empty
    if (head == NULL) {
        smaller = NULL;
        larger = NULL;
        return;
    }

    Node* curr = head;
    Node* rest = head->next;
    head = NULL;  // input list gives up ownership

    // Split the remainder of the list first
    llpivot(rest, smaller, larger, pivot);

    // Prepend curr on the way back up (keeps original order)
    if (curr->val <= pivot) {
        curr->next = smaller;
        smaller = curr;
    }
    else {
        curr->next = larger;
        larger = curr;
    }
}
