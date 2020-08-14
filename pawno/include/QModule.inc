//==============================================================================
//                                 QModule
//
//                              version: v7.4
//                               author: Qoo
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
//==============================================================================

/*개선 사항:
v1.0: 최초 릴리즈 (LA:RP 모듈 알고리즘을 참고했음.) Thank you for Acu.
v2.0:
	1. 'public:함수명' 문법 제거
	2. 문자열 관련 핸들러 처리 최적화
		ㄴ 기존에는 서버 크래시 방지를 위해 공백 문자를 방지하고자 문자열 변수를 만들고 콜백 파라미터의 문자열을 복사해서 전송했으나,
			문자열 내용이 비어있는 경우 \1 문자를, 그렇지 않은 경우 문자열을 그대로 전송하여 속도를 개선함.
		ㄴ 자세한 사항은 strfix 매크로 함수를 참고.
	3. 핸들러 호출을 도중에 끝낼 수 있는 EventInfoWithSuspend(이벤트ID, 이벤트 끝낼 반환값, 파라미터 포멧, 파마리터) 함수가 추가되었습니다.
	4. strfix 매크로 함수가 추가되었습니다.
		ㄴ 모든 이벤트들은 문자열 값을 핸들러에게 전달할 때 반드시 strfix 매크로 함수를 거쳐서 보내야 합니다. 그렇지 않으면 크래시가 일어납니다.
	5. OnPlayerCommandTextFail(playerid, const cmdtext[], const cmd[]) 콜백이 추가되었습니다.
		ㄴ OnPlayerCommandText의 핸들러에서 명령어를 찾지 못하면 해당 콜백이 호출됩니다.
v4.0:
	1. HandlerLoop (이벤트ID) 매크로가 추가되었습니다.
	2. HandlerAction (이벤트ID, 파라미터 포멧, 파라미터) 매크로 함수가 추가되었습니다.
v5.0:
	1. EventInfo, EventInfoWithSuspend 함수가 제거되고 TriggerEvent(이벤트ID, 이벤트 끝낼 반환값, 파라미터 포멧, 파마리터) 함수가 추가되었습니다.
	2. 단순히 함수를 호출하는 함수였던 TriggerEvent가 실제로 등록된 이벤트를 호출하는 함수로 개선되었습니다.
v5.1:
	1. AddEventHandler 함수에 우선순위 기능(priority 파라미터. default = MAX_EVENT_HANDLERS / 2)이 추가되었습니다.
	2. TriggerEventWithBreak, TriggerEventNoSuspend 함수가 추가되었습니다.
v5.2:
	1. MainScript(), InitScript("모듈명") 함수가 각각 main(), InitModule("모듈명")으로 변경되었습니다.
	2. IsValidHandlerEvent(eventid)가 IsValidEvent(eventid)로 변경되었습니다.
v5.3:
	1. OnPlayerCommandTextFail 콜백을 제거하고 명령어를 찾지 못할 시 D_PlayerCommandTextFail 이벤트가 호출됩니다.
		ㄴ 기존의 OnPlayerCommandTextFail 콜백에 쓰던 파라미터 형식은 그대로 입니다.
	2. QMODULE_ENGINE_VERSION 매크로가 추가되었습니다.
v5.4:
	1. 문자열 파라미터가 포함되는 native 이벤트들의 성능을 최적화했습니다.
		ㄴ 앞으로 문자열 파라미터가 포함되는 사용자 정의 이벤트를 호출하기 전에 미리 문자열 파라미터들은 strfix 함수를 거쳐야 합니다.
	2. strfix(const source[]) 매크로 함수가 strfix(source[]) 함수로 변경되었습니다.
v5.5:
	1. 플레이어 명령어 처리에 대한 시스템을 대폭 변경하였습니다.
		ㄴ 기존에는 만약 '/1234 5678 90'이라고 입력 했을 때 playerid, cmdtext[] = "/1234 5678 90", cmd[] = "/1234" 형식으로 전달 되었고 명령어 뒤에 오는 파라미터들은 strtok로 나눴지만,
		변경 후 playerid, command[] = "/1234", params[] = "5678 90" 형식으로 전달 됩니다.
	2. GetParamPoint 함수가 추가 되었습니다.
		ㄴ const params[]: D_PlayerCommandText의 params 값이나 기타 공백으로 데이터를 나눠야 하는 문자열의 총 집합을 넣습니다.
		ㄴ index: 파라미터를 쪼개어 몇 번째 파라미터를 검색 할 것인지 알려줍니다. (파라미터 인덱스는 0부터 시작합니다.)
		ㄴ &start: index번째 파라미터의 문자열 시작 지점을 반환 합니다. 찾지 못한 경우 -1이 반환됩니다.
		ㄴ &end: index번째 파라미터의 문자열 끝 지점을 반환 합니다. 찾지 못한 경우 -1이 반환됩니다.
		ㄴ delimiter = ' ': 파라미터들을 구분하는 문자를 지정합니다. 명령어는 보통 공백으로 파라미터를 나누므로 기본값은 공백입니다.
		ㄴ 반환 값: index번째 파라미터를 찾은 경우 1을, 그렇지 않은 경우 0을 반환합니다.
	3. IsValidParamIndex 함수가 추가 되었습니다.
		ㄴ const params[]: D_PlayerCommandText의 params 값이나 기타 공백으로 데이터를 나눠야 하는 문자열의 총 집합을 넣습니다.
		ㄴ index: 파라미터를 쪼개어 몇 번째 파라미터를 검색 할 것인지 알려줍니다. (파라미터 인덱스는 0부터 시작합니다.)
		ㄴ delimiter = ' ': 파라미터들을 구분하는 문자를 지정합니다. 명령어는 보통 공백으로 파라미터를 나누므로 기본값은 공백입니다.
		ㄴ 반환 값: index번째 파라미터를 찾은 경우 1을, 그렇지 않은 경우 0을 반환 합니다.
	4. GetParamString 함수가 추가 되었습니다.
		ㄴ dest[]: index번째 파라미터의 문자열 값이 들어갈 변수를 넘겨줍니다. index번째 파라미터를 찾지 못한 경우 NULL값이 입력됩니다.
		ㄴ const params[]: D_PlayerCommandText의 params 값이나 기타 공백으로 데이터를 나눠야 하는 문자열의 총 집합을 넣습니다.
		ㄴ index: 파라미터를 쪼개어 몇 번째 파라미터를 검색 할 것인지 알려줍니다. (파라미터 인덱스는 0부터 시작합니다.)
		ㄴ size = sizeof(dest): dest 문자열의 배열 길이를 입력합니다.
		ㄴ delimiter = ' ': 파라미터들을 구분하는 문자를 지정합니다. 명령어는 보통 공백으로 파라미터를 나누므로 기본값은 공백입니다.
		ㄴ 반환 값: index번째 파라미터를 찾은 경우 1을, 그렇지 않은 경우 0을 반환합니다.
	5. GetParamInt, GetParamFloat 함수가 추가 되었습니다.
		ㄴ &var: index번째 파라미터에 들어있는 값이 들어갈 변수를 넘겨줍니다. index번째 파라미터를 찾지 못한 경우 값 변경이 이뤄지지 않습니다.
		ㄴ const params[]: D_PlayerCommandText의 params 값이나 기타 공백으로 데이터를 나눠야 하는 문자열의 총 집합을 넣습니다.
		ㄴ index: 파라미터를 쪼개어 몇 번째 파라미터를 검색 할 것인지 알려줍니다. (파라미터 인덱스는 0부터 시작합니다.)
		ㄴ delimiter = ' ': 파라미터들을 구분하는 문자를 지정합니다. 명령어는 보통 공백으로 파라미터를 나누므로 기본값은 공백입니다.
		ㄴ 반환 값: index번째 파라미터를 찾은 경우 1을, 그렇지 않은 경우 0을 반환 합니다.
	6. MergeParams 함수가 추가 되었습니다.
		ㄴ dest[]: index번째 파라미터 부터 마지막 파라미터까지 합친 문자열 값이 들어갈 변수를 넘겨줍니다. index번째 파라미터를 찾지 못한 경우 NULL값이 입력됩니다.
		ㄴ const params[]: D_PlayerCommandText의 params 값이나 기타 공백으로 데이터를 나눠야 하는 문자열의 총 집합을 넣습니다.
		ㄴ startIndex: 파라미터를 쪼개어 몇 번째 파라미터 부터 합칠 것인지 알려줍니다. (파라미터 인덱스는 0부터 시작합니다.)
		ㄴ size = sizeof(dest): dest 문자열의 배열 길이를 입력합니다.
		ㄴ delimiter = ' ': 파라미터들을 구분하는 문자를 지정합니다. 명령어는 보통 공백으로 파라미터를 나누므로 기본값은 공백입니다.
		ㄴ 반환 값: 파라미터 합치기를 성공했을 경우 1을, 그렇지 않은 경우 0을 반환 합니다.
v6.0:
	1. SA-MP 버전 0.3z와 0.3.7을 공식 지원합니다.
		ㄴ 3가지의 SA-MP 버전을 완벽히 지원합니다. (0.3d, 0.3z, 0.3.7)
		ㄴ QMODULE_SAMP_VERSION 부분을 필히 서버 버전과 일치하게 바꿔주셔야 합니다.
		ㄴ 추후 0.3.7 후속 버전이 생기더라도 0.3.7 모드로 사용 가능합니다. 단, 새로운 버전에서 추가되는 일부 콜백들은 이벤트가 존재하지 않기 때문에 직접 인클루드를 수정해 주시거나, AddEvent, TriggerEvent로 사용자 정의 이벤트를 생성해 해결 할 것을 추천합니다.
v7.0:
	1. QContainer와의 playerList 연동 옵션이 추가되었습니다.
		ㄴ QContainer를 이용하여 playerList를 사용하고 싶을 경우 QMODULE_QCONTAINER_PLAYERLIST 값을 1로 바꾸시면 됩니다.
		ㄴ QContainer를 사용하는 경우 되도록이면 옵션을 켜는 것을 추천합니다. 이 옵션을 꺼도 playerList를 모드에서 다른 방법을 써서 똑같이 사용 가능하지만, 코드가 복잡해지고 구조 이해가 힘들어집니다.
		ㄴ playerList란, 두 인클루드를 연동 시 기존의 단순 반복문을 통한 플레이어 반복문이 아니라, 접속한 유저만 빠르게 검사하고 플레이어 접속 정보를 담아둔 Container 변수입니다.
		ㄴ IsPlayerConnected 함수도 같이 후킹됩니다. playerList를 통해 빠르게 플레이어 접속 여부를 알려줍니다. 반드시 가장 마지막에 QModule을 포함해 주십시오. 그렇지 않으면 QModule보다 나중에 포함 된 인클루드들과 호환성 문제가 생길 수 있습니다.
		ㄴ 플레이어 루프문의 예시는 contloop (new i : playerList) { ... } or contloop (i : playerList) { ... } 등과 같은 형식으로 이용 가능합니다.
v7.1:
	1. Params 기능들의 구조가 약간씩 변경되었고, 성능이 향상되었습니다.
		ㄴ 매 함수들마다 맨 앞 인자로 값이 들어갈 변수를 지정해야 합니다.
		ㄴ Ex) new intVar; GetParamInt(intVar, params, 0);
		ㄴ GetParamInt와 GetParamFloat는 더이상 반환값으로 결과값이 들어가는 것이 아닌, 값이 올바르게 추출되었는지에 대한 여부를 반환합니다.
		ㄴ new intVar; if (GetParamInt(intVar, params, 0) == 0) { ... } 이건 '만약 0번째 파라미터를 찾을 수 없을 경우'에 대한 조건문이고 파라미터를 찾았다면 이 조건문은 충족되지 않으며, intVar에 결과값이 들어갑니다.
		ㄴ 또한, GetParamPoint에서만 delimiter 지정이 가능했지만 이제는 모든 Params 함수들에서 delimiter을 지정할 수 있습니다.
		ㄴ v5.5의 Changelog에 있는 Params 함수들의 설명이 변경됩니다.
		ㄴ 이 업데이트 이후부터 IsValidParamIndex는 값을 활용하는 것이 아니라 오로지 검색만 할 경우와 같은 제한적인 상황에서만 사용하시는 것을 권장합니다.
v7.2:
	1. Params 기능들을 QString으로 이전하였습니다.
	2. strfix 함수를 QString으로 이전하였습니다.
	3. 일부 문자열 함수 인자들에 const를 추가하였습니다.

v7.3:
	1. SA-MP 0.3.7 미만 버전들의 지원이 종료 되었습니다.

v7.4
	1. 코드 가독성을 개선하였습니다.
	2. 잘못된 이벤트 index 참조 버그를 수정하였습니다.
	3. 네이티브 이벤트 수 검증 기능을 추가하였습니다.
	4. 일부 성능 최적화 작업이 이루어졌습니다.
*/

#if defined _QModule_included
	#endinput
#endif
#define _QModule_included
#pragma library QModule

#define QMODULE_QCONTAINER_PLAYERLIST

#include <a_samp>
#include <QString>

#if defined QMODULE_QCONTAINER_PLAYERLIST
	#include <QContainer>
#endif

#define QMODULE_ENGINE_VERSION "v7.4"

main() { return 1; }

#define main()								public __InitMain()
#define InitModule("%0")					forward LoadModule_%0(); public LoadModule_%0()

#if !defined FALSE
	stock bool: FALSE = false;
#endif

#define HandlerLoop(%0)						for (new %0_i = 0, %0_max = g_num_handlers[%0]; %0_i < %0_max; ++%0_i)
#define HandlerAction(%0,"%1"%2)			CallLocalFunction(g_handler_funcs[%0][%0_i], #%1%2)
#define TriggerEvent(%0,%1,%2)				do { HandlerLoop(%0) { if ((HandlerAction(%0, %2)) == %1) return %1; } } while (FALSE)
#define TriggerEventWithBreak(%0,%1,%2)		do { HandlerLoop(%0) { if ((HandlerAction(%0, %2)) == %1) break; } while (FALSE)
#define TriggerEventNoSuspend(%0,%1)		do { HandlerLoop(%0) { HandlerAction(%0, %1); } } while (FALSE)

#define MAX_EVENTS							128
#define MAX_EVENT_HANDLERS					128

#define MAX_MODULE_NAMES					21
#define MAX_HANDLER_FUNC_LEN				32

// DEFAULT_PRIORITY
// 기본 우선순위 값
// 우선순위 값은 0 이상일 경우 낮을 수록 우선순위가 높음
#define DEFAULT_PRIORITY					-1

enum E_SCRIPT_TYPE
{
	SCRIPT_TYPE_GAME_MODE,
	SCRIPT_TYPE_FILTER_SCRIPT
};

enum _: e_NATIVE_EVENTS
{
	D_FilterScriptInit,
	D_GameModeInit,
	D_FilterScriptExit,
	D_GameModeExit,
	D_PlayerRequestClass,
	D_PlayerConnect,
	D_PlayerDisconnect,
	D_PlayerSpawn,
	D_PlayerDeath,
	D_VehicleSpawn,
	D_VehicleDeath,
	D_PlayerText,
	D_PlayerCommandText,
	D_PlayerEnterVehicle,
	D_PlayerExitVehicle,
	D_PlayerStateChange,
	D_PlayerEnterCheckpoint,
	D_PlayerLeaveCheckpoint,
	D_PlayerEnterRaceCheckpoint,
	D_PlayerLeaveRaceCheckpoint,
	D_RconCommand,
	D_PlayerRequestSpawn,
	D_ObjectMoved,
	D_PlayerObjectMoved,
	D_PlayerPickUpPickup,
	D_VehicleMod,
	D_VehiclePaintjob,
	D_VehicleRespray,
	D_PlayerSelectedMenuRow,
	D_PlayerExitedMenu,
	D_PlayerInteriorChange,
	D_PlayerKeyStateChange,
	D_RconLoginAttempt,
	D_PlayerUpdate,
	D_PlayerStreamIn,
	D_PlayerStreamOut,
	D_VehicleStreamIn,
	D_VehicleStreamOut,
	D_DialogResponse,
	D_PlayerClickPlayer,
	D_PlayerExitMenu,
	D_PlayerGiveDamage,
	D_PlayerTakeDamage,
	D_PlayerClickMap,
	D_VehicleDamageStatusUpdate,
	D_UnoccupiedVehicleUpdate,
	D_EnterExitModShop,
	D_PlayerEditObject,
	D_PlayerEditAttachedObject,
	D_PlayerSelectObject,
	D_PlayerClickTextDraw,
	D_PlayerClickPlayerTextDraw,
	D_IncomingConnection,
	D_PlayerWeaponShot,
	D_TrailerUpdate,
	D_ActorStreamIn,
	D_ActorStreamOut,
	D_PlayerGiveDamageActor,
	D_VehicleSirenStateChange,
	D_PlayerCommandTextFail
};

new static bool: g_script_loaded = false;

new static g_module_names[MAX_EVENT_HANDLERS][MAX_MODULE_NAMES];
new static g_num_modules = 0;

new static g_handler_funcs[MAX_EVENTS][MAX_EVENT_HANDLERS][MAX_HANDLER_FUNC_LEN];
new static g_handler_priorities[MAX_EVENTS][MAX_EVENT_HANDLERS] = { -1, ... };
new static g_num_handlers[MAX_EVENTS];

new static g_num_events = 0;

#if defined QMODULE_QCONTAINER_PLAYERLIST
CreateContainer(playerList, MAX_PLAYERS);

#if defined _ALS_IsPlayerConnected
	#undef IsPlayerConnected
#else
	#define _ALS_IsPlayerConnected
#endif
#define IsPlayerConnected(%0) IsValidContainerData(playerList, %0)
#endif

// 메인 콜백
forward __InitMain();

native old_strlen(string[]) = strlen;
#if defined _ALS_strlen
	#undef strlen
#else
	#define _ALS_strlen
#endif
#define strlen(%0) ((IsNull((%0))) ? (0) : (old_strlen((%0))))

public OnFilterScriptInit()
{
#if defined FILTERSCRIPT
	if (!g_script_loaded)
		InitializeQModule(SCRIPT_TYPE_FILTER_SCRIPT);
#endif

	TriggerEvent(D_FilterScriptInit, 1, "");
	return 1;
}

public OnGameModeInit()
{
#if !defined FILTERSCRIPT
	if (!g_script_loaded)
		InitializeQModule(SCRIPT_TYPE_GAME_MODE);
#endif

	TriggerEvent(D_GameModeInit, 1, "");
	return 1;
}

public OnFilterScriptExit()
{
	TriggerEvent(D_FilterScriptExit, 1, "");
	return 1;
}

public OnGameModeExit()
{
	TriggerEvent(D_GameModeExit, 1, "");
	return 1;
}

public OnPlayerRequestClass(playerid, classid)
{
	TriggerEvent(D_PlayerRequestClass, 0, "ii", playerid, classid);
	return 1;
}

public OnPlayerConnect(playerid)
{
	new name[MAX_PLAYER_NAME];

	GetPlayerName(playerid, name, MAX_PLAYER_NAME);

	if (strlen(name) >= 3)
	{
	#if defined QMODULE_QCONTAINER_PLAYERLIST
		AddContainerData(playerList, playerid);
	#endif

		TriggerEvent(D_PlayerConnect, 1, "i", playerid);
	}

	return 1;
}

public OnPlayerDisconnect(playerid, reason)
{
#if defined QMODULE_QCONTAINER_PLAYERLIST
	if (IsPlayerConnected(playerid))
	{
		TriggerEvent(D_PlayerDisconnect, 1, "ii", playerid, reason);

		RemoveContainerData(playerList, playerid);
	}
#else
	TriggerEvent(D_PlayerDisconnect, 1, "ii", playerid, reason);
#endif
	return 1;
}

public OnPlayerSpawn(playerid)
{
	TriggerEvent(D_PlayerSpawn, 1, "i", playerid);
	return 1;
}

public OnPlayerDeath(playerid, killerid, reason)
{
	TriggerEvent(D_PlayerDeath, 1, "iii", playerid, killerid, reason);
	return 1;
}

public OnVehicleSpawn(vehicleid)
{
	TriggerEvent(D_VehicleSpawn, 1, "i", vehicleid);
	return 1;
}

public OnVehicleDeath(vehicleid, killerid)
{
	TriggerEvent(D_VehicleDeath, 1, "ii", vehicleid, killerid);
	return 1;
}

public OnPlayerText(playerid, text[])
{
	strfix(text);

	TriggerEvent(D_PlayerText, 0, "is", playerid, text);
	return 1;
}

public OnPlayerCommandText(playerid, cmdtext[])
{
	new command[145];
	new params[145];

	ParamInitialize(command, params, cmdtext);
	strfix(command);
	strfix(params);

	TriggerEvent(D_PlayerCommandText, 1, "iss", playerid, command, params);

#if defined FILTERSCRIPT
	return 0;
#else
	// 명령어를 찾지 못했을 경우
	TriggerEvent(D_PlayerCommandTextFail, 1, "is", playerid, command);
	return 1;
#endif
}

public OnPlayerEnterVehicle(playerid, vehicleid, ispassenger)
{
	TriggerEvent(D_PlayerEnterVehicle, 1, "iii", playerid, vehicleid, ispassenger);
	return 1;
}

public OnPlayerExitVehicle(playerid, vehicleid)
{
	TriggerEvent(D_PlayerExitVehicle, 1, "ii", playerid, vehicleid);
	return 1;
}

public OnPlayerStateChange(playerid, newstate, oldstate)
{
	TriggerEvent(D_PlayerStateChange, 1, "iii", playerid, newstate, oldstate);
	return 1;
}

public OnPlayerEnterCheckpoint(playerid)
{
	TriggerEvent(D_PlayerEnterCheckpoint, 1, "i", playerid);
	return 1;
}

public OnPlayerLeaveCheckpoint(playerid)
{
	TriggerEvent(D_PlayerLeaveCheckpoint, 1, "i", playerid);
	return 1;
}

public OnPlayerEnterRaceCheckpoint(playerid)
{
	TriggerEvent(D_PlayerEnterRaceCheckpoint, 1, "i", playerid);
	return 1;
}

public OnPlayerLeaveRaceCheckpoint(playerid)
{
	TriggerEvent(D_PlayerLeaveRaceCheckpoint, 1, "i", playerid);
	return 1;
}

public OnRconCommand(cmd[])
{
	new val;

	strfix(cmd);

	HandlerLoop(D_RconCommand)
	{
		if ((val = HandlerAction(D_RconCommand, "s", cmd)) == 1)
			break;
	}

	if (val == 0)
		printf(" Unknown command: %s", cmd);

	return 1;
}

public OnPlayerRequestSpawn(playerid)
{
	TriggerEvent(D_PlayerRequestClass, 0, "i", playerid);
	return 1;
}

public OnObjectMoved(objectid)
{
	TriggerEvent(D_ObjectMoved, 1, "i", objectid);
	return 1;
}

public OnPlayerObjectMoved(playerid, objectid)
{
	TriggerEvent(D_PlayerObjectMoved, 1, "ii", playerid, objectid);
	return 1;
}

public OnPlayerPickUpPickup(playerid, pickupid)
{
	TriggerEvent(D_PlayerPickUpPickup, 1, "ii", playerid, pickupid);
	return 1;
}

public OnVehicleMod(playerid, vehicleid, componentid)
{
	TriggerEvent(D_VehicleMod, 0, "iii", playerid, vehicleid, componentid);
	return 1;
}

public OnVehiclePaintjob(playerid, vehicleid, paintjobid)
{
	TriggerEvent(D_VehiclePaintjob, 0, "iii", playerid, vehicleid, paintjobid);
	return 1;
}

public OnVehicleRespray(playerid, vehicleid, color1, color2)
{
	TriggerEvent(D_VehicleRespray, 0, "iiii", playerid, vehicleid, color1, color2);
	return 1;
}

public OnPlayerSelectedMenuRow(playerid, row)
{
	TriggerEvent(D_PlayerSelectedMenuRow, 1, "ii", playerid, row);
	return 1;
}

public OnPlayerExitedMenu(playerid)
{
	TriggerEvent(D_PlayerExitMenu, 1, "i", playerid);
	return 1;
}

public OnPlayerInteriorChange(playerid, newinteriorid, oldinteriorid)
{
	TriggerEvent(D_PlayerInteriorChange, 1, "iii", playerid, newinteriorid, oldinteriorid);
	return 1;
}

public OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
	TriggerEvent(D_PlayerKeyStateChange, 1, "iii", playerid, newkeys, oldkeys);
	return 1;
}

public OnRconLoginAttempt(ip[], password[], success)
{
	strfix(ip);
	strfix(password);

	TriggerEvent(D_RconLoginAttempt, 1, "ssi", ip, password, success);
	return 1;
}

public OnPlayerUpdate(playerid)
{
	TriggerEvent(D_PlayerUpdate, 0, "i", playerid);
	return 1;
}

public OnPlayerStreamIn(playerid, forplayerid)
{
	TriggerEvent(D_PlayerStreamIn, 1, "ii", playerid, forplayerid);
	return 1;
}

public OnPlayerStreamOut(playerid, forplayerid)
{
	TriggerEvent(D_PlayerStreamOut, 1, "ii", playerid, forplayerid);
	return 1;
}

public OnVehicleStreamIn(vehicleid, forplayerid)
{
	TriggerEvent(D_VehicleStreamIn, 1, "ii", vehicleid, forplayerid);
	return 1;
}

public OnVehicleStreamOut(vehicleid, forplayerid)
{
	TriggerEvent(D_VehicleStreamOut, 1, "ii", vehicleid, forplayerid);
	return 1;
}

public OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	strfix(inputtext);

	TriggerEvent(D_DialogResponse, 1, "iiiis", playerid, dialogid, response, listitem, inputtext);
	return 0;
}

public OnPlayerClickPlayer(playerid, clickedplayerid, source)
{
	TriggerEvent(D_PlayerClickPlayer, 1, "iii", playerid, clickedplayerid, source);
	return 1;
}

public OnPlayerClickMap(playerid, Float: fX, Float: fY, Float: fZ)
{
	TriggerEvent(D_PlayerClickMap, 1, "ifff", playerid, fX, fY, fZ);
	return 1;
}

public OnVehicleDamageStatusUpdate(vehicleid, playerid)
{
	TriggerEvent(D_VehicleDamageStatusUpdate, 1, "ii", vehicleid, playerid);
	return 1;
}

public OnUnoccupiedVehicleUpdate(vehicleid, playerid, passenger_seat)
{
	TriggerEvent(D_UnoccupiedVehicleUpdate, 0, "iii", vehicleid, playerid, passenger_seat);
	return 1;
}

public OnEnterExitModShop(playerid, enterexit, interiorid)
{
	TriggerEvent(D_EnterExitModShop, 1, "iii", playerid, enterexit, interiorid);
	return 1;
}

public OnPlayerGiveDamage(playerid, damagedid,
						  Float: amount, weaponid, bodypart)
{
	TriggerEvent(D_PlayerGiveDamage, 1, "iifii", playerid, damagedid, amount, weaponid, bodypart);
	return 0;
}

public OnPlayerTakeDamage(playerid, issuerid, Float: amount, weaponid, bodypart)
{
	TriggerEvent(D_PlayerTakeDamage, 1, "iifii", playerid, issuerid, amount, weaponid, bodypart);
	return 0;
}

public OnPlayerEditObject(playerid, playerobject, objectid, response,
						  Float: fX, Float: fY, Float: fZ,
						  Float: fRotX, Float: fRotY, Float: fRotZ)
{
	TriggerEvent(D_PlayerEditObject, 1, "iiiiffffff", playerid, playerobject, objectid, response, fX, fY, fZ, fRotX, fRotY, fRotZ);
	return 0;
}

public OnPlayerEditAttachedObject(
		playerid, response, index, modelid, boneid,
		Float: fOffsetX, Float: fOffsetY, Float: fOffsetZ,
		Float: fRotX, Float: fRotY, Float: fRotZ,
		Float: fScaleX, Float: fScaleY, Float: fScaleZ)
{
	TriggerEvent(D_PlayerEditAttachedObject, 1, "iiiiifffffffff", playerid, response, index, modelid, boneid, fOffsetX, fOffsetY, fOffsetZ, fRotX, fRotY, fRotZ, fScaleX, fScaleY, fScaleZ);
	return 0;
}

public OnPlayerSelectObject(playerid, type, objectid, modelid,
							Float: fX, Float: fY, Float: fZ)
{
	TriggerEvent(D_PlayerSelectObject, 1, "iiiifff", playerid, type, objectid, modelid, fX, fY, fZ);
	return 0;
}

public OnPlayerClickTextDraw(playerid, Text: clickedid)
{
	TriggerEvent(D_PlayerClickTextDraw, 1, "ii", playerid, _: clickedid);
	return 0;
}

public OnPlayerClickPlayerTextDraw(playerid, PlayerText: playertextid)
{
	TriggerEvent(D_PlayerClickTextDraw, 1, "ii", playerid, _: playertextid);
	return 0;
}

public OnIncomingConnection(playerid, ip_address[], port)
{
	TriggerEvent(D_IncomingConnection, 1, "isi", playerid, ip_address, port);
	return 0;
}

public OnPlayerWeaponShot(playerid, weaponid, hittype, hitid,
						  Float: fX, Float: fY, Float: fZ)
{
	TriggerEvent(D_PlayerWeaponShot, 0, "iiiifff", playerid, weaponid, hittype, hitid, fX, fY, fZ);
	return 1;
}

public OnTrailerUpdate(playerid, vehicleid)
{
	TriggerEvent(D_TrailerUpdate, 0, "ii", playerid, vehicleid);
	return 1;
}

public OnActorStreamIn(actorid, forplayerid)
{
	TriggerEvent(D_ActorStreamIn, 1, "ii", actorid, forplayerid);
	return 1;
}

public OnActorStreamOut(actorid, forplayerid)
{
	TriggerEvent(D_ActorStreamIn, 1, "ii", actorid, forplayerid);
	return 1;
}

public OnPlayerGiveDamageActor(playerid, damaged_actorid,
							   Float: amount, weaponid, bodypart)
{
	TriggerEvent(D_PlayerGiveDamageActor, 1, "iifii", playerid, damaged_actorid, amount, weaponid, bodypart);
	return 0;
}

public OnVehicleSirenStateChange(playerid, vehicleid, newstate)
{
	TriggerEvent(D_VehicleSirenStateChange, 1, "iii", playerid, vehicleid, newstate);
	return 0;
}

static stock InsertHandler(eventid, const handler[], priority)
{
	new num_handlers = g_num_handlers[eventid];
	new index = num_handlers;

	if (priority >= 0)
	{
		index = GenerateHandlerID(eventid, priority);
		// 만약 핸들러가 중간에 삽입될 예정일 때
		if (index != num_handlers)
		{
			// i = g_num_handlers[eventid] - 1 이 아닌 이유는 "뒤로 당기는 작업"이기 때문
			for (new i = g_num_handlers[eventid]; i > index; --i)
			{
				g_handler_funcs[eventid][i] = g_handler_funcs[eventid][i - 1];
				g_handler_priorities[eventid][i] =
						g_handler_priorities[eventid][i - 1];
			}
		}
	}

	strcpy(g_handler_funcs[eventid][index], handler);
	g_handler_funcs[eventid][index][MAX_HANDLER_FUNC_LEN - 1] = 0;
	g_handler_priorities[eventid][index] = priority;
	++g_num_handlers[eventid];
	return index;
}

static stock bool: RemoveHandler(eventid, const handler[])
{
	new bool: id_founded = false;
	new num_handlers = g_num_handlers[eventid];

	for (new i = 0; i < num_handlers; ++i)
	{
		if (!id_founded)
		{
			// 해당 핸들러 함수의 위치를 찾은 경우
			if (strcmp(g_handler_funcs[eventid][i], handler, false) == 0)
			{
				--num_handlers;
				id_founded = true;
			}
			else
			{
				continue; // 위치를 찾은 경우에는 이동 작업만 함
			}
		}
		
		// 위치를 찾은 경우 뒤에 있는 기존 핸들러들을 한칸 앞으로 이동
		g_handler_funcs[i] = g_handler_funcs[i + 1];
		g_handler_priorities[i] = g_handler_priorities[i + 1];
	}

	if (id_founded)
	{
		g_handler_funcs[eventid][num_handlers] = "";
		g_handler_priorities[eventid][num_handlers] = -1;
		return true;
	}

	return false;
}

static stock GetHandlerID(eventid, const handler[])
{
	new num_handlers = g_num_handlers[eventid];

	for (new i = 0; i < num_handlers; ++i)
	{
		if (strcmp(g_handler_funcs[eventid][i], handler, false) == 0)
			return i;
	}

	return -1;
}

static stock GenerateHandlerID(eventid, priority)
{
	new num_handlers = g_num_handlers[eventid];

	if (num_handlers >= MAX_EVENT_HANDLERS)
		return -1;

	new id = num_handlers;

	// 우선순위를 지정하지 않은 경우 무조건 마지막 위치 지정
	if (priority == DEFAULT_PRIORITY || priority < 0)
		return id;
	
	new other_priority = -1;

	// 우선순위에 맞는 위치 탐색
	// 탐색에 실패한 경우 마지막 위치로 지정 됨
	for (id = 0; id < num_handlers; ++id)
	{
		other_priority = g_handler_priorities[eventid][id];
		if (other_priority == -1 || other_priority > priority)
			break;
	}

	return id;
}

static stock GetModuleID(const module[])
{
	for (new i = 0; i < g_num_modules; i++)
	{
		if (strcmp(g_module_names[i], module) == 0)
			return i;
	}

	return -1;
}

static stock LoadModule(const module[])
{
	new string[32];

	format(string, sizeof(string), "LoadModule_%s", module);
	CallLocalFunction(string, "");
}

static InitializeQModule(E_SCRIPT_TYPE: script_type)
{
	g_script_loaded = true;

	// 기본 이벤트 등록
	AddEvent("OnFilterScriptInit");
	AddEvent("OnGameModeInit");
	AddEvent("OnFilterScriptExit");
	AddEvent("OnGameModeExit");
	AddEvent("OnPlayerRequestClass");
	AddEvent("OnPlayerConnect");
	AddEvent("OnPlayerDisconnect");
	AddEvent("OnPlayerSpawn");
	AddEvent("OnPlayerDeath");
	AddEvent("OnVehicleSpawn");
	AddEvent("OnVehicleDeath");
	AddEvent("OnPlayerText");
	AddEvent("OnPlayerCommandText");
	AddEvent("OnPlayerEnterVehicle");
	AddEvent("OnPlayerExitVehicle");
	AddEvent("OnPlayerStateChange");
	AddEvent("OnPlayerEnterCheckpoint");
	AddEvent("OnPlayerLeaveCheckpoint");
	AddEvent("OnPlayerEnterRaceCheckpoint");
	AddEvent("OnPlayerLeaveRaceCheckpoint");
	AddEvent("OnRconCommand");
	AddEvent("OnPlayerRequestSpawn");
	AddEvent("OnObjectMoved");
	AddEvent("OnPlayerObjectMoved");
	AddEvent("OnPlayerPickUpPickup");
	AddEvent("OnVehicleMod");
	AddEvent("OnVehiclePaintjob");
	AddEvent("OnVehicleRespray");
	AddEvent("OnPlayerSelectedMenuRow");
	AddEvent("OnPlayerExitedMenu");
	AddEvent("OnPlayerInteriorChange");
	AddEvent("OnPlayerKeyStateChange");
	AddEvent("OnRconLoginAttempt");
	AddEvent("OnPlayerUpdate");
	AddEvent("OnPlayerStreamIn");
	AddEvent("OnPlayerStreamOut");
	AddEvent("OnVehicleStreamIn");
	AddEvent("OnVehicleStreamOut");
	AddEvent("OnDialogResponse");
	AddEvent("OnPlayerClickPlayer");
	AddEvent("OnPlayerExitMenu");
	AddEvent("OnPlayerGiveDamage");
	AddEvent("OnPlayerTakeDamage");
	AddEvent("OnPlayerClickMap");
	AddEvent("OnVehicleDamageStatusUpdate");
	AddEvent("OnUnoccupiedVehicleUpdate");
	AddEvent("OnEnterExitModShop");
	AddEvent("OnPlayerEditObject");
	AddEvent("OnPlayerEditAttachedObject");
	AddEvent("OnPlayerSelectObject");
	AddEvent("OnPlayerClickTextDraw");
	AddEvent("OnPlayerClickPlayerTextDraw");
	AddEvent("OnIncomingConnection");
	AddEvent("OnPlayerWeaponShot");
	AddEvent("OnTrailerUpdate");
	AddEvent("OnActorStreamIn");
	AddEvent("OnActorStreamOut");
	AddEvent("OnPlayerGiveDamageActor");
	AddEvent("OnVehicleSirenStateChange");
	AddEvent("OnPlayerCommandTextFail");

	if (g_num_events != e_NATIVE_EVENTS)
	{
		print("[QModule] Failed to registering Native events.");
		return 0;
	}

	ShowQModuleInitMessage();

	if (script_type == SCRIPT_TYPE_FILTER_SCRIPT)
		AddEventHandler(D_FilterScriptInit, "__InitMain");
	else
		AddEventHandler(D_GameModeInit, "__InitMain");
	
	return 1;
}

stock AddEvent(const eventName[])
{
	if (g_num_events >= MAX_EVENTS)
	{
		print("[QModule] Event is already full. Max event amount: "#MAX_EVENTS"");
		return -1;
	}
	
	if (IsNull(eventName)) {} // 경고 무시
	
#if defined QMODULE_DEBUG_MODE
	printf("[QModule] Event (ID: %d) was added.", g_num_events);
#endif
	return g_num_events++;
}

stock bool: IsValidEvent(eventid)
{
	if (eventid < 0 || eventid >= g_num_events)
	{
		printf("[QModule] Invalid event ID: %d.", eventid);
		if (g_num_events > 0)
			printf("[QModule] Current range is 0 ~ %d", g_num_events - 1);
		else
			print("[QModule] You are not registered any event.");
		
		return false;
	}

	return true;
}

stock AddEventHandler(eventid, const handler[], priority = DEFAULT_PRIORITY)
{
	new index = - 1;

	if (!IsValidEvent(eventid))
		return index;
	
	if (IsNull(handler))
	{
		printf("[QModule] Invalid handler function (Event ID: %d)", eventid);
		return index;
	}

	if (funcidx(handler) == -1)
	{
		printf("[QModule] Undefined symbol \"%s\"", handler);
		return index;
	}

	new num_handlers = g_num_handlers[eventid];
	if (num_handlers >= MAX_EVENT_HANDLERS)
	{
		printf("[QModule] Event ID(id: %d) of handler is already full. Max handler amount: "#MAX_HANDLER_FUNCTION"",
			   eventid);
		return index;
	}

	index = GetHandlerID(eventid, handler);
	if (index != -1)
	{
		index = -1;
		printf("[QModule] Event ID(id: %d) of handler \"%s\" is already defined.",
			   eventid, handler);
		return index;
	}
	
	index = InsertHandler(eventid, handler, priority);
#if defined QMODULE_DEBUG_MODE
	printf("[QModule] \"%s\" Handler was added for Event (ID: %d)",
		   handler, eventid);
#endif
	return index;
}

stock bool: RemoveEventHandler(eventid, const handler[])
{
	if (!IsValidEvent(eventid))
		return false;
	
	if (IsNull(handler))
	{
		printf("[QModule] Invalid handler function name. (Event ID: %d)",
			   eventid);
		return false;
	}

	if (funcidx(handler) == -1)
	{
		printf("[QModule] Undefined symbol \"%s\"", handler);
		return false;
	}
	
	new bool: success = RemoveHandler(eventid, handler);
#if defined QMODULE_DEBUG_MODE
	if (success)
		printf("[QModule] \"%s\" Handler was removed for Event (ID: %d)", handlerFunction, eventid);
#endif

	return success;
}

stock AddModule(const module[])
{
	new moduleid = -1;

	if (g_num_modules >= MAX_EVENT_HANDLERS)
	{
		print("[QModule] Module is already full. Max module amount: "#MAX_EVENT_HANDLERS"");
		return moduleid;
	}

	if (IsNull(module))
	{
		print("[QModule] Invalid module name.");
		return moduleid;
	}
	
	moduleid = GetModuleID(module);
	if (moduleid != -1)
	{
		moduleid = -1;
		printf("[QModule] Module \"%s\" is already defined.", module);
		return moduleid;
	}
	
	strcpy(g_module_names[g_num_modules], module);
	g_module_names[g_num_modules][MAX_MODULE_NAMES - 1] = '\0';
	++g_num_modules;
	
#if defined QMODULE_DEBUG_MODE
	printf("[QModule] \"%s\" Module was added.", module);
#endif

	LoadModule(module);
	return 1;
}

static stock ShowQModuleInitMessage()
{
	print("============================================");
	print("                  QModule                   ");
	print("             version: "QMODULE_ENGINE_VERSION"");
	print("                author: Qoo                 ");
	print("Copyright (c) 2018-2019 Qoo. All rights reserved.");
	print("=============================================");
}
