#ifndef Canvas_h
#define Canvas_h

#include <string>

void OpenWindow(const std::string &title, int width, int height);
bool IsWindowOpen();
void CreateRaster(int scale);
void SetProjection(double left, double right, double bottom, double top);
void SetColor(int x, int y, double red, double green, double blue);
void DrawRect(double x, double y, double width, double height, double red, double green, double blue);
void DrawRaster();
void ClearCanvas();
void DisplayCanvas();
double GetCurrentTime();

#endif
