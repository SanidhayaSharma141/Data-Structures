#include<stdio.h>
#include<stdlib.h>

struct Node //created a struct for linked list that will act as stack
{
    int data; 
    struct Node *next;
};
typedef struct Node node;
node *top=NULL;//initialised top..in our stack using linked list...head will act as top and node at beginning will act as top


//push fxn
void push(int data){
    node* ptr=malloc(sizeof(node));//declared node that will store the data
    ptr->data=data;
    if(top==NULL){//empty stack condition
        ptr->next=NULL;
        top=ptr;
    }
    else{
        ptr->next=top;
        top=ptr;//now top will point to the newly added node
    }
}
//pop fxn
void pop(){
    node* temp=top;
    if(top==NULL){//empty stack condition
        printf("stack underflow");
    }
    else{
        printf("%d",top->data);
        top=top->next;
        free(temp);
    }
}
//note: for traversing/checking the stack you can run this code below
// void print(){
//     if(top==NULL){
//         printf("stack underflow");
//     }
//     else{
//    for(node* tempp=top;tempp!=NULL;tempp=tempp->next){
//        printf("%d ",tempp->data );
//    }
//    printf("\n");}
// }




int main(void){   
    char func=0;
    int data;
    while (func!='x'){//'x' will end the program
        scanf("%c",&func);//fxns to be called on the basis of whats input is given
        if (func=='P'){
            scanf("%d" ,&data);//element to be pushed in stack taken as input
            push(data);//calling function
        }
        else if (func=='p'){
            pop();//calling function
            printf("\n");
        }
        // else if(func=='t'){
        //     print();
        // }
        fflush(stdin);
    }
    while(top!=NULL) pop();
    return 0;
}

