// functions.h


char** grabPtr(int pipeIndex, char **secondCmd, char **firstCmd);
int checkPipe(char **argv);
int getTokenIndex(char **argv);
int getTokenNumber(char** pointer); 
int checkLength(char* str);
char *myStr(char* destination, char *source);


void executePipe(char **firstCmd, char ** secondCmd);

void execute( char** arg);
void executeStdOut( char** arg);
