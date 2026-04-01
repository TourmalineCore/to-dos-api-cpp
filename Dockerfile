FROM ubuntu:22.04 AS base

# use root to be able to use privilidged port 80
# https://github.com/dotnet/aspnetcore/discussions/53015
USER root
WORKDIR /app
EXPOSE 80

# pip is installed here because it needs to be available in both the build and final stages
RUN apt-get update && export DEBIAN_FRONTEND=noninteractive \
    && apt-get -y install --no-install-recommends pip make

FROM base AS build

WORKDIR /src

RUN apt-get -y install --no-install-recommends \
    build-essential clang lld cmake ninja-build gdb \
    && apt-get autoremove -y \
    && apt-get clean -y \
    && rm -rf /var/lib/apt/lists/*

RUN pip install conan

# this is necessary so that Conan can install the dependencies
COPY conanfile.py /src/
COPY .devcontainer/to-dos-conan-profile.conf /src/.devcontainer/
COPY deps/ /src/deps/

# this is necessary so that Conan can see the local dependency recipes
RUN conan remote add local-recipes ./deps --type=local-recipes-index

RUN conan install . --build=missing \
    --profile:all=.devcontainer/to-dos-conan-profile.conf \
    # this is necessary because, by default, the `build_type` property in the profile is set to `Debug`
    --settings:host="build_type=Release"

# We cannot copy all the content before running `conan install`, because 
# otherwise the image layers cannot be cached in the pipeline
COPY . .

RUN conan build . --build=missing \
    --profile:all=.devcontainer/to-dos-conan-profile.conf \
    # this is necessary because, by default, the `build_type` property in the profile is set to `Debug`
    --settings:host="build_type=Release"

FROM base AS final

# alembic, psycopg2-binary and sqlalchemy-utils are used for performing migrations
RUN pip install alembic psycopg2-binary sqlalchemy-utils

WORKDIR /app

# alembic needs this to apply the migrations correctly
COPY --from=build /src/src/data/alembic.ini ./alembic/
COPY --from=build /src/src/data/migrations/ ./alembic/migrations/
COPY --from=build /src/src/data/models/ ./alembic/models/

COPY --from=build /src/Makefile .

COPY --from=build /src/build/Release/to-dos-api .

ENTRYPOINT ["./to-dos-api"]