#ifndef CIRCUIT
#define CIRCUIT


#include  "./quantomlibrary.h"



typedef enum {
    GATE_H,
    GATE_X,
    GATE_Y,
    GATE_Z,
    GATE_T,
    GATE_CNOT,
    GATE_CP,
    GATE_S,
    GATE_SWAP
} GateType;



struct circuitListNode{

    struct Gates * gate;
    struct circuitListNode * next;

};  

struct Gates{

    GateType gate;
    int control;
    int target;

};


struct circuitList{
    struct circuitListNode * head;
    struct circuitListNode * tail;


};



struct circuitList * createList();



struct circuitList * addNode(struct circuitList * list, GateType type, int control , int target);


void printCircuit(struct circuitList * list);


void printCircuitImproved(struct circuitList * list, Quantom_register * q);

#endif 