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
	printf("%s\n", message);
	log_file.write(message, std::strlen(message));
}