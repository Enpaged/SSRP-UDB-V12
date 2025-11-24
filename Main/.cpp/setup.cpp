#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <direct.h>
#include <Windows.h>

#include "master.h"

int setup() {
	if (_chdir(".db") != 0)
	{									//Check if .db directory exists
		system("cls");
		perror("Failed to change .db directory [S1]");
		printf("Creating .db directory automatically...\n");

		if (_mkdir(".db") != 0)
		{
			perror("\nFailed to create .db directory [S2]");		//Create .db directory if it does not exist
			printf("Exiting...\n");
			Sleep(3000);
			exit(1);
		}
		printf("Successfully created .db directory!\n");

		if (_chdir(".db") != 0) {
			system("cls");
			perror("Failed to change directory to .db [S3]");
			Sleep(3000);
			exit(1);
		}
		printf("Changed to .db directory successfully...\n");
		printf("Creating .users.txt and .count.txt files...\n");

		FILE* solver = fopen(".users.txt", "w");	//Create .users.txt file in .db directory
		if (solver == NULL) {						//Check if file was able to open
			system("cls");							//If not, print error and exit
			CWD();
			perror("\nFailed to create .users.txt [S4]");
			Sleep(3000);
			exit(1);
		}

		printf(".users.txt created successfully...\n");

		fclose(solver);								//Close the file after creation


		printf("Creating .count.txt file...\n");
		solver = fopen(".count.txt", "w");			//Create .count.txt file in .db directory
		if (solver == NULL) {						//Check if file was able to open
			system("cls");							//If not, print error and exit
			CWD();
			perror("\nFailed to create .count.txt [S5]");
			Sleep(3000);
			exit(1);
		}

		if (_chdir("..") != 0) {					//Change back to parent directory
			system("cls");							//If failed, print error and exit
			CWD();
			perror("\nFailed to change directory to parent [S6]");
			Sleep(3000);
			exit(1);
		}

		printf(".count.txt created successfully...\n");
		fprintf(solver, "0");						//Write 0 to .count.txt file
		fclose(solver);								//Close the file after creation
		printf("Successfully created main directory!\n");

		exit(1);						//Exit after creating .db directory

	}
	return 0;
}

