/*
	* =====================================================================================
	*
	*       Filename:  logger.h
	*
	*    Description:  logger for c in daily file basis 
	*
	*        Version:  1.0
	*        Created:  Thursday 02 July 2015 10:55:40  IST
	*       Revision:  none
	*       Compiler:  gcc
	*         Author:  N. ARUN SHANKAR , arunshankar.n@outlook.com
	*
	* =====================================================================================
	*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <errno.h>
#include <time.h>


#define INFO 1 
#define ERROR 2
#define FATAL 3

//Global variable for the log file pointer
FILE *log_fp = NULL ; 
//Store the prefix log name as user config
char *org_log_name ;
//Maintain current log name
char *log_name;
//Store the current date details for logfile name
int day,month,year =0;

void create_logger( char *dirpath, char *log_prefix_name) ;
void gen_log_name();
void open_log_file();
void logmsg(int level,char *fmt, ... );
void get_current_date( int * day, int * month, int * year ) ;
void check_new_file();


/* 
	* ===  FUNCTION  ======================================================================
	*         Name:  create_logger
	*  Description:  This is a main function to start with logger. This will create the file
 *                pointer for log file.
	*   Parameters:  Directory(where log file should create),File name
	*       Return:  Nothing
	* =====================================================================================
	*/
void create_logger(char *dirpath ,char *name ) 
{
        int size = strlen(dirpath)+strlen(name)+1+1 ; //Calculating size for malloc ; here +1 for "/" another +1 for \0

        org_log_name = (char *) malloc(sizeof(char)*size);
        memset(org_log_name,0,size);

								strcat(org_log_name,dirpath);
								strcat(org_log_name,"/");
        strcat(org_log_name,name);
								get_current_date(&day,&month,&year);
								gen_log_name();
								open_log_file();
}

/* 
	* ===  FUNCTION  ======================================================================
	*         Name:  open_log_file
	*  Description:  Open the file and set global file pointer and free the log_name memory
	*   Parameters:  Nothing
	*       Return:  Nothing
	* =====================================================================================
	*/
void open_log_file()
{
								log_fp = fopen(log_name, "a") ; 
								if (log_fp == NULL )
								{
																printf("Unable to open the log file '%s' - %s\n", log_name , strerror(errno));
								}
        free(log_name);//Once the file opened no use of 'log_name' so free the memory 
}

/* 
	* ===  FUNCTION  ======================================================================
	*         Name:  logmsg
	*  Description:  Used to log the message to log file.
	*   Parameters:  Level of log, Format string , n of arguments 
	*       Return:  Nothing
	* =====================================================================================
	*/
void logmsg(int level, char *fmt , ...)
{
								check_new_file();
								if ( log_fp != NULL ) 
        {
								va_list ap;
								char buf[64];
								char level_name[10];

								if (level == INFO )
																strcpy(level_name,"INFO");
								else if (level == ERROR)
																strcpy(level_name,"ERROR");
								else if (level == FATAL)
																strcpy(level_name,"FATAL");
								else
																strcpy(level_name,"INFO");

								// Preparing time stamp
								time_t meow = time(NULL);
								strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", localtime(&meow));

								va_start(ap, fmt);
								fprintf(log_fp,"%s : [%5d] : %5s : ",buf,(int)getpid(),level_name);
								vfprintf(log_fp, fmt, ap);
        fflush(log_fp);
								va_end(ap);
        }
								if (level == FATAL)
																exit(1);
}

/* 
	* ===  FUNCTION  ======================================================================
	*         Name:  get_current_date
	*  Description:  Used to get the current date details, Store value to the pointer variable
 *                which passed to the function 
	*   Parameters:  int pointer for day, int pointer for month, int pointer for year
	*       Return:  Nothing
	* =====================================================================================
	*/
void get_current_date( int * day, int * month, int * year ) {
								struct tm *current;
								time_t timenow;
								time(&timenow);
								current = localtime(&timenow);
								*month = current->tm_mon+1;
								*day = current->tm_mday;
								*year = current->tm_year+1900;
}

/* 
	* ===  FUNCTION  ======================================================================
	*         Name:  gen_log_name
	*  Description:  Generate the formated log file name with current date. 
	*   Parameters:  Nothing 
	*       Return:  Nothing
	* =====================================================================================
	*/
void gen_log_name()
{
        int size = strlen(org_log_name)+15+1 ; //Here extra 15 for '_01_01_2015.log' +1 for \0
        log_name = (char *) malloc(sizeof(char)*size);
        memset(log_name,0,size);
								sprintf(log_name,"%s_%02d_%02d_%d.log",org_log_name,day,month,year);
}

/* 
	* ===  FUNCTION  ======================================================================
	*         Name:  check_new_file 
	*  Description:  this ll be called by logmsg for every call of log to check the date and 
 *                generate new file. if the day over.
	*   Parameters:  Nothing 
	*       Return:  Nothing
	* =====================================================================================
	*/
void check_new_file()
{
								int t_day, t_month, t_year ; 
								get_current_date(&t_day, &t_month, &t_year);
								if(day != t_day || month != t_month || year != t_year)
								{
																day = t_day ; month = t_month ; year = t_year ;
																if ( log_fp != NULL ) 
																								fclose(log_fp);
																gen_log_name();
																open_log_file();
								}
}
