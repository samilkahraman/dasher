// DasherSettingsInterface.cpp
//
/////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2002 Iain Murray
//
/////////////////////////////////////////////////////////////////////////////

#include "DasherSettingsInterface.h"

namespace Dasher{
namespace Keys {
	// Standard Option strings. You are encouraged to use these constants.
	// -------------------------------------------------------------------
	
	// bool options
	const std::string TIME_STAMP = "TimeStampNewFiles";
	const std::string SHOW_TOOLBAR = "ViewToolbar";
	const std::string SHOW_TOOLBAR_TEXT = "ShowToolbarText";
	const std::string SHOW_LARGE_ICONS = "ShowLargeIcons";
	const std::string FIX_LAYOUT = "FixLayout";
	const std::string SHOW_SLIDER = "ShowSpeedSlider";
	const std::string COPY_ALL_ON_STOP = "CopyAllOnStop";
        const std::string DRAW_MOUSE = "DrawMouse";
        const std::string DRAW_MOUSELINE = "DrawMouseLine";
        const std::string START_MOUSE = "StartOnLeft";
        const std::string START_SPACE = "StartOnSpace";
        const std::string KEY_CONTROL = "KeyControl";
        const std::string WINDOW_PAUSE = "PauseOutsideWindow";
        const std::string CONTROL_MODE = "ControlMode";
        const std::string COLOUR_MODE = "ColourMode";
        const std::string KEYBOARD_MODE = "KeyboardMode";
        const std::string MOUSEPOS_START = "StartOnMousePosition";
        const std::string SPEECH_MODE = "SpeechEnabled";
        const std::string OUTLINE_MODE = "OutlineBoxes";
        const std::string PALETTE_CHANGE = "PaletteChange";

	// long options
	const std::string FILE_ENCODING = "FileEncodingFormat";
	const std::string MAX_BITRATE_TIMES100 = "MaxBitRateTimes100";
	const std::string SCREEN_ORIENTATION = "ScreenOrientation";
	const std::string VIEW_ID = "ViewID";
	const std::string LANGUAGE_MODEL_ID = "LanguageModelID";
	const std::string EDIT_FONT_SIZE = "EditFontSize";
	const std::string EDIT_HEIGHT = "EditHeight";
	const std::string SCREEN_WIDTH = "ScreenWidth";
	const std::string SCREEN_HEIGHT = "ScreenHeight";
        const std::string DASHER_FONTSIZE = "DasherFontSize";
        const std::string DASHER_DIMENSIONS = "NumberDimensions";
        const std::string DASHER_EYETRACKER = "EyetrackerMode";
        const std::string UNIFORM = "UniformTimes1000";
	const std::string YSCALE = "YScaling";
	const std::string MOUSEPOSDIST = "MousePositionBoxDistance";

	// string options
	const std::string ALPHABET_ID = "AlphabetID";
	const std::string COLOUR_ID = "ColourID";
	const std::string DASHER_FONT = "DasherFont";
	const std::string EDIT_FONT = "EditFont";
}
}


void Dasher::CDasherSettingsInterface::SettingsDefaults(CSettingsStore* Store)
{
	using namespace Dasher;
	using namespace Keys;
	using namespace Opts;
	
	Store->SetLongDefault(MAX_BITRATE_TIMES100, 150);
	this->ChangeMaxBitRate(Store->GetLongOption(MAX_BITRATE_TIMES100)/100.0);
	
	Store->SetBoolDefault(TIME_STAMP, true);
	this->TimeStampNewFiles(Store->GetBoolOption(TIME_STAMP));
	Store->SetBoolDefault(COPY_ALL_ON_STOP, false);
	this->CopyAllOnStop(Store->GetBoolOption(COPY_ALL_ON_STOP));

	Store->SetBoolDefault(DRAW_MOUSE, false);
	this->DrawMouse(Store->GetBoolOption(DRAW_MOUSE));

	Store->SetBoolDefault(DRAW_MOUSELINE, true);
	this->DrawMouseLine(Store->GetBoolOption(DRAW_MOUSELINE));

	Store->SetLongDefault(FILE_ENCODING, AlphabetDefault);
	this->SetFileEncoding((FileEncodingFormats) Store->GetLongOption(FILE_ENCODING));
	
	Store->SetBoolDefault(SHOW_SLIDER, true);
	this->ShowSpeedSlider(Store->GetBoolOption(SHOW_SLIDER));
	Store->SetBoolDefault(FIX_LAYOUT, false);
	this->FixLayout(Store->GetBoolOption(FIX_LAYOUT));
	
	// Toolbar defaults
	Store->SetBoolDefault(SHOW_TOOLBAR_TEXT, true);
	this->ShowToolbarText(Store->GetBoolOption(SHOW_TOOLBAR_TEXT));
	Store->SetBoolDefault(SHOW_LARGE_ICONS, true);
	this->ShowToolbarLargeIcons(Store->GetBoolOption(SHOW_LARGE_ICONS));

	Store->SetBoolDefault(SHOW_TOOLBAR, true);
	this->ShowToolbar(Store->GetBoolOption(SHOW_TOOLBAR));

	Store->SetLongDefault(SCREEN_ORIENTATION, Opts::LeftToRight);
	this->ChangeOrientation((ScreenOrientations) Store->GetLongOption(SCREEN_ORIENTATION));
	
	Store->SetBoolDefault(START_MOUSE, true);
	this->StartOnLeft(Store->GetBoolOption(START_MOUSE));

	Store->SetBoolDefault(START_SPACE, false);
	this->StartOnSpace(Store->GetBoolOption(START_SPACE));

	Store->SetBoolDefault(KEY_CONTROL, false);
	this->KeyControl(Store->GetBoolOption(KEY_CONTROL));

	Store->SetBoolDefault(DASHER_DIMENSIONS, false);
	this->SetDasherDimensions(Store->GetBoolOption(DASHER_DIMENSIONS));

	Store->SetBoolDefault(DASHER_EYETRACKER, false);
	this->SetDasherEyetracker(Store->GetBoolOption(DASHER_EYETRACKER));

	Store->SetBoolDefault(WINDOW_PAUSE, false);
	this->WindowPause(Store->GetBoolOption(WINDOW_PAUSE));

	// This has to be done before the alphabet is set
	Store->SetBoolDefault(CONTROL_MODE, false);
	this->ControlMode(Store->GetBoolOption(CONTROL_MODE));

	// The following standard options don't have sensible cross-platform or cross-language defaults.
	// "" or 0 will have to mean "do something sensible for this user and platform"
	// The user may have saved a preference for some of these options though:
	this->ChangeColours(Store->GetStringOption(COLOUR_ID));
	
	this->ChangeAlphabet(Store->GetStringOption(ALPHABET_ID));

	// FIXME - need to work out why this breaks stuff
	//	this->ChangeLanguageModel(Store->GetLongOption(LANGUAGE_MODEL_ID));
	this->ChangeView(Store->GetLongOption(VIEW_ID));
	
	// Fonts
	this->SetEditFont(Store->GetStringOption(EDIT_FONT), Store->GetLongOption(EDIT_FONT_SIZE));
	this->SetDasherFont(Store->GetStringOption(DASHER_FONT));
	Store->SetLongDefault(DASHER_FONTSIZE, Opts::FontSize(Normal));
	this->SetDasherFontSize(Dasher::Opts::FontSize(Store->GetLongOption(DASHER_FONTSIZE)));

	// Window Geometry
	Store->SetLongDefault(EDIT_HEIGHT,75);
	this->SetEditHeight(Store->GetLongOption(EDIT_HEIGHT));
	Store->SetLongDefault(SCREEN_WIDTH,400);
	Store->SetLongDefault(SCREEN_HEIGHT,500);
	this->SetScreenSize(Store->GetLongOption(SCREEN_WIDTH), Store->GetLongOption(SCREEN_HEIGHT));

	Store->SetBoolDefault(KEYBOARD_MODE, false);
	this->KeyboardMode(Store->GetBoolOption(KEYBOARD_MODE));

	Store->SetLongDefault(UNIFORM, 50 );
	this->SetUniform(Store->GetLongOption(UNIFORM));

	Store->SetLongDefault(YSCALE, 0 );
	this->SetYScale(Store->GetLongOption(YSCALE));

	Store->SetLongDefault(MOUSEPOSDIST, 50);
	this->SetMousePosDist(Store->GetLongOption(MOUSEPOSDIST));

	Store->SetBoolDefault(MOUSEPOS_START, false);
	this->MouseposStart(Store->GetBoolOption(MOUSEPOS_START));

	Store->SetBoolDefault(OUTLINE_MODE, true);
	this->OutlineBoxes(Store->GetBoolOption(OUTLINE_MODE));

	Store->SetBoolDefault(PALETTE_CHANGE, true);
	this->PaletteChange(Store->GetBoolOption(PALETTE_CHANGE));

	Store->SetBoolDefault(SPEECH_MODE, false);
	this->Speech(Store->GetBoolOption(SPEECH_MODE));
}


