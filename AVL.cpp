#include <stdio.h>
#include <stdlib.h>

int max(int a, int b){
    if(a < b){
        return a;
    } else return b;
}

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

int getHeight(node* curr){
    if(!curr){
        return 0;
    } else {
        return curr->height;
    }
}

int getBF(node* curr){
    return getHeight(curr->left) - getHeight(curr->right);
}

node* rightRotate(node* A){
    node *B = A->left;
    node *loseChild = B->right;
    B->right = A;
    A->left = loseChild;

    //Restore height
    A->height = max(getHeight(A->left), getHeight(A->right));
    B->height = max(getHeight(B->left), getHeight(B->right));
}

node* leftRotate(node* A){
    node *B = A->right;
    node *loseChild = B->left;
    B->left = A;
    A->right = loseChild;

    //Restore height
    A->height = max(getHeight(A->left), getHeight(A->right));
    B->height = max(getHeight(B->left), getHeight(B->right));
}

struct node *input(node* curr, int num){
    if(!curr){
        curr = newNode(num);
    } else {
        if(num > curr->num){
            input(curr->right, num);
        } else {
            input(curr->left, num);
        }
    }
    curr->height = max(getHeight(curr->left), getHeight(curr->right)) + 1;
    int BF = getBF(curr);
    if(BF > 1){
        if(num > curr->left->num){
            curr->left = leftRotate(curr->left);
        }
        return rightRotate(curr);
    } else {
        if(num < curr->right->num){
            curr->left = rightRotate(curr->left);
        }
        return leftRotate(curr);
    }
}



int main(){
    root = NULL;
}