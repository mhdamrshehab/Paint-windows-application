#ifndef FINALPROJECTCOMPUTERGRAPHICS_CONVEXFILLING_H
#define FINALPROJECTCOMPUTERGRAPHICS_CONVEXFILLING_H

#include "MyUtilities.h"
#include "Line.h"
#include <vector>

class Entry {
public:
    int XLeft, XRight;
};

Entry* table = new Entry[1000];

void initTable(Entry table[]) {
    for (int i = 0; i < 1000; i++) {
        table[i].XLeft = INT_MAX;
        table[i].XRight = INT_MIN;
    }
}

void Edge2Table(Point P1, Point P2, Entry t[]) {
    if (P1.y == P2.y)
        return;

    if (P1.y > P2.y)
        swap(P1, P2);

    int y = P1.y;
    double x = P1.x;
    double Minv = ((double)P2.x - P1.x) / ((double)P2.y - P1.y);

    while (y < P2.y) {
        if (x < t[y].XLeft)
            t[y].XLeft = (int)ceil(x);
        if (x > t[y].XRight)
            t[y].XRight = (int)floor(x);

        y++, x += Minv;
    }
}

void polygon2table(Point p[], int n, Entry t[]) {
    Point p1 = p[n - 1];
    for (int i = 0; i < n; i++) {
        Point p2 = p[i];
        Edge2Table(p1, p2, t);
        p1 = p[i];
    }
}

void Table2Screen(HDC hdc, Entry t[], COLORREF c) {
    for (int i = 0; i < 1000; i++) {
        if (t[i].XLeft < t[i].XRight) {
            DrawLine(hdc, t[i].XLeft, i, t[i].XRight, i, c);
        }
    }
}

void ConvexFilling(HDC hdc, Point P[], int n, COLORREF c) {
    initTable(table);
    polygon2table(P, n, table);
    Table2Screen(hdc, table, c);
}

void ConvexFilling(HDC hdc, vector<Point> P, COLORREF c) {
    Point* P_ = new Point[P.size()];

    for (int i = 0; i < P.size(); i++)
        P_[i] = P[i];

    ConvexFilling(hdc, P_, P.size(), c);
}

#endif

