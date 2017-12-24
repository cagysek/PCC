#include <stdio.h>
#include <stdlib.h>
#include "structure.h"



/**
 * Method to create date
 * @params yy year
 * @params mm month
 * @params dd day
 * @return pointer to date 
 */
date *create_date(int yy, int mm, int dd){
	date *new_date = (date *) malloc(sizeof(date));
	new_date -> yy = yy;
	new_date -> mm = mm;
	new_date -> dd = dd;

	return new_date;
}

/**
 * Method to convert date to number
 * Implementation of Rata Die algorithm
 * @params date pointer to date
 * @return date expressed by number
 */
int date_to_number(date *d) { 
    int yy = d -> yy;
    int mm = d -> mm;
    int dd = d -> dd;

    if (mm < 3)
        yy--, mm += 12;
    return (365 * yy) + (yy / 4) - (yy / 100) + (yy / 400) + ((153 * mm - 457) / 5) + dd - 306;
}