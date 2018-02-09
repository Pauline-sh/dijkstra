#pragma once
#include"Node.h"

int* Path(unsigned int init, unsigned int dest, unsigned int* precessor, int& length)
{
	int* reverse_path = 0;
	reverse_path = (int*)malloc(sizeof(int));
	int i = 0;
	reverse_path[i] = dest + 1;
	while (true)
	{
		i++;
		reverse_path = (int*)realloc(reverse_path, (i + 1) * sizeof(int));
		reverse_path[i] = precessor[dest] + 1;
		dest = precessor[dest];
		if (dest == init)
			break;
	}

	length = i + 1;
	int max = length - 1;
	int* path = 0;

	for (int j = 0; j < length; j++)
	{
		path = (int*)realloc(path, (j + 1) * sizeof(int));
		path[j] = reverse_path[max];
		max--;
	}

	return path;
}

int* Dijkstra(Node G, unsigned int init, unsigned int dest, int& length) // возвращает массив вершин - кратчайший путь
{
	init--; dest--;
	if (((init < 0) || (init >= G.vertex)) || ((dest < 0) || (dest >= G.vertex)))
		return NULL; // проверяем не ввели ли мы какую-нибудь странную вершину

	bool* active = (bool*)malloc(sizeof(bool) * G.vertex);
	double* weight = (double*)malloc(sizeof(double) * G.vertex);
	unsigned int* precessor = (unsigned int*)malloc(sizeof(unsigned int) * G.vertex);
	for (int i = 0; i < G.vertex; i++)
	{
		active[i] = 0;
		weight[i] = INF;
		precessor[i] = 0;
	}
	active[init] = true;
	weight[init] = 0;
	precessor[init] = init;
	unsigned int cur = init;
	while (true)
	{
		double min = INF;
		for (int i = 0; i < G.vertex; i++) // проход по инит строке в поисках смежных вершин и их весов
		{
			if ((G.w_matrix[cur * G.vertex + i] != INF) && (!active[i])) // для смежных с инит вершин меняем атрибуты. i - номер смежной вершины
			{
				if (weight[i] >(weight[cur] + G.w_matrix[cur * G.vertex + i])) // узнаем, какой вес лучше (релакс)
				{
					weight[i] = weight[cur] + G.w_matrix[cur * G.vertex + i];
					precessor[i] = cur;
				}
			}
		}
		for (int i = 0; i < G.vertex; i++) // выбор следующей активной вершины
		{
			if ((weight[i] < min) && (!active[i]))
			{
				min = weight[i]; // min это вес
				cur = i;
			}
		}
		active[cur] = true;
		if (min == INF) // если все вершины помечены выходим
			break;
	}
	int* path = Path(init, dest, precessor, length);

	free(active);
	free(weight);
	free(precessor);

	return path;
}