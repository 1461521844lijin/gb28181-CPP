if(TARGET gflags::gflags AND NOT TARGET gflags)
    add_library(gflags INTERFACE IMPORTED)
    set_property(TARGET gflags PROPERTY INTERFACE_LINK_LIBRARIES gflags::gflags)
endif()
