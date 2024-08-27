const ansi_logger = require("logger-ansi");

const logger = ansi_logger.create_logger(
  "Logger",
  "%l - %n - %m - %H - %w %d/%M/%y %h:%r:%s %u - %f:%b:%i: %c\n",
);

ansi_logger.DEBUG(logger, "Debug");
ansi_logger.INFO(logger, "Info");
ansi_logger.LOG(logger, "Log");
ansi_logger.SUCCESS(logger, "Success");
ansi_logger.WARN(logger, "Warn");
ansi_logger.ERROR(logger, "Error");
