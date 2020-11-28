#include <stdio.h>
#include <stdlib.h>

// The purpose of the following functions is to create an AVL tree that order characters and their occurences from a Huffman tree.
// This allows the user to search occurences of characters more easily, because you don't have to search in 


typedef struct Node{
    char data;
    int occurence;
    struct Node* left;
    struct Node* right;
}Node;

Node* new_node(int val, char c){
    Node* tree = (Node*)malloc(sizeof(Node));
    tree->data = c;
    tree->occurence = val;
    tree->left = NULL;
    tree->right = NULL;
    return tree;
}

int max(int a, int b){
    if (a>b) return a;
    else return b;
}

// The function tree_depth() calculates the height of the current tree.
// We use this function to calculate the balance factor.

int tree_depth(Node* tree){
    int height=0;
    if (tree==NULL){
        height = 1;
    }
    if ((tree->left!=NULL) && (tree->right!=NULL)){
        height = 1 + max(tree_depth(tree->left),tree_depth(tree->right));
    }
    if ((tree->left==NULL) && (tree->right!=NULL)){
        height = 1 + tree_depth(tree->right);
    }
    if ((tree->left!=NULL) && (tree->right==NULL)){
        height = 1 + tree_depth(tree->left);
    }
    return height;
}

int balance_factor(Node* tree){
    if(tree == NULL){
        return 0;
    }
    else{
        return tree_depth(tree->left) - tree_depth(tree->right);
    }
}

void add_BST(Node** tree, int val, char c){
    if (*tree == NULL){
        *tree = new_node(val,c);
    }
    if (((int) c) < ((int)((*tree)->data))){
        add_BST(&((*tree)->left) , val, c);
    }
    else if (((int) c) > ((int)((*tree)->data))){
        add_BST(&((*tree)->right) , val, c);
    }
}

void right_rotation(Node** tree){
    if(*tree != NULL){
        Node* temp = (*tree)->left;
        (*tree)->left = temp->right;
        temp->right = *tree;
        *tree = temp;
    }
}

void left_rotation(Node** tree){
    if(*tree != NULL){
        Node* temp = (*tree)->right;
        (*tree)->right = temp->left;
        temp->left = *tree;
        *tree = temp;
    }
}

// The function AVL() balance the tree with right or left rotation(s). We must use it each time we add a node to the tree.

void AVL(Node** tree){
    if (*tree != NULL){
        AVL(&((*tree)->left));
        AVL(&((*tree)->right));
        int bf = balance_factor(*tree);
        if(bf >= 2){
            if(balance_factor((*tree)->left) < 0){
                left_rotation(&((*tree)->left));
            }
            right_rotation(tree);
        }
        else if(bf <= -2){
            if(balance_factor((*tree)->right) > 0){
                right_rotation(&((*tree)->right));
            }
            left_rotation(tree);
        }
    }
}


// The function HF_to_AVL_char() looks for each leaf in the Huffman tree and put it into a new AVL tree. 
// Note that the AVL tree is ordering nodes according to the character they have, not according to their occurence.

void HF_to_AVL_char(Node** HT,Node* ht, Node** AVLT){
    while (&(*ht) != NULL){
        HF_to_AVL_char(HT, &(*ht->left), AVLT);
        HF_to_AVL_char(HT, &(*ht->right), AVLT);
        add_BST(AVLT, ht->occurence, ht->data);
        AVL(AVLT);
    }
}
    

int main(){
    Node** AVLT;
    Node** HT;
    Node* ht;
    Node* tree;
    ht = *HT;
    tree = *AVLT;
    ht = testHT();
    HF_to_AVL_char(HT, ht, AVLT);
    print2DUtil(tree);
    return 0;
}