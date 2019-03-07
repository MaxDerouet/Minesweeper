#include <Field.h>

Field::State& Field::getState(int row, int column)
{
    assert(0<=row && row<m_rows && 0<=column && column<m_rows && "Index out of range");
    return m_fieldArray[row*m_columns+column];
}

void Field::printMines()
{
    for (int column=0; column<m_columns; ++column)
        {
            for (int row=0; row<m_rows; ++row)
                std::cout << (getState(row, column)).mined << " ";
            std::cout << "\n";
        }
}

void Field::printInteraction()
{
    for (int column=0; column<m_columns; ++column)
        {
            for (int row=0; row<m_rows; ++row)
                std::cout << (getState(row, column)).interaction << " ";
            std::cout << "\n";
        }
}

void Field::printNoNeighbourMines()
{
    for (int column=0; column<m_columns; ++column)
        {
            for (int row=0; row<m_rows; ++row)
                std::cout << (getState(row, column)).noNeighbourMines << " ";
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
        return true;
    }
}




