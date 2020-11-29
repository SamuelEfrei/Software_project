#include <stdio.h>
#include <stdlib.h>
#include "myfunc.h"


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
