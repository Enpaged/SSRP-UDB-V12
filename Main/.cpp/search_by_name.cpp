#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>
#include <conio.h>
#include <direct.h>

#include "config.h"
#include "master.h"



void search_by_user(int exit_)								//TODO: Function to delete an entry or user
{
	char buffer[128];										//Buffer for reading data from .users.txt
	char username[32];										//Variable to store username to delete
	char moveuser[64];										//Buffer for moving user directory

	char username_[32];					//Variables to store read data
	char role[16];
	char rule[32];
	char date[16];
	char time[16];
	char status[16];
	char yt[64];
	int ID = 0;
	int FILE_ID = 0;									//Variable to store file ID

	int searchsucces = 0;									//Variable to check if deletion was successful
	char delchoice = 'W';									//Variable to store user choice
	int delid = 9999;
	char delfile[64];										//Buffer for file name to delete

	int user_entries = 0;



	while (searchsucces != 1)
	{
		system("cls");
		header();													//Display header
		gotoxy(0, 4);
		printf("Main/Delete Entry\n");
		gotoxy(0, 6);
		printf("Enter a username to delete the entry:\n");
		printf("Username: ");
		scanf_s("%31s", username, (unsigned)_countof(username));	//User input for username
		username[strcspn(username, "\n")] = '\0';					//Remove newline character from username

		//TEST IF USER EXISTS
		if (_chdir(".db") != 0) {										//Change to .db directory
			system("cls");												//If failed, print error and exit
			CWD();										//Get current working directory
			perror("Failed to change directory to .db [DE0]");
			Sleep(3000);
			exit(1);
		}

		if (_chdir(username) != 0) {									//Check if user directory exists
			system("cls");												//If not, print error and exit
			printf("User '%s' does not exist in the database\n", username);
			CWD();
			if (_chdir("..") != 0) {										//Change back to parent directory
				system("cls");
				CWD();
				perror("\nFailed to change directory to parent [DE2.1]");
				Sleep(3000);
				exit(1);					
			}
			printf("\n\nPress ESC to exit...\n");	//Prompt user to press ESC to continue
			while (exit_ != 27)
			{
				exit_ = _getch();
			}
			return;
			
		}
		if (_chdir("..") != 0) {										//Change back to parent directory
			system("cls");
			CWD();
			perror("\nFailed to change directory to parent [DE2.1]");
			Sleep(3000);
			exit(1);
		}
		searchsucces = 1;
	}

	system("cls");
	header();													//Display header
	gotoxy(0, 4);
	printf("Main/Search Entries by User\n");
	gotoxy(0, 6);
	printf("Listing user entries for: %s\n", username);			//Display user entries
	printf("\n");
	printf("%-8s %-8s %-32s %-16s %-32s %-16s %-16s %-16s %-64s\n",
		"FILE", "ID", "Username", "Role", "Rule", "Date", "Time", "Status", "Evidence[YT, GD]");
	for (int i = 0; i < HEADER_SIZE; i++)														//Display header line
	{
		printf("-");
	}
	printf("\n");

	if (_chdir(username) != 0) {									//Change to user directory
		system("cls");												//If failed, print error and exit
		CWD();
		perror("Failed to change directory to user [DE8]");
		Sleep(3000);
		exit(1);
	}
	for (int i = 0; i < MAX_USER_ENTRIES; i++)								//Loop through all user entries
	{
		char searchfile[64];												//Buffer for file name
		snprintf(searchfile, sizeof(searchfile), "%s_%d.txt", username, i);		//Create file name with username and ID
		FILE* entry = fopen(searchfile, "r");								//Open user entry file
		if (entry == NULL) {												//Check if file was able to open
			continue;														//If not, continue to next entry
		}
		fgets(username_, sizeof(username_), entry);							//Read data from file
		username_[strcspn(username_, "\n")] = '\0';							//Remove newline character from username

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
			perror("Failed to read ID from entry file [DE5]");				//If reading failed, print error and exit
			Sleep(3000);
			exit(1);
		}
		fclose(entry);														//Close the file after reading
		printf("%-8d %-8d %-32s %-16s %-32s %-16s %-16s %-16s %-64s\n",
			i, ID, username_, role, rule, date, time, status, yt);			//Display read data in table format

		user_entries++;
	}

	if (_chdir("..") != 0) {												//Change back to parent directory
		CWD();
		system("cls");														//If failed, print error and exit
		perror("Failed to change directory to parent [DE10]");
		Sleep(3000);
		exit(1);
	}
	if (_chdir("..") != 0) {										//Change back to parent directory
		system("cls");
		CWD();
		perror("\nFailed to change directory to parent [DE11]");
		Sleep(3000);
		exit(1);
	}

	printf("\n\nFound Entries: %d", user_entries);

	printf("\n\nPress ESC to exit...\n");						//Prompt user to press ESC to continue
	while (exit_ != 27)
	{
		exit_ = _getch();
	}

}
