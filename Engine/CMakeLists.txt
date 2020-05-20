set(UK_ENGINE_INCLUDES
		src/Animation.h
		src/Audio/Sound.h
		src/Audio/WAVSound.h
		src/Editor/CoreEditor.h
		src/Editor/EditorBase.h
		src/Editor/EntityEditor.h
		src/Editor/FileSystemViewer.h
		src/Editor/LogViewer.h
		src/Editor/SceneViewer.h
		src/Editor/ViewerBase.h
		src/Engine/EngineConfig.h
		src/Entity/AnimationRenderComponent.h
		src/Entity/BasePrototype.h
		src/Entity/BasicRenderComponent.h
		src/Entity/Component.h
		src/Entity/Entity.h
		src/Entity/EntityPrototype.h
		src/Entity/ImageRenderComponent.h
		src/Entity/PhysicsBodyComponent.h
		src/Entity/TimerComponent.h
		src/Filesystem/FSUtils.h
		src/Filesystem/File.h
		src/Filesystem/Filesystem.h
		src/Filesystem/Imemstream.h
		src/Filesystem/PAKFileStream.h
		src/Font/BitmapFont.h
		src/Font/Font.h
		src/Font/FontGlyph.h
		src/Font/StaticText.h
		src/Font/TTFont.h
		src/GL/GL.h
		src/GL/glad/glad.h
		src/GL/glad/khrplatform.h
		src/Graphics/Camera3D.h
		src/Graphics/FileShader.h
		src/Graphics/FrameBuffer.h
		src/Graphics/GLBackend.h
		src/Graphics/PlaceholderTexture.h
		src/Graphics/RenderingBackend.h
		src/Graphics/RenderingPipeline3D.h
		src/Graphics/SDLBackend.h
		src/Graphics/Shader.h
		src/Graphics/SkyBox3D.h
		src/ITagable.h
		src/IUpdateable.h
		src/Image.h
		src/Input/KeyBind.h
		src/Input/Mouse.h
		src/Loader.h
        src/core/log/Log.h
		src/Model/Mesh.h
		src/Model/MeshContainer.h
		src/Model/MeshRenderer.h
		src/Model/TexturedMeshRenderer.h
		src/Particle.h
		src/Renderer/Camera.h
		src/Renderer/IRenderable.h
		src/Resource/ResourceManager.h
		src/Scene/CollisionManager.h
		src/Scene/Scene.h
		src/Scene/SceneElementPrototype.h
		src/Scene/SceneGraph.h
		src/Scene/SceneManager.h
		src/Settings/SettingsParser.h
		src/Singleton.h
		src/Timer.h
		src/Types/Colour.h
		src/Types/Dimension.h
		src/Types/Direction.h
		src/Types/Point.h
		src/Types/Rect.h
		src/Types/Vector.h
		src/UI.h
		src/UI/GLDocumentContainer.h
		src/UI/HTMLGL.h
		src/UI2D.h
		src/UK.h
		src/Unknown.h
		src/Utils.h
		src/scripting/Scripting.h
		src/scripting/SharedVariable.h
		src/core/gameloop/GameLoop.h
		src/core/gameloop/PCGameLoop.h
		src/core/gameloop/EmscriptenGameLoop.h
		src/Audio/SDLAudioEngine.h
		src/light/PointLight.h
		src/light/DirectionalLight.h
		src/light/SpotLight.h
		src/light/LightingManager2D.h
		src/core/hook/HookRegistry.h
		src/core/hook/Event.h
		src/Font/FontManager.h
		src/core/SDL/SDLImageManager.h
		src/core/window/SdlWindowManager.h
		)

set(UK_ENGINE_SRC
		src/Animation.cpp
		src/ITagable.cpp
		src/IUpdateable.cpp
		src/Image.cpp
		src/Loader.cpp
        src/core/log/Log.cpp
		src/Particle.cpp
		src/Timer.cpp
		src/UI.cpp
		src/UI2D.cpp
		src/Unknown.cpp
		src/Utils.cpp
		src/Audio/Sound.cpp
		src/Audio/WAVSound.cpp
		src/Editor/CoreEditor.cpp
		src/Editor/EditorBase.cpp
		src/Editor/EntityEditor.cpp
		src/Editor/FileSystemViewer.cpp
		src/Editor/LogViewer.cpp
		src/Editor/SceneViewer.cpp
		src/Editor/ViewerBase.cpp
		src/Engine/EngineConfig.cpp
		src/Entity/AnimationRenderComponent.cpp
		src/Entity/BasePrototype.cpp
		src/Entity/BasicRenderComponent.cpp
		src/Entity/Component.cpp
		src/Entity/Entity.cpp
		src/Entity/EntityPrototype.cpp
		src/Entity/ImageRenderComponent.cpp
		src/Entity/PhysicsBodyComponent.cpp
		src/Entity/TimerComponent.cpp
		src/Filesystem/FSUtils.cpp
		src/Filesystem/File.cpp
		src/Filesystem/Filesystem.cpp
		src/Filesystem/Imemstream.cpp
		src/Filesystem/PAKFileStream.cpp
		src/Font/BitmapFont.cpp
		src/Font/Font.cpp
		src/Font/FontGlyph.cpp
		src/Font/StaticText.cpp
		src/Font/TTFont.cpp
		src/GL/GL.cpp
		src/GL/glad/glad.c
		src/Graphics/Camera3D.cpp
		src/Graphics/FileShader.cpp
		src/Graphics/FrameBuffer.cpp
		src/Graphics/GLBackend.cpp
		src/Graphics/RenderingBackend.cpp
		src/Graphics/RenderingPipeline3D.cpp
		src/Graphics/SDLBackend.cpp
		src/Graphics/Shader.cpp
		src/Graphics/SkyBox3D.cpp
		src/Input/KeyBind.cpp
		src/Input/Mouse.cpp
		src/Model/Mesh.cpp
		src/Model/MeshContainer.cpp
		src/Model/MeshRenderer.cpp
		src/Model/TexturedMeshRenderer.cpp
		src/Renderer/Camera.cpp
		src/Resource/ResourceManager.cpp
		src/Scene/CollisionManager.cpp
		src/Scene/Scene.cpp
		src/Scene/SceneElementPrototype.cpp
		src/Scene/SceneGraph.cpp
		src/Scene/SceneManager.cpp
		src/Settings/SettingsParser.cpp
		src/Types/Colour.cpp
		src/Types/Dimension.cpp
		src/Types/Direction.cpp
		src/Types/Point.cpp
		src/Types/Rect.cpp
		src/Types/Vector.cpp
		src/UI/GlDocumentContainer.cpp
		src/UI/HTMLGL.cpp
		src/scripting/SharedVariable.cpp
		src/core/gameloop/GameLoop.cpp
		src/core/gameloop/PCGameLoop.cpp
		src/core/gameloop/EmscriptenGameLoop.cpp
		src/Audio/SDLAudioEngine.cpp
		src/light/PointLight.cpp
		src/light/DirectionalLight.cpp
		src/light/SpotLight.cpp
		src/light/LightingManager2D.cpp
		src/Font/FontManager.cpp
		src/core/SDL/SDLImageManager.cpp
		src/core/window/SdlWindowManager.cpp
)

# The location of the actual engine files and deps
set(UK_CORE "${UK_DIR}/Engine")

add_definitions(-DTRACY_ENABLE)

# Add sub projects
add_subdirectory(libs)
add_subdirectory(src/Imgui)
add_subdirectory(src/scripting/lua)
#add_subdirectory(scripting/python)

set(UK_INCLUDE "${UK_CORE}/src")

add_library(UK SHARED ${UK_ENGINE_SRC} ${UK_ENGINE_INCLUDES})
target_include_directories(UK PUBLIC ${COMBINED_INCLUDE} ${UK_INCLUDE})
target_link_libraries(UK png_static jpeg SDL2main SDL2-static SDL2_mixer EnTT spdlog box2d ImGUI LUASCRIPT TRACY tmxlite assimp glm rttr_core_lib litehtml RapidJSON PAK ${COMBINED_LIBS})
set_target_properties(UK PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/Output/UK/lib)
set_target_properties(UK PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/Output/UK/lib)
set_target_properties(UK PROPERTIES ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/Output/UK/lib)
target_compile_features(UK PUBLIC cxx_std_17)

if (CMAKE_BUILD_TYPE EQUAL "RELEASE")
	message("release mode")
	target_compile_options(UK PRIVATE -O3)
endif (CMAKE_BUILD_TYPE EQUAL "RELEASE")

if (CMAKE_BUILD_TYPE EQUAL "DEBUG")
	message("release mode")
	target_compile_options(UK PRIVATE -O1 -g)
endif (CMAKE_BUILD_TYPE EQUAL "DEBUG")

# Create header dir
INSTALL(DIRECTORY "${UK_DIR}/Unknown 1.0++/"
		DESTINATION ${CMAKE_BINARY_DIR}/Output/UK/include
		FILES_MATCHING PATTERN "*.h*")

#---Copy lib dlls---

# SDL
INSTALL(DIRECTORY "${UK_DIR}/Libs/SDL2/lib/x64/"
		DESTINATION ${CMAKE_BINARY_DIR}/Output/UK/lib
		FILES_MATCHING PATTERN "*.dll")

# SDL_ttf
INSTALL(DIRECTORY "${UK_DIR}/Libs/SDL2_ttf/lib/x64/"
		DESTINATION ${CMAKE_BINARY_DIR}/Output/UK/lib
		FILES_MATCHING PATTERN "*.dll")

# SDL_mixer
INSTALL(DIRECTORY "${UK_DIR}/Libs/SDL2_mixer/lib/x64/"
		DESTINATION ${CMAKE_BINARY_DIR}/Output/UK/lib
		FILES_MATCHING PATTERN "*.dll")

# SDL_image
INSTALL(DIRECTORY "${UK_DIR}/Libs/SDL2_image/lib/x64/"
		DESTINATION ${CMAKE_BINARY_DIR}/Output/UK/lib
		FILES_MATCHING PATTERN "*.dll")

# Run install after building
#add_custom_command(TARGET UK
#				   POST_BUILD
#				   COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR} --target install)

add_library(Unknown_Engine INTERFACE)
target_link_libraries(Unknown_Engine INTERFACE UK ${COMBINED_LIBS})
target_include_directories(Unknown_Engine INTERFACE ${UK_INCLUDE} ${COMBINED_INCLUDE})
