#include <tbox/main/module.h>
#include "protocal_adapter/main_module.h"

namespace tbox {
namespace main {

void RegisterApps(Module &apps, Context &ctx) {
  apps.add(new hevake::protocal_adapter::MainModule(ctx));
}

std::string GetAppDescribe() {
  return "This is multi-protocal adapter middleware. support uart mqtt tcp udp";
}

void GetAppVersion(int &major, int &minor, int &rev, int &build) {
  major = 1;
  minor = 0;
  rev = 2;
  build = 4;
}

}
}
