#include "tcp_server.h"

#include <tbox/base/log.h>
#include <tbox/base/json.hpp>
#include <tbox/util/json.h>

#undef LOG_MODULE_ID
#define LOG_MODULE_ID "pa.tcp_srv"

namespace hevake {
namespace protocal_adapter {

using namespace std::placeholders;

TcpServer::TcpServer(tbox::main::Context &ctx, Parent &parent)
 : tbox::main::Module("tcp_server", ctx)
 , parent_(parent)
 , tcp_(ctx.loop())
{ }

//! 默认参数
void TcpServer::onFillDefaultConfig(tbox::Json &js) {
  js["enable"] = false;
  js["bind"] = "0.0.0.0:12345";
  js["threshold"] = 1;
}

bool TcpServer::onInit(const tbox::Json &js) {
  tbox::util::json::GetField(js, "enable", is_enable_);

  if (is_enable_) {
    LogInfo("tcp server enabled");

    std::string bind;
    int threshold = 0;

    tbox::util::json::GetField(js, "bind", bind);
    tbox::util::json::GetField(js, "threshold", threshold);
    LogDbg("tcp_server bind:%s, threshold:%d", bind.c_str(), threshold);

    if (!tcp_.initialize(tbox::network::SockAddr::FromString(bind), 1)) {
      LogErr("init tcp_server fail");
      return false;
    }
    tcp_.setConnectedCallback(std::bind(&TcpServer::onTcpConnected, this, _1));
    tcp_.setDisconnectedCallback(std::bind(&TcpServer::onTcpDisconnected, this, _1));
    tcp_.setReceiveCallback(std::bind(&TcpServer::onTcpRecv, this, _1, _2), threshold);
  }
  return true;
}

bool TcpServer::onStart() {
  if (is_enable_)
    return tcp_.start();
  else
    return true;
}

void TcpServer::onStop() {
  if (is_enable_)
    tcp_.stop();
}

void TcpServer::send(const void *data_ptr, size_t data_size) {
  if (!conn_token_.isNull())
    tcp_.send(conn_token_, data_ptr, data_size);
}

void TcpServer::onTcpConnected(tbox::network::TcpServer::ConnToken conn) {
  if (!conn_token_.isNull())
    tcp_.disconnect(conn_token_);
  conn_token_ = conn;
}

void TcpServer::onTcpDisconnected(tbox::network::TcpServer::ConnToken conn) {
  conn_token_.reset();
}

void TcpServer::onTcpRecv(tbox::network::TcpServer::ConnToken, tbox::network::Buffer &buffer) {
  parent_.onRecv(type(), buffer.readableBegin(), buffer.readableSize());
  buffer.hasReadAll();
}

}
}
