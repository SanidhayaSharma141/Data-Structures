/*Name: Sanidhaya Sharma                     Roll no. CS21B1024
assignment: Implementation of heap sort                             */
#include <bits/stdc++.h>
using namespace std;

class heapAge
{
    int *arr;
    int size;
    int capacity;

public:
    heapAge(int c)
    {
        capacity = c;
        arr = new int[c];
        memset(arr, 0, sizeof(arr));
        size = 0;
    };
    int parent(int i)
    {
        return (i - 1) / 2;
    }
    int left(int i)
    {
        return (2 * i) + 1;
    }
    int right(int i)
    {
        return (2 * i) + 2;
    }
    void display()
    {
        if (size <= 0)
        {
            cout << "Empty Records/Heap. Enter i to insert" << endl;
            return;
        }
        for (int i = 0; i < size; i++)
        {
            cout << arr[i] << " ";
        }
        cout << endl;
    };
    void swapVal(int *a, int *b)
    {
        int temp = *a;
        *a = *b;
        *b = temp;
    }
    // int deletemax();
    void sortHeap();
    void insert(int age);
    void maxHeapify(int val, int n);
    // int findmax();
};
void heapAge::insert(int age)
{
    if (size == capacity)
    {
        cout << "Maximum Capacity reached. Kindly delete some data to add more records." << endl;
        return;
    }
    size++;
    arr[size - 1] = age;
    for (int i = size - 1; arr[parent(i)] < arr[i] && i != 0;)
    {
        swapVal(&arr[parent(i)], &arr[i]);
        i = parent(i);
    }
}

// void heapAge::maxHeapify(int val, int n)
// {
//     int maxVal = val;
//     int leftVal = left(val);
//     int rightVal = right(val);
//     if (arr[val] < arr[leftVal] && (leftVal < n && arr[rightVal] < arr[leftVal]))
//     {
//         maxVal = leftVal;
//     }
//     else if (arr[val] < arr[rightVal] && (rightVal < n && arr[rightVal] > arr[leftVal]))
//     {
//         maxVal = rightVal;
//     }
//     if (maxVal != val)
//     {
//         swapVal(&arr[val], &arr[maxVal]);
//         maxHeapify(maxVal, n);
//     }
// }
void heapAge::maxHeapify(int val, int n)
{

    int maxVal = val;
    int leftValue = left(val);
    int rightValue = right(val);
    if ((leftValue < n) && (arr[leftValue] > arr[maxVal]))
        maxVal = leftValue;
    if ((rightValue < n) && (arr[rightValue] > arr[maxVal]))
        maxVal = rightValue;
    if (maxVal != val)
    {
        swapVal(&arr[val], &arr[maxVal]);

        maxHeapify(maxVal, n);
    }
}
// int heapAge::deletemax()
// {
//     if (size <= 0)
//     {
//         return INT_MAX;
//     }
//     if (size == 1)
//     {
//         return arr[0];
//     }
//     int maxVal = findmax();
//     swapVal(&arr[0],&arr[size-1]);
//     maxHeapify(0,size);
//     cout << maxVal << " deleted from heap" << endl;
//     return maxVal;
// }

void heapAge::sortHeap()
{
    for (int i = size - 1; i > 0; i--)
    {
        // if (arr[0] > arr[i])
        // {
        swapVal(&arr[0], &arr[i]);
        // }
        maxHeapify(0, i);
        // cout << "after heapify"
        //      << " ";
        // display();
    }
}
int main()
{
    int size, age;
    cout << "Enter the Maximum Size of Age Records: ";
    cin >> size;
    while (size <= 0)
    {
        cout << "Capacity cannot be less than or equal to zero.Enter valid capacity of the records: ";
        cin >> size;
    }
    heapAge h1(size);
    for (int i = 0; i < size; i++)
    {

        cin >> age;
        h1.insert(age);
    }
    h1.sortHeap();
    cout << "--------------------------Sorted Records------------------------" << endl;
    h1.display();

    return 0;
}

// ----------------------for code with use of array only, uncomment this and comment the above code----------------
/*
#include <bits/stdc++.h>
using namespace std;

void swapVal(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

int left(int val)
{
    return 2 * val + 1;
}
int right(int val)
{
    return 2 * val + 2;
}
int lastInternalNode(int val)
{
    return val / 2 - 1;
}
void maxHeapify(int arr[], int n, int val)
{

    int maxVal = val;
    int leftValue = left(val);
    int rightValue = right(val);
    if ((leftValue < n) && (arr[leftValue] > arr[maxVal]))
        maxVal = leftValue;
    if ((rightValue < n) && (arr[rightValue] > arr[maxVal]))
        maxVal = rightValue;
    if (maxVal != val)
    {
        swapVal(&arr[val], &arr[maxVal]);

        maxHeapify(arr, n, maxVal);
    }
}
void heapSort(int arr[], int size)
{

    for (int i = lastInternalNode(size); i >= 0; i--) // last internal node is at size-1/2
    {
        maxHeapify(arr, size, i);
    }

    for (int i = size - 1; i > 0; i--)
    {
        swapVal(&arr[0], &arr[i]);

        maxHeapify(arr, i, 0);
    }
}

int main()
{
    int size, age;
    cout << "Enter the Maximum Size of Age Records: ";
    cin >> size;
    int arr[size];
    for (int i = 0; i < size; i++)
    {
        cin >> arr[i];
    }
    cout << "Records before sorting: ";
    for (int i = 0; i < size; i++)
    {
        cout << arr[i] << " ";
    }
    cout << endl;
    heapSort(arr, size);
    cout << "Records after sorting: ";
    for (int i = 0; i < size; i++)
    {
        cout << arr[i] << " ";
    }
    cout << endl;
    return 0;
}
*/