set( LLVM_LINK_COMPONENTS
  ${LLVM_TARGETS_TO_BUILD}
  Option
  Support
  )

add_clang_executable(loops
  Loops.cpp
  )

clang_target_link_libraries(loops
  PRIVATE
  clangAST
  clangBasic
  clangDriver
  clangFrontend
  clangRewriteFrontend
  clangSerialization
  clangStaticAnalyzerFrontend
  clangTooling
  )

install(TARGETS loops
  RUNTIME DESTINATION bin)
