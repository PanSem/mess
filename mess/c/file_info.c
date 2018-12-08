#include "../headers/file_info.h"

/* Status Bar */

void statusBar() {
  if(cur.y>edg.endFile+1) { //Return if you pass the limit
    return;
  }

  //Init cursor coordinates

  cur.x = 0;
  cur.y = edg.endFile+1;

  //Go to the end of the file

  goToXY(cur.x, cur.y);

    //Go to the end of the file and print the information
    if(edg.filename==NULL) {
      printf("[Filename : No file] - lines : %d", edg.endFile);
    }else{
      printf("[Filename : %s] - lines : %d", edg.filename, edg.endFile);
    }
    goToXY(cur.x, --cur.y);
}
