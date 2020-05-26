#!/bin/sh
.././test --gtest_filter=IntegrationTests.RunServer > server_result.txt &
.././test --gtest_filter=IntegrationTests.TestCase2
