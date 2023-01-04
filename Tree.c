#include <stdio.h>
#include <stdlib.h> //included lib
#include <math.h>

struct Node // initialised a tree struct
{
    struct Node *left;
    int data;
    struct Node *right;
};

typedef struct Node node;
node *root = NULL; //root will always point to top element(root of tree)
node *ptr = NULL;

node *create(int data)//creating a node
{
    node *temp = malloc(sizeof(node *));
    temp->data = data;
    temp->right = NULL;
    temp->left = NULL;
    return temp;
}
node *insert(node *ptr, int data)//insertion operation while considering various conditions in order to be inserted in a sorted way
{
    node *tempp = malloc(sizeof(node *));
    if (root == NULL)
    {
        root = create(data);
    }
    else if (ptr == NULL)
    {
        ptr = create(data);

        return ptr;
    }
    else if (ptr->data > data)//if data is less then the ptr data, insertion will be at left
    {
        tempp = insert(ptr->left, data);
        ptr->left = tempp;
    }
    else if (ptr->data < data)//if data is bigger then the ptr data, insertion will be at right
    {
        tempp = insert(ptr->right, data);
        ptr->right = tempp;
    }
}

void search(node *temp, int data, int x)
{
    if (root == NULL)//empty tree condition
    {
        printf("%d not found, empty tree\n", data);
    }
    else if (temp == NULL)//ptr is null that means after completion of binary search, we couldnot find the searched element
    {
        printf("%d not found, last node on path: %d\n", data, x);
    }
    else if (temp->data == data)//data found if it matches
    {
        printf("found %d !\n", data);
    }
    else if (temp->data > data)//left condition
    {
        search(temp->left, data, temp->data);
    }
    else if (temp->data < data)//right condition
    {
        search(temp->right, data, temp->data);
    }
}
void deallocateheap(node* node)
{
    if (node == NULL) return;

    deallocateheap(node->left);
    deallocateheap(node->right);
   
    free(node);
}
// node* searchdel(node *temp,int data){
//     if(root==NULL){

//     }
//     else if(temp==NULL){
//         printf("%d not found",data);
//     }
//     else if(temp->right->data==data){
//         return temp;
//     }
//     else if(temp->left->data==data){
//         return temp;
//     }
//     else if(temp->data>data){
//         searchdel(temp->left,data);
//     }
//     else if(temp->data<data){
//         searchdel(temp->right,data);
//     }
// }

node *min(node *p)//will be useful while deleting
{
    if (p == NULL)
    {
        return NULL;
    }
    else if (p->left != NULL)
    {
        return min(root->left);
    }
    return p;
}

node *delete (node *tempp, int data, node *prev, int x)
{
    node* temporary=malloc(sizeof(node*));
    if (tempp == NULL)//empty condn
    {
        printf("%d not found\n",data);
        return 0;
    }
    else if (tempp == NULL)//null condn of node at end
    {
        return 0;
    }
    if (data > tempp->data)//right condn
    {
        delete (tempp->right, data, tempp, 1);
    }
    else if (data < tempp->data)//left condn
    {
        delete (tempp->left, data, tempp, 0);
    }
    else
    {
        if ((tempp->left == NULL) && (tempp->right == NULL))//leaf condition
        {
            prev->right=NULL;
            prev->left==NULL;
            free(tempp);
            return 0;
        }
        else if ((tempp->left == NULL) || (tempp->right == NULL))//left or right child empty condn
        {
            if (tempp->left == NULL)
            {
                temporary = tempp->right;
                if (x == 0)
                {
                    prev->left = temporary;//linking the child with ancestor of node
                }
                else if (x == 1)
                {
                    prev->right = temporary;//linking the child with ancestor of node
                }
                free(tempp);
            }
            else
            {
                temporary = tempp->left;
                if (x == 0)
                {
                    prev->left = temporary;//linking the child with ancestor of node
                }
                else if (x == 1)
                {
                    prev->right = temporary;//linking the child with ancestor of node
                }
                free(tempp);
            }
        }
        else
        {
            node *q = min(tempp->right);
            tempp->data = q->data;
            tempp->right=delete(tempp->right,tempp->data,tempp,1);
        }
    }
    return tempp;
}

// int delete(node *tmp,int data){
//     node* del=searchdel(root,data);
//     printf("%d\n",del->data);
//     node*datadel=malloc(sizeof(node*));
//     int x;
//     if(del->right->data==data){
//         node*datadel=del->right;
//         x=0;
//     }
//     else if(del->left->data==data){
//         node*datadel=del->left;
//         x=1;
//     }
//     printf("%d",datadel->data);

//     if((datadel->right==NULL)&&(datadel->left==NULL)){
//         free(datadel);
//     }
//     else if(datadel->right==NULL){
//             node* tempdel=datadel->left;
//             if(x==0){
//                 del->right=tempdel;
//             }
//             else if(x==1){
//                 del->left=tempdel;
//             }
//             free(datadel);
//     }
//     // else{
//     //     if(root->data==data){

//     //     }
//     // }

// }

int main(void)
{
    char func = 0;
    int data;
    node *value;
    while (func != 'x')
    {                       //'x' will end the program
        scanf("%c", &func); // fxns to be called on the basis of whats input is given
        if (func == 'i')
        {
            scanf("%d", &data);             // element to be pushed in stack taken as input
            node *tmp = insert(root, data); // calling function
        }
        else if (func == 'd')
        {
            scanf("%d", &data);
            value = delete (root, data,NULL,1); // calling function
        }
        else if (func == 's')
        {
            scanf("%d", &data);
            search(root, data, 0);
        }
        fflush(stdin);
    }
    deallocateheap(root);
    printf("%d",root->data);
    return 0;
}
