FROM ubuntu:22.04 AS base

USER root
WORKDIR /app
EXPOSE 80

RUN apt-get update && export DEBIAN_FRONTEND=noninteractive \
    && apt-get -y install --no-install-recommends pip

FROM base AS build

ARG TARGETARCH

WORKDIR /src
COPY . .

RUN apt-get -y install --no-install-recommends \
    build-essential clang lld make cmake ninja-build gdb \
    && apt-get autoremove -y \
    && apt-get clean -y \
    && rm -rf /var/lib/apt/lists/*

RUN pip install conan

RUN conan remote add local-recipes ./deps --type=local-recipes-index

RUN conan build . --build=missing \
    --profile:host=profiles/to-dos-conan-profile-${TARGETARCH}.conf \
    --profile:build=profiles/to-dos-conan-profile-${TARGETARCH}.conf

FROM base AS final

RUN pip install alembic psycopg2-binary

WORKDIR /app

COPY --from=build /src/src/data/create_db.py ./alembic/
COPY --from=build /src/src/data/alembic.ini ./alembic/
COPY --from=build /src/src/data/migrations/ ./alembic/migrations/
COPY --from=build /src/src/data/models/ ./alembic/models/

COPY --from=build /src/build/Release/to-dos-api .

ENTRYPOINT ["./to-dos-api"]