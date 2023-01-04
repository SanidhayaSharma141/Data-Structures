#include <bits/stdc++.h>
using namespace std;

typedef struct BTreeNode
{
    int arr[4];
    struct BTreeNode *ChildrenNodes[5];
    bool isLeaf;
    int currentKeys;
    BTreeNode(bool isLeaf, int currentKeys)
    {
        this->isLeaf = true;
        this->currentKeys = currentKeys;
        for (int i = 0; i < 5; i++)
        {
            ChildrenNodes[i] = NULL;
        }
        memset(arr, -1, sizeof(arr));
    }
} BT;

class BTree
{
    BT *root;

public:
    BTree(BT *root)
    {
        this->root = root;
    }
    void insert(int val);
    void search(int val);
    void traverse1(BT *node);
    void traverse()
    {
        traverse1(root);
    }
    void deleteNode(int val);
    void splitNode(BT *node, int val);
};

void BTree::splitNode(BT *node, int val)
{
    int ar[5];
    ar[4] = val;
    BT *node1 = new BT(true, 2);
    BT *node2 = new BT(true, 2);
    for (int i = 0, c = 0; i < 5; i++)
    {
        // if(val>node->arr[i]){
        //     ar[i]=node->arr[i];
        //     continue;
        // }
        if (i < 4 && (val < node->arr[i]) && c == 0)
        {
            ar[i++] = val;
            ar[i] = node->arr[i];
            c = 1;
        }
        else if (i < 4 && (val > node->arr[i]))
        {
            ar[i] = node->arr[i];
        }
        else
        {
            ar[i] = val;
        }
    }

    node->currentKeys = 1;
    node->isLeaf = false;
    node->ChildrenNodes[0] = node1;
    node->ChildrenNodes[1] = node2;
    memset(node->arr, -1, sizeof(node->arr));
    node->arr[0] = ar[2];
    node1->arr[0] = ar[0];
    node1->arr[1] = ar[1];
    node2->arr[0] = ar[3];
    node2->arr[1] = ar[4];
}
void BTree::traverse1(BT *node)
{
    if (node == NULL)
    {
        return;
    }
    if (!node->isLeaf)
    {
        for (int i = 0; i < node->currentKeys; i++)
        {
            if (node->ChildrenNodes[i] != NULL)
            {
                cout << "Node: ";
                traverse1(node->ChildrenNodes[i]);
                cout << endl;
            }

            cout << node->arr[i] << " ";
        }
        traverse1(node->ChildrenNodes[node->currentKeys]);
    }
    else
    {
        for (int i = 0; i < node->currentKeys; i++)
        {
            cout << node->arr[i] << " ";
        }
    }
    cout << endl;
}
void BTree::insert(int val)
{
    if (root == NULL)
    {
        BT *newNode = new BT(true, 0);
        newNode->arr[0] = val;
        newNode->currentKeys = 1;
        root = newNode;
        return;
    }
    BT *temp = root;
    for (; temp->isLeaf == false;)
    {
        int i = 0;
        for (i = 0; i < temp->currentKeys; i++)
        {
            if (val < temp->arr[i])
            {
                break;
            }
        }
        temp = temp->ChildrenNodes[i];
    }
    if (temp->currentKeys < 4)
    {
        int i = 0, c = 0;
        for (i = 0; i < temp->currentKeys; i++)
        {
            if (val < temp->arr[i])
            {
                c = 1;
                break;
            }
        }
        for (int p = temp->currentKeys - 1; p >= i && c == 1; p--)
        {
            temp->arr[p + 1] = temp->arr[p];
        }
        temp->arr[i] = val;
        temp->currentKeys++;
    }
    else
    {
        splitNode(temp, val);
    }
}
int main()
{
    BTree b1(NULL);
    b1.insert(1);
    b1.insert(3);
    b1.insert(2);
    b1.insert(4);
    b1.insert(5);
    b1.insert(6);
    b1.insert(7);
    b1.insert(8);
    b1.traverse();
    return 0;
}