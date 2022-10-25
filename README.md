# WASM Metadata example

This example demonstrates how to record and save metadata in a WASM filter. The example was adapted from the [proxy-wasm-cpp-sdk](https://github.com/proxy-wasm/proxy-wasm-cpp-sdk) reference module.

Typically, fields from requests are not available when the response is returned. For example, the request path is would not be available at the same time as the response status code. However, this is easily possible using the WASM filter demonstrated here. A member variable called `path` is created in the `ExampleContext` class. This variable is populated with the request path inside the `onRequestHeaders` callback. It is still available in the response - as can be seen in the `onResponseHeaders` callback, the status code is printed to the log as well as the saved request path.
