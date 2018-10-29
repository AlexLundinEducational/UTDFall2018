


################################################################################
# File Names
################################################################################

# PROJECTNAME is a descriptive name used for the backup target
# This should not contain spaces or special characters
PROJECTNAME = p4abackup

# use current directory name as exec file
# EXECFILE = $(shell basename $$(pwd))
# or name it ourseklves
EXECFILE = p4a



# https://gist.github.com/ork/11248510

################################################################################
# Build options
################################################################################

CC       = gcc

INCDIR := include


# all flags from xv6 plus the pthread flag for final executable
CFLAGS   = -std=gnu11 -O3 -Wall -Wextra -Wpedantic -Wstrict-aliasing -pthread
# optional library flags
LDFLAGS  = 
# add -I flag to the beginning of each item in INCDIR
INCDIRS := -I$(INCDIR)


SRC      = $(wildcard *.c)
OBJ      = $(SRC:.c=.o)

################################################################################
# Main Targets
################################################################################

.PHONY: clean all permissions

all: clean $(EXECFILE) permissions
	@echo Type ./p4a then enter to execute the final linked executable.

${EXECFILE}: $(OBJ)
	@echo Linking........
	$(CC) -o $@ $^ $(CFLAGS)
	@echo Sucessfully linked object files to create final executable.
	@echo Compilation Done!
	

%.o: %.c
	$(CC) $(INCDIRS) $(CFLAGS) -o $@ -c $<
	@echo Sucessfully created object file named: $@


clean:
	@rm -rf *.o
	
clean2:
	@rm -rf ./restore
	
permissions:
	@echo Setting file permissions on current directory.
	@$(eval CURDIRNAME := $(shell basename "`pwd`"))
	@chmod 777 $(CURDIRNAME)
	@echo File permissions set to:
	@stat -c "%a %n" $(CURDIRNAME)

################################################################################
# Backups
################################################################################
restore:
	@$(eval FULLDIRNAME := $(shell "`pwd`"))
	@$(eval CURDIRNAME := $(shell basename "`pwd`"))
	# copy tar over
	@mkdir ./restore
	scp -r ~/backups/$(PROJECTNAME).tar.gz ./restore
	@tar xf ~/backups/$(PROJECTNAME).tar.gz -C ./restore --strip-components 1

	
# backup creates two tarballs
# the first, is a backup with a complex file name for logging purposes
# the unique names on backup logs allow multiple versions
# the second, is a backup with a simple file name
# the simple ones are for homework submissions
# to make the TA's life easy
# always remove any existing homework submission before saving that second copy
backup:
	@make clean
	@mkdir -p ~/backups; chmod 700 ~/backups
	@$(eval CURDIRNAME := $(shell basename "`pwd`"))
	@$(eval MKBKUPNAME := ~/backups/$(PROJECTNAME)-$(shell date +'%Y.%m.%d-%H:%M:%S').tar.gz)
	@$(eval SUBMISSION := ~/backups/$(PROJECTNAME).tar.gz)
	@echo
	@echo Writing Backup file to: $(MKBKUPNAME)
	@-tar zcfv $(MKBKUPNAME) ../$(CURDIRNAME) 2> /dev/null
	@chmod 777 $(MKBKUPNAME)
	@echo Writing homework submission file to: $(SUBMISSION)
	@rm -f $(SUBMISSION)
	@-tar zcfv $(SUBMISSION) ../$(CURDIRNAME) 2> /dev/null
	@chmod 777 $(SUBMISSION)
	@echo
	@echo Done!
