// functions.c function edit 


#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include<sys/stat.h>
#include <fcntl.h>
#define POSSIBLEMAXCOMMANDS 700    //Document does not define the max number of commands but assuming 2000 / 3 since it about 2 or 3 characters per command 
#define MAXCOMMANDLENGTH 30






/* ---------------     checkLength   ---------------*/
/*
checks if the input is the correct size 
Returns 0 if valid

   -------------------------------------------------*/
int checkLength(char** argv){
		int index = 0; 
		while (argv[index] != '\0') index++;
		return index ;
}

/*-----------------getTokenIndex-------------------------------*/
/*
	inputs: char** ptr with all strings.
	outputs:	 index if found any tokens
				-1 if it doesn't exist
	Note: char** must be have a null pointer to indicate end of string
		
*/
int getTokenIndex(char **argv){
	int index = 0;
while(argv[index] != '\0') {
	if ( 	strcmp(">" , argv[index] ) == 0 || (	strcmp("<" , argv[index] ) == 0) ||
			strcmp("2>" , argv[index] ) == 0 )
		return index;

	else index++;
	}
	return -1;	
			
}
/*	-----------------checkPipe------------
	checks if string has pipe and returns the index
	inputs: char** ptr with all strings.
	outputs:	int = index of pipe
					-1 if it doesn't exist
	Note: char** must be have a null pointer to indicate end of string

*/
int checkPipe(char **argv){
	int index = 0;
	while(argv[index] != '\0') {
		if ( 	strcmp("|" , argv[index] ) == 0 )	return index;
		else index++;

		if( argv[index] == '\0') return -1; //check a pipe if there happens to be one after the null
	}
	return -1;	

}
/*	-----------------executePipe------------
	checks if string has pipe and returns the index
	inputs: char** ptr first command, char **ptr second command
	outputs:	int = index of pipe
					-1 if it doesn't exist
	Note: char** must be have a null pointer to indicate end of string

*/
void executePipe(char** argv, char** secondCmd){

	//does a check for tokens on first token
	char*  argvFile;
	int  ofd, ifd0 = -1;
	int argvTokenIndex = getTokenNumber(argv);
	if (argvTokenIndex != -1 ) { 
		argv[argvTokenIndex ] = '\0';
		argvFile = argv[argvTokenIndex+1];
	}	
	
	int secondCmdToken = getTokenNumber(secondCmd);
	char* secondCmdFile;
	if (secondCmdToken != -1 ) { 
		argv[secondCmdToken ] = '\0';
		secondCmdFile = argv[argvTokenIndex+1];
	}	
	
    int pipefd[2], status, done=0;
    pid_t cpid;

    pipe(pipefd);

    cpid = fork(); 
    if (cpid == 0) {    /* left child (for date) */
	
		close(pipefd[0]); /* Close unused read end */
		if(argvTokenIndex == -1) { //redirection
			if(argvTokenIndex == 1){
				ofd = creat(argvFile, 0644);
				dup2(ofd,1);   // same as: close(1); dup(ofd)
			}
			else if(argvTokenIndex == 2){
				ifd0 = open(argvFile, O_RDONLY);
			}
			else if(argvTokenIndex == 3){
				ifd0 = open(argvFile, O_RDONLY);
				if(ifd0 == -1){
					printf("No file %s\n", argvFile);
				}
				else	dup2(ifd0,0);   // same as: close(1); dup(ofd)
				

			}
	
		dup2(pipefd[1], 1); /* Make output go to pipe */
		execvp(argv[0], argv);
    	}
	}


    cpid = fork(); 
    if (cpid == 0) {  /* right child (for wc */
	close(pipefd[1]);          /* Close unused write end */
	dup2(pipefd[0], 0); /* Get input from pipe */
	execvp(secondCmd[0], secondCmd);
    }

    close(pipefd[0]); /* close pipes so EOF can work */
    close(pipefd[1]); /* This is a subtle but important step. The second child
                         will not receive a EOF to trigger it to terminate while
                         at least one other process (the parent)  has the write 

			 end open */
    
    /* Parent reaps children exits */
    waitpid(-1,&status, 0);
    waitpid(-1,&status, 0); 
}
/* 		getTokenNumber

		inputs: char** ptr
		outputs:	 tokenNumber 1,2,3
					-1 if not found
*/
int getTokenNumber(char **argv){
	int index = 0;
	while( argv[index] != '\0' ){
		if(strcmp(argv[index],">") == 0 ) {
			return  1;
			}
		else if(strcmp(argv[index], "<") == 0 ) {
			return  2;
			}
		else if(strcmp(argv[index], "2>") == 0 ) {
			return  3;
			}
		index++;

	} 
	return -1;	



}
/*	-----------------parse------------
	checks if string has pipe and returns the index
	inputs: char* line from cmd prompt, argv double pointer 
	outputs:	void

*/
void  parse(char *line, char **argv){
	int argCount;
     while (*line != '\0') {       /* if not the end of line ....... */
          while (*line == ' ' || *line == '\t' || *line == '\n') {
               *line++ = '\0';     /* replace white spaces with 0    */
				
			}
          *argv++ = line;          /* save the argument position     */
          while (*line != '\0' && *line != ' ' &&
                 *line != '\t' && *line != '\n') 
               line++;             /* skip the argument until ...    */
     }
	*argv--;
     *argv = '\0';                 /* mark the end of argument list  */
	


}
char** grabPtr(int pipeIndex, char **secondCmd, char **firstCmd){
				
			while ( *firstCmd != '\0') {

			 //place pointer starting at one word after pipe	
				if(strcmp("|", *firstCmd) == 0)	{
					*firstCmd = '\0'; 		//place Null character instead of pipe
					firstCmd++;
					return firstCmd++;
				}
				else firstCmd++;
			}
					//place Null character instead of pipe
			
	
	return NULL;	
	

}
 
void executeOneCommand( char** argv , int tokenIndex, int tokenNum ){
		
		

				
		int cpid = -1;	
		//for write
		int ofd = -1;
		char* output = argv[tokenIndex +1];
		//for Read
		int ifd0 = -1;
		int ifd1 = -1;
		char* input = argv[tokenIndex + 1];
		//for err
		int efd = 0;
		char* eInput = argv[tokenIndex + 1];
	
		cpid = fork();	
		if(tokenNum == -1){ // no Token
			//		execute( 	argv);
			
  

     
   		 	if (cpid == 0) {  /* Child */
				execvp(argv[0], argv);
				exit(1);
    		}
		}
		else if (tokenNum == 1){ // ">"
			argv[tokenIndex] = '\0';
				
   		 	if (cpid == 0) {  /* Child */
			ofd = creat(output, 0644);
			dup2(ofd,1);   // same as: close(1); dup(ofd)
				execvp(argv[0], argv);
				exit(1);
    		}
		}
		else if (tokenNum == 2){// "<"
			if (cpid == 0){
				ifd0 = open(input, O_RDONLY);
				argv[tokenIndex] = '\0';
				if(ifd0 == -1){
					printf("No file %s\n", input);
				}
				
				else{
				
					dup2(ifd0,0);   // same as: close(1); dup(ofd)
					execvp(argv[0], argv);
					exit(1);
				}
			}
		}
		else if (tokenNum == 3){// "2>"
			argv[tokenIndex] = '\0';
			if (cpid == 0){
				efd = open(eInput, O_RDWR);
				dup2(efd, 2);
				execvp(argv[0], argv);

				exit(1);
			}	

		}

    			wait((int *)NULL);
		return;
}


