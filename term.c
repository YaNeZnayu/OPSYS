#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


void PrintEnviron(char**);
char* Prompt(char*, char*, char*, char*);

int main(int argc, char* argv[], char* envp[])
{
	char str[10] = "exit";
	int numArgs = 1;	
	int redirectFlag = 0;
	int status = 1;
	char* tmp;

	char* ans = (char*)malloc(sizeof(char) * 255);
	char* cmd = (char*)malloc(sizeof(char) * 255);

	char* usr = (char*)malloc(sizeof(char) * strlen(getenv("USER")));	//---------------------//
	usr = getenv("USER");												

	char machine[1024];						//Assuming machine has less than 1023 characters in name//
	machine[1023] = '\0';													//Setting up the prompt//
	gethostname(machine, 1023);

	char* pwd = (char*)malloc(sizeof(char) * strlen(getenv("PWD")));
	pwd = getenv("PWD");													//---------------------//

	PrintEnviron(envp);

	while (status == 1)
	{
		ans = Prompt(ans, usr, machine, pwd);
		if((tmp = strchr(ans, '\n')) != NULL)
			*tmp = '\0';
		
		if (strcmp(ans, "exit") == 0)
		{
			status = 0;
			printf("WORKS\n");
		}
		
		printf("\n");	
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

