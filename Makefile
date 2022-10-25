PROXY_WASM_CPP_SDK=/sdk

all: myproject.wasm
	chown ${uid}.${gid} $^

include ${PROXY_WASM_CPP_SDK}/Makefile.base_lite
