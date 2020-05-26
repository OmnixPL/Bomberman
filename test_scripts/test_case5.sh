#!/bin/sh
.././test --gtest_filter=IntegrationTests.RunServer > server_result.txt &
.././test --gtest_filter=IntegrationTests.TestCase1 > client1_result.txt &
.././test --gtest_filter=IntegrationTests.TestCase2 > client2_result.txt &
.././test --gtest_filter=IntegrationTests.TestCase3 > client3_result.txt &
.././test --gtest_filter=IntegrationTests.TestCase4 > client4_result.txt &
