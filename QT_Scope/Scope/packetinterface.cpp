/*
    Copyright 2012-2014 Benjamin Vedder	benjamin@vedder.se

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
    */

#include "packetinterface.h"
#include "utility.h"
#include <QDebug>
#include <math.h>

namespace {
// CRC Table
const unsigned short crc16_tab[] = { 0x0000, 0x1021, 0x2042, 0x3063, 0x4084,
        0x50a5, 0x60c6, 0x70e7, 0x8108, 0x9129, 0xa14a, 0xb16b, 0xc18c, 0xd1ad,
        0xe1ce, 0xf1ef, 0x1231, 0x0210, 0x3273, 0x2252, 0x52b5, 0x4294, 0x72f7,
        0x62d6, 0x9339, 0x8318, 0xb37b, 0xa35a, 0xd3bd, 0xc39c, 0xf3ff, 0xe3de,
        0x2462, 0x3443, 0x0420, 0x1401, 0x64e6, 0x74c7, 0x44a4, 0x5485, 0xa56a,
        0xb54b, 0x8528, 0x9509, 0xe5ee, 0xf5cf, 0xc5ac, 0xd58d, 0x3653, 0x2672,
        0x1611, 0x0630, 0x76d7, 0x66f6, 0x5695, 0x46b4, 0xb75b, 0xa77a, 0x9719,
        0x8738, 0xf7df, 0xe7fe, 0xd79d, 0xc7bc, 0x48c4, 0x58e5, 0x6886, 0x78a7,
        0x0840, 0x1861, 0x2802, 0x3823, 0xc9cc, 0xd9ed, 0xe98e, 0xf9af, 0x8948,
        0x9969, 0xa90a, 0xb92b, 0x5af5, 0x4ad4, 0x7ab7, 0x6a96, 0x1a71, 0x0a50,
        0x3a33, 0x2a12, 0xdbfd, 0xcbdc, 0xfbbf, 0xeb9e, 0x9b79, 0x8b58, 0xbb3b,
        0xab1a, 0x6ca6, 0x7c87, 0x4ce4, 0x5cc5, 0x2c22, 0x3c03, 0x0c60, 0x1c41,
        0xedae, 0xfd8f, 0xcdec, 0xddcd, 0xad2a, 0xbd0b, 0x8d68, 0x9d49, 0x7e97,
        0x6eb6, 0x5ed5, 0x4ef4, 0x3e13, 0x2e32, 0x1e51, 0x0e70, 0xff9f, 0xefbe,
        0xdfdd, 0xcffc, 0xbf1b, 0xaf3a, 0x9f59, 0x8f78, 0x9188, 0x81a9, 0xb1ca,
        0xa1eb, 0xd10c, 0xc12d, 0xf14e, 0xe16f, 0x1080, 0x00a1, 0x30c2, 0x20e3,
        0x5004, 0x4025, 0x7046, 0x6067, 0x83b9, 0x9398, 0xa3fb, 0xb3da, 0xc33d,
        0xd31c, 0xe37f, 0xf35e, 0x02b1, 0x1290, 0x22f3, 0x32d2, 0x4235, 0x5214,
        0x6277, 0x7256, 0xb5ea, 0xa5cb, 0x95a8, 0x8589, 0xf56e, 0xe54f, 0xd52c,
        0xc50d, 0x34e2, 0x24c3, 0x14a0, 0x0481, 0x7466, 0x6447, 0x5424, 0x4405,
        0xa7db, 0xb7fa, 0x8799, 0x97b8, 0xe75f, 0xf77e, 0xc71d, 0xd73c, 0x26d3,
        0x36f2, 0x0691, 0x16b0, 0x6657, 0x7676, 0x4615, 0x5634, 0xd94c, 0xc96d,
        0xf90e, 0xe92f, 0x99c8, 0x89e9, 0xb98a, 0xa9ab, 0x5844, 0x4865, 0x7806,
        0x6827, 0x18c0, 0x08e1, 0x3882, 0x28a3, 0xcb7d, 0xdb5c, 0xeb3f, 0xfb1e,
        0x8bf9, 0x9bd8, 0xabbb, 0xbb9a, 0x4a75, 0x5a54, 0x6a37, 0x7a16, 0x0af1,
        0x1ad0, 0x2ab3, 0x3a92, 0xfd2e, 0xed0f, 0xdd6c, 0xcd4d, 0xbdaa, 0xad8b,
        0x9de8, 0x8dc9, 0x7c26, 0x6c07, 0x5c64, 0x4c45, 0x3ca2, 0x2c83, 0x1ce0,
        0x0cc1, 0xef1f, 0xff3e, 0xcf5d, 0xdf7c, 0xaf9b, 0xbfba, 0x8fd9, 0x9ff8,
        0x6e17, 0x7e36, 0x4e55, 0x5e74, 0x2e93, 0x3eb2, 0x0ed1, 0x1ef0 };
}

PacketInterface::PacketInterface(QObject *parent) :
    QObject(parent)
{
    mSendBuffer = new quint8[mMaxBufferLen + 20];

    mRxState = 0;
    mRxTimer = 0;

    // Packet state
    mPayloadLength = 0;
    mRxDataPtr = 0;

    mTimer = new QTimer(this);
    mTimer->setInterval(10);
    mTimer->start();

    mHostAddress = QHostAddress("192.168.1.117");
    mUdpPort = 7001;
    mUdpSocket = new QUdpSocket(this);

    connect(mUdpSocket, SIGNAL(readyRead()),
            this, SLOT(readPendingDatagrams()));
    connect(mTimer, SIGNAL(timeout()), this, SLOT(timerSlot()));
}

PacketInterface::~PacketInterface()
{
    delete mSendBuffer;
}

void PacketInterface::processData(QByteArray &data)
{
    unsigned char rx_data;
    const int rx_timeout = 50;

    for(int i = 0;i < data.length();i++) {
        rx_data = data[i];

        switch (mRxState) {
        case 0:
            if (rx_data == 2) {
                mRxState += 2;
                mRxTimer = rx_timeout;
                mRxDataPtr = 0;
                mPayloadLength = 0;
            } else {
                mRxState = 0;
            }
            break;

        case 1:
            mPayloadLength = (unsigned int)rx_data << 8;
            mRxState++;
            mRxTimer = rx_timeout;
            break;

        case 2:
            mPayloadLength |= (unsigned int)rx_data;
            if (mPayloadLength <= mMaxBufferLen && mPayloadLength > 0) {
                mRxState++;
                mRxTimer = rx_timeout;
            } else {
                mRxState = 0;
            }
            break;

        case 3:
            mRxBuffer[mRxDataPtr++] = rx_data;
            if (mRxDataPtr == mPayloadLength) {
                mRxState++;
            }
            mRxTimer = rx_timeout;
            break;

        case 4:
            if (rx_data == 3) {
                     // Packet received!
                    processPacket(mRxBuffer, mPayloadLength);
            }
            mRxState = 0;
            break;

        default:
            mRxState = 0;
            break;
        }
    }
}




void PacketInterface::timerSlot()
{
    if (mRxTimer) {
        mRxTimer--;
    } else {
        mRxState = 0;
    }

}

void PacketInterface::readPendingDatagrams()
{
    while (mUdpSocket->hasPendingDatagrams()) {
        QByteArray datagram;
        datagram.resize(mUdpSocket->pendingDatagramSize());
        QHostAddress sender;
        quint16 senderPort;

        mUdpSocket->readDatagram(datagram.data(), datagram.size(),
                                &sender, &senderPort);

        processPacket((unsigned char*)datagram.data(), datagram.length());
    }
}

unsigned short PacketInterface::crc16(const unsigned char *buf, unsigned int len)
{
    unsigned int i;
    unsigned short cksum = 0;
    for (i = 0; i < len; i++) {
        cksum = crc16_tab[(((cksum >> 8) ^ *buf++) & 0xFF)] ^ (cksum << 8);
    }
    return cksum;
}

bool PacketInterface::sendPacket(const unsigned char *data, unsigned int len_packet)
{    
    static unsigned char buffer[mMaxBufferLen];
    unsigned int ind = 0;

    // If the IP is valid, send the packet over UDP
    if (QString::compare(mHostAddress.toString(), "0.0.0.0") != 0) {

        memcpy(buffer + ind, data, len_packet);
        ind += len_packet;

        mUdpSocket->writeDatagram(QByteArray::fromRawData((const char*)buffer, ind), mHostAddress, mUdpPort);
        return true;
    }
    else{
        return false;
    }

}

bool PacketInterface::sendPacket(QByteArray data)
{
    return sendPacket((const unsigned char*)data.data(), data.size());
}

void PacketInterface::processPacket(const unsigned char *data, int len)
{
    int32_t ind = 0;
    int fw_major;
    int fw_minor;

    unsigned char id = data[0];
    data++;
    len--;

    switch (id) {
    case COMM_FW_VERSION:
        if (len == 2) {
            ind = 0;
            fw_major = data[ind++];
            fw_minor = data[ind++];
        } else {
            fw_major = -1;
            fw_minor = -1;
        }
        emit fwVersionReceived(fw_major, fw_minor);
        break;

    default:
        break;
    }
}


bool PacketInterface::getFwVersion()
{
    QByteArray buffer;
    buffer.clear();
    buffer.append((char)COMM_FW_VERSION);
    return sendPacket(buffer);
}



bool PacketInterface::getValues()
{
    QByteArray buffer;
    buffer.clear();
    buffer.append((char)COMM_GET_VALUES);
    return sendPacket(buffer);
}

bool PacketInterface::sendTerminalCmd(QString cmd)
{
    QByteArray buffer;
    buffer.clear();
    buffer.append((char)COMM_TERMINAL_CMD);
    buffer.append(cmd.toLatin1());
    return sendPacket(buffer);
}



bool PacketInterface::samplePrint(bool at_start, int sample_len, int dec)
{
    qint32 send_index = 0;
    mSendBuffer[send_index++] = COMM_SAMPLE_PRINT;
    mSendBuffer[send_index++] = at_start;
    utility::buffer_append_uint16(mSendBuffer, sample_len, &send_index);
    mSendBuffer[send_index++] = dec;
    return sendPacket(mSendBuffer, send_index);
}



void PacketInterface::startUdpConnection(QHostAddress ip, int port)
{
    mHostAddress = ip;
    mUdpPort = port;
    mUdpSocket->close();
    mUdpSocket->bind(QHostAddress::Any, mUdpPort + 1);
}

void PacketInterface::stopUdpConnection()
{
    mHostAddress = QHostAddress("0.0.0.0");
    mUdpPort = 0;
    mUdpSocket->close();
}

bool PacketInterface::isUdpConnected()
{
    return QString::compare(mHostAddress.toString(), "0.0.0.0") != 0;
}
