#include "logging.h"

std::ofstream log_file;

void init_log()
{
	log_file.open("log.txt", std::fstream::out);
}

void end_log()
{
	log_file.close();
}

void log(char* message)
{
	printf("%s", message);
	log_file.write(message, std::strlen(message));
}

void log_info(char* message)
{
#ifdef LOG_INFO
	log(message);
#endif
}