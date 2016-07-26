export UNKNOWN_PROJECT_ROOT=$(pwd)

alias proot="cd  $UNKNOWN_PROJECT_ROOT"
alias setup="$(echo $UNKNOWN_PROJECT_ROOT)/tools/setup/setup.sh"
alias test="$(echo $UNKNOWN_PROJECT_ROOT)/tools/test/test.sh"
alias build="$(echo $UNKNOWN_PROJECT_ROOT)/tools/build/cbuild.py"
alias build_engine="proot && build ECORE-LINUX"
alias build_test="proot && build ETEST-LINUX"
alias build_all="build_engine && build_test"
alias clean_cache="rm .cbuild_filecache-*"
alias generate_project="$(echo $UNKNOWN_PROJECT_ROOT)/tools/project/generateProject.sh"
