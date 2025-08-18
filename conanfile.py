from conan import ConanFile
from conan.tools.cmake import CMakeToolchain, CMake, cmake_layout, CMakeDeps


class to_dos_apiRecipe(ConanFile):
    name = "to-dos-api"
    version = "1.0"
    package_type = "application"

    # Optional metadata
    license = "MIT"
    author = "Oleg Kliavlin oklyavlin@tourmalinecore.com, Aleksandr Shinkarev ashinkarev@tourmalinecore.com"
    url = "https://github.com/TourmalineCore/to-dos-api-cpp"
    description = ""

    # Binary configuration
    settings = "os", "compiler", "build_type", "arch"

    # Sources are located in the same place as this recipe, copy them to the recipe
    exports_sources = "CMakeLists.txt", "src/*"

    def layout(self):
        cmake_layout(self)

    def generate(self):
        deps = CMakeDeps(self)
        deps.generate()
        tc = CMakeToolchain(self, generator="Ninja")
        tc.generate()

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

    def package(self):
        cmake = CMake(self)
        cmake.install()

    def requirements(self):
        self.requires("drogon/1.9.10")