# TODO: Try merging it with the production Dockerfile by creating a separate stage 
# that will be used by the devcontainer.
FROM mcr.microsoft.com/devcontainers/base:ubuntu-22.04 AS base

# This is necessary to ensure that the installation proceeds in the non-interactive mode. 
# If this option is not specified, apt may request confirmation during the installation.
ENV DEBIAN_FRONTEND=noninteractive

RUN sudo apt-get update && sudo apt-get -y install --no-install-recommends \
    build-essential clang lld gdb cmake ninja-build \
    crossbuild-essential-arm64 \
    git curl wget unzip \
    pip \
    clang-format clang-tidy \
    && apt-get autoremove -y \
    && apt-get clean -y \
    && rm -rf /var/lib/apt/lists/*

RUN pip install conan alembic psycopg2-binary sqlalchemy-utils

# If the local recipes are not specified in Conan, Conan will not be able 
# to find them when installing and building dependencies.
RUN conan remote add local-recipes ./deps --type=local-recipes-index

# If this profile is not copied, the profile must be specified via an argument 
# when calling `conan`. 
COPY to-dos-conan-profile.conf /root/.conan2/profiles/default

# This stage is used to build the devcontainer image in CI/CD.
# Installing and building dependencies slows down the first build 
# of a devcontainer, and they aren't always necessary. 
FROM base as conan-deps

RUN conan build . --build=missing