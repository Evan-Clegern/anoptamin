# Anoptamin
Currently in development. Base driver code behind a test game I'm working on. So far in development, in fact, it is not worthy of being considered a game, more like an "abstracted way to access SDL windows."

## External Libraries
Anoptamin abstracts itself from Simple DirectMedia Layer 2 and Open Graphics Layer 2 in a straightforward way, using wrapper classes to streamline the process. Anoptamin also makes use of the GNU C library's `<execinfo.h>` utilities.

## Features
1. A mild amount of Voodoo Magic is involved in some of the system's lower-level utilities, such as function hooks and logging.
2. A mild amount of documentation is provided in the header files, and more in the example file(s).
3. A mild amount of basic thread safety has been implemented for the utilities which might be called across threads.
