set_property(GLOBAL
	PROPERTY CONFIGURATION_COMMON_PRIVATE_COMPILE_DEFINITIONS
		$<$<PLATFORM_ID:Windows>:_CRT_SECURE_NO_DEPRECATE>
		$<$<PLATFORM_ID:Windows>:_CRT_SECURE_NO_WARNINGS>
		$<$<PLATFORM_ID:Windows>:WIN32>
		$<$<PLATFORM_ID:Windows>:_UNICODE>
		$<$<PLATFORM_ID:Windows>:UNICODE>
		$<$<PLATFORM_ID:Windows>:NOMINMAX>
		$<$<PLATFORM_ID:Windows>:WIN32_LEAN_AND_MEAN>
		$<$<PLATFORM_ID:Windows>:_WIN32_WINNT=0x0601> # Windows 7 or later (required for gRPC)
		$<$<PLATFORM_ID:Windows>:OS_WINPC>
		$<$<PLATFORM_ID:Windows>:PLAT_WINPC_X86>
		$<$<PLATFORM_ID:Windows>:WIN64>
		$<$<PLATFORM_ID:Windows>:HW_X64>
		$<$<PLATFORM_ID:Windows>:PLAT_WINPC_X64>
		$<$<AND:$<CONFIG:Debug>,$<CXX_COMPILER_ID:Clang,GNU>>:_DEBUG> # define _DEBUG constant also for gcc Linux builds
)

set_property(GLOBAL
	PROPERTY CONFIGURATION_COMMON_PRIVATE_COMPILE_OPTIONS
		$<$<CXX_COMPILER_ID:MSVC>:/WX> # treat compile-warnings as errors
		$<$<CXX_COMPILER_ID:MSVC>:/W3> # set warning level up to production-ready
		$<$<CXX_COMPILER_ID:MSVC>:/EHsc> # exception handling model
		$<$<CXX_COMPILER_ID:MSVC>:/nologo> # prevents the display of the copyright and version number message when the task starts.
		$<$<CXX_COMPILER_ID:MSVC>:/wd4996> # do not warn on deprecated
		$<$<CXX_COMPILER_ID:MSVC>:/wd4275> # do not warn on non dll-interface base for dll-interface class (ports pattern)
		$<$<CXX_COMPILER_ID:MSVC>:/Zc:__cplusplus> # let MSVC report __cplusplus correctly
		$<$<CXX_COMPILER_ID:MSVC>:/Zi> # Produces a program database (PDB)
		$<$<CXX_COMPILER_ID:MSVC>:/fp:except-> # disable reliable floating-point exception mode
		$<$<CXX_COMPILER_ID:MSVC>:/fp:precise> # floating point model
		$<$<AND:$<CXX_COMPILER_ID:MSVC>,$<CONFIG:Release>>:/Gy> # package individual functions in the form of packaged functions (COMDATs).
		$<$<AND:$<CXX_COMPILER_ID:MSVC>,$<CONFIG:Release>>:/GF> # eliminate duplicate strings
		$<$<CXX_COMPILER_ID:MSVC>:/MP> # Build with multiple processes

		$<$<CXX_COMPILER_ID:Clang,GNU>:-fPIC>
		$<$<CXX_COMPILER_ID:Clang,GNU>:-Werror>

#		$<$<CXX_COMPILER_ID:Clang,GNU>:-Winline>

#		$<$<CXX_COMPILER_ID:Clang,GNU>:-Wall>
#		$<$<CXX_COMPILER_ID:Clang,GNU>:-Wextra>
#		$<$<CXX_COMPILER_ID:Clang,GNU>:-Wpedantic>

#		$<$<CXX_COMPILER_ID:Clang,GNU>:-Wno-deprecated>
#		$<$<CXX_COMPILER_ID:Clang,GNU>:-Wno-switch>
#		$<$<CXX_COMPILER_ID:Clang,GNU>:-Wno-unknown-pragmas>
#		$<$<CXX_COMPILER_ID:Clang,GNU>:-Wno-unused-function>
#		$<$<CXX_COMPILER_ID:Clang,GNU>:-Wno-unused-variable>
#		$<$<CXX_COMPILER_ID:Clang,GNU>:-Wno-sign-compare>
#		$<$<CXX_COMPILER_ID:GNU>:-Wno-suggest-override>
#		$<$<CXX_COMPILER_ID:GNU>:-Wno-unused-but-set-variable>
#		$<$<CXX_COMPILER_ID:GNU>:-Wno-misleading-indentation>
#		$<$<CXX_COMPILER_ID:GNU>:-fdiagnostics-color=always> # always colored output (warnings, errors, etc.)
#		$<$<CXX_COMPILER_ID:Clang>:-Wno-inconsistent-missing-override>
#		$<$<CXX_COMPILER_ID:Clang>:-fcolor-diagnostics> # always colored output (warnings, errors, etc.)

		# Debug specific settings
		$<$<AND:$<CONFIG:Debug>,$<CXX_COMPILER_ID:Clang,GNU>>:-g -O0>
		# Due to -D_FORTIFY_SOURCE=2, -O1 is the lowest level of optimization that can be used for armv8.
		# However we want a debug build, therefore, we want -O0. We can't have both -D_FORTIFY_SOURCE=2
		# and -O0. The choice here is that -O0 should have higher priority, and therefore, let's disable
		# _FORTIFY_SOURCE. The toolchain also uses -Wl,-O1. Let's not optimise at link time either.
		$<$<AND:$<CONFIG:Debug>,$<STREQUAL:${CMAKE_SYSTEM_PROCESSOR},aarch64>>:-U _FORTIFY_SOURCE -Wl,-O0>

		# Release specific settings
		$<$<AND:$<CONFIG:Release>,$<CXX_COMPILER_ID:Clang,GNU>>:-O3>
		$<$<CXX_COMPILER_ID:GNU>:-fno-gnu-unique> # reinitialization of a DSO via dlclose and dlopen

		# Security related
#		$<$<CXX_COMPILER_ID:Clang,GNU>:-Wnull-dereference>
#		$<$<CXX_COMPILER_ID:Clang,GNU>:-Wuninitialized>
#		$<$<CXX_COMPILER_ID:Clang,GNU>:-Wformat=2>
#		$<$<CXX_COMPILER_ID:Clang,GNU>:-Wformat-security>
#		$<$<CXX_COMPILER_ID:Clang,GNU>:-Wshift-overflow>
#		$<$<CXX_COMPILER_ID:Clang,GNU>:-Wstrict-overflow=5>
#		$<$<CXX_COMPILER_ID:GNU>:-Walloc-zero>
#		$<$<CXX_COMPILER_ID:GNU>:-Walloca>
#		$<$<CXX_COMPILER_ID:GNU>:-Wtrampolines>
#		$<$<CXX_COMPILER_ID:GNU>:-Wformat-signedness>

		# Bugs prevention
#		$<$<CXX_COMPILER_ID:Clang,GNU>:-Wdouble-promotion>
#		$<$<CXX_COMPILER_ID:Clang,GNU>:-Wfloat-equal>
#		$<$<CXX_COMPILER_ID:Clang,GNU>:-Wconversion>
#		$<$<CXX_COMPILER_ID:Clang,GNU>:-Wsign-conversion>
#		$<$<CXX_COMPILER_ID:Clang,GNU>:-Wsign-promo>
#		$<$<CXX_COMPILER_ID:Clang,GNU>:-Wimplicit-fallthrough>
#		$<$<CXX_COMPILER_ID:Clang,GNU>:-Wcast-qual>
#		$<$<CXX_COMPILER_ID:Clang,GNU>:-Wold-style-cast>
#		$<$<CXX_COMPILER_ID:Clang,GNU>:-Wdisabled-optimization>
#		$<$<CXX_COMPILER_ID:GNU>:-Wunsafe-loop-optimizations>
#		$<$<CXX_COMPILER_ID:GNU>:-Wno-aggressive-loop-optimizations>
#		$<$<CXX_COMPILER_ID:GNU>:-Wcast-align=strict>
#		$<$<CXX_COMPILER_ID:Clang>:-Wcast-align>

		# Code quality
#		$<$<CXX_COMPILER_ID:Clang,GNU>:-Wmissing-include-dirs>
#		$<$<CXX_COMPILER_ID:Clang,GNU>:-Woverloaded-virtual>
#		$<$<CXX_COMPILER_ID:Clang,GNU>:-Wundef>
#		$<$<CXX_COMPILER_ID:Clang,GNU>:-Wunused-macros>
#		$<$<CXX_COMPILER_ID:Clang,GNU>:-Wdate-time>
#		$<$<CXX_COMPILER_ID:Clang,GNU>:-Wno-endif-labels>
#		$<$<CXX_COMPILER_ID:Clang,GNU>:-Wunused-parameter>
#		$<$<CXX_COMPILER_ID:Clang,GNU>:-Wunused-variable>
#		$<$<CXX_COMPILER_ID:GNU>:-Wduplicated-branches>
#		$<$<CXX_COMPILER_ID:GNU>:-Wduplicated-cond>
#		$<$<CXX_COMPILER_ID:GNU>:-Wlogical-op>
#		$<$<CXX_COMPILER_ID:GNU>:-Wsuggest-final-types>
#		$<$<CXX_COMPILER_ID:GNU>:-Wsuggest-final-methods>
#		$<$<CXX_COMPILER_ID:GNU>:-Wstrict-null-sentinel>
#		$<$<CXX_COMPILER_ID:GNU>:-Wnoexcept>
#		$<$<CXX_COMPILER_ID:Clang>:-Wunreachable-code>
)

set_property(GLOBAL
	PROPERTY CONFIGURATION_COMMON_PRIVATE_LINK_OPTIONS
		$<$<CXX_COMPILER_ID:MSVC>:/WX> # treat linker-warnings as errors
		$<$<CXX_COMPILER_ID:MSVC>:/IGNORE:4099> # ignore missing PDB files
		$<$<AND:$<CXX_COMPILER_ID:MSVC>,$<CONFIG:Debug>>:/INCREMENTAL:NO> # disable incremental linking
		$<$<AND:$<CXX_COMPILER_ID:MSVC>,$<CONFIG:Release>>:/NODEFAULTLIB:MSVCRTD.lib> # ignore this lib
		#$<$<CXX_COMPILER_ID:MSVC>:/SUBSYSTEM:WINDOWS> # set per-target instead (CONSOLE vs WINDOWS)
		#$<$<AND:$<CXX_COMPILER_ID:MSVC>,$<CONFIG:Release>>:/DEBUG:FULL> # write pdb files to debug crash dumps
		#$<$<AND:$<CXX_COMPILER_ID:MSVC>,$<CONFIG:Release>>:/OPT:REF> # reactivate optimisation, gets deactivated with /debug flag (eliminate not referenced functions)
		#$<$<AND:$<CXX_COMPILER_ID:MSVC>,$<CONFIG:Release>>:/OPT:ICF> # reactivate optimisation, gets deactivated with /debug flag (remove redundant COMDATs)

		# The toolchain also uses -Wl,-O1. Let's not optimise at link time.
		$<$<AND:$<CONFIG:Debug>,$<STREQUAL:${CMAKE_SYSTEM_PROCESSOR},aarch64>>:-Wl,-O0>
)

# Macro to apply global compile/link settings to a target
macro(apply_global_settings target_name)
get_property(common_defs GLOBAL PROPERTY CONFIGURATION_COMMON_PRIVATE_COMPILE_DEFINITIONS)
get_property(common_opts GLOBAL PROPERTY CONFIGURATION_COMMON_PRIVATE_COMPILE_OPTIONS)
get_property(common_link GLOBAL PROPERTY CONFIGURATION_COMMON_PRIVATE_LINK_OPTIONS)

target_compile_definitions(${target_name} PRIVATE ${common_defs})
target_compile_options(${target_name} PRIVATE ${common_opts})
target_link_options(${target_name} PRIVATE ${common_link})
endmacro()
