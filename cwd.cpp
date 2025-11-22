#include <direct.h>
#include <stdio.h>

void CWD()
{
	char CWD_[256];
	//Buffer for current working directory
	if (_getcwd(CWD_, sizeof(CWD_)) != NULL)
	{
		printf("\nDebug CWD : % s \n", CWD_);		//Print current working directory
	}
}