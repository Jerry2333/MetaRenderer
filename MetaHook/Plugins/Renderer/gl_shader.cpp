#include "gl_local.h"
#include "gl_shader.h"

glshader_t shaders[MAX_SHADERS];
int numshaders;

void R_InitShaders(void)
{
	numshaders = 0;
}

qboolean GL_IsShaderError(GLuint shader, const char *filename)
{
	char compiler_log[1000];
	int blen;

	qglGetShaderiv(shader, GL_INFO_LOG_LENGTH , &blen);
	if(blen > 1)
	{
		int slen;
		qglGetInfoLogARB(shader, 1000, &slen, compiler_log);
		if(!strstr(compiler_log, "error"))
		{
			gEngfuncs.Con_Printf("Shader %s compiled with warning: %s\n", filename, compiler_log);
			return false;
		}
		//gEngfuncs.Con_Printf("Shader %s compiled with error: %s\n", filename, compiler_log);
		Sys_ErrorEx("Shader %s compiled with error: %s\n", filename, compiler_log);
		return true;
	}

	return false;
}

GLuint R_CompileShader(const char *vscode, const char *fscode, const char *vsfile, const char *fsfile)
{
	GLuint vs = qglCreateShaderObjectARB(GL_VERTEX_SHADER_ARB);
	qglShaderSourceARB(vs, 1, &vscode, NULL);
	qglCompileShaderARB(vs);
	if(GL_IsShaderError(vs, vsfile))
	{
		qglDeleteObjectARB(vs);
		return 0;
	}

	GLuint fs = qglCreateShaderObjectARB(GL_FRAGMENT_SHADER_ARB);
	qglShaderSourceARB(fs, 1, &fscode, NULL);
	qglCompileShaderARB(fs);
	if(GL_IsShaderError(fs, fsfile))
	{
		qglDeleteObjectARB(fs);
		return 0;
	}	

	GLuint program = qglCreateProgramObjectARB();
	qglAttachObjectARB(program, vs);
	qglAttachObjectARB(program, fs);
	qglLinkProgramARB(program);

	shaders[numshaders].program = program;
	shaders[numshaders].vs = vs;
	shaders[numshaders].fs = fs;
	numshaders ++;

	return program;
}

void GL_UseProgram(GLuint program)
{
	qglUseProgramObjectARB(program);
}

void GL_EndProgram(void)
{
	qglUseProgramObjectARB(0);
}

GLuint GL_GetUniformLoc(GLuint program, const char *name)
{
	return qglGetUniformLocationARB(program, name);
}

GLuint GL_GetAttribLoc(GLuint program, const char *name)
{
	return qglGetAttribLocationARB(program, name);
}

void GL_Uniform1i(GLuint loc, int v0)
{
	qglUniform1iARB(loc, v0);
}

void GL_Uniform2i(GLuint loc, int v0, int v1)
{
	qglUniform2iARB(loc, v0, v1);
}

void GL_Uniform3i(GLuint loc, int v0, int v1, int v2)
{
	qglUniform3iARB(loc, v0, v1, v2);
}

void GL_Uniform4i(GLuint loc, int v0, int v1, int v2, int v3)
{
	qglUniform4iARB(loc, v0, v1, v2, v3);
}

void GL_Uniform1f(GLuint loc, float v0)
{
	qglUniform1fARB(loc, v0);
}

void GL_Uniform2f(GLuint loc, float v0, float v1)
{
	qglUniform2fARB(loc, v0, v1);
}

void GL_Uniform3f(GLuint loc, float v0, float v1, float v2)
{
	qglUniform3fARB(loc, v0, v1, v2);
}

void GL_Uniform4f(GLuint loc, float v0, int v1, int v2, int v3)
{
	qglUniform4fARB(loc, v0, v1, v2, v3);
}

void GL_VertexAttrib3f(GLuint index, float x, float y, float z)
{
	qglVertexAttrib3f(index, x, y, z);
}

void GL_VertexAttrib3fv(GLuint index, float *v)
{
	qglVertexAttrib3fv(index, v);
}

void GL_MultiTexCoord2f(GLenum target, float s, float t)
{
	qglMultiTexCoord2fARB(target, s, t);
}

void GL_MultiTexCoord3f(GLenum target, float s, float t, float r)
{
	qglMultiTexCoord3fARB(target, s, t, r);
}