#include "../headers/init.h"
#include "../headers/window_control.h"
#include "../headers/read_key.h"
#include "../headers/display.h"

int main(int argc, char** argv) {
  initCursorCoor();

  if(checkIfPiped()==-1) {
    if(argc!=2) {
      printf("Give filename or press help\n");
      exit(0);
    }

    if(strcmp(argv[1], "help")==0) {
      printf("Press key arrows to navigate the file\n");
      printf("Press HOME to go to the start of the file\n");
      printf("Press END to go to the end of the file\n");
      printf("Press q to quit\n");
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
