#!/bin/sh
.././test --gtest_filter=IntegrationTests.TestServerLoop > server_result.txt &
.././test --gtest_filter=IntegrationTests.TestClientLoop > client_result.txt
