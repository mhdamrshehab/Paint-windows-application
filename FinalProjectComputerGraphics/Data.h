#ifndef FINALPROJECTCOMPUTERGRAPHICS_Data_H
#define FINALPROJECTCOMPUTERGRAPHICS_Data_H

#include "Line.h"
#include "Circle.h"
#include "Rectangle.h"
#include "AddProgMenus.h"
#include "Ellipse.h"
#include "ConvexFilling.h"
#include "NonConvexFilling.h"
#include "FloodFilling.h"
#include "LineClipping.h"
#include "HermiteCurve.h"
#include "PolygonClipping.h"
#include "BezierCurve.h"
#include <string>

class FileSettings {
public:
    static string ParsePoints(Point* P, int n) {
        string str = " ";
        for (int i = 0; i < n; i++) {
            str = str + to_string(P[i].x) + " " + to_string(P[i].y) + " ";
        }
        return str;
    }

    string filename;
    explicit FileSettings(string filename) :filename(std::move(filename)) {}

    bool LoadDataFromFile(HDC hdc, const string& saved) {
        ifstream file(saved.c_str(), ios::in);

        if (!file.is_open())
            return false;

        cout << "\nPlease Wait To Load Date..\n";

        int choiceMode, ShapeID, x1, y1, x2, y2, R, red, green, blue, menuChoice, Mode, Q;
        class Window W;
        class Vector2 Vect[4];
        class vector<Point> ResPoly;

        while (!file.eof()) {
            file >> choiceMode;

            if (choiceMode == 1) {
                choiceMode = -1;
                file >> ShapeID;
                switch (ShapeID) {
                case 0: case 1: case 2: case 12: case 13:
                    file >> x1 >> y1 >> x2 >> y2 >> red >> green >> blue;
                    switch (ShapeID) {
                    case 0: DrawLineDDA(hdc, Line(x1, y1, x2, y2), RGB(red, green, blue)); break;
                    case 1: DrawLineMidPoint(hdc, Line(Line(x1, y1, x2, y2)), RGB(red, green, blue)); break;
                    case 2: DrawLine(hdc, Line(x1, y1, x2, y2), RGB(red, green, blue)); break;
                    case 12: W.drawSquare(hdc, y1, y2, x1, x2, RGB(red, green, blue)); break;
                    case 13: W.drawRectangle(hdc, y1, y2, x1, x2, RGB(red, green, blue)); break;
                    }
                    break;
                case 3: case 4: case 5: case 6: case 7: case 8: case 9: case 10: case 11:
                    file >> x1 >> y1 >> R >> red >> green >> blue;
                    switch (ShapeID) {
                    case 3: DrawCircleDirect(hdc, Point(x1, y1), R, RGB(red, green, blue)); break;
                    case 4: DrawCirclePolorSimilarity(hdc, Point(x1, y1), R, RGB(red, green, blue)); break;
                    case 5: DrawCircleIterativePolar(hdc, Point(x1, y1), R, RGB(red, green, blue)); break;
                    case 6: DrawCircleBresenhamMidPoint(hdc, Point(x1, y1), R, RGB(red, green, blue)); break;
                    case 7: DrawCircleBresenhamImproveI(hdc, Point(x1, y1), R, RGB(red, green, blue));
                        DrawCircleBresenhamImproveII(hdc, Point(x1, y1), R, RGB(red, green, blue)); break;
                    case 8: DrawEllipseCart(hdc, Point(x1, y1), R, R / 2, RGB(red, green, blue)); break;
                    case 9: DrawEllipsePolar(hdc, Point(x1, y1), R, R / 2, RGB(red, green, blue)); break;
                    case 10: DrawEllipseIterativePolar(hdc, Point(x1, y1), R, R / 2, RGB(red, green, blue)); break;
                    case 11: DrawEllipseMidPoint(hdc, Point(x1, y1), R, R / 2, RGB(red, green, blue)); break;
                    }
                }
            }

            else if (choiceMode == 2) {
                choiceMode = -1;
                file >> menuChoice;

                if (menuChoice >= 16 && menuChoice <= 21) {
                    file >> Mode >> Q >> x1 >> y1 >> R >> red >> green >> blue;
                    switch (Mode) {
                    case 0: FillingCircleWithLines(hdc, Point(x1, y1), R, Q, 1.57, RGB(red, green, blue)); break;
                    case 1: FillingCircleWithCircles(hdc, Point(x1, y1), R, Q, 1.57, RGB(red, green, blue)); break;
                    }
                }

                else if (menuChoice == 28 || menuChoice == 29 || (menuChoice >= 32 && menuChoice <= 38)) {
                    file >> R >> red >> green >> blue;
                    Point* Res = new Point[R];

                    for (int i = 0; i < R; i++) {
                        file >> x1 >> y1;
                        switch (menuChoice) {
                        case 37: case 39:
                            Vect[i].x = x1;
                            Vect[i].y = y1;
                            break;
                        default:
                            Res[i].x = x1;
                            Res[i].y = y1;
                        }
                    }

                    switch (menuChoice) {
                    case 28: ConvexFilling(hdc, Res, R, RGB(red, green, blue)); break;
                    case 29: NonConvexFilling(hdc, Res, R, RGB(red, green, blue)); break;
                    case 34: ConvexFilling(hdc, Res, R, RGB(red, green, blue)); break;
                    case 32: case 35: SetPixel(hdc, Res[0].x, Res[0].y, RGB(red, green, blue)); break;
                    case 33: case 36: DrawLine(hdc, Line(Res[0].x, Res[0].y, Res[1].x, Res[1].y), RGB(red, green, blue)); break;
                    case 37: case 38:
                        file >> W.Left >> W.Top >> W.Right >> W.Bottom;
                        menuChoice == 37 ? FillingHermite(hdc, Vect, W, RGB(red, green, blue)) : FillingBezier(hdc, Res, R, W, RGB(red, green, blue));
                        break;
                    case 39: Spline(hdc, Vect, R, 0.00001, RGB(red, green, blue));  break;
                    }
                }

                else if (menuChoice == 30 || menuChoice == 31) {
                    file >> x1 >> y1 >> red >> green >> blue;
                    switch (menuChoice) {
                    case 30: FloodFillRec(hdc, Point(x1, y1), RGB(64, 64, 64), RGB(red, green, blue)); break;
                    case 31: FloodFillNonRecQ(hdc, Point(x1, y1), RGB(64, 64, 64), RGB(red, green, blue)); break;
                    }
                }

            }
        }

        file.close();
        cout << "\nLoaded Successfully\n";
        return true;
    }

    void SaveCurrentData(int ShapeID, Point* Clicks, int R, COLORREF c, int menuChoice, int Mode, int Q) {
        ofstream file(filename.c_str(), ios::app);

        int red = GetRValue(c);
        int green = GetGValue(c);
        int blue = GetBValue(c);

        if ((ShapeID >= 0 && ShapeID <= 2) || ShapeID == 12 || ShapeID == 13)
            file << "1 " << ShapeID << " " << ParsePoints(Clicks, 2) << red << " " << green << " " << blue << endl;

        else if (ShapeID >= 3 && ShapeID <= 11)
            file << "1 " << ShapeID << " " << ParsePoints(Clicks, 1) << R << " " << red << " " << green << " " << blue << endl;

        if (menuChoice >= 16 && menuChoice <= 21)
            file << "2 " << menuChoice << " " << Mode << " " << Q << ParsePoints(Clicks, 1) << R << " " << red << " " << green << " " << blue << endl;

        else if (menuChoice == 30 || menuChoice == 31)
            file << "2 " << menuChoice << ParsePoints(Clicks, 1) << red << " " << green << " " << blue << endl;

        else if (menuChoice >= 28 && menuChoice <= 36)
            file << "2 " << menuChoice << " " << R << " " << red << " " << green << " " << blue << ParsePoints(Clicks, R) << endl;

        else if (menuChoice >= 37 && menuChoice <= 39)
            file << "2 " << menuChoice << " " << R << " " << red << " " << green << " " << blue << ParsePoints(Clicks, R + 2) << endl;

        file.close();
    }

    bool SaveFromTemp(const string& savedFile) const {
        ifstream source_file(filename.c_str());

        if (!source_file.is_open()) {
            cout << "Failed to open source file: " << filename << endl;
            return false;
        }

        ofstream dest_file(savedFile.c_str());
        if (!dest_file.is_open()) {
            cout << "Failed to open destination file: " << savedFile << endl;
            return false;
        }

        string line;
        while (getline(source_file, line))
            dest_file << line << endl;

        source_file.close();
        dest_file.close();
        cout << "\nSaved Successfully\n";
        return true;
    }

    static void ClearData(const string& filename) {
        ofstream outfile;
        outfile.open(filename.c_str(), ios::trunc);

        if (!outfile.is_open()) {
            std::cerr << "Failed to open file: " << filename << std::endl;
            return;
        }

        outfile.close();
        cout << "File " << filename << " cleared." << endl;
    }

    static bool DeleteFile(const string& filename) {
        if (remove(filename.c_str()) != 0)
            return false;
        else
            return true;
    }
};



#endif