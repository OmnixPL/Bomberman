#!/bin/sh
.././main client 6 localhost 57312 > client_result.txt
.././main server > server_result.txt &
