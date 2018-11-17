cmake_minimum_required(VERSION 3.10)
project(TP2)

set(CMAKE_CXX_STANDARD 14)

add_executable(testGrayLeveleImage2D testGrayLevelImage2D.cpp include/Image2D.h)
add_executable(testColorImage2D testColorImage2D.cpp include/Image2D.h include/Color.h)
add_executable(testColorImage2DGenere testColorImage2DGenere.cpp include/Image2D.h include/Color.h include/Image2DWriter.h include/Image2DReader.h)
add_executable(invert_red_blue invert_red_blue.cpp include/Image2DWriter.h include/Image2D.h include/Image2DReader.h include/Color.h include/Accessor.h)
add_executable(save-green-channel save-green-channel.cpp include/Image2DWriter.h include/Image2D.h include/Image2DReader.h include/Color.h include/Accessor.h)
add_executable(save-channels save-channels.cpp include/Image2DWriter.h include/Image2D.h include/Image2DReader.h include/Color.h include/Accessor.h)
add_executable(testVieuxEcran testVieuxEcran.cpp include/Image2DWriter.h include/Image2D.h include/Image2DReader.h include/Color.h include/Accessor.h)
add_executable(testBuildHistogramme testBuildHistogramme.cpp include/Image2DWriter.h include/Image2D.h include/Image2DReader.h include/Color.h include/Accessor.h include/Histogramme.h)