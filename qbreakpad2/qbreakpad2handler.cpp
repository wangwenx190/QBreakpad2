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

#include "qbreakpad2handler.h"
#include <QDir>

#if 0
#elif defined(Q_OS_MACOS)
#include <client/mac/handler/exception_handler.h>
#elif defined(Q_OS_LINUX)
#include <client/linux/handler/exception_handler.h>
#elif defined(Q_OS_WINDOWS)
#include <client/windows/handler/exception_handler.h>
#else
#  error Unsupported platform!
#endif

static inline bool QBreakpad2DumpCallback(
#if 0
#elif defined(Q_OS_WINDOWS)
const wchar_t* dump_dir, const wchar_t* /*minidump_id*/, void* /*context*/, EXCEPTION_POINTERS* /*exinfo*/, MDRawAssertionInfo* /*assertion*/, bool succeeded
#elif defined(Q_OS_MACOS)
const char* dump_dir, const char* /*minidump_id*/, void* /*context*/, bool succeeded
#elif defined(Q_OS_LINUX)
const google_breakpad::MinidumpDescriptor& /*descriptor*/, void* /*context*/, bool succeeded
#endif
)
{
    return succeeded;
}

class QBreakpad2HandlerPrivate final
{
    Q_DISABLE_COPY(QBreakpad2HandlerPrivate)
    Q_DECLARE_PUBLIC(QBreakpad2Handler)

public:
    QBreakpad2HandlerPrivate(QBreakpad2Handler* q);
    ~QBreakpad2HandlerPrivate();

    QBreakpad2Handler* q_ptr{ nullptr };
    std::unique_ptr<google_breakpad::ExceptionHandler> handler;
    QString dumpPath{};
};

QBreakpad2HandlerPrivate::QBreakpad2HandlerPrivate(QBreakpad2Handler* q) : q_ptr{ q } { Q_ASSERT(q_ptr); }

QBreakpad2HandlerPrivate::~QBreakpad2HandlerPrivate() = default;

QBreakpad2Handler::QBreakpad2Handler(QObject* parent) : QObject{ parent }, d_ptr{ std::make_unique<QBreakpad2HandlerPrivate>(this) }
{
}

QBreakpad2Handler::~QBreakpad2Handler() = default;

QBreakpad2Handler* QBreakpad2Handler::instance() {
    static QBreakpad2Handler handler{};
    return &handler;
}

QString QBreakpad2Handler::dumpPath() const
{
    Q_D(const QBreakpad2Handler);
    return d->dumpPath;
}

void QBreakpad2Handler::setDumpPath(const QString& path)
{
    Q_ASSERT(!path.isEmpty());
    Q_ASSERT(QDir::isAbsolutePath(path));
    if (path.isEmpty() || !QDir::isAbsolutePath(path)) {
        return;
    }

    Q_D(QBreakpad2Handler);
    const QString cleanedPath{ QDir::cleanPath(path) };
    if (d->dumpPath == cleanedPath) {
        return;
    }
    d->dumpPath = cleanedPath;
    Q_EMIT dumpPathChanged();

    // ### Will google breakpad create the dump folder automatically ?
    QDir().mkpath(cleanedPath);

#if 0
#elif defined(Q_OS_WINDOWS)
    d->handler.reset(new google_breakpad::ExceptionHandler(cleanedPath.toStdWString(), /*FilterCallback*/ nullptr, QBreakpad2DumpCallback, /*context*/ nullptr, google_breakpad::ExceptionHandler::HANDLER_ALL));
#elif defined(Q_OS_MACOS)
    d->handler.reset(new google_breakpad::ExceptionHandler(cleanedPath.toStdString(), /*FilterCallback*/ nullptr, QBreakpad2DumpCallback, /*context*/ nullptr, true, nullptr));
#elif defined(Q_OS_LINUX)
    d->handler.reset(new google_breakpad::ExceptionHandler(google_breakpad::MinidumpDescriptor(cleanedPath.toStdString()), /*FilterCallback*/ nullptr, QBreakpad2DumpCallback, /*context*/ nullptr, true, -1));
#endif
}
