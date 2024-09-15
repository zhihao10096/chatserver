# 定义一个SRC_LIST，包含该目录下所有源文件
aux_source_directory(. SRC_LIST)

# 指定生成可执行文件
add_executable(ChatServer ${SRC_LIST})


# 指定可执行文件需要链接的库文件
target_link_libraries(ChatServer muduo_net muduo_base pthread)