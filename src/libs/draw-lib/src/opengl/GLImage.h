/*
 * GLImage.h:
 *  A convenient OpenGL image wrapper
 */

#ifndef GLIMAGE_H_
#define GLIMAGE_H_

#include <string>

#include <lcommon/geometry.h>

#include <SDL.h>
#include <SDL_opengl.h>

#include "DrawOptions.h"

struct GLImage {
	GLImage() {
		texture = 0;
	}
	GLImage(SDL_RWops* rw_ops) {

	}
	GLImage(const std::string& filename) {
		texture = 0;
		initialize(filename);
	}
	GLImage(const Size& size, int type = GL_BGRA) {
		texture = 0;
		initialize(size, type);
	}
	~GLImage();

	void initialize(const std::string& filename);
	void initialize(const Size& size, int type = GL_BGRA) {
		image_from_bytes(size, NULL, type);
	}

	void subimage_from_bytes(const BBox& region, char* data,
			int type = GL_BGRA);
	void image_from_bytes(const Size& size, char* data, int type = GL_BGRA);

	void draw(const ldraw::DrawOptions& options, const PosF& pos);
	void draw(const PosF& pos) {
		draw(ldraw::DrawOptions(), pos);
	}

	int width, height;
	float texw, texh;
	GLuint texture;
};

#endif /* GLIMAGE_H_ */
