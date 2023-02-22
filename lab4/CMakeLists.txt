set(LLVM_LINK_COMPONENTS support)

add_clang_executable(uninit
  Uninit.cpp
  )

target_link_libraries(uninit
  PRIVATE
  clangTooling
  clangBasic
    )
