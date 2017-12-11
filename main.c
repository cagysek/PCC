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
  return lines;
}


void print_edge(edge *edge){
	printf("from: %d to: %d metirc: %d-%d-%d \n",edge -> node_from, edge -> node_to, edge -> yy, edge -> mm, edge -> dd);
}





int main()
{
	FILE *fp = fopen("input.csv","r");
	if (fp == NULL){
	  		return 0;
	}
	//get number of rows in file
	int LINES_COUNT = countlines("input.csv");
	//printf("LINES: %d\n",LINES_COUNT);
	//rows * 2 to get maximum number of vertex
	//int LINES_COUNT = LINES_COUNT * 2;
	char line[50];
	edge *data[LINES_COUNT];
	int i = 0;
	while(fgets (line,LINES_COUNT, fp) != NULL){
//	printf("%s\n", line);

	char * pch;
	pch = strtok (line, ";");

	edge *e = malloc(sizeof(edge));

	
	int j = 0;
	
	while( pch != NULL)
	{
	//	printf("%s\n", pch);
	//	pch = strtok(NULL,",");
		int val = atoi(pch);
		if( j == 0){
			e -> node_from = val;
		}
		if( j == 1){
			e -> node_to = val;

		}
		if( j == 2){

			char * pch2;
			pch2 = strtok (pch, "-");
			int k = 0;
	
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
//	print_iris(iri);
	
	data[i] = e;
	print_edge(data[i]);
	//printf("%d\n",i );
	i++;
}

    
    return 0;
}

