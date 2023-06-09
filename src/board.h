#ifndef BOARD_H
#define BOARD_H
#include "square.h"
#include "sudoku.h"
#include <QVector>
#include <QQueue>
#include <QPair>

class Board
{
public:
    Board();
    ~Board(){};
    void removeNumbers();
    void updateSquares();
    void handleInput(int num);
    void generate();
    QVector<QVector<Square*>> squares() const;
    void handleClicked(QPointF clickedPoint);
    void doSolution();
private:    
    void createSquares();
    void unselectSquares();

    Sudoku* m_sudoku;
    Square* m_clickedSquare;
    QVector<QVector<int> > m_grid;
    QVector<QVector<Square*>> m_squares;
    QPoint m_choosenSquare;
};

#endif // BOARD_H
