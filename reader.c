#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structure.h"
#include "global.h"


int LINES_COUNT; //count of lines

//Variables to store previous values, if they repeat on next line I dont need search it again 
int previous_node_from_index = -1; //stored node from index in array

int previous_node_from_val = -1; //stored node from id 

int previous_node_to_index = -1; //stored node to index in array

int previous_node_to_val = -1; //stored node to id 

/**
 * Get number of lines in input file
 * @param filnename filename
 * @return number of lines
 */
int countlines(char *filename){

  FILE *fp = fopen(filename,"r");
  int ch=0;
  int lines=0;

  if (fp == NULL){
  		return 0;
  }
  lines++;
  while ((ch = fgetc(fp)) != EOF)
    {
      if (ch == '\n'){
    	lines++;
   	  }
    }

  fclose(fp);

  return lines;
}

/**
 *	Read topology and fill arrays
 * 	read lines from file. Split by ";", create nodes and edges -> save it to arrays
 *  create nodes -> check if exist, yes -> return index in array, no -> create new and return index
 *	create edges -> working with array indexes from nodes array. NOT with their ID's
 * 	date(value of edge) is stored in struct date, where yy is year, mm is month, dd is day
 */
void load_topology(char *filename){
	FILE *fp = fopen(filename,"r");
	

	int i = 0;
	char line[40];

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
					node_index_from = create_node(val,node_order);
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
					node_index_to = create_node(val,node_order);
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
					}
					if( k == 1){
						d -> mm = val2;
					}
					if( k == 2){
						d -> dd = val2;
					}
					k++;
					pch2 = strtok(NULL,"-");
				}
			}
			j++;
			pch = strtok(NULL,";");
		}
		e -> date = d; //save date to path
		edges[i] = *e; //add edge to array of edges
		add_edge_to_node(&nodes[node_index_from],i);//add edge to node's array of edges - source node
		add_edge_to_node(&nodes[node_index_to],i);//add edge to node's array of edges - destination node
		i++;
	}
}