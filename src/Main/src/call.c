#include <unistd.h>
#include<sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int caller_de_merde (const char* input) {
	int ret;
	char* ipt = malloc (256);
	strcpy(ipt, input);
	char* const args[] = {"./min-ml",ipt, NULL};
	pid_t pid =fork();
	if (pid == -1){
    		fprintf(stderr, "Erreur appel fork typecheck \n");
    		return 1;	
  	} else {
    		if (pid == 0) {
      		execv(args[0], args);
    	} else {
      		waitpid(pid, &ret, 0);
    	}
  }	
  return WEXITSTATUS(ret);
}
