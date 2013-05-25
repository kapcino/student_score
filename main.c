#include "list.h"
#include <stdio.h>
#include <stdlib.h>             /* exit, etc. */
#include <string.h>

void create_student_list(list **slist)
{

    add_student_with_check(slist, "2012007", "Tong Xuan",  1, "Computer",   "Applied Technology");
    add_student_with_check(slist, "2012008", "Xiao Xia",   1, "Traffic",   "Applied Technology");
    add_student_with_check(slist, "2012009", "Xiang Gang", 0, "Computer",   "Applied Technology");
    add_student_with_check(slist, "2012010", "Lu Jia",     0, "Accounting", "Information");

    add_student_with_check(slist, "2012001", "Zhang Nan",  0, "Computer",   "Applied Technology");
    add_student_with_check(slist, "2012002", "Li Wei",     0, "Economy",    "Applied Technology");
    add_student_with_check(slist, "2012003", "Jin Gang",   0, "Language",   "Management");
    add_student_with_check(slist, "2012004", "Li Xue",     1, "Culture",    "Applied Technology");
    add_student_with_check(slist, "2012005", "Hui Nan",    1, "Computer",   "Finance");
    add_student_with_check(slist, "2012006", "Liu Xiang",  0, "Vehicle",     "Applied Technology");
    puts("Finish to create student list.");
}

void create_course_list(list **clist)
{
    add_score_record_with_check(clist, "2012001", "1001", "History",  1, 97);
    add_score_record_with_check(clist, "2012001", "1002", "Politics", 2, 93);
    add_score_record_with_check(clist, "2012001", "1003", "English",  3, 91);
    add_score_record_with_check(clist, "2012001", "1004", "Math",     4, 90);

    add_score_record_with_check(clist, "2012002", "1001", "History",  1, 60);
    add_score_record_with_check(clist, "2012002", "1002", "Politics", 2, 73);
    add_score_record_with_check(clist, "2012002", "1003", "English",  3, 78);
    add_score_record_with_check(clist, "2012002", "1004", "Math",     4, 84);

    add_score_record_with_check(clist, "2012003", "1001", "History",  1, 50);
    add_score_record_with_check(clist, "2012003", "1002", "Politics", 2, 74);
    add_score_record_with_check(clist, "2012003", "1003", "English",  3, 90);

    add_score_record_with_check(clist, "2012004", "1001", "History",  1, 73);
    add_score_record_with_check(clist, "2012004", "1004", "Math",     4, 69);

    add_score_record_with_check(clist, "2012005", "1001", "History",  1, 82);
    add_score_record_with_check(clist, "2012005", "1003", "English",  3, 97);

    add_score_record_with_check(clist, "2012006", "1001", "History",  1, 69);
    add_score_record_with_check(clist, "2012006", "1003", "English",  3, 93);

    add_score_record_with_check(clist, "2012007", "1001", "History",  1, 79);
    add_score_record_with_check(clist, "2012007", "1002", "Politics", 2, 93);
    add_score_record_with_check(clist, "2012007", "1004", "Math",     4, 85);

    add_score_record_with_check(clist, "2012008", "1001", "History",  1, 49);
    add_score_record_with_check(clist, "2012008", "1002", "Politics", 2, 84);
    add_score_record_with_check(clist, "2012008", "1003", "English",  3, 73);

    add_score_record_with_check(clist, "2012009", "1002", "Politics", 2, 81);
    add_score_record_with_check(clist, "2012009", "1004", "Math",     4, 86);

    add_score_record_with_check(clist, "2012010", "1004", "Math",     4, 23);

    puts("Finish to create score record list.");
}

void menu()
{
    list *slist = NULL;
    list *clist = NULL;
    list *jlist = NULL;
    create_student_list(&slist);
    create_course_list(&clist);
    join_lists(&jlist, slist, clist);

    int choice = 0;
    char stuno[128] = {0};
    char speciality[128] = {0};
    char coursename[128] = {0};
    char courseno[128] = {0};
    float avg = 0;
    int course_num = 0;
    while(1)
    {
        /* reset variables  */
        choice = 0;
        avg = 0;
        memset(courseno, 0, 128);
        memset(stuno, 0, 128);
        memset(speciality, 0, 128);
        memset(coursename, 0, 128);
        memset(courseno, 0, 128);

        puts("***********************************************************");
        puts("MENU");
        puts("Press 11: To print student table, sorted by no.");
        puts("Press 12: To print student table, sorted by name.");
        puts("Press 13: To print student table, sorted by speciality.");
        puts("Press 14: To print student table, sorted by average score.");
        puts("Press 21: To print course score table, sorted by student no.");
        puts("Press 22: To print course score table, sorted by course name.");
        puts("Press 23: To print course score table, sorted by course credit.");
        puts("Press 24: To print course score table, sorted by student score.");
        puts("Press 31: To print the joined table, sorted by student no.");
        puts("Press 32: To print the joined table, sorted by studet name.");
        puts("Press 33: To print the joined table, sorted by course no.");
        puts("Press 34: To print the joined table, sorted by course score.");
        puts("Press 41: To print student's average score and rank, with student no.");
        puts("Press 42: To print average score of course with specific speciality, and not passed students.");
        puts("Press 43: To print student name, speciality whith average >= x and has y courses.");
        puts("Press  5: To exit the PROGRAM.");
        puts("***********************************************************");
        printf("Enter your choice here : ");
        scanf("%d", &choice);

        switch(choice)
        {
        case 1:
        case 11:
            merge_sort(&slist, compare_stu_no);
            puts("Print student table, sorted by no.");
            print_student_list(slist);
            break;
        case 12:
            merge_sort(&slist, compare_stu_name);
            puts("Print student table, sorted by name.");
            print_student_list(slist);
            break;
        case 13:
            merge_sort(&slist, compare_stu_speciality);
            puts("Print student table, sorted by speciality.");
            print_student_list(slist);
            break;
        case 14:
            merge_sort(&slist, compare_stu_average_score);
            puts("Print student table, sorted by average score.");
            print_student_list(slist);
            break;
        case 2:
        case 21:
            merge_sort(&clist, compare_course_stuno);
            puts("Print course score table, sorted by student no.");
            print_course_score_list(clist);
            break;
        case 22:
            merge_sort(&clist, compare_course_name);
            puts("Print course score table, sorted by course name.");
            print_course_score_list(clist);
            break;
        case 23:
            merge_sort(&clist, compare_course_credit);
            puts("Print course score table, sorted by course credit.");
            print_course_score_list(clist);
            break;
        case 24:
            merge_sort(&clist, compare_course_student_score);
            puts("Print course score table, sorted by student score.");
            print_course_score_list(clist);
            break;
        case 3:
        case 31:
            merge_sort(&jlist, compare_joined_student_no);
            puts("Print the joined table, sorted by student no.");
            print_joined_list(jlist);
            break;
        case 32:
            merge_sort(&jlist, compare_joined_student_name);
            puts("Print the joined table, sorted by studet name.");
            print_joined_list(jlist);
            break;
        case 33:
            merge_sort(&jlist, compare_joined_course_no);
            puts("Print the joined table, sorted by course no.");
            print_joined_list(jlist);
            break;
        case 34:
            merge_sort(&jlist, compare_joined_student_score);
            puts("Print the joined table, sorted by course score.");
            print_joined_list(jlist);
            break;
        case 4:
        case 41:
            printf("Please enter the student no.: ");
            scanf("%s", stuno);
            get_average_score_rank_no(&slist, stuno);
            break;
        case 42:
            printf("Please enter the speciality: ");
            scanf("%s", speciality);
            printf("and course no: ");
            scanf("%s", courseno);
            get_all_average_score_not_pass_no(slist, &clist, speciality, courseno);
            break;
        case 43:
            puts("Print student name, speciality whith average >= x and has y courses.");
            printf("Please enter the average value: ");
            scanf("%g", &avg);
            printf("and course number: ");
            scanf("%d", &course_num);
            get_specific_students_speciality(&slist, clist, avg, course_num);
            break;
        case 5:
            destroy_list(slist);
            destroy_list(clist);
            destroy_list(jlist);
            puts("Exit program.");
            exit(0);            /* exit successfully */
        default:                /* not in the choices list */
            puts("Invalid Choice.\nRefer MENU for further assistance.");
            destroy_list(slist);
            destroy_list(clist);
            destroy_list(jlist);
            exit(-1);           /* exit with error */
        }
    }
}

int main(int argc, char *argv[])
{
    menu();
    return 0;
}
