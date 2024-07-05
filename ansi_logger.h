#ifndef ANSI_LOGGER_H
#define ANSI_LOGGER_H

#include <stdio.h>
#include <time.h>

#include "ANSI-Library/ansi_lib.h"

/////////////////////////////////////////////////
//
// The format modifiers available for the header:
// %l -> Log level
// %n -> Logger name
// %w -> Weekday
// %d -> Day of the Month
// %m -> Month
// %M -> Month in digit form
// %y -> 4-digit year
// %h -> Hour in 24 format
// %H -> Hour in 12 format
// %r -> Minutes
// %s -> Seconds
// %u -> AM/PM
// %f -> File name
// %i -> line
// %b -> function
// %c -> Message
//
/////////////////////////////////////////////////

typedef struct {
  char *name;
  char *pattern;
} Logger;

typedef enum {
  DEBUG = 0,
  INFO = 1,
  LOG = 2,
  SUCCESS = 3,
  WARN = 4,
  ERR = 5,
} LogLevel;

typedef struct {
  LogLevel level;
  const char *msg;
} LogEntry;

inline extern Logger create_logger(const char *name, const char *pattern) {
  setupConsole();

  Logger logger = {.name = (char *)malloc(sizeof(name)),
                   .pattern = (char *)malloc(sizeof(pattern))};

  strcpy(logger.name, name);
  strcpy(logger.pattern, pattern);

  return logger;
}

typedef struct {
  int year;
  int month;
  int day;
  int weekday;
  int hour;
  int minute;
  int second;
  char meridiem[3];
} Date;

inline static Date getDate() {
  time_t epoch_time = time(NULL);

  struct tm tm;

  localtime_s(&tm, &epoch_time);

  Date date = {.year = tm.tm_year + 1900,
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

static Colors getColor(const LogLevel level) {
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

static void print_msg(const Logger logger, const LogEntry entry,
                      const char *file, int line, const char *funct) {
  // Any helper structures;
  const char *log_levels[] = {"DEBUG",   "INFO", "LOG",
                              "SUCCESS", "WARN", "ERROR"};
  const char *weekdays[] = {"MONDAY", "TUESDAY",  "WEDNESDAY", "THURSDAY",
                            "FRIDAY", "SATURDAY", "SUNDAY"};
  const char *months[] = {"JANUARY",   "FEBRUARY", "MARCH",    "APRIL",
                          "MAY",       "JUNE",     "JULY",     "AUGUST",
                          "SEPTEMBER", "OCTOBER",  "NOVEMBER", "DECEMBER"};

  const Colors log_color = getColor(entry.level);

  // Used variables;
  Date date = getDate();
  char *pattern = logger.pattern;

  while (*pattern) {
    if (*pattern == '%') {
      char fmt[16] = "%";
      char *fmt_p = fmt + 1;

      pattern++;

      while (*pattern != '\0' && strchr("0123456789.-", *pattern)) {
        *fmt_p++ = *pattern++;
      }

      switch (*pattern) {
      case 'l':
        SetColor(log_color);
        *fmt_p++ = 's';
        *fmt_p = '\0';
        printf(fmt, log_levels[entry.level]);
        break;
      case 'n':
        SetColor(log_color);
        *fmt_p++ = 's';
        *fmt_p = '\0';
        printf(fmt, logger.name);
        break;
      case 'c':
        SetColor(TXT_WHITE);
        *fmt_p++ = 's';
        *fmt_p = '\0';
        printf(fmt, entry.msg);
        break;
      case 'w':
        SetColor(log_color);
        *fmt_p++ = 's';
        *fmt_p = '\0';
        printf(fmt, weekdays[date.weekday]);
        break;
      case 'd':
        SetColor(log_color);
        *fmt_p++ = 'd';
        *fmt_p = '\0';
        printf(fmt, date.day);
        break;
      case 'm':
        SetColor(log_color);
        *fmt_p++ = 's';
        *fmt_p = '\0';
        printf(fmt, months[date.month]);
        break;
      case 'M':
        SetColor(log_color);
        *fmt_p++ = 'd';
        *fmt_p = '\0';
        printf(fmt, date.month + 1);
        break;
      case 'y':
        SetColor(log_color);
        *fmt_p++ = 'd';
        *fmt_p = '\0';
        printf(fmt, date.year);
        break;
      case 'h':
        SetColor(log_color);
        *fmt_p++ = 'd';
        *fmt_p = '\0';
        printf(fmt, date.hour);
        break;
      case 'H':
        SetColor(log_color);
        *fmt_p++ = 'd';
        *fmt_p = '\0';
        printf(fmt, date.hour % 12);
        break;
      case 'r':
        SetColor(log_color);
        *fmt_p++ = 'd';
        *fmt_p = '\0';
        printf(fmt, date.minute);
        break;
      case 's':
        SetColor(log_color);
        *fmt_p++ = 'd';
        *fmt_p = '\0';
        printf(fmt, date.second);
        break;
      case 'u':
        SetColor(log_color);
        *fmt_p++ = 's';
        *fmt_p = '\0';
        printf(fmt, date.meridiem);
        break;
      case 'f':
        SetColor(log_color);
        *fmt_p++ = 's';
        *fmt_p = '\0';
        printf(fmt, file);
        break;
      case 'i':
        SetColor(log_color);
        *fmt_p++ = 'd';
        *fmt_p = '\0';
        printf(fmt, line);
        break;
      case 'b':
        SetColor(log_color);
        *fmt_p++ = 's';
        *fmt_p = '\0';
        printf(fmt, funct);
        break;
      default:
        SetColor(log_color);
        *fmt_p++ = *pattern;
        *fmt_p = '\0';
        printf("%s", fmt);
      }
    } else {
      SetColor(log_color);
      printf("%c", *pattern);
    }
    pattern++;
  }
  printf("\n");
  SetColor(TXT_WHITE);
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
