# apps/ 以下のすべての .cpp ファイルを取得
file(GLOB CASE_SOURCES "*.cpp")

foreach(CASE_SOURCE ${CASE_SOURCES})
    # ファイル名から拡張子を除いた名前を取得 (例: case01_pipe_cooldown)
    get_filename_component(EXEC_NAME ${CASE_SOURCE} NAME_WE)

    # 各ケースの実行ファイルを定義
    add_executable(${EXEC_NAME} ${CASE_SOURCE})

    # コアライブラリをリンク
    target_link_libraries(${EXEC_NAME} PRIVATE cfd_core)

    message(STATUS "Configured analysis case executable: ${EXEC_NAME}")
endforeach()