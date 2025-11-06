/*
 * MIT License

 * Copyright (C) 2009 Aleksey Palazhchenko
 * Copyright (C) 2014 Sergey Shambir
 * Copyright (C) 2016 Alexander Makarov
 * Copyright (C) 2025 wangwenx190 (Yuhang ZHAO)

 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:

 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.

 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#pragma once

#ifndef QBREAKPAD2_API
#  ifdef QBREAKPAD2_BUILD_STATIC
#    define QBREAKPAD2_API
#  else // !QBREAKPAD2_BUILD_STATIC
#    ifdef _WIN32
#      ifdef QBREAKPAD2_BUILD_LIBRARY
#        define QBREAKPAD2_API __declspec(dllexport)
#      else // !QBREAKPAD2_BUILD_LIBRARY
#        define QBREAKPAD2_API __declspec(dllimport)
#      endif // QBREAKPAD2_BUILD_LIBRARY
#    else // !_WIN32
#      define QBREAKPAD2_API __attribute__((visibility("default")))
#    endif // _WIN32
#  endif // QBREAKPAD2_BUILD_STATIC
#endif // QBREAKPAD2_API
