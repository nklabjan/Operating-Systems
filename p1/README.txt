{\rtf1\ansi\ansicpg1252\cocoartf1561\cocoasubrtf600
{\fonttbl\f0\fswiss\fcharset0 Helvetica;}
{\colortbl;\red255\green255\blue255;}
{\*\expandedcolortbl;;}
\margl1440\margr1440\vieww25400\viewh13700\viewkind0
\pard\tx720\tx1440\tx2160\tx2880\tx3600\tx4320\tx5040\tx5760\tx6480\tx7200\tx7920\tx8640\pardirnatural\partightenfactor0

\f0\fs24 \cf0 Included:\
	Source Files: process.c, p1.c, process.h\
	Makefile\
	README\
\
Running Program:\
	Running the program is rather easy due to the functionality of the Makefile. As a command line 	prompt, type \'93make\'94 and that will compile all source files into one executable called \'93537ps\'94. 	Next, just type \'93537ps [PROGRAM ARGUMENTS]\'94 and program will run. \
\
Program Goal:\
	Implement the \'93ps\'94 command with the ability to have different options turned on or off.\
\
Program Arguments:\
\pard\tx720\tx1440\tx2160\tx2880\tx3600\tx4320\tx5040\tx5760\tx6480\tx7200\tx7920\tx8640\li1727\fi-1728\pardirnatural\partightenfactor0
\cf0 	-p <pid>  Displays process information only for the process whose number is pid.\
\
\pard\tx720\tx1440\tx2160\tx2880\tx3600\tx4320\tx5040\tx5760\tx6480\tx7200\tx7920\tx8640\li1696\fi-1697\pardirnatural\partightenfactor0
\cf0 	-s            Displays the single-character state information about the process.\
 \
\pard\tx720\tx1440\tx2160\tx2880\tx3600\tx4320\tx5040\tx5760\tx6480\tx7200\tx7920\tx8640\li1725\fi-1726\pardirnatural\partightenfactor0
\cf0 	-U	    Displays the amount of user time consumed by this process. \
\
\pard\tx720\tx1440\tx2160\tx2880\tx3600\tx4320\tx5040\tx5760\tx6480\tx7200\tx7920\tx8640\li1680\fi-1681\pardirnatural\partightenfactor0
\cf0 	-S	    Displays the amount of system time consumed so far by this process. \
\
\pard\tx720\tx1440\tx2160\tx2880\tx3600\tx4320\tx5040\tx5760\tx6480\tx7200\tx7920\tx8640\pardirnatural\partightenfactor0
\cf0 	-v	    Displays the amount of virtual memory currently being used (in pages) by this program. \
\
	-c	    Displays the command-line that started this program. \
\
Program Flow:\
\pard\tx720\tx1440\tx2160\tx2880\tx3600\tx4320\tx5040\tx5760\tx6480\tx7200\tx7920\tx8640\li1306\fi-1307\pardirnatural\partightenfactor0
\cf0 	p1.c: This file contains the main() function, which is ultimately called to start the program. Within the main() function, getopt() is used to traverse through each character in the program arguments and a switch statement is used to allow for any order of program arguments. Using a switch statement allows the program to catch any invalid input due to the switch statement\'92s default property.\
\pard\tx720\tx1440\tx2160\tx2880\tx3600\tx4320\tx5040\tx5760\tx6480\tx7200\tx7920\tx8640\pardirnatural\partightenfactor0
\cf0 \
\pard\tx720\tx1440\tx2160\tx2880\tx3600\tx4320\tx5040\tx5760\tx6480\tx7200\tx7920\tx8640\li1914\fi-1915\pardirnatural\partightenfactor0
\cf0 	process.c: This file reads through all the processes in the /proc directory and prints out all the information for any options that were set in the program arguments. The options -s, -U, and -S can be found in the /proc/<pid>/stat file, -v can be found in the /proc/<pid>/statm file, and finally -c can be found in the /proc/<pid>/cmdline. These files are first opened and then traversed to find the needed information. Each processes\'92 information is stored in a data structure and each data structure is then added to an array. After all execution is done, the array is traversed and the fields for each each data structure (element in the array) are printed out.\
\
	process.h: This file contains all the data fields that are shared between p1.c and process.c. That includes all constants and a data structure, which holds all the appropriate fields for a given process. \
\pard\tx720\tx1440\tx2160\tx2880\tx3600\tx4320\tx5040\tx5760\tx6480\tx7200\tx7920\tx8640\pardirnatural\partightenfactor0
\cf0 	\
}