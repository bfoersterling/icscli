FROM gcc:latest

# Install Python3 and pip
RUN apt-get update && apt-get install -y python3 python3-pip

# Install Meson and Ninja
RUN pip3 install meson ninja --break-system-packages


# to build
# docker build -t meson-image .

# to run
# docker run --rm -it meson-image
