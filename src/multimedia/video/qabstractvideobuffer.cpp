/****************************************************************************
**
** Copyright (C) 2010 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** This file is part of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** GNU Lesser General Public License Usage
** This file may be used under the terms of the GNU Lesser General Public
** License version 2.1 as published by the Free Software Foundation and
** appearing in the file LICENSE.LGPL included in the packaging of this
** file. Please review the following information to ensure the GNU Lesser
** General Public License version 2.1 requirements will be met:
** http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Nokia gives you certain additional
** rights. These rights are described in the Nokia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU General
** Public License version 3.0 as published by the Free Software Foundation
** and appearing in the file LICENSE.GPL included in the packaging of this
** file. Please review the following information to ensure the GNU General
** Public License version 3.0 requirements will be met:
** http://www.gnu.org/copyleft/gpl.html.
**
** Other Usage
** Alternatively, this file may be used in accordance with the terms and
** conditions contained in a signed written agreement between you and Nokia.
**
**
**
**
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "qabstractvideobuffer_p.h"

#include <qvariant.h>

#include <QDebug>


QT_BEGIN_NAMESPACE

/*!
    \class QAbstractVideoBuffer
    \brief The QAbstractVideoBuffer class is an abstraction for video data.
    \since 1.0
    \inmodule QtMultimedia

    The QVideoFrame class makes use of a QAbstractVideoBuffer internally to reference a buffer of
    video data.  Creating a subclass of QAbstractVideoBuffer will allow you to construct video
    frames from preallocated or static buffers.

    The contents of a buffer can be accessed by mapping the buffer to memory using the map()
    function which returns a pointer to memory containing the contents of the the video buffer.
    The memory returned by map() is released by calling the unmap() function.

    The handle() of a buffer may also be used to manipulate its contents using type specific APIs.
    The type of a buffer's handle is given by the handleType() function.

    \sa QVideoFrame
*/

/*!
    \enum QAbstractVideoBuffer::HandleType

    Identifies the type of a video buffers handle.

    \value NoHandle The buffer has no handle, its data can only be accessed by mapping the buffer.
    \value GLTextureHandle The handle of the buffer is an OpenGL texture ID.
    \value XvShmImageHandle The handle contains pointer to shared memory XVideo image.
    \value CoreImageHandle The handle contains pointer to Mac OS X CIImage.
    \value QPixmapHandle The handle of the buffer is a QPixmap.
    \value UserHandle Start value for user defined handle types.

    \sa handleType()
*/

/*!
    \enum QAbstractVideoBuffer::MapMode

    Enumerates how a video buffer's data is mapped to memory.

    \value NotMapped The video buffer has is not mapped to memory.
    \value ReadOnly The mapped memory is populated with data from the video buffer when mapped, but
    the content of the mapped memory may be discarded when unmapped.
    \value WriteOnly The mapped memory is uninitialized when mapped, and the content will be used to
    populate the video buffer when unmapped.
    \value ReadWrite The mapped memory is populated with data from the video buffer, and the
    video buffer is repopulated with the content of the mapped memory.

    \sa mapMode(), map()
*/

/*!
    Constructs an abstract video buffer of the given \a type.
*/
QAbstractVideoBuffer::QAbstractVideoBuffer(HandleType type)
    : d_ptr(new QAbstractVideoBufferPrivate)
{
    Q_D(QAbstractVideoBuffer);

    d->handleType = type;
}

/*!
    \internal
*/
QAbstractVideoBuffer::QAbstractVideoBuffer(QAbstractVideoBufferPrivate &dd, HandleType type)
    : d_ptr(&dd)
{
    Q_D(QAbstractVideoBuffer);

    d->handleType = type;
}

/*!
    Destroys an abstract video buffer.
*/
QAbstractVideoBuffer::~QAbstractVideoBuffer()
{
    delete d_ptr;
}

/*!
    Returns the type of a video buffer's handle.

    \since 1.0
    \sa handle()
*/
QAbstractVideoBuffer::HandleType QAbstractVideoBuffer::handleType() const
{
    return d_func()->handleType;
}

/*!
    \fn QAbstractVideoBuffer::mapMode() const

    Returns the mode a video buffer is mapped in.

    \since 1.0
    \sa map()
*/

/*!
    \fn QAbstractVideoBuffer::map(MapMode mode, int *numBytes, int *bytesPerLine)

    Maps the contents of a video buffer to memory.

    The map \a mode indicates whether the contents of the mapped memory should be read from and/or
    written to the buffer.  If the map mode includes the QAbstractVideoBuffer::ReadOnly flag the
    mapped memory will be populated with the content of the video buffer when mapped.  If the map
    mode includes the QAbstractVideoBuffer::WriteOnly flag the content of the mapped memory will be
    persisted in the buffer when unmapped.

    When access to the data is no longer needed be sure to call the unmap() function to release the
    mapped memory.

    Returns a pointer to the mapped memory region, or a null pointer if the mapping failed.  The
    size in bytes of the mapped memory region is returned in \a numBytes, and the line stride in \a
    bytesPerLine.

    When access to the data is no longer needed be sure to unmap() the buffer.

    \note Writing to memory that is mapped as read-only is undefined, and may result in changes
    to shared data.

    \since 1.0
    \sa unmap(), mapMode()
*/

/*!
    \fn QAbstractVideoBuffer::unmap()

    Releases the memory mapped by the map() function

    If the \l {QAbstractVideoBuffer::MapMode}{MapMode} included the QAbstractVideoBuffer::WriteOnly
    flag this will persist the current content of the mapped memory to the video frame.

    \since 1.0
    \sa map()
*/

/*!
    Returns a type specific handle to the data buffer.

    The type of the handle is given by handleType() function.

    \since 1.0
    \sa handleType()
*/
QVariant QAbstractVideoBuffer::handle() const
{
    return QVariant();
}

#ifndef QT_NO_DEBUG_STREAM
QDebug operator<<(QDebug dbg, QAbstractVideoBuffer::HandleType type)
{
    switch (type) {
    case QAbstractVideoBuffer::NoHandle:
        return dbg.nospace() << "NoHandle";
    case QAbstractVideoBuffer::GLTextureHandle:
        return dbg.nospace() << "GLTextureHandle";
    case QAbstractVideoBuffer::XvShmImageHandle:
        return dbg.nospace() << "XvShmImageHandle";
    case QAbstractVideoBuffer::CoreImageHandle:
        return dbg.nospace() << "CoreImageHandle";
    case QAbstractVideoBuffer::QPixmapHandle:
        return dbg.nospace() << "QPixmapHandle";
    default:
        return dbg.nospace() << QString(QLatin1String("UserHandle(%1)")).arg(int(type)).toAscii().constData();
    }
}

QDebug operator<<(QDebug dbg, QAbstractVideoBuffer::MapMode mode)
{
    switch (mode) {
    case QAbstractVideoBuffer::ReadOnly:
        return dbg.nospace() << "ReadOnly";
    case QAbstractVideoBuffer::ReadWrite:
        return dbg.nospace() << "ReadWrite";
    case QAbstractVideoBuffer::WriteOnly:
        return dbg.nospace() << "WriteOnly";
    default:
        return dbg.nospace() << "NotMapped";
    }
}
#endif

QT_END_NAMESPACE
