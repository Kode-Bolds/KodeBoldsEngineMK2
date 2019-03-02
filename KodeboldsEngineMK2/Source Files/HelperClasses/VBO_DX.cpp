#include "VBO_DX.h"
#include "RenderSystem.h"


VBO_DX::VBO_DX() = default;
VBO_DX::~VBO_DX() = default;

/// <summary>
/// Creates the vertex and index buffers by loading in the obj file given a filename
/// </summary>
/// <param name="pRenderer"> the renderer to use to create the buffers with </param>
/// <param name="pFilename"> the filename of the geometry to load </param>
HRESULT VBO_DX::Create(const RenderSystem * pRenderer, const std::wstring& pFilename)
{
	auto hr{ S_OK };

	auto geometry = ObjLoader::LoadObject(pFilename);

	//Create vertex buffer
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = geometry.second.size() * sizeof(Vertex);
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;
	D3D11_SUBRESOURCE_DATA initData;
	ZeroMemory(&initData, sizeof(initData));
	initData.pSysMem = &(geometry.second[0]);
	hr = pRenderer->Device()->CreateBuffer(&bd, &initData, mVertices.GetAddressOf());
	if (FAILED(hr))
		return hr;

	//Create index buffer
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = geometry.first.size() * sizeof(WORD);
	bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	bd.CPUAccessFlags = 0;
	initData.pSysMem = &(geometry.second[0]);
	hr = pRenderer->Device()->CreateBuffer(&bd, &initData, mIndices.GetAddressOf());
	if (FAILED(hr))
		return hr;

	return hr;
}

void VBO_DX::Load(const RenderSystem* pRenderer) const
{
	// Set vertex buffer
	const UINT stride = sizeof(Vertex);
	const UINT offset = 0;
	pRenderer->Context()->IASetVertexBuffers(0, 1, mVertices.GetAddressOf(), &stride, &offset);

	// Set index buffer
	pRenderer->Context()->IASetIndexBuffer(mIndices.Get(), DXGI_FORMAT_R16_UINT, 0);
}
