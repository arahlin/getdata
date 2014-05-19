/* Copyright (C) 2014 D. V. Wiebe
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
#ifndef TEST_LZMA
  return 77;
#else
  const char *filedir = "dirfile";
  const char *format = "dirfile/format";
  const char *data = "dirfile/data.xz";
  gd_entry_t e;
  int e1, e2, e3, unlink_data, r = 0;
  DIRFILE *D;

  rmdirfile();
#ifdef USE_LZMA
  D = gd_open(filedir, GD_RDWR | GD_CREAT | GD_VERBOSE | GD_LZMA_ENCODED);
#else
  D = gd_open(filedir, GD_RDWR | GD_CREAT | GD_LZMA_ENCODED);
#endif
  gd_add_raw(D, "data", GD_UINT8, 2, 0);
  e1 = gd_error(D);

  /* check */
  e2 = gd_entry(D, "data", &e);
#ifdef USE_LZMA
  CHECKI(e2, 0);
  if (e2 == 0) {
    CHECKI(e.field_type, GD_RAW_ENTRY);
    CHECKI(e.fragment_index, 0);
    CHECKI(e.EN(raw,spf), 2);
    CHECKI(e.EN(raw,data_type), GD_UINT8);
    gd_free_entry_strings(&e);
  }
#else
  CHECKI(e2, -1);
#endif

  e3 = gd_close(D);
  CHECKI(e3, 0);

  unlink_data = unlink(data);

#ifdef USE_LZMA
  CHECKI(unlink_data, 0);
  CHECKI(e1, GD_E_OK);
#else
  CHECKI(unlink_data, -1);
  CHECKI(e1, GD_E_UNSUPPORTED);
#endif

  unlink(format);
  rmdir(filedir);

  return r;
#endif
}
