# Applied technologies

## Table Of Content

- [C++](#c)
- [Package manager](#package-manager)
  * [Overview](#overview)
  * [Selection Criteria](#selection-criteria)
    + [Key factors for decision-making:](#key-factors-for-decision-making)
  * [Comparative Table of Popular Solutions](#comparative-table-of-popular-solutions)
  * [Rationale for Selection](#rationale-for-selection)
    + [Why Conan – Chosen solution](#why-conan–chosen-solution)
    + [Why not vcpkg?](#why-not-vcpkg)
  * [Practical Considerations](#practical-considerations)
- [Compiler](#compiler)
  * [Overview](#overview-1)
  * [Selection Criteria](#selection-criteria-1)
    + [Key factors for decision-making:](#key-factors-for-decision-making-1)
  * [Comparative Table of Popular Solutions](#comparative-table-of-popular-solutions-1)
  * [Rationale for Selection](#rationale-for-selection-1)
    + [Why Clang – Chosen solution](#why-clang-chosen-solution)
    + [Why not GCC?](#why-not-gcc)
  * [Practical Considerations](#practical-considerations-1)
- [Build system](#build-system)
  * [Overview](#overview-2)
  * [Selection Criteria](#selection-criteria-2)
    + [Key factors for decision-making:](#key-factors-for-decision-making-2)
  * [Comparative Table of Popular Solutions](#comparative-table-of-popular-solutions-2)
  * [Rationale for Selection](#rationale-for-selection-2)
    + [Why CMake + Ninja – Chosen solution](#why-cmake-ninja-chosen-solution)
    + [Why not Meson?](#why-not-meson)
  * [Practical Considerations](#practical-considerations-2)
- [Web Framework](#web-framework)
- [ORM](#orm)
- [E2E Tests](#e2e-tests)

## C++

## Package manager

### Overview

**Definition:** A tool that automates the process of obtaining, installing, updating, and managing project dependencies.

**Purpose:** Solves the "dependency hell" problem—complexities in managing library versions, compatibility, and builds in C++ projects.

### Selection Criteria

#### Key factors for decision-making:

**Ease of use**
- Simplicity of setup and initial configuration (especially in a dev container)
- Intuitive commands and workflows
- Quality of documentation and examples

**Package ecosystem**
- Number of available libraries relevant to development
- Currency of popular library versions (e.g., Web Frameworks, ORM, JWT, etc.)
- Support for binary packages vs source builds

**Build system integration**
- Support for CMake, Make, other build systems, and containerized builds
- Easy integration (does not require changes to existing build scripts)
- Generation of configuration files

**Performance**
- Time for dependency download and installation (speed matters for container rebuilds)

### Comparative Table of Popular Solutions

| Criterion                | **Conan**                   | **vcpkg**                    |
|--------------------------|-----------------------------|------------------------------|
| Ease of setup            | + (excellent in containers) | + (also easy in containers)  |
| Intuitive CLI            | +                           | +                            |
| Documentation quality    | +                           | +                            |
| Number of packages       | +                           | +                            |
| Host Packages            | + (decentralized: Artifactory, Bintray, private)| + (centralized) |
| Version currency         | +                           | -                            |
| Build system integration | + (any)                     | + (CMake, MSBuild)           |
| Easy integration         | + (no forced toolchain)     | - (requires CMake toolchain) |
| Binary package support   | + (CI/CD, great for prebuilt dev containers)  | + (prevalent, but less flexible) |
| Source build support     | + (very flexible, user-defined) | + (but limited customization)  |

### Rationale for Selection

#### Why Conan – Chosen solution

**Advantages:**
- **Multiproject and scalable:** Conan easily manages dependencies for monorepos and multiplatform web services, and it excels when a template needs to be quickly copied and extended for new APIs or microservices.
- **Easiest path to custom/private packages:** Publishing and consuming in-house packages (like custom API middleware, logging, database abstraction) is straightforward, enabling fast code reuse across projects.
- **Modern C++ and cross-platform:** Conan works equally well on Linux, macOS, and Windows, vital for a template expected to run in diverse developer setups or CI environments.

**Disadvantages:**
- Initial learning curve is higher, but this is amortized quickly.

#### Why not vcpkg?

- **Intrusive build integration:** vcpkg requires using a special CMake toolchain file, which can complicate multi-project templates and may break easily when copying or embedding into new projects.
- **More CMake controll:** vcpkg does not control CMakeLists, editing and maintaining the build system remains entirely the responsibility of the user
- **Ecosystem and cross-platform limitations:** While solid for Windows/CMake, it's less frictionless when running in Linux-based containers, or when the template is adapted for non-standard build scenarios.
- **Internal libraries:** vcpkg templated package creation is easier for simple libraries, but lacks the power/flexibility required as backend projects become more complex and modular.

### Practical Considerations

For this boilerplate C++ backend template that is:
- intended to be cloned, customized, and started quickly in a dev container;
- is expected to be built and deployed reliably in CI/CD;
- Less control over C++ development configurations

## Compiler

### Overview

**Definition:** Programs that translate source code written in C++ into machine code or intermediate code executable by a computer.

**Purpose:** Efficiently and correctly convert human-readable code into optimized binary files, while providing useful diagnostic messages to support developers during build and debugging.

### Selection Criteria

#### Key factors for decision-making:

- Support of target platforms (Linux, Windows, macOS)
- Compliance and support of modern C++ standards
- Quality and readability of diagnostic messages (errors and warnings)
- Performance and optimization capabilities
- Integration with IDEs and toolkits
- Compatibility with selected package managers (e.g. Conan, vcpkg)

### Comparative Table of Popular Solutions

| Criterion               | **GCC**                | **Clang**                                 |
|-------------------------|------------------------|-------------------------------------------|
| Cross-platform          | +                      | +                                         |
| Bug Diagnostics         | + (less readable)      | + (clear and informative)                 |
| C++ Standards Support   | +                      | +                                         |
| Performance             | TOP                    | LESS THAN GCC                             |
| Integration with IDE    | +                      | + (more supported tools)                  |

### Rationale for Selection

#### Why Clang – Chosen solution

- Provides better bug reports, improving the developer experience.
- Better integration with modern IDEs and toolkits.
- Rapid implementation of new C++ standards.
- Modular and extendable architecture, support for advanced tools.

#### Why not GCC?

- Less readable and informative error and warning messages.
- Slower to implement new C++ standards.
- Less modularity and extensibility compared to Clang.
- GCC is not supporting popular developers tools like linters and autoformatters.

### Practical Considerations

For this boilerplate C++ backend template that is:
- **Clang** is often preferred in modern C++ projects because of its more readable and informative error messages, which speeds up debugging and easier for developers.
- **Clang** provides better compliance with modern C++ standards and faster support for new language features.
- **Clang** modular architecture and extensibility make it easy to fit into modern tools for static analysis, automatic formatting, and other integrations.
- **Clang** uses the most popular developer tools for automatic formatting and linting to be used in the project. **GCC** does not have such close integration with them.
- **GCC** remains the most reliable and productive solution with proven stability and is widely used. Therefore, it can be kept as a fallback compiler for extended compatibility.

## Build system

### Overview

**Definition:** Tools that automate and manage the build process of software projects, including linking binaries, managing dependencies and build configurations.

**Purpose:** Reliably and efficiently organize the build process, cross-platform compatibility and integration with other tools (e.g. package managers, CI/CD pipelines).

### Selection Criteria

#### Key factors for decision-making:

- Cross-platform build support
- Flexibility and scalability for complex and multi-project environments
- Integration with popular compilers and package managers
- Support for CI/CD and containerized environments
- Easy configuration and maintenance
- IDE support

### Comparative Table of Popular Solutions

> NOTE: Ninja is a low-level build executor that is responsible for fast and efficient incremental builds of a project. Unlike systems such as **CMake** or **Meson**, Ninja is not a build file generator and is not intended for manually writing build scripts.

| Criterion               | **CMake**                   | **Ninja**                 | **Meson**                     |
|-------------------------|-----------------------------|---------------------------|-------------------------------|
| Cross-platform support  | +                           | +                         | +                             |
| Flexibility             | +                           | depends on generator      | +                             |
| IDE integration         | +                           | +                         | + (less than CMake)           |
| CI/CD support           | +                           | +                         | +                             |
| Configuration simplicity| - (more difficult for beginners) | − (requires a generator) | +                         |

### Rationale for Selection

#### Why CMake + Ninja – Chosen solution

- **CMake** is an industry standard for build generation, very flexible and well supported in large and multi-project developments.
- Excellent integration with package managers (e.g. Conan, vcpkg).
- Allows you to generate build files for different backends, including **Ninja**.
- **Ninja** provides very fast incremental builds, which is especially important for frequent rebuilds in CI/CD and containers.
- This combination provides a balance between flexibility and build speed.

#### Why not Meson?

- It has a less mature ecosystem and less integration with IDEs than **CMake**.
- More suitable for experiments or PET projects.
- Integration with package managers is less common.
- **Meson** has less configuration flexibility, and the larger the project gets, the more the meson project loses flexibility.

### Practical Considerations

For this boilerplate C++ backend template that is:
- **CMake** is an industry standard with high flexibility and support for complex, multi-project builds, and integrates well with package managers and CI/CD.
- **Ninja** provides high speed incremental builds and minimal latency for frequent rebuilds, critical for dev containers and automated pipelines.
- The combination of **CMake + Ninja** gives a balance between configuration convenience and build performance.
- **Meson** is suitable for simple projects and quick customization, but is less common and has less integration with large tooling ecosystems.
- For a scalable and cross-platform to-dos-api-cpp template, **CMake + Ninja** remains the optimal choice for their universality and speed.

## Web Framework

At the time of research, the following versions were used:
- **Drogon:** 1.9.10
- **userver:** 2.12
- **Oat++:** 1.3.0

#### Key factors for decision-making:

**Ease of use**
- Simplicity of setup and initial configuration (especially in a dev container)
- Clear and simple syntax
- Easy to work with query parameters, headers and body
- Quality of documentation and examples

**Availability of opportunities**
- Possibility of implementing middleware for authentication (manual checking of headers or standard filters)
- Ability to work in multithreading mode, competitive processing of requests

**Availability of ORM**
- Having your own ORM system that eliminates working with SQL
- Availability of functionality for implementing database migrations

#### Comparative Table of Popular Solutions

| Criterion                      | Drogon                     | userver                        | Oat++                              |
| ------------------------------ | -------------------------- | ------------------------------ | ---------------------------------- |
| Ease of setup                  | +                          | -                              | +                                  |
| Readable syntax                | +                          | -                              | + (but more difficult than Drogon) |
| Easy work with request parts   | +                          | (not studied due to exclusion) | +                                  |
| Quality documentation          | + (but with disadvantages) | (not studied due to exclusion) | +                                  |
| Availability of middleware     | +                          | (not studied due to exclusion) | +                                  |
| Multithreaded work             | +                          | (not studied due to exclusion) | + (but with disadvantages)         |
| Availability of a suitable ORM | -                          | (not studied due to exclusion) | -                                  |
| Presence of migrations         | -                          | (not studied due to exclusion) | -                                  |

#### Why Drogon - Chosen solution

**Advantages:**
- **Ease of use:** Drogon has a simple, readable syntax, which significantly reduces the entry barrier and improves the understandability and readability of the code.
- **Support by build systems:** Drogon package is available in conan-center and is easy to install and configure the parameters.
- **Configuration file:** all of Drogon's main settings can be defined through a configuration file, which adds convenience to use and allows you to store all of your settings in one place.
- **Support for multithreaded work:** Drogon supports multi-threaded operation.

**Disadvantages:**
- The official Drogon documentation often refers to sections of documentation that do not exist, and often lacks explanations of how certain constructs work.
- Drogon has a very limited range of capabilities of the built-in ORM system; for full-fledged work it is necessary to write your own SQL queries.

#### Why not userver?

- **Difficulty of installation:** at the time of research, the userver package is missing from conan-center, which forces the installation to bypass Conan.The official userver documentation suggests building your application from a cloned repository containing the userver application template.
- **Difficult to use:** userver has a complex syntax that is not immediately clear, which makes it difficult to understand at the initial stages of development. It will take a lot of time to explore the capabilities of the framework.
- **Third party dependencies:** at the time of research it was noticed that when installing userver, it pulls in many third-party dependencies that may not be needed during operation.
- **Installing your own dependencies:** difficulty installing your own dependencies.

#### Why not Oat++?

- **More complex syntax:** Oat++ has a more difficult to understand syntax compared to Drogon.
- **Missing configuration file:** Oat++ does not provide the ability to use a single configuration file, which complicates the application configuration.
- **Lack of a full-fledged ORM:** Oat++ does not have full-fledged methods for working with databases; you need to write your own SQL queries.

## ORM

### Overview

The goal is to choose an ORM stack for PostgreSQL with versioned migrations, LINQ-style query abstraction, and relations support for a C++ project.
Three solutions were evaluated: Drogon ORM (part of the Drogon framework), ODB (a compile-time, strongly typed ORM/code generator), and TinyORM (modern C++20 ORM with a migrations tool and Qt/TinyDrivers support).

### Selection Criteria

- Migrations: availability of up/down history and/or schema evolution; suitability for an existing database.
- PostgreSQL: official support and tooling (model/schema generation).
- High-level queries: an API to compose conditions and joins similar to LINQ.
- Relations: convenient handling of join/relationship APIs.
- Integration/packaging: presence in Conan and ease of integrating into builds and CI.

### Comparative Table of Popular Solutions

| Criterion         | Drogon ORM                          | ODB                             | TinyORM                  |
|-------------------|-------------------------------------|---------------------------------|--------------------------|
| Migrations        | -                                   | - (not optimized realization)   | +                        |
| PostgreSQL        | +                                   | +                               | +                        |
| LINQ-like queries | +                                   | +                               | +                        |
| Relations         | - (manual linking on support model) | +                               | +                        |
| Packaging (Conan) | +                                   | -                               | - (vcpackage recomended) |
| Model/schema      | + (model generated from schema)     | + (class describe a table)      | +                        |

### Rationale for Selection

- Combined approach: the Python stack SQLAlchemy + Alembic provides full up/down migration history and robust schema evolution control, while ODB ensures strong typing and efficient C++ data access.
- Migrations runs in a specialized toolchain unrelated from the C++ build; the C++ data layer remains statically via ODB.

#### Why not the others?

- Drogon ORM: no native migrations; model generation is schema-first; lacks a dedicated abstraction for relations, often pushing toward manual JOINs or raw SQL.
- TinyORM: powerful migrations and CLI, but the default QtSql dependency increases integration weight; packaging ecosystem recommended with vcpkg, complicating Conan-centric pipelines.

### Practical Considerations

- CI/CD and containers: Drogon can be consumed from ConanCenter, but ODB and TinyORM typically require custom recipes/artifacts or alternative managers, affecting caching and build times.
- Existing database schemas: with an already deployed DB, schema-first model generation (Drogon) or an external migrator is convenient; for domain-first design, class-first with ODB and its schema evolution fits better.

### Conclusion

Final decision: manage migrations with SQLAlchemy/Alembic and use ODB for C++ data access.

### Chosen Approach

- Define models in SQLAlchemy; manage revisions and rollbacks with Alembic.
- Implement and maintain C++ data access with ODB on PostgreSQL.
- Coordination workflow: apply Alembic migrations first, then synchronize ODB mappings/models and the C++ data access code to reflect schema updates.

## E2E Tests