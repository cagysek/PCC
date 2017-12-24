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
        	d_min = d_temp;
	    }else if (d_temp -> yy == d_min -> yy && d_temp -> mm < d_min -> mm){ //check month
	        d_min = d_temp;
	    }else if (d_temp -> yy == d_min -> yy && d_temp -> mm == d_min -> mm && d_temp -> dd < d_min -> dd){ //check day
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