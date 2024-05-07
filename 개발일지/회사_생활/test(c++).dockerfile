FROM ubuntu:latest as builder
RUN apt-get update && apt-get install -y build-essential
WORKDIR /app
COPY FileName.cpp .
RUN g++ -o HelloWorld FileName.cpp

FROM ubuntu:latest
WORKDIR /app

COPY --from=builder /app/HelloWorld .
CMD ["./HelloWorld"]