#include<stdio.h>
#include<stdlib.h>

struct tnode{
    int data;
    struct tnode* left;
    struct tnode* right;
};

typedef struct tnode* TNode;

TNode talloc(int data){
    TNode tree = (TNode)malloc(sizeof(TNode));
    tree->data = data;
    tree->left = NULL;
    tree->right = NULL;
    return tree;
}

TNode addnode(TNode tree, int data){
    if(tree == NULL) return talloc(data);
    else if(tree->data > data) tree->left = addnode(tree->left, data);
    else tree->right = addnode(tree->right, data);
    return tree;
}

void inorder(TNode tree){
    if(tree == NULL) return;
    inorder(tree->left);
    printf("%d ", tree->data);
    inorder(tree->right);
}

void preorder(TNode tree){
    if(tree == NULL) return;
    printf("%d ", tree->data);
    preorder(tree->left);
    preorder(tree->right);
}

int deltree(TNode tree){
    if(tree == NULL) return 0;
    
    int cnt = 1 + deltree(tree->left) + deltree(tree->right); 
    free(tree);
    
    return cnt;
}

int main(){
    TNode tree = NULL;
    int arr[] = {3, 1, 0, 2, 8, 6, 5, 9};
    int n = sizeof(arr) / sizeof(arr[0]);
    for(int i = 0; i < n; i++){
        tree = addnode(tree, arr[i]);
    }
    printf("Inorder:\n");
    inorder(tree);
    printf("\n");
    printf("Preorder:\n");
    preorder(tree);
    printf("\n");

    int delete_cnt = deltree(tree);
    printf("So luong node da xoa: %d\n", delete_cnt);
    return 0;
}

/*
OUTPUT:
Inorder:        
0 1 2 3 5 6 8 9 
Preorder:       
3 1 0 2 8 6 5 9
So luong node da xoa: 8
*/