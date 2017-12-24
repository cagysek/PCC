#include <stdio.h>
#include <stdlib.h>
#include "structure.h"
#include "global.h"


/**
 * Method to print edge array
 */
void print_edge(){
	int o = 0;
	for( o = 0;o < LINES_COUNT;o++){
			printf("ID: %d from: %d to: %d \n",o,edges[o].node_from,edges[o].node_to);
	}

}