#include "view.h"
#include <QKeyEvent>
#include <QApplication>
#include <QDir>
#include <QPainter>

View::View()
    : m_gameScene(new GameScene(this))
{
    setScene(m_gameScene);
    resize(m_gameScene->sceneRect().width()+2, m_gameScene->sceneRect().height()+2);

    setMouseTracking(true);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

void View::keyReleaseEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Escape)
    {
        QApplication::instance()->quit();
    }
    if(event->key() == Qt::Key_Z)
    {
        //Uncomment below if you want to make screenshots
//        static int index = 0;
//        QString fileName = QDir::currentPath() + QDir::separator() + "screen" + QString::number(index++) + ".png";
//        QRect rect = sceneRect().toAlignedRect();
//        QImage image(rect.size(), QImage::Format_ARGB32);
//        image.fill(Qt::transparent);
//        QPainter painter(&image);
//        render(&painter);
//        image.save(fileName);
//        qDebug() << "saved " << fileName;
    }
    QGraphicsView::keyReleaseEvent(event);
}

void View::mouseMoveEvent(QMouseEvent *event)
{
    QGraphicsView::mouseMoveEvent(event);
}
