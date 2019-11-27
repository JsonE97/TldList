#include "date.h"
#include "string.h"
#include "stdlib.h"
#include "stdio.h"


/*Structure for a date:
 day   - int
 month - int
 year  - int
 */
struct date{
    int day;
    int month;
    int year;
};


/*Date *date_create
 Description:
    creates a new date based off the datestr arg
 Args:
   char* dateStr - date string expected in format dd/mm/yyyy
 Return:
   Date* - pointer to a date structure
 */
Date *date_create(char *datestr){
    
    struct date *newD;
    
    /*gets the day,month,year from the string using sscanf and places them in respective
     variables
     */
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

/*Date *date_duplicate
 Description:
    creates a new duplicate of a given date - this is a seperate pointer
 Args:
    Date* d - date to be duplicated
 Return:
    New pointer to a new Date struct
 */
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


/*int date_compare
 Description:
    Compares 2 dates, and returns an int whether date1 is earlier than date2
 Args:
    Date* date1, date2 - 2 different date structs
 Return:
    -1 - date1 before date2
    1  - date2 before date1
    0  - dates are the same (not in terms of memory)
 */
int date_compare(Date *date1, Date *date2){
    
    if(date1->year != date2->year) {
        return (date1->year < date2->year) ? -1 : 1;
    }
    else if (date1->month != date2->month) {
        return (date1->month < date2->month) ? -1 : 1;
    }
    else if (date1->day != date2->day){
        return (date1->day < date2->day) ? -1: 1;
    }
    return 0;
}


/*void date_destroy
 Description:
    Gets rid of/frees any memory associated to the date structure
 Args:
    Date* d - the date structure
 */
void date_destroy(Date *d){
    free(d);
}

