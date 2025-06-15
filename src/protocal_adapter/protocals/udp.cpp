#include "udp.h"

#include <tbox/base/log.h>
#include <tbox/base/json.hpp>
#include <tbox/util/json.h>

#undef LOG_MODULE_ID
#define LOG_MODULE_ID "pa.udp"

namespace hevake {
namespace protocal_adapter {

using namespace std::placeholders;

Udp::Udp(tbox::main::Context &ctx, Parent &parent)
 : tbox::main::Module("udp", ctx)
 , parent_(parent)
 , udp_(ctx.loop())
{ }

//! 默认参数
void Udp::onFillDefaultConfig(tbox::Json &js) const {
  js["enable"] = false;
  js["send"] = "127.0.0.1:6668";
  js["bind"] = "127.0.0.1:6669";
}

bool Udp::onInit(const tbox::Json &js) {
  bool is_enable = false;
  tbox::util::json::GetField(js, "enable", is_enable);

  if (is_enable) {
    LogInfo("udp enabled");

    std::string bind, send;
    if (tbox::util::json::GetField(js, "send", send)) {
      send_addr_ = tbox::network::SockAddr::FromString(send);
      //!NOTE: 这里采用记录发送地址而不是使用 udp_.connect() 设置目标地址，
      //!      是因为 connect()与bind()不能同时使用，否则bind()会失效，导致收不到数据。
      LogDbg("udp send: %s", send.c_str());
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
  if (send_addr_.type() != tbox::network::SockAddr::Type::kNone)
    udp_.send(data_ptr, data_size, send_addr_);
}

void Udp::onRecv(const void *data_ptr, size_t data_size, const tbox::network::SockAddr &) {
  parent_.onRecv(type(), data_ptr, data_size);
}

}
}
