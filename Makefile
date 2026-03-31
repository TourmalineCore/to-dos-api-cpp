# This is necessary so that environment variables from .env 
# are visible when Makefile commands are executed
-include .env
export

# Generate a new Alembic migration with autogenerate
create-migration:
	@cd ./src/data && \
	alembic revision --autogenerate -m $(name)

# Apply all pending Alembic migrations
apply-migrations:
	@cd ./src/data && \
	alembic upgrade head

# Build the project, apply migrations and start the application
run: apply-migrations
	@conan build . --build=missig && \
	./build/Debug/to-dos-api

# Run clang-tidy static analysis
run-code-analysis:
	@run-clang-tidy -p build/Debug