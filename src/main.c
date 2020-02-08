#include <dirent.h> 
#include <ctype.h>
#include <stdio.h> 
#include <string.h>

#define STR_BUF_LEN 64

// int chapters[] = {11};

char *html_head = "<!DOCTYPE html><html lang='en'><head><meta charset='utf-8'><meta name='description' content='Kokorobot is the virtual playground of cartoonist Rekka Bellum.'><meta name='viewport' content='width=device-width, initial-scale=1.0'><meta name='twitter:card' content='summary'><meta name='twitter:site' content='@RekkaBell'><meta name='twitter:title' content='Kokorobot'><meta name='twitter:description' content='Kokorobot is the virtual playground of cartoonist Rekka Bellum.'><meta name='twitter:creator' content='@RekkaBell'><meta name='twitter:image' content='http://kokorobot.ca/media/services/icon.jpg'><meta property='og:title' content='kokorobot'><meta property='og:type' content='article'><meta property='og:url' content='http://kokorobot.ca/'><meta property='og:image' content='https://kokorobot.ca/media/services/icon.jpg'><meta property='og:description' content='Kokorobot is the virtual playground of cartoonist Rekka Bellum.'><meta property='og:site_name' content='kokorobot'><link rel='icon' type='image/x-icon' href='../media/services/favicon.ico'><link rel='icon' type='image/png' href='../media/services/icon.jpg'><link rel='apple-touch-icon' href='../media/services/apple-touch-icon.png' /><title>Kokorobot — %.*s</title><link rel='stylesheet' type='text/css' href='../links/main.css'></head><body>";

char *html_header = "<header><h1><a href='home.html'>Rekka Bellum</a></h1><h2><a href='home.html'>⬟</a></h2><ul><li><a class='about' href='about.html'>About</a></li><li><a class='projects' href='projects.html'>Projects</a></li><li><a class='illustration' href='illustration.html'>Illustration</a></li><li><a class='stories' href='stories.html'>Stories</a></li><li><a class='store' href='store.html'>Store</a></li><li><a class='characters' href='characters.html'>Characters</a></li><li><a class='notes' href='notes.html'>Notes</a></li></ul></header>";

char *html_footer = "<footer><div class='footer_item footer_left'><a href='about.html' class='about'>Rekka Bellum </a> © 2020</div><div class='footer_item footer_right'><div class='footer_item_sub-item'><a href='https://twitter.com/RekkaBell' class='footer_social footer_social_twitter' target='_blank'></a><a href='https://www.patreon.com/100' class='footer_social footer_social_patreon' target='_blank'></a><a href='http://webring.xxiivv.com/#random' class='footer_social footer_social_webring' target='_blank'></a><a href='http://100r.co' class='footer_social footer_social_100r' target='_blank'></a><a href='https://github.com/rekkabell' class='footer_social footer_social_github' target='_blank'></a><a href='https://merveilles.town/@rek' class='footer_social footer_social_mastodon' target='_blank'></a></div></div></footer></body></html>";

void build_page(char *name) {
  if(strcmp(name,".") == 0){ return; }
  if(strcmp(name,"..") == 0){ return; }

  printf("Building %s\n", name);

  char *filename = name;
  char filepath[STR_BUF_LEN];
  snprintf(filepath, STR_BUF_LEN, "../site/%sl", filename);
  FILE *f = fopen(filepath, "w");

  char incpath[STR_BUF_LEN];
  snprintf(incpath, STR_BUF_LEN, "inc/%s", filename);

  fprintf(f, html_head, (int)(strlen(filename)-4), filename);
  fputs(html_header, f);

    fprintf(f, "<main class='%.*s'>", (int)(strlen(filename)-4), filename);
    char buffer[4096];
    FILE *fp = fopen(incpath, "r");
    if(fp == NULL){ return; }

    for (;;) {
      size_t sz = fread(buffer, 1, sizeof(buffer), fp);
      if (sz) {
        fwrite(buffer, 1, sz, f);
      } else if (feof(fp) || ferror(fp)) {
        break;
      }
    }   
    fclose(fp);
    fputs("</main>", f);

  fputs(html_footer, f);

  fclose(f);
}

int main(void) {
  DIR *d = opendir("./inc");
  struct dirent *dir;
  if (!d) { return (0); }

  while ((dir = readdir(d)) != NULL) {
    build_page(dir->d_name);
  }
  closedir(d);
  
  return (0);
}