// https://en.wikipedia.org/wiki/ANSI_escape_code
var ESC = '\x1b['
var CODE = {
  bold: 1,
  dim: 2,
  italic: 3,
  underline: 4,
  blink: 5,
  inverse: 7,
  hidden: 8,
  strikethrough: 9,

  black: 30,
  red: 31,
  green: 32,
  yellow: 33,
  blue: 34,
  magenta: 35,
  cyan: 36,
  white: 37,

  bgBlack: 40,
  bgRed: 41,
  bgGreen: 42,
  bgYellow: 43,
  bgBlue: 44,
  bgMagenta: 45,
  bgCyan: 46,
  bgWhite: 47,
}
var CLOSE = ESC + '0m'
Object.keys(CODE).forEach(function (name) {
  exports[name] = function () {
    return function (str) {
      str = str || ''
      return ESC + CODE[name] + 'm' + str + CLOSE
    }
  }
})
