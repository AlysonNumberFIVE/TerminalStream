<!-- b3fdd11 1452158919000 -->

* [[`b3fdd11`](https://github.com/zoubin/ansi-escape/commit/b3fdd11)] Format with util.format.

    
    * Use `require('util').format` to format escaped strings.
    * Fix chaining bug:
    ```js
    var cf = csi.cursorForward;
    cf(2).escape('forward 2 columns')
    
    // This had been forwarding 2 columns
    cf(3).escape('forward 3 columns')
    
    ```

## [v1.0.1](https://github.com/zoubin/ansi-escape/commit/5973039) (2015-11-23)

* [[`7adaaf6`](https://github.com/zoubin/ansi-escape/commit/7adaaf6)] Update readme

* [[`b17353c`](https://github.com/zoubin/ansi-escape/commit/b17353c)] Remove npm badge

* [[`e19ba23`](https://github.com/zoubin/ansi-escape/commit/e19ba23)] remove unused gulpfile.js

## [v1.0.0](https://github.com/zoubin/ansi-escape/commit/23c9afb) (2015-11-23)

* [[`6188fc1`](https://github.com/zoubin/ansi-escape/commit/6188fc1)] simplify dev

* [[`6252f81`](https://github.com/zoubin/ansi-escape/commit/6252f81)] Rename api

* [[`1f814c8`](https://github.com/zoubin/ansi-escape/commit/1f814c8)] Not Done

* [[`04549f6`](https://github.com/zoubin/ansi-escape/commit/04549f6)] Initial commit

