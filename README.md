#### get rid of stuff you should not have
```
sudo apt-get --purge remove libboost-dev libboost-all-dev libprotobuf-dev libgrpc++-dev protobuf-compiler 
```

#### parquet-tools
```
sudo apt-get update
sudo apt-get install -y sudo build-essential cmake wget pax-utils automake autogen shtool libtool unzip pkg-config sed bison flex git
```
#### boost deps
```
sudo apt-get install -y libz-dev liblzma-dev libzstd-dev
```
#### avro deps
```
sudo apt-get install -y libsnappy-dev
```
#### aws deps
```
sudo apt-get install -y libbz2-dev libssl-dev libcurl4-openssl-dev libgoogle-glog-dev
```
#### deps for arrow
```
sudo apt-get install -y liblz4-dev libutf8proc-dev libre2-dev llvm-7 clang
```
