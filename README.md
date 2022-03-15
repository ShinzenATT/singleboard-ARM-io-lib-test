#  IO libraries for ARM board MD-407

Here's a library containig drivers for executing IO text communcation with a keypad, a ACeP display
with an ASCII display and a console connected through USART.

To build any of the projects then the ARM gcc & g++ toolchain is needed along with a way to send
the compiled software to your device such as GDB or by cable. Run `make *.mk` to compile and make the program. For the `test/` program, the driver-lib needs to be imported by the IDE or linker
in order to link it with the program correctly.

There is also documentation about the MD-407 and the components used with it. The MD-407 and some
components are created by chalmers so some of the documentation is in Swedish. The documents can be
found in the `docs` folder.
