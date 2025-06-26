#include "main_module.h"

#include <tbox/base/log.h>
#include <tbox/base/json.hpp>
#include <tbox/util/json.h>
#include <tbox/util/string.h>
#include <tbox/terminal/terminal_nodes.h>
#include <tbox/terminal/helper.h>

#include "protocals/mqtt.h"
#include "protocals/uart.h"
#include "protocals/tcp_client.h"
#include "protocals/tcp_server.h"
#include "protocals/udp.h"

namespace hevake {
namespace protocal_adapter {

MainModule::MainModule(tbox::main::Context &ctx)
 : tbox::main::Module("pa", ctx)
{
  auto mqtt = new Mqtt(ctx, *this);
  add(mqtt);
  protocals_.push_back(mqtt);

  auto uart = new Uart(ctx, *this);
  add(uart);
  protocals_.push_back(uart);

  auto tcp_server = new TcpServer(ctx, *this);
  add(tcp_server);
  protocals_.push_back(tcp_server);

  auto tcp_client = new TcpClient(ctx, *this);
  add(tcp_client);
  protocals_.push_back(tcp_client);

  auto udp = new Udp(ctx, *this);
  add(udp);
  protocals_.push_back(udp);
}

void MainModule::onFillDefaultConfig(tbox::Json &js) const {
  js["is_enable_log"] = false;
}

bool MainModule::onInit(const tbox::Json &js) {
  tbox::util::json::GetField(js, "is_enable_log", is_enable_log_);
  initShell();
  return true;
}

bool MainModule::onStart() {
  LogInfo("started");
  return true;
}

void MainModule::onStop() {
  LogInfo("stoped");
}

void MainModule::toJson(tbox::Json &js) const {
  tbox::main::Module::toJson(js);
  js["is_enable_log"] = is_enable_log_;
}

void MainModule::onRecv(const std::string &from_who, const void *data_ptr, size_t data_size) {
  if (is_enable_log_) {
    std::string hex_str = tbox::util::string::RawDataToHexStr(data_ptr, data_size);
    LogInfo("%s recv [%d]: %s", from_who.c_str(), data_size, hex_str.c_str());
  }

  for (auto item : protocals_) {
    if (item->type() != from_who) {
      item->send(data_ptr, data_size);
    }
  }
}

void MainModule::initShell() {
  auto shell = ctx().terminal();
  auto dir_node = shell->createDirNode();

  shell->mountNode(shell->rootNode(), dir_node, name());
  tbox::terminal::AddFuncNode(*shell, dir_node, "is_enable_log", is_enable_log_);
}

}
}
