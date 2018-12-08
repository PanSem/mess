#ifndef KEY_VALUES_H
#define KEY_VALUES_H

//macro for CTRL_KEY detection

#define CTRL_KEY(k) ((k) & 0x1f)

//Key values in cmd

enum sn {
  ARROW_UP = 72,
  ARROW_DOWN = 80,
  ARROW_RIGHT = 77,
  ARROW_LEFT = 75,
  ENTER = 13,
  SPACE = 32,
  HOME = 71,
  END = 79
};

#endif
