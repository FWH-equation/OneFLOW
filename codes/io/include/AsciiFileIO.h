/*---------------------------------------------------------------------------*\
OneFLOW - LargeScale Multiphysics Scientific Simulation Environment
Copyright (C) 2017-2019 He Xin and the OneFLOW contributors.
-------------------------------------------------------------------------------
License
This file is part of OneFLOW.

OneFLOW is free software: you can redistribute it and/or modify it
under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

OneFLOW is distributed in the hope that it will be useful, but WITHOUT
ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
for more details.

You should have received a copy of the GNU General Public License
along with OneFLOW.  If not, see <http://www.gnu.org/licenses/>.

\*---------------------------------------------------------------------------*/

#pragma once
#include <fstream>
#include <sstream>
#include "BasicIO.h"
#include "HXDefine.h"
using namespace std;

BeginNameSpace( ONEFLOW )

const string whiteSpace = " ";

void SetDefaultLine( std::string * defaultLineIn );
std::string * GetDefaultLine();

void SetDefaultSeparatorOfWord( std::string * separatorOfWordIn );
std::string * GetDefaultSeparatorOfWord();
typedef streamsize StreamSize;

class CommentLineClass;
class AsciiFileRead
{
public:
	AsciiFileRead();
	~AsciiFileRead();
protected:
	std::string * line, * separator;
	fstream * file;
	int setfileFlag;
protected:
	std::string fileName;
	ios_base::openmode fileOpenMode;
	StreamSize filePosition;
	CommentLineClass * commentLineClass;
public:
	void OpenFile( const string & fileName, const ios_base::openmode & fileOpenMode );
    void OpenPrjFile( const string & fileName, const ios_base::openmode & fileOpenMode );
	void CloseFile();
	void MarkCurrentFilePosition();
	void MoveToPreviousFilePosition();
	string & GetCurrentLine() { return * this->line; };
public:
	void ResetCommentString( StringField &commentStringList );
	void SetDefaultFile     ( std::fstream * defaultFileIn   );
	void SetDefaultSeparator( const std::string & separatorIn   ) { * this->separator = separatorIn; };

	std::string  * GetDefaultLine     () { return line; }
	std::fstream * GetDefaultFile     () { return file; }
	std::string  * GetDefaultSeparator() { return separator; }
public:
	void SetLineContent( const std::string & lineContent ) { * this->line = lineContent; };
	void ShiftLineContent( int numberOfChars ) { * this->line = ( * this->line ).substr( numberOfChars ); }

	bool ReadNextMeaningfulLine();
	bool ReachTheEndOfFile();
public:
	void SkipLines( int numberOfLinesToSkip );
	bool ReadNextNonEmptyLine();
    bool NextWordIsEmpty();
	void DumpLineContentToScreen();
	std::string ReadNextWord();
	std::string ReadNextWord( const std::string & separator );
    std::string ReadNextTrueWord();
	std::string ReadNextWordToLowerCase();
	std::string ReadNextWordToLowerCase( const std::string & separator );
public:
	void SkipReadSymbol( const string & stringSymbol );
	void SkipReadWholeBlock();
public:
	template < typename T >
    friend inline AsciiFileRead & operator >> ( AsciiFileRead & textFileRead, T & value )
    {
		fstream & file = * textFileRead.GetDefaultFile();
        file >> value;
        return textFileRead;
    }

	template < typename T >
	T ReadNextDigit( ios_base & ( * f )( ios_base & ) = & std::dec )
	{
        std::string word = AsciiFileRead::ReadNextTrueWord();
		T value = StringToDigit< T >( word, f );
		return value;
	}

	template < typename T >
	T ReadNextDigit( int & num, ios_base & ( * f )( ios_base & ) = & std::dec )
	{
        std::string word = AsciiFileRead::ReadNextTrueWord();
        num = 1;
        bool flag = FindString( word, "*" );
        if ( flag )
        {
            string word_num = FindNextWord( word, "*" );
            num = StringToDigit< int >( word_num, f );
            word = FindNextWord( word, "*" );
        }
		T value = StringToDigit< T >( word, f );
		return value;
	}

};

class CommentLineClass
{
public:
	CommentLineClass();
	~CommentLineClass();
public:
	StringField commentdata;
public:
	void AddString( const string & cs );
	void ResetCommentString(StringField& commentStringList);
};

string  ReadNextWord();
string  ReadNextWord( const std::string & separatorOfWord );
string  ReadNextWord( std::string & source, const std::string & separatorOfWord );

string  ReadNextWordToLowerCase();
string  ReadNextWordToLowerCase( const std::string & separatorOfWord );

template < typename T >
inline T ReadNextDigit( ios_base & ( * f )( ios_base & ) = & std::dec )
{
	std::string * separatorOfWord = ONEFLOW::GetDefaultSeparatorOfWord();
	std::string * defaultLine     = ONEFLOW::GetDefaultLine();

    string word = ONEFLOW::FindNextWord( * defaultLine, * separatorOfWord );
	T value = ONEFLOW::StringToDigit< T >( word, f );
	return value;
}

template < typename T >
inline T ReadNextDigit( std::string & source, const std::string & separatorOfWord, ios_base & ( * f )( ios_base & ) = & std::dec )
{
    string word = ONEFLOW::FindNextWord( source, separatorOfWord );
	T value = ONEFLOW::StringToDigit< T >( word, f );
	return value;
}

bool IsEmpty( fstream & file );

bool IsEmptyLine  ( const string & line );
bool IsCommentLine( const string & line );
bool IsCommentLine(const string& line, StringField& comlist);

EndNameSpace