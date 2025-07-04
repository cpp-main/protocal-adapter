#ifndef UART_TO_MQTT_H
#define UART_TO_MQTT_H

#include <tbox/main/module.h>
#include "protocal.h"

namespace hevake {
namespace protocal_adapter {

class MainModule : public tbox::main::Module
                 , public Protocal::Parent {
 public:
  explicit MainModule(tbox::main::Context &ctx);

 protected:
  virtual void onFillDefaultConfig(tbox::Json &js) const override;
  virtual bool onInit(const tbox::Json &js) override;
  virtual bool onStart() override;
  virtual void onStop() override;
  virtual void toJson(tbox::Json &js) const override;

  virtual void onRecv(const std::string &type, const void *data_ptr, size_t data_size) override;

  void initShell();

 private:
  std::vector<Protocal*> protocals_;
  bool is_enable_log_ = false;
};

}
}

#endif //UART_TO_MQTT_H
