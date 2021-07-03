cmake_minimum_required(VERSION 3.13 FATAL_ERROR)

if(NOT TARGET score_lib_base)
  include("${SCORE_SOURCE_DIR}/cmake/ScoreExternalAddon.cmake")
endif()

project(score_addon_my_offline_process LANGUAGES CXX)

# General initialization
score_common_setup()

# Creation of the library
add_library(score_addon_my_offline_process
  MyOfflineProcess/MyOfflineProcessFactory.cpp
  MyOfflineProcess/MyOfflineProcessFactory.hpp

  score_addon_my_offline_process.hpp
  score_addon_my_offline_process.cpp
)

# Link
target_link_libraries(score_addon_my_offline_process PUBLIC score_lib_process score_plugin_media)

# Target-specific options
setup_score_plugin(score_addon_my_offline_process)
