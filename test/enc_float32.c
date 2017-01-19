/* Copyright (C) 2016, 2017 D. V. Wiebe
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
#include "test.h"

int main(void)
{
#ifdef ENC_SKIP_TEST
  return 77;
#else
  const char *filedir = "dirfile";
  const char *format = "dirfile/format";
  const char *format1 = "dirfile/format1";
  const char *data = "dirfile/data" ENC_SUFFIX;
  int e1, e2, e3, r = 0;
  DIRFILE *D;
  float data_out[8];
  int i = 0;

  /* The last of these is denormal.  The compiler may
   * round it to zero */
  const float data_in[8] = {
    (float)NAN, 3.33e38, 0, -1, -INFINITY, 1.0877e-38, -0,
    5.55e-45
  };

  rmdirfile();

  D = gd_open(filedir, GD_RDWR | GD_CREAT | GD_EXCL | GD_ENC_ENCODED
      | GD_VERBOSE);

  e1 = gd_add_spec(D, "data RAW FLOAT32 1", 0);
  CHECKI(e1, 0);

  e2 = gd_putdata(D, "data", 0, 0, 0, 8, GD_FLOAT32, data_in);
  CHECKI(e2, 8);

  e3 = gd_getdata(D, "data", 0, 0, 0, 8, GD_FLOAT32, data_out);
  CHECKI(e3, 8);

  gd_discard(D);

  /* Can't check NAN against itself */
  CHECKNAN(data_out[0]);

  if (e3 > 8)
    e3 = 8;
  for (i = 1; i < e3; ++i)
    CHECKFi(i, data_out[i], data_in[i]);

  unlink(format1);
  unlink(format);
  unlink(data);
  rmdir(filedir);

  return r;
#endif
}
