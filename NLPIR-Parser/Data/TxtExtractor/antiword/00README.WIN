Basic installation instructions for Antiword for Windows
========================================================
Unpack antiword.zip using either unzip.exe or pkunzip.exe (third-party utilities)
  unzip -d antiword.zip c:\antiword
(Windows XP users are able to use the built-in zip manager)

NOTE: Experienced users of Windows may want to add the Antiword directory
to their PATH variable.

If you don't do this, you will need to go into the Antiword directory before
running the program.


More advanced installation
==========================
These instructions can be followed under all versions of Windows, but are
most useful under Windows NT, 2000 and XP.

(1) Go to the configuration screen and choose system and environment. Make a
    HOME environment variable containing C:\home\yourname or H:\loginname or
    something similar.
(2) Follow the basic installation instructions, but use %HOME%\antiword as
    the Antiword directory.


Differences between the Unix version of Antiword and the Windows version
========================================================================

(1)
The Unix version looks for its mapping files in $HOME/.antiword.
The Windows version looks for its mapping files in %HOME%\antiword if HOME is set
and in C:\antiword if HOME is not set.

(2)
The Antiword executable (antiword.exe) can be placed in any directory. If you
choose a directory from your %PATH%, you will not have to use a full pathname
every time.


Examples of use
===============

To get text output
------------------

(1) display a Word document in Latin1, one page at a time
antiword -m cp850.txt filename.doc | more

(2) save the text version of the Word document in Latin2, in a file
antiword -m cp852.txt filename.doc > filename.txt

(3) display a Word document in Hebrew, one page at a time
antiword -m cp862.txt filename.doc | more

(4) save the text version of the Word document in Russian Cyrillic, in a file
antiword -m cp866.txt filename.doc > filename.txt

To get PostScript output
------------------------

(1) save the PostScript version of the Word document in Latin1, in a file
    generate PostScript for printing on European A4 size paper
antiword -p a4 -m 8859-1.txt filename.doc > filename.ps

(2) save the PostScipt version of the Word document in Latin2, in a file
    generate PostScript for printing on American letter size paper
antiword -p letter -m 8859-2.txt filename.doc > filename.ps

NOTE: PostScript ouput is only supported for character sets Latin1 and Latin2.

NOTE: You need different mapping files for text and PostScript.

The order of the switches is not important to Antiword. If you specify two or
more settings of the same switch, Antiword will use the rightmost one.
