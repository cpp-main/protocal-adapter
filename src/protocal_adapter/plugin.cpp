#include "main_module.h"
#include <tbox/main/main.h>

//! 作为插件的入口，使得可以被 run 执行
extern "C" void RegisterApps(tbox::main::Module &apps, tbox::main::Context &ctx) {
  apps.add(new hevake::protocal_adapter::MainModule(ctx));
}
