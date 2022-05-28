#include "../header/utility.h"

bool checkCollision(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2)
{
	if( !(std::max(x1, x2) < std::min(x1 + w1, x2 + w2)) ) 
	{
        return false;
    }
    
    if( !(std::max(y1, y2) < std::min(y1 + h1, y2 + h2)) ) 
	{
        return false;
    }

    return true;
}

void calcSlope(int x1, int y1, int x2, int y2, float *xVal, float *yVal)
{
	int steps = std::max(abs(x1 - x2), abs(y1 - y2));

	if (steps == 0)
	{
		*xVal = *yVal = 0;
		return;
	}

	*xVal = (x1 - x2);
    *xVal /= steps;

	*yVal = (y1 - y2);
    *yVal /= steps;
}
