# AngelScript Lua Virtual Machine
(Anĝelskripto Luao Virtuala Maŝino)

[**Elŝuti** - Windows](https://github.com/BrandonDyer64/ALVM/releases/download/0.2.0/ALVM.exe)

**Elŝuti** - Linux

**Elŝuti** - Mac

Cxi tio ne estas ludmotoro. Por ludmotoro kun Anĝelskripto kaj Luao, rigardu nian fratinan projecton, [Keplera Ludmotoro](https://keplerengine.com).

## Uzi ALVM

Faru la dosieron `Main.as` apud la `ALVM.exe`.

```angelscript
void Main() {
  // Diru Saluton!
  Std::Print("Saluton al Mondo!");
  // Kreu fenestron
  Canvas::OpenWindow("Saluton al Mondo!", 1280, 720);
  // Senfina iteracio
  while(Canvas::IsWindowOpen()) {
    // Bildigu
    Canvas::Clear();
    Canvas::DrawRect(320, 180, 640, 360, 1.0, 1.0, 1.0);
    Canvas::Display();
  }
}
```
