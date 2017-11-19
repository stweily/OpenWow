#pragma once

#include "GPUTimer.h"

const uint32 MaxNumVertexLayouts = 64;
const uint32 MaxComputeImages = 8;

// ---------------------------------------------------------
// General
// ---------------------------------------------------------

template<class T>
class R_Objects
{
public:
	uint32 add(const T &obj)
	{
		/*if (!_freeList.empty())
		{
			uint32 index = _freeList.back();
			_freeList.pop_back();
			_objects[index] = obj;
			return index + 1;
		}
		else
		{*/
			_objects.push_back(obj);
			return (uint32)_objects.size();
		/*}*/
	}

	void remove(uint32 handle)
	{
		assert1(handle > 0 && handle <= _objects.size());
		assert1(find(_freeList.begin(), _freeList.end(), handle - 1) == _freeList.end());

		_objects[handle - 1] = T();  // Destruct and replace with default object
		_freeList.push_back(handle - 1);
	}

	T& getRef(uint32 handle)
	{
		assert1(handle > 0 && handle <= _objects.size());

		return _objects[handle - 1];
	}

private:
	vector< T >       _objects;
	vector< uint32 >  _freeList;
};





#include "RenderEnums.h"
#include "RenderTypes.h"

// =================================================================================================

class RenderDevice
{
public:
	RenderDevice();
	~RenderDevice();

	void initStates();
	bool init();

	// Vertex layouts
	uint32 registerVertexLayout(uint32 numAttribs, R_VertexLayoutAttrib *attribs);

	// Rendering
	void beginRendering();

    // Geometry
    R_GeometryInfo* beginCreatingGeometry(uint32 vlObj);
	void finishCreatingGeometry(R_GeometryInfo* geoObj);
	void setGeomVertexParams(R_GeometryInfo* geoObj, R_Buffer* vbo, R_DataType type, uint32 offset, uint32 stride, bool needNorm = false);
	void setGeomIndexParams(R_GeometryInfo* geoObj, R_Buffer* indBuf, R_IndexFormat format);
	void destroyGeometry(R_GeometryInfo*& geoObj, bool destroyBindedBuffers);

	// Buffers
    R_Buffer* createVertexBuffer(uint32 size, const void *data, bool _isDynamic = true);
    R_Buffer* createIndexBuffer(uint32 size, const void *data, bool _isDynamic = true);
    R_TextureBuffer* createTextureBuffer(R_TextureFormats::List format, uint32 bufSize, const void *data, bool _isDynamic = true);
    R_Buffer* createShaderStorageBuffer(uint32 size, const void *data, bool _isDynamic = true);
	void destroyBuffer(R_Buffer*& bufObj);
	void destroyTextureBuffer(R_TextureBuffer*& bufObj);
	void updateBufferData(R_Buffer* bufObj, uint32 offset, uint32 size, const void *data);
	void* mapBuffer(R_Buffer* bufObj, uint32 offset, uint32 size, R_BufferMappingTypes mapType);
	void unmapBuffer(R_Buffer* bufObj);
	uint32 getBufferMem() const
	{
		return _bufferMem;
	}

	// Textures
	uint32 calcTextureSize(R_TextureFormats::List format, int width, int height, int depth);
    R_Texture* createTexture(R_TextureTypes::List type, int width, int height, int depth, R_TextureFormats::List format, bool hasMips, bool genMips, bool compress, bool sRGB);
	void uploadTextureData(R_Texture* texObj, int slice, int mipLevel, const void *pixels);
	void destroyTexture(R_Texture*& texObj);
	bool getTextureData(R_Texture* texObj, int slice, int mipLevel, void *buffer);
	void bindImageToTexture(R_Texture* texObj, void* eglImage);
	uint32 getTextureMem() const
	{
		return _textureMem;
	}

	// Shaders
    R_Shader* createShader(const char *vertexShaderSrc, const char *fragmentShaderSrc, const char *geometryShaderSrc, const char *tessControlShaderSrc, const char *tessEvaluationShaderSrc, const char *computeShaderSrc);
	void destroyShader(R_Shader*& shaderId);
	void bindShader(R_Shader* shaderId);
	int getShaderConstLoc(R_Shader* shaderId, const char *name);
	int getShaderSamplerLoc(R_Shader* shaderId, const char *name);
	int getShaderBufferLoc(R_Shader* shaderId, const char *name);
	void setShaderConst(int loc, R_ShaderConstType type, const void *values, uint32 count = 1);
	void setShaderSampler(int loc, uint32 texUnit);
	void runComputeShader(R_Shader* shaderId, uint32 xDim, uint32 yDim, uint32 zDim);
	string getShaderLog() const
	{
		return _shaderLog;
	}

	// Renderbuffers
	R_RenderBuffer* createRenderBuffer(uint32 width, uint32 height, R_TextureFormats::List format, bool depth, uint32 numColBufs, uint32 samples);
	void destroyRenderBuffer(R_RenderBuffer*& rbObj);
    R_Texture* getRenderBufferTex(R_RenderBuffer* rbObj, uint32 bufIndex);
	void setRenderBuffer(R_RenderBuffer* rbObj);
	bool getRenderBufferData(R_RenderBuffer* rbObj, int bufIndex, int *width, int *height, int *compCount, void *dataBuffer, int bufferSize);
	void getRenderBufferDimensions(R_RenderBuffer* rbObj, int *width, int *height);

	// Queries
	uint32 createOcclusionQuery();
	void destroyQuery(uint32 queryObj);
	void beginQuery(uint32 queryObj);
	void endQuery(uint32 queryObj);
	uint32 getQueryResult(uint32 queryObj);

	// Render Device dependent GPU Timer
	GPUTimer* createGPUTimer()
	{
		return new GPUTimer();
	}

	// -----------------------------------------------------------------------------
	// Commands
	// -----------------------------------------------------------------------------
	void setViewport(int x, int y, int width, int height)
	{
		_vpX = x;
		_vpY = y;
		_vpWidth = width;
		_vpHeight = height;
		_pendingMask |= PM_VIEWPORT;
	}
	void setScissorRect(int x, int y, int width, int height)
	{
		_scX = x;
		_scY = y;
		_scWidth = width;
		_scHeight = height;
		_pendingMask |= PM_SCISSOR;
	}
	void setGeometry(R_GeometryInfo* geoIndex)
	{
		_curGeometryIndex = geoIndex;
		_pendingMask |= PM_GEOMETRY;
	}
	void setTexture(uint32 slot, R_Texture* texObj, uint16 samplerState, uint16 usage)
	{
		assert1(slot < 16);
		_texSlots[slot] = R_TexSlot(texObj, samplerState, usage);
		_pendingMask |= PM_TEXTURES;
	}
	void setMemoryBarrier(R_DrawBarriers barrier)
	{
		_memBarriers = barrier;
		_pendingMask |= PM_BARRIER;
	}
	void setStorageBuffer(uint8 slot, R_Buffer* bufObj)
	{
		assert1(slot < _maxComputeBufferAttachments && _storageBufs.size() < _maxComputeBufferAttachments);

		R_Buffer* buf = bufObj;
		_storageBufs.push_back(R_ShaderStorage(slot, buf->glObj));

		_pendingMask |= PM_COMPUTE;
	}

	// Render states
	void setColorWriteMask(bool enabled)
	{
		_newRasterState.renderTargetWriteMask = enabled;
		_pendingMask |= PM_RENDERSTATES;
	}
	void getColorWriteMask(bool &enabled) const
	{
		enabled = _newRasterState.renderTargetWriteMask;
	}

	void setFillMode(R_FillMode fillMode)
	{
		_newRasterState.fillMode = fillMode;
		_pendingMask |= PM_RENDERSTATES;
	}
	void getFillMode(R_FillMode &fillMode) const
	{
		fillMode = (R_FillMode)_newRasterState.fillMode;
	}

	void setCullMode(R_CullMode cullMode)
	{
		_newRasterState.cullMode = cullMode;
		_pendingMask |= PM_RENDERSTATES;
	}
	void getCullMode(R_CullMode &cullMode) const
	{
		cullMode = (R_CullMode)_newRasterState.cullMode;
	}

	void setScissorTest(bool enabled)
	{
		_newRasterState.scissorEnable = enabled;
		_pendingMask |= PM_RENDERSTATES;
	}
	void getScissorTest(bool &enabled) const
	{
		enabled = _newRasterState.scissorEnable;
	}

	void setMulisampling(bool enabled)
	{
		_newRasterState.multisampleEnable = enabled;
		_pendingMask |= PM_RENDERSTATES;
	}
	void getMulisampling(bool &enabled) const
	{
		enabled = _newRasterState.multisampleEnable;
	}

	void setAlphaToCoverage(bool enabled)
	{
		_newBlendState.alphaToCoverageEnable = enabled;
		_pendingMask |= PM_RENDERSTATES;
	}
	void getAlphaToCoverage(bool &enabled) const
	{
		enabled = _newBlendState.alphaToCoverageEnable;
	}

	void setBlendMode(bool enabled, R_BlendFunc srcRGBBlendFunc = BS_BLEND_ZERO, R_BlendFunc destRGBBlendFunc = BS_BLEND_ZERO)
	{
		_newBlendState.blendEnable = enabled;

		_newBlendState.srcRGBBlendFunc = srcRGBBlendFunc;
		_newBlendState.destRGBBlendFunc = destRGBBlendFunc;

		_newBlendState.srcABlendFunc = srcRGBBlendFunc;
		_newBlendState.destABlendFunc = destRGBBlendFunc;

		_pendingMask |= PM_RENDERSTATES;
	}
	void setBlendModeEx(bool enabled, R_BlendFunc srcRGBBlendFunc = BS_BLEND_ZERO, R_BlendFunc destRGBBlendFunc = BS_BLEND_ZERO, R_BlendFunc srcABlendFunc = BS_BLEND_ZERO, R_BlendFunc destABlendFunc = BS_BLEND_ZERO)
	{
		_newBlendState.blendEnable = enabled;

		_newBlendState.srcRGBBlendFunc = srcRGBBlendFunc;
		_newBlendState.destRGBBlendFunc = destRGBBlendFunc;

		_newBlendState.srcABlendFunc = srcABlendFunc;
		_newBlendState.destABlendFunc = destABlendFunc;

		_pendingMask |= PM_RENDERSTATES;
	}
	void getBlendMode(bool &enabled, R_BlendFunc &srcRGBBlendFunc, R_BlendFunc &destRGBBlendFunc) const
	{
		enabled = _newBlendState.blendEnable;
		srcRGBBlendFunc = (R_BlendFunc)_newBlendState.srcRGBBlendFunc;
		destRGBBlendFunc = (R_BlendFunc)_newBlendState.destRGBBlendFunc;
	}

	void setDepthMask(bool enabled)
	{
		_newDepthStencilState.depthWriteMask = enabled;
		_pendingMask |= PM_RENDERSTATES;
	}
	void getDepthMask(bool &enabled) const
	{
		enabled = _newDepthStencilState.depthWriteMask;
	}

	void setDepthTest(bool enabled)
	{
		_newDepthStencilState.depthEnable = enabled;
		_pendingMask |= PM_RENDERSTATES;
	}
	void getDepthTest(bool &enabled) const
	{
		enabled = _newDepthStencilState.depthEnable;
	}

	void setDepthFunc(R_DepthFunc depthFunc)
	{
		_newDepthStencilState.depthFunc = depthFunc;
		_pendingMask |= PM_RENDERSTATES;
	}
	void getDepthFunc(R_DepthFunc &depthFunc) const
	{
		depthFunc = (R_DepthFunc)_newDepthStencilState.depthFunc;
	}

	void setTessPatchVertices(uint16 verts)
	{
		_tessPatchVerts = verts;
		_pendingMask |= PM_RENDERSTATES;
	}

protected:
	bool commitStates(uint32 filter = 0xFFFFFFFF);
	void resetStates();
	
public:
	// Draw calls and clears
	void clear(uint32 flags = CLR_COLOR_RT0 | CLR_COLOR_RT1 | CLR_COLOR_RT2 | CLR_COLOR_RT3 | CLR_DEPTH, float* colorRGBA = 0x0, float depth = 1.0f);
	void draw(R_PrimitiveType primType, uint32 firstVert, uint32 numVerts);
	void drawIndexed(R_PrimitiveType primType, uint32 firstIndex, uint32 numIndices, uint32 firstVert, uint32 numVerts, bool _softReset = true);

protected:
	// Buffer helper
	inline R_Buffer* createBuffer(uint32 type, uint32 size, const void *data, bool _isDynamic = true);
	inline void	decreaseBufferRefCount(R_Buffer* bufObj);

	// Shader helper
	uint32 createShaderProgram(const char *vertexShaderSrc, const char *fragmentShaderSrc, const char *geometryShaderSrc, const char *tessControlShaderSrc, const char *tessEvalShaderSrc, const char *computeShaderSrc);
	bool linkShaderProgram(uint32 programObj);

	// RenderBuffer helper
	void resolveRenderBuffer(R_RenderBuffer* rbObj);

	void checkError();
	bool applyVertexLayout(R_GeometryInfo &geo);
	void applySamplerState(R_Texture* tex);
	void applyRenderStates();

protected:
	enum RDIPendingMask
	{
		PM_VIEWPORT = 0x00000001,
		//PM_INDEXBUF      = 0x00000002,
		//PM_VERTLAYOUT    = 0x00000004,
		PM_TEXTUREBUFFER = 0x00000004,
		PM_TEXTURES = 0x00000008,
		PM_SCISSOR = 0x00000010,
		PM_RENDERSTATES = 0x00000020,
		PM_GEOMETRY = 0x00000040,
		PM_BARRIER = 0x00000080,
		PM_COMPUTE = 0x00000100
	};

protected:
	R_VertexLayout                _vertexLayouts[MaxNumVertexLayouts];
	vector< R_ShaderStorage >     _storageBufs;
	R_TexSlot					  _texSlots[16];
	R_RasterState				  _curRasterState, _newRasterState;
	R_BlendState				  _curBlendState, _newBlendState;
	R_DepthStencilState		      _curDepthStencilState, _newDepthStencilState;
	R_DrawBarriers				  _memBarriers;

	bool                             m_IsIndexFormat32;
	uint32                             _activeVertexAttribsMask;

	uint16                             _lastTessPatchVertsValue;
	uint16                             _maxComputeBufferAttachments;

	bool                               _doubleBuffered;

	//--------------------------------------------------
	// DEFAULT
	//--------------------------------------------------

	// 8 ssbo

	string					    _shaderLog;
	uint32						_depthFormat;
	int							_vpX, _vpY, _vpWidth, _vpHeight;
	int							_scX, _scY, _scWidth, _scHeight;
	int							_fbWidth, _fbHeight;
	R_RenderBuffer*				_curRendBuf;
	int							_outputBufferIndex;  // Left and right eye for stereo rendering
	uint32						_textureMem, _bufferMem;

	uint32                      _numVertexLayouts;

	R_Shader*					_curShaderId;
	uint32						_pendingMask;
    R_GeometryInfo*						_defGeometry;
    R_GeometryInfo*						_curGeometryIndex;
	uint32						_maxTexSlots; // specified in inherited render devices

	uint32						_tessPatchVerts; // number of vertices in patch. Used for tesselation.

	int							_defaultFBO;
	bool                        _defaultFBOMultisampled;
};
