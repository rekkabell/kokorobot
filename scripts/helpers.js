String.prototype.capitalize = function () {
  return this.charAt(0).toUpperCase() + this.slice(1).toLowerCase()
}

String.prototype.toUrl = function () {
  return this.toLowerCase().replace(/ /g, '+').replace(/[^0-9a-z\+]/gi, '').trim()
}

String.prototype.to_path = function () {
  return this.toLowerCase().replace(/ /g, '.').replace(/[^0-9a-z\.]/gi, '').trim()
}

String.prototype.to_markup = function () {
  html = this
  html = html.replace(/{_/g, '<i>').replace(/_}/g, '</i>')
  html = html.replace(/{\*/g, '<b>').replace(/\*}/g, '</b>')
  html = html.replace(/{\#/g, "<code class='inline'>").replace(/\#}/g, '</code>')

  var parts = html.split('{{')
  for (id in parts) {
    var part = parts[id]
    if (part.indexOf('}}') == -1) { continue }
    var content = part.split('}}')[0]
    var target = content.indexOf('|') > -1 ? content.split('|')[1] : content
    var name = content.indexOf('|') > -1 ? content.split('|')[0] : content
    var external = (target.indexOf('https:') > -1 || target.indexOf('http:') > -1 || target.indexOf('dat:') > -1)
    html = html.replace(`{{${content}}}`, external ? `<a href='${target}' class='external' target='_blank'>${name}</a>` : `<a class='local' href='#${target.toUrl()}'>${name}</a>`)
  }
  return html
}
