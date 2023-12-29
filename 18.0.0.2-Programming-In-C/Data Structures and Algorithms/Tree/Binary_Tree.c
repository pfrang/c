#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node* left;
    struct node* right;
};

struct node *new_node(int data){
    struct node* temp = (struct node*) malloc (sizeof(struct node));
    temp->data = data;
    temp->left = NULL;
    temp->right = NULL;
    return temp;
}

struct node *insertNode(struct node *node, int data){
    if(node == NULL) return new_node(data);
    if(data < node->data){
        node->left = insertNode(node->left, data);
    }
    else if(data > node->data){
        node->right = insertNode(node->right, data);
    }
    return node;
}

void inorderTraversal(struct node *root){
    if(root != NULL){
        inorderTraversal(root->left);
        printf("%d \n", root->data);
        inorderTraversal(root->right);
    }
}

void preorderTraversal(struct node *root){
    if(root != NULL){
        printf("%d \n", root->data);
        preorderTraversal(root->left);
        preorderTraversal(root->right);
    }
}

void postorderTraversal(struct node *root){
    if(root != NULL){
        postorderTraversal(root->left);
        postorderTraversal(root->right);
        printf("%d \n", root->data);
    }
}

int isBST(struct node *root){
    static struct node* prev = NULL;
    if(root != NULL){ // root have some data OR root is not empty or NULL
        if(!isBST(root->left)){ // not(isbst(root ka left))
            return 0;
        }
        if(prev != NULL && root->data <= prev->data){
            return 0;
        }
        prev = root;
        return isBST(root->left);
    }
    else{
        return 1;
    }
}

struct node* search(struct node* root, int target){
    if(root ==  NULL){
        return NULL;
    }

    if(target == root->data){
        return root;
    }

    else if(target <= root->data){
        return search(root->left, target);
    }

    else{
        return search(root->right, target);
    }
}

int main(){
    printf("---------BINARY TREE---------: \n");
    struct node *root = NULL;
    root = insertNode(root,10);
    insertNode(root,20);
    insertNode(root,30);
    insertNode(root,40);
    insertNode(root,50);
    insertNode(root,60);

    printf("PREORDER TRAVERSAL: \n");
    preorderTraversal(root);

    printf("INORDER TRAVERSAL: \n");
    inorderTraversal(root);

    printf("POSTORDER TRAVERSAL: \n");
    postorderTraversal(root);

    return 0;
}