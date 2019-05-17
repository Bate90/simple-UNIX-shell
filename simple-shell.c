//20100206
//p1 (both parts)
//run with make command


/**
 * Simple shell interface program.
 *
 * Operating System Concepts - Ninth Edition
 * Copyright John Wiley & Sons - 2013
 */

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <stdlib.h>


#define MAX_LINE		80 /* 80 chars per line, per command */


char hist[10][50];
int k_flag = 0;

void  parse(char *line, char **args, int* flag)
{

     while (*line != '\0') {       /* if not the end of line ....... */ 
          while (*line == ' ' || *line == '\t' || *line == '\n'|| *line == '&')
               *line++ = '\0';     /* replace white spaces with 0    */
          *args++ = line;          /* save the argument position     */
          while (*line != '\0' && *line != ' ' && 
                 *line != '\t' && *line != '\n'&& *line != '&') 
               line++;             /* skip the argument until ...    */
     }

     *args = '\0';                 /* mark the end of argument list  */

}

void show_history(){
	int i;


	if(strcmp(hist[0]," ")==0) printf("empty\n");
	else {
		for (i = 0; i <10; ++i)
		{
			if (!strcmp(hist[i]," ")==0) {printf(hist[i]);
			printf("\n");}
		}
	}
}

void keep_hist(){

		int i;
			for (i = 9; i > 0; --i)
		{
			strcpy(hist[i],hist[i-1]);
		}
}


int main(void)
{
	char *args[MAX_LINE/2 + 1];	/* command line (of 80) has max of 40 arguments */
   
    int should_run = 1;	
    pid_t  pid;
    int i, next, flag;
    int pos;
    pos=-1;

    for (i = 0; i < 10; ++i)
    {
    	strcpy(hist[i]," ");
    }

 
		
    while (should_run){   
        printf("osh>");
        fflush(stdout);
        flag=0;


    char* input = (char*) malloc(sizeof(char*));
	scanf ("%[^\n]%*c",input);
    int j;
    int s = strlen(input);

    if (strcmp(input,"")==0)
    {
    	printf("no command entered\n");
    	break;
    }

    

    
	if ((input[0]!='!') && strcmp(input,"history") ){
		keep_hist(); 
		strcpy (hist[0],input);	
	} 

    if (strcmp(input,"history")==0)
    {
    	show_history();
    }


	    else if (strcmp(input,"!!")==0){

	    	printf(hist[0]);

			keep_hist(); 
			strcpy (hist[0],hist[1]);

	    	char* temp[50];
	    	strcpy(temp, hist[0]);

		    parse(temp, args, &flag);
			pid = fork();
			if (pid<0){
				printf("ERROR in fork\n");
				// exit(1);
			}


		else if (pid==0)
		{
	        if ((execvp(args[0],args)==-1)) {
	        	printf("invalid command\n");
	        	// exit(1);
	        }
		}

		else {
			next = 1;
			if (flag==1){
				next=0;
				wait(NULL);
				}

		    }
	    }

    else if (((input[0]=='!')==1 && (input[1]=='!')== 0)){

		// printf("yes\n");
		int t;
		int i;

		for (i = 0; i < 10; ++i)
		{
			if(input[s-1]== i+'0') t = i;
		}


        if (strcmp(hist[t]," ")==0) {
        	printf("No command found\n"); 
        }
        
        else if (t>9) {
        	printf("history not recorded his far"); 
        }        

    	else {


    	char* temp[50];
    	strcpy(temp, hist[t]);
		keep_hist(); 
		strcpy (hist[0],temp);


	    parse(temp, args, &flag);
		pid = fork();
		if (pid<0){
			printf("ERROR in fork\n");
			// exit(1);
		}


		else if (pid==0)
		{
	        if ((execvp(args[0],args)==-1)) {
	        	printf("invalid command\n");
	        	// exit(1);
	        }
		}
		else {
			next = 1;
			if (flag==1){
				next=0;
				wait(NULL);
			}

		    }
		}
    }

    else {

    if(input[s-1]=='&'){
       flag=1;	
       input[s-1]='\0';
       if (input[s-2]==' ') input[s-2]='\0';
    } 


	

	parse(input, args, &flag);
	pid = fork();
	if (pid<0){
		printf("ERROR in fork\n");
		// exit(1);
	}


	else if (pid==0)
	{
        if ((execvp(args[0],args)==-1)) {
        	printf("invalid command\n");
        	// exit(1);
        }
	}
	else {
		next = 1;
		if (flag==1){
			next=0;
			wait(NULL);
		}

	}
	
	}

    }
    
	return 0;
}
