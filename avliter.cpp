#include <iostream>
#include <time.h>
using namespace std; 
  
struct Node { 
    int data; 
    int height;
    Node *left, *right, *parent; 
}; 
  
Node* newNode(int val) { 
    Node* temp = new Node; 
    temp->left = temp->right = temp->parent = NULL; 
    temp->data = val; 
    temp->height = 0;
    return temp; 
} 

int height(Node* root) {
    if (root == NULL) {
        return 0;
    }
    return root->height;
}

int bFactor(Node* root) {
    if (root == NULL) 
        return 0;
    else
        return height(root->left) - height(root->right);
}

int max(int a, int b) {
    if (a > b) 
        return a;
    else
        return b;
}

Node* rightRotate(Node* root) {
    Node* t1 = root->left;
    Node* t2 = t1->right;

    t1->right = root;
    root->left = t2;

    root->height = max(height(root->left), height(root->right)) + 1;
    t1->height = max(height(t1->left), height(t1->right)) + 1;

    return t1;
}

Node* leftRotate(Node* root) {
    Node* t1 = root->right;
    Node* t2 = t1->left;

    t1->left = root;
    root->right = t2;

    root->height = max(height(root->left), height(root->right)) + 1;
    t1->height = max(height(t1->left), height(t1->right)) + 1;

    return t1;

}

Node* insertIter(Node* root, int val) {
    Node* newnode = newNode(val);
    Node* node = root;
    Node* next = NULL;
    while (node != NULL) { 
        next = node; 
        if (val < node->data) 
            node = node->left; 
        else
            node = node->right; 
    }
    if (next == NULL) 
        next = newnode;
    else if (val < next->data) 
        next->left = newnode; 
    else
        next->right = newnode; 
    return next; 

    int balance = 0;
    Node* temp = NULL;
    while (root != NULL) {
        root->height = max(height(root->left), height(root->right)) + 1;
        balance = bFactor(root);
        if (balance > 1 && root->left->data > val) {
            root = rightRotate(root);
            balance = bFactor(root);
        }
        if (balance < -1 && root->right->data < val) {
            root = leftRotate(root);
            balance = bFactor(root);
        }
        if (balance > 1 && root->left->data < val) {
            root->left = leftRotate(root->left);
            root = rightRotate(root);
            balance = bFactor(root);
        }
        if (balance < -1 && root->right->data > val) {
            root->right = rightRotate(root->right);
            root = leftRotate(root);
            balance = bFactor(root);
        }
        temp = root;
        root = root->parent;
    }
    return temp;
}

Node* findMinIter(Node* root) {
    if (root == NULL)
        return NULL;
    while (root->left != NULL)
        root = root->left;
    return root;
}

Node* findMaxIter(Node* root) {
    if(root==NULL)
        return NULL;
    while (root->right != NULL)
        root = root->right;
    return root;
}

Node* findNextIter(Node* root, int key) {
	Node* next = NULL;
    if (findMaxIter(root)->data == key) {
        return root;
    }
	while (1) {
		if (key < root->data) {
			next = root;
			root = root->left;
		}
		else if (key > root->data) {
			root = root->right;
		}
		else{
			if (root->right)
				next = findMinIter(root->right);
			break;
		}
		if (!root)
			return NULL;
	}
	return next;
}

Node* findPrevIter(Node* root, int key) {
	Node* prev = NULL;
    if (findMinIter(root)->data == key) {
        return root;
    }
	while (1) {
		if (key < root->data) {
			root = root->left;
		}
		else if (key > root->data){
			prev = root;
			root = root->right;
		}
		else {
			if (root->left)
				prev = findMaxIter(root->left);
			break;
		}
		if (!root)
			return NULL;
	}
	return prev;
}

Node* deleteIter(Node* root, int val) {
    Node* current, *target, *parent;
    current = root;
    target = NULL;
    if(current == NULL) 
        return NULL;
    while(1) {  
        if(current->data == val)
            target = current;
        if(val < current->data) {
            if(current->left == NULL)
                break;
            parent = current;
            current = current->left;
        }
        else {  
            if(current->right == NULL)
                break;
            parent = current;
            current = current->right;
        }
    }
    if(target == NULL) {
        return NULL;
    }
    else {
        if(parent == NULL) {
            free(current);
            root = NULL;
        }
        else {
            target->data = current->data;
            if(parent->left == current) {
                parent->left = current->right;
            }
            else {
                parent->right = current->left;
                free(current);
            }
        }
    }
    return root;

    root->height = max(height(root->left), height(root->right)) + 1;
    int balance = 0;
    Node* temp2 = NULL;
    while (root != NULL) {
        root->height = max(height(root->left), height(root->right)) + 1;
        balance = bFactor(root);
        if (balance > 1 && root->left->data > val) {
            root = rightRotate(root);
            balance = bFactor(root);
        }
        if (balance < -1 && root->right->data < val) {
            root = leftRotate(root);
            balance = bFactor(root);
        }
        if (balance > 1 && root->left->data < val) {
            root->left = leftRotate(root->left);
            root = rightRotate(root);
            balance = bFactor(root);
        }
        if (balance < -1 && root->right->data > val) {
            root->right = rightRotate(root->right);
            root = leftRotate(root);
            balance = bFactor(root);
        }
        temp2 = root;
        root = root->parent;
    }
    return temp2;
}

void printAVL(Node* root) {  
    if(root != NULL)  
    {  
        cout << root->data << " ";  
        printAVL(root->left);  
        printAVL(root->right);  
    }  
}  

void printData(Node* root) {
    cout << root->data << endl;
}
/*
bool AVL(Node* root) {
    if (root == NULL) {
        return 1;
    }
    int lheight = height(root->left);
    int rheight = height(root->right);
    if(abs(lheight-rheight) <= 1 && AVL(root->left) && AVL(root->right))
      return 1;
    return 0;
}

void isAVL(Node* root) {
    if (AVL(root))
        cout<<"AVL CONFIRMED"<<endl;
    else
        cout<<"TRY AGAIN"<<endl;
}
*/
int main() 
{ 
    /*
              7 
            /    \ 
           5      10 
         /  \    /  \ 
        3    6   8   12 */
    Node* root = NULL; 
    Node* min, *max, *next, *prev;

    root = insertIter(root, 7); 
    insertIter(root, 10); 
    insertIter(root, 5); 
    insertIter(root, 3); 
    insertIter(root, 6); 
    insertIter(root, 8); 
    insertIter(root, 12); 
    printAVL(root);
    cout << endl;
    deleteIter(root, 3);
    cout <<"3 is deleted"<<endl;
    printAVL(root);
    cout<<endl;
    max = findMaxIter(root);
    min = findMinIter(root);
    cout <<"The max value is: ";
    printData(max);
    cout <<"The min value is: ";
    printData(min);
    next = findNextIter(root, 5); //should output 6
    prev = findPrevIter(root, 12); //should output 10
    cout <<"The next largest value of 5 is: ";
    printData(next);
    cout <<"The previous smallest value of 12 is: ";
    printData(prev);
    //isAVL(root);
    return 0; 
} 
