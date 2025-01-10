function batch() {
  local file="$1"
  local dest="$2"

  git mv "include/$file.h" "include/$dest"
  git mv "src/$file.cpp" "src/$dest"
}

mkdir include/thex/ui
mkdir src/thex/ui

batch "thex/editor" "thex/ui"
batch "thex/statusbar" "thex/ui"
batch "thex/cmdline" "thex/ui"
