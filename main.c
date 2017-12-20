#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"
 


int countlines(char *filename)
{
  // count the number of lines in the file called filename                                    
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
  printf("number of lines: %d\n",lines);
  return lines;
}




void print_edge(edge *edge){


}




/*
node *create_node(node **root,int new_ID,int edge_index){
//	printf("Create %d\n",new_ID);
	node *new_node = (node *) malloc(sizeof(node));
	

	new_node -> ID = new_ID;

	node *actual_node = *root;
	
	if (!*root){		
		*root = new_node;
		add_edge_to_node(root,edge_index); 
		return *root;	
	}

	printf("after root\n");
    while (actual_node -> node_next != NULL)
    {
    	if(actual_node -> ID != new_node -> ID){ //check if node id is uniqe, else free malloc memory and return
        	actual_node = actual_node -> node_next;
        }else{
        	add_edge_to_node(&actual_node,edge_index);
        	free(new_node);//free new_node memory
        	return actual_node;
        }
    }
    printf("end while\n");
    add_edge_to_node(&actual_node,edge_index);
    actual_node->node_next = new_node;
    //print_node(actual_node);
    return new_node;

}
*/
void add_edge_to_node(node **head, int new_index){
	
    return;
	



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
	char line[40];
	
	edge *data[LINES_COUNT];

	int nodes[LINES_COUNT*2*2];

	
	int i = 0;
	while(fgets (line,40, fp) != NULL){
		
		char * pch;
		pch = strtok (line, ";");

		
		edge *e = (edge *) malloc(sizeof(edge));
		int k = 0;
		int j = 0;
		//split row
			while( pch != NULL)
			{	
				int val = atoi(pch);
				if( j == 0){
					nodes[k] = val;
					
					e -> node_from = k;
					k++;
				}
				if( j == 1){
					nodes[k] = val;		
					e -> node_to = k;
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
			data[i] = e;
			i++;
			k++;
	}


	for(int p = 0;p< LINES_COUNT*2*2;p++){
		printf("%d\n",nodes[p] );
	}



	printf("nodes: %lu\n",sizeof(nodes));

	return 0;
}

