#include "ansi_logger.h"

int main() {
  const char *pattern =
      "%l - %n - %m - %02H - %w %02d/%02M/%y %h:%r:%s %u - %f:%b:%i: %c";

  const Logger logger = create_logger("Logger", pattern);

  DEBUG(logger, "Debug");
  LOG(logger, "Log");
  INFO(logger, "Info");
  SUCCESS(logger, "Success");
  WARN(logger, "Warn");
  ERR(logger, "Error");
}
