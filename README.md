# microsoft-pdb - Microsoft PDB and CodeView debug information C++ headers

This is a `build2` package repository for
[`microsoft-pdb`](https://github.com/microsoft/microsoft-pdb),
the headers in which Microsoft describes the PDB (Program Database) symbol
file format and the CodeView debug information it contains.

This file contains setup instructions and other details that are more
appropriate for development rather than consumption. If you want to use
`libmicrosoft-pdb` in your `build2`-based project, then instead see the accompanying
[`PACKAGE-README.md`](libmicrosoft-pdb/PACKAGE-README.md) file.

The development setup for `microsoft-pdb` uses the standard `bdep`-based workflow.
For example:

```
git clone --recurse-submodules https://github.com/build2-packaging/microsoft-pdb.git
cd microsoft-pdb

bdep init -C @msvc cc config.cxx=cl
bdep update
bdep test
```
