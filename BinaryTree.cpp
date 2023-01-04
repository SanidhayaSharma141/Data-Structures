/* Name: Sanidhaya Sharma                                     Roll no. CS21B1024                 */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#define MAX 30
//---------------------------------------------------------------------------------------------------------------------//
struct faculty
{
  struct faculty *left;
  char name[MAX];
  char deptt[MAX];
  int age;
  char gender;
  struct faculty *right;
};

typedef struct faculty Faculty;

//---------------------------------------------------------------------------------------------------------------------//
Faculty *root = NULL; // root will always point to top element(root of tree)
Faculty *ptr = NULL;
//---------------------------------------------------------------------------------------------------------------------//
Faculty *create(char name[], char deptt[], char gender, int age) // creating a Faculty
{
  Faculty *temp = (Faculty *)malloc(sizeof(Faculty));
  strcpy(temp->name, name); // copying string to Faculty temp
  strcpy(temp->deptt, deptt);
  temp->age = age;
  temp->gender = gender;
  temp->right = NULL;
  temp->left = NULL;
  return temp;
}

//---------------------------------------------------------------------------------------------------------------------//

Faculty *insert(Faculty *ptr, char name[], char deptt[], char gender, int age) // insertion operation while considering various conditions in order to be inserted in a sorted way
{
  Faculty *tempp = (Faculty *)malloc(sizeof(Faculty));
  if (root == NULL)
  {
    root = create(name, deptt, gender, age);
  }
  else if (ptr == NULL)
  {
    ptr = create(name, deptt, gender, age);

    return ptr;
  }
  else if (strcmp(ptr->name, name) >= 0) // if name is less then the ptr name, insertion will be at left
  {
    tempp = insert(ptr->left, name, deptt, gender, age);
    ptr->left = tempp;
  }
  else if (strcmp(ptr->name, name) < 0) // if name is bigger then the ptr name, insertion will be at right
  {
    tempp = insert(ptr->right, name, deptt, gender, age);
    ptr->right = tempp;
  }
}

//---------------------------------------------------------------------------------------------------------------------//

void search(Faculty *temp, char name[])
{
  if (temp == root)
  {
    printf("\n-------------------------------------------Faculty Records------------------------------------------------\n");
  }
  if (root == NULL) // empty tree condition
  {
    printf("Empty Tree. Press i to insert records\n", name);
  }
  else if (temp == NULL) // ptr is null that means after completion of binary search, we couldnot find the searched element
  {
    printf("Record with name %s not found.\n", name);
  }
  else if (strcmp(temp->name, name) == 0) // name found if it matches
  {
    printf("NAME: %s     AGE: %d     GENDER: %c     DEPARTMENT: %s\n", temp->name, temp->age, temp->gender, temp->deptt);
  }
  else if (strcmp(temp->name, name) > 0) // left condition
  {
    search(temp->left, name);
  }
  else if (strcmp(temp->name, name) < 0) // right condition
  {
    search(temp->right, name);
  }
}

//---------------------------------------------------------------------------------------------------------------------//

Faculty *minFaculty(Faculty *val) // this will be used when Faculty with two child would be deleted to min from below would be needed to replace it
{
  Faculty *temp = val;

  while (temp->left != NULL)
    temp = temp->left;

  return temp;
}

//---------------------------------------------------------------------------------------------------------------------//

void printInOrder(Faculty *tmp)
{
  if (tmp == root)
  {
    printf("\n-------------------------------------------Faculty Records------------------------------------------------\n");
  }
  if (root == NULL)
  {
    printf("Empty Records. Press I to insert a record");
  }
  if (tmp == NULL)
    return;

  printInOrder(tmp->left);
  printf("NAME: %s     AGE: %d     GENDER: %c     DEPARTMENT: %s\n", tmp->name, tmp->age, tmp->gender, tmp->deptt);

  printInOrder(tmp->right);
}

//---------------------------------------------------------------------------------------------------------------------//

Faculty *Delete(Faculty *t_del, char name[], int c)
/*!!!!!note the reason behind int c!!!!
c will make sure that is Faculty with two child is deleted,the line for deletion of minimum i.e
if Faculty 4 is deleted which has two childs the min Faculty that will be replacing it needs to be deleted due to which that line"__
deleted is also shown so this will not let that happen*/
{
  if (root == NULL)
  {
    printf("Empty Tree. Press i to insert. \n", name);
    return NULL;
  }
  if ((root->name == t_del->name) && (root->left == NULL) && (root->right == NULL))
  {
    Faculty *temp = root;
    root = NULL;
    free(temp);
  }
  if (t_del == NULL)
  {
    printf("no record found with name-%s. Enter the mentioned keys for other functions.\n", name);
    return NULL;
  }

  else if (strcmp(t_del->name, name) > 0) // searching at left if smaller than Faculty
    t_del->left = Delete(t_del->left, name, c);

  else if (strcmp(t_del->name, name) < 0) // searching at right if larger than Faculty
    t_del->right = Delete(t_del->right, name, c);

  else
  {
    // if Faculty has two Children i.e left and right both are not NULL
    if ((t_del->left != NULL) && (t_del->right != NULL))
    {
      Faculty *temp = minFaculty(t_del->right);
      if (c != 0)
      {
        printf("Record with name: %s is deleted\n", name);
      }
      strcpy(t_del->name, temp->name);

      t_del->right = Delete(t_del->right, temp->name, 0);
    }
    else
    {

      // if the Faculty has only one child or no child(leaf condition)
      // if(root->left==NULL&&root->right==NULL){
      //   temp==NULL;
      // }
      Faculty *temp;
      if (t_del->left == NULL)
      {
        temp = t_del->right;
      }
      else
      {
        temp = t_del->left;
      }

      if (temp == NULL) // if both are null
      {
        temp = t_del;
        t_del = NULL;
      }
      else
      {
        *t_del = *temp;
      }
      free(temp);
      if (c != 0)
      {
        printf("Record with name: %s is deleted\n", name);
      }
    }
  }
  return t_del;
}

//---------------------------------------------------------------------------------------------------------------------//

int main(void)
{
  char func = 0;
  char gender;
  int age, x;
  char name[MAX], deptt[MAX];
  Faculty *value;
  while (func != 'x') //'x' will end the program
  {
    printf("\n----------Enter i to insert, d to delete and s to search any record and x to exit----\n");
    scanf("%c", &func); // fxns to be called on the basis of whats input is given
    if (func == 'i')
    {
      printf("Enter name of the Faculty:");
      scanf("\n%[^\n]s", name);
      printf("Enter Age of %s:", name);
      scanf("%d", &age);
      printf("Enter Gender of %s(M/F):", name);
      scanf("\n%c", &gender);
      printf("Enter Department of %s:", name);
      scanf("\n%[^\n]s", deptt);                             // element to be pushed in stack taken as input
      Faculty *tmp = insert(root, name, deptt, gender, age); // calling function
      printInOrder(root);
    }
    else if (func == 'd')
    {
      scanf("\n%[^\n]s", name);
      value = Delete(root, name, 1); // calling function
      if (value != NULL)
      {
        printInOrder(root);
      }
    }
    else if (func == 's')
    {
      scanf("\n%[^\n]s", name);
      search(root, name);
    }
    else if (func == 'b')
    {
      printInOrder(root);
    }
    fflush(stdin);
  }
  return 0;
}