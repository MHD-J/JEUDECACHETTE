cmake_minimum_required(VERSION 3.10)
project(HideAndSeekGame)

# تحديد معيار C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# البحث عن مكتبة SFML
find_package(SFML 2.5 COMPONENTS graphics window system audio REQUIRED)

# تجميع ملفات الكود
file(GLOB_RECURSE SOURCES "src/*.cpp")
file(GLOB_RECURSE HEADERS "include/*.h")

# إنشاء ملف التشغيل
add_executable(HideAndSeek ${SOURCES} ${HEADERS})

# ربط المكتبات بالطريقة الصحيحة لـ CMake
target_link_libraries(HideAndSeek sfml-graphics sfml-window sfml-system sfml-audio)

# تحديد مكان ملفات الهيدر
target_include_directories(HideAndSeek PUBLIC include)