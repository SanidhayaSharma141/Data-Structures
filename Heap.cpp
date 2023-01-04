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
    bool findRecord(int val)
    {
        for (int i = 0; i < size; i++)
        {
            if (arr[i] == val)
            {
                return true;
            }
        }
        return false;
    }
    void display()
    {
        if (size <= 0)
        {
            cout << "Empty Records/Heap. Enter i to insert" << endl;
            return;
        }
        cout << "------------------------Records------------------------------" << endl;
        for (int i = 0; i < size; i++)
        {
            cout << "Age: " << arr[i] << "     Parent:" << arr[parent(i)];
            if (left(i) < size)
            {
                cout << "     Left child: " << arr[left(i)];
            }
            else
            {
                cout << "     Left child: - ";
            }
            if (right(i) < size)
            {
                cout << "     Right child: " << arr[right(i)] << endl;
            }
            else
            {
                cout << "     Right child: - " << endl;
            }
        }
    };
    void swapVal(int *a, int *b)
    {
        int temp = *a;
        *a = *b;
        *b = temp;
    }
    int deleteMin();
    void insert(int age);
    void heapify(int val);
    int findmin();
};

void heapAge::insert(int age)
{
    if (age <= 0)
    {
        cout << "Age cannot be lesser or equal to zero. Enter valid age." << endl;
        return;
    }
    if (findRecord(age) == true)
    {
        cout << "Record with same age exists. Kindly enter other record." << endl;
        return;
    }
    if (size == capacity)
    {
        cout << "Maximum Capacity reached. Kindly delete some data to add more records." << endl;
        return;
    }
    size++;
    arr[size - 1] = age;
    for (int i = size - 1; arr[parent(i)] > arr[i] && i != 0;)
    {
        swapVal(&arr[parent(i)], &arr[i]);
        i = parent(i);
    }
    cout << "Record with Age: " << age << " inserted successfully." << endl;
}
void heapAge::heapify(int val)
{
    int minVal = val;
    int leftVal = left(val);
    int rightVal = right(val);
    if (arr[minVal] > arr[leftVal] && leftVal < size)
    {
        minVal = leftVal;
    }
    if (arr[minVal] > arr[rightVal] && rightVal < size)
    {
        minVal = rightVal;
    }
    if (minVal != val)
    {
        swapVal(&arr[val], &arr[minVal]);
        heapify(minVal);
    }
}
int heapAge::findmin()
{
    if (size == 0)
    {
        cout << "Empty Heap" << endl;
        return -1;
    }
    return arr[0];
}

int heapAge::deleteMin()
{
    if (size <= 0)
    {
        cout << "Empty Records/Heap. Enter i to insert" << endl;
        return INT_MAX;
    }
    if (size == 1)
    {
        cout << arr[size - 1] << " deleted from heap" << endl;
        size--;
        return arr[0];
    }
    int minVal = findmin();
    // cout << "size: " << size << endl;
    // cout << "before swapping" << endl;
    // cout << arr[0] << endl;
    // cout << arr[size - 1] << endl;
    arr[0] = arr[size - 1];
    // cout << "after swapping" << endl;
    // // cout << arr[0] << endl;
    // cout << arr[size - 1] << endl;
    size--;
    // display();
    // cout << "size: " << size << endl;
    heapify(0);
    cout << minVal << " deleted from heap" << endl;
    return minVal;
}

//---------------------------------------------------------------------------------------------------------------------//
// Main Function
//---------------------------------------------------------------------------------------------------------------------//
int main()
{
    int cap;
    cout << "Enter the maximum capacity of heap records: "; // we could have used vector<int> if that would have been allowed
    cin >> cap;
    while (cap <= 0)
    {
        cout << "Capacity cannot be less than or equal to zero.Enter valid capacity of the records: ";
        cin >> cap;
    }
    heapAge h1(cap);
    char func = 0;
    int age, x;
    // #ifndef LOCAL
    //     freopen("input.txt", "r", stdin);
    //     freopen("output.txt", "w", stdout);
    // #endif
    while (func != 'x') //'x' will end the program
    {
        cout << "\n----------Enter i to insert, m to find the minimum age record,d to delete minimum age record, t for traversal of records and x to exit----\n";
        cin >> func; // fxns to be called on the basis of whats input is given
        if (func == 'i')
        {
            cout << "Enter Age : ";
            cin >> age;
            h1.insert(age);
        }
        if (func == 'm')
        {
            if (h1.findmin() != -1)
            {

                cout << "Minimum value in the heap is: " << h1.findmin() << endl;
            }
        }
        if (func == 'd')
        {
            x = h1.deleteMin();
        }
        else if (func == 't')
        {
            h1.display();
        }
        fflush(stdin);
    }
    return 0;
}