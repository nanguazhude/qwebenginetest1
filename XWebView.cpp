#include "XWebView.hpp"
#include <QtCore>
#include <QWebChannel>
#include "WebChannelBridge.hpp"

XWebView::XWebView(){
    this->resize(1024,768);

    /*创建页面*/
    QWebEnginePage * varPage = new QWebEnginePage{this};

    /*测试执行JS代码*/
    connect(varPage,&QWebEnginePage::loadFinished,[this](bool){
        QFile varFile{ QStringLiteral(":/js/test1.txt") };
        varFile.open(QIODevice::ReadOnly);
        QTextStream varStream{ &varFile };
        const QString varJS = varStream.readAll();
         this->page()->runJavaScript( varJS );
    });

    /*测试嵌入对象*/
    WebChannelBridge * varBridge = new WebChannelBridge( varPage );
    QWebChannel * varChannel = new QWebChannel( varPage );
    varChannel->registerObject( QStringLiteral("webqt_bridge") , varBridge);
    varPage->setWebChannel( varChannel );

    varPage->load( QUrl("qrc:/html/maintest.html") );

    /*加载页面*/
    this->setPage(varPage);

}



