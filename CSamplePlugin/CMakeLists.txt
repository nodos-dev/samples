list(APPEND DEPENDENCIES ${SAMPLE_SUBSYS_TARGET_NAME} ${NOS_PLUGIN_SDK_TARGET})
set(INCLUDE_FOLDERS "")

enable_language(C)
nos_add_plugin("CSamplePlugin" "${DEPENDENCIES}" "${INCLUDE_FOLDERS}")

# Project generation
nos_group_targets("CSamplePlugin" "Plugins")