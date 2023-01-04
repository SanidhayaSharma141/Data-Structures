#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#define MAX 100
struct faculty // faculty struct  declared
{
    char name[MAX];
    char deptt[MAX];
    int age;
    char gender;
    struct faculty *next;
};
typedef struct faculty Faculty;
Faculty *head = NULL; // declared head as null

void traverse()
{ // function for traversal
    if (head == NULL)
    {
        printf("Empty list\n");
    }
    printf("----------------------------Faculty Records-------------------------------\n");
    if (head == NULL)
    { // null case
        printf("No records found. Enter i to add record\n");
    }
    for (Faculty *tmp = head; tmp != NULL; tmp = tmp->next)
    { // untill it encounters null,the loop will keep traversing

        printf("NAME: %s     AGE: %d     GENDER: %c     DEPARTMENT: %s\n", tmp->name, tmp->age, tmp->gender, tmp->deptt); // traversal by for loop iteration
    }
}

void insertRecord(char name[], char deptt[], char gender, int age) // insertion function to add Faculties details
{
    Faculty *temp = (Faculty *)malloc(sizeof(Faculty));
    strcpy(temp->name, name); // copying string to node temp
    strcpy(temp->deptt, deptt);
    temp->age = age;
    temp->gender = gender;
    temp->next = NULL;
    if (head == NULL) // null case
    {
        head = temp;
        printf("%s's record is added\n", name);
    }
    else
    {
        Faculty *tmp = head; // else it will be linked to last node
        for (; tmp->next != NULL;)
        {
            tmp = tmp->next;
        }
        tmp->next = temp;
        printf("%s's record is added\n", name);
    }
    traverse();
}

void searchRecord(char n[])
{ // function searching a record by name
    int c = 0;
    for (Faculty *tmp = head; tmp != NULL; tmp = tmp->next)
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

int deleteRecord(char n[])
{ // function for delete the given Faculty from the list
    if (head == NULL)
    {
        return 0;
    }
    if (!strcmp(n, head->name))
    { // if faculty details to be deleted is the head of the LL
        Faculty *tmp = head;
        head = head->next;
        free(tmp);
        return 1;
    }
    else // else it will traverse to look for the details
        for (Faculty *tmp = head; tmp->next != NULL; tmp = tmp->next)
        {
            if (!strcmp(n, tmp->next->name))
            {
                Faculty *aptr = tmp->next;
                tmp->next = tmp->next->next;
                free(aptr);
                return 1;
            }
        }

    printf("No record found with this name, Try again\n"); // no record case

    return 0;
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
            insertRecord(name, deptt, gender, age);
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
            traverse();
            printf("\n");
        }
        else if (resp == 'd')
        {
            printf("Enter name of the Faculty:");
            scanf("\n%[^\n]s", name); // faculty name to be deleted taken as input
            x = deleteRecord(name);
            if (x != 0)
            {
                printf("%s's record is deleted\n", name);
            }
            traverse();
        }
        else if (resp == 'x')
        {
            continue;
        }
        else
        {
            printf("Enter any valid key\n");
        }
        fflush(stdin);
    }
    while (head != NULL)
        deleteRecord(head->name);
    return 0;
}