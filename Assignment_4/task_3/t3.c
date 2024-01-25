
#include <stdio.h>
#include <stdlib.h>
#include "t3.h"
#include <stdio.h>

#define MAX_BUFFER 256 // Maximum string length this program can handle
#define VERTX_NUM 4807
#define EDGE_NUM 6180
Graph *graph = NULL;

Graph *make_graph()
{
	Graph *g = (Graph *)malloc(sizeof(Graph)); // allocating memory

	g->num_vertices = 0;
	g->num_edges = 0;
	g->adj = (int **)malloc(sizeof(int *));

	// for (int i = 0; i < vertex_num; i++)
	// {
	// 	g->adj[i] = (int *)malloc(vertex_num * sizeof(int));

	// 	for (int j = 0; j < vertex_num; j++)
	// 	{
	// 		g->adj[i][j] = 0; // setting all positiions to 0
	// 	}
	// }

	return g;
}
// The CSV parser
int next_field(FILE *f, char *buf, int max)
{
	int i = 0, end = 0, quoted = 0;

	while (!feof(f))
	{
		// fetch the next character from file
		buf[i] = fgetc(f);
		// if we encounter quotes then flip our state and immediately fetch next char
		if (buf[i] == '"')
		{
			quoted = !quoted;
			buf[i] = fgetc(f);
		}
		// end of field on comma if we're not inside quotes
		if (buf[i] == ',' && !quoted)
		{
			break;
		}
		// end record on newline or end of file
		if (feof(f) || buf[i] == '\n')
		{
			end = 1;
			break;
		}
		// truncate fields that would overflow the buffer
		if (i < max - 1)
		{
			++i;
		}
	}

	buf[i] = 0; // null terminate the string
	return end; // flag stating whether or not this is end of the line
}

void add_edge(Graph* g, Edge* e){
	// if(graph->num_edges == 0){
	// 	graph->num_edges = 0;
	// 	graph->edges[0] = *e;
	// 	graph->num_edges++;
	// }
	graph->edges[graph->num_edges] = *e;
	graph->num_edges++;
}

void get_edge(FILE *file, Graph* g, Edge *e)
{
	char buf[MAX_BUFFER];
	// reading in each token from file and putting it in correct edge element
	next_field(file, buf, MAX_BUFFER);
	e->vertex1 = atoi(buf);
	next_field(file, buf, MAX_BUFFER);
	e->vertex2 = atoi(buf);
	next_field(file, buf, MAX_BUFFER);
	e->weight = atoi(buf);

	add_edge(graph, e);
}

int load_edges(char *fname)
{
	FILE *file = fopen(fname, "r");

	if (!file)
	{
		printf("Unable to open %s\n", fname);
		return 0;
	}

	if (graph == NULL)
	{
		graph = make_graph(VERTX_NUM);
	}

	graph->edges = (Edge *)malloc(EDGE_NUM * sizeof(Edge));
	get_edge(file, graph, &graph->edges[0]); // discard the header

	printf("File %s loaded\n", fname);

	int i = 1;
	// Now read and print records until the end of the file
	while (!feof(file))
	{
		if (i < EDGE_NUM)
		{
			get_edge(file, graph, &graph->edges[i]); // getting parmeters for next array slot
			graph->num_edges++;
			i++;
		}
	}

	// Always remember to close the file
	fclose(file);
	return EXIT_SUCCESS;
}

void get_vertex(FILE *file, Vertex *v)
{
	char buf[MAX_BUFFER];
	// reading in each token from file and putting it in correct vertex element
	next_field(file, buf, MAX_BUFFER);
	v->id = atoi(buf);
	next_field(file, v->name, MAX_BUFFER);
	next_field(file, buf, MAX_BUFFER);
	v->latitude = atof(buf);
	next_field(file, buf, MAX_BUFFER);
	v->longitude = atof(buf);
}

int load_vertices(char *fname)
{
	FILE *file = fopen(fname, "r");

	if (!file)
	{
		printf("Unable to open %s\n", fname);
		return 0;
	}

	if (graph == NULL)
	{
		graph = make_graph(VERTX_NUM);
	}

	graph->vertices = (Vertex *)malloc(VERTX_NUM * sizeof(Vertex));

	get_vertex(file, &graph->vertices[0]); // discard the header

	printf("File %s loaded\n", fname);

	int i = 1;
	// Now read and print records until the end of the file
	while (!feof(file))
	{
		if (i < VERTX_NUM)
		{
			get_vertex(file, &graph->vertices[i]); // getting parmeters for next array slot
			graph->num_vertices++;
			i++;
		}
	}

	// Always remember to close the file
	fclose(file);
	return EXIT_SUCCESS;
}

// void shortest_path(int startNode, int endNode);
void free_memory(void)
{

	for (int i = 0; i < EDGE_NUM; i++)
	{
		free(graph->adj[i]); // free rows from matrix
	}
	// freeing other elements that had memry allocated
	free(graph->adj);
	free(graph->edges);
	free(graph->vertices);
	free(graph);
}

int
main ( int argc, char *argv[] ) {

	if ( argc < 3 ) {
		printf("usage: ./bus VERTICES EDGES\n");
		return EXIT_FAILURE;
	}

	if ( !load_vertices("vertices.csv") ) {
		printf("Failed to load vertices\n");
		return EXIT_FAILURE;
	}

	if ( !load_edges( "edges.csv") ) {
		printf("Failed to load edges\n");		
		return EXIT_FAILURE;
	}

	


    // get the start and end point
    printf("Please enter stating bus stop >\t\t");
    int startingNode;
    scanf("%d", &startingNode);
    printf("Please enter destination bus stop >\t");
    int endingNode;
    scanf("%d", &endingNode);

	//shortest_path(startingNode, endingNode);
    

	free_memory();

	return EXIT_FAILURE;
}

