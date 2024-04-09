#ifndef UDP_H
#define UDP_H

#include <tbox/main/module.h>
#include <tbox/network/udp_socket.h>
#include "../protocal.h"

namespace hevake {
namespace protocal_adapter {

/**
 * Udp通信
 */
class Udp : public tbox::main::Module
          , public Protocal {
 public:
  explicit Udp(tbox::main::Context &ctx, Parent &parent);

 public:
  virtual void onFillDefaultConfig(tbox::Json &js) override;
  virtual bool onInit(const tbox::Json &js) override;
  virtual bool onStart() override;
  virtual void onStop() override;

 public:
  virtual std::string type() const override { return "udp"; }
  virtual void send(const void *data_ptr, size_t data_size) override;

 protected:
  void onRecv(const void *data_ptr, size_t data_size, const tbox::network::SockAddr &addr);

 private:
  Parent &parent_;
  tbox::network::UdpSocket udp_;
  bool is_enable_ = false;
  bool is_bind_ = false;
  bool is_connect_ = false;
};

}
}

#endif //UDP_H
