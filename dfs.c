#include <stdio.h>
#include <stdlib.h>
#include "structure.h"
#include "global.h"

/**
 * Method to find all paths between source and target
 * @params start index of source node
 * @params end index of target node
 * @params max_lenght max distance
 * @params p path
 * @params index of edge I came from
 */
void dfs(int start, int end, int max_lenght, path *p, int edge_index){
	
	if((current_path_lenght - 1)< max_lenght){ // -1 -> in path is current_lenght - 1(node) = number of edges between -> path lenght
		node *node = &nodes[start]; //get current node
		add_node_to_path(p,node -> ID,edge_index); // add node, edge to path
		current_path_lenght++;

		if(start != end){ //check if we find target
			node -> visited = 1;
			int i = 0;

			for(i = 0 ; i < node -> neighbors_count ; i++){
				edge *edge = &edges[node -> neighbors[i]];

				if(edge -> node_to == start){

					if(nodes[edge -> node_from].visited == 0){
						dfs(edge -> node_from, end, max_lenght, p, node -> neighbors[i]); //move deep to graph
					}
				}else{

					if(nodes[edge -> node_to].visited == 0){
						dfs(edge -> node_to, end, max_lenght, p, node -> neighbors[i]);
					}
				}
			}

			//stuff what I need to do for find all paths
			remove_last(p); //remove last in path
			node -> visited = 0; //set visited to 0
			current_path_lenght--; //decrease path lenght

		}else{
			save_path(p); //if i find target save path
			remove_last(p); //remove last
			node -> visited = 0;
			current_path_lenght--;
			return;
		}
	}else{
		return;
	}

}