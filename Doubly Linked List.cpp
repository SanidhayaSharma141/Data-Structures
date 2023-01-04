#include<stdio.h>
#include<stdlib.h> //included lib
#include<math.h>

struct Node //initialised a linked list
{
    struct Node *last;
    int data; 
    struct Node *next;
};

typedef struct Node node;
node* tail=NULL;//initialised tail that ll be used everywhere..no need of head...will directly use tail->next to go to first node

node* addemp(int data){//for adding to empty list
    node* tmp=malloc(sizeof( node));
    tmp->last=tmp;
    tmp->data=data;
    tmp->next=tmp;
    return tmp;
}

node* insert(int data){//fxn to insert
    node* p=addemp(data);
    if(tail==NULL){//null case
        tail=p;
    }
    else{
        node* tmp=tail->next;//nodes declared
        node* tmp1=tmp->next;
        if(data>=tail->data){//if the entered data is larger than tail, insertion will be at end
            p->next=tmp;
            p->last=tail;
            tail->next=p;
            tmp->last=p;
            tail=p;
            return tail;
        }
        else if(data<=tmp->data){//if the entered data is smaller than 1st node, insertion will be at beginning
            p->last=tail;
            p->next=tmp;
            tmp->last=p;
            tail->next=p;
            return tail;
        }
        else{//otherwise it ll traverse till it finds two consecutive datas which satisy the condition that data is between the range of two.
            do
            {
                if((data>=tmp->data)&&(data<tmp1->data)){
                    tmp->next=p;
                    p->last=tmp;
                    tmp1->last=p;
                    p->next=tmp1;
                    return tail;
                }
                //will keep traversing
                tmp=tmp->next;
                tmp1=tmp1->next;
            
            } while (tmp!=tail->next);//till one round, it ll traverse
            
        }

    }
    return tail; 
}
void neighbours(int num){
    if (tail==NULL){//null case
        printf("No elements/null");
    }
    else{
        node* temp=tail->next;//node initialised
        do
        {
            if(temp->data==num){//while traversing, once it finds the data=data of node,it ll print last and next as the neighbour
                printf("%d %d",temp->last->data,temp->next->data);
                return;
            }
            temp=temp->next;
        } while (temp!= tail->next);
         
    }
}
void del(int num){//fxn for deletion of specific data from the linked list
    int count=0;
    node* temp=tail->next;//node initialised
    node* temp2=temp->next;//node initialised 2nd node
    node* temp1=tail->last;//node initialised second last node
    if(num==temp->data){//if 1st node is to be deleted
        tail->next=temp2;
        temp->next->last=tail;
        free(temp);
    }
    else if(num==tail->data){//if last node is to be deleted
        temp1->next=tail->next;
        tail->next->last=temp1;
        free(tail);
        tail=temp1;
    }
    else{
        do
        {
            if(temp->data==num){//traversing till we find the data in linked list
                node* temp2=temp->last;
                temp2->next=temp->next;
                temp->next->last=temp2;
                free(temp);
                count++;
            }
            else{temp=temp->next;//otherwise it ll continue traversing
            temp2=temp2->next;
            }
        } while ((temp!= tail->next)&&(count==0));
    }
}
//NOTE!!!!!!!!!-use this for any confusion( to print the linked list)
/*void printdata(){
    if(tail==NULL){
        printf("no node");
        }
    else{
            node*temp=tail->next;
            do{
                printf("%d ",temp->data);
                temp=temp->next;
            }while(temp!=tail->next);
        }
    
}*/





//Main function
int main(void){   
    char func=0;
    int data;
    while (func!='x'){//'x' will end the program,though it is not written
        scanf("%c",&func);//fxns to be called as per the insert
        if (func=='i'){
            scanf("%d" ,&data);//element to be inserted taken as insert
            insert(data);//calling function
        }
        else if (func=='c'){
            scanf("%d" ,&data);
            neighbours(data);//calling function
        printf("\n");
        }
        else if (func=='d'){
            scanf("%d", &data);//element to be deleted taken as insert
            del(data);//calling function
        }
        //NOTE!!!!!!!!!-use this for any confusion( to print the linked list)
        /*else if(func=='p'){
            printdata();
        }*/
        fflush(stdin);
    }
    return 0;
}