# QBreakpad2

A fork of [qBreakpad](https://github.com/buzzySmile/qBreakpad) with personal modifications.

Please be aware that this repository is for my own personal usages only and thus will never accept any kinds of feature requests.

## Changes compared to the original project

- Migrate the project from QMake to CMake.
- Added support for building both shared library edition & static library edition (or only build one of them).
- Removed the crash uploader. Some important features are missing (such as proxy & SSL) and it doesn't seem to be useful enough as well.
- Updated [Google Breakpad](https://chromium.googlesource.com/breakpad/breakpad) to latest git master (currently it's [470771e32d0167c2654ecb9113dc56a3510b695f](https://chromium.googlesource.com/breakpad/breakpad/+/470771e32d0167c2654ecb9113dc56a3510b695f)).
- Updated [Linux-Syscall-Support (LSS)](https://chromium.googlesource.com/linux-syscall-support) to latest git master (currently it's [29164a80da4d41134950d76d55199ea33fbb9613](https://chromium.googlesource.com/linux-syscall-support/+/29164a80da4d41134950d76d55199ea33fbb9613)).

## License

```text
MIT License

Copyright (C) 2009 Aleksey Palazhchenko
Copyright (C) 2014 Sergey Shambir
Copyright (C) 2016 Alexander Makarov
Copyright (C) 2025 wangwenx190 (Yuhang ZHAO)

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
```

This MIT license only apply to my own personal modifications, the original code of QBreakpad/Google Breakpad/LSS still use their original licenses.
