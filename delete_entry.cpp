#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>
#include <conio.h>
#include <direct.h>

#include "master.h"
#include "config.h"

void delete_entry(int exit_)								//TODO: Function to delete an entry or user
{
	char buffer[128] = {};									//Buffer for reading data from .users.txt
	char username[32] = {};									//Variable to store username to delete
	char moveuser[64] = {};									//Buffer for moving user directory

	char username_[32];										//Variables to store read data
	char role[16];
	char rule[32];
	char date[16];
	char time[16];
	char status[16];
	char yt[64];
	int ID = 0;
	int FILE_ID = 0;										//Variable to store file ID

	int searchsucces = 0;									//Variable to check if deletion was successful
	char delchoice = 'W';									//Variable to store user choice
	int delid = 9999;
	char delfile[64];										//Buffer for file name to delete



	while (searchsucces != 1)
	{
		system("cls");
		header();													//Display header
		gotoxy(0, 4);
		printf("Main/Delete Entry\n");
		gotoxy(0, 6);
		printf("\nEnter a username to search:\n");
		printf("Username: ");
		scanf_s("%31s", username, (unsigned)_countof(username));		//User input for username
		username[strcspn(username, "\n")] = '\0';						//Remove newline character from username


		if (_chdir(".db") != 0) {									//Check if user directory exists
			system("cls");												//If not, print error and exit
			CWD();
			perror("\nFailed to change directory to user [DE1]");
			Sleep(3000);
			exit(1);
		}

		if (_chdir(username) != 0) {									//Check if user directory exists
			system("cls");		//If not, print error and exit
			header();
			gotoxy(0, 4);
			printf("Main/Delete Entry");
			gotoxy(0, 6);
			printf("\n\nUser not found: %s", username);

			if (_chdir("..") != 0) {										//Change back to parent directory
				system("cls");
				CWD();
				perror("\nFailed to change directory to parent [DE2.1]");
				Sleep(3000);
				exit(1);
			}

			printf("\n\nPress ESC to return...\n");						//Prompt user to press ESC to continue
			while (exit_ != 27)
			{
				exit_ = _getch();
			}
			return;
		}
		searchsucces = 1;
	}
	system("cls");
	header();														//Display header
	gotoxy(0, 4);
	printf("User found: %s\n", username);							//Display found user
	gotoxy(0, 6);
	printf("\n");
	printf("Delete user dir or single entry?\n");
	printf("[y] Delete user directory\n");
	printf("[n] Delete single entry\n");
	while (delchoice != 'y' && delchoice != 'n')
	{
		delchoice = _getch();										//User input for choice
	}

	switch (delchoice)
	{
	case 'y':
	{
		int delcount = 0;												//Variable to count deleted entries
		int entries = 9999;												//Variable to store old entries count
		int olddelcount = 9999;											//Variable to store old deleted entries count
		int countbuffer = 0;											//Buffer for reading .count.txt	

		if (_chdir(username) != 0) {									//Change to user directory
			system("cls");												//If failed, print error and exit
			CWD();
			perror("\nFailed to change directory to user [DE3]");
			Sleep(3000);
			exit(1);
		}
		printf("\nChange to user dir successful...\n");							//Display success message
		printf("Scanning user entries...\n");									//Display scanning message

		for (int i = 0; i < MAX_USER_ENTRIES; i++)								//Loop through all user entries
		{
			char searchfile[64];												//Buffer for file name
			snprintf(searchfile, sizeof(searchfile), "%s_%d.txt", username, i);		//Create file name with username and ID
			FILE* entry = fopen(searchfile, "r");								//Open user entry file
			if (entry == NULL) {												//Check if file was able to open
				continue;														//If not, continue to next entry
			}
			else
			{
				fclose(entry);													//Close the file after reading
				if (remove(searchfile) != 0) {									//Remove user entry file
					system("cls");
					CWD();
					perror("\nFailed to remove entry file [DE4]");
					Sleep(3000);
					exit(1);
				}
				delcount++;														//Count deleted entries
			}
		}
		printf("%d entries deleted...\n", delcount);							//Display deleted entries count

		if (_chdir("..") != 0) {												//Change back to parent directory
			system("cls");														//If failed, print error and exit
			CWD();
			perror("\nFailed to change directory to parent [DE6]");
			Sleep(3000);
			exit(1);
		}

		//TESTING
		if (_chdir("..") != 0) {												//Change back to parent directory
			system("cls");														//If failed, print error and exit
			CWD();
			perror("\nFailed to change directory to parent [DE6]");
			Sleep(3000);
			exit(1);
		}

		printf("Change to parent dir successful...\n");							//Display success message

		printf("\nUser Entries of: %s deleted successfully!\n", username);		//Display success message
		printf("\nPress ESC to continue...\n");					//Prompt user to press ESC to continue
		while (exit_ != 27)
		{
			exit_ = _getch();
		}
		break;
	}
	case 'n':
		system("cls");
		header();													//Display header
		gotoxy(0, 4);
		printf("Main/Delete Entry/Single Entry\n");
		gotoxy(0, 6);
		printf("Listing user entries for: %s\n", username);			//Display user entries
		printf("\n");
		printf("%-8s %-8s %-32s %-16s %-32s %-16s %-16s %-16s %-64s\n",
			"FILE", "ID", "Username", "Role", "Rule", "Date", "Time", "Status", "Evidence[YT, GD]");

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
				i, ID, username_, role, rule, date, time, status, yt);				//Display read data in table format
		}
		printf("\n Select FILE to delete: ");
		scanf_s("%d", &delid);													//User input for ID to delete

		snprintf(delfile, sizeof(delfile), "%s_%d.txt", username, delid);			//Create file name with username and ID

		if (remove(delfile) != 0)
		{
			system("cls");														//Remove file with the given ID
			CWD();
			perror("Failed to remove entry file [DE9]");						//If failed, print error and exit
			Sleep(3000);
			exit(1);
		}
		printf("\nEntry with FILE %d deleted successfully!\n", delid);				//Display success message

		if (_chdir("..") != 0) {												//Change back to parent directory
			CWD();
			system("cls");														//If failed, print error and exit
			perror("Failed to change directory to parent [DE10]");
			Sleep(3000);
			exit(1);
		}

		//TESTING
		if (_chdir("..") != 0) {												//Change back to parent directory
			system("cls");														//If failed, print error and exit
			CWD();
			perror("\nFailed to change directory to parent [DE6]");
			Sleep(3000);
			exit(1);
		}
		break;
	}

	printf("Press ESC to continue...\n");						//Prompt user to press ESC to continue
	while (exit_ != 27)
	{
		exit_ = _getch();
	}

}