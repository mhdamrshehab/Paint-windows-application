#ifndef FINALPROJECTCOMPUTERGRAPHICS_FLOODFILLING_H
#define FINALPROJECTCOMPUTERGRAPHICS_FLOODFILLING_H

#include "MyUtilities.h"
#include <queue>

void FloodFillNonRecS(HDC hdc, Point P, COLORREF cb, COLORREF cf) {
    stack<Point> p;
    p.push(P);
    while (!p.empty()) {
        Point p1 = p.top();
        p.pop();
        COLORREF current = GetPixel(hdc, p1.x, p1.y);
        if (current == cb || current == cf)continue;
        SetPixel(hdc, p1.x, p1.y, cf);
        p.push(Point(p1.x + 1, p1.y));
        p.push(Point(p1.x - 1, p1.y));
        p.push(Point(p1.x, p1.y + 1));
        p.push(Point(p1.x, p1.y - 1));
    }
}

void FloodFillNonRecQ(HDC hdc, Point P, COLORREF cb, COLORREF cf) {
    queue<Point> p;
    p.push(P);
    while (!p.empty()) {
        Point p1 = p.front();
        p.pop();
        COLORREF current = GetPixel(hdc, p1.x, p1.y);
        if (current == cb || current == cf)continue;
        SetPixel(hdc, p1.x, p1.y, cf);
        p.push(Point(p1.x + 1, p1.y));
        p.push(Point(p1.x - 1, p1.y));
        p.push(Point(p1.x, p1.y + 1));
        p.push(Point(p1.x, p1.y - 1));
    }
}

void FloodFillRec(HDC hdc, Point P, COLORREF cb, COLORREF cf) {
    COLORREF c = GetPixel(hdc, P.x, P.y);
    if (c == cb || c == cf)
        return;

    SetPixel(hdc, P.x, P.y, c);
    FloodFillRec(hdc, Point(P.x + 1, P.y), cb, cf);
    FloodFillRec(hdc, Point(P.x - 1, P.y), cb, cf);
    FloodFillRec(hdc, Point(P.x, P.y + 1), cb, cf);
    FloodFillRec(hdc, Point(P.x, P.y - 1), cb, cf);
}

#endif