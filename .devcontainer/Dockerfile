# See here for image contents: https://github.com/microsoft/vscode-dev-containers/tree/v0.154.0/containers/cpp/.devcontainer/base.Dockerfile

# [Choice] Debian / Ubuntu version: debian-10, debian-9, ubuntu-20.04, ubuntu-18.04
ARG VARIANT="buster"
FROM mcr.microsoft.com/vscode/devcontainers/cpp:0-${VARIANT}

# Install needed packages. Use a separate RUN statement to add your own dependencies.
# RUN apt-get update && export DEBIAN_FRONTEND=noninteractive \
#     && apt-get -y install build-essential cmake cppcheck valgrind clang lldb llvm gdb \
#     && apt-get autoremove -y && apt-get clean -y && rm -rf /var/lib/apt/lists/*

RUN apt-get update && export DEBIAN_FRONTEND=noninteractive \
    && apt-get -y install --no-install-recommends libgtest-dev google-mock git ninja-build python3-pip \
    && apt-get autoremove -y && apt-get clean -y && rm -rf /var/lib/apt/lists/* \
    && pip3 install meson \
    && pip3 install gcovr

# DEBIAN_FRONTEND=noninteractive
# This is the anti-frontend. It never interacts with you  at  all,
# and  makes  the  default  answers  be used for all questions. It
# might mail error messages to root, but that's it;  otherwise  it
# is  completely  silent  and  unobtrusive, a perfect frontend for
# automatic installs. If you are using this front-end, and require
# non-default  answers  to questions, you will need to preseed the
# debconf database; see the section below  on  Unattended  Package
# Installation for more details.

# --no-install-recommends
# This option disables installation of recommended dependencies of the installed packages. 
# This helps reduce the size of the dokcer image
# see https://ubuntu.com/blog/we-reduced-our-docker-images-by-60-with-no-install-recommends