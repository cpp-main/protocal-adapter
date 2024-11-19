#include <tbox/main/module.h>
#include "protocal_adapter/create.h"

namespace tbox {
namespace main {

void RegisterApps(Module &apps, Context &ctx) {
  apps.add(hevake::protocal_adapter::Create(ctx));
}

std::string GetAppDescribe() {
  return "This is multi-protocal adapter middleware. support uart mqtt tcp udp";
}

void GetAppVersion(int &major, int &minor, int &rev, int &build) {
  major = 1;
  minor = 1;
  rev = 2;
  build = 7;
}

}
}
