#pragma once
//FOR USE BY IRIS CLIENTS

#include "core/main/main.h"
#include "core/layers/layers.h"
#include "core/log/log.h"

#include "core/main/timestep.h"

#include "core/input/input.h"
#include "core/input/keycodes.h"
#include "core/input/mouse_button_codes.h"

//#include "core/editor/editor_interface.h"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
// Renderer Includes
#include "core/servers/rendering/renderer/Renderer2D.h"
#include "core/servers/rendering/renderer/Renderer3D.h"
#include "core/servers/rendering/renderer/renderer_rd.h"
#include "core/servers/rendering/renderer/renderer_api.h"
#include "core/servers/rendering/renderer/graphics_context.h"
#include "core/servers/rendering/renderer/buffers.h"
#include "core/servers/rendering/renderer/vertexArray.h"
#include "core/servers/rendering/renderer/shader.h"
#include "core/servers/rendering/renderer/texture.h"
#include "core/servers/rendering/renderer/framebuffer.h"

#include "core/servers/camera/2D/orthographic_camera.h"
#include "core/servers/camera/2D/controller.h"
#include "core/servers/camera/3D/controller_main.h"
#include "core/servers/camera/3D/Camera.h"


#include "imgui.h"