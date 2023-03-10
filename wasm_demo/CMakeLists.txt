set(WINDOW_TITLE "Muli Engine Demo")
set(WINDOW_WIDTH 1280)
set(WINDOW_HEIGHT 720)

set(DEMO_HEADER_FILES
    include/mesh.h
    include/shader.h
    include/dynamic_shader.h
    include/renderer.h

    include/window.h
    include/camera.h
    include/common.h
    include/demo.h
    include/game.h
    include/input.h
    include/util.h
    include/options.h
)

set(DEMO_SOURCE_FILES
    src/main.cpp
    src/window.cpp
    src/game.cpp
    src/util.cpp

    src/rendering/mesh.cpp
    src/rendering/shader.cpp
    src/rendering/dynamic_shader.cpp
    src/rendering/renderer.cpp

    src/demo/demo.cpp
    src/demo/single_box.cpp
    src/demo/box_stacking.cpp
    src/demo/pyramid.cpp
    src/demo/single_pendulum.cpp
    src/demo/springs.cpp
    src/demo/random_convex_polygons.cpp
    src/demo/seesaw.cpp
    src/demo/friction_test.cpp
    src/demo/restitution_test.cpp
    src/demo/multi_pendulum.cpp
    src/demo/suspension_bridge.cpp
    src/demo/circle_stacking.cpp
    src/demo/circles_1000.cpp
    src/demo/boxes_1000.cpp
    src/demo/capsules_1000.cpp
    src/demo/convex_polygons_1000.cpp
    src/demo/mix_1000.cpp
    src/demo/dense_collision.cpp
    src/demo/kinematic_body.cpp
    src/demo/collision_detection.cpp
    src/demo/dynamic_aabb_tree.cpp
    src/demo/convex_hull.cpp
    src/demo/compute_distance_point.cpp
    src/demo/cloth.cpp
    src/demo/collision_filtering.cpp
    src/demo/fixed_rotation.cpp
    src/demo/weld_joint_test.cpp
    src/demo/prismatic_joint_test.cpp
    src/demo/conveyor_belt.cpp
    src/demo/pulley.cpp
    src/demo/windmill.cpp
    src/demo/crank.cpp
    src/demo/terrain.cpp
    src/demo/rounded_polygon.cpp
    src/demo/ray_casting.cpp
    src/demo/line_of_sight.cpp
    src/demo/ragdoll.cpp
    src/demo/ragdoll_100.cpp
    src/demo/car.cpp
    src/demo/compound_shape.cpp
    src/demo/contact_callbacks.cpp
    src/demo/logo.cpp
    src/demo/breakable.cpp
    src/demo/compute_distance_shape.cpp
    src/demo/capsule_stacking.cpp
    src/demo/continuous_test.cpp
    src/demo/continuous_test2.cpp
    src/demo/sub_stepping.cpp
    src/demo/shape_cast_test.cpp
    src/demo/correct_awake.cpp
)

source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}/src" PREFIX "src" FILES ${DEMO_SOURCE_FILES})
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}/include" PREFIX "include" FILES ${DEMO_HEADER_FILES})

add_executable(index ${DEMO_SOURCE_FILES} ${DEMO_HEADER_FILES})

target_compile_definitions(index PUBLIC
    WINDOW_TITLE="${WINDOW_TITLE}"
    WINDOW_WIDTH=${WINDOW_WIDTH}
    WINDOW_HEIGHT=${WINDOW_HEIGHT}
)

target_include_directories(index PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(index PUBLIC muli glfw imgui)

if(EMSCRIPTEN)
    set(CMAKE_EXECUTABLE_SUFFIX .html)

    target_link_options(index PRIVATE
        -sWASM=1
        -sALLOW_MEMORY_GROWTH=1
        -sASSERTIONS=1
        -sSTACK_SIZE=50MB
        -sINITIAL_MEMORY=100MB
        -sMAXIMUM_MEMORY=1000MB
        -sUSE_GLFW=3
        -sUSE_WEBGL2=1
        -sMAX_WEBGL_VERSION=2
        -sMIN_WEBGL_VERSION=2
        -O3
        -std=c++17
    )
endif()

add_custom_command(
    TARGET index POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/index.html ${CMAKE_CURRENT_SOURCE_DIR}/../index.html
    COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/index.js ${CMAKE_CURRENT_SOURCE_DIR}/../index.js
    COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/index.wasm ${CMAKE_CURRENT_SOURCE_DIR}/../index.wasm
)