/****************************************************************************
**
** Copyright (C) 2011 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** You may use this file under the terms of the BSD license as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of Nokia Corporation and its Subsidiary(-ies) nor
**     the names of its contributors may be used to endorse or promote
**     products derived from this software without specific prior written
**     permission.
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
** $QT_END_LICENSE$
**
****************************************************************************/

#include <QtGui>

#include "scribblearea.h"

//! [0]
ScribbleArea::ScribbleArea(QWidget *parent)
    : QWidget(parent)
{
    setAttribute(Qt::WA_StaticContents);
    modified = false;
    scribbling = false;
    myPenWidth = 1;
    myPenColor = Qt::blue;


    ///////////////////////////////////////
/*
    QImage loadedImage;
  //  QImage loadedImage(300, 300, QImage::Format_Mono);
  //  loadedImage = QImage("Gnome3DBlue");
    loadedImage = QImage("image.png");  //test_0624_01

   // loadedImage = QImage("testbmpindex8_0624_0.bmp");

   //  loadedImage = loadedImage.convertToFormat(QImage::Format_RGB16 );

    image = loadedImage;

    update();
*/
    /////////////////////////////////////////

  //  QImage baseImage("Gnome3DBlue.png");
     QImage baseImage("image.png");
    //   QImage overlayLogoff("image.png");
       QImage overlayLogoff("test0628_02.png");
       QImage logoffImage = createImageWithOverlay(baseImage, overlayLogoff);

       image = logoffImage;

       update();

     //////////////////////////////////////
}
//! [0]

//! [1]
bool ScribbleArea::openImage(const QString &fileName)
//! [1] //! [2]
{
    QImage loadedImage;
    if (!loadedImage.load(fileName))
        return false;

    QSize newSize = loadedImage.size().expandedTo(size());
    resizeImage(&loadedImage, newSize);
    image = loadedImage;
    modified = false;
    update();
    return true;
}
//! [2]

//! [3]
bool ScribbleArea::saveImage(const QString &fileName, const char *fileFormat)
//! [3] //! [4]
{
    QImage visibleImage = image;
   // resizeImage(&visibleImage, size());
  //   visibleImage = visibleImage.convertToFormat(QImage::Format(3) );
  //   visibleImage = visibleImage.convertToFormat(QImage::Format_Indexed8 );
  //   visibleImage = visibleImage.convertToFormat(QImage::Format_MonoLSB );

    if (visibleImage.save(fileName, fileFormat)) {
        modified = false;
        return true;
    } else {
        return false;
    }

}
//! [4]

//! [5]
void ScribbleArea::setPenColor(const QColor &newColor)
//! [5] //! [6]
{
    myPenColor = newColor;
}
//! [6]

//! [7]
void ScribbleArea::setPenWidth(int newWidth)
//! [7] //! [8]
{
    myPenWidth = newWidth;
}
//! [8]

//! [9]
void ScribbleArea::clearImage()
//! [9] //! [10]
{
    image.fill(qRgb(255, 255, 255));
    modified = true;
    update();

    ///////////////////////////////////////
    QImage loadedImage;
    loadedImage = QImage("image.png");

    image = loadedImage;

    update();
    /////////////////////////////////////////

}
//! [10]

//! [11]
void ScribbleArea::mousePressEvent(QMouseEvent *event)
//! [11] //! [12]
{
    if (event->button() == Qt::LeftButton) {
        lastPoint = event->pos();
        scribbling = true;
    }
}

void ScribbleArea::mouseMoveEvent(QMouseEvent *event)
{
    if ((event->buttons() & Qt::LeftButton) && scribbling)
        drawLineTo(event->pos());
}

void ScribbleArea::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton && scribbling) {
        drawLineTo(event->pos());
        scribbling = false;
    }
}

//! [12] //! [13]
void ScribbleArea::paintEvent(QPaintEvent *event)
//! [13] //! [14]
{

    /////////////////////////////////////

 //   QImage img;
  //  QImage img2;
  //  QRgb value;
    QPainter painter(this);
  //  int x,y;
  //  int w,h;
 //   w= this->width();
 //   h=this->height();
 //   painter.begin(this);
    //img=QImage(320,240,QImage::Format_RGB32);
 //   img = QImage("image.png");

  // painter.drawImage(0,0,img);
  //  painter.end();
    /////////////////////////////////////



  //  QPainter painter(this);
    QRect dirtyRect = event->rect();
   //  painter.drawImage(dirtyRect, img, dirtyRect);
    painter.drawImage(dirtyRect, image, dirtyRect);

    /*
    QPicture picture;

   // QPainter painter;
    painter.begin(&picture);           // paint in picture
    painter.drawEllipse(10,20, 80,70); // draw an ellipse
    painter.end();                     // painting done
    picture.save("drawing.pic");       // save picture
   */

  //  QPicture picture;
  //         picture.load("drawing.pic");           // load picture
        //   QPainter painter;
       //    painter.begin(&picture);               // paint in myImage
   //        painter.drawPicture(0, 0, picture);    // draw the picture at (0,0)
      //     painter.end();                         // painting done

}
//! [14]

//! [15]
void ScribbleArea::resizeEvent(QResizeEvent *event)
//! [15] //! [16]
{
    if (width() > image.width() || height() > image.height()) {
        int newWidth = qMax(width() + 128, image.width());
        int newHeight = qMax(height() + 128, image.height());
     //   int newWidth = qMax(width() , image.width());
     //   int newHeight = qMax(height(), image.height());

        resizeImage(&image, QSize(newWidth, newHeight));
        update();
    }
    QWidget::resizeEvent(event);
}
//! [16]

//! [17]
void ScribbleArea::drawLineTo(const QPoint &endPoint)
//! [17] //! [18]
{
    QPainter painter(&image);

    /////////////////////////////


    /////////////////////////////
    painter.setPen(QPen(myPenColor, myPenWidth, Qt::SolidLine, Qt::RoundCap,
                        Qt::RoundJoin));
    painter.drawLine(lastPoint, endPoint);
    modified = true;

  //  int rad = (myPenWidth / 2) + 2;
   // update(QRect(lastPoint, endPoint).normalized()
   //                                  .adjusted(-rad, -rad, +rad, +rad));
    update();

    lastPoint = endPoint;
}
//! [18]

//! [19]
void ScribbleArea::resizeImage(QImage *image, const QSize &newSize)
//! [19] //! [20]
{
    if (image->size() == newSize)
        return;

    QImage newImage(newSize, QImage::Format_RGB32);
    newImage.fill(qRgb(255, 255, 255));
    QPainter painter(&newImage);
    painter.drawImage(QPoint(0, 0), *image);
    *image = newImage;
}
//! [20]

//! [21]
void ScribbleArea::print()
{
#ifndef QT_NO_PRINTER
    QPrinter printer(QPrinter::HighResolution);
 
    QPrintDialog *printDialog = new QPrintDialog(&printer, this);
//! [21] //! [22]
    if (printDialog->exec() == QDialog::Accepted) {
        QPainter painter(&printer);
        QRect rect = painter.viewport();
        QSize size = image.size();
        size.scale(rect.size(), Qt::KeepAspectRatio);
        painter.setViewport(rect.x(), rect.y(), size.width(), size.height());
        painter.setWindow(image.rect());
        painter.drawImage(0, 0, image);
    }
#endif // QT_NO_PRINTER
}
//! [22]


QImage ScribbleArea::createImageWithOverlay(const QImage& baseImage, const QImage& overlayImage)
{
    QImage imageWithOverlay = QImage(baseImage.size(), QImage::Format_ARGB32_Premultiplied);
    QPainter painter(&imageWithOverlay);

    painter.setCompositionMode(QPainter::CompositionMode_Source);
    painter.fillRect(imageWithOverlay.rect(), Qt::transparent);
   //  painter.fillRect(imageWithOverlay.rect(), Qt::white);


    painter.setCompositionMode(QPainter::CompositionMode_SourceOver);
    painter.drawImage(0, 0, baseImage);

   // painter.setCompositionMode(QPainter::CompositionMode_SourceOver);
   // painter.setCompositionMode(QPainter::CompositionMode_Multiply);//CompositionMode_SourceOut);//CompositionMode_DestinationOver);//CompositionMode_Clear);//CompositionMode_Exclusion); //CompositionMode_Overlay);  //CompositionMode_Xor);
  //   painter.setCompositionMode(QPainter::RasterOp_SourceAndDestination);//RasterOp_SourceOrDestination);//CompositionMode_Exclusion);//CompositionMode_ColorBurn);//CompositionMode_ColorDodge);//CompositionMode_Darken);//CompositionMode_Screen);
     painter.setCompositionMode(QPainter::CompositionMode_Darken);//RasterOp_SourceAndNotDestination);//RasterOp_NotSourceAndDestination);//RasterOp_NotSource);//RasterOp_NotSourceXorDestination);//RasterOp_NotSourceAndNotDestination);//RasterOp_SourceXorDestination);

    painter.drawImage(0, 0, overlayImage);

    painter.end();

    return imageWithOverlay;
}
