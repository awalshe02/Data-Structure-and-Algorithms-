int main(int argc, char *argv[])
{

	if (argc < 3)
	{
		printf("usage: ./bus VERTICES EDGES\n");
		return EXIT_FAILURE;
	}

	if (!load_vertices("vertices.csv"))
	{
		printf("Failed to load vertices\n");
		return EXIT_FAILURE;
	}

	if (!load_edges("edges.csv"))
	{
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

	shortest_path(startingNode, endingNode);

	free_memory();

	return EXIT_FAILURE;
}