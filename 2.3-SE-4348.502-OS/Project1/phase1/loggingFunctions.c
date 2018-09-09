//Alex Lundin
//AML140830@utdallas.edu
//SE-4348.502-OS

#include "project1.h"
#include <cstdlib>


using namespace std;
void daemonSpawner (std::string daemonFlag);
void daemonProcess ( int command_fd, int response_fd);
void parseConfigFile ();
int read_pid ();
int check_pid ();
int write_pid ();
void open_log();
void close_log();
void close_pid();
void signal_HUP_Handler( int signum );
void signal_INT_Handler( int signum );
void signal_TERM_Handler( int signum );
void initiateWatchAndReadBlock();
static int do_mkdir(const char *path, mode_t mode);
int mkpath(const char *path, mode_t mode);

typedef struct stat Stat;

// read map, and close log file
void close_log(){
	
	std::string logFilePath = "cs3377dirmond.log";
	
	// open the standard out file with new value
	FILE * log_file = fopen( logFilePath.c_str(), "r+");
	if(log_file) {
		printf("\nLog ended.");
		// close files
		fclose(log_file);
	}
	
	

	
}

// read map, and open log file
// only used for the daemon, so this substitutes the log file for standard output with dup2
void open_log(){
	std::string logFilePath = "cs3377dirmond.log";
	
    struct stat buf;
    int status = stat(logFilePath.c_str(), &buf);
	
	// use file status to determine if the log already exists
	if (status != 0){
		// Log file does not exist yet
		// reopen the standard out file with new value
		FILE * log_file = fopen( logFilePath.c_str(), "w");
		if(log_file) {
			dup2(fileno(log_file), 1);
		}		
	}else if (status == 0){
		
		//Log file exists already
		// reopen the standard out file with new value, in append mode
		FILE * log_file = fopen( logFilePath.c_str(), "a");
		if(log_file) {
			dup2(fileno(log_file), 1);
		}
	}
	
}
void close_pid(){
	const char *pidfile = "cs3377dirmond.pid";
	// remove pid file
	std::remove(pidfile); // delete file

}

/* read_pid
 *
 * Reads the specified pidfile and returns the read pid.
 * 0 is returned if either there's no pidfile, it's empty
 * or no pid can be read.
 */
int read_pid (){
	const char *pidfile = "cs3377dirmond.pid";
	FILE *f;
	int pid;

	if (!(f=fopen(pidfile,"r")))
	return 0;
	fscanf(f,"%d", &pid);
	fclose(f);
	return pid;
}

/* check_pid
 *
 * Reads the pid using read_pid and looks up the pid in the process
 * table (using /proc) to determine if the process already exists. If
 * so 1 is returned, otherwise 0.
 */
int check_pid ()
{
	const char *pidfile = "cs3377dirmond.pid";
	int pid = read_pid();

	/* Amazing ! _I_ am already holding the pid file... */
	if ((!pid) || (pid == getpid ()))
	return 0;

	/*
	* The 'standard' method of doing this is to try and do a 'fake' kill
	* of the process.  If an ESRCH error is returned the process cannot
	* be found -- GW
	*/
	/* But... errno is usually changed only on error.. */
	if (kill(pid, 0) && errno == ESRCH)
	  return(0);

	return pid;
}

/* write_pid
 *
 * Writes the pid to the specified file. If that fails 0 is
 * returned, otherwise the pid.
 */
int write_pid ()
{
	const char *pidfile = "cs3377dirmond.pid";
	int fd;
	char buf[BUF_SIZE];
	
	fd = open(pidfile, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
	if (fd == -1){
		printf("\nCould not open PID file.");
		return -1;
	}
	else{
	// write pid to log and to pid file	
	snprintf(buf, BUF_SIZE, "%ld\n", (long) getpid());
	
	// if statement write to pid file
	if (write(fd, buf, strlen(buf)) != strlen(buf))
		// write error to log
        printf("\nError writing to PID file");
	else{
		// write sucess to log
		printf("\nCreated pid file successfully.");
	}

	}
  
    
  // close pid
  close(fd);

  return fd;
}