add_executable(parquet-rewriter parquet-rewriter.cpp)
target_link_libraries(parquet-rewriter ${ALL_LIBS})
INSTALL(TARGETS parquet-rewriter RUNTIME DESTINATION bin)
