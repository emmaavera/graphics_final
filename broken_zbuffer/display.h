#ifndef DISPLAY_H
#define DISPLAY_H

void clear_zbuffer(zbuffer zbuf);
//void plot( screen s, color c, int x, int y);
void plot( screen s, color c, zbuffer zbuf, int x, int y, double z);
void clear_screen( screen s);
void save_ppm( screen s, char *file);
void save_extension( screen s, char *file);
void display( screen s);

color change_color( int i );
#endif
