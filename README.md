# Dumb SuperVisor

**Dumb SuperVisor** (short: dsv) is a bare minimum process supervisor.

## But why?

In a bid to understand process supervision, I attempted to implement a process supervisor myself.

## (Build) Dependencies

- [Dietlibc](https://www.fefe.de/dietlibc/) - other libc are not supported.
- [TCC](https://bellard.org/tcc/) - GCC is not supported.
- [GNU Binutils](https://www.gnu.org/software/binutils/)
- [Make](https://www.gnu.org/software/make/)

The example `empty` daemon is written in x86 assembly.

## Build

Type `make`.

## Usage

`dsv [absolute-path] [arguments...]`

Calling `dsv` without arguments will give a more detailed help message.
