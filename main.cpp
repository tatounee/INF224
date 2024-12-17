
#include <iostream>

#include <memory>
#include "group.h"

using MediaPtr = std::shared_ptr<Media>;


int main()
{
    MediaPtr m1 = MediaPtr(new Media("1mm1", "1pp1"));
    MediaPtr m2 = MediaPtr(new Media("1mm2", "1pp2"));
    MediaPtr m3 = MediaPtr(new Media("1mm3", "1pp3"));
    MediaPtr m4 = MediaPtr(new Media("1mm4", "1pp4"));

    Group *g1 = new Group("g1");
    g1->push_back(m1);
    g1->push_back(m2);
    g1->push_back(m3);

    Group *g2 = new Group("g2");
    g2->push_back(m1);
    g2->push_back(m4);

    m1.reset();
    m2.reset();
    m3.reset();
    m4.reset();

    g1->display(std::cout);
    std::cout << "---------------------" << std::endl;
    g2->display(std::cout);

    delete g1;
    std::cout << "+++++++++++++++++++++" << std::endl;
    delete g2;

    return 0;
}
