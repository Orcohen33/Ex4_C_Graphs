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


    //32 bytes in 1 blocks are definitely lost in loss record 1 of 2
    bool firstTime = true;
    char *_case2 = (char *) malloc(1);
    char _case = 'w';
    while(*_case2!='\n') {
//    while(scanf("%c",_case2)) {
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

            };
            firstTime = false;
            //set new root of the graph
            //build graph by given num of ids
            build_graph_cmd(nn, _case2);
        }
        if (*_case2 == 'B'){
            insert_node_cmd(nn,_case2);
        }
        if (*_case2 == 'D'){
            delete_node_cmd(nn,_case2);
        }
        if (*_case2 == 'X') {
            printGraph_cmd(*nn);
        }
        if (*_case2 == 'S'){ shortsPath_cmd(nn);}
        if (*_case2 == 'T'){ TSP_cmd(nn);}
        if (*_case2 == 'G'){
            deleteGraph_cmd(nn,_case2);
        }
    }
    deleteGraph_cmd(nn,_case2);
    free(_case2);
    return 0;
}
// A 4 n 0 2 5 3 3 n 2 0 4 1 1 n 1 3 7 0 2 n 3 T 3 2 1 3 B 5 0 4 2 1 T 4 2 1 3 5 B 6 2 3 1 4 T 4 6 1 3 5 X
// A 4 n 0 2 5 3 3 n 2 0 4 1 1 n 1 3 7 0 2 n 3 B 5 0 4 2 1 T 4 2 1 3 5 B 6 2 3 1 4 T 4 6 1 3 5
// A 4 n 0 2 5 3 3 n 2 0 4 1 1 n 1 3 7 0 2 n 3 B 5 0 4 2 1 B 2 1 3 5 1 A 4 n 0 2 5 3 3 n 2 0 4 1 1 n 1 3 7 0 2 n 3
// A 4 n 0 2 5 3 3 n 2 0 4 1 1 n 1 3 7 0 2 n 3 X B 5 0 4 2 1 B 2 1 3 5 1 T 3 2 1 3 X
//input1 - A 4 n 0 2 5 3 3 n 2 0 4 1 1 n 1 3 7 0 2 n 3 T 3 2 1 3 X S 2 0 X
// TEST FOR SP :  A 4 n 0 2 5 3 3 n 2 0 4 1 1 n 1 3 7 0 2 X S 2 0 X
//  A 4 n 0 2 5 3 3 n 2 0 4 1 1 n 1 3 7 0 2 X S 2 0 X
// A 4 n 0 2 5 3 3 n 2 0 4 1 1 n 1 3 7 0 2 X S 2 0 X T 3 2 0 1 X
//======================================================================
//======================== PRIORITY QUEUE ==============================
//======================================================================

//======================================================================
















/* worked
 * A 3 n 0 1 1 2 3 n 1 2 1
 * try now
 * A 4 n 0 2 5 3 3 n 2 0 4 1 1 n 1 3 7 0 2
 * A 4 n 0 2 5 3 3 n 2 0 4 1 1 n 1 3 7 0 2
 * A 4 n 0 2 5 3 3 n 2 0 4 1 1 n 1 3 7 0 2 n 3 T 3 2 1 3 S 2 0
 *  A 12 n 0 1 2 1 11 3
 *  ----------------PRINT GRAPH----------------
    id : 0 ,(d: 2 , w: 5)(d: 3 , w: 3)
    id : 1 ,(d: 3 , w: 7)(d: 0 , w: 2)
    id : 2 ,(d: 0 , w: 4)(d: 1 , w: 1)
    id : 3 ,
 *   DELETE GRAPH (BY NODE) - WORKED
 *   A 4 n 0 2 5 3 3 n 2 0 4 1 1 n 1 3 7 0 2 D 0 D 1 D 2 D 3 T
 *   A 4 n 0 2 5 3 3 n 2 0 4 1 1 n 1 3 7 0 2 T D 0 D 1 D 2 D 3 T A 4 n 0 2 5 3 3 n 2 0 4 1 1 n 1 3 7 0 2 T
 *   DELETE GRAPH - WORKED
 *   A 4 n 0 2 5 3 3 n 2 0 4 1 1 n 1 3 7 0 2 T G T A 4 n 0 2 5 3 3 n 2 0 4 1 1 n 1 3 7 0 2 T
 *   BUILD NEW GRAPH ON EXISTS GRAPH - WORKED
 *   A 4 n 0 2 5 3 3 n 2 0 4 1 1 n 1 3 7 0 2 T D 0 D 1 T A 4 n 0 2 5 3 3 n 2 0 4 1 1 n 1 3 7 0 2 T
 *
 */
