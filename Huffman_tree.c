#include <stdio.h>
#include <stdlib.h>

typedef struct List{
    struct Node* data;
    struct List* next;
}List;

typedef struct Node{
    int occurence;
    char caractere;
    struct Node* left;
    struct Node* right;
}Node;


List* create_list_from_Node(Node*n){
    List* l = (List*)malloc(sizeof(List));
    l->data=n;
    l->next=NULL;
    return l;
}

void add_List(List** list,Node* new_node){
    if((*list)==NULL){
        (*list) = create_list_from_Node(new_node);
    }else{
        List*temp=*list;
        while(temp->next!=NULL){
            temp = temp->next;
        }
        temp->next = create_list_from_Node(new_node);
    }
}

void delate_List(List** list,Node* min){
    if(*list!=NULL){
        List** temp=list;
        while(*temp!=NULL){
            if((*temp)->data == min){
                List* old = *temp;
                (*temp)=(*temp)->next;
                free(old);
            }
            else temp=&((*temp)->next);
        }
    }
}

Node* min_list(List* list){
    if(list!=NULL){
        Node* min_node = list->data;
        List* temp=list;
        while(temp!=NULL){
            if(min_node->occurence >= temp->data->occurence) min_node = temp->data;
            temp = temp->next;
        }
        return min_node;
    }
}

int sum_LF(List* list_nodes){
    if(list_nodes!=NULL) return sum_LF(list_nodes->next)+1;
}


void Huffman(List** list_nodes){
    if(*list_nodes!=NULL){
        while(sum_LF(*list_nodes)>1){
            Node* min1 = min_list(*list_nodes);
            delate_List(list_nodes, min1);
            Node* min2 = min_list(*list_nodes);
            delate_List(list_nodes,min2);
            Node* new_node = (Node*)malloc(sizeof(Node));
            new_node->occurence = min1->occurence + min2->occurence;
            new_node->caractere;
            new_node->right = min1;
            new_node->left = min2;
            add_List(list_nodes,new_node);
        }
    }
}