#include "list.h"
#include <stdio.h>

/* split one list to two lists, and merge them */
void FrontBackSplit(list *head, list **front, list **back)
{
    list *fast;
    list *slow;
    if (!head || !(head->next))
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

        /* 'slow' is before the midpoint in the list, so split it in two at that point. */
        *front = head;
        *back = slow->next;
        slow->next = NULL;
    }
}

/* cmp is a pointer to function, different cmp provides sorting with different criteria */
/* cmp can compare no, name, score, etc. */
list *SortedMerge(list *a, list *b, int (*cmp)(list *a, list *b))
{
    list *result = NULL;
    if (!a) return b;
    if (!b) return a;

    /* Pick either a or b, and recur */
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
    list *a = NULL;
    list *b = NULL;

    if ((head == NULL) || (head->next == NULL)) return;

    /* Split head into 'a' and 'b' sublists, recursively sort the sublists */
    FrontBackSplit(head, &a, &b);
    MergeSort(&a, cmp);
    MergeSort(&b, cmp);
    *headRef = SortedMerge(a, b, cmp);
}
