#include "route.h"
#include "lib_record.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
const int maxint = 99;

void split(char **dst,char *str, const char* spl)
{
    char *result = NULL;
	result = strtok(str, spl);
	while(result != NULL)
	{
		strcpy(*dst++, result);
		result = strtok(NULL, spl);
	}
}	

void print_weights(int* w,int vernum)
{
     for(int i=0; i<vernum; i++)
     {
		 for(int j=0 ;j<vernum; j++)
	     {
			printf("%d",*(w+vernum*i+j));
	        printf("  ");	 
		 }
		 printf("\n");
      }
}

void create_graph(int *weights, char *topo[5000], int vernum, int edge_num)
{
	for(int i=0; i < vernum; i++)
		for(int j=0; j < vernum; j++)
		{
			*(weights + i*vernum + j) = maxint;
		}
    //update input weights
	int p, q, weight;
    const char *del = ",";
	char *r[4];
    for(int i=0; i<4; i++)
	{
	   r[i] = new char;
	}
	for(int i=0; i<edge_num; i++)
	{

        split(r,topo[i], del);
		p = atoi(r[1]);
		q = atoi(r[2]);
		weight = atoi(r[3]);
		*(weights + p * vernum + q) = weight;
	}
	for(int i =0; i < 4; i++)
	{
		delete r[i];
		r[i] = NULL;
	}
}

//你要完成的功能总入口
void search_route(char *topo[5000], int edge_num, char *demand)
{
    
    const int vernum = 5;
	int weights[vernum][vernum];
	
	//get weights from topo
    create_graph((int*)weights, topo, vernum, edge_num);

    //printf weights
	print_weights((int*)weights, vernum);

	//dijstra
	int *dist = new int[5];
	int *prev = new int[5000];
	
	dijkstra(0, vernum, edge_num, dist, prev, (int*) weights);
    
	for(int i=0; i < vernum; i++)
		printf("%d\t",dist[i]);

  


    //unsigned short result[] = {2, 6, 3};//示例中的一个解

    //for (int i = 0; i < 3; i++)
      //  record_result(result[i]);
}

void dijkstra(int startpoint, int vernum, int edge_num,int *dist, int *prev, int *w) 
{
	bool s[5000];
	for(int i=0; i<vernum; i++)
	{
        dist[i] = *(w + vernum*startpoint + i);
		s[i] = 0;
		if(dist[i] == maxint)
			prev[i] = 0;
		else
			prev[i] = startpoint;//record pre point
	}
    
	dist[startpoint] = 0;
	s[startpoint] = 1;
	for(int i=1; i<vernum; ++i)
	{
		int tmp = maxint;
		int u = startpoint;
		for(int j=0; j<vernum; ++j)
		{
			if((!s[j]) && (dist[j] < tmp))
			{
				u = j;
				tmp = dist[j];
			}
		}
		s[u] = 1;
 
       for(int j=0; j<vernum; j++)
	   {
			if((!s[j]) && (*(w+u*vernum+j) < maxint) )
			{
				int newdist = dist[u] + *(w+u*vernum+j);
                if(newdist < dist[j])
				{
					dist[j] = newdist;
					prev[j] = u;
				}
			}
	   }
		
	}
}


