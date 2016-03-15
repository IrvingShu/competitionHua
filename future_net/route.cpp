#include "route.h"
#include "lib_record.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>
#include <queue>
#include <algorithm>
#include <iterator>
#include <vector>


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

void print_weights(int w[600][600],int vernum)
{
     for(int i=0; i<vernum; i++)
     {
		 for(int j=0 ;j<vernum; j++)
	     {
			printf("%d", w[i][j]);
	        printf("  ");	 
		 }
		 printf("\n");
      }
}

int create_graph(int nodes_index[600][600], int weights[600][600], char *topo[5000], int edge_num)
{
    int vernum = 0;
    //update input weights
	int index, p, q, weight;
    const char *del = ",";
	char *r[4];
    for(int i=0; i<4; i++)
	{
	   r[i] = new char;
	}

	int max_node = 0;
	for(int i=0; i<edge_num; i++)
	{
        split(r,topo[i], del);
		index = atoi(r[0]);
		p = atoi(r[1]);
		q = atoi(r[2]);
		weight = atoi(r[3]);
	    nodes_index[p][q] = index;
		weights[p][q] = weight;
		if(p > max_node){max_node = p ;}
		if(q > max_node){max_node = q ;}
	}
	printf("max_node: %d\n", max_node);
	vernum = max_node + 1;

	for(int i =0; i < 4; i++)
	{
		if(r[i])
		{
		   delete r[i];
		   r[i] = NULL;
		}
	}
	return vernum;
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




/*
//你要完成的功能总入口
void search_route(char *topo[5000], int edge_num, char *demand)
{
    
    int vernum = 0;   // number of vertex
	int weights[600][600];  //weights between nodes
	int nodes_index[600][600]; //nodes index
    for(int i=0; i < 600; i++)
	{
		for(int j=0; j < 600; j++)
		{
		    weights[i][j] = maxint;
			nodes_index[i][j] = maxint;
	    }	
	}

	int s=0, t=0; // s---> t
	int *include_nodes = NULL;   //must include nodes
    printf("number of edge: %d\n", edge_num);
	int include_nodes_num = get_demand(&s, &t, &include_nodes, demand);
    printf("s:%d\n", s);
	printf("t:%d\n", t);
	printf("number of must include nodes: %d\n",include_nodes_num);
	printf("The must include nodes: ");
	for(int i=0; i< include_nodes_num; i++)
		printf("%d | ", include_nodes[i]);
    printf("\n");	
	//get weights from topo
    vernum = create_graph(nodes_index, weights, topo, edge_num);
    printf("number of vertexs: %d\n", vernum);
    //printf weights
	printf("weights:\n");
	print_weights(weights, vernum);
	printf("index of nodes:\n");
    print_weights(nodes_index, vernum);
	

	//full array between must include nodes
	int **result;
	int m,n;
	full_array(include_nodes, include_nodes_num, result, m,n );

	
	//dijstra
	


	int *dist = new int[vernum];
	int *prev = new int[vernum];
	//full array
	


	dijkstra(0, vernum, edge_num, dist, prev,  weights);
   

    printf("path: ");
	for(int i=0; i < vernum; i++)
		printf("%d  ", prev[i]);
    printf("\n"); 
    searchPath(prev, 0, 2);
    

    //unsigned short result[] = {2, 6, 3};//示例中的一个解

    //for (int i = 0; i < 3; i++)
      //  record_result(result[i]);
}*/

void dijkstra(int startpoint, int vernum, int edge_num,int *dist, int *prev, int w[600][600], bool s[600]) 
{
	//bool s[5000];
	for(int i=0; i<vernum; i++)
	{
        dist[i] = w[startpoint][i];
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
			if((!s[j]) && w[u][j] < maxint) 
			{
				int newdist = dist[u] + w[u][j];
                if(newdist < dist[j])
				{
					dist[j] = newdist;
					prev[j] = u;
				}
			}
	   }
		
	}
}

void searchPath(int *prev, int vernum, int s, int t)
{
	int que[5000];
	int tot = 1;
	que[0] = t;
	int tmp = prev[t];
	bool isPass = true;
	for(int i = 0; i < vernum - 1; i++)
	{
		if(tmp == s) break;
	
		que[tot] = tmp;
		tmp = prev[tmp];
        if(que[tot] == tmp)
		{
			isPass = false;
			break;
        }
		tot++;
		
	}

	que[tot] = s;
	if(isPass)
	{	
		for(int i = tot; i> 0; i--)
		{
        
			cout << que[i] << "->";
		}
		cout << que[0] <<endl;
	}
	else
	{
		cout << s << " don't arrive " <<t <<endl;
	}
	

}

void BFS(int *map, int *path, int vernum)
{
	bool visited[vernum];
	queue<int> qu, qq;
	int s, t;
	while(true)
	{
		s = qu.size();
		if(!s) return;
		while(s--)
		{
			t = qu.front();
			for(int i = 0; i < vernum; i++)
			{
				if(*(map + vernum * t + i) != maxint &&  !visited[i])
				{
					visited[i] = 1;
					qu.push(i);
					path[i] = t;
				}
				
			}
			qu.pop();
		}
	
	}

}


void full_array(int *array, int l, vector<int*> *result)
{
	do
	{
		int *perm_result = new int[l];
		copy(array, array+l, perm_result);
       	result->push_back(perm_result);
	
	}while(next_permutation(array, array+l));

}

//你要完成的功能总入口
void search_route(char *topo[5000], int edge_num, char *demand)
{
    
    int vernum = 0;   // number of vertex
	int weights[600][600];  //weights between nodes
	int nodes_index[600][600]; //nodes index
    for(int i=0; i < 600; i++)
	{
		for(int j=0; j < 600; j++)
		{
		    weights[i][j] = maxint;
			nodes_index[i][j] = maxint;
	    }	
	}

	int s_p = 0, t_p = 0; // s---> t
	int *include_nodes = NULL;   //must include nodes
    printf("number of edge: %d\n", edge_num);
	int include_nodes_num = get_demand(&s_p, &t_p, &include_nodes, demand);
    printf("s:%d\n", s_p);
	printf("t:%d\n", t_p);
	printf("number of must include nodes: %d\n",include_nodes_num);
	printf("The must include nodes: ");
	for(int i=0; i< include_nodes_num; i++)
		printf("%d | ", include_nodes[i]);
    printf("\n");	
	//get weights from topo
    vernum = create_graph(nodes_index, weights, topo, edge_num);
    printf("number of vertexs: %d\n", vernum);
    //printf weights
	printf("weights:\n");
	print_weights(weights, vernum);
	printf("index of nodes:\n");
    print_weights(nodes_index, vernum);
	

	//full array between must include nodes
    vector<int*> include_nodes_farr;

	full_array(include_nodes, include_nodes_num, &include_nodes_farr);
    cout << "full array:" << endl; 
	for(unsigned int i = 0; i < include_nodes_farr.size(); i++)
	{
		for(int j=0; j < include_nodes_num; j++)
		{
			cout << include_nodes_farr[i][j] << " ";
		}
		cout << endl;
	
	}
    //s -- > V'
	//
	
	bool s[600];
    memset(s, 0, 600);    
    int *sDist = new int[vernum];
	int *sPrev = new int[vernum];
    dijkstra(s_p, vernum, edge_num, sDist, sPrev, weights, s);

    printf("dist: ");
	for(int i=0; i < vernum; i++)
		printf("%d  ", sDist[i]);
    printf("\n"); 
    cout << "s->v path:" <<endl;
    for(int i=0; i < include_nodes_num; i++)
	{
		searchPath(sPrev, vernum, s_p, include_nodes[i]);
	}
	//
	//
	//path between must include nodes
	
	for(unsigned int i = 0; i < include_nodes_farr.size(); i++)
	{
		int *tmp_dist = new int[vernum];
		int *tmp_prev = new int[vernum];
	    bool sV[600];
	    dijkstra(include_nodes_farr[i][0], vernum, edge_num, tmp_dist, tmp_prev, weights ,sV);
        cout << "full array:"<<i<<endl;
		for(int j = 0; j < include_nodes_num -1; j++)
		{
            //cout << "tmp_prev: " << tmp_prev[j] <<endl;
			//cout << include_nodes_farr[i][j+1] <<endl;
          
            cout << include_nodes_farr[i][j]<< " to " << include_nodes_farr[i][j+1] << " path:"<<endl;
			searchPath(tmp_prev, vernum, include_nodes_farr[i][j], include_nodes_farr[i][j+1]);
			cout << endl;
			//delete tmp_dist;
			//delete tmp_prev;
		}
		
	
	}

     
}








