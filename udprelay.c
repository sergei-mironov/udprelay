/*
  Based on http://www.brokestream.com/udp_redirect.html

  Build: gcc -o udprelay -lpthread udprelay.c

  udprelay.c

  Copyright (C) 2019 Sergey Mironov
  Copyright (C) 2007 Ivan Tikhonov

  This software is provided 'as-is', without any express or implied
  warranty.  In no event will the authors be held liable for any damages
  arising from the use of this software.

  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute it
  freely, subject to the following restrictions:

  1. The origin of this software must not be misrepresented; you must not
     claim that you wrote the original software. If you use this software
     in a product, an acknowledgment in the product documentation would be
     appreciated but is not required.
  2. Altered source versions must be plainly marked as such, and must not be
     misrepresented as being the original software.
  3. This notice may not be removed or altered from any source distribution.

  Ivan Tikhonov, kefeer@brokestream.com
  Sergey Mironov, grrwlf@gmail.com

*/

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>

struct sockaddr_in sa;
struct sockaddr_in sb;

int fa;
int fb;

void* worker(void *arg) {
  int *fsrc, *fdst;
  struct sockaddr_in *ssrc, *sdst;

  if ((uintptr_t)arg==12) {
    fsrc=&fa; fdst=&fb;
    ssrc=&sa; sdst=&sb;
  }
  else { /*(uintptr_t)arg==21*/
    fsrc=&fb; fdst=&fa;
    ssrc=&sb; sdst=&sa;
  }

  while(1) {
    char buf[65535];
    int sn=sizeof(*ssrc);
    int n=recvfrom(*fsrc,buf,sizeof(buf),0,(struct sockaddr *)ssrc,&sn);
    if(n>0 && sdst->sin_port>0) {
      sendto(*fdst,buf,n,0,(struct sockaddr *)sdst,sizeof(*sdst));
    }
  }
  return NULL;
};

int main(int argc, char *argv[]) {
  struct sockaddr_in a,b;
  memset(&a,0,sizeof(struct sockaddr_in));
  memset(&sa,0,sizeof(struct sockaddr_in));
  memset(&b,0,sizeof(struct sockaddr_in));
  memset(&sb,0,sizeof(struct sockaddr_in));

  if (argc!=4) {
    printf("Usage: %s bind-ip port-a port-b\n",argv[0]);
    exit(1);
  }

  fa=socket(PF_INET,SOCK_DGRAM,IPPROTO_IP);
  fb=socket(PF_INET,SOCK_DGRAM,IPPROTO_IP);

  a.sin_family=AF_INET;
  a.sin_addr.s_addr=inet_addr(argv[1]);
  a.sin_port=htons(atoi(argv[2]));
  if(bind(fa,(struct sockaddr *)&a,sizeof(a))==-1) {
    exit(2);
  }

  b.sin_family=AF_INET;
  b.sin_addr.s_addr=inet_addr(argv[1]);
  b.sin_port=htons(atoi(argv[3]));
  if(bind(fb,(struct sockaddr *)&b,sizeof(b))==-1) {
    exit(3);
  }

  pthread_t ab,ba;
  pthread_create(&ab,NULL,worker,(void*)12);
  pthread_create(&ba,NULL,worker,(void*)21);

  pthread_join(ab, NULL);
  pthread_join(ba, NULL);
  return 0;
}
