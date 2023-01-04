#include <stdio.h>
#include <stdlib.h>

// declared struct for avl tree

struct Node
{
  int value;
  struct Node *left;
  struct Node *right;
  int height; // this will be used inorder to access a node's height for sorting purpose/bal
};
typedef struct Node node;
node *root = NULL;

int maxval(int num1, int num2)
{ // this function will be used while taking the larger height of a node from left and right subtree
  if (num1 > num2)
  {
    return num1;
  }
  else if (num2 > num1)
  {
    return num2;
  }
}
// int maxheight(node*p,node*q){
//     if((p->height)>(q->height)){
//         return p->height +1; //1 would be added including that node as well
//     }
//     else if(p->height<q->height){
//         return q->height +1;  //1 would be added including that node as well
//     }
// }



int height(node *temp)
{ // function to get the height of node declared
  if (temp == NULL)
  {
    return 0;
  }
  else
  {
    return temp->height;//it will return height of the node that is already stored in the struct
  }
}

node *createnode(int value)
{ // fxn to create a new node
  node *tmp = (node *)malloc(sizeof(node));//dynamic memory allocation
  tmp->left = NULL;
  tmp->value = value;
  tmp->height = 1;
  tmp->right = NULL;
  return (tmp);
}

node *RRrotation(node *rnode)
{ // function for right rotation
  node *t = rnode->left;
  node *p = t->right;

  t->right = rnode;
  rnode->left = p;

  rnode->height = maxval(height(rnode->left), height(rnode->right)) + 1;
  t->height = maxval(height(t->left), height(t->right)) + 1;

  return t;
}


node *LLrotation(node *rnode)//left rotation fxn
{
  node *t = rnode->right;
  node *p = t->left;

  t->left = rnode;
  rnode->right = p;

  rnode->height = maxval(height(rnode->left), height(rnode->right)) + 1; // max height of the node from bottom will be 1+ maximum of left or right height as that node will be counted too
  t->height = maxval(height(t->left), height(t->right)) + 1;             // max height of the node from bottom will be 1+ maximum of left or right height as that node will be counted too

  return t;
}

int balfac(node *node1)
{ // fxn to find bal factor of a node
  if (node1 == NULL)
  {
    return 0;
  }
  else
  {
    int val = height(node1->left) - height(node1->right);//balancing factor=right child height-left child height
    return val;
  }
}
node *minnode(node *val)//this will be used when node with two child would be deleted to min from below would be needed to replace it
{
  node *temp = val;

  while (temp->left != NULL)
    temp = temp->left;

  return temp;
}

node *insert(node *node, int value) // fxn to insert the given value to avl tree in sorted way
{                  
  if (node == NULL) // NULL node condition
    return (createnode(value));

  if (value < node->value)
    node->left = insert(node->left, value);
  else if (value > node->value)
    node->right = insert(node->right, value);
  else
    return node;

  // balancing the tree...llrotation and rightrotation fxns would be used..for RL and LR we will use both in their respective sequence
  node->height = 1 + maxval(height(node->left),height(node->right));

  int bal = balfac(node);
  if (bal > 1 && value < node->left->value){
    return RRrotation(node);}

  if (bal < -1 && value > node->right->value){
    return LLrotation(node);}

  if (bal > 1 && value > node->left->value)
  {
    node->left = LLrotation(node->left);
    return RRrotation(node);
  }

  if (bal < -1 && value < node->right->value)
  {
    node->right = RRrotation(node->right);
    return LLrotation(node);
  }

  return node;
}

//Ques Part----Traverse in BFS order-------


void printlev(node *root, int l)
{
  if (root == NULL)
  {
    return;
  }
  if (l == 0)
  {
    printf("%d ", root->value);
  }
  else if (l > 0)
  {
    printlev(root->left, l - 1);
    printlev(root->right, l - 1);
  }
}


void traverseBFS(node *root)
{
  int val = height(root);//loop will run val times
  for (int i = 0; i < val; i++)
  {
    printlev(root, i);
  }
  printf("\n");
}
//fxn for deallocation of heap before end of program
void deallocateheap(node* node) 
{
    if (node == NULL) {
      return;
    }

    deallocateheap(node->left);
    deallocateheap(node->right);
   
    free(node);
}

//Ques Part  ----Deleting node(Balanced way)------
node *Delete(node *root, int value,int c)
// !!!!!note the reason behind int c!!!!
//c will make sure that is node with two child is deleted,the line for deletion of minimum i.e 
// if node 4 is deleted which has two childs the min node that will be replacing it needs to be deleted due to which that line"__ 
// deleted is also shown so this will not let that happen
{
  // deletion will be done by BST algorithm only but the sorting/balancing will be done after deletion
  if (root == NULL)
  {
    printf("%d not found\n", value);
    return NULL;
  }

  else if (value < root->value) // searching at left if smaller than node
    root->left = Delete(root->left, value,c);

  else if (value > root->value) // searching at right if larger than node
    root->right = Delete(root->right, value,c);

  else
  {
    if ((root->left != NULL) && (root->right != NULL))
    {
      node *temp = minnode(root->right);
      if(c!=0)
      {printf("%d deleted\n", value);
      }
      root->value = temp->value;

      root->right = Delete(root->right, temp->value,0);
    }
    else{
      //if node has two Children i.e left and right both are not NULL
     // if the node has only one child or no child(leaf condition)
      // if(root->left==NULL&&root->right==NULL){
      //   temp==NULL;
      // }
      node*temp;
      if(root->left==NULL){
        temp=root->right;
      }
      else{
        temp=root->left;
      }

      if (temp == NULL)//if both are null
      {
        temp = root;
        root = NULL;
      }
      else
      {
        *root = *temp;
      }
      free(temp);
      if(c!=0){
      printf("%d deleted\n", value);}
    }
    
  }

  if (root == NULL){
    return root;
  }
  // sort the tree now to make it bald similar to what is done while insertion

  root->height = 1 + maxval(height(root->left), height(root->right)); // height algorithm as commented earlier too

  int bal = balfac(root);//balancing factor value that ll be used later
  if (bal > 1 && balfac(root->left) >= 0){// LLcondn
    return RRrotation(root);
  }

  else if (bal < -1 && balfac(root->right) <= 0){//RR condn
    return LLrotation(root);
  }
  else if (bal > 1 && balfac(root->left) < 0)//LR condn
  {
    root->left = LLrotation(root->left);//left will be done on child of node and right will be done on node
    return RRrotation(root);
  }
  else if (bal < -1 && balfac(root->right) > 0)//RL condn
  {
    root->right = RRrotation(root->right);//right will be done on child of node and left will be done on node
    return LLrotation(root);
  }

  return root;
}





int main()
{
  char func = 0;
  int value;
  while (func != 'x')//'x' will end the program
  {                     
    scanf("%c", &func); // fxns to be called on the basis of whats input is given

    if (func == 'i')
    {
      scanf("%d", &value); 
      root = insert(root, value); // calling function
    }
    else if (func == 'd')
    {
      scanf("%d", &value);
      root = Delete(root, value,1); // calling function
    }
    else if (func == 'b')
    {
      traverseBFS(root);
    }
    // else if(func=='j'){
    //   delete(root);
    // }
    // else{
    //   printf("enter either i,d,b or x");
    // }
    fflush(stdin);
  }
  deallocateheap(root);//deallocating heap

  return 0;
}
