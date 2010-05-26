C++ BINDINGS FOR GETDATA
========================

This README describes the C++ bindings for the GetData library.  These bindings
consist of a several C++ classes in the `GetData' namespace.  Header files
defining these classes are installed into the ${includedir}/getdata directory.
The following classes are available:

DIRFILE CLASS
=============

Defined in getdata/dirfile.h, the Getdata::Dirfile class encapsulates the
DIRFILE object, providing a thin wrapper to the C API.  The following methods
are available:

* Dirfile::Dirfile()
  
  The empty constructor creates an invalid dirfile.  Attempting to call any
  member function will result in a GD_E_BAD_DIRFILE error.

* Dirfile::Dirfile(const char *dirfilename, unsigned int flags = GD_RDWR,
    gd_parser_callback_t sehandler = NULL, void *extra = NULL)

  This constructor takes the name of the dirfile, the dirfile flags, and
  optional pointers to a syntax error callback handler, and a caller pointer
  passed to that callback.  The constructor will call gd_cbopen(3) on the
  provided path name.  If flags is omitted, the default GD_RDWR will be used.

* Dirfile::Dirfile(DIRFILE *dirfile)
  
  This constructor creates a Dirfile object from the supplied C API's DIRFILE
  object.  This may be used especially in the supplied parser callback,
  sehandler, to instantiate a Dirfile object from the supplied DIRFILE pointer.

* ~Dirfile::Dirfile()

  If not done explicitly (see below), the destructor will take care of calling
  gd_close(3).

* int Dirfile::Close()
* int Dirfile::Discard()
  
  These call gd_close(3) and gd_discard(3) respectively.  If they return
  successfully (return value zero), the Dirfile should immediately be destroyed,
  by calling its destructor.  Calling any member function after these functions
  return successfully will result in a GD_E_BAD_DIRFILE error.

* int Dirfile::Error()

  The Error method provides access to the error member of the underlying
  DIRFILE* object.

* const char *Dirfile::ErrorString(size_t len = 4096)

  The ErrorString method will return a buffer containing a description of the
  last GetData library error as obtained from gd_error_string(3).  This buffer
  is local to the object, and subsequent calls to ErrorString() will overwrite
  the buffer.  The string written to the buffer will be at most len characters
  long, up to a maximum of 4096 characters.

* GetData::Entry *Dirfile::Entry(const char *field_code)

  This method will return a pointer to a newly allocated object of the
  appropriate Entry Child class, cast as a plain GetData::Entry, created after
  calling gd_get_entry(3) with the supplied field_code.  See below for a
  description of the Entry classes.

* GetData::Fragment *Dirfile::Fragment(int index)
  
  This method will return a pointer to a newly allocated GetData::Fragment
  object corresponding to the fragment with the specified index.

* int Dirfile::FragmentIndex(const char *field_code)

  This method will call gd_get_fragment_index(3) and return the index number of
  the fragment defining the specified field.

* double Dirfile::FrameNum(const char *field_code, double value,
    off_t frame_start = 0, off_t frame_end = 0)

  This method will call gd_get_framenum_subset(3) to perform a reverse look-up
  on the specified field.  If frame_start or frame_end are omitted, the start or
  end of the field will be used as the limit.

* const char *Dirfile::Name()
  
  This method returns the name of the dirfile, that is the value of the
  dirfilename parameter passed to the constructor.

* GetData::RawEntry *Dirfile::Reference(const char *field_code = NULL)
  
  This method will call gd_reference(3) to set and/or retrieve the reference
  field.  It returns a RawEntry object describing the reference field.

* const char *Dirfile::ReferenceFilename()

  This method is equivalent to calling Dirfile::Reference()->FileName() to
  return the binary file pathname associated with the dirfile reference field,
  except that it properly check that Dirfile::Reference() hasn't returned NULL,
  and it does not create a RawEntry object.

* void Dirfile::SetCallback(gd_parser_callback_t sehandler, void *extra = NULL)
  
  This method will call gd_parser_callback(3) to change or remove the parser
  callback function.

* int Dirfile::UnInclude(int fragment_index, int del = 0)

  This method will call gd_uninclude(3) to remove the indicated fragment from
  the dirfile.  Because gd_uninclude may re-arrange the order of fragments in
  the dirfile, the caller should destroy any GetData::Fragment objects it has
  retained.

* int Dirfile::Add(const Entry &entry)
* int Dirfile::AddSpec(const char *spec, int format_file = 0)
* int Dirfile::AlterSpec(const char *line, int recode = 0)
* const void *Dirfile::Constants(GetData::DataType type = Float64)
* int Delete(const char *field_code, int flags = 0)
* const char **Dirfile::FieldList()
* const char **Dirfile::FieldListByType(GetData::EntryType type)
* int Dirfile::Flush(const char *field_code = NULL)
* const char *Dirfile::FormatFilename(int index)
* size_t Dirfile::GetConstant(const char *field_code, GetData::DataType type,
    void *data_out)
* size_t Dirfile::GetData(const char *field_code, off_t first_frame,
    off_t first_sample, size_t num_frames, size_t num_samples,
    GetData::DataType type, void *data_out)
* size_t Dirfile::GetString(const char *field_code, size_t len, char *data_out)
* int Include(const char *file, int format_file, unsigned int flags)
* int Dirfile::MAdd(const Entry &entry, const char *parent)
* int Dirfile::MAddSpec(const char *spec, const char *parent)
* int Dirfile::MAlterSpec(const char *line, const char *parent)
* const void *Dirfile::MConstants(const char *parent, GetData::DataType type)
* const char **Dirfile::MFieldList(const char *parent)
* const char **Dirfile::MFieldListByType(const char *parent,
    * GetData::EntryType type)
* int Dirfile::MetaFlush()
* const char **Dirfile::MStrings(const char *parent)
* const char **Dirfile::MVectorList(const char *parent)
* DataType Dirfile::NativeType(const char *field_code)
* unsigned int Dirfile::NFields()
* unsigned int Dirfile::NFieldsByType(GetData::EntryType type)
* off_t Dirfile::NFrames()
* int Dirfile::NFormats()
* unsigned int Dirfile::NMFields(const char *parent)
* unsigned int Dirfile::NMFieldsByType(const char *parent,
    GetData::EntryType type)
* unsigned int Dirfile::NMVectors(const char *parent)
* int Dirfile::NVectors()
* size_t Dirfile::PutConstant(const char *field_code, GetData::DataType type,
    const void *data_in)
* size_t Dirfile::PutData(const char *field_code, off_t first_frame,
    off_t first_sample, size_t num_frames, size_t num_samples,
    GetData::DataType type, const void *data_in)
* size_t Dirfile::PutString(const char *field_code, const char *data_in)
* unsigned int Dirfile::SamplesPerFrame(const char *field_code)
* const char **Dirfile::Strings()
* int Dirfile::Validate(const char *field_code)
* const char **Dirfile::VectorList()

  These methods call the corresponding function from the C API on the C DIRFILE
  object associated with the C++ object.  Arguments of type GetData::DataType
  should be one of:

    Null, Unknown, UInt8, Int8, UInt16, Int16, UInt32, Int32, UInt64, Int64,
    Float32, Float64, Complex64, Complex128

  which are aliases for the gd_type_t values GD_NULL, GD_UNKNOWN, GD_UINT8, &c.
  Arguments of type GetData::EntryType should be one of 

    NoEntryType, RawEntryType, LincomEntryType, LinterpEntryType, BitEntryType,
    MultiplyEntryType, PhaseEntryType, ConstEntryType, StringEntryType,
    IndexEntryType

  which are aliases for the gd_entype_t values GD_NO_ENTRY, GD_RAW_ENTRY, &c.
  Note that the arguments to AddSpec are opposite of the corresponding function
  in add_spec.


FRAGMENT CLASS
==============

Define in getdata/fragment.h, the GetData::Fragment class provides information
about an individual fragment in a dirfile.  This class has no public
constructor, but may be created by calling Dirfile::Fragment.

Note: The Fragment class caches the format file index for the associated
fragment.  As a result, if Dirfile::UnInclude is called, these indicies will
be incorrect, and all pre-existing Fragment objects should be destroyed.

* GetData::EncodingScheme Fragment::Encoding()
* unsigned long Fragment::Endianness()
* off_t Fragment::FrameOffset()
* const char *Fragment::Name()
* int Fragment::Parent()
* int Fragment::Protection()
* int Fragment::Index()

  These methods return the specified information on the associated fragment.
  Variables of type EncodingScheme will be one of
  
    AutoEncoding, RawEncoding, TextEncoding, SlimEncoding, GzipEncoding,
    Bzip2Encoding, UnsupportedEncoding

  which are aliases for GD_AUTO_ENCODED, GD_UNENCODED, GD_TEXT_ENCODED, &c.

* int SetEncoding(EncodingScheme encoding, int recode = 0)
* int SetEndianness(unsigned long byte_sex, int recode = 0)
* int SetFrameOffset(off_t offset, int recode = 0)
* int SetProtection(int protection_level)

  These methods set the specified information on the associated fragment by
  calling gd_alter_encoding(3), gd_alter_endianness(3), gd_alter_frameoffset(3),
  or gd_protect(3) as appropriate.


ENTRY CLASS
===========

Defined in getdata/entry.h, the GetData::Entry class encapsulates the gd_entry_t
object.  An entry object may be "associated" with a dirfile.  An entry object
returned by Dirfile::Entry will be associated with that dirfile.  Entry objects
created by using one of the constructors will not be associated.

Changing the value of one of the data members of an associated entry object will
result in a call to the C API to update the corresponding entry in the dirifle.
Changing the value of one of the data members of an unassociated entry has no
such side effect.

The following methods are available:

* Entry::Entry()

  This will create an empty gd_entry_t object.

* int Entry::Associated()
  
  Returns non-zero if this entry object is associated with a dirfile.

* void Entry::Dissociate()
  
  Dissociates this entry object.  If the object is already dissocated, this
  function does nothign.

* EntryType Entry::Type()

  This will return the field type of the Entry's field.  This will be one of:

    NoEntry, RawEntry, LincomEntry, LinterpEntry, BitEntry, MultiplyEntry,
    PhaseEntry

* int Entry::SetFragmentIndex(int fragment_index)
* int Entry::Move(int new_fragment, int move_data = 0)

  These will update the fragment index of the entry.  If the entry is
  associated, these will call gd_move(3) to move the field to a different
  fragment.  These two functions are equivalent, except Entry::Move allows
  specifying the move_data flag.  Entry::SetFragmentIndex always calls gd_move
  with move_data = 0.

* const char *Entry::Name()

  This method returns the name of the field.  

* int Entry::SetName(const char *new_name)
* int Entry::Rename(const char *new_name, int move_data = 0)

  These will change the name of the field of this entry.  If the entry object
  is associated, these will also call calling gd_rename(3).  These two functions
  are equivalent, except Entry::Rename allows specifying the move_data flag
  explicitly.  Entry::SetName always calls gd_rename with move_data = 0.

* virtual int Entry::ComplexScalars()
* virtual int Entry::FragmentIndex()
* virtual int Entry::PolyOrd()
* virtual unsigned int Entry::SamplesPerFrame()
* virtual DataType Entry::RawType()
* virtual int Entry::NFields()
* virtual int Entry::FirstBit()
* virtual int Entry::NumBits()
* virtual int Entry::Shift()
* virtual DataType Entry::ConstType()
* virtual const char *Entry::Table()

  These methods will return the corresponding member of the gd_entry_t object.
  Only methods reasonable to be queried for the given field type will return
  meaningful results.

* virtual const char *Entry::Input(int index = 0)
* virtual double Entry::Scale(int index = 0)
* virtual double complex Entry::CScale(int index = 0)
* virtual double Entry::Offset(int index = 0)
* virtual double complex Entry::COffset(int index = 0)
* virtual double Entry::Coefficient(int index = 0)
* virtual double complex Entry::CCoefficient(int index = 0)
* virtual const char *Entry::Scalar(int index = 0)

  These methods will return an element from the gd_entry_t members in_fields[],
  m[], or b[], indexed by the supplied parameter.  Attempts to access elements
  out of range for the field that the Entry class describes will not return
  meaningful results.


ENTRY CHILD CLASSES
===================

The following classes are provided to create Entry objects of the corresponding
field type.  They inherit from Entry, and behave in the same way: if they are
associated, changing field parameters, will result in a call to the C API to
update the entry in the dirfile.


RawEntry Class
--------------

Defined in getdata/rawentry.h

* RawEntry::RawEntry()
  
  This creates a new RAW entry object with default parameters.

* RawEntry::RawEntry(const char *field_code, DataType data_type,
    unsigned int spf, int format_file = 0)

* const char *RawEntry::FileName()

  This calls gd_get_raw_filename(3) and returns the pathname of the binary file
  associated with the RAW field.

* virtual unsigned int RawEntry::SamplesPerFrame()
* virtual DataType RawEntry::RawType()
* virtual const char *Scalar()

  These methods, re-implemented from the Entry class, return the corresponding
  field parameter.

* int RawEntry::SetSamplesPerFrame(unsigned int spf, int recode = 0)
* int RawEntry::SetSamplesPerFrame(const char *spf, int recode = 0)
* int RawEntry::SetType(DataType type, int recode = 0)

  These methods will change the specified field parameter by calling
  gd_alter_raw(3).  If recode is non-zero, the binary file will also be
  translated.  To use a CONST field code as the sample per frame, pass a string
  to SetSamplesPerFrame().


LincomEntry Class
-----------------

Defined in getdata/lincomentry.h

* LincomEntry::LincomEntry()
  
  This creates a new LINCOM entry object with default parameters.

* LincomEntry::LincomEntry(const char *field_code, int n_fields,
    const char **in_fields, double *m, double *b, int format_file = 0)
* LincomEntry::LincomEntry(const char *field_code, int n_fields,
    const char **in_fields, double complex *m, double complex *b,
    int format_file = 0)

* virtual const char *LincomEntry::Input(int index = 0)
* virtual int LincomEntry::ComplexScalars()
* virtual int LincomEntry::NFields()
* virtual double LincomEntry::Scale(int index = 0)
* virtual double complex LincomEntry::CScale(int index = 0)
* virtual double LincomEntry::Offset(int index = 0)
* virtual double complex LincomEntry::COffset(int index = 0)
* virtual const char *LincomEntry::Scalar(int index = 0)

  These methods, re-implemented from the Entry class, return the corresponding
  field parameter.

* int LincomEntry::SetInput(const char *field, int index = 0)
* int LincomEntry::SetScale(double scale, int index = 0)
* int LincomEntry::SetScale(const char* scale, int index = 0)
* int LincomEntry::SetScale(double complex scale, int index = 0)
* int LincomEntry::SetOffset(double offset, int index = 0)
* int LincomEntry::SetOffset(const char* scale, int index = 0)
* int LincomEntry::SetOffset(double complex offset, int index = 0)

  These functions will change the specified field parameter associated with the
  input field with the given index, which should be between zero and two.  To
  use a CONST field code as a parameter, pass a string to the appropriate
  function.  The complex scalar flag will be updated automatically as
  appropriate.

* int LincomEntry::SetNFields(int nfields)

  This will set the number of input fields for the LINCOM.  If this is greater
  than its previous value, the Set methods above should be used to initialise
  the data.


LinterpEntry Class
------------------

Defined in getdata/linterpentry.h

* LinterpEntry::LinterpEntry()
  
  This creates a new LINTERP entry object with default parameters.

* LinterpEntry::LinterpEntry(const char *field_code, const char *in_field,
    const char *table, int format_file = 0)

* virtual const char *Entry::Input()
* virtual const char *LinterpEntry::Table()

  These methods, re-implemented from the Entry class, return the corresponding
  field parameter.

* int LinterpEntry::SetInput(const char *field)
* int LinterpEntry::SetTable(const char *table, int move_table = 0)

  These methods will change the specified field parameter by calling
  gd_alter_raw(3).  If move_table is non-zero, the existing look-up table will
  be renamed to account for the change in name.


BitEntry and SBitEntry Classes
------------------------------

Defined in getdata/bitentry.h and getdata/sbitentry.h

* BitEntry::BitEntry()
* SBitEntry::SBitEntry()
  
  These creates a new BIT or SBIT entry object with default parameters.

* BitEntry::BitEntry(const char *field_code, const char *in_field, int bitnum,
    int numbits = 1, int format_file = 0)
* SBitEntry::SBitEntry(const char *field_code, const char *in_field, int bitnum,
    int numbits = 1, int format_file = 0)

* virtual const char *Input(int __gd_unused index = 0)
* virtual int FirstBit()
* virtual int NumBits()
* virtual const char *Scalar(int index = 0)

  These methods, re-implemented from the Entry class, return the corresponding
  field parameter.

* int (S)BitEntry::SetInput(const char *field)
* int (S)BitEntry::SetFirstBit(int first_bit)
* int (S)BitEntry::SetFirstBit(const char *first_bit)
* int (S)BitEntry::SetNumBits(int num_bits)
* int (S)BitEntry::SetNumBits(const char *num_bits)

  These methods will change the specified field parameter.  To use a CONST
  field code as a parameter, pass a string to the appropriate function.


MultiplyEntry Class
-------------------

Defined in getdata/multiplyentry.h

* MultiplyEntry::MultiplyEntry()
  
  This creates a new MULTIPLY entry object with default parameters.

* MultiplyEntry::MultiplyEntry(const char *field_code, const char *in_field1,
    const char *in_field2, int format_file = 0)

* virtual const char *MultiplyEntry::Input(int index = 0)

  This methods, re-implemented from the Entry class, returns one of the input
  fields.

* int MultiplyEntry::SetInput(const char *field, int index = 0)

  This function will change the specified input field with the given index,
  which should be zero or one.


PhaseEntry Class
----------------

Defined in getdata/phaseentry.h

* PhaseEntry::PhaseEntry()
  
  This creates a new PHASE entry object with default parameters.

* PhaseEntry::PhaseEntry(const char *field_code, const char *in_field,
    int shift, int format_file = 0)

* virtual const char *PhaseEntry::Input(int __gd_unused index = 0)
* virtual long int PhaseEntry::Shift()

  These methods, re-implemented from the Entry class, return the corresponding
  field parameter.

* int PhaseEntry::SetInput(const char *field)
* int PhaseEntry::SetShift(long int shift)
* int PhaseEntry::SetShift(const char *shift)

  These functions will change the specified input field with the given index,
  which should be between zero or one.


PolynomEntry Class
-------------------

Defined in getdata/lincomentry.h

* PolynomEntry::PolynomEntry()
  
  This creates a new LINCOM entry object with default parameters.

* PolynomEntry::PolynomEntry(const char *field_code, int poly_ord,
    const char *in_field, double *a, int format_file = 0)
* PolynomEntry::PolynomEntry(const char *field_code, int poly_ord,
    const char *in_field, double complex *a int format_file = 0)

* virtual const char *PolynomEntry::Input(int index = 0)
* virtual int PolynomEntry::ComplexScalars()
* virtual int PolynomEntry::PolyOrd()
* virtual double PolynomEntry::Coefficient(int index = 0)
* virtual double complex PolynomEntry::CCoefficient(int index = 0)
* virtual const char *PolynomEntry::Scalar(int index = 0)

  These methods, re-implemented from the Entry class, return the corresponding
  field parameter.

* int PolynomEntry::SetInput(const char *field)
* int PolynomEntry::SetCoefficient(double scale, int index = 0)
* int PolynomEntry::SetCoefficient(const char* scale, int index = 0)
* int PolynomEntry::SetCoefficient(double complex scale, int index = 0)

  These functions will change the specified field parameter associated with the
  input field with the given index, which should be between zero and two.  To
  use a CONST field code as a parameter, pass a string to the appropriate
  function.  The complex scalar flag will be updated automatically as
  appropriate.

* int PolynomEntry::SetPolyOrd(int nfields)

  This will set the polynomial order for the POLYNOM.  If this is greater than
  its previous value, the Set methods above should be used to initialise the
  data.


ConstEntry Class
----------------

Defined in getdata/constentry.h

* ConstEntry::ConstEntry()
  
  This creates a new CONST entry object with default parameters.

* ConstEntry::ConstEntry(const char *field_code, DataType type,
    int format_file = 0)

* virtual DataType ConstEntry::ConstType()

  This method, re-implemented from the Entry class, returns the data type of the
  CONST field.

* int SetType(DataType field)

  This method will change the data type of the CONST field.


StringEntry Class
-----------------

Defined in getdata/stringentry.h

* StringEntry::StringEntry()
  
  This creates a new STRING entry object with default parameters.

* StringEntry::StringEntry(const char *field_code, int format_file = 0)


IndexEntry Class
----------------

Defined in getdata/indexentry.h

The IndexEntry has no public constructor, nor any methods other than the ones
provided by the Entry base class.
