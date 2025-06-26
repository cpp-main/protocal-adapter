#ifndef TCP_SERVER_H
#define TCP_SERVER_H

#include <tbox/main/module.h>
#include <tbox/network/tcp_server.h>
#include "../protocal.h"

namespace hevake {
namespace protocal_adapter {

/**
 * Tcp服务端
 */
class TcpServer : public tbox::main::Module
                , public Protocal {
 public:
  explicit TcpServer(tbox::main::Context &ctx, Parent &parent);

 public:
  virtual void onFillDefaultConfig(tbox::Json &js) const override;
  virtual bool onInit(const tbox::Json &js) override;
  virtual bool onStart() override;
  virtual void onStop() override;

  virtual void toJson(tbox::Json &js) const override;

 public:
  virtual std::string type() const override { return "tcp_server"; }
  virtual void send(const void *data_ptr, size_t data_size) override;

 protected:
  void onTcpConnected(tbox::network::TcpServer::ConnToken conn);
  void onTcpDisconnected(tbox::network::TcpServer::ConnToken conn);
  void onTcpRecv(tbox::network::TcpServer::ConnToken, tbox::network::Buffer &buffer);

 private:
  Parent &parent_;
  tbox::network::TcpServer tcp_;
  tbox::network::TcpServer::ConnToken conn_token_;
  bool is_enable_ = false;
};

}
}

#endif //TCP_SERVER_H
