#include "list.h"
#include <stdio.h>

/* split one list to two sub lists, and merge them */
void front_back_split(list *head, list **front, list **back)
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
/* cmp can compare with no, name, score, etc. */
list *sorted_merge(list *a, list *b, float (*cmp)(list *a, list *b))
{
    list *result = NULL;
    if (!a) return b;
    if (!b) return a;

    /* Pick either a or b, and recur */
    /* for int, <= 0 is OK, but for float needs checking range*/
    if ((cmp(a, b) <= 0.000000001)) 
    {
        result = a;
        result->next = sorted_merge(a->next, b, cmp);
    }
    else
    {
        result = b;
        result->next = sorted_merge(a, b->next, cmp);
    }
    return(result);
}

void merge_sort(list **headRef, float (*cmp)(list *a, list *b))
{
    list *head = *headRef;
    list *a = NULL;
    list *b = NULL;

    if ((head == NULL) || (head->next == NULL)) return;

    /* Split head into 'a' and 'b' sublists, recursively sort the sublists */
    front_back_split(head, &a, &b);
    merge_sort(&a, cmp);
    merge_sort(&b, cmp);
    *headRef = sorted_merge(a, b, cmp);
}
