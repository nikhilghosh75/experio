#include "../../ExperioEditor/Source/Testing/UnitTestingFramework.h"
#include "Runtime/Containers/TTypedTree.h"

TEST_SUITE("TypedTree", "Experio/Containers");

UNIT_TEST(TestTypedTreeGeneral, "TypedTree")
{
	TTypedTree<std::string> typedTree("Animal");
	typedTree.AddChildToRoot("Mammal");
	typedTree.AddChildToRoot("Amphibian");

	TTypedTreeNode<std::string>* mammal = typedTree.GetRoot()->children[0];
	mammal->AddChild("Artiodactyla");
	mammal->AddChild("Carnivore");
	mammal->AddChild("Edentata");
	mammal->AddChild("Insectivora");
	mammal->AddChild("Primate");
	mammal->AddChild("Rodentia");

	TTypedTreeNode<std::string>* amphibian = typedTree.GetRoot()->children[1];
	amphibian->AddChild("Frog");
	amphibian->AddChild("Earthworm");
	amphibian->AddChild("Salamander");

	TTypedTreeNode<std::string>* primate = mammal->children[3];
	primate->AddChild("Human");
	primate->AddChild("Ape");
	primate->AddChild("Monkey");
	primate->AddChild("Orangutan");

	TTypedTreeNode<std::string>* insect = mammal->children[2];
	insect->AddChild("Cockroaches");
	insect->AddChild("Beetles");
	insect->AddChild("Mosquito");
	insect->AddChild("Flies");
	insect->AddChild("Bee");
	insect->AddChild("Termites");
	insect->AddChild("Dragonflies");
	insect->AddChild("Crickets");

	ASSERT_EQUAL(typedTree.GetCount(), 24, "");
	ASSERT_EQUAL(mammal->object, "Mammal", "");

	TTypedTreeIterator<std::string> it(&typedTree);
	ASSERT_EQUAL(it.current->object, "Animal", "");
	it.Increment();
	ASSERT_EQUAL(it.current->object, "Mammal", "");
	it.Increment();

	TEST_END();
}