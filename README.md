# logger
c header for logger automatic daily logfile.

# Functions
create_logger(char *dir,char *log_prefix_name);

Used to create the logfile with your options. Automatically suffix will be added like "_DD_MM_YYYY.log"

logmsg(int level,char *fmt,...);

Used to print the content to the log file.
level can be, INFO,ERROR,FATAL

Note: For more info see sample.c

