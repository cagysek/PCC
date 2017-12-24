#include <stdio.h>
#include <stdlib.h>
#include "structure.h"
#include "global.h"

static const int DEFAULT_PATH_SIZE = 100000;

static const int DEFAULT_ARRAY_SIZE = 100;

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
	new_path -> iterate_edges = (int *) malloc(DEFAULT_ARRAY_SIZE * sizeof(int));
	new_path -> iterate_nodes = (int *) malloc(DEFAULT_ARRAY_SIZE * sizeof(int));
	new_path -> max_count = DEFAULT_ARRAY_SIZE;
	new_path -> path_count = 0;

	return new_path;
}

/**
 * Method to add node and edge to path
 * @params p path pointer
 * @params node_index index of node in nodes array
 * @params edge_index index of edge in edges array
 */
void add_node_to_path(path *p, int node_index, int edge_index){
	
	//check array size in path to store nodes and edges, possibly enlarge it
	if((p -> max_count - 1) < p -> path_count){
		int extension_number = p -> extension_number + 1; //increase extension number by 1
		p -> extension_number = extension_number;
		p -> max_count = extension_number * DEFAULT_ARRAY_SIZE; //increase max count of array(max array size)
		int *tmp1, *tmp2;
		tmp1 = realloc(p -> iterate_nodes, extension_number * DEFAULT_ARRAY_SIZE * sizeof(path)); //save realloc
		tmp2 = realloc(p -> iterate_edges, extension_number * DEFAULT_ARRAY_SIZE * sizeof(path));

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
 * @params p path pointer
 */
void save_path(path *p){
	//check paths array size to store paths, possibly enlarge it
	if((path_order) > path_array_max - 1){
		path_extension_number = path_extension_number + 1;
		path_array_max = path_extension_number * DEFAULT_PATH_SIZE; //increase max count of array(max array size)
		path *tmp1;
		tmp1 = realloc(paths, (path_extension_number * DEFAULT_PATH_SIZE) * sizeof(path)); //save realloc

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

	//create new path and copy values from p
	path *temp =  (path *) malloc(sizeof(path));

	temp -> iterate_edges = (int *) malloc((p -> path_count ) * sizeof(int));
	temp -> iterate_nodes = (int *) malloc(p -> path_count * sizeof(int));
	
	int i;
	for(i = 0 ; i < p -> path_count ; i++){
		temp -> iterate_edges[i] = p-> iterate_edges[i];
		temp -> iterate_nodes[i] = p-> iterate_nodes[i];
	}

	temp -> max_count = p -> max_count;
	temp -> path_count = p -> path_count;

	//calculate metric
	int metric = count_metric(temp);
	temp -> metric = metric;

	//add path to paths
	paths[path_order] = *temp;
	path_order++;
}

/**
 * Method to remove last node, edge from path
 * @params p path pointer
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

	//traverse all paths in array
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
}

/**
 * Compare method to sort paths by size, if two is equal sort by metric
 * @params a pointer
 * @params b pointer
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

/**
 * Method to calculate metric
 * first get min max date
 * after convert date to number and make difference
 */
int count_metric(path *p){
	date *d_max = create_date(0, 0, 0); 
	date *d_min = create_date(9999,99,99);
	date *d_temp = NULL;

	int i;
	for(i = 1 ; i < p->path_count; i++){
		edge *tmp_edge = &edges[p -> iterate_edges[i]]; //get edge from path
		date *d_temp = tmp_edge -> date; //get date from edge

		//get min
		if(d_temp -> yy < d_min -> yy){ //check year
        	d_min -> yy = d_temp -> yy;
        	d_min -> mm = d_temp -> mm;
        	d_min -> dd = d_temp -> dd;
	    }else if (d_temp -> yy == d_min -> yy && d_temp -> mm < d_min -> mm){ //check month
	        d_min -> yy = d_temp -> yy;
        	d_min -> mm = d_temp -> mm;
        	d_min -> dd = d_temp -> dd;
	    }else if (d_temp -> yy == d_min -> yy && d_temp -> mm == d_min -> mm && d_temp -> dd < d_min -> dd){ //check day
	        d_min -> yy = d_temp -> yy;
        	d_min -> mm = d_temp -> mm;
        	d_min -> dd = d_temp -> dd;
	    }

	    //get max
	    if(d_temp -> yy > d_max -> yy){
        	d_max -> yy = d_temp -> yy;
        	d_max -> mm = d_temp -> mm;
        	d_max -> dd = d_temp -> dd;
	    }else if (d_temp -> yy == d_max -> yy && d_temp -> mm > d_max -> mm){
	        d_max -> yy = d_temp -> yy;
        	d_max -> mm = d_temp -> mm;
        	d_max -> dd = d_temp -> dd;
	    }else if (d_temp -> yy == d_max -> yy && d_temp -> mm == d_max -> mm && d_temp -> dd > d_max -> dd){
	        d_max -> yy = d_temp -> yy;
        	d_max -> mm = d_temp -> mm;
        	d_max -> dd = d_temp -> dd;
	    }
	}

	int dif = date_to_number(d_max) - date_to_number(d_min);

	free(d_max);
	free(d_min);

	return dif;
}