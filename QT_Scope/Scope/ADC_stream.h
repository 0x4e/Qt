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
 * @file packet.h
 * @brief processes serial data using a defined packet structure.
 *
 * 
 *
 *
 * @author Nick Masson
 * @bug No known bugs
 *
 */
#ifndef ADC_STREAM_H
#define ADC_STREAM_H

#include <QObject>
#include <QTimer>
#include <QVector>
#include <QUdpSocket>
#include "circular_buffer.h"

class ADC_stream : public QObject
{
    Q_OBJECT
public:
    explicit ADC_stream(QObject *parent = 0);
    ~ADC_stream();
    void startUdpConnection(QHostAddress ip, int port);
    void stopUdpConnection();
    bool isUdpConnected();

signals:
    void dataToSend(QByteArray &data);
    void update_console(QString text_string);
    void samplesReceived();
    
public slots:
    void readPendingDatagrams();

private:
    QTimer *mTimer;
    quint8 *mSendBuffer;
    QUdpSocket *mUdpSocket;
    QHostAddress mHostAddress;
    int mUdpPort;

    // Packet state machine variables
    static const unsigned int mMaxBufferLen = 4096;
    void processPacket(const unsigned char *data, int len);

};

#endif // ADC_STREAM_H
