#include <iostream>
#include <Field.h>

int main()
{
    srand(static_cast<unsigned int>(time(0)));
    Field field;
    field.printMines();
    field.setFlagg(3,3);
    field.setFlagg(3,3);
    field.setFlagg(1,1);
//    if (!(field.click(0,0)))
//        std::cout << "boom";
//    std::cout << "\n";
//    field.printInteraction();
    std::cout << "\n";
    field.printNoNeighbourMines();
    return 0;
}
