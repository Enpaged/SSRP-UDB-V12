#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>
#include <conio.h>
#include <direct.h>

#include "config.h"
#include "master.h"

void add_entry(int exit_)				//Function to add an entry to the database
{
	char username[32];					//All variables are used to store user input
	char role[16];
	char rule[32];
	char date[16];
	char time[16];
	char status[16];
	char yt[64];

	int allentries = 0;					//buffer variables
	char choice = 'W';					//Variable to store user choice
	char searchfile[64];
	int ID = 0;

	char debug[256];					//Debug buffer for current working directory
	int dir_swutch = 0;					//Variable to check if user di was already accessed

	system("cls");
	header();														//Display header
	gotoxy(0, 4);
	printf("please enter the following information\n");

	
	//..
	

	if (_chdir(".db") != 0) {										//Change to .db directory
		system("cls");												//If failed, print error and exit
		CWD();										//Get current working directory
		printf("CWD: %s\n", debug);										//Debug print to see current working directory
		perror("Failed to change directory to .db [AE1]");
		Sleep(3000);
		exit(1);
	}

	//data_[strcspn(data_, "\n")] = '\0';

	FILE* entries = fopen(".count.txt", "r");						//Load total entries from .count.txt
	if (entries == NULL) {											//Check if  file was able to open
		system("cls");
		perror("Failed to open .count.txt [AE2]");
		Sleep(3000);
		exit(1);
	}
	if (fscanf(entries, "%d", &allentries) != 1)					//Check if reading was successful
	{																//If not, print error and exit
		system("cls");
		CWD();
		perror("Failed to read .count.txt [AE3]");
		Sleep(3000);
		exit(1);
	}
	fclose(entries);

	ID = allentries++;


	printf("\n\nID               : %d", ID);						//user UI
	printf("\nUsername         : ");
	printf("\nRole             : ");
	printf("\nRule             : ");
	printf("\nDate             : ");
	printf("\nTime             : ");
	printf("\nStatus           : ");
	printf("\nEvidence (YT, GD): ");

	gotoxy(20, 8);													//Set cursor position
	scanf_s("%31s", username, (unsigned)_countof(username));		//user input
	gotoxy(20, 9);
	scanf_s("%15s", role, (unsigned)_countof(role));
	gotoxy(20, 10);
	scanf_s("%31s", rule, (unsigned)_countof(rule));
	gotoxy(20, 11);
	scanf_s("%15s", date, (unsigned)_countof(date));
	gotoxy(20, 12);
	scanf_s("%15s", time, (unsigned)_countof(time));
	gotoxy(20, 13);
	scanf_s("%15s", status, (unsigned)_countof(status));
	gotoxy(20, 14);
	scanf_s("%63s", yt, (unsigned)_countof(yt));

	username[strcspn(username, "\n")] = '\0';						//Remove newline character from username


	if (_chdir(username) != 0)										//Check if user directory exists
	{																//If not, prompt to create it
		system("cls");
		printf("User dir: %s does not exist\n", username);
		printf("Do you want to create it? (y/n)\n");


		char choice = _getch();


		switch (choice)
		{

		case 'y':
		{
			if (_mkdir(username) != 0) {								//Create user directory
				system("cls");
				CWD();
				perror("\nFailed to create user directory [AE4]");
				Sleep(3000);
				exit(1);
			}
			if (_chdir(username) != 0) {								//Change to new user directory
				system("cls");
				CWD();
				perror("\nFailed to change directory to user [AE5]");
				Sleep(3000);
				exit(1);
			}
			if (_chdir("..") != 0) {									//Go abck to parent directory
				system("cls");
				CWD();
				perror("\nFailed to change directory to parent [AE6]");
				Sleep(3000);
				exit(1);
			}
			FILE* users = fopen(".users.txt", "a");						//Open .users.txt to attach new user
			if (users == NULL) {
				system("cls");
				CWD();
				perror("\nFailed to open .users.txt [AE7]");
				Sleep(3000);
				exit(1);
			}

			if (_chdir(username) != 0) {								//Create user directory
				system("cls");
				CWD();
				perror("\nFailed to create user directory [AE4.1]");
				Sleep(3000);
				exit(1);
			}

			fprintf(users, "\n%s", username);								//Write username to .users.txt
			fclose(users);												//Close the file

			break;														//If user directory created successfully, continue
		}
		case 'n':	//If user does not want to create directory, exit

			//TESTING
			if (_chdir("..") != 0) {												//Change back to parent directory
				system("cls");														//If failed, print error and exit
				CWD();
				perror("\nFailed to change directory to parent [DE6]");
				Sleep(3000);
				exit(1);
			}

			system("cls");
			printf("User directory creation aborted, exiting...\n");
			printf("Press ESC to continue...\n");
			while (exit_ != 27)
			{
				exit_ = _getch();
			}
			break;
		}
	}

	for (int i = 0; i < MAX_USER_ENTRIES; i++)
	{
		snprintf(searchfile, sizeof(searchfile), "%s_%d.txt", username, i);			//Create File name with username and ID

		FILE* search = fopen(searchfile, "r");										//Search or file with the same name
		if (search == NULL) {
			FILE* new_entry = fopen(searchfile, "w");								//If file does not exist, create a new one
			if (new_entry == NULL) {												//File creation check
				system("cls");
				CWD();
				perror("Failed to create new entry file [AE9]");
				Sleep(3000);
				exit(1);
			}
			fprintf(new_entry, "%s\n", username);			//Write data into new file
			fprintf(new_entry, "%s\n", role);
			fprintf(new_entry, "%s\n", rule);
			fprintf(new_entry, "%s\n", date);
			fprintf(new_entry, "%s\n", time);
			fprintf(new_entry, "%s\n", status);
			fprintf(new_entry, "%s\n", yt);
			fprintf(new_entry, "%d\n", ID);
			fclose(new_entry);
			break;											//File created successfully, break the loop
		}
		else {
			fclose(search);									//Close file securly
			continue;										//File exists, try next ID
		}
	}

	if (_chdir("..") != 0) {										//Change back to parent directory
		system("cls");
		CWD();
		perror("\nFailed to change directory to parent [AE10]");
		Sleep(3000);
		exit(1);
	}
	//Update the count file
	FILE* count_file = fopen(".count.txt", "w");
	if (count_file == NULL) {
		system("cls");
		CWD();
		perror("\nFailed to open .count.txt [AE11]");
		Sleep(3000);
		exit(1);
	}
	fprintf(count_file, "%d", allentries);				//Write new count to file
	fclose(count_file);										//Close the file									

	printf("\n\nEntry added successfully!\n");

	CWD();

	//TESTING PURPOSES ONLY
	if (_chdir("..") != 0)											//Change to parent directory
	{																//If failed, print error and exit
		system("cls");
		CWD();
		perror("\nFailed to change directory to parent [AE12]");
		Sleep(3000);
		exit(1);
	}

	printf("\nPress ESC to continue...\n");					//Prompt user to press ESC to continue
	while (exit_ != 27)
	{
		exit_ = _getch();
	}
}