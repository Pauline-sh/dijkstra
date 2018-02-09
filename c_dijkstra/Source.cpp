#include"Dijkstra.h"

int main()
{
	Node G = create_node();
	printf("Your current weight matrix is:\n");
	Pr_matrix(G.w_matrix, G.vertex, true);
	int answ = 1;
	while (answ == 1)
	{
		printf("Enter the start vertex and the finish one\n>> ");
		unsigned int init = 0;
		unsigned int dest = 0;
		scanf("%d", &init);
		printf(">> ");
		scanf("%d", &dest);

		int length = 0;
		int* path = Dijkstra(G, init, dest, length);

		if (!path)
		{
			printf("Vertex input error!");
		}
		else
		{
			printf("The shortest path from %d to %d: \n", init, dest);
			Pr_array(path, length);
		}
		printf("Wanna find another shorest path? 1 == yes/0 == no\n");
		scanf("%d", &answ);
		free(path);
	}

	free(G.w_matrix);
	getchar();
	getchar();
	return 0;
}