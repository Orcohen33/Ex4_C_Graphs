#include <stdio.h>
#include "graph.h"
#include <stdlib.h>
#include <stdbool.h>
#include "string.h"


int main() {

    pnode n = newNode(0);
    n->weight = 0;
    n->tag = 0;
    n->prev = -1;
    n->edges = NULL;
    n->next = NULL;
    pnode *nn = &n;


    bool firstTime = true;
    char *_case2 = (char *) malloc(1);
    *_case2 = 'w';
    while(*_case2!='\n') {
        scanf("%c", &_case);
        *_case2 = _case;
        if(*_case2 == '\n') break;
        if (*_case2 == 'A') {

            if(!firstTime){
                if(n!=NULL){ deleteGraph_cmd(nn,_case2);}
                n = newNode(0);
                n->weight = 0;
                n->tag =0;
                n->edges = NULL;
                n->next = NULL;
                *nn = n;
                firstTime = true;
            }
            firstTime = false;
            //set new root of the graph
            //build graph by given num of ids
            build_graph_cmd(nn, _case2);
        }
        if (*_case2 == 'B'){ insert_node_cmd(nn,_case2); }
        if (*_case2 == 'D'){ delete_node_cmd(nn,_case2); }
        if (*_case2 == 'X') { printGraph_cmd(*nn); }
        if (*_case2 == 'S'){ shortsPath_cmd(nn); }
        if (*_case2 == 'T'){ TSP_cmd(nn);}

    }
    deleteGraph_cmd(nn,_case2);
    free(_case2);
    return 0;
}
