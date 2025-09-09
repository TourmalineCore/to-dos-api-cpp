FROM mcr.microsoft.com/devcontainers/base:ubuntu-22.04 AS base

RUN apt-get update && export DEBIAN_FRONTEND=noninteractive \
    && apt-get -y install --no-install-recommends \
        build-essential clang lld make gdb cmake ninja-build \
        git curl wget unzip pkg-config sudo \
        pip \
        clang-format clang-tidy \
    && apt-get autoremove -y \
    && apt-get clean -y \
    && rm -rf /var/lib/apt/lists/*

RUN pip install conan

COPY to-dos-conan-profile.conf /root/.conan2/profiles/default