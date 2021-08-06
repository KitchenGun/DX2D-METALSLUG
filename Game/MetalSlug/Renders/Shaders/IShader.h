#pragma once
class IShader
{
public:
	IShader();
	virtual ~IShader() = default;

	virtual void Create(const wstring path, const string entryName) = 0;
	virtual void Clear() = 0;
	virtual void SetShader() = 0;

protected:
	void CompileShader(wstring path, string entryName, string profile, ID3DBlob** blob);

	wstring path = L"";		//hlsl파일이름
	string entryName="";	//진입점함수이름
	string profile="";		//쉐이터모델버전

private:
	void CheckShaderError(HRESULT hr, ID3DBlob* error);
};