#ifndef INIT_H
#define INIT_H

#include <windows.h>
#include <conio.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include "window_info.h"

struct cursorCoor cur;

struct edges edg;

void initCursorCoor();

#endif
