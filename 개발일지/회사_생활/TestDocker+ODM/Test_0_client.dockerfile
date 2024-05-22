# 스테이지 1 : 빌드용
FROM ubuntu:latest as builder
RUN apt-get update && apt-get install -y build-essential libboost-all-dev 

WORKDIR /app
COPY Test_0_client.cpp .

RUN g++ -std=c++20 -o mytest_0_cl Test_0_client.cpp -lboost_system

#스테이지 2 : 실행환경
FROM ubuntu:latest
WORKDIR /app

COPY --from=builder /app/mytest_0_cl .
CMD ["./mytest_0_cl"]