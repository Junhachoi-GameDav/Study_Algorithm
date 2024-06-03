# Stage 1: Build Stage
FROM ubuntu:latest as build-stage

# Set environment variables to non-interactive mode to prevent prompts during installation
ENV DEBIAN_FRONTEND=noninteractive

# Install required packages and libraries
RUN apt-get update && apt-get install -y \
    g++ \
    cmake \
    wget \
    git \
    unzip \
    libboost-all-dev \
    libfmt-dev \
    libtbb-dev \
    libgdal-dev \
    gdal-bin \
    libopencv-dev \
    libpq-dev \
    libpqxx-dev \
    pkg-config \
    && rm -rf /var/lib/apt/lists/*

# Copy project files
WORKDIR /app
COPY . /app

# Create a build directory and run cmake
RUN mkdir build && cd build && cmake .. && make

# Stage 2: Runtime Stage
FROM ubuntu:latest

# Set environment variables to non-interactive mode to prevent prompts during installation
ENV DEBIAN_FRONTEND=noninteractive

# Install runtime dependencies
RUN apt-get update && apt-get install -y \
    libboost-all-dev \
    libfmt-dev \
    libtbb-dev \
    libgdal-dev \
    gdal-bin \
    libopencv-dev \
    libpq-dev \
    libpqxx-dev \
    && rm -rf /var/lib/apt/lists/*

# Copy the built binary from the build stage
WORKDIR /app
COPY --from=build-stage /app/build/dem_mng /app/dem_mng

# Set the entrypoint
CMD ["./dem_mng"]
