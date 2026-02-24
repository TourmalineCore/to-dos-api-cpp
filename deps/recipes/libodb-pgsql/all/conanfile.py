import os
import textwrap
from conan import ConanFile
from conan.errors import ConanInvalidConfiguration
from conan.tools.cmake import CMake, CMakeToolchain, CMakeDeps, cmake_layout
from conan.tools.files import get, save, rmdir


class LibOdbPgsqlConan(ConanFile):
    name = "libodb-pgsql"
    version = "2.5.0"
    license = "GPL-2.0-only"
    homepage = "https://www.codesynthesis.com/products/odb/"
    topics = ("odb", "orm", "database", "c++")

    settings = "os", "compiler", "build_type", "arch"
    options  = {"shared": [True, False], "fPIC": [True, False]}
    default_options = {"shared": False, "fPIC": True}

    def config_options(self):
        if self.settings.os == "Windows":
            del self.options.fPIC

    def configure(self):
        if self.options.shared:
            self.options.rm_safe("fPIC")

    def layout(self):
        cmake_layout(self, src_folder="src")

    def validate(self):
        if self.settings.os != "Linux":
            raise ConanInvalidConfiguration(
                f"{self.ref} supported only on devcontainers/base:ubuntu-22.04"
            )

    def requirements(self):
        self.requires("libodb/2.5.0")
        self.requires("libpq/17.7")

    def source(self):
        get(
            self,
            url=f"https://www.codesynthesis.com/download/odb/{self.version}/libodb-pgsql-{self.version}.tar.gz",
            sha256="f6e63db4a2f77604f48115f64c74a5854ca20f03f208568966693e95712a3e17", # replace hash if you changing sources
            strip_root=True,
        )
        self._inject_cmake()

    def _inject_cmake(self):
        major = self.version.split(".")[0]
        cmake = textwrap.dedent(f"""\
            cmake_minimum_required(VERSION 3.15)
            project(odb-pgsql VERSION {self.version} LANGUAGES CXX)

            find_package(libodb     REQUIRED CONFIG)
            find_package(PostgreSQL REQUIRED CONFIG)

            file(GLOB ODB_SOURCES "odb/pgsql/*.cxx")

            file(GLOB ODB_PREGENERATED_SOURCES
                "odb/pgsql/details/pregenerated/odb/pgsql/details/*.cxx"
            )

            add_library(odb-pgsql
                ${{ODB_SOURCES}}
                ${{ODB_PREGENERATED_SOURCES}}
            )

            target_include_directories(odb-pgsql PUBLIC
                $<BUILD_INTERFACE:${{CMAKE_CURRENT_SOURCE_DIR}}>
                $<BUILD_INTERFACE:${{CMAKE_CURRENT_SOURCE_DIR}}/odb/pgsql/details/pregenerated>
                $<INSTALL_INTERFACE:include>
            )

            target_compile_features(odb-pgsql PUBLIC cxx_std_11)

            target_link_libraries(odb-pgsql PUBLIC
                libodb::libodb
                PostgreSQL::PostgreSQL
            )

            set_target_properties(odb-pgsql PROPERTIES
                VERSION   {self.version}
                SOVERSION {major}
                POSITION_INDEPENDENT_CODE ON
            )

            install(TARGETS odb-pgsql
                ARCHIVE DESTINATION lib
                LIBRARY DESTINATION lib
                RUNTIME DESTINATION bin
            )

            install(DIRECTORY odb/pgsql
                DESTINATION include/odb
                FILES_MATCHING
                    PATTERN "*.hxx"
                    PATTERN "*.ixx"
                    PATTERN "*.txx"
                    PATTERN "*.h"
                PATTERN "pregenerated" EXCLUDE
            )

            install(DIRECTORY odb/pgsql/details/pregenerated/odb/pgsql/details
                DESTINATION include/odb/pgsql
                FILES_MATCHING
                    PATTERN "*.hxx"
                    PATTERN "*.ixx"
            )
        """)
        save(self, os.path.join(self.source_folder, "CMakeLists.txt"), cmake)

    def generate(self):
        tc = CMakeToolchain(self)
        tc.generate()

        deps = CMakeDeps(self)
        deps.generate()

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
        self.cpp_info.libs = ["odb-pgsql"]
        self.cpp_info.requires = [
            "libodb::libodb",
            "libpq::pq",
        ]
        self.cpp_info.set_property("cmake_target_name", "libodb-pgsql::libodb-pgsql")
        self.cpp_info.set_property("pkg_config_name",   "libodb-pgsql")
