/*Jason Egan
  matric-	2191867e
  assignment-	APH Exercise 1
  This is my own work as defined in the Academics Ethics agreement I have signed
*/




#include "date.h"
#include "string.h"
#include "stdlib.h"
#include "stdio.h"


/*structure for a date defined as in header file*/
struct date{
	int day;
	int month;
	int year;
};


/*function to create a date given the datestring*/
Date *date_create(char *datestr){

	struct date *newD;
	/*gets the day,month,year from the string using sscanf and places them in respective 
	variables*/
	int day, month, year;
	sscanf(datestr, "%d/%d/%d", &day, &month, &year);

	/*iif the malloc for the newD is successful*/
	if((newD = (struct date *)malloc(sizeof(struct date)))!=NULL){

		/*assign each attribute for the newD*/
		newD->day = day;
		newD->month = month;
		newD->year = year;
		return newD;
	}
	/*else return NULL if the malloc is unsuccessful*/
	return NULL; //syntax error
}

/*function to return a duplicate pointer to a date*/
Date *date_duplicate(Date *d){
	
	/*if the malloc for the date duplicate is successful*/
	struct date *dateDup;
	if((dateDup = (struct date *)malloc(sizeof(struct date)))!=NULL){

		/*assign each attribute for the dateDup*/
		dateDup->day = d->day;
		dateDup->month = d->month;
		dateDup->year = d->year;
		return dateDup;

	}
	/*if the malloc is unsuccessful then return NULL*/
	return NULL; //Mem alloc error

}


/*function to compare 2 pointers to dates*/
int date_compare(Date *date1, Date *date2){

	/*if the year of date 1 != date 2 year*/
	if(date1->year != date2->year){

		/*if date 1 year is smaller than date 2 year then return -1 and vice versa (1)*/
		if(date1->year < date2->year){
			return -1;		
		}else{
			return 1;
		}
 
	/*if the month of date 1 != date 2 month*/
	}else if(date1->month != date2->month){

			/*if date 1 month is smaller than date 2 month then return -1 and vice
			versa (1)*/
			if(date1->month < date2->month){
				return -1;
			}else{
				return 1;
			}

		
	/*similar to above occurs for day*/
	}else if(date1->day != date2->day){
		if(date1->day < date2->day){
			return -1;

		}else{
			return 1;
	
		}
	}
	return 0;

}


/*gets rid of the date object pointer to avoid memory leaks*/
void date_destroy(Date *d){
	free(d);


}

