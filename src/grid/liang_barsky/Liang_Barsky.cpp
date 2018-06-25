#include "Grid.h"

void Grid::DrawClipping() {
    MousePair newPair = m_pvMousePairs->back();

    SortUpX( newPair );

    int xStart = newPair.begin.x;
    int yStart = newPair.begin.y;
    int xEnd = newPair.end.x;
    int yEnd = newPair.end.y;

    float t0 = 0;
    float t1 = 1;

    int xDelta = newPair.end.x - newPair.begin.x;
    int yDelta = newPair.end.y - newPair.begin.y;

    if( LeftClipCheck( newPair, t0, t1, xDelta, yDelta )
        && RightClipCheck( newPair, t0, t1, xDelta, yDelta )
        && DownClipCheck( newPair, t0, t1, xDelta, yDelta )
        && UpClipCheck( newPair, t0, t1, xDelta, yDelta ) ) {
            newPair.begin.x = xStart + t0 * xDelta;
            newPair.begin.y = yStart + t0 * yDelta;

            newPair.end.x = xStart + t1 * xDelta;
            newPair.end.y = yStart + t1 * yDelta;

            m_pvClippedLines->push_back( newPair );
    }
    else {
        MousePair empty;
        empty.begin.x = -1;
        empty.begin.y = -1;
        empty.end.x = -1;
        empty.end.y = -1;

        m_pvClippedLines->push_back( empty );
    }
}

bool Grid::LeftClipCheck( MousePair& pair, float& t0, float& t1, int xDelta, int yDelta ) {
    int xStart = pair.begin.x;
    int yStart = pair.begin.y;
    int xEnd = pair.end.x;
    int yEnd = pair.end.y;

    int P = -xDelta;
    int Q = -( 420 - xStart );
    float R = (float)Q / P;

    if( P == 0 && Q < 0 ) {
        return false;
    }
    else if( P < 0 ) {
        if( R > t1 ) {
            return false;
        }
        else if( R > t0 ) {
            t0 = R;
        }
    }
    else if( P > 0 ) {
        if( R < t0 ) {
            return false;
        }
        else if( R < t1 ) {
            t1 = R;
        }
    }

    return true;
}

bool Grid::RightClipCheck( MousePair& pair, float& t0, float& t1, int xDelta, int yDelta ) {
    int xStart = pair.begin.x;
    int yStart = pair.begin.y;
    int xEnd = pair.end.x;
    int yEnd = pair.end.y;

    int P = xDelta;
    int Q = 920 - xStart;
    float R = (float)Q / P;

    if( P == 0 && Q < 0 ) {
        return false;
    }
    else if( P < 0 ) {
        if( R > t1 ) {
            return false;
        }
        else if( R > t0 ) {
            t0 = R;
        }
    }
    else if( P > 0 ) {
        if( R < t0 ) {
            return false;
        }
        else if( R < t1 ) {
            t1 = R;
        }
    }

    return true;
}

bool Grid::DownClipCheck( MousePair& pair, float& t0, float& t1, int xDelta, int yDelta ) {
    int xStart = pair.begin.x;
    int yStart = pair.begin.y;
    int xEnd = pair.end.x;
    int yEnd = pair.end.y;

    int P = -yDelta;
    int Q = -( 220 - yStart );
    float R = (float)Q / P;

    if( P == 0 && Q < 0 ) {
        return false;
    }
    else if( P < 0 ) {
        if( R > t1 ) {
            return false;
        }
        else if( R > t0 ) {
            t0 = R;
        }
    }
    else if( P > 0 ) {
        if( R < t0 ) {
            return false;
        }
        else if( R < t1 ) {
            t1 = R;
        }
    }

    return true;
}

bool Grid::UpClipCheck( MousePair& pair, float& t0, float& t1, int xDelta, int yDelta ) {
    int xStart = pair.begin.x;
    int yStart = pair.begin.y;
    int xEnd = pair.end.x;
    int yEnd = pair.end.y;

    int P = yDelta;
    int Q = 560 - yStart;
    float R = (float)Q / P;

    if( P == 0 && Q < 0 ) {
        return false;
    }
    else if( P < 0 ) {
        if( R > t1 ) {
            return false;
        }
        else if( R > t0 ) {
            t0 = R;
        }
    }
    else if( P > 0 ) {
        if( R < t0 ) {
            return false;
        }
        else if( R < t1 ) {
            t1 = R;
        }
    }

    return true;
}