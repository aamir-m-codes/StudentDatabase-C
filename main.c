#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

#define backspace 8
#define enter 13

typedef struct student
{
    int roll_no;
    int total;
    float per;
    char name[30];
    struct subjects
    {
        int marks;
        char subject_name[23];
    } sub[3];
} student;

void insert()
{
    student *s;
    int n;
    FILE *ptr;
    ptr = fopen("Student_database.txt", "wb");
    printf("Please enter how many students you want to enter.\n");
    scanf("%d", &n);
    s = (student *)malloc(n * sizeof(student));
    for (int i = 0; i < n; i++)
    {
        {
            s[i].total = 0;
            s[i].per = 0;
            printf("Enter the Roll number of student %d.\n", i + 1);
            scanf("%d", &s[i].roll_no);
            fflush(stdin);
            printf("Enter the Name of student %d.\n", i + 1);
            scanf("%[^\n]s", &s[i].name);
            fflush(stdin);
            for (int j = 0; j < 3; j++)
            {
                printf("Enter the name of subject %d.", j + 1);
                scanf("%[^\n]s", &s[i].sub[j].subject_name);
                fflush(stdin);
                printf("Enter marks of %s subject.\n", s[i].sub[j].subject_name);
                scanf("%d", &s[i].sub[j].marks);
                fflush(stdin);
                s[i].total += s[i].sub[j].marks;
            }
            s[i].per += s[i].total / 3.0;
            fwrite(&s[i], sizeof(student), 1, ptr);
        }
    }
    fclose(ptr);
    free(s);
}

void display()
{
    FILE *ptr;
    ptr = fopen("Student_database.txt", "rb");
    student s1;
    printf("\n\t_________________________Student's Records_________________________\n\n");
    printf("\tR.No\tStudent Name\tsub_1\tsub_2\tsub_3\tTotal\tPercentage\n");
    while (fread(&s1, sizeof(student), 1, ptr))
    {
        printf("%10d%16s", s1.roll_no, s1.name);
        for (int j = 0; j < 3; j++)
        {
            printf("%8d", s1.sub[j].marks);
        }
        printf("%9d%10.2f\n", s1.total, s1.per);
    }
    fclose(ptr);
    getch();
}

void append()
{

    student *s;
    int n;
    FILE *ptr;
    ptr = fopen("Student_database.txt", "ab");
    printf("Please enter how many students you want to append.\n");
    scanf("%d", &n);
    s = (student *)malloc(n * sizeof(student));
    for (int i = 0; i < n; i++)
    {
        {
            s[i].total = 0;
            s[i].per = 0;
            printf("Enter the Roll number of student %d.\n", i + 1);
            scanf("%d", &s[i].roll_no);
            fflush(stdin);
            printf("Enter the Name of student %d.\n", i + 1);
            scanf("%[^\n]s", &s[i].name);
            fflush(stdin);
            for (int j = 0; j < 3; j++)
            {
                printf("Enter the name of subject %d.", j + 1);
                scanf("%[^\n]s", &s[i].sub[j].subject_name);
                fflush(stdin);
                printf("Enter marks of %s subject.\n", s[i].sub[j].subject_name);
                scanf("%d", &s[i].sub[j].marks);
                fflush(stdin);
                s[i].total += s[i].sub[j].marks;
            }
            s[i].per += s[i].total / 3.0;
            fwrite(&s[i], sizeof(student), 1, ptr);
        }
    }
    fclose(ptr);
    free(s);
}

void countofrec()
{
    FILE *ptr;
    int n;
    ptr = fopen("Student_database.txt", "rb");
    fseek(ptr, 0, SEEK_END);
    n = ftell(ptr) / sizeof(student);
    printf("The total records in Student database is %d.", n);
    fclose(ptr);
}

void update()
{
    int ro_no, found = 0;
    FILE *ptr, *tp;
    ptr = fopen("Student_database.txt", "rb");
    tp = fopen("temp.txt", "wb");
    student s1;
    printf("Enter the roll number of student to update the record.\n");
    scanf("%d", &ro_no);
    while (fread(&s1, sizeof(student), 1, ptr))
    {
        if (ro_no == s1.roll_no)
        {
            found = 1;
            s1.total = 0;
            s1.per = 0;
            printf("Enter the updated Roll number of student .\n");
            scanf("%d", &s1.roll_no);
            fflush(stdin);
            printf("Enter the updated Name of student.\n");
            scanf("%[^\n]s", &s1.name);
            fflush(stdin);
            for (int j = 0; j < 3; j++)
            {
                printf("Enter the name of subject %d.", j + 1);
                scanf("%[^\n]s", &s1.sub[j].subject_name);
                fflush(stdin);
                printf("Enter marks of %s subject.\n", s1.sub[j].subject_name);
                scanf("%d", &s1.sub[j].marks);
                fflush(stdin);
                s1.total += s1.sub[j].marks;
            }
            s1.per += s1.total / 3.0;
        }
        fwrite(&s1, sizeof(student), 1, tp);
    }
    fclose(ptr);
    fclose(tp);
    if (found == 1)
    {
        tp = fopen("temp.txt", "rb");
        ptr = fopen("Student_database.txt", "wb");
        while (fread(&s1, sizeof(student), 1, tp))
        {
            fwrite(&s1, sizeof(student), 1, ptr);
        }
        fclose(ptr);
        fclose(tp);
    }
    else
    {
        printf("Record is not found !!.\n");
    }
}

void delete()
{
    FILE *ptr, *tp;
    ptr = fopen("Student_database.txt", "rb");
    tp = fopen("temp.txt", "wb");
    student s1;
    int ro_no, found = 0;
    printf("Enter the roll number of studeny which you want to delete.\n");
    scanf("%d", &ro_no);
    while (fread(&s1, sizeof(student), 1, ptr))
    {
        if (ro_no == s1.roll_no)
        {
            found = 1;
        }
        else
        {
            fwrite(&s1, sizeof(student), 1, tp);
        }
    }
    fclose(ptr);
    fclose(tp);
    if (found == 1)
    {
        tp = fopen("temp.txt", "rb");
        ptr = fopen("Student_database.txt", "wb");
        while (fread(&s1, sizeof(student), 1, tp))
        {
            fwrite(&s1, sizeof(student), 1, ptr);
        }
        fclose(ptr);
        fclose(tp);
    }
    else
    {
        printf("Record is not found !!\n");
    }
}

void search()
{
    FILE *ptr;
    ptr = fopen("Student_database.txt", "rb");
    student s1;
    int ro_no, found = 0;
    printf("Enter a roll number of student which you want to search.\n");
    scanf("%d", &ro_no);
    printf("\n\t_________________________Student Record_________________________\n\n");
    printf("\tR.No\tStudent Name\tsub_1\tsub_2\tsub_3\tTotal\tPercentage\n");
    while (fread(&s1, sizeof(student), 1, ptr))
    {
        if (ro_no == s1.roll_no)
        {
            found = 1;
            printf("%10d%16s", s1.roll_no, s1.name);
            for (int j = 0; j < 3; j++)
            {
                printf("%8d", s1.sub[j].marks);
            }
            printf("%9d%10.2f\n", s1.total, s1.per);
        }
    }
    if (found == 1)
    {
    }
    else
    {
        printf("Record is not found !!\n");
    }
    fclose(ptr);
}

void sort_by_total()
{
    FILE *ptr;
    student *s1, s;
    int n;
    ptr = fopen("Student_database.txt", "rb");
    fseek(ptr, 0, SEEK_END);
    n = ftell(ptr) / sizeof(student);
    s1 = (student *)malloc(n * sizeof(student));
    rewind(ptr);

    for (int i = 0; i < n; i++)
    {
        fread(&s1[i], sizeof(student), 1, ptr);
    }
    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (s1[i].total < s1[j].total)
            {
                s = s1[i];
                s1[i] = s1[j];
                s1[j] = s;
            }
        }
    }
    printf("\n\t__________________________ Student's Records __________________________\n");
    printf("\n\t_________________________Sort by total numbers _________________________\n\n");
    printf("\tR.No\tStudent Name\tsub_1\tsub_2\tsub_3\tTotal\tPercentage\n");
    for (int i = 0; i < n; i++)
    {
        printf("%10d%16s", s1[i].roll_no, s1[i].name);
        for (int j = 0; j < 3; j++)
        {
            printf("%8d", s1[i].sub[j].marks);
        }
        printf("%9d%10.2f\n", s1[i].total, s1[i].per);
    }
    fclose(ptr);
    free(s1);
}

void change_password()
{
    char n = 'n';
    char old_pass[30];
    char ch[30];
    int flag = 0;
    FILE *ptr;
    ptr = fopen("password.txt", "r");
    fgets(ch, 30, ptr);
    fclose(ptr);
    fflush(stdin);
    printf("Enter old password.\n");
    scanf("%[^\n]s", old_pass);
    if (strcmp(ch, old_pass) == 0)
    {
        flag = 1;
        for (int i = 1; i <= 5; i++)
        {
            if (i == 1)
            {
                system("cls");
                printf("\t\tLoading.");
                Sleep(1000);
            }
            else if (i == 2)
            {
                system("cls");
                printf("\t\tLoading..");
                Sleep(1000);
            }
            else if (i == 3)
            {
                system("cls");
                printf("\t\tLoading...");
                Sleep(1000);
            }
            else if (i == 4)
            {
                system("cls");
                printf("\t\tLoading....");
                Sleep(1000);
            }
            else if (i == 5)
            {
                system("cls");
                printf("\t\tLoading.....");
                Sleep(1000);
            }
        }
        system("cls");
        printf("Password correct.\n");
    }
    else
    {
        for (int i = 1; i <= 5; i++)
        {
            if (i == 1)
            {
                system("cls");
                printf("\t\tLoading.");
                Sleep(1000);
            }
            else if (i == 2)
            {
                system("cls");
                printf("\t\tLoading..");
                Sleep(1000);
            }
            else if (i == 3)
            {
                system("cls");
                printf("\t\tLoading...");
                Sleep(1000);
            }
            else if (i == 4)
            {
                system("cls");
                printf("\t\tLoading....");
                Sleep(1000);
            }
            else if (i == 5)
            {
                system("cls");
                printf("\t\tLoading.....");
                Sleep(1000);
            }
        }
        system("cls");
        printf("\n");
        printf("Wrong password.\n");
        Sleep(2000);
        system("cls");
        printf("You are not authorized user.\n");
        Sleep(2000);
    }

    if (flag == 1)
    {
        char new_pass[30];
        fflush(stdin);
        printf("Enter new password.\n");
        scanf("%[^\n]s", new_pass);
        printf("Are you sure [y/n] ?\n");
        n = getch();
        if (n == 'y' || n == 'Y')
        {
            FILE *ptr;
            ptr = fopen("password.txt", "w");
            fputs(new_pass, ptr);
            fclose(ptr);
            printf("Successfully!!\n");
        }
    }
}

int main()
{
    int i = 0;
    FILE *pa;
    pa = fopen("password.txt", "r");
    char original_pass[30];
    fgets(original_pass, 30, pa);
    fclose(pa);
    int choice, flag = 0;
    char pass[30], ch;
start:
    system("cls");
    printf("Enter password please.");
    while (1)
    {
        ch = getch();
        if (ch == enter)
        {
            pass[i] = '\0';
            break;
        }
        else if (ch == backspace)
        {
            if (i > 0)
            {
                i--;
                printf("\b \b");
            }
        }
        else
        {
            pass[i] = ch;
            i++;
            printf("*");
        }
    }
    if (strcmp(original_pass, pass) == 0)
    {
        flag = 1;
        for (int i = 1; i <= 5; i++)
        {
            if (i == 1)
            {
                system("cls");
                printf("\t\tLoading.");
                Sleep(1000);
            }
            else if (i == 2)
            {
                system("cls");
                printf("\t\tLoading..");
                Sleep(1000);
            }
            else if (i == 3)
            {
                system("cls");
                printf("\t\tLoading...");
                Sleep(1000);
            }
            else if (i == 4)
            {
                system("cls");
                printf("\t\tLoading....");
                Sleep(1000);
            }
            else if (i == 5)
            {
                system("cls");
                printf("\t\tLoading.....");
                Sleep(1000);
            }
        }
        system("cls");
    }
    else
    {
        for (int i = 1; i <= 5; i++)
        {
            if (i == 1)
            {
                system("cls");
                printf("\t\tLoading.");
                Sleep(1000);
            }
            else if (i == 2)
            {
                system("cls");
                printf("\t\tLoading..");
                Sleep(1000);
            }
            else if (i == 3)
            {
                system("cls");
                printf("\t\tLoading...");
                Sleep(1000);
            }
            else if (i == 4)
            {
                system("cls");
                printf("\t\tLoading....");
                Sleep(1000);
            }
            else if (i == 5)
            {
                system("cls");
                printf("\t\tLoading.....");
                Sleep(1000);
            }
        }
        system("cls");
        printf("\n");
        printf("Wrong password.\n");
        Sleep(2000);
        goto start;
    }
    system("cls");
    if (flag == 1)
    {
        while (1)
        {
            system("cls");
            printf("\n\n\n++------++ Student's Database ++------++\n\n");
            printf("We have some operations for you.\n");
            printf("1.Insert Record.\n");
            printf("2.Display Record.\n");
            printf("3.Append Record.\n");
            printf("4.Count no of Record.\n");
            printf("5.Update Record.\n");
            printf("6.Delete Record.\n");
            printf("7.Search Record.\n");
            printf("8.Sort by roll no Record.\n");
            printf("9.Change Password.\n");
            printf("10.Log out\n");
            printf("Enter your choice.\n");
            scanf("%d", &choice);
            switch (choice)
            {
            case 1:
                system("cls");
                insert();
                break;
            case 2:
                system("cls");
                display();
                break;
            case 3:
                system("cls");
                append();
                break;
            case 4:
                system("cls");
                countofrec();
                break;
            case 5:
                system("cls");
                update();
                break;
            case 6:
                system("cls");
                delete();
                break;
            case 7:
                system("cls");
                search();
                break;
            case 8:
                system("cls");
                sort_by_total();
                break;
            case 9:
                system("cls");
                change_password();
                break;
            case 10:
                exit(0);
            default:
                printf("Please enter correct choice.\n");
            }
        }
    }

    return 0;
}