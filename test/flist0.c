/* Copyright (C) 2008-2011 D. V. Wiebe
 *
 ***************************************************************************
 *
 * This file is part of the GetData project.
 *
 * GetData is free software; you can redistribute it and/or modify it under
 * the terms of the GNU Lesser General Public License as published by the
 * Free Software Foundation; either version 2.1 of the License, or (at your
 * option) any later version.
 *
 * GetData is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public
 * License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with GetData; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 */
/* Retreiving the number of fields of a field should succeed cleanly */
#include "test.h"

#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

int main(void)
{
  const char *filedir = "dirfile";
  const char *format = "dirfile/format";
  int error, r = 0;
  const char **field_list;
  DIRFILE *D;

  rmdirfile();
  mkdir(filedir, 0777);

  close(open(format, O_CREAT | O_EXCL | O_WRONLY, 0666));

  D = gd_open(filedir, GD_RDONLY | GD_VERBOSE);
  field_list = gd_field_list_by_type(D, GD_RAW_ENTRY);

  error = gd_error(D);

  CHECKI(error, 0);
  CHECKPN(field_list);
  CHECKP(field_list[0]);

  gd_discard(D);
  unlink(format);
  rmdir(filedir);

  return r;
}
