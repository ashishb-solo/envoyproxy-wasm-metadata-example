// NOLINT(namespace-envoy)
#include <string>
#include <string_view>
#include <unordered_map>

#include "proxy_wasm_intrinsics.h"

class ExampleRootContext : public RootContext {
public:
  explicit ExampleRootContext(uint32_t id, std::string_view root_id) : RootContext(id, root_id) {}

  bool onConfigure(size_t) override;
};

class ExampleContext : public Context {
public:
  // store path from the request in the Context so it is available when the
  // response comes back
  std::string path;
  explicit ExampleContext(uint32_t id, RootContext* root) : Context(id, root) {}

  void onCreate() override;
  FilterHeadersStatus onRequestHeaders(uint32_t headers, bool end_of_stream) override;
  FilterHeadersStatus onResponseHeaders(uint32_t headers, bool end_of_stream) override;
};

static RegisterContextFactory register_ExampleContext(CONTEXT_FACTORY(ExampleContext),
                                                      ROOT_FACTORY(ExampleRootContext),
                                                      "my_root_id");

bool ExampleRootContext::onConfigure(size_t) {
  LOG_TRACE("onConfigure");
  proxy_set_tick_period_milliseconds(1000); // 1 sec
  return true;
}

void ExampleContext::onCreate() { LOG_WARN(std::string("onCreate " + std::to_string(id()))); }

// store the path when the request comes in
FilterHeadersStatus ExampleContext::onRequestHeaders(uint32_t, bool) {
  LOG_DEBUG(std::string("onRequestHeaders ") + std::to_string(id()));
  auto responseStatus = getRequestHeader(":path");
  path = responseStatus->toString();
  return FilterHeadersStatus::Continue;
}

// print the status code and the saved path value
FilterHeadersStatus ExampleContext::onResponseHeaders(uint32_t, bool) {
  LOG_DEBUG(std::string("onResponseHeaders ") + std::to_string(id()));
  auto responseStatus = getResponseHeader(":status");
  LOG_INFO(std::string("status code: ") + responseStatus->toString());
  LOG_INFO(std::string("saved path: ") + path);
  return FilterHeadersStatus::Continue;
}
