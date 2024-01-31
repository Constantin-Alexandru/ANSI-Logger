const ansi_lib = require("ansi-lib");

function info(message) {
  ansi_lib.SET_FOUR_BIT_COLOR(ansi_lib.COLOR_4_BIT.TXT_BLUE);
  ansi_lib.SET_EFFECT(ansi_lib.TEXT_EFFECTS.BOLD);
  process.stdout.write(`${new Date().toLocaleString()} [INFO]: `);
  ansi_lib.SET_EFFECT(ansi_lib.TEXT_EFFECTS.BOLD_RESET);
  ansi_lib.SET_FOUR_BIT_COLOR(ansi_lib.COLOR_4_BIT.TXT_DEFAULT);
  console.log(message);
}

function log(message) {
  info(message);
}

function success(message) {
  ansi_lib.SET_FOUR_BIT_COLOR(ansi_lib.COLOR_4_BIT.TXT_GREEN);
  ansi_lib.SET_EFFECT(ansi_lib.TEXT_EFFECTS.BOLD);
  process.stdout.write(`${new Date().toLocaleString()} [SUCCESS]: `);
  ansi_lib.SET_EFFECT(ansi_lib.TEXT_EFFECTS.BOLD_RESET);
  process.stdout.write(message);
  ansi_lib.SET_FOUR_BIT_COLOR(ansi_lib.COLOR_4_BIT.TXT_DEFAULT);
  console.log();
}

function warn(message) {
  ansi_lib.SET_FOUR_BIT_COLOR(ansi_lib.COLOR_4_BIT.TXT_YELLOW);
  ansi_lib.SET_EFFECT(ansi_lib.TEXT_EFFECTS.BOLD);
  process.stdout.write(`${new Date().toLocaleString()} [WARN]: `);
  ansi_lib.SET_EFFECT(ansi_lib.TEXT_EFFECTS.BOLD_RESET);
  process.stdout.write(message);
  ansi_lib.SET_FOUR_BIT_COLOR(ansi_lib.COLOR_4_BIT.TXT_DEFAULT);
  console.log();
}

function error(message) {
  ansi_lib.SET_FOUR_BIT_COLOR(ansi_lib.COLOR_4_BIT.TXT_RED);
  ansi_lib.SET_EFFECT(ansi_lib.TEXT_EFFECTS.BOLD);
  process.stdout.write(`${new Date().toLocaleString()} [RED]: `);
  ansi_lib.SET_EFFECT(ansi_lib.TEXT_EFFECTS.BOLD_RESET);
  process.stdout.write(message);
  ansi_lib.SET_FOUR_BIT_COLOR(ansi_lib.COLOR_4_BIT.TXT_DEFAULT);
  console.log();
}

exports.info = info;
exports.log = log;
exports.success = success;
exports.warn = warn;
exports.error = error;
