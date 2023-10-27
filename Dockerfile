# Use an image with a recent version of C++ and CMake
FROM ubuntu:20.04

# Set environment variables to avoid prompts
ENV DEBIAN_FRONTEND=noninteractive

# Install necessary packages for TeX Live and other installations
RUN apt-get update && apt-get install -y \
    wget \
    perl \
    g++ \
    cmake \
    libboost-all-dev \
    libasio-dev \
    git \
    libpthread-stubs0-dev \
    texlive-latex-extra \
    inkscape npm  \
    wget unzip yosys && \
    rm -rf /var/lib/apt/lists/*


WORKDIR /latexPackages

RUN wget -q https://mirrors.ctan.org/graphics/pgf/contrib/karnaugh-map.zip && \
    unzip karnaugh-map.zip && \
    rm karnaugh-map.zip

RUN wget -q https://mirrors.ctan.org/macros/generic/xstring.zip && \
    unzip xstring.zip && \
    rm xstring.zip

RUN mktexlsr




WORKDIR /yosys2digitaljs
RUN git clone https://github.com/tilk/yosys2digitaljs.git . && \
    npm install && npm run-script build

RUN git clone https://github.com/CrowCpp/Crow.git /tmp/crow && \
    cd /tmp/crow && \
    mkdir build && cd build && \
    cmake .. -DCROW_BUILD_EXAMPLES=OFF -DCROW_BUILD_TESTS=OFF && make && make install && \
    rm -rf /tmp/crow


# Create a directory for the project
WORKDIR /AlphaLogos

# Copy the project files into the container
COPY . /AlphaLogos

# Build the project
RUN if [ -d "build" ]; then rm -Rf build; fi && \
    mkdir build && \
    cd build && \
    cmake .. -DBUILD_ONLY_RELEASE=ON  && \
    make

EXPOSE 8000

WORKDIR build

RUN cp -R /yosys2digitaljs .

RUN cp /latexPackages/karnaugh-map/* /latexPackages/xstring/* .

RUN pdflatex karnaugh-map.ins

# Set the default command (for example, to run the executable)
CMD ["./AlphaLogos"]

