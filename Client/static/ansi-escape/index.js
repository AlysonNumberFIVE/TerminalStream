var util = require('util')

function CSI(escape) {
  this.escape = typeof escape === 'function' ? escape : function () {
    return util.format.apply(util, arguments)
  }
}

function defineEscape(name, creator) {
  Object.defineProperty(CSI.prototype, name, {
    get: function () {
      var self = this
      function csi() {
        return new CSI(formatter(self, creator.apply(null, arguments)))
      }
      csi.escape = formatter(this, creator())

      /* eslint-disable no-proto */
      csi.__proto__ = CSI.prototype
      return csi
    },
  })
}

function formatter(predecessor, escape) {
  return function () {
    return predecessor.escape(escape(
      util.format.apply(util, arguments)
    ))
  }
}

function defineEscapes(escapes) {
  Object.keys(escapes).forEach(function (name) {
    defineEscape(name, escapes[name])
  })
}

defineEscapes(require('./lib/escapes'))
defineEscapes(require('./lib/colors'))

exports = module.exports = new CSI()
exports.CSI = CSI
exports.defineEscape = defineEscape
exports.defineEscapes = defineEscapes

