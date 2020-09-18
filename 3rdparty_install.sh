set -ef 

export CPP_STANDARD="17"

export AVRO_VER="release-1.9.2"
export AWS_SDK_VER="1.7.220"
export GRPC_VER="v1.32.0"
export NLOHMANN_JSON_VER="3.7.1"

#deps for arrow
export DOUBLE_CONVERSION_VER="v3.1.5"
export BROTLI_VER="v1.0.7"
export FLATBUFFERS_VER="v1.11.0"
export THRIFT_VER="0.12.0"

export ARROW_VER="apache-arrow-1.0.1"


export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/usr/local/lib

rm -rf tmp
mkdir tmp
cd tmp


wget -O boost.tar.gz "https://dl.bintray.com/boostorg/release/1.70.0/source/boost_1_70_0.tar.gz" && \
mkdir -p boost && \
tar \
  --extract \
  --file boost.tar.gz \
  --directory boost \
  --strip-components 1
cd boost
./bootstrap.sh
./b2 cxxstd=17 --with-program_options --with-iostreams --with-filesystem --with-regex --with-system --with-date_time  -j "$(getconf _NPROCESSORS_ONLN)" stage
sudo ./b2 cxxstd=17 --with-program_options --with-iostreams --with-filesystem --with-regex --with-system --with-date_time install
cd ..
rm boost.tar.gz
rm -rf boost

wget -O avro.tar.gz "https://github.com/apache/avro/archive/$AVRO_VER.tar.gz"
mkdir -p avro
tar \
  --extract \
  --file avro.tar.gz \
  --directory avro \
  --strip-components 1
sed -i.bak1 's/-std=c++11/-std=c++17/g' avro/lang/c++/CMakeLists.txt
sed -i.bak2 '/regex system)/a SET(Boost_LIBRARIES boost_program_options boost_iostreams boost_filesystem boost_regex boost_system z bz2)' avro/lang/c++/CMakeLists.txt
#sed -i.bak3 '/find_package (Boost/d' avro/lang/c++/CMakeLists.txt
#sed -i.bak4 '/regex system)/d' avro/lang/c++/CMakeLists.txt
cat avro/lang/c++/CMakeLists.txt
cd avro/lang/c++/ 
mkdir build 
cd build
cmake -DCMAKE_BUILD_TYPE=Release .. -DBUILD_SHARED_LIBS=ON -DCMAKE_CXX_STANDARD=$CPP_STANDARD
make -j "$(getconf _NPROCESSORS_ONLN)"
sudo make install
cd ../../../..
rm avro.tar.gz
rm -rf arvo

git clone --recursiv --depth 1 --branch $GRPC_VER https://github.com/grpc/grpc.git
cd grpc
mkdir build && cd build
cmake ..
make -j "$(getconf _NPROCESSORS_ONLN)" && \
sudo make install && \
cd ../..

git clone https://github.com/awslabs/aws-c-common
cd aws-c-common
mkdir build && cd build
cmake .. 
make -j "$(getconf _NPROCESSORS_ONLN)" 
sudo make install 
cd ../..

git clone https://github.com/awslabs/aws-checksums
cd aws-checksums
mkdir build && cd build
cmake -DCMAKE_PREFIX_PATH=/usr/local -DCMAKE_INSTALL_PREFIX=/usr/local ..
make -j "$(getconf _NPROCESSORS_ONLN)" 
sudo make install
cd ../..

git clone https://github.com/awslabs/aws-c-event-stream
cd aws-c-event-stream
mkdir build && cd build
cmake -DCMAKE_PREFIX_PATH=/usr/local -DCMAKE_INSTALL_PREFIX=/usr/local ..
make -j "$(getconf _NPROCESSORS_ONLN)" 
sudo make install
cd ../..

wget -O aws-sdk.tar.gz "https://github.com/aws/aws-sdk-cpp/archive/$AWS_SDK_VER.tar.gz" && \
mkdir -p aws-sdk && \
tar \
  --extract \
  --file aws-sdk.tar.gz \
  --directory aws-sdk \
  --strip-components 1
cd aws-sdk
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Release -DBUILD_SHARED_LIBS=ON -DBUILD_ONLY="config;s3;transfer" -DENABLE_TESTING=OFF -DCPP_STANDARD=$CPP_STANDARD ..
#cmake -DCMAKE_BUILD_TYPE=Release -DBUILD_SHARED_LIBS=ON -DENABLE_TESTING=OFF -DCPP_STANDARD=$CPP_STANDARD ..
make -j "$(getconf _NPROCESSORS_ONLN)"
sudo make install
cd ../..

wget -O double-conversion.tar.gz "https://github.com/google/double-conversion/archive/$DOUBLE_CONVERSION_VER.tar.gz" && \
mkdir -p double-conversion && \
tar \
  --extract \
  --file double-conversion.tar.gz \
  --directory double-conversion \
  --strip-components 1
cd double-conversion
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Release -DBUILD_SHARED_LIBS=ON -DCMAKE_CXX_STANDARD=$CPP_STANDARD ..
make -j "$(getconf _NPROCESSORS_ONLN)"
sudo make install
cd ../..
rm double-conversion.tar.gz

wget -O brotli.tar.gz "https://github.com/google/brotli/archive/$BROTLI_VER.tar.gz" && \
mkdir -p brotli && \
tar \
  --extract \
  --file brotli.tar.gz \
  --directory brotli \
  --strip-components 1
cd brotli
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Release -DBUILD_SHARED_LIBS=ON -DCMAKE_CXX_STANDARD=$CPP_STANDARD ..
make -j "$(getconf _NPROCESSORS_ONLN)"
sudo make install
cd ../..
rm brotli.tar.gz


wget -O flatbuffers.tar.gz "https://github.com/google/flatbuffers/archive/$FLATBUFFERS_VER.tar.gz" && \
mkdir -p flatbuffers && \
tar \
  --extract \
  --file flatbuffers.tar.gz \
  --directory flatbuffers \
  --strip-components 1
cd flatbuffers
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Release -DBUILD_SHARED_LIBS=ON -DFLATBUFFERS_BUILD_TESTS=OFF -DCMAKE_CXX_STANDARD=$CPP_STANDARD ..
make -j "$(getconf _NPROCESSORS_ONLN)"
sudo make install
cd ../..
rm flatbuffers.tar.gz

wget -O thrift.tar.gz "https://github.com/apache/thrift/archive/$THRIFT_VER.tar.gz" && \
mkdir -p thrift && \
tar \
  --extract \
  --file thrift.tar.gz \
  --directory thrift \
  --strip-components 1 && \
cd thrift && \
mkdir -p build && cd build && \
cmake -DCMAKE_BUILD_TYPE=Release -DBUILD_SHARED_LIBS=ON -DCMAKE_CXX_STANDARD=$CPP_STANDARD .. && \
make -j "$(getconf _NPROCESSORS_ONLN)" && \
sudo make install && \
cd ../.. && \
rm thrift.tar.gz

wget -O nlomann.tar.gz "https://github.com/nlohmann/json/archive/v$NLOHMANN_JSON_VER.tar.gz" && \
mkdir -p nlomann && \
tar \
  --extract \
  --file nlomann.tar.gz \
  --directory nlomann \
  --strip-components 1 && \
cd nlomann && \
mkdir build && cd build
cmake ..
make -j "$(getconf _NPROCESSORS_ONLN)" && \
sudo make install && \
cd ../.. && \
rm nlomann.tar.gz && \
rm -rf nlomann


wget -O arrow.tar.gz "https://github.com/apache/arrow/archive/$ARROW_VER.tar.gz" && \
mkdir -p arrow && \
tar \
  --extract \
  --file arrow.tar.gz \
  --directory arrow \
  --strip-components 1
cd arrow/cpp
mkdir build
cd build
cmake \
  -DCMAKE_BUILD_TYPE=Release \
  -DARROW_DEPENDENCY_SOURCE=SYSTEM \
  -DCMAKE_CXX_STANDARD=$CPP_STANDARD \
  -DARROW_BUILD_UTILITIES=ON \
  -DARROW_CUDA=OFF \
  -DARROW_GANDIVA=ON \
  -DARROW_WITH_BZ2=ON \
  -DARROW_WITH_ZLIB=ON \
  -DARROW_WITH_ZSTD=ON \
  -DARROW_WITH_LZ4=ON \
  -DARROW_WITH_SNAPPY=ON \
  -DARROW_WITH_BROTLI=ON \
  -DARROW_COMPUTE=ON \
  -DARROW_JEMALLOC=ON \
  -DARROW_CSV=ON \
  -DARROW_DATASET=ON \
  -DARROW_FILESYSTEM=ON \
  -DARROW_JSON=ON \
  -DARROW_PARQUET=ON \
  -DARROW_PLASMA=ON \
  -DARROW_PYTHON=OFF \
  -DARROW_S3=ON \
  -DARROW_USE_GLOG=ON \
  -DPARQUET_BUILD_EXECUTABLES=ON \
  -DPARQUET_BUILD_EXAMPLES=ON \
   ..

make -j "$(getconf _NPROCESSORS_ONLN)"
sudo make install
cd ../..
rm arrow.tar.gz

#out of tmp
cd ..
rm -rf tmp



