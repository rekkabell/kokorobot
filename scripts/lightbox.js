function Lightbox () {
  this.el = document.createElement('div')
  this.el.id = 'lightbox'
  this.image = document.createElement('img')
  this.els = null

  this.install = function (host = document.getElementById('lightbox')) {
    this.el = host
    this.el.addEventListener('click', controller.lightbox.hide, false)
    this.el.appendChild(this.image)
  }

  this.update = function () {
    var els = document.getElementsByClassName('lightbox')
    console.log(`Binding ${els.length} elements.`)
    for (var i = 0; i < els.length; i++) {
      els[i].addEventListener('click', controller.lightbox.show, false)
    }
  }

  this.show = function (e) {
    var target = e.target
    if (!target) { return }

    var path = target.src.replace('.jpg', '.full.jpg')
    console.info(`Loading lightbox ${path}`)
    controller.lightbox.el.className = 'active'
    controller.lightbox.image.src = path
  }

  this.hide = function () {
    controller.lightbox.el.className = ''
  }
}
