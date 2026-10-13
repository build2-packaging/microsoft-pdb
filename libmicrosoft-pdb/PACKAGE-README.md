# libmicrosoft-pdb - Microsoft PDB and CodeView debug information C++ headers

This is a `build2` package for the
[`microsoft-pdb`](https://github.com/microsoft/microsoft-pdb) C++ library. It
provides the headers in which Microsoft describes the PDB (Program Database)
symbol file format: the CodeView debug information records and constants
(`cvinfo.h` and `cvconst.h`), the API of the `mspdb` DLL that the Microsoft
compilers and linkers use to write and read PDB files (`pdb.h`), and the hash
used for PDB signatures (`crc32.h`).

This package tracks upstream commit `805655a` (2023-04-27) as version
`2023.4.27`. Upstream does not publish releases and the repository is
archived.


## Usage

To start using `libmicrosoft-pdb` in your project, add the following `depends`
value to your `manifest`, adjusting the version constraint as appropriate:

```
depends: libmicrosoft-pdb >= 2023.4.27
```

Then import the library in your `buildfile`:

```
import libs = libmicrosoft-pdb%lib{microsoft-pdb}
```


## Importable targets

This package provides the following importable targets:

```
lib{microsoft-pdb}
```

The upstream headers, included with the `libmicrosoft-pdb/` prefix
(`#include <libmicrosoft-pdb/cvinfo.h>`,
`#include <libmicrosoft-pdb/cvconst.h>`, `#include <libmicrosoft-pdb/pdb.h>`,
and `#include <libmicrosoft-pdb/crc32.h>`).

This package is headers only. The functions declared in `pdb.h` are exported
by the `mspdb` DLL of the Microsoft toolchain, which cannot be built from the
upstream source.

As in upstream, the headers target Windows and rely on the Windows
declarations being already included (for example, `<windows.h>` must be
included first for the SAL annotations and, with MinGW, the `__intN` types).
With MinGW, `pdb.h` also requires the including code to define the
`_Deref_out_z_` SAL annotation (for example, as empty), which MinGW's
`<sal.h>` does not provide. `crc32.h` expects the including code to define
the `PB` (`BYTE*`) type, as the PDB sources do.

`cvinfo.h` and `pdb.h` include the Microsoft-internal `vcver.h` header, which
is not part of upstream, unless `_VC_VER_INC` is defined. This package defines
`_VC_VER_INC` for its consumers unless the compiler provides `vcver.h`.


## Configuration variables

This package provides no configuration variables.
