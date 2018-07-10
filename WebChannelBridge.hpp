#ifndef WEBCHANNELBRIDGE_HPP
#define WEBCHANNELBRIDGE_HPP

#include <QtCore/qobject.h>
#include <QtCore/qvariant.h>

class WebChannelBridge : public QObject{
    Q_OBJECT
public:
    WebChannelBridge( QObject * p /**/ = nullptr );
public slots:
    void runtest(QVariant);
};

#endif // WEBCHANNELBRIDGE_HPP
