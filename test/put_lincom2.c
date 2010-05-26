/* Attempt to write LINCOM 2 */
#include "test.h"

#include <inttypes.h>
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
  const char* format = __TEST__ "dirfile/format";
  const char* data = __TEST__ "dirfile/data";
  const char* format_data = "lincom LINCOM 2 data 0.5 3.0 data 1.0 2.0\ndata RAW INT8 8\n";
  int8_t c[8];
  int fd, i, r = 0;
  struct stat buf;

  memset(c, 0, 8);
  mkdir(filedir, 0777);

  for (i = 0; i < 8; ++i)
    c[i] = (int8_t)(40 + i);

  fd = open(format, O_CREAT | O_EXCL | O_WRONLY, 0666);
  write(fd, format_data, strlen(format_data));
  close(fd);

  DIRFILE* D = gd_open(filedir, GD_RDWR | GD_UNENCODED);
  int n = gd_putdata(D, "lincom", 5, 0, 1, 0, GD_INT8, c);
  int error = gd_error(D);

  gd_close(D);

  if (!stat(data, &buf)) {
    perror("stat");
    r = 1;
  }

  unlink(format);
  rmdir(filedir);

  CHECKI(n,0);
  CHECKI(error,GD_E_BAD_FIELD_TYPE);
  return r;
}
