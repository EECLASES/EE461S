//main.c

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#define MAXINPUTLENGTH 2000
#define TOKENLENGTH 30 //number of max input -1
#define MAXCOMMANDS 2	;



/*
typedef struct Process{
	int pid;
	bool ready;
	bool waiting;
	bool running;

}Process;
*/
struct ProcessGroup {
	int startIndex;
	int size;
	int type;
	struct ProcessGroup *next;

};
typedef struct ProcessGroup groups;
groups ProcessGroup[MAXPROCESSGROUPS];

	
	
	


typedef struct ParsedCmd{

	int pipes;
	int processGroups;
	bool bg;
	bool fg;
	


}ParsedCmd;


// prototypes for functions that might appear in jump table for parsing
void pipeInstruction();
void parseToken();
int checkPipes(char** parsedString, int argNum, char*** groups);
void implementPipes(char**, int index);
int checkLength(char* str);
int checkJobControl(char **parsedInput, int argNum);
/* This function has subtle advantages from a regular ptr to functions

	Jump Table researched by Nigel Jones https://embeddedgurus.com/stack-overflow/2009/12/jump-tables-via-function-pointer-arrays-in-cc/
	1. By declaring the array static within the function, no one else can access the jump table
		
	2. Forcing jump_index to be an a unsigned type would allow only one sided testing
	3. Setting jump_index to the smallest data type possible that will meet the requirements provides a little more protection (most jump tables are smaller than 256 entries)
	4. An explicit test is performed prior to making the call, thus ensuring that only valid function calls are made. (For performance critical applications, the if() statement could be replaced by an assert())*/
void jobControl(__uint8_t const jump_index)
{
    static void (*pf[])(void) = {parseToken};

    if (jump_index < sizeof(pf) / sizeof(*pf))
    {
        /* Call the function specified by jump_index */
        pf[jump_index]();
    }
}

void signals(__uint8_t const jump_index)
{
    static void (*pf[])(void) = {pipeInstruction};

    if (jump_index < sizeof(pf) / sizeof(*pf))
    {
        /* Call the function specified by jump_index */
        pf[jump_index]();
    }
}



/*

Tomorrow during the night, you need to implement each function

1.Need to split into groups then split groups
2. split them into 
2. Perform each function methodically.



*/
int main(){
	char str[MAXINPUTLENGTH + 3]; // beginning space + NewLine + null character
	char* saveString;
	int argNum;
	char myGroups[10][10][10];
	
	int counter;
	char* parsedString[MAXINPUTLENGTH + 3]; // same as str for safety 
/* WHILE LOOP BEGINS */
	while(1){
		printf("start of while loop\n");	
		printf("# ");

		gets(str); 
	
		if(checkLength(str) != 0) continue;
		
			

		str[strlen(str) - 1] = '\0';						//adding null pointer to cmd input

		
		
		char** strMalloc = (char**) malloc(sizeof (char**) );

		parsedString[0] = strtok(str, " ");
		argNum = 0; 									//getting the argument #
	
		while(parsedString[argNum] != NULL){
			argNum++;
			parsedString[argNum] = strtok(NULL," ");

					
			



			if(parsedString[argNum] != '\0'){
				strMalloc[argNum] = (char *)malloc(sizeof(char) * (strlen(parsedString[argNum])+1));			
				strcpy(strMalloc[argNum], parsedString[argNum]);
				}

			

		}
		parsedString[argNum] = '\0'; 					//adding null to char ** for multiple commands
		strMalloc[argNum] = (char *)malloc(sizeof(char) );
		strMalloc[argNum] = '\0';

		if (argNum == 0) continue; //checks for no input


//---------------------------------start of checks=--------------------
		
				
	//	ParsedCmd splitCmd(parsedString, argNum);
		
		printf("checking for any jobs\n");
		if(checkJobControl(parsedString, argNum) == 1) continue;		
		printf("passed job control\n");	
	
		printf("checking for pipes...\n");
		checkPipes(parsedString, argNum, myGroups);
		
		//Start of the basic exec process
		int pid = fork();
		if (pid == 0) {
			printf("hi from child\n");
			execvp(parsedString[0], parsedString);
			
			printf("child finished!\n");
		}
		else{

			printf("hi from parent\n");
			wait((int *)NULL);

			printf("parent has waited for child to complete\n");
		}
	}	


	
	return 0;


}


void FileRedirection(char** processGroup){
	

}
int checkJobControl(char** parsedString, int argNum){
		/*Start of job control*/
		for(int i = 0; i < argNum; i++){ 				
			if(strcmp("bg", parsedString[i]) == 0) {
			printf("found bg!\n"); 
			 return 1;
			}
			else if(strcmp("fg", parsedString[i]) == 0) {
			printf("found fg!\n");
			return 1; }
		

			else if(strcmp("jobs", parsedString[i]) == 0) {
			printf("found jobs!\n");
			return 1;
			}
			else if(strcmp("&", parsedString[i]) == 0) 
			{
			printf("found &!\n");
			return 1; 	
			}
		}

			return 0;

}
/* ---------------     checkLength   ---------------*/
/*
checks if the input is the correct size 
Returns 0 if valid

   -------------------------------------------------*/
int checkLength(char* str){

		if(fgets(str,sizeof str - 1, stdin) == NULL){
			printf(" non-valid string \n");
			return -1;
		} 
		else if (strchr(str, '\n') == NULL) {
			printf(" Input too long! \n");
			return -2;
		}
		else{
			printf("Valid String! \n%s", str);
		}
		return 0;
}
void pipeInstruction(){
 

    

	

}
void parseToken(){

}

int checkPipes(char** parsedString, int argNum, char*** myGroups, int counter){
		
		for(int i = 0; i < argNum; i++){ 	
			
							
			if(strcmp("|", parsedString[i]) == 0) {

				myGroups[counter][argNum] ='\0';
				counter++;
				printf("found a pipe!\n"); 
				
			 	
			}
			else{

				myGroups[counter][i] = parsedString[i];
			}

		}
	return 0;
		
}
int checkRedirection(char** parsedString, int argNum){
	
		for(int i = 0; i < argNum; i++){ 				
			if(strcmp(">", parsedString[i]) == 0) {
				printf("found a >!\n");
			 	return 1;
			}
			
			if(strcmp("<", parsedString[i]) == 0) {
				printf("found a <!\n"); 
			 	return 2;
			}

		}
		
}
