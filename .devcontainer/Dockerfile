FROM mcr.microsoft.com/devcontainers/base:ubuntu-22.04 AS base

RUN apt-get update && export DEBIAN_FRONTEND=noninteractive \
    && apt-get -y install --no-install-recommends \
        build-essential gcc g++ make gdb cmake \
        git curl wget unzip pkg-config sudo \
    && apt-get autoremove -y \
    && apt-get clean -y \
    && rm -rf /var/lib/apt/lists/*
