#include "Point.h"
using namespace std;
ostream& operator <<(ostream& stream,const Point& toPrint)
{
    stream << "(" << toPrint.x << "," << toPrint.y << ")" << endl;
    return stream;
}
