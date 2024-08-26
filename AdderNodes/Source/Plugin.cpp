#include <Nodos/PluginAPI.h>
#include <Nodos/PluginHelpers.hpp>
#include <Nodos/Helpers.hpp>

#include <Adder.h>

Adder *GAdderCtx{};
NOS_INIT()
NOS_BEGIN_IMPORT_DEPS()
	NOS_IMPORT_DEP_CONTEXT("sample.sys.adder", GAdderCtx)
NOS_END_IMPORT_DEPS()

nosResult NOSAPI_CALL ExportNodeFunctions(size_t* outCount, nosNodeFunctions** outFunctions)
{
    *outCount = (size_t)(2);
    if (!outFunctions)
        return NOS_RESULT_SUCCESS;

	outFunctions[0]->ClassName = NOS_NAME_STATIC("sample.adder.AddInteger");
	outFunctions[0]->ExecuteNode = [](void* ctx, nosNodeExecuteParams* params)
	{
		nos::NodeExecuteParams helper(params);
		auto inputX = static_cast<int*>(helper[NOS_NAME_STATIC("X")].Data->Data);
		auto inputY = static_cast<int*>(helper[NOS_NAME_STATIC("Y")].Data->Data);
		auto output = static_cast<int*>(helper[NOS_NAME_STATIC("Z")].Data->Data);
		// Use this direct buffer copy approach only if your type does not need custom handling (just a simple buffer), and you are inside Nodos Scheduler thread.
		// This is not thread-safe.
		*output = GAdderCtx->AddInteger(*inputX, *inputY);
		return NOS_RESULT_SUCCESS;
	};
	outFunctions[1]->ClassName = NOS_NAME_STATIC("sample.adder.AddFloat");
	outFunctions[1]->ExecuteNode = [](void* ctx, nosNodeExecuteParams* params)
	{
		nos::NodeExecuteParams helper(params);
		auto inputX = static_cast<float*>(helper[NOS_NAME_STATIC("X")].Data->Data);
		auto inputY = static_cast<float*>(helper[NOS_NAME_STATIC("Y")].Data->Data);
		auto outputId = helper[NOS_NAME_STATIC("Z")].Id;
		float result = GAdderCtx->AddFloat(*inputX, *inputY);
		// You can also use nosEngine.SetPinValue, which will call your type's copy functions (if applicable),
		// and enqueues the update if you are not on Nodos Scheduler thread.
		nosEngine.SetPinValue(outputId, nos::Buffer::From(result));
		return NOS_RESULT_SUCCESS;
	};
    return NOS_RESULT_SUCCESS;
}

extern "C"
{
NOSAPI_ATTR nosResult NOSAPI_CALL nosExportPlugin(nosPluginFunctions* out)
{
	out->ExportNodeFunctions = ExportNodeFunctions;
	return NOS_RESULT_SUCCESS;
}
}
