#ifndef FINALPROJECTCOMPUTERGRAPHICS_RECTANGLE_H
#define FINALPROJECTCOMPUTERGRAPHICS_RECTANGLE_H

#include "MyUtilities.h"
#include "Line.h"


class Window
{
public:
    int Top, Bottom, Left, Right;

    Window() :Top(0), Bottom(0), Left(0), Right(0) {}

    void check_values() {
        if (Left > Right)
            swap(Left, Right);
        if (Top > Bottom)
            swap(Top, Bottom);
    }

    Window(int top, int bottom, int left, int right) {
        Top = top;
        Bottom = bottom;
        Left = left;
        Right = right;
        check_values();
    }

    void drawRectangle(HDC hdc, int top, int bottom, int left, int right, COLORREF c) {
        Top = top; Bottom = bottom; Left = left; Right = right;
        check_values();
        DrawLine(hdc, Line(Left, Top, Left, Bottom), c);
        DrawLine(hdc, Line(Left, Top, Right, Top), c);
        DrawLine(hdc, Line(Right, Bottom, Left, Bottom), c);
        DrawLine(hdc, Line(Right, Top, Right, Bottom), c);
    }

    void drawSquare(HDC hdc, int top, int bottom, int left, int right, COLORREF c) {
        Top = top;  Left = left;
        double diagonal = CalcDistance(Point(left, top), Point(right, bottom));
        double side = sqrt(pow(diagonal, 2) / 2.0);
        Bottom = top + side; Right = left + side;
        DrawLine(hdc, Line(Left, Top, Left, Bottom), c);
        DrawLine(hdc, Line(Left, Top, Right, Top), c);
        DrawLine(hdc, Line(Right, Bottom, Left, Bottom), c);
        DrawLine(hdc, Line(Right, Top, Right, Bottom), c);
    }
};

#endif
