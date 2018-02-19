function Lightbox()
{
  this.el = document.createElement('div'); 
  this.el.id = "lightbox"
  this.image = document.createElement('img'); 
  this.els = null;

  this.start = function()
  {
    this.els = document.getElementsByClassName("lightbox");
    this.el.appendChild(this.image)
    document.body.appendChild(this.el)

    this.el.addEventListener('click', lightbox.hide, false);
    for (var i = 0; i < this.els.length; i++) {
      this.els[i].addEventListener('click', lightbox.show, false);
    }
  }

  this.show = function(e)
  {
    var full_path = e.target.src.replace(".jpg",".full.jpg");
    lightbox.el.className = "active"
    lightbox.image.src = full_path;
  }

  this.hide = function()
  {
    lightbox.el.className = ""
  }
}