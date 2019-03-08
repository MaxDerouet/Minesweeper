#include <iostream>
#include <Field.h>

int getInt()
{
    std::cout << "Type in an int ";
    int temp;
    std::cin >> temp;
    return --temp;
}

bool playMinesweeper(Field &field)
{
    int row;
    int column;
    bool continueGame(true);
    while (continueGame)
    {
        field.print();
        char action;
        std::cout << "Press c to click and f to flagg ";
        std::cin >> action;
        if (action=='c')
        {
            row=getInt();
            column=getInt();
            continueGame=field.click(row,column);
        }
        else if (action=='f')
        {
            row=getInt();
            column=getInt();
            field.setFlagg(row,column);
        }
        if (field.getNoUnclicked()==field.getNoMines())
            return true;
    }
    return false;
}

int main()
{
    srand(static_cast<unsigned int>(time(0)));
    Field field;
    bool won(playMinesweeper(field));
    if (won)
        std::cout << "You won";
    else
        std::cout << "You lost";
    return 0;
}
