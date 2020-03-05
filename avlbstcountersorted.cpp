#include <iostream>
#include <time.h>
using namespace std; 
  
struct Node { 
    int data; 
    int height;
    Node *left, *right; 
}; 

int avl_counter = 1;
int bst_counter = 1;
int avl_total = 0;
int bst_total = 0;
  
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
    for (int i = 0; i < n; i++) { //workon
        arr[i] = rand();
    }
    return arr;
}

int* getSortedArray(int n) {
    int* arr = new int[n];
    for (int i = 0; i < n; i++) {
        arr[i] = n - i;
    }
    return arr;
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
    root->height = max(height(root->left), height(root->right)) + 1;
    int balance = bFactor(root);
    if (balance < -1) {
        int childbalance = bFactor(root->right);
        if (childbalance > 0) {
            root->right = rightRotate(root->right);
            avl_counter += 2;
            avl_counter +=2;
            return leftRotate(root);
            
        }
        else {
            avl_counter +=2;
            return leftRotate(root);
        }
    }
    if (balance > 1) {
        int childbalance = bFactor(root->left);
        if (childbalance < 0) {
            root->left = leftRotate(root->left);
            avl_counter +=2;
            avl_counter +=2;
            return rightRotate(root);
        }
        else {
            avl_counter +=2;
            return rightRotate(root);
        }
    }
    return root;
}

Node* insertIter(Node* root, int val) {
    Node* newnode = newNode(val);
    Node* current = root;
    Node* next = NULL;
    while (current != NULL) { 
        next = current; 
        if (val < current->data) {
            current = current->left; 
            avl_counter += 1;
        }      
        else {
            current = current->right;
            avl_counter += 1;
        }      
    }
    if (next == NULL) 
        next = newnode;
    else if (val < next->data) {
        next->left = newnode; 
        avl_counter += 1;
    }
        
    else {
        next->right = newnode; 
        avl_counter += 1;
    }
    avl_total += avl_counter;  
    next = rebalance (next);     
    return next; 
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

Node* insertIterBST(Node* root, int val) { 
    Node* newnode = newNode(val);
    Node* current = root;
    Node* next = NULL;
    while (current != NULL) { 
        next = current; 
        if (val < current->data) {
            current = current->left; 
            bst_counter += 1;
        }      
        else {
            current = current->right;
            bst_counter += 1;
        }      
    }
    if (next == NULL) 
        next = newnode;
    else if (val < next->data) {
        next->left = newnode; 
        bst_counter += 1;
    }
        
    else {
        next->right = newnode; 
        bst_counter += 1;
    }
    bst_total += bst_counter;
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
   int lh;
   int rh;
   if(root == NULL)
      return 1;
   lh = height(root->left); // left height
   rh = height(root->right); // right height
   if(abs(lh-rh) <= 1 && AVL(root->left) && AVL(root->right)){
       return 1;
   } 
   cout << "not avl"<<endl;
   return 0;
}

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
    cout << "Building an AVL tree with "<< n <<" nodes traversed " << avl_counter << " times down." << endl;
    
    bst = insertIterBST(bst, arr[0]);
    for (int i = 1; i < n; i++){
        insertIterBST(bst, arr[i]);
    }
    cout << "Building an BST tree with "<< n <<" nodes traversed " << bst_counter << " times down." << endl;
    
 
    /*
    printInorder(avl);
    cout << endl;
    printInorder(bst);
    cout << endl;
    
    deleteIter(avl, arr[3]);
    avl = rebalance(avl);
    cout <<arr[3]<<" is deleted."<<endl;
    printInorder(avl);
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
    */
    return 0; 
} 