#include "list.h"
#include <stdio.h>
#include <stdlib.h>             /* exit, etc. */
#include <string.h>

void create_student_list(list **slist)
{
    add_student_with_check(slist, "2012001", "Zhang Nan",  0, "Computer",   "Applied Technology");
    add_student_with_check(slist, "2012002", "Li Wei",     0, "Economy",    "Applied Technology");
    add_student_with_check(slist, "2012003", "Jin Gang",   0, "Language",   "Applied Technology");
    add_student_with_check(slist, "2012004", "Li Xue",     1, "Culture",    "Applied Technology");
    add_student_with_check(slist, "2012005", "Hui Nan",    1, "Computer",   "Applied Technology");
    add_student_with_check(slist, "2012006", "Liu Xiang",  0, "Vehicle",     "Applied Technology");
    add_student_with_check(slist, "2012007", "Tong Xuan",  1, "Computer",   "Applied Technology");
    add_student_with_check(slist, "2012008", "Xiao Xia",   1, "Traffic",   "Applied Technology");
    add_student_with_check(slist, "2012009", "Xiang Gang", 0, "Computer",   "Applied Technology");
    add_student_with_check(slist, "2012010", "Lu Jia",     0, "Accounting", "Applied Technology");
    puts("Finish to create student list.");
}

void create_course_list(list **clist)
{
    add_score_record_with_check(clist, "2012001", "1001", "History",  1, 80);
    add_score_record_with_check(clist, "2012002", "1001", "Politics", 2, 70);
    add_score_record_with_check(clist, "2012001", "1003", "English",  3, 80);
    add_score_record_with_check(clist, "2012001", "1004", "Math",     4, 90);

    add_score_record_with_check(clist, "2012002", "1001", "History",  1, 60);
    add_score_record_with_check(clist, "2012002", "1002", "Politics", 2, 70);
    add_score_record_with_check(clist, "2012002", "1003", "English",  3, 78);
    add_score_record_with_check(clist, "2012002", "1004", "Math",     4, 84);

    add_score_record_with_check(clist, "2012003", "1001", "History",  1, 50);
    add_score_record_with_check(clist, "2012003", "1002", "Politics", 2, 74);
    add_score_record_with_check(clist, "2012003", "1003", "English",  3, 90);

    add_score_record_with_check(clist, "2012004", "1001", "History",  1, 73);
    add_score_record_with_check(clist, "2012004", "1004", "Math",     4, 69);
    puts("Finish to create score record list.");
}

void menu()
{
    list *slist = NULL;
    list *clist = NULL;
    create_student_list(&slist);
    create_course_list(&clist);
    int choice = 0;

    while(1)
    {
        puts("\nMENU");
        puts("Press 1 : To print student table.");
        puts("Press 2 : To print course score table.");
        puts("Press 3 : To display the CONTENTS.");
        puts("Press 4 : To Exit the PROGRAM.");
        puts("*************************************");
        printf("Enter your choice here : ");
        scanf("%d", &choice);

        switch(choice)
        {
        case 1:
            print_student_list(slist);
            break;
        case 2:
            print_course_score_list(clist);        
            break;
        case 3:
            
            break;    
        case 4:
            destroy_list(slist);
            destroy_list(clist);
            puts("Exit program.");
            exit(0);    
        default:
            puts("Invalid Choice.\nRefer MENU for further assistance.");
            break;
        }
    }
}

int main(int argc, char *argv[])
{
    menu();
    return 0;
}