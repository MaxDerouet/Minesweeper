#include <iostream>
#include <vector>
#include <cassert>
#include <random>
#include <algorithm>
#include <chrono>

class Field
{
    int m_rows;
    int m_columns;
    int m_noMines;
    enum Mined
    {
        NOMINE,
        MINE,
    };
    enum Interaction
    {
        NOTCLICKED,
        CLICKED,
        FLAGGED,
    };
    struct State
    {
        Mined mined;
        Interaction interaction;
    };
    std::vector<State> m_fieldArray;
public:
    Field(int noMines=10, int rows=8, int columns=8):m_noMines(noMines), m_rows(rows), m_columns(columns)
    {
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count(); // do think it would be better to put the seed somewhere else?
        assert(m_rows*m_columns>=m_noMines && "too many mines");
        State defaultState={NOMINE, NOTCLICKED};
        for (int column=0; column<m_columns; ++column)
        {
            for (int row=0; row<m_rows; ++row)
                m_fieldArray.push_back(defaultState);
        }
        for (int index=0; index<m_noMines; ++index)
            m_fieldArray[index].mined=MINE;
        auto rng = std::default_random_engine {seed};
        std::shuffle(std::begin(m_fieldArray), std::end(m_fieldArray), rng);
    }
    State& getState(int row, int column);
    void printMines();
    void printInteraction();
    void setFlagg(int row, int column);
    bool click(int row, int column);
};

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

int main()
{
    srand(static_cast<unsigned int>(time(0)));
    Field field;
    field.printMines();
    field.setFlagg(3,3);
    field.setFlagg(3,3);
    field.setFlagg(1,1);
    if (!(field.click(0,0)))
        std::cout << "boom";
    std::cout << "\n";
    field.printInteraction();
    return 0;
}
