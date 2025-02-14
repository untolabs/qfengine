#include "client/precompiled.hh"
#include "client/opengl/opengl.hh"

void opengl::imgui_begin_frame(void)
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL3_NewFrame();
    ImGui::NewFrame();
}

void opengl::imgui_end_frame(void)
{
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}
