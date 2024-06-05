# Find the native pqxx includes and library

find_path(PQXX_INCLUDE_DIR pqxx/pqxx)
find_library(PQXX_LIBRARY pqxx)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(PQXX DEFAULT_MSG PQXX_INCLUDE_DIR PQXX_LIBRARY)

if(PQXX_FOUND)
  set(PQXX_LIBRARIES ${PQXX_LIBRARY})
  set(PQXX_INCLUDE_DIRS ${PQXX_INCLUDE_DIR})
endif()
