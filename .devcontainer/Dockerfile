FROM mcr.microsoft.com/devcontainers/base:ubuntu-22.04

RUN apt-get update && apt-get -y install --no-install-recommends \
    build-essential clang lld gdb make cmake ninja-build \
    crossbuild-essential-arm64 \
    git curl wget unzip sudo \
    pip \
    clang-format clang-tidy \
    && apt-get autoremove -y \
    && apt-get clean -y \
    && rm -rf /var/lib/apt/lists/*

RUN pip install conan alembic psycopg2-binary sqlalchemy-utils

# If this profile is not copied, the profile must be specified via an argument 
# when calling `conan`. 
COPY ./to-dos-conan-profile.conf /root/.conan2/profiles/default