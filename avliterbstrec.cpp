#include <iostream>
#include <time.h>
using namespace std; 
  
struct Node { 
    int data; 
    int height;
    Node *left, *right; 
}; 
  
Node* newNode(int key) {
    Node* node = new Node;
    node->data = key;
    node->height = 1;
    node->left = node->right = NULL;
    return node;
}

int max(int a, int b) {
    return (a > b)? a : b;
}

int height(Node* node) {
    if (node == NULL)
        return 0;
    return node->height;
}

int bFactor(Node* node) {
    if(node == NULL)
        return 0;
    return height(node->left) - height(node->right);
}

int* getRandomArray(int n) {
    int* arr = new int[n];
    int temp;
    srand(time(0));
    for (int i = 0; i < n; i++) { 
        arr[i] = rand()%100;
    }
    return arr;
}

Node* insertIter(Node* root, int val) {
    Node* newnode = newNode(val);
    Node* current = root;
    Node* next = NULL;
    while (current != NULL) { 
        next = current; 
        if (val < current->data) 
            current = current->left; 
        else
            current = current->right; 
    }
    if (next == NULL) 
        next = newnode;
    else if (val < next->data) 
        next->left = newnode; 
    else
        next->right = newnode; 
    return next; 
}

Node* leftRotate(Node* node) {
   Node* right = node->right;
   Node* rightleft = right->left;
   
   right->left = node;
   node->right = rightleft;
   node->height = max(height(node->left), height(node->right))+1;
   right->height = max(height(right->left), height(right->right))+1;
   
   return right;
}

Node* rightRotate(Node* node) {
    Node* left = node->left;
    Node* leftright = left->right;

    left->right = node;
    node->left = leftright;
    node->height = max(height(node->left), height(node->right))+1;
    left->height = max(height(left->left), height(left->right))+1;

    return left;
}

Node* rebalance(Node* root) {
    root->height = max( height(root->left), height(root->right)) + 1;
    int balance = bFactor(root);
    if (balance < -1) {
        int childbalance = bFactor(root->right);
        if (childbalance > 0) {
            root->right = rightRotate(root->right);
            return leftRotate(root);
        }
        else {
            return leftRotate(root);
        }
    }
    if (balance > 1) {
        int childbalance = bFactor(root->left);
        if (childbalance < 0) {
            root->left = leftRotate(root->left);
            return rightRotate(root);
        }
        else {
            return rightRotate(root);
        }
    }
    return root;
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
    Node* current = root;
    Node *target = NULL;
    Node* parent = NULL;

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
}

void printInorder(Node* root) {  
    if(root != NULL) {  
        printInorder(root->left);  
        cout << root->data << " "; 
        printInorder(root->right);  
    }  
}  

void printData(Node* root) {
    cout << root->data << endl;
}

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

int main() 
{ 

    Node* root = NULL; 
    Node* min, *max, *next, *prev;

    root = insertIter(root, 7); 
    insertIter(root, 10); 
    insertIter(root, 5); 
    insertIter(root, 3); 
    insertIter(root, 6); 
    insertIter(root, 8); 
    insertIter(root, 12); 
    root = rebalance(root);
    printInorder(root);
    cout << endl;
    deleteIter(root, 3);
    root = rebalance(root);
    cout <<"3 is deleted"<<endl;
    printInorder(root);
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
    isAVL(root);
    return 0; 
} 
