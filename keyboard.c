#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <linux/input.h>

#define PATH_SIZE 256
#define MAX_KEYS 256

typedef struct dirent dirnt;
typedef struct stat STT;

int bitmap_size;

int is_chrdev(const dirnt *file){
  char path[PATH_SIZE];
  STT stt;
  snprintf(path, PATH_SIZE, "/dev/input/%s", file->d_name);
  stat(path, &stt);
  return S_ISCHR(stt.st_mode);
}

int is_one(char *bitmap, int id){
  return ((bitmap[id / 8] >> (id % 8)) & 1) == 1;
}

char *get_key_name(int key_code){
  switch(key_code){
    case KEY_1:          return strdup("1");
    case KEY_2:          return strdup("2");
    case KEY_3:          return strdup("3");
    case KEY_4:          return strdup("4");
    case KEY_5:          return strdup("5");
    case KEY_6:          return strdup("6");
    case KEY_7:          return strdup("7");
    case KEY_8:          return strdup("8");
    case KEY_9:          return strdup("9");
    case KEY_0:          return strdup("0");
    case KEY_A:          return strdup("A");
    case KEY_B:          return strdup("B");
    case KEY_C:          return strdup("C");
    case KEY_D:          return strdup("D");
    case KEY_E:          return strdup("E");
    case KEY_F:          return strdup("F");
    case KEY_G:          return strdup("G");
    case KEY_H:          return strdup("H");
    case KEY_I:          return strdup("I");
    case KEY_J:          return strdup("J");
    case KEY_K:          return strdup("K");
    case KEY_L:          return strdup("L");
    case KEY_M:          return strdup("M");
    case KEY_N:          return strdup("N");
    case KEY_O:          return strdup("O");
    case KEY_P:          return strdup("P");
    case KEY_Q:          return strdup("Q");
    case KEY_R:          return strdup("R");
    case KEY_S:          return strdup("S");
    case KEY_T:          return strdup("T");
    case KEY_U:          return strdup("U");
    case KEY_V:          return strdup("V");
    case KEY_W:          return strdup("W");
    case KEY_X:          return strdup("X");
    case KEY_Y:          return strdup("Y");
    case KEY_Z:          return strdup("Z");
    case KEY_MINUS:      return strdup("-");
    case KEY_EQUAL:      return strdup("=");
    case KEY_LEFTBRACE:  return strdup("{");
    case KEY_RIGHTBRACE: return strdup("}");
    case KEY_SEMICOLON:  return strdup(";");
    case KEY_COMMA:      return strdup(":");
    case KEY_SPACE:      return strdup("SPC");
    case KEY_DOT:        return strdup(".");
    case KEY_SLASH:      return strdup("/");
    case KEY_TAB:        return strdup("TAB");
    case KEY_ESC:        return strdup("ESC");
    case KEY_ENTER:      return strdup("ENTER");
    case KEY_LEFTCTRL:   return strdup("CTRL");
    case KEY_RIGHTCTRL:  return strdup("CTRL");
    case KEY_BACKSPACE:  return strdup("BACKSPC");
    case KEY_LEFTSHIFT:  return strdup("SHIFT");
    case KEY_RIGHTSHIFT: return strdup("SHIFT");
    case KEY_UP:         return strdup("UP");
    case KEY_DOWN:       return strdup("DOWN");
    case KEY_LEFT:       return strdup("LEFT");
    case KEY_RIGHT:      return strdup("RIGHT");
  }
  return strdup("UNDEFINED");
}

char *search_keyboard(){
  int i, j, fdsc, nfiles, bitmap_size;
  char *bitmap;
  char path[PATH_SIZE];
  dirnt **file;
  if((nfiles = scandir("/dev/input/", &file, &is_chrdev, &alphasort)) < 0){
    printf("[ERROR] No event files found\n");
    return NULL;
  }
  bitmap_size = KEY_MAX / 8 + 1;
  bitmap = (char *)malloc(bitmap_size);
  for(i = 0; i < nfiles; i++){
    snprintf(path, PATH_SIZE, "/dev/input/%s", file[i]->d_name);
    printf("[INFO] check %s\n", path);
    if((fdsc = open(path, O_RDONLY)) < 0){
      printf("[ERROR] File open error\n");
      continue;
    }
    ioctl(fdsc, EVIOCGBIT(EV_KEY, bitmap_size), bitmap);
    if(is_one(bitmap, KEY_A) && is_one(bitmap, KEY_Z)){
      printf("[INFO] Keyboard file found\n");
      close(fdsc);
      break;
    }
    close(fdsc);
  }
  if(i == nfiles){
    printf("[ERROR] No Keyboard files found\n");
    return NULL;
  }
  free(bitmap); 
  return strdup(path);
}
