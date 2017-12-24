#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structure.h"
#include "global.h"

/**
 * Get index of source in nodes array
 * @param source source value
 * @return source index in nodes array
 */
int get_source_index(int source){
	int i;
	for(i = 0 ; i < node_order ; i++){
		if(nodes[i].ID == source){
			return i;
		}
	}
	return -1;
}

/**
 * Get index of target in nodes array
 * @param target target value
 * @return target index in nodes array
 */
int get_target_index(int target){
	int i;
	for(i = 0 ; i < node_order ; i++){
		if(nodes[i].ID == target){
			return i;
		}
	}
	return -1;
}

/**
 * Method to create node if not exist and return his index. If exist just return his index in array
 * @params new_ID number of node
 * @params current size of nodes array
 * @return index in array
 */
int create_node(int new_ID, int order){
	int i = 0;

	//exists check
	while(i < order){
		if(nodes[i].ID == new_ID){
			return i;
		}
		i++;
	}

	//if not exists create new node and add to array of nodes
	node *new_node = (node *) malloc(sizeof(node));
	new_node -> ID = new_ID;
	new_node -> neighbors = (int *) malloc(100 * sizeof(int));
	new_node -> neighbors_count = 0;
	new_node -> neighbors_max_count = 99;
	new_node -> neighbors_extension_number = 1;
	new_node -> visited = 0;
	nodes[order] = *new_node;
	node_order++;
	return order;
}

/**
 * Method which manage add index of edges to array in node
 * @params node node pointer
 * @params edge edge index
 */
void add_edge_to_node(node *node, int edge){

	//check empty space in array
	//if array is full realloc his size
	if((node -> neighbors_max_count - 1) < node -> neighbors_count){
		int extension_number = node -> neighbors_extension_number + 1; //increase extension number by 1
		node -> neighbors_extension_number = extension_number;
		node -> neighbors_max_count = extension_number * 100; //increase max count of array(max array size)
		int *tmp;
		tmp = realloc(node -> neighbors, extension_number * 100 * sizeof(node)); //save realloc

		if (!tmp)
		{
		  printf("Can not realloc neighbors array in node %d \n",node -> ID); // if realloc return null
		  return;
		}
		else
		{
			node -> neighbors = tmp;
		}
	}

	//put index of edge to array
	node -> neighbors[node -> neighbors_count] = edge;
	node -> neighbors_count++;
}

/**
* Method to print node array
*/
void print_node(){

	int q;
	for( q = 0;q< node_order;q++){
		printf("node[%d]: %d\n",q,nodes[q].ID );
		printf("Neighbors: ");
		int *array = nodes[q].neighbors;
		int k = 0;
		for(k = 0 ; k < nodes[q].neighbors_count ; k++){
			printf("%d ",array[k]);
		}
		printf("\n");
	}
}