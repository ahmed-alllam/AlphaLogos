# Use an image with a recent version of C++ and CMake
FROM ubuntu:20.04

# Set environment variables to avoid prompts
ENV DEBIAN_FRONTEND=noninteractive

# Install necessary packages and libraries
RUN apt-get update && apt-get install -y \
    g++ \
    cmake \
    libboost-all-dev \
    libasio-dev \
    git \
    libpthread-stubs0-dev \
    texlive-latex-extra \
    inkscape && \
    rm -rf /var/lib/apt/lists/*

RUN git clone https://github.com/CrowCpp/Crow.git /tmp/crow && \
    cd /tmp/crow && \
    mkdir build && cd build && \
    cmake .. -DCROW_BUILD_EXAMPLES=OFF -DCROW_BUILD_TESTS=OFF && make && make install && \
    rm -rf /tmp/crow

RUN git clone https://github.com/hughperkins/Jinja2CppLight.git /tmp/Jinja2CppLight && \
    cd /tmp/Jinja2CppLight && \
    mkdir build && cd build && \
    cmake .. && make && make install && \
    rm -rf /tmp/Jinja2CppLight

# Create a directory for the project
WORKDIR /AlphaLogos

# Copy the project files into the container
COPY . /AlphaLogos

# Build the project
RUN if [ -d "build" ]; then rm -Rf build; fi && \
    mkdir build && \
    cd build && \
    cmake .. && \
    make

EXPOSE 8000

WORKDIR build

# Set the default command (for example, to run the executable)
CMD ["./AlphaLogos"]

