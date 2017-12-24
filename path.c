#include <stdio.h>
#include <stdlib.h>
#include "structure.h"
#include "global.h"


int path_array_max = 100000;

int path_extension_number = 1;

int current_path_lenght = 0;

/**
 * Method to create path
 * @return pointer to path
 */
path *create_path(){
	path *new_path = (path *) malloc(sizeof(path));
	new_path -> extension_number = 1;
	new_path -> iterate_edges = (int *) malloc(100 * sizeof(int));
	new_path -> iterate_nodes = (int *) malloc(100 * sizeof(int));
	new_path -> max_count = 100;
	new_path -> path_count = 0;

	return new_path;
}

/**
 * Method to add node and edge to path
 * @params p path
 * @params node_index index of node in nodes array
 * @params edge_index index of edge in edges array
 */
void add_node_to_path(path *p, int node_index, int edge_index){
	
	//check array size in path to store nodes and edges, possibly enlarge it
	if((p -> max_count - 1) < p -> path_count){
		int extension_number = p -> extension_number + 1; //increase extension number by 1
		p -> extension_number = extension_number;
		p -> max_count = extension_number * 100; //increase max count of array(max array size)
		int *tmp1, *tmp2;
		tmp1 = realloc(p -> iterate_nodes, extension_number * 100 * sizeof(path)); //save realloc
		tmp2 = realloc(p -> iterate_edges, extension_number * 100 * sizeof(path));

		if (!tmp1 && !tmp2)
		{
		  printf("Can not realloc path arrays \n"); // if realloc return null
		  return;
		}
		else
		{
			p -> iterate_nodes = tmp1;
			p -> iterate_edges = tmp2;
			
		}
	}

	p -> iterate_nodes[p -> path_count] = node_index;
	p -> iterate_edges[p -> path_count] = edge_index;
	p -> path_count++;

}

/**
 * Method to store paths which travel from source to target
 * @params p path
 */
void save_path(path *p){
	//check paths array size to store paths, possibly enlarge it
	if((path_order) > path_array_max -1){
		path_extension_number = path_extension_number + 1;
		path_array_max = path_extension_number * 100000; //increase max count of array(max array size)
		path *tmp1;
		tmp1 = realloc(paths, (path_extension_number * 100000) * sizeof(path)); //save realloc

		if (!tmp1)
		{
		  printf("Can not realloc paths array \n"); // if realloc return null
		  return;
		}
		else
		{
			paths = tmp1;
		}
	}

	path *temp =  (path *) malloc(sizeof(path));

	temp -> iterate_edges = (int *) malloc((p -> path_count ) * sizeof(int));
	temp -> iterate_nodes = (int *) malloc(p -> path_count * sizeof(int));
	int i = 0;

	for(i = 0 ; i < p -> path_count ; i++){
		temp -> iterate_edges[i] = p-> iterate_edges[i];
		temp -> iterate_nodes[i] = p-> iterate_nodes[i];
	}

	temp -> max_count = p -> max_count;
	temp -> path_count = p -> path_count;

	int metric = count_metric(temp);
	temp -> metric = metric;
	paths[path_order] = *temp;
	path_order++;
}

/**
 * Method to remove last node, edge from path
 * @params p path
 */
void remove_last(path *p){
	
	p -> iterate_nodes[p -> path_count] = -1;
	p -> iterate_edges[p -> path_count] = -1;
	p -> path_count = p -> path_count -1;

}

/**
 * Method to print all paths
 */
void print_path(){

	FILE *f = fopen("output.txt", "w");

	if (f == NULL)
	{
	    printf("Error opening file!\n");
	    exit(1);
	}

	int l = 0;
	for( l = 0 ; l < path_order ; l++){
		path *tmp = &paths[l];
		int *array = tmp -> iterate_nodes;
		int *array2 = tmp -> iterate_edges;
		int k = 0;

		//nodes
		for(k = 0 ; k < tmp->path_count ; k++){
			printf("%d",array[k]);

			if(k < tmp->path_count -1){
				printf("-");
			}
		}
		printf(";");

		//edges
		for(k = 1 ; k < tmp->path_count; k++){
			edge *tmp_edge = &edges[array2[k]];
			date *tmp_date = tmp_edge -> date;
			printf("%d",tmp_date -> yy);
			printf("-%02d",tmp_date -> mm);
			printf("-%02d",tmp_date -> dd);

			if(k < tmp->path_count - 1){
				printf(",");
			}
		}
		printf(";");

		//metric
		printf("%d\n", tmp -> metric );
		
	}
	printf("Path count: %d\n",path_order );
	fclose(f);
}

/**
 * Compare method to sort paths by size, if two is equal sort by metric
 * @params a pointer
 * @params b ponter
 * @return difference
 */
int cmp_func_path_order (const void * a,const void * b){
	path **x = (path**)&a;
	path **y = (path**)&b;

	int dif = (*x) -> path_count - (*y) -> path_count;
	if(dif == 0){ //for equal paths
		dif = (*x) -> metric - (*y) -> metric;
	}
	return dif;
}