/* Copyright (C) 2008-2012, 2014, 2016, 2017 D. V. Wiebe
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
#include "internal.h"

/* This is a canonicalised version of the path specified in the open call.
 * In the presence of third parties modifying symlinks after dirfile open, the
 * caller is unable to determine the actual path to the dirfile that was
 * opened if we don't help out. */
const char *gd_dirfilename(DIRFILE* D) gd_nothrow
{
  dtrace("%p", D);

  GD_RETURN_IF_INVALID(D, "%p", NULL);

  dreturn("\"%s\"", D->dir[0].path);
  return D->dir[0].path;
}

const char *gd_reference(DIRFILE* D, const char* field_code) gd_nothrow
{
  gd_entry_t *E;
  char *ptr;

  dtrace("%p, \"%s\"", D, field_code);

  GD_RETURN_IF_INVALID(D, "%p", NULL);
  
  /* if no field specified, return only the field name */
  if (field_code == NULL) {
    if (D->reference_field == NULL) {
      dreturn("%p", NULL);
      return NULL;
    }

    dreturn("\"%s\"", D->reference_field->field);
    return D->reference_field->field;
  }

  /* check access mode */
  if ((D->flags & GD_ACCMODE) == GD_RDONLY) {
    _GD_SetError(D, GD_E_ACCMODE, 0, NULL, 0, NULL);
    dreturn("%p", NULL);
    return NULL;
  }

  /* Check field */
  E = _GD_FindEntry(D, field_code);

  if (E == NULL) {
    dreturn("%p", NULL);
    return NULL;
  }

  if (E->field_type != GD_RAW_ENTRY) {
    _GD_SetError(D, GD_E_BAD_FIELD_TYPE, GD_E_FIELD_BAD, NULL, 0, field_code);
    dreturn("%p", NULL);
    return NULL;
  }

  /* Check protection */
  if (D->fragment[0].protection & GD_PROTECT_FORMAT) {
    _GD_SetError(D, GD_E_PROTECTED, GD_E_PROTECTED_FORMAT, NULL, 0,
        D->fragment[0].cname);
    dreturn("%p", NULL);
    return NULL;
  }
  
  ptr = _GD_Strdup(D, E->field);

  if (ptr == NULL) {
    dreturn("%p", NULL);
    return NULL;
  }

  /* set the new reference field */
  D->reference_field = E;
  free(D->fragment[0].ref_name);
  D->fragment[0].ref_name = ptr;
  D->fragment[0].modified = 1;
  D->flags &= ~GD_HAVE_VERSION;

  dreturn("\"%s\"", D->reference_field->field);
  return D->reference_field->field;
}

/* the mask of allowed flags */
#define GD_FLAG_MASK (GD_VERBOSE | GD_PRETTY_PRINT)
unsigned long gd_flags(DIRFILE *D, unsigned long set, unsigned long reset)
  gd_nothrow
{
  dtrace("%p, 0x%lX, 0x%lX", D, set, reset);

  _GD_ClearError(D);

  set &= GD_FLAG_MASK;
  reset &= GD_FLAG_MASK;

  D->flags = (D->flags | set) & ~(D->flags & reset);
  D->open_flags = (D->open_flags | set) & ~(D->open_flags & reset);

  dreturn("0x%lX", D->flags & GD_FLAG_MASK);
  return D->flags & GD_FLAG_MASK;
}

int gd_verbose_prefix(DIRFILE *D, const char *prefix) gd_nothrow
{
  char *ptr = NULL;
  dtrace("%p, \"%s\"", D, prefix);

  _GD_ClearError(D);

  if (prefix) {
    ptr = _GD_Strdup(D, prefix);
    if (D->error) 
      GD_RETURN_ERROR(D);
  }

  free(D->error_prefix);
  D->error_prefix = ptr;

  dreturn("%i", 0);
  return 0;
}

void gd_mplex_lookback(DIRFILE *D, int lookback) gd_nothrow
{
  dtrace("%p, %i", D, lookback);

  _GD_ClearError(D);

  D->lookback = lookback;

  dreturnvoid();
}

/* Used only when _GD_CMalloc isn't malloc(3), and always via _GD_CStrdup */
static __attribute_malloc__ char *_GD_CallerStrdup(const char *str)
{
  char *ptr;
  size_t len;
  dtrace("%s", str);

  len = strlen(str) + 1;
  ptr = _GD_CMalloc(len);
  if (ptr)
    memcpy(ptr, str, len);

  dreturn("%p", ptr);
  return ptr;
}

void gd_alloc_funcs(void *(*malloc_func)(size_t),
    void (*free_func)(void*)) gd_nothrow
{
  dtrace("%p, %p", malloc_func, free_func);

  if (malloc_func == NULL)
    _GD_CMalloc = malloc;
  else
    _GD_CMalloc = malloc_func;

  if (free_func == NULL)
    _GD_CFree = free;
  else
    _GD_CFree = free_func;

  /* Divert strdup if necessary */
  if (_GD_CMalloc == malloc)
    _GD_CStrdup = strdup;
  else
    _GD_CStrdup = _GD_CallerStrdup;

  dreturnvoid();
}

/* Find all the currently open RAWs, and close old ones until we end
 * up with not more than new_limit of them */
static int _GD_FindOpenFields(DIRFILE *D, long new_limit)
{
  unsigned int i;
  long j;
  time_t atime;

  dtrace("%p, %li", D, new_limit);

  D->open_raws = D->open_fds = 0;
  D->opened_sorted = 1;

  /* Run through everything, looking for open raw entries */
  for (i = 0; i < D->n_entries; ++i) {
    if (D->entry[i]->field_type == GD_RAW_ENTRY) {
      dwatch("%s", D->entry[i]->field);
      dwatch("%li", (long)D->entry[i]->e->u.raw.atime);
    }

    if (D->entry[i]->field_type == GD_RAW_ENTRY &&
        D->entry[i]->e->u.raw.atime > 0)
    {
      atime = D->entry[i]->e->u.raw.atime;

      if (D->open_fds + D->entry[i]->e->u.raw.fd_count > new_limit) {
        /* At the limit: close the oldest file we've found if the one
         * we just found is newer, otherwise close this field */
        if (D->opened[D->open_raws]->e->u.raw.atime < atime) {
          /* FiniRawIO decrements open_raws on success */
          if (_GD_FiniRawIO(D, D->opened[D->open_raws],
              D->opened[D->open_raws]->fragment_index, GD_FINIRAW_KEEP))
          {
            dreturn("%i", -1);
            return -1;
          }
        } else {
          /* Close this file and continue */ 
          if (_GD_FiniRawIO(D, D->entry[i], D->entry[i]->fragment_index,
              GD_FINIRAW_KEEP))
          {
            dreturn("%i", -1);
            return -1;
          }
          continue;
        }
      }

      /* Find where the new entry should go in the opened list */
      for (j = 0; j < D->open_raws && atime < D->opened[j]->e->u.raw.atime;
          ++j)
      {
        /* Nothing to do here: just counting j */
      }

      /* Insert sort */
      memmove(D->opened + j + 1, D->opened + j,
          sizeof(D->opened[0]) * (D->open_raws - j));
      D->opened[j] = D->entry[i];
      D->open_raws++;
      D->open_fds += D->entry[i]->e->u.raw.fd_count;
      dwatch("%li", D->open_fds);
    }
  }

  dreturn("%i", 0);
  return 0;
}

/* This is (b - a) because we want the larger atime sorted first */
static int openedcmp(const void *a, const void *b)
{
  return (int)((*((gd_entry_t**)b))->e->u.raw.atime
      - (*((gd_entry_t**)a))->e->u.raw.atime);
}

/* Close open RAWs until were have only limit of them open */
static int _GD_CloseOpenFields(DIRFILE *D, long limit)
{
  dtrace("%p, %li", D, limit);

  /* qsort the opened list */
  if (!D->opened_sorted) {
    qsort(D->opened, D->open_raws, sizeof(D->opened[0]), openedcmp);
    D->opened_sorted = 1;
  }

  /* FiniRawIO updates the opened list, so we just have to close
   * the last open field over and over again until we're below
   * the limit */
  while (D->open_fds > limit) {
    if (_GD_FiniRawIO(D, D->opened[D->open_raws - 1],
          D->opened[D->open_raws - 1]->fragment_index, GD_FINIRAW_KEEP))
    {
      dreturn("%i", -1);
      return -1;
    }
  }

  dreturn("%i", 0);
  return 0;
}

/* Close the oldest open fields until we have at least n free descriptors */
int _GD_AutoClose(DIRFILE *D, int n)
{
  int ret;
  dtrace("%p, %i", D, n);

  /* Not tracking opens, so nothing to do */
  if (D->open_limit == 0) {
    dreturn("%i", 0);
    return 0;
  }

  /* Close things until we're below the limit */
  ret = _GD_CloseOpenFields(D, D->open_limit - n);
  dreturn("%i", ret);
  return ret;
}

long gd_open_limit(DIRFILE *D, long new_limit)
{
  dtrace("%p, %li", D, new_limit);

  _GD_ClearError(D);

  /* If new_limit is GD_OLIMIT_COUNT, this function returns
   * the current count of open file descriptors (if we're tracking that) */
  if (new_limit == GD_OLIMIT_COUNT) {
    long count = (D->open_limit > 0) ? D->open_fds : 0;
    dreturn("%li", count);
    return count;
  }

  /* We allow calling this function with the special values on invalid
   * dirfiles */
  if (new_limit > 0)
    GD_RETURN_ERR_IF_INVALID(D);

  /* For 1, read 2 */
  if (new_limit == 1)
    new_limit = 2;

  if (new_limit >= 0 && new_limit != D->open_limit) { /* New limit */
    if (new_limit == 0) { /* Caller removes limiting */
      free(D->opened);
      D->opened = NULL;
    } else if (D->open_limit == 0) { /* Caller initiates limiting */
      D->opened = _GD_Malloc(D, sizeof(D->opened[0]) * new_limit);
      if (D->error)
        GD_RETURN_ERROR(D);

      if (_GD_FindOpenFields(D, new_limit)) {
        free(D->opened);
        D->opened = NULL;
        GD_RETURN_ERROR(D);
      }

      D->open_limit = new_limit;
    } else { /* Caller updates the limit */
      void *ptr;

      /* First close RAWs until we're under the new limit */
      if (new_limit < D->open_fds && _GD_CloseOpenFields(D, new_limit))
        GD_RETURN_ERROR(D);

      /* Now realloc */
      ptr = _GD_Realloc(D, D->opened, sizeof(D->opened[0]) * new_limit);
      if (D->error)
        GD_RETURN_ERROR(D);
      D->opened = ptr;
    }
    D->open_limit = new_limit;
  }

  dreturn("%li", D->open_limit);
  return D->open_limit;
}
