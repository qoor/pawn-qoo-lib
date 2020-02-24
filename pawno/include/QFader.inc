/****************************************************
				Fade Camera Function
					Version: v2.0
					Made by: Qoo
* MIT License
* 
* Copyright (c) 2020 Qoo
* 
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
* 
* The above copyright notice and this permission notice shall be included in all
* copies or substantial portions of the Software.
* 
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.

****************************************************/

#if defined _FadeFunc_included
	#endinput
#endif
#define _FadeFunc_included
#pragma library fadefunc

// FadeCamera 함수의 timeToFade 값은 0.02부터 유효합니다.

/*개선 사항:
v1.0: 최초 릴리즈
v1.5: 최적화 및 코드 길이 축소
v2.0:
	1. timeToFade값 범위 대폭 개선
	2. timeToFade값이 낮을 경우 필요 이상으로 많은 업데이트가 이루어짐
		ㄴ 최소 62.5프레임으로 동작하고 timeToFade값이 5.0인 경우부터는 프레임 수를 낮춰서 시간을 맞춤
*/

// 사용법: FadeCamera(플레이어ID, Fade 여부(true = 화면이 걷어짐, false = 화면이 가려짐), 소요 시간(소수점이며, 1.0은 1000ms 즉 1초임.), red (0~255), green (0~255), blue(0~255));

//***************************************************
static fadeScreenColor[MAX_PLAYERS];
static fadeScreenCount[MAX_PLAYERS];
static fadeScreenType[MAX_PLAYERS];
static fadeScreenTimer[MAX_PLAYERS];
static fadeScreenSpeed[MAX_PLAYERS];
static fadeScreenTime[MAX_PLAYERS];

static Text: fadeScreen[MAX_PLAYERS];
//***************************************************

//***************************************************
forward FadeCameraCore(playerid);
//***************************************************

//***************************************************
stock FadeCamera(playerid, fadeIn, Float: timeToFade = 1.0, red = 0, green = 0, blue = 0)
{
	if(IsPlayerConnected(playerid) == 0 || IsPlayerNPC(playerid)) return 0;
	if(fadeScreenType[playerid] == fadeIn) return 0;
	fadeScreenType[playerid] = fadeIn;
	if(fadeIn == 0) fadeScreenColor[playerid] = RGBToHex(red, green, blue);
	else fadeScreenColor[playerid] += 255;
	if(timeToFade <= 0)
	{
		fadeScreenCount[playerid] = 0;
		if(fadeIn) TextDrawHideForPlayer(playerid, fadeScreen[playerid]);
		else
		{
			TextDrawBoxColor(fadeScreen[playerid], fadeScreenColor[playerid] + 255);
			TextDrawShowForPlayer(playerid, fadeScreen[playerid]);
		}
	}
	else
	{
		new oldTime = fadeScreenTime[playerid];
		fadeScreenSpeed[playerid] = floatround(4.25 / timeToFade, floatround_floor);
		if(fadeScreenSpeed[playerid] <= 1)
		{
			if (fadeScreenSpeed[playerid] != 1) fadeScreenSpeed[playerid] = 1;
			fadeScreenTime[playerid] = floatround(1000 * timeToFade / 255, floatround_floor);
		}
		else fadeScreenTime[playerid] = 16;
		if(fadeScreenTimer[playerid] != 0 && fadeScreenTime[playerid] != oldTime)
		{
			KillTimer(fadeScreenTimer[playerid]);
			fadeScreenTimer[playerid] = 0;
		}
		if(fadeScreenTimer[playerid] == 0) fadeScreenTimer[playerid] = SetTimerEx("FadeCameraCore", fadeScreenTime[playerid], 1, "i", playerid);
	}
	return 1;
}

static RGBToHex(red, green, blue)
{
	return (red << 24) | (green << 16) | (blue << 8);
}
//***************************************************

//***************************************************
public FadeCameraCore(playerid)
{
	new Text: tText = fadeScreen[playerid];
	if(fadeScreenCount[playerid] == 0) TextDrawBoxColor(tText, fadeScreenColor[playerid]);
	else
	{
		if(fadeScreenType[playerid] == 0) TextDrawBoxColor(tText, fadeScreenColor[playerid] + fadeScreenCount[playerid]);
		else TextDrawBoxColor(tText, fadeScreenColor[playerid] - fadeScreenCount[playerid]);
	}
	TextDrawShowForPlayer(playerid, tText);
	if((fadeScreenCount[playerid] += fadeScreenSpeed[playerid]) > 255)
	{
		if(fadeScreenType[playerid]) TextDrawHideForPlayer(playerid, tText);
		else
		{
			fadeScreenCount[playerid] = 255;
			TextDrawBoxColor(tText, fadeScreenColor[playerid] + 255);
		}
		fadeScreenCount[playerid] = 0;
		if(fadeScreenTimer[playerid] != 0)
		{
			KillTimer(fadeScreenTimer[playerid]);
			fadeScreenTimer[playerid] = 0;
		}
	}
}
//***************************************************

//***************************************************
public OnPlayerConnect(playerid)
{
	if(IsPlayerNPC(playerid) == 0)
	{
		fadeScreen[playerid] = TextDrawCreate(1.000000,1.000000,"_");
		TextDrawUseBox(fadeScreen[playerid],1);
		TextDrawTextSize(fadeScreen[playerid],639.000000,0.000000);
		TextDrawAlignment(fadeScreen[playerid],0);
		TextDrawFont(fadeScreen[playerid],3);
		TextDrawLetterSize(fadeScreen[playerid],1.000000,50.000000);
		TextDrawBoxColor(fadeScreen[playerid], 0x000000FF);
		TextDrawShowForPlayer(playerid, fadeScreen[playerid]);
	}
	
	fadeScreenColor[playerid] = 0;
	fadeScreenCount[playerid] = 0;
	fadeScreenType[playerid] = 0;
	fadeScreenSpeed[playerid] = 0;
	fadeScreenTime[playerid] = 0;

	#if defined FADE_OnPlayerConnect
		return FADE_OnPlayerConnect(playerid);
	#else
		return 1;
	#endif
}

#if defined FADE_OnPlayerConnect
	forward FADE_OnPlayerConnect(playerid);
#endif
#if defined _ALS_OnPlayerConnect
	#undef OnPlayerConnect
#else
	#define _ALS_OnPlayerConnect
#endif
#define OnPlayerConnect FADE_OnPlayerConnect

public OnPlayerDisconnect(playerid, reason)
{
	TextDrawDestroy(fadeScreen[playerid]);
	KillTimer(fadeScreenTimer[playerid]);
	fadeScreenTimer[playerid] = 0;
	#if defined FADE_OnPlayerDisconnect
		return FADE_OnPlayerDisconnect(playerid, reason);
	#else
		return 1;
	#endif
}

#if defined FADE_OnPlayerDisconnect
	forward FADE_OnPlayerDisconnect(playerid, reason);
#endif
#if defined _ALS_OnPlayerDisconnect
	#undef OnPlayerDisconnect
#else
	#define _ALS_OnPlayerDisconnect
#endif
#define OnPlayerDisconnect FADE_OnPlayerDisconnect
//***************************************************
