#include <iostream>
using namespace std; 
  
struct BST { 
    int data; 
    BST *left, *right; 
}; 
  
BST* newNode(int val) { 
    BST* temp = new BST; 
    temp->left = temp->right = NULL; 
    temp->data = val; 
    return temp; 
} 

BST* insertIter(BST* root, int val) { 
    BST* newnode = newNode(val);
    BST* node = root;
    BST* next = NULL;
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
} 

BST* findMinIter(BST* root) {
    if (root == NULL)
        return NULL;
    while (root->left != NULL)
        root = root->left;
    return root;
}

BST* findMaxIter(BST* root) {
    if(root==NULL)
        return NULL;
    while (root->right != NULL)
        root = root->right;
    return root;
}

BST* findNextIter(BST* root, int key)
{
	BST* next = NULL;
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

BST* findPrevIter(BST* root, int key) {
	BST* prev = NULL;
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

BST* deleteIter(BST* root, int val) {
    BST* current, *target, *parent;
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

void printBST(BST* root) {
     if(root == NULL)
           return;
     printBST(root->left);
     printf("%d\n", root->data);
     printBST(root->right);

} 

void printData(BST* root) {
    cout << root->data << endl;
}

int main() 
{ 
    /*
              7 
            /    \ 
           5      10 
         /  \    /  \ 
        3    6   8   12 */
    BST* root = NULL; 
    BST* min, *max, *next, *prev;

    root = insertIter(root, 7); 
    insertIter(root, 10); 
    insertIter(root, 5); 
    insertIter(root, 3); 
    insertIter(root, 6); 
    insertIter(root, 8); 
    insertIter(root, 12); 
    printBST(root);
    cout << endl;
    deleteIter(root, 3);
    cout <<"3 is deleted"<<endl<<endl;
    printBST(root);
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
    return 0; 
} 