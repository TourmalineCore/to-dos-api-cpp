# Applied technologies

## C++

## Package manager

### Overview

**Definition:** A tool that automates the process of obtaining, installing, updating, and managing project dependencies.

**Purpose:** Solves the "dependency hell" problem—complexities in managing library versions, compatibility, and builds in C++ projects.

### Selection Criteria

#### Key factors for decision-making:

**Ease of use**
- Simplicity of setup and initial configuration
- Intuitive commands and workflows
- Quality of documentation and examples

**Package ecosystem**
- Number of available libraries in the repository
- Currency of popular library versions
- Support for creating custom packages

**Build system integration**
- Support for CMake, Make, MSBuild
- Non-intrusive integration (does not require changes to existing build scripts)
- Generation of configuration files

**Performance**
- Time for dependency download and installation
- Support for binary packages vs source builds
- Efficiency of caching

### Comparative Table of Popular Solutions

| Criterion           | Manager 1 | Manager 2 |
|---------------------|-----------|-----------|
| First               |     -     |     -     |
| Second              |     +     |     -     |

### Rationale for Selection

#### Manager 1 – Chosen solution

**Advantages:**
- First
- Second

**Disadvantages:**
- First
- Second

#### Why not Manager 2?

### Practical Considerations

For this project, Manager 1 is optimal because:

1. First
2. Second

**Alternative choice:** if there are special requirements for the project.

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
- Compatibility with selected package managers (e.g. Conan)

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
- Rapid adoption of new C++ standards.
- Modular and extensible architecture, support for advanced tools.

#### Why not GCC?

- Less readable and informative error and warning messages.
- Slower to implement new C++ standards.
- Less modularity and extensibility compared to Clang.

### Practical Considerations

For this boilerplate C++ backend template that is:
- **Clang** is often preferred in modern C++ projects because of its more readable and informative error messages, which speeds up debugging and makes life easier for developers.
- **Clang** provides better compliance with modern C++ standards and faster support for new language features, allowing you to utilize the latest tools and practices.
- Clang's modular architecture and extensibility make it easy to fit into modern tools for static analysis, automatic formatting, and other integrations.
- **GCC** remains the most reliable and productive solution with proven stability and is widely used. Therefore, it can be kept as a fallback compiler for extended compatibility.

## Build system

## Web Framework

## ORM

## E2E Tests