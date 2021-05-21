#include <QCoreApplication>
#include <iostream>
#include <string>
#include <QTcpServer>
#include <QTcpSocket>
#include <QString>
#include <stdlib.h>
#include <QFile>
using namespace std;

QByteArray returnQByteArray (QString s)
{
    QFile file(s);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
            cout << "Error";
            return QByteArray();
    }
    QByteArray fileAll;
    fileAll = file.readAll();
    int sizeHTML = fileAll.size();
    QString sizeQHTML = QString::number(sizeHTML);
    QString textQHTML = QString::fromUtf8(fileAll);
    QString x = "HTTP/1.1 200 OK\n";
    x += "Content-Type: text/html; charset=utf-8\n";
    x += "Content-Length: " + sizeQHTML + "\n";
    x += "Connection: close\n";
    x += "\n";
    x += textQHTML;
    cout << x.toStdString() << endl;
    return x.toUtf8();
}

int main(int /*argc*/, char *argv[])
{
    int port = atoi(argv[1]);
    QTcpSocket *socket;
    QTcpServer aServer;

    bool a = aServer.listen(QHostAddress::AnyIPv4, port);
    QByteArray t;
    t = returnQByteArray(argv[2]);
    while(true)
    {
        socket = aServer.nextPendingConnection();
        if (socket == 0)
        {
            aServer.waitForNewConnection(-1);
            socket = aServer.nextPendingConnection();
        }

        socket->write(t);
        socket->waitForBytesWritten(1000);
        delete socket;
    }
}
