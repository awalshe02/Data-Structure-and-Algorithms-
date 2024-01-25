#include "t1.h"
#include <stdio.h>
#include <stdlib.h>

node *new_node(int ver)
{ // makes new node with vertex
    node *tmp = malloc(sizeof(node));
    tmp->vertex = ver;
    tmp->next = NULL;
    return tmp;
}

Graph *create_graph(int num_nodes)
{
    Graph *tmp = malloc(sizeof(Graph)); // allocating memory
    tmp->vertices = num_nodes;

    tmp->adjacent = (node **)malloc(num_nodes * sizeof(node *)); // allocating memory for list

    for (int i = 0; i < num_nodes; i++)
    {
        tmp->adjacent[i] = NULL; // setting adjacent all node to null
    }
    return tmp;
}

void add_edge(Graph *g, int from, int to)
{
    // edge from -> to
    node *new = new_node(to); // make new node for to vertex
    new->next = g->adjacent[from];
    g->adjacent[from] = new; // updating adjancent list for from vertex
}

void bfs(Graph *g, int origin)
{
    int *visited = (int *)malloc(g->vertices * sizeof(int)); //memoery allocated for array

    for (int i = 0; i < g->vertices; i++)
    {
        visited[i] = 0; //setting to 0 as nothing visited yet
    }

    int *queue = (int *)malloc(g->vertices * sizeof(int)); //allocating memory for queue array
    int front = 0, back = 0;

    visited[origin] = 1;    //origin is visited
    queue[back++] = origin; //adding to back of queue

    printf("\nBFS ");
    while (front < back)
    {
        int curr = queue[front++]; //move to next element in queue from front
        node *tmp = g->adjacent[curr]; //adj list for current node

        printf(" %c ", 'A' + curr); //printing vertex

        while (tmp != NULL) //while node isnt empty
        {
            int adj = tmp->vertex;

            if (visited[adj] == 0) //not visited
            {
                visited[adj] = 1; //now visited
                queue[back++] = adj; //adding to back of queue
            }
            tmp = tmp->next; //go to next node
        }
    }
    printf("\n");
    free(visited); //freeing memory
    free(queue);
}

void other_dfs(Graph *g, int origin, int *visited)
{
    visited[origin] = 1; //make node as visited

    printf(" %c ", 'A' + origin); //printing vertex
    node *tmp = g->adjacent[origin];  //get adj list for current node

    while (tmp != NULL)
    {
        int adj = tmp->vertex;

        if (visited[adj] == 0) 
        {
            other_dfs(g, adj, visited); // call function again is not visited
        }
        tmp = tmp->next; //next node
    }
}

void dfs(Graph *g, int origin)
{
    int *visited = (int *)malloc(g->vertices * sizeof(int)); //aollocating memory for visited array
    for (int i = 0; i < g->vertices; i++)
    {
        visited[i] = 0; // putting all to false
    }

    printf("DFS:");
    other_dfs(g, origin, visited); //call function to do dfs
    free(visited); //freeing memory
}

void delete_graph(Graph *g)
{
    for (int i = 0; i < g->vertices; i++)
    {
        node *new = g->adjacent[i]; //get adj for currrent node

        while (new != NULL) //when full
        {
            node *tmp = new;
            new = new->next; //moving current to nxt one
            free(tmp); //freeing old current, aka prev
        }
    }

    free(g->adjacent); //freeing array of adj list
    free(g); //freeing graph
}

// converts an upper case character (A-Z) to a numerical value (between 0 and 25) 
static int char2val ( char c ) {
	if ( c < 'A' || c > 'Z' ) {
		return -1;
	}

	return c-'A';
}

int main(){
    int num_nodes = 6;
    Graph *graph = create_graph(num_nodes);
   
    add_edge(graph, char2val('A'), char2val('E'));
    add_edge(graph, char2val('B'), char2val('D'));
    add_edge(graph, char2val('A'), char2val('D'));
    add_edge(graph, char2val('A'), char2val('B'));
    add_edge(graph, char2val('B'), char2val('C'));
    add_edge(graph, char2val('C'), char2val('B'));
    add_edge(graph, char2val('E'), char2val('D'));
    add_edge(graph, char2val('D'), char2val('F'));
    add_edge(graph, char2val('F'), char2val('C'));
    add_edge(graph, char2val('C'), char2val('D'));

    dfs(graph, char2val('A'));
    bfs(graph, char2val('A'));

    delete_graph(graph);

}
