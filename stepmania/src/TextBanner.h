/* TextBanner - Shows song title, subtitle, and artist.  Displayed on the MusicWheel. */

#ifndef TEXTBANNER_H
#define TEXTBANNER_H

#include "ActorFrame.h"
#include "BitmapText.h"
class Song;

class TextBanner : public ActorFrame
{
public:
	TextBanner();
	TextBanner( const TextBanner &cpy );
	virtual TextBanner *Copy() const;

	void LoadFromNode( const XNode* pNode );
	void Load( RString sType );	// load metrics
	void LoadFromSong( const Song *pSong );
	void LoadFromString( 
		const RString &sDisplayTitle, const RString &sTranslitTitle, 
		const RString &sDisplaySubTitle, const RString &sTranslitSubTitle, 
		const RString &sDisplayArtist, const RString &sTranslitArtist );

	// Lua
	void PushSelf( lua_State *L );

private:
	void LoadInternal( 
		const RString &sDisplayTitle, const RString &sTranslitTitle, 
		const RString &sDisplaySubTitle, const RString &sTranslitSubTitle, 
		const RString &sDisplayArtist, const RString &sTranslitArtist );

	bool m_bInitted;

	BitmapText	m_textTitle, m_textSubTitle, m_textArtist;

	RString		m_sArtistPrependString;
};

#endif

/*
 * (c) 2001-2004 Chris Danford
 * All rights reserved.
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, and/or sell copies of the Software, and to permit persons to
 * whom the Software is furnished to do so, provided that the above
 * copyright notice(s) and this permission notice appear in all copies of
 * the Software and that both the above copyright notice(s) and this
 * permission notice appear in supporting documentation.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT OF
 * THIRD PARTY RIGHTS. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR HOLDERS
 * INCLUDED IN THIS NOTICE BE LIABLE FOR ANY CLAIM, OR ANY SPECIAL INDIRECT
 * OR CONSEQUENTIAL DAMAGES, OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS
 * OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR
 * OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
 * PERFORMANCE OF THIS SOFTWARE.
 */
