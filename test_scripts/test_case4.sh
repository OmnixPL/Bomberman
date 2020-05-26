#!/bin/sh
.././test --gtest_filter=IntegrationTests.RunServer > server_result.txt &
.././test --gtest_filter=IntegrationTests.TestCase3 > client1_result.txt &
.././test --gtest_filter=IntegrationTests.TestCase4 > client2_result.txt &
.././test --gtest_filter=IntegrationTests.TestCase5 > client3_result.txt 
