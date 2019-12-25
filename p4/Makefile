CC=gcc
WARNING_FLAGS=-Wall -Wextra
EXE=537malloc
# LIBS is placed at the end of gcc's linking stage (after all .o files) so it links the necessary library functions (like pthread) to your code
SCAN_BUILD_DIR=scan-build-out

# the -g flag at all gcc compilation stages ensures that you can use gdb to debug your code
$(EXE): 537malloc.o AVL.o
	$(CC) -g -o $(EXE) 537malloc.o AVL.o

537malloc.o: 537malloc.c
	$(CC) -g $(WARNING_FLAGS) -c 537malloc.c

#main.o: main.c
#	$(CC) -g $(WARNING_FLAGS) -c main.c

AVL.o: AVL.c
	$(CC) -g $(WARNING_FLAGS) -c AVL.c

# the -f flag for rm ensures that clean doesn't fail if file to be deleted doesn't exist
clean:
	rm -f $(EXE) *.o

# recompile runs clean and then makes everything again to generate executable
# this is equivalent to running "make clean" followed by "make"
recompile: clean $(EXE)

#
# Run the Clang Static Analyzer
#
scan-build: clean
	scan-build -o $(SCAN_BUILD_DIR) make

#
# View the one scan available using firefox
#
scan-view: scan-build
	firefox -new-window $(SCAN_BUILD_DIR)/*/index.html
