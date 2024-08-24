FROM ubuntu:latest
RUN apt-get update && apt-get install build-essential wget -y
ARG DEBIAN_FRONTEND=noninteractive
RUN apt-get update && apt-get install gdb -y
RUN apt-get update && apt-get install unixodbc-dev -y
RUN apt-get update && apt-get install libssl-dev -y
RUN apt-get update && apt-get install libfmt-dev -y
RUN apt-get update && apt-get install uuid-dev -y
RUN apt-get update && apt-get install ninja-build -y
RUN apt-get update && apt-get install gcc-14 g++-14 -y
RUN update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-14 14 --slave /usr/bin/g++ g++ /usr/bin/g++-14
WORKDIR /init
RUN wget https://github.com/Kitware/CMake/releases/download/v3.30.2/cmake-3.30.2-Linux-x86_64.sh
RUN sh cmake-3.30.2-Linux-x86_64.sh --skip-license
RUN ln -s /init/bin/cmake /usr/local/bin/cmake
RUN ln -s /init/bin/cpack /usr/local/bin/cpack