
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
        int noNeighbourMines;
    };
    std::vector<State> m_fieldArray;
public:
    Field(int noMines=10, int rows=8, int columns=8):m_noMines(noMines), m_rows(rows), m_columns(columns)
    {
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count(); // do think it would be better to put the seed somewhere else?
        assert(m_rows*m_columns>=m_noMines && "too many mines");
        State defaultState={NOMINE, NOTCLICKED, 0};
        for (int column=0; column<m_columns; ++column)
        {
            for (int row=0; row<m_rows; ++row)
                m_fieldArray.push_back(defaultState);
        }
        for (int index=0; index<m_noMines; ++index)
            m_fieldArray[index].mined=MINE;
        auto rng = std::default_random_engine {seed};
        std::shuffle(std::begin(m_fieldArray), std::end(m_fieldArray), rng);
        for (int row=0; row<m_rows; ++row)
        {
            for (int column=0; column<m_columns; ++column)
            {
                if (getState(row,column).mined!=MINE)
                {
                    if ((row+1)<m_rows && (column+1)<m_columns && getState((row+1),(column+1)).mined==MINE) // neighbour up right
                        ++(getState(row,column).noNeighbourMines);
                    if ((row+1)<m_rows && getState((row+1),column).mined==MINE) // neighbour up middle
                        ++(getState(row,column).noNeighbourMines);
                    if ((row+1)<m_rows && 0<=column-1 && getState((row+1),(column-1)).mined==MINE) // neighbour up left
                        ++(getState(row,column).noNeighbourMines);
                    if ((0<=row-1) && (column+1)<m_columns && getState((row-1),(column+1)).mined==MINE) // neighbour down right
                        ++(getState(row,column).noNeighbourMines);
                    if ((0<=row-1) && column<m_columns && getState((row-1),column).mined==MINE) // neighbour down middle
                        ++(getState(row,column).noNeighbourMines);
                    if ((0<=row-1) && 0<=(column-1) && getState((row-1),(column-1)).mined==MINE) // neighbour down left
                        ++(getState(row,column).noNeighbourMines);
                    if  ((column+1)<m_columns && getState(row,(column+1)).mined==MINE) // neighbour  right
                        ++(getState(row,column).noNeighbourMines);
                    if  (0<=(column-1) && getState(row,(column-1)).mined==MINE) // neighbour  left
                        ++(getState(row,column).noNeighbourMines);
                }
            }
        }
    }
    State& getState(int row, int column);
    void printMines();
    void printInteraction();
    void printNoNeighbourMines();
    void setFlagg(int row, int column);
    bool click(int row, int column);
};
