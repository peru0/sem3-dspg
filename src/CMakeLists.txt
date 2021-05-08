project(sem3-playground)

add_executable(kruskal mst_kruskal.cpp)

add_executable(binary_heap_test binary_heap_test.cpp)
target_link_libraries(binary_heap_test PRIVATE ${CONAN_LIBS})

add_executable(dijkstra dijkstra.cpp)
target_link_libraries(dijkstra PRIVATE ${CONAN_LIBS})

file(COPY
        ${DSPG_DATA_DIR}/metro.json
        DESTINATION ${CMAKE_BINARY_DIR}/bin)
