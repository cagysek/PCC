#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"

//position in nodes array
static int node_order = 0;

static int path_order = 0;

node *nodes;
edge *edges;
path *paths;



/**
 * Get number of lines in input file
 * @return number of lines
 */
int countlines(char *filename)
{
  FILE *fp = fopen(filename,"r");
  int ch=0;
  int lines=0;

  if (fp == NULL){
  		return 0;
  }

  lines++;
  while ((ch = fgetc(fp)) != EOF)
    {
      if (ch == '\n')
    lines++;
    }
  fclose(fp);

  return lines;
}

/**
 * Method to create node if not exist and return his index. If exist just return his index in array
 * @return index in array
 */
int create_node(node *nodes,int new_ID, int order){
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
	new_node -> neighbours = (int *) malloc(10 * sizeof(int));
	new_node -> neighbours_count = 0;
	new_node -> neighbours_max_count = 10;
	new_node -> neighbours_extension_number = 1;
	new_node -> visited = 0;
	nodes[order] = *new_node;
	node_order++;
	return order;
}


void print_edge(edge *edge){


}


/**
 * Method which manage add index of edges to array in node
 */
void add_edge_to_node(node *node, int edge){

	//check empty space in array
	//if array is full realloc his size
	if((node -> neighbours_max_count - 1) < node -> neighbours_count){
		int extension_number = node -> neighbours_extension_number + 1; //increase extension number by 1
		node -> neighbours_extension_number = extension_number;
		node -> neighbours_max_count = extension_number * 10; //increase max count of array(max array size)
		int *tmp;
		tmp = realloc(node -> neighbours, extension_number * 10 * sizeof(node)); //save realloc

		if (!tmp)
		{
		  printf("Can not realloc neighbours array in node %d \n",node -> ID); // if realloc return null
		  return;
		}
		else
		{
			node -> neighbours = tmp;
		}
	}

	//put index of edge to array
	node -> neighbours[node -> neighbours_count] = edge;
	node -> neighbours_count++;
}

path *create_path(){
	path *new_path = (path *) malloc(sizeof(path));
	new_path -> extension_number = 1;
	new_path -> iterate_edges = (int *) malloc(10 * sizeof(int));
	new_path -> iterate_nodes = (int *) malloc(10 * sizeof(int));
	new_path -> max_count = 10;
	new_path -> path_count = 0;

	return new_path;
}


void save_path(path *p){
	paths[path_order] = *p;
	path_order++;
}



void add_node_to_path(path *p, int node_index, int edge_index){
	if((p -> max_count - 1) < p -> path_count){
		int extension_number = p -> extension_number + 1; //increase extension number by 1
				p -> extension_number = extension_number;
				p -> max_count = extension_number * 10; //increase max count of array(max array size)
				int *tmp1, *tmp2;
				tmp1 = realloc(p -> iterate_nodes, extension_number * 10 * sizeof(path)); //save realloc
				tmp2 = realloc(p -> iterate_edges, extension_number * 10 * sizeof(path));
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
//	printf("path %d ",node_index);
	p -> iterate_nodes[p -> path_count] = node_index;
	p -> iterate_edges[p -> path_count] = edge_index;
	p -> path_count++;

}

void remove_last(path *p){
//	p -> iterate_nodes[p -> path_count] = -1;
	p -> path_count--;
}



void dfs(int start, int end, int max_lenght, path *p){
		node *node = &nodes[start];

	if(start != end){
		printf("%d %d",node -> ID,node -> visited);
		int boolean = node -> visited;
		if(boolean == 0){

			node -> visited = 1;
			int i = 0;
	//		printf("%d \n",node -> ID);
			for(i = 0 ; i < node -> neighbours_count ; i++){
			//	printf("%d \n", node -> neighbours_count);
				edge *edge = &edges[node -> neighbours[i]];
			//	printf("| dfs %d -> %d.............%d |\n",nodes[edge->node_from].ID,nodes[edge ->node_to].ID,nodes[edge ->node_to].visited);

				if(edge -> node_to == start){
					if(nodes[edge -> node_from].visited == 0){
						printf("  "+nodes[edge->node_from].ID);
						add_node_to_path(p,nodes[edge -> node_from].ID,node -> neighbours[i]);
						dfs(edge -> node_from,end,max_lenght,p);
					}
				}else{
					if(nodes[edge -> node_to].visited == 0){
						printf("  "+nodes[edge->node_to].ID);
						add_node_to_path(p,nodes[edge -> node_to].ID,node -> neighbours[i]);
						dfs(edge -> node_to,end,max_lenght,p);
					}
				}
			}
			remove_last(p);
			node -> visited = 0;

		}else{
			return;
		}
	}else{
		save_path(p);

		//printf("start and end is equals\n");
		node -> visited = 0;
//		printf("%d \n",node -> ID);
		printf("end \n");
		return;
	}
}








void print_node(node *root){

}


int main()
{
	FILE *fp = fopen("inputt.csv","r");
	if (fp == NULL){
	  		return 0;
	}

	//get number of rows in file
	int LINES_COUNT = countlines("inputt.csv");
	int i = 0;
	char line[40];

//	edge *edges[LINES_COUNT]; //alloc
	//malloc memory for edges array
	//LINES_COUNT = number of edges
	edges = (edge *) malloc(LINES_COUNT * sizeof(edge));

	//malloc memory for nodes array
	//LINES_COUNT * 2 - for the worst case(each node different)
	nodes = (node *) malloc(LINES_COUNT * 2 * sizeof(node));

	paths = (path *) malloc(10 * sizeof(path));

	while(fgets (line,40, fp) != NULL){

		char * pch;
		pch = strtok (line, ";");

		edge *e = (edge *) malloc(sizeof(edge));

		int j = 0;
		int node_index_from = 0;
		int node_index_to = 0;

		//split row
			while( pch != NULL)
			{
				int val = atoi(pch);
				if( j == 0){
					//create new node and return index in array or get index of existing node with same id
					node_index_from = create_node(nodes,val,node_order);

					//set index to edge
					e -> node_from = node_index_from;
				}
				if( j == 1){
					//create new node and return index in array or get index of existing node with same id
					node_index_to = create_node(nodes,val,node_order);

					//set index to edge
					e -> node_to = node_index_to;
				}
				if( j == 2){
					char * pch2;
					pch2 = strtok (pch, "-");
					int k = 0;

					//split date
					while( pch2 != NULL){
						int val2 = atoi(pch2);
						if( k == 0){
							e -> yy = val2;
						}
						if( k == 1){
							e -> mm = val2;
						}
						if( k == 2){
							e -> dd = val2;
						}
						k++;
						pch2 = strtok(NULL,"-");
					}
				}
				j++;
				pch = strtok(NULL,";");
			}
			edges[i] = *e; //add edge to array of edges
			add_edge_to_node(&nodes[node_index_from],i);//add edge to node's array of edges - source node
			add_edge_to_node(&nodes[node_index_to],i);//add edge to node's array of edges - destination node
			i++;
	}

	int q =0;
	for( q = 0;q< node_order;q++){
		printf("node[%d]: %d\n",q,nodes[q].ID );
		printf("Neighbors: ");
		int *array = nodes[q].neighbours;
		int k = 0;
		for(k = 0 ; k < nodes[q].neighbours_count ; k++){
			printf("%d ",array[k]);
		}
		printf("\n");
	}

	int o = 0;
	for( o = 0;o < LINES_COUNT;o++){
			printf("ID: %d from: %d to: %d \n",o,edges[o].node_from,edges[o].node_to);
		}
	path *p = create_path();
	add_node_to_path(p,nodes[0].ID,nodes[0].neighbours[0]);
	dfs(0,4,20,p);

	int ll = 0;
	printf("test %d\n",path_order);
	for( ll = 0 ; ll < path_order ; ll++){
		int *array = paths[ll].iterate_nodes;
				int k = 0;
				for(k = 0 ; k < paths[ll].path_count ; k++){
					printf("%d ",array[k]);
				}
				printf("\n");
	}


	free(nodes);
	free(edges);
	return 0;
}

