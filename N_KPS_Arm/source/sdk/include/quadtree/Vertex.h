#ifndef _VERTEX_QUADTREE_2018_08_022_
#define _VERTEX_QUADTREE_2018_08_022_

class vertex
{
    public:

        vertex ()
        {
            x = 0;
            y = 0;
        }

        vertex (long double newX, long double newY)
        {
            x = newX;
            y = newY;
        }
        ~vertex (){}

        long double x;
        long double y;

        bool operator == (vertex v){ return ((x == v.x)&&(y==v.y)); }
};
#endif//_VERTEX_QUADTREE_2018_08_022_