FROM mcr.microsoft.com/windows/servercore:ltsc2019 AS builder

WORKDIR /build
COPY . /build

FROM mcr.microsoft.com/windows/nanoserver:ltsc2019

WORKDIR /app
COPY --from=builder /build/Project1.exe /app/

CMD ["Project1.exe"]