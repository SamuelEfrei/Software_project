//
//  main.c
//  test
//
//  Created by Kelyan Szymczyk on 27/11/2020.
//

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>


typedef struct Element{
    char c;
    int occurence;
    struct Element* next;
}Element;

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


void disp_List(List* list){
    if(list!=NULL){
        printf("%c, occurence = %d\n",list->data->caractere,list->data->occurence);
        disp_List(list->next);
    }
}

//---------------------------list of Nodes-----------------------------------------------------

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

Node* min_list(List* list)
{
    Node* min_node = NULL;
    if(list!=NULL)
    {
        min_node = list->data;
        List* temp=list;
        while(temp!=NULL)
        {
            if(min_node->occurence >= temp->data->occurence)
            {
                min_node = temp->data;
                
            }
            temp = temp->next;
        }

    }
    return min_node;
}


Node* create_node(Element* el)
{
    Node* n = (Node*)malloc(sizeof(Node));
    n->occurence = el->occurence;
    n->caractere = el->c;
    n->left = NULL;
    n->right = NULL;
    return n;
}

List* create_List(Element* el){
    List* list= (List*)malloc(sizeof(List));
    list->data = create_node(el);
    list->next = NULL;
    return list;
}

//----------------------------------------------------------------------------------------------


Element* create_Element(char c){
    Element* new_el = (Element*)malloc(sizeof(Element));
    new_el->occurence = 1;
    new_el->c=c;
    new_el->next=NULL;
    return new_el;
}

int check_in(char c_check, Element*l){
    Element*temp;
    temp = l;
    while(temp!=NULL){
        if(temp->c == c_check) return 1;
        temp = temp->next;
    }
    return 0;
}

void add_list_Element(Element**l,Element* new_element){
    if(l==NULL){
        *l = new_element;
    }
    else{
        Element* temp;
        temp = *l;
         while (temp->next!=NULL){
            temp = temp->next;
        }
        temp->next = new_element;
    }
}

Element* from_text_to_list(){
    FILE*f1 = fopen("/Users/kelyan/Desktop/test/input.txt","r");
    char c = fgetc(f1);
    Element *list;
    list = create_Element(c);
    while(c!=EOF){
        c = fgetc(f1);
        if(check_in(c,list)==0) {
            Element* new_element = create_Element(c);
            add_list_Element(&list,new_element);
        }else{
            Element*temp = list;
            while(temp!=NULL){
                if(c==temp->c) temp->occurence += 1;
                temp = temp->next;
            }
        }
    }
    
    return list;
}

void disp_SLL(Element*l){
    if(l!=NULL){
        printf("%c, occurence = %d\n",l->c,l->occurence);
        disp_SLL(l->next);
    }
}

int sum_LF(List* list_nodes)
{
    if(list_nodes!=NULL)
    {
        return sum_LF(list_nodes->next)+1;
    }
    return 0;
}


List* Element_to_List(Element* el){
    List* f_list = create_List(el);
    List* temp = f_list;
    el = el->next;
    while(el->next!=NULL){
        temp->next = create_List(el);
        temp= temp->next;
        el = el->next;
    }
    return f_list;
}

void disp_Node(Node*tree){
    if(tree!=NULL){
        printf("%c, occurence = %d\n------\n",tree->caractere,tree->occurence);
        disp_Node(tree->left);
        disp_Node(tree->right);
    }
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
            //new_node->caractere;
            new_node->right = min1;
            new_node->left = min2;
            add_List(list_nodes,new_node);
        }
    }
}


char* dictionnaire(Node* huffman, char letter, char** pArray)
{
    if(huffman == NULL) return NULL;
    
    if(huffman->caractere == letter)
    {
        return "";
    }
    
    char* l = dictionnaire(huffman->left, letter, pArray);
    char* r = dictionnaire(huffman->right, letter, pArray);
    
    char array[16];
    strcpy(array, ""); // initialiser array
    
    if(l != NULL)
    {
        strcat(array,"0");
        strcat(array,l);
        strcpy(*pArray, array);
    }
    else
    {
        if(r != NULL)
        {
            strcat(array,"1");
            strcat(array,r);
            strcpy(*pArray, array);
        }
        else
            return NULL; // pas trouvé le caractère (l == NULL et r == NULL)
    }
    
    return *pArray;
   
}



void return_each_letter(Node* huffman, char* Array)
{
    if(huffman == NULL) return;
    
    if((huffman->left == NULL) && (huffman->right == NULL))
    {
        int s = (int) strlen(Array); // taille de la chaine
        *(Array + s) = huffman->caractere; // à la pos s, on place le caractère de l'arbre de huffman
        *(Array + s + 1) = '\0';
        return;
    }
    
    return_each_letter(huffman->left, Array);
    return_each_letter(huffman->right, Array);
    
}


void write_dico(Node* huffman, FILE* dico)
{
    char Array[257];
    strcpy(Array, "");
    
    return_each_letter(huffman, Array);
    
    int i = 0;
    char* code = malloc(sizeof(char)*9);
    while(Array[i] != '\0')
    {
        fprintf(dico, "%c : %s\n",Array[i], dictionnaire(huffman,Array[i],&code));
        i++;
    }
}





int main(){

    
    Element* list = from_text_to_list();
    printf("From the list : \n");
    List* final_list = Element_to_List(list);
    /*Node* min = min_list(final_list);
    printf("the min is %c, occurence %d",min->caractere,min->occurence);*/
    Huffman(&final_list);
    printf("From the huffman tree : \n");
    Node* Huffman = final_list->data;
    disp_Node(Huffman);



   
    
    FILE* f = fopen("/Users/kelyan/Desktop/test/input.txt","w");
    write_dico(Huffman,f);
    fclose(f);
    
    return 0;
}
