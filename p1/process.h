#ifndef PROCESS_H_
#define PROCESS_H_

#define FILE_NAME_SIZE 100
#define TEMP_SIZE 100
#define P_LIST_SIZE 1000
#define COMM 2
#define STATE 3
#define U_TIME 14
#define S_TIME 15
#define CMDLINE_SIZE 100

/* structure that holds data for each process */
typedef struct {
    int pID;
    char state;
    int uTime;
    int sTime;
    int vMem;
    char cmdline[CMDLINE_SIZE];
} ProcessInfo;

int ProcessFetch (ProcessInfo* query);

#endif
