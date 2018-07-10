#include "WebChannelBridge.hpp"
#include <QtCore/qdebug.h>

WebChannelBridge::WebChannelBridge(QObject *p) : QObject(p) {

}

void WebChannelBridge::runtest(QVariant v){
    qDebug()<< v;
}

