#ifndef MQTT_H
#define MQTT_H

#include <tbox/main/module.h>
#include <tbox/mqtt/client.h>
#include "../protocal.h"

namespace hevake {
namespace protocal_adapter {

/**
 * Mqtt模块
 */
class Mqtt : public tbox::main::Module
           , public Protocal {
 public:
  explicit Mqtt(tbox::main::Context &ctx, Parent &parent);

 public:
  virtual void onFillDefaultConfig(tbox::Json &js) const override;
  virtual bool onInit(const tbox::Json &js) override;
  virtual bool onStart() override;
  virtual void onStop() override;
  virtual void onCleanup() override;

 public:
  virtual std::string type() const { return "mqtt"; }
  virtual void send(const void *data_ptr, size_t data_size) override;

 private:
  Parent &parent_;
  tbox::mqtt::Client mqtt_;
  bool is_enable_ = false;
  std::string send_topic_;
};

}
}

#endif //MQTT_H
