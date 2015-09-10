#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


void PrintEnviron(char**);
char* Prompt(char*, char*, char*, char*);
char* Lstrip(char*);
char* GetCommand(char*);

int main(int argc, char* argv[], char* envp[])
{
	char str[10] = "exit";
	int numArgs = 1;	
	int redirectFlag = 0;
	int status = 1;
	char* tmp;

	char* ans = (char*)malloc(sizeof(char) * 255);
	char* cmd = (char*)malloc(sizeof(char) * 255);

	char* usr = (char*)malloc(sizeof(char) * strlen(getenv("USER")));	//-------------------------------------------------------//
	usr = getenv("USER");												

	char machine[1024];													// Assuming machine has less than 1023 characters in name
	machine[1023] = '\0';												// Setting up the prompt
	gethostname(machine, 1023);

	char* pwd = (char*)malloc(sizeof(char) * strlen(getenv("PWD")));
	pwd = getenv("PWD");												//-------------------------------------------------------//

	PrintEnviron(envp);

	while (status == 1)
	{
		ans = Prompt(ans, usr, machine, pwd);
		if((tmp = strchr(ans, '\n')) != NULL)
			*tmp = '\0';
		
		ans = Lstrip(ans);
		cmd = GetCommand(ans);

		printf("ans: %s\n", ans);
		printf("Command: %s\n", cmd);

		if (strcmp(ans, "exit") == 0)
		{
			status = 0;
			printf("WORKS\n");
		}

	}
	
	return 0;
}

char* Prompt(char* ans, char* usr, char* machine, char* pwd){
	char* retString = (char*)malloc(sizeof(char) * 255);
	size_t i = 255;
	printf("%s@%s:%s =>", usr, machine, pwd);
	getline(&retString, &i, stdin);
	return retString;
}

void PrintEnviron(char** env){
	char** ep;
	for (ep = env; *ep != NULL; ep++)
	{
		printf("%s", *ep);
		printf("\n");
	}
}

char* Lstrip(char* line){
	char* retString = (char*)malloc(sizeof(char) * 255);
	int i = 0;
	int j = 0;
	char cursor;
	cursor = line[0];

	if (isspace(cursor))							// If the command has space infront,
	{
		while(isspace(cursor) || cursor == '\t')
		{											// Go through the line until an alnum
			cursor = line[i++];						// char is hit.
		}
		i--;										// Come back one.
		while(cursor != '\0')						// Scan until the end of the array.
		{
			cursor = line[i++];						// Start adding to the retString from
			retString[j++] = cursor;				// Where the spaces stopped.
		}
		retString[j] = '\0';						// Terminate with null char.
	}
	else
		strcpy(retString, line);					// If it didn't, just return the line.

	return retString;
}

char* GetCommand(char* line){
	char* retString = (char*)malloc(sizeof(char) * 255);
	int i = 0;
	char cursor = line[0];

	while(!isspace(cursor) && cursor != '\n' && cursor != EOF && cursor != '\0')
	{
		retString[i] = cursor;
		cursor = line[++i];
	}
	retString[i] = '\0';

	return retString;
}