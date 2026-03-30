# This is necessary so that environment variables from .env 
# are visible when Makefile commands are executed
include .env
export

# Development targets

up-db:
	@docker compose --profile DbOnly up -d

# Generate a new Alembic migration with autogenerate
create-migration: up-db
	@cd ./src/data && \
	alembic revision --autogenerate -m $(name)

# Apply all pending Alembic migrations
apply-migrations: up-db
	@cd ./src/data && \
	alembic upgrade head

# Build the project, apply migrations and start the application
run: apply-migrations
	@conan build . --build=missig && \
	./build/Debug/to-dos-api

# Run clang-tidy static analysis
run-code-analysis:
	@run-clang-tidy -p build/Debug

# TODO: Try to align with the Development targets so as not to split them
# CI/CD targets (safe to run locally too)

# Apply all pending Alembic migrations
ci-apply-migrations:
	@cd alembic/ && \
	alembic upgrade head

# Running karate tests within Docker Compose
# The option --exit-code-from ensures that the command's exit code exactly matches the exit code of the specified service.
ci-run-karate-test-within-docker-compose:
	@if docker pull ghcr.io/tourmalinecore/to-dos-api-cpp:latest 2>/dev/null; then \
		docker compose --profile MockForPullRequest up --no-build --exit-code-from to-dos-api-cpp-karate-tests; \
	else \
		docker compose --profile MockForPullRequest up --build --exit-code-from to-dos-api-cpp-karate-tests; \
	fi