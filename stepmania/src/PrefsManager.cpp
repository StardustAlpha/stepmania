#include "stdafx.h"
/*
-----------------------------------------------------------------------------
 Class: PrefsManager

 Desc: See Header.

 Copyright (c) 2001-2002 by the person(s) listed below.  All rights reserved.
	Chris Danford
-----------------------------------------------------------------------------
*/

#include "PrefsManager.h"
#include "IniFile.h"
#include "GameManager.h"
#include "GameState.h"
#include "RageException.h"
#include "RageDisplay.h"


PrefsManager*	PREFSMAN = NULL;	// global and accessable from anywhere in our program


PrefsManager::PrefsManager()
{
#ifdef _DEBUG
	m_bWindowed = true;
#else
	m_bWindowed = false;
#endif
	m_iDisplayResolution = 640;
	m_iTextureResolution = 1024;
	m_iRefreshRate = RageDisplay::REFRESH_DEFAULT;
	m_bIgnoreJoyAxes = true;
	m_bOnlyDedicatedMenuButtons = false;
#ifdef _DEBUG
	m_bShowStats = true;
#else
	m_bShowStats = false;
#endif
	m_BackgroundMode = BGMODE_ANIMATIONS;
	m_bShowDanger = true;
	m_fBGBrightness = 0.8f;
	m_bMenuTimer = true;
	m_bEventMode = false;
	m_iNumArcadeStages = 3;
	m_bAutoPlay = false;
	m_fJudgeWindowSeconds = 0.17f;
	m_fJudgeWindowPerfectPercent = 0.25f;
	m_fJudgeWindowGreatPercent = 0.50f;
	m_fJudgeWindowGoodPercent = 0.75f;
	m_fLifeDifficultyScale = 1.0f;
	m_iMovieDecodeMS = 2;
	m_bUseBGIfNoBanner = false;
	m_bDelayedEscape = true;
	m_bHowToPlay = true;
	m_bArcadeOptionsNavigation = false;
	m_iUnloadTextureDelaySeconds = 60*30;	// 30 mins
	m_bCoinOpMode = true;

	/* I'd rather get occasional people asking for support for this even though it's
	 * already here than lots of people asking why songs aren't being displayed. */
	m_bHiddenSongs = false;
	m_bVsync = true;

	ReadGlobalPrefsFromDisk( true );
}

PrefsManager::~PrefsManager()
{
	SaveGlobalPrefsToDisk();
	SaveGamePrefsToDisk();
}

 void PrefsManager::ReadGlobalPrefsFromDisk( bool bSwitchToLastPlayedGame )
{
	IniFile ini;
	ini.SetPath( "StepMania.ini" );
	if( !ini.ReadFile() )
		return;		// could not read config file, load nothing

	ini.GetValueB( "Options", "Windowed",					m_bWindowed );
	ini.GetValueI( "Options", "DisplayResolution",			m_iDisplayResolution );
	ini.GetValueI( "Options", "TextureResolution",			m_iTextureResolution );
	ini.GetValueI( "Options", "RefreshRate",				m_iRefreshRate );
	ini.GetValueB( "Options", "IgnoreJoyAxes",				m_bIgnoreJoyAxes );
	ini.GetValueB( "Options", "UseDedicatedMenuButtons",	m_bOnlyDedicatedMenuButtons );
	ini.GetValueB( "Options", "ShowStats",					m_bShowStats );
	ini.GetValueI( "Options", "BackgroundMode",				(int&)m_BackgroundMode );
	ini.GetValueB( "Options", "ShowDanger",					m_bShowDanger );
	ini.GetValueF( "Options", "BGBrightness",				m_fBGBrightness );
	ini.GetValueB( "Options", "MenuTimer",					m_bMenuTimer );
	ini.GetValueB( "Options", "EventMode",					m_bEventMode );
	ini.GetValueI( "Options", "NumArcadeStages",			m_iNumArcadeStages );
	ini.GetValueB( "Options", "AutoPlay",					m_bAutoPlay );
	ini.GetValueF( "Options", "JudgeWindowSeconds",			m_fJudgeWindowSeconds );
	ini.GetValueF( "Options", "JudgeWindowPerfectPercent",	m_fJudgeWindowPerfectPercent );
	ini.GetValueF( "Options", "JudgeWindowGreatPercent",	m_fJudgeWindowGreatPercent );
	ini.GetValueF( "Options", "JudgeWindowGoodPercent",		m_fJudgeWindowGoodPercent );
	ini.GetValueF( "Options", "LifeDifficultyScale",		m_fLifeDifficultyScale );
	ini.GetValueI( "Options", "MovieDecodeMS",				m_iMovieDecodeMS );
	ini.GetValueB( "Options", "UseBGIfNoBanner",			m_bUseBGIfNoBanner );
	ini.GetValueB( "Options", "DelayedEscape",				m_bDelayedEscape );
	ini.GetValueB( "Options", "HiddenSongs",				m_bHiddenSongs );
	ini.GetValueB( "Options", "Vsync",						m_bVsync );
	ini.GetValueB( "Options", "HowToPlay",					m_bHowToPlay );
	ini.GetValueB( "Options", "ArcadeOptionsNavigation",	m_bArcadeOptionsNavigation );
	ini.GetValue ( "Options", "DWIPath",					m_DWIPath );
	ini.GetValueI( "Options", "UnloadTextureDelaySeconds",	m_iUnloadTextureDelaySeconds );
	ini.GetValueB( "Options", "CoinOpMode",					m_bCoinOpMode );

	m_asAdditionalSongFolders.RemoveAll();
	CString sAdditionalSongFolders;
	ini.GetValue( "Options", "AdditionalSongFolders", sAdditionalSongFolders );
	split( sAdditionalSongFolders, ",", m_asAdditionalSongFolders, true );

	if( bSwitchToLastPlayedGame )
	{
		Game game;
		if( ini.GetValueI("Options", "Game", (int&)game) )
			GAMESTATE->m_CurGame = game;
	}
}


void PrefsManager::SaveGlobalPrefsToDisk()
{
	IniFile ini;
	ini.SetPath( "StepMania.ini" );

	ini.SetValueB( "Options", "Windowed",					m_bWindowed );
	ini.SetValueI( "Options", "DisplayResolution",			m_iDisplayResolution );
	ini.SetValueI( "Options", "TextureResolution",			m_iTextureResolution );
	ini.SetValueI( "Options", "RefreshRate",				m_iRefreshRate );
	ini.SetValueB( "Options", "IgnoreJoyAxes",				m_bIgnoreJoyAxes );
	ini.SetValueB( "Options", "UseDedicatedMenuButtons",	m_bOnlyDedicatedMenuButtons );
	ini.SetValueB( "Options", "ShowStats",					m_bShowStats );
	ini.SetValueI( "Options", "BackgroundMode",				m_BackgroundMode);
	ini.SetValueB( "Options", "ShowDanger",					m_bShowDanger );
	ini.SetValueF( "Options", "BGBrightness",				m_fBGBrightness );
	ini.SetValueB( "Options", "EventMode",					m_bEventMode );
	ini.SetValueB( "Options", "MenuTimer",					m_bMenuTimer );
	ini.SetValueI( "Options", "NumArcadeStages",			m_iNumArcadeStages );
	ini.SetValueB( "Options", "AutoPlay",					m_bAutoPlay );
	ini.SetValueF( "Options", "JudgeWindowSeconds",			m_fJudgeWindowSeconds );
	ini.SetValueF( "Options", "JudgeWindowPerfectPercent",	m_fJudgeWindowPerfectPercent );
	ini.SetValueF( "Options", "JudgeWindowGreatPercent",	m_fJudgeWindowGreatPercent );
	ini.SetValueF( "Options", "JudgeWindowGoodPercent",		m_fJudgeWindowGoodPercent );
	ini.SetValueF( "Options", "LifeDifficultyScale",		m_fLifeDifficultyScale );
	ini.SetValueI( "Options", "MovieDecodeMS",				m_iMovieDecodeMS );
	ini.SetValueB( "Options", "UseBGIfNoBanner",			m_bUseBGIfNoBanner );
	ini.SetValueB( "Options", "DelayedEscape",				m_bDelayedEscape );
	ini.SetValueB( "Options", "HiddenSongs",				m_bHiddenSongs );
	ini.SetValueB( "Options", "Vsync",						m_bVsync );
	ini.SetValueB( "Options", "HowToPlay",					m_bHowToPlay );
	ini.SetValueB( "Options", "ArcadeOptionsNavigation",	m_bArcadeOptionsNavigation );
	ini.SetValue ( "Options", "DWIPath",					m_DWIPath );
	ini.SetValueI( "Options", "UnloadTextureDelaySeconds",	m_iUnloadTextureDelaySeconds );
	ini.SetValueB( "Options", "CoinOpMode",					m_bCoinOpMode );

	ini.SetValue( "Options", "AdditionalSongFolders", join(",", m_asAdditionalSongFolders) );

	ini.SetValueI( "Options", "Game",	GAMESTATE->m_CurGame );

	ini.WriteFile();
}

void PrefsManager::ReadGamePrefsFromDisk()
{
	if( !GAMESTATE )
		return;

	CString sGameName = GAMESTATE->GetCurrentGameDef()->m_szName;
	IniFile ini;
	ini.SetPath( sGameName+"Prefs.ini" );
	ini.ReadFile();	// it's OK if this fails

	CString sAnnouncer = sGameName, sTheme = sGameName, sNoteSkin = sGameName;

	// if these calls fail, the three strings will keep the initial values set above.
	ini.GetValue( "Options", "Announcer",		sAnnouncer );
	ini.GetValue( "Options", "Theme",			sTheme );
	ini.GetValue( "Options", "NoteSkin",		sNoteSkin );

	// it's OK to call these functions with names that don't exist.
	ANNOUNCER->SwitchAnnouncer( sAnnouncer );
	THEME->SwitchTheme( sTheme );
	GAMEMAN->SwitchNoteSkin( sNoteSkin );
}

void PrefsManager::SaveGamePrefsToDisk()
{
	if( !GAMESTATE )
		return;

	CString sGameName = GAMESTATE->GetCurrentGameDef()->m_szName;
	IniFile ini;
	ini.SetPath( sGameName+"Prefs.ini" );

	ini.SetValue( "Options", "Announcer",		ANNOUNCER->GetCurAnnouncerName() );
	ini.SetValue( "Options", "Theme",			THEME->GetCurThemeName() );
	ini.SetValue( "Options", "NoteSkin",		GAMEMAN->GetCurNoteSkin() );

	ini.WriteFile();
}


int PrefsManager::GetDisplayHeight()
{
	switch( m_iDisplayResolution )
	{
	case 1280:	return 1024;	break;
	case 1024:	return 768;	break;
	case 800:	return 600;	break;
	case 640:	return 480;	break;
	case 512:	return 384;	break;
	case 400:	return 300;	break;
	case 320:	return 240;	break;
	default:	throw RageException( "Invalid DisplayWidth '%d'", m_iDisplayResolution );
	}
}
