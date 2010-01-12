#include "FileUtils.h"
#include <stdio.h>
#include <stdlib.h>

void* load_ppm(const char* fn, int &width, int &height)
{
  FILE* f = fopen(fn, "rb");
  if (!f) exit(-1);

  char magic[3];
  fread(magic, 1, 2, f);
  if (magic[0]!='P' || magic[1]!='6') {
    printf("Error reading PPM file: %s\n", fn);
    getchar(); // Let's read the error
    exit(-1);
  }

  char c;
  do
  {
    char tmp[256];
    fscanf(f, "%[^\n]", tmp);	
    fscanf(f, "%c", &c);
  }
  while (c == '#');
  ungetc(c,f);

  int max;
  fscanf(f, "%u\n%u\n%u\n", &width, &height, &max);

  void* rgb = malloc(width*height*3);
  fread(rgb, 3, width*height, f);
  fclose(f);

  return rgb;
}