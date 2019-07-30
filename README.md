This is a GUI XML editor app. It is unfinished.

# Building

First, run qmake:

    qmake

(Or, if you want to run in the debugger:)

    qmake CONFIG+=debug

Then run:

    make

(Or, on Windows:)

    nmake

# Using

## Known problems

* No undo
* On save: whitespace, attribute order, and superfluous-but-intentional XML escaping will not be preserved
* Can't reorder elements
* Can't add or remove elements
* Open/save starts at system root every time :/
* Open/save doesn't filter for .xml files
* File-modified tracking might be wrong

This application will likely get unacceptably slow for very large (hundreds of megabytes) XML files.

# License

The Qt libraries have a LGPL license. The Qt example code this is based on has a BSD license. All new code in this repo is by <<andi.m.mcclure@gmail.com>> and is MIT licensed:

> Copyright 2019 Andi McClure
> 
> Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
> 
> The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
> 
> THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

