#include "list.h"
#include <stdio.h>

void FrontBackSplit(list *head, list **front, list **back)
{
    list *fast;
    list *slow;
    if (head==NULL || head->next==NULL)
    {
        /* length < 2 cases */
        *front = head;
        *back = NULL;
    }
    else
    {
        slow = head;
        fast = head->next;

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
        *front = head;
        *back = slow->next;
        slow->next = NULL;
    }
}



list *SortedMerge(list *a, list *b, int (*cmp)(list *a, list *b))
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

void MergeSort(list **headRef, int (*cmp)(list *a, list *b))
{
    list *head = *headRef;
    list *a;
    list *b;
    // Base case -- length 0 or 1
    if ((head == NULL) || (head->next == NULL)) 
    {
        return;
    }
    FrontBackSplit(head, &a, &b);
    // Split head into 'a' and 'b' sublists
    // We could just as well use AlternatingSplit()
    MergeSort(&a, cmp);
    // Recursively sort the sublists
    MergeSort(&b, cmp);
    *headRef = SortedMerge(a, b, cmp);
    // answer = merge the two sorted lists together
}
