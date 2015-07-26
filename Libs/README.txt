This folder is where the project will look for libraries, the libraries required to compile the engine are:

RapidJSON (https://github.com/miloyip/rapidjson)
SDL2 (http://libsdl.org/download-2.0.php)
SDL2_image (http://www.libsdl.org/projects/SDL_image)

The project will expect the folowing folder structures:

RapidJSON
¦--include
¦--¦--rapidjson
¦--¦--¦--error
¦--¦--¦--internal
¦--¦--¦--msinttypes
¦--¦--¦--<RapidJson headers>

SDL2
¦--include
¦--¦--<SDL2 headers>
¦--lib
¦--¦--x86
¦--¦--¦--<SDL2 libraries>

SDL2_image
¦--include
¦--¦--<SDL2_image headers>
¦--lib
¦--¦--x86
¦--¦--¦--<SDL2_image libraries>

Note: For both SDL2 and SDL2_image there will be a x64 folder in the lib/ directory, this folder is not used by the engine.
Due to this the decision to keep or remove this directory is up the user.

Note(2): The libraries are not included in any release or repository to comply with terms and/or licences.
