#### get rid of stuff you should not have
```
sudo apt-get --purge remove libprotobuf-dev libgrpc++-dev protobuf-compiler 
```

#### parquet-tools
```
sudo apt-get update
sudo apt-get install -y sudo build-essential cmake wget pax-utils automake autogen shtool libtool unzip pkg-config sed bison flex git gcc-10 g++-10
sudo update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-10 100 --slave /usr/bin/g++ g++ /usr/bin/g++-10 --slave /usr/bin/gcov gcov /usr/bin/gcov-10
```
#### avro deps
```
sudo apt-get install -y libboost-all-dev libsnappy-dev
```
#### aws deps
```
sudo apt-get install -y libbz2-dev libssl-dev libcurl4-openssl-dev libgoogle-glog-dev
```
#### deps for arrow
```
sudo apt-get install -y liblz4-dev libutf8proc-dev libre2-dev llvm-7 clang libz-dev liblzma-dev libzstd-dev libbz2-dev
```
