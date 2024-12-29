function watch_changes() {
  watch_path="./"
  pid=""
  while inotifywait -q -r -e close_write,moved_to,create,delete $watch_path >/dev/null 2>&1; do
    bash ./run-build.sh >./logs.txt 2>&1
    status=$?

    if [ $status -eq 0 ]; then
      rm ./logs.txt
    fi

    pkill thex
  done
}

watch_changes &

while :; do
  clear

  ERR_LOG=$(cat ./logs.txt)

  if [ -n "$ERR_LOG" ]; then
    echo "$ERR_LOG"
  else
    bash ./run-command.sh
  fi

  sleep 1
done
