#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>

int main(int argc, char** argv) {
	int n;
	int path_max = 1024;
	char actualPath[path_max];
	char *pathPtr;
	char buffer[1024];
	int fd;
	FILE *filePointer;
	if (argc == 1){
    	char needPath[42] = "Please specify the filename as argument\n";
    	write(1, needPath, strlen(needPath));
	} else {
    	pathPtr = realpath(argv[argc-1], actualPath);
    	filePointer = fopen(pathPtr, "r");
    	fd = fileno(filePointer);
    	while((n=read(fd, buffer, sizeof(fd)) != 0)){
        	write(1, buffer, strlen(buffer));
    	}
	}
}
