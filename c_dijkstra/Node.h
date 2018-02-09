#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

struct COORDS
{
	double x;
	double y;
};

struct Node
{
	double* w_matrix;
	unsigned int vertex;
	COORDS* vertex_c; // координаты вершин, номер вершины = индекс + 1
};

const double INF = 999;

void Pr_matrix(double* matrix, int size, bool mode) // mode для того,чтобы выводить с дробной частью или без
{
	for (unsigned int i = 0; i < size; i++)
	{
		for (unsigned int j = 0; j < size; j++)
		{
			if (matrix[i * size + j] == INF)
				printf("~ ");
			else if(mode)
				printf("%4.2f ", matrix[i * size + j]);
			else
				printf("%4.0f ", matrix[i * size + j]);
		}
		printf("\n");
	}
}

void init(Node& G, unsigned int V) // тут выделяется память
{
	G.vertex = V;

	G.vertex_c = (COORDS*)malloc(sizeof(COORDS) * V);
	G.w_matrix = (double*)malloc(sizeof(double) * G.vertex * G.vertex);
}

void coords_input(Node& G, FILE* matrx)
{
	G.vertex_c = (COORDS*)malloc(sizeof(COORDS) * G.vertex);	
	int i = 0;
	while ((!feof(matrx)) || (i < G.vertex))
	{
		char* c = (char*)malloc(sizeof(char));
		char buf;
		int j = 0;
		buf = fgetc(matrx);
		if ((buf <= '0') || (buf >= '9'))
			continue;
		else 
		{
			c[j] = buf;
			buf = fgetc(matrx);
			if (feof(matrx))
			{
				printf("Error in reading file!\n");
				G.vertex_c[i].y = -1;
				free(c);
				break;
			}
			while ((buf >= '0') && (buf <= '9'))
			{
				j++;
				c = (char*)realloc(c, (j + 1) * sizeof(char));
				c[j] = buf;
				buf = fgetc(matrx);
			}
			G.vertex_c[i].x = atoi(c);
			free(c);
			if (feof(matrx))
			{
				printf("Error in reading file!\n");
				G.vertex_c[i].y = -1;
				break;
			}
		}
		buf = fgetc(matrx);		
		while ((buf <= '0') || (buf >= '9'))
		{
			if (feof(matrx))
				break;
			buf = fgetc(matrx);			
		}
		if (feof(matrx))
		{
			printf("Error in reading file!\n");
			G.vertex_c[i].y = -1;
			break;
		}
		j = 0;
		c = (char*)malloc(sizeof(char));
		c[j] = buf;
		buf = fgetc(matrx);		
		while ((buf >= '0') && (buf <= '9') && (!feof(matrx)))
		{
			j++;
			c = (char*)realloc(c, (j + 1) * sizeof(char));
			c[j] = buf;
			buf = fgetc(matrx);
		}
		G.vertex_c[i].y = atoi(c);
		free(c);
		i++;
	}
	printf("The coordinates of the vertexes are:\n");
	for (int i = 0; i < G.vertex; i++)
	{
		printf("%4.0f %4.0f\n", G.vertex_c[i].x, G.vertex_c[i].y);
	}
}

void fill_weigth_matrix(double adj_matrix[], Node& G)
{
	for (unsigned int i = 0; i < G.vertex; i++)
	{
		for (unsigned int j = 0; j < G.vertex; j++)
		{
			if (adj_matrix[i * G.vertex + j] == 1)
			{
				G.w_matrix[i * G.vertex + j] = sqrt(pow(G.vertex_c[i].x - G.vertex_c[j].x, 2) + pow(G.vertex_c[i].y - G.vertex_c[j].y, 2));
			}
			else
			{
				G.w_matrix[i * G.vertex + j] = INF;
			}
		}
	}
}

void Pr_array(int* arr, int size)
{
	for (int i = 0; i < size; i++)
	{
		printf("%d ", arr[i]);
	}
	printf("\n");
}

Node create_node()
{
	printf("Enter the number of vertexes.\nHave in mind that the number must match the matrix in the file!\n>> ");
	unsigned int V = 7;
	//scanf("%d", &V);
	FILE* matrx = fopen("matrix.txt", "r");

	double* adj_matrix = (double*)malloc(sizeof(double) * V * V);
	int c = 0;
	int i = 0;
	while ((c = fgetc(matrx)) != EOF)
	{
		if (i == V*V)
			break;
		if ((c != ' ') && (c != ',') && (c != '\n'))
		{
			c -= '0';
			adj_matrix[i] = c;
			i++;
		}
	}
	printf("This is your matrix of adjustmency:\n");
	Pr_matrix(adj_matrix, V, false);

	Node G;
	init(G, V);
	coords_input(G, matrx);
	fill_weigth_matrix(adj_matrix, G);

	free(adj_matrix);
	fclose(matrx);
	return G;
}
