#ifndef FINALPROJECTCOMPUTERGRAPHICS_ADDPROGMENUS_H
#define FINALPROJECTCOMPUTERGRAPHICS_ADDPROGMENUS_H

#include "MyUtilities.h"

void AddFileMenu(HMENU MainMenu, HMENU subMenu) {
    AppendMenu(subMenu, MF_STRING, 1, L"Save");
    AppendMenu(subMenu, MF_STRING, 2, L"Load");
    AppendMenu(subMenu, MF_SEPARATOR, -1, L"");
    AppendMenu(subMenu, MF_STRING, 3, L"Clear");
    AppendMenu(subMenu, MF_SEPARATOR, -1, L"");
    AppendMenu(subMenu, MF_STRING, 0, L"Exit");
    AppendMenu(MainMenu, MF_POPUP, (UINT_PTR)subMenu, L"File");

}

void AddColorMenu(HMENU MainMenu, HMENU subMenu) {
    AppendMenu(subMenu, MF_STRING, 4, L"Choose Color ..");
    AppendMenu(MainMenu, MF_POPUP, (UINT_PTR)subMenu, L"Color");
}

void AddLineMenu(HMENU MainMenu, HMENU subMenu) {
    AppendMenu(subMenu, MF_STRING, 8, L"Line DDA");
    AppendMenu(subMenu, MF_STRING, 9,L"Line MidPoint");
    AppendMenu(subMenu, MF_STRING, 10,L"Line Parametric");
    AppendMenu(MainMenu, MF_POPUP, (UINT_PTR)subMenu, L"Line");
}

void AddCircleMenu(HMENU MainMenu, HMENU subMenu) {
    AppendMenu(subMenu, MF_STRING, 11,L"Circle Direct");
    AppendMenu(subMenu, MF_STRING, 12, L"Circle Polar");
    AppendMenu(subMenu, MF_STRING, 13, L"Circle Iterative Polar");
    AppendMenu(subMenu, MF_STRING, 14, L"Circle MidPoint");
    AppendMenu(subMenu, MF_STRING, 15, L"Circle modified MidPoint");
    AppendMenu(MainMenu, MF_POPUP, (UINT_PTR)subMenu, L"Circle");
}

void AddFillingCircleMenu(HMENU MainMenu, HMENU subMenu) {
    AppendMenu(subMenu, MF_STRING, 16, L"Filing With Lines");
    AppendMenu(subMenu, MF_STRING, 17, L"Filing With Circles");
    AppendMenu(subMenu, MF_SEPARATOR, -1, L"");
    AppendMenu(subMenu, MF_STRING, 18, L"Quarter 1");
    AppendMenu(subMenu, MF_STRING, 19, L"Quarter 2");
    AppendMenu(subMenu, MF_STRING, 20, L"Quarter 3");
    AppendMenu(subMenu, MF_STRING, 21, L"Quarter 4");
    AppendMenu(MainMenu, MF_POPUP, (UINT_PTR)subMenu, L"Filing Circle");
}

void AddEllipseMenu(HMENU MainMenu, HMENU subMenu) {
    AppendMenu(subMenu, MF_STRING, 22, L"Ellipse Direct Cartesian");
    AppendMenu(subMenu, MF_STRING, 23, L"Ellipse Polar");
    AppendMenu(subMenu, MF_STRING, 24, L"Ellipse Iterative Polar");
    AppendMenu(subMenu, MF_STRING, 25, L"Ellipse MidPoint");
    AppendMenu(MainMenu, MF_POPUP, (UINT_PTR)subMenu, L"Ellipse");
}

void AddRectangleMenu(HMENU MainMenu, HMENU subMenu) {
    AppendMenu(subMenu, MF_STRING, 26, L"Draw Square");
    AppendMenu(subMenu, MF_STRING, 27, L"Draw Rectangle");
    AppendMenu(MainMenu, MF_POPUP, (UINT_PTR)subMenu, L"Rectangle");
}

void AddConvexMenu(HMENU MainMenu, HMENU subMenu) {
    AppendMenu(subMenu, MF_STRING, 28, L"Convex Filling");
    AppendMenu(subMenu, MF_STRING, 29, L"Non-Convex Filling");
    AppendMenu(MainMenu, MF_POPUP, (UINT_PTR)subMenu, L"Convex");
}

void AddFloodFillMenu(HMENU MainMenu, HMENU subMenu) {
    AppendMenu(subMenu, MF_STRING, 30, L"FloodFill Recursive");
    AppendMenu(subMenu, MF_STRING, 31, L"FloodFill Non-Recursive");
    AppendMenu(MainMenu, MF_POPUP, (UINT_PTR)subMenu, L"FloodFill");
}

void AddRectClipMenu(HMENU MainMenu, HMENU subMenu) {
    AppendMenu(subMenu, MF_STRING, 32, L"Point Clipping");
    AppendMenu(subMenu, MF_STRING, 33, L"Line Clipping");
    AppendMenu(subMenu, MF_STRING, 34, L"Polygon Clipping");
    AppendMenu(MainMenu, MF_POPUP, (UINT_PTR)subMenu, L"Rectangle Clipping");
}

void AddSqrClipMenu(HMENU MainMenu, HMENU subMenu) {
    AppendMenu(subMenu, MF_STRING, 35, L"Point Clipping");
    AppendMenu(subMenu, MF_STRING, 36, L"Line Clipping");
    AppendMenu(MainMenu, MF_POPUP, (UINT_PTR)subMenu, L"Square Clipping");
}

void AddCurveMenu(HMENU MainMenu, HMENU subMenu) {
    AppendMenu(subMenu, MF_STRING, 37, L"Filling Square Hermite Vertical");
    AppendMenu(subMenu, MF_STRING, 38, L"Filling Rectangle Bezier Horizontal");
    AppendMenu(subMenu, MF_STRING, 39, L"Spline");
    AppendMenu(MainMenu, MF_POPUP, (UINT_PTR)subMenu, L"Curve");
}


#endif
