//gcc -o test_bin  PreventReopen-proc.c
#include <fcntl.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>
#include <stdarg.h>
#include <unistd.h>
#include <sys/wait.h>
#define PROCESS_MAX_STRING_LEN          256
#define PROGRAM_NAME                    "test_bin"
int GetProcNum(const char *pcProcessName)
{
	FILE *f;
	DIR *dir;
	struct dirent *entry;
	char path[PROCESS_MAX_STRING_LEN], buf[PROCESS_MAX_STRING_LEN], name[PROCESS_MAX_STRING_LEN], status[PROCESS_MAX_STRING_LEN];
	int num = 0;
	if (NULL == pcProcessName|| 0 == strlen(pcProcessName))
	{
		return -1;
	}
	dir = opendir("/proc");
	if (NULL == dir)
	{
		return -1;
	}
	while ((entry = readdir(dir)) != NULL)
	{
		if (atoi(entry->d_name) == 0)
		continue;
		sprintf(path, "/proc/%s/status", entry->d_name);
		if ((f = fopen(path, "r")) == NULL)
		{
			continue;
		}
		if (fgets(buf, PROCESS_MAX_STRING_LEN - 1, f) == NULL)
		{
			fclose(f);
			continue;
		}
		sscanf(buf, "%*s %s", name);
		if (strcmp(name, pcProcessName) == 0)
		{
			/*find one*/
			num++;
			/*check status*/
			memset(buf,0,sizeof(buf));
			if (fgets(buf, PROCESS_MAX_STRING_LEN - 1, f) == NULL)
			{
				//printf("read status error\n");
				fclose(f);
				continue;
			}
			sscanf(buf,"%*s %s",status);
		}
		fclose(f);
	}
	closedir(dir);
	
	return num;
}
int main()
{
 
  if (GetProcNum(PROGRAM_NAME) > 1)
   {
		printf("Error: %s is already running, please kill the old program first!\n", PROGRAM_NAME);
        return -1;
   }
   sleep(10);
   printf("the app is not run!\n");		
}