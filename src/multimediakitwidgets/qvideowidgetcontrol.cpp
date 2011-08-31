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

#include "qvideowidgetcontrol.h"
#include "private/qmediacontrol_p.h"

QT_BEGIN_NAMESPACE

/*!
    \class QVideoWidgetControl


    \brief The QVideoWidgetControl class provides a media control which
    implements a video widget.

    \inmodule QtMultimediaKit
    \ingroup multimedia-serv
    \since 1.0

    The videoWidget() property of QVideoWidgetControl provides a pointer to a
    video widget implemented by the control's media service.  This widget is
    owned by the media service and so care should be taken not to delete it.

    \snippet doc/src/snippets/multimedia-snippets/video.cpp Video widget control

    QVideoWidgetControl is one of number of possible video output controls.

    The interface name of QVideoWidgetControl is \c com.nokia.Qt.QVideoWidgetControl/1.0 as
    defined in QVideoWidgetControl_iid.

    \sa QMediaService::requestControl(), QVideoWidget
*/

/*!
    \macro QVideoWidgetControl_iid

    \c com.nokia.Qt.QVideoWidgetControl/1.0

    Defines the interface name of the QVideoWidgetControl class.

    \relates QVideoWidgetControl
*/

/*!
    Constructs a new video widget control with the given \a parent.
*/
QVideoWidgetControl::QVideoWidgetControl(QObject *parent)
    :QMediaControl(parent)
{
}

/*!
    Destroys a video widget control.
*/
QVideoWidgetControl::~QVideoWidgetControl()
{
}

/*!
    \fn QVideoWidgetControl::isFullScreen() const

    Returns true if the video is shown using the complete screen.
    \since 1.0
*/

/*!
    \fn QVideoWidgetControl::setFullScreen(bool fullScreen)

    Sets whether a video widget is in \a fullScreen mode.
    \since 1.0
*/

/*!
    \fn QVideoWidgetControl::fullScreenChanged(bool fullScreen)

    Signals that the \a fullScreen state of a video widget has changed.
    \since 1.0
*/

/*!
    \fn QVideoWidgetControl::aspectRatioMode() const

    Returns how video is scaled to fit the widget with respect to its aspect ratio.
    \since 1.0
*/

/*!
    \fn QVideoWidgetControl::setAspectRatioMode(Qt::AspectRatioMode mode)

    Sets the aspect ratio \a mode which determines how video is scaled to the fit the widget with
    respect to its aspect ratio.
    \since 1.0
*/

/*!
    \fn QVideoWidgetControl::brightness() const

    Returns the brightness adjustment applied to a video.

    Valid brightness values range between -100 and 100, the default is 0.
    \since 1.0
*/

/*!
    \fn QVideoWidgetControl::setBrightness(int brightness)

    Sets a \a brightness adjustment for a video.

    Valid brightness values range between -100 and 100, the default is 0.
    \since 1.0
*/

/*!
    \fn QVideoWidgetControl::brightnessChanged(int brightness)

    Signals that a video widget's \a brightness adjustment has changed.
    \since 1.0
*/

/*!
    \fn QVideoWidgetControl::contrast() const

    Returns the contrast adjustment applied to a video.

    Valid contrast values range between -100 and 100, the default is 0.
    \since 1.0
*/

/*!
    \fn QVideoWidgetControl::setContrast(int contrast)

    Sets the contrast adjustment for a video widget to \a contrast.

    Valid contrast values range between -100 and 100, the default is 0.
    \since 1.0
*/


/*!
    \fn QVideoWidgetControl::contrastChanged(int contrast)

    Signals that a video widget's \a contrast adjustment has changed.
    \since 1.0
*/

/*!
    \fn QVideoWidgetControl::hue() const

    Returns the hue adjustment applied to a video widget.

    Value hue values range between -100 and 100, the default is 0.
    \since 1.0
*/

/*!
    \fn QVideoWidgetControl::setHue(int hue)

    Sets a \a hue adjustment for a video widget.

    Valid hue values range between -100 and 100, the default is 0.
    \since 1.0
*/


/*!
    \fn QVideoWidgetControl::hueChanged(int hue)

    Signals that a video widget's \a hue adjustment has changed.
    \since 1.0
*/

/*!
    \fn QVideoWidgetControl::saturation() const

    Returns the saturation adjustment applied to a video widget.

    Value saturation values range between -100 and 100, the default is 0.
    \since 1.0
*/


/*!
    \fn QVideoWidgetControl::setSaturation(int saturation)

    Sets a \a saturation adjustment for a video widget.

    Valid saturation values range between -100 and 100, the default is 0.
    \since 1.0
*/

/*!
    \fn QVideoWidgetControl::saturationChanged(int saturation)

    Signals that a video widget's \a saturation adjustment has changed.
    \since 1.0
*/

/*!
    \fn QVideoWidgetControl::videoWidget()

    Returns the QWidget.
    \since 1.0
*/

#include "moc_qvideowidgetcontrol.cpp"
QT_END_NAMESPACE

