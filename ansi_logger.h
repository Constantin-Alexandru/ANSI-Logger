#ifndef ANSI_LOGGER_H
#define ANSI_LOGGER_H

#include <errno.h>
#include <stdio.h>
#include <time.h>

#include "ANSI-Library/ansi_lib.h"

static char* getDate() {
  const int DATE_STRING_LENGTH = 11;
  char* date_string = malloc(DATE_STRING_LENGTH);

  time_t date = time(NULL);
  struct tm* local_time = localtime(&date);

  if (!strftime(date_string, DATE_STRING_LENGTH, "%d/%m/%Y", local_time)) {
    printf("ERROR: %s", strerror(errno));
    free(date_string);
    return NULL;
  }

  return date_string;
}

void info(char* message) {
  char* date = getDate();
  SET_FOUR_BIT_COLOR(TXT_BLUE);
  SET_EFFECT(BOLD);
  printf("[%s] [INFO]: ", date);
  SET_EFFECT(BOLD_RESET);
  SET_FOUR_BIT_COLOR(TXT_DEFAULT);
  printf("%s\n", message);
  free(date);
}

void log(char* message) { info(message); }

void success(char* message) {
  char* date = getDate();
  SET_FOUR_BIT_COLOR(TXT_GREEN);
  SET_EFFECT(BOLD);
  printf("[%s] [SUCCESS]: ", date);
  SET_EFFECT(BOLD_RESET);
  printf("%s\n", message);
  SET_FOUR_BIT_COLOR(TXT_DEFAULT);
  free(date);
}

void warn(char* message) {
  char* date = getDate();
  SET_FOUR_BIT_COLOR(TXT_YELLOW);
  SET_EFFECT(BOLD);
  printf("[%s] [WARN]: ", date);
  SET_EFFECT(BOLD_RESET);
  printf("%s\n", message);
  SET_FOUR_BIT_COLOR(TXT_DEFAULT);
  free(date);
}

void error(char* message) {
  char* date = getDate();
  SET_FOUR_BIT_COLOR(TXT_RED);
  SET_EFFECT(BOLD);
  printf("[%s] [ERROR]: ", date);
  SET_EFFECT(BOLD_RESET);
  printf("%s\n", message);
  SET_FOUR_BIT_COLOR(TXT_DEFAULT);
  free(date);
}

#endif