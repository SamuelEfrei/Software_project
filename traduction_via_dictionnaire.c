#include <stdio.h>
#include <stdlib.h>

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