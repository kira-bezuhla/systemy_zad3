CC = gcc
CFLAGS = -Wall -std=c99 -pedantic
TARGETS = runA runB runC runCa
SOURCES = pktA.c pktB.c pktC.c pktC_additional.c
EXTRA_FILES = README.TXT 
ARCHIVE_NAME = Bezuhla_zad3.tar.gz


run: $(SOURCES)
	@echo "Compiling all programs..."
	@$(CC) $(CFLAGS) -o runA pktA.c 
	@$(CC) $(CFLAGS) -o runB pktB.c 
	@$(CC) $(CFLAGS) -o runC pktC.c  
	@$(CC) $(CFLAGS) -o runCa pktC_additional.c 

runA: pktA.c
	@echo "Compiling program A..."
	@$(CC) $(CFLAGS) -o runA pktA.c 

runB: pktB.c
	@echo "Compiling program B..."
	@$(CC) $(CFLAGS) -o runB pktB.c 

runC: pktC.c pktC_additional.c
	@echo "Compiling program C and C additional..."
	@$(CC) $(CFLAGS) -o runC pktC.c  
	@$(CC) $(CFLAGS) -o runCa pktC_additional.c 
	

help:
	@echo "Available commands:"
	@echo "make run     - Compile all programs"
	@echo "make runA    - Compile program A"	
	@echo "make runB    - Compile program B"
	@echo "make runC    - Compile program C and C additional"	
	@echo "make clean   - Remove compiled binaries"
	@echo "make tar     - Archive sources"

clean:
	@echo "Cleaning up compiled files..."
	@rm -f $(TARGETS) destination.txt

tar:
	@echo "Creating archive $(ARCHIVE_NAME)..."
	tar -czf $(ARCHIVE_NAME) $(SOURCES) makefile $(EXTRA_FILES)
