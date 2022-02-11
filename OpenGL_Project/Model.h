#ifndef MODEL_CLASS_H
#define MODEL_CLASS_H

#include"shaderClass.h"
#include"Mesh.h"
#include <string>
#include <vector>

//EH
#include"Camera.h"


#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

unsigned int TextureFromFile(const char* path, const std::string& directory, bool gamma = false);


class Model {

	public: 
		//Store all textures loaded to prevent from loading a texture twice
		std::vector<Texture> textures_loaded;
		std::string directory;

		Model(std::string path) 
		{
			loadModel(path);
		};

		void Draw(Shader& shader, Camera& camera);

		void loadModel(std::string path);
		void processNode(aiNode* node, const aiScene* scene);
		Mesh processMesh(aiMesh* mesh, const aiScene* scene);
		std::vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);

	private:
		//Model Data
		std::vector<Mesh> meshes;
};

#endif // !MODEL_CLASS_H