ARG VARIANT=ubuntu-22.04
FROM mcr.microsoft.com/vscode/devcontainers/base:${VARIANT}

# update dependencies
RUN apt update
RUN apt upgrade -y

# install xfce desktop
RUN apt install -y xfce4 xfce4-goodies


# Install riscv32-esp-elf-gdb and add to path
RUN cd /usr/local && curl -L https://github.com/espressif/binutils-gdb/releases/download/esp-gdb-v14.2_20240403/riscv32-esp-elf-gdb-14.2_20240403-x86_64-linux-gnu.tar.gz | tar xzf - --strip-components=1

# Install Espressif SVD files
RUN git clone --depth=1 https://github.com/espressif/svd /opt/esp-svd
