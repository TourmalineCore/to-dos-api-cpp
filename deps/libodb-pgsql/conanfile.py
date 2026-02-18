from conan import ConanFile
from conan.tools.gnu import Autotools, AutotoolsToolchain, AutotoolsDeps
from conan.tools.files import get, copy, rmdir
from conan.tools.layout import basic_layout
import os

required_conan_version = ">=2.0"

class LibODBPgsqlConan(ConanFile):
    name = "libodb-pgsql"
    version = "2.5.0"

    license = "GPL-2.0-only OR proprietary"
    url = "https://github.com/your-username/conan-libodb-pgsql"
    homepage = "https://www.codesynthesis.com/products/odb/"
    description = "PostgreSQL database support for ODB ORM"
    topics = ("orm", "database", "postgresql", "c++", "persistence")

    package_type = "library"
    settings = "os", "arch", "compiler", "build_type"
    
    options = {
        "shared": [True, False],
        "fPIC": [True, False],
    }
    
    default_options = {
        "shared": False,
        "fPIC": True,
    }
    
    def config_options(self):
        if self.settings.os == "Windows":
            del self.options.fPIC
    
    def configure(self):
        if self.options.shared:
            self.options.rm_safe("fPIC")
    
    def requirements(self):
        self.requires("libodb/2.4.0")
        self.requires("libpq/16.8")
    
    def layout(self):
        basic_layout(self, src_folder="src")
    
    def source(self):
        get(self, 
            f"https://www.codesynthesis.com/download/odb/{self.version}/libodb-pgsql-{self.version}.tar.gz",
            strip_root=True)
    
    def generate(self):
        tc = AutotoolsToolchain(self)
        tc.generate()
        
        deps = AutotoolsDeps(self)
        deps.generate()
    
    def build(self):
        autotools = Autotools(self)
        autotools.configure()
        autotools.make()
    
    def package(self):
        autotools = Autotools(self)
        autotools.install()
        
        copy(self, "LICENSE", 
             src=self.source_folder, 
             dst=os.path.join(self.package_folder, "licenses"))
        
        rmdir(self, os.path.join(self.package_folder, "share"))
        rmdir(self, os.path.join(self.package_folder, "lib", "pkgconfig"))
    
    def package_info(self):
        self.cpp_info.libs = ["odb-pgsql"]
        
        self.cpp_info.requires = ["libodb::libodb", "libpq::pq"]
        
        if self.settings.os in ["Linux", "FreeBSD"]:
            self.cpp_info.system_libs.append("pthread")