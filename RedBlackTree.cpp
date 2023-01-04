/*
Name: Sanidhaya Sharma                                  Roll no. CS21B1024
Assignment: Red Black Tree Implementation for storing Age Records.
*/
#include <bits/stdc++.h>
using namespace std;
//---------------------------------------------------------------------------------------------------------------------//
// Struct defined for layout of every node
//---------------------------------------------------------------------------------------------------------------------//
struct Node
{
    int age;
    struct Node *left;
    struct Node *right;
    bool color; // 0 represents red and 1 represents black
    struct Node *parent;
    Node() // constructor for NullChild
    {
        this->left = NULL;
        this->right = NULL;
        this->color = 1; // NullChild has black color
    }
    Node(int age, Node *parent, Node *left, Node *right)
    {
        this->age = age;
        this->left = left;
        this->right = right;
        this->parent = parent;
        this->color = 0; // new node must have red color
    }
};
//---------------------------------------------------------------------------------------------------------------------//
typedef struct Node ageNode;
//---------------------------------------------------------------------------------------------------------------------//
// Red Black Tree Class containing functions
//---------------------------------------------------------------------------------------------------------------------//
class RedBlackTree
{
    ageNode *root;
    ageNode *NullChild;

public:
    //---------------------------------------------------------------------------------------------------------------------//
    // Primary constructor
    //---------------------------------------------------------------------------------------------------------------------//
    RedBlackTree() // constructor
    {
        this->NullChild = new ageNode;
        this->root = NullChild;
    }
    //---------------------------------------------------------------------------------------------------------------------//
    // Rotation function for left and right rotation function
    //---------------------------------------------------------------------------------------------------------------------//
    void balanceRotation(ageNode *node, int a)
    {
        if (a == 0) // right rotation
        {
            ageNode *nl = node->left; // in right rotation, node->left takes the position of node i.e the nodes are shifted towards right side.
            node->left = nl->right;
            if (nl->right != NullChild) // if node->left->right is nullchild,then it wont have parent,else that will have node as the new parent as nl->right will be node now
            {
                nl->right->parent = node;
            }
            nl->parent = node->parent; // nl will take node's position
            if (node->parent == NULL)
            {
                this->root = nl;
            }
            else if (node == node->parent->right) // arranging nl at node's place
            {
                node->parent->right = nl;
            }
            else
            {
                node->parent->left = nl;
            }
            nl->right = node; // nl->right will now point to node now and nl will now br parent of node
            node->parent = nl;
        }
        else if (a == 1) // left rotation
        {
            ageNode *nl = node->right; // same cases as done with right rotation will take place here,just direction would change
            node->right = nl->left;
            if (nl->left != NullChild)
            {
                nl->left->parent = node;
            }
            nl->parent = node->parent;
            if (node->parent == NULL)
            {
                root = nl;
            }
            else if (node == node->parent->right)
            {
                node->parent->right = nl;
            }
            else
            {
                node->parent->left = nl;
            }
            nl->left = node;
            node->parent = nl;
        }
    }
    //---------------------------------------------------------------------------------------------------------------------//
    // Balance Function to mantain proerties of RB Tree
    //---------------------------------------------------------------------------------------------------------------------//
    void balanceRecord(ageNode *p)
    {
        ageNode *uncle;                                // uncle is a pointer that will point to the sibling of parent node
        while ((p != root) && (p->parent->color == 0)) // 0 means the color of parent of p is red
        {
            if (p->parent == p->parent->parent->right) // uncle will be decided based on the position of parent
            {
                uncle = p->parent->parent->left;
                if (uncle->color == 0) // if parent and uncle both are red,recoloring takes place
                {
                    uncle->color = 1;
                    p->parent->color = 1;
                    p->parent->parent->color = 0;
                    p = p->parent->parent;
                }
                else // else Rotation takes place
                {
                    if (p->parent->left == p) // if p is located at left of parent and parent is located at right of its parent====RR rotation(wrt to parent of p) takes place and them LL rotation(wrt grandparent of p) takes place
                    {
                        p = p->parent;
                        balanceRotation(p, 0);
                    }
                    p->parent->color = 1; // if p is located at right of parent, only Left rotation wrt to grandparent takes place
                    p->parent->parent->color = 0;
                    balanceRotation(p->parent->parent, 1);
                }
            }
            else
            {
                uncle = p->parent->parent->right; // uncle is at right position
                if (uncle->color == 0)            // if both uncle and parent have red color,recoloring takes place
                {
                    uncle->color = 1;
                    p->parent->color = 1;
                    p->parent->parent->color = 0; // grandparent given red color and the same process will happen for grandparent
                    p = p->parent->parent;
                }
                else
                {
                    if (p->parent->right == p) // if p is located at right of parent and parent is located at left of its parent====Left rotation(wrt to parent of p) takes place and them Right rotation(wrt grandparent of p) takes place
                    {
                        p = p->parent;
                        balanceRotation(p, 1);
                    }
                    p->parent->color = 1; // if p is located at left of parent, only right rotation wrt to grandparent takes place
                    p->parent->parent->color = 0;
                    balanceRotation(p->parent->parent, 0);
                }
            }
        }

        root->color = 1; // in case root's color is changed to red, it should be reverted back to black
    }
    //---------------------------------------------------------------------------------------------------------------------//
    // Insert Function
    //---------------------------------------------------------------------------------------------------------------------//
    bool insertRecord(int age)
    {
        if (searchRecord(age, root, 0)) // Duplicate case
        {
            cout << "Record with age: " << age << " already exists. Try again with other record" << endl;
            return false;
        }
        if (age <= 0) // Valid age case
        {
            cout << "Age cannot be " << age << " .Enter valid age." << endl;
            return false;
        }
        ageNode *node = new ageNode(age, NULL, NullChild, NullChild); // node with the age created
        ageNode *temp = NULL;
        ageNode *temp2 = root;
        while (temp2 != NullChild && temp2 != NULL) // after the loop temp will point to the parent position of the new node
        {
            temp = temp2;
            if (temp2->age > age) // comparison of age with nodes
            {
                temp2 = temp2->left;
            }
            else // comparison of age with nodes
            {
                temp2 = temp2->right;
            }
        }

        node->parent = temp; // parent pointer linked to parent position
        if (temp == NULL)    // empty tree case
        {
            this->root = node;
            node->color = 1;
            return true;
        }
        else if (temp->age > age) // linking parent's left or right to chuld
        {
            temp->left = node;
        }
        else // linking parent's left or right to chuld
        {
            temp->right = node;
        }

        if (temp->parent == NULL) // root parent case
        {
            return true;
        }
        else
        {
            balanceRecord(node); // balamcing function called to maintain the properties of RB Tree
        }
        return true;
    }
    //---------------------------------------------------------------------------------------------------------------------//
    // Print/Traverse function(inorder)
    //---------------------------------------------------------------------------------------------------------------------//
    void printRBTree(ageNode *node)
    {
        if (root == node) // for decoration purpose
        {
            cout << "---------------------Age Records-------------------" << endl;
        }
        if (root == NULL) // empty tree condition
        {
            cout << "Empty Records. Enter i to add some records." << endl;
            return;
        }
        if (node == NULL) // wont be used. written for security purpose
        {
            return;
        }
        if (node->left != NullChild) // recursion will occur till nullchild comes up
        {
            printRBTree(node->left);
        }
        string nodeColor = node->color ? "Black" : "Red"; // red black condition
        cout << "Age: " << node->age << "     Color: " << nodeColor;
        if (node->parent != NULL)
        {
            cout << "     Parent: " << node->parent->age;
        }
        else
        {
            cout << "     Parent: -";
        }
        if (node->left != NullChild)
        {
            cout << "     Left Child: " << node->left->age;
        }
        else
        {
            cout << "     Left Child: -";
        }
        if (node->right != NullChild)
        {
            cout << "     Right Child: " << node->right->age << endl;
        }
        else
        {
            cout << "     Right Child: -" << endl;
        }
        if (node->right != NullChild) // right side recursion till NullChild comes up
        {
            printRBTree(node->right);
        }
    }
    //---------------------------------------------------------------------------------------------------------------------//
    // Print function that will be called from main function
    //---------------------------------------------------------------------------------------------------------------------//
    void printRBTreeFromRoot()
    {
        printRBTree(root);
    }
    //---------------------------------------------------------------------------------------------------------------------//
    // Search function
    //---------------------------------------------------------------------------------------------------------------------//
    bool searchRecord(int age, ageNode *node, int a) // this function will work for 2 purposes- 1: Search an element and print the record(will execute when a=1)            2: Check duplicate condition(will execute when a=0)
    {
        bool res; // will return duplicate check result to insert function
        if (root == NULL)
        {
            if (a == 0)
            {
                return false;
            }
            cout << "Empty Records. Enter i to add some records." << endl;
            return false;
        }
        if (node == NULL)
        {
            if (a == 0)
            {
                return false;
            }
            cout << "Record not Found. Try again with other age" << endl;
            return false;
        }
        if (node->age == age) // comparison to go till the record if it is in the tree
        {
            if (a == 0)
            {
                return true;
            }
            string nodeColor = node->color ? "Black" : "Red";
            cout << "Age: " << node->age << "     Color: " << nodeColor;
            if (node->parent != NULL)
            {
                cout << "     Parent: " << node->parent->age;
            }
            else
            {
                cout << "     Parent: -";
            }
            if (node->left != NullChild)
            {
                cout << "     Left Child: " << node->left->age;
            }
            else
            {
                cout << "     Left Child: -";
            }
            if (node->right != NullChild)
            {
                cout << "     Right Child: " << node->right->age << endl;
            }
            else
            {
                cout << "     Right Child: -" << endl;
            }
            return true;
        }
        if (age > node->age)
        {
            res = searchRecord(age, node->right, a);
        }
        else
        {
            res = searchRecord(age, node->left, a);
        }
        return res;
    }
    //---------------------------------------------------------------------------------------------------------------------//
    // Search function that will be called from main function
    //---------------------------------------------------------------------------------------------------------------------//
    void searchRecordWithAge(int age) // just to call the search function
    {
        searchRecord(age, root, 1); // 1 for search and print and 0 for only search
    }
};

//---------------------------------------------------------------------------------------------------------------------//
// Main Function
//---------------------------------------------------------------------------------------------------------------------//
int main()
{
    RedBlackTree Tree1;
    char func = 0;
    int age;
    bool p;
    // #ifndef LOCAL
    //     freopen("input.txt", "r", stdin);
    //     freopen("output.txt", "w", stdout);
    // #endif
    while (func != 'x') //'x' will end the program
    {
        cout << "\n----------Enter i to insert,s to search any age record, t for traversal of records and x to exit----\n";
        cin >> func; // fxns to be called on the basis of whats input is given
        if (func == 'i')
        {
            cout << "Enter Age : ";
            cin >> age;
            p = Tree1.insertRecord(age);
            if (p)
            {
                Tree1.printRBTreeFromRoot();
            }
        }
        else if (func == 't')
        {
            Tree1.printRBTreeFromRoot();
        }
        else if (func == 's')
        {
            cout << "Enter Age : ";
            cin >> age;
            Tree1.searchRecordWithAge(age);
        }
        fflush(stdin);
    }
    return 0;
}