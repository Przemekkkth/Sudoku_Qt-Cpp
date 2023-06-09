#include "gamescene.h"
#include "utils.h"
#include "pixmapmanager.h"
#include "fontmanager.h"
#include <QKeyEvent>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsPixmapItem>
#include <QGraphicsLineItem>
#include <QDebug>
#include <QDir>
#include <QPainter>

GameScene::GameScene(QObject *parent)
    : QGraphicsScene(parent)
{
    onUserCreate();
    setBackgroundBrush(COLOR_STYLE::background_color);
    for(int i = 0; i < 256; ++i)
    {
        m_keys[i] = new KeyStatus();
    }
    m_mouse = new MouseStatus();
    setSceneRect(0,0, SCREEN::PHYSICAL_SIZE.width(), SCREEN::PHYSICAL_SIZE.height());
    connect(&m_timer, &QTimer::timeout, this, &GameScene::loop);
    m_timer.start(int(1000.0f/FPS));
    m_elapsedTimer.start();
}

GameScene::~GameScene()
{

}

void GameScene::loop()
{
    m_deltaTime = m_elapsedTimer.elapsed();
    m_elapsedTimer.restart();

    m_loopTime += m_deltaTime;
    while(m_loopTime > m_loopSpeed)
    {
        m_loopTime -= m_loopSpeed;
        handlePlayerInput();
        //clear();


        resetStatus();
    }
}

void GameScene::onUserCreate()
{
    m_titleTextItem = new QGraphicsSimpleTextItem();
    QFont titleFont = FontManager::Instance()->getFont(FontManager::FontID::STRING);
    titleFont.setBold(true);
    titleFont.setPointSize(100);
    m_titleTextItem->setText("Sudoku");
    m_titleTextItem->setFont(titleFont);
    m_titleTextItem->setPos( SCREEN::PHYSICAL_SIZE.width() - (SCREEN::PHYSICAL_SIZE.width() - BOARD_STYLE::size - BOARD_STYLE::offset) / 2,
            120);
    m_titleTextItem->moveBy(-m_titleTextItem->boundingRect().width()/2, -m_titleTextItem->boundingRect().height()/2);
    addItem(m_titleTextItem);

    m_generateButton = new Button("Generate");
    m_generateButton->setPos(SCREEN::PHYSICAL_SIZE.width() - (SCREEN::PHYSICAL_SIZE.width() - BOARD_STYLE::size - BOARD_STYLE::offset) / 2,
                           300);
    connect(m_generateButton, &Button::clicked, [this](){
       qDebug() << "Generated";
       board.generate();
    });
    addItem(m_generateButton);
    m_solveButton = new Button("Solve");
    m_solveButton->setPos(SCREEN::PHYSICAL_SIZE.width() - (SCREEN::PHYSICAL_SIZE.width() - BOARD_STYLE::size - BOARD_STYLE::offset) / 2,
                        470);
    connect(m_solveButton, &Button::clicked, [this](){
       qDebug() << "Solve";
        board.doSolution();
    });
    addItem(m_solveButton);

    initBoard();

    //board.generate();
    QVector<QVector<Square*>> squares = board.squares();
    foreach(QVector<Square*> vec , squares)
    {
        foreach(Square* square, vec)
        {
            addItem(square);
        }
    }
    //board.updateSquares();
}

void GameScene::initBoard()
{
   // 1/3 board size
    int oneOfThirdBoradSize = BOARD_STYLE::size/3;
    // 2/3 board size
    int twoOfThirdBoardSize = BOARD_STYLE::size*2/3;
    // size of piece board size / 9
    int pieceSize = BOARD_STYLE::size/9;

    QColor bgBoardColor = QColor(Qt::white);
    QColor borderColor  = QColor(Qt::black);
    QColor innerBoardColor = QColor(194, 197, 204);

    QImage board_image(BOARD_STYLE::size, BOARD_STYLE::size, QImage::Format_RGB32);
    for (int i = 0; i < BOARD_STYLE::size; i++)
    {
        for (int j = 0; j < BOARD_STYLE::size; j++)
        {
            if (i  <   0 + BOARD_STYLE::big_width || i > BOARD_STYLE::size - BOARD_STYLE::big_width
                    || j  <   0 + BOARD_STYLE::big_width || j > BOARD_STYLE::size - BOARD_STYLE::big_width
                    || (i > oneOfThirdBoradSize - BOARD_STYLE::big_width / 2 && i < oneOfThirdBoradSize + BOARD_STYLE::big_width/2)
                    || (i > twoOfThirdBoardSize - BOARD_STYLE::big_width / 2 && i < twoOfThirdBoardSize + BOARD_STYLE::big_width / 2)
                    || (j > oneOfThirdBoradSize - BOARD_STYLE::big_width / 2 && j < oneOfThirdBoradSize + BOARD_STYLE::big_width / 2)
                    || (j > twoOfThirdBoardSize - BOARD_STYLE::big_width / 2 && j < twoOfThirdBoardSize + BOARD_STYLE::big_width / 2))
            {
                board_image.setPixelColor(i, j, borderColor);
            }
            else if (i % pieceSize == 0 || j % pieceSize == 0)
            {
                board_image.setPixelColor(i, j, innerBoardColor);
            }
            else
            {
                board_image.setPixelColor(i, j, bgBoardColor);
            }
        }
    }

    QGraphicsPixmapItem* pItem = new QGraphicsPixmapItem();
    pItem->setPixmap(QPixmap::fromImage(board_image));
    pItem->setPos(BOARD_STYLE::offset, BOARD_STYLE::offset);
    addItem(pItem);
}


void GameScene::renderScene()
{
    static int index = 0;
    QString fileName = QDir::currentPath() + QDir::separator() + "screen" + QString::number(index++) + ".png";
    QRect rect = sceneRect().toAlignedRect();
    QImage image(rect.size(), QImage::Format_ARGB32);
    image.fill(Qt::transparent);
    QPainter painter(&image);
    render(&painter);
    image.save(fileName);
    qDebug() << "saved " << fileName;
}


void GameScene::handlePlayerInput()
{
    if(m_keys[Qt::Key_Z]->m_released)
    {
        renderScene();
    }
}

void GameScene::resetStatus()
{
    for(int i = 0; i < 256; ++i)
    {
        m_keys[i]->m_released = false;
    }
    for(int i = 0; i < 256; ++i)
    {
        m_keys[i]->m_pressed = false;
    }
    m_mouse->m_released = false;
}

void GameScene::keyPressEvent(QKeyEvent *event)
{
    if(KEYBOARD::KeysMapper.contains(event->key()))
    {
        if(event->isAutoRepeat())
        {
            m_keys[KEYBOARD::KeysMapper[event->key()]]->m_held = true;
            m_keys[KEYBOARD::KeysMapper[event->key()]]->m_pressed = false;
        }
        else
        {
            m_keys[KEYBOARD::KeysMapper[event->key()]]->m_pressed = true;
            m_keys[KEYBOARD::KeysMapper[event->key()]]->m_held    = false;
        }
    }
    QGraphicsScene::keyPressEvent(event);
}

void GameScene::keyReleaseEvent(QKeyEvent *event)
{
    if(KEYBOARD::KeysMapper.contains(event->key()))
    {
        if(!event->isAutoRepeat())
        {
            m_keys[KEYBOARD::KeysMapper[event->key()]]->m_held = false;
            m_keys[KEYBOARD::KeysMapper[event->key()]]->m_pressed = false;
            m_keys[KEYBOARD::KeysMapper[event->key()]]->m_released = true;
        }

    }
    if(!event->isAutoRepeat())
    {
        if(event->key() == Qt::Key_0)
        {
            board.handleInput(0);
        }
        else if(event->key() == Qt::Key_1)
        {
            board.handleInput(1);
        }
        else if(event->key() == Qt::Key_2)
        {
            board.handleInput(2);
        }
        else if(event->key() == Qt::Key_3)
        {
            board.handleInput(3);
        }
        else if(event->key() == Qt::Key_4)
        {
            board.handleInput(4);
        }
        else if(event->key() == Qt::Key_4)
        {
            board.handleInput(4);
        }
        else if(event->key() == Qt::Key_5)
        {
            board.handleInput(5);
        }
        else if(event->key() == Qt::Key_6)
        {
            board.handleInput(6);
        }
        else if(event->key() == Qt::Key_7)
        {
            board.handleInput(7);
        }
        else if(event->key() == Qt::Key_8)
        {
            board.handleInput(8);
        }
        else if(event->key() == Qt::Key_9)
        {
            board.handleInput(9);
        }
        else if(event->key() == Qt::Key_Z)
        {
            renderScene();
        }
    }
    QGraphicsScene::keyReleaseEvent(event);
}

void GameScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    m_mouse->m_x = event->scenePos().x();
    m_mouse->m_y = event->scenePos().y();
    m_mouse->m_pressed = true;
    QGraphicsScene::mousePressEvent(event);
}

void GameScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    m_mouse->m_x = event->scenePos().x();
    m_mouse->m_y = event->scenePos().y();
    QGraphicsScene::mouseMoveEvent(event);
}

void GameScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    m_mouse->m_x = event->scenePos().x();
    m_mouse->m_y = event->scenePos().y();
    m_mouse->m_pressed = false;
    m_mouse->m_released = true;
    board.handleClicked(event->scenePos());
    QGraphicsScene::mouseReleaseEvent(event);
}
