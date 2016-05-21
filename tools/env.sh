export UNKNOWN_PROJECT_ROOT=$(pwd)

alias proot="cd  $UNKNOWN_PROJECT_ROOT"
alias test="$(echo $UNKNOWN_PROJECT_ROOT)/tools/test/test.sh"
alias build="$(echo $UNKNOWN_PROJECT_ROOT)/tools/build/cbuild.py"
alias build_engine="proot && build ECORE-LINUX"
alias build_test="proot && build ETEST-LINUX"
