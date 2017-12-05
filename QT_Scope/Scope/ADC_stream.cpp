/***
 *          ___          ___
 *         /\  \        /\  \
 *         \:\  \      |::\  \
 *          \:\  \     |:|:\  \
 *      _____\:\  \  __|:|\:\  \
 *     /::::::::\__\/::::|_\:\__\
 *     \:\~~\~~\/__/\:\~~\  \/__/
 *      \:\  \       \:\  \
 *       \:\  \       \:\  \
 *        \:\__\       \:\__\
 *         \/__/        \/__/
 *
 * @file packet.c
 * @brief processes serial data using a defined packet structure.
 *
 * 
 *
 *
 * @author Nick Masson
 * @bug No known bugs
 *
 */

#include "ADC_stream.h"

#include <QDebug>

ADC_stream::ADC_stream(QObject *parent) :
    QObject(parent)
{

    mTimer = new QTimer(this);
    mTimer->setInterval(10);
    mTimer->start();

    mHostAddress = QHostAddress("192.168.1.110");
    mUdpPort = 9989;
    mUdpSocket = new QUdpSocket(this);

    connect(mUdpSocket, SIGNAL(readyRead()),
            this, SLOT(readPendingDatagrams()));

    qDebug() << "jjjdjd";

    this->startUdpConnection(mHostAddress, mUdpPort);

}

ADC_stream::~ADC_stream()
{
    //delete mSendBuffer;
}


void ADC_stream::readPendingDatagrams()
{
    while (mUdpSocket->hasPendingDatagrams()) {
        QByteArray datagram;
        datagram.resize(mUdpSocket->pendingDatagramSize());
        QHostAddress sender;
        quint16 senderPort;

        mUdpSocket->readDatagram(datagram.data(), datagram.size(),
                                &sender, &senderPort);

        processPacket((unsigned char*)datagram.data(), datagram.length());
        //qDebug() << datagram.data();

    }
}

void ADC_stream::processPacket(const unsigned char *data, int len)
{
    u_int16_t  Ch1, Ch2;
    static u_int16_t count = 0;

    for (int i = 0;i < len ;i+=4) {
         Ch1 = ((data[i+1] << 8) | data[i]);
         Ch2 = ((data[i+3] << 8) | data[i+2]);

         cb_update(Ch1, Ch2);
    }
    count++;

    emit samplesReceived();
}

void ADC_stream::startUdpConnection(QHostAddress ip, int port)
{
    mHostAddress = ip;
    mUdpPort = port;
    mUdpSocket->close();
    mUdpSocket->bind(QHostAddress::Any, mUdpPort + 1);
}

void ADC_stream::stopUdpConnection()
{
    mHostAddress = QHostAddress("0.0.0.0");
    mUdpPort = 0;
    mUdpSocket->close();
}

bool ADC_stream::isUdpConnected()
{
    return QString::compare(mHostAddress.toString(), "0.0.0.0") != 0;
}
