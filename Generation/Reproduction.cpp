#include "Reproduction.h"
#include "Random.h"
#include "Population.h"
#include "Cercle.h"

Reproduction::Reproduction(size_t nbPop, size_t width, size_t mHeight)
	:mParent1{ 0 },
	mParent2{ 0 },
	mEnfant{ 0 },
	mNbChild{0},
	mChildSolution{}

{}


Reproduction::~Reproduction()
{
}

void Reproduction::createChild( Civilisations & c, size_t nbPop, size_t nbCivilisations, std::string type)
{
	int randomParentIndex1, randomParentIndex2, mask, indexSplit;
	
	for (int i = 0; i < nbCivilisations; ++i) {
		for (int j = 0; j < nbPop; ++j)
		{
			//Selection
			randomParentIndex1 = Random::getInstance().uniformRandomize(1, nbPop - 1);
			randomParentIndex2 = Random::getInstance().uniformRandomize(1, nbPop - 1);
			mParent1 = c.getPopulation(0).rouletteWheel(nbPop).shape()->encodePropreties();
			mParent2 = c.getPopulation(0).rouletteWheel(nbPop).shape()->encodePropreties();
			//Generate Child
			indexSplit = Random::getInstance().uniformRandomize(1, 30);
			mask = (int)pow(2, indexSplit) - 1;
			//Je realise l'enfant
			mEnfant = mParent1 & mask | mParent2 & ~mask;
			//Mutate
				//Es ce que je fait un mutant ou pas
			if (int a = Random::getInstance().uniformRandomize(1, 100) <= percentageMutate)
			{
				//nombre de bit a changer
				int nbBitChange{ 1 };
				//Position aléatoire
				for (int i = 0; i < nbBitChange; ++i) {
					int indexAléatoire = Random::getInstance().uniformRandomize(1, 30);
					int maskMutate = 1;
					maskMutate <<= (indexAléatoire - 1);
					mEnfant = mEnfant ^ maskMutate;
				}
			}
			delivery(type, j, mWidth, mHeight);
		}
		c.getPopulation(i).parentDeath(mChildSolution,nbPop);
		//for (int i = 0; i < mChildSolution.size(); ++i) {
		//	mChildSolution.at(i).deleteShape();
		//}
		mChildSolution.clear();
	}
}


void Reproduction::delivery(std::string const & type, size_t i, size_t width, size_t height) {
	Shape2D *shape =nullptr;
	if (type == "cercle"){
		shape=new Cercle();
		shape->decodePropreties(mEnfant);
	}
	if (shape != nullptr) {
		mChildSolution.push_back(Solution(shape, width, height));
	}
}
