# 스테이지 1 : 빌드용
FROM ubuntu:latest as builder
RUN apt-get update && apt-get install -y build-essential libboost-all-dev

WORKDIR /app
COPY Test_0.cpp .
COPY Test_0.h .
RUN g++ -o mytest_0 Test_0.cpp

#스테이지 2 : 실행환경
FROM ubuntu:latest
WORKDIR /app

COPY --from=builder /app/mytest_0 .
CMD ["./mytest_0"]