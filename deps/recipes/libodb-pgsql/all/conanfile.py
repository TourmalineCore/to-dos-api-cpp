from conan import ConanFile
from conan.tools.cmake import CMake, cmake_layout
from conan.tools.files import get, save, copy
import os
import textwrap

class LibodbPgsqlConan(ConanFile):
    name = "libodb-pgsql"
    version = "2.5.0"
    settings = "os", "compiler", "build_type", "arch"
    requires = ("libodb/2.5.0", "libpq/17.7")
    generators = "CMakeToolchain"

    def layout(self):
        cmake_layout(self)

    def source(self):
        get(self, 
            f"https://www.codesynthesis.com/download/odb/{self.version}/libodb-pgsql-{self.version}.tar.gz",
            sha256="f6e63db4a2f77604f48115f64c74a5854ca20f03f208568966693e95712a3e17",
            strip_root=True)

    def build(self):
        libodb_inc = self.dependencies["libodb"].package_folder + "/include"
        libpq_inc  = self.dependencies["libpq"].package_folder + "/include"

        self.run(f"cp -r {libodb_inc}/odb {self.source_folder}/")

        cmake_content = textwrap.dedent(f"""\
            cmake_minimum_required(VERSION 3.15)
            project(libodb-pgsql VERSION {self.version} LANGUAGES CXX)

            file(GLOB_RECURSE SOURCES "odb/pgsql/*.cxx")

            add_library(libodb-pgsql ${{SOURCES}})

            target_include_directories(libodb-pgsql PRIVATE
                ${{CMAKE_CURRENT_SOURCE_DIR}}
                ${{CMAKE_CURRENT_SOURCE_DIR}}/odb/pgsql/details/pregenerated
                {libpq_inc}
            )

            target_link_libraries(libodb-pgsql PUBLIC odb PRIVATE pq)
            target_compile_definitions(libodb-pgsql PUBLIC ODB_THREADS_POSIX)
            target_compile_features(libodb-pgsql PUBLIC cxx_std_11)
        """)

        save(self, os.path.join(self.source_folder, "CMakeLists.txt"), cmake_content)

        cmake = CMake(self)
        cmake.configure()
        cmake.build()

    def package(self):
        copy(self, "LICENSE", src=self.source_folder, 
            dst=os.path.join(self.package_folder, "licenses"))
        copy(self, "*.h",   src=self.source_folder, 
            dst=os.path.join(self.package_folder, "include"), keep_path=True)
        copy(self, "*.hxx", src=self.source_folder, 
            dst=os.path.join(self.package_folder, "include"), keep_path=True)
        copy(self, "*.ixx", src=self.source_folder,
            dst=os.path.join(self.package_folder, "include"), keep_path=True)
        copy(self, "*.txx", src=self.source_folder, 
            dst=os.path.join(self.package_folder, "include"), keep_path=True)
        copy(self, "*.a",   src=self.build_folder,  
            dst=os.path.join(self.package_folder, "lib"), keep_path=False)

def package_info(self):
    self.cpp_info.libs = ["libodb-pgsql"]
    self.cpp_info.requires = ["libodb::libodb", "libpq::pq"]
    self.cpp_info.system_libs = []

