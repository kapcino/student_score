#include "list.h"
#include <stdio.h>

/* function prototypes */
list *SortedMerge(list *a, list *b, int (*cmp)(void *a, void *b));
void FrontBackSplit(list *source, list ** frontRef, list ** backRef);
 
/* sorts the linked list by changing next pointers (not data) */
void MergeSort(list **headRef, int (*cmp)(void *elema, void *elemb))
{
    list *head = *headRef;
    list *a;
    list *b;
 
    /* Base case -- length 0 or 1 */
    if ((head == NULL) || (head->next == NULL))
        return;
 
    /* Split head into 'a' and 'b' sublists */
    FrontBackSplit(head, &a, &b);
 
    /* Recursively sort the sublists */
    MergeSort(&a, cmp);
    MergeSort(&b, cmp);
 
    /* answer = merge the two sorted lists together */
    *headRef = SortedMerge(a, b, cmp);
}
 
/* See http://geeksforgeeks.org/?p=3622 for details of this function */
list *SortedMerge(list *a, list *b, int (*cmp)(void *a, void *b))
{
    list *result = NULL;
 
    /* Base cases */
    if (a == NULL)
        return(b);
    else if (b==NULL)
        return(a);
 
    /* Pick either a or b, and recur */
    /* if (a->data <= b->data) */
    if (cmp(a, b) <= 0)
    {
        result = a;
        result->next = SortedMerge(a->next, b, cmp);
    }
    else
    {
        result = b;
        result->next = SortedMerge(a, b->next, cmp);
    }
    return(result);
}
 
/* UTILITY FUNCTIONS */
/* Split the nodes of the given list into front and back halves,
   and return the two lists using the reference parameters.
   If the length is odd, the extra node should go in the front list.
   Uses the fast/slow pointer strategy.  */
void FrontBackSplit(list *source, list **frontRef, list **backRef)
{
    list *fast;
    list *slow;
    if (source==NULL || source->next==NULL)
    {
        /* length < 2 cases */
        *frontRef = source;
        *backRef = NULL;
    }
    else
    {
        slow = source;
        fast = source->next;
 
        /* Advance 'fast' two nodes, and advance 'slow' one node */
        while (fast != NULL)
        {
            fast = fast->next;
            if (fast != NULL)
            {
                slow = slow->next;
                fast = fast->next;
            }
        }
 
        /* 'slow' is before the midpoint in the list, so split it in two
           at that point. */
        *frontRef = source;
        *backRef = slow->next;
        slow->next = NULL;
    }
}
