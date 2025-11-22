#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>
#include <conio.h>
#include <direct.h>

#include  "master.h"

int main()					//Main programm
{
	int menu_ = 0;

	setup();

	if (_chdir("..") != 0) {					//Change back to parent directory
		system("cls");							//If failed, print error and exit
		CWD();
		perror("\nFailed to change directory to parent [S6]");
		Sleep(3000);
		exit(1);
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

//When reading database 1 line in the name file HAS to be a buffer for the username, so it can be read correctly
//TODO: ?Maybe settings tab for color custumization and other stuff?
//TODO: ?Maybe add a search function to search for users by name?
//TODO: ?Maybe add a function to edit existing entries?
//TODO: ?Maybe add a function to export database to a file?

//FIXME: When deleting user dir .users.txt is not updated correctly, it still contains the deleted user



//Line 407: change dir to user (try)
