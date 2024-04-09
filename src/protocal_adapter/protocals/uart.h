#ifndef UART_H
#define UART_H

#include <tbox/main/module.h>
#include <tbox/network/uart.h>
#include "../protocal.h"

namespace hevake {
namespace protocal_adapter {

/**
 * 串口通信模块
 */
class Uart : public tbox::main::Module
           , public Protocal {
 public:
  explicit Uart(tbox::main::Context &ctx, Parent &parent);

 public:
  virtual void onFillDefaultConfig(tbox::Json &js) override;
  virtual bool onInit(const tbox::Json &js) override;
  virtual bool onStart() override;
  virtual void onStop() override;

 public:
  virtual std::string type() const override { return "uart"; }
  virtual void send(const void *data_ptr, size_t data_size) override;

 protected:
  void onUartRecv(tbox::network::Buffer &buffer);

 private:
  Parent &parent_;
  tbox::network::Uart uart_;
  bool is_enable_ = false;
};

}
}

#endif //UART_H
