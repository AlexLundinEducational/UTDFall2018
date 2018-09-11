#Alex Lundin
#AML140830@utdallas.edu
#SE 3377.501 - CC++ in  UNIX



# Flags for the C implicit rules
CC = gcc
CFLAGS=-I.
DEPS = dash.h

# include flags, each must begin with a -I
INC=-I$(IDIR)


#
# PROJECTNAME is a descriptive name used for the backup target
# This should not contain spaces or special characters
PROJECTNAME = SE4348.aml140830.dash.phase3

EXECFILE = dash

## actually define the names of the OBJS files
OBJS = dash.o builtIns.o parsePathArguements.o commandLineLoop.o scanCommandLine.o parseCommandLine.o processControl.o executeCommandLine.o 
## use wild cards to define what types of files SRCS are 
SRCS = $(wildcard *.c)


all: $(EXECFILE)

clean:
	rm -f $(OBJS) $(EXECFILE) y.tab.h *~ \#*
	
# rule for creating objects from SRCS files, use the include flag and paths from above	
%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)
	
# rule for creating executable, use libaray flags from above
$(EXECFILE):	$(OBJS)
	$(CC) -o $@ $(OBJS)

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
