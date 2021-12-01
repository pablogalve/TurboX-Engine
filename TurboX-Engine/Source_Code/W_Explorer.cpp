#include "W_Explorer.h"

W_Explorer::W_Explorer()
{
	currDir = ASSETS_PATH;
}

W_Explorer::~W_Explorer()
{}

void W_Explorer::Draw()
{
	ImGui::Begin("Explorer");

	uint flags = 0;
	flags |= ImGuiTreeNodeFlags_Leaf;

	std::vector<std::string> files;
	std::vector<std::string> dirs;

	App->file_system->GetFilesFromDir(currDir.c_str(), files, dirs, false, true);
	ImGui::Text("%s", currDir.c_str());
	
	ImVec2 PRegion = ImGui::GetContentRegionAvail();

	ImGui::SameLine(PRegion.x - 22);

	if (ImGui::SmallButton("Back"))
	{
		App->file_system->ShiftPath(&currDir);
	}

	ImGui::Separator();
	for (int i = 0; i < dirs.size(); i++) 
	{
		std::string dirName = dirs[i];
		if (ImGui::TreeNodeEx(dirName.c_str(), flags)) 
		{
			if (ImGui::IsItemClicked(0)) 
			{
				currDir += dirName;
			}
			ImGui::TreePop();
		}
	}

	static uint nodeClicked = -1;
	
	for (int i = 0; i < files.size(); i++) 
	{
		std::string fileName;

		App->file_system->GetNameFromPath(files[i].c_str(), nullptr, nullptr, &fileName, nullptr);
		
		if (ImGui::BeginMenu(fileName.c_str())) 
		{
			if (ImGui::MenuItem("Load File")) 
				App->resources->LoadFiles(files[i].c_str());

			if (ImGui::MenuItem("Delete File")) 
				App->file_system->RemoveFile(files[i].c_str());

			ImGui::EndMenu();
		}
	}
	ImGui::End();
}

void W_Explorer::SetShowWindow()
{
	showWindow = !showWindow;
}

bool W_Explorer::GetShowWindow()
{
	return showWindow;
}
