#include "SampleScene.h"
#include "GameObject.h"

//추가하고자 하는 컴포넌트 해더 파일 포함
#include "Bookcase.h"

void SampleScene::CreateScene()
{
	//생성자 파라미터로 게임오브젝트 이름
	GameObject* bookcase = new GameObject("Bookcase");

	//컴포넌트 추가
	bookcase->AddComponent(new Bookcase());

	//씬에 게임오브젝트 추가
	AddGameObject(bookcase);
}