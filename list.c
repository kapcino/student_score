#include "list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void add_element(list **head, void *data)
{
    list *element = (list *)malloc(sizeof (list));
    if (!element) return;
    element->data = data;
    element->next = NULL;
    if (*head == NULL)
        *head = element;
    else
    {
        list *cur = *head;
        while (cur->next) cur = cur->next;
        cur->next = element;
    }    
}

void *get_element_data(list *element)
{
    if (!element) return NULL;
    return element->data;
}

student *get_student(list *slist)
{
    return (student *)get_element_data(slist);
}

score_record *get_score_record(list *clist)
{
    return (score_record *)get_element_data(clist);
}

student_score_record *get_joined_record(list *jlist)
{
    return (student_score_record *)get_element_data(jlist);
}

student_score_record *create_joined_recored(student *stu, score_record *record)
{
    if (!stu || !record) return NULL;
    student_score_record *jrecord = (student_score_record *)malloc(sizeof(student_score_record));
    strcpy(jrecord->stu_no, stu->stu_no);
    strcpy(jrecord->stu_name, stu->stu_name);
    strcpy(jrecord->stu_speciality, stu->stu_speciality);
    strcpy(jrecord->stu_departmant, stu->stu_departmant);
    strcpy(jrecord->course_no, record->course_no);
    strcpy(jrecord->course_name, record->course_name);
    jrecord->stu_gender = stu->stu_gender;
    jrecord->stu_score = record->stu_score;
    return jrecord;
}

void add_joined_record(list **jlist, student_score_record *jrecord)
{
    add_element(jlist, (void *)jrecord);
}

student *find_student_with_no(list *slist, char *student_no)
{
    list *head = slist;
    student *stu = NULL;
    while (head)
    {
        stu = get_student(slist);
        if (!stu) return NULL;                           /* if NULL, means list is empty */
        if (strcmp(stu->stu_no, student_no) == 0) break; /* find the sutdent no in list */
        stu = NULL;                                      /* reset the temporary stu */
        head = head->next;                               /* or the old value will be kept always */
    }
    return stu;
}

score_record *find_score_record(list *clist, char *stu_no, char *course_no)
{
    list *head = clist;
    score_record *rec = NULL;
    while (head)
    {
        rec = get_score_record(clist);
        if (!rec) return NULL;
        if ((strcmp(rec->stu_no, stu_no) == 0) && (strcmp(rec->course_no, course_no) ==0)) break;
        rec = NULL;
        head = head->next;
    }
    return rec;
}

void add_student(list **slist, char *no, char *name, int gender, char* speciality, char *department)
{
    student *stu = (student *)malloc(sizeof(student));
    strcpy(stu->stu_no, no);
    strcpy(stu->stu_name, name);
    strcpy(stu->stu_speciality, speciality);
    strcpy(stu->stu_departmant, department);
    stu->stu_gender = gender;
    stu->stu_average_score = 0;
    add_element(slist, (void *)stu); 
}

void add_student_with_check(list **slist, char *no, char *name, int gender, char* speciality, char *department)
{
    student *stu = find_student_with_no(*slist, no);
    if (stu)
    {
        printf("ERROR, already have the student no: %s in the list!\n", no);
        return;
    }
    add_student(slist, no, name, gender, speciality, department);
}

void add_score_record(list **clist, char *stu_no, char *course_no, char *course_name, int course_credit, int stu_score)
{
    score_record *sr = (score_record *)malloc(sizeof(score_record));
    strcpy(sr->stu_no, stu_no);
    strcpy(sr->course_no, course_no);
    strcpy(sr->course_name, course_name);
    sr->course_credit = course_credit;
    sr->stu_score = stu_score;
    add_element(clist, (void *)sr);
}

void add_score_record_with_check(list **clist, char *stu_no, char *course_no, char *course_name, int course_credit, int stu_score)
{
    score_record *rec = find_score_record(*clist, stu_no, course_no);
    if (rec)
    {
        printf("ERROR, already have the score record sutdent no: %s, course no: %s in the list!\n", stu_no, course_no);
        return;
    }
    add_score_record(clist, stu_no, course_no, course_name, course_credit, stu_score);
}

void destroy_list(list *head)
{
    list *current_element = NULL;
    if (!head) return;
    
    while (head)
    {
        current_element = head;
        head = head->next;
        free(current_element->data);
        free(current_element);
        current_element = NULL;
    }
}

void print_student_list(list *slist)
{
    printf("print student list:\n");
    list *current_element = slist;
    student *student_element;

    while (current_element)
    {
        student_element = (student *)(current_element->data);
        char gender = (student_element->stu_gender == 0) ? 'M' : 'F';
        printf("student no: %7s, name: %10s, gender: %1c, speciality: %10s, department: %15s, average score: %3.1g\n", student_element->stu_no, student_element->stu_name, gender, student_element->stu_speciality, student_element->stu_departmant, student_element->stu_average_score);
        current_element = current_element->next;
    }
    printf("print student list done.\n\n");
}

void print_course_score_list(list *clist)
{
    printf("print course score list.\n");
    list *current_element = clist;
    score_record *record;

    while (current_element)
    {
        record = (score_record *)current_element->data;
        printf("student no: %7s, course no: %4s, course name: %10s, course credit: %1d, student score: %3d\n", record->stu_no, record->course_no,  record->course_name, record->course_credit, record->stu_score);
        current_element = current_element->next;
    }
    printf("print course score list done.\n\n");
}

void print_joined_list(list *jlist)
{
    printf("print joined student and course list.\n");
    list *current_element = jlist;
    student_score_record *ssrecord;

    while (current_element)
    {
        ssrecord = (student_score_record*)current_element->data;
        char gender = (ssrecord->stu_gender == 0) ? 'M' : 'F';
        printf("SNo: %7s, SName: %10s, SGd: %c, Spec: %10s, Dept: %10s, CNo: %4s, CName: %10s, CCredit: %1d, Score: %3.1d\n", ssrecord->stu_no, ssrecord->stu_name, gender, ssrecord->stu_speciality, ssrecord->stu_departmant, ssrecord->course_no, ssrecord->course_name, ssrecord->course_credit, ssrecord->stu_score);
        current_element = current_element->next;
    }
    printf("done to print joined student and course list.\n");
}

void join_lists(list **jlist, list *slist, list *clist)
{
    list *jhead = *jlist;
    list *shead = slist;
    list *chead = clist;
    int total_score;
    int total_course;
    student *stu = NULL;
    score_record *rec = NULL;
    student_score_record *jrec = NULL;

    while (shead)
    {
        stu = get_student(shead); /* get the student in the slist */
        if (!stu)
        {
            shead = shead->next;
            continue;            /* NULL pinter checking */
        }
        if (chead == NULL) chead = clist;  /* two loops, reset the second pointer when it reaches end */
        while (chead)
        {
            rec = get_score_record(chead); /* get the score record in clist */
            if (strcmp(stu->stu_no, rec->stu_no) != 0) 
            {
                chead = chead->next;
                continue;                  /* not the same record for the student no */
            }
            jrec = create_joined_recored(stu, rec); /* find the record for the specific student no */
            if (!jrec)
            {
                chead = chead->next;
                continue;
            }
            add_joined_record(jlist, jrec); /* add new joined jrec into jlist */
            rec = jrec = NULL;  /* reset temmporary pointer to NULL */
            chead = chead->next;
        }

        stu = NULL;
        shead = shead->next;
    }
}

int compare_stu_no(list *a, list *b) /* compare the student no in student table */
{
    if (!a || !b) return 0;     /* invalid case, should go here */
    student *stua = get_student(a);
    student *stub = get_student(b);
    return strcmp(stua->stu_no, stub->stu_no);
}

int compare_stu_name(list *a, list *b) /* compare the student name in student table */
{
    if (!a || !b) return 0;     /* invalid case, should go here */
    student *stua = get_student(a);
    student *stub = get_student(b);
    return strcmp(stua->stu_name, stub->stu_name);
}

int compare_stu_speciality(list *a, list *b) /* compare the speciality in student table */
{
    if (!a || !b) return 0;
    student *stua = get_student(a);
    student *stub = get_student(b);
    return strcmp(stua->stu_speciality, stub->stu_speciality);
}

int compare_stu_average_score(list *a, list *b) /* compare the average score in student table */
{
    if (!a || !b) return 0;
    student *stua = get_student(a);
    student *stub = get_student(b);
    return stua->stu_average_score - stub->stu_average_score;
}

int compare_joimed_no(list *a, list *b)
{
    if (!a || !b) return 0;
    student_score_record *reca = get_joined_record(a);
    student_score_record *recb = get_joined_record(b);
    return strcmp(reca->stu_no, recb->stu_no);
}

int compare_joimed_name(list *a, list *b)
{
    if (!a || !b) return 0;
    student_score_record *reca = get_joined_record(a);
    student_score_record *recb = get_joined_record(b);
    return strcmp(reca->stu_name, recb->stu_name);
}
