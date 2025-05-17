// Generated code

#if !DEBUG
#include "Shaders/ShaderProvider/ShaderProvider.h"
const string ShaderProvider::UnpackCode(const uint32_t& h) {
switch (h) {
case 1939412094: return "#version 460 core\nin vec2 fragmentTextureCoords;uniform sampler2D dataTexture;out vec4 color;void main(){color=texture(dataTexture,fragmentTextureCoords);}";
case 776390504: return "#version 460 core\nin vec4 position;in vec2 vertexTextureCoords;out vec2 fragmentTextureCoords;void main(){gl_Position=position;fragmentTextureCoords=vertexTextureCoords;}";
case 4100711277: return "#version 460 core\nlayout(local_size_x=8,local_size_y=8,local_size_z=1)in;uniform ivec2 size;uniform dvec2 scale;uniform dvec2 pan;uniform uint maxIterations;layout(rgba32f)restrict uniform image2D dataTexture;dvec2 a(ivec2 e){dvec2 f=size*scale;dvec2 h=e/f;dvec2 j=h+pan;return(j*4)-(2/scale);}int c(dvec2 k){int i=0;double x=0;double y=0;double l=0;double m=0;while(l+m<4&&i<maxIterations){y=2*x*y+k.y;x=l-m+k.x;l=x*x;m=y*y;i++;}return i;}vec4 d(double i){double r=9*(1-i)*i*i*i;double g=15*(1-i)*(1-i)*i*i;double b=8.5*(1-i)*(1-i)*(1-i)*i;return vec4(r,g,b,1);}void main(){ivec2 n=ivec2(gl_GlobalInvocationID.xy);if(n.x>=size.x||n.y>=size.y)return;dvec2 o=a(n);int p=c(o);double q=p/double(maxIterations);imageStore(dataTexture,n,d(q));}";
default: return ""; }}
#endif
