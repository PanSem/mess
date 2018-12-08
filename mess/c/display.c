#include "../headers/display.h"

/* Display file */

void displayFile(char* file) {
  //Init file
  FILE * fp;
  char * line = NULL;
  size_t len = 0;
  ssize_t read;

  edg.filename = malloc(sizeof(file));
  edg.filename = file;

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

  //If piped read char by char and display it

  if(!isatty(STDIN_FILENO)) {
    cls(); //Clear console
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
