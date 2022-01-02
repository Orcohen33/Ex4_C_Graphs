#include <stdio.h>
#include "graph.h"
#include <stdlib.h>
#include <stdbool.h>


static int v_size = 0;

pnode searchNodeID(pnode *head, int node_id);

void addEdge(pnode src, pnode dest, int weight);

bool updateEdge(pnode src, pnode dest, int weight);

void deleteOutEdges(pnode *head, pnode node);

void deleteinEdges(pnode *head, pnode node);

void insertLast(int data, pnode *head);

node *newNode2(int id, int weight);

int isEmpty(node **head);

void push(node **head, int id, int weight);

void pop(node **head);

int dijkstra(pnode src, pnode dest, pnode *psrc);

void resetWeightNTags(pnode *head);

// ALGORITHMS

void build_graph_cmd(pnode *head, char *inputChar) {

// ------------------------------- Adding nodes -------------------------------
    int size = 0;
    scanf("%d", &size);
    if (size > 0) {
        v_size++;
        for (int i = 1; i < size; ++i) {
            insertLast(i, head);
            v_size++;
        }
    }
// ----------------------------------------------------------------------------
// ------------------------------- Adding edges -------------------------------
    // scan from user char to build the graph
    // WORK
    while (scanf("%c", inputChar)) {
        if (*inputChar == 'n') {
            // ask for src input to connect all the rest destinations
            int src;
            scanf("%d", &src);
            pnode srcNode = searchNodeID(head, src);
            int dest, weight;
            while (scanf("%d", &dest)) {

                //if entering wrong input (no number or 'n') break the while.
                if ((*inputChar >= 'A' && *inputChar <= 'Z') || *inputChar != 'n') break;
                scanf("%d", &weight);
                pnode destNode = searchNodeID(head, dest);

                //------------ Adding edge to src,and connect to dest ---------------
                //check if edge already exists , return true if updated weight , else return false
                if (!updateEdge(srcNode, destNode, weight)) {
                    addEdge(srcNode, destNode, weight);
                }
            }
        } else if (*inputChar >= 'A' && *inputChar <= 'Z') {
            break;
        }
    }
}

void insert_node_cmd(pnode *head, char *charInput) {

    if (*charInput == 'B') {
        int src;
        scanf("%d", &src);
        pnode newNodee = searchNodeID(head, src);

        // SRC NOT FOUND
        if (newNodee == NULL) {
            // ADD NODE
            newNodee = newNode(src);

            newNodee->weight = 0;
            newNodee->tag = 0;
            newNodee->prev = -1;
            newNodee->edges = NULL;
            newNodee->next = NULL;
            // ADD EDGES
            int dest, weight;
            while (scanf("%d", &dest)) {
                if (dest >= 'A' && dest <= 'Z') { break; }
                pnode destNode = searchNodeID(head, dest);
                scanf("%d", &weight);
                if (!updateEdge(newNodee, destNode, weight)) {
                    addEdge(newNodee, destNode, weight);
                }
            }
            pnode runNode = *head;
            while (runNode->next != NULL) {
                runNode = runNode->next;
            }
            runNode->next = newNodee;
        }
            // SRC EXISTS
        else {
            deleteOutEdges(head, newNodee);

            int dest, weight;
            while (scanf("%d", &dest)) {
                if (dest >= 'A' && dest <= 'Z') { break; }
                pnode destNode = searchNodeID(head, dest);
                scanf("%d", &weight);
                if (!updateEdge(newNodee, destNode, weight)) {
                    addEdge(newNodee, destNode, weight);
                }
            }
        }
    }
}

void delete_node_cmd(pnode *head, char *charInput) {

    if (*charInput == 'D') {
        int node_id;
        scanf("%d", &node_id);

        pnode delNode = searchNodeID(head, node_id);
        if (delNode == NULL) return;
        deleteOutEdges(head, delNode);
        deleteinEdges(head, delNode);

        //------------------if the node is the head-------------------------
        pnode *temp = head;
        pnode temp2 = *head;

        if (temp != NULL) {
            if (temp2->node_num == node_id) {
                *temp = temp2->next;
                temp2->next = NULL;
                free(temp2);
                return;
            }
        }

    }


}

void printGraph_cmd(pnode head) {
    //print nodes
    printf("\n----------------PRINT GRAPH----------------\n");
    while (head != NULL) {
        printf("id : %d ,", head->node_num);
        pedge currEdge = head->edges;
        while (currEdge != NULL) {
            printf("(d: %d , w: %d)", currEdge->endpoint->node_num, currEdge->weight);
            currEdge = currEdge->next;
        }
        head = head->next;
        printf("\n");
    }


} //for self debug

void deleteGraph_cmd(pnode *head, char *inputChar) {
    pnode delNode = *head;
    while (delNode->next != NULL) {
        pnode run = delNode->next;

        deleteOutEdges(head, delNode);
        pnode *temp = head;
        pnode temp2 = *head;
        *temp = temp2->next;
        temp2->next = NULL;
        free(temp2);
        delNode = run;
    }
    deleteOutEdges(head, delNode);
    free(delNode);
}

void shortsPath_cmd(pnode *head) {


    int src, dest;
    scanf("%d", &src);
    scanf("%d", &dest);

    pnode srcNode = searchNodeID(head, src);
    pnode destNode = searchNodeID(head, dest);

    resetWeightNTags(head);
    int sp = dijkstra(srcNode, destNode, head);

    printf("Dijsktra shortest path: %d \n", sp);

}

void TSP_cmd(pnode *head) {
    int city;
    int ans = -1;
    scanf("%d", &city);

    pnode cities[city];
    for (int i = 0; i < city; ++i) {
        int n;
        scanf("%d", &n);
        cities[i] = searchNodeID(head, n);
    }
    bool contains[city];
    for (int i = 0; i < city; ++i) { contains[i] = false; }
    for (int i = 0; i < city; ++i) {
        for (int j = 0; j < city; ++j) {
            if (i == j) continue;
            resetWeightNTags(head);
            int dist = dijkstra(cities[i], cities[j], head);
            pnode reversePath = cities[j];
            // go reverse on all prevs to check if cities contain in -> become true on bool array
            int index_of_contains = 0;
            for (int k = 0; k < city; ++k) { contains[k] = false; }
            while (reversePath->prev != -1) {
                for (int k = 0; k < city; ++k) {
                    if (reversePath->node_num == cities[k]->node_num) contains[index_of_contains++] = true;
                }
                reversePath = searchNodeID(head, reversePath->prev);
            }
            for (int k = 0; k < city; ++k) {
                if (reversePath->node_num == cities[k]->node_num) contains[index_of_contains++] = true;
            }
            bool allIn = true;
            for (int k = 0; k < city; ++k) { if (contains[k] == false) allIn = false; }
            if (allIn) {
                if (dist < ans || ans == -1) {
                    ans = dist;
                    break;
                }
            }
        }
    }


    printf("TSP shortest path: %d \n", ans);
}


// ------------------------- HELP FUNCTION -------------------------
pnode newNode(int node_num) {
    pnode _newNode = malloc(sizeof(node));
    if (_newNode == NULL) exit(1);
    _newNode->node_num = node_num;
    _newNode->weight = 0;
    _newNode->tag = 0;
    _newNode->prev = -1;
    _newNode->edges = NULL;
    _newNode->next = NULL;
    return _newNode;
}

void insertLast(int data, pnode *head) {
    pnode run = *head;
    if (run == NULL) {
        run = newNode(data);
        return;
    }
    while (run->next != NULL) {
        run = run->next;
    }
    pnode prev = run;
    run = newNode(data);
    prev->next = run;
}

pnode searchNodeID(pnode *head, int node_id) {
    pnode curr = *head;
    while (curr != NULL) {
        if (curr->node_num == node_id) return curr;
        curr = curr->next;
    }
    return curr;
}

bool updateEdge(pnode src, pnode dest, int weight) {
    pedge runEdge = src->edges;
    if (runEdge == NULL) return false;
    while (runEdge != NULL) {
        if (runEdge->endpoint == dest) {
            runEdge->weight = weight;
            return true;
        }
        runEdge = runEdge->next;
    }
    return false;
}

void addEdge(pnode src, pnode dest, int weight) {
    pedge ed = malloc(sizeof(edge));
    pedge runEdge = src->edges;
    if (runEdge == NULL) {
        ed->weight = weight;
        ed->endpoint = dest;
        ed->next = NULL;
        src->edges = ed;
    } else {
        while (runEdge->next != NULL) {
            runEdge = src->edges->next;
        }
        ed->weight = weight;
        ed->endpoint = dest;
        ed->next = NULL;
        runEdge->next = ed;
    }
}

void deleteinEdges(pnode *head, pnode node) {
    pnode run = *head;
    while (run != NULL) {
        if (run == node)
            run = run->next;        // Run on all edges of "run" and check if there any dest edge equals to "node"
        pedge prev, curr = run->edges;
        // if the first edge dest point is "node" delete it and continue to next node edges
        if (curr != NULL) {
            if (curr->endpoint == node) {
                run->edges = curr->next;
                free(curr);
                run = run->next;
                continue;
            }
        }
        // if edge with endpoint equal to "node" is in middle or in the end;
        while (curr != NULL) {
            prev = curr;
            curr = curr->next;


            if (curr->endpoint == node || curr->endpoint == NULL) {
                if (curr->next != NULL) {
                    prev->next = curr->next->next;
                    free(curr);
                    break;
                } else {
                    prev->next = NULL;
                    free(curr);
                    break;
                }
            }

            curr = curr->next;
        }
        run = run->next;
    }
}

void deleteOutEdges(pnode *head, pnode node) {
    pnode run = *head;
    //get

    while (run != node) { run = run->next; }
    if (run->edges == NULL) return;
    pedge prev, curr = run->edges;
    if (curr->next != NULL) {
        while (curr->next != NULL) {
            prev = curr;
            curr = curr->next;
            free(prev);
        }
    }
    free(curr);
    run->edges = NULL;
}

int dijkstra(pnode src, pnode dest, pnode *psrc) {
    pnode head = newNode2(src->node_num, 0);
    pnode *phead = &head;
    head->tag = 1;
    pnode curr = src;
    curr->weight = 0;
    curr->tag = 1;

    while (!isEmpty(phead)) {
        curr = searchNodeID(psrc, head->node_num);
        curr->tag = 1;
        pop(phead);


        //Explore all the adj nodes
        pedge edgeData = curr->edges;
        while (edgeData != NULL) {
            pnode adj = edgeData->endpoint;
            if (adj == src) {
                edgeData = edgeData->next;
                continue;
            }

            //Here we replace the weight if there any shorter path
            int pathWeight = curr->weight + edgeData->weight;
            if (adj->weight >= pathWeight || adj->weight == 0) {
                adj->weight = pathWeight;
                if (searchNodeID(phead, adj->node_num) != NULL) {
                    searchNodeID(phead, adj->node_num)->weight = pathWeight;
                    adj->prev = curr->node_num;
                    edgeData = edgeData->next;
                    continue;
                }
                adj->prev = curr->node_num;
            }
            if (adj->tag == 0) {
                push(phead, adj->node_num, adj->weight);
            }
            edgeData = edgeData->next;
        }

    }
    free(head);
    return searchNodeID(psrc, dest->node_num)->weight;
}

void resetWeightNTags(pnode *head) {
    pnode run = *head;
    while (run != NULL) {
        run->weight = 0;
        run->tag = 0;
        run->prev = -1;
        run = run->next;
    }
}

//======================================================================
//======================== PRIORITY QUEUE ==============================
//======================================================================


// Function to Create A New node
node *newNode2(int id, int weight) {
    node *temp = (node *) malloc(sizeof(node));
    temp->node_num = id;
    temp->weight = weight;
    temp->next = NULL;
    temp->tag = 0;

    return temp;
}


// Removes the element with the
// highest priority form the list
void pop(node **head) {
    node *temp = *head;
    (*head) = (*head)->next;
    free(temp);
}

// Function to push according to priority
void push(node **head, int id, int weight) {
    node *start = (*head);

    // Create new node
    node *temp = newNode2(id, weight);

    // Special Case: The head of list has lesser
    // priority than new node. So insert new
    // node before head node and change head node.
    if (*head != NULL) {
        if ((*head)->weight > weight) {

            // Insert New node before head
            temp->next = *head;
            (*head) = temp;
        } else {

            // Traverse the list and find a
            // position to insert new node
            while (start->next != NULL &&
                   start->next->weight < weight) {
                start = start->next;
            }

            // Either at the ends of the list
            // or at required position
            temp->next = start->next;
            start->next = temp;
        }
    } else {
        *head = temp;
    }
}

// Function to check is list is empty
int isEmpty(node **head) {
    return (*head) == NULL;
}

//======================================================================
//======================= ^PRIORITY QUEUE^ =============================
//======================================================================
