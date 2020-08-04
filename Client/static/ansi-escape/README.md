# ansi-escape
ANSI escape codes for manipulating the terminal

[![version](https://img.shields.io/npm/v/ansi-escape.svg)](https://www.npmjs.org/package/ansi-escape)
[![status](https://travis-ci.org/zoubin/ansi-escape.svg?branch=master)](https://travis-ci.org/zoubin/ansi-escape)

## Usage

```javascript
var csi = require('ansi-escape')

console.log('1'.repeat(8))
console.log(
  csi
    // underline text
    .underline

    // red text
    .red

    // move cursor one line up
    .cursorUp

    // move cursor 2 cells forward
    .cursorForward(2)

    // the text to be escaped
    .escape('2'.repeat(4))
)

```

**Output**

![chain](example/chain.png)

## escape
Type: `Function`

Accept arguments like [util.format](https://nodejs.org/docs/latest/api/util.html#util_util_format_format).

```js
var csi = require('ansi-escape')

console.log(
  csi.escape(
    'Age: %d, Size: %j',
    10,
    { h: 180, w: 80 }
  )
)


```

**Output**

```
Age: 10, Size: {"h":180,"w":80}

```


## Cursors

### cursorUp(n = 1)

Alias: `cuu`, `up`

Moves the cursor `n` cells up.

### cursorDown(n = 1)

Alias: `cud`, `down`

Moves the cursor `n` cells down.

### cursorForward(n = 1)

Alias: `cuf`, `forward`

Moves the cursor `n` cells forward.

### cursorBackward(n = 1)

Alias: `cub`, `back`

Moves the cursor `n` cells backward.


### cursorColumn(n = 1)

Alias: `cha`, `col`

Moves the cursor to column `n`.

### cursorPosition(n = 1, m = 1)

Alias: `cup`

Moves the cursor to row `n`, column `m`.

### eraseDisplay(n = 0)

Sugar: `eraseDisplayEnd`, `eraseDisplayStart`, `eraseDisplayEntire`

Clears part of the screen.

* If `n` is 0 (or missing), clear from cursor to end of screen.
* If `n` is 1, clear from cursor to beginning of the screen.
* If `n` is 2, clear entire screen (and moves cursor to upper left on DOS ANSI.SYS).

### eraseLine(n = 0)

Sugar: `eraseLineEnd`, `eraseLineStart`, `eraseLineEntire`

Erases part of the line.

* If `n` is 0 (or missing), clear from cursor to the end of the line.
* If `n` is 1, clear from cursor to beginning of the line.
* If `n` is 2, clear entire line.

Cursor position does not change.

### scrollUp(n = 1)

Alias: `su`

Scroll whole page up by n (default 1) lines.
New lines are added at the bottom. 

### scrollDown(n = 1)

Alias: `sd`

Scroll whole page down by n (default 1) lines.
New lines are added at the top.

### saveCursorPosition

Alias: `scp`, `saveCursor`

Saves the cursor position.

### restoreCursorPosition

Alias: `rcp`, `restoreCursor`

Restores the cursor position.

### hideCursor

Alias: `hide`

Hides the cursor.

### showCursor

Alias: `show`

Shows the cursor.

## Styles

### Modifiers

* bold
* dim
* italic
* underline
* blink
* inverse
* hidden
* strikethrough

### Colors

* black
* red
* green
* yellow
* blue
* magenta
* cyan
* white

### Background colors

* bgBlack
* bgRed
* bgGreen
* bgYellow
* bgBlue
* bgMagenta
* bgCyan
* bgWhite

