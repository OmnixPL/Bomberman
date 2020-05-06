#!/bin/sh
.././main server > server_result.txt &
.././main client 6 localhost 57312 > client_result.txt