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

## ORM

## E2E Tests