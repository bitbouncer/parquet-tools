#!/bin/bash
set -ef

IMAGE_TAG=${1:-latest}

export BUILD_CONTAINER_NAME=bb-parquet-tools-build:${IMAGE_TAG}
export EXTRACT_CONTAINER=bb-parquet-tools-extract-${IMAGE_TAG}
export TAG_NAME=bb-parquet-tools:${IMAGE_TAG}

rm -rf ./extract
mkdir -p ./extract/bin
mkdir -p ./extract/lib
mkdir -p ./extract/lib64
echo "removing old extract container"
docker rm -f $EXTRACT_CONTAINER || true

pushd ..
  docker build --build-arg IMAGE_TAG=${IMAGE_TAG} --file docker/Dockerfile.build --tag $BUILD_CONTAINER_NAME .
popd

docker create --name $EXTRACT_CONTAINER $BUILD_CONTAINER_NAME

docker cp $EXTRACT_CONTAINER:/usr/local/lib                            ./extract
echo $PWD
find ./extract -name "*.a" -exec rm -rf {} \;

docker cp $EXTRACT_CONTAINER:/usr/local/bin/parquet-dump-schema        ./extract/bin
docker cp $EXTRACT_CONTAINER:/usr/local/bin/parquet-reader             ./extract/bin
docker cp $EXTRACT_CONTAINER:/usr/local/bin/parquet-rewriter           ./extract/bin
docker cp $EXTRACT_CONTAINER:/usr/local/bin/parquet-scan               ./extract/bin
docker cp $EXTRACT_CONTAINER:/usr/local/bin/plasma-store-server        ./extract/bin

docker cp $EXTRACT_CONTAINER:/src/runDeps                              ./extract/runDeps

docker rm -f $EXTRACT_CONTAINER

docker build -f Dockerfile --no-cache -t$TAG_NAME .

rm -rf ./extract


