#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>
#include <conio.h>
#include <direct.h>

#include "config.h"
#include "master.h"



void list_db(int exit_)					//Function to list the database entries
{
	char username[32];					//Variables to store read data
	char role[16];
	char rule[32];
	char date[16];
	char time[16];
	char status[16];
	char yt[64];
	int ID = 0;

	int allentries = 0;								//Buffers
	char data[32];
	char buffer[128];								//Buffer for reading data from .users.txt
	int counter = 0;					//Counter for entries

	system("cls");
	header();								//Display header
	gotoxy(0, 4);
	printf("Main/Database");
	gotoxy(0, 6);
	printf("%-8s %-32s %-16s %-32s %-16s %-16s %-16s %-64s\n",
		"ID", "Username", "Role", "Rule", "Date", "Time", "Status", "Evidence [YT, GD]");	//Display first tabel line
	for (int i = 0; i < HEADER_SIZE; i++)														//Display header line
	{
		printf("-");
	}
	printf("\n");

	if (_chdir(".db") != 0) {										//Change to .db directory
		system("cls");												//If failed, print error and exit
		CWD();										//Get current working directory
		perror("Failed to change directory to .db [LD0.0]");
		Sleep(3000);
		exit(1);
	}

	FILE* database = fopen(".users.txt", "r");			//Open .db.txt to read entries
	if (database == NULL) {
		system("cls");
		CWD();									//If not, print error and exit
		perror("\nFailed to open .users.txt [LD2.2]");
		Sleep(3000);
		exit(1);
	}

	fgets(buffer, sizeof(data), database);									//Read first line from .users.txt [Buffer]

	while (fgets(data, sizeof(data), database) != NULL)
	{
		data[strcspn(data, "\n")] = '\0';


		if (_chdir(data) != 0)
		{
			system("cls");
			CWD();
			perror("Failed to change directory to user [LD3]");
			Sleep(3000);
			exit(1);
		}

		for (int i = 0; i < MAX_USER_ENTRIES; i++)								//Loop through all user entries
		{
			char searchfile[64];												//Buffer for file name
			snprintf(searchfile, sizeof(searchfile), "%s_%d.txt", data, i);		//Create file name with username and ID
			FILE* entry = fopen(searchfile, "r");								//Open user entry file
			if (entry == NULL) {												//Check if file was able to open
				continue;														//If not, continue to next entry
			}
			fgets(username, sizeof(username), entry);							//Read data from file
			username[strcspn(username, "\n")] = '\0';							//Remove newline character from username

			fgets(role, sizeof(role), entry);									//Read role
			role[strcspn(role, "\n")] = '\0';									//Remove newline character from role

			fgets(rule, sizeof(rule), entry);									//Read rule
			rule[strcspn(rule, "\n")] = '\0';									//Remove newline character from rule

			fgets(date, sizeof(date), entry);									//Read date
			date[strcspn(date, "\n")] = '\0';									//Remove newline character from date

			fgets(time, sizeof(time), entry);									//Read time
			time[strcspn(time, "\n")] = '\0';									//Remove newline character from time

			fgets(status, sizeof(status), entry);								//Read status
			status[strcspn(status, "\n")] = '\0';								//Remove newline character from status

			fgets(yt, sizeof(yt), entry);										//Read evidence
			yt[strcspn(yt, "\n")] = '\0';										//Remove newline character from evidence

			if (fscanf(entry, "%d", &ID) != 1) {								//Read ID from file
				system("cls");
				CWD();
				perror("\nFailed to read ID from entry file [LD5]");				//If reading failed, print error and exit
				Sleep(3000);
				exit(1);
			}
			fclose(entry);														//Close the file after reading
			printf("%-8d %-32s %-16s %-32s %-16s %-16s %-16s %-64s\n",
				ID, username, role, rule, date, time, status, yt);			//Display read data in table format

			counter++;														//Increment counter for entries
		}
		if (_chdir("..") != 0) {												//Change back to parent directory
			system("cls");														//If failed, print error and exit
			CWD();
			perror("\nFailed to change directory to parent [LD5.1]");
			Sleep(3000);
			exit(1);
		}

	}
	fclose(database);														//Close .users.txt file
	//TEMPORARY FIX: Resetting directory to main
	if (_chdir("..") != 0) {												//Change back to main directory
		system("cls");														//If failed, print error and exit
		CWD();
		perror("\nFailed to change directory to main [LD6]");
		Sleep(3000);
		exit(1);
	}

	printf("\nEntries: %d\n", counter);
	printf("\n\nDatabase reading successfully!\n");
	printf("\nPress ESC to continue...\n");
	while (exit_ != 27)
	{
		exit_ = _getch();
	}
}
