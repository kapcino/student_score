typedef struct _student
{
    char  stu_no[16];
    char  stu_name[48];
    int   stu_gender; // 0: male(M); 1: femal(F)
    char  stu_speciality[128];
    char  stu_departmant[128];
    float stu_average_score;
} student;

typedef struct _score_record
{
    char stu_no[16];
    char course_no[16];
    char course_name[48];
    int  course_credit;  // 1-5
    int  stu_score; // 0-100
} score_record;

typedef struct _student_socre_record
{
    char stu_no[16];
    char stu_name[48];
    int  stu_gender;
    char stu_speciality[128];
    char stu_departmant[128];
    char course_no[16];
    char course_name[48];
    int  course_credit;
    int  stu_score;
} student_score_record;

typedef struct _node
{
    void         *data;
    struct _node *next;
} list;

void add_student_with_check(list **slist, char *no, char *name, int gender, char* speciality, char *department);
void add_score_record_with_check(list **clist, char *stu_no, char *course_no, char *course_name, int course_credit, int stu_score);
void join_lists(list **jlist, list *slist, list *clist);
void destroy_list(list *head);

void print_student_list(list *slist);
void print_course_score_list(list *clist);
void print_joined_list(list *jlist);

float compare_stu_no(list *a, list *b);
float compare_stu_name(list *a, list *b);
float compare_stu_speciality(list *a, list *b);
float compare_stu_average_score(list *a, list *b);

float compare_course_stuno(list *a, list *b);
float compare_course_cno(list *a, list *b);
float compare_course_name(list *a, list *b);
float compare_course_credit(list *a, list *b);
float compare_course_student_score(list *a, list *b);

float compare_joined_student_no(list *a, list *b);
float compare_joined_student_name(list *a, list *b);
float compare_joined_student_score(list *a, list *b);
void merge_sort(list **headRef, float (*cmp)(list *a, list *b));

void get_average_score_rank_no(list **slist, char *stu_no);
void get_average_score_rank_name(list **slist, char *stu_name);

void get_all_average_score_not_pass_no(list *slist, list *clist, char *speciality, char *course_no);
void get_all_average_score_not_pass_name(list *slist, list *clist, char *speciality, char *course_name);

void get_specific_students_speciality();
