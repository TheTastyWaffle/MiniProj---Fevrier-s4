#include<stdlib.h>
#include<fcntl.h>
#include<errno.h>
#include<err.h>
#include<unistd.h>
#include<sys/stat.h>
#include"dungeon.h"





struct dungeon init_dungeon(int order){
  struct dungeon dg = malloc(sizeof(struct dungeon));
  dg->order = order;
  dg->rooms = malloc(sizeof(struct room)*order);
}

void create_room(struct dungeon dg, int loc, float val){
  
}

void dungeon_from_file(struct dungeon dg, char *path){
  char buf[2];
  int fd = open(path, O_RDONLY);
  int loc;
  float val;

  while((r = read(fd, buf, 1)))
  {
    if(r == -1)
      err(1, "Error while reading %s", path);
    if(buf[0] == '\n')
    {
      while(read(fd, buf, 1) && buf[0] != '\n')
      {
        if(buf[0] == 'R')
        {
          
        }
        if(buf[0] == 'M')
        {
          
        }
        if(buf[0] == 'B')
        {
          
        }
        if(buf[0] == 'D')
        {
          
        }
      }
    }
  }
}

int main(){
  return 0;
}
