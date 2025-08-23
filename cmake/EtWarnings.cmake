# cmake/EtWarnings.cmake
include_guard(GLOBAL)

# Toggle: treat warnings as errors
option(ET_WARNINGS_AS_ERRORS "Treat warnings as errors" OFF)

# Optional: make -Wconversion opt-in if you find it too strict
option(ET_WARNINGS_ENABLE_CONVERSION "Enable -Wconversion on GCC/Clang" ON)

# Create a single interface target that carries warning flags
if(NOT TARGET et_warnings)
  add_library(et_warnings INTERFACE)

  if(MSVC)
    target_compile_options(et_warnings INTERFACE
      /W4           # high warnings
      /permissive-  # stricter standard conformance
      /EHsc         # C++ exceptions semantics
      $<$<BOOL:${ET_WARNINGS_AS_ERRORS}>:/WX>
    )
  else()
    # Base warnings
    target_compile_options(et_warnings INTERFACE
      -Wall -Wextra -Wpedantic
      $<$<BOOL:${ET_WARNINGS_ENABLE_CONVERSION}>:-Wconversion>
      $<$<BOOL:${ET_WARNINGS_AS_ERRORS}>:-Werror>
    )
  endif()
endif()

# Expose the target name to consumers (handy in subdirs)
set(ET_WARNINGS_TARGET et_warnings CACHE INTERNAL "Interface target with warning flags")
