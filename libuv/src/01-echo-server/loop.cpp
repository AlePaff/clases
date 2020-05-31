#include "loop.h"

uv::Loop::Loop() {
    uv_loop_init(&loop);
}

uv::Loop::~Loop() {
    uv_loop_close(&loop);
}

void uv::Loop::run() {
    uv_run(&loop, UV_RUN_DEFAULT);
}
 