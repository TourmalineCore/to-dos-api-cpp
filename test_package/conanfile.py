import os
from conan import ConanFile
from conan.tools.build import can_run


class to_dos_apiTestConan(ConanFile):
    settings = "os", "compiler", "build_type", "arch"

    def requirements(self):
        self.requires(self.tested_reference_str)

    def test(self):
        if can_run(self):
            self.run("to-dos-api", env="conanrun")
