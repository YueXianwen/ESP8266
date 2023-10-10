# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "D:/36348/ESP8266/ESP8266_RTOS_SDK/components/bootloader/subproject"
  "D:/36348/CLionProjects/ESP8266/GPIO/build/bootloader"
  "D:/36348/CLionProjects/ESP8266/GPIO/build/bootloader-prefix"
  "D:/36348/CLionProjects/ESP8266/GPIO/build/bootloader-prefix/tmp"
  "D:/36348/CLionProjects/ESP8266/GPIO/build/bootloader-prefix/src/bootloader-stamp"
  "D:/36348/CLionProjects/ESP8266/GPIO/build/bootloader-prefix/src"
  "D:/36348/CLionProjects/ESP8266/GPIO/build/bootloader-prefix/src/bootloader-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "D:/36348/CLionProjects/ESP8266/GPIO/build/bootloader-prefix/src/bootloader-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "D:/36348/CLionProjects/ESP8266/GPIO/build/bootloader-prefix/src/bootloader-stamp${cfgdir}") # cfgdir has leading slash
endif()
