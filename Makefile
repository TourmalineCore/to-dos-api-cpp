# This is necessary so that environment variables from .env 
# are visible when Makefile commands are executed
include .env
export

# Install Conan dependencies and build missing packages
install:
	@conan install . --build=missing

# Build project binaries via Conan
build: install
	@conan build .

# Start postgresql container in the background
up-db:
	@docker compose up -d postgresql

# Stop postgresql container without removing it
stop-db:
	@docker compose stop postgresql

# Stop postgresql container and remove its volumes
down-db:
	@docker compose down -v postgresql

# This is necessary so that if the `name` parameter is not provided, 
# it will contain the date and time when the migration was created
name ?= $(shell date +%Y_%m_%d_%H_%M_%S)

# Generate a new Alembic migration with autogenerate
create-migration: up-db
	@cd ./src/data && \
	alembic revision --autogenerate -m $(name)

# Apply all pending Alembic migrations
apply-migrations: up-db
	@cd ./src/data && \
	alembic upgrade head

# Build the project, apply migrations and start the application
run: build apply-migrations
	@./build/Debug/to-dos-api

# Build the project and start the test application
run-test: build
	@./build/Debug/test/to-dos-api_unit_tests

# Run clang-tidy static analysis
run-tidy:
	@run-clang-tidy -p build/Debug

# Run clang-format analysis
run-format:
	@find ./src -name "*.cpp" -o -name "*.h" | xargs clang-format


