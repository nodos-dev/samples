// Copyright Nodos AS. All Rights Reserved.
#include <Adder.h>
#include <Nodos/SubsystemAPI.h>

NOS_INIT();

namespace sample
{
template <typename T>
T __stdcall Add(T a, T b)
{
    return a + b;
}
}

extern "C"
{
NOSAPI_ATTR nosResult NOSAPI_CALL nosExportSubsystem(nosSubsystemFunctions* subsystemFunctions, void** exported)
{
    auto adderCtx = new Adder;
    adderCtx->AddInteger = sample::Add<int>;
    adderCtx->AddFloat = sample::Add<float>;
    *exported = adderCtx;
    return NOS_RESULT_SUCCESS;
}

NOSAPI_ATTR nosResult NOSAPI_CALL nosUnloadSubsystem(void* subsystemContext)
{
    delete static_cast<Adder*>(subsystemContext);
    return NOS_RESULT_SUCCESS;
}
}
