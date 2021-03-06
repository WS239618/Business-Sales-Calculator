#include "Files.h"
bool Is_Index_Valid(std::vector<std::string>& objFile, std::size_t stIndex)
{
	try
	{
		objFile.at(stIndex);
		return true;
	}
	catch (...)
	{
		Display_Invalid_Command_Message();
		return false;
	}
}
bool Select_File_From_Menu(std::string &inputFilePath, std::vector<std::string>&objFile, std::string &ItemTextFile)
{
	/*stIndex = Select_File_From_Menu(inputFilePath, objFile);
	if (Is_Index_Valid(objFile, stIndex) == true)
	{
		ItemTextFile = objFile.at(stIndex);
		bExit = true;
	}*/
	std::string sChoice = "";
	int iChoice = 0;
	Message_And_Input("Choose a number that represents the text file you wish to use...\n",&sChoice);
	if (Is_Input_A_Number(sChoice, &iChoice) == true)
	{
		if (Is_Index_Valid(objFile, static_cast<std::size_t>(iChoice) - 1) == true) {
		
			ItemTextFile = objFile.at(iChoice);
			return true;
		}
	}
	else
	{
		std::cout << "#Invalid menu choice, please try again!#\n";
		return false;
	}
}

void File_Menu_System(std::vector<std::string>& objFile, std::string& inputFilePath, std::string &ItemTextFile)
{
	std::string sChoice = "";
	bool bExit = false;
	int iChoice = 0;
	std::size_t stIndex = 0;
	do 
	{
		Display_File_Menu();
		Message_And_Input("\nChoose a number from the file menu: ", &sChoice);
		std::cout << "\n";
		if (Is_Input_A_Number(sChoice, &iChoice) == true)
		{
			switch (iChoice)
			{
			case 1:
				Add_New_File(inputFilePath, objFile);
				break;
			case 2:
				Display_Existing_Files(objFile, inputFilePath);
				bExit = Select_File_From_Menu(inputFilePath, objFile,ItemTextFile);
				break;
			default:
				std::cout << "You've entered an invalid command, please try again!\n";
			}
		}
		else
		{
			Confirm_Continue();
		}
	} 
	while (bExit == false);
}
void Display_File_Menu() 
{
	std::cout << "What would you like to do?\n";
	std::cout << "1. Create a text file to store items in\n";
	std::cout << "2. Choose from text-file library\n";
}

void Display_Existing_Files(std::vector<std::string>& objFiles, std::string& inputFilePath)
{
	objFiles.resize(0);
	int iCount = 1;
	Add_Text_File_To_Vector(objFiles, inputFilePath);
	std::for_each(objFiles.begin(), objFiles.end(), [&](auto &objFile) {
		std::cout << iCount++ << ". " << objFile << "\n\n";
		});
}

//This add's text file to vector.
void Add_Text_File_To_Vector(std::vector<std::string>&objFiles, std::string& inputFilePath)
{
	std::vector<std::string>objSplit;
	std::string sLine = "";
	std::string sResult = "";
	std::ifstream file(inputFilePath);

	while (getline(file, sLine))
	{
		std::stringstream ssSplit(sLine);
		objSplit.resize(0);

		while (getline(ssSplit, sResult, ','))
		{
			objSplit.push_back(sResult);
		}
		if (objSplit.size() != 0)
		{
			objFiles.push_back({ objSplit.at(0)});
		}
	}
}
bool Add_New_File(std::string &inputFilePath, std::vector<std::string>&objFiles)
{
	objFiles.resize(0);
	Add_Text_File_To_Vector(objFiles, inputFilePath);
	std::string sNameOfNewTextFile;
	Message_And_Input("Enter name of new text file: ", &sNameOfNewTextFile);
	for (std::string objFile : objFiles)
	{
		if (objFile == sNameOfNewTextFile + ".txt")
		{
			std::cout << "#That file name already exists, please enter a unqiue name!#\n\n";
			return false;
		}
	}
	std::cout << "Successfully added!\n";
	objFiles.push_back(sNameOfNewTextFile + ".txt");
	Append_Credential_To_Text_File(inputFilePath, sNameOfNewTextFile);
	return true;

}
void Append_Credential_To_Text_File(std::string& inputFilePath, std::string& sNewTextFile)
{
	std::ofstream file;
	file.open(inputFilePath, std::ios_base::app);
	file << sNewTextFile << ".txt,\n";
	file.close();
}