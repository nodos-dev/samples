list(APPEND DEPENDENCIES ${NOS_SUBSYSTEM_SDK_TARGET})
set(INCLUDE_FOLDERS "")

nos_add_subsystem("AdderSubsystem" "${DEPENDENCIES}" "${INCLUDE_FOLDERS}")

# Project generation
nos_group_targets("AdderSubsystem" "Subsystems")