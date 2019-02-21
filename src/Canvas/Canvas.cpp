#include "Canvas.h"
#include <glfw/glfw3.h>
#include <iostream>

GLFWwindow *window;

double *raster;
int rasterScale = -1;
int rasterWidth = 0;
int rasterHeight = 0;

int canvasWidth = 0;
int canvasHeight = 0;

int msaaSamples = 4;

double lastTime = 0.0;
double deltaTime = 0.0;

bool useCustomProjection = false;
double customProjection[4];

void OpenWindow(const std::string &title, int width, int height) {
  if (window) return;
  canvasWidth = width;
  canvasHeight = height;
  if (!glfwInit())
    return;
  glfwWindowHint(GLFW_SAMPLES, msaaSamples);
  window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
  if (!window) {
    glfwTerminate();
    return;
  }
  glfwMakeContextCurrent(window);
  glClearColor(0.1, 0.1, 0.1, 0.0);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  // glOrtho(0.0, 1.0, 0.0, 1.0, -1.0, 1.0);
  if (useCustomProjection) {
    glOrtho(customProjection[0], customProjection[1], customProjection[2], customProjection[3], -1.0, 1.0);
  } else {
    glOrtho(0.0, (double)width, (double)height, 0.0, -1.0, 1.0);
  }
  glClear(GL_COLOR_BUFFER_BIT);
}

void SetMSAA(int samples) {
  msaaSamples = samples;
}

bool IsWindowOpen() {
  return !glfwWindowShouldClose(window);
}

void CreateRaster(int scale) {
  rasterScale = scale;
  rasterWidth = canvasWidth / scale;
  rasterHeight = canvasHeight / scale;
  raster = new double[(canvasWidth / scale) * (canvasHeight / scale) * 3];
}

void SetProjection(double left, double right, double bottom, double top) {
  useCustomProjection = true;
  customProjection[0] = left;
  customProjection[1] = right;
  customProjection[2] = bottom;
  customProjection[3] = top;
}

void SetColor(int x, int y, double red, double green, double blue) {
  /*double *location = &raster[(x * 3) + y * rasterWidth];
  *location = red;
  *(location + 1) = green;
  *(location + 2) = blue;*/
  raster[(x + y * rasterWidth) * 3] = red;
  raster[(x + y * rasterWidth) * 3 + 1] = green;
  raster[(x + y * rasterWidth) * 3 + 2] = blue;
}

void DrawRect(double x, double y, double width, double height, double red, double green, double blue) {
  glColor3f (red, green, blue);
  glBegin(GL_POLYGON);
    glVertex2f(x, y);
    glVertex2f(x + width, y);
    glVertex2f(x + width, y + height);
    glVertex2f(x, y + height);
  glEnd();
}

void DrawLine(double x0, double y0, double x1, double y1, double red, double green, double blue) {
  glColor3f (red, green, blue);
  glBegin(GL_LINES);
    glVertex2f(x0, y0);
    glVertex2f(x1, y1);
  glEnd();
}

void DrawRaster() {
  if (rasterScale == -1) return;
  double *location = raster;
  for (int y = 0; y < rasterHeight; y++) {
    for (int x = 0; x < rasterWidth; x++) {
      DrawRect(
        x * rasterScale,
        y * rasterScale,
        rasterScale,
        rasterScale,
        *location,
        *(location + 1),
        *(location + 2)
      );
      location += 3;
    }
  }
}

void ClearCanvas() {
  glClear(GL_COLOR_BUFFER_BIT);
}

void DisplayCanvas() {
  double nowTime = glfwGetTime();
  deltaTime = nowTime - lastTime;
  lastTime = nowTime;
  glFlush();
  glfwSwapInterval(1);
  glfwSwapBuffers(window);
  glfwPollEvents();
}

double GetDeltaTime() {
  return deltaTime;
}

double GetCurrentTime() {
  return glfwGetTime();
}
