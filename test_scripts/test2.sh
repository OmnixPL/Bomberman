#!/bin/sh
.././main server > server_result.txt &
.././test --gtest_filter=ClientTest_1.* > client_result.txt