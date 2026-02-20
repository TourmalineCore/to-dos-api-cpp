import os
import textwrap
from conan import ConanFile
from conan.tools.cmake import CMake, CMakeToolchain, cmake_layout
from conan.tools.files import get, save, rmdir


class LibOdbConan(ConanFile):
    name = "libodb"
    version = "2.5.0"
    description = "ODB C++ ORM — core runtime library"
    license = "GPL-2.0-only"
    homepage = "https://www.codesynthesis.com/products/odb/"
    topics = ("odb", "orm", "database", "c++")

    settings = "os", "compiler", "build_type", "arch"
    options  = {"shared": [True, False], "fPIC": [True, False]}
    default_options = {"shared": False, "fPIC": True}

    def layout(self):
        cmake_layout(self, src_folder="src")

    def validate(self):
        if self.settings.os != "Linux":
            raise ConanInvalidConfiguration(
                f"{self.ref} supporting only in devcontainers/base:ubuntu-22.04"
            )

    def source(self):
        get(
            self,
            url=f"https://www.codesynthesis.com/download/odb/{self.version}/libodb-{self.version}.tar.gz",
            sha256="700038a73c6cbead011129b15030b7cdd3f73510b687f2c4504808df4230441b",  # replace hash if you changing sources
            strip_root=True,
        )
        self._inject_cmake()

    def _inject_cmake(self):
        major = self.version.split(".")[0]
        cmake = textwrap.dedent(f"""\
            cmake_minimum_required(VERSION 3.15)
            project(libodb VERSION {self.version} LANGUAGES CXX)

            file(GLOB ODB_SOURCES         "odb/*.cxx")
            file(GLOB ODB_DETAILS_SOURCES "odb/details/*.cxx")

            add_library(odb
                ${{ODB_SOURCES}}
                ${{ODB_DETAILS_SOURCES}}
            )

            target_include_directories(odb PUBLIC
                $<BUILD_INTERFACE:${{CMAKE_CURRENT_SOURCE_DIR}}>
                $<INSTALL_INTERFACE:include>
            )

            target_compile_features(odb PUBLIC cxx_std_11)

            find_package(Threads REQUIRED)
            target_compile_definitions(odb PUBLIC ODB_THREADS_POSIX)
            target_link_libraries(odb PUBLIC Threads::Threads)

            set_target_properties(odb PROPERTIES
                VERSION   {self.version}
                SOVERSION {major}
            )

            install(TARGETS odb
                ARCHIVE DESTINATION lib
                LIBRARY DESTINATION lib
                RUNTIME DESTINATION bin
            )
            install(DIRECTORY odb/
                DESTINATION include/odb
                FILES_MATCHING
                    PATTERN "*.hxx"
                    PATTERN "*.ixx"
                    PATTERN "*.txx"
                    PATTERN "*.h"
            )
        """)
        save(self, os.path.join(self.source_folder, "CMakeLists.txt"), cmake)

    def generate(self):
        tc = CMakeToolchain(self)
        tc.generate()

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

    def package(self):
        cmake = CMake(self)
        cmake.install()
        rmdir(self, os.path.join(self.package_folder, "lib", "pkgconfig"))
        rmdir(self, os.path.join(self.package_folder, "share"))

    def package_info(self):
        self.cpp_info.libs = ["odb"]
        self.cpp_info.system_libs = ["pthread"]
        self.cpp_info.set_property("cmake_target_name", "libodb::libodb")
        self.cpp_info.set_property("pkg_config_name",   "libodb")
