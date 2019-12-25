/*******************************************************
 * File Name: p1.c
 *
 * Authors: Nick Klabjan, klabjan@cs.wisc.edu
 *          Sam Wheeler, swheeler4@wisc.edu
 *
 * Description: Reads through the program arguments and
 *              checks the options for the ps command.
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include "process.h"

/*
 * Reads in program arguments and traverses them to check
 * which options for the ps command are turned on.
 *
 * parameters: argc, length of argv
 *             argv, array of program arguments
 */
int main(int argc, char *argv[]) {
	int option;
	int tempLen;
	ProcessInfo *query = malloc(sizeof(ProcessInfo));
	query->pID = -1;
	query->state = 0;
	query->uTime = 1;
	query->sTime = 0;
	query->vMem = 0;
	strcpy(query->cmdline, "0");
	char *optarg = "";
    /* while there is still an option in the program arguments */
	while ((option = getopt(argc, argv, ":p:s::U::S::v::c::")) != -1) {
		switch(option){
			case 'p':
				tempLen = strlen(optarg);
				for (int i = 0; i < tempLen; i++){
					if (isdigit(optarg[i]) == 0){
					fprintf(stderr, "Invalid input\n");
					exit(EXIT_FAILURE);
					}
				}
				query->pID = atoi(optarg);

				break;
			case 's':
			if (strcmp(optarg, "") == 0){
				query->state = 1;
			}
			else if (strcmp(optarg, "-") == 0){
				query->state = 0;
			}
			else{
				fprintf(stderr, "Invalid input\n");
				exit(EXIT_FAILURE);
			}
				break;
			case 'U':
				if (strcmp(optarg, "") == 0){
					query->uTime = 1;
				}
				else if (strcmp(optarg, "-") == 0){
					query->uTime = 0;
				}
				else{
					fprintf(stderr, "Invalid input\n");
					exit(EXIT_FAILURE);
				}
				break;
			case 'S':
				if (strcmp(optarg, "") == 0) {
					query->sTime = 1;
				}
				else if (strcmp(optarg, "-") == 0){
					query->sTime = 0;
				}
				else{
					fprintf(stderr, "Invalid input\n");
					exit(EXIT_FAILURE);
				}
				break;
			case 'v':
				if (strcmp(optarg, "") == 0){
						query->vMem = 1;
				}
				else if (strcmp(optarg, "-") == 0){
					query->vMem = 0;
					}
				else{
					fprintf(stderr, "Invalid input\n");
					exit(EXIT_FAILURE);
					}
				break;
			case 'c':
				if (strcmp(optarg, "") == 0){
					strcpy(query->cmdline, "0");
				}
				else if (strcmp(optarg, "-") == 0){
					strcpy(query->cmdline, "-1");
				}
				else{
					fprintf(stderr, "Invalid input\n");
					exit(EXIT_FAILURE);
				}
				break;
			default:
				fprintf(stderr, "Invalid input\n");
				exit(EXIT_FAILURE);
		}

	}
	if (optind < argc){
		fprintf(stderr, "Invalid input\n");
		exit(EXIT_FAILURE);
	}
	if (ProcessFetch(query) == 0){
		exit(EXIT_SUCCESS);
	}
}
