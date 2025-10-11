from conan import ConanFile
from conan.tools.cmake import CMakeToolchain, CMakeDeps, cmake_layout, CMake

class EtCoreRecipe(ConanFile):
    name = "et-core"
    version = "0.0.0"
    package_type = "application"

    # Binary configuration
    settings = "os", "compiler", "build_type", "arch"
    options = {
        "shared": [True, False],
        "fPIC": [True, False]
    }
    default_options = {
        "shared": False,
        "fPIC": True
    }

    # Dependencies
    requires = (
        "spdlog/1.13.0",
        "cli11/2.4.2",
        "nlohmann_json/3.11.3",
        "sqlite3/3.46.1",
        "tl-expected/1.1.0",
        "catch2/3.6.0",
        "boost/1.84.0",     # For Boost.DI
    )

    def config_options(self):
        if self.settings.os == "Windows":
            del self.options.fPIC

    def layout(self):
        cmake_layout(self)

    def generate(self):
        deps = CMakeDeps(self)
        deps.generate()
        tc = CMakeToolchain(self)
        tc.user_presets_path = None
        tc.presets_path = None
        tc.generate()

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()
