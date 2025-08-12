# Applied technologies

## Table Of Content

- [C++](#c--)
- [Package manager](#package-manager)
  * [Overview](#overview)
  * [Selection Criteria](#selection-criteria)
    + [Key factors for decision-making:](#key-factors-for-decision-making-)
  * [Comparative Table of Popular Solutions](#comparative-table-of-popular-solutions)
  * [Rationale for Selection](#rationale-for-selection)
    + [Why Conan? (Chosen solution)](#why-conan-chosen-solution)
    + [Why not vcpkg?](#why-not-vcpkg)
  * [Practical Considerations](#practical-considerations)
- [Compiler](#compiler)
  * [Overview](#overview-1)
  * [Selection Criteria](#selection-criteria-1)
    + [Key factors for decision-making:](#key-factors-for-decision-making-1)
  * [Comparative Table of Popular Solutions](#comparative-table-of-popular-solutions-1)
  * [Rationale for Selection](#rationale-for-selection-1)
    + [Why Clang? (Chosen solution)](#why-clang-chosen-solution)
    + [Why not GCC?](#why-not-gcc)
  * [Practical Considerations](#practical-considerations-1)
- [Build system](#build-system)
  * [Overview](#overview-2)
  * [Selection Criteria](#selection-criteria-2)
    + [Key factors for decision-making:](#key-factors-for-decision-making-2)
  * [Comparative Table of Popular Solutions](#comparative-table-of-popular-solutions-2)
  * [Rationale for Selection](#rationale-for-selection-2)
    + [Why CMake + Ninja? (Chosen solution)](#why-cmake-ninja-chosen-solution)
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

### Practical Considerations

For this boilerplate C++ backend template that is:
- **Clang** is often preferred in modern C++ projects because of its more readable and informative error messages, which speeds up debugging and easier for developers.
- **Clang** provides better compliance with modern C++ standards and faster support for new language features.
- **Clang** modular architecture and extensibility make it easy to fit into modern tools for static analysis, automatic formatting, and other integrations.
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

### Practical Considerations

For this boilerplate C++ backend template that is:
- **CMake** is an industry standard with high flexibility and support for complex, multi-project builds, and integrates well with package managers and CI/CD.
- **Ninja** provides high speed incremental builds and minimal latency for frequent rebuilds, critical for dev containers and automated pipelines.
- The combination of **CMake + Ninja** gives a balance between configuration convenience and build performance.
- **Meson** is suitable for simple projects and quick customization, but is less common and has less integration with large tooling ecosystems.
- For a scalable and cross-platform to-dos-api-cpp template, **CMake + Ninja** remains the optimal choice for their universality and speed.

## Web Framework

## ORM

## E2E Tests