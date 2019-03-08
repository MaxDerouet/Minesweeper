#include <Field.h>

Field::State& Field::getState(int row, int column)
{
    assert(0<=row && row<m_rows && 0<=column && column<m_rows && "Index out of range");
    return m_fieldArray[row*m_columns+column];
}

void Field::printMines()
{
    for (int row=0; row<m_rows; ++row)
        {
            for (int column=0; column<m_columns; ++column)
                std::cout << (getState(row, column)).mined << " ";
            std::cout << "\n";
        }
}

void Field::printInteraction()
{
    for (int row=0; row<m_rows; ++row)
        {
            for (int column=0; column<m_columns; ++column)
                std::cout << (getState(row, column)).interaction << " ";
            std::cout << "\n";
        }
}

void Field::printNoNeighbourMines()
{
    for (int row=0; row<m_rows; ++row)
        {
            for (int column=0; column<m_columns; ++column)
                std::cout << (getState(row, column)).noNeighbourMines << " ";
            std::cout << "\n";
        }
}

void Field::print()
{
    std::cout<< "   ";
    for (int column=0; column<m_columns; ++column)
        std::cout << column+1 << " ";
    std::cout << "\n";
    std::cout<< "  ";
    for (int column=0; column<m_columns; ++column)
        std::cout << " $";
    std::cout << "\n";
    for (int row=0; row<m_rows; ++row)
        {
            std::cout << row+1 << "$ ";
            for (int column=0; column<m_columns; ++column)
            {
                if ((getState(row, column).interaction)==CLICKED)
                    std::cout << (getState(row, column)).noNeighbourMines << " ";
                else if ((getState(row, column).interaction)==FLAGGED)
                    std::cout << "F ";
                else
                    std::cout << "_ ";
            }
            std::cout << "\n";
        }
}

void Field::setFlagg(int row, int column)
{
    if (!(getState(row, column).interaction==CLICKED))
    {
        if (getState(row, column).interaction==FLAGGED)
            getState(row, column).interaction=NOTCLICKED;
        else
            getState(row, column).interaction=FLAGGED;
    }
}

bool Field::click(int row, int column)
{
    if (getState(row, column).mined==MINE)
        return false;
    else
    {
        getState(row, column).interaction=CLICKED;
        --m_noUnclicked;
        if (getState(row, column).noNeighbourMines==0)
        {
            if ((row+1)<m_rows && (column+1)<m_columns && getState((row+1),(column+1)).interaction==NOTCLICKED) // neighbour up right
                click((row+1),(column+1));
            if ((row+1)<m_rows && getState((row+1),column).interaction==NOTCLICKED) // neighbour up middle
                click((row+1),column);
            if ((row+1)<m_rows && 0<=column-1 && getState((row+1),(column-1)).interaction==NOTCLICKED) // neighbour up left
                click((row+1),(column-1));
            if ((0<=row-1) && (column+1)<m_columns && getState((row-1),(column+1)).interaction==NOTCLICKED) // neighbour down right
                click((row-1),(column+1));
            if ((0<=row-1) && column<m_columns && getState((row-1),column).interaction==NOTCLICKED) // neighbour down middle
                click((row-1),column);
            if ((0<=row-1) && 0<=(column-1) && getState((row-1),(column-1)).interaction==NOTCLICKED) // neighbour down left
                click((row-1),(column-1));
            if  ((column+1)<m_columns && getState(row,(column+1)).interaction==NOTCLICKED) // neighbour  right
                click(row,(column+1));
            if  (0<=(column-1) && getState(row,(column-1)).interaction==NOTCLICKED) // neighbour  left
                click(row,(column-1));
        }
        return true;
    }
}

const int Field::getNoUnclicked() const
{
    return m_noUnclicked;
}

const int Field::getNoMines() const
{
    return m_noMines;
}

