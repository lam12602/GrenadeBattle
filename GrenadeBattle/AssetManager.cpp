#include "AssetManager.h"

std::map<std::string, sf::Texture> AssetManager::textures;
std::map<std::string, sf::Font> AssetManager::fonts;


sf::Texture& AssetManager::RequestTexture(std::string assetName)
{

	auto pairFound = textures.find(assetName);
	if (pairFound != textures.end())
	{
		return pairFound->second;
	}
	else
	{
		sf::Texture& newTexture = textures[assetName];
		newTexture.loadFromFile(assetName);
		return newTexture;
	}

}

sf::Font& AssetManager::RequestFont(std::string assetName)
{
	auto pairFound = fonts.find(assetName);

	if (pairFound != fonts.end())
	{
		// We found an existing font! Use it
		return pairFound->second;
	}
	else
	{
		sf::Font& newFont = fonts[assetName];
		newFont.loadFromFile(assetName);
		return newFont;
	}
}

//sf::SoundBuffer& AssetManager::RequestSound(std::string assetName)
//{
	// TODO: insert return statement here
//}






void AssetManager::DestroyAllAssets()
{
	textures.clear();
	fonts.clear();
	//soundBuffers.clear();
}

