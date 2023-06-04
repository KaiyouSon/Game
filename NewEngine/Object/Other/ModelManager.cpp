#include "ModelManager.h"

std::map<std::string, std::unique_ptr<Model>> ModelManager::modelMap;

Model* ModelManager::GetModel(const std::string& modelTag)
{
	return modelMap[modelTag].get();
}

Model* ModelManager::LoadObjModel(const std::string& filePath, const std::string& modelTag, const bool& isSmoothing)
{
	std::unique_ptr<Model> model;
	model.reset(new Model(filePath, isSmoothing));
	modelMap.insert(std::make_pair(modelTag, std::move(model)));

	return modelMap[modelTag].get();
}