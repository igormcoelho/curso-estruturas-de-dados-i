FROM mcr.microsoft.com/devcontainers/cpp:ubuntu-24.04

# REFRESH!
RUN apt-get update && apt-get upgrade -y && apt-get autoremove -y

# install pip (for cpplint and cmake)
RUN apt-get update && export DEBIAN_FRONTEND=noninteractive \
     && apt-get -y install --no-install-recommends python3-pip

# RUN python3 -m pip install --upgrade cmake --break-system-packages

# install cmake 4 
RUN wget https://github.com/Kitware/CMake/releases/download/v4.0.0-rc4/cmake-4.0.0-rc4-linux-x86_64.tar.gz
RUN tar -zxvf cmake-4.0.0-rc4-linux-x86_64.tar.gz
RUN mv    cmake-4.0.0-rc4-linux-x86_64     /opt/cmake
RUN cp    /opt/cmake/bin/cmake             /usr/local/bin/
RUN cp -r /opt/cmake/share/cmake-4.0/      /usr/local/share/
RUN cmake --version

# command 'add-apt-repository'
RUN apt-get update && export DEBIAN_FRONTEND=noninteractive \
     && apt-get -y install --no-install-recommends software-properties-common

# ===========

# install nvm (for npm)
RUN curl -o- https://raw.githubusercontent.com/nvm-sh/nvm/v0.40.2/install.sh | bash
RUN bash /root/.nvm/install.sh

# install npm (using nvm)
RUN bash -i -c "nvm install --lts"

# bazel (using npm)
RUN bash -i -c "npm install -g @bazel/bazelisk"

# install cpplint into /usr/local/bin/cpplint
RUN python3 -m pip install cpplint --break-system-packages

# bumpver (for versioning)
RUN python3 -m pip install bumpver --break-system-packages


# ========== begin PANDOC part ===========

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
# RUN wget https://github.com/jgm/pandoc/releases/download/2.19.2/pandoc-2.19.2-1-amd64.deb
# RUN sudo dpkg -i pandoc-2.19.2-1-amd64.deb

# pandoc 3.6.4
RUN wget https://github.com/jgm/pandoc/releases/download/3.6.4/pandoc-3.6.4-1-amd64.deb
RUN sudo dpkg -i pandoc-3.6.4-1-amd64.deb


# pandoc-crossref 0.3.13 (pandoc 2.19.2)
# RUN wget https://github.com/lierdakil/pandoc-crossref/releases/download/v0.3.13.0b/pandoc-crossref-Linux.tar.xz
# RUN mv pandoc-crossref-Linux.tar.xz /usr/local/bin/
# RUN (cd /usr/local/bin/ && tar xf pandoc-crossref-Linux.tar.xz)

# pandoc-crossref 0.3.18.2 (pandoc 3.6.4)
RUN wget https://github.com/lierdakil/pandoc-crossref/releases/download/v0.3.18.2/pandoc-crossref-Linux-X64.tar.xz
RUN mv pandoc-crossref-Linux-X64.tar.xz /usr/local/bin/
RUN (cd /usr/local/bin/ && tar xf pandoc-crossref-Linux-X64.tar.xz)


# install pandoc-katex
RUN bash -c 'source ~/.cargo/env; cargo install pandoc-katex'

# install pandoc-latex-fontsize
RUN python3 -m pip install pandoc-latex-fontsize --break-system-packages

# ================= COMPILER PART ====================

# clang newer FROM LLVM WEBSITE
RUN curl --proto '=https' --tlsv1.2 https://apt.llvm.org/llvm.sh -sSf | bash -s -- -y

# clangd, clang-format and clang-tidy
RUN apt-get update && export DEBIAN_FRONTEND=noninteractive \
     && apt-get -y install --no-install-recommends clang-tidy-19 clang-format-19 clangd-19

# libc++ for clang (not using libstdc++ from gcc)
RUN apt-get update && export DEBIAN_FRONTEND=noninteractive \
     && apt-get -y install --no-install-recommends libc++-19-dev libc++abi-19-dev

# install gcc 15 (latest) - From Ubuntu 25.04 PLUCKY

# ubuntu toolchain test does not contain gcc 15 yet
# RUN sudo add-apt-repository ppa:ubuntu-toolchain-r/test -y
RUN sudo add-apt-repository "deb http://cz.archive.ubuntu.com/ubuntu plucky main universe"
RUN apt-get update && export DEBIAN_FRONTEND=noninteractive \
     && apt-get -y install --no-install-recommends g++-15 gcc-15

# FORCE UPGRADE (NEVER ON PLUCKY!)
# RUN apt-get update && export DEBIAN_FRONTEND=noninteractive \
#     && apt-get -y upgrade

# default gcc-15
RUN sudo update-alternatives --install /usr/bin/g++ g++ /usr/bin/g++-15 10
RUN sudo update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-15 10
# default clang-19
RUN sudo update-alternatives --install /usr/bin/clang clang /usr/bin/clang-19 10
RUN sudo update-alternatives --install /usr/bin/clang++ clang++ /usr/bin/clang++-19 10
RUN sudo update-alternatives --install /usr/bin/clang-format clang-format /usr/bin/clang-format-19 10
RUN sudo update-alternatives --install /usr/bin/clangd clangd /usr/bin/clangd-19 10
RUN sudo update-alternatives --install /usr/bin/clang-tidy clang-tidy /usr/bin/clang-tidy-19 10

