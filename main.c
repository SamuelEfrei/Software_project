#include <stdio.h>
#include <stdlib.h>
#include "myfunc.h"

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


Node* create_node(Element* el){
    Node* n = (Node*)malloc(sizeof(Node));
    n->occurence = el->occurence;
    n->caractere = el->c;
    n->left = NULL;
    n->right = NULL;
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
    FILE*f1 = fopen("Test.txt","r");
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

int sum_LF(List* list_nodes){
    if(list_nodes!=NULL) return sum_LF(list_nodes->next)+1;
}
//---------------------------Huffman tree-----------------------------------------------------
//----- ittératif-------------

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

//------------------------Element to list--------------------------------------------------------

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



//------------------------Affichger un arbre; prefiix 

void disp_Node(Node*tree){
    if(tree!=NULL){
        printf("%c, occurence = %d\n------\n",tree->caractere,tree->occurence);
        disp_Node(tree->left);
        disp_Node(tree->right);
    }
}

//-----------------------------------première partie ---------------------------------------------
//Rappel sur les fichier 
/* pour ouvrir un fichier -> fopen(le fichier,le mode de lecture )
les différents mode de lecture : 

                    r:lecture, le fichier doit exister
                    w:écriture seule, pas besoin d'exister
                    a:ajout à la fin d'un fichier
                    r+:lecture + écriture, le fichier doit exister
                    W+:lecture + écriture, supprime l'ancien fichier
                    a+:lecture + écriture, ajoute des élément à la fin du fichier
        pour fermer un fichier fclsoe(fichier)
    D'abbord déclaration du fichier :

    FILE* <nom_fichier> = fopen(<nom_fichier>,mode de lecture)
    
    pour lire tout le fichier:
    do{

        /*les différentes tâches 

    }while(!feof(F));
    fscanf(F,"%s",<nom_du_caractère>);
-    fprintf(F,"<Le_texte");

fgetc: lit un caractère ;

fgets: lit une chaîne ;

fscanf: lit une chaîne formatée.
*/
void write_from_file(){
    FILE*f1 = fopen("Test.txt","r");
    FILE*f3 = fopen("output.txt","a+");
    char c;
    if(f1!=NULL){
        c = fgetc(f1);
        while(c != EOF){
            printf("r : %c\n",c);
           FILE*f2 = fopen("dictionnaire.txt","r"); 
           int found = 0;
           while(!feof(f2)&&found!=1){
                char c2;
                int bi;
                fscanf(f2,"%c %d\n",&c2, &bi);
                if(c==c2){ 
                    fprintf(f3,"%d",bi);
                    found = 1;
                }
            }
            c = fgetc(f1);
            fclose(f2);
        }
    }else{
        printf("The file is NULL");
    }
    fclose(f1);
    fclose(f3);
}


int number_of_caracters(){
    FILE*f = fopen("Test.txt","r");
    int c;
    int counter=0;
    while(c!=EOF){
        c = fgetc(f);
        counter += 1;
    }
    return counter;
    fclose(f);
}
//--------------------------------Part 3------------------------------------------------

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



int main(){
//--------------------------------- Première partie------------------------------------------------------
    Element* list = from_text_to_list();
    printf("From the list : \n");
    List* final_list = Element_to_List(list);
    /*Node* min = min_list(final_list);
    printf("the min is %c, occurence %d",min->caractere,min->occurence);*/
    Huffman(&final_list);
    printf("From the huffman tree : \n");
    Node* Huffman = final_list->data;
    disp_Node(Huffman);
    return 0;
}