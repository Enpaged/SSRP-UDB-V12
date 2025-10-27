#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>
#include <conio.h>
#include <direct.h>

void gotoxy(int x, int y);
void header();
void list_db(int exit_);
void add_entry(int exit_);
void delete_entry(int exit_);
void search_by_user(int exit_);
void CWD();

//manual modifier
#define EMPTY_STRING "EMPTY"
#define MAX_USER_ENTRIES 99

#define MAIN_DATA_DIR ".db"
#define HEADER_TEXT "SSRP Unofficial Database"
#define HEADER_VERSION "Version 14.5"
#define HEADER_SIZE 180

int main()					//Main programm
{
	int menu_ = 0;

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

	do {
		system("cls");
		header();
		printf("1: Database\n");
		printf("2: Add Entry\n");
		printf("3: Delete Entry\n");
		printf("4: Search Entry by User\n");
		printf("ESC: Exit\n");
		menu_ = _getch();

		switch (menu_) {
		case '1':
			system("cls");
			list_db(menu_);
			break;
		case '2':
			system("cls");
			add_entry(menu_);
			break;
		case '3':
			system("cls");
			delete_entry(menu_);
			break;
		case '4':
			system("cls");
			search_by_user(menu_);
			break;
		case 27:
			system("cls");
			header();
			printf("Exiting...\n");
			printf("Press any ESC to continue...\n");
			menu_ = _getch();
			break;
		default:
			system("cls");
			header();
			printf("Invalid option, try again.\n");
			printf("Press any ESC to continue...\n");
			menu_ = _getch();
			break;
		}
	} while (menu_ != 27);
}

void header()									//Function to display standart header
{
	printf("%s\n", HEADER_TEXT);
	printf("%s\n", HEADER_VERSION);
	for (int i = 0; i < HEADER_SIZE; i++)
	{
		printf("=");
	}
	printf("\n\n");
	for (int i = 0; i < HEADER_SIZE; i++)
	{
		printf("=");
	}
	printf("\n");
}

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

	printf("\nEntries: %d\n", counter);
	printf("\n\nDatabase reading successfully!\n");
	printf("\nPress ESC to continue...\n");
	while (exit_ != 27)
	{
		exit_ = _getch();
	}
}

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

	if (_chdir("..") != 0)											//Change to parent directory
	{																//If failed, print error and exit
		system("cls");
		CWD();
		perror("\nFailed to change directory to parent [AE0]");
		Sleep(3000);
		exit(1);
	}

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
		case 'n':														//If user does not want to create directory, exit
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

	printf("\nPress ESC to continue...\n");					//Prompt user to press ESC to continue
	while (exit_ != 27)
	{
		exit_ = _getch();
	}
}

void delete_entry(int exit_)								//TODO: Function to delete an entry or user
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

		if (_chdir(username) != 0) {									//Check if user directory exists
			system("cls");												//If not, print error and exit
			CWD();
			perror("\nFailed to change directory to user [DE2]");
			Sleep(3000);
			exit(1);
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
		printf("\nEntry with ID %d deleted successfully!\n", delid);				//Display success message
		if (_chdir("..") != 0) {												//Change back to parent directory
			CWD();
			system("cls");														//If failed, print error and exit
			perror("Failed to change directory to parent [DE10]");
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

		if (_chdir(username) != 0) {									//Check if user directory exists
			system("cls");												//If not, print error and exit
			CWD();
			perror("\nFailed to change directory to user [DE2]");
			Sleep(3000);
			exit(1);
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
	
	printf("\n\nFound Entries: %d", user_entries);

	printf("\n\nPress ESC to exit...\n");						//Prompt user to press ESC to continue
	while (exit_ != 27)
	{
		exit_ = _getch();
	}

}


void gotoxy(int x, int y)
{
	printf("%c[%d;%df", 0x1B, y, x);
}

void CWD()
{
	char CWD_[256];
	//Buffer for current working directory
	if (_getcwd(CWD_, sizeof(CWD_)) != NULL)
	{
		printf("\nDebug CWD : % s \n", CWD_);		//Print current working directory
	}
}

//When reading database 1 line in the name file HAS to be a buffer for the username, so it can be read correctly
//TODO: ?Maybe settings tab for color custumization and other stuff?
//TODO: ?Maybe add a search function to search for users by name?
//TODO: ?Maybe add a function to edit existing entries?
//TODO: ?Maybe add a function to export database to a file?

//FIXME: When deleting user dir .users.txt is not updated correctly, it still contains the deleted user



//Line 407: change dir to user (try)