#include<stdio.h>
#include<math.h>
#include<stdlib.h>

struct Node //created a struct for linked list
{
    int data; 
    struct Node *p;
};
typedef struct Node node;
node *head=NULL;//initialised head(start)



void insertll(int n) //insertion fxn made to add nodes
{
    node *temp =(node*)malloc(sizeof(node)); //used dynamic allocation
    temp->data=n; 
    temp->p=NULL;
    if (head==NULL)
    {
        head=temp;
    }
    else{
        node *tempp=head;
        for(;tempp->p!=NULL;) {
            tempp=tempp->p;
        }
        tempp->p=temp;
    }
}



void traverse(){//function for traversing the linked list

    for(node*tempp=head;tempp!=NULL;tempp=tempp->p)//untill it encounters null,the loop will keep traversing
    printf("%d ",tempp->data);
}



void delt(int n){//function for delete the given node from the linked list
    if(head->data==n){//if node at head is to be deleted
        node *tempp=head->p;
        free(head);
        head=tempp;
    }
    else//other cases
    for(node *tempp=head;tempp->p!=NULL;tempp=tempp->p){
        if(tempp->p->data==n){
            node *aptr=tempp->p;
            tempp->p=tempp->p->p;
            free(aptr);
            return;
        }
    }  
}



void minandmax(){//function to find min and max node and print it
    int max=0,min=head->data;//initially taking max and min default value
     for(node*tempp=head;tempp!=NULL;tempp=tempp->p){//loop untill it gets null value
         if(max< tempp->data){//condition for max
             max=tempp->data;
         }
        if(min> tempp->data) {//condition for min
            min=tempp->data;
        }
     }
     printf("%d %d",min,max);
}


//Main function
int main(void){   
    char resp=0;
    int num;
    while (resp!='x'){//'x' will end the program
        scanf("%c",&resp);//fxns to be called as per the input
        if (resp=='i'){
            scanf("%d" ,&num);//element to be inserted taken as input
            insertll(num);//calling function
        }
        else if (resp=='t'){
            traverse();//calling function
        printf("\n");
        }
        else if (resp=='d'){
            scanf("%d", &num);//element to be deleted taken as input
            delt(num);//calling function
        }
        else if(resp=='m'){
            minandmax();
        printf("\n");//calling function
        }
        fflush(stdin);
    }
    while(head!=NULL) delt(head->data);
    return 0;
}
