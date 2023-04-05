FROM mcr.microsoft.com/devcontainers/cpp:0-debian-11

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