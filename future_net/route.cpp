#include "route.h"
#include "lib_record.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>
using namespace std;

const int maxint = 99;
const int max_demand_nodes = 50;

int split(char **dst,char *str, const char* spl)
{
	int n=0;
    char *result = NULL;
	result = strtok(str, spl);
	while(result != NULL)
	{
		strcpy(*dst++, result);
		result = strtok(NULL, spl);
		n++;
	}
	return n;
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
		if(r[i])
		{
		   delete r[i];
		   r[i] = NULL;
		}
	}
}

int  get_demand(int *s, int *t, int** include_nodes, char *demand)
{
	const char *del = ",";
	char *r[3];
	for(int i=0; i < 3; i++)
	{
		r[i] = new char;
	}		
	split(r, demand, del);
    *s = atoi(r[0]);
	*t = atoi(r[1]);
    //printf("s: %d,  t:%d", *s, *t);

    const char *temp = "|";

	char *demand_nodes[max_demand_nodes];
    for(int i=0; i < max_demand_nodes; i++)
	{
		demand_nodes[i] = new char;
	}

	int n = split(demand_nodes , r[2], temp);
	*include_nodes = new int[n];
	for(int i=0; i<n; i++)
	{
	    *(*(include_nodes)+i) = atoi(demand_nodes[i]);
    }

	//free r memory
	for(int i=0; i < 3; i++)
	{
		if(r[i])
		{
			delete r[i];
			r[i] = NULL;
		}
	}
    //free demand_nodes memory
	for(int i=0; i < max_demand_nodes; i++)
	{
		if(demand_nodes[i])
		{
			delete demand_nodes[i];
			demand_nodes[i] = NULL;
		}
	}

	return n;

}





//你要完成的功能总入口
void search_route(char *topo[5000], int edge_num, char *demand)
{
    
    const int vernum = 5;
	int weights[vernum][vernum];
	int s=0, t=0;
	int *include_nodes = NULL;
    
	int include_nodes_num = get_demand(&s, &t, &include_nodes, demand);
    printf("s:%d\n", s);
	printf("t:%d\n", t);
	printf("n:%d\n",include_nodes_num);
	for(int i=0; i< include_nodes_num; i++)
		printf("The must nodes:%d\n", include_nodes[i]);
	
	//get weights from topo
    create_graph((int*)weights, topo, vernum, edge_num);

    //printf weights
	print_weights((int*)weights, vernum);

	//dijstra
	int *dist = new int[vernum];
	int *prev = new int[vernum];
	
	dijkstra(0, vernum, edge_num, dist, prev, (int*) weights);
    
	for(int i=0; i < vernum; i++)
		printf("%d  ", prev[i]);
    
    searchPath(prev, 0, 2);
    

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

void searchPath(int *prev, int s, int t)
{
	int que[5000];
	int tot = 1;
	que[tot] = t;
	int tmp = prev[t];
	while(tmp != s)
	{
		que[tot] = tmp;
		tot ++;
		tmp = prev[tmp];
	}

	que[tot] = s;
	for(int i = tot; i>= 1; --i)
	{
		if(i != 1)
			cout << que[i] << "->";
		else
			cout << que[i] << endl;
	}
	

}













