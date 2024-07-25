# libPLCL

libPLCL is the reference serialization/deserialization library for the [Papyrus(Like)ConfigurationLanguage](https://github.com/PapyrusLikeConfigurationLanguage/PapyrusLikeConfigurationLanguage) language.

Until there is a stable release, the API is subject to change.

## TODO

- [x] Serialization
- [ ] Verifying configs against templates
- [ ] Better error handling
- [ ] Tests

## Building and Installing

### Requirements

- CMake 3.10 or later
- C++23 compiler

### Building

```bash
mkdir build
cd build 
cmake .. # -DCMAKE_INSTALL_PREFIX=/path/to/install, defaults to /usr/local
make
```

### Installing

```bash
make install
```

## Usage

Check the [examples](examples) folder for usage examples.
