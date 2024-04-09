#include "main_module.h"

#include <tbox/base/log.h>
#include <tbox/base/json.hpp>
#include <tbox/util/json.h>
#include <tbox/util/string.h>
#include <tbox/terminal/terminal_nodes.h>
#include <tbox/terminal/helper.h>

namespace hevake {
namespace protocal_adapter {

MainModule::MainModule(tbox::main::Context &ctx)
 : tbox::main::Module("protocal_adapter", ctx)
{
  auto mqtt = new Mqtt(ctx, *this);
  add(mqtt);
  protocals_.push_back(mqtt);

  auto uart = new Uart(ctx, *this);
  add(uart);
  protocals_.push_back(uart);
}

void MainModule::onFillDefaultConfig(tbox::Json &js) {
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

  shell->mountNode(shell->rootNode(), dir_node, "protocal_adapter");
  tbox::terminal::AddFuncNode(*shell, dir_node, "is_enable_log", is_enable_log_);
}

}
}
