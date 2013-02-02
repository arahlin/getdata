% Copyright (C) 2013 D. V. Wiebe
%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
% This file is part of the GetData project.
%
% GetData is free software; you can redistribute it and/or modify it under
% the terms of the GNU Lesser General Public License as published by the
% Free Software Foundation; either version 2.1 of the License, or (at your
% option) any later version.
%
% GetData is distributed in the hope that it will be useful, but WITHOUT
% ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
% FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public
% License for more details.
%
% You should have received a copy of the GNU Lesser General Public License
% along with GetData; if not, write to the Free Software Foundation, Inc.,
% 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA

% getdata_constants:
% ------------------
% This function defines a structure containing various constants used by
% the GetData MATLAB bindings.  Typically it is called by doing something
% like:
%
%   >> GD = getdata_constants()
%
% which then allows you to use constants like 'GD.RDWR' when required by
% the bindings.
%
% For details on the GetData MATLAB bindings see the file README.matlab
% distributed with the GetData source.
function GD = getdata_constants()
  GD = struct(...
    'VERSION', '0.8.3a', ...
    'E_OK', int32(0), ...
    'E_OPEN', int32(1), ...
    'E_FORMAT', int32(2), ...
    'E_TRUNC', int32(3), ...
    'E_CREAT', int32(4), ...
    'E_BAD_CODE', int32(5), ...
    'E_BAD_TYPE', int32(6), ...
    'E_RAW_IO', int32(7), ...
    'E_OPEN_FRAGMENT', int32(8), ...
    'E_INTERNAL_ERROR', int32(9), ...
    'E_ALLOC', int32(10), ...
    'E_RANGE', int32(11), ...
    'E_OPEN_LINFILE', int32(12), ...
    'E_RECURSE_LEVEL', int32(13), ...
    'E_BAD_DIRFILE', int32(14), ...
    'E_BAD_FIELD_TYPE', int32(15), ...
    'E_ACCMODE', int32(16), ...
    'E_UNSUPPORTED', int32(17), ...
    'E_UNKNOWN_ENCODING', int32(18), ...
    'E_BAD_ENTRY', int32(19), ...
    'E_DUPLICATE', int32(20), ...
    'E_DIMENSION', int32(21), ...
    'E_BAD_INDEX', int32(22), ...
    'E_BAD_SCALAR', int32(23), ...
    'E_BAD_REFERENCE', int32(24), ...
    'E_PROTECTED', int32(25), ...
    'E_DELETE', int32(26), ...
    'E_ARGUMENT', int32(27), ...
    'E_CALLBACK', int32(28), ...
    'E_EXISTS', int32(29), ...
    'E_UNCLEAN_DB', int32(30), ...
    'E_DOMAIN', int32(31), ...
    'E_BAD_REPR', int32(32), ...
    'E_FLUSH', int32(34), ...
    'E_BOUNDS', int32(35), ...
    'E_LINE_TOO_LONG', int32(36), ...
    'E_OPEN_INCLUDE', int32(8), ...
    'E_BAD_ENDIANNESS', int32(27), ...
    'E_BAD_PROTECTION', int32(27), ...
    'E_BAD_VERSION', int32(27), ...
    'RDONLY', int32(0), ...
    'RDWR', int32(1), ...
    'FORCE_ENDIAN', int32(2), ...
    'BIG_ENDIAN', int32(4), ...
    'LITTLE_ENDIAN', int32(8), ...
    'CREAT', int32(16), ...
    'EXCL', int32(32), ...
    'TRUNC', int32(64), ...
    'PEDANTIC', int32(128), ...
    'FORCE_ENCODING', int32(256), ...
    'VERBOSE', int32(512), ...
    'IGNORE_DUPS', int32(1024), ...
    'IGNORE_REFS', int32(2048), ...
    'PRETTY_PRINT', int32(4096), ...
    'ARM_ENDIAN', int32(8192), ...
    'NOT_ARM_ENDIAN', int32(0), ...
    'PERMISSIVE', int32(16384), ...
    'TRUNCSUB', int32(32768), ...
    'AUTO_ENCODED', int32(0), ...
    'BZIP2_ENCODED', int32(83886080), ...
    'GZIP_ENCODED', int32(67108864), ...
    'LZMA_ENCODED', int32(100663296), ...
    'SIE_ENCODED', int32(117440512), ...
    'SLIM_ENCODED', int32(50331648), ...
    'TEXT_ENCODED', int32(33554432), ...
    'UNENCODED', int32(16777216), ...
    'ZZSLIM_ENCODED', int32(150994944), ...
    'ZZIP_ENCODED', int32(134217728), ...
    'NO_ENTRY', int32(0), ...
    'RAW_ENTRY', int32(1), ...
    'LINCOM_ENTRY', int32(2), ...
    'LINTERP_ENTRY', int32(3), ...
    'BIT_ENTRY', int32(4), ...
    'MULTIPLY_ENTRY', int32(5), ...
    'PHASE_ENTRY', int32(6), ...
    'INDEX_ENTRY', int32(7), ...
    'POLYNOM_ENTRY', int32(8), ...
    'SBIT_ENTRY', int32(9), ...
    'DIVIDE_ENTRY', int32(10), ...
    'RECIP_ENTRY', int32(11), ...
    'WINDOW_ENTRY', int32(12), ...
    'MPLEX_ENTRY', int32(13), ...
    'CONST_ENTRY', int32(16), ...
    'CARRAY_ENTRY', int32(18), ...
    'STRING_ENTRY', int32(17), ...
    'NULL', int32(0), ...
    'UINT8', int32(1), ...
    'INT8', int32(33), ...
    'UINT16', int32(2), ...
    'INT16', int32(34), ...
    'UINT32', int32(4), ...
    'INT32', int32(36), ...
    'UINT64', int32(8), ...
    'INT64', int32(40), ...
    'FLOAT32', int32(132), ...
    'FLOAT64', int32(136), ...
    'COMPLEX64', int32(264), ...
    'COMPLEX128', int32(272), ...
    'DEL_META', int32(1), ...
    'DEL_DATA', int32(2), ...
    'DEL_DEREF', int32(4), ...
    'DEL_FORCE', int32(8), ...
    'REN_DATA', int32(1), ...
    'REN_UPDB', int32(2), ...
    'PROTECT_NONE', int32(0), ...
    'PROTECT_FORMAT', int32(1), ...
    'PROTECT_DATA', int32(2), ...
    'PROTECT_ALL', int32(3), ...
    'SYNTAX_ABORT', int32(0), ...
    'SYNTAX_RESCAN', int32(1), ...
    'SYNTAX_IGNORE', int32(2), ...
    'SYNTAX_CONTINUE', int32(3), ...
    'E_FORMAT_BAD_SPF', int32(1), ...
    'E_FORMAT_N_FIELDS', int32(2), ...
    'E_FORMAT_N_TOK', int32(3), ...
    'E_FORMAT_NUMBITS', int32(4), ...
    'E_FORMAT_BITNUM', int32(5), ...
    'E_FORMAT_BITSIZE', int32(6), ...
    'E_FORMAT_CHARACTER', int32(7), ...
    'E_FORMAT_BAD_LINE', int32(8), ...
    'E_FORMAT_RES_NAME', int32(9), ...
    'E_FORMAT_ENDIAN', int32(10), ...
    'E_FORMAT_BAD_TYPE', int32(11), ...
    'E_FORMAT_BAD_NAME', int32(12), ...
    'E_FORMAT_UNTERM', int32(13), ...
    'E_FORMAT_METARAW', int32(14), ...
    'E_FORMAT_NO_PARENT', int32(15), ...
    'E_FORMAT_DUPLICATE', int32(16), ...
    'E_FORMAT_LOCATION', int32(17), ...
    'E_FORMAT_PROTECT', int32(18), ...
    'E_FORMAT_LITERAL', int32(19), ...
    'E_FORMAT_WINDOP', int32(20), ...
    'E_FORMAT_META_META', int32(21), ...
    'E_FORMAT_ALIAS', int32(22), ...
    'E_FORMAT_MPLEXVAL', int32(23), ...
    'VERSION_CURRENT', int32(-1), ...
    'VERSION_LATEST', int32(-2), ...
    'VERSION_EARLIEST', int32(-3), ...
    'SEEK_SET', int32(0), ...
    'SEEK_CUR', int32(1), ...
    'SEEK_END', int32(2), ...
    'SEEK_WRITE', int32(4), ...
    'WINDOP_UNK', int32(0), ...
    'WINDOP_EQ', int32(1), ...
    'WINDOP_GE', int32(2), ...
    'WINDOP_GT', int32(3), ...
    'WINDOP_LE', int32(4), ...
    'WINDOP_LT', int32(5), ...
    'WINDOP_NE', int32(6), ...
    'WINDOP_SET', int32(7), ...
    'WINDOP_CLR', int32(8), ...
    'DESYNC_PATHCHECK', int32(1), ...
    'DESYNC_REOPEN', int32(2), ...
    'ALL_ENTRIES', int32(0), ...
    'VECTOR_ENTRIES', int32(33), ...
    'SCALAR_ENTRIES', int32(34), ...
    'ALIAS_ENTRIES', int32(-1), ...
    'ENTRIES_HIDDEN', int32(1), ...
    'ENTRIES_NOALIAS', int32(2), ...
    'ALL_FRAGMENTS', int32(-1), ...
    'DEFAULT_LOOKBACK', int32(10), ...
    'DIRFILE_STANDARDS_VERSION', int32(9), ...
    'HERE', int32(-1), ...
    'LOOKBACK_ALL', int32(-1), ...
    'MAX_LINE_LENGTH', int32(4096) ...
  );
end
