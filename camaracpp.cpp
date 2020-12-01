#include "camaracpp.h"

CamaraCPP::CamaraCPP(QQuickItem *parent)
    : QQuickPaintedItem(parent)
{
    CamaraDevice *camaraDevice;

    listarCamaras();
    camaraDevice=listaDevices.at(0);
    activarCamara(camaraDevice->deviceName);
}

void CamaraCPP::paint(QPainter *painter)
{
    painter->setRenderHints(QPainter::Antialiasing, true);
    painter->drawPixmap(boundingRect().adjusted(1, 1, -1, -1), qPixmapStream, qPixmapStream.rect());
    painter->drawPixmap(0, 0, qPixmapStream);
}

void CamaraCPP::listarCamaras()
{
    listaDevices.clear();
    QList<QCameraInfo> cameras = QCameraInfo::availableCameras();
    foreach (const QCameraInfo &cameraInfo, cameras)
    {
        CamaraDevice *camaraDevice;
        camaraDevice = new CamaraDevice;
        camaraDevice->description=cameraInfo.description();
        camaraDevice->deviceName=cameraInfo.deviceName();
        listaDevices.append(camaraDevice);
    }
}

void CamaraCPP::crearCamara(QByteArray deviceName)
{
    destruirCamara();
    camara = new QCamera(deviceName,this);
    qVideoSurfaceStream = new QVideoSurfaceStream(this);
    camara->setViewfinder(qVideoSurfaceStream);
    camara->setCaptureMode(QCamera::CaptureStillImage);
}

void CamaraCPP::destruirCamara()
{
    delete qVideoSurfaceStream;
    delete camara;
    qVideoSurfaceStream=nullptr;
    camara=nullptr;
}

void CamaraCPP::activarCamara(QString deviceName)
{
    crearCamara(deviceName.toUtf8());
    QObject::connect(qVideoSurfaceStream, &QVideoSurfaceStream::frameReady, this, &CamaraCPP::slotFrameReady);
    camara->start();
}

void CamaraCPP::desactivarCamara()
{
    camara->stop();
    QObject::disconnect(qVideoSurfaceStream, &QVideoSurfaceStream::frameReady, this, &CamaraCPP::slotFrameReady);
    destruirCamara();
}

void CamaraCPP::slotFrameReady(QPixmap qPixmap)
{
    qPixmapStream=qPixmap.copy();
    this->update(); // provocar el paint
}
