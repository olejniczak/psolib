project(testapp)
add_executable(testapp main.cpp optsuite.cpp gnuplot.cpp)
target_link_libraries(testapp psolib muparser)