// =============================================================================
//                                  QString
//                              version: v0.1.0
//                                author: Qoo
//
// MIT License
// 
// Copyright (c) 2020 Qoo
// 
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
// 
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
// 
// =============================================================================

#if defined _QString_included
	#endinput
#endif
#define _QString_included
#pragma library QString

#if !defined TRUE
	stock bool: TRUE = true;
#endif

#if !defined FALSE
	stock bool: FALSE = false;
#endif

#define IsNull(%0) ((%0[0] == 0) || (%0[0] == 1 && %0[1] == 0))
#define strresult(%0,%1,%2) do { new length = strlen(%1); while((%2 < length) && (%1[%2] <= ' ')) %2 ++; strmid(%0, %1, %2, length, sizeof %0) } while (FALSE)
#define strcpy(%0,%1) strcat((%0[0] = 0, %0), %1)

static stock strchr_null(const string[], character)
{
	new bool: TRUE = true;
	new i = 0;

	while (TRUE)
	{
		if (string[i] == character || string[i] == '\0'
			|| (string[i] == '\1' && string[i + 1] == '\0'))
			return i;
		
		++i;
	}

	return -1;
}

stock strtok(const strings[], &index)
{
	new length = strlen(strings);
	while ((index < length) && (strings[index] <= ' '))
	{
		index++;
	}
	new offset = index;
	new result[20];
	while ((index < length) && (strings[index] > ' ') && ((index - offset) < (sizeof(result) - 1)))
	{
		result[index - offset] = strings[index];
		index++;
	}
	result[index - offset] = EOS;
	return result;
}

stock split(const strsrc[], strdest[][], delimiter)
{
	new i, li, length = strlen(strsrc);
	new aNum;
	new len;
	while(i <= length){
		if(strsrc[i]==delimiter || i==length){
			len = strmid(strdest[aNum], strsrc, li, i, 128);
			strdest[aNum][len] = 0;
			li = i+1;
			aNum++;
		}
		i++;
	}
	return 1;
}

stock strchr(const string[], character)
{
	for (new i = 0; string[i]; ++i)
	{
		if (string[i] == character)
			return i;
	}

	return -1;
}

stock strrchr(const string[], character)
{
	new i = -1;

	while (string[++i]) {}
	for ( ; i >= 0; --i)
	{
		if (string[i] == character)
			break;
	}

	return i;
}

stock strfix(source[])
{
	if (source[0] == 0)
	{
		source[0] = '\1';
		source[1] = '\0';
	}
}

stock strtok_r(string[], const delimiters[], &save_index, size = sizeof(string))
{
	new index = save_index;
	new end = 0;
	
	if (index >= size || string[index] == '\0' ||
		(index + 1 < size
			&& string[index] == '\1' && string[index + 1] == '\0'))
		return -1;
	
	index += strspn(string[index], delimiters);
	if (string[index] == '\0')
	{
		save_index = index;
		return -1;
	}

	end = index + strcspn(string[index], delimiters);
	if (string[end] == '\0')
	{
		save_index = end;
		return index;
	}

	string[end] = '\0';
	save_index = end + 1;
	return index;
}

stock strspn(const string[], const accept[])
{
	if (IsNull(accept))
		return 0;
	
	if (accept[1] == '\0' || (accept[1] == '\1' && accept[2] == '\0'))
	{
		new match_count = 0;
		new character = accept[0];

		for ( ; string[match_count] == character; ++match_count) {}
		return match_count;
	}

	new table[256 char];
	new index = -1;

	do
		table{accept[++index]} = 1;
	while (accept[index]);

	if (!table{string[0]}) return 0;
	if (!table{string[1]}) return 1;
	if (!table{string[2]}) return 2;
	if (!table{string[3]}) return 3;

	index = 0;

	new c0, c1, c2, c3;

	do {
		index += 4;
		c0 = table{string[index]};
		c1 = table{string[index + 1]};
		c2 = table{string[index + 2]};
		c3 = table{string[index + 3]};
	} while ((c0 & c1 & c2 & c3) != 0);

	return ((c0 & c1) == 0) ? index + c0 : index + c2 + 2;
}

stock strcspn(const string[], const reject[])
{
	if (reject[0] == '\0' || reject[1] == '\0'
		|| (reject[1] == '\1' && reject[2] == '\0'))
	{
		new char_index = strchr_null(string, reject[0]);
		return (char_index == -1) ? 0 : char_index;
	}

	new table[256 char];
	new index = -1;

	do
		table{reject[++index]} = 1;
	while (reject[index]);

	if (table{string[0]}) return 0;
	if (table{string[1]}) return 1;
	if (table{string[2]}) return 2;
	if (table{string[3]}) return 3;

	index = 0;

	new c0, c1, c2, c3;

	do {
		index += 4;
		c0 = table{string[index]};
		c1 = table{string[index + 1]};
		c2 = table{string[index + 2]};
		c3 = table{string[index + 3]};
	} while ((c0 | c1 | c2 | c3) == 0);

	return ((c0 | c1) != 0) ? index - c0 + 1 : index - c2 + 3;
}
