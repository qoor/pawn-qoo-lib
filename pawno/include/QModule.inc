//=================================================================================================
//											  QModule
//
//											version: v7.3
//											 author: Qoo
//								Copyright (c) 2019 Qoo. All rights reserved.
//
//=================================================================================================

/*���� ����:
v1.0: ���� ������ (LA:RP ��� �˰������� ��������.) Thank you for Acu.
v2.0:
	1. 'public:�Լ���' ���� ����
	2. ���ڿ� ���� �ڵ鷯 ó�� ����ȭ
		�� �������� ���� ũ���� ������ ���� ���� ���ڸ� �����ϰ��� ���ڿ� ������ ����� �ݹ� �Ķ������ ���ڿ��� �����ؼ� ����������,
			���ڿ� ������ ����ִ� ��� \1 ���ڸ�, �׷��� ���� ��� ���ڿ��� �״�� �����Ͽ� �ӵ��� ������.
		�� �ڼ��� ������ strfix ��ũ�� �Լ��� ����.
	3. �ڵ鷯 ȣ���� ���߿� ���� �� �ִ� EventInfoWithSuspend(�̺�ƮID, �̺�Ʈ ���� ��ȯ��, �Ķ���� ����, �ĸ�����) �Լ��� �߰��Ǿ����ϴ�.
	4. strfix ��ũ�� �Լ��� �߰��Ǿ����ϴ�.
		�� ��� �̺�Ʈ���� ���ڿ� ���� �ڵ鷯���� ������ �� �ݵ�� strfix ��ũ�� �Լ��� ���ļ� ������ �մϴ�. �׷��� ������ ũ���ð� �Ͼ�ϴ�.
	5. OnPlayerCommandTextFail(playerid, const cmdtext[], const cmd[]) �ݹ��� �߰��Ǿ����ϴ�.
		�� OnPlayerCommandText�� �ڵ鷯���� ���ɾ ã�� ���ϸ� �ش� �ݹ��� ȣ��˴ϴ�.
v4.0:
	1. HandlerLoop (�̺�ƮID) ��ũ�ΰ� �߰��Ǿ����ϴ�.
	2. HandlerAction (�̺�ƮID, �Ķ���� ����, �Ķ����) ��ũ�� �Լ��� �߰��Ǿ����ϴ�.
v5.0:
	1. EventInfo, EventInfoWithSuspend �Լ��� ���ŵǰ� TriggerEvent(�̺�ƮID, �̺�Ʈ ���� ��ȯ��, �Ķ���� ����, �ĸ�����) �Լ��� �߰��Ǿ����ϴ�.
	2. �ܼ��� �Լ��� ȣ���ϴ� �Լ����� TriggerEvent�� ������ ��ϵ� �̺�Ʈ�� ȣ���ϴ� �Լ��� �����Ǿ����ϴ�.
v5.1:
	1. AddEventHandler �Լ��� �켱���� ���(priority �Ķ����. default = MAX_HANDLER_FUNCTION / 2)�� �߰��Ǿ����ϴ�.
	2. TriggerEventWithBreak, TriggerEventNoSuspend �Լ��� �߰��Ǿ����ϴ�.
v5.2:
	1. MainScript(), InitScript("����") �Լ��� ���� main(), InitModule("����")���� ����Ǿ����ϴ�.
	2. IsValidHandlerEvent(eventid)�� IsValidEvent(eventid)�� ����Ǿ����ϴ�.
v5.3:
	1. OnPlayerCommandTextFail �ݹ��� �����ϰ� ���ɾ ã�� ���� �� D_PlayerCommandTextFail �̺�Ʈ�� ȣ��˴ϴ�.
		�� ������ OnPlayerCommandTextFail �ݹ鿡 ���� �Ķ���� ������ �״�� �Դϴ�.
	2. QMODULE_ENGINE_VERSION ��ũ�ΰ� �߰��Ǿ����ϴ�.
v5.4:
	1. ���ڿ� �Ķ���Ͱ� ���ԵǴ� native �̺�Ʈ���� ������ ����ȭ�߽��ϴ�.
		�� ������ ���ڿ� �Ķ���Ͱ� ���ԵǴ� ����� ���� �̺�Ʈ�� ȣ���ϱ� ���� �̸� ���ڿ� �Ķ���͵��� strfix �Լ��� ���ľ� �մϴ�.
	2. strfix(const source[]) ��ũ�� �Լ��� strfix(source[]) �Լ��� ����Ǿ����ϴ�.
v5.5:
	1. �÷��̾� ���ɾ� ó���� ���� �ý����� ���� �����Ͽ����ϴ�.
		�� �������� ���� '/1234 5678 90'�̶�� �Է� ���� �� playerid, cmdtext[] = "/1234 5678 90", cmd[] = "/1234" �������� ���� �Ǿ��� ���ɾ� �ڿ� ���� �Ķ���͵��� strtok�� ��������,
		���� �� playerid, command[] = "/1234", params[] = "5678 90" �������� ���� �˴ϴ�.
	2. GetParamPoint �Լ��� �߰� �Ǿ����ϴ�.
		�� const params[]: D_PlayerCommandText�� params ���̳� ��Ÿ �������� �����͸� ������ �ϴ� ���ڿ��� �� ������ �ֽ��ϴ�.
		�� index: �Ķ���͸� �ɰ��� �� ��° �Ķ���͸� �˻� �� ������ �˷��ݴϴ�. (�Ķ���� �ε����� 0���� �����մϴ�.)
		�� &start: index��° �Ķ������ ���ڿ� ���� ������ ��ȯ �մϴ�. ã�� ���� ��� -1�� ��ȯ�˴ϴ�.
		�� &end: index��° �Ķ������ ���ڿ� �� ������ ��ȯ �մϴ�. ã�� ���� ��� -1�� ��ȯ�˴ϴ�.
		�� delimiter = ' ': �Ķ���͵��� �����ϴ� ���ڸ� �����մϴ�. ���ɾ�� ���� �������� �Ķ���͸� �����Ƿ� �⺻���� �����Դϴ�.
		�� ��ȯ ��: index��° �Ķ���͸� ã�� ��� 1��, �׷��� ���� ��� 0�� ��ȯ�մϴ�.
	3. IsValidParamIndex �Լ��� �߰� �Ǿ����ϴ�.
		�� const params[]: D_PlayerCommandText�� params ���̳� ��Ÿ �������� �����͸� ������ �ϴ� ���ڿ��� �� ������ �ֽ��ϴ�.
		�� index: �Ķ���͸� �ɰ��� �� ��° �Ķ���͸� �˻� �� ������ �˷��ݴϴ�. (�Ķ���� �ε����� 0���� �����մϴ�.)
		�� delimiter = ' ': �Ķ���͵��� �����ϴ� ���ڸ� �����մϴ�. ���ɾ�� ���� �������� �Ķ���͸� �����Ƿ� �⺻���� �����Դϴ�.
		�� ��ȯ ��: index��° �Ķ���͸� ã�� ��� 1��, �׷��� ���� ��� 0�� ��ȯ �մϴ�.
	4. GetParamString �Լ��� �߰� �Ǿ����ϴ�.
		�� dest[]: index��° �Ķ������ ���ڿ� ���� �� ������ �Ѱ��ݴϴ�. index��° �Ķ���͸� ã�� ���� ��� NULL���� �Էµ˴ϴ�.
		�� const params[]: D_PlayerCommandText�� params ���̳� ��Ÿ �������� �����͸� ������ �ϴ� ���ڿ��� �� ������ �ֽ��ϴ�.
		�� index: �Ķ���͸� �ɰ��� �� ��° �Ķ���͸� �˻� �� ������ �˷��ݴϴ�. (�Ķ���� �ε����� 0���� �����մϴ�.)
		�� size = sizeof(dest): dest ���ڿ��� �迭 ���̸� �Է��մϴ�.
		�� delimiter = ' ': �Ķ���͵��� �����ϴ� ���ڸ� �����մϴ�. ���ɾ�� ���� �������� �Ķ���͸� �����Ƿ� �⺻���� �����Դϴ�.
		�� ��ȯ ��: index��° �Ķ���͸� ã�� ��� 1��, �׷��� ���� ��� 0�� ��ȯ�մϴ�.
	5. GetParamInt, GetParamFloat �Լ��� �߰� �Ǿ����ϴ�.
		�� &var: index��° �Ķ���Ϳ� ����ִ� ���� �� ������ �Ѱ��ݴϴ�. index��° �Ķ���͸� ã�� ���� ��� �� ������ �̷����� �ʽ��ϴ�.
		�� const params[]: D_PlayerCommandText�� params ���̳� ��Ÿ �������� �����͸� ������ �ϴ� ���ڿ��� �� ������ �ֽ��ϴ�.
		�� index: �Ķ���͸� �ɰ��� �� ��° �Ķ���͸� �˻� �� ������ �˷��ݴϴ�. (�Ķ���� �ε����� 0���� �����մϴ�.)
		�� delimiter = ' ': �Ķ���͵��� �����ϴ� ���ڸ� �����մϴ�. ���ɾ�� ���� �������� �Ķ���͸� �����Ƿ� �⺻���� �����Դϴ�.
		�� ��ȯ ��: index��° �Ķ���͸� ã�� ��� 1��, �׷��� ���� ��� 0�� ��ȯ �մϴ�.
	6. MergeParams �Լ��� �߰� �Ǿ����ϴ�.
		�� dest[]: index��° �Ķ���� ���� ������ �Ķ���ͱ��� ��ģ ���ڿ� ���� �� ������ �Ѱ��ݴϴ�. index��° �Ķ���͸� ã�� ���� ��� NULL���� �Էµ˴ϴ�.
		�� const params[]: D_PlayerCommandText�� params ���̳� ��Ÿ �������� �����͸� ������ �ϴ� ���ڿ��� �� ������ �ֽ��ϴ�.
		�� startIndex: �Ķ���͸� �ɰ��� �� ��° �Ķ���� ���� ��ĥ ������ �˷��ݴϴ�. (�Ķ���� �ε����� 0���� �����մϴ�.)
		�� size = sizeof(dest): dest ���ڿ��� �迭 ���̸� �Է��մϴ�.
		�� delimiter = ' ': �Ķ���͵��� �����ϴ� ���ڸ� �����մϴ�. ���ɾ�� ���� �������� �Ķ���͸� �����Ƿ� �⺻���� �����Դϴ�.
		�� ��ȯ ��: �Ķ���� ��ġ�⸦ �������� ��� 1��, �׷��� ���� ��� 0�� ��ȯ �մϴ�.
v6.0:
	1. SA-MP ���� 0.3z�� 0.3.7�� ���� �����մϴ�.
		�� 3������ SA-MP ������ �Ϻ��� �����մϴ�. (0.3d, 0.3z, 0.3.7)
		�� QMODULE_SAMP_VERSION �κ��� ���� ���� ������ ��ġ�ϰ� �ٲ��ּž� �մϴ�.
		�� ���� 0.3.7 �ļ� ������ ������� 0.3.7 ���� ��� �����մϴ�. ��, ���ο� �������� �߰��Ǵ� �Ϻ� �ݹ���� �̺�Ʈ�� �������� �ʱ� ������ ���� ��Ŭ��带 ������ �ֽðų�, AddEvent, TriggerEvent�� ����� ���� �̺�Ʈ�� ������ �ذ� �� ���� ��õ�մϴ�.
v7.0:
	1. QContainer���� playerList ���� �ɼ��� �߰��Ǿ����ϴ�.
		�� QContainer�� �̿��Ͽ� playerList�� ����ϰ� ���� ��� QMODULE_QCONTAINER_PLAYERLIST ���� 1�� �ٲٽø� �˴ϴ�.
		�� QContainer�� ����ϴ� ��� �ǵ����̸� �ɼ��� �Ѵ� ���� ��õ�մϴ�. �� �ɼ��� ���� playerList�� ��忡�� �ٸ� ����� �Ἥ �Ȱ��� ��� ����������, �ڵ尡 ���������� ���� ���ذ� ��������ϴ�.
		�� playerList��, �� ��Ŭ��带 ���� �� ������ �ܼ� �ݺ����� ���� �÷��̾� �ݺ����� �ƴ϶�, ������ ������ ������ �˻��ϰ� �÷��̾� ���� ������ ��Ƶ� Container �����Դϴ�.
		�� IsPlayerConnected �Լ��� ���� ��ŷ�˴ϴ�. playerList�� ���� ������ �÷��̾� ���� ���θ� �˷��ݴϴ�. �ݵ�� ���� �������� QModule�� ������ �ֽʽÿ�. �׷��� ������ QModule���� ���߿� ���� �� ��Ŭ����� ȣȯ�� ������ ���� �� �ֽ��ϴ�.
		�� �÷��̾� �������� ���ô� contloop (new i : playerList) { ... } or contloop (i : playerList) { ... } ��� ���� �������� �̿� �����մϴ�.
v7.1
	1. Params ��ɵ��� ������ �ణ�� ����Ǿ���, ������ ���Ǿ����ϴ�.
		�� �� �Լ��鸶�� �� �� ���ڷ� ���� �� ������ �����ؾ� �մϴ�.
		�� Ex) new intVar; GetParamInt(intVar, params, 0);
		�� GetParamInt�� GetParamFloat�� ���̻� ��ȯ������ ������� ���� ���� �ƴ�, ���� �ùٸ��� ����Ǿ������� ���� ���θ� ��ȯ�մϴ�.
		�� new intVar; if (GetParamInt(intVar, params, 0) == 0) { ... } �̰� '���� 0��° �Ķ���͸� ã�� �� ���� ���'�� ���� ���ǹ��̰� �Ķ���͸� ã�Ҵٸ� �� ���ǹ��� �������� ������, intVar�� ������� ���ϴ�.
		�� ����, GetParamPoint������ delimiter ������ ���������� ������ ��� Params �Լ��鿡�� delimiter�� ������ �� �ֽ��ϴ�.
		�� v5.5�� Changelog�� �ִ� Params �Լ����� ������ ����˴ϴ�.
		�� �� ������Ʈ ���ĺ��� IsValidParamIndex�� ���� Ȱ���ϴ� ���� �ƴ϶� ������ �˻��� �� ���� ���� �������� ��Ȳ������ ����Ͻô� ���� �����մϴ�.
v7.2
	1. Params ��ɵ��� QString���� �����Ͽ����ϴ�.
	2. strfix �Լ��� QString���� �����Ͽ����ϴ�.
	3. �Ϻ� ���ڿ� �Լ� ���ڵ鿡 const�� �߰��Ͽ����ϴ�.

v7.3
	1. SA-MP 0.3.7 �̸� �������� ������ ���� �Ǿ����ϴ�.
*/

#if defined _QModule_included
	#endinput
#endif
#define _QModule_included
#pragma library QModule

#define QMODULE_QCONTAINER_PLAYERLIST 1

#include <a_samp>
#include <QString>

#if QMODULE_QCONTAINER_PLAYERLIST != 0
	#include <QContainer>
#endif

#define QMODULE_ENGINE_VERSION "v7.3"

main() { return 1; }

#define main() forward __InitMain(); public __InitMain()
#define InitModule("%0") forward LoadModule_%0(); public LoadModule_%0()

#define HandlerLoop(%0) for(new %0_i = 0, %0_j = handlerIDX[%0]; %0_i < %0_j; %0_i ++)
#define HandlerAction(%0,"%1"%2) CallLocalFunction(handlerName[%0][%0_i], #%1%2)
/*#define TriggerEvent(%0,"%1"%2) HandlerLoop(%0) CallLocalFunction(handlerName[%0][%0_i], #%1%2)
#define TriggerEvent(%0,%1,"%2"%3); HandlerLoop(%0) { if((CallLocalFunction(handlerName[%0][%0_i], #%2%3)) == %1) return %1; }*/
#define TriggerEvent(%0,%1,%2); HandlerLoop(%0) { if((HandlerAction(%0, %2)) == %1) return %1; }
#define TriggerEventWithBreak(%0,%1,%2); HandlerLoop(%0) { if((HandlerAction(%0, %2)) == %1) break; }
#define TriggerEventNoSuspend(%0,%1); HandlerLoop(%0) { HandlerAction(%0, %1); }

//#define strfix(%0) if (%0[0] == 0) %0[0] = '\1'

#define MAX_EVENTS 128
#define MAX_HANDLER_FUNCTION 128

#define D_FilterScriptInit 0
#define D_GameModeInit 1
#define D_FilterScriptExit 2
#define D_GameModeExit 3
#define D_PlayerRequestClass 4
#define D_PlayerConnect 5
#define D_PlayerDisconnect 6
#define D_PlayerSpawn 7
#define D_PlayerDeath 8
#define D_VehicleSpawn 9
#define D_VehicleDeath 10
#define D_PlayerText 11
#define D_PlayerCommandText 12
#define D_PlayerEnterVehicle 13
#define D_PlayerExitVehicle 14
#define D_PlayerStateChange 15
#define D_PlayerEnterCheckpoint 16
#define D_PlayerLeaveCheckpoint 17
#define D_PlayerEnterRaceCheckpoint 18
#define D_PlayerLeaveRaceCheckpoint 19
#define D_RconCommand 20
#define D_PlayerRequestSpawn 21
#define D_ObjectMoved 22
#define D_PlayerObjectMoved 23
#define D_PlayerPickUpPickup 24
#define D_VehicleMod 25
#define D_VehiclePaintjob 26
#define D_VehicleRespray 27
#define D_PlayerSelectedMenuRow 28
#define D_PlayerExitedMenu 29
#define D_PlayerInteriorChange 30
#define D_PlayerKeyStateChange 31
#define D_RconLoginAttempt 32
#define D_PlayerUpdate 33
#define D_PlayerStreamIn 34
#define D_PlayerStreamOut 35
#define D_VehicleStreamIn 36
#define D_VehicleStreamOut 37
#define D_DialogResponse 38
#define D_PlayerClickPlayer 39
#define D_PlayerExitMenu 40
#define D_PlayerGiveDamage 41
#define D_PlayerTakeDamage 42
#define D_PlayerClickMap 43
#define D_VehicleDamageStatusUpdate 44
#define D_UnoccupiedVehicleUpdate 45
#define D_EnterExitModShop 46
#define D_PlayerEditObject 48
#define D_PlayerEditAttachedObject 49
#define D_PlayerSelectObject 50
#define D_PlayerClickTextDraw 51
#define D_PlayerClickPlayerTextDraw 52
#define D_IncomingConnection 53
#define D_PlayerWeaponShot 54
#define D_TrailerUpdate 55
#define D_ActorStreamIn 56
#define D_ActorStreamOut 57
#define D_PlayerGiveDamageActor 58
#define D_VehicleSirenStateChange 59
#define D_PlayerCommandTextFail 60

new _scriptLoaded;

new moduleName[MAX_HANDLER_FUNCTION][21];
new moduleIDX;

new handlerName[MAX_EVENTS][MAX_HANDLER_FUNCTION][32];
new handlerPriority[MAX_EVENTS][MAX_HANDLER_FUNCTION];
new handlerIDX[MAX_EVENTS];

new eventIDX;

#if QMODULE_QCONTAINER_PLAYERLIST != 0
	CreateContainer(playerList, MAX_PLAYERS);

	stock Qoo_IsPlayerConnected(playerid)
	{
		return (IsValidContainerData(playerList, playerid));
	}
	#if defined _ALS_IsPlayerConnected
		#undef IsPlayerConnected
	#else
		#define _ALS_IsPlayerConnected
	#endif
	#define IsPlayerConnected Qoo_IsPlayerConnected
#endif

stock QModule_strlen(const string[])
{
	if (IsNull(string)) return 0;

	return strlen(string);
}
#if defined _ALS_strlen
	#undef strlen
#else
	#define _ALS_strlen
#endif
#define strlen QModule_strlen

public OnFilterScriptInit()
{
	#if defined FILTERSCRIPT
		if(_scriptLoaded == 0) InitializeQModule(0);
	#endif

	TriggerEvent(D_FilterScriptInit, 1, "");

	return 1;
}

public OnGameModeInit()
{
	#if !defined FILTERSCRIPT
		if(_scriptLoaded == 0) InitializeQModule(1);
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
		#if QMODULE_QCONTAINER_PLAYERLIST != 0
			AddContainerData(playerList, playerid);
		#endif

		TriggerEvent(D_PlayerConnect, 1, "i", playerid);
	}
	
	return 1;
}

public OnPlayerDisconnect(playerid, reason)
{
	#if QMODULE_QCONTAINER_PLAYERLIST != 0
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
		if((val = HandlerAction(D_RconCommand, "s", cmd)) == 1) break;
	}

	if(val == 0) printf(" Unknown command: %s", cmd);

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

public OnPlayerGiveDamage(playerid, damagedid, Float: amount, weaponid, bodypart)
{
	TriggerEvent(D_PlayerGiveDamage, 1, "iifii", playerid, damagedid, amount, weaponid, bodypart);

	return 0;
}

public OnPlayerTakeDamage(playerid, issuerid, Float: amount, weaponid, bodypart)
{
	TriggerEvent(D_PlayerTakeDamage, 1, "iifii", playerid, issuerid, amount, weaponid, bodypart);

	return 0;
}

public OnPlayerEditObject(playerid, playerobject, objectid, response, Float: fX, Float: fY, Float: fZ, Float: fRotX, Float: fRotY, Float: fRotZ)
{
	TriggerEvent(D_PlayerEditObject, 1, "iiiiffffff", playerid, playerobject, objectid, response, fX, fY, fZ, fRotX, fRotY, fRotZ);

	return 0;
}

public OnPlayerEditAttachedObject(playerid, response, index, modelid, boneid, Float: fOffsetX, Float: fOffsetY, Float: fOffsetZ, Float: fRotX, Float: fRotY, Float: fRotZ, Float: fScaleX, Float: fScaleY, Float: fScaleZ)
{
	TriggerEvent(D_PlayerEditAttachedObject, 1, "iiiiifffffffff", playerid, response, index, modelid, boneid, fOffsetX, fOffsetY, fOffsetZ, fRotX, fRotY, fRotZ, fScaleX, fScaleY, fScaleZ);

	return 0;
}

public OnPlayerSelectObject(playerid, type, objectid, modelid, Float: fX, Float: fY, Float: fZ)
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

public OnPlayerWeaponShot(playerid, weaponid, hittype, hitid, Float: fX, Float: fY, Float: fZ)
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

public OnPlayerGiveDamageActor(playerid, damaged_actorid, Float: amount, weaponid, bodypart)
{
	TriggerEvent(D_PlayerGiveDamageActor, 1, "iifii", playerid, damaged_actorid, amount, weaponid, bodypart);

	return 0;
}

public OnVehicleSirenStateChange(playerid, vehicleid, newstate)
{
	TriggerEvent(D_VehicleSirenStateChange, 1, "iii", playerid, vehicleid, newstate);

	return 0;
}

stock AddEvent(const eventName[])
{
	if(eventIDX >= MAX_EVENTS)
	{
		print("[QModule] Event is already full. Max event amount: "#MAX_EVENTS"");
		return -1;
	}
	if(IsNull(eventName)) {} // ignore warning
	
	#if defined QMODULE_DEBUG_MODE
		printf("[QModule] Event (ID: %d) was added.", eventIDX);
	#endif
	
	return eventIDX++;
}

stock AddEventHandler(eventid, const handlerFunction[], priority = MAX_HANDLER_FUNCTION / 2)
{
	if(IsValidEvent(eventid) == 0) return 0;
	if(IsNull(handlerFunction))
	{
		printf("[QModule] Invalid handler function (Event ID: %d)", eventid);
		return 0;
	}
	if(funcidx(handlerFunction) == -1)
	{
		printf("[QModule] Undefined symbol \"%s\"", handlerFunction);
		return 0;
	}

	new i;
	new idx = handlerIDX[eventid];

	for(i = 0; i < idx; i ++)
	{
		if(strcmp(handlerName[eventid][i], handlerFunction) == 0)
		{
			printf("[QModule] Event ID(id: %d) of handler \"%s\" is already defined.", eventid, handlerFunction);
			return 0;
		}
	}


	if(idx >= MAX_HANDLER_FUNCTION)
	{
		printf("[QModule] Event ID(id: %d) of handler is already full. Max handler amount: "#MAX_HANDLER_FUNCTION"", eventid);
		return 0;
	}

	if(priority == -1) idx = 0;
	else
	{
		for(i = 0; i < MAX_HANDLER_FUNCTION; ++i)
		{
			if(handlerPriority[eventid][i] > priority)
			{
				idx = i;

				break;
			}
		}
	}

	if(idx != handlerIDX[eventid])
	{
		new maxIdx = MAX_HANDLER_FUNCTION - 1;

		for(i = maxIdx; i > idx; --i)
		{
			handlerName[eventid][i] = handlerName[eventid][i - 1];
			handlerPriority[eventid][i] = handlerPriority[eventid][i - 1];
		}
	}
	
	strcpy(handlerName[eventid][idx], handlerFunction);
	if(charfind(handlerName[eventid][idx], 0) == -1) handlerName[eventid][idx][31] = 0;

	++handlerIDX[eventid];
	
	#if defined QMODULE_DEBUG_MODE
		printf("[QModule] \"%s\" Handler was added for Event (ID: %d)", handlerFunction, eventid);
	#endif
	
	return 1;
}

stock RemoveEventHandler(eventid, const handlerFunction[])
{
	if(IsValidEvent(eventid) == 0) return 0;
	if(IsNull(handlerFunction))
	{
		printf("[QModule] Invalid handler function name. (Event ID: %d)", eventid);
		return 0;
	}
	if(funcidx(handlerFunction) == -1)
	{
		printf("[QModule] Undefined symbol \"%s\"", handlerFunction);
		return 0;
	}
	
	new idx = handlerIDX[eventid];

	for(new i = 0; i < idx; i ++)
	{
		if(strcmp(handlerName[eventid][i], handlerFunction) == 0)
		{
			handlerIDX[eventid]--;
			idx -= 1;
			
			for(new j = i; j < idx; j ++)
			{
				handlerName[eventid][j] = handlerName[eventid][j + 1];
				handlerPriority[eventid][j] = handlerPriority[eventid][j + 1];
			}

			handlerName[eventid][idx] = "";
			
			#if defined QMODULE_DEBUG_MODE
				printf("[QModule] \"%s\" Handler was removed for Event (ID: %d)", handlerFunction, eventid);
			#endif
			
			return 1;
		}
	}

	return 0;
}

stock AddModule(const module[])
{
	if(moduleIDX >= MAX_HANDLER_FUNCTION)
	{
		print("[QModule] Module is already full. Max module amount: "#MAX_HANDLER_FUNCTION"");
		return 0;
	}
	if(IsNull(module))
	{
		print("[QModule] Invalid module name.");
		return 0;
	}
	
	for(new i = 0; i < moduleIDX; i++)
	{
		if(strcmp(moduleName[i], module) == 0)
		{
			printf("[QModule] Module \"%s\" is already defined.", module);
			return 0;
		}
	}
	
	strcpy(moduleName[moduleIDX], module);
	if(charfind(moduleName[moduleIDX], 0) == -1) moduleName[moduleIDX][20] = 0;
	moduleIDX++;
	
	#if defined QMODULE_DEBUG_MODE
		printf("[QModule] \"%s\" Module was added.", module);
	#endif
	
	new chString[32];
	format(chString, 32, "LoadModule_%s", module);
	CallLocalFunction(chString, "");
	return 1;
}

stock InitializeQModule(type)
{
	_scriptLoaded = 1;

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

	ShowQModuleInitMessage();

	if(type == 0) AddEventHandler(D_FilterScriptInit, "__InitMain");
	else AddEventHandler(D_GameModeInit, "__InitMain");
}

stock IsValidEvent(eventid)
{
	if(eventid < 0) printf("[QModule] Invalid event ID: %d", eventid);
	else if(eventid >= eventIDX) printf("[QModule] Event ID(id: %d) out of range. Current range is: %d", eventid, eventIDX);
	else return 1;

	return 0;
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

/*stock strfix(const source[])
{
	new chString[1024];
	if(IsNull(source) == false) strmid(chString, source, 0, strlen(source), 1024);
	else chString = "NULL";
	return chString;
}*/