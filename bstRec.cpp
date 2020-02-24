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

BST* insertRec(BST* root, int val) { 
    if (!root) 
        return newNode(val); 
    if (val < root->data) 
        root->left = insertRec(root->left, val); 
    else
        root->right = insertRec(root->right, val); 
    return root; 
} 

BST* findMinRec(BST* root) {
    if (root == NULL){
        return NULL;
    }
    else if(root->left == NULL){
        return root;
    }
    else {
        return findMinRec(root->left);
    }
}

BST* findMaxRec(BST* root) {
    if (root == NULL){
        return 0;
    }
    else if (root->right == NULL) {
        return root;
    }
    else {
        return findMaxRec(root->right);
    }
}

void findNextRec(BST* root, BST*& next, int key) {
	if (root == NULL) {
		next = NULL;
		return;
	}
	if (root->data == key) {
		if (root->right)
			next = findMinRec(root->right);
	}
	else if (key < root->data) {
		next = root;
		findNextRec(root->left, next, key);
	}
	else
		findNextRec(root->right, next, key);
}

void findPrevRec(BST* root, BST*& prev, int key) {
	if (root == nullptr) {
		prev = nullptr;
		return;
	}
	if (root->data == key) {
		if (root->left)
			prev = findMaxRec(root->left);
	}

	else if (key < root->data) {
		findPrevRec(root->left, prev, key);
	}
	else {
		prev = root;
		findPrevRec(root->right, prev, key);
	}
}

BST* deleteRec(BST* root, int val) {
    BST* temp;
    if (root == NULL) {
        return NULL;
    }
    else if (root->data > val) {
        root->left = deleteRec(root->left, val);

    }
    else if (root->data < val) {
        root->right = deleteRec(root->right, val);
    }
    else if (root->left && root->right) {
        temp = findMinRec(root->right);
        root->data = temp->data;
        root->right = deleteRec(root->right, root->data);
    }
    else {
        temp = root;
        if (root->left == NULL) {
            root = root->right;
        }
        else if (root->right == NULL){
            root = root->left;
        }
        delete temp;
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
  
  
int main() { 
    /*
              7 
            /    \ 
           5      10 
         /  \    /  \ 
        3    6   8   12 */
    BST* root = NULL; 
    BST* min, *max, *next, *prev;

    root = insertRec(root, 7); 
    insertRec(root, 10); 
    insertRec(root, 5); 
    insertRec(root, 3); 
    insertRec(root, 6); 
    insertRec(root, 8); 
    insertRec(root, 12); 
    printBST(root);
    cout << endl;
    deleteRec(root, 3);
    cout <<"3 is deleted"<<endl<<endl;
    printBST(root);
    cout<<endl;
    max = findMaxRec(root); //should output 12
    min = findMinRec(root); //should output 5 because 3 was deleted
    cout <<"The max value is: ";
    printData(max);
    cout <<"The min value is: ";
    printData(min);
    findNextRec(root, next, 5); //should output 6
    findPrevRec(root, prev, 12); //should output 10
    cout <<"The next largest value of 5 is: ";
    printData(next);
    cout <<"The previous smallest value of 12 is: ";
    printData(prev);
    return 0;  
} 