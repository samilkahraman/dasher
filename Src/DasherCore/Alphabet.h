// Alphabet.h
//
/////////////////////////////////////////////////////////////////////////////
// Alphabet.h
//
/////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2001-2002 David Ward
//
/////////////////////////////////////////////////////////////////////////////

#ifndef __DASHER_ALPHABET_H__
#define __DASHER_ALPHABET_H__


#include "DasherTypes.h"

#include "../Common/MSVC_Unannoy.h"
#include <map>
#include <vector>
#include "AlphabetMap.h"


namespace Dasher {class CAlphabet;}
class Dasher::CAlphabet
{
public:
	CAlphabet();
	~CAlphabet() {}
	
	int GetNumberSymbols() const { return m_Characters.size();}        // return size of alphabet
	
	Opts::ScreenOrientations GetOrientation() {return m_Orientation;}
	Opts::AlphabetTypes GetType() {return m_DefaultEncoding;}
	std::string& GetTrainingFile() {return m_TrainingFile;}
	std::string& GetPalette() {return m_DefaultPalette;}
	
	symbol GetParagraphSymbol() {return m_ParagraphSymbol;}
	symbol GetSpaceSymbol() {return m_SpaceSymbol;}
	symbol GetControlSymbol() {return m_ControlSymbol;}
	const std::string& GetDisplayText(symbol i) const {return m_Display[i];} // return display string for i'th symbol
	const std::string& GetText(symbol i) const {return m_Characters[i];}     // return string for i'th symbol
	int GetColour(symbol i) const {return m_Colours[i];}     // return the colour for i'th symbol
	int GetGroupColour(int i) const {return m_GroupColour[i];} // return the colour for i'th group
	int GetTextColour(symbol i);      // return the foreground colour for i'th symbol
	const std::string& GetForeground(symbol i) const {return m_Foreground[i];} // return the foreground colour for i'th symbol
	int get_group(symbol i) const {return m_Group[i];}                // return group membership of i'th symbol
	
	// Fills Symbols with the symbols corresponding to Input. {{{ Note that this
	// is not necessarily reversible by repeated use of GetText. Some text
	// may not be recognised and so discarded. If IsMore is true then Input
	// is truncated to any final characters that were not used due to ambiguous
	// continuation. If IsMore is false Input is assumed to be all the available
	// text and so a symbol will be returned for a final "a" even if "ae" is
	// defined as its own symbol. }}}
	void GetSymbols(std::vector<symbol>* Symbols, std::string* Input, bool IsMore);
	
	void dump() const; // diagnostic
	
	virtual void AddControlSymbol()=0;
	virtual void DelControlSymbol()=0;

protected:
	// Add the characters that can appear in Nodes
	void AddChar(const std::string NewCharacter, const std::string Display, int Colour, const std::string Foreground); // add single char to the alphabet
	// Delete a character
	void DelChar(symbol Symbol);
	void StartNewGroup(int colour=-1);

	// Alphabet language parameters
	void SetParagraphSymbol() {m_ParagraphSymbol=m_Characters.size()-1;}
	void SetSpaceSymbol() {m_SpaceSymbol=m_Characters.size()-1;}         // We can set the space symbol to be the last character added
	void SetControlSymbol() {m_ControlSymbol=m_Characters.size()-1;} // We set the control symbol to be the last character added. Given the above, this is a hack.
	void SetParagraphSymbol(symbol ParagraphSymbol) {m_ParagraphSymbol=ParagraphSymbol;}
	void SetSpaceSymbol(symbol SpaceSymbol) {m_SpaceSymbol=SpaceSymbol;} // ...or any desired symbol.
	void SetControlSymbol(symbol ControlSymbol) {m_ControlSymbol=ControlSymbol;}
	void SetOrientation(Opts::ScreenOrientations Orientation) {m_Orientation=Orientation;}
	void SetLanguage(Opts::AlphabetTypes Group) {m_DefaultEncoding=Group;}
	void SetTrainingFile(std::string TrainingFile) {m_TrainingFile=TrainingFile;}
	void SetPalette(std::string Palette) {m_DefaultPalette=Palette;}
private:
	Opts::AlphabetTypes m_DefaultEncoding;
	Opts::ScreenOrientations m_Orientation;
	symbol m_ParagraphSymbol;
	symbol m_SpaceSymbol;
	symbol m_ControlSymbol;
	std::string m_TrainingFile;
	std::string m_DefaultPalette;

	std::vector<std::string> m_Characters; // stores the characters
	std::vector<std::string> m_Display;    // stores how the characters are visually represented in the Dasher nodes
	std::vector<int> m_Colours;    // stores the colour of the characters
	std::vector<std::string> m_Foreground; // stores the colour of the character foreground
	std::vector<int> m_Group;              // stores the group indicators - e.g. caps, numbers, punctuation
	std::vector<int> m_GroupColour; // stores the colour of the group
	int m_Groups;                          // number of groups
	alphabet_map TextMap;
};


#endif // ifndef __DASHER_ALPHABET_H__