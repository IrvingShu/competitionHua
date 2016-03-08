#include "route.h"
#include "lib_record.h"
#include <stdio.h>

const int maxint = 99;


void print_weights(int* w,int edge_num)
{
     for(int i=0; i<edge_num; i++)
     {
		 for(int j=0 ;j<edge_num; j++)
	     {
			printf("%d",*(w+edge_num*i+j));
	        printf("  ");	 
		 }
		 printf("\n");
      }
}


//你要完成的功能总入口
void search_route(char *topo[5000], int edge_num, char *demand)
{

	int weights[edge_num][edge_num];
    //init weights
	for(int i=0; i < edge_num; i++)
		for(int j=0; j < edge_num; j++)
		{
			weights[i][j] = maxint;
		}
    //update input weights
	int p, q, weight;
	for(int i=0; i<edge_num; i++)
	{
		p = topo[i][2] - '0';
		q = topo[i][4] - '0';
		weight = topo[i][6] - '0';
		weights[p][q] = weight;
	}
    //printf weights
	 print_weights((int*)weights, edge_num);
    

	//dijstra
	int *dist;
	int *prev;

	dijstra();




    unsigned short result[] = {2, 6, 3};//示例中的一个解

    for (int i = 0; i < 3; i++)
        record_result(result[i]);
}

void dijkstra(int vernum,int startpoint, int edge_num, int *dist, int *prev, int *w) 
{
	bool s[5000];
	for(int i=0; i<vernum; i++)
	{
        dist[i] = c[startpoint][i];
		s[i] = 0;
		if(dist[i] == maxint)
			prev[i] = 0;
		else
			prev[i] = v;//record pre point
	}
    
	dist[v] = 0;
	s[v] = 1;
	for(int i=1; i<vernum; ++i)
	{
		int tmp = maxint;
		int u = v;
		for(int j=0; j<n; ++j)
		{
			if((!s[j]) && (dist[j] < tmp))
			{
				u = j;
				tmp = dist[j];
			}
		}
		s[u] = 1;
 
       for(int j=0; j<n; j++)
	   {
			if((!s[j]) && (*(w+u*edge_num+j) < maxint) )
			{
				int newdist = dist[u] + *(w+u*edge_num+j);
                if(newdist < dist[j])
				{
					dist[j] = newdist;
					prev[j] = u;
				}
			}
	   }
		
	}
}


