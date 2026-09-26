#include "circuit_Display.h"
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include "quantomlibrary.h"

const char *gate_names[] = {
    "H",
    "X",
    "Y",
    "Z",
    "T",
    "CNOT",
    "CP",
    "SWAP"};

struct circuitList *createList()
{

    struct circuitList *newlist = malloc(sizeof(struct circuitList));

    if (newlist == NULL)
    {
        return NULL;
    }

    newlist->head = NULL;

    newlist->tail = NULL;

    return newlist;
}

struct circuitList *addNode(struct circuitList *list, GateType type, int control, int target)
{

    struct circuitListNode *newNode = malloc(sizeof(struct circuitListNode));

    if (newNode == NULL)
    {
        return NULL;
    }

    newNode->gate = malloc(sizeof(struct Gates));

    if (newNode->gate == NULL)
    {
        free(newNode);
        return NULL;
    }

    newNode->gate->gate = type;
    newNode->gate->control = control;
    newNode->gate->target = target;
    newNode->next = NULL;

    if (list->head == NULL)
    {

        list->head = newNode;
        list->tail = newNode;

        return list;
    }

    list->tail->next = newNode;
    list->tail = newNode;

    return list;
}

void printCircuit(struct circuitList *list)
{

    if (list == NULL)
    {
        return;
    }

    int i = 0;

    struct circuitListNode *temp = list->head;

    while (temp != NULL)
    {

        if (temp->gate != NULL)
        {
            printf("the gate is %s \n", gate_names[temp->gate->gate]);
        }

        i++;
        temp = temp->next;
    }
}

void printCircuitImproved(struct circuitList *list, Quantom_register *q)
{

    if (list == NULL)
    {
        return;
    }

    for (int i = 0; i < q->num_of_qbits; i++)
    {
        printf("Q_%d ", i);
        struct circuitListNode *temp = list->head;
        while (temp != NULL)
        {
            if (temp->gate->target == i)
            {
                switch (temp->gate->gate)
                {

                case GATE_H:
                    printf("-H-");
                    break;

                case GATE_Z:
                    printf("-Z-");
                    break;

                case GATE_X:
                    printf("-X-");

                    break;

                case GATE_Y:
                    printf("-Y-");

                    break;

                case GATE_T:
                    printf("-T-");

                    break;

                case GATE_S:
                    printf("-S-");

                    break;

                case GATE_CNOT:

                    break;

                case GATE_CP:

                    break;

                case GATE_SWAP:

                    break;

                default:
                    break;
                }
            }
            else
            {
                printf("---");
            }

            temp = temp->next;
        }
        printf("\n");
    }
}
