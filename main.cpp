
#include "media.h"

int main()
{
    Media *m1 = new Media();
    Media *m2 = new Media(std::string("Harry Potter"), std::string("/media/harry_potter.mp4"));
    
    m1->display(std::cout);
    m2->display(std::cout);
    
    return 0;
}
