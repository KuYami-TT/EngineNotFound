cmake_minimum_required(VERSION 3.26)
project(EngineNotFound)

if(EMSCRIPTEN)
  message("Using Emscripten!")
endif()

if(EMSCRIPTEN)
  set(TARGET_NAME EngineNotFound_web)
  set(TARGET_PARAM )
else()
  set(TARGET_NAME EngineNotFound)
  set(TARGET_PARAM WIN32)
endif()

# list source files here
add_executable(${TARGET_NAME} ${TARGET_PARAM}
  EngineNotFound/Main.cpp
  EngineNotFound/EngineNotFound.cpp
  EngineNotFound/Renderer.cpp
  EngineNotFound/GameObject.cpp
  EngineNotFound/Scene.cpp
  EngineNotFound/Font.cpp
  EngineNotFound/Texture2D.cpp
  EngineNotFound/GUI.cpp
  EngineNotFound/Controller.cpp
  EngineNotFound/Action.cpp
  EngineNotFound/XInputImp.cpp

  EngineNotFound/Managers/GameTime.cpp
  EngineNotFound/Managers/SceneManager.cpp
  EngineNotFound/Managers/ResourceManager.cpp
  EngineNotFound/Managers/InputManager.cpp

  EngineNotFound/Components/Component.cpp
  EngineNotFound/Components/RenderComp.cpp
  EngineNotFound/Components/SpriteRenderComp.cpp
  EngineNotFound/Components/TextRenderComp.cpp
  EngineNotFound/Components/FPSComp.cpp
  EngineNotFound/Components/OrbitComp.cpp
  EngineNotFound/Components/MoveComp.cpp
  EngineNotFound/Components/PlayerHud.cpp
  EngineNotFound/Components/LivesComp.cpp
  EngineNotFound/Components/ScoreComp.cpp
 
  EngineNotFound/Widgets/WidgetWindow.cpp
  EngineNotFound/Widgets/Widget.cpp
  EngineNotFound/Widgets/TrashTheCache.cpp

  EngineNotFound/Commands/MoveCommand.cpp
  EngineNotFound/Commands/ActionCommand.cpp

  EngineNotFound/Observers/Subject.cpp
)

add_library(imgui OBJECT
  External/imgui-docking/imgui.cpp
  External/imgui-docking/imgui_draw.cpp
  External/imgui-docking/imgui_widgets.cpp
  External/imgui-docking/imgui_tables.cpp
  External/imgui-docking/backends/imgui_impl_sdl2.cpp
  External/imgui-docking/backends/imgui_impl_sdlrenderer2.cpp

  External/implot/implot.cpp
  External/implot/implot_items.cpp
)

target_include_directories(imgui PRIVATE External/imgui-docking External/implot)

target_link_libraries(${TARGET_NAME} PRIVATE imgui)

# enable c++20 features
target_compile_features(${TARGET_NAME} PUBLIC cxx_std_20)
# set minigin as the default startup project
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${TARGET_NAME})

Set(FETCHCONTENT_QUIET FALSE)

include(FetchContent)
# add glm
FetchContent_Declare(
  glm
  URL https://github.com/g-truc/glm/releases/download/0.9.9.8/glm-0.9.9.8.zip
  DOWNLOAD_NO_PROGRESS OFF
  DOWNLOAD_DIR ${CMAKE_BINARY_DIR}/downloads
)

FetchContent_GetProperties(glm)
if(NOT glm_POPULATED)
  FetchContent_Populate(glm)
endif()

FetchContent_Declare(fmt
  GIT_REPOSITORY https://github.com/fmtlib/fmt.git
  GIT_TAG 10.2.1
  GIT_PROGRESS TRUE
)
FetchContent_MakeAvailable(fmt)

target_link_libraries(${TARGET_NAME} PRIVATE fmt::fmt)

# add SDL2
if (WIN32)
  FetchContent_Declare(
    SDL2
    URL https://www.libsdl.org/release/SDL2-devel-2.28.5-VC.zip 
    DOWNLOAD_NO_PROGRESS OFF
    DOWNLOAD_DIR ${CMAKE_BINARY_DIR}/downloads 
  )
  FetchContent_GetProperties(SDL2)
  if(NOT SDL2_POPULATED)
    FetchContent_Populate(SDL2)
    set(SDL2_INCLUDE_DIR ${sdl2_SOURCE_DIR}/include)
  if (${CMAKE_SIZEOF_VOID_P} MATCHES 8)
    set(SDL2_LIBRARIES "${sdl2_SOURCE_DIR}/lib/x64/SDL2.lib;${sdl2_SOURCE_DIR}/lib/x64/SDL2main.lib")
    set(SDL2_LIBRARY_DLL "${sdl2_SOURCE_DIR}/lib/x64/SDL2.dll")
  else()
    set(SDL2_LIBRARIES "${sdl2_SOURCE_DIR}/lib/x86/SDL2.lib;${sdl2_SOURCE_DIR}/lib/x86/SDL2main.lib")
    set(SDL2_LIBRARY_DLL "${sdl2_SOURCE_DIR}/lib/x86/SDL2.dll")
  endif()
  endif()

  # add SDL2_image
  FetchContent_Declare(
    SDL2_image
    URL https://www.libsdl.org/projects/SDL_image/release/SDL2_image-devel-2.8.2-VC.zip 
    DOWNLOAD_NO_PROGRESS OFF
    DOWNLOAD_DIR ${CMAKE_BINARY_DIR}/downloads
  )
  FetchContent_GetProperties(SDL2_image)
  if(NOT SDL2_image_POPULATED)
    FetchContent_Populate(SDL2_image)
    set(SDL2_IMAGE_INCLUDE_DIR ${sdl2_image_SOURCE_DIR}/include)
  if (${CMAKE_SIZEOF_VOID_P} MATCHES 8)
    set(SDL2_IMAGE_LIBRARIES "${sdl2_image_SOURCE_DIR}/lib/x64/SDL2_image.lib")
    set(SDL2_IMAGE_LIBRARY_DLL "${sdl2_image_SOURCE_DIR}/lib/x64/SDL2_image.dll")
  else()
    set(SDL2_IMAGE_LIBRARIES "${sdl2_image_SOURCE_DIR}/lib/x86/SDL2_image.lib")
    set(SDL2_IMAGE_LIBRARY_DLL "${sdl2_image_SOURCE_DIR}/lib/x86/SDL2_image.dll")
  endif()
  endif()

  # add SDL2_ttf
  FetchContent_Declare(
    SDL2_ttf
    URL https://www.libsdl.org/projects/SDL_ttf/release/SDL2_ttf-devel-2.20.2-VC.zip
    DOWNLOAD_NO_PROGRESS OFF
    DOWNLOAD_DIR ${CMAKE_BINARY_DIR}/downloads
  )
  FetchContent_GetProperties(SDL2_ttf)
  if(NOT sdl2_ttf_POPULATED)
    FetchContent_Populate(SDL2_ttf)
    set(SDL2_TTF_INCLUDE_DIR ${sdl2_ttf_SOURCE_DIR}/include)
  if (${CMAKE_SIZEOF_VOID_P} MATCHES 8)
    set(SDL2_TTF_LIBRARIES ${sdl2_ttf_SOURCE_DIR}/lib/x64/SDL2_ttf.lib)
    set(SDL2_TTF_LIBRARY_DLL "${sdl2_ttf_SOURCE_DIR}/lib/x64/SDL2_ttf.dll")
  else()
    set(SDL2_TTF_LIBRARIES ${sdl2_ttf_SOURCE_DIR}/lib/x86/SDL2_ttf.lib)
    set(SDL2_TTF_LIBRARY_DLL "${sdl2_ttf_SOURCE_DIR}/lib/x86/SDL2_ttf.dll")
  endif()
  endif()

  set(VLD_DIR "$ENV{ProgramFiles\(x86\)}/Visual Leak Detector")
  IF(EXISTS ${VLD_DIR})
    set(VLD_INCLUDE_DIR "${VLD_DIR}/include")
    if (${CMAKE_SIZEOF_VOID_P} MATCHES 8)
        set(VLD_LIBRARY "${VLD_DIR}/lib/Win64/vld.lib")
    else()
        set(VLD_LIBRARY "${VLD_DIR}/lib/Win32/vld.lib")
    endif()
  endif()

SET( XINPUT_LIB XInput )
target_link_libraries(${TARGET_NAME} PUBLIC
    ${XINPUT_LIB} 
)

  # set all include directories
  target_include_directories(${TARGET_NAME} PRIVATE
    ${VLD_INCLUDE_DIR}
    ${SDL2_INCLUDE_DIR} 
    ${SDL2_IMAGE_INCLUDE_DIR} 
    ${SDL2_TTF_INCLUDE_DIR}
   )

  # imgui also needs sdl2
  target_include_directories(imgui PRIVATE
    ${SDL2_INCLUDE_DIR} 
    ${SDL2_IMAGE_INCLUDE_DIR} 
    ${SDL2_TTF_INCLUDE_DIR}
  )
  
  # set libraries to link with
  target_link_libraries(${TARGET_NAME} PUBLIC
    ${SDL2_LIBRARIES} 
    ${SDL2_IMAGE_LIBRARIES} 
    ${SDL2_TTF_LIBRARIES} 
    ${VLD_LIBRARY}
  )

elseif(NOT EMSCRIPTEN)

  FetchContent_Declare(
    SDL2
    GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
    GIT_TAG release-2.28.5
    GIT_SHALLOW TRUE
    GIT_PROGRESS TRUE
  )
  FetchContent_MakeAvailable(SDL2)
  
  FetchContent_Declare(
    SDL2_image
    GIT_REPOSITORY https://github.com/libsdl-org/SDL_image.git
    GIT_TAG release-2.8.2
    GIT_SHALLOW TRUE
    GIT_PROGRESS TRUE
  )
  set(SDL2IMAGE_INSTALL OFF)
  FetchContent_MakeAvailable(SDL2_image)

  FetchContent_Declare(
    SDL2_ttf
    GIT_REPOSITORY https://github.com/libsdl-org/SDL_ttf.git
    GIT_TAG release-2.20.2
    GIT_SHALLOW TRUE
    GIT_PROGRESS TRUE
  )
  set(SDL2TTF_INSTALL OFF)
  FetchContent_MakeAvailable(SDL2_ttf)

  target_include_directories("${TARGET_NAME}" PUBLIC 
    ${sdl2_SOURCE_DIR}/include
    ${sdl2_image_SOURCE_DIR}/include
    ${sdl2_ttf_SOURCE_DIR}
  )
  target_link_libraries("${TARGET_NAME}" PUBLIC 
    SDL2::SDL2main SDL2::SDL2 SDL2_image::SDL2_image SDL2_ttf::SDL2_ttf
  )
endif()

target_include_directories(${TARGET_NAME} PRIVATE
  ${CMAKE_SOURCE_DIR}/EngineNotFound/
  ${glm_SOURCE_DIR}
  External/imgui-docking
  External/implot
)

# compile at max warning level + treat warnings as errors
target_compile_options(${TARGET_NAME} PRIVATE
  $<$<CXX_COMPILER_ID:MSVC>:/W4 /WX>
  $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall -Wextra -Wpedantic -Werror>
)

if(EMSCRIPTEN)
  set(EMSCRIPTEN_COMPILE_FLAGS "${EMSCRIPTEN_LINK_FLAGS} -sUSE_SDL=2 -sUSE_SDL_IMAGE=2 -sUSE_SDL_TTF=2 -g")
  set(EMSCRIPTEN_LINK_FLAGS "${EMSCRIPTEN_LINK_FLAGS} -sUSE_SDL=2 -sUSE_SDL_IMAGE=2 -sUSE_SDL_TTF=2 -g -sALLOW_MEMORY_GROWTH --preload-file \"${CMAKE_SOURCE_DIR}/Data@/\" -sSDL2_IMAGE_FORMATS=['tga','png']")

  # work around https://github.com/emscripten-core/emscripten/issues/11513
  set(EMSCRIPTEN_LINK_FLAGS "${EMSCRIPTEN_LINK_FLAGS} -fno-stack-protector")

  # Use the Emscripten toolchain
  set(CMAKE_TOOLCHAIN_FILE ${CMAKE_CURRENT_SOURCE_DIR}/EmscriptenToolchain.cmake)

  # Additional settings for Emscripten build
  set_target_properties(${TARGET_NAME} PROPERTIES
      COMPILE_FLAGS "${EMSCRIPTEN_COMPILE_FLAGS}"
      LINK_FLAGS "${EMSCRIPTEN_LINK_FLAGS}"
  )

  # Have emscripten generate a html page too.
  set(CMAKE_EXECUTABLE_SUFFIX ".html")
  
elseif(WIN32)

  # add post build commands
  add_custom_command(TARGET ${TARGET_NAME} POST_BUILD
      COMMAND "${CMAKE_COMMAND}" -E copy "${SDL2_LIBRARY_DLL}" "$<TARGET_FILE_DIR:${TARGET_NAME}>"
  )
  add_custom_command(TARGET ${TARGET_NAME} POST_BUILD
      COMMAND "${CMAKE_COMMAND}" -E copy "${SDL2_IMAGE_LIBRARY_DLL}" "$<TARGET_FILE_DIR:${TARGET_NAME}>"
  )
  add_custom_command(TARGET ${TARGET_NAME} POST_BUILD
      COMMAND "${CMAKE_COMMAND}" -E copy "${SDL2_TTF_LIBRARY_DLL}" "$<TARGET_FILE_DIR:${TARGET_NAME}>"
  )
  add_custom_command(TARGET ${TARGET_NAME} POST_BUILD
    COMMAND "${CMAKE_COMMAND}" -E copy_directory "${CMAKE_CURRENT_SOURCE_DIR}/Data" "$<TARGET_FILE_DIR:${TARGET_NAME}>/Data"
  )
endif()
