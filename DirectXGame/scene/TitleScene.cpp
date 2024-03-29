#include "TitleScene.h"
#include "AxisIndicator.h"
#include "ImGuiManager.h"
#include "TextureManager.h"
#include <cassert>
#include <math.h>
#include<fstream>

TitleScene::TitleScene()
{
}

TitleScene::~TitleScene()
{
	delete title_; 
	delete manual_;


}

void TitleScene::Initialize()
{
	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();

	
	uint32_t textureTitle = TextureManager::Load("title.png");
	uint32_t textureManual = TextureManager::Load("manual.png");

	
	title_ = Sprite::Create(textureTitle, {640.0f, 360.0f}, {1.0f, 1.0f, 1.0f, 1}, {0.5f, 0.5f});
	manual_ = Sprite::Create(textureManual, {640.0f, 360.0f}, {1.0f, 1.0f, 1.0f, 1}, {0.5f, 0.5f});

	soundDataHandle_ = audio_->LoadWave("title.wav");

}

void TitleScene::Update()
{
	if (!audio_->IsPlaying(voiceHandle_)) {

		voiceHandle_ = audio_->PlayWave(soundDataHandle_);
	}
	
	  XINPUT_STATE joyState;

	if (Input::GetInstance()->GetJoystickState(0, joyState)) {
	
		  if (joyState.Gamepad.wButtons == XINPUT_GAMEPAD_A && titleMenu == kManual) {
			titleMenu = kTitle;
			audio_->StopWave(voiceHandle_);
			isSceneEnd = true;
		} else {
			isSceneEnd = false;
		}
	
		 if (input_->TriggerKey(DIK_SPACE) && titleMenu == kTitle) {

			titleMenu = kManual;
		} 

		 if (input_->TriggerKey(DIK_R)) {

			titleMenu = kTitle;
		} 

	}

	

	    



}

void TitleScene::Draw()
{

	// コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに背景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();
	// 深度バッファクリア
	dxCommon_->ClearDepthBuffer();
#pragma endregion

#pragma region 3Dオブジェクト描画
	// 3Dオブジェクト描画前処理
	Model::PreDraw(commandList);

	/// <summary>
	/// ここに3Dオブジェクトの描画処理を追加できる
	/// </summary>



	

	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる

	

	if (titleMenu == kTitle) {

		  title_->Draw();
	}

	if ( titleMenu == kManual) {

		   manual_->Draw();
	} 


	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion

}
