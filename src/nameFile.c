#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>

void TestFile(){
	int StopEnter = 0;
	char nameFile[80];
	char nameTest[80];
	int timeTest = 0;
	char Question[280];
	char Answer[280];
	char shadow[0];
	
	printf("Enter the name of file: ");
	
	gets(nameFile);
	
	FILE *ptrFile;
	
	ptrFile = fopen(nameFile,"w");
	
	if(ptrFile != NULL){
		
		printf("\n---File successfully created\n");
		
		printf("|Enter information without spaces| \n");
		
		printf("\nName test: ");
		gets(nameTest);
		fprintf (ptrFile, "NAME=%s\n",nameTest);
		
		printf("Time test: ");
		scanf("%d", &timeTest);
		fprintf (ptrFile, "TIME=%d\n", timeTest);
		
		while(!StopEnter){
			
			gets(shadow);
				
			printf("Question: ");
			gets(Question);
			fprintf (ptrFile, "QUESTION=%s\n",Question);
					
			printf("Answer: ");
			gets(Answer);
			fprintf (ptrFile, "ANSWER=%s\n",Answer);
			
			printf("(Continue typing: yes - 0, no - 1): ");
			scanf("%d", &StopEnter);
			
		}	
	}
	
	else
		printf("ERROR_43");	
	printf("\n---File successfully closed");
	fclose(ptrFile);
}


int main(){
	TestFile();
	getch();
}
