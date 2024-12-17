
#include <iostream>

#include "group.h"

int main()
{
    Media *m1 = new Media("1mm1", "1pp1");
    Media *m2 = new Media("2mm2", "2pp2");
    Media *m3 = new Media("3mm3", "3pp3");
    Media *m4 = new Media("4mm4", "4pp4");

    Group *g1 = new Group("g1");
    g1->push_back(m1);
    g1->push_back(m2);
    g1->push_back(m3);

    Group *g2 = new Group("g2");
    g2->push_back(m1);
    g2->push_back(m4);

    g1->display(std::cout);
    std::cout << "---------------------" << std::endl;
    g2->display(std::cout);

    return 0;
}
