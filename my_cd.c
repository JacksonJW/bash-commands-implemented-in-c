#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char** argv) {
	char buffer[1024];
	char pathNotFoundStr[1024];
	char newWd[1024];
	if (argc == 1){
    	// Take back to home directory or ~
    	chdir("/Users/jacksonwatkins/");
    	strcpy(newWd, getcwd(buffer, sizeof(buffer)));
    	int newWdlength = strlen(newWd);
    	newWd[newWdlength] = '\n';
    	newWd[newWdlength+1] = '\0';
    	write(1, newWd, strlen(newWd));

	} else {
    	strcpy(pathNotFoundStr, "bash: cd: ");
    	strcat(pathNotFoundStr, argv[1]);
    	strcat(pathNotFoundStr, " : No such file or directory\n\0");

    	char* inputWd = argv[1];
    	if (chdir(inputWd) == -1){
        	write(1, pathNotFoundStr, strlen(pathNotFoundStr));
    	} else {
        	strcpy(newWd, getcwd(buffer, sizeof(buffer)));
        	int newWdlength = strlen(newWd);
        	newWd[newWdlength] = '\n';
        	newWd[newWdlength+1] = '\0';
        	write(1, newWd, strlen(newWd));
    	}
	}
	return 0;
}
