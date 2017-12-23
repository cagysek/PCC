#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"

//Position in nodes array
static int node_order = 0;

//Position in path array
static int path_order = 0;

//Number of lines
static int LINES_COUNT;

static int path_array_max = 1000;

static int path_extension_number = 1;

static int current_path_lenght = 0;

static int previous_node_from_index = -1;

static int previous_node_from_val = -1;

static int previous_node_to_index = -1;

static int previous_node_to_val = -1;

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
	new_node -> neighbours = (int *) malloc(100 * sizeof(int));
	new_node -> neighbours_count = 0;
	new_node -> neighbours_max_count = 99;
	new_node -> neighbours_extension_number = 1;
	new_node -> visited = 0;
	nodes[order] = *new_node;
	node_order++;
	return order;
}

/**
 * Method to print edge array
 */
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
		node -> neighbours_max_count = extension_number * 100; //increase max count of array(max array size)
		int *tmp;
		tmp = realloc(node -> neighbours, extension_number * 100 * sizeof(node)); //save realloc

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


int cmp_func_path_order (const void *a,const void *b){
	printf("in\n");
	path **x = (path**)
	a;
	path **y = (path**)b;
	
		


	printf("loc %d \n",(*y) -> path_count );
	printf("%d %d\n",(*x) -> path_count, (*y) ->path_count );

	int dif = (*x) -> path_count - (*y) -> path_count;
	if(dif == 0){
		dif = (*x) -> metric - (*y) -> metric;
	}
	return dif;
}


/**
 * Method to convert date to number
 * Implementation of Rata Die algorithm
 */
int date_to_number(date *d) { 
    int yy = d -> yy;
    int mm = d -> mm;
    int dd = d -> dd;

    if (mm < 3)
        yy--, mm += 12;
    return (365 * yy) + (yy / 4) - (yy / 100) + (yy / 400) + ((153 * mm - 457) / 5) + dd - 306;
}


date *create_date(int yy, int mm, int dd){
	date *new_date = (date *) malloc(sizeof(date));
	new_date -> yy = yy;
	new_date -> mm = mm;
	new_date -> dd = dd;

	return new_date;
}


int count_metric(path *p){
	date *d_max = create_date(0, 0, 0);
	date *d_min = create_date(9999,99,99);
	date *d_temp = NULL;

	int i;
	for(i = 1 ; i < p->path_count; i++){
		edge *tmp_edge = &edges[p -> iterate_edges[i]]; //get edge from path
		date *d_temp = tmp_edge -> date; //get date from edge

		//get min
		if(d_temp -> yy < d_min -> yy){
        	d_min = d_temp;
	    }else if (d_temp -> yy == d_min -> yy && d_temp -> mm < d_min -> mm){
	        d_min = d_temp;
	    }else if (d_temp -> yy == d_min -> yy && d_temp -> mm == d_min -> mm && d_temp -> dd < d_min -> dd){
	        d_min = d_temp;
	    }

	    //get max
	    if(d_temp -> yy > d_max -> yy){
        	d_max = d_temp;
	    }else if (d_temp -> yy == d_max -> yy && d_temp -> mm > d_max -> mm){
	        d_max = d_temp;
	    }else if (d_temp -> yy == d_max -> yy && d_temp -> mm == d_max -> mm && d_temp -> dd > d_max -> dd){
	        d_max = d_temp;
	    }
	}

	int dif = date_to_number(d_max) - date_to_number(d_min);

	//free(d_max);
	//free(d_min);

	return dif;
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
/*	if((path_order - 1) < path_array_max){
		printf("on: %d ",path_extension_number);
		path_extension_number++;
		printf("after: %d ",path_extension_number);
		path_array_max = path_extension_number * 1000; //increase max count of array(max array size)
		path *tmp1;
		tmp1 = realloc(paths, path_extension_number * 1000 * sizeof(path)); //save realloc


		if (!tmp1)
		{
		  printf("Can not realloc paths arrays \n"); // if realloc return null
		  return;
		}
		else
		{
			paths = tmp1;

		}
	}

*/


	path *temp =  (path *) malloc(sizeof(path));

	temp -> iterate_edges = (int *) malloc((p -> path_count ) * sizeof(int));
	temp -> iterate_nodes = (int *) malloc(p -> path_count * sizeof(int));
	int i = 0;

	for(i = 0 ; i < p -> path_count ; i++){
		temp -> iterate_edges[i] = p-> iterate_edges[i];
		temp -> iterate_nodes[i] = p-> iterate_nodes[i];
	}
	/*for(i = 0 ; i < p -> path_count - 1 ; i++){
		temp -> iterate_edges[i] = p-> iterate_edges[i];
		
	}*/
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
	int metric = count_metric(temp);
	temp -> metric = metric;
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


/**
 * Method to find all paths between source and target
 */
void dfs(int start, int end, int max_lenght, path *p, int edge_index){
	if((current_path_lenght - 1)< max_lenght){ // -1 -> in path is current_lenght - 1(node) = number of edges between -> path lenght
		node *node = &nodes[start]; //get current node
		add_node_to_path(p,node -> ID,edge_index); // add NODE to path
		current_path_lenght++;

		if(start != end){ //check if we find target
			node -> visited = 1;
			int i = 0;

			for(i = 0 ; i < node -> neighbours_count ; i++){
				edge *edge = &edges[node -> neighbours[i]];

				if(edge -> node_to == start){
					if(nodes[edge -> node_from].visited == 0){
						dfs(edge -> node_from, end, max_lenght, p, node -> neighbours[i]); //move deep to graph
					}
				}else{
					if(nodes[edge -> node_to].visited == 0){
						dfs(edge -> node_to, end, max_lenght, p, node -> neighbours[i]);
					}
				}
			}

			//stuff what i need to do for find all paths
			remove_last(p); //remove last in path
			node -> visited = 0; //set visited to 0
			current_path_lenght--; //decrease path lenght

		}else{
			save_path(p); //if i find target save path
			remove_last(p);
			node -> visited = 0;
			current_path_lenght--;
			return;
		}
	}else{
		return;
	}
}
 /**
  * Method to print node array
  */
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





/**
 * Method to print path
 */
void print_path(){
	//fflush(stdout);
	printf("Paths: %d\n",path_order);
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

			//first nodes
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

			printf("%d\n", tmp -> metric );
			//metric


			printf("\n");
		}
		fclose(f);
}

/**
 * free memory on heap
 */
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

/**
 * Load data and fill arrays
 */
int main()
{
	FILE *fp = fopen("inputt.csv","r");
	if (fp == NULL){
	  		return 0;
	}
	printf("Start\n");
	//get number of rows in file
	LINES_COUNT = countlines("inputt.csv");

	int i = 0;
	char line[40];

//	edge *edges[LINES_COUNT]; //alloc
	//malloc memory for edges array
	//LINES_COUNT = number of edges
	edges = (edge *) malloc(LINES_COUNT * sizeof(edge));

	//malloc memory for nodes array
	//LINES_COUNT * 2 - for the worst case(each node different)
	nodes = (node *) malloc(LINES_COUNT * 2 * sizeof(node));

	paths = (path *) malloc(1000000 * sizeof(path));
	while(fgets (line,40, fp) != NULL){

		char * pch;
		pch = strtok (line, ";");

		edge *e = (edge *) malloc(sizeof(edge));
		date *d = (date *) malloc(sizeof(date));
		

		int j = 0;
		int node_index_from = 0;
		int node_index_to = 0;

		//split row
			while( pch != NULL)
			{
				int val = atoi(pch);
				if( j == 0){

					if(val == previous_node_from_val){
						node_index_from = previous_node_from_index;
					}else{
						//create new node and return index in array or get index of existing node with same id
						node_index_from = create_node(nodes,val,node_order);
						previous_node_from_val = val;
						previous_node_from_index = node_index_from;
					}
					//set index to edge
					e -> node_from = node_index_from;
				}
				if( j == 1){

					if(val == previous_node_to_val){
						node_index_to = previous_node_to_index;
					}else{
						//create new node and return index in array or get index of existing node with same id
						node_index_to = create_node(nodes,val,node_order);
						previous_node_to_index = node_index_to;
						previous_node_to_val = val;
					}


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
							d -> yy = val2;
							//e -> yy = val2;
						}
						if( k == 1){
							d -> mm = val2;
							//e -> mm = val2;
						}
						if( k == 2){
							d -> dd = val2;
							//e -> dd = val2;
						}
						k++;
						pch2 = strtok(NULL,"-");
					}
				}
				j++;
				pch = strtok(NULL,";");
			}
			e -> date = d;
			edges[i] = *e; //add edge to array of edges
			add_edge_to_node(&nodes[node_index_from],i);//add edge to node's array of edges - source node
			add_edge_to_node(&nodes[node_index_to],i);//add edge to node's array of edges - destination node
			i++;

	}

//	print_node();
//	print_edge();
	printf("LINES: %d \n", LINES_COUNT);
	printf("Loaded\n");
	path *p = create_path();
	printf("start DFS\n");
	dfs(0, 4, 3, p, -1);
	printf("END DFS\n");
	printf("order: %d\n",path_order );
	qsort(paths,path_order,sizeof(path *),cmp_func_path_order);
	print_path();

	//free_all();

	return 0;
}

