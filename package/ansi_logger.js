const ansi_lib = require("ansi-lib");

/**
 * Defining properties to get the function information
 */
Object.defineProperty(global, "__stack", {
  get: function () {
    var orig = Error.prepareStackTrace;
    Error.prepareStackTrace = function (_, stack) {
      return stack;
    };
    var err = new Error();
    Error.captureStackTrace(err, arguments.callee);
    var stack = err.stack;
    Error.prepareStackTrace = orig;
    return stack;
  },
});

Object.defineProperty(global, "__parent_line", {
  get: function () {
    return __stack[2].getLineNumber();
  },
});

Object.defineProperty(global, "__parent_function", {
  get: function () {
    return __stack[2].getFunctionName();
  },
});

Object.defineProperty(global, "__parent_file", {
  get: function () {
    return __stack[2].getFileName();
  },
});

const Colors = ansi_lib.Colors;
const Type = ansi_lib.Type;

/**
 * @typedef {Object} Logger
 * @property {string} name
 * @property {string} pattern
 */

/** @enum {number} */
const LogLevel = {
  DEBUG: 0,
  INFO: 1,
  LOG: 2,
  SUCCESS: 3,
  WARN: 4,
  ERROR: 5,
};

/**
 * @typedef {Object} LogEntry
 * @property {LogLevel} level
 * @property {string} msg
 */

/**
 * Creates a Logger object
 *
 * @param {string} name - The name of the logger
 * @param {string} pattern - The pattern for printing
 *
 * @returns {Logger}
 */
function create_logger(name, pattern) {
  return { name: name, pattern: pattern };
}

/**
 * Returns the string corresponding to the ANSI Code for the level color.
 *
 * @param {LogLevel | undefined} level - The level of the logging message
 * @returns {string}
 */
function getColorString(level) {
  switch (level) {
    case LogLevel.DEBUG:
      return ansi_lib.getColorString(Colors.TXT_MAGENTA, Type.COLOR);
    case LogLevel.INFO:
    case LogLevel.LOG:
      return ansi_lib.getColorString(Colors.TXT_BLUE, Type.COLOR);
    case LogLevel.SUCCESS:
      return ansi_lib.getColorString(Colors.TXT_GREEN, Type.COLOR);
    case LogLevel.WARN:
      return ansi_lib.getColorString(Colors.TXT_YELLOW, Type.COLOR);
    case LogLevel.ERROR:
      return ansi_lib.getColorString(Colors.TXT_RED, Type.COLOR);
    default:
      return ansi_lib.getColorString(Colors.TXT_WHITE, Type.COLOR);
  }
}

/**
 * Returns the string value of the level
 *
 * @param {LogLevel} level - The log level
 *
 * @returns {string}
 */
function getLogLevelString(level) {
  switch (level) {
    case LogLevel.DEBUG:
      return "DEBUG";
    case LogLevel.INFO:
    case LogLevel.LOG:
      return "INFO";
    case LogLevel.SUCCESS:
      return "SUCCESS";
    case LogLevel.WARN:
      return "WARN";
    case LogLevel.ERROR:
      return "ERROR";
    default:
      return "";
  }
}

/**
 * Prints the log message
 *
 * @param {Logger} logger - the logger to use
 * @param {LogEntry} entry - the entry to be printed
 */
function print_msg(logger, entry) {
  const log_color = getColorString(entry.level);
  const default_color = getColorString();
  const level_str = getLogLevelString(entry.level);
  const date = new Date();

  const message = pattern
    .replace("%l", `${log_color}${level_str}${default_color}`)
    .replace("%n", `${log_color}${logger.name}${default_color}`)
    .replace("%w", `${log_color}${date.getDay()}${default_color}`)
    .replace("%d", `${log_color}${date.getDate()}${default_color}`)
    .replace(
      "%m",
      `${log_color}\
${date.toLocaleString("default", { month: "long" })}${default_color}`,
    )
    .replace("%M", `${log_color}${date.getMonth()}${default_color}`)
    .replace("%y", `${log_color}${date.getFullYear()}${default_color}`)
    .replace("%h", `${log_color}${date.getHours()}${default_color}`)
    .replace("%H", `${log_color}${date.getHours() % 12}${default_color}`)
    .replace("%r", `${log_color}${date.getMinutes()}${default_color}`)
    .replace("%s", `${log_color}${date.getSeconds()}${default_color}`)
    .replace(
      "%u",
      `${log_color}${date.getHours() >= 12 ? "PM" : "AM"}${default_color}`,
    )
    .replace("%f", `${log_color}${__parent_file}${default_color}`)
    .replace("%i", `${log_color}${__parent_line}${default_color}`)
    .replace("%b", `${log_color}${__parent_function}${default_color}`)
    .replace("%c", `${default_color}${entry.msg}`);
}

/**
 * Prints the message with DEBUG log level
 *
 * @param {Logger} logger - The logger to use
 * @param {string} message - The message to print
 */
exports.DEBUG = function (logger, message) {
  print_msg(logger, { level: LogLevel.DEBUG, msg: message });
};

/**
 * Prints the message with INFO log level
 *
 * @param {Logger} logger - The logger to use
 * @param {string} message - The message to print
 */
exports.INFO = function (logger, message) {
  print_msg(logger, { level: LogLevel.INFO, msg: message });
};

/**
 * Prints the message with LOG log level
 *
 * @param {Logger} logger - The logger to use
 * @param {string} message - The message to print
 */
exports.LOG = function (logger, message) {
  print_msg(logger, { level: LogLevel.LOG, msg: message });
};

/**
 * Prints the message with SUCCESS log level
 *
 * @param {Logger} logger - The logger to use
 * @param {string} message - The message to print
 */
exports.SUCCESS = function (logger, message) {
  print_msg(logger, { level: LogLevel.SUCCESS, msg: message });
};

/**
 * Prints the message with WARN log level
 *
 * @param {Logger} logger - The logger to use
 * @param {string} message - The message to print
 */
exports.WARN = function (logger, message) {
  print_msg(logger, { level: LogLevel.WARN, msg: message });
};

/**
 * Prints the message with ERROR log level
 *
 * @param {Logger} logger - The logger to use
 * @param {string} message - The message to print
 */
exports.ERROR = function (logger, message) {
  print_msg(logger, { level: LogLevel.ERROR, msg: message });
};
