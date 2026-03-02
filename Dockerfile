FROM ubuntu:22.04 AS base

WORKDIR /app
EXPOSE 8080

FROM base AS build

ARG TARGETARCH

WORKDIR /src
COPY . .

RUN apt-get update && export DEBIAN_FRONTEND=noninteractive \
    && apt-get -y install --no-install-recommends \
    build-essential clang lld make cmake ninja-build gdb pip \
    && apt-get autoremove -y \
    && apt-get clean -y \
    && rm -rf /var/lib/apt/lists/*

RUN pip install conan

RUN conan export deps/recipes/libodb/all --version=2.5.0 \
    && conan export deps/recipes/libodb-pgsql/all --version=2.5.0

RUN conan build . --build=missing \
    --profile:host=profiles/to-dos-conan-profile-${TARGETARCH}.conf \
    --profile:build=profiles/to-dos-conan-profile-${TARGETARCH}.conf

FROM base AS final

WORKDIR /app
COPY --from=build /src/build/Release/to-dos-api .

RUN export $(grep -v '^#' .env | xargs)

ENTRYPOINT ["./to-dos-api"]