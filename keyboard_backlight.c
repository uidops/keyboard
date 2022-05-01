/*
* BSD 3-Clause License
* 
* Copyright (c) 2021-2022, uidops
* All rights reserved.
* 
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions are met:
* 
* 1. Redistributions of source code must retain the above copyright notice,
*    this list of conditions and the following disclaimer.
* 
* 2. Redistributions in binary form must reproduce the above copyright notice,
*    this list of conditions and the following disclaimer in the documentation
*    and/or other materials provided with the distribution.
* 
* 3. Neither the name of the copyright holder nor the names of its contributors
*    may be used to endorse or promote products derived from this software without
*    specific prior written permission.
* 
* THIS SOFTWARE IS PROVIDED BY THE TINYCU AND CONTRIBUTORS "AS IS"
* AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
* IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
* DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
* FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
* DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
* SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
* CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
* OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
* OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lib.h"

void		 help(int);

int
main(int argc, char **argv)
{
	int status;
	int aflag=0, bflag=0;

	if (argc >= 3)
		help(EXIT_FAILURE);

	if (*(argv+1) == NULL)
		aflag = 1;
	else if (!strcmp(*(argv+1), "on"))
		bflag = 2;
	else if (!strcmp(*(argv+1), "off"))
		bflag = 1;
	else if (!strcmp(*(argv+1), "toggle"))
		bflag = 3;
	else if (!strcmp(*(argv+1), "get"))
		aflag = 1;
	else if (!strcmp(*(argv+1), "help"))
		help(EXIT_SUCCESS);
	else
		help(EXIT_FAILURE);

	status = get_led(NULL);
	if (status == -1)
		exit(EXIT_FAILURE);

	if (aflag) {
		printf("keyboard_backlight=%s\n", status ? "on" : "off");
		exit(EXIT_SUCCESS);
	}

	if (bflag == 3) {
		if (set_led(status^1, NULL) == -1)
			exit(EXIT_FAILURE);
		status = status^1;
	} else if (bflag == 2) {
		if (set_led(1, NULL) == -1)
			exit(EXIT_FAILURE);
		status = 1;
	} else if (bflag == 1) {
		if (set_led(0, NULL) == -1)
			exit(EXIT_FAILURE);
		status = 0;
	}

	fprintf(stderr, "keyboard_backlight=%s\n", status ? "on" : "off");

	return EXIT_SUCCESS;
}

void
help(int exit_status)
{
	puts("KEYBOARD BACKLIGHT CONTROL\n");
	puts("values:");
	puts("   get       Get the keyboard backlight status. (default)");
	puts("              it'll be printed in stdout if selected or in default mode");
	puts("              otherwise in stderr");
	puts("   on        Turn on the keyboard backlight.");
	puts("   off       Turn off the keyboard backlight.");
	puts("   toggle    Toggle the keyboard backlight.\n");
	puts("   help      Help.\n");
	puts("Source code: https://github.com/uidops/keyboard");

	exit(exit_status);
}
