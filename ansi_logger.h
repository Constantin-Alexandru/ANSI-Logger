#ifndef ANSI_LOGGER_H
#define ANSI_LOGGER_H

#include <stdio.h>
#include <time.h>

#include "ANSI-Library/ansi_lib.h"

/////////////////////////////////////////////////
//
// The format modifiers available for the header:
// %l -> Log level
// %L -> Short log level
// %n -> Logger name
// %w -> Weekday
// %W -> Abbreviated Weekday
// %m -> Month
// %M -> Abbreviated Month
// %d -> Month in digit form
// %y -> 4-digit year
// %Y -> 2-digit year
// %h -> Hour in 24 format
// %H -> Hour in 12 format
// %r -> Minutes
// %s -> Seconds
// %c -> Date and time representation
// %u -> AM/PM
// %f -> File name
// %F -> File name and line
// %p -> File path
// %P -> File path and line
// %i -> line
// %b -> function
// %c -> Message
//
/////////////////////////////////////////////////
//
// The alignment modifiers:
// '-' -> left
// '=' -> center
// '_' -> right
//
/////////////////////////////////////////////////

struct Logger {
  char *name;
  char *pattern;
};

enum LogLevel {
  DEBUG = 0,
  INFO = 1,
  LOG = 2,
  SUCCESS = 3,
  WARN = 4,
  ERR = 5,
};

struct LogEntry {
  enum LogLevel level;
  const char *msg;
};

inline extern struct Logger create_logger(const char *name,
                                          const char *pattern) {
  setupConsole();

  struct Logger logger = {.name = (char *)malloc(sizeof(name)),
                          .pattern = (char *)malloc(sizeof(pattern))};

  strcpy(logger.name, name);
  strcpy(logger.pattern, pattern);

  return logger;
}

struct Date {
  int year;
  int month;
  int day;
  int weekday;
  int hour;
  int minute;
  int second;
  char meridiem[3];
};

inline static struct Date getDate() {
  time_t epoch_time = time(NULL);

  struct tm tm;

  localtime_s(&tm, &epoch_time);

  struct Date date = {.year = tm.tm_year + 1900,
                      .month = tm.tm_mon,
                      .day = tm.tm_mday,
                      .weekday = tm.tm_wday,
                      .hour = tm.tm_hour,
                      .minute = tm.tm_min,
                      .second = tm.tm_sec,
                      .meridiem = ""};

  strftime(date.meridiem, sizeof(date.meridiem), "%p", &tm);

  return date;
}

static enum COLOR_4_BIT getColor(const enum LogLevel level) {
  switch (level) {
  case DEBUG:
    return TXT_MAGENTA;
  case INFO:
  case LOG:
    return TXT_BLUE;
  case SUCCESS:
    return TXT_GREEN;
  case WARN:
    return TXT_YELLOW;
  case ERR:
    return TXT_RED;
    break;
  }
  return TXT_WHITE;
}

static void print_msg(const struct Logger logger, const struct LogEntry entry,
                      const char *file, int line, const char *funct) {
  // Any helper structures;
  const char *log_levels[] = {"DEBUG",   "INFO", "LOG",
                              "SUCCESS", "WARN", "ERROR"};
  const char *weekdays[] = {"MONDAY", "TUESDAY",  "WEDNESDAY", "THURSDAY",
                            "FRIDAY", "SATURDAY", "SUNDAY"};
  const char *months[] = {"JANUARY",   "FEBRUARY", "MARCH",    "APRIL",
                          "MAY",       "JUNE",     "JULY",     "AUGUST",
                          "SEPTEMBER", "OCTOBER",  "NOVEMBER", "DECEMBER"};

  const enum COLOR_4_BIT log_color = getColor(entry.level);

  // Used variables;
  struct Date date = getDate();
  char *pattern = logger.pattern;

  while (*pattern) {
    if (*pattern == '%') {
      pattern++;

      switch (*pattern) {
      case 'l':
        SET_FOUR_BIT_COLOR(log_color);
        printf("%s", log_levels[entry.level]);
        break;
      case 'L':
        SET_FOUR_BIT_COLOR(log_color);
        printf("%.3s", log_levels[entry.level]);
        break;
      case 'n':
        SET_FOUR_BIT_COLOR(log_color);
        printf("%s", logger.name);
        break;
      case 'c':
        SET_FOUR_BIT_COLOR(TXT_WHITE);
        printf("%s", entry.msg);
        break;
      case 'w':
        SET_FOUR_BIT_COLOR(log_color);
        printf("%s", weekdays[date.weekday]);
        break;
      case 'W':
        SET_FOUR_BIT_COLOR(log_color);
        printf("%.3s", weekdays[date.weekday]);
        break;
      case 'm':
        SET_FOUR_BIT_COLOR(log_color);
        printf("%s", months[date.month]);
        break;
      case 'M':
        SET_FOUR_BIT_COLOR(log_color);
        printf("%.3s", months[date.month]);
        break;
      case 'y':
        SET_FOUR_BIT_COLOR(log_color);
        printf("%d", date.year);
        break;
      case 'Y':
        SET_FOUR_BIT_COLOR(log_color);
        printf("%d", date.year % 100);
        break;
      case 'h':
        SET_FOUR_BIT_COLOR(log_color);
        printf("%d", date.hour);
        break;
      case 'H':
        SET_FOUR_BIT_COLOR(log_color);
        printf("%d", date.hour % 12);
        break;
      case 'r':
        SET_FOUR_BIT_COLOR(log_color);
        printf("%d", date.minute);
        break;
      case 's':
        SET_FOUR_BIT_COLOR(log_color);
        printf("%d", date.second);
        break;
      case 'u':
        SET_FOUR_BIT_COLOR(log_color);
        printf("%s", date.meridiem);
        break;
      case 'f':
        SET_FOUR_BIT_COLOR(log_color);
        printf("%s", file);
        break;
      case 'F':
        SET_FOUR_BIT_COLOR(log_color);
        printf("%s:%d", file, line);
        break;
      case 'i':
        SET_FOUR_BIT_COLOR(log_color);
        printf("%d", line);
        break;
      case 'b':
        SET_FOUR_BIT_COLOR(log_color);
        printf("%s", funct);
        break;
      default:
        SET_FOUR_BIT_COLOR(log_color);
        printf("%%%c", *pattern);
      }
    } else {
      SET_FOUR_BIT_COLOR(log_color);
      printf("%c", *pattern);
    }
    pattern++;
  }
  printf("\n");
  SET_FOUR_BIT_COLOR(TXT_WHITE);
}

#define DEBUG(logger, message)                                                 \
  print_msg(logger, (struct LogEntry){.level = DEBUG, .msg = message},         \
            __FILE__, __LINE__, __FUNCTION__)

#define INFO(logger, message)                                                  \
  print_msg(logger, (struct LogEntry){.level = INFO, .msg = message},          \
            __FILE__, __LINE__, __FUNCTION__)

#define LOG(logger, message)                                                   \
  print_msg(logger, (struct LogEntry){.level = LOG, .msg = message}, __FILE__, \
            __LINE__, __FUNCTION__)

#define SUCCESS(logger, message)                                               \
  print_msg(logger, (struct LogEntry){.level = SUCCESS, .msg = message},       \
            __FILE__, __LINE__, __FUNCTION__)

#define WARN(logger, message)                                                  \
  print_msg(logger, (struct LogEntry){.level = WARN, .msg = message},          \
            __FILE__, __LINE__, __FUNCTION__)

#define ERR(logger, message)                                                   \
  print_msg(logger, (struct LogEntry){.level = ERR, .msg = message}, __FILE__, \
            __LINE__, __FUNCTION__)

#endif
