#ifndef CELL_H
#define CELL_H

#include <QColor>
#include <QWidget>

#include <vector>

/*
 * \class Cell
 * \brief: Represent single cell with UI and states.
 */

class Cell : public QWidget
{
    Q_OBJECT

public:
    Cell(unsigned i, unsigned j, QWidget *parent = nullptr);

    // Check neighbouring cells and update value of should change
    void calculateState(const std::vector<std::vector<Cell*>> &cells);
    // Change life state if it should change
    void update();

    bool isAlive() const { return alive; }

    void paintEvent(QPaintEvent *event) override;

protected:
    void mouseReleaseEvent(QMouseEvent *event) override;

private:

    //Private methods
    unsigned countLiveNeighbors(const std::vector<std::vector<Cell*>> &cells);
    void changeState();
    void setColor();

    //States
    bool alive {false};
    bool shouldChange {false};
    QColor color {Qt::red};

    unsigned pos_i;
    unsigned pos_j;
};

#endif // CELL_H
