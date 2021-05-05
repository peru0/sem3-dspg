project(week9)

add_executable(dspg-kruskal mst_kruskal.cpp)

add_executable(dspg-dijkstra dijkstra.cpp dijkstra.h)
target_link_libraries(dspg-dijkstra ${CONAN_LIBS})
