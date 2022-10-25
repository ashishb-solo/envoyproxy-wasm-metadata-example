# WASM Metadata example

This example demonstrates how to record and save metadata in a WASM filter. The example was adapted from the [proxy-wasm-cpp-sdk](https://github.com/proxy-wasm/proxy-wasm-cpp-sdk) reference module.

Typically, fields from requests are not available when the response is returned. For example, the request path would not be available at the same time as the response status code. However, this can be achieved easily using the WASM filter demonstrated here. A member variable called `path` is created in the `ExampleContext` class in `myproject.cc`. This variable is populated with the request path inside the `onRequestHeaders` callback. It is still available in the response - as can be seen in the `onResponseHeaders` callback, the status code is printed to the log as well as the saved request path.

Log output should look similar to this:

    [2022-10-25 16:51:19.933][28][info][wasm] [external/envoy/source/extensions/common/wasm/context.cc:1170] wasm log ashish-wasm-test-filter my_root_id gloo-vm-id: [myproject.cc:51]::onResponseHeaders() status code: 200
    [2022-10-25 16:51:19.933][28][info][wasm] [external/envoy/source/extensions/common/wasm/context.cc:1170] wasm log ashish-wasm-test-filter my_root_id gloo-vm-id: [myproject.cc:52]::onResponseHeaders() saved path: /
