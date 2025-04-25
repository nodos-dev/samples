#include <Nodos/PluginAPI.h>

nosName GetNameHelper(const char* name) 
{
	return nosEngine.GetName(name, strlen(name)); 
}

NOS_INIT()
NOS_BEGIN_IMPORT_DEPS()
NOS_END_IMPORT_DEPS()

nosResult NOSAPI_CALL ExecuteTestNode(void* ctx, nosNodeExecuteParams* params)
{
	int x = 0;
	int y = 0;
	nosUUID outputId = {0};
	for (size_t i = 0; i < params->PinCount; i++)
	{
		if (params->Pins[i].Name.ID == GetNameHelper("X").ID)
			x = *(int*)params->Pins[i].Data->Data;
		else if (params->Pins[i].Name.ID == GetNameHelper("Y").ID)
			y = *(int*)params->Pins[i].Data->Data;
		else if (params->Pins[i].Name.ID == GetNameHelper("Z").ID)
			outputId = params->Pins[i].Id;
	}
	int result = x + y;
	// Use this direct buffer copy approach only if your type does not need custom handling (just a simple buffer), and
	// you are inside Nodos Scheduler thread. This is not thread-safe.
	nosBuffer buffer;
	buffer.Data = &result;
	buffer.Size = sizeof(result);

	nosEngine.SetPinValue(outputId, buffer);
	return NOS_RESULT_SUCCESS;
}

nosResult NOSAPI_CALL ExportNodeFunctions(size_t* outCount, nosNodeFunctions** outFunctions)
{
    *outCount = (size_t)(1);
    if (!outFunctions)
        return NOS_RESULT_SUCCESS;

	outFunctions[0]->ClassName = GetNameHelper("CSample");
	outFunctions[0]->ExecuteNode = ExecuteTestNode;
    return NOS_RESULT_SUCCESS;
}

NOSAPI_ATTR nosResult NOSAPI_CALL nosExportPlugin(nosPluginFunctions* out)
{
	out->ExportNodeFunctions = ExportNodeFunctions;
	return NOS_RESULT_SUCCESS;
}
