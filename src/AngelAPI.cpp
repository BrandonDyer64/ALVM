#include "AngelAPI.h"
#include "Canvas/Canvas.h"

#define asF(name, func, call) r |= engine->RegisterGlobalFunction(name, asFUNCTION(func), call);

void Print(const std::string &s) {
  std::cout << s << std::endl;
}

void PrintDouble(double s) {
  std::cout << s << std::endl;
}

void PrintF(const std::string &s) {
  printf(s.c_str());
}

int RegisterAngelFunctions(asIScriptEngine *engine) {
  int r = 0;

  // Output
  engine->SetDefaultNamespace("Std");
  asF("void Print(const string &in)", Print, asCALL_CDECL);
  asF("void Printu(const string &in)", Print, asCALL_CDECL);
  asF("void Print(double)", PrintDouble, asCALL_CDECL);
  asF("void Printu(double)", PrintDouble, asCALL_CDECL);
  asF("void PrintF(const string &in)", PrintF, asCALL_CDECL);
  asF("void PrintuF(const string &in)", PrintF, asCALL_CDECL);
  asF("double Time()", GetCurrentTime, asCALL_CDECL);
  asF("double DeltaTime()", GetDeltaTime, asCALL_CDECL);
  asF("double Tempo()", GetCurrentTime, asCALL_CDECL);

  // Math
  engine->SetDefaultNamespace("Math");
  RegisterScriptMath(engine);
  engine->SetDefaultNamespace("Matematiko");
  RegisterScriptMath(engine);

  // Canvas
  engine->SetDefaultNamespace("Canvas");
  asF("void OpenWindow(const string &in, int, int)", OpenWindow, asCALL_CDECL);
  asF("void SetMSAA(int)", SetMSAA, asCALL_CDECL);
  asF("bool IsWindowOpen()", IsWindowOpen, asCALL_CDECL);
  asF("void CreateRaster(int)", CreateRaster, asCALL_CDECL);
  asF("void SetProjection(double, double, double, double)", SetProjection, asCALL_CDECL);
  asF("void SetColor(int, int, double, double, double)", SetColor, asCALL_CDECL);
  asF("void DrawRect(double, double, double, double, double, double, double)", DrawRect, asCALL_CDECL);
  asF("void DrawLine(double, double, double, double, double, double, double)", DrawLine, asCALL_CDECL);
  asF("void DrawRaster()", DrawRaster, asCALL_CDECL);
  asF("void Clear()", ClearCanvas, asCALL_CDECL);
  asF("void Display()", DisplayCanvas, asCALL_CDECL);
  engine->SetDefaultNamespace("Kanvaso");
  asF("void KreuFenestron(const string &in, int, int)", OpenWindow, asCALL_CDECL);
  asF("bool CxuFenestroMalferma()", IsWindowOpen, asCALL_CDECL);
  asF("void KreuRastrumon(int)", CreateRaster, asCALL_CDECL);
  asF("void IndikuKoloron(int, int, double, double, double)", SetColor, asCALL_CDECL);
  asF("void DesegnuOrtangulon(double, double, double, double, double, double, double)", DrawRect, asCALL_CDECL);
  asF("void DesegnuRastrumon()", DrawRaster, asCALL_CDECL);
  asF("void Vakigu()", ClearCanvas, asCALL_CDECL);
  asF("void Vidigu()", DisplayCanvas, asCALL_CDECL);

  return r;
}
