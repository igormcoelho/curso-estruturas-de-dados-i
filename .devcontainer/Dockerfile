#FROM mcr.microsoft.com/devcontainers/cpp:0-debian-11
FROM mcr.microsoft.com/devcontainers/cpp:0-ubuntu-22.04

ARG REINSTALL_CMAKE_VERSION_FROM_SOURCE="none"

# Optionally install the cmake for vcpkg
COPY ./reinstall-cmake.sh /tmp/

RUN if [ "${REINSTALL_CMAKE_VERSION_FROM_SOURCE}" != "none" ]; then \
    chmod +x /tmp/reinstall-cmake.sh && /tmp/reinstall-cmake.sh ${REINSTALL_CMAKE_VERSION_FROM_SOURCE}; \
    fi \
    && rm -f /tmp/reinstall-cmake.sh

# [Optional] Uncomment this section to install additional vcpkg ports.
# RUN su vscode -c "${VCPKG_ROOT}/vcpkg install <your-port-name-here>"

# [Optional] Uncomment this section to install additional packages.
# RUN apt-get update && export DEBIAN_FRONTEND=noninteractive \
#     && apt-get -y install --no-install-recommends <your-package-list-here>

RUN apt-get update && export DEBIAN_FRONTEND=noninteractive \
    && apt-get -y install \
    texlive texlive-base texlive-latex-extra texlive-latex-recommended \
    texlive-bibtex-extra biber \
    texlive-xetex texlive-fonts-extra \
    texlive-science \
    texlive-lang-portuguese

# install rust
RUN curl --proto '=https' --tlsv1.2 https://sh.rustup.rs -sSf | bash -s -- -y

# pandoc 2.19.2
RUN wget https://github.com/jgm/pandoc/releases/download/2.19.2/pandoc-2.19.2-1-amd64.deb
RUN sudo dpkg -i pandoc-2.19.2-1-amd64.deb

# pandoc-crossref 0.3.13
RUN wget https://github.com/lierdakil/pandoc-crossref/releases/download/v0.3.13.0b/pandoc-crossref-Linux.tar.xz
RUN mv pandoc-crossref-Linux.tar.xz /usr/local/bin/
RUN (cd /usr/local/bin/ && tar xf pandoc-crossref-Linux.tar.xz)

# install pandoc-katex
RUN bash -c 'source ~/.cargo/env; cargo install pandoc-katex'

# install pip (for cpplint and cmake)
RUN apt-get update && export DEBIAN_FRONTEND=noninteractive \
     && apt-get -y install --no-install-recommends python3-pip

# RUN apt-get update && export DEBIAN_FRONTEND=noninteractive \
#     && apt-get -y install --no-install-recommends cmake 
RUN pip install --upgrade cmake

# command 'add-apt-repository'
RUN apt-get update && export DEBIAN_FRONTEND=noninteractive \
     && apt-get -y install --no-install-recommends software-properties-common

# gcc-12
RUN apt-get update && export DEBIAN_FRONTEND=noninteractive \
     && apt-get -y install --no-install-recommends g++-12 gcc-12

# clangd, clang-format and clang-tidy (standard)
#RUN apt-get update && export DEBIAN_FRONTEND=noninteractive \
#     && apt-get -y install --no-install-recommends clang-tidy clang-format clangd

# clang-16
RUN wget -O - https://apt.llvm.org/llvm-snapshot.gpg.key | sudo apt-key add -
RUN echo "deb http://apt.llvm.org/jammy/ llvm-toolchain-jammy-16 main" >> /etc/apt/sources.list
RUN echo "deb-src http://apt.llvm.org/jammy/ llvm-toolchain-jammy-16 main" >> /etc/apt/sources.list

# clangd, clang-format and clang-tidy
RUN apt-get update && export DEBIAN_FRONTEND=noninteractive \
     && apt-get -y install --no-install-recommends clang-tidy-16 clang-format-16 clangd-16

RUN apt-get update && export DEBIAN_FRONTEND=noninteractive \
     && apt-get -y install --no-install-recommends  lldb-16  lld-16 libc++-16-dev libc++abi-16-dev

# =========== https://apt.llvm.org/ (Extras) ============
# LLVM
RUN apt-get update && export DEBIAN_FRONTEND=noninteractive \
     && apt-get -y install --no-install-recommends  libllvm-16-ocaml-dev libllvm16 llvm-16 llvm-16-dev llvm-16-doc llvm-16-examples llvm-16-runtime

# clang
RUN apt-get update && export DEBIAN_FRONTEND=noninteractive \
     && apt-get -y install --no-install-recommends clang-16 clang-tools-16 clang-16-doc libclang-common-16-dev libclang-16-dev libclang1-16 clang-format-16 python3-clang-16 clangd-16 clang-tidy-16

# ===========

# nodejs (for bazel)
RUN curl -sL https://deb.nodesource.com/setup_18.x | sudo -E bash -
RUN apt-get update && export DEBIAN_FRONTEND=noninteractive \
     && apt-get -y install --no-install-recommends nodejs 

# bazel
RUN npm install -g @bazel/bazelisk

# install cpplint into /usr/local/bin/cpplint
RUN pip install cpplint 

# bumpver (for versioning)
RUN python3 -m pip install bumpver

# default gcc-12
RUN sudo update-alternatives --install /usr/bin/g++ g++ /usr/bin/g++-12 10
RUN sudo update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-12 10
# default clang-16
RUN sudo update-alternatives --install /usr/bin/clang clang /usr/bin/clang-16 10
RUN sudo update-alternatives --install /usr/bin/clang-format clang-format /usr/bin/clang-format-16 10
RUN sudo update-alternatives --install /usr/bin/clangd clangd /usr/bin/clangd-16 10
RUN sudo update-alternatives --install /usr/bin/clang-tidy clang-tidy /usr/bin/clang-tidy-16 10
