/* Test include */
#include "test.h"

#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

int main(void)
{
  const char* filedir = __TEST__ "dirfile";
  const char* format1 = __TEST__ "dirfile/format1";
  const char* format1_data = "data RAW UINT8 11\n";
  int fd, r = 0;

  mkdir(filedir, 0777);

  fd = open(format1, O_CREAT | O_EXCL | O_WRONLY, 0666);
  write(fd, format1_data, strlen(format1_data));
  close(fd);

  DIRFILE* D = gd_open(filedir, GD_RDONLY);
  gd_include(D, "format1", 0, 0);
  int error = gd_error(D);
  gd_close(D);

  unlink(format1);
  rmdir(filedir);

  CHECKI(error, GD_E_BAD_DIRFILE);

  return r;
}
