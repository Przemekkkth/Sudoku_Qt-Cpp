#include "button.h"
#include "utils.h"
#include "fontmanager.h"
#include <QBrush>
#include <QPen>

Button::Button(QString text)
{
    setBrush(QBrush(COLOR_STYLE::button_color));
    setPen(QPen(COLOR_STYLE::button_line_color, 3));

    setRect(-BUTTON_STYLE::width/2, -BUTTON_STYLE::height/2,
             BUTTON_STYLE::width,
             BUTTON_STYLE::height);

    m_text = new QGraphicsSimpleTextItem(text, this);
    QFont textFont = FontManager::Instance()->getFont(FontManager::FontID::STRING);
    textFont.setPointSize(BUTTON_STYLE::button_text_size);
    m_text->setFont(textFont);
    m_text->setText(text);
    m_text->setPos(-m_text->boundingRect().width()/2,
                   -m_text->boundingRect().height()/2);

    setFlags(QGraphicsItem::ItemIsSelectable);
}

QRectF Button::boundingRect() const
{
    return QRectF(-BUTTON_STYLE::width/2,-BUTTON_STYLE::height/2, BUTTON_STYLE::width, BUTTON_STYLE::height);
}

void Button::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    emit clicked();
    QGraphicsRectItem::mouseReleaseEvent(event);
}
