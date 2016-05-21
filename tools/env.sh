export UNKNOWN_PROJECT_ROOT=$(pwd)

alias proot="cd  $UNKNOWN_PROJECT_ROOT"
alias test=./tools/test/test.sh
alias build=./tools/build/cbuild.py
alias build_engine="build ECORE-LINUX"
alias build_test="build ETEST-LINUX"
