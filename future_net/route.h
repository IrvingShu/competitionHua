#ifndef __ROUTE_H__
#define __ROUTE_H__

int split(char **dst, char *str, const char* spl);
void print_weights(int* w, int edge_num);
void create_graph(int* weights, char *topo[5000], int vernum, int edge_num);
int get_demand(int *s, int *t, int **include_nodes, char *demand);

void dijkstra(int startpoint, int vernum, int edge_num, int* dist, int *prev, int *w);
void search_route(char *graph[5000], int edge_num, char *condition);
void searchPath(int *prev, int s, int t);
	

#endif
