#ifndef PROTOCAL_H
#define PROTOCAL_H

namespace hevake {
namespace protocal_adapter {

class Protocal {
 public:
  virtual std::string type() const = 0;
  virtual void send(const void *data_ptr, size_t data_size) = 0;

  class Parent {
   public:
    virtual void onRecv(const std::string &from_who, const void *data_ptr, size_t data_size) = 0;
  };
};

}
}

#endif //PROTOCAL_H
