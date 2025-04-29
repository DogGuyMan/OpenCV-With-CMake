#ifdef CHAPTER6
#include "chapter6/drawing_rectangle.hpp"
#include "chapter6/drawing_line.hpp"
#include "chapter6/drawing_circle.hpp"
#include "chapter6/drawing_polygon.hpp"
#include "chapter6/drawing_text.hpp"
#include "chapter6/drawing_others.hpp"

int Chapter6() {
    chapter6::DrawingRectangleWithPoints();
    chapter6::DrawingRectangleWithRect();
    chapter6::FillRectangleWithRect();
    chapter6::DrawingLine();
    chapter6::DrawingCircle();
    chapter6::FillCircle();
    chapter6::DrawingPolygon();
    chapter6::DrawingMultiplePoly();
    chapter6::DrawingPolyLine();
    chapter6::DrawingText();
    chapter6::DrawingDateTime();
    chapter6::DrawingArrow();
    chapter6::DrawingMarker();
    chapter6::DrawingTrackbar();
    return 1;
}

#endif
