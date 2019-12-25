/*******************************************************
 * File Name: process.c
 *
 * Authors: Nick Klabjan, klabjan@cs.wisc.edu
 *          Sam Wheeler, swheeler4@wisc.edu
 *
 * Description: Fetches each process and any relevant
 *              information for that process.
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <string.h>
#include <dirent.h>
#include "process.h"


/*
 * Fetches each process and the relevant information for that process
 */
int ProcessFetch (ProcessInfo* query) {
    DIR *procDir;
    struct dirent *procFile;

    /* stores all the file names */
    char fileNameStat[FILE_NAME_SIZE];
    char fileNameStatm[FILE_NAME_SIZE];
    char fileNameStatus[FILE_NAME_SIZE];
    char fileNameCmdline[FILE_NAME_SIZE];
    /* stores a word from the files */
    char temp[TEMP_SIZE];
    /* pointers to the files */
    FILE *fpStat;
    FILE *fpStatus;
    FILE *fpStatm;
    FILE *fpCmdline;
    /* retrieves the uid */
    int uID = getuid();
    int pID;
    /* counters used throughout the program */
    int count = 0;
    int lineCount = 0;
    int pCount = 0;
    int cmdChar;
    int cmdCount;

    ProcessInfo pInfo[P_LIST_SIZE] = {};
    /* opens the proc file system */
    procDir = opendir ("/proc");
    /* while there is still a process in the proc file system */
    while ((procFile = readdir(procDir)) != NULL) {
        lineCount = 0;
        count = 0;
        
        /* sets fileNameStatus = "/proc/pID/status" */
        strcpy (fileNameStatus, "/proc/");
        strcat (fileNameStatus, procFile->d_name);
        strcat(fileNameStatus, "/status");

        /* opens the status file in read mode */
        fpStatus = fopen(fileNameStatus, "r");
	       if (fpStatus != NULL){
        /* while a word in the file, temp, doesn't equal "Uid:" and count is less than 100*/
	while ((strcmp(temp, "Uid:") != 0) && count < 100) {
            /* sets temp to the next word in the file */
            fscanf(fpStatus, "%s", temp);
            count++;
        }
	fscanf(fpStatus, "%s", temp);
	pID = atoi(temp);
        fclose(fpStatus);

        /* if the process belongs to the user */
        if (((pID == uID) && (query->pID == -1) && (atoi(procFile->d_name) > 0))
			|| ((pID == uID) && ( atoi(procFile->d_name)> 0) && (query->pID == atoi(procFile->d_name)))) {
	pInfo[pCount].pID = atoi(procFile->d_name);
	/* sets fileNameStat and fileNameStatm to "/proc/pID/stat" and "/proc/pID/statm" respectively */
            strcpy (fileNameStat, "/proc/");
            strcat (fileNameStat, procFile->d_name);
            strcpy (fileNameStatm, fileNameStat);
            strcpy (fileNameCmdline, fileNameStat);
            strcat (fileNameStat, "/stat");
            strcat (fileNameStatm, "/statm");
            strcat (fileNameCmdline, "/cmdline");

            /* opens three files */
            fpStat = fopen (fileNameStat, "r");
            fpStatm = fopen (fileNameStatm, "r");
            fpCmdline = fopen (fileNameCmdline, "r");
	    if(fpStat != NULL && fpStatm != NULL && fpCmdline != NULL){
		cmdChar = fgetc(fpCmdline);
		cmdCount = 0;
		while ((cmdChar != -1) && (cmdCount < CMDLINE_SIZE)){
			pInfo[pCount].cmdline[cmdCount] = cmdChar;
			cmdChar = fgetc(fpCmdline);
			if (cmdChar == 0){
				cmdChar = ' ';
			}
			cmdCount++;
		}
	    /* while not at the end of the stat file */
            while (fscanf(fpStat, "%s", temp) != EOF) {
                /* increments lineCount */
                lineCount++;

                /* if lineCount is equal to 3 */
                if (lineCount == STATE) {
	        pInfo[pCount].state = (temp[0]);
                }
                /* if lineCount is equal to 14 */
                if (lineCount == U_TIME) {
                    pInfo[pCount].uTime = atoi(temp);
                }
                /* if lineCount is equal to 15 */
                if (lineCount == S_TIME) {
                    pInfo[pCount].sTime = atoi(temp);
                    break;
                }
            }
	    fscanf(fpStatm, "%s", temp);
	    pInfo[pCount].vMem = atoi(temp);
	    fclose (fpStat);
	    fclose (fpStatm);
	    fclose (fpCmdline);
	    pCount++;
        }
	}
  else if ((query->pID > 0) && (atoi(procFile->d_name)> 0) && (query->pID != atoi(procFile->d_name))){
    printf("Process does not exist\n");
    return 0;
  }
	}
}

    /* for each process in the pInfo array print out desired info */
    for (int i = 0; i < pCount; i++) {
      printf("%d: ",pInfo[i].pID);
      if (query->state == 1){
          printf("%c ", pInfo[i].state);
      }
      if (query->uTime == 1){
          printf("utime=%d ", pInfo[i].uTime);
      }
      if (query->sTime == 1){
	  printf("sTime=%d ", pInfo[i].sTime);
      }
      if (query->vMem == 1){
          printf("vmemory=%d ", pInfo[i].vMem);
      }
      if (strcmp(query->cmdline, "0") == 0){
          printf("[%s]", pInfo[i].cmdline);
      }
      printf("\n");
    }
    return 0;
}
