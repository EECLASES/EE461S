//yash.c
#include <stdio.h>
#include <signal.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "functions.h"


#define MAXINPUTLENGTH 2000
#define POSSIBLEMAXCOMMANDS 700    //Document does not define the max number of commands but assuming 2000 / 3 since it about 2 or 3 characters per command 
#define MAXCOMMANDLENGTH 30

void myHandler(int iSig) {
	printf("handling Ctrl-d %d\n", iSig);
	exit(1);	
}

/*


	1. Make char* [] for list of strings
	2. Seperate into two commands
	3. Work on first command 
	4. Check for pipe and execute the command if there is no pipe. 
	5. Execute pipe if needed.


*/ 
int main (){
	//signal(,SIG_DFL);


	char str[MAXINPUTLENGTH]; // beginning space + NewLine + null character
	int argNum;
	

	char* argv[POSSIBLEMAXCOMMANDS];


	//for piping
	int argc;
	int pipeIndex = -1;

	char** pipeOutput;
	

	//for one process group
	
	 int tokenNum = -1;


	//for jobs
	
	while(1){
		printf("# ");													// prints initial command
		if (fgets(str, MAXINPUTLENGTH + 3,stdin) ==NULL) exit(1);
		
		parse(str, argv);										//parses the string to string ptrs
		

		/* checking for pipe, make two strings if pipe present */

		argc = -1;	
		argc = checkLength(argv);							//counts argument plus null
		

		pipeIndex = -1;
		pipeIndex = checkPipe(argv);

		if(pipeIndex != -1)	{
			pipeOutput = grabPtr(pipeIndex, pipeOutput, argv);
			//make struct for background task?
			executePipe( argv, pipeOutput);
		}

		if(argc != -1)
		executeOneCommand(argv, getTokenIndex(argv), getTokenNumber(argv) );
		
		
			
	}

	return 0;



}
