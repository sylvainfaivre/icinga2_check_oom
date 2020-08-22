#define _GNU_SOURCE
#include <unistd.h>
#define REAL_PATH "/usr/lib/nagios/plugins/check_oom.py"
int main(int ac, char ** const av)
{
   execv(REAL_PATH, av);
}
