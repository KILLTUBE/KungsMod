#include "dock_quakeshaders.h"
#include "../imgui/include_imgui.h"
#include <client/client.h>

#include "../tr_local.h"
#include "../imgui_docks/dock_console.h"
#include "../imgui_openjk/gluecode.h"

DockQuakeShaders::DockQuakeShaders() {
}

const char *DockQuakeShaders::label() {
	return "QuakeShaders";
}

CCALL int shader_stage_set_image(int shaderid, int stageid, int imageid) {
	shaderStage_t *stage;
	stage = tr.shaders[shaderid]->stages[stageid];
	if (stage == NULL) {
		imgui_log("shader_stage_set_image> tr.shaders[%d]->stages[%d] == NULL (imageid=%d)\n", shaderid, stageid, imageid);
		return 0;
	}
	stage->bundle[0].image[0] = tr.images[imageid];
	return 1;
}

CCALL int getImageID(image_t *image) {
	int imageid = 0;
	for (int i=0; i<2048; i++)
		if (tr.images[i] == image) {
			imageid = i;
			break;
		}
	return imageid;
}
CCALL int shaderCreateStage(int shaderID, int stageID) {
	//shader_t *shader = tr.shaders[shaderID];
	//if (shader->stages[stageID] != NULL) {
	//	return 0; // stage already exists
	//}
	//shaderStage_t *stage;
	//stage = (shaderStage_t *) Hunk_Alloc( sizeof( shaderStage_t ), h_low );
	//shader->stages[stageID] = stage;
	//// some sane default values so the model shows correctly
	//stage->glslShaderGroup = tr.lightallShader;
	//stage->stateBits = 256;
	//stage->rgbGen = (colorGen_t)CGEN_IDENTITY_LIGHTING;
	return 1;
}

const char *toString(stageType_t stageType) {
	switch (stageType) {
		/*case ST_COLORMAP:*/
		case ST_DIFFUSEMAP:		   return "ST_DIFFUSEMAP"; // same as ST_COLORMAP, both 0
		case ST_NORMALMAP:		   return "ST_NORMALMAP";
		case ST_NORMALPARALLAXMAP: return "ST_NORMALPARALLAXMAP";
		case ST_SPECULARMAP:	   return "ST_SPECULARMAP";
		case ST_GLSL:			   return "ST_GLSL";
	}
	return "unknown stageType enum";
}


namespace ImGui {
	bool Enum(colorGen_t *ptrValue) {
		char *names[] = {
			"CGEN_BAD,                                                                                         ",
			"CGEN_IDENTITY_LIGHTING,	// tr.identityLight                                                    ",
			"CGEN_IDENTITY,			// always (1,1,1,1)                                                        ",
			"CGEN_ENTITY,			// grabbed from entity's modulate field                                    ",
			"CGEN_ONE_MINUS_ENTITY,	// grabbed from 1 - entity.modulate                                        ",
			"CGEN_EXACT_VERTEX,		// tess.vertexColors                                                       ",
			"CGEN_VERTEX,			// tess.vertexColors * tr.identityLight                                    ",
			"CGEN_EXACT_VERTEX_LIT,	// like CGEN_EXACT_VERTEX but takes a light direction from the lightgrid   ",
			"CGEN_VERTEX_LIT,		// like CGEN_VERTEX but takes a light direction from the lightgrid         ",
			"CGEN_ONE_MINUS_VERTEX,                                                                            ",
			"CGEN_WAVEFORM,			// programmatically generated                                              ",
			"CGEN_LIGHTING_DIFFUSE,                                                                            ",
			"CGEN_LIGHTING_DIFFUSE_ENTITY, // diffuse lighting * entity                                        ",
			"CGEN_FOG,				// standard fog                                                            ",
			"CGEN_CONST,				// fixed color                                                         ",
			"CGEN_LIGHTMAPSTYLE,		// lightmap style                                                      "
		};
		int bla = *ptrValue;
		bool ret = ImGui::Combo("Status",  (int *)&bla, names, 15);
		if (ret) {
			*ptrValue = (colorGen_t)bla;
		}
		return ret;
	}
}

void imgui_stage(shaderStage_t *stage) {
	

	if (ImGui::Button("ST_DIFFUSEMAP"))        stage->type = ST_DIFFUSEMAP;
	if (ImGui::Button("ST_NORMALMAP"))         stage->type = ST_NORMALMAP;
	if (ImGui::Button("ST_NORMALPARALLAXMAP")) stage->type = ST_NORMALPARALLAXMAP;
	if (ImGui::Button("ST_SPECULARMAP"))       stage->type = ST_SPECULARMAP;
	if (ImGui::Button("ST_GLSL"))              stage->type = ST_GLSL;
					
	ImGui::Checkbox("isDetail", &stage->isDetail);

	ImGui::SameLine();
	ImGui::Checkbox("isActive", &stage->active);
	ImGui::DragFloat4("specularScale", stage->specularScale);
	ImGui::DragFloat4("normalScale", stage->normalScale);



	if (stage->glslShaderGroup) {
		ImGui::Text("current glslShaderGroup: %s", stage->glslShaderGroup->name);
	}
				
	/*
	shaderProgram_t genericShader[GENERICDEF_COUNT];
	shaderProgram_t textureColorShader;
	shaderProgram_t fogShader[FOGDEF_COUNT];
	shaderProgram_t dlightShader[DLIGHTDEF_COUNT];
	shaderProgram_t lightallShader[LIGHTDEF_COUNT];
	shaderProgram_t shadowmapShader;
	shaderProgram_t pshadowShader;
	shaderProgram_t down4xShader;
	shaderProgram_t bokehShader;
	shaderProgram_t tonemapShader;
	shaderProgram_t calclevels4xShader[2];
	shaderProgram_t shadowmaskShader;
	shaderProgram_t ssaoShader;
	shaderProgram_t depthBlurShader[4];
	shaderProgram_t testcubeShader;
	*/
	if (ImGui::Button("glslShaderGroup = genericShader"     )) { stage->glslShaderGroup =  tr.genericShader;       }
	if (ImGui::Button("glslShaderGroup = textureColorShader")) { stage->glslShaderGroup = &tr.textureColorShader;  }
	if (ImGui::Button("glslShaderGroup = fogShader"         )) { stage->glslShaderGroup =  tr.fogShader;           }
	if (ImGui::Button("glslShaderGroup = dlightShader"      )) { stage->glslShaderGroup =  tr.dlightShader;        }
	if (ImGui::Button("glslShaderGroup = lightallShader"    )) { stage->glslShaderGroup =  tr.lightallShader;      }
	if (ImGui::Button("glslShaderGroup = shadowmapShader"   )) { stage->glslShaderGroup = &tr.shadowmapShader;     }
	if (ImGui::Button("glslShaderGroup = pshadowShader"     )) { stage->glslShaderGroup = &tr.pshadowShader;       }
	if (ImGui::Button("glslShaderGroup = down4xShader"      )) { stage->glslShaderGroup = &tr.down4xShader;        }
	if (ImGui::Button("glslShaderGroup = bokehShader"       )) { stage->glslShaderGroup = &tr.bokehShader;         }
	if (ImGui::Button("glslShaderGroup = tonemapShader"     )) { stage->glslShaderGroup = &tr.tonemapShader;       }
	if (ImGui::Button("glslShaderGroup = calclevels4xShader")) { stage->glslShaderGroup =  tr.calclevels4xShader;  }
	if (ImGui::Button("glslShaderGroup = shadowmaskShader"  )) { stage->glslShaderGroup = &tr.shadowmaskShader;    }
	if (ImGui::Button("glslShaderGroup = ssaoShader"        )) { stage->glslShaderGroup = &tr.ssaoShader;          }
	if (ImGui::Button("glslShaderGroup = depthBlurShader"   )) { stage->glslShaderGroup =  tr.depthBlurShader;     }
	if (ImGui::Button("glslShaderGroup = testcubeShader"    )) { stage->glslShaderGroup = &tr.testcubeShader;      }

	/*
	LIGHTDEF_USE_LIGHTMAP        = 0x0001,
	LIGHTDEF_USE_LIGHT_VECTOR    = 0x0002,
	LIGHTDEF_USE_LIGHT_VERTEX    = 0x0003,
	LIGHTDEF_LIGHTTYPE_MASK      = 0x0003,
	LIGHTDEF_ENTITY              = 0x0004,
	LIGHTDEF_USE_TCGEN_AND_TCMOD = 0x0008,
	LIGHTDEF_USE_PARALLAXMAP     = 0x0010,
	LIGHTDEF_USE_SHADOWMAP       = 0x0020,
	LIGHTDEF_ALL                 = 0x003F,
	LIGHTDEF_COUNT               = 0x0040				
	*/
	ImGui::DragInt("defs", &stage->glslShaderIndex);


	int tmpStateBits = stage->stateBits;
	ImGui::DragInt("stateBits", &tmpStateBits);
	stage->stateBits = tmpStateBits;

	int rgbGen = stage->rgbGen;
	ImGui::DragInt("rgbGen", &rgbGen);
	stage->rgbGen = (colorGen_t)rgbGen;

	ImGui::Enum(&stage->rgbGen);

	int defs = stage->glslShaderIndex;
	ImGui::Text("LIGHTDEF_USE_LIGHTMAP        = %d", defs & LIGHTDEF_USE_LIGHTMAP       );
	ImGui::Text("LIGHTDEF_USE_LIGHT_VECTOR    = %d", defs & LIGHTDEF_USE_LIGHT_VECTOR   );
	ImGui::Text("LIGHTDEF_USE_LIGHT_VERTEX    = %d", defs & LIGHTDEF_USE_LIGHT_VERTEX   );
	ImGui::Text("LIGHTDEF_LIGHTTYPE_MASK      = %d", defs & LIGHTDEF_LIGHTTYPE_MASK     );
	//ImGui::Text("LIGHTDEF_ENTITY              = %d", defs & LIGHTDEF_ENTITY             );
	ImGui::Text("LIGHTDEF_USE_TCGEN_AND_TCMOD = %d", defs & LIGHTDEF_USE_TCGEN_AND_TCMOD);
	ImGui::Text("LIGHTDEF_USE_PARALLAXMAP     = %d", defs & LIGHTDEF_USE_PARALLAXMAP    );
	ImGui::Text("LIGHTDEF_USE_SHADOWMAP       = %d", defs & LIGHTDEF_USE_SHADOWMAP      );
	ImGui::Text("LIGHTDEF_ALL                 = %d", defs & LIGHTDEF_ALL                );
	ImGui::Text("LIGHTDEF_COUNT               = %d", defs & LIGHTDEF_COUNT              );
				
	//ImGui::DragFloat("maila0", stage->maila + 0);
	//ImGui::DragFloat("maila1", stage->maila + 1);
	//ImGui::DragFloat("maila2", stage->maila + 2);
	//ImGui::DragFloat("maila3", stage->maila + 3);

	//if (ImGui::CollapsingHeader("Bundles")) {

		for (int bundle_id=0; bundle_id < NUM_TEXTURE_BUNDLES; bundle_id++) {
			textureBundle_t *bundle = stage->bundle + bundle_id;

			char tmp[512];
			snprintf(tmp, sizeof(tmp), "bundle[%d]: numTexMods=%d", bundle_id, bundle->numTexMods);
			if (ImGui::CollapsingHeader(tmp)) {

				for (int image_id=0; image_id<8; image_id++) {
					image_t *img = bundle->image[image_id];
					ImGui::Text("Img[%d]: %p", image_id, img);
					ImGui::PushID(((int)bundle)+image_id);
					if (img) {

						//ImGui::Text("image id: %d", imageid);
						int imageid = getImageID(img);
						if (ImGui::DragInt("id", &imageid)) {
							const int maxImages = sizeof(tr.images)/sizeof(image_t *);
							if (imageid >=0 && imageid < maxImages)
								bundle->image[image_id] = tr.images[imageid];
						}

						ImGui::Image((ImTextureID)img->texnum, ImVec2(256,256));
						
						if (ImGui::Button("image = NULL")) {
							bundle->image[image_id] = NULL;
						}
					} else {
						if (ImGui::Button("Assign Image")) {
							bundle->image[image_id] = tr.images[0];
						}
					}
					ImGui::PopID();

				}
			}	
		}
	//} // if() bundles

	/*
	#define GLS_SRCBLEND_ZERO						0x00000001
	#define GLS_SRCBLEND_ONE						0x00000002
	#define GLS_SRCBLEND_DST_COLOR					0x00000003
	#define GLS_SRCBLEND_ONE_MINUS_DST_COLOR		0x00000004
	#define GLS_SRCBLEND_SRC_ALPHA					0x00000005
	#define GLS_SRCBLEND_ONE_MINUS_SRC_ALPHA		0x00000006
	#define GLS_SRCBLEND_DST_ALPHA					0x00000007
	#define GLS_SRCBLEND_ONE_MINUS_DST_ALPHA		0x00000008
	#define GLS_SRCBLEND_ALPHA_SATURATE				0x00000009
	#define		GLS_SRCBLEND_BITS					0x0000000f

	#define GLS_DSTBLEND_ZERO						0x00000010
	#define GLS_DSTBLEND_ONE						0x00000020
	#define GLS_DSTBLEND_SRC_COLOR					0x00000030
	#define GLS_DSTBLEND_ONE_MINUS_SRC_COLOR		0x00000040
	#define GLS_DSTBLEND_SRC_ALPHA					0x00000050
	#define GLS_DSTBLEND_ONE_MINUS_SRC_ALPHA		0x00000060
	#define GLS_DSTBLEND_DST_ALPHA					0x00000070
	#define GLS_DSTBLEND_ONE_MINUS_DST_ALPHA		0x00000080
	#define		GLS_DSTBLEND_BITS					0x000000f0
	*/
				
	int src = stage->stateBits & GLS_SRCBLEND_BITS;
	int dst = stage->stateBits & GLS_DSTBLEND_BITS;
					
	int cc = 0;
#define PUSHCOLOR_IF(condition) if (condition) { cc=1; ImGui::PushStyleColor(0, ImVec4(0,0,1,1)); }
#define POPCOLOR  if (cc) { cc=0; ImGui::PopStyleColor(); }
				
	ImGui::Text("SOURCE:");
	ImGui::PushID(GLS_SRCBLEND_BITS);
	ImGui::SameLine(); PUSHCOLOR_IF(src == GLS_SRCBLEND_ZERO               ) if (ImGui::Button("ZERO")                ){ src = GLS_SRCBLEND_ZERO;                } POPCOLOR
	ImGui::SameLine(); PUSHCOLOR_IF(src == GLS_SRCBLEND_ONE                ) if (ImGui::Button("ONE")                 ){ src = GLS_SRCBLEND_ONE;                 } POPCOLOR
	ImGui::SameLine(); PUSHCOLOR_IF(src == GLS_SRCBLEND_DST_COLOR          ) if (ImGui::Button("DST_COLOR")           ){ src = GLS_SRCBLEND_DST_COLOR;           } POPCOLOR
	ImGui::SameLine(); PUSHCOLOR_IF(src == GLS_SRCBLEND_ONE_MINUS_DST_COLOR) if (ImGui::Button("ONE_MINUS_DST_COLOR") ){ src = GLS_SRCBLEND_ONE_MINUS_DST_COLOR; } POPCOLOR
	ImGui::SameLine(); PUSHCOLOR_IF(src == GLS_SRCBLEND_SRC_ALPHA          ) if (ImGui::Button("SRC_ALPHA")           ){ src = GLS_SRCBLEND_SRC_ALPHA;           } POPCOLOR
	ImGui::SameLine(); PUSHCOLOR_IF(src == GLS_SRCBLEND_ONE_MINUS_SRC_ALPHA) if (ImGui::Button("ONE_MINUS_SRC_ALPHA") ){ src = GLS_SRCBLEND_ONE_MINUS_SRC_ALPHA; } POPCOLOR
	ImGui::SameLine(); PUSHCOLOR_IF(src == GLS_SRCBLEND_DST_ALPHA          ) if (ImGui::Button("DST_ALPHA")           ){ src = GLS_SRCBLEND_DST_ALPHA;           } POPCOLOR
	ImGui::SameLine(); PUSHCOLOR_IF(src == GLS_SRCBLEND_ONE_MINUS_DST_ALPHA) if (ImGui::Button("ONE_MINUS_DST_ALPHA") ){ src = GLS_SRCBLEND_ONE_MINUS_DST_ALPHA; } POPCOLOR
	ImGui::SameLine(); PUSHCOLOR_IF(src == GLS_SRCBLEND_ALPHA_SATURATE     ) if (ImGui::Button("ALPHA_SATURATE")      ){ src = GLS_SRCBLEND_ALPHA_SATURATE;      } POPCOLOR
	ImGui::PopID();

	ImGui::Text("DST:");
	ImGui::PushID(GLS_DSTBLEND_BITS);
	ImGui::SameLine(); PUSHCOLOR_IF(dst == GLS_DSTBLEND_ZERO               ) if (ImGui::Button("ZERO"               )) { dst = GLS_DSTBLEND_ZERO;                } POPCOLOR
	ImGui::SameLine(); PUSHCOLOR_IF(dst == GLS_DSTBLEND_ONE                ) if (ImGui::Button("ONE"                )) { dst = GLS_DSTBLEND_ONE;                 } POPCOLOR
	ImGui::SameLine(); PUSHCOLOR_IF(dst == GLS_DSTBLEND_SRC_COLOR          ) if (ImGui::Button("SRC_COLOR"          )) { dst = GLS_DSTBLEND_SRC_COLOR;           } POPCOLOR
	ImGui::SameLine(); PUSHCOLOR_IF(dst == GLS_DSTBLEND_ONE_MINUS_SRC_COLOR) if (ImGui::Button("ONE_MINUS_SRC_COLOR")) { dst = GLS_DSTBLEND_ONE_MINUS_SRC_COLOR; } POPCOLOR
	ImGui::SameLine(); PUSHCOLOR_IF(dst == GLS_DSTBLEND_SRC_ALPHA          ) if (ImGui::Button("SRC_ALPHA"          )) { dst = GLS_DSTBLEND_SRC_ALPHA;           } POPCOLOR
	ImGui::SameLine(); PUSHCOLOR_IF(dst == GLS_DSTBLEND_ONE_MINUS_SRC_ALPHA) if (ImGui::Button("ONE_MINUS_SRC_ALPHA")) { dst = GLS_DSTBLEND_ONE_MINUS_SRC_ALPHA; } POPCOLOR
	ImGui::SameLine(); PUSHCOLOR_IF(dst == GLS_DSTBLEND_DST_ALPHA          ) if (ImGui::Button("DST_ALPHA"          )) { dst = GLS_DSTBLEND_DST_ALPHA;           } POPCOLOR
	ImGui::SameLine(); PUSHCOLOR_IF(dst == GLS_DSTBLEND_ONE_MINUS_DST_ALPHA) if (ImGui::Button("ONE_MINUS_DST_ALPHA")) { dst = GLS_DSTBLEND_ONE_MINUS_DST_ALPHA; } POPCOLOR
	ImGui::PopID();

	


#undef PUSHCOLOR
#undef POPCOLOR

	stage->stateBits &= ~GLS_SRCBLEND_BITS; // remove src bitmask
	stage->stateBits |= src; // and set old one or if clicked, the new one

	stage->stateBits &= ~GLS_DSTBLEND_BITS; // remove dst bitmask
	stage->stateBits |= dst; // and set old one or if clicked, the new one

	if (ImGui::Button("REMOVE SRC/DST")) {
		stage->stateBits &= ~GLS_SRCBLEND_BITS;
		stage->stateBits &= ~GLS_DSTBLEND_BITS;
	}
	if (ImGui::Button("ADD SRC/DST")) {
		// just set some src/dst, my ati driver crashes when there is a src with not dst :S
		stage->stateBits &= ~GLS_SRCBLEND_BITS; // remove src bitmask
		stage->stateBits |= GLS_SRCBLEND_ONE;
		stage->stateBits &= ~GLS_DSTBLEND_BITS; // remove dst bitmask
		stage->stateBits |= GLS_DSTBLEND_ONE; 
	}

}

void DockQuakeShaders::imgui() {

	for (int i=0; i<tr.numShaders; i++) {
		shader_t *shader = tr.shaders[i];

		char headertext[512];
		sprintf(headertext, "shader[%d] %s", i, shader->name);
		
		ImGui::PushID(shader);
		if (ImGui::CollapsingHeader(headertext)) {

			
			if (ImGui::Button("Add new Stage")) {
#if 0
				for (int stage_id=0; stage_id<8; stage_id++) {
					shaderStage_t *stage = shader->stages[stage_id];
					if (stage == NULL) {
						

						stage = (shaderStage_t *) Hunk_Alloc( sizeof( shaderStage_t ), h_low );
						shader->stages[stage_id] = stage;

						//for ( int b = 0 ; b < NUM_TEXTURE_BUNDLES ; b++ ) {
						//	int size = stage->bundle[b].numTexMods * sizeof( texModInfo_t );
						//	newShader->stages[i]->bundle[b].texMods = Hunk_Alloc( size, h_low );
						//	Com_Memcpy( newShader->stages[i]->bundle[b].texMods, stages[i].bundle[b].texMods, size );
						//}
						break;
					}
				}
#endif
			}

			//ImGui::

			for (int stage_id=0; stage_id<8; stage_id++) {
				shaderStage_t *stage = shader->stages[stage_id];
				if (stage == NULL)
					break;



				ImGui::PushID(stage);

				char tmp[512];
				snprintf(tmp, sizeof(tmp), "stage_id=%d type=%s",
					stage_id,
					toString(stage->type)
				);

				if (ImGui::CollapsingHeader(tmp)) {
					imgui_stage(stage);
				}

				
				ImGui::PopID();
			}
		}
		ImGui::PopID();
	}
	
		
}