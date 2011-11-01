/****************************************************************************
**
** Copyright (C) 2010 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** This file is part of the test suite of the Qt Toolkit.
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

//TESTED_COMPONENT=src/multimedia

#include <QtTest/QtTest>

#include <qvideosurfaceformat.h>

// Adds an enum, and the stringized version
#define ADD_ENUM_TEST(x) \
    QTest::newRow(#x) \
        << QVideoSurfaceFormat::x \
    << QString(QLatin1String(#x));

class tst_QVideoSurfaceFormat : public QObject
{
    Q_OBJECT
public:
    tst_QVideoSurfaceFormat();
    ~tst_QVideoSurfaceFormat();

public slots:
    void initTestCase();
    void cleanupTestCase();
    void init();
    void cleanup();

private slots:
    void constructNull();
    void construct_data();
    void construct();
    void frameSize_data();
    void frameSize();
    void viewport_data();
    void viewport();
    void scanLineDirection_data();
    void scanLineDirection();
    void frameRate_data();
    void frameRate();
    void pixelAspectRatio_data();
    void pixelAspectRatio();
    void sizeHint_data();
    void sizeHint();
    void yCbCrColorSpaceEnum_data();
    void yCbCrColorSpaceEnum ();
    void staticPropertyNames();
    void dynamicProperty();
    void compare();
    void copy();
    void assign();

    void isValid();
    void copyAllParameters ();
    void assignAllParameters ();

    void propertyEdgeCases();
    void debugOperator();
    void debugOperator_data();
};

tst_QVideoSurfaceFormat::tst_QVideoSurfaceFormat()
{
}

tst_QVideoSurfaceFormat::~tst_QVideoSurfaceFormat()
{
}

void tst_QVideoSurfaceFormat::initTestCase()
{
}

void tst_QVideoSurfaceFormat::cleanupTestCase()
{
}

void tst_QVideoSurfaceFormat::init()
{
}

void tst_QVideoSurfaceFormat::cleanup()
{
}

void tst_QVideoSurfaceFormat::constructNull()
{
    QVideoSurfaceFormat format;

    QVERIFY(!format.isValid());
    QCOMPARE(format.handleType(), QAbstractVideoBuffer::NoHandle);
    QCOMPARE(format.pixelFormat(), QVideoFrame::Format_Invalid);
    QCOMPARE(format.frameSize(), QSize());
    QCOMPARE(format.frameWidth(), -1);
    QCOMPARE(format.frameHeight(), -1);
    QCOMPARE(format.viewport(), QRect());
    QCOMPARE(format.scanLineDirection(), QVideoSurfaceFormat::TopToBottom);
    QCOMPARE(format.frameRate(), 0.0);
    QCOMPARE(format.pixelAspectRatio(), QSize(1, 1));
    QCOMPARE(format.yCbCrColorSpace(), QVideoSurfaceFormat::YCbCr_Undefined);
}

void tst_QVideoSurfaceFormat::construct_data()
{
    QTest::addColumn<QSize>("frameSize");
    QTest::addColumn<QVideoFrame::PixelFormat>("pixelFormat");
    QTest::addColumn<QAbstractVideoBuffer::HandleType>("handleType");
    QTest::addColumn<bool>("valid");

    QTest::newRow("32x32 rgb32 no handle")
            << QSize(32, 32)
            << QVideoFrame::Format_RGB32
            << QAbstractVideoBuffer::NoHandle
            << true;

    QTest::newRow("1024x768 YUV444 GL texture")
            << QSize(32, 32)
            << QVideoFrame::Format_YUV444
            << QAbstractVideoBuffer::GLTextureHandle
            << true;

    QTest::newRow("32x32 invalid no handle")
            << QSize(32, 32)
            << QVideoFrame::Format_Invalid
            << QAbstractVideoBuffer::NoHandle
            << false;

    QTest::newRow("invalid size, rgb32 no handle")
            << QSize()
            << QVideoFrame::Format_RGB32
            << QAbstractVideoBuffer::NoHandle
            << false;

    QTest::newRow("0x0 rgb32 no handle")
            << QSize(0,0)
            << QVideoFrame::Format_RGB32
            << QAbstractVideoBuffer::NoHandle
            << true;
}

void tst_QVideoSurfaceFormat::construct()
{
    QFETCH(QSize, frameSize);
    QFETCH(QVideoFrame::PixelFormat, pixelFormat);
    QFETCH(QAbstractVideoBuffer::HandleType, handleType);
    QFETCH(bool, valid);

    QRect viewport(QPoint(0, 0), frameSize);

    QVideoSurfaceFormat format(frameSize, pixelFormat, handleType);

    QCOMPARE(format.handleType(), handleType);
    QCOMPARE(format.property("handleType").value<QAbstractVideoBuffer::HandleType>(), handleType);
    QCOMPARE(format.pixelFormat(), pixelFormat);
    QCOMPARE(format.property("pixelFormat").value<QVideoFrame::PixelFormat>(), pixelFormat);
    QCOMPARE(format.frameSize(), frameSize);
    QCOMPARE(format.frameWidth(), frameSize.width());
    QCOMPARE(format.property("frameWidth").toInt(), frameSize.width());
    QCOMPARE(format.frameHeight(), frameSize.height());
    QCOMPARE(format.property("frameHeight").toInt(), frameSize.height());
    QCOMPARE(format.isValid(), valid);
    QCOMPARE(format.viewport(), viewport);
    QCOMPARE(format.scanLineDirection(), QVideoSurfaceFormat::TopToBottom);
    QCOMPARE(format.frameRate(), 0.0);
    QCOMPARE(format.pixelAspectRatio(), QSize(1, 1));
    QCOMPARE(format.yCbCrColorSpace(), QVideoSurfaceFormat::YCbCr_Undefined);
}

void tst_QVideoSurfaceFormat::frameSize_data()
{
    QTest::addColumn<QSize>("initialSize");
    QTest::addColumn<QSize>("newSize");

    QTest::newRow("grow")
            << QSize(64, 64)
            << QSize(1024, 1024);
    QTest::newRow("shrink")
            << QSize(1024, 1024)
            << QSize(64, 64);
    QTest::newRow("unchanged")
            << QSize(512, 512)
            << QSize(512, 512);
}

void tst_QVideoSurfaceFormat::frameSize()
{
    QFETCH(QSize, initialSize);
    QFETCH(QSize, newSize);

    {
        QVideoSurfaceFormat format(initialSize, QVideoFrame::Format_RGB32);

        format.setFrameSize(newSize);

        QCOMPARE(format.frameSize(), newSize);
        QCOMPARE(format.property("frameSize").toSize(), newSize);
        QCOMPARE(format.frameWidth(), newSize.width());
        QCOMPARE(format.property("frameWidth").toInt(), newSize.width());
        QCOMPARE(format.frameHeight(), newSize.height());
        QCOMPARE(format.property("frameHeight").toInt(), newSize.height());
    }

    {
        QVideoSurfaceFormat format(initialSize, QVideoFrame::Format_RGB32);

        format.setProperty("frameSize", newSize);

        QCOMPARE(format.frameSize(), newSize);
        QCOMPARE(format.property("frameSize").toSize(), newSize);
        QCOMPARE(format.frameWidth(), newSize.width());
        QCOMPARE(format.property("frameWidth").toInt(), newSize.width());
        QCOMPARE(format.frameHeight(), newSize.height());
        QCOMPARE(format.property("frameHeight").toInt(), newSize.height());
    }

}

void tst_QVideoSurfaceFormat::viewport_data()
{
    QTest::addColumn<QSize>("initialSize");
    QTest::addColumn<QRect>("viewport");
    QTest::addColumn<QSize>("newSize");
    QTest::addColumn<QRect>("expectedViewport");

    QTest::newRow("grow reset")
            << QSize(64, 64)
            << QRect(8, 8, 48, 48)
            << QSize(1024, 1024)
            << QRect(0, 0, 1024, 1024);
    QTest::newRow("shrink reset")
            << QSize(1024, 1024)
            << QRect(8, 8, 1008, 1008)
            << QSize(64, 64)
            << QRect(0, 0, 64, 64);
    QTest::newRow("unchanged reset")
            << QSize(512, 512)
            << QRect(8, 8, 496, 496)
            << QSize(512, 512)
            << QRect(0, 0, 512, 512);
}

void tst_QVideoSurfaceFormat::viewport()
{
    QFETCH(QSize, initialSize);
    QFETCH(QRect, viewport);
    QFETCH(QSize, newSize);
    QFETCH(QRect, expectedViewport);

    {
        QRect initialViewport(QPoint(0, 0), initialSize);

        QVideoSurfaceFormat format(initialSize, QVideoFrame::Format_RGB32);

        format.setViewport(viewport);

        QCOMPARE(format.viewport(), viewport);
        QCOMPARE(format.property("viewport").toRect(), viewport);

        format.setFrameSize(newSize);

        QCOMPARE(format.viewport(), expectedViewport);
        QCOMPARE(format.property("viewport").toRect(), expectedViewport);
    }
    {
        QVideoSurfaceFormat format(initialSize, QVideoFrame::Format_RGB32);

        format.setProperty("viewport", viewport);

        QCOMPARE(format.viewport(), viewport);
        QCOMPARE(format.property("viewport").toRect(), viewport);
    }
}

void tst_QVideoSurfaceFormat::scanLineDirection_data()
{
    QTest::addColumn<QVideoSurfaceFormat::Direction>("direction");
    QTest::addColumn<QString>("stringized");

    ADD_ENUM_TEST(TopToBottom);
    ADD_ENUM_TEST(BottomToTop);
}

void tst_QVideoSurfaceFormat::scanLineDirection()
{
    QFETCH(QVideoSurfaceFormat::Direction, direction);
    QFETCH(QString, stringized);

    {
        QVideoSurfaceFormat format(QSize(16, 16), QVideoFrame::Format_RGB32);

        format.setScanLineDirection(direction);

        QCOMPARE(format.scanLineDirection(), direction);
        QCOMPARE(
                qvariant_cast<QVideoSurfaceFormat::Direction>(format.property("scanLineDirection")),
                direction);
    }
    {
        QVideoSurfaceFormat format(QSize(16, 16), QVideoFrame::Format_RGB32);

        format.setProperty("scanLineDirection", qVariantFromValue(direction));

        QCOMPARE(format.scanLineDirection(), direction);
        QCOMPARE(
                qvariant_cast<QVideoSurfaceFormat::Direction>(format.property("scanLineDirection")),
                direction);
    }

    QTest::ignoreMessage(QtDebugMsg, stringized.toLatin1().constData());
    qDebug() << direction;
}

void tst_QVideoSurfaceFormat::yCbCrColorSpaceEnum_data()
{
    QTest::addColumn<QVideoSurfaceFormat::YCbCrColorSpace>("colorspace");
    QTest::addColumn<QString>("stringized");

    ADD_ENUM_TEST(YCbCr_BT601);
    ADD_ENUM_TEST(YCbCr_BT709);
    ADD_ENUM_TEST(YCbCr_xvYCC601);
    ADD_ENUM_TEST(YCbCr_xvYCC709);
    ADD_ENUM_TEST(YCbCr_JPEG);
    ADD_ENUM_TEST(YCbCr_CustomMatrix);
    ADD_ENUM_TEST(YCbCr_Undefined);
}

/* Test case for Enum YCbCr_BT601, YCbCr_xvYCC709 */
void tst_QVideoSurfaceFormat::yCbCrColorSpaceEnum()
{
    QFETCH(QVideoSurfaceFormat::YCbCrColorSpace, colorspace);
    QFETCH(QString, stringized);

    {
        QVideoSurfaceFormat format(QSize(64, 64), QVideoFrame::Format_RGB32);
        format.setYCbCrColorSpace(colorspace);

        QCOMPARE(format.yCbCrColorSpace(), colorspace);
        QCOMPARE(qvariant_cast<QVideoSurfaceFormat::YCbCrColorSpace>(format.property("yCbCrColorSpace")),
                colorspace);
    }
    {
        QVideoSurfaceFormat format(QSize(64, 64), QVideoFrame::Format_RGB32);
        format.setProperty("yCbCrColorSpace", qVariantFromValue(colorspace));

        QCOMPARE(format.yCbCrColorSpace(), colorspace);
        QCOMPARE(qvariant_cast<QVideoSurfaceFormat::YCbCrColorSpace>(format.property("yCbCrColorSpace")),
                colorspace);
    }

    QTest::ignoreMessage(QtDebugMsg, stringized.toLatin1().constData());
    qDebug() << colorspace;
}


void tst_QVideoSurfaceFormat::frameRate_data()
{
    QTest::addColumn<qreal>("frameRate");

    QTest::newRow("null")
            << qreal(0.0);
    QTest::newRow("1/1")
            << qreal(1.0);
    QTest::newRow("24/1")
            << qreal(24.0);
    QTest::newRow("15/2")
            << qreal(7.5);
}

void tst_QVideoSurfaceFormat::frameRate()
{
    QFETCH(qreal, frameRate);

    {
        QVideoSurfaceFormat format(QSize(64, 64), QVideoFrame::Format_RGB32);

        format.setFrameRate(frameRate);

        QCOMPARE(format.frameRate(), frameRate);
        QCOMPARE(qvariant_cast<qreal>(format.property("frameRate")), frameRate);
    }
    {
        QVideoSurfaceFormat format(QSize(64, 64), QVideoFrame::Format_RGB32);

        format.setFrameRate(frameRate);
        format.setProperty("frameRate", frameRate);

        QCOMPARE(format.frameRate(), frameRate);
        QCOMPARE(qvariant_cast<qreal>(format.property("frameRate")), frameRate);
    }
}

void tst_QVideoSurfaceFormat::pixelAspectRatio_data()
{
    QTest::addColumn<QSize>("aspectRatio");

    QTest::newRow("1:1")
            << QSize(1, 1);
    QTest::newRow("4:3")
            << QSize(4, 3);
    QTest::newRow("16:9")
            << QSize(16, 9);
}

void tst_QVideoSurfaceFormat::pixelAspectRatio()
{
    QFETCH(QSize, aspectRatio);

    {
        QVideoSurfaceFormat format(QSize(64, 64), QVideoFrame::Format_RGB32);
        format.setPixelAspectRatio(aspectRatio);

        QCOMPARE(format.pixelAspectRatio(), aspectRatio);
        QCOMPARE(format.property("pixelAspectRatio").toSize(), aspectRatio);
    }
    {
        QVideoSurfaceFormat format(QSize(64, 64), QVideoFrame::Format_RGB32);
        format.setPixelAspectRatio(aspectRatio.width(), aspectRatio.height());

        QCOMPARE(format.pixelAspectRatio(), aspectRatio);
        QCOMPARE(format.property("pixelAspectRatio").toSize(), aspectRatio);
    }
    {
        QVideoSurfaceFormat format(QSize(64, 64), QVideoFrame::Format_RGB32);
        format.setProperty("pixelAspectRatio", aspectRatio);

        QCOMPARE(format.pixelAspectRatio(), aspectRatio);
        QCOMPARE(format.property("pixelAspectRatio").toSize(), aspectRatio);
    }
}

void tst_QVideoSurfaceFormat::sizeHint_data()
{
    QTest::addColumn<QSize>("frameSize");
    QTest::addColumn<QRect>("viewport");
    QTest::addColumn<QSize>("aspectRatio");
    QTest::addColumn<QSize>("sizeHint");

    QTest::newRow("(0, 0, 1024x768), 1:1")
            << QSize(1024, 768)
            << QRect(0, 0, 1024, 768)
            << QSize(1, 1)
            << QSize(1024, 768);
    QTest::newRow("0, 0, 1024x768), 4:3")
            << QSize(1024, 768)
            << QRect(0, 0, 1024, 768)
            << QSize(4, 3)
            << QSize(1365, 768);
    QTest::newRow("(168, 84, 800x600), 1:1")
        << QSize(1024, 768)
        << QRect(168, 84, 800, 600)
        << QSize(1, 1)
        << QSize(800, 600);
    QTest::newRow("(168, 84, 800x600), 4:3")
        << QSize(1024, 768)
        << QRect(168, 84, 800, 600)
        << QSize(4, 3)
        << QSize(1066, 600);
    QTest::newRow("(168, 84, 800x600), 4:0")
        << QSize(1024, 768)
        << QRect(168, 84, 800, 600)
        << QSize(4, 0)
        << QSize(800, 600);
}

void tst_QVideoSurfaceFormat::sizeHint()
{
    QFETCH(QSize, frameSize);
    QFETCH(QRect, viewport);
    QFETCH(QSize, aspectRatio);
    QFETCH(QSize, sizeHint);

    QVideoSurfaceFormat format(frameSize, QVideoFrame::Format_RGB32);
    format.setViewport(viewport);
    format.setPixelAspectRatio(aspectRatio);

    QCOMPARE(format.sizeHint(), sizeHint);
    QCOMPARE(format.property("sizeHint").toSize(), sizeHint);
}

void tst_QVideoSurfaceFormat::staticPropertyNames()
{
    QVideoSurfaceFormat format(QSize(64, 64), QVideoFrame::Format_RGB32);

    QList<QByteArray> propertyNames = format.propertyNames();

    QVERIFY(propertyNames.contains("handleType"));
    QVERIFY(propertyNames.contains("pixelFormat"));
    QVERIFY(propertyNames.contains("frameSize"));
    QVERIFY(propertyNames.contains("frameWidth"));
    QVERIFY(propertyNames.contains("viewport"));
    QVERIFY(propertyNames.contains("scanLineDirection"));
    QVERIFY(propertyNames.contains("frameRate"));
    QVERIFY(propertyNames.contains("pixelAspectRatio"));
    QVERIFY(propertyNames.contains("yCbCrColorSpace"));
    QVERIFY(propertyNames.contains("sizeHint"));
    QCOMPARE(propertyNames.count(), 10);
}

void tst_QVideoSurfaceFormat::dynamicProperty()
{
    QVideoSurfaceFormat format(QSize(64, 64), QVideoFrame::Format_RGB32);

    QCOMPARE(format.property("integer"), QVariant());
    QCOMPARE(format.property("size"), QVariant());
    QCOMPARE(format.property("string"), QVariant());
    QCOMPARE(format.property("null"), QVariant());

    QList<QByteArray> propertyNames = format.propertyNames();

    QCOMPARE(propertyNames.count(QByteArray("integer")), 0);
    QCOMPARE(propertyNames.count(QByteArray("string")), 0);
    QCOMPARE(propertyNames.count(QByteArray("size")), 0);
    QCOMPARE(propertyNames.count(QByteArray("null")), 0);

    format.setProperty("string", QString::fromLatin1("Hello"));
    format.setProperty("integer", 198);
    format.setProperty("size", QSize(43, 65));

    QCOMPARE(format.property("integer").toInt(), 198);
    QCOMPARE(format.property("size").toSize(), QSize(43, 65));
    QCOMPARE(format.property("string").toString(), QString::fromLatin1("Hello"));

    propertyNames = format.propertyNames();

    QCOMPARE(propertyNames.count(QByteArray("integer")), 1);
    QCOMPARE(propertyNames.count(QByteArray("string")), 1);
    QCOMPARE(propertyNames.count(QByteArray("size")), 1);

    format.setProperty("integer", 125423);
    format.setProperty("size", QSize(1, 986));

    QCOMPARE(format.property("integer").toInt(), 125423);
    QCOMPARE(format.property("size").toSize(), QSize(1, 986));
    QCOMPARE(format.property("string").toString(), QString::fromLatin1("Hello"));

    propertyNames = format.propertyNames();

    QCOMPARE(propertyNames.count(QByteArray("integer")), 1);
    QCOMPARE(propertyNames.count(QByteArray("string")), 1);
    QCOMPARE(propertyNames.count(QByteArray("size")), 1);

    format.setProperty("string", QVariant());
    format.setProperty("size", QVariant());
    format.setProperty("null", QVariant());

    QCOMPARE(format.property("integer").toInt(), 125423);
    QCOMPARE(format.property("size"), QVariant());
    QCOMPARE(format.property("string"), QVariant());
    QCOMPARE(format.property("null"), QVariant());

    propertyNames = format.propertyNames();

    QCOMPARE(propertyNames.count(QByteArray("integer")), 1);
    QCOMPARE(propertyNames.count(QByteArray("string")), 0);
    QCOMPARE(propertyNames.count(QByteArray("size")), 0);
    QCOMPARE(propertyNames.count(QByteArray("null")), 0);
}

void tst_QVideoSurfaceFormat::compare()
{
    QVideoSurfaceFormat format1(
            QSize(16, 16), QVideoFrame::Format_RGB32, QAbstractVideoBuffer::GLTextureHandle);
    QVideoSurfaceFormat format2(
            QSize(16, 16), QVideoFrame::Format_RGB32, QAbstractVideoBuffer::GLTextureHandle);
    QVideoSurfaceFormat format3(
            QSize(32, 32), QVideoFrame::Format_YUV444, QAbstractVideoBuffer::GLTextureHandle);
    QVideoSurfaceFormat format4(
            QSize(16, 16), QVideoFrame::Format_RGB32, QAbstractVideoBuffer::UserHandle);

    QCOMPARE(format1 == format2, true);
    QCOMPARE(format1 != format2, false);
    QCOMPARE(format1 == format3, false);
    QCOMPARE(format1 != format3, true);
    QCOMPARE(format1 == format4, false);
    QCOMPARE(format1 != format4, true);

    format2.setFrameSize(1024, 768);

    // Not equal, frame size differs.
    QCOMPARE(format1 == format2, false);
    QCOMPARE(format1 != format2, true);

    format1.setFrameSize(1024, 768);

    // Equal.
    QCOMPARE(format1 == format2, true);
    QCOMPARE(format1 != format2, false);

    format1.setViewport(QRect(0, 0, 800, 600));
    format2.setViewport(QRect(112, 84, 800, 600));

    // Not equal, viewports differ.
    QCOMPARE(format1 == format2, false);
    QCOMPARE(format1 != format2, true);

    format1.setViewport(QRect(112, 84, 800, 600));

    // Equal.
    QCOMPARE(format1 == format2, true);
    QCOMPARE(format1 != format2, false);

    format2.setScanLineDirection(QVideoSurfaceFormat::BottomToTop);

    // Not equal scan line direction differs.
    QCOMPARE(format1 == format2, false);
    QCOMPARE(format1 != format2, true);

    format1.setScanLineDirection(QVideoSurfaceFormat::BottomToTop);

    // Equal.
    QCOMPARE(format1 == format2, true);
    QCOMPARE(format1 != format2, false);

    format1.setFrameRate(7.5);

    // Not equal frame rate differs.
    QCOMPARE(format1 == format2, false);
    QCOMPARE(format1 != format2, true);

    format2.setFrameRate(qreal(7.50001));

    // Equal.
    QCOMPARE(format1 == format2, true);
    QCOMPARE(format1 != format2, false);

    format2.setPixelAspectRatio(4, 3);

    // Not equal pixel aspect ratio differs.
    QCOMPARE(format1 == format2, false);
    QCOMPARE(format1 != format2, true);

    format1.setPixelAspectRatio(QSize(4, 3));

    // Equal.
    QCOMPARE(format1 == format2, true);
    QCOMPARE(format1 != format2, false);

    format2.setYCbCrColorSpace(QVideoSurfaceFormat::YCbCr_xvYCC601);

    // Not equal yuv color space differs.
    QCOMPARE(format1 == format2, false);
    QCOMPARE(format1 != format2, true);

    format1.setYCbCrColorSpace(QVideoSurfaceFormat::YCbCr_xvYCC601);

    // Equal.
    QCOMPARE(format1 == format2, true);
    QCOMPARE(format1 != format2, false);

    format1.setProperty("integer", 12);

    // Not equal, property mismatch.
    QCOMPARE(format1 == format2, false);
    QCOMPARE(format1 != format2, true);

    format2.setProperty("integer", 45);

    // Not equal, integer differs.
    QCOMPARE(format1 == format2, false);
    QCOMPARE(format1 != format2, true);

    format2.setProperty("integer", 12);

    // Equal.
    QCOMPARE(format1 == format2, true);
    QCOMPARE(format1 != format2, false);

    format1.setProperty("string", QString::fromLatin1("Hello"));
    format2.setProperty("size", QSize(12, 54));

    // Not equal, property mismatch.
    QCOMPARE(format1 == format2, false);
    QCOMPARE(format1 != format2, true);

    format2.setProperty("string", QString::fromLatin1("Hello"));
    format1.setProperty("size", QSize(12, 54));

    // Equal.
    QCOMPARE(format1 == format2, true);
    QCOMPARE(format1 != format2, false);

    format1.setProperty("string", QVariant());

    // Not equal, property mismatch.
    QCOMPARE(format1 == format2, false);
    QCOMPARE(format1 != format2, true);
}


void tst_QVideoSurfaceFormat::copy()
{
    QVideoSurfaceFormat original(
            QSize(1024, 768), QVideoFrame::Format_ARGB32, QAbstractVideoBuffer::GLTextureHandle);
    original.setScanLineDirection(QVideoSurfaceFormat::BottomToTop);

    QVideoSurfaceFormat copy(original);

    QCOMPARE(copy.handleType(), QAbstractVideoBuffer::GLTextureHandle);
    QCOMPARE(copy.pixelFormat(), QVideoFrame::Format_ARGB32);
    QCOMPARE(copy.frameSize(), QSize(1024, 768));
    QCOMPARE(copy.scanLineDirection(), QVideoSurfaceFormat::BottomToTop);

    QCOMPARE(original == copy, true);
    QCOMPARE(original != copy, false);

    copy.setScanLineDirection(QVideoSurfaceFormat::TopToBottom);

    QCOMPARE(copy.scanLineDirection(), QVideoSurfaceFormat::TopToBottom);

    QCOMPARE(original.scanLineDirection(), QVideoSurfaceFormat::BottomToTop);

    QCOMPARE(original == copy, false);
    QCOMPARE(original != copy, true);
}

void tst_QVideoSurfaceFormat::assign()
{
    QVideoSurfaceFormat copy(
            QSize(64, 64), QVideoFrame::Format_AYUV444, QAbstractVideoBuffer::UserHandle);

    QVideoSurfaceFormat original(
            QSize(1024, 768), QVideoFrame::Format_ARGB32, QAbstractVideoBuffer::GLTextureHandle);
    original.setScanLineDirection(QVideoSurfaceFormat::BottomToTop);

    copy = original;

    QCOMPARE(copy.handleType(), QAbstractVideoBuffer::GLTextureHandle);
    QCOMPARE(copy.pixelFormat(), QVideoFrame::Format_ARGB32);
    QCOMPARE(copy.frameSize(), QSize(1024, 768));
    QCOMPARE(copy.scanLineDirection(), QVideoSurfaceFormat::BottomToTop);

    QCOMPARE(original == copy, true);
    QCOMPARE(original != copy, false);

    copy.setScanLineDirection(QVideoSurfaceFormat::TopToBottom);

    QCOMPARE(copy.scanLineDirection(), QVideoSurfaceFormat::TopToBottom);

    QCOMPARE(original.scanLineDirection(), QVideoSurfaceFormat::BottomToTop);

    QCOMPARE(original == copy, false);
    QCOMPARE(original != copy, true);
}

/* Test case for api isValid */
void tst_QVideoSurfaceFormat::isValid()
{
    /* When both pixel format and framesize is not valid */
    QVideoSurfaceFormat format;
    QVERIFY(!format.isValid());

    /* When framesize is valid and pixel format is not valid */
    format.setFrameSize(64,64);
    QVERIFY(format.frameSize() == QSize(64,64));
    QVERIFY(!format.pixelFormat());
    QVERIFY(!format.isValid());

    /* When both the pixel format and framesize is valid. */
    QVideoSurfaceFormat format1(QSize(32, 32), QVideoFrame::Format_AYUV444);
    QVERIFY(format1.isValid());

    /* When pixel format is valid and frame size is not valid */
    format1.setFrameSize(-1,-1);
    QVERIFY(!format1.frameSize().isValid());
    QVERIFY(!format1.isValid());
}

/* Test case for copy constructor with all the parameters. */
void tst_QVideoSurfaceFormat::copyAllParameters()
{
    /* Create the instance and set all the parameters. */
    QVideoSurfaceFormat original(
            QSize(1024, 768), QVideoFrame::Format_ARGB32, QAbstractVideoBuffer::GLTextureHandle);

    original.setScanLineDirection(QVideoSurfaceFormat::BottomToTop);
    original.setViewport(QRect(0, 0, 1024, 1024));
    original.setFrameRate(qreal(15.0));
    original.setPixelAspectRatio(QSize(320,480));
    original.setYCbCrColorSpace(QVideoSurfaceFormat::YCbCr_BT709);

    /* Copy the original instance to copy and verify if both the instances
      have the same parameters. */
    QVideoSurfaceFormat copy(original);

    QCOMPARE(copy.handleType(), QAbstractVideoBuffer::GLTextureHandle);
    QCOMPARE(copy.pixelFormat(), QVideoFrame::Format_ARGB32);
    QCOMPARE(copy.frameSize(), QSize(1024, 768));
    QCOMPARE(copy.scanLineDirection(), QVideoSurfaceFormat::BottomToTop);
    QCOMPARE(copy.viewport(), QRect(0, 0, 1024, 1024));
    QCOMPARE(copy.frameRate(), qreal(15.0));
    QCOMPARE(copy.pixelAspectRatio(), QSize(320,480));
    QCOMPARE(copy.yCbCrColorSpace(), QVideoSurfaceFormat::YCbCr_BT709);

    /* Verify if both the instances are eqaul */
    QCOMPARE(original == copy, true);
    QCOMPARE(original != copy, false);
}

/* Test case for copy constructor with all the parameters. */
void tst_QVideoSurfaceFormat::assignAllParameters()
{
    /* Create the instance and set all the parameters. */
    QVideoSurfaceFormat copy(
            QSize(64, 64), QVideoFrame::Format_AYUV444, QAbstractVideoBuffer::UserHandle);
    copy.setScanLineDirection(QVideoSurfaceFormat::TopToBottom);
    copy.setViewport(QRect(0, 0, 640, 320));
    copy.setFrameRate(qreal(7.5));
    copy.setPixelAspectRatio(QSize(640,320));
    copy.setYCbCrColorSpace(QVideoSurfaceFormat::YCbCr_BT601);

    /* Create the instance and set all the parameters. */
    QVideoSurfaceFormat original(
            QSize(1024, 768), QVideoFrame::Format_ARGB32, QAbstractVideoBuffer::GLTextureHandle);
    original.setScanLineDirection(QVideoSurfaceFormat::BottomToTop);
    original.setViewport(QRect(0, 0, 1024, 1024));
    original.setFrameRate(qreal(15.0));
    original.setPixelAspectRatio(QSize(320,480));
    original.setYCbCrColorSpace(QVideoSurfaceFormat::YCbCr_BT709);

    /* Assign the original instance to copy and verify if both the instancess
      have the same parameters. */
    copy = original;

    QCOMPARE(copy.handleType(), QAbstractVideoBuffer::GLTextureHandle);
    QCOMPARE(copy.pixelFormat(), QVideoFrame::Format_ARGB32);
    QCOMPARE(copy.frameSize(), QSize(1024, 768));
    QCOMPARE(copy.scanLineDirection(), QVideoSurfaceFormat::BottomToTop);
    QCOMPARE(copy.viewport(), QRect(0, 0, 1024, 1024));
    QCOMPARE(copy.frameRate(), qreal(15.0));
    QCOMPARE(copy.pixelAspectRatio(), QSize(320,480));
    QCOMPARE(copy.yCbCrColorSpace(), QVideoSurfaceFormat::YCbCr_BT709);

     /* Verify if both the instances are eqaul */
    QCOMPARE(original == copy, true);
    QCOMPARE(original != copy, false);
}

void tst_QVideoSurfaceFormat::propertyEdgeCases()
{
    // Test setting read only properties doesn't change anything
    QVideoSurfaceFormat original(
            QSize(1024, 768), QVideoFrame::Format_ARGB32, QAbstractVideoBuffer::GLTextureHandle);

    original.setProperty("handleType", QAbstractVideoBuffer::UserHandle);
    QCOMPARE(original.handleType(), QAbstractVideoBuffer::GLTextureHandle);

    original.setProperty("pixelFormat", QVideoFrame::Format_AYUV444);
    QCOMPARE(original.pixelFormat(), QVideoFrame::Format_ARGB32);

    original.setProperty("frameWidth", 512);
    QCOMPARE(original.frameWidth(), 1024);

    original.setProperty("frameHeight", 77);
    QCOMPARE(original.frameHeight(), 768);

    original.setProperty("sizeHint", QSize(512, 384));
    QCOMPARE(original.sizeHint(), QSize(1024,768));

    // Now test setting some r/w properties with the wrong data type
    original.setProperty("frameSize", Qt::red);
    QCOMPARE(original.frameSize(), QSize(1024, 768));

    original.setProperty("viewport", Qt::red);
    QCOMPARE(original.viewport(), QRect(0, 0, 1024, 768));

    original.setScanLineDirection(QVideoSurfaceFormat::BottomToTop);
    original.setProperty("scanLineDirection", Qt::red);
    QCOMPARE(original.scanLineDirection(), QVideoSurfaceFormat::BottomToTop);

    original.setFrameRate(32);
    original.setProperty("frameRate", QSize(32, 43));
    QCOMPARE(original.frameRate(), qreal(32));

    original.setYCbCrColorSpace(QVideoSurfaceFormat::YCbCr_BT709);
    original.setProperty("yCbCrColorSpace", QSize(43,43));
    QCOMPARE(original.yCbCrColorSpace(), QVideoSurfaceFormat::YCbCr_BT709);

    original.setPixelAspectRatio(53, 45);
    original.setProperty("pixelAspectRatio", Qt::red);
    QCOMPARE(original.pixelAspectRatio(), QSize(53, 45));
}

#define ADDDEBUGTEST(format, w, h, r) \
    QTest::newRow(#format "-" #w "x" #h "@" #r) \
        << QVideoFrame::Format_ ##format \
        << "Format_" #format \
        << QSize(w, h) \
        << r;

void tst_QVideoSurfaceFormat::debugOperator_data()
{
    // This is not too exhaustive
    QTest::addColumn<QVideoFrame::PixelFormat>("format");
    QTest::addColumn<QString>("formatString");
    QTest::addColumn<QSize>("frameSize");
    QTest::addColumn<int>("frameRate"); // could be double, but formatting is unstable

    ADDDEBUGTEST(Invalid, 100, 200, 3);
    ADDDEBUGTEST(ARGB32,101, 201, 4);
    ADDDEBUGTEST(ARGB32_Premultiplied, 100, 202, 5);
    ADDDEBUGTEST(RGB32, 8, 16, 30);
    ADDDEBUGTEST(RGB24, 8, 16, 30);
    ADDDEBUGTEST(RGB565, 8, 16, 30);
    ADDDEBUGTEST(RGB555, 8, 16, 30);
    ADDDEBUGTEST(ARGB8565_Premultiplied, 8, 16, 30);
    ADDDEBUGTEST(BGRA32, 8, 16, 30);
    ADDDEBUGTEST(BGRA32_Premultiplied, 8, 16, 30);
    ADDDEBUGTEST(BGR32, 8, 16, 30);
    ADDDEBUGTEST(BGR24, 8, 16, 30);
    ADDDEBUGTEST(BGR565, 8, 16, 30);
    ADDDEBUGTEST(BGR555, 8, 16, 30);
    ADDDEBUGTEST(BGRA5658_Premultiplied, 8, 16, 30);

    ADDDEBUGTEST(AYUV444, 8, 16, 30);
    ADDDEBUGTEST(AYUV444, 8, 16, 31);
    ADDDEBUGTEST(AYUV444_Premultiplied, 8, 16, 30);
    ADDDEBUGTEST(YUV444, 8, 16, 30);
    ADDDEBUGTEST(YUV420P, 8, 16, 30);
    ADDDEBUGTEST(YV12, 8, 16, 30);
    ADDDEBUGTEST(UYVY, 8, 16, 30);
    ADDDEBUGTEST(YUYV, 8, 16, 30);
    ADDDEBUGTEST(NV12, 8, 16, 30);
    ADDDEBUGTEST(NV12, 80, 16, 30);
    ADDDEBUGTEST(NV21, 8, 16, 30);
    ADDDEBUGTEST(IMC1, 8, 16, 30);
    ADDDEBUGTEST(IMC2, 8, 16, 30);
    ADDDEBUGTEST(IMC3, 8, 16, 30);
    ADDDEBUGTEST(IMC3, 8, 160, 30);
    ADDDEBUGTEST(IMC4, 8, 16, 30);
    ADDDEBUGTEST(Y8, 8, 16, 30);
    ADDDEBUGTEST(Y16, 8, 16, 30);

    ADDDEBUGTEST(Jpeg, 8, 16, 30);

    ADDDEBUGTEST(CameraRaw, 8, 16, 30);
    ADDDEBUGTEST(AdobeDng, 8, 16, 30);

    // User is special
    QTest::newRow("User-0x0@0)")
                  << QVideoFrame::Format_User
                  << "UserType(1000)"
                  << QSize()
                  << 0;
}

void tst_QVideoSurfaceFormat::debugOperator()
{
    QFETCH(QVideoFrame::PixelFormat, format);
    QFETCH(QString, formatString);
    QFETCH(QSize, frameSize);
    QFETCH(int, frameRate);

    QString templateOutput = QString("QVideoSurfaceFormat(%1, QSize(%2, %3) , viewport=QRect(0,1 800x600) , pixelAspectRatio=QSize(320, 200) "
        ", handleType=GLTextureHandle, yCbCrColorSpace=YCbCr_BT709)\n"
        "    handleType = QVariant(QAbstractVideoBuffer::HandleType, ) \n"
        "     pixelFormat  =  QVariant(QVideoFrame::PixelFormat, ) \n"
        "     frameSize  =  QVariant(QSize, QSize(%4, %5) ) \n"
        "     frameWidth  =  QVariant(int, %6) \n"
        "     viewport  =  QVariant(QRect, QRect(0,1 800x600) ) \n"
        "     scanLineDirection  =  QVariant(QVideoSurfaceFormat::Direction, ) \n"
#if defined(QT_ARCH_ARM) // from qglobal.h
        "     frameRate  =  QVariant(float, %7) \n"
#else
        "     frameRate  =  QVariant(double, %7) \n"
#endif
        "     pixelAspectRatio  =  QVariant(QSize, QSize(320, 200) ) \n"
        "     sizeHint  =  QVariant(QSize, QSize(1280, 600) ) \n"
        "     yCbCrColorSpace  =  QVariant(QVideoSurfaceFormat::YCbCrColorSpace, )  ")
            .arg(formatString)
            .arg(frameSize.width())
            .arg(frameSize.height())
            .arg(frameSize.width())
            .arg(frameSize.height())
            .arg(frameSize.width())
            .arg(frameRate);

    QVideoSurfaceFormat vsf(frameSize, format, QAbstractVideoBuffer::GLTextureHandle);
    vsf.setViewport(QRect(0,1, 800, 600));
    vsf.setPixelAspectRatio(QSize(320, 200));
    vsf.setYCbCrColorSpace(QVideoSurfaceFormat::YCbCr_BT709);
    vsf.setFrameRate(frameRate);

    QTest::ignoreMessage(QtDebugMsg, templateOutput.toLatin1().constData());
    qDebug() << vsf;
}



QTEST_MAIN(tst_QVideoSurfaceFormat)



#include "tst_qvideosurfaceformat.moc"
