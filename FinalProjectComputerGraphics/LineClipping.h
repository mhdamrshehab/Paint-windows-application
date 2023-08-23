#ifndef FINALPROJECTCOMPUTERGRAPHICS_LINECLIPPING_H
#define FINALPROJECTCOMPUTERGRAPHICS_LINECLIPPING_H

#include "MyUtilities.h"
#include "Rectangle.h"
#include "Line.h"

Point VIntersect(Line L, double Xedge) {
    Point P;
    P.x = Xedge;
    P.y = L.S.y + (Xedge - L.S.x) * L.calcSlope();
    return P;
}

Point HIntersect(Line L, double Yedge) {
    Point P;
    P.y = Yedge;
    P.x = L.S.x + (Yedge - L.S.y) / L.calcSlope();
    return P;
}

class Out
{
public:
    unsigned left, right, top, bottom;

    void CalcOut(Point P, Window W) {
        left = (P.x < W.Left) ? 1 : 0;
        right = (P.x > W.Right) ? 1 : 0;
        top = (P.y < W.Top) ? 1 : 0;
        bottom = (P.y > W.Bottom) ? 1 : 0;
    }

    Out() {
        left = 0, right = 0, top = 0, bottom = 0;
    }

    Out(Point P, Window W) {
        CalcOut(P, W);
    }

    int isEmpty() {
        return (top == 0 && bottom == 0 && left == 0 && right == 0);
    }

    bool Intersects(Out out) {
        if ((left && out.left) || (right && out.right) || (top && out.top) || (bottom && out.bottom))
            return false;
        return true;
    }
};

bool LineClipping(Line& L, Window W) {
    Out out1(L.S, W);
    Out out2(L.E, W);
    Point P;

    while (true) {
        if (out1.isEmpty() && out2.isEmpty())
            return true;

        if (!out1.Intersects(out2))
            return false;

        if (!out1.isEmpty()) {
            if (out1.left == 1)
                P = VIntersect(L, W.Left);
            else if (out1.right == 1)
                P = VIntersect(L, W.Right);
            else if (out1.bottom == 1)
                P = HIntersect(L, W.Bottom);
            else
                P = HIntersect(L, W.Top);

            out1.CalcOut(P, W);
            L.S = P;
        }
        else if (!out2.isEmpty()) {
            if (out2.left == 1)
                P = VIntersect(L, W.Left);
            else if (out2.right == 1)
                P = VIntersect(L, W.Right);
            else if (out2.bottom == 1)
                P = HIntersect(L, W.Bottom);
            else
                P = HIntersect(L, W.Top);

            out2.CalcOut(P, W);
            L.E = P;
        }
    }
}

bool PointClipping(Point P, Window W) {
    if (P.x > W.Left && P.x < W.Right && P.y > W.Top && P.y < W.Bottom)
        return true;
    return false;
}

#endif
