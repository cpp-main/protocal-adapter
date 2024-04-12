#include "create.h"

#include "main_module.h"

namespace hevake {
namespace protocal_adapter {

tbox::main::Module* Create(tbox::main::Context &ctx) {
  return new MainModule(ctx);
}

}
}

