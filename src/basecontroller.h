#ifndef BASECONTROLLER_H
#define BASECONTROLLER_H

/*
 * This is an abstract class for all controller classes.
 * i.e. LocalController is a sub-class of the BaseController.
 */

#include <QByteArray>
#include <QHostAddress>
#include <QList>
#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include "profile.h"
#include "connection.h"
#include "encryptor.h"

using namespace QSS;

namespace QSS {

class BaseController : public QObject
{
    Q_OBJECT
public:
    explicit BaseController(QObject *parent = 0);
    virtual ~BaseController();

    virtual quint16 getServerPort();
    virtual QString getServerAddr();

signals:
    void error(const QString &);
    void info(const QString &);

public slots:
    virtual void start(const Profile &) = 0;
    virtual void stop();

protected://children can access protected members
    bool running;
    QTcpServer *tcpServer;
    Profile profile;
    QList<Connection *> conList;
    QCA::Initializer qi;

protected slots:
    virtual void onTcpServerError();
    virtual void onNewConnection();
    virtual void onConnectionDisconnected();
};

}
#endif // BASECONTROLLER_H