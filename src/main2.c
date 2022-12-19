#include <dirent.h> 
#include <ctype.h>
#include <stdio.h> 
#include <string.h>

#define STR_BUF_LEN 64

int   ssin(char *s, char *ss) { int a = 0, b = 0; while(s[a]) { if(s[a] == ss[b]) { if(!ss[b + 1]) return a - b; b++; } else b = 0; a++; } return -1; } /* string substring index */
char *scsw(char *s, char a, char b) { int i = 0; char c; while((c = s[i])) s[i++] = c == a ? b : c; return s; }
char *scpy(char *src, char *dst, int len) { int i = 0; while((dst[i] = src[i]) && i < len - 2) i++; dst[i + 1] = '\0'; return dst; }

char *html_head = "<!DOCTYPE html><html lang='en'><head><meta charset='utf-8'><meta name='description' content='Kokorobot is the virtual playground of cartoonist Rek Bellum.'><meta name='viewport' content='width=device-width, initial-scale=1.0'><meta name='twitter:card' content='summary'><meta name='twitter:site' content='@hundredrabbitss'><meta name='twitter:title' content='Kokorobot'><meta name='twitter:description' content='Kokorobot is the virtual playground of cartoonist Rek Bellum.'><meta name='twitter:creator' content='@hundredrabbits'><meta name='twitter:image' content='http://kokorobot.ca/media/services/icon.jpg'><meta property='og:title' content='kokorobot'><meta property='og:type' content='article'><meta property='og:url' content='http://kokorobot.ca/'><meta property='og:image' content='https://kokorobot.ca/media/services/icon.jpg'><meta property='og:description' content='Kokorobot is the virtual playground of cartoonist Rek Bellum.'><meta property='og:site_name' content='kokorobot'><link rel='icon' type='image/x-icon' href='../media/services/favicon.ico'><link rel='icon' type='image/png' href='../media/services/icon.jpg'><link rel='apple-touch-icon' href='../media/services/apple-touch-icon.png' /><title>Kokorobot — %.*s</title><link rel='stylesheet' type='text/css' href='../links/main.css'></head><body>";

char *html_header = "<header><h1><a href='home.html'>Rek Bellum</a></h1><h2><a href='home.html'>⬟</a></h2><ul><li><a class='about' href='about.html'>About</a></li><li><a class='projects' href='projects.html'>Projects</a></li><li><a class='illustration' href='illustration.html'>Illustration</a></li><li><a class='stories' href='stories.html'>Stories</a></li><li><a class='store' href='store.html'>Store</a></li><li><a class='characters' href='characters.html'>Characters</a></li><li><a class='notes' href='notes.html'>Other</a></li></ul></header>";

char *html_footer = "<footer><p><a href='about.html'>Rek Bellum</a> © 2009-2022 <a href='https://creativecommons.org/licenses/by-nc-sa/4.0/'>BY-NC-SA 4.0</a> <a href='http://webring.xxiivv.com/#random'>[Webring]</a> <a href='https://merveilles.town/@rek'>[Mastodon]</a> <a href='politics.html'>[Politics]</a> <a href='index.html'>[Meta]</a></p></footer></body></html>";

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

void
build_index(void){
  FILE *f;
  f = fopen("inc/index.htm", "w");
	fputs("<ul class='col3'>", f);
	DIR *d = opendir("./inc");
  struct dirent *dir;
  while ((dir = readdir(d)) != NULL) {
    char filepath[64], filename[64];
		if(dir->d_name[0] != '.')
			fprintf(f, "<li><a href='%sl'>%s</a></li>", scpy(dir->d_name, filepath, 64), scsw(scpy(dir->d_name, filename, ssin(dir->d_name, ".htm") + 1), '_', ' '));
  }
	fputs("</ul>", f);
  closedir(d);
  fclose(f);
}

int main(void) {
  DIR *d = opendir("./inc");
  struct dirent *dir;
  if (!d) { return (0); }

  build_index();
  while ((dir = readdir(d)) != NULL) {
    build_page(dir->d_name);
  }
  closedir(d);
  
  return (0);
}