# Build file for the Kinect Subsystem
include_directories("${SDL_INCLUDE_DIR}")

set(SOURCE_FILES
	ray_vec3.c
	ray_mat3.c
	ray_mat4.c
	ray_quat.c
	ray_ray.c
	ray_sphere.c
	ray_shape.c
	ray_trace.c
	)

set(HEADER_FILES
	ray_vec3.h
	ray_mat3.h
	ray_mat4.h
	ray_quat.h
	)

add_library(Raytracer SHARED ${SOURCE_FILES} ${HEADER_FILES} )
set_target_properties(Raytracer PROPERTIES LINKER_LANGUAGE C)

add_executable(test main.c)
target_link_libraries (test ${SDL_LIB} Raytracer)

install(TARGETS Raytracer
		RUNTIME DESTINATION ${INSTALL_RUNTIMES_TO}
		LIBRARY DESTINATION ${INSTALL_LIBS_TO}
		ARCHIVE DESTINATION ${INSTALL_LIBS_TO})

install(TARGETS test
		RUNTIME DESTINATION ${INSTALL_RUNTIMES_TO}
		LIBRARY DESTINATION ${INSTALL_LIBS_TO}
		ARCHIVE DESTINATION ${INSTALL_LIBS_TO})
