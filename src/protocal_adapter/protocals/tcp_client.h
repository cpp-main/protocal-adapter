#ifndef TCP_CLIENT_H
#define TCP_CLIENT_H

#include <tbox/main/module.h>
#include <tbox/network/tcp_client.h>
#include "../protocal.h"

namespace hevake {
namespace protocal_adapter {

/**
 * Tcp客户端
 */
class TcpClient : public tbox::main::Module
                , public Protocal {
 public:
  explicit TcpClient(tbox::main::Context &ctx, Parent &parent);

 public:
  virtual void onFillDefaultConfig(tbox::Json &js) const override;
  virtual bool onInit(const tbox::Json &js) override;
  virtual bool onStart() override;
  virtual void onStop() override;

 public:
  virtual std::string type() const override { return "tcp_client"; }
  virtual void send(const void *data_ptr, size_t data_size) override;

 protected:
  void onTcpRecv(tbox::network::Buffer &buffer);

 private:
  Parent &parent_;
  tbox::network::TcpClient tcp_;
  bool is_enable_ = false;
};

}
}

#endif //TCP_CLIENT_H
