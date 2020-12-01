#ifndef CAMARACPP_H
#define CAMARACPP_H

#include <QQuickItem>
#include <QtQuick/QQuickPaintedItem>
#include <QPainter>
#include <QCamera>
#include <QCameraViewfinder>
#include <QCameraImageCapture>
#include <QImageEncoderSettings>
#include <QCameraInfo>
#include "qvideosurfacestream.h"

class CamaraDevice {
public:
    CamaraDevice()
    {
        description="";
        deviceName="";
    }

    QString description;
    QString deviceName;
};

class CamaraCPP : public QQuickPaintedItem
{
public:
    CamaraCPP(QQuickItem *parent = nullptr);
    void paint(QPainter *painter);
    void listarCamaras();
    void crearCamara(QByteArray deviceName);
    void destruirCamara();
    void activarCamara(QString deviceName);
    void desactivarCamara();

    QList<CamaraDevice*> listaDevices;
    QPixmap qPixmapStream;

    QCamera *camara;
    QCameraImageCapture *camaraImageCapture;
    QImageEncoderSettings imageEncoderSettings;
    QVideoSurfaceStream *qVideoSurfaceStream;

public slots:
    void slotFrameReady(QPixmap qPixmap);
};

#endif // CAMARACPP_H
