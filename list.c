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
    jrecord->course_credit = record->course_credit;
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
    printf("=====================print student list:===================\n");
    list *current_element = slist;
    student *student_element;

    while (current_element)
    {
        student_element = (student *)(current_element->data);
        char gender = (student_element->stu_gender == 0) ? 'M' : 'F';
        printf("student no: %7s, name: %10s, gender: %1c, speciality: %10s, department: %20s, average score: %5.4g\n", 
               student_element->stu_no,
               student_element->stu_name,
               gender,
               student_element->stu_speciality,
               student_element->stu_departmant,
               student_element->stu_average_score);
        current_element = current_element->next;
    }
}

void print_course_score_list(list *clist)
{
    printf("===================print couse score list:=================\n");
    list *current_element = clist;
    score_record *record;

    while (current_element)
    {
        record = (score_record *)current_element->data;
        printf("student no: %7s, course no: %4s, course name: %10s, course credit: %1d, student score: %3d\n", 
               record->stu_no,
               record->course_no,
               record->course_name,
               record->course_credit,
               record->stu_score);
        current_element = current_element->next;
    }
}

void print_joined_list(list *jlist)
{
    printf("=====================print joined list:====================\n");
    list *current_element = jlist;
    student_score_record *ssrecord;

    while (current_element)
    {
        ssrecord = (student_score_record*)current_element->data;
        char gender = (ssrecord->stu_gender == 0) ? 'M' : 'F';
        printf("SNo: %7s, SName: %10s, SGd: %c, Spec: %10s, Dept: %20s, CNo: %4s, CName: %10s, CCredit: %1d, Score: %3d\n",
               ssrecord->stu_no,
               ssrecord->stu_name,
               gender,
               ssrecord->stu_speciality,
               ssrecord->stu_departmant,
               ssrecord->course_no, 
               ssrecord->course_name, 
               ssrecord->course_credit,
               ssrecord->stu_score);
        current_element = current_element->next;
    }
}

void join_lists(list **jlist, list *slist, list *clist)
{
    list *shead = slist;
    list *chead = clist;
    int total_score = 0;
    int total_weighed_score = 0;
    float average_score = 0;
    student *stu = NULL;
    score_record *rec = NULL;
    student_score_record *jrec = NULL;

    while (shead)
    {
        stu = get_student(shead); /* get the student in the slist */
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

            total_score += rec->stu_score;
            total_weighed_score += (rec->course_credit * rec->stu_score);

            add_joined_record(jlist, jrec); /* add new joined jrec into jlist */
            rec = NULL;
            jrec = NULL;  /* reset temmporary pointer to NULL */
            chead = chead->next;
        }

        if (total_score != 0)
        {
            average_score = total_weighed_score / (float)total_score;
            ((student *)(shead->data))->stu_average_score = average_score;
        }
        total_score = total_weighed_score = average_score = 0;
        stu = NULL;
        shead = shead->next;
    }
}

float compare_stu_no(list *a, list *b) /* compare the student no in student table */
{
    if (!a || !b) return 0;     /* invalid case, should go here */
    student *stua = get_student(a);
    student *stub = get_student(b);
    return strcmp(stua->stu_no, stub->stu_no);
}

float compare_stu_name(list *a, list *b) /* compare the student name in student table */
{
    if (!a || !b) return 0;     /* invalid case, should go here */
    student *stua = get_student(a);
    student *stub = get_student(b);
    return strcmp(stua->stu_name, stub->stu_name);
}

float compare_stu_speciality(list *a, list *b) /* compare the speciality in student table */
{
    if (!a || !b) return 0;
    student *stua = get_student(a);
    student *stub = get_student(b);
    return strcmp(stua->stu_speciality, stub->stu_speciality);
}

float compare_stu_average_score(list *a, list *b) /* compare the average score in student table */
{
    if (!a || !b) return 0;
    student *stua = get_student(a);
    student *stub = get_student(b);
    return stua->stu_average_score - stub->stu_average_score;
}

float compare_course_stuno(list *a, list *b)
{
    if (!a || !b) return 0;
    score_record *sra = get_score_record(a);
    score_record *srb = get_score_record(b);
    return strcmp(sra->stu_no, srb->stu_no);
}

float compare_course_cno(list *a, list *b)
{
    if (!a || !b) return 0;
    score_record *sra = get_score_record(a);
    score_record *srb = get_score_record(b);
    return strcmp(sra->course_no, srb->course_no);
}

float compare_course_name(list *a, list *b)
{
    if (!a || !b) return 0;
    score_record *sra = get_score_record(a);
    score_record *srb = get_score_record(b);
    return strcmp(sra->course_name, srb->course_name);
}

float compare_course_credit(list *a, list *b)
{
    if (!a || !b) return 0;
    score_record *sra = get_score_record(a);
    score_record *srb = get_score_record(b);
    return sra->course_credit - srb->course_credit;
}

float compare_course_student_score(list *a, list *b)
{
    if (!a || !b) return 0;
    score_record *sra = get_score_record(a);
    score_record *srb = get_score_record(b);
    return sra->stu_score - srb->stu_score;
}

float compare_joined_student_no(list *a, list *b)
{
    if (!a || !b) return 0;
    student_score_record *reca = get_joined_record(a);
    student_score_record *recb = get_joined_record(b);
    return strcmp(reca->stu_no, recb->stu_no);
}

float compare_joined_student_name(list *a, list *b)
{
    if (!a || !b) return 0;
    student_score_record *reca = get_joined_record(a);
    student_score_record *recb = get_joined_record(b);
    return strcmp(reca->stu_name, recb->stu_name);
}

float compare_joined_course_no(list *a, list *b)
{
    if (!a || !b) return 0;
    student_score_record *reca = get_joined_record(a);
    student_score_record *recb = get_joined_record(b);
    return strcmp(reca->course_no, recb->course_no);
}

float compare_joined_student_score(list *a, list *b)
{
    if (!a || !b) return 0;
    student_score_record *reca = get_joined_record(a);
    student_score_record *recb = get_joined_record(b);
    return reca->stu_score - recb->stu_score;
}

char *get_student_no_with_name(list *slist, char *stu_name)
{
    list *head = slist;
    student *stu = NULL;
    char sno[128] = {0};
    while (head)
    {
        stu = get_student(head);
        if (strcmp(stu->stu_name, stu_name) == 0)
        {
            strcpy(sno, stu->stu_no);
            break;
        }
        head = head->next;
    }
    return sno;
}

void get_average_score_rank_no(list **slist, char *stu_no)
{
    if (!slist || !stu_no)
    {
        printf("get_average_score_rank:Parameter error.\n");
        return;
    }

    student *stu = NULL;
    int position = 0;
    int total_student = 0;
    float avg_score = 0.0;
    int found = 0;
    merge_sort(slist, compare_stu_average_score);
    list *cur = *slist;
    while (cur)
    {
        stu = get_student(cur);
        if (strcmp(stu->stu_no, stu_no) == 0) /* find the target student */
        {
            avg_score = stu->stu_average_score; /* get the average score */
            found = 1;
        }
        else if (found != 1)
            position ++;        /* save the position in sorted list */

        total_student ++;
        cur = cur->next;
    }
    
        int rank = total_student - position;
    if (found == 0)
        printf("Fail to find the info for student: %s.\n", stu_no);
    else
        printf("Find student: %7s, average score: %5.4g, rank: %3d.\n", stu_no, avg_score, rank);
}

void get_average_score_rank_name(list **slist, char *stu_name)
{
    if (!slist || !stu_name)
    {
        printf("get_average_score_rank:Parameter error.\n");
        return;
    }

    char sno[128] = {0};
    strcpy(sno, get_student_no_with_name(slist, stu_name));
    if (strlen(sno) != 0)
        get_average_score_rank_no(slist, sno);
    else
        printf("fail to get the student with name: %s.\n", stu_name);
}

char *get_course_no_with_name(list *clist, char *cname)
{
    list *head = clist;
    score_record *rec = NULL;
    char cno[128] = {0};
    while (head)
    {
        rec = get_score_record(head);
        if (strcmp(rec->course_name, cname) == 0)
        {
            strcpy(cno, rec->course_no);
            break;
        }
        head = head->next;
    }
    return cno;
}

void get_all_average_score_not_pass_no(list *slist, list **clist, char *speciality, char *course_no)
{
    if (!slist || !clist || !speciality || !course_no)
    {
        printf("get_all_average_score_not_pass_no: parameter error.\n");
        return;
    }

    merge_sort(clist, compare_course_cno); /* sorting by course no */
    list *shead = slist;
    list *chead = *clist;
    int total_score = 0;
    int total_student = 0;
    float average_score = 0;
    student *stu = NULL;
    score_record *rec = NULL;
    /* save the student nos in a arrary, and then convert to names */
    /* max number of not passed student is 50 */
    char nopass_no[50][16];
    memset(nopass_no, 0, 50 * 16);
    int index = 0;

    while (shead)
    {
        stu = get_student(shead); /* get the student in the slist */
        /* not the student who has the specific speciality */
        if (strcmp(stu->stu_speciality, speciality) != 0)
        {
            shead = shead->next;
            continue;
        }

        if (chead == NULL) chead = *clist;  /* two loops, reset the second pointer when it reaches end */
        while (chead)
        {
            rec = get_score_record(chead); /* get the score record in clist */
            /* in the record list, to ensure next record is the target student not others */
            if (strcmp(stu->stu_no, rec->stu_no) != 0)
            {
                chead = chead->next;
                continue;
            }

            /* not the specific course*/
            if (strcmp(rec->course_no, course_no) != 0)
            {
                chead = chead->next;
                continue;
            }

            /* save the student no which has less than 60 scores into a array */
            if (rec->stu_score < 60)
            {
                strcpy(nopass_no[index], rec->stu_no);
                index ++;
            }

            total_score += rec->stu_score;
            total_student ++;
            // printf("stu no: %s, course no: %s, total score: %d, student: %d\n", stu->stu_no, rec->course_no, total_score, total_student);
            rec = NULL;
            chead = chead->next;
        }

        stu = NULL;
        shead = shead->next;
    }

    if (total_student != 0)
    {
        average_score = total_score / (float)total_student;
        printf("Speciality: %7s, course: %7s, all average socre: %5.4f\n", speciality, course_no, average_score);
    }
    else
        printf("Speciality: %7s, course: %7s, all average socre: 0.\n", speciality, course_no);
    
    shead = slist;
    printf("Not passed student in speciality: %7s are:\n", speciality);
    printf("================\n");
    while (shead)      /* find the student name with student no, and print out */
    {
        stu = get_student(shead);
        for (int i = 0; (i < 50) && (strlen(nopass_no[i]) > 0); i++)
        {
            if (strcmp(stu->stu_no, nopass_no[i]) == 0)
                printf("%7s\n", stu->stu_name);
        }
        shead = shead->next;
    }
    
}

void get_all_average_score_not_pass_name(list *slist, list **clist, char *speciality, char *course_name)
{
    if (!slist || !clist || !course_name)
    {
        printf("get_all_average_score_not_pass_name: parameter error.\n");
        return;
    }

    char cno[128] = {0};
    strcpy(cno, get_course_no_with_name(*clist, course_name));
    if (strlen(cno) != 0)
        get_all_average_score_not_pass_no(slist, clist, speciality, cno);
    else
        printf("Fail to find the course no with name: %s in list.\n", course_name);
    
}

void get_specific_students_speciality()
{
}
