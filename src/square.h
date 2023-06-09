#ifndef SQUARE_H
#define SQUARE_H

#include <QObject>
#include <QGraphicsRectItem>
#include <QGraphicsSimpleTextItem>

class Square : public QObject, public QGraphicsRectItem
{
    Q_OBJECT
public:
    explicit Square();
    Square(QPointF pos, int correctNumber);
    ~Square(){};

    int m_correctNumber;
    bool m_locked;
    int m_enteredNumber;
    void setText(int val);
    void setDefaultColor();
    void setBlackTextColor();
    void setActiveColor();
    void setEnteredText(int val);
private:
    QGraphicsSimpleTextItem *m_text;
};

#endif // SQUARE_H
