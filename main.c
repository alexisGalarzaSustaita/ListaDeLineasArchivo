#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<ctype.h>

typedef struct node{
    char string[100]; 
    struct node *league; }*LIST; 

/*PROTOTIPOS*/
void startist(LIST *head); 
int createNode(LIST *new, char string[]); 
int insertEnd(LIST *head, char string[]); 
void sampleList(LIST head);
int eliminateStart(LIST *head, char string[]); 
int eliminateEnd(LIST *head, char string[]); 
int openFile(FILE **file, char nameFile[], char mode[]); 
void closeFile(FILE *file); 
int readFile(char *namesFiles[], int numberFiles, LIST *head);  

int main(){

    char *files[] = {"gramatica1.txt", "gramatica2.txt", "gramatica7.txt", "gramatica8.txt", "gramatica12.txt", "gramatica13.txt", "gramatica16.txt", "gramatica17.txt", "gramatica22.txt", "gramatica23.txt"};
    int numberFiles=sizeof(files)/sizeof(files[0]);
    LIST *list; 

    startist(&list);
    if(readFile(files,numberFiles,&list)){
        printf("Contenido: \n");  
        sampleList(list);   }
    else 
        printf("Error"); 

    return(0);                  }

/*FUNCIONES*/
void startist(LIST *head){
    *head=NULL;             }


int createNode(LIST *new, char string[]){
    int result=0; 

    *new=(LIST)malloc(sizeof(struct node)); 
    if(*new){
        strncpy((*new)->string, string, sizeof((*new)->string) - 1);
        (*new)->string[sizeof((*new)->string) - 1] = '\0'; 
        (*new)->league = NULL;
        result=1;           }

    return(result);             }


int insertEnd(LIST *head, char string[]){
    int result; 
    LIST new,aux;

    result=createNode(&new,string); 
    if(result) 
        if(!*head)
            *head=new; 
        else{
            aux=*head; 
            for(;aux->league;aux=aux->league); 
            aux->league=new;                }

    return(result);                                     } 


void sampleList(LIST head){
    if(head){
        printf("%s \n", head->string);
        sampleList(head->league);        }       }


int eliminateStart(LIST *head, char string[]){
    int result=0; 
    LIST aux; 

    if(*head){
        aux=*head; 
        strcpy(string,aux->string);
        *head=aux->league; 
        free(aux); 
        result=1;                      }

    return(result);                 }


int eliminateEnd(LIST *head, char string[]){
    int result=0;
    LIST aux,former; 

    if(*head){
        aux=*head; 
        while(aux->league){
            former=aux; 
            aux=aux->league;        }

        if(*head==aux)
            *head=NULL; 
        else
            former->league=NULL; 
    
        strcpy(string,aux->string);
        free(aux); 
        result=1;               }

    return(result);                     }


int openFile(FILE **file, char nameFile[], char mode[]){
    int result=0;

    *file=fopen(nameFile,mode); 
    if(*file)
        result=1; 

    return(result);         }


void closeFile(FILE *file){
    fclose(file);           }


int readFile(char *namesFiles[], int numberFiles, LIST *head){
    char row[100],nameFile[25],*mode="r"; 
    int result,counter;
    FILE *file; 

    for(counter=0;counter<numberFiles;counter++){ 
        strncpy(nameFile, namesFiles[counter], sizeof(nameFile) - 1);
        nameFile[sizeof(nameFile) - 1] = '\0';
        result=openFile(&file,nameFile,mode); 
        if(result){
            while(fgets(row,sizeof(row),file)!=NULL){ 
                row[strcspn(row, "\n")] = '\0';
                if(!insertEnd(head,row)) 
                    printf("Error al insertar el nodo en el archivo: %s\n", nameFile);
                                                                                             }
            closeFile(file);                }     
        else 
            printf("No se pudo abrir\n");         }     
            
    return(result);    }
