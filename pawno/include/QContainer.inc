//====================================== Qoo Container Core =======================================
//
//											Version: 2.0
//											Made by Qoo
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
//=================================================================================================

#if defined _QContainer_included
	#endinput
#endif
#define _QContainer_included
#pragma library QContainer

/*변수를 선언함. 만약 배열 크기가 20이라면 그의 배수 40부터 배열크기값인 20까지 역순으로 저장함. 왜냐하면 루프가 배열 맨 끝에서부터 배열 크기와 배열값이 일치한지 검사하기 때문.
루프는 배열 크기 - 1값이 나올 때 종료됨.*/
#define CreateContainer(%0,%1) new QContainer: %0[%1 + 1] = { QContainer: (%1 * 2), QContainer: (%1 * 2 - 1), ... }

#define CONTAINER_SIZE CONTAINER_ARRAY_SIZE
#define CONTAINER_ARRAY_SIZE(%0) sizeof(%0) - 1

/*해당 값이 저장돼있는지 확인. 해당 값으로 참조하는 인덱스의 값이 만약 배열 크기 - 1이라면 해당 값은 마지막에 들어간 값이므로 참이고,
만약 배열 크기 - 1보다 작다면 값이 들어가 있으며 뒤에 값이 또 있다는 것을 의미하므로 참이고,
만약 배열 크기 - 1보다 크다면 해당 값이 들어가지 않았다는 것을 의미하므로 거짓*/
#define IsValidContainerData(%0,%1) (%1 >= 0 && %1 < CONTAINER_ARRAY_SIZE(%0) && _: %0[%1] <= CONTAINER_ARRAY_SIZE(%0))

// 메인 반복문. 주석 예시로는 (new i : playerList) 혹은 (i : playerList) (으)로 설명됨.
#define contloop(%0) for (new QCONTAINER_CONTLOOP_1|||QCONTAINER_CONTLOOP_2|||%0|||)

/*new를 필터링 함.
만약 처음 contloop로 만들어진 new QCONTAINER_CONTLOOP_1|||QCONTAINER_CONTLOOP_2|||i:playerList|||가 들어오면
QCONTAINER_CONTLOOP_2|||QCONTAINER_CONTLOOP_1|||i:playerList|||로 변환되고,

만약 QCONTAINER_CONTLOOP_2(으)로 시작하는 매크로로 만들어진 new i=QCONTAINER_CONTLOOP_4|||QCONTAINER_CONTLOOP_3|||new i:playerList|||가 들어오면
QCONTAINER_CONTLOOP_3|||i=QCONTAINER_CONTLOOP_4|||new i|||playerList|||로 변환되어
QCONTAINER_CONTLOOP_3로 시작하는 매크로가 호출됨.

만약 QCONTAINER_CONTLOOP_3(으)로 시작하는 매크로로 만들어진 new QCONTAINER_CONTLOOP_5;Player: i|||QCONTAINER_CONTLOOP_6|||playerList|||가 들어오면
QCONTAINER_CONTLOOP_6|||QCONTAINER_CONTLOOP_5;i|||*/
#define new%0|||%1|||%2:%3||| %1|||%0|||%2|||%3|||

/*만약 new가 없이 바로 변수명으로 시작하면
i=QCONTAINER_CONTLOOP_4|||QCONTAINER_CONTLOOP_3|||i:playerList||| 이렇게 변환되고,
QCONTAINER_CONTLOOP_4(으)로 시작하는 매크로가 바로 호출되어 반복문이 완성됨.

그렇지 않고 'new 변수명'으로 시작하면 new i=QCONTAINER_CONTLOOP_4|||QCONTAINER_CONTLOOP_3|||new i:playerList||| 이렇게 변환되고,
new%0(으)로 시작하는 매크로가 다시 한 번 더 호출 됨.*/
#define QCONTAINER_CONTLOOP_2|||%0|||%1|||%2||| %1=QCONTAINER_CONTLOOP_4|||QCONTAINER_CONTLOOP_3|||%1:%2|||

/*'new 변수명'으로 시작할 때 new%0 매크로가 실행되며 QCONTAINER_CONTLOOP_3|||i=QCONTAINER_CONTLOOP_4|||new i|||playerList로 변환되면
QCONTAINER_CONTLOOP_5;i|||QCONTAINER_CONTLOOP_6|||playerList||| 이렇게 변환되고,
QCONTAINER_CONTLOOP_5;%0로 시작하는 매크로가 호출됨.*/
#define QCONTAINER_CONTLOOP_3|||%0=QCONTAINER_CONTLOOP_4|||%1|||%2||| new QCONTAINER_CONTLOOP_5;%0|||QCONTAINER_CONTLOOP_6|||%2|||

// new가 없이 변수명으로만 시작할 때 호출되는 매크로
#define QCONTAINER_CONTLOOP_4|||QCONTAINER_CONTLOOP_3|||%0:%1||| CONTAINER_ARRAY_SIZE(%1); (%0 = _: %1[%0]) < CONTAINER_ARRAY_SIZE(%1);

// 'new 변수명'으로 시작할 때 호출되는 매크로
#define QCONTAINER_CONTLOOP_5;%0|||QCONTAINER_CONTLOOP_6|||%1||| %0 = CONTAINER_ARRAY_SIZE(%1); (%0 = _: %1[%0]) < CONTAINER_ARRAY_SIZE(%1);

// 'new 태그명: 변수명'으로 시작할 때 호출되는 매크로
#define QCONTAINER_CONTLOOP_6|||%0QCONTAINER_CONTLOOP_5;%1|||%2|||%3||| new %1: %2 = %1: (CONTAINER_ARRAY_SIZE(%3)); _: (%2 = %1: %3[_: %2]) < CONTAINER_ARRAY_SIZE(%3);

/*맨 첫번째로 들어가는 값은 항상 맨 마지막 배열에 들어가고, 해당 값으로 참조하는 인덱스에는 맨 마지막 배열에 들어가 있던 배열 크기 - 1이 들어가 루프를 종료시킴.
그 후에 들어가는 값은 예를 들어 이전에 들어왔던 값이 1이었고 그다음 2가 들어간다면 1번 인덱스에 2가 들어가고 2번 인덱스에 원래 1번 인덱스가 가지고 있었던 값이 들어감.
만약 반대로 이전에 들어왔던 값이 2이었고 그다음 1이 들어간다면 2가 들어가 있는 인덱스에 1을 채우고 1번 인덱스에 2가 들어감.

배열에서 배열 크기 - 1보다 작은 값이 들어가 있다면 그 다음번에 참조할 배열을 가리킴과 동시에 참조할 수 있는 값이 되는 것이고
배열에서 배열 크기 - 1이 들어가 있다면 해당 인덱스가 마지막 값이라는 뜻임.
배열에서 배열 크기 - 1보다 큰 값이 들어가 있다면 아직 해당 인덱스값이 값으로 들어오지 않았다는 뜻임.*/
stock AddContainerData(QContainer: contArray[], inputValue, size = sizeof(contArray))
{
	--size;
	
	if (inputValue < 0 || inputValue >= size || _: contArray[inputValue] <= size) return 0;
	
	new currentIndex = size, nextValue = _: contArray[currentIndex];
	
	while (nextValue < inputValue)
	{
		currentIndex = nextValue;
		nextValue = _: contArray[currentIndex];
	}
	
	contArray[currentIndex] = QContainer: inputValue;
	contArray[inputValue] = QContainer: nextValue;
	
	return 1;
}

/*만약 값이 한 개만 들어온 상태라면 곧바로 해당 값으로 참조하는 인덱스에 들어가 있던 배열 크기 - 1이 맨 마지막 인덱스에 들어가고,
해당 값으로 참조하는 인덱스에는 배열 크기 - 1보다 큰 값을 넣어서 혹시나 있을 오류를 사전에 방지함.

만약 값이 여러개가 들어온 상태라면 지워질 값이 들어간 인덱스를 찾아 지워질 값으로 참조하는 인덱스에 있는 값을 넣고(즉, 다음으로 참조할 인덱스나 마지막을 알리는 배열 크기 - 1이 들어갈 것임),
지워질 값으로 참조하는 인덱스에는 배열 크기 - 1보다 큰 값을 넣어 루프에서 참조할 값에서 제외시킴.*/
stock RemoveContainerData(QContainer: contArray[], rmvValue, size = sizeof(contArray))
{
	--size;
	
	if (rmvValue < 0 || rmvValue >= size || _: contArray[rmvValue] > size) return 0;
	
	new currentIndex = size, nextValue = _: contArray[currentIndex];
	
	while (nextValue != rmvValue)
	{
		currentIndex = nextValue;
		nextValue = _: contArray[currentIndex];
	}
	
	contArray[currentIndex] = contArray[rmvValue];
	contArray[rmvValue] = QContainer: (size + 1);
	
	return 1;
}
