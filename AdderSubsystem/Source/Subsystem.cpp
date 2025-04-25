// Copyright MediaZ Teknoloji A.S. All Rights Reserved.
#include <Adder.h>
#include <Nodos/PluginAPI.h>

NOS_INIT()
NOS_BEGIN_IMPORT_DEPS()
NOS_END_IMPORT_DEPS()

namespace sample
{
template <typename T>
T __stdcall Add(T a, T b)
{
    return a + b;
}
}

std::unique_ptr<Adder> GAdderAPI;

nosResult NOSAPI_CALL OnRequestAPI(uint32_t minorVersion, void** outSubsystemContext)
{
	if (!GAdderAPI)
		{
		GAdderAPI = std::make_unique<Adder>();
		GAdderAPI->AddInteger = sample::Add<int>;
		GAdderAPI->AddFloat = sample::Add<float>;
	}
	*outSubsystemContext = GAdderAPI.get();
	return NOS_RESULT_SUCCESS;
}


extern "C"
NOSAPI_ATTR nosResult NOSAPI_CALL nosExportPlugin(nosPluginFunctions* outFunctions)
{
	outFunctions->OnRequestAPI = OnRequestAPI;
	return NOS_RESULT_SUCCESS;
}
