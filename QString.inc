//===========================================
//					QString
//				version: v0.0.3
//				  author: Qoo
//===========================================

#if defined _QString_included
	#endinput
#endif
#define _QString_included
#pragma library QString

#define IsNull(%0) ((%0[0] == 0) || (%0[0] == 1 && %0[1] == 0))
#define strresult(%0,%1,%2) new length = strlen(%1); while((%2 < length) && (%1[%2] <= ' ')) %2 ++; strmid(%0, %1, %2, length, sizeof %0)
#define strcpy(%0,%1) strcat((%0[0] = 0, %0), %1)

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

stock charfind(const string[], findChar, bool: reverseSearch = false, startIndex = 0)
{
	new length = strlen(string);

	if (startIndex < 0 || startIndex >= length)
	{
		return -1;
	}

	new index = startIndex;
	
	if (!reverseSearch)
	{
		while (index < length)
		{
			if (string[index] == findChar)
			{
				return index;
			}
			
			++index;
		}
	}
	else if (reverseSearch)
	{
		if (startIndex == 0)
		{
			index = length - 1;
		}

		while (index >= 0)
		{
			if (string[index] == findChar)
			{
				return index;
			}
			
			--index;
		}
	}
	
	return -1;
}

stock strfix(source[])
{
	if (source[0] == 0) source[0] = '\1';
}

stock ParamInitialize(outBase[], outParams[], const source[], baseSize = sizeof(outBase), paramsSize = sizeof(outParams), delimiter = ' ')
{
	new paramStartIndex = charfind(source, delimiter);
	new length = strlen(source);

	outBase[0] = '\0';
	outParams[0] = '\0';

	if (paramStartIndex == -1 || paramStartIndex + 1 >= length || source[paramStartIndex + 1] <= 1)
	{
		strmid(outBase, source, 0, (paramStartIndex != -1) ? paramStartIndex : length, baseSize);
		strfix(outBase);
	}
	else
	{
		strmid(outBase, source, 0, paramStartIndex, baseSize);
		strfix(outBase);

		while (source[paramStartIndex] == delimiter)
		{
			++paramStartIndex;
		}

		if (paramStartIndex < length)
		{
			strmid(outParams, source, paramStartIndex, length, paramsSize);
			strfix(outParams);
		}
	}
}

stock GetParamPoint(const params[], index, &start, &end, delimiter = ' ')
{
	start = -1;
	end = -1;

	if (IsNull(params))
	{
		return false;
	}

	new paramsLength = strlen(params);
	new const paramCheckMax = paramsLength - 1;
	new i = 0;
	new paramCount = 0;
	new paramStartIndex = i;
	new bool: paramFound = (index == 0);

	for (; i < paramCheckMax; ++i)
	{
		if (params[i] == delimiter)
		{
			if (paramFound)
			{
				break;
			}
			else if (i + 1 < paramsLength && params[i + 1] > 1 && params[i + 1] != delimiter)
			{
				if ((++paramCount) == index)
				{
					paramFound = true;
					paramStartIndex = i + 1;
				}
			}
		}
	}

	if (paramFound)
	{
		start = paramStartIndex;
		end = i + _: (i == paramCheckMax);
	}

	return paramFound;
}

stock IsValidParamIndex(const params[], index)
{
	new temp;

	return GetParamPoint(params, index, temp, temp);
}

stock GetParamString(dest[], const params[], index, size = sizeof(dest), delimiter = ' ')
{
	new start, end;

	if (GetParamPoint(params, index, start, end, delimiter))
	{
		strmid(dest, params, start, end, size);
		return 1;
	}

	return 0;
}

stock GetParamInt(&var, const params[], index, delimiter = ' ')
{
	new dest[11];
	
	if (GetParamString(dest, params, index, _, delimiter) != 0)
	{
		var = strval(dest);
		return 1;
	}

	return 0;
}

stock GetParamFloat(&Float: var, const params[], index, delimiter = ' ')
{
	new dest[32];
	
	if (GetParamString(dest, params, index, _, delimiter) != 0)
	{
		var = floatstr(dest);
		return 1;
	}

	return 0;
}

stock MergeParams(dest[], const params[], startIndex = 0, size = sizeof(dest), delimiter = ' ')
{
	new start, end;

	if (GetParamPoint(params, startIndex, start, end))
	{
		new i;
		new length = strlen(params);

		for (i = length - 1; i >= 0; --i)
		{
			if (params[i] != delimiter && params[i] > 1)
			{
				length = i + 1;
				break;
			}
		}

		strmid(dest, params, start, length, size);
		return 1;
	}
	
	strcpy(dest, "\1", size);
	return 0;
}
