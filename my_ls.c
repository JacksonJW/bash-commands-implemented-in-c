// Supports '-i' flag to display each file's inodes
// in the directory.

#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>

int main(int argc, char** argv) {
	char list[1024];
	char inodeNum[12];
	DIR* dir;
	struct dirent *dirEntry;
	int path_max = 1024;
	char actualPath[path_max];
	char *pathPtr;
	pathPtr = realpath(argv[argc-1], actualPath);

	if (argc == 1){
    	dir = opendir(".");
	} else if (argc == 2 && strcmp(argv[1], "-i") == 0){
    	dir = opendir(".");
	} else {
    	dir = opendir(pathPtr);
	}
	strcpy(list, "");

	while((dirEntry = readdir(dir)) != NULL){
    	if (strcmp(dirEntry->d_name, ".") != 0 && strcmp(dirEntry->d_name, "..") != 0){
        	if (strcmp(argv[1], "-i") == 0){
            	sprintf(inodeNum, "%lu", dirEntry->d_ino);
            	strcat(list, inodeNum);
            	strcat(list, " ");
        	}
        	strcat(list, dirEntry->d_name);
        	strcat(list, "\n");
    	}
	}
	strcat(list, "\0");
	write(1, list, strlen(list));
	closedir(dir);
}
