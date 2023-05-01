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

void log(log_level const level, std::string_view const message)
{
  std::cout << "[" << static_cast<char>(level) << "] " << message << "\n";
  log_file << "[" << static_cast<char>(level) << "] " << message << "\n";
}
