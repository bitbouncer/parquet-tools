file(GLOB SRCS
 *.h
 *.cpp
)
  
ADD_LIBRARY(bb_parquet_utils STATIC ${SRCS})
INSTALL(TARGETS bb_parquet_utils
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
)

