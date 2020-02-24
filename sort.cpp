#include <iostream>
#include <vector>
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
    if (root == NULL) 
        return newNode(val); 
    if (val < root->data) 
        root->left = insertRec(root->left, val); 
    else
        root->right = insertRec(root->right, val); 
    return root; 
} 

void sort(BST* root, vector<int> elements) {
    for (int i = 1; i < elements.size(); i++){
        insertRec(root, elements[i]);
    }
}

void printBST(BST* root) {
    if(root == NULL)
           return;
     printBST(root->left);
     printf("%d ", root->data);
     printBST(root->right);

} 
  
  
int main() { 
    /*
              7 
            /    \ 
           5      10 
         /  \    /  \ 
        3    6   8   12 */
    BST* tree = NULL;
    vector<int> list{7, 5 , 6, 3, 10, 8, 12};
    tree = newNode(list[0]);
    sort(tree, list);
    printBST(tree);
    return 0;  
} 