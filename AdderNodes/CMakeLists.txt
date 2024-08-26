
# Dependencies
nos_get_module("sample.sys.adder" "0.1.0" SAMPLE_SUBSYS_TARGET_NAME)

list(APPEND DEPENDENCIES ${SAMPLE_SUBSYS_TARGET_NAME} ${NOS_PLUGIN_SDK_TARGET})
set(INCLUDE_FOLDERS "")

nos_add_plugin("AdderNodes" "${DEPENDENCIES}" "${INCLUDE_FOLDERS}")

# Project generation
nos_group_targets("AdderNodes" "Plugins")