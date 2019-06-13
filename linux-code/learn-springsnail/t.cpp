#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <assert.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/epoll.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <vector>

int main()
{
   struct stat buf;
   int fd;
   fd = open("/etc/passwd", O_RDONLY);
   fstat(fd, &buf);
   printf("/etc/passwd file size +%d\n ", buf.st_size);
   return 0;
}
