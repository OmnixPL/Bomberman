#!/bin/sh
.././main server > server_result.txt &
.././main client 6 localhost 57312 resources/moves.txt > client_result.txt

