FROM fedora
MAINTAINER Ed Asriyan <ed-asriyan@protonmail.com>

RUN yum update -y
RUN yum install -y gcc-c++
RUN yum install -y boost-devel
RUN yum install -y cmake
RUN yum install -y make

WORKDIR /app
ADD ./core/ ./core
ADD main.cpp .
ADD RouteTranslator.hpp .
ADD CMakeLists.txt .

RUN cmake CMakeLists.txt
RUN make

CMD ./app
EXPOSE 8080
