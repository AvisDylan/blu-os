# BluOS

### License

Licenced under [GLPv3](./License.txt).

### Description

Blu OS is a hobby x86 operating system.

### Goals

Blu OS as of now is just a hobby OS made for fun. A roadmap can be found in [TODO](./TODO.md).

### Contributing

Please go ahead and read our [CONTRIBUTING](./CONTRIBUTING.md) before making pull requests.

### Documentation

Full documentation is available in the [Doxygen](https://www.doxygen.nl/index.html) generated site: [Documentation](https://avisdylan.github.io/blu-os/html/).

### How to build
You can find some scripts to build and make the iso in `scripts/`. Find the appropriate build script for the target architecture.
**NOTE: to build you need GCC elf cross-compiler, and grub.**

#### Build scripts:
- [amd64](./scripts/build-amd64.sh)
- [i386](./scripts/build-i386.sh)

#### ISO scripts:
- [amd64](./scripts/build-amd64-iso.sh)
- [i386](./scripts/build-i386-iso.sh)
