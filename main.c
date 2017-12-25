#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structure.h"
#include "global.h"

//Position in nodes array
int node_order = 0;

//Position in path array
int path_order = 0;

static const int DEFAULT_PATH_SIZE = 100000;


node *nodes;
edge *edges;
path *paths;

/**
 * free memory on heap
 */
void free_all(){
	
	int i;

	//free paths
	for(i = 0 ; i < path_order ; i++){
		free(paths[i].iterate_nodes);
		free(paths[i].iterate_edges);
	}
	free(paths);

	
	//free edges
	for(i = 0 ; i < LINES_COUNT ; i++){
		free(edges[i].date);
	}
	free(edges);


	//free nodes
	for(i = 0 ; i < LINES_COUNT * 2; i++){
		free(nodes[i].neighbors);
		
	}
	free(nodes);

}



/**
 * Load input from console and check it
 */
int main(int argc, char *argv[])
{
	
	char *filename = argv[1];	
	int source = atoi(argv[2]);
	int target = atoi(argv[3]);
	int max_lenght = atoi(argv[4]);


	//PREPARE ARRAYS FOR STORE VALUES
 	//================================

 	//get number of rows in file
	LINES_COUNT = countlines(filename);


	//malloc memory for edges array
	//LINES_COUNT = number of edges
	edges = (edge *) malloc(LINES_COUNT * sizeof(edge));

	//malloc memory for nodes array
	//LINES_COUNT * 2 - for the worst case(each node different)
	nodes = (node *) malloc(LINES_COUNT * 2 * sizeof(node));

	//malloc memory for paths array
	//deafault size is 100 000
	paths = (path *) malloc(DEFAULT_PATH_SIZE * sizeof(path));//default size is 10 000 paths

	load_topology(filename);

	int source_index = get_source_index(source);
	int target_index = get_target_index(target);

	if(source_index != -1 && target_index != -1){

		path *p = create_path();

		dfs(source_index, target_index, max_lenght, p, -1);



		qsort(paths,path_order,sizeof(path),cmp_func_path_order);

		print_path();

		free(p -> iterate_edges);
		free(p -> iterate_nodes);
		free(p);
		free_all();

		return EXIT_SUCCESS;
	}else{
		printf("One of the input verticles does not exist\n");
		return EXIT_FAILURE;
	}
}

