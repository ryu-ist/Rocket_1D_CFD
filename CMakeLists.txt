cmake_minimum_required(VERSION 3.16)
project(Rocket1DCFD VERSION 0.1.0 LANGUAGES CXX)

# C++17標準を強制
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# コンパイラ警告オプションの設定（クリーンなコード維持のため推奨）
if(MSVC)
    add_compile_options(/W4)
else()
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# --------------------------------------------------------------------
# 1. コアライブラリ (cfd_core) の定義
# --------------------------------------------------------------------
# src/ 以下の実装ファイルをまとめる
file(GLOB_RECURSE CORE_SOURCES "src/*.cpp")

add_library(cfd_core STATIC ${CORE_SOURCES})

# インクルードディレクトリの指定 (PUBLICにすることでリンク側からも参照可能に)
target_include_directories(cfd_core PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

# --------------------------------------------------------------------
# 2. 解析ケース (apps) フォルダの読み込み
# --------------------------------------------------------------------
add_subdirectory(apps)