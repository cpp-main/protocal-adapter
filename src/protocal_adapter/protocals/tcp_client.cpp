#include "tcp_client.h"

#include <tbox/base/log.h>
#include <tbox/base/json.hpp>
#include <tbox/util/json.h>
#include <tbox/network/buffer.h>

#undef LOG_MODULE_ID
#define LOG_MODULE_ID "pa.tcp_cli"

namespace hevake {
namespace protocal_adapter {

using namespace std::placeholders;

TcpClient::TcpClient(tbox::main::Context &ctx, Parent &parent)
 : tbox::main::Module("tcp_client", ctx)
 , parent_(parent)
 , tcp_(ctx.loop())
{ }

//! 默认参数
void TcpClient::onFillDefaultConfig(tbox::Json &js) {
  js["enable"] = false;
  js["connect"] = "0.0.0.0:12345";
  js["threshold"] = 1;
}

bool TcpClient::onInit(const tbox::Json &js) {
  tbox::util::json::GetField(js, "enable", is_enable_);

  if (is_enable_) {
    LogInfo("tcp client enabled");

    std::string addr;
    int threshold = 0;

    tbox::util::json::GetField(js, "connect", addr);
    tbox::util::json::GetField(js, "threshold", threshold);
    LogDbg("tcp_client connect:%s, threshold:%d", addr.c_str(), threshold);

    if (!tcp_.initialize(tbox::network::SockAddr::FromString(addr))) {
      LogErr("init tcp fail");
      return false;
    }
    tcp_.setReceiveCallback(std::bind(&TcpClient::onTcpRecv, this, _1), threshold);
  }
  return true;
}

bool TcpClient::onStart() {
  if (is_enable_)
    return tcp_.start();
  else
    return true;
}

void TcpClient::onStop() {
  if (is_enable_)
    tcp_.stop();
}

void TcpClient::send(const void *data_ptr, size_t data_size) {
  if (tcp_.state() == tbox::network::TcpClient::State::kConnected)
    tcp_.send(data_ptr, data_size);
}

void TcpClient::onTcpRecv(tbox::network::Buffer &buffer) {
  parent_.onRecv(type(), buffer.readableBegin(), buffer.readableSize());
  buffer.hasReadAll();
}

}
}
