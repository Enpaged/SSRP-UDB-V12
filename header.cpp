#include <stdio.h>
#include "config.h"

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