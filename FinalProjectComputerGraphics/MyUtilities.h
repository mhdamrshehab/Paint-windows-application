#ifndef FINALPROJECTCOMPUTERGRAPHICS_MyUtilities_H
#define FINALPROJECTCOMPUTERGRAPHICS_MyUtilities_H

#include "Point.h"
#include <windows.h>
#include <iostream>
#include <fstream>
#include <stack>
#include <algorithm>
#include <cmath>

using namespace std;

void GetWindowSize(HWND hwnd, int& width, int& height) {
    RECT rect;
    GetClientRect(hwnd, &rect);
    width = rect.right - rect.left;
    height = rect.bottom - rect.top;
}

void Draw8Points(HDC hdc, int Xs, int Ys, int x, int y, COLORREF c) {
    SetPixel(hdc, Xs + x, Ys + y, c);
    SetPixel(hdc, Xs - x, Ys + y, c);
    SetPixel(hdc, Xs + x, Ys - y, c);
    SetPixel(hdc, Xs - x, Ys - y, c);
    SetPixel(hdc, Xs + y, Ys + x, c);
    SetPixel(hdc, Xs - y, Ys + x, c);
    SetPixel(hdc, Xs + y, Ys - x, c);
    SetPixel(hdc, Xs - y, Ys - x, c);
}

void Draw8Points(HDC hdc, Point pStart, int x, int y, COLORREF c) {
    Draw8Points(hdc, pStart.x, pStart.y, x, y, c);
}

// This function draws four points on an ellipse given the center (Xc, Yc),
// x and y coordinates of a point on the ellipse, and a color
void Draw4Points(HDC hdc, int Xc, int Yc, int x, int y, COLORREF c) {
    SetPixel(hdc, Xc + x, Yc + y, c);  // Draw point in first quadrant
    SetPixel(hdc, Xc - x, Yc + y, c);  // Draw point in second quadrant
    SetPixel(hdc, Xc - x, Yc - y, c);  // Draw point in third quadrant
    SetPixel(hdc, Xc + x, Yc - y, c);  // Draw point in fourth quadrant
}

double CalcDistance(int x1, int y1, int x2, int y2) {
    return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
}

double CalcDistance(Point P1, Point P2) {
    return CalcDistance(P1.x, P1.y, P2.x, P2.y);
}

double calcSlope(int x1, int y1, int x2, int y2) {
    return (double)(y2 - y1) / (double)(x2 - x1);
}

int Round(double x) {
    if (x >= 0.0) {
        return (int)(x + 0.5);
    }
    else {
        return (int)(x - 0.5);
    }
}

#endif