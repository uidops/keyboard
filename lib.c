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

#include <X11/Xlib.h>
#include <X11/XKBlib.h>
#include <err.h>
#include <stdlib.h>

#include "lib.h"

int
get_led(char *display_name)
{
	Display *dpy; 
	XKeyboardState x;

	dpy = XOpenDisplay(display_name);
	if (dpy == NULL) {
		if (display_name == NULL)
			display_name = getenv("DISPLAY");
		warnx("(%s): Connection refused", display_name);
		return -1;
	}

	XGetKeyboardControl(dpy, &x);
	XCloseDisplay(dpy);

	return (x.led_mask&4) ? 1 : 0; 
}

int
set_led(int status, char *display_name) {
	Display	*dpy;
	XKeyboardControl values;

	dpy	= XOpenDisplay(display_name);
	if (dpy == NULL) {
		if (display_name== NULL)
			display_name = getenv("DISPLAY");
		warnx("(%s): Connection refused", display_name);
		return -1;
	}

	values.led_mode = status ? LedModeOn : LedModeOff; 
	values.led = 3;

	XChangeKeyboardControl(dpy, KBLed|KBLedMode, &values);
	XFlush(dpy);
	XCloseDisplay(dpy);

	return 0;
}
