#include "uart.h"

#include <tbox/base/log.h>
#include <tbox/base/json.hpp>
#include <tbox/util/json.h>

#undef LOG_MODULE_ID
#define LOG_MODULE_ID "pa.uart"

namespace hevake {
namespace protocal_adapter {

using namespace std::placeholders;

Uart::Uart(tbox::main::Context &ctx, Parent &parent)
 : tbox::main::Module("uart", ctx)
 , parent_(parent)
 , uart_(ctx.loop())
{ }

//! 默认参数
void Uart::onFillDefaultConfig(tbox::Json &js) const {
  js["enable"] = false;
  js["dev"] = "/dev/ttyS0";
  js["mode"] = "115200 8n1";
  js["threshold"] = 1;
}

bool Uart::onInit(const tbox::Json &js) {
  tbox::util::json::GetField(js, "enable", is_enable_);

  if (is_enable_) {
    LogInfo("uart enabled");

    std::string dev;
    std::string mode;
    int threshold = 0;

    tbox::util::json::GetField(js, "dev", dev);
    tbox::util::json::GetField(js, "mode", mode);
    tbox::util::json::GetField(js, "threshold", threshold);
    LogDbg("uart dev:%s, mode:%s, threshold:%d", dev.c_str(), mode.c_str(), threshold);

    if (!uart_.initialize(dev, mode)) {
      LogErr("init mqtt fail");
      return false;
    }
    uart_.setReceiveCallback(std::bind(&Uart::onUartRecv, this, _1), threshold);
  }
  return true;
}

bool Uart::onStart() {
  if (is_enable_)
    return uart_.enable();
  else
    return true;
}

void Uart::onStop() {
  if (is_enable_)
    uart_.disable();
}

void Uart::toJson(tbox::Json &js) const {
  tbox::main::Module::toJson(js);
  js["is_enable"] = is_enable_;
}

void Uart::send(const void *data_ptr, size_t data_size) {
  if (is_enable_)
    uart_.send(data_ptr, data_size);
}

void Uart::onUartRecv(tbox::network::Buffer &buffer) {
  parent_.onRecv(type(), buffer.readableBegin(), buffer.readableSize());
  buffer.hasReadAll();
}

}
}
