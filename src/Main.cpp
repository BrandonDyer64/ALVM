#include <iostream>
#include <string>
#include <angelscript.h>
#include <scriptstdstring/scriptstdstring.h>
#include <scriptbuilder/scriptbuilder.h>

#ifdef _WIN32
#include <windows.h>
WORD saved_attributes;
#endif

void print(const std::string &s) {
  std::cout << s << std::endl;
}

void SetColorAndBackground(WORD wColor);
void SaveAttributes();
void MessageCallback(const asSMessageInfo *msg, void *param)
{
  const char *type = "ERR ";
  if( msg->type == asMSGTYPE_WARNING ) {
    type = "WARN";
    return;
  }
  else if( msg->type == asMSGTYPE_INFORMATION ) {
    type = "INFO";
    return;
  }
  #ifdef _WIN32
  SaveAttributes();
  SetColorAndBackground(FOREGROUND_BLUE);
  SetColorAndBackground(BACKGROUND_BLUE);
  printf("Exeption");
  SetColorAndBackground(saved_attributes);
  #else
  std::cout << "Exeption " << msg->message << std::endl;
  printf("    at %s:%d\n", msg->section, msg->row);
  #endif
}

int main() {
  // Create AngelScript Engine
  asIScriptEngine *angelEngine = asCreateScriptEngine();

  int r = angelEngine->SetMessageCallback(asFUNCTION(MessageCallback), 0, asCALL_CDECL);
  //assert(r >= 0);

  RegisterStdString(angelEngine);

  r = angelEngine->RegisterGlobalFunction("void Print(const string &in)", asFUNCTION(print), asCALL_CDECL);
  //assert(r >= 0);

  CScriptBuilder builder;
  r = builder.StartNewModule(angelEngine, "MyModule");
  if( r < 0 )
  {
    // If the code fails here it is usually because there
    // is no more memory to allocate the module
    printf("Unrecoverable error while starting a new module.\n");
    return 1;
  }
  r = builder.AddSectionFromFile("Main.as");
  if( r < 0 )
  {
    // The builder wasn't able to load the file. Maybe the file
    // has been removed, or the wrong name was given, or some
    // preprocessing commands are incorrectly written.
    printf("Please correct the errors in the script and try again.\n");
    return 1;
  }
  r = builder.BuildModule();
  if( r < 0 )
  {
    // An error occurred. Instruct the script writer to fix the
    // compilation errors that were listed in the output stream.
    printf("Compiler Error.\n");
    return 1;
  }

  // Find the function that is to be called.
  asIScriptModule *mod = angelEngine->GetModule("MyModule");
  asIScriptFunction *func = mod->GetFunctionByDecl("void Main()");
  if( func == 0 )
  {
    // The function couldn't be found. Instruct the script writer
    // to include the expected function in the script.
    printf("The script must have the function 'void Main()'. Please add it and try again.\n");
    return 1;
  }
  // Create our context, prepare it, and then execute
  asIScriptContext *ctx = angelEngine->CreateContext();
  ctx->Prepare(func);
  r = ctx->Execute();
  if( r != asEXECUTION_FINISHED )
  {
    // The execution didn't complete as expected. Determine what happened.
    if( r == asEXECUTION_EXCEPTION )
    {
      // An exception occurred, let the script writer know what happened so it can be corrected.
      printf("An exception '%s' occurred. Please correct the code and try again.\n", ctx->GetExceptionString());
    }
  }

  // Clean up
  ctx->Release();
  angelEngine->ShutDownAndRelease();

  std::cout << "Done." << std::endl;
  return 0;
}

#ifdef _WIN32
void SetColorAndBackground(WORD wColor)
{
     //WORD wColor = ((BackC & 0x0F) << 4) + (ForgC & 0x0F);
     SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), wColor);
     return;
}
void SaveAttributes() {
  CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
  GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &consoleInfo);
  saved_attributes = consoleInfo.wAttributes;
}
#endif