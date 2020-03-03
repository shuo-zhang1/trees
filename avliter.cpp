#include <iostream>
using namespace std; 
  
struct BST { 
    int data; 
    int height;
    BST *left, *right, *parent; 
}; 
  
BST* newNode(int val) { 
    BST* temp = new BST; 
    temp->left = temp->right = temp->parent = NULL; 
    temp->data = val; 
    temp->height = 0;
    return temp; 
} 

int height(BST* root) {
    if (root == NULL) {
        return 0;
    }
    return root->height;
}

int bFactor(BST* root) {
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

BST* RR(BST* root) {
    BST* t1 = root->left;
    BST* t2 = t1->right;

    t1->right = root;
    root->left = t2;

    root->height = max(height(root->left), height(root->right)) + 1;
    t1->height = max(height(t1->left), height(t1->right)) + 1;

    return t1;
}

BST* LR(BST* root) {
    BST* t1 = root->right;
    BST* t2 = t1->left;

    t1->left = root;
    root->right = t2;
    
    root->height = max(height(root->left), height(root->right)) + 1;
    t1->height = max(height(t1->left), height(t1->right)) + 1;

    return t1;

}

BST* insertIter(BST* root, int val) {
    BST* parent = NULL;
    if (root == NULL) {
        root = newNode(val);
        root->parent = NULL;
        return root;
    }
    while (root != NULL) {
        if (root->data > val) {
            parent = root;
            root = root->left;
            if (root == NULL) {
                root= newNode(val);
                root->parent = parent;
                parent->left = root;
                break;
            }
            continue;
        }
        if (root->data < val) {
            parent = root;
            root = root->right;
            if (root == NULL) {
                root = newNode(val);
                root->parent = parent;
                parent->right = root;
                break;
            }
            continue;
        }
        return root;

    }
    int balance = 0;
    BST* temp = NULL;
    while (root != NULL) {
        root->height = max(height(root->left), height(root->right)) + 1;
        balance = bFactor(root);
        if (balance > 1 && root->left->data > val) {
            root = RR(root);
            balance = bFactor(root);
        }
        if (balance < -1 && root->right->data < val) {
            root = LR(root);
            balance = bFactor(root);
        }
        if (balance > 1 && root->left->data < val) {
            root->left = LR(root->left);
            root = RR(root);
            balance = bFactor(root);
        }
        if (balance < -1 && root->right->data > val) {
            root->right = RR(root->right);
            root = LR(root);
            balance = bFactor(root);
        }
        temp = root;
        root = root->parent;
    }
    return temp;
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
    BST* parent = NULL;
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
        BST* temp = root->left ? root->left : root->right;
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
        BST* temp = findMinIter(root->right);
        root->data = temp->data;
        root = root->right;
        val = temp->data;
    }
    if (root == NULL) {
        return root;
    }
    root->height = max(height(root->left), height(root->right)) + 1;
    int balance = 0;
    BST* temp2 = NULL;
    while (root != NULL) {
        root->height = max(height(root->left), height(root->right)) + 1;
        balance = bFactor(root);
        if (balance > 1 && root->left->data > val) {
            root = RR(root);
            balance = bFactor(root);
        }
        if (balance < -1 && root->right->data < val) {
            root = LR(root);
            balance = bFactor(root);
        }
        if (balance > 1 && root->left->data < val) {
            root->left = LR(root->left);
            root = RR(root);
            balance = bFactor(root);
        }
        if (balance < -1 && root->right->data > val) {
            root->right = RR(root->right);
            root = LR(root);
            balance = bFactor(root);
        }
        temp2 = root;
        root = root->parent;
    }
    return temp2;
}

void printBST(BST* root) {
     if(root == NULL)
           return;
     printBST(root->left);
     printf("%d ", root->data);
     printBST(root->right);

} 

void printData(BST* root) {
    cout << root->data << endl;
}
/*
bool AVL(BST* root) {
    if (root == NULL) {
        return 1;
    }
    int lheight = height(root->left);
    int rheight = height(root->right);
    if(abs(lheight-rheight) <= 1 && AVL(root->left) && AVL(root->right))
      return 1;
    return 0;
}

void isAVL(BST* root) {
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
    cout <<"3 is deleted"<<endl;
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
    //isAVL(root);
    return 0; 
} 
