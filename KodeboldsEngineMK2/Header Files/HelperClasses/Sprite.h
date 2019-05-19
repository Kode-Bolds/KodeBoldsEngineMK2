#pragma once
#include <wrl.h>
#include <d3d11.h>

class Sprite
{
private:
public:
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> mTexture;
	DirectX::XMFLOAT2 mPosition;
	DirectX::XMFLOAT2 mOrigin;
	float mRotation;
	float mScale;
	float mWidth;
	float mHeight;
};