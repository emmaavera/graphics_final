/*====================== display.c ========================
Contains functions for basic manipulation of a screen 
represented as a 2 dimensional array of colors.

A color is an ordered triple of ints, with each value standing
for red, green and blue respectively
==================================================*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "ml6.h"
#include "display.h"

void clear_zbuffer(zbuffer zbuf){
    int i, j;

  for (i = 0; i < XRES; i++) 
    for (j = 0; j < YRES; j++)
      zbuf[i][j] = 0;
  }

color change_color( int i ) {
  
  color c;
  i = i % 7;

  switch( i ) {
    
  case 0:
    c.red = 255;
    c.green = 255; 
    c.blue = 255;
    break;
  case 1:
    c.red = 255;
    c.green = 0; 
    c.blue = 0;
    break;
  case 2:
    c.red = 0;
    c.green = 255; 
    c.blue = 0;
    break;
  case 3:
    c.red = 0;
    c.green = 0; 
    c.blue = 255;
    break;
  case 4:
    c.red = 255;
    c.green = 255; 
    c.blue = 0;
    break;
  case 5:
    c.red = 255;
    c.green = 0; 
    c.blue = 255;
    break;
  case 6:
    c.red = 0;
    c.green = 255; 
    c.blue = 255;
    break;
  }
  return c;
}

/*======== void plot() ==========
Inputs:   screen s
         color c
         int x
         int y 
Returns: 
Sets the color at pixel x, y to the color represented by c
Note that s[0][0] will be the upper left hand corner 
of the screen. 
If you wish to change this behavior, you can change the indicies
of s that get set. For example, using s[x][YRES-1-y] will have
pixel 0, 0 located at the lower left corner of the screen

02/12/10 09:09:00
jdyrlandweaver
====================*/
/*
void plot( screen s, color c, int x, int y) {
  int newy = YRES - 1 - y;
  if ( x >= 0 && x < XRES && newy >=0 && newy < YRES )
    s[x][newy] = c;
}*/

//plot with z buffer
void plot( screen s, color c, zbuffer zbuf, int x, int y, double z) {
  int newy = YRES - 1 - y;
  if ( x >= 0 && x < XRES && newy >=0 && newy < YRES ){
    if (z > zbuf[x][newy]){
      s[x][newy] = c;
      zbuf[x][newy] = z;
      printf("zbuffer executed\n");
    }
  }
}



/*======== void clear_screen() ==========
Inputs:   screen s  
Returns: 
Sets every color in screen s to black

02/12/10 09:13:40
jdyrlandweaver
====================*/
void clear_screen( screen s ) {

  int x, y;
  color c;

  c.red = 0;
  c.green = 0;
  c.blue = 0;

  for ( y=0; y < YRES; y++ )
    for ( x=0; x < XRES; x++)      
      s[x][y] = c;
}

/*======== void save_ppm() ==========
Inputs:   screen s
         char *file 
Returns: 
Saves screen s as a valid ppm file using the
settings in ml6.h

02/12/10 09:14:07
jdyrlandweaver
====================*/
void save_ppm( screen s, char *file) {

  int x, y;
  FILE *f;
  
  f = fopen(file, "w");
  fprintf(f, "P3\n%d %d\n%d\n", XRES, YRES, MAX_COLOR);
  for ( y=0; y < YRES; y++ ) {
    for ( x=0; x < XRES; x++) 
      
      fprintf(f, "%d %d %d ", s[x][y].red, s[x][y].green, s[x][y].blue);
    fprintf(f, "\n");
  }
  fclose(f);
}
 
/*======== void save_extension() ==========
Inputs:   screen s
         char *file 
Returns: 
Saves the screen stored in s to the filename represented
by file. 
If the extension for file is an image format supported
by the "convert" command, the image will be saved in
that format.

02/12/10 09:14:46
jdyrlandweaver
====================*/
void save_extension( screen s, char *file) {
  
  int x, y;
  FILE *f;
  char line[256];

  sprintf(line, "convert - %s", file);

  f = popen(line, "w");
  fprintf(f, "P3\n%d %d\n%d\n", XRES, YRES, MAX_COLOR);
  for ( y=0; y < YRES; y++ ) {
    for ( x=0; x < XRES; x++) 
      
      fprintf(f, "%d %d %d ", s[x][y].red, s[x][y].green, s[x][y].blue);
    fprintf(f, "\n");
  }
  pclose(f);
}


/*======== void display() ==========
Inputs:   screen s 
Returns: 
Will display the screen s on your monitor

02/12/10 09:16:30
jdyrlandweaver
====================*/
void display( screen s) {
   int x, i;
  char *fname = ".tmp.png";
  save_extension(s, fname);
  i = fork();
  if (i == 0) {
    execlp("display", "display", fname, NULL);
  }
  else {
    wait(&x);
    remove( fname );
  }
  /* For some reason, this refuses to run correctly
     on some systems. Most likely a strange imagemagick
     install issue. 
     Above is a workaroudn for now.
  int x, y;
  FILE *f;

  f = popen("display", "w");

  fprintf(f, "P3\n%d %d\n%d\n", XRES, YRES, MAX_COLOR);
  for ( y=0; y < YRES; y++ ) {
    for ( x=0; x < XRES; x++) 
      
      fprintf(f, "%d %d %d ", s[x][y].red, s[x][y].green, s[x][y].blue);
    fprintf(f, "\n");
  }
  pclose(f);
  */
}

