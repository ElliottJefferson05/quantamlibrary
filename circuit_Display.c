#include "circuit_Display.h"
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>



const char *gate_names[] = {
    "H",
    "X",
    "Y",
    "Z",
    "T",
    "CNOT",
    "CP",
    "SWAP"
};


struct circuitList * createList(){


    struct circuitList * newlist = malloc(sizeof(struct circuitList));

    if(newlist == NULL){
        return NULL;
    }

    newlist -> head = NULL;

    newlist -> tail = NULL;


    return newlist;

}

struct circuitList * addNode(struct circuitList * list, GateType type, int control , int target){
    
    struct circuitListNode * newNode = malloc(sizeof(struct circuitListNode));

    if(newNode == NULL){
        return NULL;
    }


    newNode -> gate = malloc(sizeof(struct Gates));

    if (newNode -> gate == NULL){
        free(newNode);
        return NULL;
    }

    newNode -> gate -> gate = type;
    newNode -> gate -> control = control;
    newNode -> gate -> target = target;
    newNode -> next = NULL;


    
    if(list->head == NULL){
        


        list -> head = newNode;
        list -> tail = newNode;
        


        return list;

    }


    list -> tail -> next = newNode;
    list -> tail = newNode;

    return list;
}


void printCircuit(struct circuitList * list){

    if(list == NULL){
        return;
    }
    


    int i = 0;

    struct circuitListNode * temp = list -> head;

    while( temp != NULL){

        if(temp->gate != NULL){
        printf("the gate is %s \n",gate_names[temp->gate->gate]);
        
    }

    i++;
    temp = temp -> next;
}

}


