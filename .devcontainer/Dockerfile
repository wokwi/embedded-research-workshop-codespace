ARG VARIANT=ubuntu-22.04
FROM mcr.microsoft.com/vscode/devcontainers/base:${VARIANT}

# Install riscv32-esp-elf-gdb and add to path
RUN cd ~ && curl -L https://github.com/espressif/binutils-gdb/releases/download/esp-gdb-v14.2_20240403/riscv32-esp-elf-gdb-14.2_20240403-x86_64-linux-gnu.tar.gz | tar xzf -
RUN mkdir -p ~/.local/bin && ln -s ~/riscv32-esp-elf-gdb/bin/riscv32-esp-elf-gdb ~/.local/bin
