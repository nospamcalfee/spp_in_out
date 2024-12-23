cmake_minimum_required(VERSION 3.13...3.27)
set(PICO_BOARD pico_w)
set(FAMILY rp2040)
set(CMAKE_C_STANDARD 11)

set(PICO_SDK_PATH $ENV{PICO_SDK_PATH})

message(PICO_SDK_PATH="${PICO_SDK_PATH}")
set(PROGRAM_NAME spp_in_out)

include(${PICO_SDK_PATH}/external/pico_sdk_import.cmake)

project(${PROGRAM_NAME} C CXX ASM)

pico_sdk_init()

add_executable(${PROGRAM_NAME}
  spp_in_out.c
  ringqueue.c
  ${PICO_SDK_PATH}/lib/btstack/src/classic/rfcomm.c
  ${PICO_SDK_PATH}/lib/btstack/src/classic/sdp_server.c
  ${PICO_SDK_PATH}/lib/btstack/src/classic/spp_server.c
  ${PICO_SDK_PATH}/lib/btstack/src/classic/sdp_util.c
  ${PICO_SDK_PATH}/lib/btstack/src/classic/btstack_link_key_db_tlv.c
)
target_link_libraries(${PROGRAM_NAME}
  hardware_adc
  hardware_flash
  hardware_rtc
  hardware_sync
  pico_stdlib
  pico_btstack_ble
  pico_cyw43_arch_none
  pico_cyw43_arch_threadsafe_background
  pico_btstack_cyw43
)

pico_set_linker_script(${PROGRAM_NAME} ${CMAKE_SOURCE_DIR}/memmap_custom.ld)

target_include_directories(${PROGRAM_NAME}
  PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/include
  ${PICO_SDK_PATH}/src/rp2_common/pico_cyw43_arch/include
  ${PICO_SDK_PATH}/lib/cyw43-driver/src
  ${PICO_SDK_PATH}/src/rp2_common/pico_cyw43_driver/include
  ${PICO_SDK_PATH}/lib/lwip/src/include
  ${PICO_SDK_PATH}/src/rp2_common/pico_lwip/include
  ${PICO_SDK_PATH}/src/rp2_common/pico_rand/include
  ${PICO_SDK_PATH}/src/rp2_common/pico_async_context/include
)
target_compile_options(${PROGRAM_NAME} PUBLIC -Werror -Wall -Wextra -Wnull-dereference -Wno-unused-parameter -Wno-null-dereference -ggdb3 -O0 -v)
string(APPEND CMAKE_EXE_LINKER_FLAGS "-Wl,--print-memory-usage")

pico_enable_stdio_usb(${PROGRAM_NAME} 1)
pico_add_extra_outputs(${PROGRAM_NAME})


find_program(OPENOCD openocd)
if(OPENOCD)
  add_custom_target(flash
    COMMAND ${OPENOCD} -f interface/cmsis-dap.cfg -f target/rp2040.cfg -c "adapter speed 5000" -c "program ${CMAKE_PROJECT_NAME}.elf verify reset exit"
    DEPENDS ${CMAKE_PROJECT_NAME}
  )
endif()
