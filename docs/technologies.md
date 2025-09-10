# Applied technologies

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

## Build system

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

## E2E Tests