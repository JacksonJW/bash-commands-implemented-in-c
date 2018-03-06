// Works with -w parameter for the wordCount
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>

int main(int argc, char** argv) {
	int characterCount = 0;
	int wordCount = 0;
	int lineCount = 0;
	char currentChar;
	char resultText [1024];
	char tempStr [1024];
	int path_max = 1024;
	char actualPath[path_max];
	char *pathPtr;
	FILE *filePointer;
	if (argc == 1 || (argc == 2 && strcmp(argv[1], "-w") == 0)){
    	char needPath[42] = "Please specify the filename as argument\n";
    	write(1, needPath, strlen(needPath));
	} else {
    	pathPtr = realpath(argv[argc-1], actualPath);
    	filePointer = fopen(pathPtr, "r");
    	while((currentChar=fgetc(filePointer))!=EOF){
        	characterCount++;
        	if (currentChar == ' '){
            	wordCount++;
        	}
        	if (currentChar == '\n'){
            	lineCount++;
            	wordCount++;
        	}
    	}
    	if (characterCount > 0 && lineCount == 0){
        	lineCount++;
    	}
    	if (strcmp(argv[1], "-w") == 0){
        	strcpy(resultText, "	");
        	sprintf(tempStr, "%d", wordCount);
        	strcat(resultText, tempStr);
        	strcat(resultText, " ");
        	sprintf(tempStr, "%s", argv[argc-1]);
        	strcat(resultText, tempStr);
    	} else {
        	strcpy(resultText, "	");
        	sprintf(tempStr, "%d", lineCount);
        	strcat(resultText, tempStr);
        	strcat(resultText, "	");
        	sprintf(tempStr, "%d", wordCount);
        	strcat(resultText, tempStr);
        	strcat(resultText, "	");
        	sprintf(tempStr, "%d", characterCount);
        	strcat(resultText, tempStr);
        	strcat(resultText, " ");
        	sprintf(tempStr, "%s", argv[argc-1]);
        	strcat(resultText, tempStr);
    	}

    	strcat(resultText, "\n");
    	write(1, resultText, strlen(resultText));
	}
}
