# 스테이지 1 : 빌드용
FROM ubuntu:latest as builder
RUN apt-get update && apt-get install -y build-essential libboost-all-dev libtbb-dev

WORKDIR /app
COPY Test_0_server.cpp .

RUN g++ -std=c++20 -o mytest_0_sv Test_0_server.cpp -lboost_system -ltbb
#-ltbb

#스테이지 2 : 실행환경
FROM ubuntu:latest
WORKDIR /app

COPY --from=builder /app/mytest_0_sv .
CMD ["./mytest_0_sv"]