project(sem3-playground)

add_executable(kruskal mst_kruskal.cpp)

add_executable(dijkstra dijkstra.cpp dijkstra.h)
target_link_libraries(dijkstra PRIVATE ${CONAN_LIBS})

file(COPY
        ${DSPG_DATA_DIR}/metro.json
        DESTINATION ${CMAKE_BINARY_DIR}/bin)
