# This is necessary so that environment variables from .env 
# are visible when Makefile commands are executed
include .env
export

# Generate a new Alembic migration with autogenerate
create-migration:
	@cd ./alembic && \
	alembic revision --autogenerate -m $(name)

# Apply all pending Alembic migrations
apply-migrations:
	@cd ./alembic && \
	alembic upgrade head

# Build the project, apply migrations and start the application
run: apply-migrations
	@conan build . --build=missig && \
	./build/Debug/to-dos-api

# Run clang-tidy static analysis
run-tidy:
	@run-clang-tidy -p build/Debug
