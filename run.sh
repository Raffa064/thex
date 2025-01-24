#!/bin/bash

function load_settings() {
  source ./run-settings.sh
}

load_settings # first load

function watch_changes() {
  while inotifywait -q -r -e close_write,moved_to,create,delete $RUN_WATCH >/dev/null 2>&1; do
    load_settings

    if [ -f "$RUN_EXECUTABLE" ]; then
      rm $RUN_EXECUTABLE
    fi

    eval $RUN_BUILD_COMMAND >$RUN_LOG 2>&1
    status=$?

    if [ $status -eq 0 ]; then
      >$RUN_LOG # clear logs
    fi
    
    pkill $(basename $RUN_EXECUTABLE)
  done
}

watch_changes &

while :; do
  clear

  load_settings
  LOGS=$(cat $RUN_LOG 2>/dev/null)

  if [ -n "$LOGS" ]; then
    echo "$LOGS"
  else
    eval "$RUN_EXECUTABLE $RUN_ARGUMENTS"
  fi

  sleep 1
done
