#!/bin/sh
# AUTO-GENERATED FILE, DO NOT EDIT!
if [ -f $1.org ]; then
  sed -e 's!^D:/cygwin/lib!/usr/lib!ig;s! D:/cygwin/lib! /usr/lib!ig;s!^D:/cygwin/bin!/usr/bin!ig;s! D:/cygwin/bin! /usr/bin!ig;s!^D:/cygwin/!/!ig;s! D:/cygwin/! /!ig;s!^Z:!/cygdrive/z!ig;s! Z:! /cygdrive/z!ig;s!^Y:!/cygdrive/y!ig;s! Y:! /cygdrive/y!ig;s!^X:!/cygdrive/x!ig;s! X:! /cygdrive/x!ig;s!^W:!/cygdrive/w!ig;s! W:! /cygdrive/w!ig;s!^V:!/cygdrive/v!ig;s! V:! /cygdrive/v!ig;s!^U:!/cygdrive/u!ig;s! U:! /cygdrive/u!ig;s!^T:!/cygdrive/t!ig;s! T:! /cygdrive/t!ig;s!^S:!/cygdrive/s!ig;s! S:! /cygdrive/s!ig;s!^R:!/cygdrive/r!ig;s! R:! /cygdrive/r!ig;s!^D:!/cygdrive/d!ig;s! D:! /cygdrive/d!ig;s!^C:!/cygdrive/c!ig;s! C:! /cygdrive/c!ig;' $1.org > $1 && rm -f $1.org
fi
