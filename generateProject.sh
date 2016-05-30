#!/bin/bash

mkdir -p "$1"
mkdir -p "$1/src"
mkdir -p "$1/Libs/Unknown/headers"

#Temporary - till I have better internet (not fast enough to clone submodule)
cp -R  "tools/libs/third_party/rapidJSON" "$1/Libs/RapidJSON"

cp "Output/lib/linux/libUK.so" "$1"

cp "tools/project/cbuild-PROJECT-TEMPLATE.cb" "$1"

cp "tools/build/cbuild.py" "$1"

cp UK_SRC/headers/* "$1/Libs/Unknown/headers"

printf '{ \n    "Width":512,\n    "Height":512,\n    "Title":"Test"\n}\n' > "$1"/Config.json

printf '#include "Unknown.h"\n\nint main(int argc, char** argv)\n{\n    UK_CREATE_WINDOW();\n    UK_INIT_GAME();\n    return 0;\n}\n' > "$1"/src/Game.cpp

printf '#!/bin/bash\nexport LD_LIBRARY_PATH="."\n./a.out\n' > "$1/test.sh"
chmod +x "$1/test.sh"
