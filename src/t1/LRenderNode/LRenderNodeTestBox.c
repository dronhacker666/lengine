#include "LRenderNodeTestBox.h"

static GLuint tex = 0;

#define MAKEFOURCC(ch0, ch1, ch2, ch3) \
  (GLuint)( \
    (((GLuint)(GLubyte)(ch3) << 24) & 0xFF000000) | \
    (((GLuint)(GLubyte)(ch2) << 16) & 0x00FF0000) | \
    (((GLuint)(GLubyte)(ch1) <<  8) & 0x0000FF00) | \
     ((GLuint)(GLubyte)(ch0)        & 0x000000FF) )

#define FOURCC_DXT1 MAKEFOURCC('D', 'X', 'T', '1')
#define FOURCC_DXT3 MAKEFOURCC('D', 'X', 'T', '3')
#define FOURCC_DXT5 MAKEFOURCC('D', 'X', 'T', '5')


GLuint loadDDS(const char * imagepath){
 
	unsigned char header[124];

	FILE *fp;

	/* try to open the file */
	fp = fopen(imagepath, "rb");
	if (fp == NULL)
	    return 0;

	/* verify the type of file */
	char filecode[4];
	fread(filecode, 1, 4, fp);
	if (strncmp(filecode, "DDS ", 4) != 0) {
	    fclose(fp);
	    return 0;
	}

	/* get the surface desc */
	fread(&header, 124, 1, fp); 

	unsigned int height      = *(unsigned int*)&(header[8 ]);
	unsigned int width       = *(unsigned int*)&(header[12]);
	unsigned int linearSize  = *(unsigned int*)&(header[16]);
	unsigned int mipMapCount = *(unsigned int*)&(header[24]);
	unsigned int fourCC      = *(unsigned int*)&(header[80]);

    unsigned char * buffer;
    unsigned int bufsize;
    /* how big is it going to be including all mipmaps? */
    bufsize = mipMapCount > 1 ? linearSize * 2 : linearSize;
    buffer = (unsigned char*)malloc(bufsize * sizeof(unsigned char));
    fread(buffer, 1, bufsize, fp);
    /* close the file pointer */
    fclose(fp);

    unsigned int components  = (fourCC == FOURCC_DXT1) ? 3 : 4;
    unsigned int format;
    switch(fourCC)
    {
    case FOURCC_DXT1:
        format = GL_COMPRESSED_RGBA_S3TC_DXT1_EXT;
        break;
    case FOURCC_DXT3:
        format = GL_COMPRESSED_RGBA_S3TC_DXT3_EXT;
        break;
    case FOURCC_DXT5:
        format = GL_COMPRESSED_RGBA_S3TC_DXT5_EXT;
        break;
    default:
        free(buffer);
        return 0;
    }

    // Create one OpenGL texture
    GLuint textureID;
    glGenTextures(1, &textureID);
 
    // "Bind" the newly created texture : all future texture functions will modify this texture
    glBindTexture(GL_TEXTURE_2D, textureID);

    unsigned int blockSize = (format == GL_COMPRESSED_RGBA_S3TC_DXT1_EXT) ? 8 : 16;
    unsigned int offset = 0;
 
    /* load the mipmaps */
    for (unsigned int level = 0; level < mipMapCount && (width || height); ++level)
    {
        unsigned int size = ((width+3)/4)*((height+3)/4)*blockSize;
        glCompressedTexImage2D(GL_TEXTURE_2D, level, format, width, height, 0, size, buffer + offset);
        offset += size;
        width  /= 2;
        height /= 2;
    }
    free(buffer); 
 
    return textureID;
}



LRenderNodeTestBox* LRenderNodeTestBox_create(LRenderNode* node)
{
	node->need_draw = true;
	
	LRenderNodeTestBox* box = calloc(1, sizeof(LRenderNodeTestBox));

	const float s = 50.0f;
	const float vertexes[][5] = {
		{-s, s, s,  0.0f,1.0f}, { s, s, s,  1.0f,1.0f}, { s,-s, s,  1.0f,0.0f}, {-s,-s, s,  0.0f,0.0f}, // front
		{ s, s,-s,  0.0f,1.0f}, {-s, s,-s,  1.0f,1.0f}, {-s,-s,-s,  1.0f,0.0f}, { s,-s,-s,  0.0f,0.0f}, // back
		{-s, s,-s,  0.0f,1.0f}, { s, s,-s,  1.0f,1.0f}, { s, s, s,  1.0f,0.0f}, {-s, s, s,  0.0f,0.0f}, // top
		{ s,-s,-s,  0.0f,1.0f}, {-s,-s,-s,  1.0f,1.0f}, {-s,-s, s,  1.0f,0.0f}, { s,-s, s,  0.0f,0.0f}, // bottom
		{-s, s,-s,  0.0f,1.0f}, {-s, s, s,  1.0f,1.0f}, {-s,-s, s,  1.0f,0.0f}, {-s,-s,-s,  0.0f,0.0f}, // left
		{ s, s, s,  0.0f,1.0f}, { s, s,-s,  1.0f,1.0f}, { s,-s,-s,  1.0f,0.0f}, { s,-s, s,  0.0f,0.0f}  // right
	};

	const uint32_t indices[] = {
		 0, 3, 1,  1, 3, 2, // front
		 4, 7, 5,  5, 7, 6, // back
		 8,11, 9,  9,11,10, // top
		12,15,13, 13,15,14, // bottom
		16,19,17, 17,19,18, // left
		20,23,21, 21,23,22  // right
	};

	glGenVertexArrays(1, &box->VAO);
	glBindVertexArray(box->VAO);

	glGenBuffers(2, box->VBO);

	glBindBuffer(GL_ARRAY_BUFFER, box->VBO[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexes), vertexes, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, box->VBO[1]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	GLint iPosition = glGetAttribLocation(shader_program, "iPosition");
	glVertexAttribPointer(iPosition, 3, GL_FLOAT, GL_FALSE, 5*sizeof(float), 0);
	glEnableVertexAttribArray(iPosition);

	GLint iTexCoord = glGetAttribLocation(shader_program, "iTexCoord");
	glVertexAttribPointer(iTexCoord, 2, GL_FLOAT, GL_FALSE, 5*sizeof(float), (const GLvoid*)(3*sizeof(float)) );
	glEnableVertexAttribArray(iTexCoord);

	glBindVertexArray(0);


	if(!tex){
		tex = loadDDS("wood.dds");
		if(!tex){
			printf("Error\n");
			exit(0);
		}
	}

	return box;
}

void LRenderNodeTestBox_free(LRenderNodeTestBox* box)
{
	free(box);
}

void LRenderNodeTestBox_draw(LRenderNodeTestBox* box)
{
	GLint program;
	glGetIntegerv(GL_CURRENT_PROGRAM, &program);

	float color[3] = {1.0, 0.0, 0.0};
	glUniform3fv(glGetUniformLocation(program, "uColor"), 1, (const GLfloat*)&color);


	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, tex);
	glUniform1i(glGetUniformLocation(program, "colorTex0") , 0);
	glActiveTexture(0);


	glBindVertexArray(box->VAO);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, NULL);
	glBindVertexArray(0);
}
