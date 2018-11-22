#include <windows.h>
#include <conio.h>
#include <stdio.h>
#include <unistd.h>

//Key values in cmd

enum sn {
  ARROW_UP = 72,
  ARROW_DOWN = 80,
  ARROW_RIGHT = 77,
  ARROW_LEFT = 75,
  ENTER = 13,
  SPACE = 32
};

//Save cursor's position

struct cursorCoor {
  int x;
  int y;
};

struct cursorCoor cur;

//Save columns of the window and rows of the file

struct edges {
  int x;
  int endFile;
};

struct edges edg;

struct info {
  char* filename;
};

struct info in;

/* Get window size */

COORD getWindowSize() {
  CONSOLE_SCREEN_BUFFER_INFO csbi;
  int columns, rows;

  //Calculate the columns and rows of the window

  GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
  columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
  rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;

  COORD coor = {columns, rows};
  return coor;
}

/* Clear */

void cls() {
   HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
   COORD coordScreen = {0, 0};    // home for the cursor
   DWORD cCharsWritten;
   CONSOLE_SCREEN_BUFFER_INFO csbi;
   DWORD dwConSize;

   // Get the number of character cells in the current buffer.

   if(!GetConsoleScreenBufferInfo( hConsole, &csbi )) {
      return;
   }

   dwConSize = csbi.dwSize.X * csbi.dwSize.Y;

   // Fill the entire screen with blanks.

   if(!FillConsoleOutputCharacter(hConsole, (TCHAR) ' ', dwConSize, coordScreen, &cCharsWritten)) {
      return;
   }

   // Get the current text attribute.

   if(!GetConsoleScreenBufferInfo(hConsole, &csbi)) {
      return;
   }

   // Set the buffer's attributes accordingly.

   if(!FillConsoleOutputAttribute(hConsole, csbi.wAttributes, dwConSize, coordScreen, &cCharsWritten)) {
      return;
   }

   // Put the cursor at its home coordinates.

   SetConsoleCursorPosition(hConsole, coordScreen);
}

/* Implementation of getline for windows */

size_t getline(char **lineptr, size_t *n, FILE *stream) {
    char *bufptr = NULL;
    char *p = bufptr;
    size_t size;
    int c;

    //If error return

    if (lineptr == NULL) {
        return -1;
    }
    if (stream == NULL) {
        return -1;
    }
    if (n == NULL) {
        return -1;
    }
    bufptr = *lineptr;
    size = *n;

    //Get first char in file

    c = fgetc(stream);
    if (c == EOF) {
        return -1;
    }

    //Allocate 128 for the line

    if (bufptr == NULL) {
        bufptr = malloc(128);
        if (bufptr == NULL) {
            return -1;
        }
        size = 128;
    }

    p = bufptr; //Keep track of the pointer's start

    while(c != EOF) {
        if ((p - bufptr) > (size - 1)) {    //If line is bigger than allocate space,
            size = size + 128;             //allocate 128 more bytes
            bufptr = realloc(bufptr, size);
            if (bufptr == NULL) {
                return -1;
            }
        }
        *p++ = c; //Take next char

        //If new line break

        if (c == '\n') {
            break;
        }
        c = fgetc(stream);
    }

    //Return the start of the pointer and line's size

    *p++ = '\0';
    *lineptr = bufptr;
    *n = size;

    //Return the number of bytes that have been read

    return p - bufptr - 1;
}

/* Take cursor's the coordinates and save them in coord */

void goToXY(int x, int y) {
  COORD coord;
  coord.X = x;
  coord.Y = y;
  SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void statusBar() {
  if(cur.y>edg.endFile+1) {
    return;
  }

  char a[5];

  itoa(edg.endFile, a, 4);

  cur.x = 0;
  cur.y = edg.endFile+1;

  goToXY(cur.x, cur.y);
  printf("[Filename : %s] - lines : %d", in.filename, edg.endFile);
  goToXY(cur.x, --cur.y);
}

/* Init cursor and window size */

void initCursorCoor() {
  COORD coor = getWindowSize();

  cur.x = 0;
  cur.y = 0;

  edg.x = coor.X;
  edg.endFile = 0;

  in.filename = NULL;
}

/* Read key */

void readKey() {
  int c;
  c=getch();

  switch(c) {
    case 'q': //Exit
      cls();
      exit(0);
      break;
    case ARROW_DOWN: //One line down
      if(cur.y==edg.endFile) { //If end of file have been reached stop
        statusBar();
        break;
      }
      goToXY(cur.x, ++cur.y);
      break;
    case ARROW_UP: //One line up
      if(cur.y==0) { //If on top stop
        break;
      }
      goToXY(cur.x, --cur.y);
      break;
    case ARROW_RIGHT: //One char to the right
      if(cur.x==edg.x-1) { //If right edge reached stop
        break;
      }
      goToXY(++cur.x, cur.y);
      break;
    case ARROW_LEFT: //One char left
      if(cur.x==0) { //If left edge reached stop
        break;
      }
      goToXY(--cur.x, cur.y);
      break;
    case 's':
    //TODO:Save in txt
      break;
    case ENTER: //Go to the or the start of the file
      if(cur.y==edg.endFile) {
        cur.x = 0;
        cur.y = 0;
        goToXY(cur.x, cur.y);
      }else{
        cur.y = edg.endFile;
        goToXY(cur.x, cur.y);
      }
      break;
    case SPACE: //Go 50 lines forward
      if(cur.y!=edg.endFile) {
        if(cur.y+50<=edg.endFile) {
          cur.y+=50;
          goToXY(cur.x, cur.y);
        }else{
        cur.y+=(edg.endFile-cur.y);
        goToXY(cur.x, cur.y);
        }
      }
      break;
  }
}

/* Display file */

void displayFile(char* file) {
  //Init file
  FILE * fp;
  char * line = NULL;
  size_t len = 0;
  ssize_t read;

  in.filename = malloc(sizeof(file));
  in.filename = file;

  goToXY(0, 0); //Go to start

  fp = fopen(file, "r"); //Open file

  if (fp == NULL)
      exit(EXIT_FAILURE);

  //Read line by line and display the file

  while ((read = getline(&line, &len, fp)) != -1) {
      write(STDOUT_FILENO, line, read);
      edg.endFile++; //Keep track of the size of the file
  }

  fclose(fp);
  if (line)
      free(line);

  goToXY(0, 0); //Go to start
}

/* Check if piped */

int checkIfPiped() {
  char ch;

  cls(); //Clear console

  //If piped read char by char and display it

  if(!isatty(STDIN_FILENO)) {
    while(read(STDIN_FILENO, &ch, 1) > 0) {
      write(STDOUT_FILENO, &ch, 1);
      if(ch=='\n') {
        edg.endFile++; //Keep track of the size of the file
      }
    }
    goToXY(0, 0); //Got to start
    return 0;
  }else{
    return -1; //If not piped return -1
  }
}

int main(int argc, char** argv) {
  initCursorCoor();

  if(checkIfPiped()==-1) {
    if(argc!=2) {
      printf("Give filename\n");
      exit(0);
    }

    cls(); //Clear screen

    displayFile(argv[1]); //Display file
  }

  //Wait until read a key

  while(1) {
    readKey();
  }
}
