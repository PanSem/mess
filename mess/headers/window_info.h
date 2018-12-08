#ifndef WINDOW_INFO_H
#define WINDOW_INFO_H

//Save cursor's position

struct cursorCoor {
  int x;
  int y;
};

//Save columns of the window and rows of the file

struct edges {
  int endFile;
  char* filename;
};

#endif
