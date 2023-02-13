set(LLVM_LINK_COMPONENTS support)

add_clang_executable(traverse
  Traverse.cpp
  )

target_link_libraries(traverse
  PRIVATE
  clangTooling
  clangBasic
    )
