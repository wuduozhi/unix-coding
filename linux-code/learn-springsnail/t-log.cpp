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


#include "log.h"

using std::vector;

static const char* version = "1.0";

static void usage( const char* prog )
{
    log( LOG_INFO, __FILE__, __LINE__,  "usage: %s [-h] [-v] [-f config_file]", prog );
}

int main(int argc, char* argv[] )
{
  
   return 0;
}
