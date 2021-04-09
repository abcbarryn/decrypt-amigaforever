Usage: decrypt-amigaforever rom_file_name >output_file

This will decrypt Amiga Forver kickstart ROMs so they can be used in a real Amiga. To use it you will need a copy of the rom.key file in the current folder from your copy of Amiga Forever. I have compiled and tested it on MacOS and Linux.
To compile just run: gcc decrypt-amigaforever.c -o decrypt-amigaforever
Copy decrypt-amigaforever to a folder in your path. It should compile on windows in a cygwin environment, but this has not been tested by me.
