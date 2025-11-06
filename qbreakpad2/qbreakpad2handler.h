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

#include "qbreakpad2_global.h"
#include <QObject>

class QBreakpad2HandlerPrivate;
class QBreakpad2Handler final : public QObject {
    Q_OBJECT
    Q_DISABLE_COPY(QBreakpad2Handler)
    Q_DECLARE_PRIVATE(QBreakpad2Handler)
    Q_PROPERTY(QString dumpPath READ dumpPath WRITE setDumpPath NOTIFY dumpPathChanged FINAL)

public:
    [[nodiscard]] QBREAKPAD2_API static QBreakpad2Handler* instance();

    [[nodiscard]] QBREAKPAD2_API QString dumpPath() const;
    QBREAKPAD2_API void setDumpPath(const QString& path);

Q_SIGNALS:
    void dumpPathChanged();

private:
    explicit QBreakpad2Handler(QObject* parent = nullptr);
    ~QBreakpad2Handler() override;

private:
    const std::unique_ptr<QBreakpad2HandlerPrivate> d_ptr;
};
