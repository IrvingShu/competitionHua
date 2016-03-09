#ifndef __ROUTE_H__
#define __ROUTE_H__

void split(char **dst, char *str, const char* spl);
void print_weights(int* w, int edge_num);
void create_graph(int* weights, char *topo[5000], int vernum, int edge_num);

void dijkstra(int startpoint, int vernum, int edge_num, int* dist, int *prev, int *w);
void search_route(char *graph[5000], int edge_num, char *condition);

#endif
