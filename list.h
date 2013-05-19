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

void add_element(list **list, void *data);
void destroy_list(list *list);
void print_student_list(list *slist);
void print_course_score_list(list *clist);
void print_joinex_list(list *jlist);
void add_student(list **slist, char *no, char *name, int gender, char* speciality, char *department);
void add_student_with_check(list **slist, char *no, char *name, int gender, char* speciality, char *department);
void add_score_record(list **clist, char *stu_no, char *course_no, char *course_name, int course_credit, int stu_score);
void add_score_record_with_check(list **clist, char *stu_no, char *course_no, char *course_name, int course_credit, int stu_score);
