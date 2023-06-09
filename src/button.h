#ifndef BUTTON_H
#define BUTTON_H

#include <QObject>
#include <QGraphicsRectItem>
#include <QGraphicsSimpleTextItem>

class Button : public QObject, public QGraphicsRectItem
{
    Q_OBJECT
public:
    explicit Button(QString text="");

signals:
    void clicked();

    // QGraphicsItem interface
public:
    virtual QRectF boundingRect() const override;

private:
    QGraphicsSimpleTextItem* m_text;

    // QGraphicsItem interface
protected:
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
};

#endif // BUTTON_H
