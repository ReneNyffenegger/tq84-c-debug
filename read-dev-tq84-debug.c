#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
// #include "resrever.h"

#define    BUFLEN 0x40000

static char recv[BUFLEN];

int main() {
  int fd;    

  #define    TQ84_DEVICE_NAME "tq84_debug"

 
  #define DEV "/dev/" TQ84_DEVICE_NAME
  
  fd = open(DEV, O_RDWR);

  
  if (read(fd, recv, BUFLEN/2) < 0) {
    perror("Could ot read recv\n");
    exit (3);
  }

  printf(recv);
}
