# This is necessary so that environment variables from .env 
# are visible when Makefile commands are executed
-include .env
export

# By default, Make treats all targets as files; unless you specify that targets 
# are commands, the instructions will be skipped if a file with the target’s name exists.
# More info: https://www.gnu.org/software/make/manual/make.html#Phony-Targets
.PHONY: create-migration apply-migrations run run-code-analysis run-e2e-tests-within-docker-compose

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