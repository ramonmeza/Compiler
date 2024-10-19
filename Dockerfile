FROM ubuntu

RUN DEBIAN_FRONTEND=noninteractive \
    apt-get update && \
    apt-get install -y \
    g++

WORKDIR /app

COPY *.cpp .
COPY *.hpp .

RUN echo $(g++ --version)

RUN g++ *.cpp *.hpp -o compiler.o

CMD ["./compiler.o"]