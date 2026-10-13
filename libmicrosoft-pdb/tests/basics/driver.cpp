// The headers rely on the Windows declarations (SAL annotations and, with
// MinGW, the __intN types) being already included.
//
#include <windows.h>

#include <libmicrosoft-pdb/cvconst.h>
#include <libmicrosoft-pdb/cvinfo.h>

// pdb.h uses the _Deref_out_z_ SAL annotation that MinGW's <sal.h> does
// not define.
//
#ifndef _Deref_out_z_
#  define _Deref_out_z_
#endif

#include <libmicrosoft-pdb/pdb.h>

// crc32.h expects the PB pointer type of the PDB sources.
//
typedef BYTE* PB;
#include <libmicrosoft-pdb/crc32.h>

#undef NDEBUG
#include <cassert>

int main ()
{
  // CodeView constants and type records.
  //
  {
    assert (CV_CFL_AMD64 == 0xD0);
    assert (sizeof (CV_typ_t) == 4);

    // The record length excludes the length field itself.
    //
    char r[8] {};
    TYPTYPE* t (reinterpret_cast<TYPTYPE*> (r));
    t->len = 6;
    t->leaf = LF_POINTER;
    assert (NextType (r) == r + sizeof (r));
  }

  // Compressed annotation data round trip.
  //
  {
    using namespace CodeViewInfo;

    UInt8 b[4];
    assert (CVCompressData (0x1234, b) == 2);

    PCompressedAnnotation p (b);
    assert (CVUncompressData (p) == 0x1234);
    assert (p == b + 2);

    assert (DecodeSignedInt32 (EncodeSignedInt32 (-5)) == -5);
  }

  // PDB API interface version and DLL entry point type.
  //
  {
    assert (static_cast<int> (PDB::intv) == static_cast<int> (PDBIntv));

    PfnPDBExportValidateInterface f (nullptr);
    assert (f == nullptr);
  }

  // The PDB signature hash is the reflected CRC-32 without the initial and
  // final inversion, so adding both gives the standard CRC-32 check value.
  //
  {
    const char s[] = "123456789";
    SIG sig (PDBCRC32::SigForPbCb (PB (s), sizeof (s) - 1, ~SIG (0)));
    assert (~sig == 0xCBF43926);
  }
}
