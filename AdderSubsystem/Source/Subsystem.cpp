// Copyright MediaZ Teknoloji A.S. All Rights Reserved.
#include <Adder.h>
#include <Nodos/SubsystemAPI.h>

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

std::unique_ptr<Adder> GAdderCtx;

nosResult NOSAPI_CALL OnRequest(uint32_t minorVersion, void** outSubsystemContext)
{
	if (!GAdderCtx)
		{
		GAdderCtx = std::make_unique<Adder>();
		GAdderCtx->AddInteger = sample::Add<int>;
		GAdderCtx->AddFloat = sample::Add<float>;
	}
	*outSubsystemContext = GAdderCtx.get();
	return NOS_RESULT_SUCCESS;
}


extern "C"
NOSAPI_ATTR nosResult NOSAPI_CALL nosExportSubsystem(nosSubsystemFunctions* subsystemFunctions)
{
	subsystemFunctions->OnRequest = OnRequest;
	return NOS_RESULT_SUCCESS;
}
