#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"

//position in nodes array
static int node_order = 0;

static int path_order = 0;

static int LINES_COUNT;

static int current_path_lenght = 0;
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
  printf("4");
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
	new_node -> neighbours_max_count = 9;
	new_node -> neighbours_extension_number = 1;
	new_node -> visited = 0;
	nodes[order] = *new_node;
	node_order++;
	return order;
}


void print_edge(){
	int o = 0;
	for( o = 0;o < LINES_COUNT;o++){
			printf("ID: %d from: %d to: %d \n",o,edges[o].node_from,edges[o].node_to);
	}

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
	new_path -> iterate_edges = (int *) malloc(100 * sizeof(int));
	new_path -> iterate_nodes = (int *) malloc(100 * sizeof(int));
	new_path -> max_count = 100;
	new_path -> path_count = 0;

	return new_path;
}


void save_path(path *p){

	path *temp =  (path *) malloc(sizeof(path));

	temp -> iterate_edges = (int *) malloc(p -> path_count * sizeof(int));
	temp -> iterate_nodes = (int *) malloc(p -> path_count * sizeof(int));
	int i = 0;

	for(i = 0 ; i < p -> path_count ; i++){
		temp -> iterate_edges[i] = p-> iterate_edges[i];
		temp -> iterate_nodes[i] = p-> iterate_nodes[i];
	}
	temp -> max_count = p -> max_count;
	temp -> path_count = p -> path_count;

/*
	int k = 0;
		for(k = 0 ; k < temp->path_count ; k++){
			printf("%d",temp -> iterate_nodes[k]);
			if(k < temp->path_count -1){
				printf("-");
			}
		}
		printf(";");

							for(k = 1 ; k < temp->path_count; k++){
								edge *tmp_edge = &edges[temp -> iterate_edges[k]];
								printf("%d",tmp_edge -> yy);
								printf("-%02d",tmp_edge -> mm);
								printf("-%02d",tmp_edge -> dd);
								if(k < temp->path_count - 1){
									printf(",");
								}
							}
		printf("\n");

*/
	paths[path_order] = *temp;
	path_order++;
}



void add_node_to_path(path *p, int node_index, int edge_index){
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
//	printf("path %d ",node_index);
	p -> iterate_nodes[p -> path_count] = node_index;
	p -> iterate_edges[p -> path_count] = edge_index;
	p -> path_count++;

}

void remove_last(path *p){
	p -> iterate_nodes[p -> path_count] = -1;
	p -> iterate_edges[p -> path_count] = -1;
	p -> path_count = p -> path_count -1;
}



void dfs(int start, int end, int max_lenght, path *p, int edge_index){
	if((current_path_lenght -1)< max_lenght){ // -1 -> in path is current_lenght - 1(node) = number of edges between -> path lenght
		node *node = &nodes[start];
		add_node_to_path(p,node -> ID,edge_index);
		current_path_lenght++;

		if(start != end){
			node -> visited = 1;
			int i = 0;

			for(i = 0 ; i < node -> neighbours_count ; i++){
				edge *edge = &edges[node -> neighbours[i]];

				if(edge -> node_to == start){
					if(nodes[edge -> node_from].visited == 0){
						dfs(edge -> node_from, end, max_lenght, p, node -> neighbours[i]);
					}
				}else{
					if(nodes[edge -> node_to].visited == 0){
						dfs(edge -> node_to, end, max_lenght, p, node -> neighbours[i]);
					}
				}
			}
			remove_last(p);
			node -> visited = 0;
			current_path_lenght--;

		}else{
			save_path(p);
			remove_last(p);
			node -> visited = 0;
			current_path_lenght--;
			return;
		}
	}else{
		return;
	}
}

void print_node(){
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
}

void print_path(){
	printf("Paths: %d\n",path_order);
	FILE *f = fopen("output.txt", "w");
	if (f == NULL)
	{
	    printf("Error opening file!\n");
	    exit(1);
	}

	/* print some text */



	int l = 0;

		for( l = 0 ; l < path_order ; l++){
			path *tmp = &paths[l];
			int *array = tmp -> iterate_nodes;
			int *array2 = tmp -> iterate_edges;
					int k = 0;
					for(k = 0 ; k < tmp->path_count ; k++){
						fprintf(f,"%d",array[k]);
						if(k < tmp->path_count -1){
							fprintf(f,"-");
						}
					}
					fprintf(f,";");

					for(k = 1 ; k < tmp->path_count; k++){
						edge *tmp_edge = &edges[array2[k]];
						fprintf(f,"%d",tmp_edge -> yy);
						fprintf(f,"-%02d",tmp_edge -> mm);
						fprintf(f,"-%02d",tmp_edge -> dd);
						if(k < tmp->path_count - 1){
							fprintf(f,",");
						}
					}
					fprintf(f,";");



					fprintf(f,"\n");
		}
		fclose(f);
}


void free_all(){
	int i = 0;

	//free paths
	for(i = 0 ; i < path_order ; i++){
		free(&paths[i].iterate_nodes);
		free(&paths[i].iterate_edges);
		free(&paths[i]);
	}
	free(paths);

	//free edges
	for(i = 0 ; i < LINES_COUNT ; i++){
		free(&edges[i]);
	}
	free(edges);

	//free nodes
	for(i = 0 ; i < LINES_COUNT * 2; i++){
		free(&nodes[i].neighbours);
		free(&nodes[i]);
	}
	free(nodes);


}


int main()
{
	FILE *fp = fopen("input.csv","r");
	if (fp == NULL){
	  		return 0;
	}
	printf("Start");
	//get number of rows in file
	LINES_COUNT = countlines("input.csv");
	printf("%d",LINES_COUNT);
	int i = 0;
	char line[40];

//	edge *edges[LINES_COUNT]; //alloc
	//malloc memory for edges array
	//LINES_COUNT = number of edges
	edges = (edge *) malloc(LINES_COUNT * sizeof(edge));

	//malloc memory for nodes array
	//LINES_COUNT * 2 - for the worst case(each node different)
	nodes = (node *) malloc(LINES_COUNT * 2 * sizeof(node));

	paths = (path *) malloc(100 * sizeof(path));

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
			printf("%d",i);
	}

//	print_node();
//	print_edge();
	printf("LINES: %d \n", LINES_COUNT);
	printf("Loaded\n");
	path *p = create_path();
	dfs(0, 4, 3, p, -1);

	print_path();

	free_all();

	return 0;
}

