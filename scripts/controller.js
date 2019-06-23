function Controller () {
  this.el = null
  this.database = null
  this.lightbox = new Lightbox()

  this.install = function (el = document.getElementById('main')) {
    this.el = el
    this.database = new Indental(DATABASE).parse()
    this.lightbox.install()
  }

  this.start = function () {
    this.load(window.document.location.hash == '' ? 'Home' : window.document.location.hash)
  }

  this.load = function (input = window.location.hash) {
    const target = input.to_url() === '' ? 'Home' : input.to_url()

    if (target === '') {
      window.history.replaceState(undefined, undefined, '#' + target)
    } else {
      window.location.hash = target.to_url()
    }

    console.info(`Loading ${target}.`)

    var content = this.database[target.toUpperCase()]

    this.el.className = 'loading'
    this.el.innerHTML = content ? `<page>${new Runic(content.LONG)}</page>` : `<page><p>Could not find page ${target}</p></page>`

    setTimeout(() => { this.lightbox.update() }, 500)

    setTimeout(() => {
      this.el.className = 'ready'
      window.scrollTo(0, 0)
    }, 200)
  }

  this.touch = function (target) {
    var link = target.getAttribute('href') ? target.getAttribute('href') : target.parentNode.getAttribute('href')

    if (!link) { return }
    if (link.substr(0, 1) != '#') { return }

    this.load(link.substr(1, link.length - 1))
  }

  document.addEventListener('mouseup', (e) => { this.touch(e.target); e.preventDefault() })
}

var detectBackOrForward = function (onBack, onForward) {
  hashHistory = [window.location.hash]
  historyLength = window.history.length

  return function () {
    var hash = window.location.hash; var length = window.history.length
    if (hashHistory.length && historyLength == length) {
      if (hashHistory[hashHistory.length - 2] == hash) {
        hashHistory = hashHistory.slice(0, -1)
        onBack()
      } else {
        hashHistory.push(hash)
        onForward()
      }
    } else {
      hashHistory.push(hash)
      historyLength = length
    }
  }
}

window.addEventListener('hashchange', detectBackOrForward(
  function () { console.log('back'); controller.load() },
  function () { console.log('forward'); controller.load() }
))
