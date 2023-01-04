// Name: Sanidhaya Sharma                         Rollno: CS21B1024

#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#define MAX 100
struct Faculty // initialised a linked list
{
    struct Faculty *last;
    char name[MAX];
    char deptt[MAX];
    int age;
    char gender;
    struct Faculty *next;
};

typedef struct Faculty faculty;
faculty *head = NULL;
faculty *tail = NULL;

faculty *emptyInsertion(char name[], char deptt[], char gender, int age)
{ // for adding to empty list
    faculty *tmp = malloc(sizeof(faculty));
    tmp->last = NULL;
    strcpy(tmp->name, name); // copying string to node temp
    strcpy(tmp->deptt, deptt);
    tmp->age = age;
    tmp->gender = gender;
    tmp->next = NULL;
    return tmp;
}

void insertFaculty(char name[], char deptt[], char gender, int age)
{
    faculty *p = emptyInsertion(name, deptt, gender, age);
    if ((tail == NULL) & (head == NULL))
    { // null case
        tail = p;
        head = p;
    }
    else
    {
        faculty *temp = tail;
        p->last = tail;
        p->next = NULL;
        temp->next = p;
        tail = p;
    }
}
// Note:for insertion from beginning,uncomment this and comment the previous function for insertion
/*void insertFaculty(char name[], char deptt[], char gender, int age)
{
    faculty *p = emptyInsertion(name, deptt, gender, age);
    if ((tail == NULL) & (head == NULL))
    { // null case
        tail = p;
        head = p;
    }
    else
    {
        faculty *temp = head;
        p->last = NULL;
        p->next = head;
        temp->last = p;
        head = p;
    }
}*/

int deleteFaculty(char n[])
{ // fxn for deleteFacultyetion of specific data from the linked list
    if (head == NULL)
    {
        printf("Empty records\n");
        return 3;
    }
    int count = 0;
    faculty *temp = head;
    faculty *temp3 = tail;
    faculty *temp2 = head->next;
    faculty *temp1 = tail->last; // faculty initialised second last faculty
    if (head == tail || head->next == NULL)
    {
        head = NULL;
        tail = NULL;
        free(temp);
        return 1;
    }
    if (!strcmp(n, head->name))
    { // if 1st faculty is to be deleteFacultyeted

        head = head->next;
        head->last = NULL;
        temp->next = NULL;
        free(temp);
        return 1;
    }
    else if (!strcmp(n, tail->name))
    { // if last faculty is to be deleteFacultyeted
        tail->last->next = NULL;
        tail = temp1;
        free(temp3);
        return 1;
    }
    else
    {
        do
        {
            temp2 = temp->next;
            if (!strcmp(n, temp->name))
            { // traversing till we find the data in linked list
                faculty *temp2 = temp->last;
                temp2->next = temp->next;
                temp->next->last = temp2;
                free(temp);
                count++;
                return 1;
            }
            else
            {
                temp = temp->next; // otherwise it ll continue traversing
            }
        } while ((temp != NULL) && (count == 0));
        return 0;
    }
}

void traverseFromStart()
{ // function for traversal
    printf("----------------------------Faculty Records(From beginning to end)-------------------------------\n");
    if (head == NULL)
    { // null case
        printf("No records found. Enter i to add record");
    }
    for (faculty *tmp = head; tmp != NULL; tmp = tmp->next)
    { // untill it encounters null,the loop will keep traversing

        printf("NAME: %s     AGE: %d     GENDER: %c     DEPARTMENT: %s\n", tmp->name, tmp->age, tmp->gender, tmp->deptt); // traversal by for loop iteration
    }
}

void traverseFromEnd()
{ // function for traversal
    printf("----------------------------Faculty Records(from End to beginning)-------------------------------\n");
    if (head == NULL)
    { // null case
        printf("No records found. Enter i to add record");
    }
    for (faculty *tmp = tail; tmp != NULL; tmp = tmp->last)
    { // untill it encounters null,the loop will keep traversing

        printf("NAME: %s     AGE: %d     GENDER: %c     DEPARTMENT: %s\n", tmp->name, tmp->age, tmp->gender, tmp->deptt); // traversal by for loop iteration
    }
}

void searchRecord(char n[])
{ // function searching a record by name
    if (head == NULL)
    {
        printf("Empty records\n");
        return;
    }
    int c = 0;
    for (faculty *tmp = head; tmp != NULL; tmp = tmp->next)
    {
        if (!strcmp(n, tmp->name))
        { // if details found by the entered name
            printf("---------------------------------Search Record for %s-----------------------------------\n", n);
            printf("NAME: %s     AGE: %d     GENDER: %c     DEPARTMENT: %s\n", tmp->name, tmp->age, tmp->gender, tmp->deptt);
            c++;
            break;
        }
    }
    if (c == 0)
    { // if no record found
        printf("No record found with this name, Try again");
    }
}

// Main function
int main(void)
{
    char resp = 0;
    char gender;
    int age, x;
    char name[MAX], deptt[MAX];
    printf("Enter i to insert, d to delete and s to searchRecord any record and x to exit\n");
    while (resp != 'x')
    { //'x' will end the program
        printf("Enter your command:");
        scanf("%c", &resp); // fxns to be called as per the input
        if (resp == 'i')
        {
            printf("Enter name of the Faculty:");
            scanf("\n%[^\n]s", name);
            printf("Enter Age of %s:", name);
            scanf("%d", &age);
            printf("Enter Gender of %s(M/F):", name);
            scanf("\n%c", &gender);
            printf("Enter Department of %s:", name);
            scanf("\n%[^\n]s", deptt);
            insertFaculty(name, deptt, gender, age);
            traverseFromStart();
            printf("\n");
            traverseFromEnd();
        }
        else if (resp == 's')
        {
            printf("Enter name of the Faculty:");
            scanf("\n%[^\n]s", name);
            searchRecord(name);
            printf("\n");
        }
        else if (resp == 't')
        {
            traverseFromStart();
            printf("\n");
            traverseFromEnd();
            printf("\n");
        }
        else if (resp == 'd')
        {
            printf("Enter name of the Faculty:");
            scanf("\n%[^\n]s", name); // faculty name to be deleted taken as input
            x = deleteFaculty(name);
            if (x == 1)
            {
                printf("%s's record is deleted\n", name);
                traverseFromStart();
                printf("\n");
                traverseFromEnd();
            }
            else if (x == 0)
            {
                printf("no record found with this name\n", name);
            }
        }
        else if (resp == 'x')
        {
            exit(0);
        }
        else
        {
            printf("Enter any valid key\n");
        }
        fflush(stdin);
    }
    while (head != NULL)
        deleteFaculty(head->name);
    return 0;
}