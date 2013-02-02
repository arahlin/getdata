/* Copyright (C) 2013 D. V. Wiebe
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
#include "gd_matlab.h"

void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{
  DIRFILE *D;
  int fragment_index;
  char *al[3];

  GDMX_CHECK_RHS(2);

  D = gdmx_to_dirfile(prhs[0]);
  fragment_index = gdmx_to_int(prhs, 1);

  gd_fragment_affixes(D, fragment_index, al, al + 1);
  al[2] = NULL;

  gdmx_err(D, 0);

  plhs[0] = gdmx_from_string_list((const char**)al);
}
