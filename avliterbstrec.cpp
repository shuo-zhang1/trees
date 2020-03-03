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

int* getRandomArray(int n) {
    int* arr = new int[n];
    int temp;
    srand(time(0));
    for (int i = 0; i < n; i++) { //workon
        arr[i] = rand()%100;
    }
    return arr;
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

Node* insertRec(Node* root, int val) { 
    if (!root) 
        return newNode(val); 
    if (val < root->data) 
        root->left = insertRec(root->left, val); 
    else
        root->right = insertRec(root->right, val); 
    return root; 
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
    Node* parent = NULL;
    while (root != NULL) {
        if (root->data > val) {
            parent = root;
            root = root->left;
            continue;
        }
        if (root->data < val) {
            parent = root;
            root = root->right;
            continue;
        }
        break;
    }
    if (root->left == NULL || root->right == NULL) {
        Node* temp = root->left ? root->left : root->right;
        if (temp == NULL) {
            temp = root;
            root->parent->left = NULL;
            root = NULL;
        }
        else 
            *root = *temp;
        free(temp);
    }
    else {
        Node* temp = findMinIter(root->right);
        root->data = temp->data;
        root = root->right;
        val = temp->data;
    }
    if (root == NULL) {
        return root;
    }
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

void printBST(Node* root) {
     if(root == NULL)
           return;
     printBST(root->left);
     printf("%d ", root->data);
     printBST(root->right);

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
int main() { 
    Node* avl = NULL; 
    Node* bst = NULL;
    Node* min, *max, *next, *prev;
    int n = 10000;
    int* arr;
    arr = getRandomArray(n);
    cout<< endl;
    
    avl = insertIter(avl, arr[0]);
    for (int i = 1; i < n; i++){
        insertIter(avl, arr[i]);
    }
    bst = insertRec(bst, arr[0]);
    for (int i = 1; i < n; i++){
        insertRec(bst, arr[i]);
    }
    
    printAVL(avl);
    cout << endl;
    printBST(bst);
    cout << endl;
    
    deleteIter(avl, arr[3]);
    cout <<arr[3]<<" is deleted."<<endl;
    printBST(avl);
    cout<<endl;
    
    max = findMaxIter(avl);
    min = findMinIter(avl);
    cout <<"The max value is: ";
    printData(max);
    cout <<"The min value is: ";
    printData(min);
    next = findNextIter(avl, arr[2]); 
    prev = findPrevIter(avl, arr[5]); 
    cout <<"The next largest value of "<< arr[2]<<" is: ";
    printData(next);
    cout <<"The previous smallest value of "<<arr[5]<<" is: ";
    printData(prev);
    //isAVL(avl);
    return 0; 
} 