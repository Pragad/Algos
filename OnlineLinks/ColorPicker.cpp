/*
 * Author: Pragad Thiru
 * Program to select a random color based on given weights
 *
 */

#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <memory>
#include <stack>
#include <queue>
#include <typeinfo>
#include <ctime>

// ---------------------------------------------------------------------------------------
// Class RandomColorByWeight
//
// This class is used to pick a random color by considerint the weight of each color
//
// Assumption:
//      All colors are stored in case-sensitive way
//      This can be modified by storing colors in all lower case
//
// Each Color is represented in the form of a Node. 
// A Binary Tree (similar to Sum Tree) is constructed for all the Colors
// The binary tree is used at each step to decide which half of the colors to consider
//
// Complexity: O(log (N))
//
//     _colorRoot:
//          Represent Root of the Tree
//
//     _colorsMap:
//          Stores all colors Node and the corresponding weights
//          This map is used to quickly get to the Node on the tree
//
//     buildTree()
//          This function creates the binary tree by computing the sum of children
//          and storing it in the leaf
//
//     getRandomColor()
//     getRandomColorRec()
//          Generates a random color biased by the weights
//
//     insertColors()
//          Inserts the colors into the _colorsMap and builds the tree
//
//     adjustWeight()
//     adjustTreeWeights()
//          Used to modify the weight of the color
//          It also updates the weight of the corresponding nodes in the tree
//
//     printColorList()
//          Utility function to print all the colors and its weights
//
//     printTree()
//     printTreeRec()
//          Utility function to print the entire tree
//
// ---------------------------------------------------------------------------------------
class RandomColorByWeight
{
private:

    // Private class that represents a node
    class ColorNode
    {
    public:
        uint32_t _weight;
        std::string _colorName; // can be NULL. Only leaf will have a value
        std::shared_ptr<ColorNode> _left;
        std::shared_ptr<ColorNode> _right;
        std::shared_ptr<ColorNode> _parent;

        ColorNode(uint32_t weight) : _left(nullptr),
                                     _right(nullptr),
                                     _parent(nullptr),
                                     _weight(weight) { }

        ColorNode(std::string color, uint32_t weight) : _left(nullptr),
                                                        _right(nullptr),
                                                        _parent(nullptr),
                                                        _colorName(color),
                                                        _weight(weight) { }
    };

    std::shared_ptr<ColorNode> _colorRoot;
    std::unordered_map<std::string, std::shared_ptr<ColorNode>> _colorsMap;

    void buildTree();
    void printTreeRec(std::shared_ptr<ColorNode> root);
    std::string getRandomColorRec(std::shared_ptr<ColorNode> root);
    void adjustTreeWeights(std::shared_ptr<ColorNode> root, int weightDiff);

public:
    void insertColors(const std::vector<std::pair<std::string, uint32_t>>& colorsVec);
    void adjustWeight(const std::string& entry, uint32_t weight);
    std::string getRandomColor();
    void printColorList();
    void printTree();

    RandomColorByWeight() : _colorRoot(nullptr) { }
};

// ---------------------------------------------------------------------------------------
// This function will print the Sum Tree. It is useful for debugging purposes
// ---------------------------------------------------------------------------------------
void
RandomColorByWeight::printTreeRec(std::shared_ptr<ColorNode> root)
{
    if (root == nullptr)
    {
        return;
    }
        
    if (root->_colorName != "")
    {
        std::cout << (root->_colorName) << " : " << root->_weight << std::endl;
    }
    else
    {
        std::cout << "Wt: " << (root->_weight) << std::endl;
    }

    printTreeRec(root->_left);
    printTreeRec(root->_right);
}

void
RandomColorByWeight::printTree()
{
    printTreeRec(_colorRoot);
}

// ---------------------------------------------------------------------------------------
// This function will build the Tree
//
// Logic:
//      Go bottom up. Take two nodes at a time and create parent for all leaf nodes
//      Insert the parent nodes in a queue
//      Take two elements from the queue and create parent for all those nodes
//      Repeat this process until the queue is empty
//      Make sure to set the _colorRoot to the first node in the queue
// ---------------------------------------------------------------------------------------
void
RandomColorByWeight::buildTree()
{
    std::queue<std::shared_ptr<ColorNode>> colorNodesQueue;

    for (auto colorMapItr = _colorsMap.begin(); colorMapItr != _colorsMap.end(); colorMapItr++)
    {
        std::shared_ptr<ColorNode> elmnt1 = colorMapItr->second;

        // Go to the next element in the map
        colorMapItr++;

        if (colorMapItr != _colorsMap.end())
        {
            std::shared_ptr<ColorNode> elmnt2 = colorMapItr->second;
            std::shared_ptr<ColorNode> tmpEntry (new ColorNode(elmnt1->_weight + elmnt2->_weight));

            // Adjust left and right pointers of the new entry that we created
            tmpEntry->_left = elmnt1;
            tmpEntry->_right = elmnt2;

            // Add parent pointer to the child entries
            elmnt1->_parent = tmpEntry;
            elmnt2->_parent = tmpEntry;

            colorNodesQueue.push(tmpEntry);    
        }
        else
        {
            // We have reach the end of Map. So break out of the loop
            colorNodesQueue.push(elmnt1);    
            break;
        }
    }

    // Take two nodes from the stack and form a SumNode
    // Push the sumNode back into the stack
    // Repeat till the stack size is > 1
    while (!colorNodesQueue.empty())
    {
        // Get the next element from the stack
        std::shared_ptr<ColorNode> elmnt1 = colorNodesQueue.front();
        colorNodesQueue.pop();

        if (!colorNodesQueue.empty())
        {
            // Get the next element from the stack
            std::shared_ptr<ColorNode> elmnt2 = colorNodesQueue.front();
            colorNodesQueue.pop();

            std::shared_ptr<ColorNode> tmpEntry (new ColorNode(elmnt1->_weight + elmnt2->_weight));

            // Adjust left and right pointers of the new entry that we created
            tmpEntry->_left = elmnt1;
            tmpEntry->_right = elmnt2;

            // Add parent pointer to the child entries
            elmnt1->_parent = tmpEntry;
            elmnt2->_parent = tmpEntry;

            colorNodesQueue.push(tmpEntry);    
        }
        else
        {
            _colorRoot = elmnt1;
        }
    }
}

// ---------------------------------------------------------------------------------------
// This function inserts a new color into the list.
// If the color is already present in the list it will throw an exception.
// It can be modified to update the weight if the entry already exists
// ---------------------------------------------------------------------------------------
void
RandomColorByWeight::insertColors(const std::vector<std::pair<std::string, uint32_t>>& colorsVec)
{
    for (auto colorEntry : colorsVec)
    {
        auto itrColor = _colorsMap.find(colorEntry.first);

        // entry is already present in the list. Throw an exception
        if (itrColor != _colorsMap.end())
        {
            throw std::invalid_argument("Error Inserting Color. Duplicate Entry: \"" + colorEntry.first + "\"");
        }

        // Create a color Node and insert that into the map with
        // Key: ColorName
        // Value: Pointer to ColorNode
        _colorsMap.insert(make_pair(colorEntry.first,
                                    std::shared_ptr<ColorNode>
                                    (new ColorNode(colorEntry.first, colorEntry.second))));
    }

    buildTree();
}

// ---------------------------------------------------------------------------------------
// This function will return a random color by considering the weight
//
// Logic:
//      At each step a random number between 0 and root->_weight is generated
//      If the number is less than root->_left->_data then we go left
//      Else we go right and repeat the process  till the leaf node is hit
// ---------------------------------------------------------------------------------------
std::string
RandomColorByWeight::getRandomColorRec(std::shared_ptr<ColorNode> root)
{
    if (root == nullptr)
    {
        return "";
    }

    if (root->_left == nullptr && root->_right == nullptr)
    {
        return root->_colorName;
    }

    uint32_t randNum = rand() % (root->_weight);
    if (randNum > root->_left->_weight)
    {
        return getRandomColorRec(root->_right);
    }
    else
    {
        return getRandomColorRec(root->_left);
    }
    return "";
}

std::string
RandomColorByWeight::getRandomColor()
{
    // Use Time as seed to generate different random numbers each time
    srand(time(NULL));

    return getRandomColorRec(_colorRoot);
}

// ---------------------------------------------------------------------------------------
// Utility function for debugging purposes to know what is there in the colors list
// ---------------------------------------------------------------------------------------
void
RandomColorByWeight::printColorList()
{
    for (auto colorMapItr = _colorsMap.begin(); colorMapItr != _colorsMap.end(); colorMapItr++)
    {
        std::cout << colorMapItr->first << ": " << colorMapItr->second->_weight << ", ";
    }
    std::cout << std::endl;
}

// ---------------------------------------------------------------------------------------
// Function to adjust weight of a color
// If the Color is not present in the list then throw an exception
// ---------------------------------------------------------------------------------------
void
RandomColorByWeight::adjustTreeWeights(std::shared_ptr<ColorNode> root, int weightDiff)
{
    // Adjust the weight of the entry
    if (root == nullptr)
    {
        return;
    }

    if (root->_parent == nullptr)
    {
        // We have reached the root of the tree
        root->_weight += weightDiff;
        return;
    }

    root->_weight += weightDiff;
    adjustTreeWeights(root->_parent, weightDiff);
}

void
RandomColorByWeight::adjustWeight(const std::string& entry, uint32_t weight)
{
    std::cout<< "Adjusting Weight... Color: \"" << entry << "\" New Wt: " << weight << std::endl;

    auto itrColor = _colorsMap.find(entry);

    // entry is not present. Throw an exception
    if (itrColor == _colorsMap.end())
    {
        throw std::invalid_argument(entry + " is not present. Adjust existing entry");
    }

    adjustTreeWeights(itrColor->second, weight - itrColor->second->_weight);
}

// ---------------------------------------------------------------------------------------
// Main Function
// ---------------------------------------------------------------------------------------
int main()
{
    std::string color1 = "Red";
    std::string color2 = "Green";
    std::string color3 = "Blue";
    std::string color4 = "Yellow";
    std::string color5 = "Brown";
    std::string color6 = "Purple";
    std::string color7 = "White";
    std::string color8 = "Black";
    std::string color9 = "Orange";

    std::vector<std::pair<std::string, uint32_t>> colorsVec = { {color1, 5}, {color2, 3},
                                                                {color3, 2}, {color4, 1},
                                                                {color5, 8}, {color6, 20},
                                                                {color7, 4}, {color8, 6},
                                                                {color9, 7} };

    RandomColorByWeight objRandomColor;

    try
    {
        // 1. Insert all the colors
        objRandomColor.insertColors(colorsVec);

        // 2. Print the colors
        objRandomColor.printColorList();

        // 3. Print the tree to verify the colors and tree is properly constructed
        objRandomColor.printTree();

        // 4. Get a random color
        std::cout << "Random Color Based on Weight: " << objRandomColor.getRandomColor() << std::endl << std::endl;

        // 5. Adjust weight of a color
        objRandomColor.adjustWeight(color5, 28);

        // 6. Print the colors with new weights
        objRandomColor.printColorList();

        // 7. Print the new tree to verify the new weight got updated
        objRandomColor.printTree();

        // 8. Get the next random color
        std::cout << "Random Color Based on Weight: " << objRandomColor.getRandomColor() << std::endl;
    }
    catch (const std::invalid_argument& e)
    {
        std::cout << "Exception Occurred: " << e.what() << std::endl;
    }


    std::cout << std::endl;
    return 0;
}


/*
 Sample Debug Output:
    White: 4, Brown: 8, Yellow: 1, Black: 6, Purple: 20, Blue: 2, Orange: 7, Green: 3, Red: 5,
    Wt: 56              <-----
    Wt: 32              <-----
    Wt: 22              <-----
    Purple : 20
    Blue : 2
    Wt: 10              <-----
    Orange : 7
    Green : 3
    Wt: 24              <-----
    Red : 5
    Wt: 19              <-----
    Wt: 12              <-----
    White : 4
    Brown : 8
    Wt: 7               <-----
    Yellow : 1
    Black : 6
    Random Color Based on Weight: Purple

                                                                        56

                                                24

                            19                                                                              32

            7                               12                                              10                              22

    6              1                8               4               5               3               7               2               20

    Adjusting Weight... Color: "Brown" New Wt: 28
    White: 4, Brown: 28, Yellow: 1, Black: 6, Purple: 20, Blue: 2, Orange: 7, Green: 3, Red: 5,
    Wt: 76
    Wt: 32
    Wt: 22
    Purple : 20
    Blue : 2
    Wt: 10
    Orange : 7
    Green : 3
    Wt: 44
    Red : 5
    Wt: 39
    Wt: 32
    White : 4
    Brown : 28
    Wt: 7
    Yellow : 1
    Black : 6
    Random Color Based on Weight: Purple

                                                                        76

                                                44

                            39                                                                              32

            7                               32                                              10                              22

    6              1                28               4               5               3               7               2               20
 */
