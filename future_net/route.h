#ifndef __ROUTE_H__
#define __ROUTE_H__
#include <iostream>
#include <vector>
#include <map>
using namespace std;

int split(char **dst, char *str, const char* spl);
void print_weights(int* w, int edge_num);
int create_graph(int weights_index[600][600], int* weights[600][600], char *topo[5000], int edge_num);
int get_demand(int *s, int *t, int **include_nodes, char *demand);

void dijkstra(int startpoint, int vernum, int edge_num, int* dist, int *prev, int w[600][600], bool s[600]);
void search_route(char *graph[5000], int edge_num, char *condition);
void searchPath(int que[5000] ,int *prev, int vernum, int s, int t, vector<int> *result);
bool searchIncludeNodesPath(int *prev, int vernum, int s, int t, int *include_nodes, int include_nodes_num, vector<int> *result);

void BFS(int* w, int *path, int vernum);	
void full_array(int *array, int l, vector<int*> *result);

void print_path(vector<vector<int> > path);
void convert_demand_path(vector<vector<int> > path, int weights_index[600][600]);

int get_result(vector<vector<int> > spath, int *sdist, vector<vector<int> > vpath, map<int, int*> include_nodes_dist, vector<vector<int> > tpath, vector<vector<int> > *pass_path, int *include_nodes, int include_num);


#endif
