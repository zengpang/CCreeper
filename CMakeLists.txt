cmake_minimum_required(VERSION 3.12)
project(CCreeper VERSION 0.1.0)

# 设置 vcpkg 工具链（必须放在最前面！）
set(CMAKE_TOOLCHAIN_FILE "E:/vcpkg/scripts/buildsystems/vcpkg.cmake")

# 明确指定使用静态 triplet
set(VCPKG_TARGET_TRIPLET "x64-windows-static")

# Windows 专用静态链接设置
set(BUILD_SHARED_LIBS OFF)

# 对于 MSVC 编译器，设置静态运行时库
if(MSVC)
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
endif()

# 查找 curl 静态库
find_package(CURL REQUIRED)

# 显示找到的库信息（调试用）
message(STATUS "CURL library: ${CURL_LIBRARIES}")
message(STATUS "CURL include dir: ${CURL_INCLUDE_DIRS}")

# 添加可执行文件
add_executable(CCreeper main.cpp)

# 链接 curl 并添加必要的 Windows 系统库
target_link_libraries(CCreeper PRIVATE 
    CURL::libcurl
    ws2_32.lib    # Windows Sockets
    crypt32.lib   # Crypto API
    wldap32.lib   # LDAP
    normaliz.lib  # Normalization
    advapi32.lib  # Advanced API
)

# 必须添加的静态编译定义
target_compile_definitions(CCreeper PRIVATE 
    CURL_STATICLIB
    _WIN32_WINNT=0x0600  # Windows Vista 或更高版本
)

# 对于 MSVC，强制静态运行时
if(MSVC)
    target_compile_options(CCreeper PRIVATE 
        /MT$<$<CONFIG:Debug>:d>
    )
endif()