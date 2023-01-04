// Sanidhaya Sharma CS21B1024
// Following is the Array Implementation of Circular Queue with two operations-Insert and Delete(as per the assignment)

#include <stdio.h>
#define MAX_SIZE 3 // Note: I have defined max size of Array to be 8, you can change as per your convenience
int arrayAge[MAX_SIZE];
int front = -1, end = -1; // initialised front and end as -1

void enqueue(int age)
{
  if ((front == 0 && end == MAX_SIZE - 1) ||
      (end == (front - 1) % (MAX_SIZE - 1))) // queue overflow condition
  {
    printf("\n------------Queue Overflow--------------\n");
    return;
  }

  else if (front == -1) // empty queue condition
  {
    front = end = 0;
    arrayAge[end] = age;
  }

  else if (end == MAX_SIZE - 1 && front != 0)
  {
    end = 0;
    arrayAge[end] = age;
  }

  else
  {
    end++;
    arrayAge[end] = age;
  }
  printf("-----------%d age is added to the records.---------\n", age);
}
int dequeue() // function to delete first element in queue
{
  if (front == -1) // queue underflow condition
  {
    printf("\n-----------------Queue Underflow--------------------\n");
    return -1;
  }

  int data = arrayAge[front];
  arrayAge[front] = -1;
  if (front == end) // single element condition
  {
    front = -1;
    end = -1;
  }
  else if (front == MAX_SIZE - 1)
    front = 0;
  else
    front++;

  return data;
}

// Display the queue
void traverse()
{
  if (front == -1)
  {
    printf("-------------Empty Queue-------------\n");
    return;
  }
  printf("Age Records is as follows: ");
  if (end >= front)
  {
    for (int i = front; i <= end; i++)
      printf("%d ", arrayAge[i]);
  }
  else
  {
    for (int i = front; i < MAX_SIZE; i++)
      printf("%d ", arrayAge[i]);

    for (int i = 0; i <= end; i++)
      printf("%d ", arrayAge[i]);
  }
  printf("\n");
  // printf(" \nend next=%d \n", arrayAge[(end+1)/MAX_SIZE]);
}

// Main function
int main(void)
{
  char resp = 0;
  int age, x;
  printf("---------------------Enter i to insert, d to delete and x to exit---------------------\n");
  while (resp != 'x')
  { //'x' will end the program
    printf("Enter your command: ");
    scanf("%c", &resp); // fxns to be called as per the input
    if (resp == 'i')
    {
      printf("Enter Age of faculty: ");
      scanf("%d", &age);
      if (age <= 0)
      {
        printf("Enter Valid Age. Enter Again: ");
        scanf("%d", &age);
      }
      enqueue(age);
      traverse();
    }
    else if (resp == 'd')
    {
      x = dequeue();
      if (x != -1)
      {
        printf("%d is deleted\n", x);
        traverse();
      }
    }
    else if (resp == 'x')
    {
      continue;
    }
    else
    {
      printf("Enter any valid key: \n");
    }
    fflush(stdin);
  }
  while (!front == -1)
    dequeue();
  return 0;
}
