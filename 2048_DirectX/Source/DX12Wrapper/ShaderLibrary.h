#pragma once

#include "Shader.h"
#include "../Utility/EngineUtility.h"

namespace DX12Wrapper {
	enum class SHADERTYPE {
		VERTEX,
		PIXEL
	};

	class ShaderLibrary {
	private:
		ShaderLibrary();
		~ShaderLibrary();
		ShaderLibrary(const ShaderLibrary& inst) = delete;
		void operator=(const ShaderLibrary& inst) = delete;

		std::unordered_map<std::string, Shader> _shaderMap;
		std::unordered_map<SHADERTYPE, const char*> _shaderTypeMap;

	public:
		static ShaderLibrary& Instance();

		void RegistShader(
			const TCHAR* shaderFileName, const std::string& shaderTag,
			SHADERTYPE shaderType, const char* entryPointName = "main");

		Shader* GetShader(const std::string& shaderTag);
	};
}