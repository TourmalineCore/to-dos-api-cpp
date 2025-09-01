from conan import ConanFile
from conan.tools.cmake import CMakeToolchain, CMake, cmake_layout, CMakeDeps
from conan.tools.files import get, copy, apply_conandata_patches
from conan.tools.scm import Git
import os

class TinyORMConan(ConanFile):
    name = "tinyorm"
    version = "0.38.1"
    
    license = "MIT"
    author = "Silver Zachara <silver.zachara@gmail.com>"
    url = "https://github.com/silverqx/TinyORM"
    description = "Modern C++ ORM library for Qt framework"
    topics = ("orm", "database", "qt", "mysql", "cpp20")
    homepage = "https://www.tinyorm.org"
    
    package_type = "library"
    settings = "os", "arch", "compiler", "build_type"
    
    options = {
        "shared": [True, False],
        "fPIC": [True, False],
        "build_drivers": [True, False],
        "build_mysql_driver": [True, False],
        "mysql_ping": [True, False],
        "build_tom": [True, False],
        "disable_orm": [True, False],
        "tiny_mysql_ping": [True, False],
        "inline_constants": [True, False],
        "msvc_runtime_dynamic": [True, False],
        "with_tests": [True, False]
    }
    
    default_options = {
        "shared": False,
        "fPIC": True,
        "build_drivers": True,
        "build_mysql_driver": True,
        "mysql_ping": True,
        "build_tom": True,
        "disable_orm": False,
        "tiny_mysql_ping": True,
        "inline_constants": True,
        "msvc_runtime_dynamic": True,
        "with_tests": False
    }
    
    generators = "CMakeDeps", "CMakeToolchain"
    
    exports_sources = "CMakeLists.txt", "cmake/*", "include/*", "src/*", "tom/*", "drivers/*", "tests/*", "patches/*", "*.md", "*.txt"
    
    def config_options(self):
        if self.settings.os == "Windows":
            self.options.rm_safe("fPIC")
            
    def configure(self):
        if not self.options.shared:
            self.options.rm_safe("fPIC")
            
        if self.options.disable_orm:
            self.options.build_tom = False
            
        if self.options.build_drivers and not self.options.build_mysql_driver:
            self.output.warn("build_drivers=True requires build_mysql_driver=True, enabling it")
            self.options.build_mysql_driver = True
    
    def layout(self):
        cmake_layout(self)
    
    def requirements(self):
        self.requires("range-v3/0.12.0")
        self.requires("tabulate/1.5")
        
        if not self.options.build_drivers:
            self.requires("qt/6.6.1")
        
        if self.options.build_drivers and self.options.build_mysql_driver:
            self.requires("libmysqlclient/8.0.34")
            
        if self.options.with_tests:
            self.test_requires("gtest/1.14.0")
    
    def build_requirements(self):
        self.tool_requires("cmake/[>=3.22]")
        
    def source(self):
        get(self,
            url=self.conan_data["sources"][self.version]["url"],
            sha256=self.conan_data["sources"][self.version]["sha256"],
            strip_root=self.conan_data["sources"][self.version].get("strip_root", True))
    
    def generate(self):
        tc = CMakeToolchain(self)
        
        tc.variables["BUILD_SHARED_LIBS"] = self.options.shared
        tc.variables["ORM"] = not self.options.disable_orm
        tc.variables["BUILD_DRIVERS"] = self.options.build_drivers
        tc.variables["BUILD_MYSQL_DRIVER"] = self.options.build_mysql_driver
        tc.variables["MYSQL_PING"] = self.options.mysql_ping
        tc.variables["BUILD_TESTS"] = self.options.with_tests
        tc.variables["TOM"] = self.options.build_tom
        tc.variables["TINY_MYSQL_PING"] = self.options.tiny_mysql_ping
        tc.variables["INLINE_CONSTANTS"] = self.options.inline_constants
        
        if self.settings.os == "Windows":
            tc.variables["MSVC_RUNTIME_DYNAMIC"] = self.options.msvc_runtime_dynamic
            
        if self.options.build_drivers:
            if self.options.shared:
                tc.variables["DRIVERS_TYPE"] = "Shared"
            else:
                tc.variables["DRIVERS_TYPE"] = "Static"
        
        deps = CMakeDeps(self)
    
    def build(self):
        apply_conandata_patches(self) 
        cmake = CMake(self)
        cmake.configure()
        cmake.build()
        
        if self.options.with_tests and not self.conf.get("tools.build:skip_test", default=False):
            cmake.test()
    
    def package(self):
        copy(self, "LICENSE", dst=os.path.join(self.package_folder, "licenses"), src=self.source_folder)
        
        cmake = CMake(self)
        cmake.install()
    
    def package_info(self):
        if not self.options.disable_orm:
            self.cpp_info.components["tinyorm"].libs = ["TinyOrm"]
            self.cpp_info.components["tinyorm"].includedirs = ["include"]
            
            self.cpp_info.components["tinyorm"].requires = ["range-v3::range-v3", "tabulate::tabulate"]
            
            if not self.options.build_drivers:
                self.cpp_info.components["tinyorm"].requires.append("qt::qtcore")
                self.cpp_info.components["tinyorm"].requires.append("qt::qtsql")
        
        if self.options.build_drivers:
            self.cpp_info.components["tinydrivers"].libs = ["TinyDrivers"]
            self.cpp_info.components["tinydrivers"].includedirs = ["include"]
            
            if self.options.build_mysql_driver:
                if self.options.shared:
                    self.cpp_info.components["tinymysql"].libs = ["TinyMySql"]
                self.cpp_info.components["tinymysql"].requires = ["libmysqlclient::libmysqlclient"]
                
        if self.options.build_tom:
            self.cpp_info.components["tom"].bindirs = ["bin"]
        
        self.cpp_info.set_property("cmake_find_mode", "both")
        self.cpp_info.set_property("cmake_file_name", "TinyOrm")
        self.cpp_info.set_property("cmake_target_name", "TinyOrm::TinyOrm")
        
        if self.options.build_drivers:
            self.cpp_info.defines.append("TINYORM_USING_TINYDRIVERS=1")
            
        if self.options.inline_constants:
            self.cpp_info.defines.append("TINYORM_INLINE_CONSTANTS=1")

    def package_id(self):
        del self.info.options.with_tests
