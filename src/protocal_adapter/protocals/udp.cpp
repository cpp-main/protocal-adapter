#include "udp.h"

#include <tbox/base/log.h>
#include <tbox/base/json.hpp>
#include <tbox/util/json.h>

namespace hevake {
namespace protocal_adapter {

using namespace std::placeholders;

Udp::Udp(tbox::main::Context &ctx, Parent &parent)
 : tbox::main::Module("udp", ctx)
 , parent_(parent)
 , udp_(ctx.loop())
{ }

//! 默认参数
void Udp::onFillDefaultConfig(tbox::Json &js) {
  js["enable"] = false;
  js["connect"] = "0.0.0.0:23456";
  js["bind"] = "0.0.0.0:23456";
}

bool Udp::onInit(const tbox::Json &js) {
  tbox::util::json::GetField(js, "enable", is_enable_);

  if (is_enable_) {
    LogInfo("udp enabled");

    std::string bind, connect;
    if (tbox::util::json::GetField(js, "connect", connect)) {
      udp_.connect(tbox::network::SockAddr::FromString(connect));
      LogDbg("udp connect: %s", connect.c_str());
      is_connect_ = true;
    }

    if (tbox::util::json::GetField(js, "bind", bind)) {
      udp_.bind(tbox::network::SockAddr::FromString(bind));
      udp_.setRecvCallback(std::bind(&Udp::onRecv, this, _1, _2, _3));
      LogDbg("udp bind: %s", bind.c_str());
      is_bind_ = true;
    }
  }
  return true;
}

bool Udp::onStart() {
  if (is_bind_)
    return udp_.enable();
  else
    return true;
}

void Udp::onStop() {
  if (is_bind_)
    udp_.disable();
}

void Udp::send(const void *data_ptr, size_t data_size) {
  if (is_connect_)
    udp_.send(data_ptr, data_size);
}

void Udp::onRecv(const void *data_ptr, size_t data_size, const tbox::network::SockAddr &) {
  parent_.onRecv(type(), data_ptr, data_size);
}

}
}
