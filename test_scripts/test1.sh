#!/bin/sh
.././main server > server_result.txt &
.././main client 6 127.0.0.1 57312 testUser resources/moves.txt 2 > client_result.txt

