set(BUILD_SHARED_LIBS OFF CACHE BOOL "Build the library as a shared library" FORCE)
set(SUPPORT_WEBP ON CACHE BOOL "Support loading WEBP images" FORCE)
set(SUPPORT_JPG ON CACHE BOOL "Support loading WEBP images" FORCE)
set(SUPPORT_PNG OFF CACHE BOOL "Support loading WEBP images" FORCE)


add_subdirectory(SDL_image)