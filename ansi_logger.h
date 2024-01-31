#ifndef ANSI_LOGGER_H
#define ANSI_LOGGER_H

#include <stdio.h>
#include <time.h>

#include "ANSI-Library/ansi_lib.h"

static char* getDate() {
  const int DATE_STRING_LENGTH = 11;
  char date_string[DATE_STRING_LENGTH];

  time_t date = time(NULL);
  struct tm* local_time = localtime(&date);

  strftime(date_string, sizeof(date_string), "%02d/%02d/%04d", local_time);

  return date_string;
}

void info(char* message) {
  SET_FOUR_BIT_COLOR(TXT_BLUE);
  printf("[%s] [INFO]: ", getDate());
  SET_FOUR_BIT_COLOR(TXT_DEFAULT);
  printf("%s\n", message);
}

void log(char* message) { info(message); }

void success(char* message) {
  SET_FOUR_BIT_COLOR(TXT_GREEN);
  printf("[%s] [SUCCESS]: ", getDate());
  SET_FOUR_BIT_COLOR(TXT_DEFAULT);
  printf("%s\n", message);
}

void warn(char* message) {
  SET_FOUR_BIT_COLOR(TXT_YELLOW);
  printf("[%s] [WARN]: ", getDate());
  SET_FOUR_BIT_COLOR(TXT_DEFAULT);
  printf("%s\n", message);
}

void error(char* message) {
  SET_FOUR_BIT_COLOR(TXT_RED);
  printf("[%s] [ERROR]: ", getDate());
  SET_FOUR_BIT_COLOR(TXT_DEFAULT);
  printf("%s\n", message);
}

#endif