file(GLOB_RECURSE SOURCES main.c user/*.c)

set(include_dirs user/inc)

idf_component_register(SRCS ${SOURCES} INCLUDE_DIRS ${include_dirs})
