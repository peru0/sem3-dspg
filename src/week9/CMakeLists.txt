project(week9)

add_executable(dspg-kruskal mst_kruskal.cpp)

add_executable(dspg-prim prim.cpp prim.h)
target_link_libraries(dspg-prim ${CONAN_LIBS})

add_executable(dspg-dijkstra dijkstra.cpp dijkstra.h)
target_link_libraries(dspg-dijkstra ${CONAN_LIBS})
