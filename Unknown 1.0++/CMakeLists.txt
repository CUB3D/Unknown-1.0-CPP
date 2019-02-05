project(Unknown VERSION 0.0.1)

set(UK_ENGINE_INCLUDES

	Animation.h
	Audio/Sound.h
	Audio/WAVSound.h
	Editor/CoreEditor.h
	Editor/EditorBase.h
	Editor/EntityEditor.h
	Editor/FileSystemViewer.h
	Editor/LogViewer.h
	Editor/SceneViewer.h
	Editor/ViewerBase.h
	Engine/EngineConfig.h
	Entity/AnimationRenderComponent.h
	Entity/BasePrototype.h
	Entity/BasicRenderComponent.h
	Entity/Component.h
	Entity/Entity.h
	Entity/EntityPrototype.h
	Entity/ImageRenderComponent.h
	Entity/PhysicsBodyComponent.h
	Entity/TimerComponent.h
	Event/Event.h
	Event/EventManager.h
	Event/ItterativeEventHandler.h
	Filesystem/FSUtils.h
	Filesystem/File.h
	Filesystem/Filesystem.h
	Filesystem/Imemstream.h
	Filesystem/PAKFileStream.h
	Font/BitmapFont.h
	Font/Font.h
	Font/FontGlyph.h
	Font/StaticText.h
	Font/TTFont.h
	GL/GL.h
	GL/glad/glad.h
	GL/glad/khrplatform.h
	Graphics/Camera3D.h
	Graphics/FileShader.h
	Graphics/FrameBuffer.h
	Graphics/GLBackend.h
	Graphics/PlaceholderTexture.h
	Graphics/RenderingBackend.h
	Graphics/RenderingPipeline3D.h
	Graphics/SDLBackend.h
	Graphics/Shader.h
	Graphics/SkyBox3D.h
	IInitable.h
	ITagable.h
	IUpdateable.h
	Image.h
	Imgui/GUI.h
	Imgui/imconfig.h
	Imgui/imgui.h
	Imgui/imgui_impl_opengl3.h
	Imgui/imgui_impl_sdl.h
	Imgui/imgui_internal.h
	Imgui/imstb_rectpack.h
	Imgui/imstb_textedit.h
	Imgui/imstb_truetype.h
	Input/KeyBind.h
	Input/Mouse.h
	Loader.h
	Log.h
	Map.h
	Map/BasicMapGenerator.h
	Map/BinaryMapGenerator.h
	Model/Mesh.h
	Model/MeshContainer.h
	Model/MeshRenderer.h
	Model/TexturedMeshRenderer.h
	Particle.h
	Renderer/BasicTileMapRenderer.h
	Renderer/Camera.h
	Renderer/IRenderable.h
	Renderer/ImageDirectoryTileMapRenderer.h
	Resource/ResourceManager.h
	Scene/CollisionManager.h
	Scene/Scene.h
	Scene/SceneElementPrototype.h
	Scene/SceneGraph.h
	Scene/SceneManager.h
	Settings/SettingsParser.h
	Singleton.h
	Timer.h
	Types/Colour.h
	Types/Dimension.h
	Types/Direction.h
	Types/Point.h
	Types/Rect.h
	Types/Vector.h
	UI.h
	UI/GLDocumentContainer.h
	UI/HTMLGL.h
	UI2D.h
	UK.h
	Unknown.h
	Utils.h
	scripting/Scripting.h
	scripting/SharedVariable.h
	scripting/lua/LuaScript.h
	scripting/python/PythonScript.h
)

set(UK_ENGINE_SRC

	Animation.cpp
	Audio/Sound.cpp
	Audio/WAVSound.cpp
	Editor/CoreEditor.cpp
	Editor/EditorBase.cpp
	Editor/EntityEditor.cpp
	Editor/FileSystemViewer.cpp
	Editor/LogViewer.cpp
	Editor/SceneViewer.cpp
	Editor/ViewerBase.cpp
	Engine/EngineConfig.cpp
	Entity/AnimationRenderComponent.cpp
	Entity/BasePrototype.cpp
	Entity/BasicRenderComponent.cpp
	Entity/Component.cpp
	Entity/Entity.cpp
	Entity/EntityPrototype.cpp
	Entity/ImageRenderComponent.cpp
	Entity/PhysicsBodyComponent.cpp
	Entity/TimerComponent.cpp
	Event/Event.cpp
	Event/EventManager.cpp
	Event/ItterativeEventHandler.cpp
	Filesystem/FSUtils.cpp
	Filesystem/File.cpp
	Filesystem/Filesystem.cpp
	Filesystem/Imemstream.cpp
	Filesystem/PAKFileStream.cpp
	Font/BitmapFont.cpp
	Font/Font.cpp
	Font/FontGlyph.cpp
	Font/StaticText.cpp
	Font/TTFont.cpp
	GL/GL.cpp
	GL/glad/glad.c
	Graphics/Camera3D.cpp
	Graphics/FileShader.cpp
	Graphics/FrameBuffer.cpp
	Graphics/GLBackend.cpp
	Graphics/RenderingBackend.cpp
	Graphics/RenderingPipeline3D.cpp
	Graphics/SDLBackend.cpp
	Graphics/Shader.cpp
	Graphics/SkyBox3D.cpp
	IInitable.cpp
	ITagable.cpp
	IUpdateable.cpp
	Image.cpp
	Imgui/imgui.cpp
	Imgui/imgui_demo.cpp
	Imgui/imgui_draw.cpp
	Imgui/imgui_impl_opengl3.cpp
	Imgui/imgui_impl_sdl.cpp
	Imgui/imgui_widgets.cpp
	Input/KeyBind.cpp
	Input/Mouse.cpp
	Loader.cpp
	Log.cpp
	Map.cpp
	Map/BasicMapGenerator.cpp
	Map/BinaryMapGenerator.cpp
	Model/Mesh.cpp
	Model/MeshContainer.cpp
	Model/MeshRenderer.cpp
	Model/TexturedMeshRenderer.cpp
	Particle.cpp
	Renderer/BasicTileMapRenderer.cpp
	Renderer/Camera.cpp
	Renderer/ImageDirectoryTileMapRenderer.cpp
	Resource/ResourceManager.cpp
	Scene/CollisionManager.cpp
	Scene/Scene.cpp
	Scene/SceneElementPrototype.cpp
	Scene/SceneGraph.cpp
	Scene/SceneManager.cpp
	Settings/SettingsParser.cpp
	Timer.cpp
	Types/Colour.cpp
	Types/Dimension.cpp
	Types/Direction.cpp
	Types/Point.cpp
	Types/Rect.cpp
	Types/Vector.cpp
	UI.cpp
	UI/GlDocumentContainer.cpp
	UI/HTMLGL.cpp
	UI2D.cpp
	Unknown.cpp
	Utils.cpp
	scripting/SharedVariable.cpp
	scripting/lua/LuaScript.cpp
	scripting/python/PythonScript.cpp
)

# Remove seperate modules
list(FILTER UK_ENGINE_SRC EXCLUDE REGEX "python")
list(FILTER UK_ENGINE_SRC EXCLUDE REGEX "lua")

# Add sub projects
add_subdirectory(Box2D)
add_subdirectory(Imgui)
add_subdirectory(Tracy)
add_subdirectory(Map/Tiled)
add_subdirectory(scripting/lua)
#add_subdirectory(scripting/python)

set(UK_INCLUDE "${UK_DIR}/Unknown 1.0++")

add_definitions(-DTRACY_ENABLE)

add_library(UK SHARED ${UK_ENGINE_SRC} ${UK_DIR}/Libs/tracy/TracyClient.cpp ${UK_ENGINE_INCLUDES} )
target_include_directories(UK PUBLIC ${COMBINED_INCLUDE} ${UK_INCLUDE} ${UK_DIR}/Libs/tracy)
target_link_libraries(UK Box2D ImGUI LUASCRIPT ${COMBINED_LIBS})
set_target_properties(UK PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/Output/UK/lib)
set_target_properties(UK PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/Output/UK/lib)
set_target_properties(UK PROPERTIES ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/Output/UK/lib)
target_compile_features(UK PUBLIC cxx_std_17)
target_compile_options(UK PRIVATE -O3 -g -ggdb)

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
