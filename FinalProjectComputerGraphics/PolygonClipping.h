#ifndef FINALPROJECTCOMPUTERGRAPHICS_POLYGONCLIPPING_H
#define FINALPROJECTCOMPUTERGRAPHICS_POLYGONCLIPPING_H

#include "MyUtilities.h"
#include "Rectangle.h"
#include "LineClipping.h"
#include <vector>

bool InLeft(Point& P, double XLeft) {
    return P.x >= XLeft;
}

bool InRight(Point& P, double XRight) {
    return P.x <= XRight;
}

bool InBottom(Point& P, double YBottom)
{
    return P.y <= YBottom;
}

bool InTop(Point& P, double YTop) {
    return P.y >= YTop;
}

typedef vector<Point> PVector;

PVector ClipWithEdge(PVector& P, double edge, bool (*In)(Point&, double), Point(*Intersect)(Line, double))
{
    PVector out;
    size_t n = P.size();
    Point P1 = P[n - 1];
    bool in1 = In(P1, edge);
    for (int i = 0; i < n; i++)
    {
        Point P2 = P[i];
        bool in2 = In(P2, edge);
        if (in1 && in2)
            out.push_back(P2);
        else if (in1)
            out.push_back(Intersect(Line(P1, P2), edge));
        else if (in2)
        {
            out.push_back(Intersect(Line(P1, P2), edge));
            out.push_back(P2);
        }
        P1 = P2;
        in1 = in2;
    }
    return out;
}

PVector PolyClip(PVector P, Window W)
{
    PVector out;
    out = ClipWithEdge(P, W.Left, InLeft, VIntersect);
    out = ClipWithEdge(out, W.Right, InRight, VIntersect);
    out = ClipWithEdge(out, W.Bottom, InBottom, HIntersect);
    return ClipWithEdge(out, W.Top, InTop, HIntersect);
}

PVector PolyClip(Point* P, int& n, Window W)
{
    PVector PV;
    for (int i = 0; i < n; i++)
        PV.push_back(P[i]);

    return PolyClip(PV, W);
}

#endif

