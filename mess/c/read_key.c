#include "../headers/read_key.h"

/* Read key */

void readKey() {
  int c;
  c=getch();

  if(c==224) {
    c = getch();
  }

  switch(c) {
    case 'q': //Exit
      cls();
      exit(0);
      break;
    case ARROW_DOWN: //One line down
      if(cur.y==edg.endFile) { //If end of file have been reached stop
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
    case ARROW_RIGHT: //Go 50 lines forward
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
    case ARROW_LEFT: //Go 50 lines backward
      if(cur.y!=0) {
        if(cur.y-50>=0) {
          cur.y-=50;
          goToXY(cur.x, cur.y);
        }else{
        cur.y=0;
        goToXY(cur.x, cur.y);
        }
      }
      break;
    case HOME: //Go to the start of the file
      cur.x = 0;
      cur.y = 0;
      goToXY(cur.x, cur.y);
      break;
    case END:
      cur.y = edg.endFile;
      goToXY(cur.x, cur.y);
      break;
  }

  if(cur.y==edg.endFile) { //If end of file have been reached stop
    statusBar();
  }
}
