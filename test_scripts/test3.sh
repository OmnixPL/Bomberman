#!/bin/sh
.././main server > server_result.txt &
.././test --gtest_filter=ClientSenderTest_1.* > client_result.txt