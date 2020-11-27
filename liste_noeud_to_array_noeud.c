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

Node* from_list_to_array(List* list,int size){
    if(list!=NULL){
        Node* array = (Node*)malloc(sizeof(Node)*size);
        List* temp = list;
        for(int i=0;i<size;i++){
            array[i].caractere = temp->data->occurence;
            array[i].occurence = temp->data->caractere;
            temp = temp->next;
        }
        return array;
    }
}

void add_in_array(Node** array,Node* new_node,int size){
    Node* new_array = (Node*)malloc(sizeof(Node)*size+1);
    int check=0;
    int i;
    for(i=0;i<size;i++){
        if(new_node->caractere=(*array[i]).caractere){
            array[i]->occurence += 1;
            check = 1;
        }
        new_array[i]=*array[i];
    }
    if(check == 0){
        new_array[i+1].caractere = new_node->caractere;
        new_array[i+1].occurence = new_node->occurence;
    } 
    *array = new_array;
    free(new_array);
}

void delete_in_array(Node** array,Node* delate_node,int size){
    Node* new_array = (Node*)malloc(sizeof(Node)*size-1);
    for(int i=0;i<size;i++){
       if((*array[i]).caractere!=delate_node->caractere){
        new_array[i].caractere = (*array[i]).caractere;
        new_array[i].occurence = (*array[i]).occurence;
       } 
    }
    *array = new_array;
    free(new_array);
}
