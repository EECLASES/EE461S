// main.c












/* Usage of Jump table, specified as efficient by paper done by Expert Nigel Jones.
	paper found at chrome-extension://nacjakoppgmdcpemlfnfegmlhipddanj/https://rmbconsulting.us/Publications/jump-Tables.pdf 

*/






#include  <stdio.h>
#include  <string.h>
#include  <sys/types.h>

#define   MAX_COUNT  2000 //character limit...
#define   BUF_SIZE   100

void  main(void)
{
     pid_t  pid;
     int    i;
     char   buf[BUF_SIZE];

     fork();
     pid = getpid();
     for (i = 1; i <= MAX_COUNT; i++) {
          sprintf(buf, "This line is from pid %d, value = %d\n", pid, i);
          write(1, buf, strlen(buf));
     }
}

