#include <stdio.h>
#include <stdlib.h>


struct node{
    int num, height;
    struct node *left, *right;
}*root;

struct node *newNode(int num){
    node *temp = (node*) malloc(sizeof(node));
    temp->num = num;
    temp->left = NULL;
    temp->right = NULL;
    temp->height = 1;
    return temp;
}

int max(int a, int b){
    if(a > b){
        return a;
    } else return b;
}

int getHeight(node* curr){
    if(!curr){
        return 0;
    } else {
        return curr->height;
    }
}

int getBF(node* curr){ 
    if(!curr) return 0;
    return getHeight(curr->left) - getHeight(curr->right);
}

node* rightRotate(node* A){
    node *B = A->left;
    node *loseChild = B->right;
    B->right = A;
    A->left = loseChild;

    //Restore height
    A->height = max(getHeight(A->left), getHeight(A->right)) + 1;
    B->height = max(getHeight(B->left), getHeight(B->right)) + 1;

    return B;
}

node* leftRotate(node* A){
    node *B = A->right;
    node *loseChild = B->left;
    B->left = A;
    A->right = loseChild;

    //Restore height
    A->height = max(getHeight(A->left), getHeight(A->right)) + 1;
    B->height = max(getHeight(B->left), getHeight(B->right)) + 1;

    return B;
}

struct node *input(node* curr, int num){
    if(!curr){
        curr = newNode(num);
    } else {
        if(num > curr->num){
            curr->right = input(curr->right, num);
        } else {
            curr->left = input(curr->left, num);
        }
    }
    curr->height = max(getHeight(curr->left), getHeight(curr->right)) + 1;
    int BF = getBF(curr);
    if(BF > 1){
        if(num > curr->left->num){
            curr->left = leftRotate(curr->left);
        }
        return rightRotate(curr);
    } else if(BF < -1) {
        if(num < curr->right->num){
            curr->right = rightRotate(curr->right);
        }
        return leftRotate(curr);
    }
    return curr;
}

void inOrder(node *curr){
    if(!curr) return;
    inOrder(curr->left);
    printf("%d ", curr->num);
    inOrder(curr->right);
}

struct node *getPredecessor(node* curr){
    node *predecessor = curr->left;
    while(predecessor->right){
        predecessor = predecessor->right;
    }
    return predecessor;
}

struct node *deleteNode(node *curr, int num){
    if(!curr){
        return curr;
    } else if(num > curr->num){
        curr->right = deleteNode(curr->right, num);
    } else if(num < curr->num){
        curr->left = deleteNode(curr->left, num);
    } else {
        if(!curr->left || !curr->right){
            node *temp;

            if(curr->right)
                temp = curr->right;
            else
                temp = curr->left;

            if(!temp) {
                temp = curr;
                curr = NULL;
            } else {
                *curr = *temp;
            }

            free(temp);
        } else {
            node *temp = getPredecessor(curr);

            curr->num = temp->num;

            curr->left = deleteNode(curr->left, temp->num);
        }
    }

    if(!curr){
        return curr;
    }

    curr->height = max(getHeight(curr->left), getHeight(curr->right)) + 1;

    int BF = getBF(curr);

    if(BF > 1){
        if(getBF(curr->left) < 0){
            curr->left = leftRotate(curr->left);
        }
        return rightRotate(curr);
    } else if(BF < -1) {
        if(getBF(curr->right) > 0){
            curr->right = rightRotate(curr->right);
        }
        return leftRotate(curr);
    }
    return curr;
}

int main(){
    root = NULL;
    root = input(root, 1);
    root = input(root, 6);
    root = input(root, 2);
    root = input(root, 3);
    root = input(root, 5);
    root = input(root, 9);
    root = input(root, 4);
    root = input(root, 8);
    root = input(root, 7);
    root = input(root, 10);
    printf("Preorder traversal of the constructed AVL"
            " tree is \n");
    inOrder(root);
    root = deleteNode(root, 1);
    root = deleteNode(root, 8);
    root = input(root, 1);
    root = deleteNode(root, 2);
    printf("\n");
    inOrder(root);
}