#include "logger.h"

main()
{
								create_logger("./","log"); 
								// Passing directory path and log filename.
								// automatically suffix will be added like "_DD_MM_YYYY.log"

								logmsg(INFO,"Hai, I am %s\n","Robo"); // INFO message
								logmsg(ERROR,"Technical issue\n"); // ERROR message
								logmsg(FATAL,"Going to Die ..\n"); // FATAL message. this will exit your program.
}
