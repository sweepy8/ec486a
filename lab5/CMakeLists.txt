set(LLVM_LINK_COMPONENTS support)

add_clang_executable(fixer
  Fixer.cpp
  )

target_link_libraries(fixer
  PRIVATE
  clangTooling
  clangBasic
    )
