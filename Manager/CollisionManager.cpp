//#include "CollisionManager.h"
//#include "../Component/Collider.h"	
//
//
////	静的メンバ変数の初期化
//CollisionManager* CollisionManager::pInstance = nullptr;
//
///*
// *	@brief		コンストラクタ
// *	@tips		外部で生成されないようにアクセス指定子を private	にする
// */
//CollisionManager::CollisionManager()
//	: pColliderArray()
//	, prevs()
//	, currents() {
//}
//
///*
// *	@brief		デストラクタ
// */
//CollisionManager::~CollisionManager() {
//	for (auto pCol : pColliderArray) {
//		if (pCol != nullptr) {
//			delete pCol;
//			pCol = nullptr;
//		}
//	}
//
//	pColliderArray.clear();
//	pColliderArray.shrink_to_fit();
//	prevs.clear();
//	prevs.shrink_to_fit();
//	currents.clear();
//	currents.shrink_to_fit();
//}
//
///*
// *	@function	CreateInstance
// *	@brief		自身のインスタンスを生成する
// */
//void CollisionManager::CreateInstance() {
//	pInstance = new CollisionManager();
//}
//
///*
// *	@function	GetInstance
// *	@brief		自身のインスタンスを取得する唯一の手段
// *	@return		InputManager*	自身のインスタンスのアドレス
// */
//CollisionManager* CollisionManager::GetInstance() {
//	if (pInstance == nullptr)
//		CreateInstance();
//	return pInstance;
//}
//
///*
// *	@function	DestroyInstance
// *	@breif		自身のインスタンスを破棄する唯一の手段
// */
//void CollisionManager::DestroyInstance() {
//	if (pInstance != nullptr) {
//		delete pInstance;
//		pInstance = nullptr;
//	}
//}
//
//void CollisionManager::Update() {
//	//	一元管理配列内の全ての要素に総当たりで衝突検知を行う
//	for (int i = 0; i < pColliderArray.size(); i++) {
//		//	非表示、当たり判定が無効なものは処理しない
//		if (!pColliderArray[i]->GetGameObject()->IsVisible() || !pColliderArray[i]->IsEnable())
//			continue;
//
//		for (int j = i + 1; j < pColliderArray.size(); j++) {
//			if (!pColliderArray[j]->GetGameObject()->IsVisible() || !pColliderArray[j]->IsEnable())
//				continue;
//
//			//	現在の衝突結果を更新
//			currents[i] = CheckHit(pColliderArray[i], pColliderArray[j]);
//			currents[j] = CheckHit(pColliderArray[j], pColliderArray[i]);
//
//			//	当たった瞬間	(!前 && 今)
//			if ((!prevs[i] && currents[i]), (!prevs[j] && currents[j])) {
//				//	OnTriggerEnter
//				pColliderArray[i]->GetGameObject()->OnTriggerEnter(pColliderArray[j]);
//				pColliderArray[j]->GetGameObject()->OnTriggerEnter(pColliderArray[i]);
//			}
//
//			//	当たっている間	(今)
//			else if (currents[i] && currents[j]) {
//				//	OnTriggerStay
//				pColliderArray[i]->GetGameObject()->OnTriggerStay(pColliderArray[j]);
//				pColliderArray[j]->GetGameObject()->OnTriggerStay(pColliderArray[i]);
//			}
//			//	離れている瞬間	(前 && !今)
//			if ((prevs[i] && !currents[i]), (prevs[j] && !currents[j])) {
//				//	OnTriggerExit
//				pColliderArray[i]->GetGameObject()->OnTriggerExit(pColliderArray[j]);
//				pColliderArray[j]->GetGameObject()->OnTriggerExit(pColliderArray[i]);
//			}
//
//			//	1フレーム前の衝突結果を更新
//			prevs[i] = currents[i];
//			prevs[j] = currents[j];
//		}
//	}
//
//}
//
//void CollisionManager::Register(Collider* _pCol) {
//	//	一元管理配列に追加する
//	pColliderArray.push_back(_pCol);
//
//	//	衝突結果配列にも追加
//	prevs.push_back(false);
//	currents.push_back(false);
//}
//
//void CollisionManager::Unregister(Collider* _pCol) {
//	//	2種類の考え方を記載
//
//	//	イテレーターの考え方
//	//	vector の先頭から末尾までの中に _pCol あるかどうか調べる
//	auto itr = std::find(pColliderArray.begin(), pColliderArray.end(), _pCol);
//
//	//	イテレーターの末尾まで進んだ場合が _pCol がなかった時
//	if (itr == pColliderArray.end())
//		return;
//
//	//	配列要素の考え方
//	int index = -1;		//	要素番号
//
//	//	配列の中に検索する要素があるかどうか
//	for (int i = 0; i < pColliderArray.size(); i++) {
//		if (*itr == _pCol) {
//			index = i;		//	あったら要素番号を保存しておく
//			break;
//		}
//	}
//
//	//	指定された要素を削除する
//	pColliderArray.erase(itr);
//	//	衝突結果配列の要素も削除する
//	prevs.erase(prevs.begin() + index);
//	currents.erase(currents.begin() + index);
//}
//
///*
// *	@function	CheckHit
// *	@brief		当たり判定の衝突検知
// *	@param[in]	Collider* _pCol1		当たり判定1
// *	@param[in]	Collider* _pCol2		当たり判定2
// *	@return		bool
// */
//bool CollisionManager::CheckHit(Collider* _pCol1, Collider* _pCol2) {
//	// ダウンキャスト を利用して当たり判定を振り分ける
//	//
//	//	アップキャスト : 派生 is 基底 の関係 == 犬 は 哺乳類 だ -> 安全 ( 100%正しい )
//	//	ダウンキャスト : 基底 is 派生 の関係 == 哺乳類 は 犬 だ -> 危険 ( 犬に対して操作した場合 正しい )
//	//
//	//	ダウンキャスト 行う場合は dynamic_cast<>() を利用する
//	//	static_cast		: 従来のC言語のキャストとほぼ一緒、どんな型でも書かれていたらやる、できない場合はエラー
//	//	dynamic_cast	: 従来のC言語のキャストとほぼ一緒、どんな型でも書かれていたらやる、できない場合はエラー
//	//						ポインタキャストの場合、できない場合は nullptr を返す
//
//
//
//	//	Sphere-○○
//	{
//		//	_pCol1 が SphereCollider* なのかどうかを調べる
//		auto tmp1 = dynamic_cast<CircleCollider*>(_pCol1);
//
//		if (tmp1 != nullptr) {
//			//	pCol1 -> SphereCollider* !!!!!
//
//
//			//	Sphere-Sphere
//			{
//				//	_pCol2 が SphereCollider* なのかどうかを調べる
//				auto tmp2 = dynamic_cast<CircleCollider*>(_pCol2);
//
//				if (tmp2 != nullptr) {
//					//	_pCol2 -> SphereCollider* !!!!!
//
//					//	計算
//					//	2つの中心点を取得
//					VECTOR center1 = tmp1->GetWorldCenter();
//					VECTOR center2 = tmp2->GetWorldCenter();
//
//					//	2点間の差分を求める
//					VECTOR delta = VSub(center1, center2);
//
//					//	当たりの検知
//					//	差分の長さ < 半径1 + 半径2
//					if (VSize(delta) <= tmp1->GetRadius() + tmp2->GetRadius()) {
//						return true;
//					}
//				}
//			}
//
//			//	Sphere-Capsule
//			{
//				//	_pCol2 が CapsuleCollider* なのかどうかを調べる
//				auto tmp2 = dynamic_cast<CircleCollider*>(_pCol2);
//
//				if (tmp2 != nullptr) {
//					//	_pCol2 -> SphereCollider* !!!!!
//
//					//	計算
//				}
//			}
//		}
//	}
//}
//
//
//
