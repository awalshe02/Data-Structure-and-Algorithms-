#include "t2.h"
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

Graph *create_graph(int num_nodes)
{
    Graph *g = (Graph *)malloc(sizeof(Graph)); // allocating memory for graph

    g->numnode = num_nodes;

    g->adj_matrix = (int **)malloc((num_nodes) * sizeof(int *)); // allocating memory foradj matrix

    for (int i = 0; i < num_nodes; i++)
    {
        g->adj_matrix[i] = (int *)malloc((num_nodes) * sizeof(int));

        for (int j = 0; j < g->numnode; j++)
        {
            g->adj_matrix[i][j] = 0; // setting whole matrix as not visited
        }
    }
    return g;
}

void add_edge(Graph *g, int from, int to, int weight)
{
    g->adj_matrix[from][to] = weight; // adding weight from -> to
    g->adj_matrix[to][from] = weight; // adding weight to -> from
}

int min_distance(int *distance, int *visit, int num_node)
{
    int min = MAX_DISTANCE;
    int min_index;

    for (int i = 0; i < num_node; i++)
    {
        if (visit[i] == 0) // if not visited
        {
            if (distance[i] < min) // if node has smaller distance or if distance equal, it'll take the one first in alphabet
            {
                min = distance[i];
                min_index = i;
            }
        }
    }
    return min_index;
}

void dijkstra(Graph *g, int origin)
{
    int num_node = g->numnode;
    int *distance = (int *)malloc(num_node * sizeof(int)); // allocating memory to store distance from source to other nodes
    int *visit = (int *)malloc(num_node * sizeof(int));    // allocating memory for visited nodes

    for (int i = 0; i < num_node; i++)
    {
        distance[i] = MAX_DISTANCE; // set to max num allowed
        visit[i] = 0;               // not visited
    }

    distance[origin] = 0; // source already at itself

    for (int c = 0; c < num_node; c++)
    {
        int s = min_distance(distance, visit, num_node); // get index of node with smallest distance
        visit[s] = 1;                                    // mark as visited

        printf("%c ", 'A' + s); // print node

        for (int i = 0; i < num_node; i++)
        {
            if (!visit[i] && g->adj_matrix[s][i] && distance[s] != MAX_DISTANCE) // check if not visited, is there is edge between s and i,
            {                                                                    // if distance isn't as big as possible (aka is there a path to node)
                if (distance[s] + g->adj_matrix[s][i] < distance[i]) //if distance from source + edge weight is less than current distance fromm node
                {
                    distance[i] = distance[s] + g->adj_matrix[s][i]; //replace with new smaller diatnce
                }
            }
        }
    }

    printf("\nThe length of the shortest path between %c and %c is %d\n", 'A' + origin, 'A', distance[0]);
    for (int i = 1; i < num_node; i++)
    {
        printf("The length of the shortest path between %c and %c is %d\n", 'A' + origin, 'A' + i, distance[i]);
    }
    free(distance); // freeing allocated memory
    free(visit);
}

void delete_graph(Graph *g)
{
    for (int i = 0; i < g->numnode; i++)
    {
        free(g->adj_matrix[i]); // freeing each row of matrix
    }
    free(g->adj_matrix); // freeing the matrix
    free(g);             // freeing graph
}

#include "t2.h"

// converts an upper case character (A-Z) to a numerical value (between 0 and 25) 
static int char2val ( char c ) {
	if ( c < 'A' || c > 'Z' ) {
		return -1;
	}

	return c-'A';
}

int main(){
    int num_nodes = 7;
    Graph *graph = create_graph(num_nodes);
   
    add_edge(graph, char2val('A'), char2val('B'),1);
    add_edge(graph, char2val('A'), char2val('C'),3);
    add_edge(graph, char2val('A'), char2val('F'), 10);
    add_edge(graph, char2val('B'), char2val('G'), 2);
    add_edge(graph, char2val('B'), char2val('D'), 7);
    add_edge(graph, char2val('B'), char2val('E'), 5);
    add_edge(graph, char2val('B'), char2val('C'), 1);
    add_edge(graph, char2val('C'), char2val('D'), 9);
    add_edge(graph, char2val('C'), char2val('E'), 3);
    add_edge(graph, char2val('D'), char2val('G'), 12);
    add_edge(graph, char2val('D'), char2val('F'), 1);
    add_edge(graph, char2val('D'), char2val('E'), 2);
    add_edge(graph, char2val('E'), char2val('F'), 2);

    dijkstra(graph, char2val('A'));
    
    delete_graph(graph);

}