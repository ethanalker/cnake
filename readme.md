# cnake

Snake game that runs in the terminal, written in c. WIP

## building

This project uses [nobuild](https://github.com/tsoding/nobuild), so all you need to compile is a C compiler.
The executable will also automagically rebuild itself after it's edited, so you don't need to recompile after making changes to `nobuild.c`.

```bash
$ cc ./nobuild.c -o nobuild
$ ./nobuild
```
