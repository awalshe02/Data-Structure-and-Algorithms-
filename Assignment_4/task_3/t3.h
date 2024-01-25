#ifndef T3_H_
#define T3_H_
#define MAX_BUFFER 256 // Maximum string length this program can handle

typedef struct Vertex{
    int id;
    char name[MAX_BUFFER];
    double latitude;
    double longitude;
}Vertex;

typedef struct Edge{
    int vertex1;
    int vertex2;
    double weight;
}Edge;

typedef struct Graph{
    Vertex *vertices;
    Edge *edges;
    int num_vertices;
    int num_edges;
    int** adj;
}Graph;

int load_edges ( char *fname ); //loads the edges from the CSV file of name fname
int load_vertices ( char *fname );  //loads the vertices from the CSV file of name fname
void shortest_path(int startNode, int endNode); // prints the shortest path between startNode and endNode, if there is any
void free_memory ( void ) ; // frees any memory that was used

#endif
