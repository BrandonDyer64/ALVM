# AngelScript Lua Virtual Machine

Creates a binary that runs a Main.as file.

[**Download**](https://github.com/BrandonDyer64/ALVM/releases/latest)

This is not intended to be used as a game engine. For a similary functioning game engine with AngelScript and Lua see our sister project [Kepler Engine](https://keplerengine.com)

## Using ALVM

Make a file next to `ALVM.exe` called `Main.as`. This will be the file executed by the runtime.

```angelscript
void Main() {
  // Say Hello!
  Std::Print("Hello, World!");
  // Create a window
  Canvas::OpenWindow("Hello, World!", 1280, 720);
  // Main loop
  while(Canvas::IsWindowOpen()) {
    // Render
    Canvas::Clear();
    Canvas::DrawRect(320, 180, 640, 360, 1.0, 1.0, 1.0);
    Canvas::Display();
  }
}
```

## Roadmap

- [X] AngelScript VM
- [ ] Lua VM
- [X] OpenGL canvas
- [X] Windows support
- [ ] Linux support
- [ ] Mouse input
- [ ] Keyboard input
- [ ] Networking
- [ ] Package manager
- [ ] Native libraries
