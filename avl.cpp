#include <iostream>
#include <vector>
#include <time.h>
#include <algorithm>

using namespace std;

int avlcounter = 0;
int bstcounter = 0;

struct Node
{
    int data;
    int height;
    int bf;
    Node *left, *right, *parent;
    Node()
    {
        this->left = NULL;
        this->right = NULL;
        this->parent = NULL;
        this->height = 1;
        this->bf = 0;
    }
};

class BST
{
private:
    Node *root;

public:

    BST(Node *r = NULL)
    {
        root = r;
    }

    void inOrderPrint()
    {
        inOrderPrint(root);
    }

    void preOrderPrint()
    {
        preOrderPrint(root);
    }

    int findMinIter()
    {
        return ((findMinIter(root))->data);
    }

    int findMaxIter()
    {
        return ((findMaxIter(root))->data);
    }

    void insertRec(int data)
    {
        insertRec(root, data);
    }

    void deleteRec(int data)
    {
        deleteRec(root, data);
    }

    int findMinRec()
    {
        return ((findMinRec(root))->data);
    }

    int findMaxRec()
    {
        return ((findMaxRec(root))->data);
    }

    void insertIter(int data)
    {
        if (root == NULL)
        {
            Node *temp = new Node;
            temp->data = data;
            temp->left = NULL;
            temp->right = NULL;
            temp->parent = NULL;
            root = temp;
            bstcounter++;
        }
        else
        {
            Node *p1 = root, *p;
            Node *temp = new Node;
            temp->data = data;
            temp->left = NULL;
            temp->right = NULL;
            while (p1 != NULL)
            {
                if (temp->data < p1->data)
                {
                    p = p1;
                    p1 = p1->left;
                    bstcounter++;
                }
                else
                {
                    p = p1;
                    p1 = p1->right;
                    bstcounter++;
                }
            }
            if (temp->data < p->data)
            {
                p->left = temp;
                bstcounter++;
                temp->parent = p;
            }
            else
            {
                p->right = temp;
                bstcounter++;
            }
        }
    }

    void deleteIter(int data)
    {
        Node *temp = root;
        Node *p1, *p2;
        while (temp != NULL)
        {
            if (temp->data == data)
            {
                p1 = temp;
                break;
            }
            else if (data > temp->data)
            {
                p2 = temp;
                temp = temp->right;
            }
            else
            {
                p2 = temp;
                temp = temp->left;
            }
        }
        if (p1->right == NULL && p1->left == NULL)
        {
            if (p1->data > p2->data)
            {
                p2->right = NULL;
                delete p1;
            }
            else
            {
                p2->left = NULL;
                delete p1;
            }
        }
        else if (p1->right == NULL || p1->left == NULL)
        {
            if (p1->right == NULL)
            {
                if (p1->data > p2->data)
                {
                    p2->right = p1->left;
                    delete p1;
                }
                else
                {
                    p2->left = p1->left;
                    delete p1;
                }
            }
            else if (p1->left == NULL)
            {
                if (p1->data > p2->data)
                {
                    p2->right = p1->right;
                    delete p1;
                }
                else
                {
                    p2->left = p1->right;
                    delete p1;
                }
            }
        }
        else
        {
            Node *p0 = p1->right, *p3 = p0;
            if (p0->right == NULL && p0->left == NULL)
            {
                p1->data = p0->data;
                p1->right = NULL;
                delete p0;
            }
            else if (p0->left == NULL)
            {
                p1->right = p0->right;
                p1->data = p0->data;
                delete p0;
            }
            else
            {
                while (p0->left != NULL)
                {
                    p3 = p0;
                    p0 = p0->left;
                }
                if (p0->right != NULL)
                {
                    p3->left = p0->right;
                    p1->data = p0->data;
                    delete p0;
                }
                else
                {
                    p3->left = NULL;
                    p1->data = p0->data;
                    delete p0;
                }
            }
        }
    }

    Node *findMinIter(Node *root)
    {
        if (root == NULL)
            return NULL;
        while (root->left != NULL)
            root = root->left;
        return root;
    }

    Node *findMaxIter(Node *root)
    {
        if (root == NULL)
            return NULL;
        while (root->right != NULL)
            root = root->right;
        return root;
    }

    void inOrderPrint(Node *root)
    {
        if (root != NULL)
        {
            if (root->left)
                inOrderPrint(root->left);
            cout << root->data << " ";
            if (root->right)
                inOrderPrint(root->right);
        }
    }

    void preOrderPrint(Node *root)
    {
        if (root != NULL)
        {
            cout << root->data << " ";
            preOrderPrint(root->left);
            preOrderPrint(root->right);
        }
    }

    void sortNodes(Node *parent, vector<Node *> &nodeVec)
    {
        if (parent != NULL)
        {
            sortNodes(parent->left, nodeVec);
            nodeVec.push_back(parent);
            sortNodes(parent->right, nodeVec);
        }
    }

    Node *findNextIter(int value)
    {
        vector<Node *> nodes;
        sortNodes(root, nodes);
        for (int i = 0; i < nodes.size(); i++)
        {
            if (nodes[i]->data == value)
            {
                return (nodes[i + 1]);
            }
        }
    }

    Node *findPrevIter(int value)
    {
        vector<Node *> nodes;
        sortNodes(root, nodes);
        for (int i = 0; i < nodes.size(); i++)
        {
            if (nodes[i]->data == value)
            {
                return (nodes[i - 1]);
            }
        }
    }

    void insertRec(Node *node, int val)
    {
        Node *newnode = new Node;
        newnode->data = val;
        if (root == NULL)
        {
            root = newnode;
            return;
        }
        if (node->data > val)
        {
            if (node->left == NULL)
            {
                node->left = newnode;
                newnode->parent = node;
            }
            else
            {
                insertRec(node->left, val);
            }
        }

        else if (node->data < val)
        {
            if (node->right == NULL)
            {
                node->right = newnode;
                newnode->parent = node;
            }
            else
            {
                insertRec(node->right, val);
            }
        }
    }

    void deleteRec(Node *node, int val)
    {
        Node *temp;
        if (node == NULL)
        {
            return;
        }
        else if (node->data > val)
        {
            deleteRec(node->left, val);
        }
        else if (node->data < val)
        {
            deleteRec(node->right, val);
        }
        else if (node->left && node->right)
        {
            temp = findMinRec(node->right);
            node->data = temp->data;
            deleteRec(node->right, node->data);
        }
        else
        {
            if (node->left == NULL && node->right == NULL)
            {
                temp = NULL;
            }
            else if (node->left != NULL && node->right == NULL)
            {
                temp = node->left;
                temp->parent = node->parent;
            }
            else if (node->right != NULL && node->left == NULL)
            {
                temp = node->right;
                temp->parent = node->parent;
            }
            if (node->parent->data > node->data)
            {
                node->parent->left = temp;
            }
            else if (node->parent->data <= node->data)
            {
                node->parent->right = temp;
            }
            delete node;
            node = NULL;
        }
    }

    Node *findMaxRec(Node *root)
    {
        if (root == NULL)
        {
            return NULL;
        }
        else if (root->right == NULL)
        {
            return root;
        }
        else
        {
            return findMaxRec(root->right);
        }
    }

    Node *findMinRec(Node *root)
    {
        if (root == NULL)
        {
            return NULL;
        }
        else if (root->left == NULL)
        {
            return root;
        }
        else
        {
            return findMinRec(root->left);
        }
    }

    Node* findNextRec(int key) {
        vector<Node*> nodes;
        sortNodes(root, nodes);
        return nodes[findNextRec(key, nodes, 0) + 1];
    }

    int findNextRec(int key, vector<Node*> nodes, int index) {
        if (nodes[index]->data != key) {
            index = findNextRec(key, nodes, index + 1);
        } 
        return index;
    }

    Node* findPrevRec(int key) {
        vector<Node*> nodes;
        sortNodes(root, nodes);
        return nodes[findNextRec(key, nodes, 0) - 1];
    }

    int findPrevRec(int key, vector<Node*> nodes, int index) {
        if (nodes[index]->data != key) {
            index = findPrevRec(key, nodes, index + 1);
        } 
        return index;
    }
};

class AVL
{
public:
    Node *root;

    AVL(Node *r = NULL)
    {
        root = r;
        avlcounter = 0;
    }

    void inOrderPrint()
    {
        inOrderPrint(root);
    }

    void preOrderPrint()
    {
        preOrderPrint(root);
    }

    int max(int a, int b)
    {
        return (a > b) ? a : b;
    }

    int height(Node *node)
    {
        if (node == NULL)
            return 0;
        return node->height;
    }

    void setHeight(Node *node)
    {
        Node *temp = new Node();
        temp = node;
        while (temp != NULL)
        {
            int left = height(temp->left);
            int right = height(temp->right);
            temp->height = (max(left, right) + 1);
            temp = temp->parent;
        }
        delete temp;
    }

    int bFactor(Node *node)
    {
        if (node == NULL)
            return 0;
        return height(node->left) - height(node->right);
    }

    void setHeightBf(Node *node) {}

    void inOrderPrint(Node *root)
    {
        if (root != NULL)
        {
            if (root->left)
                inOrderPrint(root->left);
            cout << root->data << " ";
            if (root->right)
                inOrderPrint(root->right);
        }
    }

    void preOrderPrint(Node *root)
    {
        if (root != NULL)
        {
            cout << root->data << " ";
            preOrderPrint(root->left);
            preOrderPrint(root->right);
        }
    }

    void leftRotate(Node *node)
    {
        Node *right = node->right;
        Node *rightleft = right->left;

        right->left = node;
        node->right = rightleft;
        setHeight(node);
        setHeight(right);
    }

    void rightRotate(Node *node)
    {
        Node *left = node->left;
        Node *leftright = left->right;
        left->right = node;
        node->left = leftright;
        setHeight(node);
        setHeight(left);
    }

    void rebalance(Node *root)
    {
        root->height = max(height(root->left), height(root->right)) + 1;
        int balance = bFactor(root);
        if (balance < -1)
        {
            int childbalance = bFactor(root->right);
            if (childbalance > 0)
            {
                rightRotate(root->right);
                leftRotate(root);
            }
            else
            {

                leftRotate(root);
            }
        }
        if (balance > 1)
        {
            int childbalance = bFactor(root->left);
            if (childbalance < 0)
            {
                leftRotate(root->left);
                return rightRotate(root);
            }
            else
            {
                return rightRotate(root);
            }
        }
    }

    void insertIter(int data)
    {
        Node *temp = new Node;
        temp->data = data;
        if (root == NULL)
        {
            temp->left = NULL;
            temp->right = NULL;
            temp->parent = NULL;
            root = temp;
        }
        else
        {
            Node *p1 = root, *p;
            Node *temp = new Node;
            temp->data = data;
            temp->left = NULL;
            temp->right = NULL;
            while (p1 != NULL)
            {
                if (temp->data < p1->data)
                {
                    p = p1;
                    p1 = p1->left;
                    avlcounter++;
                }
                else
                {
                    p = p1;
                    p1 = p1->right;
                    avlcounter++;
                }
            }
            if (temp->data < p->data)
            {
                p->left = temp;
                avlcounter++;
                temp->parent = p;
            }
            else
            {
                p->right = temp;
                avlcounter++;
            }
        }
        setHeight(temp);
        Node *temp2 = new Node();
        temp2 = temp;
        while (temp2)
        {
            int BF = bFactor(temp2);
            if (BF > 1 || BF < -1)
            {
                rebalance(temp2);
            }
            temp2 = temp2->parent;
        }

    }

    void deleteIter(int data)
    {
        Node *temp = root;
        Node *p1, *p2;
        while (temp != NULL)
        {
            if (temp->data == data)
            {
                p1 = temp;
                break;
            }
            else if (data > temp->data)
            {
                p2 = temp;
                temp = temp->right;
            }
            else
            {
                p2 = temp;
                temp = temp->left;
            }
        }
        if (p1->right == NULL && p1->left == NULL)
        {
            if (p1->data > p2->data)
            {
                p2->right = NULL;
                delete p1;
            }
            else
            {
                p2->left = NULL;
                delete p1;
            }
        }
        else if (p1->right == NULL || p1->left == NULL)
        {
            if (p1->right == NULL)
            {
                if (p1->data > p2->data)
                {
                    p1->left->parent = p2;
                    p2->right = p1->left;
                    delete p1;
                }
                else
                {
                    p1->left->parent = p2;
                    p2->left = p1->left;
                    delete p1;
                }
            }
            else if (p1->left == NULL)
            {
                if (p1->data > p2->data)
                {
                    p1->right->parent = p2;
                    p2->right = p1->right;
                    
                    delete p1;
                }
                else
                {
                    p1->right->parent = p2;
                    p2->left = p1->right;
                    delete p1;
                }
            }
        }
        else
        {
            Node *p0 = p1->right, *p3 = p0;
            if (p0->right == NULL && p0->left == NULL)
            {
                p1->data = p0->data;
                p1->right = NULL;
                delete p0;
            }
            else if (p0->left == NULL)
            {
                p1->right = p0->right;
                p1->data = p0->data;
                delete p0;
            }
            else
            {
                while (p0->left != NULL)
                {
                    p3 = p0;
                    p0 = p0->left;
                }
                if (p0->right != NULL)
                {
                    p3->left = p0->right;
                    p1->data = p0->data;
                    delete p0;
                }
                else
                {
                    p3->left = NULL;
                    p1->data = p0->data;
                    delete p0;
                }
            }
        }
    }
    int findMinIter()
    {
        return ((findMinIter(root))->data);
    }

    int findMaxIter()
    {
        return ((findMaxIter(root))->data);
    }

    Node *findMinIter(Node *root)
    {
        if (root == NULL)
            return NULL;
        while (root->left != NULL)
            root = root->left;
        return root;
    }

    Node *findMaxIter(Node *root)
    {
        if (root == NULL)
            return NULL;
        while (root->right != NULL)
            root = root->right;
        return root;
    }

    void sortNodes(Node *parent, vector<Node *> &nodeVec)
    {
        if (parent != NULL)
        {
            sortNodes(parent->left, nodeVec);
            nodeVec.push_back(parent);
            sortNodes(parent->right, nodeVec);
        }
    }

    Node *findNextIter(int value)
    {
        vector<Node *> nodes;
        sortNodes(root, nodes);
        for (int i = 0; i < nodes.size(); i++)
        {
            if (nodes[i]->data == value)
            {
                return (nodes[i + 1]);
            }
        }
    }

    Node *findPrevIter(int value)
    {
        vector<Node *> nodes;
        sortNodes(root, nodes);
        for (int i = 0; i < nodes.size(); i++)
        {
            if (nodes[i]->data == value)
            {
                return (nodes[i - 1]);
            }
        }
    }


};


vector<int> getSortedArray(int n)
{
    vector<int> list;
    for (int i = n; i > 0; i--)
    {
        list.push_back(i);
    }
    return list;
}

vector<int> getRandomArray(int n)
{
    vector<int> list;
    list = getSortedArray(n);
    random_shuffle(list.begin(), list.end());
    return list;
}

int main()
{
    BST bstiter;
    BST bstrec;
    AVL avliter;
    int n = 10000;
    vector<int> list = getRandomArray(n);
    

    for (int i = 0; i < list.size(); i++)
    {
        bstiter.insertIter(list[i]);
        bstrec.insertRec(list[i]);
        avliter.insertIter(list[i]);
    }
    cout << "********************************BST Iterative Test with Random Array********************************" << endl;
    cout << "BST traversed " << bstcounter << " levels to insert " << n << " random nodes." << endl;
    //cout << "Pre-order: ";
    //bstiter.preOrderPrint();
    //cout << endl;
    //cout << "Post-order: ";
    //bstiter.inOrderPrint();
    cout << endl;
    cout << "Deleting " << list[4] << endl;
    bstiter.deleteIter(list[4]);
    //bstiter.inOrderPrint();
    cout << endl;
    int min = bstiter.findMinIter();
    cout << "Min is: " << min << endl;
    int max = bstiter.findMaxIter();
    cout << "Max is: " << max << endl;
    Node *next = bstiter.findNextIter(list[6]);
    cout << "value after " << list[6] << " is: " << next->data << endl;
    Node *prev = bstiter.findPrevIter(list[6]);
    cout << "value before " << list[6] << " is: " << prev->data << endl;
    cout << "********************************BST Recursion Test with Random Array********************************" << endl;
    //cout << "Pre-order: ";
   // bstrec.preOrderPrint();
    //cout << endl;
   // cout << "Post-order: ";
    //bstrec.inOrderPrint();
    //cout << endl;
    cout << "Deleting " << list[4] << endl;
    bstrec.deleteRec(list[4]);
    //bstrec.inOrderPrint();
    cout << endl;
    min = bstrec.findMinRec();
    max = bstrec.findMaxRec();
    cout << "Min is: " << min << endl;
    cout << "Max is: " << max << endl;
    next = bstrec.findNextRec(list[6]);
    prev = bstrec.findPrevRec(list[6]);
    cout << "value after " << list[6] << " is: " << next->data << endl;
    cout << "value before " << list[6] << " is: " << prev->data << endl;
    cout << "********************************AVL Iterative Test with Random Array********************************" << endl;
    cout << "AVL traversed " << avlcounter << " levels to insert " << n <<" random nodes." << endl;
    //cout << "Pre-order: ";
    //avliter.preOrderPrint();
    //cout << endl;
    //cout << "Post-order: ";
    //avliter.inOrderPrint();
    //cout << endl;
    cout << "Deleting " << list[4] << endl;
    avliter.deleteIter(list[4]);
    //avliter.inOrderPrint();
    cout << endl;
    min = avliter.findMinIter();
    max = avliter.findMaxIter();
    cout << "Min is: " << min << endl;
    cout << "Max is: " << max << endl;
    next = avliter.findNextIter(list[6]);
    prev = avliter.findPrevIter(list[6]);
    cout << "value after " << list[6] << " is: " << next->data << endl;
    cout << "value before " << list[6] << " is: " << prev->data << endl;

    vector<int> slist = getSortedArray(n);

    for (int i = 0; i < slist.size(); i++)
    {
        bstiter.insertIter(slist[i]);
        avliter.insertIter(slist[i]);
    }

    cout << "********************************BST Iterative Test with Sorted Array********************************" << endl;
    cout << "BST traversed " << bstcounter << " levels to insert " << n << " sorted nodes." << endl;
    //cout << "Pre-order: ";
    //bstiter.preOrderPrint();
    //cout << endl;
    //cout << "Post-order: ";
    //bstiter.inOrderPrint();
    cout << endl;
    cout << "Deleting " << list[4] << endl;
    bstiter.deleteIter(list[4]);
    //bstiter.inOrderPrint();
    cout << endl;
    min = bstiter.findMinIter();
    cout << "Min is: " << min << endl;
    max = bstiter.findMaxIter();
    cout << "Max is: " << max << endl;
    next = bstiter.findNextIter(list[6]);
    cout << "value after " << list[6] << " is: " << next->data << endl;
    prev = bstiter.findPrevIter(list[6]);
    cout << "value before " << list[6] << " is: " << prev->data << endl;
    cout << "********************************AVL Iterative Test with Sorted Array********************************" << endl;
    cout << "AVL traversed " << avlcounter << " levels to insert " << n <<" sorted nodes." << endl;
    //cout << "Pre-order: ";
    //avliter.preOrderPrint();
    //cout << endl;
    //cout << "Post-order: ";
    //avliter.inOrderPrint();
    cout << endl;
    cout << "Deleting " << list[4] << endl;
    avliter.deleteIter(list[4]);
    //avliter.inOrderPrint();
    cout << endl;
    min = avliter.findMinIter();
    max = avliter.findMaxIter();
    cout << "Min is: " << min << endl;
    cout << "Max is: " << max << endl;
    next = avliter.findNextIter(list[6]);
    prev = avliter.findPrevIter(list[6]);
    cout << "value after " << list[6] << " is: " << next->data << endl;
    cout << "value before " << list[6] << " is: " << prev->data << endl;

    return 0;
}