# BSD 3-Clause License
# 
# Copyright (c) 2021-2022, uidops
# All rights reserved.
# 
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions are met:
# 
# 1. Redistributions of source code must retain the above copyright notice,
#    this list of conditions and the following disclaimer.
# 
# 2. Redistributions in binary form must reproduce the above copyright notice,
#    this list of conditions and the following disclaimer in the documentation
#    and/or other materials provided with the distribution.
# 
# 3. Neither the name of the copyright holder nor the names of its contributors
#    may be used to endorse or promote products derived from this software without
#    specific prior written permission.
# 
# THIS SOFTWARE IS PROVIDED BY THE TINYCU AND CONTRIBUTORS "AS IS"
# AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
# IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
# DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
# FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
# DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
# SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
# CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
# OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
# OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

CC=clang

CFLAGS=-O3
CFLAGS+=-march=native
CFLAGS+=-flto=thin
CFLAGS+=-Wall
CFLAGS+=-Wextra

LIBS=-lX11

RM=rm

all: keyboard_backlight keyboard_numlock

keyboard_backlight: compile_lib
	$(CC) $(CFLAGS) -I. keyboard_backlight.c libkeyboard.o $(LIBS) -o keyboard_backlight

keyboard_numlock: compile_lib
	$(CC) $(CFLAGS) -I. keyboard_numlock.c libkeyboard.o $(LIBS) -o keyboard_numlock

compile_lib:
	$(CC) -c $(CFLAGS) -I. lib.c -o libkeyboard.o

clean:
	$(RM) -f keyboard_backlight keyboard_numlock *.o
