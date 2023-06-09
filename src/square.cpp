#include "square.h"
#include "utils.h"
#include "fontmanager.h"
#include <QBrush>
#include <QPen>

Square::Square(){}

Square::Square(QPointF pos, int correctNumber)
    : m_correctNumber(correctNumber), m_locked(true), m_enteredNumber(correctNumber)
{
    setBrush(QBrush(COLOR_STYLE::clear_color));
    setPen(QPen(COLOR_STYLE::clear_color));
    setRect(-BOARD_STYLE::square_pixel_size/2,
            -BOARD_STYLE::square_pixel_size/2,
            BOARD_STYLE::square_pixel_size,
            BOARD_STYLE::square_pixel_size);
    setPos(pos);
    moveBy(BOARD_STYLE::square_pixel_size/2,
           BOARD_STYLE::square_pixel_size/2
           );

    m_text = new QGraphicsSimpleTextItem(this);
    QFont textFont = FontManager::Instance()->getFont(FontManager::FontID::NUMBER);
    textFont.setPointSize(20);
    m_text->setFont(textFont);
    m_text->setText(" ");
    m_text->setPos(-m_text->boundingRect().width()/2,
                   -m_text->boundingRect().height()/2);
    m_text->setBrush(QBrush(COLOR_STYLE::black_color));
    m_text->setPen(QPen(COLOR_STYLE::black_color));

    setFlags(QGraphicsItem::ItemIsSelectable);
}


void Square::setText(int val)
{
    if(val)
    {
        m_text->setText(QString::number(val));
    }
    else
    {
        m_text->setText(" ");
    }
}

void Square::setDefaultColor()
{
    setBrush(QBrush(COLOR_STYLE::clear_color));
    setPen(QPen(COLOR_STYLE::clear_color));
}

void Square::setBlackTextColor()
{
    m_text->setBrush(QBrush(COLOR_STYLE::black_color));
    m_text->setPen(QPen(COLOR_STYLE::black_color));
}

void Square::setActiveColor()
{
    setBrush(QBrush(COLOR_STYLE::chosen_square_color));
    setPen(QPen(COLOR_STYLE::chosen_square_color));
}

void Square::setEnteredText(int val)
{
    m_enteredNumber = val;
    if(m_enteredNumber == m_correctNumber)
    {
        m_text->setBrush(QBrush(COLOR_STYLE::blue_color));
        m_text->setPen(QPen(COLOR_STYLE::blue_color));
    }
    else
    {
        m_text->setBrush(QBrush(COLOR_STYLE::red_color));
        m_text->setPen(QPen(COLOR_STYLE::red_color));
    }
    setText(val);
}


