#!/bin/bash

SCRIPT_PATH=$(realpath "$(dirname "${BASH_SOURCE[0]}")")
TODOS_PATH=$SCRIPT_PATH/../../build/Debug/to-dos-api

if [ ! -f "$TODOS_PATH" ]; then
  echo "'$TODOS_PATH' does not exist.\n"
  echo "Please build to-dos-api project first!"
  exit 1
else
  echo "Running to-dos-api..."
fi

"$TODOS_PATH" > /dev/null 2>&1 &
todos_pid=$!

todos_timeout=30
echo "Waiting for port 8000 to be ready..."
while ! lsof -i :8000 > /dev/null 2>&1; do
  sleep 1
  ((todos_timeout--))
  if [ $todos_timeout -le 0 ]; then
    echo "Timeout waiting for port 8000"
    kill -9 $todos_pid
    exit 1
  fi
done
echo "Port 8000 is now open."

curl_pids=()
for i in {1..10}; do
  echo "Sending request $i"
  curl -s -o /dev/null "http://127.0.0.1:8000/threads" &
  curl_pids+=($!)
done

echo "Running to-dos-api threads: "
ps -o nlwp= -p $todos_pid

for pid in "${curl_pids[@]}"; do
  wait $pid
done

kill -9 $todos_pid

echo "All requests completed."
 