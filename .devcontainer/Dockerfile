FROM mcr.microsoft.com/devcontainers/base:ubuntu-22.04 AS base

RUN apt-get update && export DEBIAN_FRONTEND=noninteractive \
    && apt-get -y install --no-install-recommends \
        build-essential clang lld make gdb cmake ninja-build \
        git curl wget unzip sudo \
        pip \
        clang-format clang-tidy \
        libpq-dev \
    && apt-get autoremove -y \
    && apt-get clean -y \
    && rm -rf /var/lib/apt/lists/*

RUN pip install conan

ARG ODB_VERSION=2.5.0

RUN mkdir -p /opt/odb && \
    wget -q -nc -P /opt/odb \
    https://www.codesynthesis.com/download/odb/${ODB_VERSION}/ubuntu/ubuntu22.04/x86_64/libodb_${ODB_VERSION}-0~ubuntu22.04_amd64.deb \
    https://www.codesynthesis.com/download/odb/${ODB_VERSION}/ubuntu/ubuntu22.04/x86_64/libodb-dev_${ODB_VERSION}-0~ubuntu22.04_amd64.deb \
    https://www.codesynthesis.com/download/odb/${ODB_VERSION}/ubuntu/ubuntu22.04/x86_64/libodb-pgsql_${ODB_VERSION}-0~ubuntu22.04_amd64.deb \
    https://www.codesynthesis.com/download/odb/${ODB_VERSION}/ubuntu/ubuntu22.04/x86_64/libodb-pgsql-dev_${ODB_VERSION}-0~ubuntu22.04_amd64.deb \
    https://www.codesynthesis.com/download/odb/${ODB_VERSION}/ubuntu/ubuntu22.04/x86_64/odb_${ODB_VERSION}-0~ubuntu22.04_amd64.deb

RUN dpkg -i /opt/odb/*.deb && rm -rf /opt/odb

COPY to-dos-conan-profile.conf /root/.conan2/profiles/default