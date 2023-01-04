/*
    Name: Sanidhaya Sharma
    Roll NO: CS21B1024
    Asssignment: Threaded Binary tree for faculty
*/
#include <bits/stdc++.h>
using namespace std;

struct faculty
{
    struct faculty *left;
    string name;
    string deptt;
    int age;
    char gender;
    bool leftThread;
    bool rightThread;
    struct faculty *right;
    faculty(string name, string deptt, char gender, int age) // constructor
    {
        this->name = name;
        this->deptt = deptt;
        this->age = age;
        this->gender = gender;
    }
    // faculty(faculty f){
    //     name=f->name; deptt=f->deptt; age=f->age; gender=f->gender;
    // }
};

typedef struct faculty Faculty;

//---------------------------------------------------------------------------------------------------------------------//
Faculty *root = NULL; // root will always point to top element(root of tree)
//---------------------------------------------------------------------------------------------------------------------//

//---------------------------------------------------------------------------------------------------------------------//
// Insertion function
//---------------------------------------------------------------------------------------------------------------------//
Faculty *insert(string &name, string &deptt, char &gender, int &age) // insertion function
{
    Faculty *parent = NULL;
    for (Faculty *ptr = root; ptr != NULL;)
    {
        parent = ptr;
        if (ptr->name == name)
        {
            cout << "Record Already Exists. Enter i to insert other records." << endl; // duplicate case
            return root;
        }
        if (ptr->name > name)
        { // if the name is lexiographically lesser tham  pointer's name, it would go to right pointer to again compare. it will break once it reaches the designated position        {
            if (ptr->leftThread == true)
            {
                break;
            }
            else
            {
                ptr = ptr->left;
            }
        }
        else if (ptr->name < name) // if the name is lexiographically greater tham  pointer's name, it would go to right pointer to again compare.it will break once it reaches the designated position
        {
            if (ptr->rightThread == true)
            {
                break;
            }
            else
            {
                ptr = ptr->right;
            }
        }
    }
    // now we are having  the position for insertion and its parent as well
    Faculty *t = new Faculty(name, deptt, gender, age);
    t->leftThread = t->rightThread = true;

    if (parent == NULL) // empty tree condition
    {
        root = t;
        root->left = root->right = NULL;
    }
    else if (parent->name > name) // left child insertion case
    {
        t->left = parent->left;
        t->right = parent;
        parent->left = t;
        parent->leftThread = false;
    }
    else if (parent->name < name) // right child insertion case
    {
        t->right = parent->right;
        t->left = parent;
        parent->right = t;
        parent->rightThread = false;
    }
    return root; // returns the root of the tree
}

//---------------------------------------------------------------------------------------------------------------------//
// Search record Function
//---------------------------------------------------------------------------------------------------------------------//

void searchRecord(Faculty *temp, string &name)
{
    if (temp == root)
    {
        cout << "\n-------------------------------------------Search Records for: " << name << "------------------------------------------------\n";
    }
    if (root == NULL) // empty tree condition
    {
        cout << "Empty Tree. Press i to insert records\n";
    }
    else if (temp == NULL) // ptr is null that means after completion of binary searchRecord, we couldnot find the searched element
    {
        cout << "Record with name" << name << "not found.\n";
    }
    else if (temp->name == name) // name found if it matches
    {
        cout << "NAME:" << temp->name
             << "       AGE:" << temp->age << "      GENDER: " << temp->gender << "       DEPARTMENT: " << temp->deptt;
        if (temp->left != NULL && temp->leftThread == true)
        {
            cout << "   LEFT PARENT:" << temp->left->name;
        }
        else
        {
            cout << "   LEFT PARENT:    -   ";
        }
        if (temp->right != NULL && temp->rightThread == true)
        {
            cout << "   RIGHT PARENT:   " << temp->right->name << endl;
        }
        else
        {
            cout << "   RIGHT PARENT:   -   " << endl;
        }
    }
    else if (temp->name > name) // left condition
    {
        if (temp->leftThread == false)
        {
            searchRecord(temp->left, name);
        }
        else // if we reach the ending node which lexiographically satisfies the condition. It would mean it isnt in the tree
        {
            cout << "Record with Name: " << name << " not found.\n";
        }
    }
    else if (temp->name < name) // right condition
    {
        if (temp->rightThread == false)
        {
            searchRecord(temp->right, name);
        }
        else
        {
            cout << "Record with Name: " << name << " not found.\n";
        }
    }
}

//---------------------------------------------------------------------------------------------------------------------//
//   To Print in Order Traversal
//---------------------------------------------------------------------------------------------------------------------//

void TBTinOrderTraversal(Faculty *fac)
{
    if (fac == root)
    {
        cout << "\n-------------------------------------------Faculty Records------------------------------------------------\n";
    }
    if (root == NULL)
    {
        cout << "Empty Records. Press i to insert a record" << endl;
    }
    if (fac == NULL)
        return;

    if (fac->leftThread == false)
    {
        TBTinOrderTraversal(fac->left);
    }
    cout << "NAME:" << fac->name
         << "       AGE:" << fac->age << "      GENDER: " << fac->gender << "       DEPARTMENT : " << fac->deptt;
    if (fac->left != NULL && fac->leftThread == true)
    {
        cout << "    LEFT PARENT:" << fac->left->name;
    }
    else
    {
        cout << "    LEFT PARENT:    -    ";
    }
    if (fac->right != NULL && fac->rightThread == true)
    {
        cout << "    RIGHT PARENT:   " << fac->right->name << endl;
    }
    else
    {
        cout << "    Right PARENT:    -   " << endl;
    }

    if (fac->rightThread == false)
    {
        TBTinOrderTraversal(fac->right);
    }
}

Faculty *inOrderSuccessor(Faculty *ptrSuc)
{
    if (ptrSuc->rightThread == true)
        return ptrSuc->right;

    ptrSuc = ptrSuc->right;
    while (ptrSuc->leftThread == false)
        ptrSuc = ptrSuc->left;

    return ptrSuc;
}
Faculty *inOrderPredecessor(Faculty *ptrPre)
{
    if (ptrPre->leftThread == true)
        return ptrPre->left;

    ptrPre = ptrPre->left;
    while (ptrPre->rightThread == false)
        ptrPre = ptrPre->right;
    return ptrPre;
}

// //---------------------------------------------------------------------------------------------------------------------//
// FUNCTION TO DELETE RECORD
// //---------------------------------------------------------------------------------------------------------------------//
Faculty *deleteRecord(string name)
{
    bool found = false;
    Faculty *parent = NULL;
    Faculty *ptr = root;
    for (; ptr != NULL;) // to check if the record is present or not
    {
        if (ptr->name == name)
        {
            found = true;
            break;
        }
        else if (ptr->name > name)
        {
            if (ptr->leftThread == true)
            {
                break;
            }
            parent = ptr;
            ptr = ptr->left;
        }
        else if (ptr->name < name)
        {
            if (ptr->rightThread == true)
            {
                break;
            }
            parent = ptr;
            ptr = ptr->right;
        }
    }
    if (!found)
    {
        cout << "Record with name: " << name << " not found!" << endl;
        return NULL;
    }

    // cases
    if (ptr->leftThread == false && ptr->rightThread == false)
    {
        Faculty *parSuc = ptr;
        Faculty *successor = ptr->right;
        for (; successor->leftThread == false;)
        {
            parSuc = successor;
            successor = successor->left;
        }
        ptr->name = successor->name;
        ptr->age = successor->age;
        ptr->deptt = successor->deptt;
        ptr->gender = successor->gender;
        if (successor->rightThread == false)
        {
            Faculty *suc = inOrderSuccessor(successor);
            Faculty *pre = inOrderPredecessor(successor);
            Faculty *child = successor->right;
            if (parSuc == NULL)
            {
                root = child;
            }
            else if (parSuc->left == successor)
            {
                parSuc->left = child;
            }
            else
            {
                parSuc->right = child;
            }
            suc->left = pre;
            free(successor);
        }
        else
        {
            if (parSuc == NULL)
            {
                root = NULL;
            }
            else if (parSuc->left == successor)
            {
                parSuc->leftThread = true;
                parSuc->left = successor->left;
            }
            else
            {
                parSuc->rightThread = true;
                parSuc->right = successor->right;
            }
            free(successor);
        }
    }
    else if (ptr->leftThread == false)
    {
        Faculty *suc = inOrderSuccessor(ptr);
        Faculty *pre = inOrderPredecessor(ptr);
        Faculty *child = ptr->left;
        if (parent == NULL)
        {
            root = child;
        }
        else if (parent->left == ptr)
        {
            parent->left = child;
        }
        else
        {
            parent->right = child;
        }
        pre->right = suc;
        free(ptr);
    }
    else if (ptr->rightThread == false)
    {
        Faculty *suc = inOrderSuccessor(ptr);
        Faculty *pre = inOrderPredecessor(ptr);
        Faculty *child = ptr->right;
        if (parent == NULL)
        {
            root = child;
        }
        else if (parent->left == ptr)
        {
            parent->left = child;
        }
        else
        {
            parent->right = child;
        }
        suc->left = pre;
        free(ptr);
    }
    else
    {
        if (parent == NULL)
        {
            root = NULL;
        }
        else if (parent->left == ptr)
        {
            parent->leftThread = true;
            parent->left = ptr->left;
        }
        else
        {
            parent->rightThread = true;
            parent->right = ptr->right;
        }
        free(ptr);
    }
    return root;
}
//---------------------------------------------------------------------------------------------------------------------//
// Main Function
//---------------------------------------------------------------------------------------------------------------------//
int main()
{
    char func = 0;
    char gender;
    int age, x;
    string name, deptt;
    Faculty *value;
    // #ifndef LOCAL
    //     freopen("input.txt", "r", stdin);
    //     freopen("output.txt", "w", stdout);
    // #endif
    while (func != 'x') //'x' will end the program
    {
        cout << "\n----------Enter i to insert, d to delete and s to search any record, t for inorder traversal and x to exit----\n";
        cin >> func; // fxns to be called on the basis of whats input is given
        if (func == 'i')
        {
            cout << "Enter name of the Faculty: ";
            cin >> name;
            name[0] = toupper(name[0]);
            cout << "Enter Age of " << name << ": ";
            cin >> age;
            cout << "Enter Gender of " << name << "(M/F): ";
            cin >> gender;
            gender = toupper(gender);
            cout << "Enter Department of " << name << ": ";
            cin >> deptt;
            Faculty *fac = insert(name, deptt, gender, age);
            TBTinOrderTraversal(root);
        }
        else if (func == 'd')
        {
            cout << "Enter name of the Faculty: ";
            cin >> name;
            name[0] = toupper(name[0]);
            value = deleteRecord(name);
            if (value != NULL)
            {
                cout << "Record with name: " << name << " deleted successfully" << endl;
            }
            //   if (value != NULL)
            //   {
            //     TBTinOrderTraversal(root);
            //   }
        }
        else if (func == 's')
        {
            cout << "Enter name of the Faculty: ";
            cin >> name;
            name[0] = toupper(name[0]);
            searchRecord(root, name);
        }
        else if (func == 't')
        {
            TBTinOrderTraversal(root);
        }
        fflush(stdin);
    }
    return 0;
}
