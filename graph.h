

#ifndef EX4_C_GRAPH_H
#define EX4_C_GRAPH_H

typedef struct GRAPH_NODE_ *pnode;

typedef struct edge_ {
    int weight;
    pnode endpoint;
    struct edge_ *next;
} edge, *pedge;


typedef struct GRAPH_NODE_ {
    int node_num;
    int weight;
    int tag;
    int prev;
    pedge edges;
    struct GRAPH_NODE_ *next;
} node, *pnode;


void build_graph_cmd(pnode *head, char *string);
void insert_node_cmd(pnode *head, char *string);
void delete_node_cmd(pnode *head ,char *string);
void printGraph_cmd(pnode head); //for self debug
void deleteGraph_cmd(pnode* head,char *string);
void shortsPath_cmd(pnode *head);
pnode newNode(int node_num);
void TSP_cmd(pnode *head);
int v_sizes();
#endif //EX4_C_GRAPH_H
/*
 *     node* _newNode = (node *) malloc(sizeof(node));
    if(_newNode == NULL) exit(1);
    _newNode->node_num = node_num;
    _newNode->edges = NULL;
    _newNode->next = NULL;
    return _newNode;
 */