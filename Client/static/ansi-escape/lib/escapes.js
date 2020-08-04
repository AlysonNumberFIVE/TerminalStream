// https://en.wikipedia.org/wiki/ANSI_escape_code
var ESC = '\x1b['
var escapes = [
  {
    code: 'A',
    name: ['cursorUp', 'cuu', 'up'],
  },
  {
    code: 'B',
    name: ['cursorDown', 'cud', 'down'],
  },
  {
    code: 'C',
    name: ['cursorForward', 'cuf', 'forward'],
  },
  {
    code: 'D',
    name: ['cub', 'cursorBackward', 'back'],
  },
  {
    code: 'E',
    name: ['cursorNextLine', 'cnl'],
  },
  {
    code: 'F',
    name: ['cursorPreviousLine', 'cpl'],
  },
  {
    code: 'G',
    name: ['cursorColumn', 'cha', 'col'],
  },
  {
    code: 'H',
    name: ['cursorPosition', 'cup'],
  },
  {
    code: 'J',
    name: ['eraseDisplay', 'ed'],
  },
  {
    code: 'J',
    name: 'eraseDisplayEnd',
    args: [0],
  },
  {
    code: 'J',
    name: 'eraseDisplayStart',
    args: [1],
  },
  {
    code: 'J',
    name: 'eraseDisplayEntire',
    args: [2],
  },
  {
    code: 'K',
    name: ['eraseLine', 'el'],
  },
  {
    code: 'K',
    name: 'eraseLineEnd',
    args: [0],
  },
  {
    code: 'K',
    name: 'eraseLineStart',
    args: [1],
  },
  {
    code: 'K',
    name: 'eraseLineEntire',
    args: [2],
  },
  {
    code: 'S',
    name: ['scrollUp', 'su'],
  },
  {
    code: 'T',
    name: ['scrollDown', 'sd'],
  },
  {
    code: 'f',
    name: ['cursorHVPosition', 'hvp'],
    description: 'Horizontal and Vertical Position',
  },
  {
    code: 's',
    name: ['saveCursorPosition', 'saveCursor', 'scp'],
  },
  {
    code: 'u',
    name: ['restoreCursorPosition', 'restoreCursor', 'rcp'],
  },
  {
    code: '?25l',
    name: ['hideCursor', 'hide'],
  },
  {
    code: '?25h',
    name: ['showCursor', 'show'],
  },
  {
    code: 'm',
    name: ['selectGraphicRendition', 'sgr'],
    fn: function (n) {
      // https://en.wikipedia.org/wiki/ANSI_escape_code#graphics
      n = n == null ? 0 : n
      return function (str) {
        str = str || ''
        return n === 0
          ? str + ESC + n + 'm'
          : ESC + n + 'm' + str
      }
    },
  },
]
escapes.forEach(function (escape) {
  var fn = escape.fn || function (n, m) {
    n = n == null ? '' : n
    m = m == null ? '' : ';' + m
    return function (str) {
      str = str || ''
      return ESC + n + m + escape.code + str
    }
  }
  if (escape.args) {
    fn = fn.apply.bind(fn, null, escape.args)
  }
  [].concat(escape.name).forEach(function (name) {
    exports[name] = fn
  })
})

