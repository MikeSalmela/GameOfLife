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
    Cell(unsigned i, unsigned j,std::vector<std::vector<Cell *>> *cells, QWidget *parent = nullptr);

    // Check neighbouring cells and update value of should change
    void calculateState();

    // Change life state if it should change
    void update();
    void addLivingNeighbor();
    void removeLivingNeighbor();

    bool isAlive() const { return alive; }

    void checkIfShouldChange();


    void paintEvent(QPaintEvent *event) override;
protected:
    void mouseReleaseEvent(QMouseEvent *event) override;

private:

    void changeState();
    void setColor();
    void notifyNeighbors();

    //States
    bool alive {false};
    bool shouldChange {false};
    QColor color {Qt::red};

    size_t pos_i;
    size_t pos_j;
    const std::vector<std::vector<Cell *>> *cells;
    char livingNeighbours = 0;
};

#endif // CELL_H
